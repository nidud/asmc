include stdio.inc
include conio.inc
include stdlib.inc
include limits.inc
include wchar.inc
include fltintrn.inc

    option  wstring:on

;
; the following should be set depending on the sizes of various types
;
ifndef LONGDOUBLE_IS_DOUBLE
LONGDOUBLE_IS_DOUBLE equ 0  ; 1 means long double is same as double
LONG_IS_INT     equ 1       ; 1 means long is same size as int
SHORT_IS_INT    equ 0       ; 1 means short is same size as int
PTR_IS_INT      equ 1       ; 1 means ptr is same size as int
PTR_IS_LONG     equ 1       ; 1 means ptr is same size as long
endif

BUFFERSIZE      equ 512     ; ANSI-specified minimum is 509
MAXPRECISION    equ BUFFERSIZE

;if BUFFERSIZE LT _CVTBUFSIZE + 6
;
; Buffer needs to be big enough for default minimum precision
; when converting floating point needs bigger buffer, and malloc
; fails
;
;.err <Conversion buffer too small for max double>
;endif ; BUFFERSIZE < _CVTBUFSIZE + 6

FL_SIGN         equ 0x0001 ; put plus or minus in front
FL_SIGNSP       equ 0x0002 ; put space or minus in front
FL_LEFT         equ 0x0004 ; left justify
FL_LEADZERO     equ 0x0008 ; pad with leading zeros
FL_LONG         equ 0x0010 ; long value given
FL_SHORT        equ 0x0020 ; short value given
FL_SIGNED       equ 0x0040 ; signed data given
FL_ALTERNATE    equ 0x0080 ; alternate form requested
FL_NEGATIVE     equ 0x0100 ; value is negative
FL_FORCEOCTAL   equ 0x0200 ; force leading '0' for octals
FL_LONGDOUBLE   equ 0x0400 ; long double
FL_WIDECHAR     equ 0x0800
FL_LONGLONG     equ 0x1000 ; long long value given
FL_I64          equ 0x8000 ; 64-bit value given

ST_NORMAL       equ 0   ; normal state; outputting literal chars
ST_PERCENT      equ 1   ; just read '%'
ST_FLAG         equ 2   ; just read flag character
ST_WIDTH        equ 3   ; just read width specifier
ST_DOT          equ 4   ; just read '.'
ST_PRECIS       equ 5   ; just read precision specifier
ST_SIZE         equ 6   ; just read size specifier
ST_TYPE         equ 7   ; just read type specifier
ST_INVALID      equ 8   ; Invalid format

ifdef FORMAT_VALIDATIONS
NUMSTATES       equ (ST_INVALID + 1)
else
NUMSTATES       equ (ST_TYPE + 1)
endif

externdef __lookuptable:byte
externdef __nullstring:byte
externdef __wnullstring:byte

.code

write_char proc private wc:wint_t, fp:LPFILE, pnumwritten:ptr

    mov eax,fp
    .if ([eax]._iobuf._file == 1 || [eax]._iobuf._file == 2)
        .if _putwch_nolock(wc) == WEOF
            movsx eax,ax
        .endif
    .else
        fputwc(wc, fp)
    .endif
    .if eax == -1
        mov ecx,pnumwritten
        mov [ecx],eax
    .else
        mov ecx,pnumwritten
        inc dword ptr [ecx]
    .endif
    ret

write_char endp

write_string proc private uses esi edi ebx string, len, f:LPFILE, pnumwritten:ptr

    .fors esi = string, edi = len, ebx = pnumwritten: edi > 0: edi--

        lodsw
        write_char(ax, f, ebx)
        .break .if dword ptr [ecx] == -1
    .endf
    ret

write_string endp

write_multi_char proc private uses edi char:wint_t, num:dword, f:LPFILE, pnumwritten:ptr

    .fors edi = num: edi > 0: edi--

        write_char(char, f, pnumwritten)
        .break .if dword ptr [ecx] == -1
    .endf
    ret

write_multi_char endp

_woutput proc PUBLIC uses edx ecx esi edi ebx fp:LPFILE, format:LPWSTR, arglist:PVOID

