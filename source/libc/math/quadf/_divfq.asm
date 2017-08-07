include intn.inc

.code

_divfq proc r:ptr, a:ptr, b:ptr

    mov ecx,r
    mov eax,a
    mov edx,b
    _lk_divfq()
    ret

_divfq endp

    end
