; _atond() - Converts a string to integer
;
include intn.inc

option win64:rsp nosave noauto

    .code

_atond proc uses rdi number:ptr, string:ptr, radix:dword, n:dword

    mov r10,rcx
    mov rdi,rcx
    mov ecx,r9d
    xor rax,rax
    rep stosq
    mov al,[rdx]
    .if al == '+' || al == '-'
        inc rdx
    .endif
    push rax
    .while 1
        mov al,[rdx]
        .break .if !al
        and eax,not 0x30
        bt  eax,6
        sbb ecx,ecx
        and ecx,55
        sub eax,ecx
        mov ecx,r9d
        shl ecx,2
        mov r11,r10
        .repeat
            movzx edi,word ptr [r11]
            imul  edi,r8d
            add   eax,edi
            mov   [r11],ax
            add   r11,2
            shr   eax,16
        .untilcxz
        inc rdx
    .endw
    pop rdx
    .if dl == '-'
        _negnd(r10, r9d)
    .endif
    mov rax,r10
    ret

_atond endp

    end
