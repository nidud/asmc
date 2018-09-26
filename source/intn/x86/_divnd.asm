; _divnd() - Divide
;
; Unsigned binary division of dividend by source.
; Note: The quotient is stored in dividend.
;
include intn.inc
include malloc.inc

.code

_divnd proc uses esi edi ebx dividend:ptr, divisor:ptr, reminder:ptr, n:dword

  local count

    mov esi,dividend
    mov edi,reminder
    mov ecx,n
    rep movsd

    xor eax,eax
    mov edi,dividend
    mov ecx,n
    rep stosd

    .repeat

        option epilogue:flags
        ;
        ; Preserve flags from function calls
        ;
        _cmpnd(divisor, dividend, n)
        .ifz
            mov edi,reminder
            mov ecx,n
            rep stosd
            .break
        .endif

        _cmpnd(divisor, reminder, n)
        .ifa
            ;
            ; divisor > dividend : reminder = dividend, quotient = 0
            ;
            .break
        .else
            .ifz
                ;
                ; divisor == dividend : reminder = 0, quotient = 1
                ;
                mov edi,reminder
                mov ecx,n
                rep stosd
                mov edi,dividend
                inc byte ptr [edi]
                .break
            .endif
        .endif

        mov eax,n
        shl eax,2
        mov edi,alloca(eax)
        mov esi,divisor
        mov divisor,eax
        mov ecx,n
        rep movsd
        mov count,0

        .while 1
            mov esi,divisor
            mov ecx,n
            xor edx,edx
            .repeat
                mov eax,[esi]
                shr edx,1
                adc [esi],eax
                sbb edx,edx
                add esi,4
            .untilcxz
            .break .if edx
            _cmpnd(divisor, reminder, n)
            .break .ifa
            inc count
        .endw

        .while 1

            mov esi,divisor
            mov ecx,n
            sbb edx,edx
            .repeat
                mov eax,[esi+ecx*4-4]
                shr edx,1
                rcr eax,1
                mov [esi+ecx*4-4],eax
                sbb edx,edx
            .untilcxz
            mov edi,reminder
            mov ecx,n
            xor edx,edx
            .repeat
                mov eax,[esi]
                shr edx,1
                sbb [edi],eax
                sbb edx,edx
                add esi,4
                add edi,4
            .untilcxz
            shr edx,1
            cmc
            .ifnc
                .repeat
                    mov edi,dividend
                    mov ecx,n
                    xor edx,edx
                    .repeat
                        mov eax,[edi]
                        shr edx,1
                        adc [edi],eax
                        sbb edx,edx
                        add edi,4
                    .untilcxz
                    dec count
                    mov edi,reminder
                    mov esi,divisor
                    mov ecx,n
                    .ifs
                        xor edx,edx
                        .repeat
                            mov eax,[esi]
                            shr edx,1
                            adc [edi],eax
                            sbb edx,edx
                            add esi,4
                            add edi,4
                        .untilcxz
                        .break(1)
                    .endif
                    xor edx,edx
                    .repeat
                        mov eax,[esi+ecx*4-4]
                        shr edx,1
                        rcr eax,1
                        sbb edx,edx
                        mov [esi+ecx*4-4],eax
                    .untilcxz
                    xor edx,edx
                    mov ecx,n
                    .repeat
                        mov eax,[esi]
                        shr edx,1
                        adc [edi],eax
                        sbb edx,edx
                        add esi,4
                        add edi,4
                    .untilcxz
                    shr edx,1
                .untilb
            .endif
            mov edi,dividend
            mov ecx,n
            sbb edx,edx
            .repeat
                mov eax,[edi]
                shr edx,1
                adc [edi],eax
                sbb edx,edx
                add edi,4
            .untilcxz
            dec count
            .break .ifs
        .endw
    .until 1
    ret

_divnd endp

    end
