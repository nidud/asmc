include intn.inc

.code

_addfq proc r:ptr, a:ptr, b:ptr

    mov ecx,r
    mov eax,a
    mov edx,b
    _lk_addfq()
    ret

_addfq endp

    end
