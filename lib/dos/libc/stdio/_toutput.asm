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
define FL_LONGLONG      0x0800  ; long long or REAL16 value given
define FL_I64           0x1000  ; 64-bit value given
define FL_PTRSIZE       0x2000  ; platform dependent number
define FL_CHAR          0x4000  ; hh - int-size arg from char
define FL_WIDECHAR      0x8000

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

write_char proc stdcall private uses bx c:int_t, fp:LPFILE, pnumwritten:ptr int_t

    lesl bx,fp
    mov cx,c

    .if ( ( esl[bx]._iobuf._flag & _IOSTRG ) && word ptr esl[bx]._iobuf._base == NULL )

        mov ax,1
        lesl bx,pnumwritten
        add esl[bx],ax

    .elseif ( _fputtc( cx, rbx ) == -1 )

        test word ptr esl[bx]._iobuf._flag[2],(_IOSNPRINTF shr 16)
        lesl bx,pnumwritten

        .ifnz
            mov ax,esl[bx]
            inc ax
        .endif
        mov esl[bx],ax
    .else
        lesl bx,pnumwritten
        inc int_t ptr esl[bx]
    .endif
    ret

write_char endp

write_string proc stdcall private uses bx string:LPTSTR, len:SINT, fp:LPFILE, pnumwritten:ptr int_t

    lesl bx,string
    .for ( : len > 0 : len-- )

        mov cl,esl[bx]
        inc bx
        pushl es
        write_char( cx, fp, pnumwritten )
        popl es
       .break .if ( ax == -1 )
    .endf
    ret

write_string endp

write_multi_char proc stdcall private c:int_t, num:int_t, fp:LPFILE, pnumwritten:ptr int_t

    .for ( : num > 0 : num-- )

       .break .if ( write_char( c, fp, pnumwritten ) == -1 )
    .endf
    ret

write_multi_char endp


_va_arg macro ap
    lesl bx,ap
    add word ptr ap,size_t
    retm<esl[bx]>
    endm

define flags <si>

_toutput proc uses si di bx fp:LPFILE, format:LPTSTR, arglist:ptr

   .new charsout            : int_t
   .new state               : uint_t
   .new curadix             : uint_t
   .new prefix[2]           : char_t
   .new textlen             : uint_t
   .new prefixlen           : uint_t
   .new no_output           : uint_t
   .new fldwidth            : uint_t
   .new precision           : uint_t
