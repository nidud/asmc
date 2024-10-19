
.intel_syntax noprefix

.global SwitchDirective

.extern HllContinueIf
.extern ExpandHllExpression
.extern ExpandHllProc
.extern EvaluateHllExpression
.extern ExpandCStrings
.extern GetLabelStr
.extern GetResWName
.extern Tokenize
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern LstWrite
.extern GetCurrOffset
.extern EvalOperand
.extern SizeFromMemtype
.extern LclDup
.extern LclAlloc
.extern tstrcmp
.extern tstrcpy
.extern tstrchr
.extern tmemcpy
.extern tsprintf
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	rsi, rcx
	mov	rbx, rdx
	mov	rdi, r8
	mov	rcx, qword ptr [rbx+0x20]
	test	rcx, rcx
	jnz	$_002
	mov	edx, dword ptr [rbx+0x18]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	jmp	$_004

$_002:	mov	edx, 46
	call	tstrchr@PLT
	test	rax, rax
	jz	$_003
	cmp	byte ptr [rax+0x1], 46
	jnz	$_003
	mov	byte ptr [rax], 0
	lea	rdi, [rax+0x2]
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	ecx, eax
	lea	rax, [DS0002+rip]
	mov	qword ptr [rsp+0x40], rax
	mov	dword ptr [rsp+0x38], ecx
	mov	eax, dword ptr [rbx+0x18]
	mov	dword ptr [rsp+0x30], eax
	mov	qword ptr [rsp+0x28], rdi
	mov	rax, qword ptr [rsi+0x20]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, ecx
	mov	r8, qword ptr [rbx+0x20]
	mov	rdx, qword ptr [rsi+0x20]
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
	jmp	$_004

$_003:	mov	r9d, dword ptr [rbx+0x18]
	mov	r8, qword ptr [rbx+0x20]
	mov	rdx, qword ptr [rsi+0x20]
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
$_004:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_005:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, rdx
	lea	r8, [DS0002+rip]
	mov	rdx, rdi
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	mov	rbx, qword ptr [rsi+0x8]
	jmp	$_007

$_006:	mov	r8, rdi
	mov	rdx, rbx
	mov	rcx, rsi
	call	$_001
	mov	rbx, qword ptr [rbx+0x8]
$_007:	test	rbx, rbx
	jnz	$_006
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_008:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	add	rdx, qword ptr [rbp+0x20]
	xor	eax, eax
	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_011

$_009:	test	byte ptr [rcx+0x2D], 0x40
	jz	$_010
	cmp	rdx, qword ptr [rcx+0x10]
	jl	$_010
	add	eax, 1
$_010:	mov	rcx, qword ptr [rcx+0x8]
$_011:	test	rcx, rcx
	jnz	$_009
	leave
	ret

$_012:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rdx, qword ptr [rbp+0x20]
	xor	eax, eax
	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_015

$_013:	test	byte ptr [rcx+0x2D], 0x40
	jz	$_014
	cmp	rdx, qword ptr [rcx+0x10]
	jg	$_014
	add	eax, 1
$_014:	mov	rcx, qword ptr [rcx+0x8]
$_015:	test	rcx, rcx
	jnz	$_013
	leave
	ret

$_016:
	mov	qword ptr [rsp+0x20], r9
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, r8
	add	rbx, qword ptr [rbp+0x30]
	xor	eax, eax
	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_019

$_017:	test	byte ptr [rcx+0x2D], 0x40
	jz	$_018
	cmp	rbx, qword ptr [rcx+0x10]
	jge	$_018
	and	dword ptr [rcx+0x2C], 0xFFFFBFFF
	dec	dword ptr [rdx]
	inc	eax
$_018:	mov	rcx, qword ptr [rcx+0x8]
$_019:	test	rcx, rcx
	jnz	$_017
	mov	edx, dword ptr [rdx]
	leave
	pop	rbx
	ret

$_020:
	mov	qword ptr [rsp+0x20], r9
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, r8
	sub	rbx, qword ptr [rbp+0x30]
	xor	eax, eax
	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_023

$_021:	test	byte ptr [rcx+0x2D], 0x40
	jz	$_022
	cmp	rbx, qword ptr [rcx+0x10]
	jle	$_022
	and	dword ptr [rcx+0x2C], 0xFFFFBFFF
	dec	dword ptr [rdx]
	inc	eax
$_022:	mov	rcx, qword ptr [rcx+0x8]
$_023:	test	rcx, rcx
	jnz	$_021
	mov	edx, dword ptr [rdx]
	leave
	pop	rbx
	ret

$_024:
	mov	rax, qword ptr [rcx+0x8]
	jmp	$_027

$_025:	test	byte ptr [rax+0x2D], 0x40
	jz	$_026
	cmp	qword ptr [rax+0x10], rdx
	jnz	$_026
	jmp	$_028

$_026:	mov	rcx, rax
	mov	rax, qword ptr [rax+0x8]
$_027:	test	rax, rax
	jnz	$_025
$_028:	ret

$_029:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call	$_024
	test	rax, rax
	jz	$_030
	and	dword ptr [rax+0x2C], 0xFFFFBFFF
	mov	eax, 1
$_030:	leave
	ret

$_031:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	byte ptr [rbp-0x74], 1
	xor	edi, edi
	xor	ebx, ebx
	mov	rax, qword ptr [rdx+0x10]
	mov	qword ptr [rbp-0x80], rax
	mov	rsi, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rsi+0x2C]
	and	eax, 0xE00
	cmp	eax, 512
	jnz	$_032
	inc	byte ptr [rbp-0x74]
	jmp	$_034

$_032:	cmp	eax, 1024
	jnz	$_033
	mov	byte ptr [rbp-0x74], 4
	jmp	$_034

$_033:	cmp	eax, 2048
	jnz	$_034
	mov	byte ptr [rbp-0x74], 8
$_034:	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_042

$_035:	test	byte ptr [rsi+0x2D], 0x20
	je	$_040
	or	byte ptr [rsi+0x2D], 0x40
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, qword ptr [rsi+0x20]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	dword ptr [rbp-0x4], 0
	mov	ecx, eax
	mov	byte ptr [rsp+0x20], 1
	lea	r9, [rbp-0x70]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	test	eax, eax
	jnz	$_043
	mov	rax, qword ptr [rbp-0x70]
	cmp	byte ptr [rbp-0x74], 1
	jnz	$_036
	movsx	rax, al
	jmp	$_038

$_036:	cmp	byte ptr [rbp-0x74], 2
	jnz	$_037
	movsx	rax, ax
	jmp	$_038

$_037:	cmp	byte ptr [rbp-0x74], 4
	jnz	$_038
	movsxd	rax, eax
$_038:	cmp	dword ptr [rbp-0x34], 1
	jnz	$_039
	mov	rcx, qword ptr [rbp-0x20]
	mov	ecx, dword ptr [rcx+0x28]
	add	rax, rcx
$_039:	mov	qword ptr [rsi+0x10], rax
	inc	ebx
	jmp	$_041

$_040:	cmp	qword ptr [rsi+0x20], 0
	jz	$_041
	inc	edi
$_041:	mov	rsi, qword ptr [rsi+0x8]
$_042:	test	rsi, rsi
	jne	$_035
$_043:	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, qword ptr [rbp-0x80]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rax, qword ptr [rbp+0x38]
	mov	dword ptr [rax], edi
	mov	rax, qword ptr [rbp+0x40]
	mov	dword ptr [rax], ebx
	test	ebx, ebx
	jz	$_047
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_047
	mov	rsi, qword ptr [rbp+0x28]
	mov	rsi, qword ptr [rsi+0x8]
	mov	rdi, qword ptr [rsi+0x8]
	jmp	$_046

$_044:	test	byte ptr [rsi+0x2D], 0x20
	jz	$_045
	mov	edx, dword ptr [rsi+0x10]
	mov	rcx, rsi
	call	$_024
	test	rax, rax
	jz	$_045
	mov	rcx, rax
	mov	eax, dword ptr [rcx+0x10]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rcx+0x20]
	mov	r8d, dword ptr [rsi+0x10]
	mov	rdx, qword ptr [rsi+0x20]
	mov	ecx, 3022
	call	asmerr@PLT
$_045:	mov	rsi, qword ptr [rsi+0x8]
	mov	rdi, qword ptr [rsi+0x8]
$_046:	test	rdi, rdi
	jnz	$_044
$_047:	mov	eax, ebx
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_048:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	xor	edi, edi
	movabs	rax, 0x8000000000000000
	movabs	rdx, 0x7FFFFFFFFFFFFFFF
	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_051

$_049:	test	byte ptr [rsi+0x2D], 0x40
	jz	$_050
	inc	edi
	mov	rcx, qword ptr [rsi+0x10]
	cmp	rcx, rax
	cmovg	rax, rcx
	cmp	rcx, rdx
	cmovl	rdx, rcx
$_050:	mov	rsi, qword ptr [rsi+0x8]
$_051:	test	rsi, rsi
	jnz	$_049
	test	edi, edi
	jnz	$_052
	xor	eax, eax
	xor	edx, edx
$_052:	mov	rbx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp+0x30]
	mov	qword ptr [rbx], rax
	mov	qword ptr [rcx], rdx
	mov	rsi, qword ptr [rbp+0x28]
	mov	ecx, 1
	mov	eax, 8
	test	byte ptr [rsi+0x2C], 0x40
	jz	$_053
	mov	eax, 1
	jmp	$_054

