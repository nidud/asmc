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

_rssave proc uses rbx hwnd:THWND, file:LPSTR

    .new d:TOBJ
    .new h:int_t = _sopen(file, O_BINARY or O_CREAT or O_TRUNC or O_WRONLY, SH_DENYNO, _S_IWRITE)
    .return .if ( h == -1 )

    ldr rbx,hwnd
    memcpy(&d, rbx, TOBJ)
    and d.flags,not (W_ISOPEN or W_VISIBLE)
    _write(h, &d, TOBJ)
    .for ( rbx = [rbx].object : rbx : rbx=[rbx].next )
        _write(h, rbx, TOBJ)
    .endf

   .new size:dword
   .new wp:ptr
    mov     rbx,hwnd
    movzx   eax,[rbx].rc.col
    mul     [rbx].rc.row
    shl     eax,4
    mov     wp,malloc(eax)
    mov     size,_rczip([rbx].rc, rax, [rbx].window)

    _write(h, wp, size)
    _close(h)

    free(wp)

   .return( 1 )

_rssave endp

    end
