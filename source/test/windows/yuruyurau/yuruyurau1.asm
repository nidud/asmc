; https://x.com/yuruyurau/status/2090832898488459699
;
; a=(m,d=mag(k=9*cos(i*5)*sin(i),e=cos(i*3)*cos(i*2)*9)**3/1999+1.5-sin(t/2+m)**3/3)=>
; point(99*sin(c=d/16-t/48+m)+k*(p=d**sin(d*d-t+m))+200,99*sin(c*4)+e*p+200)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(9).stroke(w,96);
; for(t+=PI/20,i=1e4;i--;)a(i%16*13)}

include stdafx.inc

D = 15
T proto {
  _mm_move_sd(t, _mm_add_sd(_mm_move_sd(xmm0, t), M_PI/20.0))
  }

A proto {
  _mm_move_sd(i, _mm_cvtsi32_sd(xmm0, ebx))
  mov eax,ebx
  and eax,15
  imul eax,eax,13
  _mm_move_sd(m, _mm_cvtsi32_sd(xmm1, eax))
  _mm_move_sd(k, _mm_sin_sd(xmm0))
  _mm_move_sd(k, _mm_mul_sd(_mm_mul_sd(_mm_cos_sd(_mm_mul_sd(_mm_move_sd(xmm0, i), 5.0)), 9.0), k))
  _mm_move_sd(e, _mm_cos_sd(_mm_add_sd(_mm_move_sd(xmm0, i), xmm0)))
  _mm_move_sd(e, _mm_mul_sd(_mm_mul_sd(_mm_cos_sd(_mm_mul_sd(_mm_move_sd(xmm0, i), 3.0)), e), 9.0))
  _mm_move_sd(d, _mm_add_sd(_mm_div_sd(_mm_pow_sd(_mm_mag_sd(xmm0, _mm_move_sd(xmm1, k)), 3), 1999.0), 1.5))
  _mm_div_sd(_mm_pow_sd(_mm_sin_sd(_mm_add_sd(_mm_mul_sd(_mm_move_sd(xmm0, t), 0.5), m)), 3), 3.0)
  _mm_move_sd(d, _mm_sub_sd(_mm_move_sd(xmm1, d), xmm0))
  _mm_move_sd(c, _mm_add_sd(_mm_sub_sd(_mm_div_sd(xmm1, 16.0), _mm_div_sd(_mm_move_sd(xmm0, t), 48.0)), m))
  movsd p,pow(d, _mm_sin_sd(_mm_add_sd(_mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm0, d), xmm0), t), m)))
  _mm_move_sd(x, _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_sin_sd(c), 99.0), 200.0), _mm_mul_sd(_mm_move_sd(xmm1, k), p)))
  _mm_move_sd(y, _mm_add_sd(_mm_add_sd(_mm_mul_sd(_mm_sin_sd(_mm_mul_sd(_mm_move_sd(xmm0, c), 4.0)), 99.0), 200.0), _mm_mul_sd(_mm_move_sd(xmm1, e), p)))
  }

include winmain.inc
