
;--- test invoke "register value overwritten" with 64-bit
;--- v2.34.72 - added SIMD registers

	.x64
	.model flat, fastcall
	.code

p1 proc a1:qword,a2:dword,a3:word,a4:byte,a5:qword,a6:dword
p1 endp
p2 proc a1:real4,a2:real4,a3:real4,a4:real4
p2 endp
p3 proc a1:ptr,a2:vararg
p3 endp
;--- error: rdx overwritten
	invoke p1,rdx,2,3,4,5,6
;--- error: r8d overwritten
	invoke p1,1,r8d,3,4,5,6
;--- error: edx overwritten, eax overwritten
	invoke p1,addr [edx],eax,3,4,addr [ecx],addr [r8]
;--- error: eax overwritten
	invoke p1, rbx,eax,bx,bl,addr [esi],ebx
;--- error: xmm1 overwritten
	invoke p2, xmm1,xmm0,xmm2,xmm3
;--- error: xmm2 overwritten
	invoke p2, xmm0,xmm2,xmm0,xmm3
;--- error: xmm3 overwritten
	invoke p2, xmm0,xmm1,xmm3,xmm0
;--- error: xmm0 and xmm3 overwritten
	invoke p3, rsi,xmm1,xmm3,xmm0,real4 ptr [rbx]

	end
