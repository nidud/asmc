; _TOUTPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include limits.inc
include wchar.inc
include fltintrn.inc
include winnls.inc
include tchar.inc

define BUFFERSIZE       512     ; ANSI-specified minimum is 509

define FL_SIGN          0x0001  ; put plus or minus in front
define FL_SIGNSP        0x0002  ; put space or minus in front
define FL_LEFT          0x0004  ; left justify
define FL_LEADZERO      0x0008  ; pad with leading zeros
define FL_LONG          0x0010  ; long value given
define FL_SHORT         0x0020  ; short value given
define FL_SIGNED        0x0040  ; signed data given
define FL_ALTERNATE     0x0080  ; alternate form requested
define FL_NEGATIVE      0x0100  ; value is negative
define FL_FORCEOCTAL    0x0200  ; force leading '0' for octals
define FL_LONGDOUBLE    0x0400  ; long double
define FL_WIDECHAR      0x0800
define FL_LONGLONG      0x1000  ; long long or REAL16 value given
define FL_I64           0x8000  ; 64-bit value given
define FL_PTRSIZE       0x10000 ; platform dependent number
define FL_CHAR          0x20000 ; hh - int-size arg from char

define ST_NORMAL        0       ; normal state; outputting literal chars
define ST_PERCENT       1       ; just read '%'
define ST_FLAG          2       ; just read flag character
define ST_WIDTH         3       ; just read width specifier
define ST_DOT           4       ; just read '.'
define ST_PRECIS        5       ; just read precision specifier
define ST_SIZE          6       ; just read size specifier
define ST_TYPE          7       ; just read type specifier

ifdef FORMAT_VALIDATIONS
define NUMSTATES        (ST_INVALID + 1)
else
define NUMSTATES        (ST_TYPE + 1)
endif

externdef __lookuptable:byte

    .code

write_char proc private uses rbx c:int_t, fp:LPFILE, pnumwritten:ptr int_t

    ldr rbx,pnumwritten
    ldr rdx,fp
    ldr ecx,c

    .if ( ( [rdx]._iobuf._flag & _IOSTRG ) && [rdx]._iobuf._base == NULL )

        mov eax,1
        add [rbx],eax

    .elseifd ( _fputtc( ecx, rdx ) == -1 )

        mov rdx,fp
        .if ( [rdx]._iobuf._flag & _IOSNPRINTF )

            mov eax,[rbx]
            inc eax
        .endif
        mov [rbx],eax
    .else
        inc int_t ptr [rbx]
    .endif
    ret

write_char endp

write_string proc private uses rbx string:LPTSTR, len:SINT, fp:LPFILE, pnumwritten:ptr int_t

    ldr rbx,string
    .for ( : len > 0 : len-- )

        movzx ecx,TCHAR ptr [rbx]
        add rbx,TCHAR

       .break .ifd ( write_char( ecx, fp, pnumwritten ) == -1 )
    .endf
    ret

write_string endp

write_multi_char proc private c:SINT, num:SINT, fp:LPFILE, pnumwritten:ptr int_t

    .for ( : num > 0 : num-- )

       .break .ifd ( write_char( c, fp, pnumwritten ) == -1 )
    .endf
    ret

write_multi_char endp


_va_arg macro ap
if defined(__UNIX__) and defined(_AMD64_)
    dec argcnt
    .ifz
        mov ap,r13
    .endif
endif
    mov rax,ap
    add ap,size_t
    retm<[rax]>
    endm

ifdef _WIN64
ifdef __UNIX__
_toutput proc uses rbx r12 r13 r14 r15 fp:LPFILE, format:LPTSTR, argptr:ptr
define flags        <r14d>
define precision    <r15d>
define arglist      <r12>
   .new argxmm      : ptr
   .new argcnt      : int_t     ; regargs + 1
else
_toutput proc uses rsi rdi rbx r12 fp:LPFILE, format:LPTSTR, argptr:ptr
define flags        <edi>
define precision    <esi>
define arglist      <r12>
endif
else
_toutput proc uses esi edi ebx fp:LPFILE, format:LPTSTR, arglist:ptr
define flags        <edi>
define precision    <esi>
endif

   .new charsout            : int_t = 0
   .new hexoff              : uint_t
   .new state               : uint_t = 0
   .new curadix             : uint_t
   .new prefix[2]           : TCHAR
   .new textlen             : uint_t = 0
   .new prefixlen           : uint_t
   .new no_output           : uint_t
   .new fldwidth            : uint_t
   .new bufferiswide        : uint_t = 0
   .new padding             : uint_t
   .new text                : LPTSTR
   .new mbuf[MB_LEN_MAX+1]  : wint_t
   .new buffer[BUFFERSIZE]  : TCHAR

