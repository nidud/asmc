include stdlib.inc

.pragma comment(lib, extern)

DllProc proto WINAPI

    .code

main proc

    DllProc()
    exit(0)

main endp

    end main
