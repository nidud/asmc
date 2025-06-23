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
include qfloat.inc
include lqueue.inc
include types.inc
include reswords.inc

public MacroLocals

; TEVALUE_UNSIGNED
; 1 = the % operator used in an TEXTEQU expression is supposed to
;     return an UNSIGNED value ( Masm-compatible ).

TEVALUE_UNSIGNED equ 1
MAX_TEXTMACRO_NESTING equ 20

.data
 MacroLocals int_t 0     ; counter for LOCAL names
 MacroLevel  dd 0        ; current macro nesting level

.code

; C ltoa() isn't fully compatible since hex digits are lower case.
; for JWasm, it's ensured that 2 <= radix <= 16.

myltoa proc __ccall uses rsi rdi rbx value:qword, buffer:string_t, radix:uint_t, sign:int_t, addzero:int_t

  local tmpbuf[64]:char_t

ifdef _WIN64

    mov rdi,rdx
    mov rax,rcx

    .if ( r9d )

        mov byte ptr [rdi],'-'
        inc rdi
        neg rax

    .elseif ( rax == 0 )

        mov word ptr [rdi],'0'
       .return 1
    .endif

    .for ( rsi = &tmpbuf[63] : rax : rsi-- )

        xor edx,edx
        div r8
        add dl,'0'
        .if dl > '9'
            add dl,'A'-'9'-1
        .endif
        mov [rsi],dl
    .endf
    inc rsi

else

    mov edi,buffer
    mov eax,dword ptr value
    mov edx,dword ptr value[4]

    .if ( sign )

        mov byte ptr [edi],'-'
        inc edi
        neg eax
        neg edx
        sbb edx,0

    .elseif ( edx == 0 && eax == 0 )

        mov word ptr [edi],'0'
       .return 1
    .endif

    .for ( esi = &tmpbuf[63] : eax || edx : esi-- )

        .if ( !edx || !radix )

            div radix
            mov ecx,edx
            xor edx,edx

        .else

            push edi
            .for ( ebx = 64, ecx = 0, edi = 0 : ebx : ebx-- )

                add eax,eax
                adc edx,edx
                adc ecx,ecx
                adc edi,edi

                .if ( edi || ecx >= radix )

                    sub ecx,radix
                    sbb edi,0
                    inc eax
                .endif
            .endf
            pop edi
        .endif

        add cl,'0'
        .if cl > '9'
            add cl,'A'-'9'-1
        .endif
        mov [esi],cl
    .endf
    inc esi

endif

    ; v2: add a leading '0' if first digit is alpha

    .if ( addzero && byte ptr [rsi] > '9' )
        mov byte ptr [rdi],'0'
        inc rdi
    .endif

    lea rcx,tmpbuf[64]
    sub rcx,rsi
    rep movsb
    mov byte ptr [rdi],0
    mov rax,rdi
    sub rax,buffer
    ret

myltoa endp


; Read the current (macro) queue until it's done.

SkipMacro proc __ccall private tokenarray:token_t

   .new buffer:string_t = alloc_line()

    ; The queue isn't just thrown away, because any
    ; coditional assembly directives found in the source
    ; must be executed.

    .while GetTextLine( buffer )
        Tokenize( buffer, 0, tokenarray, TOK_DEFAULT )
    .endw
    free_line(buffer)
    ret

SkipMacro endp


ExpandTMacro proto __ccall :string_t, :token_t, :int_t, :int_t

; run a macro.
; - macro:  macro item
; - out:    value to return (for macro functions)
; - label:  token of label ( or -1 if none )
; - is_exitm: returns TRUE if EXITM has been hit
; returns index of token not processed or -1 on errors

    assume rsi:asym_t
    assume rdi:macro_t
    assume rbx:token_t

