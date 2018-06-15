include malloc.inc
include string.inc

    .code

_strdup proc string:LPSTR

    .if strlen(rcx)

        inc rax
        .if malloc(rax)

            strcpy(rax, string)
        .endif
    .endif
    ret

_strdup endp

    end
