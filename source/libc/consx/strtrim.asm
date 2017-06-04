include string.inc

    .code

strtrim PROC string:LPSTR
    .if strlen(string)
        mov ecx,eax
        add ecx,string
        .repeat
            dec ecx
            .break .if byte ptr [ecx] > ' '
            mov byte ptr [ecx],0
            dec eax
        .untilz
    .endif
    ret
strtrim ENDP

    END
