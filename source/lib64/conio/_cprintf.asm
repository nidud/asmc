include conio.inc
include stdio.inc

    .code

_cprintf proc format:LPSTR, argptr:VARARG

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,_INTIOBUF
    lea rax,_bufin
    mov o._ptr,rax
    mov o._base,rax
    _output(addr o, format, addr argptr)
    mov rax,o._ptr
    mov byte ptr [rax],0
    _cputs(&_bufin)
    ret

_cprintf endp

    END
