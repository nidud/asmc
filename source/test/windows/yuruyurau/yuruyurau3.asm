; https://x.com/yuruyurau/status/2091540720628932622
;
; a=(y,d=mag(k=5*cos(y*9),e=y-35)/2.5)
; =>point((79+k*k+d*4)*sin(c=d/3-t)+200,
; 89*sin(c/2)+7/d*sin(k*2)+y/44*k*e+d*3*sin(t*9-d*2+sin(t)/.6**3)+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);
; background(9).stroke(w,66);for(t+=PI/240,i=1e4;i--;)a(i/254)}
;

include stdafx.inc

D = 15
T proto {
  _mm_move_sd(t, _mm_add_sd(_mm_move_sd(xmm0, t), M_PI/240.0))
  }

A proto {
  _mm_move_sd(m, _mm_div_sd(_mm_cvtsi32_sd(xmm0, ebx), 254.0))
  _mm_move_sd(k, _mm_mul_sd(_mm_cos_sd(_mm_mul_sd(xmm0, 9.0)), 5.0))
  _mm_move_sd(e, _mm_sub_sd(_mm_move_sd(xmm1, m), 35.0))
  _mm_move_sd(d, _mm_div_sd(_mm_mag_sd(xmm0, xmm1), 2.5))
  _mm_move_sd(c, _mm_sub_sd(_mm_div_sd(xmm0, 3.0), t))
  _mm_sin_sd(xmm0)
  _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_move_sd(xmm1, k), xmm1), 79.0), _mm_mul_sd(_mm_move_sd(xmm2, d), 4.0))
  _mm_move_sd(x, _mm_add_sd(_mm_mul_sd(xmm0, xmm1), 200.0))
  _mm_move_sd(xmm6, _mm_mul_sd(_mm_sin_sd(_mm_mul_sd(_mm_move_sd(xmm0, c), 0.5)), 89.0))
  _mm_move_sd(xmm3, _mm_sin_sd(_mm_add_sd(_mm_move_sd(xmm0, k), xmm0)))
  _mm_add_sd(xmm6, _mm_mul_sd(_mm_div_sd(_mm_move_sd(xmm0, 7.0), d), xmm3))
  _mm_add_sd(xmm6, _mm_mul_sd(_mm_mul_sd(_mm_div_sd(_mm_move_sd(xmm0, m), 44.0), k), e))
  _mm_move_sd(xmm7, _mm_sin_sd(t))
  _mm_div_sd(xmm7, _mm_pow_sd(_mm_move_sd(xmm0, 0.6), 3))
  _mm_add_sd(xmm7, _mm_mul_sd(_mm_move_sd(xmm0, d), 2.0))
  _mm_move_sd(xmm7, _mm_sin_sd(_mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm0, t), 9.0), xmm7)))
  _mm_move_sd(y, _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_mul_sd(_mm_move_sd(xmm0, d), 3.0), xmm7), 200.0), xmm6))
  }

include winmain.inc

