; https://x.com/yuruyurau/status/1875565755254894621
;
; a=(x,y,d=5*cos(o=mag(k=x/8-12.5,e=y/8-12.5)/12*cos(sin(k/2)*cos(e/2))))
; =>point((x+d*k*(sin(d*2+t)+sin(y*o*o)/9))/1.5+133,(y/3-d*40+19*cos(d+t))*1.5+300)
; t=0,draw=$=>{t||createCanvas(w=400,w);background(6,96).stroke(w,46);for(t+=PI/90,i=4e4;i--;)a(i%200,i/200)}
;
include stdafx.inc

define I 40000

T proto {
  _mm_move_sd(t, _mm_add_sd(_mm_move_sd(xmm0, t), M_PI/90.0))
  }

A proto {
  mov ecx,200
  mov eax,ebx
  cdq
  div ecx
  _mm_move_sd(i, _mm_cvtsi32_sd(xmm0, edx))
  _mm_move_sd(m, _mm_cvtsi32_sd(xmm0, eax))
  _mm_move_sd(k, _mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm0, i), 0.125), 12.5))
  _mm_move_sd(e, _mm_sub_sd(_mm_mul_sd(_mm_move_sd(xmm0, m), 0.125), 12.5))
  _mm_move_sd(xmm6, _mm_sin_sd(_mm_mul_sd(_mm_move_sd(xmm0, k), 0.5)))
  _mm_move_sd(xmm6, _mm_cos_sd(_mm_mul_sd(_mm_cos_sd(_mm_mul_sd(_mm_move_sd(xmm0, e), 0.5)), xmm6)))
  _mm_move_sd(p, _mm_mul_sd(_mm_div_sd(_mm_mag_sd(_mm_move_sd(xmm0, k), _mm_move_sd(xmm1, e)), 12.0), xmm6))
  _mm_move_sd(d, _mm_mul_sd(_mm_cos_sd(xmm0), 5.0))
  _mm_move_sd(xmm6, _mm_div_sd(_mm_sin_sd(_mm_mul_sd(_mm_mul_sd(_mm_move_sd(xmm0, m), p), p)), 9.0))
  _mm_add_sd(_mm_mul_sd(_mm_mul_sd(_mm_add_sd(_mm_sin_sd(_mm_add_sd(_mm_mul_sd(_mm_move_sd(xmm0, d), 2.0), t)), xmm6), k), d), i)
  _mm_move_sd(x, _mm_add_sd(_mm_div_sd(xmm0, 1.5), 133.0))
  _mm_mul_sd(_mm_cos_sd(_mm_add_sd(_mm_move_sd(xmm0, d), t)), 19.0)
  _mm_add_sd(xmm0, _mm_sub_sd(_mm_div_sd(_mm_move_sd(xmm1, m), 3.0), _mm_mul_sd(_mm_move_sd(xmm2, d), 40.0)))
  _mm_move_sd(y, _mm_add_sd(_mm_mul_sd(xmm0, 1.5), 300.0))
  }

include winmain.inc

