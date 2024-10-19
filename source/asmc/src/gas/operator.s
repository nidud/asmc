
.intel_syntax noprefix

.global GetOperator
.global GetOpType
.global OperatorParam
.global ProcessOperator
.global EvalOperator
.global ParseOperator

.extern StoreState
.extern GetQualifiedType
.extern InsertLineQueue
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern LclAlloc
.extern GetResWName
.extern EvalOperand
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tsprintf
.extern GetType
.extern asmerr
.extern ModuleInfo
.extern SymFind


.SECTION .text
	.ALIGN	16

GetOperator:
	mov	rdx, rcx
	mov	ecx, 24
	mov	rax, qword ptr [rdx+0x10]
	mov	eax, dword ptr [rax]
	jmp	$_017

$_001:	cmp	ah, 43
	jz	$_002
	mov	eax, 581
	jmp	$_019

$_002:	add	ecx, 24
	mov	eax, 675
	jmp	$_019

$_003:	cmp	ah, 45
	jz	$_004
	mov	eax, 586
	jmp	$_019

$_004:	add	ecx, 24
	mov	eax, 676
	jmp	$_019

$_005:	cmp	ah, 61
	jz	$_006
	mov	eax, 523
	jmp	$_019

$_006:	add	ecx, 24
	mov	eax, 588
	jmp	$_019

	jmp	$_018

$_007:	cmp	ah, 126
	jz	$_008
	mov	eax, 585
	jmp	$_019

$_008:	add	ecx, 24
	mov	eax, 1582
	jmp	$_019

$_009:	mov	eax, 582
	jmp	$_019

$_010:	mov	eax, 587
	jmp	$_019

$_011:	mov	eax, 655
	jmp	$_019

$_012:	mov	eax, 653
	jmp	$_019

$_013:	cmp	ah, 60
	jnz	$_018
	mov	eax, 595
	jmp	$_019

$_014:	cmp	ah, 62
	jnz	$_018
	mov	eax, 596
	jmp	$_019

$_015:	mov	eax, 657
	jmp	$_019

$_016:	mov	eax, 269
	jmp	$_019

	jmp	$_018

$_017:	cmp	al, 43
	je	$_001
	cmp	al, 45
	je	$_003
	cmp	al, 61
	je	$_005
	cmp	al, 38
	jz	$_007
	cmp	al, 124
	jz	$_009
	cmp	al, 94
	jz	$_010
	cmp	al, 42
	jz	$_011
	cmp	al, 47
	jz	$_012
	cmp	al, 60
	jz	$_013
	cmp	al, 62
	jz	$_014
	cmp	al, 126
	jz	$_015
	cmp	al, 37
	jz	$_016
$_018:	xor	eax, eax
$_019:	ret

GetOpType:
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rcx, rbx
	call	GetOperator
	test	rax, rax
	jnz	$_020
	mov	rax, -1
	jmp	$_021

$_020:	add	rbx, rcx
	mov	rdx, qword ptr [rbp+0x20]
	mov	ecx, eax
	call	GetResWName@PLT
	mov	rax, rbx
$_021:	leave
	pop	rbx
	ret

OperatorParam:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rbx, rcx
	lea	rdx, [DS0000+rip]
	mov	rcx, qword ptr [rbp+0x30]
	call	tstrcat@PLT
	mov	rdi, rax
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	jmp	$_023

$_022:	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	add	rbx, 24
$_023:	cmp	byte ptr [rbx], 5
	jnz	$_024
	cmp	dword ptr [rbx+0x4], 270
	jz	$_022
$_024:	cmp	byte ptr [rbx], 6
	jnz	$_025
	mov	rdx, rdi
	mov	ecx, dword ptr [rbx+0x4]
	call	GetResWName@PLT
	jmp	$_030

