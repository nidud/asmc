include consx.inc

    .code

tiretevent proc
    mov eax,_TE_RETEVENT ; return current event (keystroke)
    ret
tiretevent endp

    END
