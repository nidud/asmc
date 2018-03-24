    .code

_memicmp::

    mov r9,rdx
    .repeat

        .break .if !r8

        dec r8
        mov al,[rcx]
        cmp al,[r9]
        lea rcx,[rcx+1]
        lea r9,[r9+1]
        .continue(0) .ifz

        mov dl,[r9-1]
        mov ah,dl
        sub ax,'AA'
        cmp al,'Z'-'A' + 1
        sbb dl,dl
        and dl,'a'-'A'
        cmp ah,'Z'-'A' + 1
        sbb dh,dh
        and dh,'a'-'A'
        add ax,dx
        add ax,'AA'
        .continue(0) .if al == ah

        sbb al,al
        sbb al,-1
        movsx r8,al
    .until 1
    mov rax,r8
    ret

    end
