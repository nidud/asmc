include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

isleadbyte proc wc:SINT
    lea rax,_ctype
    mov ax,[rax+rcx*2+2]
    and eax,_LEADBYTE
    ret
isleadbyte endp

    end

