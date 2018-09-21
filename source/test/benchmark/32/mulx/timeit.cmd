;
; asmc -q -bin ?.asm
; asmc -q -pe %0
; %~n0.exe
; del %~n0.exe
; del *.bin
; exit /b %errorlevel%
;

procs  equ <for x,<0,1>> ; add functions to test...

args_x macro a:=<arg1>, b:=<arg2>, r:=<arg3>
    push r
    push dword ptr b[4]
    push dword ptr b[0]
    push dword ptr a[4]
    push dword ptr a[0]
    exitm<>
    endm

include ../timeit.inc

    .data

m128    dq 2 dup(?)
arg1    dq 2
arg2    dq 2
arg3    dd m128

info_0  db "mul",0
info_1  db "mulx",0
info_2  db "2.asm",0
info_3  db "3.asm",0
info_4  db "4.asm",0
info_5  db "5.asm",0
info_6  db "6.asm",0
info_7  db "7.asm",0
info_8  db "8.asm",0
info_9  db "9.asm",0

    .code

validate_x proc uses esi edi ebx x:dword

    mov ecx,x
    lea eax,proc_p
    mov esi,[eax+ecx*4]
    .if !esi
        .if ReadProc(ecx)
            mov esi,proc_x
        .endif
    .endif

    .if esi

        callx macro a1, a2, ql, qh
            local a, b, rl, rh
            .data
            a dq a1
            b dq a2
            rl dq ql
            rh dq qh
            .code
            args_x(a, b)
            call esi
            mov eax,dword ptr m128
            mov edx,dword ptr m128[4]
            mov ebx,dword ptr rl
            mov ecx,dword ptr rl[4]
            .if eax != ebx || edx != ecx
                printf("error: %d.asm -- %08X%08X %08X%08X\n", x, edx, eax, ecx, ebx)
                inc nerror
            .endif
            exitm<>
            endm

        callx( 0, 0, 0, 0 )
        callx( 1, 1, 1, 0 )
        callx( 2, 1, 2, 0 )
        callx( 20, 10, 200, 0 )
        callx( 33, 10, 330, 0 )
        callx( 100000, 100000, 10000000000, 0 )
        callx( 100000, 1000000, 100000000000, 0 )
        callx( 100000, 10000000, 1000000000000, 0 )
        callx( 1000000, 10000000, 10000000000000, 0 )
        callx( 20000000, 10000000, 200000000000000, 0 )
        callx( 0x1000000000000000, 3, 0x3000000000000000, 0 )
        callx( 0x7FFFFFFFFFFFFFFF, 2, 0xFFFFFFFFFFFFFFFE, 0 )
        callx( 0x7FFFFFFFFFFFFFFF, 3, 0x7FFFFFFFFFFFFFFD, 0 )
        callx( 0x7FFFFFFFFFFFFFFF, 3, 0x7FFFFFFFFFFFFFFD, 0x1 )
        callx( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x00000000000000001, 0xFFFFFFFFFFFFFFFE )
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
                mov nerror,0
            .endif
            endm

        printf("mul(2, 2)\n")
        GetCycleCount(0, 3, 1, 5000)
        mov dword ptr arg1,0xFFFFFFFF
        mov dword ptr arg1[4],0x7FFFFFFF
        printf("\nmul(2, 0x7FFFFFFFFFFFFFFF)\n")
        GetCycleCount(0, 3, 1, 5000)
    .until 1
    ret

main endp

    end start
