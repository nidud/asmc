; _DOS_TIME.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

define DT_BASEYEAR 1980

.code

_dos_time proc

    mov     ah,0x2A
    int     0x21
    mov     ax,cx
    sub     ax,DT_BASEYEAR
    shl     ax,9
    xchg    ax,dx
    mov     cl,al
    mov     al,ah
    xor     ah,ah
    shl     ax,5
    xchg    ax,dx
    or      ax,dx
    or      al,cl
    push    ax
    mov     ah,0x2C ; CH = hour
    int     0x21    ; CL = minute
    xor     ax,ax   ; DH = second
    mov     al,dh
    shr     ax,1
    mov     dx,ax   ; second/2
    mov     al,ch
    mov     ch,ah
    shl     cx,5
    shl     ax,11
    or      ax,cx
    or      ax,dx   ; hhhhhmmmmmmsssss
    pop     dx
    ret

_dos_time endp

    end
