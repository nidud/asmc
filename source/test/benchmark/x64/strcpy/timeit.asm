define size_s  256 ; maximum data size
procs  equ <for x,<0,1,2,3,4>> ; add functions to test...
args_x macro
    mov eax,step_x
    lea rdx,str_1[size_s]
    sub rdx,rax
    lea rcx,dst_1
    exitm<>
    endm

    option  dllimport:<msvcrt>
    strcpy  proto :ptr, :ptr

include ../timeit.inc

.data

dst_1   db size_s dup(0)
str_1   db size_s-1 dup('x'),0

info_0  db "msvcrt",0
info_1  db "movsb",0
info_2  db " 4 byte",0
info_3  db "16 byte (SEE)",0
info_4  db "32 byte (AVX)",0

    .code

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

validate_x proc uses rsi rdi rbx r12 x:qword

    mov x,rcx
    lea rax,proc_p
    mov r12,[rax+rcx*8]
    .if !r12
        .if ReadProc(ecx)
            mov r12,proc_x
        .endif
    .endif
    .if r12

        .for ( ebx = 0 : ebx < 70 && nerror < 20 : ebx++ )


            lea rdi,dst_1
            lea ecx,[rbx+2]
            mov eax,9
            rep stosb

            lea rdx,str_1[size_s-1]
            sub rdx,rbx
            lea rcx,dst_1
            call r12
            mov rsi,rax

            .if ( byte ptr [rdi-1] != 9 )

                lea rcx,str_1[size_s-1]
                sub rcx,rbx
                movzx edx,byte ptr [rdi-1]
                printf("error: %d [9] (%d) %p %d.asm\n", edx, ebx, rcx, x)
                inc nerror
            .endif

            lea rdi,dst_1
            .if rdi != rsi

                printf("error: %p [%p] %d.asm\n", rsi, rdi, x)
                inc nerror
            .endif

            lea rsi,str_1[size_s-1]
            sub rsi,rbx
            mov rax,rsi
            lea ecx,[rbx+1]
            repz cmpsb

            .ifnz; ecx

                printf("error: %s [%s] %d.asm\n", &dst_1, rax, x)
                inc nerror
            .endif
        .endf
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret

validate_x endp

main proc

    strcpy(&dst_1, &str_1)
    mov rax,__imp_strcpy
    mov proc_p,rax

    .repeat

        procs
            validate_x(x)
            .if nerror
                printf("hit any key to continue...\n")
                _getch()
                .break
            .endif
        endm


        GetCycleCount(0,    32, 1, 1000)
        GetCycleCount(33,   64, 1, 1000)
        GetCycleCount(200, 204, 1, 500)
    .until 1
    ret

main endp

    end start