RunMacro proc __ccall uses rsi rdi rbx mac:asym_t, idx:int_t, tokenarray:token_t,
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
    local info              :macro_t
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
    local mem_alloc         :int_t
    local cvt               :FLTINFO

    mov rax,StringBufferEnd
    sub rax,StringBuffer
    mov savedStringBuffer,rax

    mov _retm,0
    .if idx > 1
        inc _retm
    .endif
    mov bracket_level,-1

    .if MacroLevel == MAX_MACRO_NESTING
        .return asmerr( 2123 )
    .endif

    mov  mem_alloc,0
    mov  mi.parm_array,NULL
    mov  rsi,mac
    mov  rdi,[rsi].macroinfo
    mov  info,rdi
    imul ebx,idx,asm_tok
    add  rbx,tokenarray

    ; invokation of macro functions requires params enclosed in "()"

    mov parm_end_delim,T_FINAL
    .if ( [rsi].isfunc )

        .if ( [rbx].token == T_OP_BRACKET ) ; should be always true

            inc idx
            add rbx,asm_tok
            mov parm_end_delim,T_CL_BRACKET
            mov bracket_level,1
        .endif
        mov rax,_out ; v2.08: init return value buffer
        mov byte ptr [rax],0
    .endif

    ; v2.08: if macro is purged, return "void"

    .if ( [rsi].purged )

        .if ( bracket_level > 0 )

            .for ( : bracket_level && [rbx].token != T_FINAL: idx++, rbx += asm_tok )

                .if [rbx].token == T_OP_BRACKET
                    inc bracket_level
                .elseif [rbx].token == T_CL_BRACKET
                    dec bracket_level
                .endif
            .endf
        .else
            mov idx,TokenCount
        .endif
        .return idx
    .endif

    .if ( [rdi].parmcnt )

        movzx   eax,[rdi].parmcnt
        mov     ecx,MaxLineLength
        mov     edx,ecx
        add     ecx,ecx
        lea     ecx,[rcx+rax*size_t]

        .if ( edx == MAX_LINE_LEN )
            alloca( ecx )
        .else
            mov mem_alloc,1
            MemAlloc( ecx )
        .endif

        mov     mi.parm_array,rax
        movzx   ecx,[rdi].parmcnt
        lea     rax,[rax+rcx*size_t]
        mov     parmstrings,rax ; init the macro arguments pointer
        mov     currparm,rax
    .endif

    ; now get all the parameters from the original src line.
    ; macro parameters are expanded if
    ; - it is a macro function call or
    ; - the expansion operator (%) is found

    mov rbx,tokenarray
    mov parmidx,0

    .if ( [rsi].islabel )

        .if ( mflags & MF_LABEL )

            mov i,tstrlen( [rbx].string_ptr )
            mov ecx,parmidx
            mov rdx,mi.parm_array
            mov rdi,currparm
            mov [rdx+rcx*size_t],rdi
            mov ecx,i
            inc ecx
            mov rsi,[rbx].string_ptr
            rep movsb
            mov currparm,GetAlignedPointer( currparm, i )
        .else
            mov ecx,parmidx
            mov rdx,mi.parm_array
            lea rax,@CStr("")
            mov [rdx+rcx*size_t],rax
        .endif
        inc parmidx
    .endif

    mov rax,is_exitm
    mov dword ptr [rax],FALSE

    ; v2.08: allow T_FINAL to be chained, lastidx==0 is true final

    imul eax,TokenCount,asm_tok
    mov  [rbx+rax].lastidx,0
    imul eax,idx,asm_tok
    add  rbx,rax

    .for ( varargcnt = 0, skipcomma = 0 : : parmidx++ )

        ; v2.09: don't skip comma if it was the last argument.
        ; this will a) make a trailing comma trigger warning 'too many arguments...'
        ; and b), argument handling of FOR loop is significantly simplified.

        mov rsi,mac
        mov rdi,info
        movzx ecx,[rdi].parmcnt
        .break .if parmidx >= ecx

        imul ebx,idx,asm_tok
        add  rbx,tokenarray
        .if [rbx].token == T_COMMA && skipcomma
            inc idx
            add rbx,asm_tok
        .endif

        mov skipcomma,1
        dec ecx

        .if ( [rbx].token == T_FINAL || [rbx].token == parm_end_delim ||
             ( [rbx].token == T_COMMA &&
              ( !( [rsi].mac_vararg ) || parmidx != ecx ) ) )

            ; it's a blank parm

            imul eax,parmidx,mparm_list
            mov rcx,[rdi].parmlist
            add rcx,rax

            .if ( [rcx].mparm_list.required )

                mov idx,asmerr( 2125 )
                jmp toend
            .endif

            .if ( varargcnt == 0 )

                imul edx,parmidx,ptr_t
                add rdx,mi.parm_array
                mov [rdx],[rcx].mparm_list.deflt
            .endif
        .else

            mov inside_literal,0
            mov inside_angle_brackets,0
            mov old_tokencount,TokenCount

            mov rdx,currparm
            mov byte ptr [rdx],0

            .for ( p = rdx : : idx++ )

                imul ebx,idx,asm_tok
                add  rbx,tokenarray
                .break .if ( [rbx].token == T_FINAL || [rbx].token == T_COMMA ) && !inside_literal

                ; if were're inside a literal, go up one level and continue scanning the argument

                .if [rbx].token == T_FINAL

                    mov  idx,[rbx].lastidx ;; restore token index
                    imul ebx,eax,asm_tok
                    add  rbx,tokenarray

                    dec inside_literal
                    .if [rbx].string_delim == '<'
                        mov inside_angle_brackets,0
                    .else
                        mov rax,p
                        inc p
                        mov byte ptr [rax],'}'
                    .endif
                    .continue
                .endif

                .if ( [rbx].token == T_PERCENT )

                    ; expansion of macro parameters.
                    ; if the token behind % is not a text macro or macro function
                    ; the expression will be always expanded and evaluated.
                    ; Else it is expanded, but only evaluated if

                    inc idx
                    add rbx,asm_tok
                    .while [rbx].token == T_PERCENT
                        inc idx
                        add rbx,asm_tok
                    .endw
                    mov i,idx
                    mov cnt_opnum,1
                    .if [rbx].token == T_ID
                        mov sym,SymSearch( [rbx].string_ptr )

                        .if ( rax && [rax].asym.isdefined && ( [rax].asym.state == SYM_TMACRO ||
                                ( [rax].asym.state == SYM_MACRO && [rax].asym.isfunc &&
                                  [rbx+asm_tok].token == T_OP_BRACKET ) ) )

                            mov cnt_opnum,0
                        .endif
                    .endif

                    .for ( cnt = 0 :: i++ )

                        imul ebx,i,asm_tok
                        add  rbx,tokenarray
                        .break .if [rbx].token == T_FINAL || [rbx].token == T_COMMA

                        mov rcx,[rbx].string_ptr
                        .if ( isdotlabel( [rcx], MODULE.dotname ) )

                            .if ( [rbx+asm_tok].token == T_OP_BRACKET )

                                add i,2
                                add rbx,asm_tok*2
                                .for ( ecx = 1: ecx && [rbx].token != T_FINAL: i++, rbx += asm_tok )
                                    .if [rbx].token == T_OP_BRACKET
                                        inc ecx
                                    .elseif [rbx].token == T_CL_BRACKET
                                        dec ecx
                                    .endif
                                .endf
                                dec i
                            .endif
                            .continue
                        .endif

                        ; count brackets

                        .if parm_end_delim == T_CL_BRACKET
                            .if [rbx].token == T_OP_BRACKET
                                inc cnt
                            .elseif [rbx].token == T_CL_BRACKET
                                .break .if cnt == 0
                                dec cnt
                            .endif
                        .endif

                        ; stop if undelimited string occurs (need to scan for '!')

                        .break .if ( [rbx].token == T_STRING && [rbx].string_delim == 0 )

                        ; names dot and amp are ok

                        .if !( [rbx].token == T_DOT || [rbx].token == '&' || [rbx].token == '%' )
                            inc cnt_opnum ; anything else will trigger numeric evaluation
                        .endif
                    .endf

                    .if i == idx ; no items except %?

                        dec idx
                       .continue
                    .endif

                    mov   rcx,[rbx].tokpos
                    imul  ebx,idx,asm_tok
                    add   rbx,tokenarray
                    mov   rsi,[rbx].tokpos
                    sub   rcx,rsi
                    .while islspace( [rsi+rcx-1] )
                        dec ecx
                    .endw
                    mov cnt,ecx
                    mov rdi,p
                    rep movsb
                    mov byte ptr [rdi],0

                    .ifd ExpandText( p, tokenarray, FALSE ) == ERROR

                        mov idx,eax
                        mov rax,savedStringBuffer
                        add rax,StringBuffer
                        mov StringBufferEnd,rax
                        jmp toend
                    .endif

                    mov idx,i
                    dec idx
                    .if cnt_opnum

                        ; convert numeric expression into a string

                        mov edx,TokenCount
                        inc edx
                        mov max,Tokenize( p, edx, tokenarray, TOK_RESCAN )
                        mov i,TokenCount
                        inc i

                        ; the % operator won't accept forward references.
                        ; v2.09: flag EXPF_NOUNDEF set.

                        .ifd EvalOperand( &i, tokenarray, max, &opndx, EXPF_NOUNDEF ) == ERROR
                            mov opndx.value,0
                            mov opndx.hvalue,0
                        .elseif ( opndx.kind != EXPR_CONST &&
                               !( opndx.kind == EXPR_FLOAT && opndx.mem_type == MT_REAL16 ) )
                            asmerr( 2026 )
                            mov opndx.value,0
                            mov opndx.hvalue,0
                        .endif

                        ; v2.08: accept constant and copy any stuff that's following

                        .if opndx.kind == EXPR_CONST

                            xor eax,eax
                            cmp opndx.hvalue,0
                            setl al
                            myltoa( opndx.llvalue, StringBufferEnd, MODULE.radix, eax, FALSE )

                        .elseif ( opndx.kind == EXPR_FLOAT && opndx.mem_type == MT_REAL16 )

                            .if ( ( opndx.value == 16 && opndx.h64_h == 0 ) )
                                tstrcpy( StringBufferEnd, "16" )
                            .elseif ( MODULE.floatformat == 'x' )
                                tsprintf( StringBufferEnd, "%16lx%16lx", opndx.hlvalue, opndx.llvalue )
                            .else

                                mov cvt.expchar,'e'
                                mov cvt.expwidth,3
                                mov cvt.ndigits,MODULE.floatdigits
                                mov cvt.bufsize,MaxLineLength

                                .if ( MODULE.floatformat == 'e' )
                                    mov cvt.scale,1
                                    mov cvt.flags,_ST_E
                                .elseif ( MODULE.floatformat == 'g' )
                                    mov cvt.scale,1
                                    mov cvt.flags,_ST_G
                                .else
                                    mov cvt.scale,0
                                    mov cvt.flags,_ST_F
                                .endif
                                mov rsi,StringBufferEnd
                                inc rsi
                                _flttostr( &opndx, &cvt, rsi, _ST_QUADFLOAT )
                                .if ( cvt.sign == -1 )
                                    mov byte ptr [rsi-1],'-'
                                .else
                                    tstrcpy( StringBufferEnd, rsi )
                                .endif
                            .endif
                        .endif

                        .if ( i != max )
                            ;
                            ; the evaluator was unable to evaluate the full expression. the rest
                            ; has to be "copied"
                            ;
                            imul ebx,i,asm_tok
                            add  rbx,tokenarray
                            tstrcat( StringBufferEnd, [rbx].tokpos )
                        .endif
                        tstrcpy( p, StringBufferEnd )
                    .endif
                    add p,tstrlen( p )
                   .continue
                .endif

                imul ebx,idx,asm_tok
                add  rbx,tokenarray

                .if ( [rbx].token == T_STRING && [rbx].string_delim == '{' )

                    mov rcx,[rbx].string_ptr
                    mov ebx,idx
                    mov rax,p ; copy the '{'
                    inc p
                    mov byte ptr [rax],'{'

                    ; the string must be tokenized

                    inc inside_literal
                    mov idx,TokenCount
                    mov TokenCount,Tokenize( rcx, &[rax+1], tokenarray, TOK_RESCAN or TOK_NOCURLBRACES )
                    imul eax,eax,asm_tok
                    add rax,tokenarray
                    mov [rax].asm_tok.lastidx,ebx
                   .continue
                .endif

                .if inside_angle_brackets == 0

                    ; track brackets for macro functions; exit if one more ')' than '(' is found

                    .if bracket_level > 0
                        .if [rbx].token == T_OP_BRACKET
                            inc bracket_level
                        .elseif [rbx].token == T_CL_BRACKET
                            dec bracket_level
                            .break .ifz ; ( bracket_level == 0 )
                        .endif
                    .endif

                    ; if there's a literal enclosed in <>, remove the delimiters and
                    ; tokenize the item (TokenCount must be adjusted, since RunMacro()
                    ; might be called later!)

                    .if ( [rbx].token == T_STRING && [rbx].string_delim == '<' && inside_angle_brackets == 0 )

                        mov rsi,[rbx].tokpos
                        inc rsi
                        mov rcx,[rbx+asm_tok].tokpos
                        sub rcx,rsi
                        mov edx,ecx
                        mov rdi,StringBufferEnd
                        rep movsb
                        mov rdi,StringBufferEnd
                        .while byte ptr [rdi+rdx-1] != '>'
                            dec edx
                        .endw
                        mov byte ptr [rdi+rdx-1],0
                        mov StringBufferEnd,GetAlignedPointer( rdi, edx )

                        ; the string must be tokenized

                        inc inside_literal
                        mov inside_angle_brackets,1

                        mov ebx,idx
                        mov idx,TokenCount
                        mov TokenCount,Tokenize( rdi, &[rax+1], tokenarray, TOK_RESCAN )
                        imul eax,eax,asm_tok
                        add rax,tokenarray
                        mov [rax].asm_tok.lastidx,ebx

                        ; copy spaces located before the first token

                        imul ebx,idx,asm_tok
                        add rbx,tokenarray
                        mov rcx,[rbx+asm_tok].tokpos
                        sub rcx,rdi
                        mov rsi,rdi
                        mov rdi,p
                        rep movsb
                        mov p,rdi
                       .continue
                    .endif

                    ; macros functions must be expanded always.
                    ; text macros are expanded only selectively

                    .if ( [rbx].token == T_ID )

                        .if SymSearch( [rbx].string_ptr )

                            mov sym,rax
                            .if ( [rax].asym.state == SYM_MACRO &&
                                  [rax].asym.isdefined &&
                                  [rax].asym.isfunc &&
                                  [rbx+asm_tok].token == T_OP_BRACKET )

                                inc idx
                                mov idx,RunMacro( sym, idx, tokenarray, p, 0, &is_exitm2 )

                                .if idx < 0

                                    mov rax,savedStringBuffer
                                    add rax,StringBuffer
                                    mov StringBufferEnd,rax
                                    jmp toend
                                .endif

                                add p,tstrlen(p)

                                ; copy spaces behind macro function call

                                imul ebx,idx,asm_tok
                                add  rbx,tokenarray

                                .if ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )

                                    mov rsi,[rbx-asm_tok].tokpos
                                    inc rsi
                                    mov rcx,[rbx].tokpos
                                    sub rcx,rsi
                                    mov rdi,p
                                    rep movsb
                                    mov p,rdi
                                .endif
                                dec idx ; adjust token index
                                sub rbx,asm_tok
                               .continue

                            .elseif ( [rax].asym.state == SYM_TMACRO && [rax].asym.isdefined )

                                mov ecx,parmidx
                                mov edx,1
                                shl edx,cl
                                mov rdi,info
                                mov rsi,mac
                                .if ( [rsi].predefined && ( [rdi].autoexp & dx ) )

                                    tstrcpy( p, [rax].asym.string_ptr )
                                    ExpandTMacro( p, tokenarray, FALSE, 0 )
                                    add p,tstrlen( p )

                                    ; copy spaces behind text macro

                                    .if ( [rbx+asm_tok].token != T_FINAL && [rbx+asm_tok].token != T_COMMA )

                                        mov rdx,sym
                                        mov esi,[rdx].asym.name_size
                                        add rsi,[rbx].tokpos
                                        mov rcx,[rbx+asm_tok].tokpos
                                        sub rcx,rsi
                                        mov rdi,p
                                        rep movsb
                                        mov p,rdi
                                    .endif
                                    .continue
                                .endif
                            .endif
                        .endif
                    .endif
                .endif

                ; get length of item

                mov rcx,[rbx+asm_tok].tokpos
                sub rcx,[rbx].tokpos
                .if ( !inside_literal &&
                      ( [rbx+asm_tok].token == T_COMMA || [rbx+asm_tok].token == parm_end_delim ) )

                    mov rdx,[rbx].tokpos
                    .while islspace( [rdx+rcx-1] )
                        dec rcx
                    .endw
                .endif

                ; the literal character operator ! is valid for macro arguments

                mov rdi,p
                mov rsi,[rbx].tokpos
                .if ( [rbx].token == T_STRING && [rbx].string_delim == 0 )

                    add rcx,rsi
                    .for ( : rsi < rcx : )
                        .if ( byte ptr [rsi] == '!' )
                            inc rsi
                        .endif
                        movsb
                    .endf
                    mov p,rdi
                   .continue
                .endif
                rep movsb
                mov p,rdi
            .endf
            mov rax,p
            mov byte ptr [rax],0

            ; restore input status values

            mov TokenCount,old_tokencount
            mov rax,savedStringBuffer
            add rax,StringBuffer
            mov StringBufferEnd,rax

            mov rdi,info
            mov rsi,mac

            ; store the macro argument in the parameter array

            movzx eax,[rdi].parmcnt
            dec eax
            mov rdx,currparm

            .if ( [rsi].mac_vararg && parmidx == eax )

                .if ( varargcnt == 0 )

                    mov rax,mi.parm_array
                    mov ecx,parmidx
                    mov [rax+rcx*size_t],rdx
                .endif

                mov rax,p
                .if ( [rsi].predefined )

                    sub rax,currparm
                    GetAlignedPointer( currparm, eax )
                .endif
                mov currparm,rax

                ; v2.08: Masm swallows the last trailing comma

                .if ( [rbx].token == T_COMMA )

                    inc idx
                    add rbx,asm_tok
                    mov rdx,rax

                    .if ( !( [rsi].isfunc ) || [rbx].token != parm_end_delim )
                        dec parmidx
                        .if ( !( [rsi].predefined ) )
                            mov byte ptr [rdx],','
                            inc rdx
                            inc currparm
                        .endif
                        mov byte ptr [rdx],0
                    .endif
                    mov skipcomma,0
                .endif
                inc varargcnt

            .elseif byte ptr [rdx]

                mov rax,rdx
                mov rcx,mi.parm_array
                mov edx,parmidx
                mov [rcx+rdx*size_t],rax
                mov rdx,p
                sub rdx,rax
                mov currparm,GetAlignedPointer( rax, edx )
            .else
                mov rdx,mi.parm_array
                mov ecx,parmidx
                lea rax,@CStr("")
                mov [rdx+rcx*size_t],rax
            .endif
        .endif
    .endf

    ; for macro functions, check for the terminating ')'

    .if ( bracket_level >= 0 )

        .if ( [rbx].token != T_CL_BRACKET )

            .for ( i = idx: idx < TokenCount && [rbx].token != T_CL_BRACKET: idx++, rbx += asm_tok )
            .endf

            .if ( idx == TokenCount )

                mov idx,asmerr( 2157 )
                jmp toend

            .else

                ; v2.09: changed to a warning only (Masm-compatible)

                imul eax,i,asm_tok
                add rax,tokenarray
                asmerr( 4006, [rsi].name, [rax].asm_tok.tokpos )
            .endif
        .endif

        inc idx
        add rbx,asm_tok

    .elseif ( [rbx].token != T_FINAL )

        ; v2.05: changed to a warning. That's what Masm does
        ; v2.09: don't emit a warning if it's a FOR directive
        ; (in this case, the caller knows better what to do ).

        .if ( !( mflags & MF_IGNARGS ) )
            asmerr( 4006, [rsi].name, [rbx].tokpos )
        .endif
    .endif

    ; a predefined macro func with a function address?

    assume rsi:asym_t

    .if ( [rsi].predefined && [rsi].func_ptr )

        mov mi.parmcnt,varargcnt
        [rsi].func_ptr( &mi, _out, tokenarray )
        mov rax,is_exitm
        mov dword ptr [rax],TRUE
        jmp toend
    .endif

    mov mi.localstart,MacroLocals
    add MacroLocals,[rdi].localcnt ; adjust global variable MacroLocals

    ; avoid to use values stored in struct macro_info directly. A macro
    ; may be redefined within the macro! Hence copy all values that are
    ; needed later in the while loop to macro_instance!

    mov mi.startline,[rdi].lines
    mov mi.currline,NULL
    mov mi.parmcnt,[rdi].parmcnt

    .if mi.startline

        mov rax,[rsi].name
        .if ( !( [rsi].isfunc ) && byte ptr [rax] )
            LstWriteSrcLine()
        .endif
        .if ( !( mflags & MF_NOSAVE ) )
            mov tokenarray,PushInputStatus( &oldstat )
        .endif

        ; move the macro instance onto the file stack!
        ; Also reset the current linenumber!

        mov mi._macro,rsi
        PushMacro( &mi )
        inc MacroLevel
        mov oldifnesting,GetIfNestLevel() ;; v2.10
        mov cntgoto,0 ;; v2.10

        ; Run the assembler until we hit EXITM or ENDM.
        ; Also handle GOTO and macro label lines!
        ; v2.08 no need anymore to check the queue level
        ; v2.11 GetPreprocessedLine() replaced by GetTextLine()
        ; and PreprocessLine().

        .while ( GetTextLine( CurrSource ) )

            .continue .if ( PreprocessLine( tokenarray ) == 0 )

            mov rbx,tokenarray

            ; skip macro label lines

            .if ( [rbx].token == T_COLON )

                ; v2.05: emit the error msg here, not in StoreMacro()

                .if ( [rbx+asm_tok].token != T_ID )
                    asmerr( 2008, [rbx].tokpos )
                .elseif ( [rbx+asm_tok*2].token != T_FINAL )
                    asmerr( 2008, [rbx+asm_tok*2].tokpos )
                .endif
                .continue
            .endif

            .if ( [rbx].token == T_DIRECTIVE )

                .if ( [rbx].tokval == T_EXITM || [rbx].tokval == T_RETM )

                    .if ( MODULE.list && MODULE.list_macro == LM_LISTMACROALL )
                        LstWriteSrcLine()
                    .endif

                    .if ( [rbx+asm_tok].token != T_FINAL )

                        ; v2.05: display error if there's more than 1 argument or
                        ; the argument isn't a text item

                        .if ( [rbx+asm_tok].token != T_STRING || [rbx+asm_tok].string_delim != '<' )
                            TextItemError( &[rbx+asm_tok] )
                        .elseif ( TokenCount > 2 )
                            asmerr( 2008, [rbx+asm_tok*2].tokpos )
                        .elseif ( _out ) ; return value buffer may be NULL ( loop directives )

                            ; v2.08a: the <>-literal behind EXITM is handled specifically,
                            ; macro operator '!' within the literal is only handled
                            ; if it contains a placeholder (macro argument, macro local ).

                            ; v2.09: handle '!' inside literal if ANY expansion occurred.
                            ; To determine text macro or macro function expansion,
                            ; check if there's a literal in the original line.

                            mov rdi,_out
                            mov rdx,mi.currline
                            mov rax,[rbx+asm_tok].tokpos
                            sub rax,CurrSource
                            mov al,[rdx].srcline.line[rax]

                            .if ( !_retm && [rbx].tokval == T_RETM )

                                mov rax,_out
                                mov byte ptr [rax],0

                            .elseif ( [rdx].srcline.ph_count || al != '<' )

                                mov ecx,[rbx+asm_tok].stringlen
                                inc ecx
                                mov rsi,[rbx+asm_tok].string_ptr
                                rep movsb

                            .else

                                ; since the string_ptr member has the !-operator stripped, it
                                ; cannot be used. To get the original value of the literal,
                                ; use tokpos.

                                mov rsi,[rbx+asm_tok].tokpos
                                inc rsi
                                mov rcx,[rbx+asm_tok*2].tokpos
                                sub rcx,rsi
                                rep movsb
                                dec rdi
                                .while( byte ptr [rdi] != '>' )
                                    dec rdi
                                .endw
                                mov byte ptr [rdi],0
                            .endif
                        .endif
                    .endif

                    ; v2.10: if a goto had occured, rescan the full macro to ensure that
                    ; the "if"-nesting level is ok.

                    .if cntgoto

                        mov mi.currline,NULL
                        SetLineNumber( 0 )
                        SetIfNestLevel( oldifnesting )
                    .endif

                    SkipMacro( tokenarray )
                    mov rax,is_exitm
                    mov dword ptr [rax],TRUE
                   .break

                .elseif ( [rbx].tokval == T_GOTO )

                    .if ( [rbx+asm_tok].token != T_FINAL )

                        mov len,tstrlen( [rbx+asm_tok].string_ptr )

                        ; search for the destination line

                        assume rdi:srcline_t

                        .for ( i = 1, rdi = mi.startline: rdi != NULL: rdi = [rdi].next, i++ )

                            lea rsi,[rdi].line

                            .if ( byte ptr [rsi] == ':' )

                                .if ( [rdi].ph_count )

                                    fill_placeholders( StringBufferEnd, rsi, mi.parmcnt,
                                        mi.localstart, mi.parm_array )
                                    mov rsi,StringBufferEnd
                                .endif

                                inc rsi
                                .while islspace( [rsi] )
                                    inc rsi
                                .endw

                                .ifd !tmemicmp( rsi, [rbx+asm_tok].string_ptr, len )

                                    mov ecx,len ; label found!
                                   .break .if !islabel( [rsi+rcx] )
                                .endif
                            .endif
                        .endf

                        .if !rdi

                            ; v2.05: display error msg BEFORE SkipMacro()!

                            asmerr( 2147, [rbx+asm_tok].string_ptr )

                        .else

                            ; v2.10: rewritten, "if"-nesting-level handling added

                            mov mi.currline,rdi
                            SetLineNumber(i)
                            SetIfNestLevel( oldifnesting )
                            inc cntgoto
                           .continue
                        .endif
                    .else
                        asmerr( 2008, [rbx].tokpos )
                    .endif
                    SkipMacro( tokenarray )
                   .break
                .endif
            .endif

            ParseLine(tokenarray)
            .if ( Options.preprocessor_stdout == TRUE )
                WritePreprocessedLine(CurrSource)
            .endif

            ; the macro might contain an END directive.
            ; v2.08: this doesn't mean the macro is to be cancelled.
            ; Masm continues to run it and the assembly is stopped
            ; when the top source level is reached again.
        .endw

        dec MacroLevel
        .if ( !( mflags & MF_NOSAVE ) )
            PopInputStatus(&oldstat)
        .endif

        ; don't use tokenarray from here on, it's invalid after PopInputStatus()

    .endif

