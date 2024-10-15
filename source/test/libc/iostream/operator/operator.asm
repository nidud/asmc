; OPERATOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include iostream
include tchar.inc

operator macro vector, type

.namespace type

    .template <vector, type> t

        __v type ?

        .operator + :&type&_t {
            mov vector,this
            add vector,_1
            }
        .operator - :&type&_t {
            mov vector,this
            sub vector,_1
            }
        .operator * :&type&_t {
            mov vector,this
            mul _1
            }
        .operator / :&type&_t {
            mov vector,this
            div _1
            }
        .operator<abs> = :&type&_t {
            mov this,_1
            }
        .ends
    .endn
    endm

operator al, byte

.code

foo proc a:byte_t, b:byte_t, c:byte_t, d:byte_t

   .new n:byte_t = 2

    n = (a + b * d - c) / n

    movzx eax,n
    ret

foo endp

_tmain proc

   .new i:int_t = foo(1, 2, 3, 4)

    cout << "(1 + 2 * 4 - 3) / 2 = " << i << endl
    xor eax,eax
    ret

_tmain endp

    end _tstart
