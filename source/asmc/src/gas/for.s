
.intel_syntax noprefix

.global ForDirective

.extern ExpandHllProc
.extern EvaluateHllExpression
.extern ExpandCStrings
.extern GetLabelStr
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern LstWrite
.extern GetCurrOffset
.extern LclDup
.extern LclAlloc
.extern Tokenize
.extern tstrstart
.extern tstrcat
.extern tstrcpy
.extern tstrrchr
.extern tstrchr
.extern tstrlen
.extern asmerr
.extern ModuleInfo


.SECTION .text
	.ALIGN	16

$_001:	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	call	tstrlen@PLT
	test	rax, rax
	jz	$_003
	mov	ecx, eax
	add	rcx, rbx
$_002:	dec	rcx
	cmp	byte ptr [rcx], 32
	ja	$_003
	mov	byte ptr [rcx], 0
	dec	eax
	jz	$_003
	jmp	$_002

$_003:
	leave
	pop	rbx
	ret

$_004:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	al, byte ptr [rcx]
	jmp	$_006

$_005:	inc	rcx
	mov	al, byte ptr [rcx]
$_006:	cmp	al, 32
	jz	$_005
	cmp	al, 9
	jz	$_005
	mov	rbx, rcx
	xor	edx, edx
$_007:	mov	al, byte ptr [rcx]
	jmp	$_017

$_008:	jmp	$_019

$_009:	inc	edx
	jmp	$_018

$_010:	dec	edx
	jmp	$_018

$_011:	test	edx, edx
	jnz	$_018
	mov	byte ptr [rcx], dl
	mov	al, byte ptr [rcx-0x1]
	cmp	al, 32
	jz	$_012
	cmp	al, 9
	jnz	$_013
$_012:	mov	byte ptr [rcx-0x1], dl
$_013:	inc	rcx
	mov	al, byte ptr [rcx]
	jmp	$_015

$_014:	inc	rcx
	mov	al, byte ptr [rcx]
$_015:	cmp	al, 32
	jz	$_014
	cmp	al, 9
	jz	$_014
	mov	rdx, rbx
	cmp	byte ptr [rdx], 0
	jnz	$_016
	test	al, al
	jz	$_016
	mov	rbx, rcx
	xor	edx, edx
	jmp	$_007

$_016:	jmp	$_019

$_017:	cmp	al, 0
	jz	$_008
	cmp	al, 40
	jz	$_009
	cmp	al, 41
	jz	$_010
	cmp	al, 44
	jz	$_011
$_018:	inc	rcx
	jmp	$_007

$_019:
	mov	rdx, rbx
	movzx	eax, byte ptr [rdx]
	leave
	pop	rbx
	ret

