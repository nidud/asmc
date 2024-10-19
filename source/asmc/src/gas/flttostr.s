
.intel_syntax noprefix

.global _flttostr

.extern _fltpowtable
.extern _i64toflt
.extern _flttoi64
.extern _fltmul
.extern _fltsub
.extern _fltscale
.extern _fltunpack


.SECTION .text
	.ALIGN	16

_flttostr:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 664
	mov	rbx, rdx
	mov	rcx, r8
	mov	eax, dword ptr [rbx+0x2C]
	add	rax, rcx
	dec	rax
	mov	qword ptr [rbp-0x270], rax
	mov	eax, 20
	test	byte ptr [rbp+0x42], 0x10
	jz	$_001
	mov	eax, 23
	jmp	$_002

$_001:	test	byte ptr [rbp+0x42], 0x20
	jz	$_002
	mov	eax, 33
$_002:	mov	dword ptr [rbp-0x18], eax
	xor	eax, eax
	mov	dword ptr [rbx+0x1C], eax
	mov	dword ptr [rbx+0x20], eax
	mov	dword ptr [rbx+0x24], eax
	mov	dword ptr [rbx+0x28], eax
	mov	dword ptr [rbx+0x18], eax
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x40]
	call	_fltunpack@PLT
	mov	ax, word ptr [rbp-0x30]
	bt	eax, 15
	sbb	ecx, ecx
	mov	dword ptr [rbx+0x14], ecx
	and	eax, 0x7FFF
	mov	word ptr [rbp-0x30], ax
	movzx	ecx, ax
	xor	eax, eax
	mov	dword ptr [rbp-0x28], eax
	cmp	ecx, 32767
	jnz	$_006
	or	rax, qword ptr [rbp-0x40]
	or	rax, qword ptr [rbp-0x38]
	jnz	$_003
	mov	eax, 6712937
	or	byte ptr [rbx+0x8], 0x40
	jmp	$_004

$_003:	mov	eax, 7233902
	or	byte ptr [rbx+0x8], 0x20
$_004:	test	byte ptr [rbp+0x42], 0x01
	jz	$_005
	and	eax, 0xFFDFDFDF
$_005:	mov	rcx, qword ptr [rbp+0x38]
	mov	dword ptr [rcx], eax
	mov	dword ptr [rbx+0x1C], 3
	mov	eax, 64
	jmp	$_097

$_006:	test	ecx, ecx
	jnz	$_007
	mov	dword ptr [rbx+0x14], eax
	mov	dword ptr [rbp-0x10], eax
	mov	dword ptr [rbp-0x28], 8
	jmp	$_013

$_007:	mov	esi, ecx
	sub	ecx, 16382
	mov	eax, 30103
	imul	ecx
	mov	ecx, 100000
	idiv	ecx
	sub	eax, 8
	mov	dword ptr [rbp-0x10], eax
	test	eax, eax
	je	$_013
	jns	$_008
	neg	eax
	add	eax, 7
	and	eax, 0xFFFFFFF8
	neg	eax
	mov	dword ptr [rbp-0x10], eax
	neg	eax
	mov	dword ptr [rbp-0x24], eax
	lea	rcx, [rbp-0x40]
	call	_fltscale@PLT
	jmp	$_013

$_008:	mov	eax, dword ptr [rbp-0x38]
	mov	edx, dword ptr [rbp-0x34]
	cmp	esi, 16436
	jc	$_009
	cmp	esi, 16436
	jnz	$_010
	cmp	edx, -1910781505
	jc	$_009
	cmp	edx, -1910781505
	jnz	$_010
	cmp	eax, 67108864
	jnc	$_010
$_009:	mov	dword ptr [rbp-0x10], 0
	jmp	$_013

$_010:	cmp	esi, 16489
	jc	$_011
	cmp	esi, 16489
	jnz	$_012
	cmp	edx, -1647989336
	jc	$_011
	cmp	edx, -1647989336
	jnz	$_012
	cmp	eax, 728806813
	jnc	$_012
