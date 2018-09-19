include winnt.inc

    .code

_mul128 proc Multiplier:qword, Multiplicand:qword, Highproduct:ptr

    mov eax,dword ptr Multiplier
    mov edx,dword ptr Multiplier[4]
    mov ecx,dword ptr Multiplicand[4]

    .if !edx && !ecx

        .if Highproduct

            mov ecx,Highproduct
            mov [ecx],edx
            mov [ecx+4],edx
        .endif
        mul dword ptr Multiplicand
    .else

        push    ebx
        push    esi
        push    edi
        push    ebp
        push    eax
        push    edx
        push    edx
        mov     ebx,dword ptr Multiplicand
        mul     ebx
        mov     esi,edx
        mov     edi,eax
        pop     eax
        mul     ecx
        mov     ebp,edx
        xchg    ebx,eax
        pop     edx
        mul     edx
        add     esi,eax
        adc     ebx,edx
        adc     ebp,0
        pop     eax
        mul     ecx
        add     esi,eax
        adc     ebx,edx
        adc     ebp,0
        mov     ecx,ebp
        mov     edx,esi
        mov     eax,edi
        pop     ebp
        mov     edi,Highproduct

        .if edi

            mov [edi],ebx
            mov [edi+4],ecx
        .endif
        pop     edi
        pop     esi
        pop     ebx

    .endif
    ret

_mul128 endp

    end
