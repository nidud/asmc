;
; asmc -q -bin ?.asm
; asmc -q -pe %0
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
info_3  db "3.asm",0
info_4  db "4.asm",0
info_5  db "5.asm",0
info_6  db "6.asm",0
info_7  db "7.asm",0
info_8  db "8.asm",0
info_9  db "9.asm",0

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