$_053:	test	dword ptr [rsi+0x2C], 0x80
	jnz	$_054
	add	eax, 2
	add	ecx, 1
	test	byte ptr [rsi+0x2D], 0x0E
	jnz	$_054
	add	eax, 1
	test	byte ptr [ModuleInfo+0x334+rip], 0x20
	jnz	$_054
	add	eax, 10
$_054:	mov	rsi, qword ptr [rbp+0x40]
	mov	dword ptr [rsi], eax
	mov	rsi, qword ptr [rbp+0x48]
	mov	eax, edi
	shl	eax, cl
	mov	dword ptr [rsi], eax
	mov	rax, qword ptr [rbx]
	sub	rax, rdx
	mov	ecx, edi
	add	rax, 1
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_055:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	xor	edi, edi
	xor	edx, edx
	jmp	$_063

$_056:	mov	al, byte ptr [rsi]
	mov	ah, byte ptr [rsi-0x18]
	mov	ecx, dword ptr [rsi-0x14]
	jmp	$_061

$_057:	inc	edx
	jmp	$_062

$_058:	dec	edx
	jmp	$_062

$_059:	test	edx, edx
	jnz	$_062
	cmp	ah, 2
	jnz	$_060
	cmp	ecx, 25
	jc	$_060
	cmp	ecx, 31
	jbe	$_062
$_060:	mov	byte ptr [rsi], 0
	mov	rdi, rsi
	jmp	$_064

$_061:	cmp	al, 40
	jz	$_057
	cmp	al, 41
	jz	$_058
	cmp	al, 58
	jz	$_059
$_062:	add	rsi, 24
$_063:	cmp	byte ptr [rsi], 0
	jnz	$_056
$_064:	mov	rax, rdi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_065:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rbx, r9
	add	rbx, 24
	mov	rax, rbx
	mov	rsi, rbx
	xor	edi, edi
	mov	dword ptr [rbp-0x4], edi
	mov	rcx, rbx
	call	$_055
	mov	qword ptr [rbp-0x10], rax
$_066:	mov	al, byte ptr [rbx]
	jmp	$_071

$_067:	jmp	$_073

$_068:	inc	edi
	jmp	$_072

$_069:	dec	edi
	jmp	$_072

$_070:	test	edi, edi
	jnz	$_072
	mov	rdi, qword ptr [rbx+0x10]
	mov	byte ptr [rdi], 0
	mov	rdx, qword ptr [rsi+0x10]
	mov	rcx, qword ptr [rbp+0x38]
	call	tstrcpy@PLT
	lea	rsi, [rbx+0x18]
	mov	byte ptr [rdi], 44
	xor	edi, edi
	inc	dword ptr [rbp-0x4]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	mov	byte ptr [rbx], 0
	jmp	$_072

$_071:	cmp	al, 0
	jz	$_067
	cmp	al, 40
	jz	$_068
	cmp	al, 41
	jz	$_069
	cmp	al, 44
	jz	$_070
$_072:	add	rbx, 24
	jmp	$_066

$_073:
	mov	rbx, qword ptr [rbp-0x10]
	test	rbx, rbx
	jz	$_074
	mov	byte ptr [rbx], 58
$_074:	mov	eax, dword ptr [rbp-0x4]
	test	eax, eax
	jz	$_079
	mov	rdx, qword ptr [rsi+0x10]
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	mov	rbx, qword ptr [rbp+0x40]
	xor	eax, eax
	jmp	$_076

$_075:	add	eax, 1
	add	rbx, 24
$_076:	cmp	byte ptr [rbx], 0
	jnz	$_075
	mov	rbx, qword ptr [rbp+0x30]
	mov	dword ptr [rbx], eax
	mov	rsi, qword ptr [rbp+0x28]
	test	byte ptr [rsi+0x2E], 0x10
	jz	$_078
	and	dword ptr [rsi+0x2C], 0xFFEFFFFF
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_077
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_077:	call	RunLineQueue@PLT
	or	byte ptr [rsi+0x2E], 0x10
$_078:	mov	eax, 1
$_079:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_080:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 64
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x30], rax
	mov	rax, qword ptr [rbp+0x18]
	mov	qword ptr [rsp+0x28], rax
	mov	rax, qword ptr [rbp+0x10]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp+0x28]
	mov	r8, qword ptr [rbp+0x20]
	mov	rdx, qword ptr [rbp+0x10]
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
	leave
	ret

$_081:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 104
	test	byte ptr [ModuleInfo+0x334+rip], 0x20
	jnz	$_082
	mov	edx, dword ptr [rbp+0x18]
	lea	rcx, [DS0007+rip]
	call	AddLineQueueX@PLT
$_082:	lea	rdx, [rbp-0x40]
	mov	ecx, dword ptr [rbp+0x18]
	call	GetResWName@PLT
	mov	eax, dword ptr [rbp+0x20]
	mov	edx, dword ptr [rbp+0x18]
	mov	rbx, qword ptr [rbp+0x28]
	test	eax, 0xE00
	jnz	$_085
	test	eax, 0x100
	jz	$_083
	mov	r8, rbx
	lea	rcx, [DS0008+rip]
	call	AddLineQueueX@PLT
	jmp	$_084

$_083:	mov	r8, rbx
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
$_084:	jmp	$_092

$_085:	test	eax, 0x200
	jz	$_088
	test	eax, 0x100
	jz	$_086
	mov	r8, rbx
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
	jmp	$_087

$_086:	mov	r8, rbx
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
$_087:	jmp	$_092

$_088:	test	eax, 0x400
	jz	$_091
	test	eax, 0x100
	jz	$_089
	mov	r8, rbx
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
	jmp	$_090

$_089:	mov	r8, rbx
	lea	rcx, [DS000C+rip]
	call	AddLineQueueX@PLT
$_090:	jmp	$_092

$_091:	mov	r8, rbx
	lea	rcx, [DS000D+rip]
	call	AddLineQueueX@PLT
$_092:	leave
	pop	rbx
	ret

$_093:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	mov	ecx, 682
	mov	edx, 4
	cmp	dword ptr [rbp+0x10], 205
	jnz	$_094
	mov	edx, 1
	mov	ecx, 719
	jmp	$_095

$_094:	cmp	dword ptr [rbp+0x10], 207
	jnz	$_095
	mov	edx, 2
	mov	ecx, 719
$_095:	mov	rax, qword ptr [rbp+0x30]
	mov	qword ptr [rsp+0x40], rax
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x38], rax
	mov	dword ptr [rsp+0x30], edx
	mov	rax, qword ptr [rbp+0x20]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], edx
	mov	r9d, dword ptr [rbp+0x18]
	mov	r8d, dword ptr [rbp+0x10]
	mov	edx, ecx
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
	leave
	ret

$_096:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 232
	lea	rax, [rbp-0x28]
	mov	qword ptr [rbp-0x48], rax
	lea	rax, [rbp-0x18]
	mov	qword ptr [rbp-0x50], rax
	mov	rax, qword ptr [rbp+0x40]
	mov	qword ptr [rbp-0x58], rax
	mov	rsi, rcx
	mov	rdi, r8
	lea	r9, [rbp-0x60]
	lea	r8, [rbp-0x5C]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rsi
	call	$_031
	test	eax, eax
	jz	$_097
	test	byte ptr [rsi+0x2C], 0x40
	jz	$_097
	add	eax, 8
$_097:	test	byte ptr [ModuleInfo+0x334+rip], 0x10
	jnz	$_098
	cmp	eax, 8
	jnc	$_099
$_098:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_005
	jmp	$_178

$_099:	mov	dword ptr [rbp-0x64], 210
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x50]
	call	tstrcpy@PLT
	mov	qword ptr [rbp-0x70], 0
	test	byte ptr [rsi+0x2C], 0x01
	jz	$_102
	mov	rax, rsi
	mov	rbx, qword ptr [rsi+0x8]
$_100:	test	rbx, rbx
	jz	$_102
	test	byte ptr [rbx+0x2C], 0x10
	jz	$_101
	mov	qword ptr [rax+0x8], 0
	mov	qword ptr [rbp-0x70], rbx
	mov	rdx, qword ptr [rbp+0x40]
	mov	ecx, dword ptr [rbx+0x18]
	call	GetLabelStr@PLT
	jmp	$_102

$_101:	mov	rax, rbx
	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_100

$_102:	cmp	byte ptr [ModuleInfo+0x336+rip], 0
	jz	$_103
	test	byte ptr [rsi+0x2E], 0x40
	jnz	$_103
	mov	cl, byte ptr [ModuleInfo+0x336+rip]
	mov	eax, 1
	shl	eax, cl
	mov	edx, eax
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
	jmp	$_104

$_103:	test	byte ptr [rsi+0x2C], 0x40
	jz	$_104
	test	byte ptr [rsi+0x2E], 0x20
	jz	$_104
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_104
	test	byte ptr [rsi+0x2E], 0x40
	jnz	$_104
	lea	rcx, [DS0010+rip]
	call	AddLineQueue@PLT
$_104:	lea	r8, [DS0002+rip]
	mov	rdx, qword ptr [rbp-0x50]
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x5C], 0
	jz	$_107
	mov	rax, rsi
	mov	rbx, qword ptr [rsi+0x8]
