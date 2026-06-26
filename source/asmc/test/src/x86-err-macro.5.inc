    .386
    .model flat
    .code


line_error macro line

    mov ax,line1
    exitm<eax>
    endm

    mov edx,line_error(5)