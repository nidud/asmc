;
; v2.37.20 - const divide
;
ifdef __JWASM__
ifndef __ASMC64__
    .x64
    .model flat
endif
endif

    .code

    mov rax,-1 / 16
    mov rax,0FFFFFFFFFFFFFFFFh / 16
    mov rax,0FFFFFFFFFFFFFFFFh / -16
    mov rax,0FFFFFFFFFFFFFFFFh / -15
    mov rax,0FFFFFFFFFFFFFFFFh / 0FFFFFFFFFFFFFFF0h

    mov rcx,-1 mod 16
    mov rcx,0FFFFFFFFFFFFFFFFh mod 16
    mov rcx,0FFFFFFFFFFFFFFFFh mod -16
    mov rcx,0FFFFFFFFFFFFFFFFh mod -15
    mov rcx,0FFFFFFFFFFFFFFFFh mod 0FFFFFFFFFFFFFFF0h

    end

