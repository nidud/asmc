; _TSPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc
include tchar.inc

    .code

_stprintf proc string:LPTSTR, format:LPTSTR, argptr:VARARG

  local o:_iobuf

    ldr rcx,string
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rcx
    mov o._base,rcx
    _toutput(&o, format, &argptr)
    mov rcx,o._ptr
    mov TCHAR ptr [rcx],0
    ret

_stprintf endp

    end
