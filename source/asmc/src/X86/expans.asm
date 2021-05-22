; EXPANS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; do macro expansion.
;
; functions:
; - myltoa()         generic function which replaces ltoa()
; - RunMacro         run a macro
; - ExpandText       expand a source line when % operator is at pos 0
; - ExpandLineItems   expand parts of a source line
; - ExpandLine       expand a source line
; - ExpandLiterals    expand <> or {} literals for struct initialization
;

include asmc.inc
include memalloc.inc
include malloc.inc
include parser.inc
include preproc.inc
include expreval.inc
include equate.inc
include input.inc
include tokenize.inc
include macro.inc
include condasm.inc
include listing.inc
include fltintrn.inc

public MacroLocals

;; TEVALUE_UNSIGNED
;; 1 = the % operator used in an TEXTEQU expression is supposed to
;;     return an UNSIGNED value ( Masm-compatible ).

TEVALUE_UNSIGNED equ 1
MAX_TEXTMACRO_NESTING equ 20

GetMacroLine proto :ptr macro_instance, :string_t
.data
MacroLocals int_t 0     ;; counter for LOCAL names
MacroLevel  dd 0        ;; current macro nesting level
__digits    char_t "0123456789ABCDEF"

    .code

;; C ltoa() isn't fully compatible since hex digits are lower case.
;; for JWasm, it's ensured that 2 <= radix <= 16.

myltoa proc uses esi edi ebx value:uint_t, buffer:string_t, radix:uint_t, sign:int_t, addzero:int_t

  local tmpbuf[34]:char_t

    mov edi,buffer
    mov ebx,value
    .if sign
        mov byte ptr [edi],'-'
        inc edi
        neg ebx
    .elseif ebx == 0
        mov word ptr [edi],'0'
        .return edi
    .endif
    .for ( ecx = radix, esi = 33, tmpbuf[33] = 0 : ebx : )
        mov eax,ebx
        xor edx,edx
        div ecx
        mov ebx,eax
        dec esi
        mov tmpbuf[esi],__digits[edx]
    .endf
    .if addzero && tmpbuf[esi] > '9' ;; v2: add a leading '0' if first digit is alpha
        mov byte ptr [edi],'0'
        inc edi
    .endif
    mov ecx,34
    sub ecx,esi
    lea esi,tmpbuf[esi]
    rep movsb
    mov eax,buffer
    ret

myltoa endp

;; Read the current (macro) queue until it's done.

SkipMacro proc private tokenarray:token_t

    local buffer:ptr char_t

    mov buffer,alloca(ModuleInfo.max_line_len)

    ;; The queue isn't just thrown away, because any
    ;; coditional assembly directives found in the source
    ;; must be executed.

    .while GetTextLine( buffer )
        Tokenize( buffer, 0, tokenarray, TOK_DEFAULT )
    .endw
    ret

SkipMacro endp

ExpandTMacro proto :string_t, :token_t, :int_t, :int_t

;; run a macro.
;; - macro:  macro item
;; - out:    value to return (for macro functions)
;; - label:  token of label ( or -1 if none )
;; - is_exitm: returns TRUE if EXITM has been hit
;; returns index of token not processed or -1 on errors

    assume esi:dsym_t
    assume edi:ptr macro_info
    assume ebx:token_t

