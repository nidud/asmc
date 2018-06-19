include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalnum proc char:SINT
    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_UPPER or _LOWER or _DIGIT
    ret
isalnum endp

    end