$_105:	test	rbx, rbx
	jz	$_107
	test	byte ptr [rbx+0x2D], 0x20
	jnz	$_106
	mov	rcx, qword ptr [rbx+0x8]
	mov	qword ptr [rax+0x8], rcx
	mov	r8, rdi
	mov	rdx, rbx
	mov	rcx, rsi
	call	$_001
$_106:	mov	rax, rbx
	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_105

$_107:	jmp	$_174

$_108:	lea	rax, [rbp-0x88]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rbp-0x84]
	lea	r8, [rbp-0x80]
	lea	rdx, [rbp-0x78]
	mov	rcx, rsi
	call	$_048
	mov	qword ptr [rbp-0x90], rax
	mov	dword ptr [rbp-0x94], ecx
	mov	dword ptr [rbp-0x98], 0
	cmp	ecx, dword ptr [rbp-0x84]
	jc	$_175
	mov	ebx, ecx
$_109:	cmp	ebx, dword ptr [rbp-0x84]
	jc	$_116
	cmp	qword ptr [rbp-0x80], rdx
	jle	$_116
	cmp	eax, dword ptr [rbp-0x88]
	jbe	$_116
	mov	r8d, dword ptr [rbp-0x88]
	mov	rdx, qword ptr [rbp-0x78]
	mov	rcx, rsi
	call	$_008
	mov	ebx, eax
	mov	r8d, dword ptr [rbp-0x88]
	mov	rdx, qword ptr [rbp-0x80]
	mov	rcx, rsi
	call	$_012
	jmp	$_114

$_110:	mov	rdx, qword ptr [rbp-0x78]
	mov	rcx, rsi
	call	$_029
	test	rax, rax
	je	$_116
	sub	dword ptr [rbp-0x94], eax
	jmp	$_115

$_111:	mov	rdx, qword ptr [rbp-0x80]
	mov	rcx, rsi
	call	$_029
	test	rax, rax
	je	$_116
	sub	dword ptr [rbp-0x94], eax
	jmp	$_115

$_112:	mov	ebx, dword ptr [rbp-0x94]
	mov	r9d, dword ptr [rbp-0x88]
	mov	r8, qword ptr [rbp-0x78]
	lea	rdx, [rbp-0x94]
	mov	rcx, rsi
	call	$_016
	jmp	$_115

$_113:	mov	ebx, dword ptr [rbp-0x94]
	mov	r9d, dword ptr [rbp-0x88]
	mov	r8, qword ptr [rbp-0x80]
	lea	rdx, [rbp-0x94]
	mov	rcx, rsi
	call	$_020
	jmp	$_115

$_114:	cmp	ebx, dword ptr [rbp-0x84]
	jc	$_110
	cmp	eax, dword ptr [rbp-0x84]
	jc	$_111
	cmp	ebx, eax
	jnc	$_112
	jmp	$_113

$_115:	add	dword ptr [rbp-0x98], eax
	lea	rax, [rbp-0x88]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rbp-0x84]
	lea	r8, [rbp-0x80]
	lea	rdx, [rbp-0x78]
	mov	rcx, rsi
	call	$_048
	mov	qword ptr [rbp-0x90], rax
	cmp	ebx, dword ptr [rbp-0x94]
	jz	$_116
	mov	ebx, dword ptr [rbp-0x94]
	jmp	$_109

$_116:	mov	eax, dword ptr [rbp-0x94]
	cmp	eax, dword ptr [rbp-0x84]
	jc	$_175
	mov	byte ptr [rbp-0x39], 0
	cmp	rax, qword ptr [rbp-0x90]
	jge	$_117
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_117
	inc	byte ptr [rbp-0x39]
$_117:	test	byte ptr [rsi+0x2C], 0x40
	jz	$_118
	test	byte ptr [rsi+0x2E], 0x20
	jz	$_118
	mov	rdx, qword ptr [rbp-0x50]
	mov	rcx, qword ptr [rbp-0x48]
	call	tstrcpy@PLT
	mov	r8, qword ptr [rbp-0x78]
	mov	rdx, rax
	lea	rcx, [DS0011+rip]
	call	AddLineQueueX@PLT
	jmp	$_119

$_118:	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	rdx, qword ptr [rbp-0x48]
	mov	ecx, eax
	call	GetLabelStr@PLT
$_119:	mov	rdi, qword ptr [rbp+0x40]
	cmp	dword ptr [rbp-0x98], 0
	jz	$_120
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	rdx, qword ptr [rbp-0x50]
	mov	ecx, eax
	call	GetLabelStr@PLT
	mov	rdi, rax
$_120:	mov	rbx, qword ptr [rsi+0x20]
	test	byte ptr [rsi+0x2C], 0x40
	jnz	$_121
	mov	r9, rdi
	mov	r8, qword ptr [rbp-0x78]
	mov	rdx, qword ptr [rbp-0x80]
	mov	rcx, rbx
	call	$_080
$_121:	mov	cl, byte ptr [ModuleInfo+0x1CC+rip]
	test	byte ptr [rsi+0x2C], 0x40
	jz	$_124
	test	byte ptr [rsi+0x2E], 0x20
	jz	$_124
	test	byte ptr [rsi+0x2E], 0x40
	jz	$_122
	mov	rdx, qword ptr [rbp-0x48]
	lea	rcx, [DS0012+rip]
	call	AddLineQueueX@PLT
	jmp	$_123

$_122:	cmp	cl, 2
	jnz	$_123
	mov	dword ptr [rbp-0x64], 214
$_123:	jmp	$_153

$_124:	mov	dword ptr [rbp-0x9C], 0
	mov	qword ptr [rbp-0xA8], rsi
	mov	rsi, qword ptr [rsi+0x8]
$_125:	test	rsi, rsi
	jz	$_128
	test	byte ptr [rsi+0x2D], 0x40
	jz	$_127
	lea	rdx, [rbp-0x38]
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr@PLT
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jz	$_126
	mov	eax, dword ptr [rax+0x28]
	mov	dword ptr [rbp-0x9C], eax
$_126:	jmp	$_128

$_127:	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_125

$_128:	mov	rsi, qword ptr [rbp-0xA8]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_129
	cmp	qword ptr [rbp-0x70], 0
	jnz	$_129
	call	GetCurrOffset@PLT
	add	rax, 34
	add	eax, dword ptr [rbp-0x60]
	jmp	$_130

$_129:	mov	rcx, qword ptr [rbp-0x58]
	call	SymFind@PLT
	test	rax, rax
	jz	$_130
	mov	eax, dword ptr [rax+0x28]
$_130:	cmp	dword ptr [rbp-0x9C], 0
	jz	$_132
	test	eax, eax
	jz	$_132
	sub	eax, dword ptr [rbp-0x9C]
	test	eax, 0xFFFFFF00
	jnz	$_131
	mov	dword ptr [rbp-0x64], 205
	jmp	$_132

$_131:	test	eax, 0xFFFF0000
	jnz	$_132
	mov	dword ptr [rbp-0x64], 207
$_132:	cmp	byte ptr [rbp-0x39], 0
	jne	$_137
	test	dword ptr [rsi+0x2C], 0x1080
	je	$_137
	test	byte ptr [ModuleInfo+0x334+rip], 0x20
	je	$_137
	mov	ebx, dword ptr [rsi+0x30]
	cmp	ebx, 126
	jz	$_133
	cmp	ebx, 110
	jnz	$_134
$_133:	lea	rdx, [DS0013+rip]
	mov	ecx, 2008
	call	asmerr@PLT
$_134:	lea	rcx, [DS0014+rip]
	call	AddLineQueue@PLT
	test	byte ptr [rsi+0x2D], 0x10
	jz	$_136
	mov	rax, qword ptr [rbp-0x78]
	cmp	rax, 0
	jge	$_135
	mov	edx, ebx
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	mov	ebx, 115
	jmp	$_136

$_135:	mov	ecx, ebx
	lea	ebx, [rbx+0x62]
	cmp	ecx, 107
	jc	$_136
	lea	ebx, [rcx+0x10]
$_136:	mov	rdx, qword ptr [rbp-0x58]
	lea	rcx, [DS0016+rip]
	call	AddLineQueueX@PLT
	mov	rax, qword ptr [rbp-0x58]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x48]
	mov	r8, qword ptr [rbp-0x78]
	mov	edx, ebx
	mov	ecx, dword ptr [rbp-0x64]
	call	$_093
	lea	rcx, [DS0017+rip]
	call	AddLineQueueX@PLT
	jmp	$_151

$_137:	test	byte ptr [ModuleInfo+0x334+rip], 0x20
	je	$_144
	lea	rcx, [DS0014+rip]
	call	AddLineQueue@PLT
	mov	rcx, rbx
	mov	ebx, dword ptr [rsi+0x30]
	test	dword ptr [rsi+0x2C], 0x1080
	jnz	$_138
	mov	r8, rcx
	mov	edx, dword ptr [rsi+0x2C]
	mov	ecx, 115
	call	$_081
	mov	ebx, 115
	jmp	$_140

$_138:	test	byte ptr [rsi+0x2D], 0x10
	jz	$_140
	mov	rax, qword ptr [rbp-0x78]
	cmp	rax, 0
	jge	$_139
	mov	edx, ebx
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	mov	ebx, 115
	jmp	$_140

$_139:	mov	ecx, ebx
	lea	ebx, [rbx+0x62]
	cmp	ecx, 107
	jc	$_140
	lea	ebx, [rcx+0x10]
