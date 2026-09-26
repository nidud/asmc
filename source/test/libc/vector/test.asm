include stdio.inc
include math.inc
include intrin.inc

define FORMAT <"\t({ .5, 1, 2, 3 }): { %10f, %10f, %10f, %10f }\n">
define VECTOR <{ 0.5, 1.0, 2.0, 3.0 }>

testcase macro func, x
  ifb <x>
    _mm_store_ps(f, @CatStr(<_mm_>, <func>, <_ps>) (VECTOR))
  else
    @CatStr(<_mm_>, <func>, <_ps>) (x, VECTOR)
    _mm_store_ps(f, xmm0)
  endif
    printf( @CatStr(<!">, <func>, <f>, <!">) FORMAT, f.f1, f.f2, f.f3, f.f4 )
    exitm<>
    endm

.code

main proc

   .new f:XVEC4F

    testcase(cos)
    testcase(sin)
    testcase(tan)
    testcase(exp)
    testcase(exp2)
    testcase(log)
    testcase(log2)
    testcase(cosh)
    testcase(sinh)
    testcase(tanh)
    testcase(acos)
    testcase(asin)
    testcase(atan)
    testcase(atan2, { 1.0, 1.0, 1.0, 1.0 })
    testcase(fmod, { 1.0, 1.0, 1.0, 1.0 })
    testcase(trunc)
    ret
    endp

    end
