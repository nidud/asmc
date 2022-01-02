; MACRO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; macro handling.
;
; functions:
; - CreateMacro             create a macro item
; - ReleaseMacroData used to redefine/purge a macro
; - StoreMacro      store a macro's parameter/local/line list
; - MacroDir        handle MACRO directive
; - PurgeDirective   handle PURGE directive
; - MacroInit       global macro initialization, set predefined macros
;

include asmc.inc
include memalloc.inc
include parser.inc
include input.inc
include tokenize.inc
include macro.inc
include fastpass.inc
include listing.inc
include malloc.inc
include ltype.inc

CCALLBACK(GETLINE, :string_t)

;; a placeholder consists of escape char (0x0a) + index (1 byte).
;; if this is to change, function fill_placeholders() must
;; be adjusted!

PLACEHOLDER_SIZE equ 2

MAX_PLACEHOLDERS equ 256

;; store empty macro lines, to ensure correct line numbering

STORE_EMPTY_LINES equ 1

;; 1="undefine" macros with PURGE - this isn't Masm-compatible,
;; and offers no real benefit because the name remains in the namespace.
;; The macro is marked "undefined" and cannot be invoked anymore.
;; 0=just delete the macro content.

TRUEPURGE equ 0

externdef MacroLocals:int_t

;; the list of macro param + local names is hold temporarily only.
;; once the names have been replaced by placeholders,
;; the list is superfluous. What's stored permanently
;; in the macro item is the number of params and locals only.

mname_list struct
    name    string_t ?  ;; name of param/local
    len     dw ?
mname_list ends

    .data
    GetLine GETLINE GetTextLine

    .code

;; Replace placeholders in a stored macro source line with values of actual
;; parameters and locals. A placeholder consists of escape char 0x0a,
;; followed by a one-byte index field.

fill_placeholders proc uses rsi rdi rbx dst:string_t, src:string_t, argc:uint_t,
        localstart:uint_t, argv:array_t

    mov rdi,rcx

    ;; scan the string, replace the placeholders #nn

    .for( rsi = rdx: byte ptr [rsi]: )
        .if ( byte ptr [rsi] == PLACEHOLDER_CHAR )
            add rsi,2
            ;; we found a placeholder, get the index part!
            movzx ebx,byte ptr [rsi-1]
            dec ebx ;; index is one-based!

            ;; if parmno > argc, then it's a macro local

            .if ebx >= argc

                mov eax,'??'
                stosw
                add ebx,localstart
                sub ebx,argc
                .if ebx > 0xFFFF
                    tsprintf( rdi, "%X", ebx )
                    add rdi,rbx
                .else
                    mov eax,ebx
                    and eax,0x0F0F
                    shr ebx,4
                    and ebx,0x0F0F
                    add ebx,'00'
                    add eax,'00'
                    .if al > '9'
                        add al,'A' - '9' - 1
                    .endif
                    .if ah > '9'
                        add ah,'A' - '9' - 1
                    .endif
                    .if bl > '9'
                        add bl,'A' - '9' - 1
                    .endif
                    .if bh > '9'
                        add bh,'A' - '9' - 1
                    .endif
                    mov [rdi+0],bh
                    mov [rdi+1],ah
                    mov [rdi+2],bl
                    mov [rdi+3],al
                    add rdi,4
                .endif
            .else
                mov rdx,argv
                mov rbx,[rdx+rbx*8]
                .if rbx  ;; actual parameter might be empty (=NULL)
                    mov ecx,tstrlen(rbx)
                    xchg rbx,rsi
                    rep movsb
                    mov rsi,rbx
                .endif
            .endif
        .else
            movsb
        .endif
    .endf
    mov byte ptr [rdi],0
    ret

fill_placeholders endp

