;
; asmc64 -q -bin ?.asm
; asmc64 -q -pe %0
; %~n0.exe
; del %~n0.exe
; del *.bin
; exit /b %errorlevel%
;

procs  equ <for x,<0,1,2>> ; add functions to test...
args_x macro
    exitm<>
    endm

include ../timeit.inc

    .data

info_0  db "enter/leave",0
info_1  db "push/leave",0
info_2  db "push/pop",0

    .code

main proc
    ;           default
    ; ----------------------------------------
    ; enter     push rbp        push rbp
    ; leave     mov rbp,rsp     mov rbp,rsp
    ;           leave           mov rsp,rbp
    ;                           pop rbp
    ;
    GetCycleCount(0, 3, 1, 1000)
    ret

main endp

    end start
