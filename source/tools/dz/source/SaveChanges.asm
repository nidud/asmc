include tinfo.inc

externdef IDD_TESave:dword

    .code

SaveChanges proc uses esi file:LPSTR

    .if rsopen(IDD_TESave)

        mov esi,eax
        dlshow(eax)
        sub ecx,ecx
        mov cl,[esi][6]
        sub cl,10
        mov ax,[esi][4]
        add ax,0205h
        mov dl,ah
        scpath(eax, edx, ecx, file)
        rsevent(IDD_TESave, esi)
        dlclose(esi)
        mov eax,edx
    .endif
    ret

SaveChanges endp

    END
