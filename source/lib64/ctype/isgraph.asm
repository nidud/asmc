include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

isgraph proc char:SINT
    mov eax,ecx
    .if al < 0x21 || al >= 0x7F
        xor eax,eax
    .endif
    ret
isgraph endp

    END
