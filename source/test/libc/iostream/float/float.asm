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

float_sub_oword proto this:abs, vector:abs {
    float_sub_float(this, vector)
    }

float::mul_oword macro this, vector
    exitm<float::mul_float(this, vector)>
    endm

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
