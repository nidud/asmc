include wsub.inc

    .code

wsffirst proc wsub:ptr S_WSUB

    mov eax,wsub
    fbffirst([eax].S_WSUB.ws_fcb, [eax].S_WSUB.ws_count)
    ret

wsffirst endp

    END