;  .new flags               : uint_t
   .new padding             : uint_t
   .new text                : LPTSTR
   .new buffer[BUFFERSIZE]  : char_t
   .new hexoff              : char_t

    xor ax,ax
    mov charsout,ax
    mov state,ax
    mov textlen,ax

    .while 1

        lesl bx,format
        inc word ptr format
        xor ax,ax
        mov al,esl[bx]
        mov dx,ax

        .break .if ( !al || charsout > _I16_MAX )

        .if ( al >= ' ' && al <= 'z' )

            mov di,ax
            mov al,__lookuptable[di-32]
            and ax,15
        .else
            xor ax,ax
        .endif

        shl ax,3
        add ax,state
        mov di,ax
        mov al,__lookuptable[di]
        shr ax,4
        and ax,0x0F
        mov state,ax

        option switch:regax

        .if ( ax <= 7 )

            .switch ax
            .case ST_NORMAL
                write_char( dx, fp, &charsout )
               .endc

            .case ST_PERCENT
                xor ax,ax
                mov no_output,ax
                mov fldwidth,ax
                mov prefixlen,ax
                mov flags,ax
                mov precision,-1
               .endc

            .case ST_FLAG
                .switch pascal dx
                .case '+': or flags,FL_SIGN      ; '+' force sign indicator
                .case ' ': or flags,FL_SIGNSP    ; ' ' force sign or space
                .case '#': or flags,FL_ALTERNATE ; '#' alternate form
                .case '-': or flags,FL_LEFT      ; '-' left justify
                .case '0': or flags,FL_LEADZERO  ; '0' pad with leading zeros
                .endsw
                .endc

            .case ST_WIDTH
                .if ( dx == '*' )

                    mov ax,_va_arg(arglist)
                    .ifs ( ax < 0 )
                        or  flags,FL_LEFT
                        neg ax
                    .endif
                    mov fldwidth,ax
                .else
                    .ifs ( dl < 0 )
                        mov dh,-1
                    .endif
                    imul ax,fldwidth,10
                    add ax,dx
                    add ax,-48
                    mov fldwidth,ax
                .endif
                .endc

            .case ST_DOT
                mov precision,0
               .endc

            .case ST_PRECIS
                mov cx,precision
                .if ( dx == '*' )

                    mov cx,_va_arg(arglist)
                    .ifs ( cx < 0 )
                        mov cx,-1
                    .endif
                .else
                    imul ax,cx,10
                    .ifs ( dl < 0 )
                        mov dh,-1
                    .endif
                    mov cx,dx
                    add cx,ax
                    add cx,-48
                .endif
                mov precision,cx
               .endc

            .case ST_SIZE

                .switch dx
                .case 'l'
                    or flags,FL_LONG
                   .endc
                .case 'I'
                    lesl bx,format
                    xor cx,cx
                    mov cl,esl[bx]
                    .switch cx
                    .case '3'
                        .if ( byte ptr esl[bx+1] != '2' )
                            .gotosw(2:ST_NORMAL)
                        .endif
                        add bx,2*tchar_t
                        mov word ptr format,bx
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
                .case 't' ; ptrdiff_t
                .case 'z' ; size_t
                   .endc
                .endsw
                .endc

            .case ST_TYPE

                mov ax,dx
                .switch ax

                .case 'B'
                .case 'b'
                    mov curadix,2
                    .if ( flags & FL_ALTERNATE )
                        ;
                        ; alternate form means '0b' prefix
                        ;
                        mov prefix,'0'
                        mov prefix[tchar_t],_tal
                        mov prefixlen,2
                    .endif
                    jmp COMMON_INT

                .case 'c'
                    ;
                    ; print a single character specified by int argument
                    ;
                    mov al,_va_arg(arglist)
                    mov buffer,al
                    lea dx,buffer
                    mov textlen,1 ; print just a single character
                    mov word ptr text,dx
                    movl word ptr text[2],ss
                   .endc

                .case 's'

                    ; print a string --
                    ; ANSI rules on how much of string to print:
                    ;   all if precision is default,
                    ;   min(precision, length) if precision given.
                    ; prints '(null)' if a null string is passed

                    mov ax,_va_arg(arglist)
                    movl dx,_va_arg(arglist)
                    mov cx,precision
                    .if ( cx == -1 )
                        mov cx,_I16_MAX
                    .endif
                    .if ( !ax )

                        lea ax,@CStr("(null)")
                        movl dx,ds
                    .endif
                    mov bx,ax
                    movl es,dx
                    .while ( cx && byte ptr esl[bx] )
                        inc bx
                        dec cx
                    .endw
                    sub bx,ax
                    mov word ptr text,ax
                    movl word ptr text[2],dx
                    mov textlen,bx
                   .endc

                .case 'n'
                    mov ax,_va_arg(arglist)
                    movl dx,_va_arg(arglist)
                    mov bx,ax
                    movl es,dx
                    mov ax,charsout
                    mov esl[bx],ax
                    .if ( flags & FL_LONG )
                        mov no_output,1
                    .endif
                    .endc

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
                        mov prefix[tchar_t],'x';_tal
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
                    mov ax,_va_arg(arglist)
                    xor dx,dx
                    .if ( flags & FL_LONG )
                        mov dx,_va_arg(arglist)
                    .endif

                    .if ( flags & FL_SHORT )

                        .if ( flags & FL_CHAR )
                            .if ( flags & FL_SIGNED )
                                cbw         ; sign extend
                            .else
                                mov ah,0    ; zero-extend
                            .endif
                        .else
                            .if ( flags & FL_SIGNED )
                                cwd         ; sign extend
                            .endif
                        .endif
                    .endif

                    .if ( flags & FL_SIGNED )

                        .if ( !( flags & FL_LONG ) )

                            .ifs ( ax < 0 )

                                dec dx
                                or  flags,FL_NEGATIVE
                            .endif

                        .elseifs ( dx < 0 )

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
                    .if ( !ax && !dx )
                        mov prefixlen,ax
                    .endif
                    ;
                    ; Convert data to ASCII -- note if precision is zero
                    ; and number is zero, we get no digits at all.
                    ;
                    .if ( flags & FL_SIGNED )

                        test dx,dx
                        .ifs
                            neg dx
                            neg ax
                            sbb dx,0
                            or  flags,FL_NEGATIVE
                        .endif
                    .endif

                    mov di,BUFFERSIZE-1

                    .fors ( : ax || dx || precision > 0 : precision-- )

                        .if ( !dx || !curadix )

                            div curadix
                            mov cx,dx
                            xor dx,dx

                        .else

                            push si
                            .for ( si = 32, cx = 0, bx = 0 : si : si-- )

                                add ax,ax
                                adc dx,dx
                                adc cx,cx
                                adc bx,bx

                                .if ( bx || cx >= curadix )

                                    sub cx,curadix
                                    sbb bx,0
                                    inc ax
                                .endif
                            .endf
                            pop si
                        .endif

                        add cl,'0'
                        .ifs ( cl > '9' )
                            add cl,hexoff
                        .endif
                        mov buffer[di],cl
                        dec di
                    .endf

                    ; compute length of number

                    mov ax,BUFFERSIZE-1
                    sub ax,di
                    inc di

                    ; text points to first digit now

                    ; Force a leading zero if FORCEOCTAL flag set

                    .if ( flags & FL_FORCEOCTAL )

                        .if ( buffer[di] != '0' || ax == 0 )

                            dec di
                            mov buffer[di],'0'
                            inc ax
                        .endif
                    .endif
                    lea cx,buffer[di]
                    mov word ptr text,cx
                    movl word ptr text[2],ss
                    mov textlen,ax
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
                    mov ax,fldwidth
                    sub ax,textlen
                    sub ax,prefixlen
                    mov padding,ax
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

                    write_string( text, textlen, fp, &charsout )
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
