; TOKENIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

include asmc.inc
include token.inc
include parser.inc
include reswords.inc
include operands.inc
include symbols.inc
include input.inc
include tokenize.inc
include condasm.inc
include assume.inc
include fastpass.inc

define B <byte ptr>

externdef CurrEnum:asym_t

.data

;tokarray  token_t 0
;
; strings for token 0x28 - 0x2F
;
stokstr1    dw '(',')','*','+',',','-','.','/'
;
; strings for token 0x5B - 0x5D
;
stokstr2    dw '[',0,']'

__equ       db '=',0
__dcolon    db ':'
__colon     db ':',0
__amp       db '&',0
__percent   db '%',0
__quest     db '?',0
__null      db 0

    .code

    option  proc:private

    .pragma warning( disable: 6004 )

    assume  rcx:token_t

IsMultiLine proc fastcall tokenarray:token_t
    ;
    ; test line concatenation if last token is a comma.
    ; dont concat EQU, macro invocations or
    ; - ECHO
    ; - FORC/IRPC (v2.0)
    ; - INCLUDE (v2.8)
    ; lines!
    ; v2.05: don't concat if line's an instruction.
    ;
    .if ( [rcx+asm_tok].token == T_DIRECTIVE && [rcx+asm_tok].tokval == T_EQU )

        .return( 0 )
    .endif

    .if ( [rcx+asm_tok].token == T_COLON )

        add rcx,asm_tok * 2
    .endif

    movzx eax,[rcx].token
    .switch eax

      .case T_DIRECTIVE

        mov ecx,[rcx].tokval
        .switch ecx
        .case T_ECHO
        .case T_INCLUDE
        .case T_FORC
        .case T_IRPC
            .return( 0 )
        .endsw
        .endc

    .case T_INSTRUCTION
        .return( 0 )

      .case T_ID
        .if ( CurrEnum )
            .return( 0 )
        .endif

        ; don't concat macros

        .if SymFind( [rcx].string_ptr )

            .if ( [rax].asym.state == SYM_MACRO && !( [rax].asym.mac_flag & M_MULTILINE ) )

                .return( 0 )
            .endif
        .endif
    .endsw
    .return( 1 )

IsMultiLine endp


    assume rcx:nothing
    assume rbx:ptr line_status

ConcatLine proc __ccall uses rsi rdi rbx src:string_t, cnt:int_t, o:string_t, ls:ptr line_status

    ldr rsi,src
    ldr rdi,o
    ldr rbx,ls

    tstrstart( &[rsi+1] )

    .if ( ecx && ecx != ';' )
        .return( EMPTY )
    .endif
    .if ( GetTextLine( rdi ) == NULL )
        .return( EMPTY )
    .endif

    mov rdi,tstrstart( rdi )
    tstrlen( rdi )

    .if ( cnt == 0 )

        mov byte ptr [rsi],' '
        inc rsi
    .endif

    mov rcx,rsi
    sub rcx,[rbx].start
    add ecx,eax

    .if ( ecx >= MaxLineLength  )

        asmerr( 2039 )

        mov rcx,rsi
        sub rcx,[rbx].start
        inc ecx
        mov eax,MaxLineLength
        sub eax,ecx
        mov byte ptr [rdi+rax],0
    .endif

    lea  ecx,[rax+1]
    xchg rsi,rdi
    rep  movsb

    .return( NOT_ERROR )

ConcatLine endp


    assume rbx:ptr asm_tok
    assume rdx:ptr line_status

