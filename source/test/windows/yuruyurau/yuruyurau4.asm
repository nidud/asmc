; https://x.com/yuruyurau/status/2093711731084415124
;
; a=(y,d=mag(k=(4+cos(y))*cos(i),e=y/5-11)-6)
; =>point((79+k*k)*cos(c=d/2-t/2+i%2*8)+200,
; 99*sin(c/3)+d**3/5*sin(t*3-d/.7)+3*sin(k*2)+y/13*k*(e+sin(e*4-d*4))+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(9).stroke(w,96);
; for(t+=PI/60,i=1e4;i--;)a(i/498)}

include stdafx.inc

T proto {
  _mm_move_sd(t, _mm_add_sd(_mm_move_sd(xmm0, t), M_PI/60.0))
  }

A proto {
  _mm_move_sd(i, _mm_cvtsi32_sd(xmm0, ebx))
  _mm_move_sd(m, _mm_div_sd(xmm0, 498.0))
  _mm_move_sd(xmm6, _mm_add_sd(_mm_cos_sd(xmm0), 4.0))
  _mm_move_sd(k, _mm_mul_sd(_mm_cos_sd(i), xmm6))
  _mm_move_sd(e, _mm_sub_sd(_mm_div_sd(_mm_move_sd(xmm0, m), 5.0), 11.0))
  _mm_move_sd(d, _mm_sub_sd(_mm_mag_sd(xmm0, _mm_move_sd(xmm1, k)), 6.0))
  mov eax,ebx
  and eax,1
  shl eax,3
  _mm_sub_sd(_mm_mul_sd(xmm0, 0.5), _mm_mul_sd(_mm_move_sd(xmm1, t), 0.5))
  _mm_move_sd(c, _mm_add_sd(xmm0, _mm_cvtsi32_sd(xmm1, eax)))
  _mm_move_sd(x, _mm_add_sd(_mm_mul_sd(_mm_cos_sd(xmm0), _mm_add_sd(_mm_mul_sd(_mm_move_sd(xmm1, k), xmm1), 79.0)), 200.0))
  _mm_move_sd(xmm6, _mm_mul_sd(_mm_sin_sd(_mm_div_sd(_mm_move_sd(xmm0, c), 3.0)), 99.0))
  _mm_move_sd(xmm7, _mm_pow_sd(_mm_move_sd(xmm0, d), 3))
  _mm_add_sd(xmm6, _mm_mul_sd(_mm_sin_sd(_mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm0, t), 3.0), _mm_div_sd(_mm_move_sd(xmm1, d), 0.7))), _mm_div_sd(xmm7, 5.0)))
  _mm_add_sd(xmm6, _mm_mul_sd(_mm_sin_sd(_mm_mul_sd(_mm_move_sd(xmm0, k), 2.0)), 3.0))
  _mm_add_sd(_mm_sin_sd(_mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm0, e), 4.0), _mm_mul_sd(_mm_move_sd(xmm1, d), 4.0))), e)
  _mm_move_sd(xmm7, _mm_mul_sd(xmm0, k))
  _mm_mul_sd(_mm_div_sd(_mm_move_sd(xmm0, m), 13.0), xmm7)
  _mm_move_sd(y, _mm_add_sd(_mm_add_sd(xmm0, xmm6), 200.0))
  }

include winmain.inc

