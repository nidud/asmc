; https://x.com/yuruyurau/status/2091536763152142373
;
; a=(y,d=mag(k=5*cos(y*9),e=y/2-15)/3+sin(t)**4)
; =>point((79+k*k)*sin(c=d/2-t)+200,
; 89*sin(c/2)+7/d*sin(k*2)+y/(y<6?7:99*sin(e/2)+1)*k*e+d**3/6*sin(t*9-d*2)+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);
; background(9).stroke(w,66);for(t+=PI/240,i=1e4;i--;)a(i/254)}
;

include stdafx.inc

define TIMER   30
define STEPDIV 240
define MAXOBJ  10000

define X_LINK  <"https://x.com/yuruyurau/status/2091536763152142373">

CApplication::Point proc id:UINT

   .new m:real4, e, d, x

    ldr edx,id

    _mm_move_ss(m, _mm_div_ss(_mm_cvt_si2ss(xmm0, edx), 254.0))
    _mm_move_ss(xmm7, _mm_mul_ss(_mm_cos_ss(_mm_mul_ss(xmm0, 9.0)), 5.0))
    _mm_move_ss(e, _mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm1, m), 0.5), 15.0))
    _mm_move_ss(xmm6, _mm_div_ss(_mm_mag_ss(xmm0, xmm1), 3.0))
    _mm_move_ss(d, _mm_add_ss(_mm_pow_ss(_mm_sin_ss(m_time), 4), xmm6))
    _mm_move_ss(xmm6, _mm_sub_ss(_mm_mul_ss(xmm0, 0.5), m_time))
    _mm_move_ss(xmm1, _mm_sin_ss(xmm0))
    _mm_add_ss(_mm_mul_ss(_mm_move_ss(xmm0, xmm7), xmm0), 79.0)
    _mm_move_ss(x, _mm_add_ss(_mm_mul_ss(xmm0, xmm1), 200.0))

    _mm_move_ss(xmm6, _mm_mul_ss(_mm_sin_ss(_mm_mul_ss(xmm6, 0.5)), 89.0))
    _mm_move_ss(xmm1, _mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, xmm7), 2.0)))
    _mm_add_ss(_mm_add_ss(xmm6, _mm_mul_ss(_mm_div_ss(_mm_move_ss(xmm0, 7.0), d), xmm1)), 200.0)
    _mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm0, m_time), 9.0), _mm_mul_ss(_mm_move_ss(xmm1, d), 2.0))
    _mm_move_ss(xmm2, _mm_sin_ss(xmm0))
    _mm_add_ss(xmm6, _mm_mul_ss(_mm_div_ss(_mm_pow_ss(_mm_move_ss(xmm0, d), 3), 6.0), xmm2))
    .if ( _mm_move_ss(xmm0, m) < 6.0 )
        _mm_div_ss(xmm0, 7.0)
    .else
        _mm_mul_ss(_mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, e), 0.5)), 99.0)
        _mm_move_ss(xmm0, _mm_div_ss(_mm_move_ss(xmm1, m), _mm_add_ss(xmm0, 1.0)))
    .endif
    _mm_move_ss(xmm1, _mm_add_ss(_mm_mul_ss(_mm_mul_ss(xmm0, xmm7), e), xmm6))
    _mm_move_ss(xmm0, x)
    ret
    endp

include winmain.inc
