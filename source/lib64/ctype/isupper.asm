include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

isupper proc char:SINT
    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_UPPER
    ret
isupper endp

    end

