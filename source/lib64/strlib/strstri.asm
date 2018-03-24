include string.inc
include strlib.inc

    .code

strstri proc uses rsi dst:LPSTR, src:LPSTR

    mov rsi,strlen(rcx)
    memstri(dst, rsi, src, strlen(src))
    ret

strstri endp

    END
