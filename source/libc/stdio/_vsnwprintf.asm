; _VSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_vsnwprintf proc string:LPWSTR, count:size_t, format:LPWSTR, args:ptr

  local o:_iobuf

ifndef _WIN64
    mov ecx,string
    mov edx,count
endif
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,edx
    mov o._ptr,rcx
    mov o._base,rcx
    _woutput(addr o, format, args)
    mov rcx,o._ptr
    mov word ptr [rcx],0
    ret

_vsnwprintf endp

    end
