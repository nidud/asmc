include errno.inc
include winbase.inc

    .code

_getdrive proc

  local b[512]:byte

    .if GetCurrentDirectory(512, &b)

ifdef _UNICODE
        mov al,b
        mov ah,b[2]
else
        mov ax,word ptr b
endif
        .if ah == ':'

            movzx eax,al
            or    al,0x20
            sub   al,'a' - 1  ; A: == 1
        .else
            xor eax,eax
        .endif
    .else
        osmaperr()
    .endif
    ret

_getdrive endp

    END
