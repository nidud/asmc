
procs  equ <for x,<0,1,2,3>> ; add functions to test...
args_x macro
    mov eax,step_x
    add eax,eax
    lea rcx,str_1[size_s]
    sub rcx,rax
    mov edx,1
    exitm<>
    endm

    option  dllimport:<msvcrt>
    strchr  proto :ptr, :dword

include ../timeit.inc

size_s  equ 4096 ; maximum data size

.data

str_1   db size_s-2 dup('x')
arg_2   db 1,0

info_0  db "msvcrt",0
info_1  db "libc",0
info_2  db "SSE",0
info_3  db "AVX",0

.code

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

validate_x PROC USES rsi rdi rbx x

    lea rax,proc_p
    mov rsi,[rax+rcx*8]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif

    .if rsi

        mov ebx,2
        .repeat

            lea rcx,str_1[size_s]
            sub rcx,rbx
            mov edx,1
            call rsi

            lea rdx,arg_2
            .if rdx != rax
                mov rcx,rax
                printf("error: eax %06X [%06X] (%d) %d.asm\n", rcx, rdx, ebx, x)
                inc nerror
            .endif
            .break .if nerror > 12
            inc ebx
        .until ebx == 290
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
validate_x ENDP

main proc

    strchr(&str_1, 0)
    mov rax,__imp_strchr
    lea rcx,proc_p
    mov [rcx],rax

    .repeat

        procs
            validate_x(x)
            .if nerror
                printf("hit any key to continue...\n")
                _getch()
                .break
            .endif
        endm
        GetCycleCount(1, 4, 1, 1000)
        GetCycleCount(15, 17, 1, 1000)
        GetCycleCount(127, 129, 1, 1000)
    .until 1
    ret

main endp

    end start
