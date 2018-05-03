include DirectXMath.inc

    .code

XMMatrixPerspectiveFovLH proc FovAngleY:float, AspectRatio:float, NearZ:float, FarZ:float

  local SinFov:float, CosFov:float
  local fRange:float, Height:float

    mov fRange,0.5
    _mm_mul_ss(xmm0, fRange)
    _mm_store_ss(fRange, xmm0)

    XMScalarSinCos(&SinFov, &CosFov, fRange)

    _mm_move_ss(xmm4, SinFov)
    _mm_div_ss(xmm4, CosFov)
    _mm_move_ss(xmm3, FarZ)
    _mm_store_ps(xmm0, xmm3)
    _mm_move_ss(xmm2, NearZ)
    _mm_sub_ss(xmm0, xmm2)
    _mm_move_ss(xmm1, AspectRatio)
    _mm_div_ss(xmm3, xmm0)
    _mm_store_ps(xmm0, xmm4)
    _mm_div_ss(xmm0, xmm1)
    _mm_store_ps(xmm1, xmm3)
    _mm_xor_ps(xmm1, _mm_get_epi32(0x80000000, 0, 0, 0))
    _mm_unpacklo_ps(xmm0, xmm4)
    _mm_mul_ss(xmm2, xmm1)
    _mm_setzero_ps(xmm1)
    _mm_unpacklo_ps(xmm3, xmm2)
    _mm_store_ps(xmm2, xmm1)
    _mm_movelh_ps(xmm0, xmm3)
    _mm_move_ss(xmm2, xmm0)
    _mm_store_ps(xmm4, xmm2)
    _mm_store_ps(xmm1, g_XMMaskY)
    _mm_and_ps(xmm1, xmm0)
    _mm_shuffle_ps(xmm0, g_XMIdentityR3, _MM_SHUFFLE(3,2,3,2))
    _mm_shuffle_ps(xmm2, xmm0, _MM_SHUFFLE(3,0,0,0))
    _mm_shuffle_ps(xmm3, xmm0, _MM_SHUFFLE(2,1,0,0))
    _mm_store_ps(xmm0, xmm4)
    ret

XMMatrixPerspectiveFovLH endp

    end

#include <emmintrin.h>

#define XM_PI	    3.141592654
#define XM_2PI	    6.283185307
#define XM_1DIVPI   0.318309886
#define XM_1DIV2PI  0.159154943
#define XM_PIDIV2   1.570796327
#define XM_PIDIV4   0.785398163

typedef struct {
    __m128 r[4];
} XMMATRIX;

typedef __m128 XMVECTOR;

void XMScalarSinCos(float*, float*, float);

extern __m128 g_XMIdentityR1;
extern __m128 g_XMIdentityR3;
extern __m128 g_XMMaskY;

XMMATRIX FovLH
(
    float FovAngleY,
    float AspectRatio,
    float NearZ,
    float FarZ
){
    float    SinFov;
    float    CosFov;
    XMScalarSinCos(&SinFov, &CosFov, 0.5f * FovAngleY);

    float fRange = FarZ / (FarZ-NearZ);
    // Note: This is recorded on the stack
    float Height = CosFov / SinFov;
    XMVECTOR rMem = {
	Height / AspectRatio,
	Height,
	fRange,
	-fRange * NearZ
    };
    XMVECTOR vValues = rMem;
    XMVECTOR vTemp = _mm_setzero_ps();
    vTemp = _mm_move_ss(vTemp,vValues);
    XMMATRIX M;
    M.r[0] = vTemp;
    vTemp = vValues;
    vTemp = _mm_and_ps(vTemp,g_XMMaskY);
    M.r[1] = vTemp;
    vTemp = _mm_setzero_ps();
    vValues = _mm_shuffle_ps(vValues,g_XMIdentityR3,_MM_SHUFFLE(3,2,3,2));
    vTemp = _mm_shuffle_ps(vTemp,vValues,_MM_SHUFFLE(3,0,0,0));
    M.r[2] = vTemp;
    vTemp = _mm_shuffle_ps(vTemp,vValues,_MM_SHUFFLE(2,1,0,0));
    M.r[3] = vTemp;
    return M;
}
