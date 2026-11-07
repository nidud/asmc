#include <intrin.h>

__m512 __vectorcall foo(__m512 v1) {
    return _mm512_mul_ps(v1, _mm512_set1_ps(2.0));
}
__m256 __vectorcall bar(__m256 v1) {
    return _mm256_mul_ps(v1, _mm256_set1_ps(2.0));
}
