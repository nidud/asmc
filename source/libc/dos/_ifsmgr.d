; _IFSMGR.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.data
 _ifsmgr db 0,0

.code

_init_ifsmgr proc private uses di bx

  local buffer[32]:byte

    lea     di,buffer
    mov     ax,ss
    mov     es,ax
    mov     ah,0x19
    int     0x21
    add     al,'A'
    mov     ah,':'
    mov     [di],ax
    mov     ax,'\'
    mov     [di+2],ax
    mov     dx,di
    mov     cx,32
    mov     ax,0x71A0
    stc
    int     0x21
    jc      .0
    and     bh,0x40
    jz      .0
    mov     _ifsmgr,0x71
    mov     _ifsmgr[1],bh
.0:
    ret

_init_ifsmgr endp

.pragma init(_init_ifsmgr, 38)

    end
