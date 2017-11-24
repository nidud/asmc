include conio.inc
include wchar.inc

    .code

    option win64:rsp nosave

_cputws proc uses rsi string:LPWSTR

    .for rsi=rcx :: rsi+=2
        movzx eax,WORD PTR [rsi]
        .break .if !eax
        .break .if _putwch_nolock(eax) == WEOF
    .endf
    ret

_cputws endp

    end
