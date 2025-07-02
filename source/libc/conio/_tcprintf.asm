; _TCPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc
include tchar.inc

    .code

_tcprintf proc format:tstring_t, argptr:vararg

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,_INTIOBUF
    lea rax,_bufin
    mov o._ptr,rax
    mov o._base,rax
    _toutput(&o, format, &argptr)
    mov rax,o._ptr
    mov tchar_t ptr [rax],0
    _cputts(&_bufin)
    ret

_tcprintf endp

    end
