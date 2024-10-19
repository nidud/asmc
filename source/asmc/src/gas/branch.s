
.intel_syntax noprefix

.global process_branch

.extern SegOverride
.extern segm_override
.extern GetOverrideAssume
.extern GetCurrOffset
.extern GetSymOfssize
.extern set_frame
.extern optable_idx
.extern InstrTable
.extern CreateFixup
.extern OutputByte
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

$_001:	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	mov	ebx, edx
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_002
	mov	ecx, 6003
	call	asmerr@PLT
$_002:	mov	al, byte ptr [rsi+0x63]
	test	ebx, ebx
	jz	$_006
	cmp	byte ptr [rsi+0xA], 0
	jz	$_004
	mov	ebx, 8
	test	al, al
	jz	$_003
	mov	ebx, 6
$_003:	jmp	$_005

$_004:	mov	ebx, 5
	test	al, al
	jz	$_005
	mov	ebx, 7
$_005:	jmp	$_007

$_006:	mov	ebx, 3
	test	al, al
	jz	$_007
	mov	ebx, 5
$_007:	mov	rdx, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rdx+0x6]
	xor	eax, 0x01
	mov	ecx, eax
	call	OutputByte@PLT
	mov	ecx, ebx
	call	OutputByte@PLT
	mov	word ptr [rsi+0xE], 532
	movzx	eax, word ptr [optable_idx+0x2+rip]
	lea	rdx, [InstrTable+rip]
	lea	rax, [rdx+rax*8]
	mov	qword ptr [rsi+0x58], rax
	leave
	pop	rbx
	pop	rsi
	ret

$_008:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_009
	mov	ecx, 7003
	call	asmerr@PLT
$_009:	mov	ecx, 14
	call	OutputByte@PLT
	mov	rcx, qword ptr [rbp+0x10]
	mov	byte ptr [rcx+0x60], -127
	leave
	ret

process_branch:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rsi, rcx
	mov	rbx, r8
	movzx	eax, word ptr [rsi+0xE]
	sub	eax, 531
	lea	rcx, [optable_idx+rip]
	movzx	eax, word ptr [rcx+rax*2]
	mov	dword ptr [rbp-0x24], eax
	cmp	dword ptr [rbp+0x30], 0
	jz	$_010
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_121

$_010:	test	byte ptr [rbx+0x43], 0x02
	jz	$_011
	cmp	dword ptr [rbx+0x38], 253
	jz	$_011
	mov	al, byte ptr [rbx+0x40]
	mov	byte ptr [rsi+0x60], al
$_011:	cmp	qword ptr [rbx+0x30], 0
	jz	$_013
	xor	edx, edx
	mov	rcx, rbx
	call	segm_override@PLT
	mov	rcx, qword ptr [rbx+0x50]
	mov	rax, qword ptr [SegOverride+rip]
	test	rax, rax
	jz	$_013
	test	rcx, rcx
	jz	$_013
	cmp	qword ptr [rcx+0x30], 0
	jz	$_013
	mov	rdx, qword ptr [rcx+0x30]
	mov	rdx, qword ptr [rdx+0x68]
	mov	rdx, qword ptr [rdx]
	cmp	rax, qword ptr [rcx+0x30]
	jz	$_012
	cmp	rax, rdx
	jz	$_012
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2074
	call	asmerr@PLT
	jmp	$_121

$_012:	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdx, qword ptr [rcx+0x68]
	mov	rdx, qword ptr [rdx]
	cmp	rax, rcx
	jz	$_013
	cmp	rax, rdx
	jz	$_013
	mov	byte ptr [rsi+0x60], -126
$_013:	mov	eax, dword ptr [rbx]
	mov	dword ptr [rsi+0x20], eax
	mov	dword ptr [rsi+0x24], 0
	mov	rdi, qword ptr [rbx+0x50]
	test	rdi, rdi
	jnz	$_014
	mov	ecx, 2076
	call	asmerr@PLT
	jmp	$_121

