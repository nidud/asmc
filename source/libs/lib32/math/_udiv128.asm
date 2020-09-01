; _UDIV128.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _udiv128() - Divide
;
; Unsigned binary division of dividend by source.
; Note: The quotient is stored in dividend.
;
include quadmath.inc

_U8D    proto

.code

_udiv128 proc uses esi edi ebx dividend:ptr, divisor:ptr, reminder:ptr

  local bits:uint_t, overflow:int_t

    mov ebx,divisor     ; EBX: divisor
    mov esi,dividend    ; dividend --> reminder
    mov edi,reminder
    mov ecx,4
    rep movsd

    xor eax,eax         ; quotient (dividend) --> 0
    mov edi,dividend
    mov ecx,4
    rep stosd
    mov overflow,eax

    .repeat

        mov edi,reminder

        or eax,[ebx+8]      ; divisor 64-bit ?
        or eax,[ebx+12]
if 0
        .ifz

            or ecx,[edi+8]  ; dividend 64-bit ?
            or ecx,[edi+12]
            .ifz

                mov eax,[edi]
                mov edx,[edi+4]     ; dividend
                mov ecx,[ebx+4]
                mov ebx,[ebx]       ; divisor
                _U8D()
                mov edi,reminder
                mov [edi],ebx
                mov [edi+4],ecx
                mov edi,dividend
                mov [edi],eax
                mov [edi+4],edx

                .break

            .endif
        .endif
endif
        or eax,[ebx]    ; divisor zero ?
        or eax,[ebx+4]
        .ifz
            mov ecx,4
            rep stosd
            .break
        .endif

        assume ebx:ptr dword
        .if ( [ebx+0x0C] == [edi+0x0C] && \
              [ebx+0x08] == [edi+0x08] && \
              [ebx+0x04] == [edi+0x04] )
            cmp [ebx],[edi]
        .endif
        .break .ifa
            ;
            ; divisor > dividend : reminder = dividend, quotient = 0
            ;
        .ifz
            ;
            ; divisor == dividend : reminder = 0, quotient = 1
            ;
            xor eax,eax
            mov ecx,4
            rep stosd
            mov edi,dividend
            inc byte ptr [edi]
            .break
        .endif

        mov edi,ebx
        mov esi,[edi+0x00]
        mov edx,[edi+0x04]
        mov ebx,[edi+0x08]
        mov ecx,[edi+0x0C]
        mov bits,0
        mov edi,reminder

        .while 1

            add esi,esi
            adc edx,edx
            adc ebx,ebx
            adc ecx,ecx
            .break .ifc
            .if ( ecx == [edi+0x0C] && \
                  ebx == [edi+0x08] && \
                  edx == [edi+0x04] )
                cmp esi,[edi]
            .endif
            .break .ifa
            inc bits
        .endw

        .while 1

            rcr ecx,1
            rcr ebx,1
            rcr edx,1
            rcr esi,1

            mov edi,reminder
            sub [edi+0x00],esi
            sbb [edi+0x04],edx
            sbb [edi+0x08],ebx
            sbb [edi+0x0C],ecx

            cmc
            .ifnc

                assume edi:ptr dword

                .repeat
                    mov edi,dividend
                    add [edi+0x00],[edi+0x00]
                    adc [edi+0x04],[edi+0x04]
                    adc [edi+0x08],[edi+0x08]
                    adc [edi+0x0C],[edi+0x0C]
                    adc overflow,0
                    dec bits
                    mov edi,reminder
                    .ifs
                        add [edi+0x00],esi
                        adc [edi+0x04],edx
                        adc [edi+0x08],ebx
                        adc [edi+0x0C],ecx
                        .break(1)
                    .endif
                    shr ecx,1
                    rcr ebx,1
                    rcr edx,1
                    rcr esi,1
                    add [edi+0x00],esi
                    adc [edi+0x04],edx
                    adc [edi+0x08],ebx
                    adc [edi+0x0C],ecx
                .untilb
            .endif
            mov edi,dividend
            adc [edi+0x00],[edi+0x00]
            adc [edi+0x04],[edi+0x04]
            adc [edi+0x08],[edi+0x08]
            adc [edi+0x0C],[edi+0x0C]
            adc overflow,0
            dec bits
            .break .ifs
        .endw
    .until 1
    mov eax,overflow
    ret

_udiv128 endp

    end
