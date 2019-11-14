;
; Copyright (c) 2011, Intel Corporation
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
	xor	eax,eax
	cmp	byte ptr [edx],0
	jz	exit_tail0
	cmp	byte ptr [edx+1],0
	jz	exit_tail1
	cmp	byte ptr [edx+2],0
	jz	exit_tail2
	cmp	byte ptr [edx+3],0
	jz	exit_tail3

	cmp	byte ptr [edx+4],0
	jz	exit_tail4
	cmp	byte ptr [edx+5],0
	jz	exit_tail5
	cmp	byte ptr [edx+6],0
	jz	exit_tail6
	cmp	byte ptr [edx+7],0
	jz	exit_tail7

	cmp	byte ptr [edx+8],0
	jz	exit_tail8
	cmp	byte ptr [edx+9],0
	jz	exit_tail9
	cmp	byte ptr [edx+10],0
	jz	exit_tail10
	cmp	byte ptr [edx+11],0
	jz	exit_tail11

	cmp	byte ptr [edx+12],0
	jz	exit_tail12
	cmp	byte ptr [edx+13],0
	jz	exit_tail13
	cmp	byte ptr [edx+14],0
	jz	exit_tail14
	cmp	byte ptr [edx+15],0
	jz	exit_tail15

	pxor	xmm0,xmm0
	lea	eax,[edx+16]
	mov	ecx,eax
	and	eax,-16

	pcmpeqb xmm0,[eax]
	pmovmskb edx,xmm0
	pxor	xmm1,xmm1
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm1,[eax]
	pmovmskb edx,xmm1
	pxor	xmm2,xmm2
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm2,[eax]
	pmovmskb edx,xmm2
	pxor	xmm3,xmm3
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm3,[eax]
	pmovmskb edx,xmm3
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm0,[eax]
	pmovmskb edx,xmm0
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm1,[eax]
	pmovmskb edx,xmm1
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm2,[eax]
	pmovmskb edx,xmm2
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm3,[eax]
	pmovmskb edx,xmm3
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm0,[eax]
	pmovmskb edx,xmm0
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm1,[eax]
	pmovmskb edx,xmm1
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm2,[eax]
	pmovmskb edx,xmm2
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm3,[eax]
	pmovmskb edx,xmm3
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm0,[eax]
	pmovmskb edx,xmm0
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm1,[eax]
	pmovmskb edx,xmm1
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm2,[eax]
	pmovmskb edx,xmm2
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm3,[eax]
	pmovmskb edx,xmm3
	lea	eax,[eax+16]
	test	edx,edx
	jnz	exit

	and	eax,-40h

	align 4
aligned_64_loop:
	movaps	xmm0,[eax]
	movaps	xmm1,[eax+16]
	movaps	xmm2,[eax+32]
	movaps	xmm6,[eax+48]
	pminub	xmm0,xmm1
	pminub	xmm2,xmm6
	pminub	xmm2,xmm0
	pcmpeqb xmm2,xmm3
	pmovmskb edx,xmm2
	lea	eax,[eax+64]
	test	edx,edx
	jz	aligned_64_loop

	pcmpeqb xmm3,[eax-64]
	pmovmskb edx,xmm3
	lea	ecx,[ecx+48]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm3,xmm1
	pmovmskb edx,xmm3
	lea	ecx,[ecx-16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm3,[eax-32]
	pmovmskb edx,xmm3
	lea	ecx,[ecx-16]
	test	edx,edx
	jnz	exit

	pcmpeqb xmm3,xmm6
	pmovmskb edx,xmm3
	lea	ecx,[ecx-16]
exit:
	sub	eax,ecx
	test	dl,dl
	jz	exit_high

	mov	cl,dl
	and	cl,15
	jz	exit_8
	test	dl,1
	jnz	exit_tail0
	test	dl,2
	jnz	exit_tail1
	test	dl,4
	jnz	exit_tail2
	add	eax,3
	ret

	align 4
exit_8:
	test	dl,10h
	jnz	exit_tail4
	test	dl,20h
	jnz	exit_tail5
	test	dl,40h
	jnz	exit_tail6
	add	eax,7
	ret

	align 4
exit_high:
	mov	ch,dh
	and	ch,15
	jz	exit_high_8
	test	dh,1
	jnz	exit_tail8
	test	dh,2
	jnz	exit_tail9
	test	dh,4
	jnz	exit_tail10
	add	eax,11
	ret

	align 4
exit_high_8:
	test	dh,10h
	jnz	exit_tail12
	test	dh,20h
	jnz	exit_tail13
	test	dh,40h
	jnz	exit_tail14
	add	eax,15
exit_tail0:
	ret

	align 4
exit_tail1:
	add	eax,1
	ret

	align 4
exit_tail2:
	add	eax,2
	ret

	align 4
exit_tail3:
	add	eax,3
	ret

	align 4
exit_tail4:
	add	eax,4
	ret

	align 4
exit_tail5:
	add	eax,5
	ret

	align 4
exit_tail6:
	add	eax,6
	ret

	align 4
exit_tail7:
	add	eax,7
	ret

	align 4
exit_tail8:
	add	eax,8
	ret

	align 4
exit_tail9:
	add	eax,9
	ret

	align 4
exit_tail10:
	add	eax,10
	ret

	align 4
exit_tail11:
	add	eax,11
	ret

	align 4
exit_tail12:
	add	eax,12
	ret

	align 4
exit_tail13:
	add	eax,13
	ret

	align 4
exit_tail14:
	add	eax,14
	ret

	align 4
exit_tail15:
	add	eax,15
	ret

strlen	endp

	end
