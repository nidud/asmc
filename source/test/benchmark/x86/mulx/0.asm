    .486
    .model flat, stdcall
    .code

_mul128 proc Multiplier:qword, Multiplicand:qword, Highproduct:ptr

    mov ecx,Highproduct
    mov eax,dword ptr Multiplier[4]

    .if !dword ptr Multiplicand[4] && !eax

        mov     [ecx+8],eax
        mov     [ecx+12],eax
        mov     eax,dword ptr Multiplier
        mul     dword ptr Multiplicand
        mov     [ecx],eax
        mov     [ecx+4],edx

    .else

        mul     dword ptr Multiplicand
        mov     [ecx+4],eax
        mov     eax,dword ptr Multiplier
        mul     dword ptr Multiplicand
        mov     [ecx],eax
        add     [ecx+4],edx
        mov     eax,dword ptr Multiplicand[4]
        mul     dword ptr Multiplier
        add     [ecx+4],eax
        adc     edx,0
        mov     [ecx+8],edx
        mov     eax,dword ptr Multiplicand[4]
        mul     dword ptr Multiplier[4]
        add     [ecx+8],eax
        adc     edx,0
        mov     [ecx+12],edx

    .endif
    ret

_mul128 endp

    end
