include alloc.inc
include string.inc

    .code

_strdup proc string:LPSTR

    mov eax,string
    .if eax
        .if malloc(&[strlen(eax)+1])

            strcpy(eax, string)
        .endif
    .endif
    ret

_strdup endp

    END