local   charsout:   sdword
local   hexoff:     dword
local   state:      dword
local   curadix:    dword
local   prefix[2]:  wint_t
local   textlen:    dword
local   prefixlen:  dword
local   no_output:  dword
local   fldwidth:   dword
local   bufferiswide:   dword
local   padding:    dword
local   text:       dword
local   capexp:     dword
local   numeax:     dword
local   numedx:     dword
local   wchar:      wint_t
local   buffer[BUFFERSIZE]:word
if LONGDOUBLE_IS_DOUBLE
local   tmp:        REAL8
else
local   tmp:        REAL10
endif

    xor eax,eax
    mov textlen,eax
    mov charsout,eax
    mov state,eax

    .while  1
        mov eax,format
        add format,2
        movzx eax,word ptr [eax]
        mov edx,eax
        .break .if !eax || charsout > INT_MAX

        .if eax >= ' ' && eax <= 'x'

            mov al,__lookuptable[eax-32]
            and eax,15
        .else
            xor eax,eax
        .endif
        shl eax,3
        add eax,state
        mov al,__lookuptable[eax]
        shr eax,4
        and eax,0Fh
        mov state,eax

        .if eax <= 7

            .switch eax

              .case ST_NORMAL

                mov bufferiswide,1
                write_char(dx, fp, addr charsout)
                .endc

              .case ST_PERCENT
                xor eax,eax
                mov no_output,eax
                mov fldwidth,eax
                mov prefixlen,eax
                mov capexp,eax
                mov bufferiswide,eax
                mov esi,eax ; flags
                mov edi,eax ; precision
                dec edi
                .endc

              .case ST_FLAG
                movzx   eax,dx
                .switch eax
                  .case '+': or esi,FL_SIGN:      .endc ; '+' force sign indicator
                  .case ' ': or esi,FL_SIGNSP:    .endc ; ' ' force sign or space
                  .case '#': or esi,FL_ALTERNATE: .endc ; '#' alternate form
                  .case '-': or esi,FL_LEFT:      .endc ; '-' left justify
                  .case '0': or esi,FL_LEADZERO:  .endc ; '0' pad with leading zeros
                .endsw
                .endc

              .case ST_WIDTH
                .if dx == '*'
                    mov eax,arglist
                    add arglist,4
                    mov eax,[eax]
                    .ifs eax < 0
                        or  esi,FL_LEFT
                        neg eax
                    .endif
                    mov fldwidth,eax
                .else
                    movsx eax,dl
                    push eax
                    mov eax,fldwidth
                    mov edx,10
                    imul edx
                    pop edx
                    add edx,eax
                    add edx,-48
                    mov fldwidth,edx
                .endif
                .endc

              .case ST_DOT
                xor edi,edi
                .endc

              .case ST_PRECIS
                .if dx == '*'
                    mov eax,arglist
                    add arglist,4
                    mov edi,[eax]
                    .ifs edi < 0
                        or edi,-1
                    .endif
                .else
                    movsx eax,dl
                    push eax
                    mov eax,edi
                    mov edx,10
                    imul edx
                    pop edx
                    add edx,eax
                    add edx,-48
                    mov edi,edx
                .endif
                .endc

              .case ST_SIZE
                .switch edx
                  .case 'l'
                    .if !(esi & FL_LONG)

                        or esi,FL_LONG
                        .endc
                    .endif
                    ;
                    ; case ll => long long
                    ;
                    and esi,NOT FL_LONG
                    or  esi,FL_LONGLONG
                    .endc
                  .case 'L'
                    or  esi,FL_LONGDOUBLE or FL_I64
                    .endc
                  .case 'I'
                    mov eax,format
                    mov ecx,[eax]
                    .switch cx
                      .case '6'
                        .if ecx != 0x00340036

                            .gotosw2(ST_NORMAL)
                        .endif
                        or  esi,FL_I64
                        add eax,4
                        mov format,eax
                        .endc
                      .case '3'
                        .if ecx != 0x00320033

                            .gotosw2(ST_NORMAL)
                        .endif
                        and esi,not FL_I64
                        add eax,4
                        mov format,eax
                        .endc
                      .case 'd'
                      .case 'i'
                      .case 'o'
                      .case 'u'
                      .case 'x'
                      .case 'X'
                        .endc
                      .default
                        .gotosw2(ST_NORMAL)
                    .endsw
                    .endc

                  .case 'h'
                    or esi,FL_SHORT
                    .endc
                  .case 'w'
                    or esi,FL_WIDECHAR  ; 'w' => wide character
                    .endc
                .endsw
                .endc

              .case ST_TYPE

                mov eax,edx
                .switch eax
                  ;
                  ; binary output
                  ;
                  .case 'b'
                    mov eax,arglist
                    add arglist,4
                    mov edx,[eax]
                    bsr ecx,edx
                    inc ecx
                    mov textlen,ecx
                    .repeat
                        sub eax,eax
                        shr edx,1
                        adc al,'0'
                        mov buffer[ecx*2-2],ax
                    .untilcxz
                    lea eax,buffer
                    mov text,eax
                    .endc

                  .case 'C' ; ISO wide character
                    .if !(esi & (FL_SHORT or FL_LONG or FL_WIDECHAR))
                        ;
                        ; CONSIDER: non-standard
                        ;
                        or esi,FL_SHORT
                    .endif

                  .case 'c'
                    ;
                    ; print a single character specified by int argument
                    ;
                    mov bufferiswide,1
                    mov eax,arglist
                    add arglist,4
                    mov edx,[eax]

                    .if esi & FL_SHORT
                        ;
                        ; format multibyte character
                        ; this is an extension of ANSI
                        ;
                        movzx eax,dl
                        push edx
                        push eax
                        mov  edx,esp
                        .ifs mbtowc(addr buffer, edx, MB_CUR_MAX) < 0
                            ;
                            ; ignore if conversion was unsuccessful
                            ;
                            mov no_output,1
                        .endif
                        pop eax
                        pop edx
                    .else
                        mov buffer,dx
                    .endif

                    lea eax,buffer
                    mov text,eax
                    mov textlen,1 ; print just a single character
                    .endc

                  .case 'S' ; ISO wide character string
                    .if !(esi & (FL_SHORT or FL_LONG or FL_WIDECHAR))

                        or esi,FL_SHORT
                    .endif
                  .case 's'
                    ; print a string --
                    ; ANSI rules on how much of string to print:
                    ;   all if precision is default,
                    ;   min(precision, length) if precision given.
                    ; prints '(null)' if a null string is passed

                    mov eax,arglist
                    add arglist,4
                    mov eax,[eax]

                    .if edi == -1
                        mov ecx,INT_MAX
                    .else
                        mov ecx,edi
                    .endif
                    .if esi & FL_SHORT
                        .if !eax ; NULL passed, use special string
                            lea eax,__nullstring
                        .endif
                        mov text,eax
                        .for edx=0: edx < ecx && byte ptr [eax]: edx++,eax++
                        ;if (_isleadbyte_l(*p, _loc_update.GetLocaleT()))
                        ;    ++p;
                        ;++p;
                        .endf
                        mov textlen,edx
                        ; textlen now contains length in multibyte chars
                    .else
                        .if !eax
                            lea eax,__wnullstring
                        .endif
                        mov text,eax
                        .repeat
                            .break .if word ptr [eax] == 0
                            add eax,2
                        .untilcxz
                        sub eax,text
                        shr eax,1
                        mov textlen,eax
                        mov bufferiswide,1
                    .endif
                    .endc
                  .case 'n'
                    mov eax,arglist
                    add arglist,4
                    mov edx,[eax-4]
                    mov eax,charsout
                    mov [edx],eax
                    .if esi & FL_LONG

                        mov no_output,1
                    .endif
                    .endc
                  .case 'E'
                  .case 'G'
                  .case 'A'
                    mov capexp,1        ; capitalize exponent
                    add dl,'a' - 'A'    ; convert format char to lower
                    ;
                    ; DROP THROUGH
                    ;
                  .case 'e'
                  .case 'f'
                  .case 'g'
                  .case 'a'
                    ; floating point conversion -- we call cfltcvt routines
                    ; to do the work for us.
                    or  esi,FL_SIGNED ; floating point is signed conversion
                    lea eax,buffer ; put result in buffer
                    mov text,eax
                    ;
                    ; compute the precision value
                    ;
                    .ifs edi < 0
                        mov edi,6 ; default precision: 6
                    .elseif !edi && dl == 'g'
                        mov edi,1 ; ANSI specified
                    .endif
                    mov ecx,arglist
                    add arglist,8
                    mov eax,[ecx]
                    mov dword ptr tmp,eax
                    mov eax,[ecx+4]
                    mov dword ptr tmp[4],eax
                    mov ebx,edx