toend:

    .if ( mem_alloc )
        MemFree(mi.parm_array)
    .endif
    .return( idx )

RunMacro endp

    assume rsi:nothing
    assume rdi:nothing


; make room (or delete items) in the token buffer at position <start>

AddTokens proc __ccall private uses rbx tokenarray:token_t, start:int_t, count:int_t, _end:int_t

    ldr     rbx,tokenarray
ifdef _WIN64
    movsxd  rax,count
else
    mov     eax,count
endif
    imul    rcx,rax,asm_tok
    mov     edx,start

    .ifs ( eax > 0 )

        imul eax,_end,asm_tok
        add  rbx,rax

        .for ( : _end >= edx : _end--, rbx -= asm_tok )

            mov [rbx+rcx],asm_tok ptr [rbx]
        .endf

    .elseifs ( eax < 0 )

        sub  edx,eax
        imul eax,edx,asm_tok
        add  rbx,rax

        .for ( : edx <= _end : edx++, rbx += asm_tok )

            mov [rbx+rcx],asm_tok ptr [rbx]
        .endf
    .endif
    ret

AddTokens endp


; ExpandText() is called if
; - the evaluation operator '%' has been found as first char of the line.
; - the % operator is found in a macro argument.
; if substitute is TRUE, scanning for the substitution character '&' is active!
; Both text macros and macro functions are expanded!

    assume rsi:string_t
    assume rdi:string_t
    assume rdx:string_t

