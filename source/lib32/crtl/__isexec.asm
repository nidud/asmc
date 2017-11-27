include crtl.inc
include strlib.inc

    .code   ; Test if <ext> == bat | cmd | com | exe

__isexec proc filename:LPSTR

    .if strext(filename)

        mov eax,[eax+1]
        or  eax,'   '

        .switch eax

          .case 'dmc':  mov eax,_EXEC_CMD: .endc
          .case 'exe':  mov eax,_EXEC_EXE: .endc
          .case 'moc':  mov eax,_EXEC_COM: .endc
          .case 'tab':  mov eax,_EXEC_BAT: .endc

          .default
            xor eax,eax
        .endsw
    .endif
    ret

__isexec endp

    END
