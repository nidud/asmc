include consx.inc

wcputxg proto

    .code

wcputa proc uses ecx ebx wp:PVOID, l, attrib
    mov ebx,wp
    mov eax,attrib
    mov ecx,l
    and eax,0xFF
    wcputxg()
    ret
wcputa endp

    END
