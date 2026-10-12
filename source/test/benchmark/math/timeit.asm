ifndef VALUE
define VALUE 1.0
endif

procs equ <for x,<0,1,2,3>> ; functions to test...
args_x macro
    movsd xmm0,VALUE
    exitm<>
    endm

include ../timeit.inc

option dllimport:<msvcrt>
externdef import FUNC:ptr_t
ifdef VALUE2
ifdef ISFLOAT
func_t typedef proto :real4, :real4
else
func_t typedef proto :real8, :real8
endif
else
ifdef ISFLOAT
func_t typedef proto :real4
else
func_t typedef proto :real8
endif
endif

.data
 info_0 db "MSVCRT",0
 info_1 db "SSE",0
 info_2 db "VECTOR",0
 info_3 db "FPU",0

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
        assume rsi:ptr func_t
ifdef VALUE2
        rsi(VALUE, VALUE2)
else
        rsi(VALUE)
endif
ifdef ISFLOAT
        cvtss2sd xmm0,xmm0
endif
ifdef VALUE2
        %fprintf(fp, "&FUNC&(&VALUE&, &VALUE2&) %d.asm: %.18f\n", x, xmm0)
else
        %fprintf(fp, "&FUNC&(&VALUE&) %d.asm: %.18f\n", x, xmm0)
endif
    .endif
    ret
    endp

main proc
    mov proc_p,FUNC
    procs
        validate_x(x)
        endm
    GetCycleCount(0, 3, 1, 4000)
    xor eax,eax
    ret
    endp
    end start
