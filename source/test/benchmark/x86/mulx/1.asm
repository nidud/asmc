    .686
    .xmm
    .model flat, stdcall
    .code

_mul128 proc Multiplier:qword, Multiplicand:qword, Highproduct:ptr

    mov ecx,Highproduct
    mov edx,dword ptr Multiplier[4]
    mov eax,dword ptr Multiplicand[4]

    .if edx || eax

        mulx    edx,eax,dword ptr Multiplicand
        mov     [ecx+4],eax
        mov     edx,dword ptr Multiplier
        mulx    edx,eax,dword ptr Multiplicand
        mov     [ecx],eax
        add     [ecx+4],edx
        mov     edx,dword ptr Multiplicand[4]
        mulx    edx,eax,dword ptr Multiplier
        add     [ecx+4],eax
        adc     edx,0
        mov     [ecx+8],edx
        mov     edx,dword ptr Multiplicand[4]
        mulx    edx,eax,dword ptr Multiplier[4]
        add     [ecx+8],eax
        adc     edx,0
        mov     [ecx+12],edx

    .else

        mov     [ecx+8],edx
        mov     [ecx+12],edx
        mov     edx,dword ptr Multiplier
        mulx    edx,eax,dword ptr Multiplicand
        mov     [ecx],eax
        mov     [ecx+4],edx
    .endif
    ret

_mul128 endp

    end