$_025:	cmp	byte ptr [rbx], 8
	jne	$_030
	mov	rcx, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rcx]
	or	eax, 0x202020
	cmp	eax, 7561825
	jnz	$_026
	lea	rdx, [DS0001+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	jmp	$_030

$_026:	mov	dword ptr [rbp-0x4], 0
	xor	eax, eax
	mov	qword ptr [rbp-0x20], rax
	mov	qword ptr [rbp-0x18], rax
	mov	qword ptr [rbp-0x10], rax
	lea	r8, [rbp-0x20]
	mov	rdx, rbx
	lea	rcx, [rbp-0x4]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	jz	$_030
	cmp	byte ptr [rbp-0x10], -61
	jnz	$_029
	jmp	$_028

$_027:	mov	rdx, rdi
	mov	ecx, 270
	call	GetResWName@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	dec	byte ptr [rbp-0xF]
$_028:	cmp	byte ptr [rbp-0xF], 0
	jnz	$_027
$_029:	mov	rsi, qword ptr [rbp-0x18]
	test	rsi, rsi
	jz	$_030
	cmp	byte ptr [rsi+0x18], 7
	jnz	$_030
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rdi
	call	tstrcat@PLT
$_030:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_031:
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rbx
$_032:	cmp	byte ptr [rbx], 0
	jz	$_041
	cmp	byte ptr [rbx], 40
	jnz	$_036
	add	rbx, 24
	mov	edx, 1
$_033:	cmp	byte ptr [rbx], 0
	jz	$_036
	cmp	byte ptr [rbx], 40
	jnz	$_034
	inc	edx
	jmp	$_035

$_034:	cmp	byte ptr [rbx], 41
	jnz	$_035
	dec	edx
	jz	$_036
$_035:	add	rbx, 24
	jmp	$_033

$_036:	cmp	byte ptr [rbx], 91
	jnz	$_040
	add	rbx, 24
	mov	edx, 1
$_037:	cmp	byte ptr [rbx], 0
	jz	$_040
	cmp	byte ptr [rbx], 91
	jnz	$_038
	inc	edx
	jmp	$_039

$_038:	cmp	byte ptr [rbx], 93
	jnz	$_039
	dec	edx
	jz	$_040
$_039:	add	rbx, 24
	jmp	$_037

$_040:	mov	rcx, rbx
	call	GetOperator
	test	rax, rax
	jnz	$_041
	add	rbx, 24
	jmp	$_032

$_041:
	mov	rax, rbx
	sub	rax, rsi
	mov	ecx, 24
	xor	edx, edx
	div	ecx
	leave
	pop	rbx
	pop	rsi
	ret

ProcessOperator:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 456
	mov	byte ptr [rbp-0x11], 0
	mov	dword ptr [rbp-0x18], 0
	mov	rbx, rcx
	cmp	dword ptr [StoreState+rip], 0
	jnz	$_042
	xor	eax, eax
	jmp	$_074

$_042:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_043
	call	RunLineQueue@PLT
$_043:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x10], rax
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jz	$_045
	cmp	byte ptr [rax+0x19], -60
	jnz	$_044
	mov	rax, qword ptr [rax+0x20]
$_044:	cmp	byte ptr [rax+0x19], -61
	jnz	$_045
	inc	byte ptr [rbp-0x11]
	mov	rax, qword ptr [rax+0x40]
$_045:	test	rax, rax
	jz	$_050
	test	byte ptr [rax+0x16], 0x01
	jz	$_050
	test	byte ptr [rax+0x16], 0xFFFFFF80
	jz	$_050
	mov	qword ptr [rbp-0x8], rax
	movzx	edx, word ptr [rax+0x4A]
	movzx	eax, word ptr [rax+0x48]
	test	eax, eax
	jnz	$_046
	mov	eax, dword ptr [ModuleInfo+0x340+rip]
$_046:	test	edx, edx
	jnz	$_048
	mov	edx, 210
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_047
	mov	edx, 214
$_047:	jmp	$_049

$_048:	inc	byte ptr [rbp-0x11]
$_049:	mov	dword ptr [rbp-0x18], eax
	mov	dword ptr [rbp-0x1C], edx
	jmp	$_051

