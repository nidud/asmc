
;; macro handling.

;; functions:
;; - CreateMacro             create a macro item
;; - ReleaseMacroData used to redefine/purge a macro
;; - StoreMacro      store a macro's parameter/local/line list
;; - MacroDir        handle MACRO directive
;; - PurgeDirective   handle PURGE directive
;; - MacroInit       global macro initialization, set predefined macros

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

    .code

;; Replace placeholders in a stored macro source line with values of actual
;; parameters and locals. A placeholder consists of escape char 0x0a,
;; followed by a one-byte index field.

fill_placeholders proc uses esi edi ebx dst:string_t, src:string_t, argc:uint_t,
        localstart:uint_t, argv:array_t

    mov edi,dst

    ;; scan the string, replace the placeholders #nn

    .for( esi = src: byte ptr [esi]: )
        .if ( byte ptr [esi] == PLACEHOLDER_CHAR )
            add esi,2
            ;; we found a placeholder, get the index part!
            movzx ebx,byte ptr [esi-1]
            dec ebx ;; index is one-based!

            ;; if parmno > argc, then it's a macro local

            .if ebx >= argc

                mov eax,'??'
                stosw
                add ebx,localstart
                sub ebx,argc
                .if ebx > 0xFFFF
                    sprintf( edi, "%X", ebx )
                    add edi,ebx
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
                    mov [edi+0],bh
                    mov [edi+1],ah
                    mov [edi+2],bl
                    mov [edi+3],al
                    add edi,4
                .endif
            .else
                mov edx,argv
                mov ebx,[edx+ebx*4]
                .if ebx  ;; actual parameter might be empty (=NULL)
                    mov ecx,strlen(ebx)
                    xchg ebx,esi
                    rep movsb
                    mov esi,ebx
                .endif
            .endif
        .else
            movsb
        .endif
    .endf
    mov byte ptr [edi],0
    ret

fill_placeholders endp

replace_parm proc uses esi edi ebx line:string_t, start:string_t, len:int_t, mnames:ptr mname_list

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

    mov ebx,mnames
    assume ebx:ptr mname_list

    .for ( count = 1: [ebx].name: count++, ebx += mname_list )

        .continue .if [ebx].len != len

        .if !SymCmpFunc( start, [ebx].name, len )

            ;; found a macro parameter/local!

            .if count >= MAX_PLACEHOLDERS
                asmerr(1005)
                .break
            .endif

            ;; handle substitution operator '&'
            mov edi,start
            mov esi,len
            add esi,edi
            .if edi != line && byte ptr [edi-1] == '&'
                dec edi
            .endif
            .if byte ptr [esi] == '&'
                inc esi
            .endif
            mov eax,PLACEHOLDER_CHAR
            stosb

            ;; additional space needed for the placeholder?
            .if edi >= esi
                lea ecx,[esi+strlen(esi)]
                lea edx,[ecx+1]
                .while ( ecx >= esi )
                    mov al,[ecx]
                    mov [edx],al
                    dec ecx
                    dec edx
                .endw
                mov eax,count
                mov [edi],al
            .else
                mov eax,count
                stosb
                ;; v2.10: strcpy should not be used if strings overlap
                memmove( edi, esi, &[strlen(esi)+1] );
            .endif
            .return edi ;; word has been replaced
        .endif
    .endf
    xor eax,eax
    ret

replace_parm endp

