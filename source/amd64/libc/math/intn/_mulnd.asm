; _mulnd() - Multiply
;
; Multiplication of multiplier by multiplicand with result placed
; in highproduct:multiplier.
;
include intn.inc
include alloc.inc

.code

_mulnd proc uses rsi rdi rbx multiplier:ptr, multiplicand:ptr, highproduct:ptr, n:dword

local nd, result:ptr

    mov eax,n
    shl eax,1
    mov nd,eax
    shl eax,3
    mov result,alloca(eax)

    .for rdi=rax, rsi=multiplier, rbx=multiplicand, ecx=0: ecx < n: ecx++, rbx += 8

        lodsq
        mul qword ptr [rbx]
        stosq
        mov rax,rdx
        stosq
    .endf

    .for ebx=1, rsi=multiplier, rdi=multiplicand: ebx < n: ebx++

        .for ecx=1: ecx < n: ecx++

            mov rax,[rsi+rbx*8-8]
            mul qword ptr [rdi+rcx*8]
            _addq()
            mov rax,[rsi+rbx*8]
            mul qword ptr [rdi+rcx*8-8]
            _addq()
        .endf
    .endf

    mov rsi,result
    mov rdi,multiplier
    mov ecx,n
    rep movsq
    mov rdi,highproduct
    .if rdi
        mov ecx,n
        rep movsq
    .endif

    ret

_addq:  ; add qword to number on dword position

    push rbx
    push rcx
    mov ecx,ebx
    mov rbx,result
    add [rbx+rcx*8],rax
    adc [rbx+rcx*8+8],rdx
    sbb edx,edx
    xor eax,eax
    .for ecx+=2: ecx < nd: ecx+=2
        shr edx,1
        adc [rbx+rcx*8],rax
        adc [rbx+rcx*8+8],rax
        sbb edx,edx
    .endf
    pop rcx
    pop rbx
    retn

_mulnd endp

    end
