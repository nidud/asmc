; FLOAT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include iostream
include tchar.inc

.template <xmm0, real4> float

    __v real4 ?

    .operator<abs> = :float {
        movss this,_1
        }
    .ends

float_add_float proto :real4, :abs {
    addss _1,_2
    }
float_sub_oword proto :real4, :abs {
    subss _1,_2
    }
float_mul_oword proto :real4, :abs {
    mulss _1,_2
    }
float_div_float proto :real4, :abs {
    divss _1,_2
    }
float_div_flt proto :real4, :abs {
    divss _1,_2
    }

    .code

foo proc a:float, b:float, c:float, d:float

    b * xmm3 - xmm2 + a / 2.0
    ret

foo endp

_tmain proc

   .new result:real4 = foo(1.0, 2.0, 3.0, 4.0)

    cout << "2.0 * 4.0 - 3.0 + 1.0 / 2.0 = " << result << endl
    xor eax,eax
    ret

_tmain endp

    end _tstart
