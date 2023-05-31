; _VSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include limits.inc

    .code

_vsnprintf proc string:LPSTR, count:size_t, format:LPSTR, args:ptr

  local o:_iobuf

    ldr rcx,string
    ldr rdx,count
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,edx
    mov o._ptr,rcx
    mov o._base,rcx
    _output(&o, format, args)
    mov rcx,o._ptr
    mov byte ptr [rcx],0
    ret

_vsnprintf endp

    end
