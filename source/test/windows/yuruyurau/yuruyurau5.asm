; https://x.com/yuruyurau/status/2103900438961778890
;
; a=(y,d=mag(k=6*cos(i/66),e=y/2-15)/3)
; =>point((79+d*d+k*k)*sin(c=d/2-t/3+i%2*5)/2+200,99*cos(c/3)+6/d*sin(k*2)+y/(97*sin(e/2)+.1)*k*e/2+d*d/2*cos(t*3-d*d/4)+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(9).stroke(w,66);for(t+=PI/80,i=2e4;i--;)a(i/595)}
;

include stdafx.inc

define TIMER   36
define STEPDIV 40
define MAXOBJ  20000

define X_LINK  <"https://x.com/yuruyurau/status/2103900438961778890">

CApplication::Point proc uses xmm6 xmm7 i:UINT

   .new m:real4, k, e, c, d

    ldr edx,i

    ; m = i / 595
    _mm_move_ss(xmm1, _mm_cvt_si2ss(xmm0, edx))
    _mm_move_ss(m, _mm_div_ss(xmm1, 595.0))

    ; k = 6 * cos(i / 66)
    _mm_move_ss(k, _mm_mul_ss(_mm_cos_ss(_mm_div_ss(xmm0, 66.0)), 6.0))

    ; e = m / 2 - 15
    _mm_move_ss(e, _mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm1, m), 0.5), 15.0))

    ; d = mag(k, e) / 3
    _mm_move_ss(d, _mm_div_ss(_mm_hypot_ss(xmm0, xmm1), 3.0))

    ; c = d / 2 - t / 3 + i % 2 * 5
    and edx,1
    imul eax,edx,5
    _mm_sub_ss(_mm_mul_ss(xmm0, 0.5), _mm_div_ss(_mm_move_ss(xmm1, m_time), 3.0))
    _mm_move_ss(c, _mm_add_ss(xmm0, _mm_cvt_si2ss(xmm1, eax)))

    ; x = (79 + d * d + k * k) * sin(c) / 2 + 200
    _mm_sin_ss(xmm0)
    _mm_mul_ss(_mm_move_ss(xmm1, k), xmm1)
    _mm_mul_ss(_mm_move_ss(xmm2, d), xmm2)
    _mm_add_ss(_mm_add_ss(xmm1, xmm2), 79.0)
    _mm_mul_ss(_mm_mul_ss(xmm0, xmm1), 0.5)
    _mm_move_ss(xmm6, _mm_add_ss(xmm0, 200.0))

    ; y = 99 * cos(c / 3)
    _mm_move_ss(xmm7, _mm_mul_ss(_mm_cos_ss(_mm_div_ss(_mm_move_ss(xmm0, c), 3.0)), 99.0))
    ;     + 6 / d * sin(k * 2)
    _mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, k), 2.0))
    _mm_div_ss(_mm_move_ss(xmm1, 6.0), d)
    _mm_add_ss(xmm7, _mm_mul_ss(xmm0, xmm1))
    ;     + m / (97 * sin(e / 2) + .1) * k * e / 2
    _mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, e), 0.5))
    _mm_add_ss(_mm_mul_ss(xmm0, 97.0), 0.1)
    _mm_div_ss(_mm_move_ss(xmm1, m), xmm0)
    _mm_mul_ss(_mm_mul_ss(xmm1, k), e)
    _mm_add_ss(xmm7, _mm_mul_ss(xmm1, 0.5))
    ;     + d * d / 2 * cos(t * 3 - d * d / 4)
    _mm_mul_ss(_mm_move_ss(xmm0, m_time), 3.0)
    _mm_div_ss(_mm_mul_ss(_mm_move_ss(xmm1, d), xmm1), 4.0)
    _mm_cos_ss(_mm_sub_ss(xmm0, xmm1))
    _mm_div_ss(_mm_mul_ss(_mm_move_ss(xmm1, d), xmm1), 2.0)
    _mm_add_ss(_mm_mul_ss(xmm0, xmm1), xmm7)
    ;     + 200
    _mm_move_ss(xmm1, _mm_add_ss(xmm0, 200.0))
    _mm_move_ss(xmm0, xmm6)
    ret
    endp

include winmain.inc