store_placeholders proc private uses esi edi ebx line:string_t, mnames:ptr mname_list

    ;; scan a macro source line for parameter and local names.
    ;; - line: the source line
    ;; - mnames: list of macro params + locals
    ;; if a param/local is found, replace the name by a 2-byte placeholder.

    local qlevel:uchar_t

    xor edi,edi ;; number of replacements in this line
    xor ebx,ebx
    mov qlevel,bl

    .for ( esi = line: byte ptr [esi]: )

        movzx eax,byte ptr [esi]
        movzx ecx,byte ptr [esi-1]

        .if ( _ltype[eax+1] & _DIGIT )

            ;; skip numbers (they may contain alphas)
            ;; this is not exactly what masm does. Masm
            ;; stops at the first non-digit.

            .repeat
                inc esi
                mov al,[esi]
            .until !( _ltype[eax+1] & _DIGIT or _LABEL )

        .elseif ( _ltype[eax+1] & _DIGIT or _LABEL || \
                ( al == '.' && ModuleInfo.dotname && \
                ( esi == line || ( cl != ']' && ( !( _ltype[ecx+1] & _DIGIT or _LABEL ) ) ) ) ) )

            mov edx,esi
            .repeat
                inc esi
                mov al,[esi]
            .until !( _ltype[eax+1] & _DIGIT or _LABEL )

            ;; v2.08: both a '&' before AND after the name trigger substitution (and disappear)
            xor eax,eax
            .if ( ( edx > line && byte ptr [edx-1] == '&' ) || byte ptr [esi] == '&' )
                inc eax
            .endif
            .if ( bl == 0 || eax )
                ;; look for this word in the macro parms, and replace it if it is

                mov eax,esi
                sub eax,edx
                .if replace_parm( line, edx, eax, mnames )
                    inc edi
                    mov esi,eax
                .endif
            .endif
        .else
            .switch eax
            .case '!'
                ;; v2.11: skip next char only if it is a "special" one; see expans40.asm
                .if bl == 0
                    movzx eax,byte ptr [esi+1]
                    .if strchr( "<>\"'", eax )
                        inc esi
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
            inc esi
        .endif
    .endf
    mov eax,edi
    ret

store_placeholders endp


;; store a macro's parameter, local and content list.
;; i = start index of macro params in token buffer.

    assume esi:dsym_t
    assume edi:ptr macro_info
    assume ebx:tok_t

