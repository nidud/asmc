include windows.inc
include tchar.inc

catch proto signo:int_t {
except:
    mov eax,ecx
    .if rcx
        lea rax,@F
        mov [r8].CONTEXT._Rip,rax
        mov eax,0
        retn
        @@:
        mov eax,1
    .endif
    }

.code

main proc frame:except argc:int_t

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

    end _tstart
