include time.inc

    .code

DaysInFebruary proc year

    mov eax,year

    .repeat
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

            mov eax,28
            .break(1)
        .endw
        mov eax,29
    .until 1
    ret

DaysInFebruary endp

    END