$_014:	movzx	eax, byte ptr [rdi+0x18]
	mov	dword ptr [rbp-0x10], eax
	call	GetCurrOffset@PLT
	mov	dword ptr [rbp-0x4], eax
	cmp	dword ptr [rbp-0x10], 2
	jnz	$_015
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_015
	mov	dword ptr [rbp-0x10], 0
$_015:	cmp	dword ptr [rbp-0x10], 1
	jz	$_016
	cmp	dword ptr [rbp-0x10], 2
	jne	$_026
$_016:	mov	eax, dword ptr [Parse_Pass+rip]
	and	eax, 0xFF
	mov	ecx, dword ptr [rbp-0x4]
	cmp	dword ptr [rbp-0x10], 1
	jnz	$_017
	cmp	byte ptr [rdi+0x3A], al
	jz	$_017
	cmp	dword ptr [rdi+0x28], ecx
	jge	$_017
	jmp	$_018

$_017:	mov	eax, dword ptr [rdi+0x28]
	mov	dword ptr [rbp-0x4], eax
$_018:	mov	rax, qword ptr [rdi+0x30]
	mov	qword ptr [rbp-0x20], rax
	test	rax, rax
	jz	$_019
	cmp	rax, qword ptr [ModuleInfo+0x1F8+rip]
	je	$_025
$_019:	test	rax, rax
	jz	$_020
	mov	rcx, qword ptr [rax+0x68]
$_020:	mov	dl, byte ptr [ModuleInfo+0x1CC+rip]
	cmp	qword ptr [ModuleInfo+0x200+rip], 0
	jz	$_022
	test	rax, rax
	jz	$_021
	cmp	byte ptr [rcx+0x68], dl
	jnz	$_022
$_021:	jmp	$_024

$_022:	test	rax, rax
	jz	$_024
	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jz	$_024
	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdx, qword ptr [rax+0x68]
	mov	rax, qword ptr [rcx]
	test	rax, rax
	jz	$_023
	cmp	rax, qword ptr [rdx]
	jnz	$_023
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	cmp	byte ptr [rcx+0x68], al
	jnz	$_023
	jmp	$_024

$_023:	cmp	byte ptr [rbx+0x40], -127
	jnz	$_024
	cmp	qword ptr [SegOverride+rip], 0
	jnz	$_024
	mov	ecx, 2107
	call	asmerr@PLT
	jmp	$_121

$_024:	mov	dword ptr [rbp-0x10], 2
$_025:	jmp	$_027

$_026:	cmp	dword ptr [rbp-0x10], 0
	jz	$_027
	mov	ecx, 2076
	call	asmerr@PLT
	jmp	$_121

$_027:	cmp	dword ptr [rbp-0x10], 2
	je	$_052
	cmp	qword ptr [SegOverride+rip], 0
	jz	$_028
	cmp	byte ptr [rsi+0x60], -64
	jnz	$_028
	mov	ecx, 1
	call	GetOverrideAssume@PLT
	cmp	qword ptr [SegOverride+rip], rax
	jz	$_028
	mov	byte ptr [rsi+0x60], -126
$_028:	cmp	byte ptr [rsi+0x60], -64
	jz	$_029
	cmp	byte ptr [rsi+0x60], -127
	jne	$_052
$_029:	test	byte ptr [rsi+0x66], 0x04
	jne	$_052
	cmp	word ptr [rsi+0xE], 531
	jnz	$_031
	cmp	byte ptr [rsi+0x60], -64
	jnz	$_031
	cmp	byte ptr [rdi+0x19], -126
	jz	$_030
	cmp	qword ptr [SegOverride+rip], 0
	jz	$_031
$_030:	mov	rcx, rsi
	call	$_008
