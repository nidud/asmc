ifdef _WIN64
procs equ <for x,<0,4,2,3>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov rcx,m_endp
ifdef _WIN64
    mov r8d,step_x
    sub rcx,r8
    mov edx,1
else
    sub ecx,step_x
    push step_x
    push 1
    push ecx
endif
    exitm<>
    endm

include ../timeit.inc

option dllimport:<msvcrt>
externdef import memchr:ptr_t

.data
info_0  db "msvcrt.memchr()",0
info_1  db "libc(__X86__)",0
info_2  db "libc(__SSE__)",0
info_3  db "libc(__AVX__)",0
info_4  db "libc(__AVX512__)",0

.code

memchr_t typedef proto :ptr, :dword, :size_t

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
        assume rsi:ptr memchr_t
        .if ( rsi(m_4096, 1, 4095) != 0 )
            mov rcx,rax
            printf("error%d: %06X [0] (%d) %d.asm\n", size_t*8, rcx, 4095, x)
            inc nerror
        .endif
        .if ( rsi(m_4096, 1, 4096) == 0 )
            mov rcx,rax
            printf("error%d: %06X [%06X] (%d) %d.asm\n", size_t*8, rcx, m_endp, 4096, x)
            inc nerror
        .endif
        .for ( ebx = 2 : ebx < 290 && nerror < 10 : ebx++ )
            mov rcx,m_endp
            sub rcx,rbx
            lea rdi,[rcx+rbx-1]
            .if ( rsi(rcx, 1, rbx) != rdi )
                mov rcx,rax
                printf("error%d: %06X [%06X] (%d) %d.asm\n", size_t*8, rcx, rdi, ebx, x)
                inc nerror
            .endif
        .endf
        assume rsi:nothing
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov rax,memchr
    mov proc_p,rax
    mov rdi,m_4096
    mov ecx,4095
    mov eax,'x'
    rep stosb
    mov byte ptr [rdi],1
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
    GetCycleCount(   0,  63,   3, 800)
    GetCycleCount(  64,1023, 120, 400)
    GetCycleCount(1024,4095, 250, 100)
    xor eax,eax
    ret
    endp
    end start
