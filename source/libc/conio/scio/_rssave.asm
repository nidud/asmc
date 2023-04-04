; _RSSAVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include sys/stat.inc
include share.inc
include fcntl.inc
include conio.inc
include malloc.inc
include string.inc

    .code

    assume rbx:THWND

_rssave proc uses rsi rdi rbx hwnd:THWND, file:LPWSTR

    .new d:TOBJ
    .new h:int_t = _wsopen(file,
            O_BINARY or O_CREAT or O_TRUNC or O_WRONLY, SH_DENYNO, _S_IWRITE)
    .if ( h == -1 )

        .return
    .endif

    mov rbx,hwnd
    memcpy(&d, rbx, TOBJ)
    and d.flags,not (W_ISOPEN or W_VISIBLE)
    _write(h, &d, TOBJ)

    .for ( rbx = [rbx].object : d.count : d.count--, rbx = [rbx].next )

        _write(h, rbx, TOBJ)
    .endf
    mov rbx,hwnd
    movzx eax,[rbx].rc.col
    mul [rbx].rc.row
    shl eax,4
    mov rdi,malloc(eax)
    mov esi,_rczip([rbx].rc, rdi, [rbx].window)
    _write(h, rdi, esi)
    _close(h)
   .return(1)

_rssave endp

    end
