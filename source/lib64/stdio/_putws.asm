include stdio.inc
include conio.inc
include wchar.inc

    .code

_putws proc uses rsi rdi string:LPWSTR

    .for ( rsi=rcx, edi=0: word ptr [rsi] : rsi+=2, edi++ )

        movzx eax,word ptr [rsi]
        .if _putwch(eax) == WEOF

            movsx edi,ax
            .break
        .endif
    .endf
    mov eax,edi
    ret

_putws endp

    END
