include string.inc

    .code

strcat proc s1:LPSTR, s2:LPSTR

    strlen(rcx)
    add rax,s1
    strcpy(rax,s2)
    mov rax,s1
    ret

strcat endp

    END
