;
; asmc64 -DCOUNT=100 -q -bin ?.asm
; asmc64 -q -pe %0
; %~n0.exe
; del %~n0.exe
; del *.bin
; exit /b %errorlevel%
;

procs  equ <for x,<0,1,2,3>> ; add functions to test...
args_x macro
    mov ecx,step_x
    exitm<>
    endm

include ../timeit.inc

    .data

info_0  db "elseif",0
info_1  db "notable",0
info_2  db "table",0
info_3  db "notest",0
info_4  db "4.asm",0
info_5  db "5.asm",0
info_6  db "6.asm",0
info_7  db "7.asm",0
info_8  db "8.asm",0
info_9  db "9.asm",0

    .code

validate_x proc uses rsi rdi rbx x:dword

    mov x,ecx
    lea rax,proc_p
    mov rsi,[rax+rcx*8]

    .if !rsi

        .if ReadProc(ecx)

            mov rsi,proc_x
        .endif
    .endif

    .if rsi

        .for ( ebx = 0 : ebx < 100 && nerror < 12 : ebx++ )

            mov ecx,ebx
            call rsi

            .if ( eax != ebx )
                printf("error: eax %d (%d) %d.asm\n", eax, ebx, x)
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
        GetCycleCount(0, 4, 1, 1000)
        GetCycleCount(5, 9, 1, 1000)
        GetCycleCount(90, 92, 1, 1000)
    .until 1
    ret

main endp

    end start
