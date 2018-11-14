; _VSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

    option win64:rsp nosave

_vsnprintf proc string:LPSTR, count:size_t, format:LPSTR, vargs:PVOID

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,edx
    mov o._ptr,rcx
    mov o._base,rcx
    _output(addr o, r8, r9)
    mov rcx,o._ptr
    mov byte ptr [rcx],0
    ret

_vsnprintf endp

    END
