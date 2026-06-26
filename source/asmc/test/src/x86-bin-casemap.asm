
; v2.37 - casemap set on symbol creation

.486
.model flat
.code

option casemap:none

abc equ 1
ABC equ 2

option casemap:all

size_t typedef ptr

    mov eax,abc ; Asmc: 1, Masm: 2, JWasm: 1
    mov edx,ABC ; Asmc: 2, Masm: 2, JWasm: 1

option casemap:none

    mov eax,SIZE_T ; Asmc: 4, Masm: error, JWasm: error

    end
