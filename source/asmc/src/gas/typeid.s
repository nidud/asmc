
.intel_syntax noprefix

.global GetType
.global GetTypeId

.extern GetResWName
.extern SizeFromRegister
.extern EvalOperand
.extern tstricmp
.extern tstrcat
.extern tstrcpy
.extern tstrlen


.SECTION .text
	.ALIGN	16

GetType:
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	mov	rbx, rdx
	mov	rdx, r8
	test	rdx, rdx
	jz	$_002
	cmp	rdi, rdx
	jz	$_001
	mov	rcx, rdi
	call	tstrcpy@PLT
$_001:	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	jmp	$_003

$_002:	mov	byte ptr [rdi], 0
$_003:	mov	eax, dword ptr [rbx+0x3C]
	test	eax, eax
	jz	$_004
	cmp	eax, 3
	jnz	$_006
$_004:	lea	rdx, [DS0000+rip]
	test	eax, eax
	jnz	$_005
	lea	rdx, [DS0001+rip]
$_005:	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	eax, 1
	jmp	$_057

$_006:	cmp	eax, 2
	jne	$_026
	test	byte ptr [rbx+0x43], 0x01
	jne	$_026
	mov	rcx, qword ptr [rbx+0x18]
	mov	ecx, dword ptr [rcx+0x4]
	call	SizeFromRegister@PLT
	xor	ecx, ecx
	cmp	eax, 16
	jc	$_012
	jmp	$_010

$_007:	mov	ecx, 219
	jmp	$_011

$_008:	mov	ecx, 222
	jmp	$_011

$_009:	mov	ecx, 223
	jmp	$_011

$_010:	cmp	eax, 16
	jz	$_007
	cmp	eax, 32
	jz	$_008
	cmp	eax, 64
	jz	$_009
$_011:	jmp	$_025

$_012:	cmp	byte ptr [rbx+0x40], -64
	jz	$_019
	test	byte ptr [rbx+0x40], 0x40
	jz	$_019
	jmp	$_017

$_013:	mov	ecx, 206
	jmp	$_018

$_014:	mov	ecx, 208
	jmp	$_018

$_015:	mov	ecx, 211
	jmp	$_018

$_016:	mov	ecx, 215
	jmp	$_018

$_017:	cmp	eax, 1
	jz	$_013
	cmp	eax, 2
	jz	$_014
	cmp	eax, 4
	jz	$_015
	cmp	eax, 8
	jz	$_016
$_018:	jmp	$_025

$_019:	jmp	$_024

$_020:	mov	ecx, 205
	jmp	$_025

$_021:	mov	ecx, 207
	jmp	$_025

$_022:	mov	ecx, 210
	jmp	$_025

$_023:	mov	ecx, 214
	jmp	$_025

$_024:	cmp	eax, 1
	jz	$_020
	cmp	eax, 2
	jz	$_021
	cmp	eax, 4
	jz	$_022
	cmp	eax, 8
	jz	$_023
$_025:	mov	rdx, rdi
	call	GetResWName@PLT
	mov	eax, 1
	jmp	$_057

$_026:	cmp	dword ptr [rbp+0x40], 0
	jz	$_027
	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	add	rdi, 3
	jmp	$_028

$_027:	cmp	eax, 1
	jz	$_028
	cmp	eax, 2
	jz	$_028
	xor	eax, eax
	jmp	$_057

$_028:	mov	rdx, qword ptr [rbx+0x50]
	mov	rsi, qword ptr [rbx+0x60]
	cmp	qword ptr [rbx+0x58], 0
	jz	$_029
	mov	rdx, qword ptr [rbx+0x58]
$_029:	test	rdx, rdx
	jz	$_030
	cmp	byte ptr [rdx+0x18], 0
	jnz	$_031
$_030:	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	mov	eax, 1
	jmp	$_057

$_031:	cmp	byte ptr [rdx+0x18], 6
	jne	$_037
	mov	rcx, qword ptr [rbx+0x50]
	mov	eax, dword ptr [rbx+0x3C]
	test	rsi, rsi
	jz	$_033
	test	rcx, rcx
	jnz	$_033
	cmp	eax, 1
	jnz	$_032
	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	add	rdi, 3
$_032:	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	eax, 1
	jmp	$_057

$_033:	mov	rbx, rcx
	test	rbx, rbx
	jz	$_037
	cmp	byte ptr [rbx+0x19], -60
	jnz	$_034
	mov	rbx, qword ptr [rbx+0x20]
$_034:	cmp	qword ptr [rbx+0x40], 0
	jz	$_036
	cmp	byte ptr [rbx+0x19], -61
	jz	$_035
	cmp	byte ptr [rbx+0x3A], -60
	jnz	$_036