RunMacro proc uses esi edi ebx mac:dsym_t, idx:int_t, tokenarray:token_t,
        _out:string_t, mflags:int_t, is_exitm:ptr int_t

    local currparm          :string_t
    local savedStringBuffer :string_t
    local i                 :int_t
    local _retm             :int_t
    local parmidx           :int_t
    local skipcomma         :int_t
    local varargcnt         :int_t
    local bracket_level     :int_t      ;; () level (needed for macro functions)
    local parm_end_delim    :int_t      ;; parameter end delimiter
    local p                 :string_t
    local parmstrings       :string_t
    local info              :ptr macro_info
    local lnode             :srcline_t
    local sym               :asym_t
    local opndx             :expr
    local mi                :macro_instance
    local oldstat           :input_status
    local oldifnesting      :int_t
    local cntgoto           :int_t
    local inside_literal    :int_t
    local inside_angle_brackets:int_t
    local old_tokencount    :int_t
    local max               :int_t
    local cnt               :int_t
    local cnt_opnum         :int_t
    local is_exitm2         :int_t
    local len               :int_t
    local cvt               :FLTINFO

    mov savedStringBuffer,StringBufferEnd
    mov _retm,0
    .if idx > 1
        inc _retm
    .endif
    mov bracket_level,-1

    .return asmerr( 2123 ) .if MacroLevel == MAX_MACRO_NESTING

    mov  mi.parm_array,NULL
    mov  esi,mac
    mov  edi,[esi].macroinfo
    mov  info,edi
    imul ebx,idx,asm_tok
    add  ebx,tokenarray

    ;; invokation of macro functions requires params enclosed in "()"

    mov parm_end_delim,T_FINAL
    .if [esi].sym.mac_flag & M_ISFUNC
        .if [ebx].token == T_OP_BRACKET ;; should be always true
            inc idx
            add ebx,16
            mov parm_end_delim,T_CL_BRACKET
            mov bracket_level,1
        .endif
        mov eax,_out ;; v2.08: init return value buffer
        mov byte ptr [eax],0
    .endif
    ;; v2.08: if macro is purged, return "void"
    .if [esi].sym.mac_flag & M_PURGED
        .if bracket_level > 0
            .for ( : bracket_level && [ebx].token != T_FINAL: idx++, ebx += 16 )
                .if [ebx].token == T_OP_BRACKET
                    inc bracket_level
                .elseif [ebx].token == T_CL_BRACKET
                    dec bracket_level
                .endif
            .endf
        .else
            mov idx,Token_Count
        .endif
        .return idx
    .endif

    .if [edi].parmcnt

        movzx   ecx,[edi].parmcnt
        mov     eax,ModuleInfo.max_line_len
        add     eax,eax
        lea     eax,[eax+ecx*4]
        mov     mi.parm_array,alloca(eax)
        movzx   ecx,[edi].parmcnt
        lea     eax,[eax+ecx*4]
        mov     parmstrings,eax ;; init the macro arguments pointer
        mov     currparm,eax
    .endif

    ;; now get all the parameters from the original src line.
    ;; macro parameters are expanded if
    ;; - it is a macro function call            or
    ;; - the expansion operator (%) is found

    mov ebx,tokenarray
    mov parmidx,0
    .if [esi].sym.mac_flag & M_LABEL
        .if mflags & MF_LABEL
            mov i,strlen( [ebx].string_ptr )
            mov ecx,parmidx
            mov edx,mi.parm_array
            mov [edx+ecx*4],currparm
            mov ecx,i
            inc ecx
            mov edi,currparm
            mov esi,[ebx].string_ptr
            rep movsb
            mov currparm,GetAlignedPointer( currparm, i )
        .else
            mov ecx,parmidx
            mov edx,mi.parm_array
            lea eax,@CStr("")
            mov [edx+ecx*4],eax
        .endif
        inc parmidx
    .endif
    mov eax,is_exitm
    mov dword ptr [eax],FALSE

    ;; v2.08: allow T_FINAL to be chained, lastidx==0 is true final
    imul eax,Token_Count,asm_tok
    mov  [ebx+eax].lastidx,0
    imul eax,idx,asm_tok
    add  ebx,eax

    .for ( varargcnt = 0, skipcomma = 0 : : parmidx++ )

        ;; v2.09: don't skip comma if it was the last argument.
        ;; this will a) make a trailing comma trigger warning 'too many arguments...'
        ;; and b), argument handling of FOR loop is significantly simplified.

        mov esi,mac
        mov edi,info
        movzx ecx,[edi].parmcnt
        .break .if parmidx >= ecx

        imul ebx,idx,asm_tok
        add  ebx,tokenarray
        .if [ebx].token == T_COMMA && skipcomma
            inc idx
            add ebx,16
        .endif

        mov skipcomma,1
        dec ecx

        .if ( [ebx].token == T_FINAL || [ebx].token == parm_end_delim || \
            ( [ebx].token == T_COMMA && \
              ( !( [esi].sym.mac_flag & M_ISVARARG ) || parmidx != ecx ) ) )

            ;; it's a blank parm
            imul eax,parmidx,mparm_list
            mov ecx,[edi].parmlist
            add ecx,eax
            .if [ecx].mparm_list.required
                .return asmerr( 2125 )
            .endif
            .if varargcnt == 0
                imul edx,parmidx,ptr_t
                add edx,mi.parm_array
                mov [edx],[ecx].mparm_list.deflt
            .endif
        .else

            mov inside_literal,0
            mov inside_angle_brackets,0
            mov old_tokencount,Token_Count

            mov edx,currparm
            mov byte ptr [edx],0

            .for ( p = edx : : idx++ )

                imul ebx,idx,asm_tok
                add  ebx,tokenarray
                .break .if ( [ebx].token == T_FINAL || [ebx].token == T_COMMA ) && !inside_literal

                ;; if were're inside a literal, go up one level and continue scanning the argument

                .if [ebx].token == T_FINAL

                    mov  idx,[ebx].lastidx ;; restore token index
                    imul ebx,eax,asm_tok
                    add  ebx,tokenarray

                    dec inside_literal
                    .if [ebx].string_delim == '<'
                        mov inside_angle_brackets,0
                    .else
                        mov eax,p
                        inc p
                        mov byte ptr [eax],'}'
                    .endif
                    .continue
                .endif

                .if ( [ebx].token == T_PERCENT )

                    ;; expansion of macro parameters.
                    ;; if the token behind % is not a text macro or macro function
                    ;; the expression will be always expanded and evaluated.
                    ;; Else it is expanded, but only evaluated if

                    inc idx
                    add ebx,16
                    .while [ebx].token == T_PERCENT
                        inc idx
                        add ebx,16
                    .endw
                    mov i,idx
                    mov cnt_opnum,1
                    .if [ebx].token == T_ID
                        mov sym,SymSearch( [ebx].string_ptr )
                        .if ( eax && [eax].asym.flags & S_ISDEFINED && ( [eax].asym.state == SYM_TMACRO || \
                             ( [eax].asym.state == SYM_MACRO && ( [eax].asym.mac_flag & M_ISFUNC ) && \
                               [ebx+16].token == T_OP_BRACKET ) ) )
                            mov cnt_opnum,0
                        .endif
                    .endif

                    .for ( cnt = 0 :: i++ )

                        imul ebx,i,asm_tok
                        add  ebx,tokenarray
                        .break .if [ebx].token == T_FINAL || [ebx].token == T_COMMA

                        mov edx,[ebx].string_ptr
                        .if ( is_valid_id_first_char( [edx] ) )

                            .if ( [ebx+16].token == T_OP_BRACKET )

                                add i,2
                                add ebx,32
                                .for ( ecx = 1: ecx && [ebx].token != T_FINAL: i++, ebx += 16 )
                                    .if [ebx].token == T_OP_BRACKET
                                        inc ecx
                                    .elseif [ebx].token == T_CL_BRACKET
                                        dec ecx
                                    .endif
                                .endf
                                dec i
                            .endif
                            .continue
                        .endif
                        ;; count brackets
                        .if parm_end_delim == T_CL_BRACKET
                            .if [ebx].token == T_OP_BRACKET
                                inc cnt
                            .elseif [ebx].token == T_CL_BRACKET
                                .break .if cnt == 0
                                dec cnt
                            .endif
                        .endif

                        ;; stop if undelimited string occurs (need to scan for '!')
                        .break .if ( [ebx].token == T_STRING && [ebx].string_delim == 0 )

                        ;; names dot and amp are ok
                        .if !( [ebx].token == T_DOT || [ebx].token == '&' || [ebx].token == '%' )
                            inc cnt_opnum ;; anything else will trigger numeric evaluation
                        .endif
                    .endf

                    .if i == idx ;; no items except %?
                        dec idx
                        .continue
                    .endif

                    mov   ecx,[ebx].tokpos
                    imul  ebx,idx,asm_tok
                    add   ebx,tokenarray
                    mov   esi,[ebx].tokpos
                    sub   ecx,esi
                    .while islspace( [esi+ecx-1] )
                        dec ecx
                    .endw
                    mov cnt,ecx
                    mov edi,p
                    rep movsb
                    mov byte ptr [edi],0

                    .if ExpandText( p, tokenarray, FALSE ) == ERROR
                        mov ecx,savedStringBuffer
                        mov StringBufferEnd,ecx
                        .return
                    .endif
                    mov idx,i
                    dec idx
                    .if cnt_opnum
                        ;; convert numeric expression into a string
                        mov edx,Token_Count
                        inc edx
                        mov max,Tokenize( p, edx, tokenarray, TOK_RESCAN )
                        mov i,Token_Count
                        inc i
                        ;; the % operator won't accept forward references.
                        ;; v2.09: flag EXPF_NOUNDEF set.
                        .if EvalOperand( &i, tokenarray, max, &opndx, EXPF_NOUNDEF ) == ERROR
                            mov opndx.value,0
                            mov opndx.hvalue,0
                        .elseif ( opndx.kind != EXPR_CONST && \
                               !( opndx.kind == EXPR_FLOAT && opndx.mem_type == MT_REAL16 ) )
                            asmerr( 2026 )
                            mov opndx.value,0
                            mov opndx.hvalue,0
                        .endif
                        ;; v2.08: accept constant and copy any stuff that's following
                        .if opndx.kind == EXPR_CONST
                            xor eax,eax
                            cmp opndx.hvalue,0
                            setl al
                            myltoa( opndx.uvalue, StringBufferEnd, ModuleInfo.radix, eax, FALSE )
                        .elseif ( opndx.kind == EXPR_FLOAT && opndx.mem_type == MT_REAL16 )
                            .if ( ( opndx.value == 16 && opndx.h64_h == 0 ) )
                                strcpy( StringBufferEnd, "16" )
                            .else

                                mov cvt.expchar,'e'
                                mov cvt.expwidth,3
                                mov cvt.ndigits,ModuleInfo.floatdigits
                                mov cvt.bufsize,ModuleInfo.max_line_len

                                .if ( ModuleInfo.floatformat == 'e' )
                                    mov cvt.scale,1
                                    mov cvt.flags,_ST_E
                                .elseif ( ModuleInfo.floatformat == 'g' )
                                    mov cvt.scale,1
                                    mov cvt.flags,_ST_G
                                .else
                                    mov cvt.scale,0
                                    mov cvt.flags,_ST_F
if 0
                                    movzx ecx,word ptr opndx.h64_h[2]
                                    and ecx,0x7FFF
                                    .if ecx < 0x3FFF
                                        sub  ecx,0x3FFE
                                        mov  eax,30103
                                        imul ecx
                                        mov  ecx,100000
                                        idiv ecx
                                        neg  eax
                                        inc  eax
                                        mov cvt.ndigits,eax
                                    .endif
