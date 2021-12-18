; STRTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
    s0 dd ?

    .code

strtok proc uses ebx s1:LPSTR, s2:LPSTR

    mov eax,s1
    .if eax

        mov s0,eax
    .endif

    mov ebx,s0
    .while byte ptr [ebx]

        mov ecx,s2
        mov al,[ecx]
        .while  al
            .break .if al == [ebx]
            inc ecx
            mov al,[ecx]
        .endw
        .break .if !al
        inc ebx
    .endw

    .repeat

        xor eax,eax
        .break .if al == [ebx]

        mov edx,ebx
        .while byte ptr [ebx]

            mov ecx,s2
            mov al,[ecx]

            .while al

                .if al == [ebx]
                    mov [ebx],ah
                    inc ebx
                    .break(1)
                .endif

                inc ecx
                mov al,[ecx]
            .endw
            inc ebx
        .endw
        mov eax,edx
    .until 1
    mov s0,ebx
    ret

strtok endp

    END
