
pcg_state_setseq_64 struct
    state   dq ?
    _inc    dq ?
pcg_state_setseq_64 ends

procs  equ <for x,<0,1>> ; add functions to test...
args_x macro
    lea rcx,pcg32_global
    exitm<>
    endm

include ../timeit.inc

    .data
    info_0 db "pcg32",0
    info_1 db "rdrand",0

    pcg32_global pcg_state_setseq_64 { 0x853c49e6748fea9b, 0xda3e39cb94b95bdb }

    .code

main proc

    GetCycleCount(0, 3, 1, 1000)
    ret

main endp

    end start
