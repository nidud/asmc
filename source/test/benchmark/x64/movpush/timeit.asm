
procs  equ <for x,<0,1>> ; add functions to test...
args_x macro
    exitm<>
    endm

include ../timeit.inc

    .data
    info_0 db "push",0
    info_1 db "move",0

    .code

main proc

    GetCycleCount(0, 3, 1, 3000)
    ret

main endp

    end start
