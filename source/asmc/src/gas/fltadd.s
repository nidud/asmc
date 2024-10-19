
.intel_syntax noprefix

.global _fltadd
.global _fltsub


.SECTION .text
	.ALIGN	16

$_001:	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	r11, rcx
	mov	rbx, qword ptr [rdx]
	mov	rdi, qword ptr [rdx+0x8]
	mov	si, word ptr [rdx+0x10]
	shl	esi, 16
	mov	rax, qword ptr [rcx]
	mov	rdx, qword ptr [rcx+0x8]
	mov	si, word ptr [rcx+0x10]
	add	si, 1
	jc	$_024
	jo	$_024
	add	esi, 65535
	jc	$_027
	jo	$_027
	sub	esi, 65536
	xor	esi, r8d
	mov	rcx, rax
	or	rcx, rdx
	je	$_018
$_002:	mov	rcx, rbx
	or	rcx, rdi
	je	$_020
$_003:	mov	ecx, esi
	rol	esi, 16
	sar	esi, 16
	sar	ecx, 16
	and	esi, 0x80007FFF
	and	ecx, 0x80007FFF
	mov	r9d, ecx
	rol	esi, 16
	rol	ecx, 16
	add	cx, si
	rol	esi, 16
	rol	ecx, 16
	sub	cx, si
	jz	$_005
	jnc	$_004
	mov	r9d, esi
	neg	cx
	xchg	rax, rbx
	xchg	rdi, rdx
$_004:
	cmp	cx, 128
	jbe	$_005
	mov	esi, r9d
	shl	esi, 1
	rcr	si, 1
	mov	rax, rbx
	mov	rdx, rdi
	jmp	$_017

$_005:	mov	esi, r9d
	mov	ch, 0
	test	ecx, ecx
	jns	$_006
	mov	ch, -1
	neg	rdi
	neg	rbx
	sbb	rdi, 0
	xor	esi, 0x80000000
$_006:	mov	r8d, 0
	test	cl, cl
	jz	$_010
	cmp	cl, 64
	jc	$_009
	test	rax, rax
	jz	$_007
	inc	r8d
$_007:	cmp	cl, -128
	jnz	$_008
	shr	rdx, 32
	or	r8d, edx
	xor	edx, edx
$_008:	mov	rax, rdx
	xor	edx, edx
$_009:	xor	r9d, r9d
	mov	r10d, eax
	shrd	r9d, r10d, cl
	or	r8d, r9d
	shrd	rax, rdx, cl
	shr	rdx, cl
$_010:	add	rax, rbx
	adc	rdx, rdi
	adc	ch, 0
	jns	$_012
	cmp	cl, -128
	jnz	$_011
	test	r8d, 0x7FFFFFFF
	jz	$_011
	add	rax, 1
	adc	rdx, 0
$_011:	neg	rdx
	neg	rax
	sbb	rdx, 0
	xor	ch, ch
	xor	esi, 0x80000000
$_012:	mov	r9d, ecx
	and	r9d, 0xFF00
	or	r9, rax
	or	r9, rdx
	jnz	$_013
	xor	esi, esi
$_013:	test	si, si
	jz	$_017
	test	ch, ch
	mov	ecx, r8d
	jnz	$_015
	rol	ecx, 1
	rol	ecx, 1
$_014:	dec	si
	jz	$_016
	adc	rax, rax
	adc	rdx, rdx
	jnc	$_014
$_015:	inc	si
	cmp	si, 32767
	je	$_022
	stc
	rcr	rdx, 1
	rcr	rax, 1
	add	ecx, ecx
	jnc	$_016
	adc	rax, 0
	adc	rdx, 0
	jnc	$_016
	rcr	rdx, 1
	rcr	rax, 1
	inc	si
	cmp	si, 32767
	jz	$_022
$_016:	add	esi, esi
	rcr	si, 1
$_017:	mov	qword ptr [r11], rax
	mov	qword ptr [r11+0x8], rdx
	mov	word ptr [r11+0x10], si
	mov	rax, r11
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_018:	shl	si, 1
	jnz	$_019
	shr	esi, 16
	mov	rax, rbx
	mov	rdx, rdi
	shl	esi, 1
	mov	rcx, rax
	or	rcx, rdx
	jz	$_017
	shr	esi, 1
	jmp	$_017

$_019:	rcr	si, 1
	jmp	$_002

$_020:	test	esi, 0x7FFF0000
	jz	$_017
	jmp	$_003

$_021:	mov	esi, 65535
	movabs	rdx, 0x4000000000000000
	xor	eax, eax
	jmp	$_017

$_022:	mov	esi, 32767
	xor	eax, eax
	xor	edx, edx
	jmp	$_017

$_023:	mov	rax, rbx
	mov	rdx, rdi
	shr	esi, 16
	jmp	$_017

$_024:	dec	si
	add	esi, 65536
	jc	$_025
	jo	$_025
	jns	$_017
	mov	rcx, rax
	or	rcx, rdx
	jne	$_017
	xor	esi, 0x8000
	jmp	$_017

$_025:	sub	esi, 65536
	mov	rcx, rax
	or	rcx, rdx
	or	rcx, rbx
	or	rcx, rdi
	jnz	$_026
	or	esi, 0xFFFFFFFF
	jmp	$_021

$_026:	cmp	rdx, rdi
	jc	$_023
	ja	$_017
	cmp	rax, rbx
	jbe	$_023
	jmp	$_017

$_027:
	sub	esi, 65536
	mov	rcx, rbx
	or	rcx, rdi
	jnz	$_023
	mov	ecx, esi
	shl	ecx, 16
	xor	esi, ecx
	and	esi, 0x80000000
	jmp	$_023

_fltadd:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	xor	r8d, r8d
	call	$_001
	leave
	ret

_fltsub:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	r8d, 2147483648
	call	$_001
	leave
	ret

.att_syntax prefix
