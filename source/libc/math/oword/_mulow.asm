include intn.inc

.code

_mulow proc uses esi edi ebx multiplier:ptr, multiplicand:ptr, highproduct:ptr

local n[8] ; 256-bit result

    mov edi,multiplier
    mov esi,multiplicand

    mov eax,[edi]
    mov edx,[edi+4]
    mov ebx,[esi]
    mov ecx,[esi+4]
    _lk_mulqw()
    mov n[0],eax
    mov n[4],edx
    mov n[8],ebx
    mov n[12],ecx
    xor eax,eax
    mov n[16],eax
    mov n[20],eax
    mov n[24],eax
    mov n[28],eax

    mov eax,[edi+8]
    mov edx,[edi+12]
    mov ebx,[esi+8]
    mov ecx,[esi+12]
    _lk_mulqw()
    mov n[16],eax
    mov n[20],edx
    mov n[24],ebx
    mov n[28],ecx

    mov eax,[edi]
    mov edx,[edi+4]
    mov ebx,[esi+8]
    mov ecx,[esi+12]
    _lk_mulqw()
    add n[8],eax
    adc n[12],edx
    adc n[16],ebx
    adc n[20],ecx
    adc n[24],0
    adc n[28],0

    mov eax,[edi+8]
    mov edx,[edi+12]
    mov ebx,[esi]
    mov ecx,[esi+4]
    _lk_mulqw()
    add n[8],eax
    adc n[12],edx
    adc n[16],ebx
    adc n[20],ecx
    adc n[24],0
    adc n[28],0

    mov eax,n[0]
    mov edx,n[4]
    mov ebx,n[8]
    mov ecx,n[12]
    mov [edi],eax
    mov [edi+4],edx
    mov [edi+8],ebx
    mov [edi+12],ecx

    mov edi,highproduct
    .if edi
        mov eax,n[16]
        mov edx,n[20]
        mov ebx,n[24]
        mov ecx,n[28]
        mov [edi],eax
        mov [edi+4],edx
        mov [edi+8],ebx
        mov [edi+12],ecx
    .endif
    ret

_mulow endp

    end
