; _mulnd() - Multiply
;
; Multiplication of multiplier by multiplicand with result placed
; in highproduct:multiplier.
;
include intn.inc
include alloc.inc

.code

_mulnd proc uses esi edi ebx multiplier:ptr, multiplicand:ptr, highproduct:ptr, n:dword

local nd, result

    mov eax,n
    shl eax,1
    mov nd,eax
    shl eax,2
    mov result,alloca(eax)

    .for edi=eax, esi=multiplier, ebx=multiplicand, ecx=0: ecx < n: ecx++, ebx += 4

        lodsd
        mul dword ptr [ebx]
        stosd
        mov eax,edx
        stosd
    .endf

    .for ebx=1, esi=multiplier, edi=multiplicand: ebx < n: ebx++

        .for ecx=1: ecx < n: ecx++

            mov eax,[esi+ebx*4-4]
            mul dword ptr [edi+ecx*4]
            _addq()
            mov eax,[esi+ebx*4]
            mul dword ptr [edi+ecx*4-4]
            _addq()
        .endf
    .endf

    mov esi,result
    mov edi,multiplier
    mov ecx,n
    rep movsd
    mov edi,highproduct
    .if edi
        mov ecx,n
        rep movsd
    .endif

    ret

_addq:  ; add qword to number on dword position

    push ebx
    push ecx
    mov ecx,ebx
    mov ebx,result
    add [ebx+ecx*4],eax
    adc [ebx+ecx*4+4],edx
    sbb edx,edx
    xor eax,eax
    .for ecx+=2: ecx < nd: ecx+=2
        shr edx,1
        adc [ebx+ecx*4],eax
        adc [ebx+ecx*4+4],eax
        sbb edx,edx
    .endf
    pop ecx
    pop ebx
    retn

_mulnd endp

    end
