.486
.model flat, stdcall

D0T typedef proto :ptr
D1T typedef proto :ptr, :ptr, :ptr, :ptr, :ptr
D0  typedef ptr D0T
D1  typedef ptr D1T

xx  struc
l1  D0 ?
l2  D1 ?
xx  ends

LPXX TYPEDEF PTR xx

.data
p LPXX ?
q D1 ?
x xx <>

.code

    q( 0, 1, 2, 3, 4 )
    x.l2( 0, 1, 2, 3, 4 )
    p.l2( 1, 2, 3, 4 )

    x.l1( 0 )
    p.l1()

foo proc
local lp:LPXX

    q( 0, 1, 2, 3, 4 )
    p.l2( 1, 2, 3, 4 )
    p.l1()
    lp.l2( 1, 2, 3, 4 )
    lp.l1()

foo endp

    end
