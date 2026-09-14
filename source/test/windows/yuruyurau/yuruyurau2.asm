; https://x.com/yuruyurau/status/2091536763152142373
;
; a=(y,d=mag(k=5*cos(y*9),e=y/2-15)/3+sin(t)**4)
; =>point((79+k*k)*sin(c=d/2-t)+200,
; 89*sin(c/2)+7/d*sin(k*2)+y/(y<6?7:99*sin(e/2)+1)*k*e+d**3/6*sin(t*9-d*2)+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);
; background(9).stroke(w,66);for(t+=PI/240,i=1e4;i--;)a(i/254)}
;

include stdafx.inc

define D 10

T proto {
  _mm_move_sd(t, _mm_add_sd(_mm_move_sd(xmm0, t), M_PI/240.0))
  }

A proto {
  _mm_move_sd(m, _mm_div_sd(_mm_cvtsi32_sd(xmm0, ebx), 254.0))
  _mm_move_sd(k, _mm_mul_sd(_mm_cos_sd(_mm_mul_sd(xmm0, 9.0)), 5.0))
  _mm_move_sd(e, _mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm1, m), 0.5), 15.0))
  _mm_move_sd(d, _mm_div_sd(_mm_mag_sd(xmm0, xmm1), 3.0))
  _mm_move_sd(d, _mm_add_sd(_mm_pow_sd(_mm_sin_sd(t), 4), d))
  _mm_move_sd(c, _mm_sub_sd(_mm_div_sd(xmm0, 2.0), t))
  _mm_move_sd(x, _mm_add_sd(_mm_mul_sd(_mm_sin_sd(xmm0), _mm_add_sd(_mm_mul_sd(_mm_move_sd(xmm1, k), xmm1), 79.0)), 200.0))
  _mm_move_sd(y, _mm_mul_sd(_mm_sin_sd(_mm_mul_sd(_mm_move_sd(xmm0, c), 0.5)), 89.0))
  _mm_mul_sd(_mm_sin_sd(_mm_mul_sd(_mm_move_sd(xmm0, k), 2.0)), _mm_div_sd(_mm_move_sd(xmm1, 7.0), d))
  _mm_move_sd(y, _mm_add_sd(xmm0, y))
  .if ( _mm_move_sd(xmm0, m) < 6.0 )
    _mm_div_sd(xmm0, 7.0)
  .else
    _mm_add_sd(_mm_mul_sd(_mm_sin_sd(_mm_mul_sd(_mm_move_sd(xmm0, e), 0.5)), 99.0), 1.0)
    _mm_move_sd(xmm0, _mm_div_sd(_mm_move_sd(xmm1, m), xmm0))
  .endif
  _mm_move_sd(y, _mm_add_sd(_mm_mul_sd(_mm_mul_sd(xmm0, k), e), y))
  movsd xmm3,sin(_mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm0, t), 9.0), _mm_mul_sd(_mm_move_sd(xmm1, d), 2.0)))
  _mm_move_sd(y, _mm_add_sd(_mm_add_sd(_mm_add_sd(_mm_div_sd(_mm_pow_sd(_mm_move_sd(xmm0, d), 3), 6.0), xmm3), 200.0), y))
  }

include winmain.inc

