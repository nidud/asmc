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

main proc
    ;
    ; A jump table is created if number of cases >= 8
    ;
    GetCycleCount(0, 4, 1, 1000)
    GetCycleCount(5, 9, 1, 1000)
    GetCycleCount(90, 92, 1, 1000)
    ret

main endp

    end start