endif
                                .endif
                                mov esi,StringBufferEnd
                                inc esi
                                _flttostr( &opndx, &cvt, esi, _ST_QUADFLOAT )
                                .if ( cvt.sign == -1 )
                                    mov byte ptr [esi-1],'-'
                                .else
                                    strcpy( StringBufferEnd, esi )
                                .endif
                            .endif
                        .endif
                        .if ( i != max )
                            ;
                            ; the evaluator was unable to evaluate the full expression. the rest
                            ; has to be "copied"
                            ;
                            imul ebx,i,asm_tok
                            add  ebx,tokenarray
                            strcat( StringBufferEnd, [ebx].tokpos )
                        .endif
                        strcpy( p, StringBufferEnd )
                    .endif
                    add p,strlen( p )
                    .continue
                .endif

                imul ebx,idx,asm_tok
                add  ebx,tokenarray

                .if [ebx].token == T_STRING && [ebx].string_delim == '{'

                    mov ecx,[ebx].string_ptr
                    mov ebx,idx
                    mov eax,p ;; copy the '{'
                    inc p
                    mov byte ptr [eax],'{'
                    ;; the string must be tokenized
                    inc inside_literal
                    mov idx,Token_Count
                    mov Token_Count,Tokenize( ecx, &[eax+1], tokenarray, TOK_RESCAN or TOK_NOCURLBRACES )
                    shl eax,4
                    add eax,tokenarray
                    mov [eax].asm_tok.lastidx,ebx
                    .continue
                .endif

                .if inside_angle_brackets == 0
                    ;; track brackets for macro functions; exit if one more ')' than '(' is found
                    .if bracket_level > 0
                        .if [ebx].token == T_OP_BRACKET
                            inc bracket_level
                        .elseif [ebx].token == T_CL_BRACKET
                            dec bracket_level
                            .break .ifz ;; ( bracket_level == 0 )
                        .endif
                    .endif

                    ;; if there's a literal enclosed in <>, remove the delimiters and
                    ;; tokenize the item (Token_Count must be adjusted, since RunMacro()
                    ;; might be called later!)

                    .if ( [ebx].token == T_STRING && [ebx].string_delim == '<' && inside_angle_brackets == 0 )

                        mov esi,[ebx].tokpos
                        inc esi
                        mov ecx,[ebx+16].tokpos
                        sub ecx,esi
                        mov edx,ecx
                        mov edi,StringBufferEnd
                        rep movsb
                        mov edi,StringBufferEnd
                        .while byte ptr [edi+edx-1] != '>'
                            dec edx
                        .endw
                        mov byte ptr [edi+edx-1],0
                        mov StringBufferEnd,GetAlignedPointer( edi, edx )
                        ;; the string must be tokenized
                        inc inside_literal
                        mov inside_angle_brackets,1

                        mov ebx,idx
                        mov idx,Token_Count
                        mov Token_Count,Tokenize( edi, &[eax+1], tokenarray, TOK_RESCAN )
                        shl eax,4
                        add eax,tokenarray
                        mov [eax].asm_tok.lastidx,ebx

                        ;; copy spaces located before the first token
                        imul ebx,idx,asm_tok
                        add ebx,tokenarray
                        mov ecx,[ebx+16].tokpos
                        sub ecx,edi
                        mov esi,edi
                        mov edi,p
                        rep movsb
                        mov p,edi
                        .continue
                    .endif

                    ;; macros functions must be expanded always.
                    ;; text macros are expanded only selectively

                    .if [ebx].token == T_ID
                        .if SymSearch([ebx].string_ptr)
                            mov sym,eax
                            .if ( [eax].asym.state == SYM_MACRO && [eax].asym.flags & S_ISDEFINED && \
                                [eax].asym.mac_flag & M_ISFUNC && [ebx+16].token == T_OP_BRACKET )
                                inc idx
                                mov idx,RunMacro( sym, idx, tokenarray, p, 0, &is_exitm2 )
                                .if idx < 0
                                    mov StringBufferEnd,savedStringBuffer
                                    .return idx
                                .endif
                                add p,strlen(p)
                                ;; copy spaces behind macro function call
                                imul ebx,idx,asm_tok
                                add  ebx,tokenarray
                                .if [ebx].token != T_FINAL && [ebx].token != T_COMMA
                                    mov esi,[ebx-16].tokpos
                                    inc esi
                                    mov ecx,[ebx].tokpos
                                    sub ecx,esi
                                    mov edi,p
                                    rep movsb
                                    mov p,edi
                                .endif
                                dec idx ;; adjust token index
                                sub ebx,16
                                .continue

                            .elseif ( [eax].asym.state == SYM_TMACRO && [eax].asym.flags & S_ISDEFINED )

                                mov ecx,parmidx
                                mov edx,1
                                shl edx,cl
                                mov edi,info
                                mov esi,mac
                                .if ( [esi].sym.flags & S_PREDEFINED && ( [edi].autoexp & dx ) )

                                    strcpy( p, [eax].asym.string_ptr )
                                    ExpandTMacro( p, tokenarray, FALSE, 0 )
                                    add p,strlen( p )

                                    ;; copy spaces behind text macro
                                    .if ( [ebx+16].token != T_FINAL && [ebx+16].token != T_COMMA )

                                        mov     edx,sym
                                        movzx   esi,[edx].asym.name_size
                                        add     esi,[ebx].tokpos
                                        mov     ecx,[ebx+16].tokpos
                                        sub     ecx,esi
                                        mov     edi,p
                                        rep     movsb
                                        mov     p,edi
                                    .endif
                                    .continue
                                .endif
                            .endif
                        .endif
                    .endif
                .endif

                ;; get length of item
                mov ecx,[ebx+16].tokpos
                sub ecx,[ebx].tokpos
                .if ( !inside_literal && \
                      ( [ebx+16].token == T_COMMA || [ebx+16].token == parm_end_delim ) )

                    mov edx,[ebx].tokpos
                    .while islspace( [edx+ecx-1] )
                        dec ecx
                    .endw
                .endif

                ;; the literal character operator ! is valid for macro arguments

                mov edi,p
                mov esi,[ebx].tokpos
                .if ( [ebx].token == T_STRING && [ebx].string_delim == 0 )

                    add ecx,esi
                    .for : esi < ecx :
                        .if byte ptr [esi] == '!'
                            inc esi
                        .endif
                        movsb
                    .endf
                    mov p,edi
                    .continue
                .endif
                rep movsb
                mov p,edi
            .endf ;; end for

            mov eax,p
            mov byte ptr [eax],0

            ;; restore input status values
            mov Token_Count,old_tokencount
            mov StringBufferEnd,savedStringBuffer

            mov edi,info
            mov esi,mac

            ;; store the macro argument in the parameter array
            movzx eax,[edi].parmcnt
            dec eax
            mov edx,currparm

            .if [esi].sym.mac_flag & M_ISVARARG && parmidx == eax
                .if varargcnt == 0
                    mov eax,mi.parm_array
                    mov ecx,parmidx
                    mov [eax+ecx*4],edx
                .endif
                mov eax,p
                .if [esi].sym.flags & S_PREDEFINED
                    sub eax,currparm
                    GetAlignedPointer( currparm, eax )
                .endif
                mov currparm,eax

                ;; v2.08: Masm swallows the last trailing comma

                .if ( [ebx].token == T_COMMA )

                    inc idx
                    add ebx,16
                    mov edx,eax

                    .if ( !( [esi].sym.mac_flag & M_ISFUNC ) || [ebx].token != parm_end_delim )
                        dec parmidx
                        .if ( !( [esi].sym.flags & S_PREDEFINED ) )
                            mov byte ptr [edx],','
                            inc edx
                            inc currparm
                        .endif
                        mov byte ptr [edx],0
                    .endif
                    mov skipcomma,0
                .endif
                inc varargcnt

            .elseif byte ptr [edx]

                mov eax,mi.parm_array
                mov ecx,parmidx
                mov [eax+ecx*4],edx
                mov ecx,p
                sub ecx,edx
                mov currparm,GetAlignedPointer( edx, ecx )
            .else
                mov edx,mi.parm_array
                mov ecx,parmidx
                lea eax,@CStr("")
                mov [edx+ecx*4],eax
            .endif
        .endif ;;end if
    .endf ;; end for

    ;; for macro functions, check for the terminating ')'
    .if ( bracket_level >= 0 )
        .if ( [ebx].token != T_CL_BRACKET )
            .for ( i = idx: idx < Token_Count && [ebx].token != T_CL_BRACKET: idx++, ebx += 16 )
            .endf
            .if ( idx == Token_Count )
                asmerr( 2157 )
                .return( -1 )
            .else
                ;; v2.09: changed to a warning only (Masm-compatible)
                imul eax,i,asm_tok
                add eax,tokenarray
                asmerr( 4006, [esi].sym.name, [eax].asm_tok.tokpos )
            .endif
        .endif
        inc idx
        add ebx,16
    .elseif ( [ebx].token != T_FINAL )
        ;; v2.05: changed to a warning. That's what Masm does
        ;; v2.09: don't emit a warning if it's a FOR directive
        ;; (in this case, the caller knows better what to do ).

        .if ( !( mflags & MF_IGNARGS ) )
            asmerr( 4006, [esi].sym.name, [ebx].tokpos )
        .endif
    .endif

    ;; a predefined macro func with a function address?

    assume esi:asym_t

    .if ( [esi].flags & S_PREDEFINED && [esi].func_ptr )
        mov mi.parmcnt,varargcnt
        [esi].func_ptr( &mi, _out, tokenarray )
        mov eax,is_exitm
        mov dword ptr [eax],TRUE
        .return idx
    .endif

    mov mi.localstart,MacroLocals
    add MacroLocals,[edi].localcnt ;; adjust global variable MacroLocals

    ;; avoid to use values stored in struct macro_info directly. A macro
    ;; may be redefined within the macro! Hence copy all values that are
    ;; needed later in the while loop to macro_instance!

    mov mi.startline,[edi].lines
    mov mi.currline,NULL
    mov mi.parmcnt,[edi].parmcnt

    .if mi.startline

        mov eax,[esi].name
        .if ( !( [esi].mac_flag & M_ISFUNC ) && byte ptr [eax] )
            LstWriteSrcLine()
        .endif
        .if ( !( mflags & MF_NOSAVE ) )
            mov tokenarray,PushInputStatus( &oldstat )
        .endif

        ;; move the macro instance onto the file stack!
        ;; Also reset the current linenumber!

        mov mi._macro,esi
        PushMacro( &mi )
        inc MacroLevel
        mov oldifnesting,GetIfNestLevel() ;; v2.10
        mov cntgoto,0 ;; v2.10

        ;; Run the assembler until we hit EXITM or ENDM.
        ;; Also handle GOTO and macro label lines!
        ;; v2.08 no need anymore to check the queue level
        ;; v2.11 GetPreprocessedLine() replaced by GetTextLine()
        ;; and PreprocessLine().


        .while ( GetTextLine( CurrSource ) )
            .continue .if ( PreprocessLine( tokenarray ) == 0 )

            mov ebx,tokenarray

            ;; skip macro label lines
            .if ( [ebx].token == T_COLON )
                ;; v2.05: emit the error msg here, not in StoreMacro()
                .if ( [ebx+16].token != T_ID )
                    asmerr(2008, [ebx].tokpos )
                .elseif ( [ebx+32].token != T_FINAL )
                    asmerr(2008, [ebx+32].tokpos )
                .endif
                .continue
            .endif

            .if ( [ebx].token == T_DIRECTIVE )
                .if ( [ebx].tokval == T_EXITM || [ebx].tokval == T_RETM )
                    .if ( ModuleInfo.list && ModuleInfo.list_macro == LM_LISTMACROALL )
                        LstWriteSrcLine()
                    .endif
                    .if ( [ebx+16].token != T_FINAL )
                        ;; v2.05: display error if there's more than 1 argument or
                        ;; the argument isn't a text item

                        .if ( [ebx+16].token != T_STRING || [ebx+16].string_delim != '<' )
                            TextItemError( &[ebx+16] )
                        .elseif ( Token_Count > 2 )
                            asmerr(2008, [ebx+32].tokpos )
                        .elseif ( _out ) ;; return value buffer may be NULL ( loop directives )

                            ;; v2.08a: the <>-literal behind EXITM is handled specifically,
                            ;; macro operator '!' within the literal is only handled
                            ;; if it contains a placeholder (macro argument, macro local ).

                            ;; v2.09: handle '!' inside literal if ANY expansion occurred.
                            ;; To determine text macro or macro function expansion,
                            ;; check if there's a literal in the original line.
                            mov edi,_out
                            mov edx,mi.currline
                            mov eax,[ebx+16].tokpos
                            sub eax,CurrSource
                            mov al,[edx].srcline.line[eax]

                            .if ( !_retm && [ebx].tokval == T_RETM )

                                mov eax,_out
                                mov byte ptr [eax],0

                            .elseif ( [edx].srcline.ph_count || al != '<' )

                                mov ecx,[ebx+16].stringlen
                                inc ecx
                                mov esi,[ebx+16].string_ptr
                                rep movsb

                            .else

                                ;; since the string_ptr member has the !-operator stripped, it
                                ;; cannot be used. To get the original value of the literal,
                                ;; use tokpos.

                                mov esi,[ebx+16].tokpos
                                inc esi
                                mov ecx,[ebx+32].tokpos
                                sub ecx,esi
                                rep movsb
                                dec edi
                                .while( byte ptr [edi] != '>' )
                                    dec edi
                                .endw
                                mov byte ptr [edi],0

                            .endif
                        .endif
                    .endif

                    ;; v2.10: if a goto had occured, rescan the full macro to ensure that
                    ;; the "if"-nesting level is ok.

                    .if cntgoto
                        mov mi.currline,NULL
                        SetLineNumber( 0 )
                        SetIfNestLevel( oldifnesting )
                    .endif

                    SkipMacro( tokenarray )
                    mov eax,is_exitm
                    mov dword ptr [eax],TRUE
                    .break

                .elseif ( [ebx].tokval == T_GOTO )

                    .if ( [ebx+16].token != T_FINAL )

                        mov len,strlen( [ebx+16].string_ptr )

                        ;; search for the destination line
                        assume edi:srcline_t

                        .for ( i = 1, edi = mi.startline: edi != NULL: edi = [edi].next, i++ )
                            lea esi,[edi].line
                            .if ( byte ptr [esi] == ':' )
                                .if ( [edi].ph_count )
                                    fill_placeholders( StringBufferEnd, esi, mi.parmcnt, mi.localstart, mi.parm_array )
                                    mov esi,StringBufferEnd
                                .endif
                                inc esi
                                .while islspace( [esi] )
                                    inc esi
                                .endw
                                .if !_memicmp( esi, [ebx+16].string_ptr, len )
                                    mov ecx,len ;; label found!
                                    .break .if !is_valid_id_char( [esi+ecx]  )
                                .endif
                            .endif
                        .endf
                        .if !edi
                            ;; v2.05: display error msg BEFORE SkipMacro()!
                            asmerr( 2147, [ebx+16].string_ptr )
                        .else
                            ;; v2.10: rewritten, "if"-nesting-level handling added
                            mov mi.currline,edi
                            SetLineNumber( i )
                            SetIfNestLevel( oldifnesting )
                            inc cntgoto
                            .continue
                        .endif
                    .else
                        asmerr(2008, [ebx].tokpos )
                    .endif
                    SkipMacro( tokenarray )
                    .break
                .endif
            .endif
            ParseLine( tokenarray )
            .if ( Options.preprocessor_stdout == TRUE )
                WritePreprocessedLine( CurrSource )
            .endif

            ;; the macro might contain an END directive.
            ;; v2.08: this doesn't mean the macro is to be cancelled.
            ;; Masm continues to run it and the assembly is stopped
            ;; when the top source level is reached again.

        .endw ;; end while

        dec MacroLevel
        .if ( !(mflags & MF_NOSAVE ) )
            PopInputStatus( &oldstat )
        .endif

        ;; don't use tokenarray from here on, it's invalid after PopInputStatus()
    .endif ;; end if

    mov eax,idx
    ret