$_140:	mov	rdx, qword ptr [rbp-0x58]
	lea	rcx, [DS0016+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp-0x78]
	cmp	byte ptr [rbp-0x39], 0
	jz	$_143
	cmp	qword ptr [rbp-0x90], 256
	jge	$_141
	mov	rax, qword ptr [rbp-0x58]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x48]
	mov	r8, rcx
	mov	edx, ebx
	lea	rcx, [DS0018+rip]
	call	AddLineQueueX@PLT
	jmp	$_142

$_141:	mov	rax, qword ptr [rbp-0x58]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x48]
	mov	r8, rcx
	mov	edx, ebx
	lea	rcx, [DS0019+rip]
	call	AddLineQueueX@PLT
$_142:	xor	ecx, ecx
	mov	ebx, 115
$_143:	mov	rax, qword ptr [rbp-0x58]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x48]
	mov	r8, rcx
	mov	edx, ebx
	mov	ecx, dword ptr [rbp-0x64]
	call	$_093
	lea	rcx, [DS0017+rip]
	call	AddLineQueue@PLT
	jmp	$_151

$_144:	mov	rcx, rbx
	mov	ebx, dword ptr [rsi+0x30]
	test	dword ptr [rsi+0x2C], 0x1080
	jnz	$_145
	mov	r8, rcx
	mov	edx, dword ptr [rsi+0x2C]
	mov	ecx, 115
	call	$_081
	mov	ebx, 115
	jmp	$_147

$_145:	lea	rcx, [DS0014+rip]
	call	AddLineQueue@PLT
	test	byte ptr [rsi+0x2D], 0x10
	jz	$_147
	mov	rax, qword ptr [rbp-0x78]
	cmp	rax, 0
	jge	$_146
	mov	edx, ebx
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	mov	ebx, 115
	jmp	$_147

$_146:	mov	ecx, ebx
	lea	ebx, [rbx+0x62]
	cmp	ecx, 107
	jc	$_147
	lea	ebx, [rcx+0x10]
$_147:	mov	rdx, qword ptr [rbp-0x58]
	lea	rcx, [DS001A+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp-0x78]
	cmp	byte ptr [rbp-0x39], 0
	jz	$_150
	cmp	qword ptr [rbp-0x90], 256
	jge	$_148
	mov	rax, qword ptr [rbp-0x58]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x48]
	mov	r8, rcx
	mov	edx, ebx
	lea	rcx, [DS0018+rip]
	call	AddLineQueueX@PLT
	jmp	$_149

$_148:	mov	rax, qword ptr [rbp-0x58]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x48]
	mov	r8, rcx
	mov	edx, ebx
	lea	rcx, [DS0019+rip]
	call	AddLineQueueX@PLT
$_149:	xor	ecx, ecx
	mov	ebx, 115
$_150:	mov	rax, qword ptr [rbp-0x58]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x48]
	mov	r8, rcx
	mov	edx, ebx
	mov	ecx, dword ptr [rbp-0x64]
	call	$_093
	lea	rcx, [DS001B+rip]
	call	AddLineQueue@PLT
$_151:	cmp	dword ptr [rbp-0x64], 205
	jz	$_152
	mov	edx, dword ptr [rbp-0x64]
	lea	rcx, [DS001C+rip]
	call	AddLineQueueX@PLT
$_152:	lea	r8, [DS0002+rip]
	mov	rdx, qword ptr [rbp-0x48]
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
$_153:	cmp	byte ptr [rbp-0x39], 0
	je	$_167
	mov	qword ptr [rbp-0xA8], rdi
	mov	ebx, 4294967295
	mov	edi, 4294967295
	mov	rsi, qword ptr [rsi+0x8]
$_154:	test	rsi, rsi
	jz	$_157
	test	byte ptr [rsi+0x2D], 0x40
	jz	$_156
	lea	rdx, [rbp-0x38]
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr@PLT
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jz	$_157
	cmp	ebx, dword ptr [rax+0x28]
	jz	$_155
	mov	ebx, dword ptr [rax+0x28]
	inc	edi
$_155:	mov	qword ptr [rsi], rdi
$_156:	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_154

$_157:	inc	edi
	mov	dword ptr [rbp-0x4], edi
	mov	rdi, qword ptr [rbp-0xA8]
	mov	rsi, qword ptr [rbp+0x28]
	mov	ebx, 4294967295
	mov	rsi, qword ptr [rsi+0x8]
$_158:	test	rsi, rsi
	jz	$_160
	test	byte ptr [rsi+0x2D], 0x40
	jz	$_159
	cmp	rbx, qword ptr [rsi]
	jz	$_159
	mov	r9d, dword ptr [rsi+0x18]
	mov	r8, qword ptr [rbp-0x58]
	mov	edx, dword ptr [rbp-0x64]
	lea	rcx, [DS001D+rip]
	call	AddLineQueueX@PLT
	mov	rbx, qword ptr [rsi]
$_159:	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_158

$_160:	mov	rsi, qword ptr [rbp+0x28]
	mov	edx, dword ptr [rbp-0x64]
	lea	rcx, [DS001E+rip]
	call	AddLineQueueX@PLT
	mov	rax, qword ptr [rbp-0x80]
	sub	rax, qword ptr [rbp-0x78]
	inc	eax
	mov	dword ptr [rbp-0x8], eax
	mov	ecx, 205
	cmp	eax, 256
	jle	$_161
	mov	ecx, 207
$_161:	mov	dword ptr [rbp-0xAC], ecx
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp-0x48]
	lea	rcx, [DS001F+rip]
	call	AddLineQueueX@PLT
	xor	ebx, ebx
$_162:	cmp	ebx, dword ptr [rbp-0x8]
	jnc	$_165
	mov	rax, qword ptr [rbp-0x78]
	add	rax, rbx
	mov	rdx, rax
	mov	rcx, rsi
	call	$_024
	test	rax, rax
	jz	$_163
	mov	rdx, qword ptr [rax+0x8]
	mov	qword ptr [rcx+0x8], rdx
	mov	r8, qword ptr [rax]
	mov	edx, dword ptr [rbp-0xAC]
	lea	rcx, [DS0020+rip]
	call	AddLineQueueX@PLT
	jmp	$_164

$_163:	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rbp-0xAC]
	lea	rcx, [DS0020+rip]
	call	AddLineQueueX@PLT
$_164:	inc	ebx
	jmp	$_162

$_165:	cmp	dword ptr [rbp-0x64], 205
	jz	$_166
	mov	edx, dword ptr [rbp-0x64]
	lea	rcx, [DS001C+rip]
	call	AddLineQueueX@PLT
$_166:	jmp	$_171

$_167:	xor	ebx, ebx
$_168:	cmp	rbx, qword ptr [rbp-0x90]
	jge	$_171
	mov	rax, qword ptr [rbp-0x78]
	add	rax, rbx
	mov	rdx, rax
	mov	rcx, rsi
	call	$_024
	test	rax, rax
	jz	$_169
	mov	rdx, qword ptr [rax+0x8]
	mov	qword ptr [rcx+0x8], rdx
	mov	ecx, dword ptr [rax+0x18]
	mov	r9d, ecx
	mov	r8, qword ptr [rbp-0x58]
	mov	edx, dword ptr [rbp-0x64]
	lea	rcx, [DS001D+rip]
	call	AddLineQueueX@PLT
	jmp	$_170

$_169:	mov	edx, dword ptr [rbp-0x64]
	lea	rcx, [DS001E+rip]
	call	AddLineQueueX@PLT
$_170:	inc	ebx
	jmp	$_168

$_171:	test	byte ptr [rsi+0x2E], 0x40
	jz	$_172
	lea	rcx, [DS0021+rip]
	call	AddLineQueue@PLT
$_172:	cmp	dword ptr [rbp-0x98], 0
	jz	$_174
	lea	r8, [DS0002+rip]
	mov	rdx, qword ptr [rbp-0x50]
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	mov	rbx, qword ptr [rsi+0x8]
$_173:	test	rbx, rbx
	jz	$_174
	or	byte ptr [rbx+0x2D], 0x40
	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_173

$_174:	cmp	qword ptr [rsi+0x20], 0
	jne	$_108
$_175:	mov	rbx, qword ptr [rsi+0x8]
$_176:	test	rbx, rbx
	jz	$_177
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, rbx
	mov	rcx, rsi
	call	$_001
	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_176

$_177:	cmp	qword ptr [rbp-0x70], 0
	jz	$_178
	cmp	qword ptr [rsi+0x8], 0
	jz	$_178
	mov	rdx, qword ptr [rbp+0x40]
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
$_178:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_179:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	rsi, rcx
	lea	rdi, [rbp-0x20]
	cmp	dword ptr [rsi+0x14], 0
	jnz	$_180
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_180:	cmp	dword ptr [rsi+0x1C], 0
	jnz	$_181
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x1C], eax
$_181:	lea	r8, [DS0002+rip]
	mov	edx, dword ptr [rsi+0x1C]
	lea	rcx, [DS0001+0x2F+rip]
	call	AddLineQueueX@PLT
	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr@PLT
	lea	rdx, [rbp-0x10]
	mov	ecx, dword ptr [rsi+0x14]
	call	GetLabelStr@PLT
	mov	ebx, dword ptr [rsi+0x30]
	test	byte ptr [rsi+0x2D], 0x10
	jz	$_184
	mov	r8, rdi
	lea	rdx, [DS0023+rip]
	lea	rcx, [rbp-0x40]
	call	tsprintf@PLT
	lea	rcx, [rbp-0x40]
	call	SymFind@PLT
	test	rax, rax
	jz	$_182
	mov	rcx, rax
	xor	eax, eax
	cmp	dword ptr [rcx+0x50], 0
	jge	$_182
	inc	eax