StoreMacro proc uses esi edi ebx mac:dsym_t, i:int_t, tokenarray:tok_t, store_data:int_t

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
    local buffer[MAX_LINE_LEN]:char_t
    local final:tok_t

    mov nesting_depth,0
    mov esi,mac
    mov edi,[esi].macroinfo
    mov info,edi
    imul ebx,i,asm_tok
    add ebx,tokenarray
    imul eax,Token_Count,asm_tok
    add eax,tokenarray
    mov final,eax

    .if store_data

        .if ( ebx < final )
            .for ( eax = ebx, [edi].parmcnt = 1: eax < final: eax += 16 )
                .if [eax].asm_tok.token == T_COMMA
                    inc [edi].parmcnt
                .endif
            .endf
            movzx ecx,[edi].parmcnt
            imul eax,ecx,mparm_list
            mov [edi].parmlist,LclAlloc(eax)
        .else
            mov [edi].parmcnt,0
            mov [edi].parmlist,NULL
        .endif

        assume esi:ptr mparm_list
        .for( esi = [edi].parmlist, mindex = 0: ebx < final : esi += mparm_list )

            mov token,[ebx].string_ptr

            ;; Masm accepts reserved words and instructions as parameter
            ;; names! So just check that the token is a valid id.

            movzx eax,byte ptr [eax]

            .if ( !( ( _ltype[eax+1] & _LABEL ) || ( al == '.' && ModuleInfo.dotname ) ) || \
                 [ebx].token == T_STRING )
                asmerr(2008, token )
                .break
            .elseif ( [ebx].token != T_ID )
                asmerr( 7006, [ebx].string_ptr )
            .endif

            mov [esi].deflt,NULL
            mov [esi].required,FALSE

            ;; first get the parm. name
            strlen( token )
            imul ecx,mindex,mname_list
            mov mnames[ecx].len,ax
            mov mnames[ecx].name,token
            inc mindex
            mov mnames[ecx+mname_list].name,NULL ;; init next entry
            add ebx,16

            ;; now see if it has a default value or is required
            .if [ebx].token == T_COLON
                add ebx,16
                mov edx,mac
                .if [ebx].token == T_DIRECTIVE && [ebx].dirtype == DRT_EQUALSGN
                    add ebx,16
                    ;; allowed syntax is parm:=<literal>
                    .if [ebx].token != T_STRING || [ebx].string_delim != '<'
                        asmerr( 3016 )
                        .break ;; return( ERROR );
                    .endif
                    mov eax,[ebx].stringlen
                    inc eax
                    mov [esi].deflt,LclAlloc(eax)
                    xchg eax,edi
                    mov ecx,[ebx].stringlen
                    inc ecx
                    mov edx,esi
                    mov esi,[ebx].string_ptr
                    rep movsb
                    mov esi,edx
                    mov edi,eax
                    add ebx,16
                .elseif !_stricmp( [ebx].string_ptr, "REQ" )
                    ;; required parameter
                    mov [esi].required,TRUE
                    add ebx,16
                .elseif( [ebx].token == T_RES_ID && [ebx].tokval == T_VARARG )
                    ;; more parameters can follow
                    or [edx].asym.mac_flag,M_ISVARARG
                    .if ( [ebx+16].token != T_FINAL )
                        asmerr( 2129 )
                        .break
                    .endif
                    add ebx,16
                .elseif( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_LABEL && \
                          ModuleInfo.strict_masm_compat == FALSE ) ;; parm:LABEL?
                    ;; LABEL attribute for first param only!
                    .if esi != [edi].parmlist
                        asmerr( 2143 )
                        .break
                    .endif
                    or [edx].asym.mac_flag,M_LABEL
                    add ebx,16
                .elseif !_stricmp( [ebx].string_ptr, "VARARGML" )
                    ;; more parameters can follow, multi lines possible
                    or [edx].asym.mac_flag,M_ISVARARG
                    or [edx].asym.mac_flag,M_MULTILINE
                    .if [ebx+16].token != T_FINAL
                        asmerr( 2129 )
                        .break
                    .endif
                    add ebx,16
                .else
                    asmerr(2008, [ebx].string_ptr )
                    .break
                .endif
            .endif
            .if( ebx < final && [ebx].token != T_COMMA )
                asmerr(2008, [ebx].tokpos )
                .break ;; return( ERROR );
            .endif
            ;; go past comma
            add ebx,16

        .endf ;; end for()
    .endif

    mov locals_done,FALSE
    lea eax,[edi]._data
    mov nextline,eax

    ;; now read in the lines of the macro, and store them if store_data is TRUE
    .for( :: )

        mov src,GetTextLine( &buffer )
        .if eax == NULL
            asmerr(1008) ;; unmatched macro nesting
        .endif

        ;; add the macro line to the listing file
        .if ModuleInfo.list
            and ModuleInfo.line_flags,not LOF_LISTED
            LstWrite( LSTTYPE_MACROLINE, 0, &buffer )
        .endif
        mov ls.input,src
        mov ls.start,eax
        mov ls.index,0

    continue_scan:

        mov edx,ls.input
        movzx eax,byte ptr [edx]
        .while _ltype[eax+1] & _SPACE
            inc edx
            mov al,[edx]
        .endw
        mov ls.input,edx

        ;; skip empty lines!
        .if al == 0 || al == ';'
if STORE_EMPTY_LINES
            .if store_data
                LclAlloc( srcline )
                mov [eax].srcline.next,NULL
                mov [eax].srcline.ph_count,0
                mov [eax].srcline.line,0
                mov edx,nextline
                mov [edx],eax
                mov nextline,eax
            .endif
