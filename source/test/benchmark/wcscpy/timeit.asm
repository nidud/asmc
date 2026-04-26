ifdef _WIN64
procs equ <for x,<0,2,3>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov eax,step_x
    lea rdx,str_1[size_s]
    sub rdx,rax
ifdef _WIN64
    mov rcx,m_4096
else
    push edx
    push m_4096
endif
    exitm<>
    endm

include ../timeit.inc
option  dllimport:<msvcrt>
externdef import wcscpy:ptr_t

define size_s 4096 ; maximum data size

.data
align   16
str_1   dw size_s/2-1 dup('x'),0

info_0  db "msvcrt.wcscpy()",0
info_1  db "libc(__X86__)",0
info_2  db "libc(__SSE__)",0
info_3  db "libc(__AVX__)",0

.code

strcpy_t typedef proto :ptr, :ptr

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

        assume rsi:ptr strcpy_t
        .for ( ebx = 0 : ebx < 70 && nerror < 16 : ebx++ )

            mov rdx,m_endp
            sub rdx,17*2
            sub rdx,rbx
            sub rdx,rbx
            mov word ptr [rdx-2],0
            mov eax,'?'
            lea rcx,[rbx+16]
            mov rdi,rdx
            rep stosw
            mov word ptr [rdi],0
            mov rdi,rdx
            lea rdx,str_1[size_s-2]
            sub rdx,rbx
            sub rdx,rbx

            .if ( rsi(rdi, rdx) != rdi )
                printf("error: rax %06X [%06X] %d.asm\n", rax, rdi, x)
                inc nerror
            .else
                .for ( edx = 0, ecx = ebx : ecx : ecx-- )
                    .if word ptr [rax+rcx*2-2] != 'x'
                        inc edx
                       .break
                    .endif
                .endf
                .if word ptr [rax-2]
                    inc edx
                .endif
                lea rax,[rax+rbx*2]
                .if word ptr [rax]
                    inc edx
                .endif
                .for ( rax+=2, ecx = 15 : ecx : ecx-- )
                    .if word ptr [rax+rcx*2-2] != '?'
                        inc edx
                       .break
                    .endif
                .endf
                .if edx
                    printf("error: %04X (%d) %d.asm: %S\n", edi, ebx, x, rdi)
                    inc nerror
                .endif
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
    mov rax,wcscpy
    mov proc_p,rax
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
    GetCycleCount(  0,  32, 4, 1000)
    GetCycleCount( 32, 128, 8, 800)
    GetCycleCount(128, 512, 8, 400)
    ret
    endp
    end start