RunMacro endp

    assume esi:nothing
    assume edi:nothing

;; make room (or delete items) in the token buffer at position <start>

AddTokens proc private uses ebx tokenarray:token_t, start:int_t, count:int_t, _end:int_t

    imul ecx,count,asm_tok

    .if count > 0
        mov  edx,_end
        imul ebx,edx,asm_tok
        add  ebx,tokenarray
        .for( : edx >= start: edx--, ebx -= asm_tok )
            mov [ebx+ecx+0x00],dword ptr [ebx+0x00]
            mov [ebx+ecx+0x04],dword ptr [ebx+0x04]
            mov [ebx+ecx+0x08],dword ptr [ebx+0x08]
            mov [ebx+ecx+0x0C],dword ptr [ebx+0x0C]
        .endf
    .elseif count < 0
        mov  edx,start
        sub  edx,count
        imul ebx,edx,asm_tok
        add  ebx,tokenarray
        .for( : edx <= _end: edx++, ebx += asm_tok )
            mov [ebx+ecx+0x00],dword ptr [ebx+0x00]
            mov [ebx+ecx+0x04],dword ptr [ebx+0x04]
            mov [ebx+ecx+0x08],dword ptr [ebx+0x08]
            mov [ebx+ecx+0x0C],dword ptr [ebx+0x0C]
        .endf
    .endif
    ret

