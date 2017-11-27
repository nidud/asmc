include intn.inc

option win64:rsp nosave noauto

.code

_mulow proc multiplier:ptr, multiplicand:ptr, highproduct:ptr

    mov r9,rdx

    mov rax,[rcx]
    mov rdx,[rcx+8]
    mov r10,[r9]
    mov r11,[r9+8]
    ;
    ; r11:r10:rdx:rax = rdx:rax * r11:r10
    ;
    .if !rdx && !r11
        mul     r10
        xor     r10,r10
    .else
        push    rsi
        push    rdi
        mul     r10
        mov     rsi,rdx
        mov     rdi,rax
        mov     rax,[rcx+8]
        mul     r11
        mov     r11,rdx
        xchg    r10,rax
        mov     rdx,[rcx+8]
        mul     rdx
        add     rsi,rax
        adc     r10,rdx
        adc     r11,0
        mov     rax,[rcx]
        mov     rdx,[r9+8]
        mul     rdx
        add     rsi,rax
        adc     r10,rdx
        adc     r11,0
        mov     rdx,rsi
        mov     rax,rdi
        pop     rdi
        pop     rsi
    .endif
    mov [rcx],rax
    mov [rcx+8],rdx
    .if r8
        mov [r8],r10
        mov [r8+8],r11
    .endif
    ret

_mulow endp

    end
