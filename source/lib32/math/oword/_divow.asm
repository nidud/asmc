; _divow() - Divide (OWORD)
;
; Unsigned binary division of dividend by source.
;
; Note: The quotient is stored in dividend.
;
include intn.inc

.code

_divow proc uses esi edi ebx dividend:ptr, divisor:ptr, reminder:ptr

    mov esi,dividend
    mov edi,reminder
    mov ecx,4
    rep movsd
    xor eax,eax
    mov edi,dividend
    mov ecx,4
    rep stosd

    .repeat

        mov esi,divisor
        or eax,[esi]
        or eax,[esi+4]
        or eax,[esi+8]
        or eax,[esi+12]
        .ifz
            mov edi,reminder
            mov ecx,4
            rep stosd
            .break
        .endif

        mov edi,reminder
        mov eax,[esi+12]
        .if eax == [edi+12]
            mov eax,[esi+8]
            .if eax == [edi+8]
                mov eax,[esi+4]
                .if eax == [edi+4]
                    mov eax,[esi]
                    cmp eax,[edi]
                .endif
            .endif
        .endif
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
                mov ecx,4
                xor eax,eax
                rep stosd
                mov edi,dividend
                inc byte ptr [edi]
                .break
            .endif
        .endif

        mov ecx,[esi+12]    ; ESI = divisor
        mov ebx,[esi+8]
        mov edx,[esi+4]
        mov eax,[esi]
        mov divisor,0       ; divisor used as bit-count

        .while 1

            add eax,eax
            adc edx,edx
            adc ebx,ebx
            adc ecx,ecx
            .break .ifc
            .if ecx == [edi+12]
                .if ebx == [edi+8]
                    .if edx == [edi+4]
                        cmp eax,[edi]
                    .endif
                .endif
            .endif
            .break .ifa
            inc divisor
        .endw

        .while 1

            rcr ecx,1
            rcr ebx,1
            rcr edx,1
            rcr eax,1

            mov edi,reminder
            sub [edi],eax
            sbb [edi+4],edx
            sbb [edi+8],ebx
            sbb [edi+12],ecx

            cmc
            .ifnc
                .repeat
                    mov edi,dividend
                    mov esi,[edi]
                    add [edi],esi
                    mov esi,[edi+4]
                    adc [edi+4],esi
                    mov esi,[edi+8]
                    adc [edi+8],esi
                    mov esi,[edi+12]
                    adc [edi+12],esi

                    dec divisor
                    mov edi,reminder
                    .ifs
                        add [edi],eax
                        adc [edi+4],edx
                        adc [edi+8],ebx
                        adc [edi+12],ecx
                        .break(1)
                    .endif
                    shr ecx,1
                    rcr ebx,1
                    rcr edx,1
                    rcr eax,1
                    add [edi],eax
                    adc [edi+4],edx
                    adc [edi+8],ebx
                    adc [edi+12],ecx
                .untilb
            .endif
            mov edi,dividend
            mov esi,[edi]
            adc [edi],esi
            mov esi,[edi+4]
            adc [edi+4],esi
            mov esi,[edi+8]
            adc [edi+8],esi
            mov esi,[edi+12]
            adc [edi+12],esi
            dec divisor
            .break .ifs
        .endw
    .until 1
    ret

_divow endp

    end
