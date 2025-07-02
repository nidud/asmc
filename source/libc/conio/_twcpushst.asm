; _TWCPUSHST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
     rc TRECT <>

    .code

wcpushst proc uses rbx p:PCHAR_INFO, cp:tstring_t

    ldr     rbx,p

    mov     rdx,_console
    mov     cl,[rdx].TCONSOLE.rc.col
    mov     ch,1
    shl     ecx,16
    mov     ch,[rdx].TCONSOLE.rc.row
    dec     ch
    mov     rc,ecx
    _at     BG_MENU,FG_KEYBAR,' '
    movzx   ecx,rc.col
    invoke  wcputw(rbx, ecx, eax)
    mov     eax,U_LIGHT_VERTICAL
    mov     [rbx+18*4],ax
    movzx   eax,rc.col
    invoke  wcputs(&[rbx+4], eax, eax, cp)
    invoke  _rcxchg(rc, rbx)
    ret

wcpushst endp

wcpopst proc wp:PCHAR_INFO

    ldr     rcx,wp
    invoke  _rcxchg(rc, rcx)
    ret

wcpopst endp

    END