endif
            .continue
        .endif

        ;; get first token
        mov ls.output,StringBufferEnd
        mov ls.flags,TOK_DEFAULT
        mov ls.flags2,0
        mov tok[0].token,T_FINAL
        .return .if GetToken( &tok[0], &ls ) == ERROR

        ;; v2.05: GetTextLine() doesn't concat lines anymore.
        ;; So if a backslash is found in the current source line,
        ;; tokenize it to get possible concatenated lines.
        .if strchr( ls.input, '\' )
            mov edi,ls.input
            mov edx,edi
            .while ( byte ptr [edx] && byte ptr [edx] != ';' )
                mov ls.flags3,0
                GetToken( &tok[asm_tok], &ls )
                .if ( ( ls.flags3 & TF3_ISCONCAT ) && ModuleInfo.list )
                    and ModuleInfo.line_flags,not LOF_LISTED
                    LstWrite( LSTTYPE_MACROLINE, 0, ls.input )
                .endif
                mov edx,ls.input
                movzx eax,byte ptr [edx]
                .while _ltype[eax+1] & _SPACE
                    inc edx
                    mov al,[edx]
                .endw
                mov ls.input,edx
            .endw
            mov ls.input,edi
        .endif

        cmp tok[0].token,T_FINAL ;; did GetToken() return EMPTY?
        je continue_scan

        ;; handle LOCAL directive(s)
        .if locals_done == FALSE && tok[0].token == T_DIRECTIVE && tok[0].tokval == T_LOCAL
            .continue .if !store_data
            .for ( :: )
                mov edx,ls.input
                movzx eax,byte ptr [edx]
                .while _ltype[eax+1] & _SPACE
                    inc edx
                    mov al,[edx]
                .endw
                mov ls.input,edx
                .break .if al == 0 || al == ';' ;; 0 locals are ok

                mov ls.output,StringBufferEnd
                GetToken( &tok[0], &ls )
                mov edx,StringBufferEnd
                movzx eax,byte ptr [edx]
                .if ( !( ( _ltype[eax+1] & _LABEL ) || ( al == '.' && ModuleInfo.dotname ) ) )
                    asmerr( 2008, edx )
                    .break
                .elseif tok[0].token != T_ID
                    asmerr( 7006, edx )
                .endif

                .if mindex == ( MAX_PLACEHOLDERS - 1 )
                    asmerr( 1005 )
                    .break
                .endif
                mov edi,strlen(StringBufferEnd)
                alloca(eax)
                imul ecx,mindex,mname_list
                mov mnames[ecx].len,di
                mov mnames[ecx].name,eax
                mov mnames[ecx+mname_list].name,NULL ;; mark end of placeholder array
                inc mindex
                mov ecx,edi
                mov edi,eax
                mov edx,esi
                mov esi,StringBufferEnd
                rep movsb
                mov esi,edx
                mov edi,info
                inc [edi].localcnt
                mov edx,ls.input
                movzx eax,byte ptr [edx]
                .while _ltype[eax+1] & _SPACE
                    inc edx
                    mov al,[edx]
                .endw
                mov ls.input,edx
                .if al == ','
                    inc ls.input
                .elseif ( ( _ltype[eax+1] & _LABEL ) || ( al == '.' && ModuleInfo.dotname ) )
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

        mov edx,ls.input
        .if ( tok[0].token == T_COLON ) ;; macro label?

            ;; skip leading spaces for macro labels! In RunMacro(),
            ;; the label search routine expects no spaces before ':'.

            dec edx
            mov src,edx
        .elseif tok[0].token == T_DIRECTIVE
            .if tok[0].tokval == T_EXITM || tok[0].tokval == T_RETM
                .if nesting_depth == 0
                    movzx eax,byte ptr [edx]
                    .while _ltype[eax+1] & _SPACE
                        inc edx
                        mov al,[edx]
                    .endw
                    .if al && al != ';'
                        mov edx,mac
                        or [edx].asym.mac_flag,M_ISFUNC
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
        .elseif tok[0].token != T_INSTRUCTION || byte ptr [edx] == '&'

            ;; Skip any token != directive or instruction (and no '&' attached)
            ;; might be text macro ids, macro function calls,
            ;; code labels, ...

            .for (::)
                mov tok[0].token,T_FINAL
                mov edx,ls.input
                movzx eax,byte ptr [edx]
                .while _ltype[eax+1] & _SPACE
                    inc edx
                    mov al,[edx]
                .endw
                mov ls.input,edx
                .break .if al == 0 || al == ';'
                movzx edi,byte ptr [edx-1]
                .break .if GetToken( &tok[0], &ls ) == ERROR
                mov edx,ls.input
                .break .if ( ( tok[0].token == T_INSTRUCTION || tok[0].token == T_DIRECTIVE ) && \
                    edi != '&' && byte ptr [edx] != '&' )
            .endf
            .if tok[0].token == T_DIRECTIVE
                ;; MACRO or loop directive?
                .if tok[0].tokval == T_MACRO || tok[0].dirtype == DRT_LOOPDIR
                    inc nesting_depth
                .endif
            .endif
        .endif

        ;; store the line, but first check for placeholders!
        ;; this is to be improved. store_placeholders() is too
        ;; primitive. It's necessary to use the tokenizer.

        .if store_data

            xor eax,eax
            .if mindex
                store_placeholders( src, &mnames )
            .endif
            push eax
            mov edi,strlen(src)
            add eax,srcline
            LclAlloc(eax)
            mov edx,nextline
            mov [edx],eax
            mov [eax].srcline.next,NULL
            pop ecx
            mov [eax].srcline.ph_count,cl
            inc edi
            mov nextline,eax
            memcpy( &[eax].srcline.line, src, edi )
        .endif
    .endf ;; end for
    mov edx,mac
    or  [edx].asym.flag,S_ISDEFINED
    and [edx].asym.mac_flag,not M_PURGED
    mov eax,NOT_ERROR
    ret

StoreMacro endp

;; create a macro symbol

    assume ecx:ptr macro_info

CreateMacro proc name:string_t

    .if SymCreate(name)
        mov [eax].asym.state,SYM_MACRO
        and [eax].asym.mac_flag,not ( M_ISVARARG or M_ISFUNC )
        push eax
        mov ecx,LclAlloc(sizeof(macro_info))
        pop eax
        mov [eax].esym.macroinfo,ecx
        xor edx,edx
        mov [ecx].parmcnt,dx
        mov [ecx].localcnt,dx
        mov [ecx].parmlist,edx
        mov [ecx]._data,edx
        mov [ecx].srcfile,edx
    .endif
    ret

CreateMacro endp

;; clear macro data

ReleaseMacroData proc mac:dsym_t

    mov eax,mac
    and [eax].asym.mac_flag,not M_ISVARARG
    mov ecx,[eax].esym.macroinfo
    xor eax,eax
    mov [ecx].parmcnt,ax
    mov [ecx].localcnt,ax
    mov [ecx].parmlist,eax
    mov [ecx]._data,eax
    mov [ecx].srcfile,eax
    ret

ReleaseMacroData endp

;; MACRO directive: define a macro
;; i: directive token ( is to be 1 )

    assume esi:dsym_t

MacroDir proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local store_data:int_t

    mov ebx,tokenarray
    mov edi,[ebx].string_ptr
    mov esi,SymSearch(edi)

    .if eax == NULL

        mov esi,CreateMacro(edi)

    .elseif [esi].sym.state != SYM_MACRO

        .if [esi].sym.state != SYM_UNDEFINED

            .if [esi].sym.state == SYM_EXTERNAL && !ModuleInfo.strict_masm_compat

                mov ebx,edx
                .if SymAlloc(edi)

                    mov [esi].sym.target_type,eax
                    mov esi,eax
                    mov [esi].sym.altname,ebx
                    mov [esi].sym.state,SYM_MACRO
                    and [esi].sym.mac_flag,not ( M_ISVARARG or M_ISFUNC )
                    mov ecx,LclAlloc(macro_info)
                    mov [esi].macroinfo,ecx
                    xor edx,edx
                    mov [ecx].parmcnt,dx
                    mov [ecx].localcnt,dx
                    mov [ecx].parmlist,edx
                    mov [ecx]._data,edx
                    mov [ecx].srcfile,edx

                .else
                    .return asmerr( 2005, edi )
                .endif
                mov ebx,tokenarray
            .else
                .return asmerr( 2005, edi )
            .endif

        .else

            ;; the macro was used before it's defined. That's
            ;; a severe error. Nevertheless define the macro now,
            ;; error msg 'invalid symbol type in expression' will
            ;; be displayed in second pass when the (unexpanded)
            ;; macro name is found by the expression evaluator.

            sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], esi )
            mov [esi].sym.state,SYM_MACRO
            mov [esi].macroinfo,LclAlloc(macro_info)
            mov edi,eax
            mov ecx,macro_info
            xor eax,eax
            rep stosb
        .endif
    .endif
    mov edi,[esi].macroinfo
    mov [edi].srcfile,get_curr_srcfile()

    .if ( ( Parse_Pass == PASS_1 ) || ( [esi].sym.flag & S_VARIABLE ) )
        ;; is the macro redefined?
        .if [edi]._data != NULL
            ReleaseMacroData(esi)
            ;; v2.07: isfunc isn't reset anymore in ReleaseMacroData()
            and [esi].sym.mac_flag,not M_ISFUNC
            or  byte ptr [esi].sym.flag,S_VARIABLE
        .endif
        mov store_data,TRUE
    .else
        mov store_data,FALSE
    .endif

    .if ModuleInfo.list
        LstWriteSrcLine()
    .endif
    inc i
    StoreMacro( esi, i, tokenarray, store_data )
    ret

