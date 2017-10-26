include iost.inc
include string.inc

.code

oreadb proc uses ecx edx b:LPSTR, z

    mov eax,z
    oread()
    .ifnz
        memcpy(b, eax, z)
        mov ecx,z
    .else
        xor ecx,ecx
        mov edx,b
        .while ecx < z
            ogetc()
            .break .ifz
            mov [edx],al
            inc edx
            inc ecx
        .endw
    .endif
    mov eax,ecx
    ret

oreadb endp

    END
