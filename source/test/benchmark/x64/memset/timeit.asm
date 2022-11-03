
procs  equ <for x,<0,1,2,3>> ; add functions to test...
args_x macro
    lea rcx,str_1
    mov edx,0
    mov r8d,step_x
    exitm<>
    endm

    option  dllimport:<msvcrt>
    memset  proto :ptr, :dword, :qword

include ../timeit.inc

size_s  equ 4096 ; maximum data size

.data?
str_1   db size_s dup(?)

    .data

info_0  db "msvcrt.memset()",0
info_1  db "switch 32 SSE",0
info_2  db "switch 32 AVX",0
info_3  db "switch 64 AVX",0

    .code

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

validate_x PROC USES rsi rdi rbx x:QWORD

    mov x,rcx
    lea rax,proc_p
    mov rsi,[rax+rcx*8]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif
    .if rsi
        mov ebx,1
        .repeat
            lea  rdi,str_1
            mov  al,'?'
            lea  rcx,[rbx+16]
            rep  stosb
            lea  rdi,str_1
            mov  byte ptr [rdi+rbx+16],0

            mov rcx,rdi
            mov edx,'x'
            mov r8,rbx
            call rsi

            xor edx,edx
            mov rcx,rdi
            .if rax != rcx
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
                lea r10,str_1
                mov rdx,rax
                printf("error: eax %06X [%06X] (%d) %d.asm: %s\n",edx,r10,ebx,x,r10)
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

    memset(&str_1, 0, 1)
    mov rax,__imp_memset
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
        ;
        ; A jump table is created if number of cases >= 8
        ;
        GetCycleCount(1, 4, 1, 1000)
        GetCycleCount(15, 17, 1, 1000)
        GetCycleCount(63, 65, 1, 1000)
        GetCycleCount(127, 129, 1, 1000)
        GetCycleCount(511, 513, 1, 1000)
        GetCycleCount(1023, 1025, 1, 1000)
        GetCycleCount(4023, 4025, 1, 1000)

    .until 1
    ret

main endp

    end start
