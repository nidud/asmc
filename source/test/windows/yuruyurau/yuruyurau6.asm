; https://x.com/yuruyurau/status/2108593527961899180
;
; a=(y,d=mag(k=(5+3*sin(y+4))*cos(i/7),e=y/5-9)-2.8+sin(t-k*k/9))
; =>point((q=3*sin(k*2)+k*y/25*(d*2.5+2*sin(e*6-d*5+t*3)))+6*d*cos(c=d-t)+200,q*sin(c)+d*39)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(9).stroke(w,46);for(t+=PI/240,i=2e4;i--;)a(i/885)};

include stdafx.inc

define TIMER   36
define STEPDIV 80
define MAXOBJ  20000

define X_LINK  <"https://x.com/yuruyurau/status/2108593527961899180">

CApplication::Point proc uses xmm6 xmm7 i:UINT

   .new m:real4, k, e, c, d, q, x

    ldr edx,i

    ; m = i / 885
    _mm_move_ss(xmm1, _mm_cvt_si2ss(xmm0, edx))
    _mm_move_ss(m, _mm_div_ss(xmm1, 885.0))

    ; k = ( 5 + 3 * sin(m + 4) ) * cos(i / 7)
    _mm_move_ss(xmm6, _mm_cos_ss(_mm_div_ss(xmm0, 7.0)))
    _mm_mul_ss(_mm_sin_ss(_mm_add_ss(_mm_move_ss(xmm0, m), 4.0)), 3.0)
    _mm_move_ss(k, _mm_mul_ss(_mm_add_ss(xmm0, 5.0), xmm6))

    ; e = m / 5 - 9
    _mm_move_ss(e, _mm_sub_ss(_mm_div_ss(_mm_move_ss(xmm1, m), 5.0), 9.0))

    ; d = mag(k, e) - 2.8 + sin(t - k * k / 9)
    _mm_move_ss(xmm6, _mm_sub_ss(_mm_hypot_ss(xmm0, xmm1), 2.8))
    _mm_div_ss(_mm_mul_ss(_mm_move_ss(xmm1, k), xmm1), 9.0)
    _mm_sub_ss(_mm_move_ss(xmm0, m_time), xmm1)
    _mm_move_ss(d, _mm_add_ss(_mm_sin_ss(xmm0), xmm6))

    ; c = d - t
    _mm_move_ss(c, _mm_sub_ss(xmm0, m_time))

    ; q = 3 * sin(k * 2) + k * m / 25 * (d * 2.5 + 2 * sin(e * 6 - d * 5 + t * 3))
    _mm_move_ss(xmm6, _mm_mul_ss(_mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, k), 2.0)), 3.0))
    _mm_mul_ss(_mm_move_ss(xmm0, e), 6.0)
    _mm_mul_ss(_mm_move_ss(xmm1, d), 5.0)
    _mm_mul_ss(_mm_move_ss(xmm2, m_time), 3.0)
    _mm_mul_ss(_mm_sin_ss(_mm_add_ss(_mm_sub_ss(xmm0, xmm1), xmm2)), 2.0)
    _mm_add_ss(_mm_mul_ss(_mm_move_ss(xmm1, d), 2.5), xmm0)
    _mm_div_ss(_mm_move_ss(xmm0, m), 25.0)
    _mm_mul_ss(_mm_mul_ss(xmm0, xmm1), k)
    _mm_move_ss(q, _mm_add_ss(xmm0, xmm6))

    ; x = q + 6 * d * cos(c) + 200
    _mm_mul_ss(_mm_mul_ss(_mm_cos_ss(c), d), 6.0)
    _mm_move_ss(x, _mm_add_ss(_mm_add_ss(xmm0, q), 200.0))

    ; y = q * sin(c) + d * 39
    _mm_mul_ss(_mm_sin_ss(c), q)
    _mm_add_ss(_mm_mul_ss(_mm_move_ss(xmm1, d), 39.0), xmm0)
    _mm_move_ss(xmm0, x)
    ret
    endp

include winmain.inc