$_011:	mov	dword ptr [rbp-0x10], 16
$_012:	mov	eax, dword ptr [rbp-0x10]
	and	eax, 0xFFFFFFF8
	mov	dword ptr [rbp-0x10], eax
	neg	eax
	mov	dword ptr [rbp-0x24], eax
	lea	rcx, [rbp-0x40]
	call	_fltscale@PLT
$_013:	mov	eax, dword ptr [rbx]
	test	byte ptr [rbx+0x9], 0x20
	jz	$_015
	add	eax, dword ptr [rbp-0x10]
	add	eax, 18
	cmp	dword ptr [rbx+0x4], 0
	jle	$_014
	add	eax, dword ptr [rbx+0x4]
$_014:	jmp	$_016

$_015:	add	eax, 24
$_016:	cmp	eax, 495
	jbe	$_017
	mov	eax, 495
$_017:	mov	dword ptr [rbp-0x8], eax
	mov	ecx, dword ptr [rbp-0x18]
	add	ecx, 8
	mov	dword ptr [rbp-0x14], ecx
	xor	eax, eax
	mov	qword ptr [rbp-0x278], rax
	lea	rdi, [rbp-0x268]
	mov	word ptr [rdi], 48
	inc	rdi
	mov	dword ptr [rbp-0x4], 0
	jmp	$_024

$_018:	sub	dword ptr [rbp-0x8], 16
	cmp	qword ptr [rbp-0x278], 0
	jnz	$_019
	lea	rcx, [rbp-0x40]
	call	_flttoi64@PLT
	mov	qword ptr [rbp-0x278], rax
	cmp	dword ptr [rbp-0x8], 0
	jle	$_019
	mov	rdx, qword ptr [rbp-0x278]
	lea	rcx, [rbp-0x68]
	call	_i64toflt@PLT
	lea	rdx, [rbp-0x68]
	lea	rcx, [rbp-0x40]
	call	_fltsub@PLT
	lea	rdx, [_fltpowtable+0x60+rip]
	lea	rcx, [rbp-0x40]
	call	_fltmul@PLT
$_019:	mov	ecx, 16
	mov	rax, qword ptr [rbp-0x278]
	mov	qword ptr [rbp-0x278], 0
	test	rax, rax
	jz	$_022
	mov	r8d, 10
$_020:	test	ecx, ecx
	jz	$_021
	xor	edx, edx
	div	r8
	add	dl, 48
	mov	byte ptr [rdi+rcx-0x1], dl
	dec	ecx
	jmp	$_020

$_021:	add	rdi, 16
	jmp	$_023

$_022:	mov	al, 48
	rep stosb
$_023:	add	dword ptr [rbp-0x4], 16
$_024:	cmp	dword ptr [rbp-0x8], 0
	jg	$_018
	mov	eax, dword ptr [rbp-0x4]
	mov	edx, 510
	lea	rsi, [rbp-0x267]
	mov	ecx, dword ptr [rbp-0x10]
	add	ecx, 15
$_025:	test	edx, edx
	jz	$_026
	cmp	byte ptr [rsi], 48
	jnz	$_026
	dec	eax
	dec	ecx
	dec	edx
	inc	rsi
	jmp	$_025

$_026:	mov	dword ptr [rbp-0x8], eax
	mov	rbx, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbx]
	test	byte ptr [rbx+0x9], 0x20
	jz	$_027
	add	ecx, dword ptr [rbx+0x4]
	lea	edx, [rdx+rcx+0x1]
	jmp	$_030

$_027:	test	byte ptr [rbx+0x9], 0x10
	jz	$_030
	cmp	dword ptr [rbx+0x4], 0
	jle	$_028
	inc	edx
	jmp	$_029

$_028:	add	edx, dword ptr [rbx+0x4]
$_029:	inc	ecx
	sub	ecx, dword ptr [rbx+0x4]
$_030:	cmp	edx, 0
	jl	$_041
	cmp	edx, eax
	jle	$_031
	mov	edx, eax
$_031:	mov	eax, dword ptr [rbp-0x18]
	cmp	edx, eax
	jle	$_032
	mov	edx, eax
