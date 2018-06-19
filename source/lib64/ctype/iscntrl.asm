include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

iscntrl proc char:SINT
    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_CONTROL
    ret
iscntrl endp

    end

