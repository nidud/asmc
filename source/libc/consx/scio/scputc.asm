include consx.inc

    .code

scputc proc uses eax ecx edx x, y, l, char

    local NumberOfCharsWritten

    movzx ecx,byte ptr char
    movzx eax,byte ptr x
    movzx edx,byte ptr y
    shl   edx,16
    mov   dx,ax

    FillConsoleOutputCharacter(
        hStdOutput,
        ecx,
        l,
        edx,
        &NumberOfCharsWritten)
    ret

scputc endp

    END