replace_parm proc private uses rsi rdi rbx line:string_t, start:string_t, len:int_t, mnames:ptr mname_list

    ;; scan list of macro paras/locals if current word is found.
    ;; - line: current line
    ;; - start: start 'current word' in line
    ;; - len: size current word
    ;; - mnames: list of macro params+locals
    ;; if found, the 'current word' is replaced by a placeholder.
    ;; format of placeholders is <placeholder_char><index>
    ;; <placeholder_char> is an escape character whose hex-code is
    ;; "impossible" to occur in a source line, <index> has type uint_8,
    ;; value 00 isn't used - this restricts the total of parameters
    ;; and locals for a macro to 255.

    local count:uint_t

    mov rbx,mnames
    assume rbx:ptr mname_list

    .for ( count = 1: [rbx].name: count++, rbx += mname_list )

        .continue .if [rbx].len != len

        .if !SymCmpFunc( start, [rbx].name, len )

            ;; found a macro parameter/local!

            .if count >= MAX_PLACEHOLDERS
                asmerr(1005)
                .break
            .endif

            ;; handle substitution operator '&'
            mov rdi,start
            mov esi,len
            add rsi,rdi
            .if rdi != line && byte ptr [rdi-1] == '&'
                dec rdi
            .endif
            .if byte ptr [rsi] == '&'
                inc rsi
            .endif
            mov eax,PLACEHOLDER_CHAR
            stosb

            ; additional space needed for the placeholder?
            .if rdi >= rsi
                lea rcx,[rsi+tstrlen(rsi)]
                lea rdx,[rcx+1]
                .while ( rcx >= rsi )
                    mov al,[rcx]
                    mov [rdx],al
                    dec rcx
                    dec rdx
                .endw
                mov eax,count
                mov [rdi],al
            .else
                mov eax,count
                stosb

                ; v2.10: strcpy should not be used if strings overlap
                tmemmove( rdi, rsi, &[tstrlen(rsi)+1] )
            .endif
            .return rdi ;; word has been replaced
        .endif
    .endf
    xor eax,eax
    ret

replace_parm endp

store_placeholders proc private uses rsi rdi rbx line:string_t, mnames:ptr mname_list
    ;
    ; scan a macro source line for parameter and local names.
    ; - line: the source line
    ; - mnames: list of macro params + locals
    ; if a param/local is found, replace the name by a 2-byte placeholder.
    ;
  local qlevel:uchar_t

    xor edi,edi ;; number of replacements in this line
    xor ebx,ebx
    mov qlevel,bl

    .for ( rsi = line : byte ptr [rsi] : )

        movzx ecx,byte ptr [rsi-1]
        lea r8,_ltype
        .if isldigit( [rsi] )
            ;
            ; skip numbers (they may contain alphas)
            ; this is not exactly what masm does. Masm
            ; stops at the first non-digit.
            ;
            .repeat
                inc rsi
            .until !is_valid_id_char( [rsi] )

        .elseif ( is_valid_id_char( eax ) || \
                ( al == '.' && ModuleInfo.dotname && \
                ( rsi == line || ( cl != ']' && ( !( byte ptr [r8+rcx+1] & _DIGIT or _LABEL ) ) ) ) ) )

            mov rdx,rsi
            .repeat
                inc rsi
            .until !is_valid_id_char( [rsi] )
            ;
            ; v2.08: both a '&' before AND after the name trigger substitution (and disappear)
            ;
            xor eax,eax
            .if ( ( rdx > line && byte ptr [rdx-1] == '&' ) || byte ptr [rsi] == '&' )
                inc eax
            .endif
            .if ( bl == 0 || eax )
                ;
                ; look for this word in the macro parms, and replace it if it is
                ;
                mov rax,rsi
                sub rax,rdx
                .if replace_parm( line, rdx, eax, mnames )
                    inc rdi
                    mov rsi,rax
                .endif
            .endif
        .else
            .switch eax
            .case '!'
                ;
                ; v2.11: skip next char only if it is a "special" one; see expans40.asm
                ;
                .if bl == 0
                    movzx eax,byte ptr [rsi+1]
                    .if strchr( "<>\"'", eax )
                        inc rsi
                    .endif
                .endif
                .endc
            .case '<'
                inc bh
                .endc
            .case '>'
                .if bh
                    .if qlevel == bh
                        mov bl,0
                    .endif
                    dec bh
                .endif
                .endc
            .case '"'
            .case "'"
                .if bl
                    .if bl == al
                        mov bl,0
                    .endif
                .else
                    mov bl,al
                    mov qlevel,bh
                .endif
            .endsw
            inc rsi
        .endif
    .endf
    mov rax,rdi
    ret

store_placeholders endp


;; store a macro's parameter, local and content list.
;; i = start index of macro params in token buffer.

    assume rsi:dsym_t
    assume rdi:ptr macro_info
    assume rbx:token_t