$_020:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	cmp	qword ptr [rbp+0x20], 0
	jz	$_021
	mov	rdx, qword ptr [rbp+0x20]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	$_001
	lea	rdx, [DS0000+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_021:	cmp	qword ptr [rbp+0x28], 0
	jz	$_023
	mov	rdx, qword ptr [rbp+0x28]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	$_001
	cmp	qword ptr [rbp+0x20], 0
	jz	$_022
	cmp	qword ptr [rbp+0x30], 0
	jz	$_022
	lea	rdx, [DS0001+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_022:	cmp	qword ptr [rbp+0x30], 0
	jz	$_023
	lea	rdx, [DS0000+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_023:	cmp	qword ptr [rbp+0x30], 0
	jz	$_024
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	$_001
$_024:	lea	rdx, [DS0002+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	eax, 1
	leave
	pop	rdi
	ret

$_025:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	mov	rbx, rdx
	mov	rdx, qword ptr [rbx+0x8]
	mov	cl, byte ptr [rbx]
	mov	ch, byte ptr [rbx+0x18]
	mov	eax, dword ptr [rdx]
	mov	byte ptr [rbp-0x1], 0
	cmp	cl, 91
	jnz	$_026
	inc	byte ptr [rbp-0x1]
$_026:	jmp	$_030

$_027:	xor	r9d, r9d
	lea	r8, [rdx+0x1]
	lea	rdx, [DS0003+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_028:	xor	r9d, r9d
	mov	r8, qword ptr [rbx+0x40]
	lea	rdx, [DS0004+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_029:	xor	r9d, r9d
	mov	r8, qword ptr [rbx+0x40]
	lea	rdx, [DS0005+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_030:	cmp	al, 126
	jz	$_027
	cmp	cl, 45
	jnz	$_031
	cmp	ch, 45
	jz	$_028
$_031:	cmp	cl, 43
	jnz	$_032
	cmp	ch, 43
	jz	$_029
$_032:	xor	eax, eax
	mov	ecx, 1
$_033:	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_047
	imul	esi, ecx, 24
	add	rsi, rbx
	mov	rdx, qword ptr [rsi+0x8]
	mov	edx, dword ptr [rdx]
	jmp	$_044

$_034:	inc	byte ptr [rbp-0x1]
	jmp	$_046

$_035:	dec	byte ptr [rbp-0x1]
$_036:	jmp	$_046

$_037:	mov	rax, qword ptr [rsi+0x10]
	mov	dl, byte ptr [rax]
	mov	dh, byte ptr [rsi+0x18]
	mov	rcx, qword ptr [rsi+0x28]
	jmp	$_047

$_038:	jmp	$_043

$_039:	mov	rax, qword ptr [rsi+0x10]
	lea	rcx, [rax+0x3]
	cmp	byte ptr [rcx], 0
	jnz	$_040
	mov	rcx, qword ptr [rsi+0x28]
$_040:	jmp	$_047

$_041:	mov	rax, qword ptr [rsi+0x10]
	lea	rcx, [rax+0x2]
	cmp	byte ptr [rcx], 0
	jnz	$_042
	mov	rcx, qword ptr [rsi+0x28]
$_042:	jmp	$_047

$_043:	cmp	dl, 62
	jz	$_039
	cmp	dl, 60
	jz	$_039
	cmp	dl, 124
	jz	$_041
	cmp	dl, 126
	jz	$_041
	cmp	dl, 94
	jz	$_041
	jmp	$_046

$_044:	cmp	byte ptr [rsi], 91
	jz	$_034
	cmp	byte ptr [rsi], 93
	jz	$_035
	cmp	byte ptr [rbp-0x1], 0
	jnz	$_036
	cmp	byte ptr [rsi], 43
	jz	$_037
	cmp	byte ptr [rsi], 45
	jz	$_037
	cmp	byte ptr [rsi], 38
	jz	$_037
	cmp	dword ptr [rsi+0x4], 523
	jnz	$_045
	cmp	byte ptr [rsi+0x1], 45
	je	$_037
$_045:	cmp	byte ptr [rsi], 9
	jz	$_038
$_046:	inc	ecx
	jmp	$_033

$_047:	test	eax, eax
	jnz	$_048
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_070

$_048:	jmp	$_068

$_049:	mov	byte ptr [rax], 0
	cmp	dh, 38
	jnz	$_050
	mov	r9, qword ptr [rsi+0x40]
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0006+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_055

$_050:	cmp	byte ptr [rcx], 126
	jnz	$_051
	lea	r9, [rcx+0x1]
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0007+rip]
	mov	rcx, rdi
	call	$_020
	xor	r9d, r9d
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0003+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_055

$_051:	mov	rax, qword ptr [rsi+0x20]
	mov	ax, word ptr [rax]
	cmp	dh, 10
	jnz	$_054
	cmp	ax, 48
	jnz	$_054
	cmp	dword ptr [rbx+0x4], 1
	jc	$_052
	cmp	dword ptr [rbx+0x4], 24
	jbe	$_053
$_052:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_054
	cmp	dword ptr [rbx+0x4], 91
	jc	$_054
	cmp	dword ptr [rbx+0x4], 130
	ja	$_054
$_053:	mov	r9, qword ptr [rbx+0x8]
	mov	r8, qword ptr [rbx+0x8]
	lea	rdx, [DS0008+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_055

$_054:	mov	r9, rcx
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0007+rip]
	mov	rcx, rdi
	call	$_020
$_055:	jmp	$_070

$_056:	cmp	dh, 61
	jne	$_069
	mov	byte ptr [rax], 0
	mov	r9, rcx
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0009+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_057:	cmp	dh, 61
	jne	$_069
	mov	byte ptr [rax], 0
	mov	r9, rcx
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0007+rip]
	mov	rcx, rdi
	call	$_020
	xor	r9d, r9d
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0003+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_058:	cmp	dh, 61
	jne	$_069
	mov	byte ptr [rax], 0
	mov	r9, rcx
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0008+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_059:	cmp	byte ptr [rsi+0x19], 45
	jne	$_069
	mov	byte ptr [rax], 0
	mov	r9, qword ptr [rsi+0x40]
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS000A+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_060:	shr	edx, 8
	cmp	dl, 62
	jne	$_069
	cmp	dh, 61
	jne	$_069
	mov	byte ptr [rax], 0
	mov	r9, rcx
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS000B+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_061:	shr	edx, 8
	cmp	dl, 60
	jne	$_069
	cmp	dh, 61
	jne	$_069
	mov	byte ptr [rax], 0
	mov	r9, rcx
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS000C+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_062:	cmp	dh, 43
	jnz	$_063
	mov	byte ptr [rax], 0
	xor	r9d, r9d
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0005+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

	jmp	$_064

$_063:	cmp	byte ptr [rsi+0x19], 45
	jnz	$_064
	mov	byte ptr [rax], 0
	mov	r9, qword ptr [rsi+0x40]
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS000D+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_064:	jmp	$_069

$_065:	cmp	dh, 45
	jnz	$_066
	mov	byte ptr [rax], 0
	xor	r9d, r9d
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS0004+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

	jmp	$_067

$_066:	cmp	byte ptr [rsi+0x19], 45
	jnz	$_067
	mov	byte ptr [rax], 0
	mov	r9, qword ptr [rsi+0x40]
	mov	r8, qword ptr [rbx+0x10]
	lea	rdx, [DS000E+rip]
	mov	rcx, rdi
	call	$_020
	jmp	$_070

$_067:	jmp	$_069

$_068:	cmp	dl, 61
	je	$_049
	cmp	dl, 124
	je	$_056
	cmp	dl, 126
	je	$_057
	cmp	dl, 94
	je	$_058
	cmp	dl, 38
	je	$_059
	cmp	dl, 62
	je	$_060
	cmp	dl, 60
	je	$_061
	cmp	dl, 43
	je	$_062
	cmp	dl, 45
	je	$_065
$_069:	mov	rdx, qword ptr [rsi+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	xor	eax, eax
$_070:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_071:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 4136
	mov	rdi, rdx
	lea	rsi, [rbp-0x800]
	jmp	$_074

$_072:	mov	rbx, rcx
	mov	rdi, rdx
	mov	rdx, rdi
	lea	rcx, [rbp-0x1000]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x38]
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	r8, qword ptr [rbp+0x38]
	xor	edx, edx
	mov	rcx, rsi
	call	ExpandHllProc@PLT
	cmp	eax, -1
	jz	$_075
	cmp	byte ptr [rsi], 0
	jz	$_073
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcat@PLT
	lea	rdx, [DS0002+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	byte ptr [rsi], 0
$_073:	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, rsi
	call	$_025
	test	rax, rax
	jz	$_075
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcat@PLT
	lea	rdx, [DS0002+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdi, rbx
$_074:	mov	rcx, rdi
	call	$_004
	test	rax, rax
	jne	$_072
$_075:	mov	rax, qword ptr [rbp+0x28]
	movzx	eax, byte ptr [rax]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ForDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 6232
	mov	dword ptr [rbp-0x4], 0
	mov	rbx, rdx
	lea	rdi, [rbp-0x828]
	imul	eax, dword ptr [rbp+0x28], 24
	mov	eax, dword ptr [rbx+rax+0x4]
	mov	dword ptr [rbp-0x8], eax
	inc	dword ptr [rbp+0x28]
	cmp	eax, 400
	jne	$_082
	mov	rsi, qword ptr [ModuleInfo+0xF8+rip]
	test	rsi, rsi
	jnz	$_076
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_099

$_076:	mov	rdx, qword ptr [rsi]
	mov	rcx, qword ptr [ModuleInfo+0x100+rip]
	mov	qword ptr [ModuleInfo+0xF8+rip], rdx
	mov	qword ptr [rsi], rcx
	mov	qword ptr [ModuleInfo+0x100+rip], rsi
	cmp	dword ptr [rsi+0x28], 6
	jz	$_077
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_099

$_077:	mov	eax, dword ptr [rsi+0x10]
	test	eax, eax
	jz	$_078
	mov	rdx, rdi
	mov	ecx, eax
	call	GetLabelStr@PLT
	lea	r8, [DS0010+rip]
	mov	rdx, rax
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
$_078:	cmp	qword ptr [rsi+0x20], 0
	jz	$_079
	mov	rcx, qword ptr [rsi+0x20]
	call	AddLineQueue@PLT
$_079:	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr@PLT
	mov	rdx, rax
	lea	rcx, [DS0011+rip]
	call	AddLineQueueX@PLT
	mov	eax, dword ptr [rsi+0x14]
	test	eax, eax
	jz	$_080
	mov	rdx, rdi
	mov	ecx, eax
	call	GetLabelStr@PLT
	lea	r8, [DS0010+rip]
	mov	rdx, rax
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
$_080:	imul	eax, dword ptr [rbp+0x28], 24
	add	rbx, rax
	cmp	byte ptr [rbx], 0
	jz	$_081
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_081
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], eax
$_081:	jmp	$_096

$_082:	mov	rsi, qword ptr [ModuleInfo+0x100+rip]
	test	rsi, rsi
	jnz	$_083
	mov	ecx, 56
	call	LclAlloc@PLT
	mov	rsi, rax
$_083:	mov	rcx, qword ptr [rbp+0x30]
	call	ExpandCStrings@PLT
	xor	eax, eax
	mov	dword ptr [rsi+0x14], eax
	cmp	dword ptr [rbp-0x8], 399
	jnz	$_084
	or	eax, 0x80000
$_084:	mov	dword ptr [rsi+0x2C], eax
	mov	dword ptr [rsi+0x28], 6
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x18], eax
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x10], eax
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
	imul	eax, dword ptr [rbp+0x28], 24
	add	rbx, rax
	cmp	byte ptr [rbx], 40
	jnz	$_085
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_085:	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	edx, 58
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_086
	mov	ecx, 2206
	call	asmerr@PLT
	jmp	$_099

$_086:	cmp	byte ptr [rax+0x1], 39
	jnz	$_087
	mov	edx, 58
	lea	rcx, [rax+0x1]
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_087
	mov	ecx, 2206
	call	asmerr@PLT
	jmp	$_099

$_087:	mov	byte ptr [rax], 0
	inc	rax
	mov	rcx, rax
	call	tstrstart@PLT
	mov	qword ptr [rbp-0x10], rax
	mov	edx, 58
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_088
	mov	ecx, 2206
	call	asmerr@PLT
	jmp	$_099

$_088:	mov	byte ptr [rax], 0
	inc	rax
	mov	rcx, rax
	call	tstrstart@PLT
	mov	qword ptr [rbp-0x18], rax
	mov	rcx, rax
	call	$_001
	mov	rcx, rdi
	call	tstrstart@PLT
	mov	rdi, rax
	mov	rcx, rdi
	call	$_001
	mov	rcx, qword ptr [rbp-0x10]
	call	$_001
	cmp	byte ptr [rbx-0x18], 40
	jnz	$_089
	mov	edx, 41
	mov	rcx, qword ptr [rbp-0x18]
	call	tstrrchr@PLT
	test	rax, rax
	jz	$_089
	mov	byte ptr [rax], 0
	mov	rcx, qword ptr [rbp-0x18]
	call	$_001
$_089:	lea	rbx, [rbp-0x1028]
	mov	byte ptr [rbx], 0
	mov	r8, qword ptr [rbp+0x30]
	mov	rdx, rdi
	mov	rcx, rbx
	call	$_071
	test	rax, rax
	jz	$_090
	mov	rcx, rbx
	call	AddLineQueue@PLT
$_090:	lea	rdx, [rbp-0x28]
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr@PLT
	lea	r8, [DS0010+rip]
	mov	rdx, rax
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
	mov	byte ptr [rbx], 0
	mov	qword ptr [rsi+0x20], 0
	mov	r8, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbp-0x18]
	mov	rcx, rbx
	call	$_071
	test	rax, rax
	jz	$_091
	mov	rcx, rbx
	call	LclDup@PLT
	mov	qword ptr [rsi+0x20], rax
$_091:	mov	rdi, qword ptr [rbp-0x10]
	mov	byte ptr [rbx], 0
	jmp	$_094

$_092:	mov	qword ptr [rbp-0x18], rcx
	mov	rdi, rdx
	lea	rdx, [DS0012+rip]
	lea	rcx, [rbp-0x1828]
	call	tstrcpy@PLT
	mov	rdx, rdi
	mov	rcx, rax
	call	tstrcat@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	dword ptr [rbp+0x28], 1
	mov	qword ptr [rsp+0x28], rbx
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	EvaluateHllExpression@PLT
	mov	dword ptr [rbp-0x4], eax
	test	eax, eax
	jnz	$_093
	mov	rcx, rbx
	call	AddLineQueue@PLT
$_093:	mov	rdi, qword ptr [rbp-0x18]
$_094:	mov	rcx, rdi
	call	$_004
	test	rax, rax
	jne	$_092
	cmp	rsi, qword ptr [ModuleInfo+0x100+rip]
	jnz	$_095
	mov	rax, qword ptr [rsi]
	mov	qword ptr [ModuleInfo+0x100+rip], rax
$_095:	mov	rax, qword ptr [ModuleInfo+0xF8+rip]
	mov	qword ptr [rsi], rax
	mov	qword ptr [ModuleInfo+0xF8+rip], rsi
$_096:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_097
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_097:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_098
	call	RunLineQueue@PLT
$_098:	mov	eax, dword ptr [rbp-0x4]
$_099:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x20, 0x00

DS0001:
	.byte  0x2C, 0x00

DS0002:
	.byte  0x0A, 0x00

DS0003:
	.byte  0x6E, 0x6F, 0x74, 0x00

DS0004:
	.byte  0x64, 0x65, 0x63, 0x00

DS0005:
	.byte  0x69, 0x6E, 0x63, 0x00

DS0006:
	.byte  0x6C, 0x65, 0x61, 0x00

DS0007:
	.byte  0x6D, 0x6F, 0x76, 0x00

DS0008:
	.byte  0x78, 0x6F, 0x72, 0x00

DS0009:
	.byte  0x6F, 0x72, 0x20, 0x00

DS000A:
	.byte  0x61, 0x6E, 0x64, 0x00

DS000B:
	.byte  0x73, 0x68, 0x72, 0x00

DS000C:
	.byte  0x73, 0x68, 0x6C, 0x00

DS000D:
	.byte  0x61, 0x64, 0x64, 0x00

DS000E:
	.byte  0x73, 0x75, 0x62, 0x00

DS000F:
	.byte  0x25, 0x73, 0x25, 0x73, 0x00

DS0010:
	.byte  0x3A, 0x00

DS0011:
	.byte  0x6A, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x00

DS0012:
	.byte  0x2E, 0x69, 0x66, 0x20, 0x00


.att_syntax prefix
