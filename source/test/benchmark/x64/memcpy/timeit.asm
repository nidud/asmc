
procs  equ <for x,<0,1,2,3>> ; add functions to test...
args_x macro
    lea rcx,dst_1
    lea rdx,str_1
    mov r8d,step_x
    exitm<>
    endm

    option  dllimport:<msvcrt>
    memcpy  proto :ptr, :ptr, :qword

include ../timeit.inc

size_s  equ 4096 ; maximum data size

.data?
str_1   db size_s dup(?)
align   16
dst_1   db size_s dup(?)

.data
info_0  db "msvcrt.memcpy()",0
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
            lea  rdi,dst_1
            mov  al,'?'
            lea  rcx,[rbx+16]
            rep  stosb
            lea  rdi,str_1
            mov  byte ptr [rdi+rbx],0

            lea rcx,dst_1
            lea rdx,str_1
            mov r8,rbx
            call rsi

            mov byte ptr [rdi+rbx],'x'
            lea rdx,dst_1
            mov byte ptr [rdx+rbx],'?'
            xor edx,edx
            lea rcx,dst_1
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
                lea r10,dst_1
                mov rdx,rax
                printf("error: eax %06X [%06X] (%d) %d.asm: %s\n",edx,r10,ebx,x,r10)
                inc nerror
            .endif
            .break .if nerror > 12
            inc ebx
        .until ebx == 129
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
validate_x ENDP

main proc

    lea rdi,str_1
    mov ecx,size_s
    mov al,'x'
    rep stosb
    xor eax,eax
    stosb
    memcpy(&dst_1, &str_1, 1)
    mov rax,__imp_memcpy
    lea rcx,proc_p
    mov [rcx],rax

    procs
        validate_x(x)
        cmp nerror,0
        jne error
    endm
    ;
    ; A jump table is created if number of cases >= 8
    ;
    GetCycleCount(1, 4, 1, 1000)
    GetCycleCount(127, 129, 1, 1000)
    GetCycleCount(511, 513, 1, 1000)
    GetCycleCount(1023, 1025, 1, 1000)

toend:
    ret
error:
    printf("hit any key to continue...\n")
    _getch()
    jmp toend

main endp

    end start