ExpandText proc __ccall uses rsi rdi rbx line:string_t, tokenarray:token_t, substitute:uint_t

   .new lvl:int_t
   .new is_exitm:int_t
   .new rc:int_t = NOT_ERROR
   .new i:int_t
   .new sym:asym_t
   .new sarray[MAX_TEXTMACRO_NESTING]:string_t
   .new cnt:int_t
   .new oldcnt:int_t = TokenCount
   .new quoted_string:char_t = 0
   .new macro_proc:char_t = FALSE
   .new p:string_t
   .new buffer:string_t
   .new strpos:string_t
   .new oldend:string_t

    mov rax,StringBufferEnd
    sub rax,StringBuffer
    mov oldend,rax

    mov ecx,MaxLineLength
    mov strpos,rcx
    add ecx,ecx
    mov buffer,MemAlloc(ecx)
    add strpos,rax
    mov rdi,rax
    mov sarray,line

    .for ( lvl = 0 : lvl >= 0 : lvl-- )

        mov eax,lvl
        mov rsi,sarray[rax*string_t]

        .while ( [rsi] )

            .if ( isdotlabel( [rsi], MODULE.dotname ) && ( substitute || !quoted_string ) )

                mov p,rdi
                .repeat
                    stosb
                    inc rsi
                .until !islabel( [rsi] )
                mov [rdi],0
                mov sym,SymSearch( p )

                .if ( rax && [rax].asym.isdefined )
                    .if ( [rax].asym.state == SYM_TMACRO )

                        ;
                        ; v2.08: no expansion inside quoted strings without &
                        ;
                        mov rdx,p
                        .continue .if ( quoted_string && [rdx-1] != '&' && [rsi] != '&' )

                        .if ( substitute )
                            .if ( [rdx-1] == '&' )
                                dec rdx
                            .endif
                            .if ( [rsi] == '&' )
                                inc rsi
                            .endif
                        .elseif ( rdx > buffer && [rdx-1] == '%' )
                            dec rdx
                        .endif
                        mov rdi,rdx
                        mov p,rdx
                        mov rc,STRING_EXPANDED
                        mov eax,lvl
                        inc lvl
                        mov sarray[rax*string_t],rsi
                        mov rsi,strpos
                        mov rax,sym
                        tstrlen( tstrcpy( rsi, [rax].asym.string_ptr ) )
                        mov strpos,GetAlignedPointer( rsi, eax )

                    .elseif ( [rax].asym.state == SYM_MACRO && [rax].asym.isfunc )

                        ; expand macro functions.

                        mov rcx,rsi
                        .while islspace( [rcx] )
                            inc rcx
                        .endw

                        ; no macro function invokation if the '(' is missing!

                        .if ( al == '(' )

                            mov i,TokenCount
                            inc i
                            mov TokenCount,Tokenize( rcx, i, tokenarray, TOK_RESCAN )

                            mov  edx,i
                            imul ecx,edx,asm_tok
                            add  rcx,TokenArray
                            .for ( eax = 0 : edx < TokenCount : edx++, rcx += asm_tok )
                                .if [rcx].asm_tok.token == T_OP_BRACKET
                                    inc eax
                                .elseif [rcx].asm_tok.token == T_CL_BRACKET
                                    dec eax
                                    .ifz
                                        add rcx,asm_tok
                                        .break
                                    .endif
                                .endif
                            .endf

                            ; don't substitute inside quoted strings if there's no '&'

                            mov rdx,p
                            .if ( quoted_string && [rdx-1] != '&' && [rcx].asm_tok.token != '&' )

                                mov TokenCount,oldcnt
                               .continue
                            .endif
                            .if substitute
                                .if byte ptr [rdx-1] == '&'
                                    dec p
                                .endif
                            .elseif ( rdx > buffer && [rdx-1] == '%' )
                                dec p
                            .endif

                            mov rc,RunMacro( sym, i, TokenArray, rdi, 0, &is_exitm )
                            mov ecx,oldcnt
                            mov TokenCount,ecx
                            mov rcx,oldend
                            add rcx,StringBuffer
                            mov StringBufferEnd,rcx

                            .if ( eax == -1 )

                                MemFree(buffer)
                               .return(rc)
                            .endif

                            imul ebx,eax,asm_tok
                            add rbx,TokenArray

                            mov rsi,[rbx-asm_tok].tokpos
                            add rsi,tstrlen( [rbx-asm_tok].string_ptr )
                            .if ( substitute && [rsi] == '&' )
                                inc rsi
                            .endif
                            mov eax,lvl
                            inc lvl
                            mov sarray[rax*string_t],rsi
                            tstrlen( rdi )

                            mov rsi,rdi
                            mov rdi,strpos
                            lea rcx,[rax+1]
                            rep movsb
                            mov rsi,strpos
                            mov strpos,GetAlignedPointer( rsi, eax )
                            mov rdi,p
                            mov rc,STRING_EXPANDED
                        .endif
                    .elseif [rax].asym.state == SYM_MACRO
                        mov macro_proc,TRUE
                    .endif

                    .if ( lvl == MAX_TEXTMACRO_NESTING )

                        asmerr( 2123 )
                       .break
                    .endif
                .endif
            .else
                mov al,[rsi]
                .if ( al == '"' || al == "'" )
                    .if ( quoted_string == 0 )
                        mov quoted_string,al
                    .elseif ( al == quoted_string )
                        mov quoted_string,0
                    .endif
                .endif
                movsb
            .endif
        .endw
    .endf
    xor eax,eax
    stosb
    mov rax,oldend
    add rax,StringBuffer
    mov StringBufferEnd,rax

    .if ( rc == STRING_EXPANDED )

        mov rcx,rdi
        mov rsi,buffer
        sub rcx,rsi
        mov rdi,line
        rep movsb
    .endif
    MemFree(buffer)

    .if ( substitute )

        mov rbx,TokenArray
        .if rc == STRING_EXPANDED
            mov TokenCount,Tokenize( [rbx].tokpos, 0, rbx, TOK_RESCAN )
        .endif
        .if rc == STRING_EXPANDED || macro_proc
            .if DelayExpand(rbx)
                mov rc,0
            .else
                mov rc,ExpandLine( [rbx].tokpos, rbx )
            .endif
        .endif
    .endif
    .return( rc )