$_031:	call	GetCurrOffset@PLT
	mov	edx, dword ptr [rbp-0x4]
	sub	edx, eax
	sub	edx, 2
	add	edx, dword ptr [rsi+0x20]
	mov	eax, dword ptr [rbp-0x24]
	lea	rcx, [InstrTable+rip]
	lea	rcx, [rcx+rax*8]
	cmp	byte ptr [rsi+0x63], 0
	jz	$_032
	cmp	byte ptr [rcx+0x1], 3
	jz	$_033
$_032:	cmp	byte ptr [rsi+0x63], 1
	jz	$_034
	cmp	byte ptr [rcx+0x1], 4
	jnz	$_034
$_033:	dec	edx
$_034:	cmp	byte ptr [rsi+0x60], -127
	jz	$_035
	cmp	word ptr [rsi+0xE], 531
	jz	$_035
	cmp	edx, -128
	jl	$_035
	cmp	edx, 127
	jg	$_035
	mov	dword ptr [rsi+0x10], 65536
	jmp	$_048

$_035:	cmp	dword ptr [rbx+0x38], 253
	jz	$_036
	cmp	word ptr [rsi+0xE], 563
	jc	$_041
	cmp	word ptr [rsi+0xE], 580
	jnc	$_041
$_036:
	cmp	word ptr [rsi+0xE], 531
	jnz	$_037
	lea	rdx, [DS0000+rip]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_121

$_037:	cmp	edx, 0
	jge	$_038
	sub	edx, -128
	xor	eax, eax
	sub	eax, edx
	mov	edx, eax
	jmp	$_039

$_038:	sub	edx, 127
$_039:	cmp	byte ptr [rsi+0x60], -64
	jnz	$_040
	mov	ecx, 2075
	call	asmerr@PLT
	jmp	$_121

$_040:	mov	ecx, 2080
	call	asmerr@PLT
	jmp	$_121

$_041:	cmp	byte ptr [rbx+0x42], -2
	jz	$_045
	cmp	byte ptr [rbx+0x42], 0
	jnz	$_042
	mov	dword ptr [rsi+0x10], 131072
	dec	edx
	jmp	$_043

$_042:	mov	dword ptr [rsi+0x10], 262144
	sub	edx, 3
$_043:	movzx	ecx, byte ptr [rbx+0x42]
	cmp	cl, byte ptr [rsi+0x63]
	setne	al
	mov	byte ptr [rsi+0xA], al
	cmp	byte ptr [rsi+0xA], 0
	jz	$_044
	dec	edx
$_044:	jmp	$_047

$_045:	cmp	byte ptr [rsi+0x63], 0
	jbe	$_046
	mov	dword ptr [rsi+0x10], 262144
	sub	edx, 3
	jmp	$_047

$_046:	mov	dword ptr [rsi+0x10], 131072
	dec	edx
$_047:
	cmp	word ptr [rsi+0xE], 533
	jc	$_048
	cmp	word ptr [rsi+0xE], 562
	ja	$_048
	dec	edx
$_048:	mov	dword ptr [rbp-0x4], edx
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsi+0x20], eax
	mov	ecx, dword ptr [ModuleInfo+0x1C0+rip]
	and	ecx, 0xF0
	cmp	ecx, 48
	jnc	$_051
	cmp	word ptr [rsi+0xE], 532
	jbe	$_051
	cmp	word ptr [rsi+0xE], 563
	jnc	$_051
	cmp	dword ptr [rsi+0x10], 65536
	jz	$_051
	cmp	byte ptr [rsi+0x60], -64
	jnz	$_049
	cmp	byte ptr [ModuleInfo+0x1D5+rip], 1
	jnz	$_049
	xor	edx, edx
	mov	rcx, rsi
	call	$_001
	sub	dword ptr [rbp-0x4], 1
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsi+0x20], eax
	jmp	$_051

$_049:	mov	eax, 2079
	cmp	byte ptr [rsi+0x60], -64
	jnz	$_050
	mov	eax, 2075
$_050:	mov	edx, dword ptr [rbp-0x4]
	mov	ecx, eax
	call	asmerr@PLT
	jmp	$_121

