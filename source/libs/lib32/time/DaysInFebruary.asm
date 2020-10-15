; DAYSINFEBRUARY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

DaysInFebruary proc year

    mov eax,year

    .while 1

        .break .if !eax

        .if !(eax & 3)

            mov ecx,100
            xor edx,edx
            div ecx
            .break .if edx

            mov eax,year
        .endif

        mov ecx,400
        xor edx,edx
        div ecx
        .break .if !edx

        .return 28
    .endw
    mov eax,29
    ret

DaysInFebruary endp

    END
