include stdio.inc
include intrin.inc

foo proto vectorcall :zword
bar proto vectorcall :yword

.code

foo2 proc vectorcall v1:zword
    _mm512_mul_ps(zmm0, _mm512_set1_ps(2.0))
    ret
    endp
bar2 proc vectorcall v1:yword
    _mm256_mul_ps(ymm0, _mm256_set1_ps(2.0))
    ret
    endp

 main proc
    bar(ymm0)
    xor eax,eax
    ret
    endp

    end
