; _RCPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputc proc w:TRECT, rc:TRECT, p:PCHAR_INFO, c:wchar_t

    .for ( : rc.row : rc.row--, rc.y++ )

        movzx   eax,w.col
        mul     rc.y
        movzx   edx,rc.x
        add     edx,eax
        shl     edx,2
        add     rdx,p
        mov     ax,c

        .for ( cl = 0 : cl < rc.col : cl++, rdx += 4 )

            mov [rdx],ax
        .endf
    .endf
    ret

_rcputc endp

    end