$_182:	mov	ecx, ebx
	lea	ebx, [rbx+0x62]
	cmp	ecx, 107
	jc	$_183
	lea	ebx, [rcx+0x10]
$_183:	test	eax, eax
	jz	$_184
	mov	r8d, ecx
	mov	edx, ebx
	lea	rcx, [DS0024+rip]
	call	AddLineQueueX@PLT
$_184:	test	byte ptr [ModuleInfo+0x334+rip], 0x20
	jz	$_187
	cmp	ebx, 126
	jz	$_185
	cmp	ebx, 110
	jnz	$_186
$_185:	lea	rdx, [DS0013+rip]
	mov	ecx, 2008
	call	asmerr@PLT
$_186:	lea	rax, [rbp-0x10]
	mov	qword ptr [rsp+0x28], rax
	mov	qword ptr [rsp+0x20], rdi
	mov	r9, rdi
	mov	r8d, ebx
	lea	rdx, [rbp-0x10]
	lea	rcx, [DS0025+rip]
	call	AddLineQueueX@PLT
	jmp	$_189

$_187:	mov	esi, 115
	cmp	ebx, esi
	jnz	$_188
	mov	esi, 117
$_188:	mov	dword ptr [rsp+0x50], esi
	lea	rax, [rbp-0x10]
	mov	qword ptr [rsp+0x48], rax
	mov	qword ptr [rsp+0x40], rdi
	mov	qword ptr [rsp+0x38], rdi
	mov	dword ptr [rsp+0x30], ebx
	mov	dword ptr [rsp+0x28], esi
	mov	dword ptr [rsp+0x20], esi
	lea	r9, [rbp-0x10]
	mov	r8d, esi
	mov	edx, esi
	lea	rcx, [DS0026+rip]
	call	AddLineQueueX@PLT
$_189:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_190:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2216
	mov	dword ptr [rbp-0x870], 0
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0x86C], eax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	rsi, qword ptr [ModuleInfo+0x100+rip]
	test	rsi, rsi
	jnz	$_191
	mov	ecx, 56
	call	LclAlloc@PLT
	mov	rsi, rax
	jmp	$_192

$_191:	xor	eax, eax
	mov	ecx, 56
	mov	rdi, rsi
	rep stosb
$_192:	mov	rcx, qword ptr [rbp+0x30]
	call	ExpandCStrings@PLT
	lea	rdi, [rbp-0x800]
	mov	dword ptr [rsi+0x28], 4
	mov	eax, 4
	mov	byte ptr [rbp-0x871], 0
$_193:	cmp	byte ptr [rbx], 40
	jnz	$_194
	inc	dword ptr [rbp+0x28]
	inc	byte ptr [rbp-0x871]
	add	rbx, 24
	jmp	$_193

$_194:
	cmp	dword ptr [rbx+0x4], 532
	jnz	$_195
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	or	eax, 0x40
$_195:	cmp	byte ptr [rbx], 8
	jnz	$_196
	mov	rcx, qword ptr [rbx+0x8]
	mov	ecx, dword ptr [rcx]
	or	cl, 0x20
	cmp	cx, 99
	jnz	$_196
	mov	dword ptr [rbx+0x4], 277
	mov	byte ptr [rbx], 7
	mov	byte ptr [rbx+0x1], 1
$_196:	cmp	dword ptr [rbx+0x4], 277
	jnz	$_197
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_199

$_197:	cmp	dword ptr [rbx+0x4], 280
	jnz	$_198
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	or	eax, 0x100000
	jmp	$_199

$_198:	test	byte ptr [ModuleInfo+0x334+rip], 0x08
	jz	$_199
	or	eax, 0x100000
$_199:	mov	dword ptr [rsi+0x2C], eax
	cmp	byte ptr [rbx], 0
	je	$_228
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, rdi
	call	ExpandHllProc@PLT
	cmp	eax, -1
	jnz	$_200
	jmp	$_231

$_200:	cmp	byte ptr [rdi], 0
	jz	$_201
	mov	rcx, rdi
	call	AddLineQueue@PLT
$_201:	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rsi+0x30], eax
	jmp	$_213

$_202:	or	byte ptr [rsi+0x2D], 0x02
$_203:	jmp	$_221

$_204:	or	byte ptr [rsi+0x2D], 0x04
	or	byte ptr [rsi+0x2D], 0x10
	test	byte ptr [rsi+0x2C], 0x40
	jz	$_205
	or	dword ptr [rsi+0x2C], 0x200080
$_205:	jmp	$_221

$_206:	or	byte ptr [rsi+0x2D], 0x08
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_207
	or	dword ptr [rsi+0x2C], 0x80
	test	byte ptr [rsi+0x2C], 0x40
	jz	$_207
	or	byte ptr [rsi+0x2E], 0x20
$_207:	jmp	$_221

$_208:	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x878], eax
	or	byte ptr [rsi+0x2D], 0x01
	mov	byte ptr [rsp+0x20], 1
	lea	r9, [rbp-0x868]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x878]
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_212
	mov	eax, 8
	cmp	dword ptr [rbp-0x82C], 1
	jnz	$_209
	cmp	byte ptr [rbp-0x828], -64
	jz	$_209
	mov	r8, qword ptr [rbp-0x808]
	movzx	edx, byte ptr [rbp-0x826]
	movzx	ecx, byte ptr [rbp-0x828]
	call	SizeFromMemtype@PLT
$_209:	cmp	eax, 2
	jnz	$_210
	or	byte ptr [rsi+0x2D], 0x02
	jmp	$_212

$_210:	cmp	eax, 4
	jnz	$_211
	or	byte ptr [rsi+0x2D], 0x04
	jmp	$_212

$_211:	cmp	eax, 8
	jnz	$_212
	or	byte ptr [rsi+0x2D], 0x08
$_212:	jmp	$_221

$_213:	cmp	eax, 99
	jc	$_214
	cmp	eax, 106
	jbe	$_202
$_214:	cmp	eax, 9
	jc	$_215
	cmp	eax, 16
	jbe	$_202
$_215:	cmp	eax, 87
	jc	$_216
	cmp	eax, 98
	jbe	$_203
$_216:	cmp	eax, 1
	jc	$_217
	cmp	eax, 8
	jbe	$_203
$_217:	cmp	eax, 107
	jc	$_218
	cmp	eax, 114
	jbe	$_204
$_218:	cmp	eax, 17
	jc	$_219
	cmp	eax, 24
	jbe	$_204
$_219:	cmp	eax, 115
	jc	$_220
	cmp	eax, 130
	jbe	$_206
$_220:	jmp	$_208

$_221:	imul	ecx, dword ptr [ModuleInfo+0x220+rip], 24
	add	rcx, qword ptr [rbp+0x30]
	jmp	$_223

$_222:	sub	rcx, 24
	dec	byte ptr [rbp-0x871]
$_223:	cmp	byte ptr [rbp-0x871], 0
	jz	$_224
	cmp	byte ptr [rcx-0x18], 41
	jz	$_222
$_224:	mov	rcx, qword ptr [rcx+0x10]
	jmp	$_226

$_225:	dec	rcx
$_226:	cmp	rcx, rdi
	jbe	$_227
	cmp	byte ptr [rcx-0x1], 32
	jbe	$_225
$_227:	sub	rcx, qword ptr [rbx+0x10]
	mov	edi, ecx
	inc	ecx
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x20], rax
	mov	r8d, edi
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rax
	call	tmemcpy@PLT
	mov	byte ptr [rax+rdi], 0
$_228:	imul	eax, dword ptr [rbp+0x28], 24
	cmp	dword ptr [rsi+0x2C], 0
	jnz	$_229
	cmp	byte ptr [rbx+rax], 0
	jz	$_229
	cmp	dword ptr [rbp-0x870], 0
	jnz	$_229
	mov	rdx, qword ptr [rbx+rax+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x870], eax
$_229:	cmp	rsi, qword ptr [ModuleInfo+0x100+rip]
	jnz	$_230
	mov	rax, qword ptr [rsi]
	mov	qword ptr [ModuleInfo+0x100+rip], rax
$_230:	mov	rax, qword ptr [ModuleInfo+0xF8+rip]
	mov	qword ptr [rsi], rax
	mov	qword ptr [ModuleInfo+0xF8+rip], rsi
	mov	eax, dword ptr [rbp-0x870]
$_231:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_232:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2120
	mov	dword ptr [rbp-0x4], 0
	mov	rsi, qword ptr [ModuleInfo+0xF8+rip]
	test	rsi, rsi
	jnz	$_233
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_249

$_233:	mov	rax, qword ptr [rsi]
	mov	rcx, qword ptr [ModuleInfo+0x100+rip]
	mov	qword ptr [ModuleInfo+0xF8+rip], rax
	mov	qword ptr [rsi], rcx
	mov	qword ptr [ModuleInfo+0x100+rip], rsi
	lea	rdi, [rbp-0x808]
	mov	rbx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rsi+0x28]
	cmp	ecx, 4
	jz	$_234
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_249

