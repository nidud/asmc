; ASIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option float:double

asin proc x:double

ifdef __SSE__

   .new x6:xmmword
   .new polynomial:double
   .new d0:double
   .new d1:double
   .new x0:double = xmm0

    .if ( xmm0 < -0.5 )

        movsd xmm1,-0.0
        xorpd xmm0,xmm1

    .elseif ( xmm0 <= 0.5 )

        movsd xmm1,xmm0
        movsd xmm2,xmm0
        mulsd xmm1,xmm1
        movsd xmm0,0.0316658385792867081040808
        mulsd xmm0,xmm1
        addsd xmm0,-0.0158620440988475212803145
        mulsd xmm0,xmm1
        addsd xmm0,0.0192942786775238654913582
        mulsd xmm0,xmm1
        addsd xmm0,0.0066153165197009078340075
        mulsd xmm0,xmm1
        addsd xmm0,0.0121483892822292648695383
        mulsd xmm0,xmm1
        addsd xmm0,0.0138885410156894774969889
        mulsd xmm0,xmm1
        addsd xmm0,0.0173593516996479249428647
        mulsd xmm0,xmm1
        addsd xmm0,0.0223717830666671020710108
        mulsd xmm0,xmm1
        addsd xmm0,0.0303819580081956423799529
        mulsd xmm0,xmm1
        addsd xmm0,0.0446428568582815922683933
        mulsd xmm0,xmm1
        addsd xmm0,0.0750000000029696112392353
        mulsd xmm0,xmm1
        addsd xmm0,0.1666666666666558995379880
        mulsd xmm0,xmm1
        mulsd xmm0,xmm2
        addsd xmm0,xmm2
       .return
    .endif

    .if ( xmm0 >= 1.0 )

        movsd xmm0,7FF8000000000000r ; 1.#QNAN
       .return .ifp
       .return .ifnz
       .return real8 ( 1.5707963267948966 ) ; Pi/2 rounded down
    .endif

    movsd xmm1,-0.0000121189820098929624806
    mulsd xmm1,xmm0
    addsd xmm1,0.0001307564187657962919394
    mulsd xmm1,xmm0
    addsd xmm1,-0.0006702485124770180942917
    mulsd xmm1,xmm0
    addsd xmm1,0.0021912255981979442677477
    mulsd xmm1,xmm0
    addsd xmm1,-0.0052049731575223952626203
    mulsd xmm1,xmm0
    addsd xmm1,0.0097868293573384001221447
    mulsd xmm1,xmm0
    addsd xmm1,-0.0156746038587246716524035
    mulsd xmm1,xmm0
    addsd xmm1,0.0229883479552557203133368
    mulsd xmm1,xmm0
    addsd xmm1,-0.0331919619444009606270380
    mulsd xmm1,xmm0
    addsd xmm1,0.0506659694457588602631748
    mulsd xmm1,xmm0
    addsd xmm1,-0.0890259194305537131666744
    mulsd xmm1,xmm0
    addsd xmm1,0.2145993335526539017488949
    mulsd xmm1,xmm0
    movsd polynomial,xmm1

    movaps x6,xmm6

    movsd xmm6,1.0
    movsd xmm1,xmm6
    subsd xmm1,xmm0 ; 1-x
    movsd xmm0,xmm1
    sqrtsd xmm0,xmm0
    divsd xmm6,xmm0 ; 1 / sqrt( 1 - x )

    movsd xmm0,xmm6

    movsd xmm2,134217729.0
    movsd xmm5,xmm0
    movsd xmm3,xmm0
    mulsd xmm5,xmm2
    movsd xmm4,xmm2
    movsd xmm2,xmm1
    mulsd xmm4,xmm1
    subsd xmm3,xmm5
    subsd xmm2,xmm4
    addsd xmm3,xmm5
    movsd xmm5,xmm1
    addsd xmm2,xmm4
    movsd xmm4,xmm0
    mulsd xmm0,xmm1
    movsd xmm1,xmm3
    subsd xmm4,xmm3
    subsd xmm5,xmm2
    mulsd xmm1,xmm2
    mulsd xmm2,xmm4
    mulsd xmm3,xmm5
    mulsd xmm4,xmm5
    subsd xmm1,xmm0
    addsd xmm1,xmm3
    addsd xmm1,xmm2
    addsd xmm1,xmm4

    movsd d0,xmm0
    movsd d1,xmm1

    movsd xmm4,134217729.0
    movsd xmm5,xmm6
    movsd xmm2,xmm6
    mulsd xmm1,xmm2
    mulsd xmm6,xmm4
    movsd xmm3,xmm4
    movsd xmm4,xmm0
    mulsd xmm3,xmm0
    subsd xmm5,xmm6
    subsd xmm4,xmm3
    addsd xmm5,xmm6
    movsd xmm6,xmm0
    addsd xmm4,xmm3
    subsd xmm2,xmm5
    movsd xmm3,xmm5
    subsd xmm6,xmm4
    mulsd xmm3,xmm4
    subsd xmm3,1.0
    mulsd xmm4,xmm2
    mulsd xmm5,xmm6
    mulsd xmm6,xmm2
    movsd xmm0,xmm5
    addsd xmm0,xmm3
    addsd xmm0,xmm4
    addsd xmm0,xmm6
    addsd xmm0,xmm1

    movsd xmm2,xmm0
    movsd xmm0,d0
    movsd xmm1,d1

    mulsd xmm2,-0.5
    mulsd xmm2,xmm0

    movsd xmm3,xmm0
    addsd xmm3,xmm2
    subsd xmm0,xmm3
    addsd xmm0,xmm2
    addsd xmm1,xmm0
    movsd xmm0,xmm3
    addsd xmm0,xmm1
    subsd xmm3,xmm0
    addsd xmm3,xmm1

    movsd xmm4,xmm0
    movsd xmm0,-1.5707961988153776
    movsd xmm1,1.0640719477080884e-16

    movsd xmm2,xmm0
    addsd xmm2,polynomial
    subsd xmm0,xmm2
    addsd xmm0,polynomial
    addsd xmm1,xmm0
    movsd xmm0,xmm2
    addsd xmm0,xmm1
    subsd xmm2,xmm0
    addsd xmm2,xmm1

    movsd xmm5,xmm0
    movsd xmm0,xmm4
    movsd xmm1,xmm3
    movsd xmm3,xmm2
    movsd xmm2,xmm5

    movsd xmm6,134217729.0
    movsd xmm5,xmm0

    mulsd xmm3,xmm0
    mulsd xmm5,xmm6
    mulsd xmm6,xmm2
    mulsd xmm1,xmm2
    addsd xmm1,xmm3
    movsd xmm3,xmm0
    subsd xmm3,xmm5
    movsd xmm4,xmm6
    movsd xmm6,xmm2
    subsd xmm6,xmm4
    addsd xmm3,xmm5
    movsd xmm5,xmm0
    mulsd xmm5,xmm2
    addsd xmm6,xmm4
    movsd xmm4,xmm3
    movsd xmm3,xmm0
    subsd xmm3,xmm4
    subsd xmm2,xmm6
    movsd xmm0,xmm4
    mulsd xmm4,xmm6
    mulsd xmm6,xmm3
    mulsd xmm0,xmm2
    mulsd xmm3,xmm2
    subsd xmm4,xmm5
    addsd xmm4,xmm0
    addsd xmm4,xmm6
    addsd xmm4,xmm3
    addsd xmm1,xmm4
    movsd xmm0,xmm5
    addsd xmm0,xmm1
    subsd xmm5,xmm0
    addsd xmm1,xmm5

    movsd xmm2,1.5707963267948966
    movsd xmm3,6.123233995736766e-17

    movsd xmm4,xmm2
    addsd xmm4,xmm0
    subsd xmm2,xmm4
    addsd xmm2,xmm0
    addsd xmm2,xmm1
    addsd xmm2,xmm3
    movsd xmm0,xmm2
    addsd xmm0,xmm4

    movaps xmm6,x6

    movsd xmm1,x0
    .if ( xmm1 < -0.5 )

        movsd xmm1,-0.0
        xorpd xmm0,xmm1
    .endif

else

    fld     x
    fld     st(0)
    fmul    st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan

endif

    ret

asin endp

    end
