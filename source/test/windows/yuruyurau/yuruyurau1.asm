; https://x.com/yuruyurau/status/2090832898488459699
;
; a=(m,d=mag(k=9*cos(i*5)*sin(i),e=cos(i*3)*cos(i*2)*9)**3/1999+1.5-sin(t/2+m)**3/3)=>
; point(99*sin(c=d/16-t/48+m)+k*(p=d**sin(d*d-t+m))+200,99*sin(c*4)+e*p+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(9).stroke(w,96);
; for(t+=PI/20,i=1e4;i--;)a(i%16*13)}

include stdafx.inc

define TIMER   30
define STEPDIV 20
define MAXOBJ  10000

define X_LINK  <"https://x.com/yuruyurau/status/2090832898488459699">

CApplication::Point proc id:UINT

   .new m:real4, e, d

    ldr edx,id
    mov eax,edx
    and eax,15
    imul eax,eax,13

    _mm_move_ss(m, _mm_cvt_si2ss(xmm0, eax))
    _mm_move_ss(xmm6, _mm_sin_ss(_mm_cvt_si2ss(xmm7, edx)))
    _mm_cos_ss(_mm_mul_ss(_mm_move_sd(xmm0, xmm7), 5.0))
    _mm_move_ss(xmm6, _mm_mul_ss(_mm_mul_ss(xmm0, 9.0), xmm6))
    _mm_move_ss(e, _mm_cos_ss(_mm_add_ss(_mm_move_ss(xmm0, xmm7), xmm0)))
    _mm_cos_ss(_mm_mul_ss(_mm_move_ss(xmm0, xmm7), 3.0))
    _mm_move_ss(e, _mm_mul_ss(_mm_mul_ss(xmm0, e), 9.0))
    _mm_pow_ss(_mm_mag_ss(xmm0, _mm_move_ss(xmm1, xmm6)), 3)
    _mm_move_ss(d, _mm_add_ss(_mm_div_ss(xmm0, 1999.0), 1.5))
    _mm_sin_ss(_mm_add_ss(_mm_mul_ss(_mm_move_ss(xmm0, m_time), 0.5), m))
    _mm_div_ss(_mm_pow_ss(xmm0, 3), 3.0)
    _mm_move_ss(d, _mm_sub_ss(_mm_move_ss(xmm1, d), xmm0))
    _mm_div_ss(_mm_move_ss(xmm0, m_time), 48.0)
    _mm_move_ss(xmm7, _mm_add_ss(_mm_sub_ss(_mm_div_ss(xmm1, 16.0), xmm0), m))
    movss d,powf(d, _mm_sin_ss(_mm_add_ss(_mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm0, d), xmm0), m_time), m)))
    _mm_add_ss(_mm_mul_ss(_mm_sin_ss(xmm7), 99.0), 200.0)
    _mm_move_ss(m, _mm_add_ss(xmm0, _mm_mul_ss(_mm_move_ss(xmm1, xmm6), d)))
    _mm_add_ss(_mm_mul_ss(_mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, xmm7), 4.0)), 99.0), 200.0)
    _mm_add_ss(xmm0, _mm_mul_ss(_mm_move_ss(xmm1, e), d))
    _mm_move_ss(xmm1, xmm0)
    _mm_move_ss(xmm0, m)
    ret
    endp

include winmain.inc
