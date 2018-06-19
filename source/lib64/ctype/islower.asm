include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

islower proc char:SINT
    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_LOWER
    ret
islower endp

    end

