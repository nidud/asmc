include stdio.inc
include limits.inc

    .code

    option win64:rsp nosave

vsprintf proc uses rcx string:LPSTR, format:LPSTR, vargs:PVOID

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rcx
    mov o._base,rcx
    _output(addr o, rdx, r8)
    mov rcx,o._ptr
    mov byte ptr [rcx],0

    ret
vsprintf endp

    END
