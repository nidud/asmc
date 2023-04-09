; _SCPUTSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

_conpaint proto

    .code

_scputsA proc uses rbx x:BYTE, y:BYTE, string:LPSTR

    mov     r10,_console
    movzx   eax,[r10].TCONSOLE.rc.col
    mov     ecx,eax
    mul     sil
    and     edi,0xFF
    sub     ecx,edi
    add     edi,eax
    shl     edi,2
    add     rdi,[r10].TCONSOLE.buffer
    xor     eax,eax

    .for ( rbx = rdx : ecx && byte ptr [rbx] : ecx--, rbx++, rdi+=4 )

        mov al,[rbx]
        mov [rdi],ax
    .endf
    sub rbx,rdx
    .if ( [r10].TCONSOLE.paint > 0 )
        _conpaint()
    .endif
    .return( rbx )

_scputsA endp

    end
