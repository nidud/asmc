include stdio.inc
include conio.inc
include wchar.inc

    .code

_putws proc uses esi edi string:LPWSTR

    .for ( esi=string, edi=0: word ptr [esi] : esi+=2, edi++ )

        movzx eax,word ptr [esi]
        .if _putwch(eax) == WEOF

            movsx edi,ax
            .break
        .endif
    .endf
    mov eax,edi
    ret

_putws endp

    END
