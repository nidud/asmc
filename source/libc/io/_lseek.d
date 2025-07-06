; _LSEEK.--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_lseek proc uses bx fd:int_t, offs:dword, pos:uint_t

    mov ax,0x4200
    add ax,pos
    mov bx,fd
    mov cx,word ptr offs+2
    mov dx,word ptr offs
    int 0x21
    .ifc
.0:
        _dosmaperr( ax )
        cwd

    .elseif ( ax == -1 && dx == -1 )

        xor cx,cx
        xor dx,dx
        mov ax,0x4200
        int 0x21
        mov ax,ERROR_NEGATIVE_SEEK
        jmp .0
    .endif
    ret

_lseek endp

    end
