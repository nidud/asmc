; FLOAT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include iostream
include tchar.inc

.template <xmm0, real4> float

    __v real4 ?

    .operator<abs> = :real8 {
        cvtsd2ss xmm0,xmm1
        movss this,xmm0
        }
    .ends

float_add_float proto :abs, :abs {
    ifidn <_2>, <xmm0>
        addss _2,_1
    elseifidn <_1>, <xmm0>
        addss _1,_2
    else
        movss xmm1,_2
        movss xmm0,_1
        addss _1,_2
    endif
    }
float_sub_float proto :real4, :abs {
    subss _1,_2
    }
float_mul_float proto :real4, :abs {
    mulss _1,_2
    }
float_div_float proto :real4, :abs {
    divss _1,_2
    }
float_equ_float proto :abs, :abs {
    movss _1,_2
    }

    .code

foo proc a:float, b:float, c:float, d:float

   .new n:float = 2.0

    n = (a + b * d - c) / n
    ret

foo endp

_tmain proc

   .new result:real4 = foo(1.0, 2.0, 3.0, 4.0)

    cout << "(a + b * d - c) / 2.0 = " << result << endl
    xor eax,eax
    ret

_tmain endp

    end _tstart
