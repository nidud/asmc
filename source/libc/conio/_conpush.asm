; _CONPUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include malloc.inc

    .code

    assume rbx:PCONSOLE

_conpush proc uses rbx

ifdef __TTY__

    _write(_confd, CSI "?1049h", 8)  ; enables the alternative buffer
else
    mov rbx,_console
    .if ( _rcalloc([rbx].rc, 0) )

        _rcread([rbx].rc, rax)
        mov ecx,[rbx].rc
        mov rdx,[rbx].buffer
        mov rbx,rax
        _rcclear(ecx, rdx, 0x00070020)
        _conpaint()
        mov rax,rbx
    .endif
endif
    ret

_conpush endp

_conpop proc uses rbx p:PCHAR_INFO

ifdef __TTY__
    _write(_confd, CSI "?1049l", 8) ; disables the alternative buffer
else
    mov rbx,_console
    mov eax,[rbx].rc
    ldr rbx,p
    _rcwrite(eax, rbx)
    free(rbx)
endif
    ret

_conpop endp

    end
