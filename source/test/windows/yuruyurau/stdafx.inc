.pragma list(push, 0)

include windows.inc
include DirectX/d2d1.inc
include stdio.inc
include math.inc
include immintrin.inc
include fltintrn.inc
include commctrl.inc
include winres.inc
include tchar.inc

.pragma list(pop)

.pragma comment(linker,
    "/manifestdependency:\""
    "type='win32' "
    "name='Microsoft.Windows.Common-Controls' "
    "version='6.0.0.0' "
    "processorArchitecture='*' "
    "publicKeyToken='6595b64144ccf1df' "
    "language='*'"
    "\""
    )

define CLASS_NAME   <"MainWindowClass">
define WINDOWSTYLES WS_VISIBLE or WS_POPUP
define ID_TIMER     1
define IDD_HELP     129

.class CApplication

    m_hInstance     HINSTANCE ?
    m_hwnd          HWND ?
    m_rect          RECT <>
    m_size          D2D1_SIZE_U <>
    m_time          real4 ?
    m_DeltaX        real4 ?
    m_DeltaY        real4 ?
    m_radius        real4 ?
    m_step          int_t ?
    m_count         int_t ?
    m_texty         int_t ?
    m_timer         int_t ?
    m_intensity     int_t ?
    m_isFullScreen  BOOL ?
    m_pD2DFactory   ptr ID2D1Factory ?
    m_pRT           ptr ID2D1HwndRenderTarget ?
    m_brush         ptr ID2D1RadialGradientBrush ?

    CApplication    proc :HINSTANCE
    Release         proc
    Run             proc
    Point           proc :UINT
    OnKeyDown       proc :WPARAM
    OnRender        proc
    OnSize          proc :UINT, :UINT
    OnClose         proc
    GoFullScreen    proc
    GoPartialScreen proc
    CreateDeviceResources proc
    RenderMainContent proc
    EnterMessageLoop proc
    CreateApplicationWindow proc
    ErrorMessage    proc :HRESULT, :LPTSTR
   .ends

.data
 IID_ID2D1Factory GUID {0x06152247,0x6f50,0x465a,{0x92,0x45,0x11,0x8b,0xfd,0x3b,0x60,0x07}}

.code

_mm_mag_ss macro a, b
    mulss a,a
    mulss b,b
    addss a,b
    sqrtss a,a
    retm<a>
    endm

_mm_sin_ss macro x
    Sine(x)
    retm<xmm0>
    endm

_mm_cos_ss macro x
    Cosine(x)
    retm<xmm0>
    endm

_mm_pow_ss macro x, i
    movss xmm1,x
    repeat i-1
      mulss x,xmm1
    endm
    retm<x>
    endm


VectorModAngles proto vectorcall :real16 {
    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm0, { 0.159154943, 0.159154943, 0.159154943, 0.159154943 })
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm_mul_ps(xmm0, { M_TWOPI, M_TWOPI, M_TWOPI, M_TWOPI })
    _mm_sub_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm1)
    }


Sine proc vectorcall x:float

    VectorModAngles(xmm0)

    _mm_and_ps(xmm1, { -0x0, -0x0, -0x0, -0x0 })
    _mm_store_ps(xmm2, xmm1)
    _mm_or_ps(xmm2, { M_PI, M_PI, M_PI, M_PI })
    _mm_store_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm3, xmm0)
    _mm_sub_ps(xmm2, xmm0)
    _mm_cmple_ps(xmm3, { M_PI_2, M_PI_2, M_PI_2, M_PI_2 })
    _mm_and_ps(xmm0, xmm3)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_or_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm1, xmm0)
    _mm_store_ps(xmm3, { -2.3889859e-08, -0.16665852, +0.0083139502, -0.00018524670 })
    _mm_store_ps(xmm2, _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm3, { -0.16666667, +0.0083333310, -0.00019840874, +2.7525562e-06 })
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(3,3,3,3)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(2,2,2,2)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(1,1,1,1)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, { 1.0, 1.0, 1.0, 1.0 })
    _mm_mul_ps(xmm0, xmm2)
    ret
    endp


Cosine proc vectorcall x:float

    VectorModAngles(xmm0)

    _mm_and_ps(xmm1, { -0x0, -0x0, -0x0, -0x0 })
    _mm_store_ps(xmm2, xmm1)
    _mm_or_ps(xmm2, { M_PI, M_PI, M_PI, M_PI })
    _mm_store_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm3, xmm0)
    _mm_sub_ps(xmm2, xmm0)
    _mm_cmple_ps(xmm3, { M_PI_2, M_PI_2, M_PI_2, M_PI_2 })
    _mm_store_ps(xmm4, xmm3)
    _mm_and_ps(xmm0, xmm3)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_or_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm4)
    _mm_and_ps(xmm0, { 1.0, 1.0, 1.0, 1.0 })
    _mm_andnot_ps(xmm4, { -1.0, -1.0, -1.0, -1.0 })
    _mm_or_ps(xmm0, xmm4)

    _mm_store_ps(xmm3, { -2.6051615e-07, -0.49992746, 0.041493919, -0.0012712436 })
    _mm_store_ps(xmm2, _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm3, { -0.5, +0.041666638, -0.0013888378, +2.4760495e-05 })
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(3,3,3,3)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(2,2,2,2)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(1,1,1,1)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, { 1.0, 1.0, 1.0, 1.0 })
    _mm_mul_ps(xmm0, xmm2)
    ret
    endp

 assume class:rbx

