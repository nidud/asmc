;
; atoquad() - Converts a string to Quadfloat
;
include quadmath.inc
include ltype.inc

MAXDIGIT    equ 39
MAXSIGDIGIT equ 49

    .code

atoquad proc uses rsi rdi rbx number:ptr, string:LPSTR, endptr:ptr LPSTR

    local buffer[128]:sbyte
    local digits, sigdig, flags, exponent

    mov rsi,string
    mov rdi,number
    xor eax,eax
    mov [rdi],rax
    mov [rdi+8],rax
    mov sigdig,eax
    mov exponent,eax
    mov flags,_ST_ISZERO
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

        dec rsi
        lea rdi,buffer
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
                .break .if !( byte ptr [r8+rax+1] & _DIGIT )
                .if ecx & _ST_DOT
                    inc sigdig
                .endif
                or ecx,_ST_DIGITS
                or edx,eax
                .continue .if edx == '0' ; if a significant digit
                .if ebx < MAXSIGDIGIT
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
            .if al == 'e'

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
                    .break .if !( byte ptr [r8+rax+1] & _DIGIT )
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
            sub rdx,rax
            mov ebx,digits
            mov eax,MAXDIGIT
            .if ebx > eax
                add rdx,rbx
                mov rbx,rax
                sub edx,eax
            .endif
            lea rax,buffer
            .while 1
                .break .ifs ebx <= 0
                .break .if byte ptr [rax+rbx-1] != '0'
                inc edx
                dec ebx
            .endw
            mov digits,ebx
        .else
            mov rsi,string
        .endif

        mov flags,ecx
        mov exponent,edx
        lea rdx,buffer
        mov eax,digits
        mov byte ptr [rdx+rax],0
        ;
        ; convert string to binary
        ;
        mov r10,number
        xor eax,eax
        mov bl,[rdx]
        .if bl == '+' || bl == '-'
            inc rdx
        .endif

        .while 1
            mov al,[rdx]
            .break .if !al
            and eax,not 0x30
            bt  eax,6
            sbb ecx,ecx
            and ecx,55
            sub eax,ecx
            mov ecx,8
            mov r11,r10
            .repeat
                movzx edi,word ptr [r11]
                imul  edi,10
                add   eax,edi
                mov   [r11],ax
                add   r11,2
                shr   eax,16
            .untilcxz
            inc rdx
        .endw
        mov rax,[r10]
        mov rdx,[r10+8]
        .if bl == '-'
            neg rdx
            neg rax
            sbb rdx,0
        .endif
         ;
        ; get bit-count of number
        ;
        xor ecx,ecx
        bsr rcx,rdx
        .ifz
            bsr rcx,rax
        .else
            add ecx,64
        .endif
        .ifnz
            inc ecx
        .endif

        .if ecx
            ;
            ; shift number to bit-size
            ;
            ; - 0x0001 --> 0x8000
            ;
            mov edi,Q_SIGBITS
            mov ebx,edi
            sub ebx,ecx

            .if ecx > edi
                sub ecx,edi
                ;
                ; or 0x10000 --> 0x1000
                ;
                .if cl >= 64
                    mov rax,rdx
                    xor edx,edx
                    sub cl,64
                .endif
                shrd rax,rdx,cl
                shr rdx,cl

            .elseif ebx

                mov ecx,ebx
                .if cl >= 64
                    mov rdx,rax
                    xor eax,eax
                    sub cl,64
                .endif
                shld rdx,rax,cl
                shl rax,cl

            .endif
            mov [r10],rax
            mov [r10+8],rdx
            ;
            ; create exponent bias and mask
            ;
            mov edi,Q_EXPBIAS+Q_SIGBITS-1
            sub edi,ebx         ; - shift count
            and edi,Q_EXPMASK   ; remove sign bit
            .if flags & _ST_NEGNUM
                or di,0x8000
            .endif
            mov [r10+14],di
        .else
            or flags,_ST_ISZERO
        .endif

    .until 1

    mov rax,endptr
    .if rax
        mov [rax],rsi
    .endif

    mov edi,flags
    mov ax,[r10+14]
    and eax,Q_EXPMASK
    mov edx,1

    .switch
      .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID
        mov edx,0x7FFF0000
        .if edi & _ST_ISNAN or _ST_INVALID
            or edx,0x00004000
        .endif
        .endc
      .case edi & _ST_OVERFLOW
      .case eax >= Q_EXPMAX + Q_EXPBIAS
        mov edx,0x7FFF0000
        .if edi & _ST_NEGNUM
            or edx,0x80000000
        .endif
        .endc
      .case edi & _ST_UNDERFLOW
        xor edx,edx
        .endc
    .endsw
    mov rax,r10
    .if edx != 1
        xor ecx,ecx
        mov [rax],rcx
        mov [rax+8],rcx
        mov qerrno,ERANGE
    .elseif exponent
        quadnormalize(rax, exponent)
    .endif
    ret

atoquad endp

    end
