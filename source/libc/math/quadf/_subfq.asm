include intn.inc

.code

_subfq proc r:ptr, a:ptr, b:ptr

    mov ecx,r
    mov eax,a
    mov edx,b
    _lk_subfq()
    ret

_subfq endp

    end
