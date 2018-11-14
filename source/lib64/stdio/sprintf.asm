; SPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

sprintf proc uses rcx string:LPSTR, format:LPSTR, argptr:VARARG

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rcx
    mov o._base,rcx

    _output(addr o, format, addr argptr)

    mov rcx,o._ptr
    mov byte ptr [rcx],0
    ret

sprintf endp

    END
