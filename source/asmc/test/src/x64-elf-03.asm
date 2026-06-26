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
    p1(a1, a2, a3, a4, a5)  ; al == 2, a4 --> real8
    ret
p2  endp

p14 proto   :byte,  ; dil
            :real8, ; xmm0
            :real8, ; xmm1
            :real8, ; xmm2
            :sword, ; si (esi) -- extend word to dword if const value
            :dword, ; edx
            :real4, ; xmm3
            :real4, ; xmm4
            :real4, ; xmm5
            :qword, ; rcx
            :ptr,   ; r8
            :real8, ; xmm6
            :real8, ; xmm7
            :byte   ; r9b

p3  proc
    ; no params set
    p14(dil,xmm0,xmm1,xmm2,si,edx,xmm3,xmm4,xmm5,rcx,r8,xmm6,xmm7,r9b)
    ; sign extend sil
    p14(dil,xmm0,xmm1,xmm2,sil,edx,xmm3,xmm4,xmm5,rcx,r8,xmm6,xmm7,r9b)
    ; all params set
    p14(0,1.0,2.0,3.0,4,5,6.0,7.0,8.0,9,10,11.0,12.0,13)
    ret
p3  endp

    end
