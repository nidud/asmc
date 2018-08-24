include stdlib.inc

    .data
    holdrand dword 1

    .code
    option win64:rsp nosave

srand proc seed:UINT

    mov holdrand,ecx
    ret

srand endp

rand proc

    mov eax,214013
    mul holdrand
    add eax,2531011
    mov holdrand,eax
    shr eax,16
    and eax,0x7fff
    ret

rand endp

    END
