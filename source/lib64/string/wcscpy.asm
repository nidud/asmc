    .code

wcscpy::

    mov rax,rcx
    xor ecx,ecx
    .repeat
        mov r8w,[rdx+rcx]
        mov [rax+rcx],r8w
        add ecx,2
    .until !r8w
    ret

    end
