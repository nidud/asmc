include stdlib.inc
include crtl.inc
include winbase.inc

.data
__argv	dd 0
_pgmptr dd 0

.code

Install:
    mov __argv,setargv( addr __argc, GetCommandLineA() )
    mov eax,[eax]
    mov _pgmptr,eax
    ret

pragma_init Install, 4

    end