$_051:	cmp	dword ptr [rbp-0x10], 0
	jz	$_052
	xor	eax, eax
	jmp	$_121

$_052:	mov	dword ptr [rbp-0xC], 0
	mov	dword ptr [rbp-0x8], 1
	mov	al, byte ptr [rbx+0x40]
	mov	byte ptr [rbp-0x11], al
	cmp	word ptr [rsi+0xE], 531
	jnz	$_056
	cmp	byte ptr [rsi+0x60], -64
	jnz	$_056
	cmp	byte ptr [rdi+0x19], -126
	jz	$_053
	cmp	qword ptr [SegOverride+rip], 0
	jz	$_056
$_053:	mov	rax, qword ptr [rdi+0x30]
	mov	qword ptr [rbp-0x20], rax
	xor	ecx, ecx
	test	rax, rax
	jz	$_054
	mov	rcx, qword ptr [rax+0x68]
	test	rcx, rcx
	jz	$_054
	mov	rcx, qword ptr [rcx]
$_054:	mov	rdx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdx, qword ptr [rdx+0x68]
	cmp	rax, qword ptr [ModuleInfo+0x1F8+rip]
	jz	$_055
	test	rax, rax
	jz	$_056
	test	rcx, rcx
	jz	$_056
	cmp	rcx, qword ptr [rdx]
	jnz	$_056
$_055:	mov	rcx, rsi
	call	$_008
$_056:	mov	al, byte ptr [rbp-0x11]
	cmp	byte ptr [rsi+0x60], -64
	jnz	$_063
	cmp	al, -64
	jz	$_063
	cmp	dword ptr [rbx+0x38], 253
	jz	$_063
	jmp	$_062

$_057:
	cmp	word ptr [rsi+0xE], 531
	jz	$_058
	cmp	word ptr [rsi+0xE], 532
	jnz	$_059
$_058:	or	byte ptr [rsi+0x66], 0x04
$_059:	cmp	dword ptr [rbp-0x10], 0
	jz	$_060
	mov	byte ptr [rsi+0x60], al
$_060:	jmp	$_063

$_061:	mov	byte ptr [rsi+0x60], al
	jmp	$_063

$_062:	cmp	al, -126
	jz	$_057
	cmp	al, -127
	jz	$_059
	jmp	$_061

$_063:	mov	al, byte ptr [rsi+0x60]
	cmp	word ptr [rsi+0xE], 531
	jz	$_064
	cmp	word ptr [rsi+0xE], 532
	jne	$_075
$_064:	test	byte ptr [rsi+0x66], 0x04
	jnz	$_065
	cmp	al, -126
	jne	$_075
$_065:	or	byte ptr [rsi+0x66], 0x04
	jmp	$_073

$_066:	test	byte ptr [rbx+0x43], 0x02
	jnz	$_067
	cmp	dword ptr [rbx+0x38], 253
	jnz	$_068
$_067:	mov	ecx, 2077
	call	asmerr@PLT
	jmp	$_121

$_068:	cmp	byte ptr [rbx+0x42], -2
	jz	$_069
	movzx	ecx, byte ptr [rsi+0x63]
	cmp	cl, byte ptr [rbx+0x42]
	setne	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_070

$_069:	mov	rcx, rdi
	call	GetSymOfssize@PLT
	movzx	ecx, al
	cmp	cl, byte ptr [rsi+0x63]
	setne	al
	mov	byte ptr [rsi+0xA], al
$_070:	mov	rcx, rdi
	call	set_frame@PLT
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	cmp	byte ptr [rsi+0xA], al
	jnz	$_071
	mov	dword ptr [rbp-0x8], 10
	mov	dword ptr [rsi+0x10], 1073741824
	jmp	$_072

$_071:	mov	dword ptr [rbp-0x8], 9
	mov	dword ptr [rsi+0x10], 262144
$_072:	jmp	$_074

