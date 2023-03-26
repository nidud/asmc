; _CWPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_cwprintf proc format:wstring_t, argptr:vararg

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,_INTIOBUF
    lea rax,_bufin
    mov o._ptr,rax
    mov o._base,rax
    _woutput(&o, format, &argptr)
    mov rax,o._ptr
    mov wchar_t ptr [rax],0
    _cputws(&_bufin)
    ret

_cwprintf endp

    end
