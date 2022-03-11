; __ISEXEC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code   ; Test if <ext> == bat | cmd | com | exe

__isexec proc filename:LPSTR

    .if strext(rcx)

        mov ecx,[rax+1]
        or  ecx,'   '
        xor eax,eax

        .switch ecx
          .case 'dmc': mov eax,_EXEC_CMD: .endc
          .case 'exe': mov eax,_EXEC_EXE: .endc
          .case 'moc': mov eax,_EXEC_COM: .endc
          .case 'tab': mov eax,_EXEC_BAT: .endc
        .endsw
    .endif
    ret

__isexec endp

    end
