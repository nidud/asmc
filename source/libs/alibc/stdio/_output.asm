; _OUTPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include limits.inc
include string.inc
include fltintrn.inc

BUFFERSIZE      equ 512     ; ANSI-specified minimum is 509

FL_SIGN         equ 0x0001  ; put plus or minus in front
FL_SIGNSP       equ 0x0002  ; put space or minus in front
FL_LEFT         equ 0x0004  ; left justify
FL_LEADZERO     equ 0x0008  ; pad with leading zeros
FL_LONG         equ 0x0010  ; long value given
FL_SHORT        equ 0x0020  ; short value given
FL_SIGNED       equ 0x0040  ; signed data given
FL_ALTERNATE    equ 0x0080  ; alternate form requested
FL_NEGATIVE     equ 0x0100  ; value is negative
FL_FORCEOCTAL   equ 0x0200  ; force leading '0' for octals
FL_LONGDOUBLE   equ 0x0400  ; long double
FL_WIDECHAR     equ 0x0800
FL_LONGLONG     equ 0x1000  ; long long or REAL16 value given
FL_I64          equ 0x8000  ; 64-bit value given

ST_NORMAL       equ 0       ; normal state; outputting literal chars
ST_PERCENT      equ 1       ; just read '%'
ST_FLAG         equ 2       ; just read flag character
ST_WIDTH        equ 3       ; just read width specifier
ST_DOT          equ 4       ; just read '.'
ST_PRECIS       equ 5       ; just read precision specifier
ST_SIZE         equ 6       ; just read size specifier
ST_TYPE         equ 7       ; just read type specifier

externdef __lookuptable:byte

    .code

write_char proc private uses rbx char:SINT, fp:LPFILE, pNumWritten:LPWORD

    mov rbx,rdx
    .if fputc(edi, rsi) == -1
        mov [rbx],eax
    .else
        inc DWORD PTR [rbx]
    .endif
    ret

write_char endp

write_string proc private uses rbx r12 r13 r14 string:LPSTR, len:UINT, fp:LPFILE, pNumwritten:LPWORD

    .fors ( r13 = rdi,
            ebx = esi,
            r12 = rdx,
            r14 = rcx : ebx > 0 : ebx-- )

        movzx edi,byte ptr [r13]
        inc r13
        .ifd fputc(edi, r12) == -1
            mov [r14],eax
            .break
        .endif
        inc dword ptr [r14]
    .endf
    ret

write_string endp

write_multi_char proc private uses rbx r12 r13 r14 char:SINT, num:UINT, fp:LPFILE, pNumWritten:PVOID

    .fors ( r14d = edi,
            ebx = esi,
            r12 = rdx,
            r13 = rcx : ebx > 0 : ebx-- )

        .ifd fputc(r14d, r12) == -1
            mov [r13],eax
            .break
        .endif
        inc dword ptr [r13]
    .endf
    ret

write_multi_char endp