$_050:	mov	rdx, qword ptr [rbp-0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_074

$_051:	add	rbx, 24
$_052:	lea	rdi, [rbp-0x9C]
	mov	rcx, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rcx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdx, [DS0000+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	mov	rdx, rdi
	mov	rcx, rbx
	call	GetOpType
	cmp	eax, -1
	je	$_072
	mov	rbx, rax
	lea	rsi, [rbp-0x11C]
	mov	byte ptr [rsi], 0
	cmp	byte ptr [rbp-0x11], 0
	jnz	$_053
	lea	rdx, [DS0002+rip]
	mov	rcx, rsi
	call	tstrcpy@PLT
$_053:	cmp	qword ptr [rbp-0x10], 0
	jz	$_054
	mov	rdx, qword ptr [rbp-0x10]
	mov	rcx, rsi
	call	tstrcat@PLT
	jmp	$_055

$_054:	mov	rcx, rsi
	call	tstrlen@PLT
	add	rax, rsi
	mov	r8d, dword ptr [rbp-0x18]
	lea	rdx, [DS0003+rip]
	mov	rcx, rax
	call	tsprintf@PLT
$_055:	cmp	dword ptr [rbp-0x18], 0
	jz	$_056
	mov	qword ptr [rbp-0x10], 0
$_056:	mov	rcx, rbx
	call	$_031
	test	rax, rax
	je	$_071
	mov	dword ptr [rbp-0x120], eax
	mov	rax, rbx
	sub	rax, qword ptr [rbp+0x28]
	mov	ecx, 24
	xor	edx, edx
	div	ecx
	mov	dword ptr [rbp-0x124], eax
	add	dword ptr [rbp-0x120], eax
	lea	rdx, [DS0004+rip]
	mov	rcx, rsi
	call	tstrcat@PLT
	mov	rdi, rsi
	mov	rsi, qword ptr [rbx+0x10]
	imul	ebx, dword ptr [rbp-0x120], 24
	add	rbx, qword ptr [rbp+0x28]
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	mov	rcx, qword ptr [rbx+0x10]
	sub	rcx, rsi
	rep movsb
	mov	byte ptr [rdi], 0
	lea	rdi, [rbp-0x9C]
	jmp	$_070

$_057:	mov	dword ptr [rbp-0x194], 0
	lea	rdx, [DS0000+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	imul	ecx, dword ptr [rbp-0x124], 24
	add	rcx, qword ptr [rbp+0x28]
	mov	rax, qword ptr [rcx+0x8]
	test	rax, rax
	jz	$_058
	mov	eax, dword ptr [rax]
$_058:	cmp	ax, 76
	jnz	$_059
	cmp	byte ptr [rcx+0x18], 9
	jnz	$_059
	lea	rdx, [DS0005+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	add	dword ptr [rbp-0x124], 2
	jmp	$_069

$_059:	test	byte ptr [rcx+0x2], 0x08
	jz	$_062
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_060
	lea	rdx, [DS0006+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	jmp	$_061

$_060:	lea	rdx, [DS0007+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_061:	mov	eax, dword ptr [rbp-0x120]
	mov	dword ptr [rbp-0x124], eax
	jmp	$_069

$_062:	cmp	byte ptr [rcx], 7
	jnz	$_063
	cmp	dword ptr [rcx+0x4], 273
	jnz	$_063
	inc	dword ptr [rbp-0x124]
	inc	dword ptr [rbp-0x194]
$_063:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x190]
	mov	r8d, dword ptr [rbp-0x120]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x124]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_074
	cmp	dword ptr [rbp-0x154], 0
	jnz	$_068
	mov	rcx, qword ptr [rbp-0x180]
	test	rcx, rcx
	jz	$_066
	cmp	byte ptr [rcx], 9
	jnz	$_066
	test	byte ptr [ModuleInfo+0x334+rip], 0x02
	jz	$_064
	lea	rdx, [DS0005+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	jmp	$_065

$_064:	lea	rdx, [DS0008+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_065:	jmp	$_067

$_066:	lea	rdx, [DS0001+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_067:	jmp	$_069

$_068:	mov	r9d, dword ptr [rbp-0x194]
	mov	r8, rdi
	lea	rdx, [rbp-0x190]
	mov	rcx, rdi
	call	GetType@PLT
$_069:	imul	ecx, dword ptr [rbp-0x124], 24
	add	rcx, qword ptr [rbp+0x28]
	cmp	byte ptr [rcx], 44
	jnz	$_070
	inc	dword ptr [rbp-0x124]
$_070:	mov	eax, dword ptr [rbp-0x120]
	cmp	dword ptr [rbp-0x124], eax
	jl	$_057
	lea	r8, [rbp-0x11C]
	lea	rdx, [rbp-0x9C]
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
$_071:	jmp	$_052

$_072:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_073
	call	InsertLineQueue@PLT
$_073:	xor	eax, eax
$_074:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

EvalOperator:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdx, qword ptr [ModuleInfo+0x180+rip]
	cmp	byte ptr [rdx], 8
	jnz	$_075
	cmp	byte ptr [rdx+0x18], 3
	jnz	$_075
	cmp	dword ptr [rdx+0x1C], 523
	jz	$_076
$_075:	mov	rax, -1
	jmp	$_093

$_076:	mov	rcx, qword ptr [rdx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jnz	$_077
	mov	rax, -1
	jmp	$_093

$_077:	cmp	byte ptr [rax+0x19], -60
	jnz	$_078
	mov	rax, qword ptr [rax+0x20]
$_078:	cmp	byte ptr [rax+0x19], -61
	jnz	$_079
	mov	rax, qword ptr [rax+0x40]
$_079:	test	rax, rax
	jz	$_080
	test	byte ptr [rax+0x16], 0xFFFFFF80
	jnz	$_081
$_080:	mov	rax, -1
	jmp	$_093

$_081:	mov	rsi, qword ptr [rbp+0x28]
	mov	rcx, qword ptr [rsi+0x60]
	mov	rax, qword ptr [rsi+0x50]
	test	rcx, rcx
	jnz	$_084
	test	rax, rax
	jz	$_084
	cmp	byte ptr [rax+0x19], -60
	jnz	$_082
	mov	rax, qword ptr [rax+0x20]
$_082:	cmp	byte ptr [rax+0x19], -61
	jnz	$_083
	mov	rax, qword ptr [rax+0x40]
$_083:	mov	rcx, rax
$_084:	test	rcx, rcx
	jz	$_085
	test	byte ptr [rcx+0x16], 0xFFFFFF80
	jnz	$_086
$_085:	cmp	dword ptr [rsi+0x3C], 2
	jz	$_086
	mov	rax, -1
	jmp	$_093

$_086:	mov	qword ptr [rsi+0x60], rcx
	mov	ecx, 224
	call	LclAlloc@PLT
	mov	rbx, rax
	mov	qword ptr [rbx], 0
	mov	rcx, qword ptr [rbp+0x38]
	call	GetOperator
	mov	dword ptr [rbx+0xD8], eax
	test	rax, rax
	jnz	$_087
	mov	rax, -1
	jmp	$_093

$_087:	mov	rdx, qword ptr [rbp+0x30]
	mov	rax, qword ptr [rdx+0x48]
	test	rax, rax
	jz	$_088
	cmp	qword ptr [rsi+0x48], 0
	jnz	$_088
	mov	qword ptr [rsi+0x48], rax
	mov	qword ptr [rdx+0x48], 0
$_088:	lea	rdi, [rbx+0x8]
	mov	rcx, 104
	rep movsb
	mov	rsi, rdx
	mov	rcx, 104
	rep movsb
	mov	rsi, qword ptr [rbp+0x28]
	mov	rax, rbx
	cmp	qword ptr [rsi+0x48], 0
	jz	$_091
	mov	rbx, qword ptr [rsi+0x48]
	jmp	$_090

$_089:	mov	rbx, qword ptr [rbx]
$_090:	cmp	qword ptr [rbx], 0
	jnz	$_089
	mov	qword ptr [rbx], rax
	jmp	$_092

$_091:	mov	qword ptr [rsi+0x48], rax
$_092:	xor	eax, eax
$_093:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_094:
	push	rsi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	jmp	$_100

$_095:	mov	rcx, qword ptr [rsi+0x10]
	mov	rdx, qword ptr [rcx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	jmp	$_101

$_096:	mov	r8d, dword ptr [rsi]
	lea	rdx, [DS000A+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	jmp	$_101

$_097:	mov	rcx, qword ptr [rsi+0x50]
	test	rcx, rcx
	jz	$_098
	mov	rdx, qword ptr [rcx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
$_098:	jmp	$_101

$_099:	mov	rdx, qword ptr [rsi+0x18]
	mov	r8d, dword ptr [rdx+0x4]
	lea	rdx, [DS0003+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	jmp	$_101

$_100:	cmp	dword ptr [rsi+0x3C], 3
	jz	$_095
	cmp	dword ptr [rsi+0x3C], 0
	jz	$_096
	cmp	dword ptr [rsi+0x3C], 1
	jz	$_097
	cmp	dword ptr [rsi+0x3C], 2
	jz	$_099
$_101:	leave
	pop	rsi
	ret

ParseOperator:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 312
	mov	dword ptr [rbp-0x104], 0
	mov	rbx, rdx
	jmp	$_103

$_102:	mov	rbx, qword ptr [rbx]
$_103:	cmp	qword ptr [rbx], 0
	jnz	$_102
	mov	dword ptr [rbp-0x104], eax
	mov	rcx, qword ptr [rbx+0x68]
	mov	rax, qword ptr [rcx+0x8]
	mov	qword ptr [rbp-0x110], rax
	movzx	eax, word ptr [rcx+0x48]
	movzx	edx, word ptr [rcx+0x4A]
	test	eax, eax
	jnz	$_104
	mov	eax, dword ptr [ModuleInfo+0x340+rip]
$_104:	test	edx, edx
	jnz	$_105
	mov	edx, 210
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_105
	mov	edx, 214
$_105:	mov	dword ptr [rbp-0x114], eax
	mov	dword ptr [rbp-0x118], edx
	mov	rbx, qword ptr [rbp+0x30]
$_106:	test	rbx, rbx
	je	$_124
	lea	rdi, [rbp-0x100]
	mov	r9d, dword ptr [rbx+0xD8]
	mov	r8, qword ptr [rbp-0x110]
	lea	rdx, [DS000B+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	jmp	$_113

$_107:	mov	rcx, qword ptr [rbx+0x80]
	test	rcx, rcx
	jz	$_110
	cmp	byte ptr [rcx], 9
	jnz	$_110
	test	byte ptr [ModuleInfo+0x334+rip], 0x02
	jz	$_108
	lea	rdx, [DS0005+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	jmp	$_109

$_108:	lea	rdx, [DS0008+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_109:	jmp	$_111

$_110:	lea	rdx, [DS0001+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_111:	jmp	$_114

$_112:	xor	r9d, r9d
	mov	r8, rdi
	lea	rdx, [rbx+0x70]
	mov	rcx, rdi
	call	GetType@PLT
	jmp	$_114

$_113:	cmp	dword ptr [rbx+0xAC], 3
	jz	$_107
	cmp	dword ptr [rbx+0xAC], 0
	jz	$_107
	jmp	$_112

$_114:	lea	rdx, [DS000C+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	mov	rcx, qword ptr [rbx+0x30]
	test	rcx, rcx
	jnz	$_115
	mov	rcx, qword ptr [rbx+0x20]
$_115:	mov	rdx, qword ptr [rbx+0x98]
	test	rdx, rdx
	jnz	$_116
	mov	rdx, qword ptr [rbx+0x88]
$_116:	test	rcx, rcx
	jz	$_118
	test	byte ptr [rcx+0x2], 0x20
	jz	$_118
	test	rdx, rdx
	jz	$_117
	or	byte ptr [rdx+0x2], 0x20
$_117:	mov	r8d, dword ptr [rbp-0x114]
	lea	rdx, [DS000D+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, rax
	lea	rcx, [rbx+0x70]
	call	$_094
	jmp	$_123

$_118:	test	rdx, rdx
	jz	$_120
	test	byte ptr [rdx+0x2], 0x20
	jz	$_120
	test	rcx, rcx
	jz	$_119
	or	byte ptr [rcx+0x2], 0x20
$_119:	lea	rcx, [rbx+0x8]
	call	$_094
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	mov	r8d, dword ptr [rbp-0x114]
	lea	rdx, [DS000E+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	jmp	$_123

$_120:	test	rdx, rdx
	jz	$_121
	or	byte ptr [rdx+0x2], 0x20
$_121:	test	rcx, rcx
	jz	$_122
	or	byte ptr [rcx+0x2], 0x20
$_122:	lea	rcx, [rbx+0x8]
	call	$_094
	lea	rdx, [DS000D+0x2+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	lea	rcx, [rbx+0x70]
	call	$_094
$_123:	lea	rdx, [DS0009+0x5+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rcx, [rbp-0x100]
	call	AddLineQueue@PLT
	mov	rbx, qword ptr [rbx]
	inc	dword ptr [rbp-0x104]
	jmp	$_106

$_124:
	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_125
	call	RunLineQueue@PLT
$_125:	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x5F, 0x00

DS0001:
	.byte  0x61, 0x62, 0x73, 0x00

DS0002:
	.byte  0x61, 0x64, 0x64, 0x72, 0x20, 0x00

DS0003:
	.byte  0x25, 0x72, 0x00

DS0004:
	.byte  0x2C, 0x20, 0x00

DS0005:
	.byte  0x70, 0x74, 0x72, 0x77, 0x6F, 0x72, 0x64, 0x00

DS0006:
	.byte  0x71, 0x77, 0x6F, 0x72, 0x64, 0x00

DS0007:
	.byte  0x64, 0x77, 0x6F, 0x72, 0x64, 0x00

DS0008:
	.byte  0x70, 0x74, 0x72, 0x73, 0x62, 0x79, 0x74, 0x65
	.byte  0x00

DS0009:
	.byte  0x25, 0x73, 0x28, 0x25, 0x73, 0x29, 0x00

DS000A:
	.byte  0x25, 0x64, 0x00

DS000B:
	.byte  0x25, 0x73, 0x5F, 0x25, 0x72, 0x5F, 0x00

DS000C:
	.byte  0x28, 0x00

DS000D:
	.byte  0x25, 0x72, 0x2C, 0x20, 0x00

DS000E:
	.byte  0x2C, 0x20, 0x25, 0x72, 0x00


.att_syntax prefix
