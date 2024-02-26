; _TVSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include limits.inc
include tchar.inc

    .code

_vsntprintf proc string:LPTSTR, count:size_t, format:LPTSTR, args:ptr

  local o:_iobuf

    ldr rcx,string
    ldr rdx,count
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,edx
    mov o._ptr,rcx
    mov o._base,rcx
    _toutput(&o, format, args)
    mov rcx,o._ptr
    mov TCHAR ptr [rcx],0
    ret

_vsntprintf endp

    end
