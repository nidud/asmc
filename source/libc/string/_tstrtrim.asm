; _TSTRTRIM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

_tstrtrim proc uses rbx string:LPTSTR

    ldr rbx,string
    add rbx,_tcslen(rbx)
ifdef _UNICODE
    add rbx,rax
endif
    .for ( : eax : eax-- )

        sub rbx,TCHAR
        .break .if TCHAR ptr [rbx] > ' '

        mov TCHAR ptr [rbx],0
    .endf
    ret

_tstrtrim endp

    END
