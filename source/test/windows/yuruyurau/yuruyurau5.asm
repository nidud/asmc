; https://x.com/yuruyurau/status/2099149181474750888
;
; a=(y,d=mag(k=(4+cos(y))*cos(i/7),e=y/5-11)-6)
; =>point((q=99+3*sin(9/k)+y/23*k*(e+sin(-d*4)))*sin(c=d/4-t/4+i%2*9+sin(t*3+e)/9)+200, q*cos(c)+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(9).stroke(w,166);for(t+=PI/60,i=1e4;i--;)a(i/289)}
;
include stdafx.inc

T proto {
  _mm_move_sd(t, _mm_add_sd(_mm_move_sd(xmm0, t), M_PI/60.0))
  }

A proto {
  _mm_move_sd(i, _mm_cvtsi32_sd(xmm0, ebx))
  _mm_move_sd(m, _mm_div_sd(xmm0, 289.0))
  _mm_move_sd(xmm6, _mm_add_sd(_mm_cos_sd(xmm0), 4.0))
  _mm_move_sd(k, _mm_mul_sd(_mm_cos_sd(_mm_div_sd(_mm_move_sd(xmm0, i), 7.0)), xmm6))
  _mm_move_sd(e, _mm_sub_sd(_mm_div_sd(_mm_move_sd(xmm0, m), 5.0), 11.0))
  _mm_move_sd(d, _mm_sub_sd(_mm_mag_sd(_mm_move_sd(xmm0, k), _mm_move_sd(xmm1, e)), 6.0))
  _mm_move_sd(xmm3, _mm_div_sd(_mm_sin_sd(_mm_add_sd(_mm_mul_sd(_mm_move_sd(xmm0, t), 3.0), e)), 9.0))
  mov eax,ebx
  and eax,1
  _mm_mul_sd(_mm_cvtsi32_sd(xmm2, eax), 9.0)
  _mm_mul_sd(_mm_move_sd(xmm1, t), 0.25)
  _mm_mul_sd(_mm_move_sd(xmm0, d), 0.25)
  _mm_move_sd(c, _mm_add_sd(_mm_add_sd(_mm_sub_sd(xmm0, xmm1), xmm2), xmm3))
  movsd xmm1,d
  movaps xmm0,{ -0.0, 0.0 }
  _mm_move_sd(xmm6, _mm_mul_sd(_mm_add_sd(_mm_sin_sd(_mm_mul_sd(_mm_or_pd(xmm0, xmm1), 4.0)), e), k))
  _mm_add_sd(_mm_mul_sd(xmm6, _mm_div_sd(_mm_move_sd(xmm0, m), 23.0)), 99.0)
  _mm_add_sd(xmm6, _mm_mul_sd(_mm_sin_sd(_mm_div_sd(_mm_move_sd(xmm0, 9.0), k)), 3.0))
  _mm_move_sd(x, _mm_add_sd(_mm_mul_sd(_mm_sin_sd(c), xmm6), 200.0))
  _mm_move_sd(y, _mm_add_sd(_mm_mul_sd(_mm_cos_sd(c), xmm6), 200.0))
  }

include winmain.inc

