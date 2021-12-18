; SPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

sprintf proc c string:LPSTR, format:LPSTR, argptr:VARARG

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov eax,string
    mov o._ptr,eax
    mov o._base,eax

    _output(&o, format, &argptr)

    mov ecx,o._ptr
    mov byte ptr [ecx],0
    ret

sprintf endp

    END