$_234:	inc	dword ptr [rbp+0x28]
	cmp	dword ptr [rsi+0x10], 0
	je	$_247
	cmp	dword ptr [rsi+0x18], 0
	jnz	$_235
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x18], eax
$_235:	cmp	dword ptr [rsi+0x14], 0
	jnz	$_236
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_236:	lea	rdx, [rbp-0x818]
	mov	ecx, dword ptr [rsi+0x14]
	call	GetLabelStr@PLT
	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr@PLT
	mov	rax, rsi
	jmp	$_238

$_237:	mov	rax, qword ptr [rax+0x8]
$_238:	cmp	qword ptr [rax+0x8], 0
	jnz	$_237
	cmp	rax, rsi
	jz	$_239
	test	byte ptr [rax+0x2D], 0xFFFFFF80
	jnz	$_239
	test	byte ptr [rsi+0x2E], 0x40
	jnz	$_239
	mov	edx, dword ptr [rsi+0x14]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
$_239:	mov	cl, byte ptr [ModuleInfo+0x336+rip]
	test	cl, cl
	jz	$_240
	mov	eax, 1
	shl	eax, cl
	mov	edx, eax
	lea	rcx, [DS000F+0x1+rip]
	call	AddLineQueueX@PLT
$_240:	cmp	qword ptr [rsi+0x20], 0
	jne	$_246
	mov	rbx, qword ptr [rsi+0x8]
	lea	r8, [DS0002+rip]
	mov	rdx, rdi
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	jmp	$_245

$_241:	cmp	qword ptr [rbx+0x20], 0
	jnz	$_242
	mov	edx, dword ptr [rbx+0x18]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	jmp	$_244

$_242:	test	byte ptr [rbx+0x2C], 0x08
	jz	$_243
	mov	dword ptr [rbp+0x28], 1
	or	byte ptr [rbx+0x2C], 0x04
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 1
	mov	r9d, 2
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rbx
	call	ExpandHllExpression@PLT
	jmp	$_244

$_243:	mov	rcx, qword ptr [rbx+0x20]
	call	AddLineQueue@PLT
$_244:	mov	rbx, qword ptr [rbx+0x8]
$_245:	test	rbx, rbx
	jnz	$_241
	jmp	$_247

$_246:	lea	r9, [rbp-0x818]
	mov	r8, rdi
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rsi
	call	$_096
$_247:	mov	eax, dword ptr [rsi+0x14]
	test	eax, eax
	jz	$_248
	lea	r8, [DS0002+rip]
	mov	edx, eax
	lea	rcx, [DS0001+0x2F+rip]
	call	AddLineQueueX@PLT
$_248:	mov	eax, dword ptr [rbp-0x4]
$_249:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_250:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2184
	mov	dword ptr [rbp-0x4], 0
	mov	rax, qword ptr [ModuleInfo+0xF8+rip]
	mov	qword ptr [rbp-0x828], rax
	mov	rsi, rax
	test	rsi, rsi
	jnz	$_251
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_321

$_251:	mov	rcx, qword ptr [rbp+0x30]
	call	ExpandCStrings@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	lea	rdi, [rbp-0x818]
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0x8], eax
	xor	ecx, ecx
	jmp	$_318

$_252:	test	byte ptr [rsi+0x2C], 0x01
	jz	$_253
	mov	ecx, 2142
	call	asmerr@PLT
	jmp	$_321

$_253:	cmp	byte ptr [rbx+0x18], 0
	jz	$_254
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_321

$_254:	or	byte ptr [rsi+0x2C], 0x01
$_255:	jmp	$_257

$_256:	mov	rsi, qword ptr [rsi]
$_257:	test	rsi, rsi
	jz	$_258
	cmp	dword ptr [rsi+0x28], 4
	jnz	$_256
$_258:	cmp	dword ptr [rsi+0x28], 4
	jz	$_259
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	jmp	$_321

$_259:	cmp	dword ptr [rsi+0x18], 0
	jnz	$_262
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x18], eax
	test	byte ptr [rsi+0x2C], 0x40
	jz	$_260
	test	byte ptr [rsi+0x2E], 0x20
	jz	$_260
	mov	rcx, rsi
	call	$_179
	jmp	$_261

$_260:	mov	edx, eax
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
$_261:	jmp	$_266

$_262:	test	byte ptr [rsi+0x2E], 0x10
	jz	$_266
	cmp	dword ptr [rsi+0x14], 0
	jnz	$_263
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_263:	mov	rax, rsi
	jmp	$_265

$_264:	mov	rax, qword ptr [rax+0x8]
$_265:	cmp	qword ptr [rax+0x8], 0
	jnz	$_264
	cmp	rax, rsi
	jz	$_266
	test	byte ptr [rax+0x2D], 0xFFFFFF80
	jnz	$_266
	mov	edx, dword ptr [rsi+0x14]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
$_266:	mov	qword ptr [rbp-0x830], 0
	cmp	byte ptr [rbx+0x18], 9
	jnz	$_267
	cmp	byte ptr [rbx+0x30], 8
	jnz	$_267
	cmp	byte ptr [rbx+0x48], 9
	jnz	$_267
	mov	rax, qword ptr [rbx+0x38]
	mov	qword ptr [rbp-0x830], rax
	add	rbx, 72
	add	dword ptr [rbp+0x28], 3
$_267:	mov	r9, rbx
	mov	r8, rdi
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	$_065
	test	rax, rax
	jne	$_319
	mov	cl, byte ptr [ModuleInfo+0x336+rip]
	test	cl, cl
	jz	$_268
	mov	eax, 1
	shl	eax, cl
	mov	edx, eax
	lea	rcx, [DS000F+0x1+rip]
	call	AddLineQueueX@PLT
$_268:	inc	dword ptr [rsi+0x10]
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rbp-0x834], eax
	lea	r8, [DS0002+rip]
	mov	edx, eax
	lea	rcx, [DS0001+0x2F+rip]
	call	AddLineQueueX@PLT
	cmp	qword ptr [rbp-0x830], 0
	jz	$_269
	mov	rdx, qword ptr [rbp-0x830]
	lea	rcx, [DS0027+rip]
	call	AddLineQueueX@PLT
$_269:	mov	ecx, 56
	call	LclAlloc@PLT
	mov	ecx, dword ptr [rbp-0x834]
	mov	rdx, rsi
	mov	rsi, rax
	mov	rax, qword ptr [rdx+0x20]
	mov	dword ptr [rsi+0x18], ecx
	jmp	$_271

$_270:	mov	rdx, qword ptr [rdx+0x8]
$_271:	cmp	qword ptr [rdx+0x8], 0
	jnz	$_270
	mov	qword ptr [rdx+0x8], rsi
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	qword ptr [rbp-0x840], rax
	mov	qword ptr [rbp-0x848], rbx
	mov	qword ptr [rbp-0x850], rsi
	xor	esi, esi
$_272:	mov	rcx, rbx
	call	$_055
	test	rax, rax
	jz	$_275
	mov	rbx, rax
	test	rsi, rsi
	jz	$_273
	mov	rax, qword ptr [rbx+0x10]
	mov	byte ptr [rax], 0
	mov	rcx, rsi
	call	AddLineQueue@PLT
	mov	rax, qword ptr [rbx+0x10]
	mov	byte ptr [rax], 58
	jmp	$_274

$_273:	sub	rax, qword ptr [rbp+0x30]
	mov	ecx, 24
	xor	edx, edx
	div	ecx
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_274:	add	rbx, 24
	mov	rsi, qword ptr [rbx+0x10]
	jmp	$_272

$_275:	test	rsi, rsi
	jz	$_276
	mov	rcx, rsi
	call	AddLineQueue@PLT
$_276:	mov	rsi, qword ptr [rbp-0x850]
	cmp	qword ptr [rbp-0x840], 0
	je	$_287
	cmp	dword ptr [rbp-0x8], 419
	je	$_287
	mov	rbx, qword ptr [rbp-0x848]
	mov	qword ptr [rbp-0x850], rdi
	xor	edi, edi
$_277:	movzx	eax, byte ptr [rbx]
	jmp	$_284
$C0149:
	cmp	edi, 1
	jnz	$_278
	cmp	byte ptr [rbx+0x18], 0
	jnz	$_278
	or	byte ptr [rsi+0x2D], 0x20
	jmp	$_286

$_278:	sub	edi, 2
$C014D:
	inc	edi
$C014E:
	jmp	$_285
$C0155:
$_279:	cmp	byte ptr [rbx+0x18], 0
	jnz	$_280
	or	byte ptr [rsi+0x2D], 0x20
	jmp	$_286

$_280:	jmp	$_285
$C0158:
	cmp	dword ptr [rbx+0x1C], 270
	je	$_286
	jmp	$_279
$C0159:
	cmp	byte ptr [rbx+0x18], 46
	je	$_286
	jmp	$_279
$C015A:
	cmp	dword ptr [rbx+0x4], 249
	jne	$_286
	jmp	$_279
$C015B:
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_282
	cmp	byte ptr [rax+0x18], 1
	jne	$_286
	cmp	byte ptr [rax+0x19], -127
	jz	$_281
	cmp	byte ptr [rax+0x19], -64
	jnz	$_286
$_281:	jmp	$_283

$_282:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_283
	jmp	$_286

$_283:	jmp	$_279

$C0161: jmp	$_286

$_284:	cmp	eax, 1
	jl	$C0161
	cmp	eax, 47
	jg	$C0161
	push	rax
	lea	r11, [$C0161+rip]
	movzx	eax, byte ptr [r11+rax-(1)+(IT$C0162-$C0161)]
	movzx	eax, byte ptr [r11+rax+($C0162-$C0161)]
	sub	r11, rax
	pop	rax
	jmp	r11
