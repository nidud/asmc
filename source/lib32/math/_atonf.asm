; _atonf() - Converts a string to float
;
include intn.inc
include malloc.inc
include ltype.inc

    .code

_atonf proc uses esi edi ebx number:ptr, string:ptr, endptr:ptr, expptr:ptr, bits, expbits, n

    local buffer, flags, exponent, radix
    local digits, sigdig, maxdig, maxsig

    mov radix,10    ; assume desimal
    mov eax,bits    ; 53-bit --> 17
    mov ecx,eax     ; 64-bit --> 22
    mov edx,eax     ;113-bit --> 39
    shr eax,2
    shr edx,4
    shr ecx,5
    add eax,edx
    add eax,ecx
    shr ecx,2
    sub eax,ecx
    mov maxdig,eax
    add eax,10
    mov maxsig,eax
    inc eax
    mov buffer,alloca(eax)
    mov edi,number
    mov ecx,n
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
            mov edx,bits
            shl edx,2
            mov maxdig,edx
        .endif
        dec esi

        mov edi,buffer
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
                .if ecx & _ST_ISHEX
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
                .if ebx < maxsig
                    stosb
                .endif
                inc ebx
            .endif
        .endw
        mov byte ptr [edi],0
        mov digits,ebx
        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor edi,edi ; exponent

            or  al,0x20
            mov ah,'e'
            .if ecx & _ST_ISHEX
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
            .if ecx & _ST_ISHEX
                shl eax,2
            .endif
            sub edx,eax
            mov ebx,digits
            mov eax,maxdig
            .if ebx > eax
                add edx,ebx
                mov ebx,eax
                .if ecx & _ST_ISHEX
                    shl eax,2
                .endif
                sub edx,eax
            .endif
            mov eax,buffer
            .while 1
                .break .ifs ebx <= 0
                .break .if byte ptr [eax+ebx-1] != '0'
                inc edx
                .if ecx & _ST_ISHEX
                    add edx,3
                .endif
                dec ebx
            .endw
            mov digits,ebx
        .else
            mov esi,string
        .endif
        .if ecx & _ST_ISHEX
            mov radix,16
        .endif
        mov flags,ecx
        mov exponent,edx
        mov eax,digits
        add eax,buffer
        mov byte ptr [eax],0
        ;
        ; convert string to binary
        ;
        _atond(number, buffer, radix, n)
        ;
        ; get bit-count of number
        ;
        .if _bsrnd(number, n)
            ;
            ; shift number to bit-size
            ;
            ; - 0x0001 --> 0x8000
            ;
            mov edi,bits
            mov ebx,edi
            sub ebx,eax

            .if eax > edi
                sub eax,edi
                ;
                ; or 0x10000 --> 0x1000
                ;
                _shrnd(number, eax, n)
            .elseif ebx
                _shlnd(number, ebx, n)
            .endif
            ;
            ; create exponent bias and mask
            ;
            mov ecx,expbits
            mov eax,1
            shl eax,cl
            mov ecx,eax     ; sign bit
            dec eax         ; mask
            mov edx,eax
            shr edx,1       ; bias
            add edi,edx     ; bits + bias
            sub edi,ebx     ; - shift count
            dec edi
            and edi,eax     ; remove sign bit
            .if flags & _ST_NEGNUM
                or edi,ecx
            .endif
            mov ebx,ecx
            xor edx,edx     ; get dword-id from bits
            mov eax,bits
            mov ecx,32
            div ecx
            mov ecx,ebx
            shl ecx,1
            dec ecx
            .if edx
                ;
                ; then shift exponent and sign to high word
                ;
                mov edx,ecx
                mov ecx,31
                bsf ebx,ebx
                sub ecx,ebx
                shl edi,cl
                shl edx,cl
                mov ecx,edx
            .endif

            lea ebx,[eax*4]
            add ebx,number
            not ecx
            and [ebx],ecx
            or  [ebx],edi
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
