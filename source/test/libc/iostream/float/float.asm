; FLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include iostream
include tchar.inc

.template <xmm0, real4> float

    __v real4 ?

    .operator + :float {
        addss this,_1
        }
    .operator - :float {
        subss this,_1
        }
    .operator * :float {
        mulss this,_1
        }
    .operator / :float {
        divss this,_1
        }
    .operator<abs> = :float {
        movss this,_1
        }
    .ends

define float_sub_oword <float_sub_float> ; xmm3 - xmm2
define float_mul_oword <float_mul_float> ; b * xmm3


    .code

foo proc a:float, b:float, c:float, d:float

   .new n:float = 2.0

    n = (a + b * xmm3 - xmm2) / n
    ret

foo endp

_tmain proc

   .new result:real4 = foo(1.0, 2.0, 3.0, 4.0)

    cout << "(1.0 + 2.0 * 4.0 - 3.0) / 2.0 = " << result << endl
    ret

_tmain endp

    end _tstart