ifdef _WIN64
ifdef __UNIX__
    mov eax,[rdx]
    mov ecx,[rdx+4]
    add rax,[rdx+16]
    add rcx,[rdx+16]
    mov arglist,rax
    mov argxmm,rcx
    mov r13,[rdx+8]
    mov ecx,7
    mov eax,[rdx]
    shr eax,3
    sub ecx,eax
    mov argcnt,ecx
else
    mov arglist,r8
endif
endif

    .while 1

        lea   rcx,__lookuptable
        mov   rax,format
        add   format,TCHAR
        movzx eax,TCHAR ptr [rax]
        mov   edx,eax

        .break .if ( !eax || charsout > INT_MAX )

        .if ( eax >= ' ' && eax <= 'z' )

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
                mov bufferiswide,TCHAR-1
                mov ecx,edx
if not defined(__UNIX__) and not defined(_UNICODE)
                .if isleadbyte( ecx )

                    write_char( ecx, fp, &charsout )

                    mov rax,format
                    inc format
                    movzx ecx,BYTE PTR [rax]
                .endif
endif
                write_char( ecx, fp, &charsout )
               .endc

            .case ST_PERCENT
                xor eax,eax
                mov no_output,eax
                mov fldwidth,eax
                mov prefixlen,eax
                mov bufferiswide,eax
                mov flags,eax
                mov precision,-1
               .endc

            .case ST_FLAG
                .switch pascal edx
                .case '+': or flags,FL_SIGN      ; '+' force sign indicator
                .case ' ': or flags,FL_SIGNSP    ; ' ' force sign or space
                .case '#': or flags,FL_ALTERNATE ; '#' alternate form
                .case '-': or flags,FL_LEFT      ; '-' left justify
                .case '0': or flags,FL_LEADZERO  ; '0' pad with leading zeros
                .endsw
                .endc

            .case ST_WIDTH
                .if ( edx == '*' )

                    mov eax,_va_arg(arglist)
                    .ifs ( eax < 0 )
                        or  flags,FL_LEFT
                        neg eax
                    .endif
                    mov fldwidth,eax

                .else

                    movsx edx,dl
                    imul  eax,fldwidth,10
                    add   eax,edx
                    add   eax,-48
                    mov   fldwidth,eax
                .endif
                .endc

            .case ST_DOT
                mov precision,0
               .endc

            .case ST_PRECIS
                mov ecx,precision
                .if ( edx == '*' )

                    mov ecx,_va_arg(arglist)
                    .ifs ( ecx < 0 )
                        mov ecx,-1
                    .endif
                .else
                    imul  eax,ecx,10
                    movsx ecx,dl
                    add   ecx,eax
                    add   ecx,-48
                .endif
                mov precision,ecx
               .endc

            .case ST_SIZE

                .switch edx
                .case 'l'
                    .if ( !( flags & FL_LONG ) )
                        or flags,FL_LONG
                       .endc
                    .endif

                    ; case ll => long long

                    and flags,NOT FL_LONG
                    or  flags,FL_LONGLONG
                   .endc

                .case 'L'
                    or  flags,FL_LONGDOUBLE or FL_I64
                   .endc

                .case 'I'
ifdef _WIN64
                    or  flags,FL_I64 ; 'I' => __int64 on WIN64 systems
endif
                    mov rax,format
                    movzx ecx,TCHAR ptr [rax]
                    .switch ecx
                    .case '6'
                        .if ( TCHAR ptr [rax+TCHAR] != '4' )
                            .gotosw(2:ST_NORMAL)
                        .endif
                        or  flags,FL_I64
                        add rax,2*TCHAR
                        mov format,rax
                       .endc
                    .case '3'
                        .if ( TCHAR ptr [rax+TCHAR] != '2' )
                            .gotosw(2:ST_NORMAL)
                        .endif
                        and flags,not FL_I64
                        add rax,2*TCHAR
                        mov format,rax
                       .endc
                    .case 'd','i','o','u','x','X'
                        or flags,FL_PTRSIZE
                       .endc
                    .default
                        .gotosw(1:'z')
                    .endsw
                    .endc
                .case 'h'
                    .if ( flags & FL_SHORT )
                        or flags,FL_CHAR
                    .endif
                    or flags,FL_SHORT
                   .endc
                .case 'w'
                    or flags,FL_WIDECHAR  ; 'w' => wide character
                   .endc
                .case 't' ; ptrdiff_t
                .case 'z' ; size_t
