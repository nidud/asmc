include string.inc

include asmc.inc
include token.inc

GetTextLine proto :dword
FindResWord proto fastcall :dword, :dword
conditional_assembly_prepare proto :dword

INST_ALLOWED_PREFIX equ 007h
INST_FIRST          equ 008h
INST_RM_INFO        equ 010h
INST_OPND_DIR       equ 0E0h

instr_item      STRUC
opclsidx        db ?    ; v2.06: index for opnd_clstab
byte1_info      db ?    ; flags for 1st byte
flags           db ?
reserved        db ?    ; not used yet
cpu             dw ?
opcode          db ?    ; opcode byte
rm_byte         db ?    ; mod_rm_byte
instr_item      ENDS

externdef       InstrTable:instr_item
externdef       token_stringbuf:DWORD
externdef       commentbuffer:DWORD
externdef       CurrIfState:DWORD
externdef       optable_idx:WORD

.data
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

_cstring    db 0    ; allow \" in string
_brachets   db 0    ; proc ( ... )

    .code

    option  proc:private
    assume  ecx:ptr asmtok

IsMultiLine proc fastcall tokenarray:ptr asmtok
    ;
    ; test line concatenation if last token is a comma.
    ; dont concat EQU, macro invocations or
    ; - ECHO
    ; - FORC/IRPC (v2.0)
    ; - INCLUDE (v2.8)
    ; lines!
    ; v2.05: don't concat if line's an instruction.
    ;
    .if [ecx+16].token == T_DIRECTIVE && [ecx+16].tokval == T_EQU

        xor eax,eax
        ret
    .endif

    .if [ecx+16].token == T_COLON

        add ecx,16 * 2
    .endif

    movzx   eax,[ecx].token
    .switch eax

      .case T_DIRECTIVE

        mov ecx,[ecx].tokval
        .switch ecx

          .case T_ECHO
          .case T_INCLUDE
          .case T_FORC
          .case T_IRPC

            xor eax,eax
            ret
        .endsw
        .endc

      .case T_INSTRUCTION

        xor eax,eax
        ret

      .case T_ID
        ;
        ; don't concat macros
        ;
        .if SymFind( [ecx].string_ptr )

            .if [eax].asym.state == SYM_MACRO && \
                !([eax].asym.mac_flag & SMAC_MULTILINE)

                xor eax,eax
                ret
            .endif
        .endif

    .endsw
    mov eax,1
    ret
IsMultiLine endp

    assume edx:ptr line_status

ConcatLine proc uses esi edi edx ecx src, cnt, o, ls

    mov eax,src
    mov esi,eax
    add eax,1

    .repeat
        .if M_EAT_SPACE(ecx, eax)

            mov eax,EMPTY
            .break .if ecx != ';'
        .endif

        mov edi,o
        .if !GetTextLine(edi)

            mov eax,EMPTY
            .break
        .endif

        M_SKIP_SPACE eax, edi
        strlen( edi )

        .if !cnt

            mov byte ptr [esi],' '
            inc esi
        .endif

        mov edx,ls
        mov ecx,esi
        sub ecx,[edx].start
        add ecx,eax

        .if ecx >= MAX_LINE_LEN

            asmerr( 2039 )
            mov ecx,esi
            sub ecx,[edx].start
            inc ecx
            mov eax,MAX_LINE_LEN
            sub eax,ecx
            mov byte ptr [edi+eax],0
        .endif

        lea ecx,[eax+1]
        xchg esi,edi
        rep movsb
        mov eax,NOT_ERROR

    .until 1
    ret
ConcatLine endp

    assume ecx:nothing
    assume ebx:ptr asmtok