ExpandText endp

    assume rsi:nothing
    assume rdi:nothing
    assume rdx:nothing

; replace text macros and macro functions by their values, recursively
; outbuf in: text macro or macro function value
; outbuf out: expanded value
; equmode: if 1, don't expand macro functions

ExpandTMacro proc __ccall private uses rsi rdi rbx outbuf:string_t,
        tokenarray:token_t, equmode:int_t, level:int_t

    .new old_tokencount:int_t = TokenCount
    .new i:int_t
    .new len:int_t
    .new is_exitm:int_t
    .new sym:asym_t
    .new rc:int_t = NOT_ERROR
    .new expanded:char_t = TRUE

    .if ( level >= MAX_TEXTMACRO_NESTING )
        .return( asmerr( 2123 ) )
    .endif
    .new buffer:string_t = alloc_line()

    .while ( expanded == TRUE )

        mov i,old_tokencount
        inc i
        mov TokenCount,Tokenize( outbuf, i, tokenarray, TOK_RESCAN )
        mov expanded,FALSE

        .for ( : i < TokenCount: i++ )

            imul ebx,i,asm_tok
            add  rbx,tokenarray

            .if ( [rbx].token == T_ID )

                mov sym,SymSearch( [rbx].string_ptr )

                ; expand macro functions

                .if ( rax &&
                      [rax].asym.state == SYM_MACRO &&
                      [rax].asym.isdefined &&
                      [rax].asym.isfunc &&
                      [rbx+asm_tok].token == T_OP_BRACKET &&
                      equmode == FALSE )

                    mov rcx,[rbx].tokpos
                    sub rcx,outbuf
                    mov rdi,buffer
                    mov rsi,outbuf
                    rep movsb
                    mov edx,i
                    inc edx
                    .ifsd ( RunMacro( sym, edx, tokenarray, rdi, 0, &is_exitm ) < 0 )
                        mov rc,ERROR
                       .break( 1 )
                    .endif
                    imul ebx,eax,asm_tok
                    add rbx,tokenarray

                    ; v2.15: don't ignore white space(s) behind closing ')' ; see expans43.asm.

                    mov rdx,[rbx].tokpos
                    .if ( eax > i && byte ptr [rdx-1] == ' ' )
                        dec rdx
                    .endif
                    mov i,eax
                    tstrcat( rdi, rdx )
                    tstrcpy( outbuf, buffer )
                    mov expanded,TRUE
                    ; is i to be decremented here?
                   .break

                .elseif ( rax && [rax].asym.state == SYM_TMACRO && [rax].asym.isdefined )

                    mov rsi,outbuf
                    mov rdi,buffer
                    mov rcx,[rbx].tokpos
                    sub rcx,rsi
                    rep movsb
                    tstrcpy( rdi, [rax].asym.string_ptr )
                    mov ecx,level
                    inc ecx
                    .ifd ExpandTMacro( rdi, tokenarray, equmode, ecx ) == ERROR
                        mov rc,eax
                       .break(1)
                    .endif
                    mov rax,sym
                    mov edx,[rax].asym.name_size
                    add rdx,[rbx].tokpos
                    tstrcat( rdi, rdx )
                    tstrcpy( outbuf, buffer )
                    mov expanded,TRUE
                   .break
                .endif
            .endif
        .endf
    .endw
    free_line(buffer)
    mov TokenCount,old_tokencount
   .return( rc )

ExpandTMacro endp


; rebuild a source line
; adjust all "pos" values behind the current pos
; - newstring = new value of item i
; - i = token buffer index of item to replace
; - outbuf = start of source line to rebuild
; - oldlen = old length of item i
; - pos_line = position of item in source line

RebuildLine proc __ccall private uses rsi rdi rbx newstring:string_t, i:int_t,
        tokenarray:token_t, oldlen:uint_t, pos_line:uint_t, addbrackets:int_t

   .new dest:string_t
   .new src:string_t
   .new newlen:uint_t
   .new rest:uint_t
   .new rc:int_t = NOT_ERROR
   .new buffer:string_t = alloc_line()

    imul ebx,i,asm_tok
    add rbx,tokenarray

    mov esi,oldlen
    add rsi,[rbx].tokpos
    inc tstrlen( rsi )
    mov rest,eax
    mov rdi,buffer
    mov ecx,eax
    rep movsb ; save content of line behind item

    mov rdi,[rbx].tokpos
    mov newlen,tstrlen( newstring )

    .if ( addbrackets )

        add newlen,2 ; count '<' and '>'

        .for ( rsi = newstring, al = [rsi] : al : rsi++, al = [rsi] )

            .if ( al == '<' || al == '>' || al == '!' ) ; count '!' operator
                inc newlen
            .endif
        .endf
    .endif

    .if ( newlen > oldlen )

        mov eax,pos_line
        add eax,newlen
        sub eax,oldlen
        add eax,rest
        .if ( eax >= MaxLineLength )

            mov rc,asmerr( 2039 )
            jmp toend
        .endif
    .endif

    .if ( addbrackets )

        mov byte ptr [rdi],'<'
        inc rdi

        .for ( rsi = newstring: byte ptr [rsi] : rsi++ )

            mov al,[rsi]
            .if ( al == '<' || al == '>' || al == '!' )
                mov byte ptr [rdi],'!'
                inc rdi
            .endif
            mov [rdi],al
            inc rdi
        .endf
        mov byte ptr [rdi],'>'
        inc rdi
    .else
        mov ecx,newlen
        mov rsi,newstring
        rep movsb
    .endif

    mov ecx,rest
    mov rsi,buffer
    rep movsb ; add rest of line

    ; v2.05: changed '<' to '<='

    .for ( ecx = i, ecx++,
           rbx += asm_tok,
           eax = oldlen,
           edx = newlen : ecx <= TokenCount : ecx++, rbx += asm_tok )

        sub [rbx].tokpos,rax
        add [rbx].tokpos,rdx
    .endf

