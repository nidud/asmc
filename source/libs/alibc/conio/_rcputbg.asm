; _RCPUTBG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputbg proc w:TRECT, rc:TRECT, p:PCHAR_INFO, a:uchar_t

     shr edi,24
     shl cl,4

    .for ( : rc.row : rc.row--, rc.y++ )

        mov     eax,edi
        mul     rc.y
        movzx   esi,rc.x
        add     esi,eax
        shl     esi,2
        add     rsi,rdx

        .for ( r8b = 0 : r8b < rc.col : r8b++, rsi += 4 )

            mov al,[rsi+2]
            and al,0x0F
            or  al,cl
            mov [rsi+2],al
        .endf
    .endf
    ret

_rcputbg endp

    end