get_string proc uses esi edi ebx buf:ptr asmtok, p:ptr line_status

    local   symbol_c:   SBYTE,
            symbol_o:   SBYTE,
            delim:      SBYTE,
            level:      UINT,
            tdst:       LPSTR,
            tsrc:       LPSTR,
            tcount:     UINT

    mov edx,p
    mov ebx,buf
    mov esi,[edx].input
    mov edi,[edx].output
    movzx eax,BYTE PTR [esi]
    xor ecx,ecx
    mov symbol_o,al

    .switch eax

      .case '"'
      .case 27h

        mov [ebx].string_delim,al
        mov ah,al
        movsb

        .repeat
            mov al,[esi]
            .switch
              .case !al
                ;
                ; missing terminating quote, change to undelimited string
                ;
                mov [ebx].string_delim,al
                add ecx,1 ; count the first quote
                .break

              .case ah == '"' && al == _cstring ; case \" ?

                .if BYTE PTR [esi-1] == '\' && \
                    BYTE PTR [esi-2] != '\' ; case \\"

                    stosb
                    inc esi
                    inc ecx
                    .endc
                .endif

                lea eax,[esi+1]

                .while byte ptr [eax] == ' ' || \
                       byte ptr [eax] == 9

                       add eax,1
                .endw

                .if byte ptr [eax] == '"'
                    ;
                    ; "string1" "string2"
                    ;
                    lea esi,[eax+1]
                    mov eax,'""'
                    .endc
                .endif

                mov eax,'""'

              .case al == ah        ; another quote?

                stosb
                inc esi
                .break .if [esi] != al  ; exit loop
                dec edi

              .default
                mov [edi],al
                add edi,1
                add esi,1
                add ecx,1
                .endc
            .endsw
        .until ecx >= MAX_STRING_LEN
        ;
        ; end of string marker is the same
        ;
        .endc

      .case '{'

        test [edx].flags,TOK_NOCURLBRACES
        jnz default

        mov symbol_c,'}'

      .case '<'

        mov [ebx].string_delim,al
        mov level,ecx

        .if al == '<'

            mov symbol_c,'>'
        .endif
        add esi,1

        .while  ecx < MAX_STRING_LEN

            mov ax,[esi]
            .if al == symbol_o      ; < or { ?

                inc level
            .elseif al == symbol_c  ; > or } ?

                .if level

                    dec level
                .else
                    ;
                    ; store the string delimiter unless it is <>
                    ; v2.08: don't store delimiters for {}-literals
                    ;
                    add esi,1
                    .break      ; exit loop
                .endif

            .elseif ( al == '"' || al == 27h ) && !( [edx].flags2 & DF_STRPARM )
                ;
                ; a " or ' inside a <>/{} string? Since it's not a must that
                ; [double-]quotes are paired in a literal it must be done
                ; directive-dependant!
                ; see: IFIDN <">,<">
                ;
                mov delim,al
                movsb
                add ecx,1
                mov tdst,edi
                mov tsrc,esi
                mov tcount,ecx
                mov ax,[esi]

                .while al != delim && al && ecx < MAX_STRING_LEN - 1

                    .if symbol_o == '<' && al == '!' && ah

                        add esi,1
                    .endif
                    movsb
                    add ecx,1
                    mov ax,[esi]
                .endw

                .if al != delim

                    mov esi,tsrc
                    mov edi,tdst
                    mov ecx,tcount
                    .continue
                .endif
            .elseif al == '!' && symbol_o == '<' && ah
                ;
                ; handle literal-character operator '!'.
                ; it makes the next char to enter the literal uninterpreted.
                ;
                ; v2.09: don't store the '!'
                ;
                add esi,1
            .elseif al == '\'

                .if ConcatLine(esi, ecx, edi, edx) != EMPTY

                    or [edx].flags3,TF3_ISCONCAT
                    .continue
                .endif
            .elseif !al || ( al == ';' && symbol_o == '{' )

                .if [edx].flags == TOK_DEFAULT && !([edx].flags2 & DF_NOCONCAT)
                    ;
                    ; if last nonspace character was a comma
                    ; get next line and continue string scan
                    ;
                    mov tdst,edi
                    mov tcount,ecx
                    sub edi,1

                    .if M_EAT_SPACE_R(eax, edi) == ','

                        strlen( [edx].output )
                        add eax,4
                        and eax,-4
                        add eax,[edx].output
                        mov edi,eax

                        .if GetTextLine(eax)

                            M_SKIP_SPACE eax, edi
                            strlen( edi )
                            add eax,tcount
                            .if eax >= MAX_LINE_LEN

                                asmerr( 2039 )
                                jmp toend
                            .endif
                            strcpy( esi, edi )
                            mov edi,tdst
                            mov ecx,tcount
                            mov edx,p
                            .continue
                        .endif
                    .endif
                .endif

                mov edx,p
                mov esi,[edx].input
                mov edi,[edx].output
                movsb
                mov ecx,1
                jmp default

            .endif
            movsb
            add ecx,1
        .endw
        .endc

      .default
       default:

        mov [ebx].string_delim,0
        ;
        ; this is an undelimited string,
        ; so just copy it until we hit something that looks like the end.
        ; this format is used by the INCLUDE directive, but may also
        ; occur inside the string macros!
        ;
        ; v2.05: also stop if a ')' is found - see literal2.asm regression test
        ;
        .while  ecx < MAX_STRING_LEN

            movzx   eax,BYTE PTR [esi]

            .break .if !eax
            .break .if BYTE PTR _ltype[eax+1] & _SPACE
            .break .if eax == ','

            .if eax == ')'

                mov _brachets,0
                .break
            .endif

            .break .if eax == '%'
            .break .if eax == ';' && [edx].line_status.flags == TOK_DEFAULT

            .if eax == '\'

                .if [edx].flags == TOK_DEFAULT || [edx].flags & TOK_LINE

                    .if ConcatLine(esi, ecx, edi, edx) != EMPTY

                        or [edx].flags3,TF3_ISCONCAT
                        .continue .if ecx

                        mov eax,EMPTY
                        jmp toend
                    .endif
                .endif
            .elseif eax == '!' && BYTE PTR [esi+1] && ecx < MAX_STRING_LEN - 1
                ;
                ; v2.08: handle '!' operator
                ;
                movsb
            .endif
            movsb
            add ecx,1
        .endw
    .endsw

    .if ecx == MAX_STRING_LEN

        asmerr( 2041 )
    .else
        xor eax,eax
        mov [edi],al
        add edi,1
        mov [ebx].token,T_STRING
        mov [ebx].stringlen,ecx
        mov [edx].input,esi
        mov [edx].output,edi
    .endif
