include intrin.inc

    .code

    option win64:0

umul256 proc syscall Multiplier:oword, Multiplicand:oword, HighProduct:ptr

    mov rax,Multiplier

    .if !rsi && !rcx

        .if HighProduct

            mov [HighProduct],rcx
            mov [HighProduct+8],rcx
        .endif
        mul Multiplicand
        ret

    .endif

    mov     r9,Multiplicand
    mul     Multiplicand        ; a * b
    push    rax
    mov     r10,rdx

    mov     rax,r9
    mul     rsi                 ; a[8] * b
    add     r10,rax
    mov     r11,rdx

    mov     rax,Multiplier
    mul     rcx                 ; a * b[8]
    add     r10,rax
    adc     r11,rdx
    mov     r9d,0
    adc     r9d,0

    .if HighProduct

        mov     rax,rsi
        mul     rcx             ; a[8] * b[8]
        add     rax,r11
        adc     rdx,r9
        mov     [HighProduct],rax
        mov     [HighProduct+8],rdx
    .endif

    pop     rax
    mov     rdx,r10
    ret

umul256 endp

    end
