; SWPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

swprintf proc string:LPWSTR, format:LPWSTR, argptr:VARARG

  local o:_iobuf

ifndef _WIN64
    mov ecx,string
endif
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rcx
    mov o._base,rcx

    _woutput(addr o, format, addr argptr)

    mov rcx,o._ptr
    mov word ptr [rcx],0
    ret

swprintf endp

    end
