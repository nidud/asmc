
    ; 2.32.38 - Assign const value > 4

    option win64:3

    .code

    S1 STRUC
    o  oword ?
    f  real4 ?
    d  real8 ?
    l  real10 ?
    q  real16 ?
    S1 ENDS

foo proc
   .new a:S1 = { 0, 0.0, 0.0, 0.0, 0.0 }
   .new b:S1 = { 16, 4.0, 8.0, 10.0, 16.0 }
    ret
    endp

    end
