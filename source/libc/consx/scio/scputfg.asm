include consx.inc

    .code

scputfg proc uses eax ecx edx x, y, l, a
    mov edx,a
    mov ecx,l
    and dl,0x0F
    .repeat
        getxya(x, y)
        and al,0xF0
        or  al,dl
        scputa(x, y, 1, eax)
        inc x
    .untilcxz
    ret
scputfg endp

    END
