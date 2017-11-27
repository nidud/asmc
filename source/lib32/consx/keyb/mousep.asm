include consx.inc

    .code

mousep proc uses ecx edx

    ReadEvent()
    mov eax,edx
    shr eax,16
    and eax,3
    ret

mousep endp

    END