externdef token_stringbuf:ptr

StoreMacro proc uses rsi rdi rbx r12 mac:dsym_t, i:int_t, tokenarray:token_t, store_data:int_t

  local info:ptr macro_info
  local src:string_t
  local token:string_t
  local mindex:int_t
  local paranode:ptr mparm_list
  local nextline:srcline_t
  local nesting_depth:uint_t
  local locals_done:int_t
  local ls:line_status
  local tok[2]:asm_tok
  local mnames[MAX_PLACEHOLDERS]:mname_list ;; there are max 255 placeholders
  local final:token_t

    mov ls.outbuf,token_stringbuf
    mov ls.start,alloca( ModuleInfo.max_line_len )

    mov nesting_depth,0
    mov rsi,mac
    mov rdi,[rsi].macroinfo
    mov info,rdi
    imul ebx,i,asm_tok
    add rbx,tokenarray
    imul eax,Token_Count,asm_tok
    add rax,tokenarray
    mov final,rax

    .if store_data

        .if ( rbx < final )
            .for ( rax = rbx, [rdi].parmcnt = 1: rax < final: rax += asm_tok )
                .if [rax].asm_tok.token == T_COMMA
                    inc [rdi].parmcnt
                .endif
            .endf
            movzx ecx,[rdi].parmcnt
            imul eax,ecx,mparm_list
            mov [rdi].parmlist,LclAlloc(eax)
        .else
            mov [rdi].parmcnt,0
            mov [rdi].parmlist,NULL
        .endif

        assume rsi:ptr mparm_list
        .for( rsi = [rdi].parmlist, mindex = 0: rbx < final : rsi += mparm_list )

            mov token,[rbx].string_ptr

            ;; Masm accepts reserved words and instructions as parameter
            ;; names! So just check that the token is a valid id.

            .if ( !is_valid_id_first_char( [rax] ) || [rbx].token == T_STRING )
                asmerr(2008, token )
                .break
            .elseif ( [rbx].token != T_ID )
                asmerr( 7006, [rbx].string_ptr )
            .endif

            mov [rsi].deflt,NULL
            mov [rsi].required,FALSE

            ;; first get the parm. name
            tstrlen( token )
            imul ecx,mindex,mname_list
            mov mnames[rcx].len,ax
            mov mnames[rcx].name,token
            inc mindex
            mov mnames[rcx+mname_list].name,NULL ;; init next entry
            add rbx,asm_tok

            ;; now see if it has a default value or is required
            .if [rbx].token == T_COLON
                add rbx,asm_tok
                .if [rbx].token == T_DIRECTIVE && [rbx].dirtype == DRT_EQUALSGN
                    add rbx,asm_tok
                    ;; allowed syntax is parm:=<literal>
                    .if [rbx].token != T_STRING || [rbx].string_delim != '<'
                        asmerr( 3016 )
                        .break ;; return( ERROR );
                    .endif
                    mov eax,[rbx].stringlen
                    inc eax
                    mov [rsi].deflt,LclAlloc(eax)
                    xchg rax,rdi
                    mov ecx,[rbx].stringlen
                    inc ecx
                    mov rdx,rsi
                    mov rsi,[rbx].string_ptr
                    rep movsb
                    mov rsi,rdx
                    mov rdi,rax
                    add rbx,asm_tok
                .elseifd !tstricmp( [rbx].string_ptr, "REQ" )
                    ;; required parameter
                    mov [rsi].required,TRUE
                    add rbx,asm_tok
                .elseif( [rbx].token == T_RES_ID && [rbx].tokval == T_VARARG )
                    ;; more parameters can follow
                    mov rdx,mac
                    or [rdx].asym.mac_flag,M_ISVARARG
                    .if ( [rbx+asm_tok].token != T_FINAL )
                        asmerr( 2129 )
                        .break
                    .endif
                    add rbx,asm_tok
                .elseif( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_LABEL && \
                          ModuleInfo.strict_masm_compat == FALSE ) ;; parm:LABEL?
                    ;; LABEL attribute for first param only!
                    .if rsi != [rdi].parmlist
                        asmerr( 2143 )
                        .break
                    .endif
                    mov rdx,mac
                    or [rdx].asym.mac_flag,M_LABEL
                    add rbx,asm_tok
                .elseifd !tstricmp( [rbx].string_ptr, "VARARGML" )
                    ;; more parameters can follow, multi lines possible
                    mov rdx,mac
                    or [rdx].asym.mac_flag,M_ISVARARG or M_MULTILINE
                    .if [rbx+asm_tok].token != T_FINAL
                        asmerr( 2129 )
                        .break
                    .endif
                    add rbx,asm_tok
                .else
                    asmerr(2008, [rbx].string_ptr )
                    .break
                .endif
            .endif
            .if ( rbx < final && [rbx].token != T_COMMA )
                asmerr(2008, [rbx].tokpos )
                .break ;; return( ERROR );
            .endif
            ;; go past comma
            add rbx,asm_tok

        .endf ;; end for()
    .endif

    mov locals_done,FALSE
    lea rax,[rdi].lines
    mov nextline,rax

    ;
    ; now read in the lines of the macro, and store them if store_data is TRUE
    ;
    .for ( :: )

        mov src,GetLine( ls.start )
        .if rax == NULL
            asmerr(1008) ;; unmatched macro nesting
        .endif

        ;; add the macro line to the listing file
        .if ModuleInfo.list
            and ModuleInfo.line_flags,not LOF_LISTED
            LstWrite( LSTTYPE_MACROLINE, 0, ls.start )
        .endif
        mov ls.input,src
        mov ls.index,0

    continue_scan:

        mov rdx,ls.input
        .while ( islspace( [rdx] ) )
            inc rdx
        .endw
        mov ls.input,rdx

        ;; skip empty lines!
        .if al == 0 || al == ';'