ifndef _WIN64
                   .endc
endif
                .case 'j' ; [u]intmax_t
                .case 'q' ; quad word
                    and flags,NOT FL_LONG
                    or  flags,FL_LONGLONG or FL_I64
                   .endc
                .endsw
                .endc

            .case ST_TYPE

                mov eax,edx
                .switch eax

                .case 'B'
                .case 'b'
                    mov curadix,2
                    .if ( flags & FL_ALTERNATE )
                        ;
                        ; alternate form means '0b' prefix
                        ;
                        mov prefix,'0'
                        mov prefix[TCHAR],_tal
                        mov prefixlen,2
                    .endif
                    jmp COMMON_INT

                .case 'C' ; ISO wide character
                    .if ( !( flags & ( FL_SHORT or FL_LONG or FL_WIDECHAR ) ) )
ifdef _UNICODE
                        or flags,FL_SHORT
else
                        or flags,FL_WIDECHAR ; ISO std.
endif
                    .endif

                .case 'c'
                    ;
                    ; print a single character specified by int argument
                    ;
                    mov bufferiswide,TCHAR-1
                    _va_arg(arglist)
                    mov rcx,rax
                    lea rdx,buffer
                    mov textlen,1 ; print just a single character
                    mov text,rdx

if not defined(__UNIX__) and not defined(_UNICODE)
                    .if ( flags & ( FL_LONG or FL_WIDECHAR ) )

                        movzx eax,word ptr [rcx]
                        mov [rdx],eax
                        WideCharToMultiByte( 0, 0, rdx, 1, rdx, 1, 0, 0 )
                    .else
endif
                        mov _tal,[rcx]
                        mov [rdx],_tal
if not defined(__UNIX__) and not defined(_UNICODE)
                    .endif
endif
                    .endc

                .case 'S' ; ISO wide character string
                    .if ( !( flags & ( FL_SHORT or FL_LONG or FL_WIDECHAR ) ) )

                        or flags,FL_WIDECHAR
                    .endif
                .case 's'

                    ; print a string --
                    ; ANSI rules on how much of string to print:
                    ;   all if precision is default,
                    ;   min(precision, length) if precision given.
                    ; prints '(null)' if a null string is passed

                    mov rax,_va_arg(arglist)
                    mov ecx,precision
                    .if ( ecx == -1 )
                        mov ecx,INT_MAX
                    .endif

                    .if ( !rax )

                        lea rax,@CStr("(null)")
ifndef _UNICODE
                        and flags,not ( FL_LONG or FL_WIDECHAR )
endif
                    .endif
                    mov rdx,rax
ifndef _UNICODE
                    .if ( flags & ( FL_LONG or FL_WIDECHAR ) )

                        mov bufferiswide,1
endif
                        .while ( ecx && word ptr [rax] )

                            add rax,2
                            dec ecx
                        .endw
                        sub rax,rdx
                        sar eax,1
ifndef _UNICODE
                    .else

                        .while ( ecx && byte ptr [rax] )

                            inc rax
                            dec ecx
                        .endw
                        sub rax,rdx
                    .endif
endif
                    mov text,rdx
                    mov textlen,eax
                   .endc

                .case 'n'
                    _va_arg(arglist)
                    mov rdx,[rax-size_t]
                    mov eax,charsout
                    mov [rdx],eax
                    .if ( flags & FL_LONG )
                        mov no_output,1
                    .endif
                    .endc

if not defined(_STDCALL_SUPPORTED) and not defined(NOSTDFLT)

                .case 'E'
                .case 'G'
                .case 'A'
                    or  flags,_ST_CAPEXP    ; capitalize exponent
                    add dl,'a' - 'A'        ; convert format char to lower
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
                    or  flags,FL_SIGNED     ; floating point is signed conversion
                    lea rax,buffer          ; put result in buffer
                    mov text,rax
                    ;
                    ; compute the precision value
                    ;
                    .ifs ( precision < 0 )
                        mov precision,6     ; default precision: 6
                    .elseif ( !precision && dl == 'g' )
                        mov precision,1     ; ANSI specified
                    .endif
if defined(__UNIX__) and defined(_AMD64_)
                    mov rax,argxmm
                    add argxmm,16
else
                    mov rcx,arglist
                    add arglist,size_t
                    mov rax,[rcx]
endif
                    mov ebx,edx
                    mov edx,flags
                    and edx,_ST_CAPEXP
                    ;
                    ; do the conversion
                    ;
                    .if ( flags & FL_LONGDOUBLE )
