; _atonf() - Converts a string to float
;
include intn.inc
include ltype.inc

MAXBUF  equ 256 ; maximum digits to keep

    .code

_atonf proc uses esi edi ebx number:ptr, string:ptr, endptr:ptr, expptr:ptr, radix, n

    local buffer[MAXBUF]:sbyte, digits, sigdig
    local flags, exponent, bits, r_expptr

    mov edi,number
    mov ecx,n
    mov edx,8
    mov eax,64      ; assuming REAL10

    .if ecx != 3
        mov eax,ecx
        shl eax,5   ; else n * 32 - 16
        sub eax,16
        mov edx,eax
        shr edx,3
    .endif

    add edx,edi
    mov r_expptr,edx
    mov bits,eax
    xor eax,eax
    rep stosd
    mov sigdig,eax
    mov exponent,eax
    mov flags,_ST_ISZERO
    mov esi,string

    .repeat

        .repeat
            lodsb
            .break(1) .if !al
        .until !(_ltype[eax+1] & _SPACE)
        dec esi

        xor ecx,ecx
        .if al == '+'
            inc esi
            or  ecx,_ST_SIGN
        .endif
        .if al == '-'
            inc esi
            or  ecx,_ST_SIGN or _ST_NEGNUM
        .endif

        lodsb
        .break .if !al

        or  al,0x20
        .if al == 'n'
            mov ax,[esi]
            or  ax,0x2020
            .if ax == 'na'
                add esi,2
                or ecx,_ST_ISNAN
                movzx eax,byte ptr [esi]
                .if al == '('
                    lea edx,[esi+1]
                    movzx eax,byte ptr [edx]
                    .while al == '_' || _ltype[eax+1] & _DIGIT or _UPPER or _LOWER
                        inc edx
                        mov al,[edx]
                    .endw
                    .if al == ')'
                        lea esi,[edx+1]
                    .endif
                .endif
            .else
                dec esi
                or ecx,_ST_INVALID
            .endif
            mov flags,ecx
            .break
        .endif

        .if al == 'i'
            mov ax,[esi]
            or  ax,0x2020
            .if ax == 'fn'
                add esi,2
                or ecx,_ST_ISINF
            .else
                dec esi
                or ecx,_ST_INVALID
            .endif
            mov flags,ecx
            .break
        .endif

        mov ah,[esi]
        or  ah,0x20
        .if ax == 'x0'
            or ecx,_ST_ISHEX
            add esi,2
        .endif
        dec esi

        lea edi,buffer
        xor ebx,ebx
        xor edx,edx
        xor eax,eax
        ;
        ; Parse the mantissa
        ;
        .while 1
            lodsb
            .break .if !al
            .if al == '.'
                .break .if ecx & _ST_DOT
                or ecx,_ST_DOT
            .else
                .if radix == 16
                    .break .if !(_ltype[eax+1] & _HEX)
                .else
                    .break .if !(_ltype[eax+1] & _DIGIT)
                .endif
                .if ecx & _ST_DOT
                    inc sigdig
                .endif
                or ecx,_ST_DIGITS
                or edx,eax
                .continue .if edx == '0' ; if a significant digit
                .if ebx < MAXBUF
                    stosb
                .endif
                inc ebx
            .endif
        .endw
        mov digits,ebx
        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor edi,edi ; exponent

            or  al,0x20
            mov ah,'e'
            .if radix == 16
                mov ah,'p'
            .endif

            .if al == ah

                mov al,[esi]
                lea edx,[esi-1]
                .if al == '+'
                    inc esi
                .endif
                .if al == '-'
                    inc esi
                    or  ecx,_ST_NEGEXP
                .endif
                and ecx,not _ST_DIGITS

                .while 1
                    movzx eax,byte ptr [esi]
                    .break .if !(_ltype[eax+1] & _DIGIT)
                    .if edi < 100000000 ; else overflow
                        lea ebx,[edi*8]
                        lea edi,[edi*2+ebx-'0']
                        add edi,eax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc esi
                .endw
                .if ecx & _ST_NEGEXP
                    neg edi
                .endif
                .if !(ecx & _ST_DIGITS)
                    mov esi,edx
                .endif
            .else
                dec esi ; digits found, but no e or E
            .endif

            mov edx,edi
            mov eax,sigdig
            .if radix == 16
                shl eax,2
            .endif
            sub edx,eax
            mov ebx,digits
            lea eax,buffer
            .while 1
                .break .ifs ebx <= 0
                .break .if byte ptr [eax+ebx-1] != '0'
                inc edx
                .if radix == 16
                    add edx,3
                .endif
                dec ebx
            .endw
            mov digits,ebx
        .else
            mov esi,string
        .endif
        mov flags,ecx
        mov exponent,edx
        mov eax,digits
        mov buffer[eax],0

        _atond(number, &buffer, radix, n)

        .if _bsrnd(number, n)

            mov edi,bits
            mov ebx,edi
            sub ebx,eax

            .if eax > edi
                sub eax,edi
                ;or flags,_ST_OVERFLOW
                .if n > 3
                    dec eax
                .endif
                .if eax
                    _shrnd(number, eax, n)
                .endif
            .else
                mov eax,ebx
                .if n > 3
                    inc eax
                .endif
                _shlnd(number, eax, n)
            .endif

            lea edi,[edi+EXPONENT_BIAS-1]
            sub edi,ebx
            mov edx,r_expptr
            .if flags & _ST_NEGNUM
                or di,0x8000
            .endif
            mov [edx],di

        .else
            or flags,_ST_ISZERO
        .endif

    .until 1

    mov eax,expptr
    .if eax
        mov ecx,exponent
        mov [eax],ecx
    .endif
    mov eax,endptr
    .if eax
        mov [eax],esi
    .endif
    mov eax,flags
    ret

_atonf endp

    end
