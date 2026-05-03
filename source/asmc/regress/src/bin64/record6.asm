
; -- additional handling for C-type RECORD fields

ifndef __ASMC64__
    .x64
    .model flat
endif

option casemap:none

.template T
    x   dd ?
    record
     a  dd :  1 ?
     b  dd :  7 ?
     c  dd :  8 ?
     d  dd : 16 ?
    ends
   .ends

   .code

    assume  rcx:ptr T
    define  mem <[rcx]>

    cmp     mem.a, 0        ; TEST a,1
    cmp     mem.a, 1        ; MOV/AND/CMP
    cmp     mem.b, 0        ; TEST
    cmp     mem.b, 1        ; MOV/AND/CMP
    cmp     mem.c, 1        ; CMP
    test    mem.a, 1        ; TEST
    test    mem.b, 1        ; TEST
    test    mem.c, 1        ; TEST
    or      mem.a, 1        ; OR
    or      mem.b, 1        ; OR
    or      mem.c, 1        ; OR
    xor     mem.a, 1        ; XOR
    xor     mem.b, 1        ; XOR
    xor     mem.c, 1        ; XOR
    mov     mem.a, 1        ; OR
    mov     mem.a, 0        ; AND
    mov     mem.b, 1        ; AND/OR
    mov     mem.c, 1        ; MOV
    mov     mem.a, eax      ; AND/OR
    mov     mem.b, eax      ; SHL/AND/OR
    mov     mem.c, eax      ; MOV
    mov     mem.d, eax      ; MOV
    mov     eax, mem.a      ; MOV/AND
    mov     eax, mem.b      ; MOV/AND/SHR
    mov     eax, mem.c      ; MOVZX
    mov     eax, mem.d      ; MOVZX
    mov     mem.a, mem.a    ; MOV/AND+AND/OR
    mov     mem.b, mem.b    ; MOV/AND/SHR+SHL/AND/OR
    mov     mem.c, mem.c    ; MOVZX/MOV
    mov     mem.d, mem.d    ; MOVZX/MOV

    .if ( mem.a == 0 )      ; TEST/JNZ
    .endif
    .if ( mem.a == 1 )      ; TEST/JZ
    .endif

    end
