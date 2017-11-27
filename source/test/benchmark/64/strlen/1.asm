;
; Copyright (c) 2014, Intel Corporation
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
;
;     * Redistributions of source code must retain the above copyright notice,
;     * this list of conditions and the following disclaimer.
;
;     * Redistributions in binary form must reproduce the above copyright notice,
;     * this list of conditions and the following disclaimer in the documentation
;     * and/or other materials provided with the distribution.
;
;     * Neither the name of Intel Corporation nor the names of its contributors
;     * may be used to endorse or promote products derived from this software
;     * without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
; ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
; ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;
; 2015-03-23 - converted from AT&T syntax (nidud)
; 2016-09-20 - converted to 64-bit (nidud)
;
ifndef __64__
	.x64
	.model	flat, fastcall
endif
	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

	mov	rdx,rcx		; string
	and	rcx,3Fh
	pxor	xmm0,xmm0
	cmp	rcx,30h
	ja	next
	movdqu	xmm1,[rdx]

	pcmpeqb xmm0,xmm1
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit_less16
	mov	rax,rdx
	and	rax,-16
	jmp	align16_start
next:
	mov	rax,rdx
	and	rax,-16
;	PUSH	rdi
	pcmpeqb xmm0,[rax]
	mov	r8d,-1
	sub	rcx,rax
	shl	r8d,cl
	pmovmskb ecx,xmm0
	and	ecx,r8d
;	POP	rdi
	jnz	exit_unaligned
	pxor	xmm0,xmm0
align16_start:
	pxor	xmm1,xmm1
	pxor	xmm2,xmm2
	pxor	xmm3,xmm3
	pcmpeqb xmm0,[rax+16]
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[rax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[rax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[rax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	pcmpeqb xmm0,[rax+80]
	add	rax,64
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[rax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[rax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[rax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	pcmpeqb xmm0,[rax+80]
	add	rax,64
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[rax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[rax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[rax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	pcmpeqb xmm0,[rax+80]
	add	eax,64
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[rax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[rax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[rax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm0,[rax+80]
	add	rax,80
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm1,[rax+16]
	add	rax,16
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm2,[rax+16]
	add	rax,16
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm3,[rax+16]
	add	rax,16
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit

	add	rax,16
	align 4
align64_loop:
	movaps	xmm4,[rax]
	pminub	xmm4,[rax+16]
	movaps	xmm5,[rax+32]
	pminub	xmm5,[rax+48]
	add	rax,64
	pminub	xmm5,xmm4
	pcmpeqb xmm5,xmm0
	pmovmskb ecx,xmm5
	test	ecx,ecx
	jz	align64_loop

	pcmpeqb xmm0,[rax-64]
	sub	rax,80
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[rax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[rax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[rax+64]
	pmovmskb ecx,xmm3

	sub	rax,rdx
	bsf	ecx,ecx
	add	rax,rcx
	add	rax,64
	ret

	align 4
exit:
	sub	rax,rdx
	bsf	ecx,ecx
	add	rax,rcx
	ret

exit_less16:
	bsf	rax,rcx
	ret

	align 4
exit_unaligned:
	sub	rax,rdx
	bsf	ecx,ecx
	add	rax,rcx
	ret

	align 4
exit16:
	sub	rax,rdx
	bsf	rcx,rcx
	add	rax,rcx
	add	rax,16
	ret

	align 4
exit32:
	sub	rax,rdx
	bsf	ecx,ecx
	add	rax,rcx
	add	rax,32
	ret

	align 4
exit48:
	sub	rax,rdx
	bsf	ecx,ecx
	add	rax,rcx
	add	rax,48
	ret

	align 4
exit64:
	sub	rax,rdx
	bsf	ecx,ecx
	add	rax,rcx
	add	rax,64
	ret

	END
