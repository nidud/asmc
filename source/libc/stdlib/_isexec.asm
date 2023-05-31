; _ISEXEC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code   ; Test if <ext> == bat | cmd | com | exe

_isexec proc filename:string_t

    ldr rcx,filename
    .if strext( rcx )

        mov ecx,[rax+1]
        or  ecx,'   '
        xor eax,eax

        .switch pascal ecx
        .case 'dmc' : mov eax,_EXEC_CMD
        .case 'exe' : mov eax,_EXEC_EXE
        .case 'moc' : mov eax,_EXEC_COM
        .case 'tab' : mov eax,_EXEC_BAT
        .endsw
    .endif
    ret

_isexec endp

    end
