include stdio.inc
include iost.inc

    .code

oputs proc uses edx string:LPSTR

    mov edx,string

    .repeat

        .while 1

            mov al,[edx]
            inc edx
            .break .if !al
            oputc()
            .break(1) .ifnz
        .endw
        mov eax,0Dh
        oputc()
        .break .ifz
        mov eax,0Ah
        oputc()
    .until 1
    ret

oputs endp

    END