$_032:	mov	dword ptr [rbp-0x14], eax
	mov	eax, 48
	cmp	dword ptr [rbp-0x8], edx
	jle	$_033
	cmp	byte ptr [rsi+rdx], 53
	jge	$_034
$_033:	cmp	edx, dword ptr [rbp-0x18]
	jnz	$_035
	cmp	byte ptr [rsi+rdx-0x1], 57
	jnz	$_035
$_034:	mov	al, 57
$_035:	mov	edi, dword ptr [rbx+0x4]
	add	edi, dword ptr [rbx]
	cmp	al, 57
	jnz	$_039
	cmp	edx, edi
	jnz	$_039
	cmp	byte ptr [rsi+rdx], 57
	jz	$_039
	cmp	byte ptr [rsi+rdx-0x1], 57
	jnz	$_039
	jmp	$_037

$_036:	dec	edi
	cmp	byte ptr [rsi+rdi], 57
	jnz	$_038
$_037:	test	edi, edi
	jnz	$_036
$_038:	cmp	byte ptr [rsi+rdi], 57
	jnz	$_039
	mov	al, 48
$_039:	lea	rdi, [rsi+rdx-0x1]
	xchg	edx, ecx
	inc	ecx
	std
	repe scasb
	cld
	xchg	edx, ecx
	inc	rdi
	cmp	al, 57
	jnz	$_040
	inc	byte ptr [rdi]
$_040:	sub	rdi, rsi
	jns	$_041
	dec	rsi
	inc	edx
	inc	ecx
$_041:	cmp	edx, 0
	jle	$_042
	cmp	dword ptr [rbp-0x28], 8
	jnz	$_043
$_042:	mov	edx, 1
	xor	ecx, ecx
	mov	byte ptr [rbp-0x268], 48
	mov	dword ptr [rbx+0x14], ecx
	lea	rsi, [rbp-0x268]
$_043:	mov	dword ptr [rbp-0x4], 0
	mov	eax, dword ptr [rbx+0x8]
	test	eax, 0x2000
	jnz	$_045
	test	eax, 0x4000
	je	$_062
	cmp	ecx, -1
	jl	$_044
	cmp	ecx, dword ptr [rbx]
	jl	$_045
$_044:	test	eax, 0x8000
	je	$_062
$_045:	mov	rdi, qword ptr [rbp+0x38]
	inc	ecx
	test	eax, 0x4000
	jz	$_047
	cmp	edx, dword ptr [rbx]
	jge	$_046
	test	eax, 0x800
	jnz	$_046
	mov	dword ptr [rbx], edx
$_046:	sub	dword ptr [rbx], ecx
	cmp	dword ptr [rbx], 0
	jge	$_047
	mov	dword ptr [rbx], 0
$_047:	cmp	ecx, 0
	jg	$_052
	test	eax, 0x8000
	jnz	$_049
	mov	byte ptr [rdi], 48
	inc	dword ptr [rbp-0x4]
	cmp	dword ptr [rbx], 0
	jg	$_048
	test	eax, 0x800
	jz	$_049
$_048:	mov	byte ptr [rdi+0x1], 46
	inc	dword ptr [rbp-0x4]
$_049:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rbx+0x1C], eax
	mov	eax, ecx
	neg	eax
	cmp	dword ptr [rbx], eax
	jge	$_050
	mov	ecx, dword ptr [rbx]
	neg	ecx
$_050:	mov	eax, ecx
	neg	eax
	mov	dword ptr [rbx+0x18], eax
	mov	dword ptr [rbx+0x20], eax
	add	dword ptr [rbx], ecx
	cmp	dword ptr [rbx], edx
	jge	$_051
	mov	edx, dword ptr [rbx]
