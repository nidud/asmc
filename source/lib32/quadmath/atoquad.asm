;
; atoquad() - Converts a string to Quadfloat
;
include quadmath.inc
include ltype.inc

MAXDIGIT    equ 39
MAXSIGDIGIT equ 49

    .code

atoquad proc uses esi edi ebx number:ptr, string:LPSTR, endptr:ptr LPSTR

    local buffer[128]:sbyte
    local digits, sigdig, flags, exponent

    mov esi,string
    mov edi,number
    xor eax,eax
    mov [edi],eax
    mov [edi+4],eax
    mov [edi+8],eax
    mov [edi+12],eax
    mov sigdig,eax
    mov exponent,eax
    mov flags,_ST_ISZERO

    .repeat

        .repeat
            lodsb
            .break(1) .if !al
        .until !( _ltype[eax+1] & _SPACE )
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
                .break .if !( _ltype[eax+1] & _DIGIT )
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
                    .break .if !( _ltype[eax+1] & _DIGIT )
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
            sub edx,eax
            mov ebx,digits
            mov eax,MAXDIGIT
            .if ebx > eax
                add edx,ebx
                mov ebx,eax
                sub edx,eax
            .endif
            lea eax,buffer
            .while 1
                .break .ifs ebx <= 0
                .break .if byte ptr [eax+ebx-1] != '0'
                inc edx
                dec ebx
            .endw
            mov digits,ebx
        .else
            mov esi,string
        .endif
        mov flags,ecx
        mov exponent,edx
        lea edx,buffer
        mov eax,digits
        mov byte ptr [edx+eax],0
        ;
        ; convert string to binary
        ;

        xor eax,eax
        mov bl,[edx]
        .if bl == '+' || bl == '-'
            inc edx
        .endif

        push esi

        .while 1
            mov al,[edx]
            .break .if !al
            and eax,not 0x30
            bt  eax,6
            sbb ecx,ecx
            and ecx,55
            sub eax,ecx
            mov ecx,8
            mov esi,number
            .repeat
                movzx edi,word ptr [esi]
                imul  edi,10
                add   eax,edi
                mov   [esi],ax
                add   esi,2
                shr   eax,16
            .untilcxz
            inc edx
        .endw

        mov esi,number
        mov eax,[esi]
        mov edx,[esi+4]
        mov ecx,[esi+8]
        mov esi,[esi+12]

        .if bl == '-'
            neg esi
            neg ecx
            sbb esi,0
            neg edx
            sbb ecx,0
            neg eax
            sbb edx,0
        .endif
        ;
        ; get bit-count of number
        ;
        xor ebx,ebx
        bsr ebx,esi
        .ifz
            bsr ebx,ecx
            .ifz
                bsr ebx,edx
                .ifz
                    bsr ebx,eax
                .else
                    add ebx,32
                .endif
            .else
                add ebx,64
            .endif
        .else
            add ebx,96
        .endif
        .ifnz
            inc ebx
        .endif

        .if ebx

            xchg ebx,ecx
            mov edi,Q_SIGBITS
            sub edi,ecx
            ;
            ; shift number to bit-size
            ;
            ; - 0x0001 --> 0x8000
            ;
            .if ecx > Q_SIGBITS
                sub ecx,Q_SIGBITS
                ;
                ; or 0x10000 --> 0x1000
                ;
                .while cl >= 32
                    mov eax,edx
                    mov edx,ebx
                    mov ebx,esi
                    xor esi,esi
                    sub cl,32
                .endw
                shrd eax,edx,cl
                shrd edx,ebx,cl
                shrd ebx,esi,cl
                shr esi,cl

            .elseif edi
                mov ecx,edi
                .while cl >= 32
                    mov esi,ebx
                    mov ebx,edx
                    mov edx,eax
                    xor eax,eax
                    sub cl,32
                .endw
                shld esi,ebx,cl
                shld ebx,edx,cl
                shld edx,eax,cl
                shl eax,cl
            .endif
            mov ecx,number
            mov [ecx],eax
            mov [ecx+4],edx
            mov [ecx+8],ebx
            mov [ecx+12],esi
            ;
            ; create exponent bias and mask
            ;
            mov ebx,Q_EXPBIAS+Q_SIGBITS-1
            sub ebx,edi
            and ebx,Q_EXPMASK ; remove sign bit
            .if flags & _ST_NEGNUM
                or ebx,0x8000
            .endif
            mov [ecx+14],bx
        .else
            or flags,_ST_ISZERO
        .endif
        pop esi

    .until 1

    mov eax,endptr
    .if eax
        mov [eax],esi
    .endif

    mov eax,number
    mov edi,flags
    mov ax,[eax+14]
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
    mov eax,number
    .if edx != 1
        xor ecx,ecx
        mov [eax],ecx
        mov [eax+4],ecx
        mov [eax+8],ecx
        mov [eax+12],ecx
        mov qerrno,ERANGE
    .elseif exponent
        quadnormalize(eax, exponent)
    .endif
    ret

atoquad endp

    end