ifndef _WIN64
                        add arglist,12
                        mov eax,ecx
endif
                        or edx,_ST_LONGDOUBLE
                    .elseif ( flags & FL_LONGLONG )
ifndef _WIN64
                        add arglist,8
                        mov eax,ecx
endif
                        or edx,_ST_QUADFLOAT
                    .else
ifndef _WIN64
                        add arglist,4
endif
                        or edx,_ST_DOUBLE
if defined(__UNIX__) and defined(_AMD64_)
else
                        mov rax,rcx
endif
                    .endif
                    _cfltcvt( rax, text, ebx, precision, edx )
                    ;
                    ; '#' and precision == 0 means force a decimal point
                    ;
                    .if ( ( flags & FL_ALTERNATE ) && !precision )

                        _forcdecpt( text )
                    .endif
                    ;
                    ; 'g' format means crop zero unless '#' given
                    ;
                    .if ( bl == 'g' && !( flags & FL_ALTERNATE ) )

                        _cropzeros( text )
                    .endif
                    ;
                    ; check if result was negative, save '-' for later
                    ; and point to positive part (this is for '0' padding)
                    ;
                    mov rcx,text
                    mov al,[rcx]
                    .if ( al == '-' )

                        or  flags,FL_NEGATIVE
                        inc rcx
                        mov text,rcx
                    .endif
                    mov textlen,strlen( rcx ) ; compute length of text
ifdef _UNICODE ; convert to wide string
ifndef __UNIX__
                    push rsi
                    push rdi
endif
                    lea  rcx,[rax+1]
                    mov  rdx,text
                    lea  rsi,[rdx+rax]
                    lea  rdi,[rdx+rax*2]
                    xor  eax,eax
                    std
                    .repeat
                        lodsb
                        stosw
                    .untilcxz
                    cld
ifndef __UNIX__
                    pop rdi
                    pop rsi
endif
endif
                   .endc

endif ; _STDCALL_SUPPORTED

                .case 'd'
                .case 'i'
                    ;
                    ; signed decimal output
                    ;
                    or  flags,FL_SIGNED
                .case 'u'
                    mov curadix,10
                    jmp COMMON_INT

                .case 'p'
                    ;
                    ; write a pointer -- this is like an integer or long
                    ; except we force precision to pad with zeros and
                    ; output in big hex.
                    ;
                    mov precision,size_t * 2
ifdef _WIN64
                    or  flags,FL_I64
endif
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
                    .if ( flags & FL_ALTERNATE )
                        ;
                        ; alternate form means '0x' prefix
                        ;
                        ;mov eax,'x' - 'a' + '9' + 1
                        ;add eax,hexoff
                        mov prefix,'0'
                        mov prefix[TCHAR],'x';_tal
                        mov prefixlen,2
                    .endif
                    jmp COMMON_INT

                .case 'o' ; unsigned octal output
                    mov curadix,8
                    .if ( flags & FL_ALTERNATE )
                        ;
                        ; alternate form means force a leading 0
                        ;
                        or flags,FL_FORCEOCTAL
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
                    _va_arg(arglist)
                    xor edx,edx
                    mov rcx,rax
                    mov eax,[rcx]
                    .if ( flags & ( FL_I64 or FL_LONGLONG ) )

                        mov edx,[rcx+4]
ifndef _WIN64
                        add arglist,size_t
endif
                    .endif

                    .if ( flags & FL_SHORT )

                        .if ( flags & FL_CHAR )
                            .if ( flags & FL_SIGNED )
                                movsx eax,al ; sign extend
                            .else
                                movzx eax,al ; zero-extend
                            .endif
                        .else
                            .if ( flags & FL_SIGNED )
                                movsx eax,ax ; sign extend
                            .else
                                movzx eax,ax ; zero-extend
                            .endif
                        .endif
                    .endif

                    .if ( flags & FL_SIGNED )

                        .if ( !( flags & ( FL_I64 or FL_LONGLONG ) ) )

                            .ifs ( eax < 0 )

                                dec edx
                                or  flags,FL_NEGATIVE
                            .endif

                        .elseifs ( edx < 0 )

                            or  flags,FL_NEGATIVE
                        .endif
                    .endif
                    ;
                    ; check precision value for default; non-default
                    ; turns off 0 flag, according to ANSI.
                    ;
                    .ifs ( precision < 0 )
                        mov precision,1 ; default precision
                    .else
                        and flags,NOT FL_LEADZERO
                    .endif
                    ;
                    ; Check if data is 0; if so, turn off hex prefix
                    ;
                    .if ( !eax && !edx )
                        mov prefixlen,eax
                    .endif
                    ;
                    ; Convert data to ASCII -- note if precision is zero
                    ; and number is zero, we get no digits at all.
                    ;
                    .if ( flags & FL_SIGNED )

                        test edx,edx
                        .ifs
                            neg edx
                            neg eax
                            sbb edx,0
                            or  flags,FL_NEGATIVE
                        .endif
                    .endif

                    lea rbx,buffer[BUFFERSIZE*TCHAR-TCHAR]
