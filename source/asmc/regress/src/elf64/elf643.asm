;
; v2.28 - option win64:auto
;
    .code

    option win64:auto

p1  proc string:ptr sbyte, argptr:vararg
    ;
    ; xmm0..7 copied to stack if AL set
    ; argptr set to rax
    ;
    ret
p1  endp

p2  proc a1:ptr, a2:word, a3:dword, a4:real4, a5:real8, a6:real16

    p1(a1, a2, a3)          ; al == 0
    p1(a1, a2, a3, a4, a5)  ; al == 1
    ret
p2  endp

    end

