include intn.inc

.code

_mulqw proc uses ebx multiplier:qword, multiplicand:qword, highproduct:ptr

    mov eax,dword ptr multiplier
    mov edx,dword ptr multiplier[4]
    mov ebx,dword ptr multiplicand
    mov ecx,dword ptr multiplicand[4]
    _lk_mulqw()
    push eax
    mov eax,highproduct
    .if eax
        mov [eax],ebx
        mov [eax+4],ecx
    .endif
    pop eax
    ret

_mulqw endp

    end
