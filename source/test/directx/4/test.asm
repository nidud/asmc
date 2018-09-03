
include stdio.inc
include directxmath.inc

.code

main proc

    XMVectorTan(_mm_set1_epi32(1.0))
    printf("XMVectorTan(1.0): %f\n", _mm_cvtsi128_si64(_mm_cvtss_sd(xmm0)))
    xor eax,eax
    ret

main endp

    end
