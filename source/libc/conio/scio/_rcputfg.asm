; _RCPUTFG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputfg proc w:TRECT, rc:TRECT, p:PCHAR_INFO, a:uchar_t

    .for ( : rc.row : rc.row--, rc.y++ )

        movzx   eax,w.col
        mul     rc.y
        movzx   edx,rc.x
        add     edx,eax
        shl     edx,2
        add     rdx,p
        mov     ah,a

        .for ( cl = 0 : cl < rc.col : cl++, rdx += 4 )

            mov al,[rdx+2]
            and al,0xF0
            or  al,ah
            mov [rdx+2],al
        .endf
    .endf
    ret

_rcputfg endp

    end
