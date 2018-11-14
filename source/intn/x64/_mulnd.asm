; _MULND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _mulnd() - Multiply
;
; Multiplication of multiplier by multiplicand with result placed
; in highproduct:multiplier.
;
include intn.inc
include malloc.inc

.code

_mulnd proc uses rsi rdi rbx multiplier:ptr, multiplicand:ptr, highproduct:ptr, n:dword

    mov eax,r9d
    shl eax,1
    mov r10d,eax
    shl eax,3
    mov r9,alloca(eax)

    .for ( rdi = rax, rsi = multiplier, rbx = multiplicand, ecx = 0: ecx < n: ecx++, rbx += 8 )

        lodsq
        mul qword ptr [rbx]
        stosq
        mov rax,rdx
        stosq
    .endf

    .for ( ebx = 1, rsi = multiplier, rdi = multiplicand: ebx < n: ebx++ )

        .for ( ecx = 1: ecx < n: ecx++ )

            mov rax,[rsi+rbx*8-8]
            mul qword ptr [rdi+rcx*8]

            mov r8,rbx
            add [r9+r8*8],rax
            adc [r9+r8*8+8],rdx
            sbb edx,edx
            xor eax,eax

            .for ( r8d += 2: r8d < r10d: r8d += 2 )

                bt  edx,0
                adc [r9+r8*8],rax
                adc [r9+r8*8+8],rax
                sbb edx,edx
            .endf

            mov rax,[rsi+rbx*8]
            mul qword ptr [rdi+rcx*8-8]

            mov r8,rbx
            add [r9+r8*8],rax
            adc [r9+r8*8+8],rdx
            sbb edx,edx
            xor eax,eax

            .for ( r8d += 2: r8d < r10d: r8d += 2 )

                bt  edx,0
                adc [r9+r8*8],rax
                adc [r9+r8*8+8],rax
                sbb edx,edx
            .endf
        .endf
    .endf

    mov rsi,r9
    mov rdi,multiplier
    mov ecx,n
    rep movsq
    mov rdi,highproduct
    .if rdi
        mov ecx,n
        rep movsq
    .endif
    ret

_mulnd endp

    end