ifdef _WIN64
                    mov r8,rbx
                    mov r9d,curadix
                    shl rdx,32
                    or  rax,rdx

                    .fors ( : rax || precision > 0 : precision-- )

                        xor edx,edx
                        div r9
                        add dl,'0'
                        .ifs dl > '9'
                            add dl,byte ptr hexoff
                        .endif
ifdef _UNICODE
                        mov [rbx],dx
                        sub rbx,2
else
                        mov [rbx],dl
                        dec rbx
endif
                    .endf

else

                    .fors ( : eax || edx || precision > 0 : precision-- )

                        .if ( !edx || !curadix )

                            div curadix
                            mov ecx,edx
                            xor edx,edx

                        .else

                            push esi
                            push edi

                            .for ( ecx = 64, esi = 0, edi = 0 : ecx : ecx-- )

                                add eax,eax
                                adc edx,edx
                                adc esi,esi
                                adc edi,edi

                                .if ( edi || esi >= curadix )

                                    sub esi,curadix
                                    sbb edi,0
                                    inc eax
                                .endif
                            .endf
                            mov ecx,esi
                            pop edi
                            pop esi
                        .endif

                        add ecx,'0'
                        .ifs ( ecx > '9' )
                            add ecx,hexoff
                        .endif
ifdef _UNICODE
                        mov [ebx],cx
                        sub ebx,2
else
                        mov [ebx],cl
                        dec ebx
endif
                    .endf

endif
                    ; compute length of number

                    lea rax,buffer[BUFFERSIZE*TCHAR-TCHAR]
                    sub rax,rbx
ifdef _UNICODE
                    shr eax,1
endif
                    add rbx,TCHAR

                    ; text points to first digit now

                    ; Force a leading zero if FORCEOCTAL flag set

                    .if ( flags & FL_FORCEOCTAL )

                        .if ( TCHAR ptr [rbx] != '0' || eax == 0 )

                            sub rbx,TCHAR
                            mov TCHAR ptr [rbx],'0'
                            inc eax
                        .endif
                    .endif
                    mov text,rbx
                    mov textlen,eax
                .endsw
                ;
                ; At this point, we have done the specific conversion, and
                ; 'text' points to text to print; 'textlen' is length.   Now we
                ; justify it, put on prefixes, leading zeros, and then
                ; print it.
                ;
                .if ( !no_output )

                    .if ( flags & FL_SIGNED )
                        .if ( flags & FL_NEGATIVE )
                            mov prefix,'-'
                            mov prefixlen,1
                        .elseif ( flags & FL_SIGN )
                            mov prefix,'+'
                            mov prefixlen,1
                        .elseif ( flags & FL_SIGNSP )
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
                    .if ( !( flags & ( FL_LEFT or FL_LEADZERO ) ) )
                        ;
                        ; pad on left with blanks
                        ;
                        write_multi_char( ' ', padding, fp, &charsout )
                    .endif
                    ;
                    ; write prefix
                    ;
                    write_string( &prefix, prefixlen, fp, &charsout )

                    .if ( ( flags & FL_LEADZERO ) && !( flags & FL_LEFT ) )
                        ;
                        ; write leading zeros
                        ;
                        write_multi_char( '0', padding, fp, &charsout )
                    .endif

                    ; write text

if not defined(__UNIX__) and not defined(_UNICODE)

                    .if ( bufferiswide && textlen )

                        mov rbx,text
                        .while textlen

                            .break .ifd !WideCharToMultiByte( 0, 0, rbx, 1, &mbuf, 1, 0, 0 )

                            movzx ecx,mbuf
                            write_char( ecx, fp, &charsout )

                            add rbx,2
                            sub textlen,1
                           .break .ifs
                        .endw
                    .else
endif
                        write_string( text, textlen, fp, &charsout )
if not defined(__UNIX__) and not defined(_UNICODE)
                    .endif
endif

                    .if ( flags & FL_LEFT )

                        ; pad on right with blanks

                        write_multi_char( ' ', padding, fp, &charsout )
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

_toutput endp

    end
