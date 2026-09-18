; https://x.com/yuruyurau/status/2091540720628932622
;
; a=(y,d=mag(k=5*cos(y*9),e=y-35)/2.5)
; =>point((79+k*k+d*4)*sin(c=d/3-t)+200,
; 89*sin(c/2)+7/d*sin(k*2)+y/44*k*e+d*3*sin(t*9-d*2+sin(t)/.6**3)+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);
; background(9).stroke(w,66);for(t+=PI/240,i=1e4;i--;)a(i/254)}
;
include stdafx.inc

define TIMER   30
define STEPDIV 240
define MAXOBJ  10000

define X_LINK  <"https://x.com/yuruyurau/status/2091540720628932622">

CApplication::Point proc id:UINT

   .new m:real4, e, d, x
    ldr edx,id
    _mm_move_ss(m, _mm_div_ss(_mm_cvt_si2ss(xmm0, edx), 254.0))
    _mm_move_ss(xmm7, _mm_mul_ss(_mm_cos_ss(_mm_mul_ss(xmm0, 9.0)), 5.0))
    _mm_move_ss(e, _mm_sub_ss(_mm_move_ss(xmm1, m), 35.0))
    _mm_move_ss(d, _mm_div_ss(_mm_mag_ss(xmm0, xmm1), 2.5))
    _mm_move_ss(xmm6, _mm_sub_ss(_mm_div_ss(xmm0, 3.0), m_time))
    _mm_sin_ss(xmm0)
    _mm_add_ss(_mm_add_ss(_mm_mul_ss(_mm_move_ss(xmm1, xmm7), xmm1), 79.0), _mm_mul_ss(_mm_move_ss(xmm2, d), 4.0))
    _mm_move_ss(x, _mm_add_ss(_mm_mul_ss(xmm0, xmm1), 200.0))
    _mm_move_ss(xmm6, _mm_mul_ss(_mm_sin_ss(_mm_mul_ss(xmm6, 0.5)), 89.0))
    _mm_move_ss(xmm3, _mm_sin_ss(_mm_add_ss(_mm_move_ss(xmm0, xmm7), xmm0)))
    _mm_add_ss(xmm6, _mm_mul_ss(_mm_div_ss(_mm_move_ss(xmm0, 7.0), d), xmm3))
    _mm_add_ss(xmm6, _mm_mul_ss(_mm_mul_ss(_mm_div_ss(_mm_move_ss(xmm0, m), 44.0), xmm7), e))
    _mm_move_ss(xmm7, _mm_sin_ss(m_time))
    _mm_div_ss(xmm7, _mm_pow_ss(_mm_move_ss(xmm0, 0.6), 3))
    _mm_add_ss(xmm7, _mm_mul_ss(_mm_move_ss(xmm0, d), 2.0))
    _mm_move_ss(xmm7, _mm_sin_ss(_mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm0, m_time), 9.0), xmm7)))
    _mm_move_ss(xmm1, _mm_add_ss(_mm_add_ss(_mm_mul_ss(_mm_mul_ss(_mm_move_ss(xmm0, d), 3.0), xmm7), 200.0), xmm6))
    _mm_move_ss(xmm0, x)
    ret
    endp

include winmain.inc
