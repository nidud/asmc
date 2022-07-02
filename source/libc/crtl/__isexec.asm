; __ISEXEC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code   ; Test if <ext> == bat | cmd | com | exe

__isexec proc filename:string_t

    .if strext( filename )

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

__isexec endp

    end
