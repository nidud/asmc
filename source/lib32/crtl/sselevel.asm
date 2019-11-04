; SSELEVEL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

__SSE__ equ 1
include sselevel.inc

    .data
    sselevel dd 0

    .code

setsselevel proc uses ebx

    pushfd
    pop     eax
    mov     ecx,0x200000
    mov     edx,eax
    xor     eax,ecx
    push    eax
    popfd
    pushfd
    pop     eax
    xor     eax,edx
    and     eax,ecx

    .ifnz

        xor eax,eax
        cpuid
        .if eax
            .if ah == 5
                xor     eax,eax
            .else
                mov     eax,7
                xor     ecx,ecx
                cpuid               ; check AVX2 support
                xor     eax,eax
                bt      ebx,5       ; AVX2
                adc     eax,eax     ; into bit 9
                push    eax
                mov     eax,1
                cpuid
                pop     eax
                bt      ecx,28      ; AVX support by CPU
                adc     eax,eax     ; into bit 8
                bt      ecx,27      ; XGETBV supported
                adc     eax,eax     ; into bit 7
                bt      ecx,20      ; SSE4.2
                adc     eax,eax     ; into bit 6
                bt      ecx,19      ; SSE4.1
                adc     eax,eax     ; into bit 5
                bt      ecx,9       ; SSSE3
                adc     eax,eax     ; into bit 4
                bt      ecx,0       ; SSE3
                adc     eax,eax     ; into bit 3
                bt      edx,26      ; SSE2
                adc     eax,eax     ; into bit 2
                bt      edx,25      ; SSE
                adc     eax,eax     ; into bit 1
                bt      ecx,0       ; MMX
                adc     eax,eax     ; into bit 0
                mov     sselevel,eax
            .endif
        .endif
    .endif

    .if eax & SSE_XGETBV

        xor ecx,ecx
        xgetbv
        .if eax & 6 ; AVX support by OS?
            or sselevel,SSE_AVXOS
        .endif

        and eax,0xE0
        .if eax == 0xE0

            xor ecx,ecx
            mov eax,7
            cpuid

            .if ebx & 1 shl 16      ; SSE_AVX512F ?

                xor eax,eax
                bt  ebx,30          ; SSE_AVX512BW
                adc eax,eax         ; into bit 28
                bt  ecx,1           ; SSE_AVX512VBMI
                adc eax,eax         ; into bit 27
                bt  ebx,31          ; SSE_AVX512VL
                adc eax,eax         ; into bit 26
                bt  edx,2           ; SSE_AVX5124VNNIW
                adc eax,eax         ; into bit 25
                bt  edx,3           ; SSE_AVX5124FMAPS
                adc eax,eax         ; into bit 24
                bt  ebx,21          ; SSE_AVX512IFMA
                adc eax,eax         ; into bit 23
                bt  ebx,17          ; SSE_AVX512DQ
                adc eax,eax         ; into bit 22
                bt  edx,8           ; SSE_AVX512VP2INTERSECT
                adc eax,eax         ; into bit 21
                bt  ecx,14          ; SSE_AVX512VPOPCNTDQ
                adc eax,eax         ; into bit 20
                bt  ecx,12          ; SSE_AVX512BITALG
                adc eax,eax         ; into bit 19
                bt  ecx,11          ; SSE_AVX512VNNI
                adc eax,eax         ; into bit 18
                bt  ecx,10          ; SSE_AVX512PVPCLMULQDQ
                adc eax,eax         ; into bit 17
                bt  ecx,9           ; SSE_AVX512PVAES
                adc eax,eax         ; into bit 16
                bt  ecx,8           ; SSE_AVX512PGFNI
                adc eax,eax         ; into bit 15
                bt  ecx,6           ; SSE_AVX512VBMI2
                adc eax,eax         ; into bit 14
                bt  ebx,28          ; SSE_AVX512CD
                adc eax,eax         ; into bit 13
                bt  ebx,27          ; SSE_AVX512ER
                adc eax,eax         ; into bit 12
                bt  ebx,26          ; SSE_AVX512PF
                adc eax,eax         ; into bit 11
                shl eax,11
                or  eax,SSE_AVX512F ; into bit 10
                or  sselevel,eax

                mov ecx,1
                mov eax,7
                cpuid
                .if ebx & 1 shl 5
                    or sselevel,SSE_AVX512BF16
                .endif
            .endif
        .endif
    .endif
    ret

setsselevel endp

.pragma(init(setsselevel, 30))

    end
