
.intel_syntax noprefix

.global _fltsetflags


.SECTION .text
	.ALIGN	16

_fltsetflags:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	mov	rsi, rdx
	mov	ecx, r8d
	xor	eax, eax
	mov	qword ptr [rdi], rax
	mov	qword ptr [rdi+0x8], rax
	mov	word ptr [rdi+0x10], ax
	mov	dword ptr [rdi+0x1C], eax
	or	ecx, 0x08
$_001:	lodsb
	test	al, al
	je	$_018
	cmp	al, 32
	jz	$_001
	cmp	al, 9
	jc	$_002
	cmp	al, 13
	jbe	$_001
$_002:	dec	rsi
	and	ecx, 0xFFFFFFF7
	cmp	al, 43
	jnz	$_003
	inc	rsi
	or	ecx, 0x01
$_003:	cmp	al, 45
	jnz	$_004
	inc	rsi
	or	ecx, 0x03
$_004:	lodsb
	test	al, al
	je	$_018
	or	al, 0x20
	cmp	al, 110
	jnz	$_013
	mov	ax, word ptr [rsi]
	or	ax, 0x2020
	cmp	ax, 28257
	jnz	$_011
	add	rsi, 2
	or	ecx, 0x20
	mov	word ptr [rdi+0x10], -1
	movzx	eax, byte ptr [rsi]
	cmp	al, 40
	jnz	$_010
	lea	rdx, [rsi+0x1]
	mov	al, byte ptr [rdx]
	jmp	$_006

$_005:	inc	rdx
	mov	al, byte ptr [rdx]
	jmp	$_006

$_006:	cmp	al, 95
	jz	$_005
	cmp	al, 48
	jc	$_007
	cmp	al, 57
	jbe	$_005
$_007:	cmp	al, 97
	jc	$_008
	cmp	al, 122
	jbe	$_005
$_008:	cmp	al, 65
	jc	$_009
	cmp	al, 90
	jbe	$_005
$_009:	cmp	al, 41
	jnz	$_010
	lea	rsi, [rdx+0x1]
$_010:	jmp	$_012

$_011:	dec	rsi
	or	ecx, 0x80
$_012:	jmp	$_018

$_013:	cmp	al, 105
	jnz	$_016
	mov	ax, word ptr [rsi]
	or	ax, 0x2020
	cmp	ax, 26222
	jnz	$_014
	add	rsi, 2
	or	ecx, 0x40
	jmp	$_015

$_014:	dec	rsi
	or	ecx, 0x80
$_015:	jmp	$_018

$_016:	cmp	al, 48
	jnz	$_017
	mov	al, byte ptr [rsi]
	or	al, 0x20
	cmp	al, 120
	jnz	$_017
	or	ecx, 0x10
	add	rsi, 2
$_017:	dec	rsi
$_018:	mov	dword ptr [rdi+0x18], ecx
	mov	qword ptr [rdi+0x20], rsi
	mov	eax, ecx
	leave
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