AddTokens endp


;; ExpandText() is called if
;; - the evaluation operator '%' has been found as first char of the line.
;; - the % operator is found in a macro argument.
;; if substitute is TRUE, scanning for the substitution character '&' is active!
;; Both text macros and macro functions are expanded!


ExpandText proc uses esi edi ebx line:string_t, tokenarray:token_t, substitute:uint_t

    local pIdent:string_t
    local lvl:int_t
    local is_exitm:int_t
    local old_tokencount:int_t
    local old_stringbufferend:string_t
    local rc:int_t
    local sym:asym_t
    local _sp[MAX_TEXTMACRO_NESTING]:string_t
    local i:int_t
    local cnt:int_t
    local quoted_string:char_t
    local macro_proc:char_t

    mov old_tokencount,Token_Count
    mov old_stringbufferend,StringBufferEnd
    mov quoted_string,0
    mov macro_proc,FALSE

    mov _sp[0],line
    mov edi,StringBufferEnd
    add StringBufferEnd,ModuleInfo.max_line_len

    mov rc,NOT_ERROR

    .for ( lvl = 0 : lvl >= 0 : lvl-- )

        mov eax,lvl
        mov esi,_sp[eax*4]

        .while ( byte ptr [esi] )

            .if ( is_valid_id_first_char( [esi] ) && ( substitute || !quoted_string ) )

                mov pIdent,edi
                .repeat
                    stosb
                    inc esi
                .until !is_valid_id_char( [esi] )
                mov byte ptr [edi],0

                mov sym,SymSearch( pIdent )
                .if ( eax && [eax].asym.flags & S_ISDEFINED )
                    .if ( [eax].asym.state == SYM_TMACRO )

                        ;
                        ; v2.08: no expansion inside quoted strings without &
                        ;
                        mov edx,pIdent
                        .continue .if ( quoted_string && \
                            byte ptr [edx-1] != '&' && byte ptr [esi] != '&' )

                        .if ( substitute )
                            .if ( byte ptr [edx-1] == '&' )
                                dec pIdent
                            .endif
                            .if ( byte ptr [esi] == '&' )
                                inc esi
                            .endif
                        .elseif ( pIdent > old_stringbufferend && byte ptr [edx-1] == '%' )
                            dec pIdent
                        .endif

                        mov eax,lvl
                        inc lvl
                        mov _sp[eax*4],esi
                        mov esi,StringBufferEnd
                        mov eax,sym
                        strcpy( esi, [eax].asym.string_ptr )
                        mov StringBufferEnd,GetAlignedPointer( esi, strlen( esi ) )
                        mov edi,pIdent
                        mov rc,STRING_EXPANDED
                    .elseif ( [eax].asym.state == SYM_MACRO && [eax].asym.mac_flag & M_ISFUNC )
                        ;; expand macro functions.

                        mov edx,esi
                        .while islspace( [edx] )
                            inc edx
                        .endw
                        ;
                        ; no macro function invokation if the '(' is missing!
                        ;
                        .if ( al == '(' )

                            mov i,Token_Count
                            inc i
                            mov Token_Count,Tokenize( edx, i, tokenarray, TOK_RESCAN )

                            mov  edx,i
                            imul ecx,edx,asm_tok
                            add  ecx,tokenarray
                            .for ( eax = 0 : edx < Token_Count : edx++, ecx += asm_tok )
                                .if [ecx].asm_tok.token == T_OP_BRACKET
                                    inc eax
                                .elseif [ecx].asm_tok.token == T_CL_BRACKET
                                    dec eax
                                    .ifz
                                        add ecx,asm_tok
                                        .break
                                    .endif
                                .endif
                            .endf
                            ;; don't substitute inside quoted strings if there's no '&'
                            mov edx,pIdent
                            .if quoted_string && byte ptr [edx-1] != '&' && [ecx].asm_tok.token != '&'
                                mov Token_Count,old_tokencount
                                .continue
                            .endif
                            .if substitute
                                .if byte ptr [edx-1] == '&'
                                    dec pIdent
                                .endif
                            .elseif edx > old_stringbufferend && byte ptr [edx-1] == '%'
                                dec pIdent
                            .endif
                            mov i,RunMacro( sym, i, tokenarray, edi, 0, &is_exitm )
                            mov ecx,old_tokencount
                            mov Token_Count,ecx
                            .return .if eax == -1

                            imul ebx,eax,asm_tok
                            add  ebx,tokenarray
                            mov esi,[ebx-16].tokpos
                            add esi,strlen( [ebx-16].string_ptr )
                            .if substitute && byte ptr [esi] == '&'
                                inc esi
                            .endif
                            mov eax,lvl
                            inc lvl
                            mov _sp[eax*4],esi
                            strlen(edi)
                            mov esi,edi
                            mov edi,StringBufferEnd
                            lea ecx,[eax+1]
                            rep movsb
                            mov esi,StringBufferEnd
                            mov StringBufferEnd,GetAlignedPointer( esi, eax )
                            mov edi,pIdent
                            mov rc,STRING_EXPANDED
                        .endif
                    .elseif [eax].asym.state == SYM_MACRO
                        mov macro_proc,TRUE
                    .endif
                    .if lvl == MAX_TEXTMACRO_NESTING
                        asmerr(2123)
                        .break
                    .endif
                .endif
            .else
                mov al,[esi]
                .if al == '"' || al == "'"
                    .if quoted_string == 0
                        mov quoted_string,al
                    .elseif al == quoted_string
                        mov quoted_string,0
                    .endif
                .endif
                movsb
            .endif
        .endw ;; end while
    .endf
    mov byte ptr [edi],0
    inc edi
    mov StringBufferEnd,old_stringbufferend
    .if rc == STRING_EXPANDED
        mov ecx,edi
        sub ecx,eax
        mov esi,eax
        mov edi,line
        rep movsb
    .endif
    .if substitute
        mov ebx,tokenarray
        .if rc == STRING_EXPANDED
            mov Token_Count,Tokenize( [ebx].tokpos, 0, ebx, TOK_RESCAN )
        .endif
        .if rc == STRING_EXPANDED || macro_proc
            .return 0 .if DelayExpand(ebx)
            .return ExpandLine( [ebx].tokpos, ebx )
        .endif
    .endif
    mov eax,rc
    ret