$_051:	mov	dword ptr [rbx+0x24], edx
	sub	edx, dword ptr [rbx]
	neg	edx
	mov	dword ptr [rbx+0x28], edx
	mov	ecx, dword ptr [rbx+0x1C]
	add	rdi, rcx
	mov	ecx, dword ptr [rbx+0x20]
	mov	eax, dword ptr [rbx+0x24]
	add	eax, dword ptr [rbx+0x28]
	add	eax, ecx
	lea	rax, [rdi+rax]
	cmp	rax, qword ptr [rbp-0x270]
	ja	$_098
	add	dword ptr [rbp-0x4], ecx
	mov	al, 48
	rep stosb
	mov	ecx, dword ptr [rbx+0x24]
	add	dword ptr [rbp-0x4], ecx
	rep movsb
	mov	ecx, dword ptr [rbx+0x28]
	add	dword ptr [rbp-0x4], ecx
	rep stosb
	jmp	$_061

$_052:	cmp	edx, ecx
	jge	$_055
	add	dword ptr [rbp-0x4], edx
	mov	dword ptr [rbx+0x1C], edx
	mov	eax, ecx
	sub	eax, edx
	mov	dword ptr [rbx+0x20], eax
	mov	dword ptr [rbx+0x18], ecx
	mov	ecx, edx
	rep movsb
	lea	rcx, [rdi+rax+0x2]
	cmp	rcx, qword ptr [rbp-0x270]
	ja	$_098
	mov	ecx, eax
	mov	eax, 48
	add	dword ptr [rbp-0x4], ecx
	rep stosb
	mov	ecx, dword ptr [rbx]
	test	byte ptr [rbx+0x9], 0xFFFFFF80
	jnz	$_054
	cmp	ecx, 0
	jg	$_053
	test	byte ptr [rbx+0x9], 0x08
	jz	$_054
$_053:	mov	byte ptr [rdi], 46
	inc	rdi
	inc	dword ptr [rbp-0x4]
	mov	dword ptr [rbx+0x24], 1
$_054:	lea	rdx, [rdi+rcx]
	cmp	rdx, qword ptr [rbp-0x270]
	ja	$_098
	mov	dword ptr [rbx+0x28], ecx
	add	dword ptr [rbp-0x4], ecx
	rep stosb
	jmp	$_061

$_055:	mov	dword ptr [rbx+0x18], ecx
	add	dword ptr [rbp-0x4], ecx
	sub	edx, ecx
	rep movsb
	mov	rdi, qword ptr [rbp+0x38]
	mov	ecx, dword ptr [rbx+0x18]
	test	byte ptr [rbx+0x9], 0xFFFFFF80
	jnz	$_058
	cmp	dword ptr [rbx], 0
	jg	$_056
	test	byte ptr [rbx+0x9], 0x08
	jz	$_057
$_056:	mov	eax, dword ptr [rbp-0x4]
	mov	byte ptr [rdi+rax], 46
	inc	dword ptr [rbp-0x4]
$_057:	jmp	$_059

$_058:	cmp	byte ptr [rdi], 48
	jnz	$_059
	mov	dword ptr [rbx+0x18], 0
$_059:	cmp	dword ptr [rbx], edx
	jge	$_060
	mov	edx, dword ptr [rbx]
$_060:	mov	eax, dword ptr [rbp-0x4]
	add	rdi, rax
	mov	ecx, edx
	rep movsb
	add	dword ptr [rbp-0x4], edx
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rbx+0x1C], eax
	mov	eax, edx
	mov	ecx, dword ptr [rbx]
	add	edx, ecx
	mov	dword ptr [rbx+0x20], edx
	sub	ecx, eax
	add	dword ptr [rbp-0x4], ecx
	lea	rdx, [rdi+rcx]
	cmp	rdx, qword ptr [rbp-0x270]
	ja	$_098
	mov	eax, 48
	rep stosb
$_061:	mov	edi, dword ptr [rbp-0x4]
	add	rdi, qword ptr [rbp+0x38]
	mov	byte ptr [rdi], 0
	jmp	$_097

$_062:	mov	eax, dword ptr [rbx]
	cmp	dword ptr [rbx+0x4], 0
	jg	$_063
	add	eax, dword ptr [rbx+0x4]
	jmp	$_064

