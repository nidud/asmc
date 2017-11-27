include stdio.inc

    .code

ftobufin proc c format:LPSTR, argptr:VARARG

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,_INTIOBUF
    mov _bufin,0
    mov eax,offset _bufin
    mov o._ptr,eax
    mov o._base,eax
    _output(addr o, format, dword ptr argptr)

    mov edx,o._ptr
    mov byte ptr [edx],0
    lea edx,_bufin
    ret

ftobufin endp

    END
