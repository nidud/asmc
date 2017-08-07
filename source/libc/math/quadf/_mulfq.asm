include intn.inc

.code

_mulfq proc r:ptr, a:ptr, b:ptr

    mov ecx,r
    mov eax,a
    mov edx,b
    _lk_mulfq()
    ret

_mulfq endp

    end