$_063:	sub	eax, dword ptr [rbx+0x4]
	inc	eax
$_064:	mov	dword ptr [rbp-0x4], 0
	test	byte ptr [rbx+0x9], 0x40
	jz	$_067
	cmp	edx, eax
	jnc	$_065
	test	byte ptr [rbx+0x9], 0x08
	jnz	$_065
	mov	eax, edx
$_065:	dec	eax
	cmp	eax, 0
	jge	$_066
	xor	eax, eax
$_066:	cmp	ecx, -5
	jle	$_067
	cmp	ecx, 0
	jge	$_067
	neg	ecx
	add	eax, ecx
	add	edx, ecx
	sub	rsi, rcx
	xor	ecx, ecx
$_067:	mov	dword ptr [rbx], eax
	mov	dword ptr [rbp-0x10], ecx
	mov	dword ptr [rbp-0xC], edx
	mov	rdi, qword ptr [rbp+0x38]
	cmp	dword ptr [rbx+0x4], 0
	jg	$_069
	mov	byte ptr [rdi], 48
	inc	dword ptr [rbp-0x4]
	cmp	ecx, dword ptr [rbp-0x14]
	jl	$_068
	inc	dword ptr [rbp-0x10]
$_068:	jmp	$_071

$_069:	mov	eax, dword ptr [rbx+0x4]
	cmp	eax, edx
	jbe	$_070
	mov	eax, edx
$_070:	mov	edx, eax
	mov	ecx, dword ptr [rbp-0x4]
	add	rdi, rcx
	mov	ecx, eax
	mov	rax, rsi
	rep movsb
	mov	rsi, rax
	add	dword ptr [rbp-0x4], edx
	add	rsi, rdx
	sub	dword ptr [rbp-0xC], edx
	cmp	edx, dword ptr [rbx+0x4]
	jge	$_071
	mov	ecx, dword ptr [rbx+0x4]
	sub	ecx, edx
	add	dword ptr [rbp-0x4], ecx
	mov	edi, dword ptr [rbp-0x4]
	add	rdi, qword ptr [rbp+0x38]
	mov	al, 48
	rep stosb
$_071:	mov	edx, dword ptr [rbp-0x4]
	mov	rdi, qword ptr [rbp+0x38]
	mov	dword ptr [rbx+0x18], edx
	mov	eax, dword ptr [rbx]
	test	byte ptr [rbx+0x9], 0xFFFFFF80
	jnz	$_073
	cmp	eax, 0
	jg	$_072
	test	byte ptr [rbx+0x9], 0x08
	jz	$_073
$_072:	mov	byte ptr [rdi+rdx], 46
	inc	dword ptr [rbp-0x4]
$_073:	mov	ecx, dword ptr [rbx+0x4]
	cmp	ecx, 0
	jge	$_074
	neg	ecx
	add	rdi, rdx
	add	dword ptr [rbp-0x4], ecx
	mov	al, 48
	rep stosb
$_074:	mov	ecx, dword ptr [rbp-0xC]
	mov	eax, dword ptr [rbx]
	cmp	eax, 0
	jle	$_077
	cmp	eax, ecx
	jge	$_075
	mov	ecx, eax
	mov	dword ptr [rbp-0xC], eax
$_075:	test	ecx, ecx
	jz	$_076
	mov	edi, dword ptr [rbp-0x4]
	add	rdi, qword ptr [rbp+0x38]
	add	dword ptr [rbp-0x4], ecx
	rep movsb
$_076:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rbx+0x1C], eax
	mov	ecx, dword ptr [rbx]
	sub	ecx, dword ptr [rbp-0xC]
	mov	dword ptr [rbx+0x20], ecx
	mov	edi, dword ptr [rbp-0x4]
	add	rdi, qword ptr [rbp+0x38]
	add	dword ptr [rbp-0x4], ecx
	mov	eax, 48
	rep stosb
$_077:	mov	edi, dword ptr [rbp-0x10]
	mov	rsi, qword ptr [rbp+0x38]
	mov	ecx, dword ptr [rbp-0x4]
	test	byte ptr [rbx+0x9], 0x40
	jz	$_078
	test	edi, edi
	jnz	$_078
	mov	edx, ecx
	jmp	$_096

