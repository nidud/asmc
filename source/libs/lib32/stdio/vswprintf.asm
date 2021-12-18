; VSWPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

vswprintf proc string:LPWSTR, format:LPWSTR, vargs:PVOID

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov eax,string
    mov o._ptr,eax
    mov o._base,eax
    _woutput(&o, format, vargs)
    mov ecx,o._ptr
    mov WORD PTR [ecx],0
    ret

vswprintf endp

    END
