
; v2.39.17: allow vector assignment for YMM and ZMM

option win64:3

.code

bar proto :zword {} ; uses VMOVUPS
baz proto :yword, :yword {}

foo proc uses xmm6 xmm7 x:real8
    bar( { 1, 2, 3, 4, 5, 6, 7, 8.0 } )
    baz( { 1, 2, 3, 4 }, { 5, 6, 7, 8.0 } )
    ret
    endp

    end

