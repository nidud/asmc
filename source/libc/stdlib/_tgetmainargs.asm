; _TGETMAINARGS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

.code

_tgetmainargs proc pargc:ptr, pargv:ptr, penvp:ptr, dowildcard:int_t, startinfo:ptr _startupinfo

if 0

    mov rcx,startinfo
    mov _newmode,[rcx]._startupinfo.newmode

    _tsetargv(pargc, GetCommandLine())
    .if ( !rax )

        dec rax
       .return
    .endif
    mov rcx,pargv
    mov [rcx],rax

endif

    mov rcx,pargc
    mov [rcx],__argc
    mov rcx,pargv
    mov [rcx],__targv
    mov rcx,penvp
    mov [rcx],_tenviron
    xor eax,eax
    ret

_tgetmainargs endp

    end
