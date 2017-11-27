include consx.inc

    .code

rsevent proc robj:ptr S_ROBJ, dobj:ptr S_DOBJ
    dlevent(dobj)
    mov ecx,dobj
    mov edx,[ecx+4]
    mov ecx,robj
    mov [ecx+6],edx
    ret
rsevent endp

    END