if STORE_EMPTY_LINES
            .if store_data
                LclAlloc( srcline )
                mov [rax].srcline.next,NULL
                mov [rax].srcline.ph_count,0
                mov [rax].srcline.line,0
                mov rdx,nextline
                mov [rdx],rax
                mov nextline,rax
            .endif
endif
            .continue
        .endif

        ;; get first token
        mov ls.output,StringBufferEnd
        mov ls.flags,TOK_DEFAULT
        mov ls.flags2,0
        mov tok[0].token,T_FINAL
        .return .ifd GetToken( &tok[0], &ls ) == ERROR

        ;; v2.05: GetTextLine() doesn't concat lines anymore.
        ;; So if a backslash is found in the current source line,
        ;; tokenize it to get possible concatenated lines.
        .if strchr( ls.input, '\' )
            mov rdi,ls.input
            mov rdx,rdi
            .while ( byte ptr [rdx] && byte ptr [rdx] != ';' )
                mov ls.flags3,0
                GetToken( &tok[asm_tok], &ls )
                .if ( ( ls.flags3 & TF3_ISCONCAT ) && ModuleInfo.list )
                    and ModuleInfo.line_flags,not LOF_LISTED
                    LstWrite( LSTTYPE_MACROLINE, 0, ls.input )
                .endif
                mov rdx,ls.input
                .while ( islspace( [rdx] ) )
                    inc rdx
                .endw
                mov ls.input,rdx
            .endw
            mov ls.input,rdi
        .endif

        cmp tok[0].token,T_FINAL ;; did GetToken() return EMPTY?
        je continue_scan

        ;; handle LOCAL directive(s)
        .if locals_done == FALSE && tok[0].token == T_DIRECTIVE && tok[0].tokval == T_LOCAL
            .continue .if !store_data
            .for ( :: )
                mov rdx,ls.input
                .while ( islspace( [rdx] ) )
                    inc rdx
                .endw
                mov ls.input,rdx
                .break .if al == 0 || al == ';' ;; 0 locals are ok

                mov ls.output,StringBufferEnd
                GetToken( &tok[0], &ls )
                mov rdx,StringBufferEnd
                .if ( !is_valid_id_first_char( [rdx] ) )
                    asmerr( 2008, rdx )
                    .break
                .elseif tok[0].token != T_ID
                    asmerr( 7006, rdx )
                .endif

                .if mindex == ( MAX_PLACEHOLDERS - 1 )
                    asmerr( 1005 )
                    .break
                .endif
                mov edi,tstrlen(StringBufferEnd)
                alloca(eax)
                imul ecx,mindex,mname_list
                mov mnames[rcx].len,di
                mov mnames[rcx].name,rax
                mov mnames[rcx+mname_list].name,NULL ;; mark end of placeholder array
                inc mindex
                mov rcx,rdi
                mov rdi,rax
                mov rdx,rsi
                mov rsi,StringBufferEnd
                rep movsb
                mov rsi,rdx
                mov rdi,info
                inc [rdi].localcnt
                mov rdx,ls.input
                .while ( islspace( [rdx] ) )
                    inc rdx
                .endw
                mov ls.input,rdx
                .if al == ','
                    inc ls.input
                .elseif ( is_valid_id_first_char( eax ) )
                    asmerr( 2008, ls.input )
                    .break
                .endif
            .endf
            .continue
        .endif
        mov locals_done,TRUE

        ;; handle macro labels, EXITM, ENDM and macro loop directives.
        ;; this must be done always, even if store_data is false,
        ;; to find the matching ENDM that terminates the macro.

        mov rdx,ls.input
        .if ( tok[0].token == T_COLON ) ;; macro label?

            ;; skip leading spaces for macro labels! In RunMacro(),
            ;; the label search routine expects no spaces before ':'.

            dec rdx
            mov src,rdx
        .elseif tok[0].token == T_DIRECTIVE
            .if tok[0].tokval == T_EXITM || tok[0].tokval == T_RETM
                .if nesting_depth == 0
                    .while islspace( [rdx] )
                        inc rdx
                    .endw
                    .if ( al && al != ';' )
                        mov rdx,mac
                        or [rdx].asym.mac_flag,M_ISFUNC
                    .endif
                .endif
            .elseif( tok[0].tokval == T_ENDM )
                .if nesting_depth
                    dec nesting_depth
                .else
                    .break ;; exit the for() loop
                .endif
            .elseif tok[0].dirtype == DRT_LOOPDIR
                inc nesting_depth ;; FOR[C], IRP[C], REP[EA]T, WHILE
            .endif
        .elseif tok[0].token != T_INSTRUCTION || byte ptr [rdx] == '&'
            ;
            ; Skip any token != directive or instruction (and no '&' attached)
            ; might be text macro ids, macro function calls,
            ; code labels, ...
            ;
            .for ( :: )
                mov tok[0].token,T_FINAL
                mov ls.input,ltokstart(ls.input)
                .break .if cl == 0 || cl == ';'
                movzx edi,byte ptr [rax-1]
                .break .ifd GetToken( &tok[0], &ls ) == ERROR
                mov rdx,ls.input
                .break .if ( ( tok[0].token == T_INSTRUCTION || tok[0].token == T_DIRECTIVE ) &&
                    edi != '&' && byte ptr [rdx] != '&' )
            .endf
            .if ( tok[0].token == T_DIRECTIVE )
                ;
                ; MACRO or loop directive?
                ;
                .if ( tok[0].tokval == T_MACRO || tok[0].dirtype == DRT_LOOPDIR )
                    inc nesting_depth
                .endif
            .endif
        .endif
        ;
        ; store the line, but first check for placeholders!
        ; this is to be improved. store_placeholders() is too
        ; primitive. It's necessary to use the tokenizer.
        ;
        .if ( store_data )

            xor eax,eax
            .if ( mindex )
                store_placeholders( src, &mnames )
            .endif
            mov r12,rax
            mov edi,tstrlen(src)
            add eax,srcline
            LclAlloc(eax)
            mov rdx,nextline
            mov [rdx],rax
            mov [rax].srcline.next,NULL
            mov ecx,r12d
            mov [rax].srcline.ph_count,cl
            inc edi
            mov nextline,rax
            tmemcpy( &[rax].srcline.line, src, edi )
        .endif
    .endf
    mov rdx,mac
    or  [rdx].asym.flags,S_ISDEFINED
    and [rdx].asym.mac_flag,not M_PURGED
    mov eax,NOT_ERROR
    ret

StoreMacro endp

;; create a macro symbol

    assume rcx:ptr macro_info

CreateMacro proc uses rbx name:string_t

    .if ( SymCreate(name) )

        mov [rax].asym.state,SYM_MACRO
        and [rax].asym.mac_flag,not ( M_ISVARARG or M_ISFUNC )
        mov rbx,rax
        mov rcx,LclAlloc(sizeof(macro_info))
        mov rax,rbx
        mov [rax].dsym.macroinfo,rcx
        xor edx,edx
        mov [rcx].parmcnt,dx
        mov [rcx].localcnt,dx
        mov [rcx].parmlist,rdx
        mov [rcx].lines,rdx
        mov [rcx].srcfile,edx
    .endif
    ret

CreateMacro endp

;; clear macro data

ReleaseMacroData proc mac:dsym_t

    mov rax,mac
    and [rax].asym.mac_flag,not M_ISVARARG
    mov rcx,[rax].dsym.macroinfo
    xor eax,eax
    mov [rcx].parmcnt,ax
    mov [rcx].localcnt,ax
    mov [rcx].parmlist,rax
    mov [rcx].lines,rax
    mov [rcx].srcfile,eax
    ret

ReleaseMacroData endp

;; MACRO directive: define a macro
;; i: directive token ( is to be 1 )

    assume rsi:dsym_t

MacroDir proc uses rsi rdi rbx i:int_t, tokenarray:token_t

  local store_data:int_t

    mov rbx,tokenarray
    mov rdi,[rbx].string_ptr
    mov rsi,SymSearch(rdi)

    .if eax == NULL

        mov rsi,CreateMacro(rdi)

    .elseif [rsi].state != SYM_MACRO

        .if [rsi].state != SYM_UNDEFINED

            .if [rsi].state == SYM_EXTERNAL && !ModuleInfo.strict_masm_compat

                mov rbx,rdx
                .if SymAlloc(rdi)

                    mov [rsi].target_type,rax
                    or  [rsi].flag2,S_ISINLINE
                    mov rsi,rax
                    mov [rsi].altname,rbx
                    and [rsi].mac_flag,not ( M_ISVARARG or M_ISFUNC )
                    jmp alloc_macroinfo
                .else
                    .return asmerr( 2005, rdi )
                .endif
                mov rbx,tokenarray
            .else
                .return asmerr( 2005, rdi )
            .endif

        .else

            ;; the macro was used before it's defined. That's
            ;; a severe error. Nevertheless define the macro now,
            ;; error msg 'invalid symbol type in expression' will
            ;; be displayed in second pass when the (unexpanded)
            ;; macro name is found by the expression evaluator.

            sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rsi )

            alloc_macroinfo:

            mov [rsi].state,SYM_MACRO
            mov [rsi].macroinfo,LclAlloc(macro_info)
            mov rdi,rax
            mov ecx,macro_info
            xor eax,eax
            rep stosb
        .endif
    .endif
    mov rdi,[rsi].macroinfo
    mov [rdi].srcfile,get_curr_srcfile()

    .if ( ( Parse_Pass == PASS_1 ) || ( [rsi].flags & S_VARIABLE ) )
        ;; is the macro redefined?
        .if [rdi].lines != NULL
            ReleaseMacroData(rsi)
            ;; v2.07: isfunc isn't reset anymore in ReleaseMacroData()
            and [rsi].mac_flag,not M_ISFUNC
            or  byte ptr [rsi].flags,S_VARIABLE
        .endif
        mov store_data,TRUE
    .else
        mov store_data,FALSE
    .endif

    .if ModuleInfo.list
        LstWriteSrcLine()
    .endif
    inc i
    StoreMacro( rsi, i, tokenarray, store_data )
    ret

