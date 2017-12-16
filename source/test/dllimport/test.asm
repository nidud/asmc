include stdlib.inc

option dllimport:<extern>
DllProc proto

    .code

main proc

    DllProc()
    exit(0)

main endp

    end main