$_035:	mov	rbx, qword ptr [rbx+0x40]
$_036:	cmp	byte ptr [rdx+0x19], -63
	jnz	$_037
	cmp	word ptr [rbx+0x5A], 1
	jnz	$_037
	mov	rsi, qword ptr [rdx+0x8]
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdx, [DS0002+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, rsi
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	eax, 1
	jmp	$_057

$_037:	mov	rbx, rdx
	cmp	byte ptr [rbx+0x19], -60
	jnz	$_038
	cmp	qword ptr [rbx+0x20], 0
	jz	$_038
	mov	rbx, qword ptr [rbx+0x20]
$_038:	cmp	qword ptr [rbx+0x40], 0
	jz	$_041
	cmp	byte ptr [rbx+0x19], -61
	jz	$_039
	cmp	byte ptr [rbx+0x3A], -60
	jnz	$_041
$_039:	cmp	byte ptr [rbx+0x19], -61
	jnz	$_040
	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	add	rdi, 3
	cmp	byte ptr [rbx+0x39], 2
	jnz	$_040
	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	add	rdi, 3
$_040:	mov	rbx, qword ptr [rbx+0x40]
$_041:	cmp	byte ptr [rbx+0x18], 7
	jnz	$_042
	cmp	word ptr [rbx+0x5A], 1
	jnz	$_042
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	eax, 1
	jmp	$_057

$_042:	test	rsi, rsi
	jz	$_043
	cmp	byte ptr [rsi+0x18], 7
	jnz	$_043
	cmp	word ptr [rsi+0x5A], 1
	jnz	$_043
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	eax, 1
	jmp	$_057

$_043:	mov	al, byte ptr [rbx+0x18]
	cmp	al, 1
	jz	$_044
	cmp	al, 2
	jz	$_044
	cmp	al, 5
	jz	$_044
	cmp	al, 6
	jz	$_044
	cmp	al, 7
	jne	$_056
$_044:	mov	cl, byte ptr [rbx+0x19]
	jmp	$_053
$C003E: mov	eax, 205
	jmp	$_055
$C0040: mov	eax, 206
	jmp	$_055
$C0041: mov	eax, 207
	jmp	$_055
$C0042: mov	eax, 208
	jmp	$_055
$C0043: mov	eax, 209
	jmp	$_055
$C0044: mov	eax, 210
	jmp	$_055
$C0045: mov	eax, 211
	jmp	$_055
$C0046: mov	eax, 212
	jmp	$_055
$C0047: mov	eax, 213
	jmp	$_055
$C0048: mov	eax, 214
	jmp	$_055
$C0049: mov	eax, 215
	jmp	$_055
$C004A: mov	eax, 216
	jmp	$_055
$C004B: mov	eax, 217
	jmp	$_055
$C004C: mov	eax, 218
	jmp	$_055
$C004D: mov	eax, 219
	jmp	$_055
$_045:	mov	eax, 220
	jmp	$_055
$C004F: mov	eax, 221
	jmp	$_055
$C0050: mov	eax, 222
	jmp	$_055
$C0051: mov	eax, 223
	jmp	$_055
$_046:	mov	eax, 508
	jmp	$_055
$_047:	mov	eax, 226
	jmp	$_055
$_048:	mov	eax, 227
	jmp	$_055
$_049:	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	add	rdi, 3
	mov	cl, byte ptr [rbx+0x19]
	cmp	byte ptr [rbx+0x39], 1
	jnz	$_051
	cmp	cl, byte ptr [rbx+0x3A]
	jz	$_051
	cmp	byte ptr [rbx+0x3A], -64
	jz	$_050
	mov	cl, byte ptr [rbx+0x3A]
	jmp	$_053

$_050:	jmp	$_052

$_051:	cmp	byte ptr [rbx+0x39], 2
	jnz	$_052
	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
$_052:	mov	eax, 1
	jmp	$_057

	jmp	$_055

$C005A: mov	eax, 1
	jmp	$_057

	jmp	$_055

$_053:	cmp	cl, 0
	jl	$_054
	cmp	cl, 71
	jg	$_054
	push	rax
	movsx	rax, cl
	lea	r11, [$C005A+rip]
	movzx	eax, byte ptr [r11+rax+(IT$C005B-$C005A)]
	movzx	eax, word ptr [r11+rax*2+($C005B-$C005A)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C005B:
	.word $C005A-$C003E
	.word $C005A-$C0040
	.word $C005A-$C0041
	.word $C005A-$C0042
	.word $C005A-$C0043
	.word $C005A-$C0044
	.word $C005A-$C0045
	.word $C005A-$C0046
	.word $C005A-$C0047
	.word $C005A-$C0048
	.word $C005A-$C0049
	.word $C005A-$C004A
	.word $C005A-$C004B
	.word $C005A-$C004C
	.word $C005A-$C004D
	.word $C005A-$C004F
	.word $C005A-$C0050
	.word $C005A-$C0051
	.word 0
IT$C005B:
	.byte 0
	.byte 2
	.byte 18
	.byte 5
	.byte 18
	.byte 8
	.byte 18
	.byte 9
	.byte 18
	.byte 12
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 14
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 16
	.byte 18
	.byte 4
	.byte 18
	.byte 7
	.byte 18
	.byte 18
	.byte 18
	.byte 11
	.byte 18
	.byte 13
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 15
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 18
	.byte 17
	.byte 1
	.byte 3
	.byte 18
	.byte 6
	.byte 18
	.byte 18
	.byte 18
	.byte 10
	.ALIGN 2
$C005C:
$_054:	cmp	cl, 79
	je	$_045
	cmp	cl, -128
	je	$_046
	cmp	cl, -127
	je	$_047
	cmp	cl, -126
	je	$_048
	cmp	cl, -61
	je	$_049
	jmp	$C005A

$_055:	mov	rdx, rdi
	mov	ecx, eax
	call	GetResWName@PLT
	mov	eax, 1
	jmp	$_057

$_056:	xor	eax, eax
$_057:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

GetTypeId:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 424
	mov	rbx, rdx
	jmp	$_060

$_058:	cmp	byte ptr [rbx], 8
	jnz	$_059
	lea	rdx, [DS0003+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_059
	mov	rax, qword ptr [rbx+0x8]
	mov	byte ptr [rax], 63
	jmp	$_061

$_059:	add	rbx, 24
$_060:	cmp	byte ptr [rbx], 0
	jnz	$_058
$_061:	cmp	byte ptr [rbx], 0
	jnz	$_062
	cmp	byte ptr [rbx+0x18], 40
	jnz	$_062
	add	rbx, 24
	jmp	$_064

$_062:	cmp	byte ptr [rbx], 0
	jz	$_063
	add	rbx, 24
	jmp	$_064

$_063:	mov	rbx, qword ptr [rbp+0x30]
$_064:	cmp	byte ptr [rbx], 40
	jz	$_065
	xor	eax, eax
	jmp	$_079

$_065:	add	rbx, 24
	mov	byte ptr [rbp-0x170], 0
	cmp	byte ptr [rbx+0x18], 44
	jnz	$_066
	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [rbp-0x170]
	call	tstrcpy@PLT
	add	rbx, 48
$_066:	xor	esi, esi
	cmp	byte ptr [rbx], 7
	jnz	$_067
	cmp	dword ptr [rbx+0x4], 273
	jnz	$_067
	add	rbx, 24
	inc	esi
$_067:	mov	rax, rbx
	sub	rax, qword ptr [rbp+0x30]
	mov	ecx, 24
	xor	edx, edx
	div	ecx
	mov	ecx, eax
	mov	dword ptr [rbp-0x4], eax
	xor	eax, eax
	mov	edx, 1
$_068:	cmp	byte ptr [rbx], 0
	jz	$_074
	jmp	$_072

$_069:	inc	edx
	test	eax, eax
	jnz	$_070
	cmp	byte ptr [rbx-0x18], 8
	jnz	$_070
	mov	eax, ecx
$_070:	jmp	$_073

$_071:	dec	edx
	jnz	$_073
	jmp	$_074

$_072:	cmp	byte ptr [rbx], 40
	jz	$_069
	cmp	byte ptr [rbx], 41
	jz	$_071
$_073:	add	rbx, 24
	inc	ecx
	jmp	$_068

$_074:	mov	edi, ecx
	test	eax, eax
	jz	$_076
	mov	ecx, eax
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x70]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_075
	xor	eax, eax
	jmp	$_079

$_075:	xor	eax, eax
	cmp	byte ptr [rbp-0x30], -127
	jnz	$_076
	inc	eax
$_076:	test	eax, eax
	jnz	$_077
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x70]
	mov	r8d, edi
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_077
	xor	eax, eax
	jmp	$_079

$_077:	xor	ecx, ecx
	cmp	byte ptr [rbp-0x170], 0
	jz	$_078
	lea	rcx, [rbp-0x170]
$_078:	mov	r9d, esi
	mov	r8, rcx
	lea	rdx, [rbp-0x70]
	mov	rcx, qword ptr [rbp+0x28]
	call	GetType
$_079:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x66, 0x6C, 0x74, 0x00

DS0001:
	.byte  0x69, 0x6D, 0x6D, 0x00

DS0002:
	.byte  0x2E, 0x00

DS0003:
	.byte  0x74, 0x79, 0x70, 0x65, 0x69, 0x64, 0x00


.att_syntax prefix
