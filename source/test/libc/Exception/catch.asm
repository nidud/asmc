include windows.inc

catch proto signo:int_t {
__except:
    mov eax,signo
    .if eax
        lea rax,@F
        mov [r8].CONTEXT._Rip,rax
        xor eax,eax
        retn
        @@:
        mov eax,1
    .endif
    }

.code

main proc frame:__except argc:dword

    xor eax,eax
    .if ecx > 1
        mov eax,[rax] ; gpf
    .endif
    MessageBox(0, "No Exception", "Catch", 0)

    .if catch(0)

        MessageBox(0, "Exception error: argc used", "Catch error", 0)
    .endif
    ExitProcess(0)
    ret

main endp

    end