$_073:	cmp	al, -127
	jz	$_066
	cmp	al, -126
	jz	$_068
	cmp	al, -64
	jz	$_068
$_074:	mov	r8d, dword ptr [rbp-0xC]
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, rdi
	call	CreateFixup@PLT
	mov	qword ptr [rsi+0x18], rax
	xor	eax, eax
	jmp	$_121

$_075:	movzx	eax, word ptr [rsi+0xE]
	jmp	$_119

$_076:	cmp	dword ptr [rbx+0x38], 253
	jnz	$_077
	mov	ecx, 2077
	call	asmerr@PLT
	jmp	$_121

$_077:	cmp	byte ptr [rsi+0x60], -64
	jnz	$_080
	mov	dword ptr [rbp-0xC], 4
	cmp	byte ptr [rsi+0x63], 0
	jbe	$_078
	mov	dword ptr [rbp-0x8], 3
	mov	dword ptr [rsi+0x10], 262144
	jmp	$_079

$_078:	mov	dword ptr [rbp-0x8], 2
	mov	dword ptr [rsi+0x10], 131072
$_079:	jmp	$_120

$_080:	mov	al, byte ptr [rsi+0x60]
	jmp	$_089

$_081:	mov	dword ptr [rsi+0x10], 65536
	mov	dword ptr [rbp-0x8], 1
	mov	eax, 0
	cmp	dword ptr [rbx+0x38], 253
	jnz	$_082
	mov	eax, 1
$_082:	mov	dword ptr [rbp-0xC], eax
	jmp	$_090

$_083:	mov	dword ptr [rbp-0xC], 1
	cmp	byte ptr [rbx+0x42], -2
	jz	$_086
	cmp	byte ptr [rbx+0x42], 0
	jnz	$_084
	mov	dword ptr [rbp-0x8], 2
	mov	dword ptr [rsi+0x10], 131072
	jmp	$_085

$_084:	mov	dword ptr [rbp-0x8], 3
	mov	dword ptr [rsi+0x10], 262144
$_085:	movzx	ecx, byte ptr [rsi+0x63]
	cmp	cl, byte ptr [rbx+0x42]
	setne	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_088

$_086:	cmp	byte ptr [rsi+0x63], 0
	jbe	$_087
	mov	dword ptr [rbp-0x8], 3
	mov	dword ptr [rsi+0x10], 262144
	jmp	$_088

$_087:	mov	dword ptr [rbp-0x8], 2
	mov	dword ptr [rsi+0x10], 131072
$_088:	mov	rcx, rdi
	call	set_frame@PLT
	jmp	$_090

$_089:	cmp	al, -64
	je	$_081
	cmp	al, -127
	jz	$_083
$_090:	jmp	$_120

$_091:	cmp	eax, 563
	jc	$_093
	cmp	eax, 580
	jnc	$_093
	cmp	byte ptr [rsi+0x60], -64
	jz	$_092
	cmp	dword ptr [rbx+0x38], 253
	jz	$_092
	mov	ecx, 2080
	call	asmerr@PLT
	jmp	$_121

$_092:	mov	dword ptr [rsi+0x10], 65536
	mov	dword ptr [rbp-0xC], 1
	mov	dword ptr [rbp-0x8], 1
	jmp	$_120

$_093:	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 48
	jc	$_109
	mov	al, byte ptr [rsi+0x60]
	jmp	$_107

$_094:	mov	eax, 3
	cmp	dword ptr [rbx+0x38], 253
	jnz	$_095
	mov	eax, 1
$_095:	mov	dword ptr [rbp-0xC], eax
	mov	dword ptr [rbp-0x8], 1
	mov	dword ptr [rsi+0x10], 65536
	jmp	$_108

