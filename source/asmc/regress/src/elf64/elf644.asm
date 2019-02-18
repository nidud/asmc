;
; v2.28 - invoke(__int128)
;
    __int128    typedef oword
    __float128  typedef real16

    option win64:auto

    .data
    x __int128 0

    .code

p1  proc a1:__int128, a2:__int128, a3:__int128

    mov rax,a1 ; RDI: high64 in RSI
    mov rax,a2 ; RDX: high64 in RCX
    mov rax,a3 ; R8:  high64 in R9
    ret
p1  endp

p2  proc a1:__int128, a2:__int128, a3:__int128, a4:__float128, a5:__float128, a6:__float128

    p1(a1, a2, a3) ; no params set
    movaps xmm0,a4 ; xmm0
    movaps xmm0,a5 ; xmm1
    movaps xmm0,a6 ; xmm2
    ret
p2  endp

p3  proc
    p1( 0, 1, 2 )
    p1( 0x0000000000000000FFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF0000000000000000,
        0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF )
    p1( -0, -1, x )
    ret
p3  endp

    end
