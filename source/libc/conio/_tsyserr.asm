; _TSYSERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include syserr.inc
include tchar.inc

.code

_syserr proc title:tstring_t, format:tstring_t, argptr:vararg

   .new msg:string_t = _sys_err_msg(_get_errno(NULL))

    _vstprintf(&_bufin, format, &argptr)
    lea rcx,_bufin
    lea rcx,[rcx+rax*TCHAR]
    mov eax,10
    mov [rcx],_tal
    mov [rcx+TCHAR],_tal
    add rcx,TCHAR*2

    .for ( rdx = msg : eax : rdx++, rcx+=TCHAR )

        mov al,[rdx]
        mov [rcx],_tal
    .endf

    _vmsgbox(MB_OK or MB_ICONERROR, title, &_bufin)
    xor eax,eax
    ret

_syserr endp

    end
