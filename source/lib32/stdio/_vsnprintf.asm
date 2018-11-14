; VSPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_vsnprintf proc string:LPSTR, count:size_t, format:LPSTR, vargs:PVOID

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov eax,count
    mov o._cnt,eax
    mov eax,string
    mov o._ptr,eax
    mov o._base,eax

    _output(&o, format, vargs)

    mov ecx,o._ptr
    mov BYTE PTR [ecx],0
    ret

_vsnprintf endp

    END