$_078:	mov	eax, dword ptr [rbx+0xC]
	test	al, al
	jz	$_079
	mov	byte ptr [rsi+rcx], al
	inc	dword ptr [rbp-0x4]
	inc	ecx
$_079:	cmp	edi, 0
	jl	$_080
	mov	byte ptr [rsi+rcx], 43
	jmp	$_081

$_080:	mov	byte ptr [rsi+rcx], 45
	neg	edi
$_081:	inc	dword ptr [rbp-0x4]
	mov	eax, edi
	mov	ecx, dword ptr [rbx+0x10]
	jmp	$_088

$_082:	mov	ecx, 3
	cmp	eax, 1000
	jl	$_083
	mov	ecx, 4
$_083:	jmp	$_089

$_084:	cmp	eax, 10
	jl	$_085
	mov	ecx, 2
$_085:	cmp	eax, 100
	jl	$_086
	mov	ecx, 3
$_086:	cmp	eax, 1000
	jl	$_087
	mov	ecx, 4
$_087:	jmp	$_089

$_088:	cmp	ecx, 0
	jz	$_082
	cmp	ecx, 1
	jz	$_084
	cmp	ecx, 2
	jz	$_085
	cmp	ecx, 3
	jz	$_086
$_089:	mov	dword ptr [rbx+0x10], ecx
	cmp	ecx, 4
	jc	$_091
	xor	edx, edx
	cmp	eax, 1000
	jc	$_090
	mov	ecx, 1000
	div	ecx
	mov	edx, eax
	imul	eax, eax, 1000
	sub	edi, eax
	mov	ecx, dword ptr [rbx+0x10]
$_090:	lea	eax, [rdx+0x30]
	mov	edx, dword ptr [rbp-0x4]
	mov	byte ptr [rsi+rdx], al
	inc	dword ptr [rbp-0x4]
$_091:	cmp	ecx, 3
	jc	$_093
	xor	edx, edx
	cmp	edi, 100
	jl	$_092
	mov	eax, edi
	mov	ecx, 100
	div	ecx
	mov	edx, eax
	imul	eax, eax, 100
	sub	edi, eax
	mov	ecx, dword ptr [rbx+0x10]
$_092:	lea	eax, [rdx+0x30]
	mov	edx, dword ptr [rbp-0x4]
	mov	byte ptr [rsi+rdx], al
	inc	dword ptr [rbp-0x4]
$_093:	cmp	ecx, 2
	jc	$_095
	xor	edx, edx
	cmp	edi, 10
	jl	$_094
	mov	eax, edi
	mov	ecx, 10
	div	ecx
	mov	edx, eax
	imul	eax, eax, 10
	sub	edi, eax
	mov	ecx, dword ptr [rbx+0x10]
$_094:	lea	eax, [rdx+0x30]
	mov	edx, dword ptr [rbp-0x4]
	mov	byte ptr [rsi+rdx], al
	inc	dword ptr [rbp-0x4]
$_095:	mov	edx, dword ptr [rbp-0x4]
	lea	eax, [rdi+0x30]
	mov	byte ptr [rsi+rdx], al
	inc	edx
$_096:	mov	eax, edx
	sub	eax, dword ptr [rbx+0x1C]
	mov	dword ptr [rbx+0x24], eax
	xor	eax, eax
	mov	byte ptr [rsi+rdx], al
$_097:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_098:
	mov	rdi, qword ptr [rbp+0x38]
	lea	rsi, [e_space+rip]
	mov	ecx, 18
	rep movsb
	jmp	$_097


.SECTION .data
	.ALIGN	16

e_space:
	.byte  0x23, 0x6E, 0x6F, 0x74, 0x20, 0x65, 0x6E, 0x6F
	.byte  0x75, 0x67, 0x68, 0x20, 0x73, 0x70, 0x61, 0x63
	.byte  0x65, 0x00


.att_syntax prefix