$_096:	mov	dword ptr [rbp-0xC], 1
	cmp	byte ptr [rbx+0x42], -2
	jz	$_098
	movzx	ecx, byte ptr [rsi+0x63]
	cmp	cl, byte ptr [rbx+0x42]
	setne	al
	mov	byte ptr [rsi+0xA], al
	mov	eax, 131072
	cmp	byte ptr [rbx+0x42], 1
	jc	$_097
	mov	eax, 262144
$_097:	mov	dword ptr [rsi+0x10], eax
	jmp	$_100

$_098:	cmp	byte ptr [rsi+0x63], 0
	jbe	$_099
	mov	dword ptr [rbp-0x8], 3
	mov	dword ptr [rsi+0x10], 262144
	jmp	$_100

$_099:	mov	dword ptr [rbp-0x8], 2
	mov	dword ptr [rsi+0x10], 131072
$_100:	jmp	$_108

$_101:	cmp	byte ptr [ModuleInfo+0x1D5+rip], 0
	jz	$_106
	cmp	byte ptr [rbx+0x42], -2
	jz	$_102
	movzx	ecx, byte ptr [rsi+0x63]
	cmp	cl, byte ptr [rbx+0x42]
	setne	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_103

$_102:	mov	rcx, rdi
	call	GetSymOfssize@PLT
	movzx	ecx, al
	cmp	cl, byte ptr [rsi+0x63]
	setne	al
	mov	byte ptr [rsi+0xA], al
$_103:	mov	edx, 1
	mov	rcx, rsi
	call	$_001
	or	byte ptr [rsi+0x66], 0x04
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	cmp	byte ptr [rsi+0xA], al
	jnz	$_104
	mov	dword ptr [rbp-0x8], 10
	mov	dword ptr [rsi+0x10], 1073741824
	jmp	$_105

$_104:	mov	dword ptr [rbp-0x8], 9
	mov	dword ptr [rsi+0x10], 262144
$_105:	jmp	$_108

$_106:	mov	ecx, 2080
	call	asmerr@PLT
	jmp	$_121

	jmp	$_108

$_107:	cmp	al, -64
	je	$_094
	cmp	al, -127
	je	$_096
	cmp	al, -126
	je	$_101
	jmp	$_106

$_108:	jmp	$_118

$_109:	mov	al, byte ptr [rsi+0x60]
	jmp	$_117

$_110:	cmp	dword ptr [rbx+0x38], 253
	jnz	$_111
	mov	dword ptr [rbp-0xC], 1
	jmp	$_112

$_111:	mov	dword ptr [rbp-0xC], 2
$_112:	mov	dword ptr [rbp-0x8], 1
	mov	dword ptr [rsi+0x10], 65536
	jmp	$_118

$_113:	cmp	byte ptr [ModuleInfo+0x1D5+rip], 0
	jz	$_116
	cmp	al, -126
	jnz	$_114
	mov	edx, 1
	mov	rcx, rsi
	call	$_001
	mov	dword ptr [rbp-0x8], 9
	or	byte ptr [rsi+0x66], 0x04
	mov	dword ptr [rsi+0x10], 262144
	jmp	$_115

$_114:	xor	edx, edx
	mov	rcx, rsi
	call	$_001
	mov	dword ptr [rbp-0x8], 2
	mov	dword ptr [rsi+0x10], 131072
$_115:	jmp	$_118

$_116:	mov	ecx, 2080
	call	asmerr@PLT
	jmp	$_121

	jmp	$_118

$_117:	cmp	al, -64
	je	$_110
	cmp	al, -127
	jz	$_113
	cmp	al, -126
	jz	$_113
	jmp	$_116

$_118:	jmp	$_120

$_119:	cmp	eax, 531
	je	$_076
	cmp	eax, 532
	je	$_080
	jmp	$_091

$_120:	mov	r8d, dword ptr [rbp-0xC]
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, rdi
	call	CreateFixup@PLT
	mov	qword ptr [rsi+0x18], rax
	mov	eax, 0
$_121:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x73, 0x68, 0x6F, 0x72, 0x74, 0x00


.att_syntax prefix
