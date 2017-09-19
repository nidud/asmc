include consx.inc

wcputxg proto

    .code

wcputbg proc uses ecx ebx wp:PVOID, l, attrib
    mov eax,attrib
    mov ah,0x0F
    and al,0xF0
    mov ecx,l
    mov ebx,wp
    wcputxg()
    ret
wcputbg endp

    END
