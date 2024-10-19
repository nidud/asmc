
.intel_syntax noprefix

.global __div64_
.global __rem64_
.global _atoow
.global _atoqw
.global atofloat
.global quad_resize

.extern qerrno
.extern __cvta_q
.extern __cvtld_q
.extern __cvtsd_q
.extern __cvtss_q
.extern __cvth_q
.extern __cvtq_ld
.extern __cvtq_sd
.extern __cvtq_ss
.extern __cvtq_h
.extern tstrlen
.extern tmemset
.extern asmerr
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

$_001:	mov	rcx, rdx
	xor	edx, edx
	test	rcx, rcx
	jz	$_002
	div	rcx
	jmp	$_003

$_002:	xor	eax, eax
$_003:	ret

__div64_:
	test	rax, rax
	js	$_004
	test	rdx, rdx
	js	$_004
	call	$_001
	jmp	$_006

$_004:	neg	rax
	test	rdx, rdx
	jns	$_005
	neg	rdx
	call	$_001
	neg	rdx
	jmp	$_006

$_005:	call	$_001
	neg	rdx
	neg	rax
$_006:	ret

__rem64_:
	call	__div64_
	mov	rax, rdx
	ret

_atoow:
	mov	r10, rcx
	mov	r11, rdx
	xor	edx, edx
	mov	qword ptr [rcx], rdx
	mov	qword ptr [rcx+0x8], rdx
	xor	ecx, ecx
	movzx	eax, word ptr [r11]
	or	eax, 0x2000
	cmp	eax, 30768
	jnz	$_007
	add	r11, 2
	sub	r9d, 2
$_007:	cmp	r8d, 16
	jnz	$_009
$_008:	movzx	eax, byte ptr [r11]
	inc	r11
	and	eax, 0xFFFFFFCF
	bt	eax, 6
	sbb	r8d, r8d
	and	r8d, 0x37
	sub	eax, r8d
	shld	rdx, rcx, 4
	shl	rcx, 4
	add	rcx, rax
	dec	r9d
	jnz	$_008
	jmp	$_013

$_009:	cmp	r8d, 10
	jnz	$_011
	mov	cl, byte ptr [r11]
	inc	r11
	sub	cl, 48
$_010:	dec	r9d
	jz	$_013
	mov	r8, rdx
	mov	rax, rcx
	shld	rdx, rcx, 3
	shl	rcx, 3
	add	rcx, rax
	adc	rdx, r8
	add	rcx, rax
	adc	rdx, r8
	movzx	eax, byte ptr [r11]
	inc	r11
	sub	al, 48
	add	rcx, rax
	adc	rdx, 0
	jmp	$_010

$_011:	movzx	eax, byte ptr [r11]
	and	eax, 0xFFFFFFCF
	bt	eax, 6
	sbb	ecx, ecx
	and	ecx, 0x37
	sub	eax, ecx
	mov	ecx, 8
$_012:	movzx	edx, word ptr [r10]
	imul	edx, r8d
	add	eax, edx
	mov	word ptr [r10], ax
	add	r10, 2
	shr	eax, 16
	dec	ecx
	jnz	$_012
	sub	r10, 16
	inc	r11
	dec	r9d
	jnz	$_011
	mov	rcx, qword ptr [r10]
	mov	rdx, qword ptr [r10+0x8]
$_013:	mov	rax, r10
	mov	qword ptr [rax], rcx
	mov	qword ptr [rax+0x8], rdx
	ret

_atoqw:
	push	rbx
	push	rbp
	mov	rbp, rsp
	xor	edx, edx
	xor	eax, eax
$_014:	mov	dl, byte ptr [rcx]
	inc	rcx
	cmp	dl, 32
	jz	$_014
	mov	bl, dl
	cmp	dl, 43
	jz	$_015
	cmp	dl, 45
	jnz	$_016
$_015:	mov	dl, byte ptr [rcx]
	inc	rcx
$_016:	sub	dl, 48
	jc	$_017
	cmp	dl, 9
	ja	$_017
	imul	eax, eax, 10
	add	eax, edx
	mov	dl, byte ptr [rcx]
	inc	rcx
	jmp	$_016