MacroDir endp


;; PURGE directive.
;; syntax: PURGE macro [, macro, ... ]
;; Masm deletes the macro content, but the symbol name isn't released
;; and cannot be used for something else.
;; Text macros cannot be purged, because the PURGE arguments are expanded.

    assume esi:asym_t

PurgeDirective proc uses esi edi ebx i:int_t, tokenarray:tok_t

    inc i ;; skip directive

    .repeat

        imul ebx,i,asm_tok
        add ebx,tokenarray

        .if [ebx].token != T_ID
            .return asmerr(2008, [ebx].string_ptr )
        .endif
        mov esi,SymSearch( [ebx].string_ptr )
        .if eax == NULL
            .return asmerr( 2006, [ebx].string_ptr )
        .endif
        .if [esi].state != SYM_MACRO
            .return asmerr( 2065, "macro name" )
        .endif
if TRUEPURGE
        [esi].defined = FALSE;
else
        ReleaseMacroData(esi)
        or byte ptr [esi].flag,S_VARIABLE
        or [esi].mac_flag,M_PURGED
endif
        inc i
        add ebx,16
        .if i < Token_Count
            .if [ebx].token != T_COMMA || [ebx+16].token == T_FINAL
                .return asmerr(2008, [ebx].tokpos )
            .endif
            inc i
        .endif
    .until i >= Token_Count
    mov eax,NOT_ERROR
    ret

