
    .486
    .model flat
    .code

    repeat 10
    push ebp
    mov  ebp,esp
    mov  esp,ebp
    pop  ebp
    endm
    ret

    END