$_017:
	cmp	bl, 45
	jnz	$_018
	neg	eax
$_018:	leave
	pop	rbx
	ret

atofloat:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	dword ptr [qerrno+rip], 0
	cmp	byte ptr [rbp+0x30], 0
	je	$_021
	mov	rcx, qword ptr [rbp+0x18]
	call	tstrlen@PLT
	lea	eax, [rax-0x1]
	mov	dword ptr [rbp+0x28], eax
	jmp	$_019
$C0003:
	jmp	$_020
$C0009:
	mov	rcx, qword ptr [rbp+0x18]
	cmp	byte ptr [rcx], 48
	jnz	$C000F
	inc	qword ptr [rbp+0x18]
	dec	dword ptr [rbp+0x28]
	jmp	$_020

$C000F: mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, 2104
	call	asmerr@PLT
	jmp	$_020

$_019:	cmp	eax, 4
	jl	$C000F
	cmp	eax, 33
	jg	$C000F
	push	rax
	lea	r11, [$C000F+rip]
	movzx	eax, byte ptr [r11+rax-(4)+(IT$C0010-$C000F)]
	movzx	eax, byte ptr [r11+rax+($C0010-$C000F)]
	sub	r11, rax
	pop	rax
	jmp	r11
$C0010:
	.byte $C000F-$C0003
	.byte $C000F-$C0009
	.byte 0
IT$C0010:
	.byte 0
	.byte 1
	.byte 2
	.byte 2
	.byte 0
	.byte 1
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 0
	.byte 1
	.byte 2
	.byte 2
	.byte 0
	.byte 1
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 0
	.byte 1
$C0008:
$_020:	mov	r9d, dword ptr [rbp+0x28]
	mov	r8d, 16
	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	_atoow
	mov	eax, dword ptr [rbp+0x20]
	mov	rcx, qword ptr [rbp+0x10]
	mov	rdx, rcx
	add	rcx, rax
	add	rdx, 16
$C0011:
	cmp	rcx, rdx
	jnc	Unnamed_1_26F
	cmp	byte ptr [rcx], 0
	jz	Unnamed_1_26A
	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, 2104
	call	asmerr@PLT
	jmp	Unnamed_1_26F

Unnamed_1_26A:
	inc	rcx
	jmp	$C0011

Unnamed_1_26F:
	mov	eax, dword ptr [rbp+0x28]
	shr	eax, 1
	cmp	eax, dword ptr [rbp+0x20]
	je	Unnamed_1_30F
	jmp	Unnamed_1_2E1
$C0017:
	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvth_q@PLT
	jmp	Unnamed_1_2FC
$C0019:
	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvtss_q@PLT
	jmp	Unnamed_1_2FC
$C001A:
	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvtsd_q@PLT
	jmp	Unnamed_1_2FC
$C001B:
	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvtld_q@PLT
	jmp	Unnamed_1_2FC
$C001C:
	jmp	Unnamed_1_2FC
$C001D:
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	Unnamed_1_2D0
	mov	ecx, 7004
	call	asmerr@PLT
Unnamed_1_2D0:
	mov	r8d, dword ptr [rbp+0x20]
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x10]
	call	tmemset@PLT
	jmp	Unnamed_1_2FC

Unnamed_1_2E1:
	cmp	eax, 2
	jz	$C0017
	cmp	eax, 4
	jz	$C0019
	cmp	eax, 8
	jz	$C001A
	cmp	eax, 10
	jz	$C001B
	cmp	eax, 16
	jz	$C001C
	jmp	$C001D

Unnamed_1_2FC:
	cmp	dword ptr [qerrno+rip], 0
	jz	Unnamed_1_30F
	mov	ecx, 2071
	call	asmerr@PLT
Unnamed_1_30F:
	jmp	$_035

$_021:	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvta_q@PLT
	cmp	dword ptr [qerrno+rip], 0
	jz	$_022
	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, 2104
	call	asmerr@PLT