toend:

     free_line(buffer)
    .return( rc )

RebuildLine endp


; expand one token
; line: full source line
; *pi: index of token in tokenarray
; equmode: if 1, dont expand macro functions

ExpandToken proc __ccall private uses rsi rdi rbx line:string_t, pi:ptr int_t, tokenarray:token_t,
        max:int_t, bracket_flags:int_t, equmode:int_t, buffer:ptr char_t

    local pos:int_t
    local i2:int_t
    local i:int_t
    local size:int_t
    local addbrackets:int_t
    local evaluate:char_t
    local is_exitm:int_t
    local opndx:expr
    local rc:int_t
    local old_tokencount:int_t

    ldr rdx,pi
    mov i,[rdx]
    mov addbrackets,bracket_flags
    mov evaluate,FALSE
    mov rc,NOT_ERROR

    .for ( : i < max : i++ )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .break .if ( [rbx].token == T_COMMA )

        ; v2.05: the '%' should only be handled as an operator if addbrackets==TRUE,
        ; which means that the current directive is a preprocessor directive and the
        ; expected argument is a literal (or text macro).

        .if ( [rbx].token == T_PERCENT && addbrackets && evaluate == FALSE )

            mov evaluate,TRUE
            mov addbrackets,FALSE
            mov equmode,FALSE
            mov pos,i
           .continue
        .endif

        .if ( [rbx].token == T_ID )

            mov rsi,SymSearch( [rbx].string_ptr )

            ; don't check isdefined flag (which cannot occur in pass one, and this code usually runs
            ; in pass one only!

            .if ( rsi )

                .if ( [rsi].asym.state == SYM_MACRO )

                    mov ecx,i
                    mov edi,ecx ;; save index of macro name

                    .if ( [rsi].asym.isfunc )

                        ; ignore macro functions without a following '('

                        .continue .if ( [rbx+asm_tok].token != T_OP_BRACKET )

                        inc i
                        add rbx,asm_tok

                        .if ( equmode == TRUE )

                            inc i ; skip '('
                            add rbx,asm_tok

                            ; go beyond the ')'

                            .for ( ecx = 1: i < max: i++, rbx += asm_tok )
                                .if ( [rbx].token == T_OP_BRACKET )
                                    inc ecx
                                .elseif ( [rbx].token == T_CL_BRACKET )
                                    dec ecx
                                    .break .ifz
                                .endif
                            .endf
                            dec i
                            sub rbx,asm_tok
                           .continue
                        .endif

                        xor edx,edx
                        .if edi == 1
                            mov edx,MF_LABEL
                        .endif

                        mov i,RunMacro( rsi, i, tokenarray, buffer, edx, &is_exitm )
                        .return .if ( eax == -1 )

                        imul ebx,i,asm_tok
                        add rbx,tokenarray

                        ; expand text, but don't if macro was at position 0 (might be a text macro definition directive
                        ; v2.09: don't expand further if addbrackets is set

                        .if edi && !addbrackets
                            .return .ifd ExpandTMacro( buffer, tokenarray, equmode, 0 ) == ERROR
                        .endif

                        ; get size of string to replace ( must be done before AddTokens()

                        imul ecx,edi,asm_tok
                        mov rax,[rbx-asm_tok].tokpos
                        inc rax
                        add rcx,tokenarray
                        sub rax,[rcx].asm_tok.tokpos
                        mov size,eax
                        mov edx,edi
                        inc edx
                        mov ecx,edx
                        sub ecx,i
                        AddTokens( tokenarray, edx, ecx, TokenCount )

                        mov eax,edi
                        inc eax
                        sub eax,i
                        add TokenCount,eax
                        .if ( TokenCount < max ) ; take care not to read beyond T_FINAL
                            mov max,TokenCount
                        .endif
                        imul ecx,edi,asm_tok
                        add rcx,tokenarray
                        mov rdx,[rcx].asm_tok.tokpos
                        sub rdx,line
                        .return .ifd RebuildLine( buffer, edi, tokenarray, size, edx, addbrackets ) == ERROR
                        mov rc,STRING_EXPANDED
                        mov i,edi

                    .else

                        ; a macro proc is expanded at pos 0 or pos 2
                        ; (or at pos 1 if sym->label is on)

                        mov edx,i
                        mov rcx,tokenarray
                        .if ( edx == 0 || ( edx == 2 && ( [rcx+asm_tok].asm_tok.token == T_COLON ||
                             [rcx+asm_tok].asm_tok.token == T_DBL_COLON ) ) ||
                             ( edx == 1 && [rsi].asym.islabel ) )
                        .else
                            .continue
                        .endif

                        ; v2.08: write optional code label. This has been
                        ; moved out from RunMacro().

                        .if ( edx == 2 )
                            .return .ifd WriteCodeLabel( line, tokenarray ) == ERROR
                            mov edx,i
                        .endif

                        mov ecx,MF_NOSAVE
                        .if ( edx == 1 )
                            or ecx,MF_LABEL
                        .endif
                        inc edx

                        .ifd ( RunMacro( rsi, edx, tokenarray, NULL, ecx, &is_exitm ) == -1 )
                            .return
                        .endif
                        .return EMPTY ; no further processing
                    .endif

                .elseif ( [rsi].asym.state == SYM_TMACRO )

                    .if ( [rbx-asm_tok].token == T_DOT )

                        ; v2.34.01 - Name conflict with register param and stuct members
                        ;
                        ; This apply to SYSCALL-64, WATCALL-32, and FASTCALL-32

                        mov ecx,i
                        sub ecx,2
                        lea rdx,[rbx-asm_tok*2]

                        ; [reg].type.name

                        .while ( [rdx-asm_tok].asm_tok.token == T_DOT )

                            sub ecx,2
                            lea rdx,[rdx-asm_tok*2]
                        .endw

                        .if ( [rdx].asm_tok.token == T_CL_SQ_BRACKET )

                            .for ( eax = 0 : rdx > tokenarray : rdx -= asm_tok, ecx-- )

                                .if ( [rdx].asm_tok.token == T_OP_SQ_BRACKET )
                                    dec eax
                                   .break .ifz
                                .elseif ( [rdx].asm_tok.token == T_CL_SQ_BRACKET )
                                    inc eax
                                .endif
                            .endf
                        .endif

                        mov i2,ecx
                        .ifd ( EvalOperand( &i2, tokenarray, TokenCount, &opndx, EXPF_NOERRMSG ) != ERROR )

                            .if ( opndx.kind == EXPR_ADDR && opndx.mbr )
                                .continue
                            .endif
                        .endif
                    .endif

                    tstrcpy( buffer, [rsi].asym.string_ptr )
                    .ifd ( ExpandTMacro( buffer, tokenarray, equmode, 0 ) == ERROR )
                        .return
                    .endif

                    mov edx,tstrlen( [rbx].string_ptr )
                    mov rcx,[rbx].tokpos
                    sub rcx,line
                    .ifd ( RebuildLine( buffer, i, tokenarray, edx, ecx, addbrackets ) == ERROR )
                        .return
                    .endif
                    mov rc,STRING_EXPANDED

                .elseif ( [rsi].asym.state == SYM_STACK && i > 2 &&
                          [rbx-asm_tok].token == T_OP_BRACKET && [rbx-asm_tok*2].tokval == T_LDR )

                    ; v2.36.01 -- extension: pull register from ldr(param)
                    ; v2.36.11 -- moved here

                    .if ( [rsi].asym.regparam )
                        movzx ecx,[rsi].asym.param_reg
                        GetResWName( ecx, buffer )
                    .else
                        tstrcpy( buffer, [rbx].string_ptr )
                    .endif
                    sub rbx,asm_tok*2
                    sub i,2
                    mov rcx,[rbx+asm_tok*4].tokpos
                    mov rdx,rcx
                    sub rdx,[rbx].tokpos
                    sub rcx,line
                    .ifd ( RebuildLine( buffer, i, tokenarray, edx, ecx, addbrackets ) == ERROR )
                        .return
                    .endif
                    mov rc,STRING_EXPANDED
                    mov TokenCount,Tokenize( line, 0, tokenarray, TOK_RESCAN )
                    mov max,eax
                .endif
            .endif
        .endif
    .endf

    mov ecx,i
    mov rax,pi
    mov [rax],ecx

    .if ( evaluate )

        mov old_tokencount,TokenCount
        mov rbx,tokenarray
        mov edx,pos
        lea rax,[rdx+1]

        .if ( eax == i ) ; just a single %?

            mov opndx.value,0
            mov i,edx

        .else

            mov i,edx
            inc edx
            imul ecx,ecx,asm_tok
            imul edx,edx,asm_tok
            mov rcx,[rbx+rcx].tokpos
            mov rsi,[rbx+rdx].tokpos
            mov rdi,buffer
            sub rcx,rsi
            rep movsb
            mov byte ptr [rdi],0
            mov edi,old_tokencount
            inc edi
            mov TokenCount,Tokenize( buffer, edi, tokenarray, TOK_RESCAN )

            mov i2,edi
            .ifd EvalOperand( &i2, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF ) == ERROR
                mov opndx.value,0 ; v2.09: assume value 0, don't return with ERROR
            .elseif opndx.kind != EXPR_CONST
                asmerr( 2026 )
                mov opndx.value,0 ; assume value 0
            .endif
            mov TokenCount,old_tokencount
        .endif

if TEVALUE_UNSIGNED

        ; v2.03: Masm compatible: returns an unsigned value

        mov opndx.hvalue,0
        myltoa( opndx.llvalue, StringBufferEnd, MODULE.radix, FALSE, FALSE )

else
        xor eax,eax
        .if ( opndx.hvalue < 0 )
            mov eax,1
        .endif
        myltoa( opndx.llvalue, StringBufferEnd, MODULE.radix, eax, FALSE )
endif
        ; v2.05: get size of string to be "replaced"

        mov rsi,pi
        mov esi,[rsi]
        imul eax,esi,asm_tok
        imul edx,i,asm_tok
        mov rdi,[rbx+rax].tokpos
        sub rdi,[rbx+rdx].tokpos
        add rbx,rdx
        mov [rbx].string_ptr,StringBufferEnd
        mov eax,i
        inc eax
        mov edx,eax
        sub edx,esi
        AddTokens( tokenarray, eax, edx, TokenCount )
        mov eax,i
        inc eax
        sub eax,esi
        add TokenCount,eax
        mov rcx,[rbx].tokpos
        sub rcx,line
        .return .ifd RebuildLine( StringBufferEnd, i, tokenarray, edi, ecx, bracket_flags ) == ERROR
        mov rc,STRING_EXPANDED
    .endif
    .return( rc )

ExpandToken endp


; used by EQU ( may also be used by directives flagged with DF_NOEXPAND
; if they have to partially expand their arguments ).
; equmode: 1=don't expand macro functions

ExpandLineItems proc __ccall uses rsi rdi line:string_t, i:int_t, tokenarray:token_t,
        addbrackets:int_t, equmode:int_t

   .new k:int_t
   .new buffer:string_t = alloc_line()

    .for ( esi = 0 :: esi++ )

        mov edi,NOT_ERROR
        .for ( k = i : k < TokenCount : )

            ExpandToken(line, &k, tokenarray, TokenCount, addbrackets, equmode, buffer)
            .break(1) .if eax == ERROR
            .if eax == STRING_EXPANDED
                mov edi,eax
            .endif
            imul eax,k,asm_tok
            add rax,tokenarray
            .if ( [rax].asm_tok.token == T_COMMA )
                inc k
            .endif
        .endf
        .break .if ( edi == NOT_ERROR )

        ; expansion happened, re-tokenize and continue!

        mov TokenCount,Tokenize( line, i, tokenarray, TOK_RESCAN )

        .if ( esi == MAX_TEXTMACRO_NESTING )

            asmerr( 2123 )
           .break
        .endif
    .endf
     free_line(buffer)
    .return( esi )

ExpandLineItems endp


; v2.09: added, expand literals for structured data items.
; since 2.09, initialization of structure members is no longer
; done by generated code, but more directly inside data.c.
; This improves Masm-compatibility, but OTOH requires to expand
; the literals explicitly.

ExpandLiterals proc __ccall uses rbx i:int_t, tokenarray:token_t

    xor eax,eax
    ldr rbx,tokenarray

    ; count non-empty literals

    .for ( : ecx < TokenCount: ecx++ )

        imul edx,ecx,asm_tok
        .if ( [rbx+rdx].token == T_STRING && [rbx+rdx].stringlen &&
             ( [rbx+rdx].string_delim == '<' || [rbx+rdx].string_delim == '{' ) )
            inc eax
        .endif
    .endf

    ; if non-empty literals are found, expand the line. if the line
    ; was expanded, re-tokenize it.

    .if ( eax )

        imul ecx,i,asm_tok
        add rbx,rcx

        .if ExpandText( [rbx].tokpos, tokenarray, FALSE ) == STRING_EXPANDED

            Tokenize( [rbx].tokpos, i, tokenarray, TOK_RESCAN )
        .endif
    .endif
    ret

ExpandLiterals endp


; scan current line for (text) macros and expand them.
; this is only called when the % operator is not the first item.

ExpandLine proc __ccall uses rsi rdi rbx string:string_t, tokenarray:token_t

   .new count         : int_t
   .new bracket_flags : uint_t
   .new flags         : int_t
   .new lvl           : int_t
   .new rc            : int_t
   .new addbrackets   : int_t
   .new tmp           : int_t
   .new class         : string_t
   .new buffer        : string_t = alloc_line()

    ; filter certain conditions.
    ; bracket_flags: for (preprocessor) directives that expect a literal
    ; parameter, the expanded argument has to be enclosed in '<>' again.

    .for ( lvl = 0: lvl < MAX_TEXTMACRO_NESTING: lvl++ )

        xor esi,esi
        mov bracket_flags,esi
        mov count,esi
        mov rc,esi
        mov rbx,tokenarray

        .if ( TokenCount > 2 )

            .if ( [rbx+asm_tok].token == T_COLON || [rbx+asm_tok].token == T_DBL_COLON )

                ; no expansion right of label:[:]

                .if ( [rbx].token != T_ID ||
                      [rbx+asm_tok].token == T_COLON ||
                      [rbx+asm_tok*2].token != T_ID )

                   .break
                .endif

                .if ( SymFind( [rbx+asm_tok*2].string_ptr ) )
                    .if ( [rax].asym.state == SYM_MACRO )

                       .break
                    .endif
                .endif
                .if ( [rbx+asm_tok*2].token == T_DIRECTIVE )
                    add rbx,asm_tok*2
                .endif
            .endif
        .endif

        mov rdx,tokenarray
        .if ( [rbx].token == T_DIRECTIVE )

            mov flags,GetValueSp( [rbx].tokval )
            .if ( eax & DF_STRPARM )

                mov bracket_flags,-1

                ; v2.08 handle .ERRDEF and .ERRNDEF here. Previously
                ; expansion for these directives was handled in condasm.asm,
                ; and the directives were flagged as DF_NOEXPAND.

                .if ( [rbx].dirtype == DRT_ERRDIR )
                    .if ( [rbx].tokval == T_DOT_ERRDEF ||
                          [rbx].tokval == T_DOT_ERRNDEF )

                        .if esi
                            mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE, buffer )
                        .endif
                        .while [rbx].token != T_FINAL && [rbx].token != T_COMMA
                            inc esi
                            add rbx,asm_tok
                        .endw
                        mov count,esi ; don't expand the symbol name
                    .endif
                .endif

            .elseif ( eax & DF_NOEXPAND )

                ; [ELSE]IF[N]DEF, ECHO, FOR[C]
                ; .[NO|X]CREF, INCLUDE
                ; don't expand arguments

                mov rc,NOT_ERROR
               .break
            .endif

        .elseif TokenCount > 1 && [rdx+asm_tok].asm_tok.token == T_DIRECTIVE

            mov al,[rdx+asm_tok].asm_tok.dirtype
            .switch al
            .case DRT_CATSTR
                mov bracket_flags,-1
                mov count,2
               .endc
            .case DRT_SUBSTR
                ; syntax: name SUBSTR <literal>, pos [, size]
                mov bracket_flags,0x1
                mov count,2
               .endc
            .case DRT_SIZESTR
                ; syntax: label SIZESTR literal
                mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE, buffer )
                mov bracket_flags,0x1
                mov count,2
               .endc
            .case DRT_INSTR
                ; syntax: label INSTR [number,] literal, literal
                mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE, buffer )
                ; check if the optional <number> argument is given
                .for esi = 2, eax = 0, ecx = 0: esi < TokenCount: esi++
                    imul ebx,esi,asm_tok
                    add rbx,tokenarray
                    .if [rbx].token == T_OP_BRACKET
                        inc eax
                    .elseif [rbx].token == T_CL_BRACKET
                        dec eax
                    .elseif [rbx].token == T_COMMA && eax == 0
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
                SymSearch( [rdx].asm_tok.string_ptr )
                ; don't expand macro DEFINITIONs!
                ; the name is an exception, if it's not the macro itself

                .if ( rax && [rax].asym.state != SYM_MACRO )
                    mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE, buffer )
                .endif
                mov count,TokenCount ; stop further expansion
               .endc
            .case DRT_EQU
                ; EQU is a special case. If the - expanded - expression is
                ; a number, then the value for EQU is numeric. Else the
                ; expression isn't expanded at all. This effectively makes it
                ; impossible to expand EQU lines here.

                mov rc,NOT_ERROR
               .break
            .endsw
        .else
            ; v2.08: expand the very first token and then ...
            mov rc,ExpandToken( string, &count, tokenarray, 1, FALSE, FALSE, buffer )

            .if ( eax == ERROR || eax == EMPTY )

               .break
            .endif

            .if ( rc == STRING_EXPANDED )
                ;
                ; ... fully retokenize - the expansion might have revealed a
                ; conditional assembly directive
                ;
                mov TokenCount,Tokenize( string, 0, tokenarray, TOK_DEFAULT )
               .continue
            .endif
            mov rax,tokenarray
            .if ( count == 1 && [rax].asm_tok.token == T_ID && [rax+asm_tok].asm_tok.token == T_ID )
                mov rc,ExpandToken( string, &count, tokenarray, 2, FALSE, FALSE, buffer )
                .if ( eax == ERROR || eax == EMPTY )

                   .break
                .endif
                .if ( rc == STRING_EXPANDED )

                    mov TokenCount,Tokenize( string, 0, tokenarray, TOK_DEFAULT )
                   .continue
                .endif
            .endif
        .endif
        ;
        ; scan the line from left to right for (text) macros.
        ; it's currently not quite correct. a macro proc should only
        ; be evaluated in the following cases:
        ; 1. it is the first token of a line
        ; 2. it is the second token, and the first one is an ID
        ; 3. it is the third token, the first one is an ID and
        ;    the second is a ':' or '::'.
        ;
        .while ( count < TokenCount )

            mov eax,bracket_flags
            and eax,1
            mov addbrackets,eax
            .if bracket_flags != -1
                shr bracket_flags,1
            .endif
            ExpandToken( string, &count, tokenarray, TokenCount, addbrackets, FALSE, buffer )

            .ifs ( eax < NOT_ERROR ) ; ERROR or EMPTY?

                mov rc,eax
               .break( 1 )
            .endif

            .if eax == STRING_EXPANDED
                mov rc,STRING_EXPANDED
            .endif
            imul ebx,count,asm_tok
            add rbx,tokenarray
            .if ( [rbx].token == T_COMMA )
                inc count
            .endif
        .endw

        .if ( rc == STRING_EXPANDED )
            mov TokenCount,Tokenize( string, 0, tokenarray, TOK_RESCAN or TOK_LINE )
        .endif

        mov rbx,tokenarray
        .if ( TokenCount > 2 && [rbx].Expand )

            .if ( [rbx].IsProc )

                lea rsi,@CStr( "invoke " )
                SymSearch( [rbx].string_ptr )
                .if ( rax && [rax].asym.state == SYM_TYPE )
                    lea rsi,@CStr( ".new " )
                .endif
                tstrcat( tstrcpy( buffer, rsi ), [rbx].tokpos )
                mov TokenCount,Tokenize( tstrcpy( string, buffer ), 0, tokenarray, TOK_DEFAULT )
            .endif

            .for ( : [rbx].token != T_FINAL : rbx += asm_tok )

                .if ( [rbx+asm_tok].token == T_DBL_COLON )

                    mov class,[rbx].string_ptr
                    .if ( SymSearch( rax ) )
                        .if ( [rax].asym.state == SYM_TYPE )
                            .while ( [rax].asym.type )
                                mov rax,[rax].asym.type
                            .endw
                        .endif
                        mov rcx,[rax].asym.name
                        mov class,rcx
                    .endif

                    xor edi,edi
                    mov ecx,[rbx+3*asm_tok].tokval
                    .if ( [rbx+3*asm_tok].token == T_DIRECTIVE &&
                        ( ecx == T_PROC || ecx == T_PROTO ) )

                        ; if 'class::name proto|proc'

                        inc edi
                        .if ( rax && [rax].asym.isclass )

                            ; - add 'this:ptr class' as first argument

                            inc edi
                        .endif

                    .else

                        ; class::name(..
                        ; class::name endp

                        mov al,[rbx].token
                        mov ah,[rbx+asm_tok*2].token
                        .if ( ( al != T_REG && [rbx+3*asm_tok].token == T_OP_BRACKET ) ||
                              ( al < T_STRING && al > T_REG && ah < T_STRING && ah > T_REG ) )

                            ; T_DIRECTIVE
                            ; T_UNARY_OPERATOR
                            ; T_BINARY_OPERATOR
                            ; T_STYPE
                            ; T_RES_ID
                            ; T_ID

                            inc edi
                        .endif

                    .endif
                    mov tmp,edi

                    .if ( edi )

                        mov rdi,buffer
                        mov rdx,tokenarray
                        mov rsi,[rdx].asm_tok.tokpos
                        mov rcx,[rbx].tokpos
                        sub rcx,rsi
                        rep movsb
                        mov rsi,class
                        .repeat
                            lodsb
                            stosb
                        .until !al
                        mov byte ptr [rdi-1],'_'

                        .if !tstrcmp( [rbx].string_ptr, [rbx+asm_tok*2].string_ptr )

                            mov rsi,class
                            .repeat
                                lodsb
                                stosb
                            .until !al
                            mov byte ptr [rdi-1],' '
                            mov rsi,[rbx+asm_tok*3].tokpos
                            mov edx,4*asm_tok
                        .else
                            mov rsi,[rbx+asm_tok*2].tokpos
                            mov edx,3*asm_tok
                        .endif

                    .endif

                    .if ( tmp == 1 )

                        mov ecx,tstrlen(rsi)
                        inc ecx
                        rep movsb

                    .elseif ( tmp > 1 )

                        ;
                        ; class::name proc syscall private uses regs name:dword,..
                        ;
                        .for ( : [rbx+rdx].token != T_FINAL : rdx+=asm_tok )
                            .break .if ( [rbx+rdx].token == T_COLON )
                            .break .if ( [rbx+rdx].token == T_STRING )
                        .endf

                        .if ( [rbx+rdx].token == T_COLON && [rbx+rdx-asm_tok].token == T_ID )

                            sub rdx,asm_tok
                        .endif

                        mov rcx,[rbx+rdx].tokpos
                        sub rcx,rsi
                        rep movsb

                        .if ( byte ptr [rdi-1] == ' ' )
                            dec rdi
                        .endif

                        ; add " this:ptr class"

                        mov eax,'iht '
                        stosd
                        mov eax,'tp:s'
                        stosd
                        mov ax,' r'
                        stosw
                        mov rcx,class
                        mov al,[rcx]
                        .while al
                            stosb
                            inc rcx
                            mov al,[rcx]
                        .endw

                        .if ( [rbx+rdx].token == T_COLON || [rbx+rdx+asm_tok].token == T_COLON )
                            mov eax,' ,'
                            stosw
                        .endif
                        mov ecx,tstrlen(rsi)
                        inc ecx
                        rep movsb
                    .endif

                    .if ( edi )

                        tstrcpy(string, buffer)
                        mov TokenCount,Tokenize( string, 0, tokenarray, TOK_DEFAULT )
                        .if ( eax > 2 && rbx == tokenarray && [rbx].IsProc &&
                              [rbx+asm_tok].token == T_OP_BRACKET )

                            tstrcat( tstrcpy( buffer, "invoke " ), [rbx].tokpos )
                            mov TokenCount,Tokenize( tstrcpy( string, buffer ), 0, rbx, TOK_DEFAULT )
                        .endif
                        sub rbx,asm_tok
                    .endif
                .endif
            .endf
        .endif
        .break .if ( rc != STRING_EXPANDED )
    .endf

    free_line(buffer)
    .if ( lvl == MAX_TEXTMACRO_NESTING )
        .return asmerr( 2123 )
    .endif
    .return( rc )

ExpandLine endp

    end
