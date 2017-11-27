; _atonf() - Converts a string to float
;
include intn.inc
include malloc.inc
include ltype.inc
option cstack:on

    .code

_atonf proc uses rsi rdi rbx number:ptr, string:ptr, endptr:ptr, expptr:ptr, bits, expbits, n

    local buffer:ptr
    local digits, sigdig, maxdig, maxsig, flags, exponent, radix

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
    mov rdi,number
    mov ecx,n
    xor eax,eax
    rep stosq
    mov sigdig,eax
    mov exponent,eax
    mov flags,_ST_ISZERO
    mov rsi,string
    lea r8,_ltype

    .repeat

        .repeat
            lodsb
            .break(1) .if !al
        .until !(byte ptr [r8+rax+1] & _SPACE)
        dec rsi

        xor ecx,ecx
        .if al == '+'
            inc rsi
            or  ecx,_ST_SIGN
        .endif
        .if al == '-'
            inc rsi
            or  ecx,_ST_SIGN or _ST_NEGNUM
        .endif

        lodsb
        .break .if !al

        or  al,0x20
        .if al == 'n'
            mov ax,[rsi]
            or  ax,0x2020
            .if ax == 'na'
                add rsi,2
                or ecx,_ST_ISNAN
                movzx eax,byte ptr [rsi]
                .if al == '('
                    lea rdx,[rsi+1]
                    movzx eax,byte ptr [rdx]
                    .while al == '_' || byte ptr [r8+rax+1] & _DIGIT or _UPPER or _LOWER
                        inc rdx
                        mov al,[rdx]
                    .endw
                    .if al == ')'
                        lea rsi,[rdx+1]
                    .endif
                .endif
            .else
                dec rsi
                or ecx,_ST_INVALID
            .endif
            mov flags,ecx
            .break
        .endif

        .if al == 'i'
            mov ax,[rsi]
            or  ax,0x2020
            .if ax == 'fn'
                add rsi,2
                or ecx,_ST_ISINF
            .else
                dec rsi
                or ecx,_ST_INVALID
            .endif
            mov flags,ecx
            .break
        .endif

        mov ah,[rsi]
        or  ah,0x20
        .if ax == 'x0'
            or ecx,_ST_ISHEX
            add rsi,2
            mov edx,bits
            shl edx,2
            mov maxdig,edx
        .endif
        dec rsi

        mov rdi,buffer
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
                    .break .if !(byte ptr [r8+rax+1] & _HEX)
                .else
                    .break .if !(byte ptr [r8+rax+1] & _DIGIT)
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
        mov byte ptr [rdi],0
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

                mov al,[rsi]
                lea edx,[rsi-1]
                .if al == '+'
                    inc rsi
                .endif
                .if al == '-'
                    inc rsi
                    or  ecx,_ST_NEGEXP
                .endif
                and ecx,not _ST_DIGITS

                .while 1
                    movzx eax,byte ptr [rsi]
                    .break .if !(byte ptr [r8+rax+1] & _DIGIT)
                    .if edi < 100000000 ; else overflow
                        lea rbx,[rdi*8]
                        lea rdi,[rdi*2+rbx-'0']
                        add rdi,rax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc rsi
                .endw
                .if ecx & _ST_NEGEXP
                    neg rdi
                .endif
                .if !(ecx & _ST_DIGITS)
                    mov rsi,rdx
                .endif
            .else
                dec rsi ; digits found, but no e or E
            .endif

            mov rdx,rdi
            mov eax,sigdig
            .if ecx & _ST_ISHEX
                shl eax,2
            .endif
            sub rdx,rax
            mov ebx,digits
            mov eax,maxdig
            .if ebx > eax
                add rdx,rbx
                mov rbx,rax
                .if ecx & _ST_ISHEX
                    shl eax,2
                .endif
                sub edx,eax
            .endif
            mov rax,buffer
            .while 1
                .break .ifs ebx <= 0
                .break .if byte ptr [rax+rbx-1] != '0'
                inc edx
                .if ecx & _ST_ISHEX
                    add edx,3
                .endif
                dec ebx
            .endw
            mov digits,ebx
        .else
            mov rsi,string
        .endif
        .if ecx & _ST_ISHEX
            mov radix,16
        .endif
        mov flags,ecx
        mov exponent,edx
        mov eax,digits
        add rax,buffer
        mov byte ptr [rax],0
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
            xor edx,edx     ; get qword-id from bits
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
            add rbx,number
            not ecx
            and [rbx],ecx
            or  [rbx],edi
        .else
            or flags,_ST_ISZERO
        .endif

    .until 1

    mov rax,expptr
    .if rax
        mov ecx,exponent
        mov [rax],ecx
    .endif
    mov rax,endptr
    .if rax
        mov [rax],rsi
    .endif
    mov eax,flags
    ret

_atonf endp

    end
