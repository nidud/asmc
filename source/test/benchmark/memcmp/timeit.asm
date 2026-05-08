procs equ <for x,<0,1,2>> ; functions to test...
args_x macro
ifdef _WIN64
    mov rcx,arg_1
    mov rdx,arg_2
    mov r8d,step_x
else
    push proc_x ; for (missing) relocation in 32-bit
    push step_x
    push arg_2
    push arg_1
endif
    exitm<>
    endm

include ../timeit.inc

option dllimport:<msvcrt>
externdef import memcmp:ptr_t

.data
align 16
str_1 db 4096 dup('x')
arg_1 ptr_t str_1
arg_2 ptr_t 0

info_0  db "msvcrt.memcmp()",0
info_1  db "libc(__x86__)",0
info_2  db "libc(__AVX__)",0

.code

memcmp_t typedef proto :ptr, :ptr, :size_t

validate_x proc uses rsi rdi rbx x

    ldr ecx,x
    lea rax,proc_p
    mov rsi,[rax+rcx*size_t]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif
    .if rsi
        assume rsi:ptr memcmp_t
ifndef _WIN64
        push proc_x
endif
        .if ( rsi(arg_1, arg_2, 4096) != 0 )
            mov rcx,rax
            printf("error%d: %d [0] %d.asm\n", size_t*8, ecx, x)
            inc nerror
        .endif
        mov str_1[4096-1],0
        .if ( rsi(arg_1, arg_2, 4096) == 0 )
            mov rcx,rax
            printf("error%d: 0 [-1] %d.asm\n", size_t*8, x)
            inc nerror
        .endif
        mov str_1[4096-1],'x'
        .for ( ebx = 1 : ebx < 90 && nerror < 20 : ebx++ )
            .if ( rsi(arg_1, arg_2, rbx) != 0 )
                mov ecx,eax
                printf("error%d: %d [0] (%d) %d.asm\n", size_t*8, ecx, ebx, x)
                inc nerror
            .endif
        .endf
ifndef _WIN64
        add esp,4
endif
        assume rsi:nothing
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov proc_p,memcmp
    mov rdi,m_4096
    mov arg_2,rdi
    mov ecx,4096/4
    mov eax,'xxxx'
    rep stosd
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
    GetCycleCount(   0,   15,   1, 1000)
    GetCycleCount(  16,  256,  64, 1000)
    GetCycleCount( 512, 1024, 128,  800)
    GetCycleCount(4096, 4096,   1,  500)
    xor eax,eax
    ret
    endp
    end start