toend:
    mov _cstring,0
    ret
get_string endp

    assume edx:nothing
    assume esi:ptr line_status

get_special_symbol proc fastcall uses esi edi ebx buf:ptr asmtok , p:ptr line_status

    mov ebx,buf
    mov esi,p
    mov edi,[esi].input
    mov eax,[edi]
    mov [ebx].tokval,0

    .switch al

      .case ':' ; T_COLON binary operator (0x3A)

        inc [esi].input
        lea ecx,__dcolon

        .if ah == ':'

            inc [esi].input
            mov [ebx].token,T_DBL_COLON
            mov [ebx].string_ptr,ecx
        .else
            inc ecx
            mov [ebx].token,T_COLON
            mov [ebx].string_ptr,ecx
        .endif

        .endc

      .case '%' ; T_PERCENT (0x25)

        shr eax,8
        or  eax,202020h
        .if eax == 'tuo'    ; %OUT directive?

            mov eax,[esi].input
            movzx   eax,BYTE PTR [eax+4]

            .if !( _ltype[eax+1] & _LABEL or _DIGIT )

                mov [ebx].token,T_DIRECTIVE
                mov [ebx].tokval,T_ECHO
                mov [ebx].dirtype,DRT_ECHO
                mov edi,[esi].output
                mov ecx,[esi].input
                add [esi].input,4
                add [esi].output,5
                mov eax,[ecx]
                mov [edi],eax
                xor eax,eax
                mov [edi+4],al
                .endc
            .endif
        .endif

        inc [esi].input
        .if [esi].flags == TOK_DEFAULT && [esi].index == 0

            or  [esi].flags3,TF3_EXPANSION
            mov eax,EMPTY
            jmp toend
        .endif

        lea eax,__percent
        mov [ebx].token,T_PERCENT
        mov [ebx].string_ptr,eax

        .endc

      .case '('
        ;
        ; 0x28: T_OP_BRACKET operator - needs a matching ')'
        ; v2.11: reset c-expression flag if a macro function call is detected
        ; v2.20: set _cstring to allow escape chars (\") in @CStr( string )
        ; v2.20: removed auto off switch for asmc_syntax in macros
        ; v2.20: added more test code for label() calls
        ;

        .if ah == ')' && [ebx-16].token == T_REG
            ;
            ; REG() expans as CALL REG
            ;
            or [ebx-16].hll_flags,T_HLL_PROC

        .elseif [esi].index && [ebx-16].token == T_ID

            xor eax,eax

            .if [esi].index >= 3 && [ebx-32].token == T_DOT
                ;
                ; p.x(...)
                ; [...][.type].x(...)
                ;
                lea edi,[ebx-16*3]
                .if [edi].asmtok.token == T_CL_SQ_BRACKET

                    add edi,32
                    inc eax
                    mov edx,SYM_TYPE

                .else

                    SymFind( [edi].asmtok.string_ptr )
                    xor edx,edx

                .endif

            .else

                lea edi,[ebx-16]
                SymFind( [ebx-16].string_ptr )
                xor edx,edx

            .endif

            .if eax

                xor ecx,ecx
                .if !edx
                    movzx edx,[eax].asym.state
                .endif
                .switch

                  .case !(ModuleInfo.aflag & _AF_ON)
                    .endc .if edx != SYM_MACRO
                    .endc .if !([eax].asym.mac_flag & SMAC_ISFUNC)
                    and [esi].flags2,not DF_CEXPR
                    .endc

                  .case edx == SYM_MACRO
                    .if [eax].asym.mac_flag & SMAC_ISFUNC

                        and [esi].flags2,not DF_CEXPR
                        .if [eax].asym.flag & SFL_PREDEFINED

                            mov edx,[eax].asym._name
                            mov edx,[edx]
                            .if edx == "tSC@"

                                inc _brachets
                                mov _cstring,'"'
                                .endc
                            .endif
                        .endif
                        mov ecx,T_HLL_MACRO
                        .endc
                    .endif

                    .endc .if [eax].asym.flag & SFL_PREDEFINED
                    .endc .if ![eax].asym.string_ptr
                    .endc .if !SymFind( [eax].asym.string_ptr )
                    xor ecx,ecx

                    .endc .if !( [eax].asym.flag & SFL_ISPROC )
                    mov ecx,T_HLL_PROC
                    inc _brachets
                    mov _cstring,'"'
                    .endc

                  .case edx == SYM_TYPE ;  structure, union, typedef, record
                    ;
                    ; [...].type.x(...)
                    ;
                    mov eax,[esi].index
                    .endc .if eax < 5
                    .endc .if [edi-16].asmtok.token != T_DOT
                    .endc .if [edi-32].asmtok.token != T_CL_SQ_BRACKET
                    sub edi,48
                    sub eax,3
                    mov edx,1 ; v2.27 - added: [foo(&[..])+rcx].class.method()
                    .repeat
                        .if [edi].asmtok.token == T_OP_SQ_BRACKET
                            dec edx
                            .break .ifz
                        .elseif [edi].asmtok.token == T_CL_SQ_BRACKET
                            inc edx
                        .endif
                        sub edi,16
                        dec eax
                    .untilz
                    .endc .if [edi].asmtok.token != T_OP_SQ_BRACKET

                  .case edx == SYM_STACK
                  .case edx == SYM_INTERNAL
                  .case edx == SYM_EXTERNAL
                  .case [eax].asym.flag & SFL_ISPROC
                    mov ecx,T_HLL_PROC
                    inc _brachets
                    mov _cstring,'"'
                    .endc

                  .case edx == SYM_UNDEFINED
                    mov edx,[esi].input
                    .endc .if BYTE PTR [edx+1] != ')'
                    mov ecx,T_HLL_PROC
                    .endc
                .endsw

                or [edi].asmtok.hll_flags,cl

            .else
                mov edi,[esi].input
                .if BYTE PTR [edi+1] == ')' ;&& [ebx-32].token == T_DIRECTIVE
                    ;
                    ; undefined code label..
                    ;
                    ; label() or .if label()
                    ; ...
                    ; label:
                    ;
                    or [ebx-16].hll_flags,T_HLL_PROC
                .endif
            .endif
            mov edi,[esi].input
            mov eax,[edi]
        .endif
        ;
        ; no break
        ;
      .case ')'
        .if al == ')' && _brachets

            dec _brachets
            mov _cstring,0
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
        inc [esi].input
        mov [ebx].token,al
        mov [ebx].specval,0 ; initialize, in case the token needs extra data
        movzx   eax,al      ; v2.06: use constants for the token string
        sub al,'('
        lea eax,stokstr1[eax*2]
        mov [ebx].string_ptr,eax
        .endc

      .case '[' ; T_OP_SQ_BRACKET operator - needs a matching ']' (0x5B)
      .case ']' ; T_CL_SQ_BRACKET (0x5D)

        inc [esi].input
        mov [ebx].token,al
        movzx   eax,al
        sub al,'['
        lea eax,stokstr2[eax*2]
        mov [ebx].string_ptr,eax
        .endc

      .case '=' ; (0x3D)

        .if ah != '='

            mov [ebx].token,T_DIRECTIVE
            mov [ebx].tokval,T_EQU
            mov [ebx].dirtype,DRT_EQUALSGN ;  to make it differ from EQU directive
            lea eax,__equ
            mov [ebx].string_ptr,eax
            inc [esi].input
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
        mov edx,eax
        strchr( "=!<>&|", eax )

        .if eax && [esi].flags2 & DF_CEXPR

            mov al,[eax]
            mov ecx,[esi].output
            inc [esi].output
            mov [ecx],al
            inc [esi].input
            mov [ebx].stringlen,1
            mov edx,[esi].input
            .if al == '&' || al == '|'

                .if [edx] == al

                    add ecx,1
                    mov [ecx],al
                    inc [esi].output
                    inc [esi].input
                    mov [ebx].stringlen,2
                    ;
                    ; v2.24 proc( &arg )
                    ;
                .elseif al == '&' && \
                   ([ebx-16].token == T_COMMA || [ebx-16].token == T_OP_BRACKET)
                    mov [ebx].token,al
                    lea eax,__amp
                    mov [ebx].string_ptr,eax
                    .endc
                .endif
            .elseif BYTE PTR [edx] == '='

                add ecx,1
                mov BYTE PTR [ecx],'='
                inc [esi].output
                inc [esi].input
                mov [ebx].stringlen,2
            .endif
            xor eax,eax
            mov [ebx].token,T_STRING
            mov [ebx].string_delim,al
            mov [ecx+1],al
            inc [esi].output
            .endc
        .endif

        .if dl == '&'   ; v2.08: ampersand is a special token

            inc [esi].input
            mov [ebx].token,dl
            lea eax,__amp
            mov [ebx].string_ptr,eax
            .endc
        .endif
        ;
        ; anything we don't recognise we will consider a string,
        ; delimited by space characters, commas, newlines or nulls
        ;
        get_string( ebx, esi )
        jmp toend
    .endsw

    xor eax,eax
toend:
    ret
get_special_symbol endp

get_number proc fastcall uses esi edi ebx buf:ptr asmtok, p:ptr line_status

    mov ebx,buf
    mov esi,p
    mov edx,[esi].input
    xor edi,edi

ifdef CHEXPREFIX
    push ebp
    movzx ebp,WORD PTR [edx]
    or ebp,00002000h
    .if ebp == 'x0'
        add edx,2
    .endif
endif

    ALIGN 4
    ;
    ; Read numbers 0..9 and a..f
    ;
    .while 1
        movzx ecx,BYTE PTR [edx]
        sub ecx,'A'             ; tolower(ecx)
        cmp ecx,'Z' - 'A' + 1
        sbb eax,eax
        and eax,'a' - 'A'
        add ecx,eax
        add ecx,'A'
        cmp ecx,'a'             ; break if cl > '0' && cl < 'a'
        sbb eax,eax
        cmp ecx,'9' + 1
        adc eax,0
        .break .if !ZERO?
        cmp ecx,'f' + 1         ; 'a'..'f' --> 10..15
        sbb eax,eax
        cmp ecx,'a'
        adc eax,0
        and eax,'a' - '9' - 1
        sub ecx,eax
        .break .if ecx < '0'    ; validate --> 0..15
        .break .if ecx > '0' + 15
        sub ecx,'0'
        mov eax,1
        shl eax,cl
        or  edi,eax
        add edx,1
    .endw

    mov eax,ecx
    mov ecx,edx
ifdef   CHEXPREFIX
    .if ebp == 'x0'
        mov eax,16
        .if !edi
            xor eax,eax
        .endif
    .else
endif

    .switch eax

      .case '.'
        ;
        ; valid floats look like: (int)[.(int)][e(int)]
        ; Masm also allows hex format, terminated by 'r' (3F800000r)
        ;
        xor edi,edi
        mov eax,1
        .while al

            mov al,[edx]
            .if eax == '.'
                add ah,1
            .elseif al < '0' || al > '9'
                or al,20h
                .break .if al != 'e'
                .break .if edi
                mov edi,1
                ;
                ; accept e+2 / e-4 /etc.
                ;
                mov al,[edx+1]
                .if al == '+' || al == '-'
                    add edx,1
                .endif
            .endif
            add edx,1
        .endw
        mov [ebx].token,T_FLOAT
        mov [ebx].floattype,0
        jmp number_done

      .case 'r'

        mov [ebx].token,T_FLOAT
        mov [ebx].floattype,'r'
        inc edx
        jmp number_done

      .case 'h'

        mov eax,16
        inc edx
        .endc

      .case 'y'

        xor eax,eax
        .endc .if !(edi & 3)
        mov eax,2
        inc edx
        .endc

      .case 't'

        xor eax,eax
        .endc .if !(edi & 03FFh)
        mov eax,10
        inc edx
        .endc

      .case 'q'
        .if !( edi & 0x00FF )
            mov [ebx].token,T_FLOAT
            mov [ebx].floattype,'q'
            inc edx
            jmp number_done
        .endif

      .case 'o'

        xor eax,eax
        .endc .if !( edi & 0x00FF )
        mov eax,8
        inc edx
        .endc

      .default

        mov cl,ModuleInfo.radix
        mov eax,1
        shl eax,cl
        dec edx
        mov cl,[edx]
        or  cl,20h

        .if (cl == 'b' || cl == 'd') && edi >= eax

            mov eax,[esi].input
            mov ch,'1'

            .if cl != 'b'
                mov ch,'9'
            .endif
            .while  eax < edx && BYTE PTR [eax] <= ch
                add eax,1
            .endw
            .if eax == edx
                mov eax,2
                .if cl != 'b'
                    mov eax,10
                .endif
                mov ecx,edx
                add edx,1
                .endc
            .endif
        .endif

        inc edx
        mov cl,ModuleInfo.radix
        mov eax,1
        shl eax,cl
        cmp edi,eax
        mov eax,0
        mov ecx,edx
        .endc .if !CARRY?
        movzx eax,ModuleInfo.radix
    .endsw
ifdef CHEXPREFIX
    .endif
endif
    .if eax
        mov [ebx].token,T_NUM
        mov [ebx].numbase,al
        sub ecx,[esi].input
        mov [ebx].itemlen,ecx
    .else
        mov [ebx].token,T_BAD_NUM
        movzx eax,BYTE PTR [edx]
        .while _ltype[eax+1] & _LABEL or _DIGIT
            add edx,1
            mov al,[edx]
        .endw
    .endif

number_done:
    mov ecx,edx
    mov edx,esi
    mov edi,[edx].line_status.output
    mov esi,[edx].line_status.input
    sub ecx,esi
    rep movsb
    xor eax,eax
    mov [edi],al
    add edi,1
    mov [edx].line_status.input,esi
    mov [edx].line_status.output,edi
toend:
ifdef CHEXPREFIX
    pop ebp
endif
    ret
get_number ENDP

    assume edx:ptr line_status

get_id_in_backquotes proc fastcall uses esi edi ebx buf:ptr asmtok, p:ptr line_status

    mov ebx,buf
    inc [edx].input
    mov esi,[edx].input
    mov edi,[edx].output
    mov [ebx].token,T_ID
    mov [ebx].idarg,0

    .repeat

        mov al,[esi]

        .while al != '`'

            .if !al || al == ';'

                mov byte ptr [edi],0
                asmerr( 2046 )
                .break(1)
            .endif
            lodsb
            stosb
            inc [edx].input
        .endw

        inc [edx].input
        xor eax,eax
        stosb
        mov [edx].output,edi
    .until 1
    ret

get_id_in_backquotes endp

get_id proc fastcall uses esi edi ebx buf:ptr asmtok, p:ptr line_status

    mov ebx,buf
    mov esi,[edx].input
    mov edi,[edx].output
    mov [ebx].bytval,0 ; added v2.27

    mov eax,[esi]

    .repeat

        .if ax == '"L' && _brachets

            stosb
            inc [edx].input
            inc [edx].output
            get_string( ebx, p )
            .break
        .endif

        movzx eax,al
        .repeat
            mov [edi],al
            add edi,1
            add esi,1
            mov al,[esi]
        .until !(_ltype[eax+1] & _LABEL or _DIGIT)

        mov ecx,edi
        sub ecx,[edx].output

        .if ecx > MAX_ID_LEN

            asmerr( 2043 )
            mov edi,[edx].output
            add edi,MAX_ID_LEN
        .endif

        mov BYTE PTR [edi],0
        add edi,1
        mov eax,[edx].output
        mov al,[eax]

        .if ecx == 1 && al == '?'

            mov [edx].input,esi
            mov [ebx].token,T_QUESTION_MARK
            mov [ebx].string_ptr,offset __quest
            .break
        .endif

        push edx
        mov  edx,[edx].output
        xchg edx,ecx
        call FindResWord
        pop  edx

        .if !eax

            mov eax,[edx].output
            mov al,[eax]
            .if al == '.' && !ModuleInfo.dotname

                mov [ebx].token,T_DOT
                lea eax,stokstr1[('.' - '(') * 2]
                mov [ebx].string_ptr,eax
                inc [edx].input
                .break
            .endif
            mov [edx].input,esi
            mov [edx].output,edi
            mov [ebx].token,T_ID
            mov [ebx].idarg,0
            .break
        .endif

        mov [edx].input,esi
        mov [edx].output,edi

        .switch eax
          .case T_SYSCALL       ; v2.24 hack for syscall..
            .if ![edx].index
                mov eax,T_SYSCALL_
            .endif
            .endc
          .case T_DOT_ELSEIF
          .case T_DOT_WHILE
          .case T_DOT_CASE
            mov [ebx].hll_flags,T_HLL_DELAY
            .endc
        .endsw
        mov [ebx].tokval,eax

        .if eax >= SPECIAL_LAST

            .if ModuleInfo.m510

                mov eax,[ebx].tokval
                sub eax,SPECIAL_LAST
                movzx eax,optable_idx[eax*2]
                movzx ecx,InstrTable[eax*sizeof(instr_item)].cpu
                mov eax,ecx
                and eax,P_CPU_MASK
                and ecx,P_EXT_MASK
                mov edi,ModuleInfo.curr_cpu
                mov esi,edi
                and edi,P_CPU_MASK
                and esi,P_EXT_MASK

                .if eax > edi || ecx > esi

                    mov [ebx].token,T_ID
                    mov [ebx].idarg,0
                    .break
                .endif
            .endif
            mov [ebx].token,T_INSTRUCTION
            .break
        .endif

        mov ecx,edx
        mov edx,sizeof(special_item)
        mov eax,[ebx].tokval
        mul edx
        mov edx,ecx
        mov esi,eax
        mov al,SpecialTable[esi].bytval
        mov [ebx].bytval,al
        movzx eax,SpecialTable[esi]._type

        .switch eax
          .case RWT_REG
            mov ecx,T_REG
            .endc
          .case RWT_DIRECTIVE
            mov ecx,T_DIRECTIVE
            .endc   .if [edx].flags2
            mov eax,SpecialTable[esi].value
            mov [edx].flags2,al
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
            mov [ebx].idarg,0
        .endsw
        mov [ebx].token,cl
    .until 1
    xor eax,eax
    ret
get_id endp

;
; save symbols in IFDEF's so they don't get expanded
;
StartComment proc fastcall p:LPSTR

    mov eax,p
    .if M_EAT_SPACE( ecx, eax )

        mov ModuleInfo.inside_comment,cl
        add eax,1
        .if strchr( eax, ecx )

            mov ModuleInfo.inside_comment,0
        .endif
        ret
    .else
        asmerr( 2110 )
    .endif
    ret
StartComment endp

    option proc:public
    assume esi:nothing

GetToken proc fastcall tokenarray:ptr asmtok, p:ptr line_status
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
    mov [ecx].asmtok.hll_flags,0
    mov eax,[edx].input
    movzx eax,BYTE PTR [eax]

    .switch

      .case BYTE PTR _ltype[eax+1] & _DIGIT
        jmp get_number

      .case _ltype[eax+1] & _LABEL
        jmp get_id

      .case al == '`'
        .endc .if Options.strict_masm_compat
        jmp get_id_in_backquotes

      .case al == '.'

        mov eax,[edx].input
        movzx eax,BYTE PTR [eax+1]
        .endc .if !( _ltype[eax+1] & _LABEL or _DIGIT )

        movzx eax,[ecx-16].asmtok.token
        .if ![edx].index || \
            (eax != T_REG && eax != T_CL_BRACKET && eax != T_CL_SQ_BRACKET && eax != T_ID)

            jmp get_id
        .endif
        ;
        ; added v2.29 for .break(n) and .continue(n)
        ;
        .if (eax == T_CL_BRACKET && [ecx-48].asmtok.token == T_OP_BRACKET)

            .if ( [ecx-64].asmtok.tokval == T_DOT_BREAK || \
                  [ecx-64].asmtok.tokval == T_DOT_CONTINUE )
                jmp get_id
            .endif
        .endif
    .endsw

    jmp get_special_symbol
toend:
    ret
GetToken ENDP

Tokenize PROC USES esi edi ebx line:LPSTR, start:UINT, tokenarray:ptr asmtok, flags:UINT

  local rc, p:line_status
;
; create tokens from a source line.
; line:  the line which is to be tokenized
; start: where to start in the token buffer. If start == 0,
;    then some variables are additionally initialized.
; flags: 1=if the line has been tokenized already.
;
    mov eax,line
    mov p.input,eax
    mov p.start,eax
    mov eax,flags
    mov p.flags,al
    mov eax,start
    mov p.index,eax
    mov p.flags2,0
    mov p.flags3,0
    mov _cstring,0
    mov _brachets,0

    .if !eax

        mov eax,token_stringbuf
        mov p.output,eax
        .if ModuleInfo.inside_comment

            .if strchr( line, ModuleInfo.inside_comment )

                mov ModuleInfo.inside_comment,0
            .endif
            jmp skipline
        .endif
    .else
        mov eax,ModuleInfo.stringbufferend
        mov p.output,eax
    .endif

    .while 1

        mov eax,p.input
        M_SKIP_SPACE ecx, eax
        mov edx,eax
        mov p.input,eax

        .if ecx == ';' && flags == TOK_DEFAULT

            .while edx > line
                movzx eax,BYTE PTR [edx-1]
                .break .if !BYTE PTR _ltype[eax+1] & _SPACE
                sub edx,1
            .endw

            mov p.input,edx
            strcpy( commentbuffer, edx )
            mov ModuleInfo.CurrComment,eax
            mov BYTE PTR [edx],0
        .endif

        mov ebx,p.index
        shl ebx,4
        add ebx,tokenarray
        mov [ebx].tokpos,edx

        .if BYTE PTR [edx] == 0
            ;
            ; if a comma is last token, concat lines ... with some exceptions
            ; v2.05: moved from PreprocessLine(). Moved because the
            ; concatenation may be triggered by a comma AFTER expansion.
            ;
            .if p.index > 1 && \
                ([ebx-16].token == T_COMMA || _brachets) && \
                ( Parse_Pass == PASS_1 || !UseSavedState ) && !start

                .if IsMultiLine( tokenarray ) || _brachets

                    strlen( p.output )
                    add eax,4
                    and eax,-4
                    add eax,p.output
                    mov edi,eax

                    .if GetTextLine(eax)

                        .if M_EAT_SPACE(eax, edi)

                            strcpy( p.input, edi )

                            .if strlen( p.start ) >= MAX_LINE_LEN

                                asmerr( 2039 )
                                mov eax,start
                                mov p.index,eax
                                .break
                            .endif
                            .continue
                        .endif
                    .endif
                .endif
            .endif
            .break
        .endif

        mov eax,p.output
        mov [ebx].string_ptr,eax
        GetToken( ebx, &p )
        mov rc,eax

        .switch
          .case eax == EMPTY
            .continue

          .case eax == ERROR
            ;
            ; skip this line
            ;
            mov eax,start
            mov p.index,eax
            .break

          .case [ebx].token == T_DBL_COLON
            mov eax,tokenarray
            or [eax].asmtok.hll_flags,T_HLL_DBLCOLON
            .endc
        .endsw

        ;
        ; v2.04: this has been moved here from condasm.c to
        ; avoid problems with (conditional) listings. It also
        ; avoids having to search for the first token twice.
        ; Note: a conditional assembly directive within an
        ;   inactive block and preceded by a label isn't detected!
        ;   This is an exact copy of the Masm behavior, although
        ;   it probably is just a bug!
        ;
        .if !(flags & TOK_RESCAN)

            mov eax,tokenarray
            movzx ecx,[eax+16].asmtok.token
            mov eax,p.index

            .if !eax || (eax == 2 && (ecx == T_COLON || ecx == T_DBL_COLON))

                mov ecx,[ebx].tokval
                .if [ebx].token == T_DIRECTIVE && \
                    ([ebx].bytval == DRT_CONDDIR || ecx == T_DOT_ASSERT)

                    .if ecx == T_COMMENT
                        ;
                        ; p.index is 0 or 2
                        ;
                        StartComment( p.input )
                        .break
                    .endif

                    .if ecx == T_DOT_ASSERT

                        test ModuleInfo.xflag,_XF_ASSERT
                        jnz @F
                        mov eax,p.input
                        M_SKIP_SPACE ecx, eax
                        cmp cl,':'
                        jne @F
                        inc eax
                        M_SKIP_SPACE ecx, eax
                        mov eax,[eax]
                        or  eax,20202020h
                        cmp eax,'sdne'
                        jne @F
                        mov ecx,T_ENDIF
                    .endif

                    conditional_assembly_prepare( ecx )
                    .if CurrIfState != BLOCK_ACTIVE
                        ;
                        ; p.index is 1 or 3
                        ;
                        inc p.index
                        .break
                    .endif

                .else
                @@:
                    .if CurrIfState != BLOCK_ACTIVE
                        ;
                        ; further processing skipped. p.index is 0
                        ;
                        .break
                    .endif
                .endif
            .endif
        .endif

        inc p.index
        .if p.index >= MAX_TOKEN

            asmerr( 2141 )
            mov eax,start
            mov p.index,eax
            jmp skipline
        .endif

        mov eax,p.output
        sub eax,token_stringbuf
        add eax,4
        and eax,-4
        add eax,token_stringbuf
        mov p.output,eax

    .endw

    mov eax,p.output
    sub eax,token_stringbuf
    add eax,4
    and eax,-4
    add eax,token_stringbuf
    mov p.output,eax
    mov ModuleInfo.stringbufferend,eax

skipline:
    mov ebx,tokenarray
    mov eax,p.index
    shl eax,4
    add ebx,eax
    mov [ebx].token,T_FINAL
    mov al,p.flags3
    mov [ebx].bytval,al
    mov [ebx].string_ptr,offset __null
    mov eax,p.index
    ret
Tokenize ENDP

    END