ExpandText endp

;; replace text macros and macro functions by their values, recursively
;; outbuf in: text macro or macro function value
;; outbuf out: expanded value
;; equmode: if 1, don't expand macro functions

ExpandTMacro proc private uses esi edi ebx outbuf:string_t, tokenarray:token_t, equmode:int_t, level:int_t

    local old_tokencount:int_t
    local i:int_t
    local len:int_t
    local is_exitm:int_t
    local sym:asym_t
    local buffer:ptr char_t
    local expanded:char_t

    mov buffer,alloca(ModuleInfo.max_line_len)
    mov old_tokencount,Token_Count
    mov expanded,TRUE

    .if ( level >= MAX_TEXTMACRO_NESTING )
        .return( asmerr( 2123 ) )
    .endif

    .while ( expanded == TRUE )
        mov i,old_tokencount
        inc i
        mov Token_Count,Tokenize( outbuf, i, tokenarray, TOK_RESCAN )
        mov expanded,FALSE
        .for ( : i < Token_Count: i++ )

            imul ebx,i,asm_tok
            add  ebx,tokenarray
            .if [ebx].token == T_ID
                mov sym,SymSearch( [ebx].string_ptr )

                ;; expand macro functions

                .if ( eax && [eax].asym.state == SYM_MACRO && \
                      [eax].asym.flags & S_ISDEFINED && [eax].asym.mac_flag & M_ISFUNC && \
                      [ebx+16].token == T_OP_BRACKET && equmode == FALSE )

                    mov ecx,[ebx].tokpos
                    sub ecx,outbuf
                    mov edi,buffer
                    mov esi,outbuf
                    rep movsb
                    mov ecx,i
                    inc ecx
                    mov i,RunMacro( sym, ecx, tokenarray, edi, 0, &is_exitm )
                    .if i < 0
                        mov Token_Count,old_tokencount
                        .return ERROR
                    .endif
                    imul ebx,i,asm_tok
                    add  ebx,tokenarray
                    strcat( edi, [ebx].tokpos )
                    strcpy( outbuf, buffer )
                    mov expanded,TRUE
                    ;; is i to be decremented here?
                    .break
                .elseif ( eax && [eax].asym.state == SYM_TMACRO && [eax].asym.flags & S_ISDEFINED )

                    mov esi,outbuf
                    mov edi,buffer
                    mov ecx,[ebx].tokpos
                    sub ecx,esi
                    rep movsb
                    strcpy( edi, [eax].asym.string_ptr )
                    mov ecx,level
                    inc ecx
                    .if ExpandTMacro( edi, tokenarray, equmode, ecx ) == ERROR
                        mov Token_Count,old_tokencount
                        .return( ERROR )
                    .endif
                    mov eax,sym
                    movzx ecx,[eax].asym.name_size
                    add ecx,[ebx].tokpos
                    strcat( edi, ecx )
                    strcpy( outbuf, buffer )
                    mov expanded,TRUE
                    .break
                .endif
            .endif
        .endf
    .endw
    mov Token_Count,old_tokencount
    mov eax,NOT_ERROR
    ret

ExpandTMacro endp

;; rebuild a source line
;; adjust all "pos" values behind the current pos
;; - newstring = new value of item i
;; - i = token buffer index of item to replace
;; - outbuf = start of source line to rebuild
;; - oldlen = old length of item i
;; - pos_line = position of item in source line

RebuildLine proc private uses esi edi ebx newstring:string_t, i:int_t,
        tokenarray:token_t, oldlen:uint_t, pos_line:uint_t, addbrackets:int_t

    local dest:string_t
    local src:string_t
    local newlen:uint_t
    local rest:uint_t
    local buffer:ptr char_t

    mov buffer,alloca(ModuleInfo.max_line_len)
    imul ebx,i,asm_tok
    add  ebx,tokenarray

    mov esi,[ebx].tokpos
    add esi,oldlen
    inc strlen(esi)
    mov rest,eax
    mov edi,buffer
    mov ecx,eax
    rep movsb       ;; save content of line behind item

    mov edi,[ebx].tokpos
    mov newlen,strlen(newstring)

    .if addbrackets
        add newlen,2 ;; count '<' and '>'
        .for ( esi = newstring, al = [esi] : al : esi++, al = [esi] )
            .if ( al == '<' || al == '>' || al == '!' ) ;; count '!' operator
                inc newlen
            .endif
        .endf
    .endif
    .if newlen > oldlen
        mov eax,pos_line
        add eax,newlen
        sub eax,oldlen
        add eax,rest
        .return asmerr( 2039 ) .if ( eax >= ModuleInfo.max_line_len )
    .endif
    .if addbrackets
        mov byte ptr [edi],'<'
        inc edi
        .for ( esi = newstring: byte ptr [esi] : esi++ )
            mov al,[esi]
            .if ( al == '<' || al == '>' || al == '!' )
                mov byte ptr [edi],'!'
                inc edi
            .endif
            mov [edi],al
            inc edi
        .endf
        mov byte ptr [edi],'>'
        inc edi
    .else
        mov ecx,newlen
        mov esi,newstring
        rep movsb
    .endif
    mov ecx,rest
    mov esi,buffer
    rep movsb   ;; add rest of line

    ;; v2.05: changed '<' to '<='

    .for ( ecx = i, ecx++,
           ebx += asm_tok,
           eax = oldlen,
           edx = newlen : ecx <= Token_Count : ecx++, ebx += asm_tok )

        sub [ebx].tokpos,eax
        add [ebx].tokpos,edx
    .endf
    mov eax,NOT_ERROR
    ret

RebuildLine endp

;; expand one token
;; line: full source line
;; *pi: index of token in tokenarray
;; equmode: if 1, dont expand macro functions

