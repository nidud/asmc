include string.inc

    .data
    s0 dd ?

    .code

strtok proc uses edx ebx s1:LPSTR, s2:LPSTR
    mov eax,s1
    .if eax
        mov s0,eax
    .endif
    mov ebx,s0
    .while byte ptr [ebx]
        mov ecx,s2
        mov al,[ecx]
        .while  al
            .break .if al == [ebx]
            inc ecx
            mov al,[ecx]
        .endw
        .break .if !al
        inc ebx
    .endw
    xor eax,eax
    cmp [ebx],al
    je  toend
    mov edx,ebx
    .while  byte ptr [ebx]
        mov ecx,s2
        mov al,[ecx]
        .while  al
            .if al == [ebx]
                mov [ebx],ah
                inc ebx
                jmp retok
            .endif
            inc ecx
            mov al,[ecx]
        .endw
        inc ebx
    .endw
retok:
    mov eax,edx
toend:
    mov s0,ebx
    ret
strtok  endp

    END