_output proc public uses rbx r12 r13 r14 r15 fp:LPFILE, format:string_t, arglist:ptr

  local charsout            : int_t,
        hexoff              : uint_t,
        state               : uint_t,
        curadix             : uint_t,
        prefix[2]           : uchar_t,
        textlen             : uint_t,
        prefixlen           : uint_t,
        no_output           : uint_t,
        fldwidth            : uint_t,
        bufferiswide        : uint_t,
        padding             : uint_t,
        text                : string_t,
        mbuf[MB_LEN_MAX+1]  : wint_t,
        buffer[BUFFERSIZE]  : char_t,
        floattype           : char_t

    mov r15,rsi

    mov r14d,[rdx]
    mov ebx,[rdx+4]
    add r14,[rdx+16]
    add rbx,[rdx+16]

    xor eax,eax
    mov textlen,eax
    mov charsout,eax
    mov state,eax
    mov bufferiswide,eax

    .while 1

        lea   rcx,__lookuptable
        movzx eax,BYTE PTR [r15]
        inc   r15
        mov   edx,eax

        .break .if ( !eax || charsout > INT_MAX )

        .if ( eax >= ' ' && eax <= 'x' )

            mov al,[rcx+rax-32]
            and eax,15
        .else
            xor eax,eax
        .endif

        shl eax,3
        add eax,state
        mov al,[rcx+rax]
        shr eax,4
        and eax,0x0F
        mov state,eax

        .if ( eax <= 7 )

            .switch eax

              .case ST_NORMAL
                mov bufferiswide,0
                mov edi,edx
                write_char(edi, fp, &charsout)
               .endc

              .case ST_PERCENT
                xor eax,eax
                mov no_output,eax
                mov fldwidth,eax
                mov prefixlen,eax
                mov bufferiswide,eax
                xor r12d,r12d ; flags
                mov r13d,-1   ; precision
               .endc

              .case ST_FLAG
                movzx eax,dl
                .switch pascal eax
                  .case '+': or r12d,FL_SIGN      ; '+' force sign indicator
                  .case ' ': or r12d,FL_SIGNSP    ; ' ' force sign or space
                  .case '#': or r12d,FL_ALTERNATE ; '#' alternate form
                  .case '-': or r12d,FL_LEFT      ; '-' left justify
                  .case '0': or r12d,FL_LEADZERO  ; '0' pad with leading zeros
                .endsw
                .endc

              .case ST_WIDTH
                .if ( dl == '*' )

                    mov rax,r14
                    add r14,8
                    mov eax,[rax]

                    .ifs ( eax < 0 )

                        or  r12d,FL_LEFT
                        neg eax
                    .endif
                    mov fldwidth,eax

                .else

                    movsx edx,dl
                    imul eax,fldwidth,10
                    add eax,edx
                    add eax,-48
                    mov fldwidth,eax
                .endif
                .endc

              .case ST_DOT
                xor r13d,r13d
               .endc

              .case ST_PRECIS
                .if ( dl == '*' )

                    mov  rax,r14
                    add  r14,8
                    mov  r13d,[rax]
                    .ifs r13d < 0
                        mov r13d,-1
                    .endif
                .else
                    imul eax,r13d,10
                    movsx r13d,dl
                    add r13d,eax
                    add r13d,-48
                .endif
                .endc

              .case ST_SIZE

                .switch edx

                  .case 'l'

                    .if !(r12d & FL_LONG)

                        or r12d,FL_LONG
                       .endc
                    .endif

                    ; case ll => long long

                    and r12d,NOT FL_LONG
                    or  r12d,FL_LONGLONG
                   .endc

                  .case 'L'
                    or  r12d,FL_LONGDOUBLE or FL_I64
                   .endc

                  .case 'I'
                    mov cx,[r15]
                    .switch cl
                    .case '6'
                        .gotosw(2:ST_NORMAL) .if ch != '4'
                        or  r12d,FL_I64
                        add r15,2
                        .endc

                    .case '3'
                        .gotosw(2:ST_NORMAL) .if ch != '2'
                        and r12d,not FL_I64
                        add r15,2
                        .endc

                    .case 'd','i','o','u','x','X'
                        .endc
                    .default
                        .gotosw(2:ST_NORMAL)
                    .endsw
                    .endc

                .case 'h'
                    or r12d,FL_SHORT
                   .endc
                .case 'w'
                    or r12d,FL_WIDECHAR  ; 'w' => wide character
                .endsw
                .endc

              .case ST_TYPE

                mov eax,edx

                .switch rax

                .case 'b'
                    mov rax,r14
                    add r14,8
                    mov edx,[rax]
                    xor ecx,ecx
                    bsr ecx,edx
                    inc ecx
                    mov textlen,ecx
                    lea r8,buffer
                    .repeat
                        xor eax,eax
                        shr edx,1
                        adc al,'0'
                        mov [r8+rcx-1],al
                    .untilcxz
                    mov text,r8
                   .endc

                .case 'C' ; ISO wide character
                    .if !( r12d & ( FL_SHORT or FL_LONG or FL_WIDECHAR ) )
                        ;
                        ; CONSIDER: non-standard
                        ;
                        or r12d,FL_WIDECHAR ; ISO std.
                    .endif

                .case 'c'
                    ;
                    ; print a single character specified by int argument
                    ;
                    mov rcx,r14
                    add r14,8
                    lea rax,buffer
                    mov textlen,1 ; print just a single character
                    mov text,rax
                    mov dl,[rcx]
                    mov [rax],dl

                    .endc

                .case 'S' ; ISO wide character string
                    .if !(r12d & ( FL_SHORT or FL_LONG or FL_WIDECHAR ) )

                        or r12d,FL_WIDECHAR
                    .endif
                .case 's'

                    ; print a string --
                    ; ANSI rules on how much of string to print:
                    ;   all if precision is default,
                    ;   min(precision, length) if precision given.
                    ; prints '(null)' if a null string is passed

                    mov rcx,r14
                    add r14,8
                    mov rax,[rcx]
                    mov ecx,r13d
                    .if r13d == -1
                        mov ecx,INT_MAX
                    .endif
                    .if !rax
                        lea rax,@CStr("(null)")
                        and r12d,not ( FL_LONG or FL_WIDECHAR )
                    .endif
                    mov text,rax

                    .if r12d & ( FL_LONG or FL_WIDECHAR )
                        mov bufferiswide,1
                        .repeat
                            .break .if WORD PTR [rax] == 0
                            add rax,2
                        .untilcxz
                    .else
                        .repeat
                            .break .if BYTE PTR [rax] == 0
                            inc rax
                        .untilcxz
                    .endif
                    sub rax,text
                    mov textlen,eax
                    .endc

                .case 'n'
                    mov rax,r14
                    add r14,8
                    mov rdx,[rax-8]
                    mov eax,charsout
                    mov [rdx],eax
                    .if r12d & FL_LONG
                        mov no_output,1
                    .endif
                    .endc

                .case 'E'
                .case 'G'
                .case 'A'
                    or  r12d,_ST_CAPEXP  ; capitalize exponent
                    add dl,'a' - 'A'    ; convert format char to lower
                    ;
                    ; DROP THROUGH
                    ;
                .case 'e'
                .case 'f'
                .case 'g'
                .case 'a'
                    ;
                    ; floating point conversion -- we call cfltcvt routines
                    ; to do the work for us.
                    ;
                    or  r12d,FL_SIGNED   ; floating point is signed conversion
                    lea rax,buffer      ; put result in buffer
                    mov text,rax
                    ;
                    ; compute the precision value
                    ;
                    .ifs r13d < 0
                        mov r13d,6       ; default precision: 6
                    .elseif !r13d && dl == 'g'
                        mov r13d,1       ; ANSI specified
                    .endif
                    mov rdi,rbx
                    add rbx,16
                    mov floattype,dl

                    mov r8d,r12d
                    and r8d,_ST_CAPEXP
                    ;
                    ; do the conversion
                    ;

                    .if ( r12d & FL_LONGDOUBLE )

                        or r8d,_ST_LONGDOUBLE
                        _cldcvt(rdi, text, edx, r13d, r8d)

                    .elseif ( r12d & FL_LONGLONG )

                        or r8d,_ST_QUADFLOAT
                        _cqcvt(rdi, text, edx, r13d, r8d)
                    .else

                        or r8d,_ST_DOUBLE
                        _cfltcvt(rdi, text, edx, r13d, r8d)
                    .endif
                    ;
                    ; '#' and precision == 0 means force a decimal point
                    ;
                    .if ( ( r12d & FL_ALTERNATE ) && !r13d )

                        _forcdecpt(text)
                    .endif
                    ;
                    ; 'g' format means crop zero unless '#' given
                    ;
                    .if ( floattype == 'g' && !( r12d & FL_ALTERNATE ) )

                        _cropzeros(text)
                    .endif
                    ;
                    ; check if result was negative, save '-' for later
                    ; and point to positive part (this is for '0' padding)
                    ;
                    mov rcx,text
                    mov al,[rcx]
                    .if al == '-'

                        or  r12d,FL_NEGATIVE
                        inc text
                    .endif
                    strlen(text) ; compute length of text
                    mov textlen,eax
                   .endc

                .case 'd'
                .case 'i'
                    ;
                    ; signed decimal output
                    ;
                    or  r12d,FL_SIGNED
                .case 'u'
                    mov curadix,10
                    jmp COMMON_INT

                .case 'p'
                    ;
                    ; write a pointer -- this is like an integer or long
                    ; except we force precision to pad with zeros and
                    ; output in big hex.
                    ;
                    mov r13d,size_t * 2
                    or  r12d,FL_I64
                    ;
                    ; DROP THROUGH to hex formatting
                    ;
                .case 'X' ; unsigned upper hex output
                    ;
                    ; set hexadd for uppercase hex
                    ;
                    mov hexoff,'A'-'9'-1
                    jmp COMMON_HEX

                .case 'x'
                    ;
                    ; unsigned lower hex output
                    ;
                    mov hexoff,'a'-'9'-1
                    ;
                    ; DROP THROUGH TO COMMON_HEX
                    ;
                    COMMON_HEX:

                    mov curadix,16
                    .if r12d & FL_ALTERNATE
                        ;
                        ; alternate form means '0x' prefix
                        ;
                        mov eax,'x' - 'a' + '9' + 1
                        add eax,hexoff
                        mov prefix,'0'
                        mov prefix[1],al
                        mov prefixlen,2
                    .endif
                    jmp COMMON_INT

                .case 'o' ; unsigned octal output
                    mov curadix,8
                    .if r12d & FL_ALTERNATE
                        ;
                        ; alternate form means force a leading 0
                        ;
                        or r12d,FL_FORCEOCTAL
                    .endif
                    ;
                    ; DROP THROUGH to COMMON_INT
                    ;
                   COMMON_INT:
                    ;
                    ; This is the general integer formatting routine.
                    ; Basically, we get an argument, make it positive
                    ; if necessary, and convert it according to the
                    ; correct radix, setting text and textlen
                    ; appropriately.
                    ;
                    mov eax,[r14]
                    .if r12d & (FL_I64 or FL_LONGLONG)
                        mov rax,[r14]
                    .endif
                    add r14,8

                    xor edx,edx
                    .if r12d & FL_SHORT

                        .if r12d & FL_SIGNED
                            ; sign extend
                            movsx rax,ax
                        .else   ; zero-extend
                            movzx rax,ax
                        .endif
                    .elseif r12d & FL_SIGNED
                        .if !(r12d & (FL_I64 or FL_LONGLONG))
                            test eax,eax
                            .ifs
                                dec rdx
                                shl rdx,32
                                or  rax,rdx
                                xor rdx,rdx
                            .endif
                        .endif
                        .ifs rax < rdx
                            or r12d,FL_NEGATIVE
                        .endif
                    .endif
                    ;
                    ; check precision value for default; non-default
                    ; turns off 0 flag, according to ANSI.
                    ;
                    .ifs r13d < 0
                        mov r13d,1 ; default precision
                    .else
                        and r12d,NOT FL_LEADZERO
                    .endif
                    ;
                    ; Check if data is 0; if so, turn off hex prefix
                    ;
                    .if !rax
                        mov prefixlen,eax
                    .endif
                    ;
                    ; Convert data to ASCII -- note if precision is zero
                    ; and number is zero, we get no digits at all.
                    ;
                    .if r12d & FL_SIGNED

                        test rax,rax
                        .ifs
                            neg rax
                            or  r12d,FL_NEGATIVE
                        .endif
                    .endif

                    lea rcx,buffer[BUFFERSIZE-1]
                    mov r9d,curadix
                    mov r8,rcx

                    .fors ( : rax || r13d > 0 : r13d-- )

                        xor edx,edx
                        div r9
                        add dl,'0'
                        .ifs dl > '9'
                            add dl,byte ptr hexoff
                        .endif
                        mov [rcx],dl
                        dec rcx
                    .endf

                    ; compute length of number

                    mov rax,r8
                    sub rax,rcx
                    inc rcx

                    ; text points to first digit now

                    ; Force a leading zero if FORCEOCTAL flag set

                    .if r12d & FL_FORCEOCTAL

                        .if byte ptr [rcx] != '0' || eax == 0
                            dec rdx
                            mov byte ptr [rcx],'0'
                            inc eax
                        .endif
                    .endif
                    mov text,rcx
                    mov textlen,eax
                .endsw
                ;
                ; At this point, we have done the specific conversion, and
                ; 'text' points to text to print; 'textlen' is length.   Now we
                ; justify it, put on prefixes, leading zeros, and then
                ; print it.
                ;
                .if !no_output
                    .if r12d & FL_SIGNED
                        .if r12d & FL_NEGATIVE
                            ; prefix is a '-'
                            mov prefix,'-'
                            mov prefixlen,1
                        .elseif r12d & FL_SIGN
                            ; prefix is '+'
                            mov prefix,'+'
                            mov prefixlen,1
                        .elseif r12d & FL_SIGNSP
                            ; prefix is ' '
                            mov prefix,' '
                            mov prefixlen,1
                        .endif
                    .endif
                    ;
                    ; calculate amount of padding -- might be negative,
                    ; but this will just mean zero
                    ;
                    mov eax,fldwidth
                    sub eax,textlen
                    sub eax,prefixlen
                    mov padding,eax
                    ;
                    ; put out the padding, prefix, and text, in the correct order
                    ;
                    .if !(r12d & (FL_LEFT or FL_LEADZERO))
                        ;
                        ; pad on left with blanks
                        ;
                        write_multi_char(' ', padding, fp, &charsout)
                    .endif
                    ;
                    ; write prefix
                    ;
                    write_string(&prefix, prefixlen, fp, &charsout)

                    .if (r12d & FL_LEADZERO) && !(r12d & FL_LEFT)
                        ;
                        ; write leading zeros
                        ;
                        write_multi_char('0', padding, fp, &charsout)
                    .endif

                    ; write text

                    write_string(text, textlen, fp, &charsout)
                    .if r12d & FL_LEFT

                        ; pad on right with blanks

                        write_multi_char(' ', padding, fp, &charsout)
                    .endif
                .endif
                ;
                ; we're done!
                ;
                .endc
            .endsw
        .endif
    .endw
    .return( charsout ) ; return value = number of characters written

_output endp

    end