$C0162:
	.byte $C0161-$C0149
	.byte $C0161-$C014D
	.byte $C0161-$C014E
	.byte $C0161-$C0155
	.byte $C0161-$C0158
	.byte $C0161-$C0159
	.byte $C0161-$C015A
	.byte $C0161-$C015B
	.byte 0
IT$C0162:
	.byte 2
	.byte 8
	.byte 8
	.byte 6
	.byte 8
	.byte 4
	.byte 8
	.byte 7
	.byte 3
	.byte 3
	.byte 5
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 2
	.byte 8
	.byte 8
	.byte 1
	.byte 0
	.byte 2
	.byte 2
	.byte 8
	.byte 2
	.byte 8
	.byte 2
$C0154:
$_285:	add	rbx, 24
	jmp	$_277

$_286:	mov	rdi, qword ptr [rbp-0x850]
$_287:	mov	rax, qword ptr [rbp-0x840]
	mov	rbx, qword ptr [rbp-0x848]
	cmp	dword ptr [rbp-0x8], 419
	jnz	$_288
	or	byte ptr [rsi+0x2C], 0x10
	jmp	$_292

$_288:	cmp	byte ptr [rbx], 0
	jnz	$_289
	mov	rdx, qword ptr [rbx-0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_321

$_289:	test	eax, eax
	jnz	$_290
	mov	ebx, dword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 1
	mov	r9d, 2
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	EvaluateHllExpression@PLT
	mov	dword ptr [rbp+0x28], ebx
	mov	dword ptr [rbp-0x4], eax
	cmp	eax, -1
	je	$_319
	jmp	$_291

$_290:	imul	eax, dword ptr [ModuleInfo+0x220+rip], 24
	add	rax, qword ptr [rbp+0x30]
	mov	rax, qword ptr [rax+0x10]
	sub	rax, qword ptr [rbx+0x10]
	mov	word ptr [rdi+rax], 0
	mov	r8d, eax
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rdi
	call	tmemcpy@PLT
$_291:	mov	rcx, rdi
	call	LclDup@PLT
	mov	qword ptr [rsi+0x20], rax
$_292:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x28], eax
	jmp	$_319

$_293:	test	rsi, rsi
	jz	$_294
	cmp	dword ptr [rsi+0x28], 4
	jz	$_294
	mov	rsi, qword ptr [rsi]
	jmp	$_293

$_294:	test	rsi, rsi
	jz	$_297
	test	ecx, ecx
	jz	$_297
	mov	rsi, qword ptr [rsi]
$_295:	test	rsi, rsi
	jz	$_296
	cmp	dword ptr [rsi+0x28], 4
	jz	$_296
	mov	rsi, qword ptr [rsi]
	jmp	$_295

$_296:	dec	ecx
	jmp	$_294

$_297:	test	rsi, rsi
	jnz	$_298
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_321

$_298:	cmp	dword ptr [rsi+0x14], 0
	jnz	$_299
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_299:	mov	ecx, 1
	cmp	dword ptr [rbp-0x8], 417
	jz	$_300
	mov	ecx, 2
$_300:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	dword ptr [rbp-0x81C], 0
	cmp	ecx, 2
	jne	$_313
	cmp	byte ptr [rbx], 40
	jne	$_313
	cmp	byte ptr [rbx+0x18], 0
	jz	$_301
	cmp	byte ptr [rbx+0x30], 58
	jnz	$_301
	add	dword ptr [rbp+0x28], 2
	add	rbx, 48
$_301:	mov	rax, qword ptr [rbx+0x28]
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	ecx, 1
$_302:	cmp	byte ptr [rbx], 0
	jz	$_305
	cmp	byte ptr [rbx], 40
	jnz	$_303
	inc	ecx
	jmp	$_304

$_303:	cmp	byte ptr [rbx], 41
	jnz	$_304
	dec	ecx
	jz	$_305
$_304:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_302

$_305:	cmp	byte ptr [rbx], 41
	jne	$_319
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx-0x30], 40
	je	$_312
	cmp	byte ptr [rbx-0x30], 58
	je	$_312
	mov	rcx, qword ptr [rbx-0x8]
	sub	rcx, rax
	je	$_312
	cmp	ecx, 2016
	ja	$_319
	mov	qword ptr [rbp-0x850], rsi
	mov	qword ptr [rbp-0x840], rcx
	mov	r8d, ecx
	mov	rdx, rax
	mov	rcx, rdi
	call	tmemcpy@PLT
	mov	rcx, qword ptr [rbp-0x840]
	add	rcx, rax
	mov	byte ptr [rcx], 0
	dec	rcx
$_306:	cmp	rcx, rax
	jbe	$_307
	cmp	byte ptr [rcx], 32
	ja	$_307
	mov	byte ptr [rcx], 0
	dec	rcx
	jmp	$_306

$_307:	mov	rsi, qword ptr [rsi+0x8]
$_308:	test	rsi, rsi
	jz	$_310
	cmp	qword ptr [rsi+0x20], 0
	jz	$_309
	mov	rdx, qword ptr [rsi+0x20]
	mov	rcx, rdi
	call	tstrcmp@PLT
	test	eax, eax
	jnz	$_309
	mov	ecx, dword ptr [rsi+0x18]
	jmp	$_310

$_309:	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_308

$_310:	mov	rax, rsi
	mov	rsi, qword ptr [rbp-0x850]
	test	rax, rax
	jz	$_311
	mov	edx, dword ptr [rsi+0x18]
	mov	dword ptr [rsi+0x18], ecx
	mov	dword ptr [rbp-0x81C], edx
	jmp	$_312

$_311:	cmp	qword ptr [rsi+0x20], 0
	jz	$_312
	mov	r8, rdi
	mov	rdx, qword ptr [rsi+0x20]
	lea	rcx, [DS0028+rip]
	call	AddLineQueueX@PLT
	mov	eax, dword ptr [rsi+0x1C]
	test	eax, eax
	jz	$_312
	mov	edx, dword ptr [rsi+0x18]
	mov	dword ptr [rsi+0x18], eax
	mov	dword ptr [rbp-0x81C], edx
$_312:	mov	ecx, 2
	jmp	$_314

$_313:	cmp	ecx, 2
	jnz	$_314
	cmp	dword ptr [rsi+0x1C], 0
	jz	$_314
	mov	eax, dword ptr [rsi+0x1C]
	mov	edx, dword ptr [rsi+0x18]
	mov	dword ptr [rsi+0x18], eax
	mov	dword ptr [rbp-0x81C], edx
$_314:	mov	dword ptr [rsp+0x28], 1
	mov	rax, qword ptr [rbp-0x828]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, ecx
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	HllContinueIf@PLT
	cmp	dword ptr [rbp-0x81C], 0
	jz	$_315
	mov	eax, dword ptr [rbp-0x81C]
	mov	dword ptr [rsi+0x18], eax
$_315:	jmp	$_319

$_316:	cmp	byte ptr [rbx+0x18], 40
	jnz	$_317
	cmp	byte ptr [rbx+0x48], 58
	jnz	$_317
	mov	rax, qword ptr [rbx+0x38]
	mov	al, byte ptr [rax]
	cmp	al, 48
	jc	$_317
	cmp	al, 57
	ja	$_317
	sub	al, 48
	movzx	ecx, al
$_317:	jmp	$_293

$_318:	cmp	eax, 419
	je	$_252
	cmp	eax, 416
	je	$_255
	cmp	eax, 417
	je	$_293
	cmp	eax, 418
	jz	$_316
$_319:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_320
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_320
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], -1
$_320:	mov	eax, dword ptr [rbp-0x4]
$_321:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SwitchDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	dword ptr [rbp-0x4], 0
	imul	eax, dword ptr [rbp+0x10], 24
	add	rax, qword ptr [rbp+0x18]
	mov	eax, dword ptr [rax+0x4]
	jmp	$_325

$_322:	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, dword ptr [rbp+0x10]
	call	$_250
	mov	dword ptr [rbp-0x4], eax
	jmp	$_326

$_323:	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, dword ptr [rbp+0x10]
	call	$_232
	mov	dword ptr [rbp-0x4], eax
	jmp	$_326

$_324:	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, dword ptr [rbp+0x10]
	call	$_190
	mov	dword ptr [rbp-0x4], eax
	jmp	$_326

$_325:	cmp	eax, 416
	jz	$_322
	cmp	eax, 418
	jz	$_322
	cmp	eax, 419
	jz	$_322
	cmp	eax, 417
	jz	$_322
	cmp	eax, 420
	jz	$_323
	cmp	eax, 415
	jz	$_324
$_326:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_327
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_327:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_328
	call	RunLineQueue@PLT
$_328:	mov	eax, dword ptr [rbp-0x4]
	leave
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x20, 0x6A, 0x6D, 0x70, 0x20, 0x24, 0x43, 0x25
	.byte  0x30, 0x34, 0x58, 0x00

DS0001:
	.byte  0x20, 0x63, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x2C
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x6A, 0x62, 0x20
	.byte  0x24, 0x43, 0x25, 0x30, 0x34, 0x58, 0x0A, 0x20
	.byte  0x63, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x2C, 0x20
	.byte  0x25, 0x73, 0x0A, 0x20, 0x6A, 0x62, 0x65, 0x20
	.byte  0x24, 0x43, 0x25, 0x30, 0x34, 0x58, 0x0A, 0x24
	.byte  0x43, 0x25, 0x30, 0x34, 0x58, 0x25, 0x73, 0x00

