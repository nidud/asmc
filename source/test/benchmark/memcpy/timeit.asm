ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3,4>>
endif
args_x macro
ifdef _WIN64
    mov rcx,arg_1
    mov rdx,arg_2
    mov r8d,step_x
else
    push step_x
    push arg_2
    push arg_1
endif
    exitm<>
    endm

include ../timeit.inc
option  dllimport:<msvcrt>
externdef import memcpy:ptr_t

.data?
 str_1  db 4096 dup(?)
 arg_1  ptr_t ?
 arg_2  ptr_t ?

.data
 info_0 db "msvcrt.memcpy()",0
 info_1 db "libc(__X86__)",0
 info_2 db "libc(__SSE__)",0
 info_3 db "libc(__AVX__)",0
 info_4 db "libc(__AVX512__)",0

.code

memcpy_t typedef proto :ptr, :ptr, :size_t

validate_x proc uses rsi rdi rbx x:dword

    ldr ecx,x
    lea rax,proc_p
    mov rsi,[rax+rcx*size_t]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif
    .if rsi
        assume rsi:ptr memcpy_t
        .for ( ebx = 1 : ebx < 140 && nerror < 12 : ebx++ )

            mov rdi,arg_1
            mov al,'?'
            lea rcx,[rbx+16]
            rep stosb
            mov [rdi],ecx
            mov rdi,arg_2
            mov al,'x'
            lea rcx,[rbx+16]
            rep stosb
            mov [rdi],ecx
            rsi(arg_1, arg_2, rbx)
            xor edx,edx
            mov rdi,arg_2
            mov rcx,arg_1
            .if ( edx != [rdi+rbx+16] )
                inc edx
            .elseif ( edx != [rcx+rbx+16] )
                inc edx
            .elseif rax != rcx
                inc edx
            .else
                mov rcx,rbx
                .repeat
                    .if byte ptr [rax+rcx-1] != 'x'
                        inc edx
                    .endif
                .untilcxz
                lea rdi,[rax+rbx]
                mov ecx,16
                .repeat
                    .if byte ptr [rdi+rcx-1] != '?'
                        inc edx
                    .endif
                .untilcxz
            .endif
            .if edx
                mov rdi,arg_1
                mov rdx,rax
                printf("error: %06X [%06X] %06X (%d) %d.asm: %s\n",edx,rdi,arg_2,ebx,x,rdi)
                inc nerror
            .endif
            mov rcx,arg_1
            mov rdx,arg_2
            mov arg_1,rdx
            mov arg_2,rcx
        .endf
        assume rsi:nothing
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov proc_p,memcpy
    mov rax,m_4096
    mov arg_2,rax
    lea rdi,str_1
    mov arg_1,rdi
    mov ecx,4096
    mov al,'x'
    rep stosb
    xor eax,eax
    stosb
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
if 1
    GetCycleCount(   0,   32,  1, 1000)
    GetCycleCount( 128,  511, 10,  800)
    GetCycleCount( 511, 1023, 20,  200)
    GetCycleCount(4092, 4096,  1,  100)
    mov rcx,arg_1
    mov rdx,arg_2
    mov arg_1,rdx
    mov arg_2,rcx
    GetCycleCount(4096-4, 4096, 1, 100)
endif
    xor eax,eax
    ret
    endp
    end start
