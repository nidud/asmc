include string.inc

    .code

    option win64:rsp nosave noauto

wcscmp proc s1:LPWSTR, s2:LPWSTR

    mov eax,0xFFFF

    .repeat

        .break .if !eax

        mov ax,[rdx]
        add rdx,2
        cmp ax,[rcx]
        lea rcx,[rcx+2]
        .continue(0) .ifz
        sbb ax,ax
        sbb ax,-1
    .until 1
    movsx eax,ax
    ret

wcscmp endp

    END
