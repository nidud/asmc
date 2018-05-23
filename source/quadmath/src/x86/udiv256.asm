;
; _udiv256() - Divide
;
; Unsigned binary division of dividend by source.
; Note: The quotient is stored in dividend.
;
include quadmath.inc

.code

_udiv256 proc uses esi edi ebx dividend:PU256, divisor:PU256, reminder:PU256

  local bits, m08, m12, m16, m20

    mov ebx,divisor     ; EBX: divisor
    mov esi,dividend    ; dividend --> reminder
    mov edi,reminder
    mov ecx,8
    rep movsd

    xor eax,eax         ; quotient (dividend) --> 0
    mov edi,dividend
    mov ecx,8
    rep stosd

    .repeat

        mov edi,reminder

        or eax,[ebx]    ; divisor zero ?
        or eax,[ebx+4]
        or eax,[ebx+8]
        or eax,[ebx+12]
        or eax,[ebx+16]
        or eax,[ebx+20]
        or eax,[ebx+24]
        or eax,[ebx+28]
        .ifz
            mov ecx,8
            rep stosd
            .break
        .endif

        mov eax,[ebx+28]
        .if eax == [edi+28]
            mov eax,[ebx+24]
            .if eax == [edi+24]
                mov eax,[ebx+20]
                .if eax == [edi+20]
                    mov eax,[ebx+16]
                    .if eax == [edi+16]
                        mov eax,[ebx+12]
                        .if eax == [edi+12]
                            mov eax,[ebx+8]
                            .if eax == [edi+8]
                                mov eax,[ebx+4]
                                .if eax == [edi+4]
                                    mov eax,[ebx]
                                    cmp eax,[edi]
                                .endif
                            .endif
                        .endif
                    .endif
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
                mov ecx,8
                rep stosd
                mov edi,dividend
                inc byte ptr [edi]
                .break
            .endif
        .endif

        mov edi,ebx
        mov eax,[edi+8]
        mov m08,eax
        mov eax,[edi+12]
        mov m12,eax
        mov eax,[edi+16]
        mov m16,eax
        mov eax,[edi+20]
        mov m20,eax
        mov ecx,[edi+28]
        mov ebx,[edi+24]
        mov edx,[edi+4]
        mov eax,[edi]
        mov bits,0
        mov edi,reminder

        .while 1

            add eax,eax
            adc edx,edx
            mov esi,m08
            adc m08,esi
            mov esi,m12
            adc m12,esi
            mov esi,m16
            adc m16,esi
            mov esi,m20
            adc m20,esi
            adc ebx,ebx
            adc ecx,ecx
            .break .ifc

            .if ecx == [edi+28]
                .if ebx == [edi+24]
                    mov esi,m20
                    .if esi == [edi+20]
                        mov esi,m16
                        .if esi == [edi+16]
                            mov esi,m12
                            .if esi == [edi+12]
                                mov esi,m08
                                .if esi == [edi+8]
                                    .if edx == [edi+4]
                                        cmp eax,[edi]
                                    .endif
                                .endif
                            .endif
                        .endif
                    .endif
                .endif
            .endif
            .break .ifa
            inc bits
        .endw

        .while 1

            rcr ecx,1
            rcr ebx,1
            rcr m20,1
            rcr m16,1
            rcr m12,1
            rcr m08,1
            rcr edx,1
            rcr eax,1

            mov edi,reminder
            sub [edi],eax
            sbb [edi+4],edx
            mov esi,m08
            sbb [edi+8],esi
            mov esi,m12
            sbb [edi+12],esi
            mov esi,m16
            sbb [edi+16],esi
            mov esi,m20
            sbb [edi+20],esi
            sbb [edi+24],ebx
            sbb [edi+28],ecx
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
                    mov esi,[edi+16]
                    adc [edi+16],esi
                    mov esi,[edi+20]
                    adc [edi+20],esi
                    mov esi,[edi+24]
                    adc [edi+24],esi
                    mov esi,[edi+28]
                    adc [edi+28],esi
                    dec bits
                    mov edi,reminder
                    .ifs
                        add [edi],eax
                        adc [edi+4],edx
                        mov esi,m08
                        adc [edi+8],esi
                        mov esi,m12
                        adc [edi+12],esi
                        mov esi,m16
                        adc [edi+16],esi
                        mov esi,m20
                        adc [edi+20],esi
                        adc [edi+24],ebx
                        adc [edi+28],ecx
                        .break(1)
                    .endif
                    shr ecx,1
                    rcr ebx,1
                    rcr m20,1
                    rcr m16,1
                    rcr m12,1
                    rcr m08,1
                    rcr edx,1
                    rcr eax,1
                    add [edi],eax
                    adc [edi+4],edx
                    mov esi,m08
                    adc [edi+8],esi
                    mov esi,m12
                    adc [edi+12],esi
                    mov esi,m16
                    adc [edi+16],esi
                    mov esi,m20
                    adc [edi+20],esi
                    adc [edi+24],ebx
                    adc [edi+28],ecx
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
            mov esi,[edi+16]
            adc [edi+16],esi
            mov esi,[edi+20]
            adc [edi+20],esi
            mov esi,[edi+24]
            adc [edi+24],esi
            mov esi,[edi+28]
            adc [edi+28],esi
            dec bits
            .break .ifs
        .endw
    .until 1
    ret

_udiv256 endp

    end
