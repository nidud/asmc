; https://x.com/yuruyurau/status/2093711731084415124
;
; a=(y,d=mag(k=(4+cos(y))*cos(i),e=y/5-11)-6)
; =>point((79+k*k)*cos(c=d/2-t/2+i%2*8)+200,
; 99*sin(c/3)+d**3/5*sin(t*3-d/.7)+3*sin(k*2)+y/13*k*(e+sin(e*4-d*4))+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(9).stroke(w,96);
; for(t+=PI/60,i=1e4;i--;)a(i/498)}

include stdafx.inc

define TIMER   30
define STEPDIV 60
define MAXOBJ  10000

define X_LINK  <"https://x.com/yuruyurau/status/2093711731084415124">

CApplication::Point proc id:UINT

   .new m:real4, e, d, i, x, k, c

    ldr edx,id

    _mm_move_ss(i, _mm_cvt_si2ss(xmm0, edx))
    _mm_move_ss(m, _mm_div_ss(xmm0, 498.0))
    _mm_move_ss(xmm6, _mm_add_ss(_mm_cos_ss(xmm0), 4.0))
    _mm_move_ss(k, _mm_mul_ss(_mm_cos_ss(i), xmm6))
    _mm_move_ss(e, _mm_sub_ss(_mm_div_ss(_mm_move_ss(xmm0, m), 5.0), 11.0))
    _mm_move_ss(d, _mm_sub_ss(_mm_mag_ss(xmm0, _mm_move_ss(xmm1, k)), 6.0))
    and edx,1
    shl edx,3
    _mm_sub_ss(_mm_mul_ss(xmm0, 0.5), _mm_mul_ss(_mm_move_ss(xmm1, m_time), 0.5))
    _mm_move_ss(c, _mm_add_ss(xmm0, _mm_cvt_si2ss(xmm1, edx)))
    _mm_move_ss(x, _mm_add_ss(_mm_mul_ss(_mm_cos_ss(xmm0), _mm_add_ss(_mm_mul_ss(_mm_move_ss(xmm1, k), xmm1), 79.0)), 200.0))
    _mm_move_ss(xmm6, _mm_mul_ss(_mm_sin_ss(_mm_div_ss(_mm_move_ss(xmm0, c), 3.0)), 99.0))
    _mm_move_ss(xmm7, _mm_pow_ss(_mm_move_ss(xmm0, d), 3))
    _mm_add_ss(xmm6, _mm_mul_ss(_mm_sin_ss(_mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm0, m_time), 3.0), _mm_div_ss(_mm_move_ss(xmm1, d), 0.7))), _mm_div_ss(xmm7, 5.0)))
    _mm_add_ss(xmm6, _mm_mul_ss(_mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, k), 2.0)), 3.0))
    _mm_add_ss(_mm_sin_ss(_mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm0, e), 4.0), _mm_mul_ss(_mm_move_ss(xmm1, d), 4.0))), e)
    _mm_move_ss(xmm7, _mm_mul_ss(xmm0, k))
    _mm_mul_ss(_mm_div_ss(_mm_move_ss(xmm0, m), 13.0), xmm7)
    _mm_move_ss(xmm1, _mm_add_ss(_mm_add_ss(xmm0, xmm6), 200.0))
    _mm_move_ss(xmm0, x)
    ret
    endp

include winmain.inc