DS0002:
	.byte  0x3A, 0x00

DS0003:
	.byte  0x20, 0x63, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x2C
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x6A, 0x65, 0x20
	.byte  0x24, 0x43, 0x25, 0x30, 0x34, 0x58, 0x00

DS0004:
	.byte  0x25, 0x73, 0x25, 0x73, 0x00

DS0005:
	.byte  0x20, 0x2E, 0x63, 0x61, 0x73, 0x65, 0x20, 0x25
	.byte  0x73, 0x00

DS0006:
	.byte  0x20, 0x63, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x2C
	.byte  0x25, 0x64, 0x0A, 0x20, 0x6A, 0x6C, 0x20, 0x20
	.byte  0x25, 0x73, 0x0A, 0x20, 0x63, 0x6D, 0x70, 0x20
	.byte  0x25, 0x73, 0x2C, 0x25, 0x64, 0x0A, 0x20, 0x6A
	.byte  0x67, 0x20, 0x20, 0x25, 0x73, 0x00

DS0007:
	.byte  0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72, 0x00

DS0008:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x20, 0x25
	.byte  0x72, 0x2C, 0x20, 0x62, 0x79, 0x74, 0x65, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS0009:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x20, 0x25
	.byte  0x72, 0x2C, 0x20, 0x25, 0x73, 0x00

DS000A:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x20, 0x25
	.byte  0x72, 0x2C, 0x20, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS000B:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x64, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x00

DS000C:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x64, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x25, 0x73, 0x00

DS000D:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x71, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x70
	.byte  0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS000E:
	.byte  0x20, 0x25, 0x72, 0x20, 0x65, 0x61, 0x78, 0x2C
	.byte  0x20, 0x25, 0x72, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x5B, 0x72, 0x31, 0x31, 0x2B, 0x25, 0x72, 0x2A
	.byte  0x25, 0x64, 0x2D, 0x28, 0x25, 0x64, 0x2A, 0x25
	.byte  0x64, 0x29, 0x2B, 0x28, 0x25, 0x73, 0x2D, 0x25
	.byte  0x73, 0x29, 0x5D, 0x00

DS000F:
	.byte  0x20, 0x41, 0x4C, 0x49, 0x47, 0x4E, 0x20, 0x25
	.byte  0x64, 0x00

DS0010:
	.byte  0x20, 0x41, 0x4C, 0x49, 0x47, 0x4E, 0x20, 0x38
	.byte  0x00

DS0011:
	.byte  0x4D, 0x49, 0x4E, 0x25, 0x73, 0x20, 0x65, 0x71
	.byte  0x75, 0x20, 0x25, 0x64, 0x00

DS0012:
	.byte  0x2E, 0x64, 0x61, 0x74, 0x61, 0x0A, 0x41, 0x4C
	.byte  0x49, 0x47, 0x4E, 0x20, 0x34, 0x0A, 0x44, 0x54
	.byte  0x25, 0x73, 0x20, 0x6C, 0x61, 0x62, 0x65, 0x6C
	.byte  0x20, 0x64, 0x77, 0x6F, 0x72, 0x64, 0x00

DS0013:
	.byte  0x72, 0x65, 0x67, 0x69, 0x73, 0x74, 0x65, 0x72
	.byte  0x20, 0x72, 0x31, 0x31, 0x20, 0x6F, 0x76, 0x65
	.byte  0x72, 0x77, 0x72, 0x69, 0x74, 0x74, 0x65, 0x6E
	.byte  0x20, 0x62, 0x79, 0x20, 0x2E, 0x53, 0x57, 0x49
	.byte  0x54, 0x43, 0x48, 0x00

DS0014:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61
	.byte  0x78, 0x00

DS0015:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x64, 0x20
	.byte  0x72, 0x61, 0x78, 0x2C, 0x20, 0x25, 0x72, 0x00

DS0016:
	.byte  0x20, 0x6C, 0x65, 0x61, 0x20, 0x72, 0x31, 0x31
	.byte  0x2C, 0x20, 0x25, 0x73, 0x00

DS0017:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x31, 0x31
	.byte  0x2C, 0x20, 0x72, 0x61, 0x78, 0x0A, 0x20, 0x70
	.byte  0x6F, 0x70, 0x20, 0x72, 0x61, 0x78, 0x0A, 0x20
	.byte  0x6A, 0x6D, 0x70, 0x20, 0x72, 0x31, 0x31, 0x00

DS0018:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x7A, 0x78, 0x20, 0x65
	.byte  0x61, 0x78, 0x2C, 0x20, 0x62, 0x79, 0x74, 0x65
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x5B, 0x72, 0x31
	.byte  0x31, 0x2B, 0x25, 0x72, 0x2D, 0x28, 0x25, 0x64
	.byte  0x29, 0x2B, 0x28, 0x49, 0x54, 0x25, 0x73, 0x2D
	.byte  0x25, 0x73, 0x29, 0x5D, 0x00

DS0019:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x7A, 0x78, 0x20, 0x65
	.byte  0x61, 0x78, 0x2C, 0x20, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x5B, 0x72, 0x31
	.byte  0x31, 0x2B, 0x25, 0x72, 0x2A, 0x32, 0x2D, 0x28
	.byte  0x25, 0x64, 0x2A, 0x32, 0x29, 0x2B, 0x28, 0x49
	.byte  0x54, 0x25, 0x73, 0x2D, 0x25, 0x73, 0x29, 0x5D
	.byte  0x00

DS001A:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x31
	.byte  0x31, 0x0A, 0x20, 0x6C, 0x65, 0x61, 0x20, 0x72
	.byte  0x31, 0x31, 0x2C, 0x20, 0x25, 0x73, 0x00

DS001B:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x31, 0x31
	.byte  0x2C, 0x20, 0x72, 0x61, 0x78, 0x0A, 0x20, 0x6D
	.byte  0x6F, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2C, 0x20
	.byte  0x5B, 0x72, 0x73, 0x70, 0x2B, 0x38, 0x5D, 0x0A
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x72, 0x73
	.byte  0x70, 0x2B, 0x38, 0x5D, 0x2C, 0x20, 0x72, 0x31
	.byte  0x31, 0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x72
	.byte  0x31, 0x31, 0x0A, 0x20, 0x72, 0x65, 0x74, 0x6E
	.byte  0x00

DS001C:
	.byte  0x41, 0x4C, 0x49, 0x47, 0x4E, 0x20, 0x25, 0x72
	.byte  0x00

DS001D:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x73, 0x2D, 0x24
	.byte  0x43, 0x25, 0x30, 0x34, 0x58, 0x00

DS001E:
	.byte  0x20, 0x25, 0x72, 0x20, 0x30, 0x00

DS001F:
	.byte  0x49, 0x54, 0x25, 0x73, 0x20, 0x6C, 0x61, 0x62
	.byte  0x65, 0x6C, 0x20, 0x25, 0x72, 0x00

DS0020:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x64, 0x00

DS0021:
	.byte  0x2E, 0x63, 0x6F, 0x64, 0x65, 0x00

DS0022:
	.byte  0x20, 0x6A, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x00

DS0023:
	.byte  0x4D, 0x49, 0x4E, 0x25, 0x73, 0x00

DS0024:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x64, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x25, 0x72, 0x00

DS0025:
	.byte  0x20, 0x6C, 0x65, 0x61, 0x20, 0x72, 0x31, 0x31
	.byte  0x2C, 0x20, 0x25, 0x73, 0x0A, 0x20, 0x73, 0x75
	.byte  0x62, 0x20, 0x72, 0x31, 0x31, 0x2C, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2A, 0x38, 0x2B, 0x72, 0x31, 0x31
	.byte  0x2D, 0x28, 0x4D, 0x49, 0x4E, 0x25, 0x73, 0x2A
	.byte  0x38, 0x29, 0x2B, 0x28, 0x25, 0x73, 0x2D, 0x25
	.byte  0x73, 0x29, 0x5D, 0x0A, 0x20, 0x6A, 0x6D, 0x70
	.byte  0x20, 0x72, 0x31, 0x31, 0x00

DS0026:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72
	.byte  0x0A, 0x20, 0x6C, 0x65, 0x61, 0x20, 0x20, 0x25
	.byte  0x72, 0x2C, 0x20, 0x25, 0x73, 0x0A, 0x20, 0x73
	.byte  0x75, 0x62, 0x20, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x5B, 0x25, 0x72, 0x2B, 0x25, 0x72, 0x2A, 0x38
	.byte  0x2D, 0x28, 0x4D, 0x49, 0x4E, 0x25, 0x73, 0x2A
	.byte  0x38, 0x29, 0x2B, 0x28, 0x25, 0x73, 0x2D, 0x25
	.byte  0x73, 0x29, 0x5D, 0x0A, 0x20, 0x78, 0x63, 0x68
	.byte  0x67, 0x20, 0x25, 0x72, 0x2C, 0x20, 0x5B, 0x72
	.byte  0x73, 0x70, 0x5D, 0x0A, 0x20, 0x72, 0x65, 0x74
	.byte  0x6E, 0x00

DS0027:
	.byte  0x25, 0x73, 0x3A, 0x00

DS0028:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00


.att_syntax prefix