$_022:	cmp	dword ptr [rbp+0x28], 0
	jz	$_023
	mov	rcx, qword ptr [rbp+0x10]
	or	byte ptr [rcx+0xF], 0xFFFFFF80
$_023:	mov	eax, dword ptr [rbp+0x20]
	jmp	$_034

$_024:	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvtq_h@PLT
	cmp	dword ptr [qerrno+rip], 0
	jz	$_025
	mov	ecx, 2071
	call	asmerr@PLT
$_025:	jmp	$_035

$_026:	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvtq_ss@PLT
	cmp	dword ptr [qerrno+rip], 0
	jz	$_027
	mov	ecx, 2071
	call	asmerr@PLT
$_027:	jmp	$_035

$_028:	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvtq_sd@PLT
	cmp	dword ptr [qerrno+rip], 0
	jz	$_029
	mov	ecx, 2071
	call	asmerr@PLT
$_029:	jmp	$_035

$_030:	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x10]
	call	__cvtq_ld@PLT
$_031:	jmp	$_035

$_032:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_033
	mov	ecx, 7004
	call	asmerr@PLT
$_033:	mov	r8d, dword ptr [rbp+0x20]
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x10]
	call	tmemset@PLT
	jmp	$_035

$_034:	cmp	al, 2
	je	$_024
	cmp	al, 4
	je	$_026
	cmp	al, 8
	jz	$_028
	cmp	al, 10
	jz	$_030
	cmp	al, 16
	jz	$_031
	jmp	$_032

$_035:
	leave
	ret

quad_resize:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	dword ptr [qerrno+rip], 0
	mov	rbx, qword ptr [rbp+0x20]
	movzx	esi, word ptr [rbx+0xE]
	and	esi, 0x7FFF
	mov	eax, dword ptr [rbp+0x28]
	jmp	$_046

$_036:	mov	rdx, rbx
	mov	rcx, rbx
	call	__cvtq_ld@PLT
	jmp	$_047

$_037:	test	byte ptr [rbx+0xF], 0xFFFFFF80
	jz	$_038
	or	byte ptr [rbx+0x43], 0x20
	and	byte ptr [rbx+0xF], 0x7F
$_038:	mov	rdx, rbx
	mov	rcx, rbx
	call	__cvtq_sd@PLT
	test	byte ptr [rbx+0x43], 0x20
	jz	$_039
	or	byte ptr [rbx+0x7], 0xFFFFFF80
$_039:	mov	byte ptr [rbx+0x40], 39
	jmp	$_047

$_040:	test	byte ptr [rbx+0xF], 0xFFFFFF80
	jz	$_041
	or	byte ptr [rbx+0x43], 0x20
	and	byte ptr [rbx+0xF], 0x7F
$_041:	mov	rdx, rbx
	mov	rcx, rbx
	call	__cvtq_ss@PLT
	test	byte ptr [rbx+0x43], 0x20
	jz	$_042
	or	byte ptr [rbx+0x3], 0xFFFFFF80
$_042:	mov	byte ptr [rbx+0x40], 35
	jmp	$_047

$_043:	test	byte ptr [rbx+0xF], 0xFFFFFF80
	jz	$_044
	or	byte ptr [rbx+0x43], 0x20
	and	byte ptr [rbx+0xF], 0x7F
$_044:	mov	rdx, rbx
	mov	rcx, rbx
	call	__cvtq_h@PLT
	test	byte ptr [rbx+0x43], 0x20
	jz	$_045
	or	byte ptr [rbx+0x1], 0xFFFFFF80
$_045:	mov	byte ptr [rbx+0x40], 33
	jmp	$_047

$_046:	cmp	eax, 10
	je	$_036
	cmp	eax, 8
	je	$_037
	cmp	eax, 4
	jz	$_040
	cmp	eax, 2
	jz	$_043
$_047:	cmp	dword ptr [qerrno+rip], 0
	jz	$_048
	cmp	esi, 32767
	jz	$_048
	mov	ecx, 2071
	call	asmerr@PLT
$_048:	leave
	pop	rbx
	pop	rsi
	ret

.att_syntax prefix