get_string proc fastcall uses rsi rdi rbx buf:ptr asm_tok, _p:ptr line_status

   .new symbol_c:   char_t
   .new symbol_o:   char_t
   .new delim:      char_t
   .new level:      uint_t
   .new tdst:       string_t
   .new tsrc:       string_t
   .new tcount:     uint_t
   .new maxlen:     uint_t
   .new maxl_1:     uint_t
   .new p:          ptr line_status = rdx

    mov     rbx,rcx
    mov     rsi,[rdx].input
    mov     rdi,[rdx].output
    movzx   eax,B[rsi]
    mov     symbol_o,al
    xor     ecx,ecx

    .switch eax

      .case '"'
      .case 27h

        mov ecx,MaxLineLength
        sub ecx,32
        mov maxlen,ecx
        xor ecx,ecx

        mov [rbx].string_delim,al
        mov ah,al
        movsb

        .repeat

            mov al,[rsi]

            .switch
              .case !al
                ;
                ; missing terminating quote, change to undelimited string
                ;
                mov [rbx].string_delim,al
                inc ecx ; count the first quote
                .break

              .case ( ax == '""' && [rdx].cstring ) ; case \" ?

                .if ( B[rsi-1] == '\' && ( word ptr [rsi-3] == '\\' || B[rsi-2] != '\' ) )

                    ; case \\"
                    ; case \\\"

                    stosb
                    inc rsi
                    inc ecx
                   .endc
                .endif

                lea rax,[rsi+1]
                .while ( B[rax] == ' ' || B[rax] == 9 )
                    add rax,1
                .endw

                .if ( B[rax] == '"' )
                    ;
                    ; "string1" "string2"
                    ;
                    lea rsi,[rax+1]
                    mov eax,'""'
                   .endc
                .endif

                mov eax,'""'

              .case ( al == ah ) ; another quote?

                stosb
                inc rsi
                .break .if ( [rsi] != al ) ; exit loop
                dec rdi

              .default
                mov [rdi],al
                inc rdi
                inc rsi
                inc ecx
               .endc
            .endsw
        .until ecx >= maxlen
        ;
        ; end of string marker is the same
        ;
        .endc

      .case '{'

        test [rdx].flags,TOK_NOCURLBRACES
        jnz default

        mov symbol_c,'}'

      .case '<'

        mov [rbx].string_delim,al
        mov level,ecx

        .if ( al == '<' )
            mov symbol_c,'>'
        .endif
        inc rsi

continue:

        mov eax,MaxLineLength
        sub eax,32
        mov maxlen,eax
        dec eax
        mov maxl_1,eax

        .while ( ecx < maxlen )

            mov ax,[rsi]

            .switch
            .case al == symbol_o ; < or { ?

                inc level
               .endc
            .case al == symbol_c ; > or } ?

                .if ( level )
                    dec level
                .else
                    ;
                    ; store the string delimiter unless it is <>
                    ; v2.08: don't store delimiters for {}-literals
                    ;
                    inc rsi
                   .break ; exit loop
                .endif
                .endc

            .case ( ( al == '"' || al == 27h ) && !( [rdx].flags2 & DF_STRPARM ) )
                ;
                ; a " or ' inside a <>/{} string? Since it's not a must that
                ; [double-]quotes are paired in a literal it must be done
                ; directive-dependant!
                ; see: IFIDN <">,<">
                ;
                mov delim,al
                movsb
                inc ecx
                mov tdst,rdi
                mov tsrc,rsi
                mov tcount,ecx
                mov ax,[rsi]

                .while ( al != delim && al && ecx < maxl_1 )

                    .if ( symbol_o == '<' && al == '!' && ah )

                        inc rsi
                    .endif
                    movsb
                    inc ecx
                    mov ax,[rsi]
                .endw

                .if ( al != delim )

                    mov rsi,tsrc
                    mov rdi,tdst
                    mov ecx,tcount
                   .continue
                .endif
               .endc

            .case ( al == '!' && symbol_o == '<' && ah )
                ;
                ; handle literal-character operator '!'.
                ; it makes the next char to enter the literal uninterpreted.
                ;
                ; v2.09: don't store the '!'
                ;
                inc rsi
               .endc

            .case ( al == '\' )

                mov tcount,ecx
                ConcatLine( rsi, ecx, rdi, rdx )
                mov ecx,tcount
                mov rdx,p
                .if ( eax != EMPTY )

                    or [rdx].flags3,TF3_ISCONCAT
                   .continue
                .endif
                .endc

            .case ( !al || ( al == ';' && symbol_o == '{' ) )

                .if ( [rdx].flags == TOK_DEFAULT && !( [rdx].flags2 & DF_NOCONCAT ) )

                    ; if last nonspace character was a comma
                    ; get next line and continue string scan

                    mov tdst,rdi
                    mov tcount,ecx

                    .if ( ( al == 0 || al == ';' ) && symbol_o == '{' )

                        mov eax,1

                    .else

                        dec rdi
                        .while ( islspace( [rdi] ) )

                            .break .if ( rdi <= [rdx].output )
                            dec rdi
                        .endw
                        cmp al,','
                        mov al,0
                        setz al
                    .endif

                    .if ( eax )

                        mov edi,tstrlen( [rdx].output )
                        mov rdx,p
                        add edi,size_t
                        and edi,-size_t
                        add rdi,[rdx].output

                        ; name proto ... {
                        ; type::name proto ... {

                        mov rcx,[rdx].tokenarray
                        mov eax,[rcx].asm_tok.tokval
                        mov edx,[rcx+asm_tok].asm_tok.tokval
                        mov ecx,[rcx+asm_tok*3].asm_tok.tokval

                        .if ( eax == T_DOT_STATIC || eax == T_DOT_OPERATOR ||
                              eax == T_DOT_INLINE || edx == T_PROTO || ecx == T_PROTO )

                            .while GetTextLine( &[rdi+1] )

                                .continue .if ( B[rdi+1] == 0 )

                                inc rdi
                                mov rdi,tstrstart(rdi)
                                dec rdi
                                mov B[rdi],10
                               .break
                            .endw

                        .elseif GetTextLine(rdi)

                            mov rdi,tstrstart(rdi)
                        .endif

                        .if ( rax )

                            tstrlen(rdi)
                            add eax,tcount
                            .if ( eax >= MaxLineLength )

                                mov rdx,p
                                sub rsi,[rdx].input
                                sub rdi,[rdx].output
                                sub rbx,[rdx].tokenarray
                                mov rax,tdst
                                sub rax,[rdx].output
                                mov tdst,rax

                                .if ( InputExtend( rdx ) == FALSE )
                                    .return asmerr( 2039 )
                                .endif

                                mov rdx,p
                                add rbx,[rdx].tokenarray
                                add rsi,[rdx].input
                                mov rax,[rdx].output
                                add rdi,rax
                                add tdst,rax
                            .endif

                            tstrcpy( rsi, rdi )
                            mov rdx,p
                            mov rdi,tdst
                            mov ecx,tcount
                            jmp continue
                        .endif
                    .endif
                .endif

                mov rdx,p
                mov rsi,[rdx].input
                mov rdi,[rdx].output
                movsb
                mov ecx,1
                jmp default

            .endsw

            movsb
            inc ecx
        .endw
        .endc

      .default
       default:

        mov eax,MaxLineLength
        sub eax,32
        mov maxlen,eax
        dec eax
        mov maxl_1,eax

        mov [rbx].string_delim,0
        ;
        ; this is an undelimited string,
        ; so just copy it until we hit something that looks like the end.
        ; this format is used by the INCLUDE directive, but may also
        ; occur inside the string macros!
        ;
        ; v2.05: also stop if a ')' is found - see literal2.asm regression test
        ;
        .while ( ecx < maxlen )

            movzx eax,B[rsi]

            .break .if !eax
            .break .if islspace( eax )
            .break .if eax == ','

            .if ( eax == '(' )

                inc [rdx].brachets

            .elseif eax == ')'

                dec [rdx].brachets
               .break
            .endif

            .break .if ( eax == '%' )
            .break .if ( eax == ';' && [rdx].flags == TOK_DEFAULT )

            .if ( eax == '\' )

                .if ( [rdx].flags == TOK_DEFAULT || [rdx].flags & TOK_LINE )

                    mov tcount,ecx
                    ConcatLine( rsi, ecx, rdi, rdx )
                    mov ecx,tcount
                    mov rdx,p

                    .if ( eax != EMPTY )

                        or [rdx].flags3,TF3_ISCONCAT

                        .continue .if ecx
                        .return( EMPTY )
                    .endif
                .endif

            .elseif ( eax == '!' && B[rsi+1] && ecx < maxl_1 )
                ;
                ; v2.08: handle '!' operator
                ;
                movsb
            .endif
            movsb
            inc ecx
        .endw
    .endsw

    .if ( ecx == maxlen )

        asmerr( 2041 )
    .else

        xor eax,eax
        mov [rdi],al
        inc rdi
        mov [rbx].token,T_STRING
        mov [rbx].stringlen,ecx
        mov [rdx].input,rsi
        mov [rdx].output,rdi
    .endif
    ret

get_string endp


    assume rdx:nothing
    assume rsi:ptr line_status

get_special_symbol proc __ccall uses rsi rdi rbx buf:token_t, p:ptr line_status

    ldr rbx,buf
    ldr rsi,p
    mov rdi,[rsi].input
    mov eax,[rdi]
    mov [rbx].tokval,0

    .switch al

      .case ':' ; T_COLON binary operator (0x3A)

        inc [rsi].input
        lea rcx,__dcolon

        .if ( ah == ':' )

            inc [rsi].input
            mov [rbx].token,T_DBL_COLON
            mov [rbx].string_ptr,rcx
        .else

            inc rcx
            mov [rbx].token,T_COLON
            mov [rbx].string_ptr,rcx
        .endif
        .endc

      .case '%' ; T_PERCENT (0x25)

        shr eax,8
        or  eax,0x202020

        .if ( eax == 'tuo' ) ; %OUT directive?

            mov rax,[rsi].input

            .if !islabel( [rax+4] )

                mov [rbx].token,T_DIRECTIVE
                mov [rbx].tokval,T_ECHO
                mov [rbx].dirtype,DRT_ECHO
                mov rdi,[rsi].output
                mov rcx,[rsi].input
                add [rsi].input,4
                add [rsi].output,5
                mov eax,[rcx]
                mov [rdi],eax
                xor eax,eax
                mov [rdi+4],al
               .endc
            .endif
        .endif

        inc [rsi].input
        .if ( [rsi].flags == TOK_DEFAULT && [rsi].index == 0 )

            or [rsi].flags3,TF3_EXPANSION
            .return EMPTY
        .endif

        lea rax,__percent
        mov [rbx].token,T_PERCENT
        mov [rbx].string_ptr,rax
       .endc

      .case '('
        ;
        ; 0x28: T_OP_BRACKET operator - needs a matching ')'
        ; v2.11: reset c-expression flag if a macro function call is detected
        ; v2.20: set _cstring to allow escape chars (\") in @CStr( string )
        ; v2.20: removed auto off switch for asmc_syntax in macros
        ; v2.20: added more test code for label() calls
        ; v2.30: added invocation for reg(...) if typedef
        ; v2.32: .pragma comment(linker,"

        inc [rsi].brachets
        xor ecx,ecx

        .if ( [rsi].index == 2 && [rbx-2*asm_tok].tokval == T_DOT_PRAGMA )

            inc [rsi].cstring

        .elseif ( ah == ')' && [rbx-asm_tok].token == T_REG )
            ;
            ; REG() expans as CALL REG
            ;
            or [rbx-asm_tok].flags,T_ISPROC

        .elseif ( [rsi].index && [rbx-asm_tok].token == T_REG )

            mov ecx,[rbx-asm_tok].tokval
            .new tmp:int_t = eax
            .if ( GetValueSp( ecx ) & OP_RGT8 )
                .if ( GetStdAssume( GetRegNo( ecx ) ) )
                    or [rbx-asm_tok].flags,T_ISPROC
                .endif
            .endif
            mov eax,tmp
            xor ecx,ecx

        .elseif ( [rsi].index && ( [rbx-asm_tok].token == T_ID || [rbx-asm_tok].token == T_REG ) )

            xor eax,eax
            .if ( [rsi].index >= 3 && [rbx-2*asm_tok].token == T_DOT )
                ;
                ; p.x(...)
                ; [...][.type].x(...)
                ;
                lea rdi,[rbx-asm_tok*3]
                .if ( [rdi].asm_tok.token == T_CL_SQ_BRACKET )

                    add rdi,2*asm_tok
                    inc eax
                    mov edx,SYM_TYPE
                .else

                    .while ( [rdi-asm_tok].asm_tok.token == T_DOT && [rdi-2*asm_tok].asm_tok.token == T_ID )
                        lea rdi,[rdi-2*asm_tok]
                    .endw

                    SymFind( [rdi].asm_tok.string_ptr )
                    xor edx,edx
                .endif

            .else

                lea rdi,[rbx-asm_tok]
                SymFind( [rbx-asm_tok].string_ptr )
                xor edx,edx
            .endif
            xor ecx,ecx
            .if ( rax )

                .if !edx
                    movzx edx,[rax].asym.state
                .endif
                .switch

                .case ( ModuleInfo.strict_masm_compat == 1 )
                    .endc .if ( edx != SYM_MACRO )
                    .endc .if ( !( [rax].asym.mac_flag & M_ISFUNC ) )
                     and [rsi].flags2,not DF_CEXPR
                    .endc

                .case ( edx == SYM_MACRO )
                    .if ( [rax].asym.mac_flag & M_ISFUNC )

                        and [rsi].flags2,not DF_CEXPR
                        .if ( [rax].asym.flags & S_PREDEFINED )

                            mov rdx,[rax].asym.name
                            mov edx,[rdx]
                            .if ( edx == "tSC@" )

                                inc [rsi].cstring
                               .endc
                            .endif
                        .endif
                        mov ecx,T_ISFUNC
                       .endc
                    .endif

                    .endc .if ( [rax].asym.flags & S_PREDEFINED )
                    .endc .if ( ![rax].asym.string_ptr )
                    .endc .if ( SymFind( [rax].asym.string_ptr ) == NULL )
                     xor ecx,ecx
                    .endc .if !( [rax].asym.flags & S_ISPROC )
                     mov ecx,T_ISPROC
                     inc [rsi].cstring
                    .endc

                .case ( edx == SYM_TYPE ) ;  structure, union, typedef, record
                    ;
                    ; [...].type.x(...)
                    ;
                    mov eax,[rsi].index
                    .if ( eax == 1 || [rdi-asm_tok].asm_tok.token != T_DOT )
                        ;
                        ; type(...)
                        ;
                        .endc .if ( [rdi-asm_tok].asm_tok.token == T_ID )
                        .endc .if ( CurrSeg == NULL )
                         mov rdx,CurrSeg
                         mov rdx,[rdx].dsym.seginfo
                        .endc .if ( [rdx].seg_info.segtype != SEGTYPE_CODE )
                    .else
                        .endc .if ( eax < 5 )
                        .endc .if ( [rdi-asm_tok].asm_tok.token != T_DOT )
                        .endc .if ( [rdi-2*asm_tok].asm_tok.token != T_CL_SQ_BRACKET )
                         sub rdi,3*asm_tok
                         sub eax,3
                         mov edx,1 ; v2.27 - added: [foo(&[..])+rcx].class.method()
                        .repeat
                            .if ( [rdi].asm_tok.token == T_OP_SQ_BRACKET )
                                dec edx
                               .break .ifz
                            .elseif ( [rdi].asm_tok.token == T_CL_SQ_BRACKET )
                                inc edx
                            .endif
                            sub rdi,asm_tok
                            dec eax
                        .untilz
                        .endc .if ( [rdi].asm_tok.token != T_OP_SQ_BRACKET )
                        .if ( eax > 1 && [rdi-asm_tok].asm_tok.token == T_ID )
                            sub rdi,asm_tok
                        .endif
                    .endif

                .case ( edx == SYM_STACK )
                .case ( edx == SYM_INTERNAL )
                .case ( edx == SYM_EXTERNAL )
                .case ( [rax].asym.flags & S_ISPROC )
                    mov ecx,T_ISPROC
                    inc [rsi].cstring
                   .endc

                .case ( edx == SYM_UNDEFINED )
                     mov rdx,[rsi].input
                    .endc .if ( B[rdx+1] != ')' )
                     mov ecx,T_ISPROC
                    .endc
                .endsw
                or [rdi].asm_tok.flags,cl

            .else
                mov rdi,[rsi].input
                .if ( B[rdi+1] == ')' ) ; && [rbx-2*asm_tok].token == T_DIRECTIVE
                    ;
                    ; undefined code label..
                    ;
                    ; label() or .if label()
                    ; ...
                    ; label:
                    ;
                    or [rbx-asm_tok].flags,T_ISPROC
                .endif
            .endif
            mov rdi,[rsi].input
            mov eax,[rdi]
        .endif
        or cl,[rbx-asm_tok].flags
        .if ( cl & T_ISPROC && !ModuleInfo.strict_masm_compat )

            mov rcx,[rsi].tokenarray
            or  [rcx].asm_tok.flags,T_EXPAND
        .endif
        ;
        ; no break
        ;
      .case ')'
        .if ( al == ')' && [rsi].brachets )

            dec [rsi].brachets
            dec [rsi].cstring
        .endif

      .case '*'..'/'
        ;
        ; ')' : 0x29: T_CL_BRACKET
        ; '*' : 0x2A: binary operator
        ; '+' : 0x2B: unary|binary operator
        ; ',' : 0x2C: T_COMMA
        ; '-' : 0x2D: unary|binary operator
        ; '.' : 0x2E: T_DOT binary operator
        ; '/' : 0x2F: binary operator
        ;
        ; all of these are themselves a token
        ;
        inc [rsi].input
        mov [rbx].token,al
        mov [rbx].specval,0 ; initialize, in case the token needs extra data
        movzx eax,al        ; v2.06: use constants for the token string
        sub al,'('
        lea rcx,stokstr1
        lea rax,[rcx+rax*2]
        mov [rbx].string_ptr,rax
       .endc

      .case '[' ; T_OP_SQ_BRACKET operator - needs a matching ']' (0x5B)
      .case ']' ; T_CL_SQ_BRACKET (0x5D)

        inc [rsi].input
        mov [rbx].token,al
        movzx eax,al
        sub al,'['
        lea rcx,stokstr2
        lea rax,[rcx+rax*2]
        mov [rbx].string_ptr,rax
       .endc

    .case '=' ; (0x3D)

        .if ( ah != '=' )

            mov [rbx].token,T_DIRECTIVE
            mov [rbx].tokval,T_EQU
            mov [rbx].dirtype,DRT_EQUALSGN ;  to make it differ from EQU directive
            lea rax,__equ
            mov [rbx].string_ptr,rax
            inc [rsi].input
           .endc
        .endif
        ;
        ; fall through
        ;
    .default
        ;
        ; detect C style operators.
        ; DF_CEXPR is set if .IF, .WHILE, .ELSEIF or .UNTIL
        ; has been detected in the current line.
        ; will catch: '!', '<', '>', '&', '==', '!=', '<=', '>=', '&&', '||'
        ; A single '|' will also be caught, although it isn't a valid
        ; operator - it will cause a 'operator expected' error msg later.
        ; the tokens are stored as one- or two-byte sized "strings".
        ;
        tstrchr("=!<>&|", eax)
        mov edx,[rdi]

        .if ( rax && [rsi].flags2 & DF_CEXPR )

            mov al,[rax]
            mov rcx,[rsi].output
            inc [rsi].output
            mov [rcx],al
            inc [rsi].input
            mov [rbx].stringlen,1
            mov rdx,[rsi].input

            .if ( al == '&' || al == '|' )

                .if ( [rdx] == al )

                    inc rcx
                    mov [rcx],al
                    inc [rsi].output
                    inc [rsi].input
                    mov [rbx].stringlen,2
                    ;
                    ; v2.24 proc( &arg )
                    ;
                .elseif ( al == '&' && ( [rbx-asm_tok].token == T_COMMA || [rbx-asm_tok].token == T_OP_BRACKET ) )

                    mov [rbx].token,al
                    lea rax,__amp
                    mov [rbx].string_ptr,rax
                   .endc
                .endif

            .elseif ( B[rdx] == '=' )

                inc rcx
                mov B[rcx],'='
                inc [rsi].output
                inc [rsi].input
                mov [rbx].stringlen,2
            .endif

            xor eax,eax
            mov [rbx].token,T_STRING
            mov [rbx].string_delim,al
            mov [rcx+1],al
            inc [rsi].output
           .endc
        .endif

        .if ( dl == '&' ) ; v2.08: ampersand is a special token

            inc [rsi].input
            mov [rbx].token,dl
            lea rax,__amp
            mov [rbx].string_ptr,rax
           .endc
        .endif
        ;
        ; anything we don't recognise we will consider a string,
        ; delimited by space characters, commas, newlines or nulls
        ;
        .return get_string(rbx, rsi)
    .endsw
    .return( 0 )

get_special_symbol endp


get_number proc __ccall uses rsi rdi rbx buf:token_t, p:ptr line_status

    ldr rbx,buf
    ldr rsi,p
    mov rdx,[rsi].input
    xor edi,edi

ifdef CHEXPREFIX

   .new prefix:byte = 0
    mov eax,[rdx]
    or  eax,0x2000
    .if ( ax == 'x0' )
        add rdx,2
        inc prefix
    .endif

endif

    ;
    ; Read numbers 0..9 and a..f
    ;
    .while 1

        .if ( isldigit( [rdx] ) )

            sub eax,'0'
            mov ecx,eax
            mov eax,1
            shl eax,cl
            or  edi,eax

        .elseif ( islxdigit( eax ) )

            or  eax,0x20
            add eax,10 - 'a'
            mov ecx,eax
            mov eax,1
            shl eax,cl
            or  edi,eax

        .else

            or  eax,0x20
           .break
        .endif
        inc rdx
    .endw

    mov rcx,rdx

ifdef CHEXPREFIX

    .if ( prefix )

        mov eax,16
        .if !edi
            xor eax,eax
        .endif

    .else

endif

    .switch eax

    .case '.'
        ;
        ; valid floats look like: (int)[.(int)][r(int)]
        ; Masm also allows hex format, terminated by 'r' (3F800000r)
        ;
        xor edi,edi
        mov eax,1

        .while al

            mov al,[rdx]

            .if ( eax == '.' )

                add ah,1

            .elseif ( al < '0' || al > '9' )

                or al,0x20

                .if ( al != 'e' || edi )
                    .break
                .endif
                inc edi
                ;
                ; accept e+2 / e-4 /etc.
                ;
                mov al,[rdx+1]
                .if ( al == '+' || al == '-' )
                    inc rdx
                .endif
            .endif
            inc rdx
        .endw

        mov [rbx].token,T_FLOAT
        mov [rbx].floattype,0
        jmp number_done

    .case 'r'
        mov [rbx].token,T_FLOAT
        mov [rbx].floattype,'r'
        inc rdx
        jmp number_done

    .case 'h'
        mov eax,16
        inc rdx
       .endc

    .case 'y'
        xor eax,eax
        .if ( edi & 3 )
            mov eax,2
            inc rdx
        .endif
       .endc

    .case 't'
        xor eax,eax
        .if ( edi & 0x03FF )
            mov eax,10
            inc rdx
        .endif
        .endc

    .case 'q'
        .if ( !( edi & 0x00FF ) )

            mov [rbx].token,T_FLOAT
            mov [rbx].floattype,'q'
            inc rdx
            jmp number_done
        .endif

    .case 'o'
        xor eax,eax
        .if ( edi & 0x00FF )
            mov eax,8
            inc rdx
        .endif
        .endc

    .default

        mov cl,ModuleInfo.radix
        mov eax,1
        shl eax,cl
        dec rdx
        mov cl,[rdx]
        or  cl,20h

        .if ( ( cl == 'b' || cl == 'd' ) && edi >= eax )

            mov rax,[rsi].input
            mov ch,'1'

            .if ( cl != 'b' )
                mov ch,'9'
            .endif

            .while ( rax < rdx && B[rax] <= ch )
                inc rax
            .endw

            .if ( rax == rdx )

                mov eax,2
                .if ( cl != 'b' )
                    mov eax,10
                .endif
                mov rcx,rdx
                inc rdx
               .endc
            .endif
        .endif

        inc rdx
        mov cl,ModuleInfo.radix
        mov eax,1
        shl eax,cl
        cmp edi,eax
        mov eax,0
        mov rcx,rdx
        .ifc
            movzx eax,ModuleInfo.radix
        .endif
    .endsw

ifdef CHEXPREFIX

    .endif

endif

    .if ( eax )

        mov [rbx].token,T_NUM
        mov [rbx].numbase,al
        sub rcx,[rsi].input
        mov [rbx].itemlen,ecx
    .else

        mov [rbx].token,T_BAD_NUM
        .while ( islabel( [rdx] ) )
            inc rdx
        .endw
    .endif

number_done:

    mov rcx,rdx
    mov rdx,rsi
    mov rdi,[rdx].line_status.output
    mov rsi,[rdx].line_status.input
    sub rcx,rsi
    rep movsb
    xor eax,eax
    mov [rdi],al
    inc rdi
    mov [rdx].line_status.input,rsi
    mov [rdx].line_status.output,rdi
    ret

get_number endp


    assume rdx:ptr line_status

get_id_in_backquotes proc __ccall uses rsi rdi rbx buf:token_t, p:ptr line_status

    ldr rdx,p
    ldr rbx,buf
    inc [rdx].input
    mov rsi,[rdx].input
    mov rdi,[rdx].output
    mov [rbx].token,T_ID
    mov [rbx].idarg,0

    mov al,[rsi]

    .while ( al != '`' )

        .if ( !al || al == ';' )

            mov B[rdi],0
           .return asmerr( 2046 )
        .endif
        lodsb
        stosb
        inc [rdx].input
    .endw

    inc [rdx].input
    xor eax,eax
    stosb
    mov [rdx].output,rdi
    ret

get_id_in_backquotes endp


get_id proc __ccall uses rsi rdi rbx buf:token_t, p:ptr line_status

    ldr rbx,buf
    ldr rdx,p
    mov rsi,[rdx].input
    mov rdi,[rdx].output
    mov [rbx].bytval,0 ; added v2.27

    mov eax,[rsi]
    .if ( ax == '"L' && [rdx].brachets )

        stosb
        inc [rdx].input
        inc [rdx].output
       .return get_string( rbx, rdx )
    .endif

continue_scan:

    .repeat
        stosb
        inc rsi
    .until !islabel( [rsi] )
    ;
    ; if the name starts with a dot then accept dots
    ; within the name (though not as last char). OPTION DOTNAMEX
    ; must be on.
    ;
    .if ( al == '.' && ModuleInfo.dotnamex )

        mov rcx,[rdx].output
        .if ( al == [rcx] )
            ;
            ; allow .name..
            ; allow .name.00100
            ;
            .if ( al == B[rsi+1] || ( B[rsi+1] >= '0' && B[rsi+1] <= '9') )

                jmp continue_scan
            .endif
            .if ( islabel( [rsi+1] ) )

                mov al,'.'
                jmp continue_scan
            .endif
        .endif
    .endif

    mov rcx,rdi
    sub rcx,[rdx].output

    .if ( ecx > MAX_ID_LEN )

        asmerr( 2043 )
        mov rdx,p
        mov rdi,[rdx].output
        add rdi,MAX_ID_LEN
    .endif

    mov B[rdi],0
    inc rdi
    mov rax,[rdx].output
    mov al,[rax]

    .if ( ecx == 1 && al == '?' )

        mov [rdx].input,rsi
        mov [rbx].token,T_QUESTION_MARK
        mov [rbx].string_ptr,&__quest
       .return
    .endif

    mov rax,[rdx].output
    FindResWord( rax, ecx )
    mov rdx,p

    .if ( eax == 0 )

        mov rax,[rdx].output
        mov al,[rax]

        .if ( al == '.' && !ModuleInfo.dotname )

            mov [rbx].token,T_DOT
            lea rax,stokstr1[('.' - '(') * 2]
            mov [rbx].string_ptr,rax
            inc [rdx].input
           .return
        .endif
        mov [rdx].input,rsi
        mov [rdx].output,rdi
        mov [rbx].token,T_ID
        mov [rbx].idarg,0
       .return
    .endif

    mov [rdx].input,rsi
    mov [rdx].output,rdi

    .switch eax
    .case T_SYSCALL       ; v2.24 hack for syscall..
        .if ( [rdx].index == 0 )
            mov eax,T_SYSCALL_
        .endif
        .endc
      .case T_DOT_ELSEIF
      .case T_DOT_WHILE
      .case T_DOT_CASE
        mov [rbx].flags,T_HLLCODE
       .endc
    .endsw
    mov [rbx].tokval,eax

    .if ( eax >= SPECIAL_LAST )

        .if ( ModuleInfo.m510 )

            mov     eax,[rbx].tokval
            sub     eax,SPECIAL_LAST
            lea     rdx,optable_idx
            lea     rcx,InstrTable
            movzx   eax,word ptr [rdx+rax*2]
            movzx   ecx,[rcx+rax*instr_item].instr_item.cpu
            mov     eax,ecx
            and     eax,P_CPU_MASK
            and     ecx,P_EXT_MASK
            mov     edi,ModuleInfo.curr_cpu
            mov     esi,edi
            and     edi,P_CPU_MASK
            and     esi,P_EXT_MASK

            .if ( eax > edi || ecx > esi )

                mov [rbx].token,T_ID
                mov [rbx].idarg,0
               .return
            .endif
        .endif
        mov [rbx].token,T_INSTRUCTION
       .return
    .endif

    imul    esi,[rbx].tokval,special_item
    lea     rcx,SpecialTable
    add     rcx,rsi
    mov     [rbx].bytval,[rcx].special_item.bytval
    movzx   eax,[rcx].special_item.type

    .switch eax
    .case RWT_REG
        mov ecx,T_REG
       .endc
    .case RWT_DIRECTIVE
        mov rdx,p
        .if ( [rdx].flags2 == 0 )
            mov [rdx].flags2,[rcx].special_item.value
        .endif
        mov ecx,T_DIRECTIVE
       .endc
    .case RWT_UNARY_OP
        mov ecx,T_UNARY_OPERATOR
       .endc
    .case RWT_BINARY_OP
        mov ecx,T_BINARY_OPERATOR
       .endc
    .case RWT_STYPE
        mov ecx,T_STYPE
       .endc
    .case RWT_RES_ID
        mov ecx,T_RES_ID
       .endc
    .default
        mov ecx,T_ID
        mov [rbx].idarg,0
    .endsw
     mov [rbx].token,cl
    .return( 0 )

get_id endp


;
; save symbols in IFDEF's so they don't get expanded
;
StartComment proc fastcall p:string_t

    tstrstart(rcx)
    .if ecx
        mov ModuleInfo.inside_comment,cl
        inc rax
        .if tstrchr(rax, ecx)
            mov ModuleInfo.inside_comment,0
        .endif
    .else
        asmerr( 2110 )
    .endif
    ret

StartComment endp


    option proc:public


    assume rsi:nothing
    assume rdx:ptr line_status

GetToken proc fastcall uses rsi rdi rbx tokenarray:token_t, p:ptr line_status

    ;
    ; get one token.
    ; possible return values: NOT_ERROR, ERROR, EMPTY.
    ;
    ; names beginning with '.' are difficult to detect,
    ; because the dot is a binary operator. The rules to
    ; accept a "dotted" name are:
    ; 1.- a valid ID char is to follow the dot
    ; 2.- if buffer index is > 0, then the previous item
    ;     must not be a reg, ), ] or an ID.
    ; [bx.abc]    -> . is an operator
    ; ([bx]).abc  -> . is an operator
    ; [bx].abc    -> . is an operator
    ; varname.abc -> . is an operator
    ;

    mov [rcx].asm_tok.flags,0
    mov rax,[rdx].input

    .switch
    .case isldigit( [rax] )
        .return get_number( rcx, rdx )
    .case islabel0( eax )
        .return get_id( rcx, rdx )

    .case ( al == '`' )
        .endc .if ModuleInfo.strict_masm_compat
        .return get_id_in_backquotes( rcx, rdx )

    .case ( al == '.' )

        mov rax,[rdx].input
        .endc .if !islabel( [rax+1] )

        xor eax,eax
        .if ( eax != [rdx].index )
            movzx eax,[rcx-asm_tok].asm_tok.token
        .endif
        .if ( [rdx].index == 0 || ( eax != T_REG && eax != T_CL_BRACKET &&
              eax != T_CL_SQ_BRACKET && eax != T_ID ) )

            .return get_id( rcx, rdx )
        .endif
        ;
        ; added v2.29 for .break(n) and .continue(n)
        ; added v2.30 for .return and .new
        ;
        .if ( eax == T_CL_BRACKET )

            mov rsi,rcx
            lea rbx,[rcx-2*asm_tok]
            mov eax,1
            mov ecx,[rdx].index

            .fors ( ecx -= 2 : ecx > 1 : ecx--, rbx -= asm_tok )
                .if ( [rbx].token == T_OP_BRACKET )
                    dec eax
                   .break .ifz
                .elseif ( [rbx].token == T_CL_BRACKET )
                    inc eax
                .endif
            .endf

            .if ( ecx > 1 )

                ; .return id(..)

                sub ecx,1
                sub rbx,asm_tok

                .if ( [rbx-asm_tok].token == T_DOT )

                    sub ecx,2
                    sub rbx,2*asm_tok

                    ; .return [..].id(..)

                    .if ( [rbx].token == T_CL_SQ_BRACKET )
                        .for ( rbx -= asm_tok, ecx-- : ecx : ecx--, rbx -= asm_tok )
                            .break .if ( [rbx].token == T_OP_SQ_BRACKET )
                        .endf
                    .endif
                .endif
            .endif
            mov eax,[rbx-asm_tok].tokval
            mov rcx,rsi
        .else
            xor eax,eax
            .if ( [rdx].index > 1 )
                mov eax,[rcx-2*asm_tok].asm_tok.tokval
            .endif
        .endif
        .if ( eax == T_DOT_BREAK || eax == T_DOT_GOTOSW ||
              eax == T_DOT_CONTINUE || eax == T_DOT_RETURN )
            .return get_id( rcx, rdx )
        .endif
    .endsw
    .return get_special_symbol( rcx, rdx )

GetToken ENDP


;
; create tokens from a source line.
; line:  the line which is to be tokenized
; start: where to start in the token buffer. If start == 0,
;    then some variables are additionally initialized.
; flags: 1=if the line has been tokenized already.
;
; Extend the size dynamically for large arrays
;

Tokenize proc __ccall uses rsi rdi rbx line:string_t, start:uint_t, tokenarray:token_t, flags:uint_t

  local rc, p:line_status

    mov p.input,line
    mov p.start,rax
    mov p.tokenarray,tokenarray
    mov p.outbuf,StringBuffer
    mov p.flags,flags
    mov p.index,start
    mov p.flags2,0
    mov p.flags3,0
    mov p.cstring,0
    mov p.brachets,0

    .repeat

        .if ( start == 0 )

            mov p.output,StringBuffer
            .if ( ModuleInfo.inside_comment )

                .if tstrchr( p.start, ModuleInfo.inside_comment )

                    mov ModuleInfo.inside_comment,0
                .endif
                .break
            .endif
        .else

            mov p.output,StringBufferEnd
        .endif

        .while 1

            mov rsi,p.input
            .while ( islspace( [rsi] ) )
                inc rsi
            .endw
            mov p.input,rsi

            .if ( al == ';' && flags == TOK_DEFAULT )

                .while ( rsi > p.start )

                    .break .if !islspace( [rsi-1] )
                    dec rsi
                .endw

                mov p.input,rsi
                mov CurrComment,tstrcpy( CommentBuffer, rsi )
                mov B[rsi],0
            .endif

            imul ebx,p.index,asm_tok
            add rbx,p.tokenarray
            mov [rbx].tokpos,rsi

            .if ( B[rsi] == 0 )

                .if ( p.index > 1 && ( [rbx-asm_tok].token == T_COMMA || p.brachets ) &&
                      ( Parse_Pass == PASS_1 || !UseSavedState ) && !start )

                    .if ( IsMultiLine( p.tokenarray ) || p.brachets )

                        mov edi,tstrlen( p.output )
                        add edi,size_t
                        and edi,-size_t
                        add rdi,p.output

                        .if ( GetTextLine( rdi ) )

                            mov rdi,ltokstart( rdi )

                            .if ( ecx )

                                tstrcpy( p.input, rdi )
                                tstrlen( p.start )
                                mov ecx,MaxLineLength
                                sub ecx,32

                                .if ( eax >= ecx )

                                    .if ( InputExtend( &p ) == 0 )

                                        asmerr( 2039 )
                                        mov p.index,start
                                       .break
                                    .endif
                                .endif
                                .continue
                            .endif
                        .endif
                    .endif
                .endif
                .break
            .endif

            mov [rbx].string_ptr,p.output
            mov rc,GetToken( rbx, &p )

            imul ebx,p.index,asm_tok
            add rbx,p.tokenarray

            .switch
            .case ( eax == EMPTY )
                .continue

            .case ( eax == ERROR )
                ;
                ; skip this line
                ;
                mov p.index,start
               .break

            .case ( [rbx].token == T_DBL_COLON )
                .if ( !ModuleInfo.strict_masm_compat )
                    mov rax,p.tokenarray
                    or [rax].asm_tok.flags,T_EXPAND
                .endif
               .endc
            .endsw

            .if ( !( flags & TOK_RESCAN ) )

                mov rax,p.tokenarray
                mov cl,[rax+asm_tok].asm_tok.token
                mov eax,p.index

                .if ( !eax || ( eax == 2 && ( cl == T_COLON || cl == T_DBL_COLON ) ) )

                    mov ecx,[rbx].tokval
                    .if ( [rbx].token == T_DIRECTIVE &&
                         ( [rbx].bytval == DRT_CONDDIR || ecx == T_DOT_ASSERT ) )

                        .if ( ecx == T_COMMENT )
                            ;
                            ; p.index is 0 or 2
                            ;
                            StartComment( p.input )
                           .break
                        .endif

                        mov edx,1
                        .if ( ecx == T_DOT_ASSERT )

                            dec edx
                            .if ( !( ModuleInfo.xflag & OPT_ASSERT ) )

                                mov rax,p.input
                                mov cl,[rax]

                                .while ( cl == ' ' || cl == 9 )

                                    inc rax
                                    mov cl,[rax]
                                .endw

                                .if ( cl == ':' )

                                    inc rax
                                    mov cl,[rax]

                                    .while ( cl == ' ' || cl == 9 )

                                        inc rax
                                        mov cl,[rax]
                                    .endw

                                    mov eax,[rax]
                                    or  eax,0x20202020

                                    .if ( eax == 'sdne' )

                                        mov ecx,T_ENDIF
                                        inc edx
                                    .endif
                                .endif
                            .endif
                        .endif

                        .if ( edx )

                            CondPrepare(ecx)
                            .if ( CurrIfState != BLOCK_ACTIVE )
                                ;
                                ; p.index is 1 or 3
                                ;
                                inc p.index
                               .break
                            .endif
                        .else
                            .break .if ( CurrIfState != BLOCK_ACTIVE )
                            ;
                            ; further processing skipped. p.index is 0
                            ;
                        .endif

                    .elseif ( CurrIfState != BLOCK_ACTIVE )
                        ;
                        ; further processing skipped. p.index is 0
                        ;
                        .break
                    .endif
                .endif
            .endif

            inc p.index
            mov eax,MaxLineLength
            shr eax,2

            .ifs ( p.index >= eax ) ; MAX_TOKEN

                dec p.index
                .if ( InputExtend( &p ) == FALSE )

                    asmerr( 2141 )
                    mov p.index,start
                   .break(1)
                .endif
                inc p.index
            .endif

            mov rax,p.output
            sub rax,StringBuffer
            add rax,size_t
            and rax,-size_t
            add rax,StringBuffer
            mov p.output,rax
        .endw

        mov rax,p.output
        sub rax,StringBuffer
        add rax,size_t
        and rax,-size_t
        add rax,StringBuffer
        mov p.output,rax
        mov StringBufferEnd,rax

        .break .if ( !p.brachets )
        .break .if ( flags == TOK_RESCAN )
        .break .if ( CurrIfState != BLOCK_ACTIVE )

        asmerr( 2157 )
    .until 1

    mov rbx,p.tokenarray
    imul eax,p.index,asm_tok
    add rbx,rax
    mov [rbx].token,T_FINAL
    mov al,p.flags3
    mov [rbx].bytval,al
    mov [rbx].string_ptr,&__null
    mov eax,p.index
    ret

Tokenize endp

    end
