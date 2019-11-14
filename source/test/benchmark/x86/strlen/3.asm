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
;

	.686
	.xmm
	.model flat, c
	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strlen	proc string

	mov	edx,[esp+4]	; string
	mov	ecx,edx
	and	ecx,3Fh
	pxor	xmm0,xmm0
	cmp	ecx,30h
	ja	next
	movdqu	xmm1,[edx]

	pcmpeqb xmm0,xmm1
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit_less16
	mov	eax,edx
	and	eax,-16
	jmp	align16_start
next:
	mov	eax,edx
	and	eax,-16
	PUSH	edi
	pcmpeqb xmm0,[eax]
	mov	edi,-1
	sub	ecx,eax
	shl	edi,cl
	pmovmskb ecx,xmm0
	and	ecx,edi
	POP	edi
	jnz	exit_unaligned
	pxor	xmm0,xmm0
align16_start:
	pxor	xmm1,xmm1
	pxor	xmm2,xmm2
	pxor	xmm3,xmm3
	pcmpeqb xmm0,[eax+16]
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[eax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[eax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[eax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	pcmpeqb xmm0,[eax+80]
	add	eax,64
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[eax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[eax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[eax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	pcmpeqb xmm0,[eax+80]
	add	eax,64
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[eax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[eax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[eax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	pcmpeqb xmm0,[eax+80]
	add	eax,64
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[eax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[eax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[eax+64]
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit64

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm0,[eax+80]
	add	eax,80
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm1,[eax+16]
	add	eax,16
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm2,[eax+16]
	add	eax,16
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit

	test	eax,3fh
	jz	align64_loop

	pcmpeqb xmm3,[eax+16]
	add	eax,16
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jnz	exit

	add	eax,16
	align 4
align64_loop:
	movaps	xmm4,[eax]
	pminub	xmm4,[eax+16]
	movaps	xmm5,[eax+32]
	pminub	xmm5,[eax+48]
	add	eax,64
	pminub	xmm5,xmm4
	pcmpeqb xmm5,xmm0
	pmovmskb ecx,xmm5
	test	ecx,ecx
	jz	align64_loop

	pcmpeqb xmm0,[eax-64]
	sub	eax,80
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit16

	pcmpeqb xmm1,[eax+32]
	pmovmskb ecx,xmm1
	test	ecx,ecx
	jnz	exit32

	pcmpeqb xmm2,[eax+48]
	pmovmskb ecx,xmm2
	test	ecx,ecx
	jnz	exit48

	pcmpeqb xmm3,[eax+64]
	pmovmskb ecx,xmm3

	sub	eax,edx
	bsf	ecx,ecx
	add	eax,ecx
	add	eax,64
	ret

	align 4
exit:
	sub	eax,edx
	bsf	ecx,ecx
	add	eax,ecx
	ret

exit_less16:
	bsf	eax,ecx
	ret

	align 4
exit_unaligned:
	sub	eax,edx
	bsf	ecx,ecx
	add	eax,ecx
	ret

	align 4
exit16:
	sub	eax,edx
	bsf	ecx,ecx
	add	eax,ecx
	add	eax,16
	ret

	align 4
exit32:
	sub	eax,edx
	bsf	ecx,ecx
	add	eax,ecx
	add	eax,32
	ret

	align 4
exit48:
	sub	eax,edx
	bsf	ecx,ecx
	add	eax,ecx
	add	eax,48
	ret

	align 4
exit64:
	sub	eax,edx
	bsf	ecx,ecx
	add	eax,ecx
	add	eax,64
	ret

strlen	endp

	END