PurgeDirective endp

;; internal @Environ macro function */
;; v2.08: ensured no buffer overflow if environment variable is larger than MAX_LINE_LEN */

EnvironFunc proc private uses esi edi ebx mi:ptr macro_instance, buffer:string_t, tokenarray:tok_t

    mov eax,mi
    mov eax,[eax].macro_instance.parm_array
    mov eax,[eax]
    mov esi,getenv(eax)
    mov edi,buffer
    mov byte ptr [edi],0
    .if esi
        mov ecx,strlen(esi)
        .if eax >= MAX_LINE_LEN
            mov ecx,MAX_LINE_LEN - 1
        .endif
        rep movsb
        mov byte ptr [edi],0
    .endif
    mov eax,NOT_ERROR
    ret

EnvironFunc endp

;; macro initialization
;; this proc is called once per pass

MacroInit proc pass:int_t

    mov MacroLevel,0

    .if pass == PASS_1

        StringInit()

        ;; add @Environ() macro func

        CreateMacro( "@Environ" )
        or  byte ptr [eax].asym.flag,S_ISDEFINED or S_PREDEFINED
        or  [eax].asym.mac_flag,M_ISFUNC
        mov [eax].asym.func_ptr,EnvironFunc
        mov eax,[eax].esym.macroinfo
        mov [eax].macro_info.parmcnt,1
        push eax
        LclAlloc(sizeof(mparm_list))
        pop edx
        mov [edx].macro_info.parmlist,eax
        mov [eax].mparm_list.deflt,NULL
        mov [eax].mparm_list.required,TRUE
    .endif
    mov eax,NOT_ERROR
    ret

MacroInit endp

    end
