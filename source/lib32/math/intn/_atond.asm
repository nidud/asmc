; _atond() - Converts a string to integer
;
include intn.inc

    .code

_atond proc uses esi edi ebx number:ptr, string:ptr, radix:dword, n:dword

    mov edi,number
    mov ecx,n
    xor eax,eax
    rep stosd
    mov edi,number
    mov esi,string
    mov al,[esi]
    .if al == '+' || al == '-'
        inc esi
    .endif
    push eax
    mov ebx,radix
    mov ecx,n
    add ecx,ecx
    mov n,ecx
    .while 1
        mov al,[esi]
        .break .if !al
        and eax,not 30h
        bt  eax,6
        sbb ecx,ecx
        and ecx,55
        sub eax,ecx
        mov ecx,n
        .repeat
            movzx edx,word ptr [edi]
            imul  edx,ebx
            add   eax,edx
            mov   [edi],ax
            add   edi,2
            shr   eax,16
        .untilcxz
        mov edi,number
        add esi,1
    .endw
    pop eax
    .if al == '-'
        mov eax,n
        shr eax,1
        _negnd(number, eax)
    .endif
    mov eax,number
    ret

_atond endp

    end