MacroDir endp

    assume rsi:nothing


lq_line struct  ;; item of a line queue
next    ptr_t ?
line    char_t 1 dup(?)
lq_line ends

LineQueue equ <ModuleInfo.line_queue>

PreprocessLine proto __ccall :ptr asm_tok

GeLineQueue proc private uses rsi rdi rbx buffer:string_t

    mov rax,LineQueue.head
    .return .if !rax

    mov rsi,rax
    mov LineQueue.head,[rsi].lq_line.next
    mov rdi,strcpy(buffer, &[rsi].lq_line.line)
    MemFree(rsi)

    xor ebx,ebx ; (
    .while 1    ; test line concatenation, get last token

        mov     ecx,-1
        xor     eax,eax
        repne   scasb
        neg     ecx
        dec     rdi
        dec     ecx
        .break .ifz
        .repeat
            dec rdi
            .break .if byte ptr [rdi] > ' '
        .untilcxz

        mov [rdi+1],al
        mov al,[rdi]
        .switch al
        .case '('
            inc bl
        .case ','
        .case ':'
        .case '&'
        .case '|'
            mov al,' '
            mov [rdi+1],ax
            add rdi,2
            mov rsi,LineQueue.head
            .break .if !rsi
            mov LineQueue.head,[rsi].lq_line.next
            strcpy(rdi, &[rsi].lq_line.line)
            MemFree(rsi)
            .continue
        .case '{'
            inc bh
            .gotosw(',')
        .case ')'
            .break .if bl <= 1
            dec bl
            .endc
        .case '}'
            .break .if bh <= 1
            dec bh
        .default
            .gotosw(',') .if ebx
            .break
        .endsw
    .endw
    mov rax,buffer
    ret

GeLineQueue endp


MacroLineQueue proc

  local oldstat:input_status
  local oldline:GETLINE
  local tokenarray:token_t

    mov tokenarray,PushInputStatus( &oldstat )
    inc ModuleInfo.GeneratedCode
    mov oldline,GetLine
    mov GetLine,&GeLineQueue
    .if GetLine( CurrSource )
        PreprocessLine( tokenarray )
    .endif
    mov GetLine,oldline
    dec ModuleInfo.GeneratedCode
    PopInputStatus( &oldstat )
    ret

MacroLineQueue endp

;; PURGE directive.
;; syntax: PURGE macro [, macro, ... ]
;; Masm deletes the macro content, but the symbol name isn't released
;; and cannot be used for something else.
;; Text macros cannot be purged, because the PURGE arguments are expanded.

    assume rsi:asym_t

PurgeDirective proc uses rsi rdi rbx i:int_t, tokenarray:token_t

    inc i ;; skip directive

    .repeat

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if [rbx].token != T_ID
            .return asmerr( 2008, [rbx].string_ptr )
        .endif
        mov rsi,SymSearch( [rbx].string_ptr )
        .if rax == NULL
            .return asmerr( 2006, [rbx].string_ptr )
        .endif
        .if [rsi].state != SYM_MACRO
            .return asmerr( 2065, "macro name" )
        .endif
if TRUEPURGE
        [rsi].defined = FALSE;
else
        ReleaseMacroData(rsi)
        or byte ptr [rsi].flags,S_VARIABLE
        or [rsi].mac_flag,M_PURGED
endif
        inc i
        add rbx,asm_tok
        .if i < Token_Count
            .if [rbx].token != T_COMMA || [rbx+asm_tok].token == T_FINAL
                .return asmerr(2008, [rbx].tokpos )
            .endif
            inc i
        .endif
    .until i >= Token_Count
    mov eax,NOT_ERROR
    ret

PurgeDirective endp

;; internal @Environ macro function */
;; v2.08: ensured no buffer overflow if environment variable is larger than MAX_LINE_LEN */

EnvironFunc proc private uses rsi rdi rbx mi:ptr macro_instance, buffer:string_t, tokenarray:token_t

    mov rax,mi
    mov rax,[rax].macro_instance.parm_array
    mov rax,[rax]
    mov rsi,getenv(rax)
    mov rdi,buffer
    mov byte ptr [rdi],0
    .if rsi
        mov ecx,tstrlen(rsi)
        .if eax >= MAX_LINE_LEN
            mov ecx,MAX_LINE_LEN-1
        .endif
        rep movsb
        mov byte ptr [rdi],0
    .endif
    mov eax,NOT_ERROR
    ret

EnvironFunc endp

;; macro initialization
;; this proc is called once per pass

MacroInit proc uses r12 pass:int_t

    mov MacroLevel,0
    mov MacroLocals,0 ; added 2.31.45

    .if pass == PASS_1

        StringInit()

        ;; add @Environ() macro func

        CreateMacro( "@Environ" )
        or  byte ptr [rax].asym.flags,S_ISDEFINED or S_PREDEFINED
        or  [rax].asym.mac_flag,M_ISFUNC
        lea rcx,EnvironFunc
        mov [rax].asym.func_ptr,rcx
        mov rax,[rax].dsym.macroinfo
        mov [rax].macro_info.parmcnt,1
        mov r12,rax
        LclAlloc(sizeof(mparm_list))
        mov [r12].macro_info.parmlist,rax
        mov [rax].mparm_list.deflt,NULL
        mov [rax].mparm_list.required,TRUE
    .endif
    mov eax,NOT_ERROR
    ret

MacroInit endp

    end