ExpandToken proc uses esi edi ebx line:string_t, pi:ptr int_t, tokenarray:token_t,
        max:int_t, bracket_flags:int_t, equmode:int_t

    local pos:int_t
    local tmp:int_t
    local i:int_t
    local size:int_t
    local addbrackets:int_t
    local evaluate:char_t
    local is_exitm:int_t
    local opndx:expr
    local sym:asym_t
    local rc:int_t
    local buffer:ptr char_t
    local old_tokencount:int_t

    mov buffer,alloca(ModuleInfo.max_line_len)
    mov eax,pi
    mov i,[eax]
    mov addbrackets,bracket_flags
    mov evaluate,FALSE
    mov rc,NOT_ERROR

    .for ( : i < max : i++ )

        imul ebx,i,asm_tok
        add ebx,tokenarray

        .break .if [ebx].token == T_COMMA

        ;; v2.05: the '%' should only be handled as an operator if addbrackets==TRUE,
        ;; which means that the current directive is a preprocessor directive and the
        ;; expected argument is a literal (or text macro).

        .if [ebx].token == T_PERCENT && addbrackets && evaluate == FALSE

            mov evaluate,TRUE
            mov addbrackets,FALSE
            mov equmode,FALSE
            mov pos,i
            .continue
        .endif

        .if [ebx].token == T_ID

            mov sym,SymSearch([ebx].string_ptr)

            ;; don't check isdefined flag (which cannot occur in pass one, and this code usually runs
            ;; in pass one only!

            .if eax

                .if [eax].asym.state == SYM_MACRO

                    mov ecx,i
                    mov tmp,ecx ;; save index of macro name

                    .if [eax].asym.mac_flag & M_ISFUNC

                        ;; ignore macro functions without a following '('
                        .continue .if [ebx+16].token != T_OP_BRACKET

                        inc i
                        add ebx,16

                        .if equmode == TRUE

                            inc i ;; skip '('
                            add ebx,16

                            ;; go beyond the ')'

                            .for ecx = 1: i < max: i++, ebx += asm_tok
                                .if [ebx].token == T_OP_BRACKET
                                    inc ecx
                                .elseif [ebx].token == T_CL_BRACKET
                                    dec ecx
                                    .break .ifz
                                .endif
                            .endf
                            dec i
                            sub ebx,16
                            .continue
                        .endif

                        xor edx,edx
                        .if tmp == 1
                            mov edx,MF_LABEL
                        .endif
                        mov i,RunMacro( sym, i, tokenarray, buffer, edx, &is_exitm )
                        .return .if eax == -1

                        imul ebx,i,asm_tok
                        add ebx,tokenarray

                        ;; expand text, but don't if macro was at position 0 (might be a text macro definition directive
                        ;; v2.09: don't expand further if addbrackets is set
                        .if tmp && !addbrackets
                            .return .if ExpandTMacro( buffer, tokenarray, equmode, 0 ) == ERROR
                        .endif
                        ;; get size of string to replace ( must be done before AddTokens()
                        imul ecx,tmp,asm_tok
                        mov eax,[ebx-16].tokpos
                        inc eax
                        add ecx,tokenarray
                        sub eax,[ecx].asm_tok.tokpos
                        mov size,eax
                        mov edx,tmp
                        inc edx
                        mov ecx,edx
                        sub ecx,i
                        AddTokens( tokenarray, edx, ecx, Token_Count )
                        mov eax,tmp
                        inc eax
                        sub eax,i
                        add Token_Count,eax
                        .if Token_Count < max ;; take care not to read beyond T_FINAL
                            mov max,Token_Count
                        .endif
                        imul ecx,tmp,asm_tok
                        add ecx,tokenarray
                        mov edx,[ecx].asm_tok.tokpos
                        sub edx,line
                        .return .if RebuildLine( buffer, tmp, tokenarray, size, edx, addbrackets ) == ERROR
                        mov rc,STRING_EXPANDED
                        mov i,tmp

                    .else

                        ;; a macro proc is expanded at pos 0 or pos 2
                        ;; (or at pos 1 if sym->label is on)

                        mov edx,i
                        mov ecx,tokenarray
                        .if ( edx == 0 || ( edx == 2 && ( [ecx+16].asm_tok.token == T_COLON || \
                             [ecx+16].asm_tok.token == T_DBL_COLON ) ) || \
                             ( edx == 1 && [eax].asym.mac_flag & M_LABEL ) )
                        .else
                            .continue
                        .endif

                        ;; v2.08: write optional code label. This has been
                        ;; moved out from RunMacro().

                        .if edx == 2
                            .return .if WriteCodeLabel( line, tokenarray ) == ERROR
                            mov edx,i
                        .endif
                        mov ecx,MF_NOSAVE
                        .if edx == 1
                            or ecx,MF_LABEL
                        .endif
                        inc edx
                        mov i,RunMacro( sym, edx, tokenarray, NULL, ecx, &is_exitm )
                        .return .if eax == -1
                        .return EMPTY ;; no further processing
                    .endif

                .elseif [eax].asym.state == SYM_TMACRO

                    strcpy( buffer, [eax].asym.string_ptr )
                    .return .if ExpandTMacro( buffer, tokenarray, equmode, 0 ) == ERROR
                    strlen( [ebx].string_ptr )
                    mov ecx,[ebx].tokpos
                    sub ecx,line
                    .return .if RebuildLine( buffer, i, tokenarray, eax, ecx, addbrackets ) == ERROR
                    mov rc,STRING_EXPANDED
                .endif
            .endif
        .endif
    .endf

    mov ecx,i
    mov eax,pi
    mov [eax],ecx

    .if evaluate

        mov old_tokencount,Token_Count
        mov ebx,tokenarray
        mov edx,pos
        lea eax,[edx+1]
        .if eax == i ;; just a single %?
            mov opndx.value,0
            mov i,edx
        .else
            mov i,edx
            inc edx
            shl ecx,4
            shl edx,4
            mov ecx,[ebx+ecx].tokpos
            mov esi,[ebx+edx].tokpos
            mov edi,buffer
            sub ecx,esi
            rep movsb
            mov byte ptr [edi],0
            mov edi,old_tokencount
            inc edi
            mov Token_Count,Tokenize( buffer, edi, tokenarray, TOK_RESCAN )
            mov tmp,edi
            .if EvalOperand( &tmp, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR
                mov opndx.value,0 ;; v2.09: assume value 0, don't return with ERROR
            .elseif opndx.kind != EXPR_CONST
                asmerr( 2026 )
                mov opndx.value,0 ;; assume value 0
            .endif
            mov Token_Count,old_tokencount
        .endif
if TEVALUE_UNSIGNED
        ;; v2.03: Masm compatible: returns an unsigned value
        myltoa( opndx.value, StringBufferEnd, ModuleInfo.radix, FALSE, FALSE )
else
        xor eax,eax
        .if opndx.hvalue < 0
            mov eax,1
        .endif
        myltoa( opndx.value, StringBufferEnd, ModuleInfo.radix, eax, FALSE )
endif
        ;; v2.05: get size of string to be "replaced"

        mov esi,pi
        mov esi,[esi]
        imul eax,esi,asm_tok
        imul edx,i,asm_tok
        mov edi,[ebx+eax].tokpos
        sub edi,[ebx+edx].tokpos
        add ebx,edx
        mov [ebx].string_ptr,StringBufferEnd
        mov eax,i
        inc eax
        mov edx,eax
        sub edx,esi
        AddTokens( tokenarray, eax, edx, Token_Count )
        mov eax,i
        inc eax
        sub eax,esi
        add Token_Count,eax
        mov ecx,[ebx].tokpos
        sub ecx,line
        .return .if RebuildLine( StringBufferEnd, i, tokenarray, edi, ecx, bracket_flags ) == ERROR
        mov rc,STRING_EXPANDED
    .endif
    mov eax,rc
    ret

ExpandToken endp

;; used by EQU ( may also be used by directives flagged with DF_NOEXPAND
;; if they have to partially expand their arguments ).
;; equmode: 1=don't expand macro functions


ExpandLineItems proc uses esi edi line:string_t, i:int_t, tokenarray:token_t,
        addbrackets:int_t, equmode:int_t

    local k:int_t

    .for esi = 0 :: esi++

        mov edi,NOT_ERROR
        .for ( k = i : k < Token_Count : )

            ExpandToken( line, &k, tokenarray, Token_Count, addbrackets, equmode )
            .break(1) .if eax == ERROR
            .if eax == STRING_EXPANDED
                mov edi,eax
            .endif
            imul eax,k,asm_tok
            add eax,tokenarray
            .if ( [eax].asm_tok.token == T_COMMA )
                inc k
            .endif
        .endf
        .break .if edi == NOT_ERROR

        ;; expansion happened, re-tokenize and continue!
        mov Token_Count,Tokenize( line, i, tokenarray, TOK_RESCAN )
        .if esi == MAX_TEXTMACRO_NESTING
            asmerr( 2123 )
            .break
        .endif
    .endf
    mov eax,esi
    ret

ExpandLineItems endp

;; v2.09: added, expand literals for structured data items.
;; since 2.09, initialization of structure members is no longer
;; done by generated code, but more directly inside data.c.
;; This improves Masm-compatibility, but OTOH requires to expand
;; the literals explicitly.


ExpandLiterals proc uses ebx i:int_t, tokenarray:token_t

    xor eax,eax
    mov ebx,tokenarray

    ;; count non-empty literals
    .for ( ecx = i: ecx < Token_Count: ecx++ )
        shl ecx,4
        .if ( [ebx+ecx].token == T_STRING && [ebx+ecx].stringlen && \
            ( [ebx+ecx].string_delim == '<' || [ebx+ecx].string_delim == '{' ) )
            inc eax
        .endif
        shr ecx,4
    .endf
    ;; if non-empty literals are found, expand the line. if the line
    ;; was expanded, re-tokenize it.
    imul ecx,i,asm_tok
    add ebx,ecx
    .if eax
        .if ExpandText( [ebx].tokpos, tokenarray, FALSE ) == STRING_EXPANDED
            Tokenize( [ebx].tokpos, i, tokenarray, TOK_RESCAN )
        .endif
    .endif
    ret

ExpandLiterals endp

;; scan current line for (text) macros and expand them.
;; this is only called when the % operator is not the first item.

ExpandLine proc uses esi edi ebx string:string_t, tokenarray:token_t

    local count         : int_t
    local bracket_flags : uint_t ;; flags
    local flags         : int_t
    local lvl           : int_t
    local rc            : int_t
    local addbrackets   : int_t

    ;; filter certain conditions.
    ;; bracket_flags: for (preprocessor) directives that expect a literal
    ;; parameter, the expanded argument has to be enclosed in '<>' again.

    mov ebx,tokenarray

    .for ( lvl = 0: lvl < MAX_TEXTMACRO_NESTING: lvl++ )

        xor esi,esi
        mov bracket_flags,esi
        mov count,esi
        mov rc,esi

        .if ( Token_Count > 2 && ( [ebx+16].token == T_COLON || \
            [ebx+16].token == T_DBL_COLON ) && [ebx+32].token == T_DIRECTIVE )
            mov esi,2
            add ebx,32
        .endif

        mov edx,tokenarray
        .if [ebx].token == T_DIRECTIVE
            mov flags,GetValueSp( [ebx].tokval )
            .if flags & DF_STRPARM
                mov bracket_flags,-1
                ;; v2.08 handle .ERRDEF and .ERRNDEF here. Previously
                ;; expansion for these directives was handled in condasm.asm,
                ;; and the directives were flagged as DF_NOEXPAND.

                .if [ebx].dirtype == DRT_ERRDIR
                    .if ( [ebx].tokval == T_DOT_ERRDEF || [ebx].tokval == T_DOT_ERRNDEF )
                        .if esi
                            mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE )
                        .endif
                        .while [ebx].token != T_FINAL && [ebx].token != T_COMMA
                            inc esi
                            add ebx,asm_tok
                        .endw
                        mov count,esi ;; don't expand the symbol name
                    .endif
                .endif
            .elseif flags & DF_NOEXPAND
                ;; [ELSE]IF[N]DEF, ECHO, FOR[C]
                ;; .[NO|X]CREF, INCLUDE
                ;; don't expand arguments
                .return NOT_ERROR
            .endif
        .elseif Token_Count > 1 && [edx+16].asm_tok.token == T_DIRECTIVE
            mov al,[edx+16].asm_tok.dirtype
            .switch al
            .case DRT_CATSTR
                mov bracket_flags,-1
                mov count,2
                .endc
            .case DRT_SUBSTR
                ;; syntax: name SUBSTR <literal>, pos [, size]
                mov bracket_flags,0x1
                mov count,2
                .endc
            .case DRT_SIZESTR
                ;; syntax: label SIZESTR literal
                mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE )
                mov bracket_flags,0x1
                mov count,2
                .endc
            .case DRT_INSTR
                ;; syntax: label INSTR [number,] literal, literal
                mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE )
                ;; check if the optional <number> argument is given
                .for esi = 2, eax = 0, ecx = 0: esi < Token_Count: esi++
                    imul ebx,esi,asm_tok
                    add ebx,tokenarray
                    .if [ebx].token == T_OP_BRACKET
                        inc eax
                    .elseif [ebx].token == T_CL_BRACKET
                        dec eax
                    .elseif [ebx].token == T_COMMA && eax == 0
                        inc ecx
                    .endif
                .endf
                mov eax,3
                .if ecx > 1
                    mov eax,6
                .endif
                mov bracket_flags,eax
                mov count,2
                .endc
            .case DRT_MACRO
                SymSearch( [edx].asm_tok.string_ptr )
                ;; don't expand macro DEFINITIONs!
                ;; the name is an exception, if it's not the macro itself

                .if ( eax && [eax].asym.state != SYM_MACRO )
                    mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE )
                .endif
                mov count,Token_Count ;; stop further expansion
                .endc
            .case DRT_EQU
                ;; EQU is a special case. If the - expanded - expression is
                ;; a number, then the value for EQU is numeric. Else the
                ;; expression isn't expanded at all. This effectively makes it
                ;; impossible to expand EQU lines here.

                .return NOT_ERROR
            .endsw
        .else
            ;; v2.08: expand the very first token and then ...
            mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE );
            .return .if eax == ERROR || eax == EMPTY

            .if ( rc == STRING_EXPANDED )
                ;; ... fully retokenize - the expansion might have revealed a conditional
                ;; assembly directive

                mov Token_Count,Tokenize( string, 0, tokenarray, TOK_DEFAULT )
                .continue
            .endif
            mov eax,tokenarray
            .if ( count == 1 && [eax].asm_tok.token == T_ID && [eax+16].asm_tok.token == T_ID )
                mov rc,ExpandToken( string, &count, tokenarray, 2, FALSE, FALSE )
                .return .if eax == ERROR || eax == EMPTY
                .if rc == STRING_EXPANDED
                    mov Token_Count,Tokenize( string, 0, tokenarray, TOK_DEFAULT )
                    .continue
                .endif
            .endif
        .endif
        ;; scan the line from left to right for (text) macros.
        ;; it's currently not quite correct. a macro proc should only
        ;; be evaluated in the following cases:
        ;; 1. it is the first token of a line
        ;; 2. it is the second token, and the first one is an ID
        ;; 3. it is the third token, the first one is an ID and
        ;;    the second is a ':' or '::'.

        .while ( count < Token_Count )

            mov eax,bracket_flags
            and eax,1
            mov addbrackets,eax
            .if bracket_flags != -1
                shr bracket_flags,1
            .endif
            ExpandToken( string, &count, tokenarray, Token_Count, addbrackets, FALSE )
            .return .ifs ( eax < NOT_ERROR ) ;; ERROR or EMPTY?
            .if eax == STRING_EXPANDED
                mov rc,STRING_EXPANDED
            .endif
            imul ebx,count,asm_tok
            add ebx,tokenarray
            .if ( [ebx].token == T_COMMA )
                inc count
            .endif
        .endw
        .if rc == STRING_EXPANDED
            mov Token_Count,Tokenize( string, 0, tokenarray, TOK_RESCAN or TOK_LINE )
        .else
            .break
        .endif
    .endf ;; end for()

    .return asmerr( 2123 ) .if ( lvl == MAX_TEXTMACRO_NESTING )
    mov eax,rc
    ret

ExpandLine endp

    end
