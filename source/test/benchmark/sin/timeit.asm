
define VALUE 1.57079632679489661923132169163975144209858469968755

procs equ <for x,<0,1,2>> ; add functions to test...
args_x macro
    movsd xmm0,VALUE
    exitm<>
    endm

include ../timeit.inc

option dllimport:<msvcrt>
externdef import sin:ptr_t
sin_t typedef proto :real8

.data
 info_0 db "msvcrt",0
 info_1 db "SSE",0
 info_2 db "FSIN",0

.code

validate_x proc uses rsi x
    ldr ecx,x
    lea rax,proc_p
    mov rsi,[rax+rcx*size_t]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif
    .if rsi
        assume rsi:ptr sin_t
        rsi(VALUE)
        printf("%d: %.14f\n", x, xmm0)
    .endif
    ret
    endp

main proc
    mov proc_p,sin
    procs
        validate_x(x)
        endm
    GetCycleCount(0, 3, 1, 4000)
    xor eax,eax
    ret
    endp
    end start
