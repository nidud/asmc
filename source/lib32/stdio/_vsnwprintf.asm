; VSPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_vsnwprintf proc string:LPWSTR, count:size_t, format:LPWSTR, vargs:PVOID

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov eax,count
    mov o._cnt,eax
    mov eax,string
    mov o._ptr,eax
    mov o._base,eax

    _woutput(&o, format, vargs)

    mov ecx,o._ptr
    mov word ptr [ecx],0
    ret

_vsnwprintf endp

    END