if (LONGDOUBLE_IS_DOUBLE eq 0)
                    ;
                    ; do the conversion
                    ;
                    .if esi & FL_LONGDOUBLE

                        add arglist,4
                        mov eax,[ecx+8]
                        mov word ptr tmp[8],ax
                        ;
                        ; Note: assumes ch is in ASCII range
                        ;
                        _cldcvt(addr tmp, text, edx, edi, capexp)
                    .else
endif  ; !LONGDOUBLE_IS_DOUBLE
                        ;
                        ; Note: assumes ch is in ASCII range
                        ;
                        _cfltcvt(addr tmp, text, edx, edi, capexp)
if (LONGDOUBLE_IS_DOUBLE eq 0)
                    .endif
endif
                    ;
                    ; '#' and precision == 0 means force a decimal point
                    ;
                    .if ((esi & FL_ALTERNATE) && !edi)

                        _forcdecpt(text)
                    .endif
                    ;
                    ; 'g' format means crop zero unless '#' given
                    ;
                    .if bl == 'g' && !(esi & FL_ALTERNATE)

                        _cropzeros(text)
                    .endif
                    ;
                    ; check if result was negative, save '-' for later
                    ; and point to positive part (this is for '0' padding)
                    ;
                    mov ecx,text
                    mov al,[ecx]
                    .if al == '-'

                        or  esi,FL_NEGATIVE
                        inc text
                    .endif
                    mov textlen,strlen(text) ; compute length of text
                    .endc

                  .case 'd'
                  .case 'i'
                    ;
                    ; signed decimal output
                    ;
                    or  esi,FL_SIGNED
                  .case 'u'
                    mov curadix,10
                    jmp COMMON_INT

                  .case 'p'
                    ;
                    ; write a pointer -- this is like an integer or long
                    ; except we force precision to pad with zeros and
                    ; output in big hex.
                    ;
                    mov edi,size_t * 2
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
                    .if esi & FL_ALTERNATE
                        ;
                        ; alternate form means '0x' prefix
                        ;
                        mov eax,'x' - 'a' + '9' + 1
                        add eax,hexoff
                        mov prefix,'0'
                        mov prefix[2],ax
                        mov prefixlen,2
                    .endif
                    jmp COMMON_INT

                  .case 'o' ; unsigned octal output
                    mov curadix,8
                    .if esi & FL_ALTERNATE
                        ;
                        ; alternate form means force a leading 0
                        ;
                        or esi,FL_FORCEOCTAL
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
                    mov eax,arglist
                    add arglist,4
                    mov eax,[eax]
                    xor edx,edx

                    .if esi & FL_I64

                        mov edx,arglist
                        add arglist,4
                        mov edx,[edx]
                    .endif

                    .if esi & FL_SHORT

                        .if esi & FL_SIGNED
                            ; sign extend
                            movsx eax,ax
                        .else   ; zero-extend
                            movzx eax,ax
                        .endif
                    .elseif esi & FL_SIGNED
                        .if esi & FL_LONGLONG or FL_I64
                            .ifs edx < 0

                                or  esi,FL_NEGATIVE
                            .endif
                        .else
                            .ifs eax < 0

                                dec edx
                                or  esi,FL_NEGATIVE
                            .endif
                        .endif
                    .endif
                    ;
                    ; check precision value for default; non-default
                    ; turns off 0 flag, according to ANSI.
                    ;
                    .ifs edi < 0
                        mov edi,1 ; default precision
                    .else
                        and esi,NOT FL_LEADZERO
                    .endif
                    ;
                    ; Check if data is 0; if so, turn off hex prefix
                    ;
                    mov ecx,eax
                    or  ecx,edx
                    .ifz
                        mov prefixlen,eax
                    .endif
                    ;
                    ; Convert data to ASCII -- note if precision is zero
                    ; and number is zero, we get no digits at all.
                    ;
                    .if esi & FL_SIGNED

                        test edx,edx
                        .ifs
                            neg eax
                            neg edx
                            sbb edx,0
                            or  esi,FL_NEGATIVE
                        .endif
                    .endif
                    mov numeax,eax
                    mov numedx,edx
                    lea eax,buffer[BUFFERSIZE*2-2]
                    mov text,eax
                    jmp convert_next

                convert_loop:
                    mov ecx,curadix
                    mov eax,numeax
                    mov edx,numedx
                    test edx,edx
                    jz  DIV00
                    test ecx,ecx
                    jnz DIV01
                DIV00:
                    div ecx
                    mov ecx,edx
                    xor edx,edx
                    jmp DIV06
                DIV01:
                    push esi
                    push edi
                    mov ebx,ecx
                    mov ecx,64
                    xor esi,esi
                    xor edi,edi
                DIV02:
                    shl eax,1
                    rcl edx,1
                    rcl esi,1
                    rcl edi,1
                    cmp edi,0
                    jb  DIV04
                    ja  DIV03
                    cmp esi,ebx
                    jb  DIV04
                DIV03:
                    sub esi,ebx
                    sbb edi,0
                    inc eax
                DIV04:
                    dec ecx
                    jnz DIV02
                    mov ebx,esi
                DIV05:
                    mov ecx,ebx
                    pop edi
                    pop esi
                DIV06:
                    mov numeax,eax
                    mov numedx,edx
                    add ecx,'0'
                    .ifs ecx > '9'

                        add ecx,hexoff
                    .endif
                    mov edx,text
                    mov [edx],cx
                    sub text,2
                convert_next:
                    mov ecx,edi
                    dec edi
                    test ecx,ecx
                    jg  convert_loop
                    or  eax,numedx
                    jnz convert_loop
                    ;
                    ; compute length of number
                    ;
                    lea eax,buffer[BUFFERSIZE*2-2]
                    sub eax,text
                    shr eax,1
                    mov textlen,eax
                    add text,2 ; text points to first digit now
                    ;
                    ; Force a leading zero if FORCEOCTAL flag set
                    ;
                    .if esi & FL_FORCEOCTAL

                        mov edx,text

                        .if word ptr [edx] != '0' || textlen == 0

                            sub edx,2
                            mov text,edx
                            mov word ptr [edx],'0'
                            inc textlen
                        .endif
                    .endif
                    .endc
                .endsw
                ;
                ; At this point, we have done the specific conversion, and
                ; 'text' points to text to print; 'textlen' is length.   Now we
                ; justify it, put on prefixes, leading zeros, and then
                ; print it.
                ;

                .if !no_output

                    .if esi & FL_SIGNED
                        .if esi & FL_NEGATIVE
                            ; prefix is a '-'
                            mov prefix,'-'
                            mov prefixlen,1
                        .elseif esi & FL_SIGN
                            ; prefix is '+'
                            mov prefix,'+'
                            mov prefixlen,1
                        .elseif esi & FL_SIGNSP
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
                    .if !(esi & (FL_LEFT or FL_LEADZERO))
                        ;
                        ; pad on left with blanks
                        ;
                        write_multi_char(' ', padding, fp, addr charsout)
                    .endif
                    ;
                    ; write prefix
                    ;
                    write_string(addr prefix, prefixlen, fp, addr charsout)

                    .if (esi & FL_LEADZERO) && !(esi & FL_LEFT)
                        ;
                        ; write leading zeros
                        ;
                        write_multi_char('0', padding, fp, addr charsout)
                    .endif
                    ;
                    ; write text
                    ;
                    if 0
                    .ifs !bufferiswide && textlen > 0

                        push  esi
                        push  edi
                        .fors edi = textlen, esi = text: edi > 0: edi--

                            .ifs mbtowc(addr wchar, esi, MB_CUR_MAX) <= 0

                                .break
                            .endif
                            add esi,eax
                            write_char(wchar, fp, addr charsout)
                        .endf
                        pop   edi
                        pop   esi
                    .else
                    endif
                        write_string(text, textlen, fp, addr charsout)
                    ;.endif

                    .if esi & FL_LEFT
                        ; pad on right with blanks
                        write_multi_char(' ', padding, fp, addr charsout)
                    .endif
                .endif
                ;
                ; we're done!
                ;
                .endc
            .endsw
        .endif
    .endw

    mov eax,charsout ; return value = number of characters written
    ret

_woutput endp

    END
