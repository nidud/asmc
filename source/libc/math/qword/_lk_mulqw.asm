include intn.inc

.code

_lk_mulqw proc    ; ecx:ebx:edx:eax = edx:eax * ecx:ebx

    .if !edx && !ecx

        mul ebx
        xor ebx,ebx
        ret
    .endif

    push    ebp
    push    esi
    push    edi
    push    eax
    push    edx
    push    edx
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
    pop     edi
    pop     esi
    pop     ebp
    ret

_lk_mulqw endp

    end
