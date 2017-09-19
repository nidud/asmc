include stdio.inc
include limits.inc

    .code

vsprintf proc uses ecx string:LPSTR, format:LPSTR, vargs:PVOID

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov eax,string
    mov o._ptr,eax
    mov o._base,eax

    _output(&o, format, vargs)

    mov ecx,o._ptr
    mov BYTE PTR [ecx],0
    ret

vsprintf endp

    END
