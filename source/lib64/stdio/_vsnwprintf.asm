; _VSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

    option win64:rsp nosave

_vsnwprintf proc string:LPWSTR, count:size_t, format:LPWSTR, vargs:PVOID

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,edx
    mov o._ptr,rcx
    mov o._base,rcx
    _woutput(addr o, r8, r9)
    mov rcx,o._ptr
    mov word ptr [rcx],0
    ret

_vsnwprintf endp

    END
