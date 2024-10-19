
.intel_syntax noprefix

.global get_register
.global InvokeDirective

.extern ExpandHllProc
.extern GetResWName
.extern AssignPointer
.extern CreateFloat
.extern atofloat
.extern quad_resize
.extern get_fasttype
.extern sym_ReservedStack
.extern CurrProc
.extern Mangle
.extern LstWrite
.extern GetGroup
.extern GetCurrOffset
.extern GetSymOfssize
.extern GetOfssizeAssume
.extern GetStdAssume
.extern search_assume
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern EvalOperand
.extern SizeFromRegister
.extern SizeFromMemtype
.extern SpecialTable
.extern LclDup
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tmemcpy
.extern tsprintf
.extern asmerr
.extern stackreg
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	mov	dword ptr [simd_scratch+rip], 0
	mov	dword ptr [wreg_scratch+rip], 0
	ret

get_register:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	lea	rcx, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x10], 12
	mov	edx, dword ptr [rbp+0x18]
	test	byte ptr [rcx+rax], 0x10
	jz	$_002
	mov	edx, 16
$_002:	movzx	ecx, byte ptr [rcx+rax+0xA]
	mov	eax, dword ptr [rbp+0x10]
	cmp	ecx, 15
	ja	$_012
	jmp	$_011

$_003:	cmp	ecx, 4
	jnc	$_004
	lea	rax, [rcx+0x1]
	jmp	$_012

$_004:	lea	rax, [rcx+0x53]
	jmp	$_012

$_005:	cmp	ecx, 8
	jnc	$_006
	lea	rax, [rcx+0x9]
	jmp	$_012

$_006:	lea	rax, [rcx+0x5B]
	jmp	$_012

$_007:	cmp	ecx, 8
	jnc	$_008
	lea	rax, [rcx+0x11]
	jmp	$_012

$_008:	lea	rax, [rcx+0x63]
	jmp	$_012

$_009:	cmp	ecx, 8
	jnc	$_010
	lea	rax, [rcx+0x73]
	jmp	$_012

$_010:	lea	rax, [rcx+0x73]
	jmp	$_012

	jmp	$_012

$_011:	cmp	rdx, 1
	jz	$_003
	cmp	rdx, 2
	jz	$_005
	cmp	rdx, 4
	jz	$_007
	cmp	rdx, 8
	jz	$_009
$_012:	leave
	ret

$_013:
	mov	rdx, qword ptr [rdx]
	xchg	rdi, rdx
	mov	ecx, 31
	repne scasb
	movzx	eax, byte ptr [rdi]
	mov	rdi, rdx
	ret

$_014:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	dword ptr [rbp-0x74], 0
	mov	dword ptr [rbp-0x78], 0
	mov	dword ptr [rbp-0x7C], 0
	mov	dword ptr [rbp-0x80], 0
	mov	byte ptr [rbp-0x85], 0
	mov	rbx, rcx
	mov	esi, edx
	mov	rcx, rbx
	call	GetSymOfssize@PLT
	mov	ecx, eax
	mov	dword ptr [rbp-0x84], ecx
	mov	eax, 2
	shl	eax, cl
	mov	dword ptr [rbp-0x70], eax
	mov	rdx, qword ptr [rbx+0x68]
	mov	rdi, qword ptr [rdx+0x8]
$_015:	test	rdi, rdi
	jz	$_023
	test	byte ptr [rdi+0x17], 0x01
	jnz	$_016
	cmp	byte ptr [rdi+0x19], -62
	jnz	$_018
$_016:	dec	esi
	cmp	byte ptr [rdi+0x19], -62
	jnz	$_017
	inc	dword ptr [rbp-0x7C]
$_017:	jmp	$_022

$_018:	test	byte ptr [rdi+0x3B], 0x04
	jz	$_019
	dec	dword ptr [rbp+0x30]
	inc	byte ptr [rbp-0x85]
	jmp	$_022

$_019:	inc	dword ptr [rbp-0x74]
	mov	eax, dword ptr [rdi+0x50]
	mov	edx, dword ptr [rbp-0x70]
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	add	dword ptr [rbp-0x80], eax
	mov	dl, byte ptr [rdi+0x19]
	cmp	dl, -60
	jnz	$_020
	mov	rdx, qword ptr [rdi+0x20]
	mov	dl, byte ptr [rdx+0x19]
$_020:	test	dl, 0x20
	jnz	$_021
	cmp	dl, 31
	jnz	$_022
$_021:	inc	dword ptr [rbp-0x78]
$_022:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_015

$_023:
	cmp	byte ptr [rbp-0x85], 0
	je	$_038
	imul	edi, dword ptr [rbp+0x38], 24
	add	rdi, qword ptr [rbp+0x40]
	xor	ecx, ecx
$_024:	cmp	ecx, dword ptr [rbp+0x30]
	jg	$_026
	cmp	byte ptr [rdi], 0
	jz	$_026
	inc	dword ptr [rbp+0x38]
	cmp	byte ptr [rdi], 44
	jnz	$_025
	inc	ecx
$_025:	add	rdi, 24
	jmp	$_024

$_026:	jmp	$_037

$_027:	movzx	eax, byte ptr [rdi]
	jmp	$_032

$_028:	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x6C], eax
	mov	byte ptr [rsp+0x20], 1
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x40]
	lea	rcx, [rbp-0x6C]
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_033
	cmp	byte ptr [rbp-0x28], -64
	jz	$_029
	test	byte ptr [rbp-0x28], 0x20
	jz	$_029
	inc	dword ptr [simd_scratch+rip]
$_029:	jmp	$_033

$_030:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rdi+0x4], 12
	test	byte ptr [r11+rax], 0x10
	jz	$_033
$_031:	inc	dword ptr [simd_scratch+rip]
	jmp	$_033

$_032:	cmp	eax, 8
	jz	$_028
	cmp	eax, 6
	jz	$_028
	cmp	eax, 91
	jz	$_028
	cmp	eax, 2
	jz	$_030
	cmp	eax, 11
	jz	$_031
$_033:	jmp	$_035

$_034:	inc	dword ptr [rbp+0x38]
	add	rdi, 24
	cmp	byte ptr [rdi-0x18], 44
	jz	$_036
$_035:	cmp	byte ptr [rdi], 0
	jnz	$_034
$_036:	inc	dword ptr [wreg_scratch+rip]
$_037:	cmp	byte ptr [rdi], 0
	jne	$_027
	mov	eax, dword ptr [simd_scratch+rip]
	sub	dword ptr [wreg_scratch+rip], eax
$_038:	movzx	edx, byte ptr [rbx+0x1A]
	mov	ecx, dword ptr [rbp-0x84]
	call	get_fasttype@PLT
	mov	rdi, rax
	mov	rcx, qword ptr [rbp+0x48]
	mov	eax, dword ptr [simd_scratch+rip]
	add	eax, dword ptr [wreg_scratch+rip]
	mul	dword ptr [rbp-0x70]
	add	eax, dword ptr [rbp-0x80]
	mov	edx, eax
	test	byte ptr [rdi+0xF], 0x10
	je	$_048
	xor	eax, eax
	mov	dword ptr [rcx], eax
	mov	ecx, dword ptr [rbp-0x70]
	movzx	edx, byte ptr [rdi+0xD]
	movzx	eax, byte ptr [rbx+0x1F]
	cmp	dl, byte ptr [rdi+0xC]
	jbe	$_039
	add	ecx, ecx
$_039:	cmp	eax, ecx
	jbe	$_040
	mov	ecx, eax
$_040:	mov	byte ptr [rbx+0x1F], cl
	mov	eax, dword ptr [rbp+0x30]
	add	eax, dword ptr [simd_scratch+rip]
	add	eax, dword ptr [wreg_scratch+rip]
	sub	eax, dword ptr [rbp-0x7C]
	cmp	al, dl
	jnc	$_041
	mov	al, dl
$_041:	mov	edx, eax
	cmp	ecx, 8
	jnz	$_042
	test	eax, 0x1
	jz	$_042
	inc	eax
$_042:	test	byte ptr [rbx+0x16], 0x10
	jz	$_043
	cmp	dl, byte ptr [rdi+0xD]
	jnz	$_043
	xor	eax, eax
$_043:	mul	ecx
	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jz	$_046
	mov	rdx, qword ptr [CurrProc+rip]
	test	eax, eax
	jz	$_044
	test	rdx, rdx
	jz	$_044
	or	byte ptr [rdx+0x3B], 0x10
$_044:	mov	rdx, qword ptr [sym_ReservedStack+rip]
	cmp	eax, dword ptr [rdx+0x28]
	jle	$_045
	mov	dword ptr [rdx+0x28], eax
$_045:	jmp	$_047

$_046:	test	eax, eax
	jz	$_047
	mov	rcx, qword ptr [rbp+0x48]
	mov	dword ptr [rcx], eax
	mov	edx, eax
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
$_047:	xor	eax, eax
	jmp	$_054

$_048:	test	byte ptr [rdi+0xF], 0x20
	jz	$_052
	movzx	edi, byte ptr [rbx+0x1E]
	movzx	esi, byte ptr [rbx+0x1D]
	add	edi, dword ptr [simd_scratch+rip]
	add	edi, dword ptr [rbp-0x78]
	add	esi, dword ptr [rbp-0x74]
	sub	esi, dword ptr [rbp-0x78]
	add	esi, dword ptr [wreg_scratch+rip]
	xor	eax, eax
	cmp	esi, 6
	jbe	$_049
	lea	eax, [rsi-0x6]
$_049:	cmp	edi, 8
	jbe	$_050
	lea	eax, [rax+rdi-0x8]
	mov	edi, 8
$_050:	mul	dword ptr [rbp-0x70]
	mov	dword ptr [rcx], eax
	test	eax, 0xF
	jz	$_051
	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jz	$_051
	add	eax, 8
	mov	dword ptr [rcx], eax
	lea	rcx, [DS0001+rip]
	call	AddLineQueue@PLT
$_051:	mov	eax, edi
	jmp	$_054

$_052:	mov	eax, dword ptr [rbp-0x84]
	shr	eax, 1
	test	byte ptr [rdi+0xF], 0x02
	jz	$_053
	test	byte ptr [rbx+0x16], 0x10
	jnz	$_053
	xor	edx, edx
$_053:	mov	dword ptr [rcx], edx
$_054:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_055:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	edx, r8d
	test	edx, edx
	jz	$_056
	call	GetSymOfssize@PLT
	lea	rdx, [stackreg+rip]
	mov	edx, dword ptr [rdx+rax*4]
	mov	r8d, dword ptr [rbp+0x20]
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
$_056:	leave
	ret

$_057:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	mov	dword ptr [rbp-0x8], 0
	mov	dword ptr [rbp-0xC], 0
	mov	dword ptr [rbp-0x1C], 0
	mov	dword ptr [rbp-0x4C], 0
	mov	byte ptr [rbp-0x65], 0
	mov	byte ptr [rbp-0x67], 0
	mov	byte ptr [rbp-0x69], 0
	mov	byte ptr [rbp-0x7A], 0
	mov	rbx, rcx
	mov	rsi, r8
	mov	rdi, qword ptr [rbp+0x48]
	movzx	ecx, byte ptr [rbx+0x1B]
	mov	byte ptr [rbp-0x66], cl
	mov	eax, 2
	shl	eax, cl
	mov	dword ptr [rbp-0x30], eax
	movzx	edx, byte ptr [rbx+0x1A]
	call	get_fasttype@PLT
	mov	qword ptr [rbp-0x40], rax
	mov	rdx, rax
	xor	eax, eax
	test	byte ptr [rdx+0xF], 0x10
	setne	al
	mov	byte ptr [rbp-0x67], al
	test	byte ptr [rdx+0xF], 0x08
	setne	al
	add	eax, eax
	cmp	byte ptr [rbp-0x66], 0
	setne	cl
	shl	eax, cl
	mov	dword ptr [rbp-0x48], eax
	mov	al, byte ptr [rdx+0xE]
	mov	dword ptr [rbp-0x44], eax
	mov	eax, dword ptr [rdx+0x8]
	mov	dword ptr [rbp-0x50], eax
	mov	al, byte ptr [rsi+0x19]
	cmp	al, -60
	jnz	$_058
	mov	rax, qword ptr [rsi+0x20]
	mov	al, byte ptr [rax+0x19]
$_058:	mov	byte ptr [rbp-0x68], al
	mov	rcx, qword ptr [rbp+0x50]
	cmp	byte ptr [rcx], 0
	jz	$_059
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_060
	test	byte ptr [rbx+0x16], 0x10
	jz	$_060
$_059:	jmp	$_356

$_060:	mov	rdx, qword ptr [rbx+0x68]
	test	byte ptr [rdx+0x40], 0x01
	jz	$_061
	test	byte ptr [rbx+0x16], 0x10
	jz	$_061
	test	byte ptr [rbx+0x15], 0xFFFFFF80
	jz	$_061
	cmp	dword ptr [rbp+0x30], 0
	jnz	$_061
	jmp	$_356

$_061:	cmp	byte ptr [rbp-0x68], -62
	jnz	$_062
	mov	rcx, qword ptr [rbp+0x50]
	call	LclDup@PLT
	mov	qword ptr [rsi+0x8], rax
	jmp	$_356

$_062:	mov	cl, byte ptr [rbp-0x66]
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	mov	dword ptr [rbp-0x2C], eax
	movzx	edx, byte ptr [rbx+0x1F]
	mov	dword ptr [rbp-0x34], edx
	cmp	byte ptr [rbp-0x67], 0
	jz	$_064
	mov	eax, dword ptr [rbp-0x30]
	mov	ecx, dword ptr [rbp+0x30]
	cmp	al, dl
	jnc	$_063
	mov	al, dl
$_063:	mul	ecx
	mov	dword ptr [rbp-0x4C], eax
	mov	byte ptr [rsi+0x4B], al
$_064:	mov	eax, dword ptr [rbp-0x30]
	cmp	eax, 8
	jnz	$_065
	cmp	dword ptr [rbp+0x40], 0
	jnz	$_065
	cmp	dword ptr [rdi+0x38], 249
	jz	$_065
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_065
	mov	eax, 4
$_065:	mov	dword ptr [rbp-0x4], eax
	mov	cl, byte ptr [rdi+0x40]
	cmp	cl, -16
	jnz	$_066
	mov	cl, -64
$_066:	cmp	dword ptr [rbp+0x40], 0
	jnz	$_067
	cmp	dword ptr [rdi+0x38], 249
	jnz	$_068
$_067:	jmp	$_080

$_068:	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_075
	test	byte ptr [rdi+0x43], 0x01
	jz	$_073
	cmp	cl, -64
	jz	$_070
	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rbp-0x66]
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	test	eax, eax
	jz	$_069
	mov	dword ptr [rbp-0x4], eax
$_069:	jmp	$_072

$_070:	cmp	byte ptr [rbp-0x68], -61
	jz	$_071
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_072
$_071:	mov	eax, dword ptr [rbp-0x30]
	mov	dword ptr [rbp-0x4], eax
$_072:	jmp	$_074

$_073:	cmp	cl, -64
	jz	$_074
	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rbp-0x66]
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	test	eax, eax
	jz	$_074
	mov	dword ptr [rbp-0x4], eax
$_074:	jmp	$_080

$_075:	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_080
	xor	eax, eax
	cmp	cl, -64
	jz	$_077
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_076
	cmp	byte ptr [rbp-0x68], -64
	jnz	$_076
	mov	byte ptr [rbp-0x68], cl
$_076:	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rbp-0x66]
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	jmp	$_079

$_077:	cmp	byte ptr [rbp-0x68], -61
	jz	$_078
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_079
$_078:	mov	eax, dword ptr [rbp-0x30]
$_079:	test	eax, eax
	jz	$_080
	mov	dword ptr [rbp-0x4], eax
$_080:	cmp	qword ptr [rdi+0x18], 0
	je	$_088
	mov	rax, qword ptr [rdi+0x18]
	mov	ecx, dword ptr [rax+0x4]
	lea	rdx, [SpecialTable+rip]
	imul	eax, ecx, 12
	add	rdx, rax
	mov	eax, dword ptr [rdx+0x4]
	and	eax, 0x7F
	mov	dword ptr [rbp-0xC], eax
	mov	eax, ecx
	movzx	ecx, byte ptr [rdx+0xA]
	mov	edx, dword ptr [rdx]
	mov	dword ptr [rbp-0x10], ecx
	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_081
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_081
	mov	dword ptr [rbp-0x8], eax
$_081:	test	edx, 0x70
	jz	$_082
	inc	byte ptr [rbp-0x65]
	add	ecx, 16
$_082:	test	edx, 0xF
	jnz	$_083
	cmp	ecx, 32
	jnc	$_088
	test	edx, 0x70
	jz	$_088
$_083:	mov	dword ptr [rbp-0x60], eax
	mov	eax, 1
	shl	eax, cl
	and	eax, dword ptr [rbp-0x50]
	mov	rcx, qword ptr [rbp+0x58]
	test	eax, eax
	jz	$_085
	test	dword ptr [rcx], eax
	jz	$_084
	mov	byte ptr [rbp-0x7A], 1
$_084:	jmp	$_087

$_085:	test	byte ptr [rcx], 0x01
	jz	$_087
	test	edx, 0x80
	jnz	$_086
	cmp	dword ptr [rbp-0x60], 5
	jnz	$_087
$_086:	mov	byte ptr [rbp-0x7A], 1
$_087:	test	edx, 0xF
	jz	$_088
	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_088
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_088
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rbp-0x4], eax
$_088:	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_092
	cmp	qword ptr [rdi+0x20], 0
	jz	$_092
	mov	rax, qword ptr [rdi+0x20]
	mov	ecx, dword ptr [rax+0x4]
	lea	rdx, [SpecialTable+rip]
	imul	eax, ecx, 12
	mov	dword ptr [rbp-0x60], ecx
	movzx	ecx, byte ptr [rdx+rax+0xA]
	mov	edx, dword ptr [rdx+rax]
	test	edx, 0xF
	jz	$_092
	mov	eax, 1
	shl	eax, cl
	and	eax, dword ptr [rbp-0x50]
	mov	rcx, qword ptr [rbp+0x58]
	test	eax, eax
	jz	$_090
	test	dword ptr [rcx], eax
	jz	$_089
	mov	byte ptr [rbp-0x7A], 1
$_089:	jmp	$_092

$_090:	test	byte ptr [rcx], 0x01
	jz	$_092
	test	edx, 0x80
	jnz	$_091
	cmp	dword ptr [rbp-0x60], 5
	jnz	$_092
$_091:	mov	byte ptr [rbp-0x7A], 1
$_092:	cmp	byte ptr [rbp-0x7A], 0
	jz	$_093
	mov	ecx, 2133
	call	asmerr@PLT
	inc	eax
	mov	rcx, qword ptr [rbp+0x58]
	mov	dword ptr [rcx], eax
$_093:	mov	eax, dword ptr [rbp-0x4]
	mov	byte ptr [rbp-0x7B], 1
	test	byte ptr [rsi+0x3B], 0x04
	jnz	$_094
	mov	r8, qword ptr [rsi+0x20]
	movzx	edx, byte ptr [rbp-0x66]
	movzx	ecx, byte ptr [rsi+0x19]
	call	SizeFromMemtype@PLT
	mov	byte ptr [rbp-0x7B], 0
$_094:	mov	dword ptr [rbp-0x14], eax
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_095
	cmp	byte ptr [rbp-0x68], -64
	jz	$_096
	test	byte ptr [rbp-0x68], 0x20
	jz	$_096
$_095:	inc	byte ptr [rbp-0x65]
$_096:	mov	rcx, rbx
	xor	ebx, ebx
	test	byte ptr [rsi+0x17], 0x01
	jz	$_097
	movzx	ebx, byte ptr [rsi+0x48]
	mov	dword ptr [rbp-0x18], ebx
	jmp	$_108

$_097:	test	byte ptr [rsi+0x3B], 0x04
	je	$_108
	cmp	byte ptr [rbp-0x68], -64
	jnz	$_098
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rbp-0x68], al
	and	al, 0xFFFFFFE0
	cmp	al, 32
	jnz	$_098
	inc	byte ptr [rbp-0x65]
$_098:	mov	rdx, qword ptr [rbp-0x40]
	test	byte ptr [rdx+0xF], 0x10
	jz	$_103
	mov	eax, dword ptr [rbp+0x30]
	cmp	byte ptr [rbp-0x65], 0
	jz	$_101
	cmp	al, byte ptr [rdx+0xD]
	jnc	$_100
	lea	ebx, [rax+0x28]
	cmp	al, 7
	jbe	$_099
	add	ebx, 92
$_099:	cmp	al, byte ptr [rdx+0xC]
	jnc	$_100
	movzx	ecx, byte ptr [rbp-0x66]
	shl	ecx, 3
	add	ecx, eax
	add	rcx, qword ptr [rdx]
	movzx	eax, byte ptr [rcx+0x8]
	mov	dword ptr [rbp-0x1C], eax
$_100:	jmp	$_102

$_101:	cmp	al, byte ptr [rdx+0xC]
	jnc	$_102
	movzx	ecx, byte ptr [rbp-0x66]
	shl	ecx, 3
	add	ecx, eax
	add	rcx, qword ptr [rdx]
	movzx	ebx, byte ptr [rcx+0x8]
$_102:	jmp	$_106

$_103:	cmp	byte ptr [rbp-0x65], 0
	jz	$_105
	cmp	dword ptr [simd_scratch+rip], 0
	jz	$_104
	movzx	eax, byte ptr [rcx+0x1E]
	dec	dword ptr [simd_scratch+rip]
	mov	ecx, dword ptr [simd_scratch+rip]
	cmp	byte ptr [rdx+0xD], cl
	jbe	$_104
	lea	ebx, [rax+rcx+0x28]
$_104:	jmp	$_106

$_105:	cmp	dword ptr [wreg_scratch+rip], 0
	jz	$_106
	movzx	eax, byte ptr [rcx+0x1D]
	dec	dword ptr [wreg_scratch+rip]
	mov	ecx, dword ptr [wreg_scratch+rip]
	cmp	byte ptr [rdx+0xC], cl
	jbe	$_106
	add	eax, ecx
	movzx	ecx, byte ptr [rbp-0x66]
	shl	ecx, 3
	add	ecx, eax
	add	rcx, qword ptr [rdx]
	movzx	ebx, byte ptr [rcx+0x8]
$_106:	test	ebx, ebx
	jz	$_108
	mov	ecx, ebx
	call	SizeFromRegister@PLT
	cmp	eax, 16
	jnc	$_107
	mov	edx, dword ptr [rbp-0x30]
	cmp	eax, dword ptr [rbp-0x14]
	jle	$_107
	shr	edx, 1
	cmp	edx, dword ptr [rbp-0x14]
	jl	$_107
	mov	ecx, ebx
	call	get_register
	mov	ebx, eax
$_107:	mov	dword ptr [rbp-0x18], ebx
$_108:	test	ebx, ebx
	jz	$_114
	lea	rdx, [SpecialTable+rip]
	imul	eax, ebx, 12
	movzx	ecx, byte ptr [rdx+rax+0xA]
	cmp	dword ptr [rbp-0x1C], 0
	jnz	$_109
	cmp	dword ptr [rbp-0x8], 0
	jz	$_109
	cmp	ecx, dword ptr [rbp-0x10]
	jz	$_113
$_109:	test	byte ptr [rdx+rax], 0x70
	jz	$_110
	add	ecx, 16
$_110:	xor	eax, eax
	cmp	ecx, 32
	jnc	$_111
	inc	eax
	shl	eax, cl
$_111:	mov	ecx, dword ptr [rbp-0x1C]
	test	ecx, ecx
	jz	$_112
	imul	ecx, ecx, 12
	movzx	ecx, byte ptr [rdx+rcx+0xA]
	mov	edx, 1
	shl	edx, cl
	or	eax, edx
$_112:	mov	rcx, qword ptr [rbp+0x58]
	or	dword ptr [rcx], eax
$_113:	jmp	$_117

$_114:	cmp	byte ptr [rbp-0x67], 0
	jnz	$_115
	mov	rdx, qword ptr [rbp-0x40]
	movzx	eax, byte ptr [rsi+0x49]
	sub	al, byte ptr [rdx+0xC]
	mul	dword ptr [rbp-0x30]
	mov	byte ptr [rsi+0x4B], al
$_115:	mov	byte ptr [rbp-0x69], 1
	movzx	eax, byte ptr [rbp-0x66]
	lea	rdx, [stackreg+rip]
	mov	eax, dword ptr [rdx+rax*4]
	mov	dword ptr [rbp-0x28], eax
	mov	ebx, dword ptr [ModuleInfo+0x340+rip]
	mov	eax, ebx
	mov	edx, dword ptr [rbp-0x30]
	cmp	edx, dword ptr [rbp-0x14]
	jle	$_116
	shr	edx, 1
	cmp	edx, dword ptr [rbp-0x14]
	jl	$_116
	mov	ecx, ebx
	call	get_register
$_116:	mov	dword ptr [rbp-0x18], eax
$_117:	mov	eax, dword ptr [rbp-0x18]
	mov	dword ptr [rbp-0x24], eax
	mov	ecx, dword ptr [rbp-0x18]
	call	SizeFromRegister@PLT
	mov	dword ptr [rbp-0x20], eax
	cmp	byte ptr [rbp-0x66], 0
	jz	$_118
	mov	edx, 4
	mov	ecx, dword ptr [rbp-0x18]
	call	get_register
	mov	dword ptr [rbp-0x24], eax
$_118:	mov	eax, dword ptr [rbp-0x14]
	mov	ecx, dword ptr [rbp-0x30]
	mov	edx, ecx
	shr	edx, 1
	cmp	dword ptr [rbp+0x40], 0
	jnz	$_119
	cmp	eax, ecx
	jbe	$_239
$_119:	cmp	eax, ecx
	jz	$_120
	cmp	eax, edx
	jnz	$_124
$_120:	mov	esi, ebx
	cmp	eax, edx
	jnz	$_121
	mov	esi, dword ptr [rbp-0x24]
$_121:	mov	r8, qword ptr [rbp+0x50]
	mov	edx, esi
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbp-0x69], 0
	jz	$_123
	cmp	byte ptr [rbp-0x67], 0
	jz	$_122
	mov	ebx, esi
$_122:	jmp	$_352

$_123:	jmp	$_356

$_124:	cmp	eax, ecx
	jc	$_355
	cmp	byte ptr [rbp-0x65], 0
	je	$_152
	cmp	eax, 8
	ja	$_132
	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_128
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_128
	mov	ecx, 612
	cmp	eax, 4
	jnz	$_125
	mov	ecx, 1050
$_125:	cmp	byte ptr [rbp-0x69], 0
	jz	$_126
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, ecx
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_126:	cmp	ebx, dword ptr [rbp-0x8]
	jz	$_127
	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, ebx
	mov	edx, ecx
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
$_127:	jmp	$_356

$_128:	mov	rdx, qword ptr [rbp+0x50]
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_131
	xor	eax, eax
	test	byte ptr [rdi+0x43], 0x20
	jz	$_129
	inc	eax
$_129:	mov	rcx, qword ptr [rdi+0x10]
	test	rcx, rcx
	jz	$_130
	mov	rdx, qword ptr [rcx+0x8]
$_130:	mov	byte ptr [rsp+0x20], 0
	mov	r9d, eax
	mov	r8d, 8
	mov	rcx, rdi
	call	atofloat@PLT
	mov	r8d, dword ptr [rdi]
	mov	edx, dword ptr [rdi+0x4]
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_131:	mov	r8, rdx
	lea	rcx, [DS0007+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_132:	cmp	dword ptr [rdi+0x3C], 3
	jne	$_139
	cmp	byte ptr [rbp-0x69], 0
	je	$_137
	cmp	byte ptr [rbp-0x66], 1
	jnz	$_133
	mov	eax, dword ptr [rdi]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rdi+0x4]
	mov	r8d, dword ptr [rdi+0x8]
	mov	edx, dword ptr [rdi+0xC]
	lea	rcx, [DS0008+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_133:	cmp	byte ptr [rbp-0x67], 0
	jnz	$_134
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
$_134:	cmp	byte ptr [rbp-0x66], 2
	jnz	$_135
	cmp	dword ptr [rdi+0x4], 0
	jnz	$_135
	cmp	dword ptr [rdi], 0
	jnz	$_135
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
	jmp	$_136

$_135:	mov	eax, dword ptr [rdi+0x4]
	mov	dword ptr [rsp+0x30], eax
	mov	eax, dword ptr [rbp-0x4C]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rdi]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
$_136:	mov	eax, dword ptr [rdi+0xC]
	mov	dword ptr [rsp+0x30], eax
	mov	eax, dword ptr [rbp-0x4C]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rdi+0x8]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000C+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_137:	cmp	dword ptr [rdi], 0
	jnz	$_138
	cmp	dword ptr [rdi+0x4], 0
	jnz	$_138
	cmp	dword ptr [rdi+0x8], 0
	jnz	$_138
	cmp	dword ptr [rdi+0xC], 0
	jnz	$_138
	mov	r9d, ebx
	mov	r8d, ebx
	mov	edx, 1002
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_138:	lea	rsi, [rbp-0x79]
	mov	r8, rsi
	mov	rdx, rdi
	mov	ecx, eax
	call	CreateFloat@PLT
	mov	r9, rsi
	mov	r8d, ebx
	mov	edx, 1030
	lea	rcx, [DS000D+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_139:	cmp	dword ptr [rbp-0x8], 0
	je	$_145
	cmp	byte ptr [rbp-0x69], 0
	jz	$_142
	mov	ecx, 1030
	cmp	eax, 16
	jbe	$_140
	mov	ecx, 1394
$_140:	cmp	byte ptr [rbp-0x67], 0
	jnz	$_141
	mov	r8d, eax
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
$_141:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x4C]
	mov	r8d, dword ptr [rbp-0x28]
	mov	edx, ecx
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
	jmp	$_144

$_142:	cmp	ebx, dword ptr [rbp-0x8]
	jz	$_144
	mov	ecx, 1394
	cmp	dword ptr [rbp-0x8], 140
	jge	$_143
	cmp	eax, 16
	jnz	$_143
	mov	ecx, 1030
$_143:	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, ebx
	mov	edx, ecx
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
$_144:	jmp	$_356

$_145:	cmp	byte ptr [rbp-0x69], 0
	jne	$_151
	lea	r11, [SpecialTable+rip]
	imul	eax, ebx, 12
	mov	ecx, dword ptr [r11+rax]
	test	ecx, 0x70
	jnz	$_146
	jmp	$_355

$_146:	mov	edx, 1394
	mov	esi, 233
	test	ecx, 0x40
	jz	$_147
	mov	esi, 225
	jmp	$_149

$_147:	test	ecx, 0x20
	jz	$_148
	mov	esi, 224
	jmp	$_149

$_148:	cmp	ebx, 140
	jnc	$_149
	mov	edx, 1030
$_149:	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, esi
	mov	r8d, ebx
	lea	rcx, [DS0010+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_150
	mov	r8, qword ptr [rbp+0x50]
	mov	edx, dword ptr [rbp-0x1C]
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
$_150:	jmp	$_356

$_151:	jmp	$_217

$_152:	cmp	dword ptr [rbp-0x8], 0
	je	$_179
	mov	rdx, qword ptr [rdi+0x18]
	cmp	byte ptr [rdx-0x18], 13
	jnz	$_153
	mov	ecx, dword ptr [rdx-0x2C]
	mov	eax, dword ptr [rdx+0x4]
	jmp	$_163

$_153:	cmp	byte ptr [rbp-0x69], 0
	jz	$_158
	cmp	byte ptr [rbp-0x67], 0
	jz	$_156
	mov	edx, 207
	cmp	ecx, 4
	jnz	$_154
	mov	edx, 210
	jmp	$_155

$_154:	cmp	ecx, 8
	jnz	$_155
	mov	edx, 214
$_155:	mov	eax, dword ptr [rbp-0x30]
	mov	dword ptr [rsp+0x38], eax
	mov	eax, dword ptr [rbp-0x4C]
	mov	dword ptr [rsp+0x30], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rsp+0x28], eax
	mov	dword ptr [rsp+0x20], edx
	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0011+rip]
	call	AddLineQueueX@PLT
	jmp	$_157

$_156:	mov	edx, dword ptr [rbp-0x8]
	lea	rcx, [DS0012+rip]
	call	AddLineQueueX@PLT
$_157:	jmp	$_162

$_158:	cmp	ebx, dword ptr [rbp-0x8]
	jz	$_159
	mov	r8d, dword ptr [rbp-0x8]
	mov	edx, ebx
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
$_159:	mov	rdx, qword ptr [rbp-0x40]
	mov	eax, ebx
	call	$_013
	test	eax, eax
	jnz	$_160
	jmp	$_355

$_160:	cmp	dword ptr [rbp-0x30], 8
	jnz	$_161
	mov	edx, 4
	mov	ecx, eax
	call	get_register
$_161:	mov	r8d, eax
	mov	edx, eax
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
$_162:	jmp	$_356

$_163:	mov	dword ptr [rbp-0x60], ecx
	mov	dword ptr [rbp-0x5C], eax
	mov	esi, 2
	cmp	byte ptr [rdx+0x18], 13
	jnz	$_164
	mov	ecx, dword ptr [rdx+0x34]
	mov	eax, dword ptr [rdx+0x64]
	mov	dword ptr [rbp-0x58], ecx
	mov	dword ptr [rbp-0x54], eax
	mov	esi, 4
$_164:	cmp	byte ptr [rbp-0x69], 0
	jz	$_170
	cmp	byte ptr [rbp-0x67], 0
	jz	$_167
	mov	ebx, dword ptr [rbp-0x4C]
$_165:	test	esi, esi
	jz	$_166
	mov	r9d, dword ptr [rbp+rsi*4-0x64]
	mov	r8d, ebx
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	dec	esi
	add	ebx, dword ptr [rbp-0x30]
	jmp	$_165

$_166:	jmp	$_169

$_167:	xor	ebx, ebx
$_168:	cmp	ebx, esi
	jnc	$_169
	mov	edx, dword ptr [rbp+rbx*4-0x60]
	lea	rcx, [DS0012+0x8+rip]
	call	AddLineQueueX@PLT
	inc	ebx
	jmp	$_168

$_169:	jmp	$_178

$_170:	mov	rdx, qword ptr [rbp-0x40]
	mov	eax, ebx
	call	$_013
	test	eax, eax
	jnz	$_171
	jmp	$_355

$_171:	mov	edi, eax
	cmp	esi, 4
	jnz	$_176
	mov	rdx, qword ptr [rbp-0x40]
	mov	eax, edi
	call	$_013
	test	eax, eax
	jnz	$_172
	jmp	$_355

$_172:	mov	esi, eax
	mov	rdx, qword ptr [rbp-0x40]
	mov	eax, esi
	call	$_013
	test	eax, eax
	jnz	$_173
	jmp	$_355

$_173:	mov	ecx, eax
	cmp	eax, dword ptr [rbp-0x60]
	jz	$_174
	mov	r8d, dword ptr [rbp-0x60]
	mov	edx, ecx
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
$_174:	cmp	esi, dword ptr [rbp-0x5C]
	jz	$_175
	mov	r8d, dword ptr [rbp-0x5C]
	mov	edx, esi
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
$_175:	mov	eax, dword ptr [rbp-0x58]
	mov	dword ptr [rbp-0x60], eax
	mov	eax, dword ptr [rbp-0x54]
	mov	dword ptr [rbp-0x5C], eax
$_176:	cmp	edi, dword ptr [rbp-0x60]
	jz	$_177
	mov	r8d, dword ptr [rbp-0x60]
	mov	edx, edi
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
$_177:	cmp	ebx, dword ptr [rbp-0x5C]
	jz	$_178
	mov	r8d, dword ptr [rbp-0x5C]
	mov	edx, ebx
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
$_178:	jmp	$_356

$_179:	cmp	byte ptr [rbp-0x69], 0
	je	$_197
	cmp	dword ptr [rdi+0x3C], 0
	jne	$_197
	cmp	byte ptr [rbp-0x67], 0
	je	$_182
	cmp	dword ptr [rdi+0x4], 0
	jnz	$_180
	cmp	dword ptr [rdi], 0
	jnz	$_180
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
	jmp	$_181

$_180:	mov	eax, dword ptr [rdi+0x4]
	mov	dword ptr [rsp+0x30], eax
	mov	eax, dword ptr [rbp-0x4C]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rdi]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
$_181:	mov	eax, dword ptr [rdi+0xC]
	mov	dword ptr [rsp+0x30], eax
	mov	eax, dword ptr [rbp-0x4C]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rdi+0x8]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000C+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_182:	cmp	byte ptr [rbp-0x66], 0
	jnz	$_187
	jmp	$_185

$_183:	movzx	ecx, word ptr [rdi+0x6]
	movzx	edx, word ptr [rdi+0x4]
	mov	r8d, edx
	mov	edx, ecx
	lea	rcx, [DS0008+0x12+rip]
	call	AddLineQueueX@PLT
$_184:	movzx	ecx, word ptr [rdi+0x2]
	movzx	edx, word ptr [rdi]
	mov	r8d, edx
	mov	edx, ecx
	lea	rcx, [DS0008+0x12+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

	jmp	$_186

$_185:	cmp	eax, 8
	jz	$_183
	cmp	eax, 4
	jz	$_184
$_186:	jmp	$_355

$_187:	cmp	byte ptr [rbp-0x66], 1
	jnz	$_192
	jmp	$_190

$_188:	mov	r8d, dword ptr [rdi+0x8]
	mov	edx, dword ptr [rdi+0xC]
	lea	rcx, [DS0008+0x12+rip]
	call	AddLineQueueX@PLT
$_189:	mov	r8d, dword ptr [rdi]
	mov	edx, dword ptr [rdi+0x4]
	lea	rcx, [DS0008+0x12+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

	jmp	$_191

$_190:	cmp	eax, 16
	jz	$_188
	cmp	eax, 8
	jz	$_189
$_191:	jmp	$_355

$_192:	cmp	eax, 16
	jne	$_355
	cmp	dword ptr [rdi+0xC], 0
	jnz	$_193
	mov	edx, dword ptr [rdi+0x8]
	lea	rcx, [DS0008+0x1B+rip]
	call	AddLineQueueX@PLT
	jmp	$_194

$_193:	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax], 0x01
	mov	r8, qword ptr [rdi+0x8]
	mov	edx, ebx
	lea	rcx, [DS0016+rip]
	call	AddLineQueueX@PLT
	mov	edx, ebx
	lea	rcx, [DS0012+0x8+rip]
	call	AddLineQueueX@PLT
$_194:	cmp	dword ptr [rdi+0x4], 0
	jnz	$_195
	mov	edx, dword ptr [rdi]
	lea	rcx, [DS0008+0x1B+rip]
	call	AddLineQueueX@PLT
	jmp	$_196

$_195:	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax], 0x01
	mov	r8, qword ptr [rdi]
	mov	edx, ebx
	lea	rcx, [DS0016+rip]
	call	AddLineQueueX@PLT
	mov	edx, ebx
	lea	rcx, [DS0012+0x8+rip]
	call	AddLineQueueX@PLT
$_196:	jmp	$_356

$_197:	cmp	byte ptr [rbp-0x69], 0
	jne	$_217
	test	byte ptr [rsi+0x17], 0x02
	jnz	$_198
	jmp	$_220

$_198:	mov	dword ptr [rbp-0x60], ebx
	mov	ebx, 207
	cmp	ecx, 4
	jnz	$_199
	mov	ebx, 210
	jmp	$_200

$_199:	cmp	ecx, 8
	jnz	$_200
	mov	ebx, 214
$_200:	mov	edx, 1
$_201:	cmp	ecx, eax
	jnc	$_202
	inc	edx
	add	ecx, dword ptr [rbp-0x30]
	jmp	$_201

$_202:	mov	dword ptr [rbp-0x64], edx
	xor	esi, esi
$_203:	cmp	esi, dword ptr [rbp-0x64]
	jge	$_216
	mov	eax, dword ptr [rbp-0x30]
	mul	esi
	cmp	dword ptr [rdi+0x3C], 0
	jne	$_214
	mov	ecx, eax
	cmp	dword ptr [rbp-0x30], 2
	jnz	$_204
	movzx	eax, word ptr [rdi+rax]
	jmp	$_206

$_204:	cmp	dword ptr [rbp-0x30], 8
	jnz	$_205
	mov	edx, dword ptr [rdi+rax+0x4]
$_205:	mov	eax, dword ptr [rdi+rax]
$_206:	test	eax, eax
	jnz	$_210
	test	edx, edx
	jnz	$_210
	mov	eax, dword ptr [rdi]
	or	eax, dword ptr [rdi+0x4]
	or	eax, dword ptr [rdi+0x8]
	or	eax, dword ptr [rdi+0xC]
	test	eax, eax
	jz	$_207
	test	byte ptr [rdi+0x43], 0x20
	jz	$_207
	cmp	dword ptr [rbp-0x30], 8
	jnz	$_207
	mov	edx, dword ptr [rbp-0x60]
	lea	rcx, [DS0017+rip]
	call	AddLineQueueX@PLT
	jmp	$_209

$_207:	mov	ecx, dword ptr [rbp-0x60]
	cmp	dword ptr [rbp-0x30], 8
	jnz	$_208
	mov	edx, 4
	call	get_register
	mov	ecx, eax
$_208:	mov	r8d, ecx
	mov	edx, ecx
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
$_209:	jmp	$_213

$_210:	cmp	dword ptr [rbp-0x30], 8
	jge	$_211
	mov	r8d, eax
	mov	edx, dword ptr [rbp-0x60]
	lea	rcx, [DS0018+rip]
	call	AddLineQueueX@PLT
	jmp	$_213

$_211:	test	edx, edx
	jnz	$_212
	mov	dword ptr [rbp-0x5C], eax
	mov	edx, 4
	mov	ecx, dword ptr [rbp-0x60]
	call	get_register
	mov	ecx, eax
	mov	r8d, dword ptr [rbp-0x5C]
	mov	edx, ecx
	lea	rcx, [DS0018+rip]
	call	AddLineQueueX@PLT
	jmp	$_213

$_212:	mov	r8, qword ptr [rdi+rcx]
	mov	edx, dword ptr [rbp-0x60]
	lea	rcx, [DS0016+rip]
	call	AddLineQueueX@PLT
$_213:	jmp	$_215

$_214:	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp+0x50]
	mov	r8d, ebx
	mov	edx, dword ptr [rbp-0x60]
	lea	rcx, [DS0019+rip]
	call	AddLineQueueX@PLT
$_215:	mov	rdx, qword ptr [rbp-0x40]
	mov	eax, dword ptr [rbp-0x60]
	call	$_013
	mov	dword ptr [rbp-0x60], eax
	inc	esi
	jmp	$_203

$_216:	jmp	$_356

$_217:	mov	esi, 1
$_218:	cmp	ecx, eax
	jnc	$_219
	add	esi, esi
	add	ecx, ecx
	jmp	$_218

$_219:	cmp	ecx, dword ptr [rbp-0x34]
	jg	$_220
	cmp	ecx, dword ptr [rbp-0x44]
	jle	$_222
$_220:	mov	r8, qword ptr [rbp+0x50]
	mov	edx, ebx
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbp-0x69], 0
	jz	$_221
	jmp	$_352

$_221:	jmp	$_356

$_222:	cmp	dword ptr [rdi+0x3C], 0
	jne	$_231
$_223:	test	esi, esi
	je	$_230
	cmp	dword ptr [rbp-0x30], 8
	jnz	$_226
	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax], 0x01
	mov	r8, qword ptr [rdi+rsi*8-0x8]
	mov	edx, ebx
	lea	rcx, [DS0016+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbp-0x67], 0
	jz	$_224
	lea	ecx, [rsi*8-0x8]
	add	ecx, dword ptr [rbp-0x4C]
	mov	r9d, ebx
	mov	r8d, ecx
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	jmp	$_225

$_224:	mov	edx, ebx
	lea	rcx, [DS0012+0x8+rip]
	call	AddLineQueueX@PLT
$_225:	jmp	$_229

$_226:	cmp	dword ptr [rbp-0x30], 4
	jnz	$_227
	mov	eax, dword ptr [rdi+rsi*4-0x4]
	jmp	$_228

$_227:	movzx	eax, word ptr [rdi+rsi*2-0x2]
$_228:	mov	edx, eax
	lea	rcx, [DS0008+0x1B+rip]
	call	AddLineQueueX@PLT
$_229:	dec	esi
	jmp	$_223

$_230:	jmp	$_356

$_231:	mov	ebx, 210
	jmp	$_236

$_232:	mov	ebx, 214
	jmp	$_237

$_233:	mov	ebx, 233
	jmp	$_237

$_234:	mov	ebx, 224
	jmp	$_237

$_235:	mov	ebx, 225
	jmp	$_237

$_236:	cmp	ecx, 8
	jz	$_232
	cmp	ecx, 16
	jz	$_233
	cmp	ecx, 32
	jz	$_234
	cmp	ecx, 64
	jz	$_235
$_237:	cmp	byte ptr [rbp-0x67], 0
	jnz	$_238
	mov	r8d, ecx
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
$_238:	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, ebx
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS001A+rip]
	call	AddLineQueueX@PLT
	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax], 0x01
	jmp	$_356

$_239:	cmp	byte ptr [rbp-0x65], 0
	je	$_288
	mov	dl, byte ptr [rbp-0x68]
	mov	ecx, dword ptr [rbp-0x14]
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_241
	cmp	dl, 35
	jz	$_241
	cmp	dl, 39
	jz	$_241
	mov	dl, 35
	cmp	dword ptr [rbp-0xC], 16
	jz	$_240
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_241
$_240:	mov	dl, 39
$_241:	cmp	ecx, 8
	ja	$_242
	cmp	byte ptr [rbp-0x66], 2
	jnc	$_243
	cmp	ecx, 4
	jbe	$_243
$_242:	jmp	$_355

$_243:	cmp	ecx, dword ptr [rbp-0x30]
	jge	$_244
	mov	ecx, dword ptr [rbp-0x30]
$_244:	cmp	dword ptr [rdi+0x3C], 2
	jne	$_262
	test	byte ptr [rdi+0x43], 0x01
	jne	$_262
	cmp	byte ptr [rbp-0x69], 0
	jnz	$_246
	cmp	ebx, dword ptr [rbp-0x8]
	jnz	$_246
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_245
	mov	r8d, ebx
	mov	edx, dword ptr [rbp-0x1C]
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
$_245:	jmp	$_356

$_246:	mov	byte ptr [rbp-0x68], dl
	cmp	byte ptr [rbp-0x69], 0
	jz	$_247
	cmp	byte ptr [rbp-0x67], 0
	jnz	$_247
	mov	r8d, ecx
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
$_247:	mov	dl, byte ptr [rbp-0x68]
	mov	ecx, 1030
	cmp	dl, 35
	jz	$_248
	cmp	dl, 33
	jnz	$_249
$_248:	mov	ecx, 1050
	jmp	$_250

$_249:	cmp	dl, 39
	jnz	$_250
	mov	ecx, 612
$_250:	cmp	dword ptr [rbp-0x8], 140
	jl	$_253
	mov	ecx, 1394
	cmp	dl, 35
	jz	$_251
	cmp	dl, 33
	jnz	$_252
$_251:	mov	ecx, 1406
	jmp	$_253

$_252:	cmp	dl, 39
	jnz	$_253
	mov	ecx, 1405
$_253:	cmp	ecx, 1406
	jz	$_254
	cmp	ecx, 1405
	jnz	$_257
$_254:	cmp	byte ptr [rbp-0x69], 0
	jz	$_255
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x4C]
	mov	r8d, dword ptr [rbp-0x28]
	mov	edx, ecx
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
	jmp	$_256

$_255:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, ebx
	mov	r8d, ebx
	mov	edx, ecx
	lea	rcx, [DS001C+rip]
	call	AddLineQueueX@PLT
$_256:	jmp	$_356

$_257:	cmp	byte ptr [rbp-0x69], 0
	jz	$_259
	cmp	ecx, 1050
	jnz	$_258
	cmp	dword ptr [rbp-0x30], 8
	jnz	$_258
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_258
	mov	ecx, 1024
	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, dword ptr [rbp-0x8]
	mov	edx, ecx
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	mov	ecx, 612
$_258:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x4C]
	mov	r8d, dword ptr [rbp-0x28]
	mov	edx, ecx
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_259:	cmp	ecx, 1050
	jnz	$_260
	cmp	dword ptr [rbp-0x30], 8
	jnz	$_260
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_260
	mov	ecx, 1024
$_260:	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, ebx
	mov	edx, ecx
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_261
	mov	r8d, ebx
	mov	edx, dword ptr [rbp-0x1C]
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
$_261:	jmp	$_356

$_262:	cmp	byte ptr [rbp-0x69], 0
	je	$_267
	cmp	byte ptr [rbp-0x67], 0
	je	$_267
	cmp	dword ptr [rdi+0x3C], 3
	jne	$_267
	xor	eax, eax
	mov	rdx, qword ptr [rbp+0x50]
	test	byte ptr [rdi+0x43], 0x20
	jz	$_263
	inc	eax
$_263:	mov	rcx, qword ptr [rdi+0x10]
	test	rcx, rcx
	jz	$_264
	mov	rdx, qword ptr [rcx+0x8]
$_264:	cmp	dword ptr [rbp-0x30], 8
	jnz	$_265
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_265
	cmp	dword ptr [rbp-0x14], 4
	jnz	$_265
	mov	dword ptr [rbp-0x14], 8
$_265:	mov	byte ptr [rsp+0x20], 0
	mov	r9d, eax
	mov	r8d, dword ptr [rbp-0x14]
	mov	rcx, rdi
	call	atofloat@PLT
	mov	r9d, dword ptr [rdi]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS001D+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x14], 8
	jnz	$_266
	mov	r9d, dword ptr [rdi+0x4]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS000B+0x1E+rip]
	call	AddLineQueueX@PLT
$_266:	jmp	$_356

$_267:	cmp	dl, 33
	jnz	$_271
	mov	rdx, qword ptr [rbp+0x50]
	lea	rcx, [DS001E+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbp-0x69], 0
	jz	$_269
	cmp	byte ptr [rbp-0x67], 0
	jz	$_268
	mov	ebx, 9
$_268:	jmp	$_352

	jmp	$_270

$_269:	mov	rdx, qword ptr [rbp+0x58]
	or	byte ptr [rdx], 0x01
	mov	edx, ebx
	lea	rcx, [DS001F+rip]
	call	AddLineQueueX@PLT
$_270:	jmp	$_356

$_271:	cmp	dl, 35
	jne	$_283
	cmp	byte ptr [rbp-0x69], 0
	je	$_280
	cmp	dword ptr [rbp-0x30], 4
	jg	$_276
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_274
	xor	eax, eax
	mov	rdx, qword ptr [rbp+0x50]
	test	byte ptr [rdi+0x43], 0x20
	jz	$_272
	inc	eax
$_272:	mov	rcx, qword ptr [rdi+0x10]
	test	rcx, rcx
	jz	$_273
	mov	rdx, qword ptr [rcx+0x8]
$_273:	mov	byte ptr [rsp+0x20], 0
	mov	r9d, eax
	mov	r8d, 4
	mov	rcx, rdi
	call	atofloat@PLT
	mov	edx, dword ptr [rdi]
	lea	rcx, [DS0020+rip]
	call	AddLineQueueX@PLT
	jmp	$_275

$_274:	mov	rdx, qword ptr [rbp+0x50]
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
$_275:	jmp	$_356

$_276:	mov	ecx, 682
	mov	dword ptr [rbp-0x60], 17
	test	byte ptr [rsi+0x3B], 0x04
	je	$_278
	mov	dword ptr [rbp-0x60], 115
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_278
	mov	ecx, 1024
	mov	esi, 40
	mov	r9, qword ptr [rbp+0x50]
	mov	r8d, esi
	mov	edx, ecx
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax+0x2], 0x01
	cmp	byte ptr [rbp-0x67], 0
	jz	$_277
	mov	ecx, 612
	mov	dword ptr [rsp+0x20], esi
	mov	r9d, dword ptr [rbp-0x4C]
	mov	r8d, dword ptr [rbp-0x28]
	mov	edx, ecx
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_277:	mov	ecx, 1028
	mov	r9d, esi
	mov	r8d, ebx
	mov	edx, ecx
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	jmp	$_352

$_278:	mov	r9, qword ptr [rbp+0x50]
	mov	r8d, dword ptr [rbp-0x60]
	mov	edx, ecx
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbp-0x67], 0
	jz	$_279
	mov	ebx, dword ptr [rbp-0x60]
$_279:	jmp	$_352

$_280:	mov	ecx, 1050
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_281
	cmp	dword ptr [rbp-0x30], 8
	jnz	$_281
	mov	ecx, 1024
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_281
	mov	ecx, 612
$_281:	mov	r9, qword ptr [rbp+0x50]
	mov	r8d, ebx
	mov	edx, ecx
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_282
	mov	r8d, ebx
	mov	edx, dword ptr [rbp-0x1C]
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
$_282:	jmp	$_356

$_283:	mov	rcx, qword ptr [rbp+0x50]
	cmp	byte ptr [rbp-0x69], 0
	jz	$_286
	cmp	dword ptr [rbp-0x30], 8
	jnz	$_284
	mov	ebx, 115
	mov	r8, rcx
	mov	edx, ebx
	lea	rcx, [DS0023+rip]
	call	AddLineQueueX@PLT
	jmp	$_352

$_284:	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_285
	mov	r8d, dword ptr [rdi]
	mov	edx, dword ptr [rdi+0x4]
	lea	rcx, [DS0008+0x12+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_285:	mov	r8, rcx
	mov	rdx, rcx
	lea	rcx, [DS0024+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_286:	mov	r8, rcx
	mov	edx, ebx
	lea	rcx, [DS0025+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_287
	mov	r8d, ebx
	mov	edx, dword ptr [rbp-0x1C]
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
$_287:	jmp	$_356

$_288:	cmp	dword ptr [rdi+0x3C], 0
	jz	$_289
	cmp	dword ptr [rdi+0x3C], 1
	jne	$_308
	test	byte ptr [rdi+0x43], 0x01
	jne	$_308
	cmp	byte ptr [rdi+0x40], -64
	jne	$_308
	cmp	dword ptr [rdi+0x38], 249
	je	$_308
$_289:	cmp	ecx, 8
	jnz	$_293
	cmp	eax, 8
	jnz	$_293
	mov	rax, qword ptr [rdi]
	cmp	rax, 2147483647
	jg	$_290
	cmp	rax, -2147483648
	jge	$_293
$_290:	mov	rdx, qword ptr [rbp+0x50]
	cmp	byte ptr [rbp-0x69], 0
	jz	$_291
	cmp	byte ptr [rbp-0x67], 0
	jz	$_291
	mov	qword ptr [rsp+0x30], rdx
	mov	eax, dword ptr [rbp-0x4C]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, rdx
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0026+rip]
	call	AddLineQueueX@PLT
	jmp	$_292

$_291:	mov	r8, rdx
	mov	edx, ebx
	lea	rcx, [DS0023+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbp-0x69], 0
	jz	$_292
	jmp	$_352

$_292:	jmp	$_356

$_293:	mov	rax, qword ptr [rdi+0x50]
	cmp	byte ptr [rsi+0x19], -61
	jnz	$_294
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_294
	cmp	byte ptr [rax+0x18], 0
	jz	$_294
	jmp	$_355

$_294:	mov	rdx, qword ptr [rbp+0x50]
	cmp	byte ptr [rbp-0x69], 0
	jnz	$_297
	cmp	word ptr [rdx], 48
	jz	$_295
	cmp	dword ptr [rdi], 0
	jnz	$_296
	cmp	dword ptr [rdi+0x4], 0
	jnz	$_296
$_295:	mov	r8d, dword ptr [rbp-0x24]
	mov	edx, dword ptr [rbp-0x24]
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_296:	jmp	$_300

$_297:	cmp	byte ptr [rbp-0x67], 0
	jnz	$_300
	cmp	dword ptr [rbp-0x2C], 16
	jge	$_298
	mov	r9d, ebx
	mov	r8, rdx
	mov	edx, ebx
	lea	rcx, [DS0027+rip]
	call	AddLineQueueX@PLT
	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax], 0x01
	jmp	$_299

$_298:	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
$_299:	jmp	$_356

$_300:	cmp	byte ptr [rbp-0x69], 0
	jz	$_305
	mov	eax, dword ptr [rbp-0x14]
	mov	ecx, 214
	cmp	eax, 1
	jnz	$_301
	mov	ecx, 205
	jmp	$_304

$_301:	cmp	eax, 2
	jnz	$_302
	mov	ecx, 207
	jmp	$_304

$_302:	cmp	eax, 4
	jnz	$_304
	cmp	dword ptr [rdi], 0
	jnz	$_303
	test	byte ptr [rsi+0x3B], 0x04
	jnz	$_304
$_303:	mov	ecx, 210
$_304:	mov	qword ptr [rsp+0x20], rdx
	mov	r9d, dword ptr [rbp-0x4C]
	mov	r8d, dword ptr [rbp-0x28]
	mov	edx, ecx
	lea	rcx, [DS0028+rip]
	call	AddLineQueueX@PLT
	jmp	$_307

$_305:	cmp	dword ptr [rdi+0x4], 0
	jnz	$_306
	mov	ebx, dword ptr [rbp-0x24]
$_306:	mov	r8, rdx
	mov	edx, ebx
	lea	rcx, [DS0023+rip]
	call	AddLineQueueX@PLT
$_307:	jmp	$_356

$_308:	cmp	dword ptr [rbp-0x8], 0
	je	$_327
	mov	edx, dword ptr [rbp-0xC]
	cmp	edx, eax
	jnc	$_309
	cmp	byte ptr [rbp-0x68], -61
	jnz	$_309
	jmp	$_355

$_309:	cmp	edx, dword ptr [rbp-0x20]
	jle	$_311
	mov	edx, dword ptr [rbp-0x20]
	mov	ecx, dword ptr [rbp-0x8]
	call	get_register
	mov	dword ptr [rbp-0x8], eax
	cmp	eax, dword ptr [rbp-0x18]
	jnz	$_310
	cmp	byte ptr [rbp-0x69], 0
	jnz	$_310
	jmp	$_356

$_310:	mov	eax, dword ptr [rbp-0x20]
	mov	dword ptr [rbp-0xC], eax
	mov	dword ptr [rbp-0x4], eax
	mov	edx, eax
$_311:	cmp	byte ptr [rbp-0x69], 0
	je	$_316
	cmp	byte ptr [rbp-0x67], 0
	jz	$_314
	cmp	byte ptr [rbp-0x7B], 0
	jz	$_313
	cmp	dword ptr [rbp-0x48], edx
	jle	$_313
	cmp	dword ptr [rbp-0x2C], 48
	jl	$_313
	mov	esi, 719
	movzx	eax, byte ptr [rdi+0x40]
	and	al, 0xFFFFFFC0
	cmp	al, 64
	jnz	$_312
	mov	esi, 718
$_312:	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, dword ptr [rbp-0x18]
	mov	edx, esi
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	mov	eax, dword ptr [rbp-0x18]
	mov	dword ptr [rbp-0x8], eax
	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax], 0x01
$_313:	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	jmp	$_315

$_314:	mov	edx, dword ptr [rbp-0x30]
	mov	ecx, dword ptr [rbp-0x8]
	call	get_register
	mov	rdx, rax
	lea	rcx, [DS0027+0xC+rip]
	call	AddLineQueueX@PLT
$_315:	jmp	$_356

$_316:	mov	esi, 682
	cmp	dword ptr [rbp-0x48], edx
	jle	$_320
	mov	edx, dword ptr [rbp-0x48]
	mov	ecx, dword ptr [rbp-0x18]
	call	get_register
	mov	ebx, eax
	cmp	dword ptr [rbp-0x2C], 48
	jl	$_318
	mov	esi, 719
	movzx	eax, byte ptr [rdi+0x40]
	and	al, 0xFFFFFFC0
	cmp	al, 64
	jnz	$_317
	mov	esi, 718
$_317:	jmp	$_319

$_318:	jmp	$_324

$_319:	jmp	$_325

$_320:	cmp	dword ptr [rbp-0x20], edx
	jle	$_325
	cmp	dword ptr [rbp-0x2C], 48
	jl	$_324
	mov	esi, 719
	movzx	eax, byte ptr [rdi+0x40]
	and	al, 0xFFFFFFC0
	cmp	al, 64
	jnz	$_321
	mov	esi, 718
$_321:	cmp	edx, 4
	jnz	$_323
	cmp	esi, 719
	jnz	$_322
	mov	esi, 682
	mov	edx, 4
	mov	ecx, dword ptr [rbp-0x18]
	call	get_register
	mov	ebx, eax
	jmp	$_323

$_322:	mov	esi, 1203
$_323:	jmp	$_325

$_324:	imul	eax, ebx, 12
	lea	rdx, [SpecialTable+rip]
	movzx	ecx, byte ptr [rdx+rax+0xA]
	lea	ebx, [rcx+0x1]
	add	ecx, 5
	mov	edx, ecx
	lea	rcx, [DS0029+rip]
	call	AddLineQueueX@PLT
$_325:	cmp	ebx, dword ptr [rbp-0x8]
	jz	$_326
	mov	r9d, dword ptr [rbp-0x8]
	mov	r8d, ebx
	mov	edx, esi
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
$_326:	jmp	$_356

$_327:	mov	esi, eax
	bsf	eax, eax
	bsr	esi, esi
	cmp	eax, esi
	jne	$_341
	mov	eax, dword ptr [rbp-0x20]
	cmp	dword ptr [rbp-0x4], eax
	jle	$_328
	mov	dword ptr [rbp-0x4], eax
$_328:	mov	eax, dword ptr [rbp-0x4]
	cmp	eax, ecx
	jnz	$_329
	cmp	byte ptr [rbp-0x69], 0
	jz	$_329
	cmp	byte ptr [rbp-0x67], 0
	jnz	$_329
	mov	rdx, qword ptr [rbp+0x50]
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
	jmp	$_356

$_329:	mov	esi, 682
	mov	edx, dword ptr [rbp-0x20]
	cmp	byte ptr [rbp-0x69], 0
	jnz	$_330
	cmp	dword ptr [rbp-0x48], edx
	jle	$_330
	mov	edx, dword ptr [rbp-0x48]
	mov	ecx, dword ptr [rbp-0x18]
	call	get_register
	mov	dword ptr [rbp-0x18], eax
	mov	eax, dword ptr [rbp-0x48]
	mov	dword ptr [rbp-0x20], eax
	mov	eax, dword ptr [rbp-0x4]
$_330:	mov	ecx, 205
	cmp	eax, 2
	jnz	$_331
	mov	ecx, 207
	jmp	$_333

$_331:	cmp	eax, 4
	jnz	$_332
	mov	ecx, 210
	jmp	$_333

$_332:	cmp	eax, 8
	jnz	$_333
	mov	ecx, 214
$_333:	cmp	eax, dword ptr [rbp-0x20]
	jge	$_338
	cmp	dword ptr [rbp-0x2C], 48
	jl	$_337
	mov	esi, 719
	movzx	eax, byte ptr [rdi+0x40]
	and	al, 0xFFFFFFC0
	cmp	al, 64
	jnz	$_334
	mov	esi, 718
$_334:	cmp	dword ptr [rbp-0x4], 4
	jnz	$_336
	cmp	esi, 719
	jnz	$_335
	mov	edx, 4
	mov	ecx, dword ptr [rbp-0x18]
	call	get_register
	mov	dword ptr [rbp-0x18], eax
	mov	esi, 682
	mov	ecx, 210
	jmp	$_336

$_335:	mov	esi, 1203
$_336:	jmp	$_338

$_337:	imul	eax, ebx, 12
	lea	rdx, [SpecialTable+rip]
	movzx	ecx, byte ptr [rdx+rax+0xA]
	lea	eax, [rcx+0x1]
	mov	dword ptr [rbp-0x18], eax
	add	ecx, 5
	mov	edx, ecx
	lea	rcx, [DS0029+rip]
	call	AddLineQueueX@PLT
	mov	ecx, 205
$_338:	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, ecx
	mov	r8d, dword ptr [rbp-0x18]
	mov	edx, esi
	lea	rcx, [DS0010+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbp-0x69], 0
	jz	$_340
	cmp	byte ptr [rbp-0x67], 0
	jz	$_339
	mov	ebx, dword ptr [rbp-0x18]
$_339:	jmp	$_352

$_340:	jmp	$_356

$_341:	mov	ecx, dword ptr [rbp-0x4]
	mov	edi, 210
	mov	esi, 1
	jmp	$_347

$_342:	inc	esi
$_343:	inc	esi
$_344:	jmp	$_348

$_345:	mov	edi, 207
	jmp	$_348

$_346:	jmp	$_355

	jmp	$_348

$_347:	cmp	ecx, 7
	jz	$_342
	cmp	ecx, 6
	jz	$_343
	cmp	ecx, 5
	jz	$_344
	cmp	ecx, 3
	jz	$_345
	jmp	$_346

$_348:	sub	ecx, esi
	mov	edx, ecx
	mov	ecx, ebx
	call	get_register
	mov	ecx, eax
	mov	edx, 682
	cmp	edi, 207
	jnz	$_349
	mov	edx, 719
	mov	ecx, ebx
$_349:	mov	dword ptr [rsp+0x28], esi
	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, edi
	mov	r8d, ecx
	lea	rcx, [DS002A+rip]
	call	AddLineQueueX@PLT
	cmp	esi, 1
	jbe	$_350
	sub	esi, 2
	mov	edx, 2
	mov	ecx, ebx
	call	get_register
	mov	ecx, eax
	mov	dword ptr [rsp+0x20], esi
	mov	r9, qword ptr [rbp+0x50]
	mov	r8d, ecx
	mov	edx, ebx
	lea	rcx, [DS002B+rip]
	call	AddLineQueueX@PLT
$_350:	test	esi, esi
	jz	$_351
	mov	edx, 1
	mov	ecx, ebx
	call	get_register
	mov	ecx, eax
	mov	r9, qword ptr [rbp+0x50]
	mov	r8d, ecx
	mov	edx, ebx
	lea	rcx, [DS002C+rip]
	call	AddLineQueueX@PLT
$_351:	cmp	byte ptr [rbp-0x69], 0
	jz	$_354
$_352:	mov	rax, qword ptr [rbp+0x58]
	or	byte ptr [rax], 0x01
	cmp	byte ptr [rbp-0x67], 0
	jz	$_353
	mov	r9d, ebx
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, dword ptr [rbp-0x28]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	jmp	$_354

$_353:	mov	edx, ebx
	lea	rcx, [DS0027+0xC+rip]
	call	AddLineQueueX@PLT
$_354:	jmp	$_356

$_355:	mov	edx, dword ptr [rbp+0x30]
	inc	edx
	mov	ecx, 2114
	call	asmerr@PLT
$_356:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	esi, 0
	mov	rdi, rcx
	mov	rax, qword ptr [rdi+0x50]
	mov	rdx, qword ptr [rdi+0x30]
	test	rdx, rdx
	jz	$_359
	cmp	byte ptr [rdx], 2
	jnz	$_357
	mov	esi, dword ptr [rdx+0x4]
	jmp	$_358

$_357:	mov	rdx, qword ptr [rdx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
$_358:	jmp	$_369

$_359:	test	rax, rax
	je	$_367
	cmp	qword ptr [rax+0x30], 0
	je	$_367
	mov	rbx, qword ptr [rax+0x30]
	mov	rcx, qword ptr [rbx+0x68]
	cmp	dword ptr [rcx+0x48], 2
	jz	$_360
	cmp	dword ptr [rcx+0x48], 3
	jnz	$_361
$_360:	mov	r8d, 1
	mov	edx, 3
	mov	rcx, rbx
	call	search_assume@PLT
	jmp	$_362

$_361:	mov	r8d, 1
	mov	edx, 1
	mov	rcx, rbx
	call	search_assume@PLT
$_362:	cmp	eax, -2
	jz	$_363
	lea	rsi, [rax+0x19]
	jmp	$_366

$_363:	mov	rcx, qword ptr [rdi+0x50]
	call	GetGroup@PLT
	test	rax, rax
	jnz	$_364
	mov	rax, rbx
$_364:	test	rax, rax
	jz	$_365
	mov	rdx, qword ptr [rax+0x8]
	mov	rcx, qword ptr [rbp+0x30]
	call	tstrcpy@PLT
	jmp	$_366

$_365:	lea	rdx, [DS002D+rip]
	mov	rcx, qword ptr [rbp+0x30]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, rax
	call	tstrcat@PLT
$_366:	jmp	$_369

$_367:	test	rax, rax
	jz	$_368
	cmp	byte ptr [rax+0x18], 5
	jnz	$_368
	mov	esi, 27
	jmp	$_369

$_368:	lea	rdx, [DS002D+rip]
	mov	rcx, qword ptr [rbp+0x30]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, rax
	call	tstrcat@PLT
$_369:	mov	rax, rsi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_370:
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	imul	ebx, edx, 24
	add	rbx, qword ptr [rbp+0x38]
	xor	eax, eax
	mov	byte ptr [rdi], al
$_371:	cmp	byte ptr [rbx], 44
	jz	$_374
	cmp	byte ptr [rbx], 0
	jz	$_374
	cmp	byte ptr [rbx+0x18], 5
	jnz	$_372
	cmp	dword ptr [rbx+0x1C], 270
	jnz	$_372
	add	rbx, 24
	jmp	$_373

$_372:	mov	rsi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, rsi
	rep movsb
$_373:	add	rbx, 24
	jmp	$_371

$_374:
	stosb
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_375:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2344
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	xor	ecx, ecx
$_376:	cmp	ecx, dword ptr [rbp+0x48]
	jg	$_379
	cmp	byte ptr [rbx], 0
	jnz	$_377
	mov	rax, -1
	jmp	$_562

$_377:	cmp	byte ptr [rbx], 44
	jnz	$_378
	inc	ecx
$_378:	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	jmp	$_376

$_379:	mov	dword ptr [rbp-0x4], ecx
	mov	rdi, qword ptr [rbp+0x40]
	test	rdi, rdi
	jnz	$_380
	xor	eax, eax
	jmp	$_562

$_380:	mov	eax, dword ptr [rbp+0x48]
	inc	eax
	mov	dword ptr [rbp-0x8D4], eax
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	mov	dword ptr [rbp-0x8D0], eax
	mov	rsi, qword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x8C], 17
	mov	dword ptr [rbp-0x1C], 0
	mov	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rbp-0x8], eax
	cmp	byte ptr [rbx], 7
	jnz	$_381
	cmp	dword ptr [rbx+0x4], 273
	jnz	$_381
	mov	dword ptr [rbp-0x1C], 1
	cmp	byte ptr [rdi+0x19], -62
	jz	$_381
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
$_381:	mov	rdx, rbx
$_382:	cmp	byte ptr [rdx], 44
	jz	$_383
	cmp	byte ptr [rdx], 0
	jz	$_383
	add	rdx, 24
	jmp	$_382

$_383:	mov	rsi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rdx+0x10]
	sub	rcx, rsi
	lea	rdi, [rbp-0x88C]
	rep movsb
	mov	byte ptr [rdi], 0
	mov	rdi, qword ptr [rbp+0x40]
	cmp	byte ptr [rdi+0x19], -62
	jnz	$_384
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_384
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
$_384:	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x14], eax
	mov	rsi, qword ptr [rbp+0x38]
	movzx	eax, byte ptr [rsi+0x1B]
	cmp	byte ptr [rsi+0x18], 7
	jz	$_385
	mov	rcx, rsi
	call	GetSymOfssize@PLT
$_385:	mov	byte ptr [rbp-0x8D5], al
	mov	ecx, eax
	mov	eax, 2
	shl	eax, cl
	add	eax, 2
	mov	dword ptr [rbp-0x18], eax
	movzx	edx, byte ptr [rsi+0x1A]
	movzx	ecx, byte ptr [rbp-0x8D5]
	call	get_fasttype@PLT
	cmp	qword ptr [rax], 0
	setne	al
	mov	byte ptr [rbp-0x8D6], al
	cmp	dword ptr [rbp-0x1C], 0
	je	$_393
	movzx	eax, byte ptr [ModuleInfo+0x1F1+rip]
	mov	dword ptr [rsp+0x20], eax
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x14]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_386
	jmp	$_562

$_386:	imul	ebx, dword ptr [rbp-0x14], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbp-0x18]
	cmp	dword ptr [rbp-0x8], eax
	jle	$_387
	cmp	dword ptr [rbp-0x18], 4
	jle	$_387
	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_562

$_387:	cmp	byte ptr [rbp-0x8D6], 0
	jz	$_388
	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x30], rax
	lea	rax, [rbp-0x88C]
	mov	qword ptr [rsp+0x28], rax
	lea	rax, [rbp-0x88]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x1C]
	mov	r8, qword ptr [rbp+0x40]
	mov	edx, dword ptr [rbp+0x48]
	mov	rcx, qword ptr [rbp+0x38]
	call	$_057
	xor	eax, eax
	jmp	$_562

$_388:	cmp	dword ptr [rbp-0x4C], 2
	jz	$_389
	test	byte ptr [rbp-0x45], 0x01
	jz	$_390
$_389:	lea	r8, [rbp-0x88C]
	mov	edx, dword ptr [ModuleInfo+0x340+rip]
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	mov	edx, dword ptr [ModuleInfo+0x340+rip]
	lea	rcx, [DS0027+0xC+rip]
	call	AddLineQueueX@PLT
	jmp	$_390

$_390:	test	byte ptr [rdi+0x3B], 0x04
	jz	$_392
	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	cmp	byte ptr [rdi+0x1C], 0
	jz	$_391
	add	eax, eax
$_391:	add	dword ptr [size_vararg+rip], eax
$_392:	xor	eax, eax
	jmp	$_562

$_393:	cmp	byte ptr [rbx], 2
	jne	$_397
	cmp	byte ptr [rbx+0x18], 13
	jne	$_397
	cmp	byte ptr [rbx+0x30], 2
	jne	$_397
	mov	ecx, dword ptr [rbx+0x4]
	call	SizeFromRegister@PLT
	mov	dword ptr [rbp-0x8DC], eax
	mov	ecx, dword ptr [rbx+0x34]
	call	SizeFromRegister@PLT
	mov	dword ptr [rbp-0xC], eax
	cmp	dword ptr [rbp-0x8DC], 8
	jz	$_394
	cmp	byte ptr [rbp-0x8D6], 0
	jnz	$_394
	mov	edx, dword ptr [rbx+0x4]
	lea	rcx, [DS0027+0xC+rip]
	call	AddLineQueueX@PLT
$_394:	mov	eax, dword ptr [rbp-0xC]
	add	eax, dword ptr [rbp-0x8DC]
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_395
	cmp	al, byte ptr [ModuleInfo+0x1CE+rip]
	jz	$_395
	mov	eax, dword ptr [rbp-0x8DC]
	add	dword ptr [size_vararg+rip], eax
	jmp	$_396

$_395:	mov	eax, dword ptr [rbp-0x8DC]
	add	dword ptr [rbp-0xC], eax
$_396:	mov	rdx, qword ptr [rbx+0x38]
	lea	rcx, [rbp-0x88C]
	call	tstrcpy@PLT
	mov	dword ptr [rbp-0x4C], 2
	and	byte ptr [rbp-0x45], 0xFFFFFFFE
	mov	qword ptr [rbp-0x38], 0
	lea	rax, [rbx+0x30]
	mov	qword ptr [rbp-0x70], rax
	jmp	$_420

$_397:	cmp	byte ptr [rdi+0x19], -62
	jnz	$_398
	mov	dword ptr [rbp-0x4C], 0
	mov	byte ptr [rbp-0x48], -62
	mov	qword ptr [rbp-0x38], 0
	mov	qword ptr [rbp-0x30], 0
	mov	qword ptr [rbp-0x70], 0
	jmp	$_399

$_398:	movzx	eax, byte ptr [ModuleInfo+0x1F1+rip]
	mov	dword ptr [rsp+0x20], eax
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x14]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_562
	imul	ebx, dword ptr [rbp-0x14], 24
	add	rbx, qword ptr [rbp+0x30]
$_399:	cmp	dword ptr [rbp-0x4C], 2
	jnz	$_401
	test	byte ptr [rbp-0x45], 0x01
	jnz	$_401
	mov	rcx, qword ptr [rbp-0x70]
	mov	ecx, dword ptr [rcx+0x4]
	call	SizeFromRegister@PLT
	mov	dword ptr [rbp-0xC], eax
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp-0x14], eax
	jge	$_400
	cmp	byte ptr [rbx], 44
	jz	$_400
	or	byte ptr [rbp-0x45], 0x01
$_400:	jmp	$_420

$_401:	cmp	dword ptr [rbp-0x4C], 0
	jz	$_402
	cmp	byte ptr [rbp-0x48], -64
	jnz	$_406
$_402:	mov	eax, dword ptr [rbp-0x8]
	mov	rcx, qword ptr [rbp-0x38]
	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_403
	cmp	dword ptr [rbp-0x50], 249
	jnz	$_403
	test	rcx, rcx
	jz	$_403
	call	GetSymOfssize@PLT
	mov	ecx, eax
	mov	eax, 2
	shl	eax, cl
$_403:	mov	dword ptr [rbp-0xC], eax
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_405
	test	byte ptr [rdi+0x3B], 0x04
	jnz	$_404
	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
$_404:	mov	rcx, qword ptr [rbp-0x30]
	test	rcx, rcx
	jz	$_405
	cmp	byte ptr [rcx+0x19], -60
	jnz	$_405
	mov	r8, qword ptr [rcx+0x20]
	movzx	edx, byte ptr [rbp-0x46]
	movzx	ecx, byte ptr [rcx+0x19]
	call	SizeFromMemtype@PLT
	mov	dword ptr [rbp-0xC], eax
$_405:	jmp	$_420

$_406:	cmp	byte ptr [rbp-0x48], -60
	je	$_418
	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_408
	test	byte ptr [rbp-0x45], 0x01
	jnz	$_408
	cmp	qword ptr [rbp-0x38], 0
	jz	$_408
	cmp	dword ptr [rbp-0x50], -2
	jnz	$_408
	cmp	byte ptr [rbp-0x48], -127
	jz	$_407
	cmp	byte ptr [rbp-0x48], -126
	jnz	$_408
$_407:	jmp	$_390

$_408:	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_415
	cmp	byte ptr [rbp-0x48], -61
	jnz	$_415
	cmp	qword ptr [rbp-0x38], 0
	jz	$_415
	mov	rcx, qword ptr [rbp-0x38]
	cmp	byte ptr [rcx+0x18], 2
	jnz	$_412
	movzx	edx, byte ptr [rbp-0x46]
	cmp	edx, 254
	jnz	$_409
	mov	dl, byte ptr [rcx+0x38]
$_409:	cmp	byte ptr [rcx+0x1C], 0
	jz	$_410
	mov	ecx, 130
	jmp	$_411

$_410:	mov	ecx, 129
$_411:	xor	r8d, r8d
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	jmp	$_414

$_412:	mov	rdx, qword ptr [rbp-0x30]
	test	rdx, rdx
	jz	$_413
	mov	rcx, rdx
$_413:	mov	eax, dword ptr [rcx+0x50]
	test	byte ptr [rcx+0x15], 0x02
	jz	$_414
	mov	ecx, dword ptr [rcx+0x58]
	xor	edx, edx
	div	ecx
$_414:	jmp	$_417

$_415:	cmp	byte ptr [rbp-0x46], -2
	jnz	$_416
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x46], al
$_416:	mov	r8, qword ptr [rbp-0x28]
	movzx	edx, byte ptr [rbp-0x46]
	movzx	ecx, byte ptr [rbp-0x48]
	call	SizeFromMemtype@PLT
$_417:	mov	dword ptr [rbp-0xC], eax
	jmp	$_420

$_418:	mov	rcx, qword ptr [rbp-0x38]
	test	rcx, rcx
	jnz	$_419
	mov	rcx, qword ptr [rbp-0x30]
$_419:	mov	rcx, qword ptr [rcx+0x20]
	mov	eax, dword ptr [rcx+0x50]
	mov	dword ptr [rbp-0xC], eax
$_420:	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	mov	dword ptr [rbp-0x10], eax
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_421
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rbp-0x8], eax
$_421:	cmp	dword ptr [rbp-0xC], 16
	jnz	$_422
	cmp	byte ptr [rbp-0x48], 47
	jnz	$_422
	cmp	dword ptr [rbp-0x10], 4
	jnz	$_422
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rbp-0xC], eax
$_422:	cmp	byte ptr [rbp-0x8D6], 0
	jz	$_423
	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x30], rax
	lea	rax, [rbp-0x88C]
	mov	qword ptr [rsp+0x28], rax
	lea	rax, [rbp-0x88]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x1C]
	mov	r8, qword ptr [rbp+0x40]
	mov	edx, dword ptr [rbp+0x48]
	mov	rcx, qword ptr [rbp+0x38]
	call	$_057
	xor	eax, eax
	jmp	$_562

$_423:	mov	eax, dword ptr [rbp-0x8]
	cmp	dword ptr [rbp-0xC], eax
	jg	$_424
	mov	eax, dword ptr [rbp-0x8]
	cmp	dword ptr [rbp-0xC], eax
	jge	$_425
	cmp	byte ptr [rdi+0x19], -61
	jnz	$_425
$_424:	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_562

$_425:	cmp	dword ptr [rbp-0x10], 8
	jnz	$_426
	mov	dword ptr [rbp-0x8C], 115
$_426:	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_427
	cmp	dword ptr [rbp-0x50], 249
	jnz	$_428
$_427:	cmp	dword ptr [rbp-0x4C], 2
	jne	$_462
	test	byte ptr [rbp-0x45], 0x01
	je	$_462
$_428:	mov	rcx, qword ptr [rbp+0x50]
	mov	rdx, qword ptr [rbp-0x70]
	mov	rax, qword ptr [rbp-0x68]
	cmp	byte ptr [rcx], 0
	jz	$_431
	test	rdx, rdx
	jz	$_429
	cmp	dword ptr [rdx+0x4], 17
	jz	$_430
	cmp	dword ptr [rdx+0x4], 115
	jz	$_430
$_429:	test	rax, rax
	jz	$_431
	cmp	dword ptr [rax+0x4], 17
	jz	$_430
	cmp	dword ptr [rax+0x4], 115
	jnz	$_431
$_430:	mov	byte ptr [rcx], 0
	mov	ecx, 2133
	call	asmerr@PLT
$_431:	test	byte ptr [rdi+0x3B], 0x04
	jz	$_433
	mov	eax, dword ptr [rbp-0x10]
	cmp	dword ptr [rbp-0xC], eax
	jle	$_432
	mov	eax, dword ptr [rbp-0xC]
$_432:	add	dword ptr [size_vararg+rip], eax
$_433:	mov	eax, dword ptr [rbp-0x10]
	cmp	dword ptr [rbp-0xC], eax
	jle	$_436
	mov	dword ptr [rbp-0x8E0], 207
	cmp	dword ptr [rbp-0x8D0], 48
	jc	$_434
	mov	dword ptr [rbp-0x10], 4
	mov	dword ptr [rbp-0x8E0], 210
$_434:	test	byte ptr [rbp-0x45], 0x02
	jz	$_435
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	lea	rcx, [rbp-0x88C]
	call	$_370
	and	byte ptr [rbp-0x45], 0xFFFFFFFD
$_435:	jmp	$_461

$_436:	mov	eax, dword ptr [rbp-0x10]
	cmp	dword ptr [rbp-0xC], eax
	jge	$_457
	cmp	dword ptr [rbp-0x8], 4
	jle	$_437
	cmp	dword ptr [rbp-0x10], 8
	jge	$_437
	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
$_437:	movzx	eax, byte ptr [rbp-0x48]
	and	al, 0xFFFFFFC0
	cmp	dword ptr [rbp-0xC], 4
	jge	$_438
	cmp	dword ptr [rbp-0x8], 2
	jle	$_438
	cmp	al, 64
	jnz	$_438
	cmp	dword ptr [rbp-0x8D0], 48
	jc	$_438
	mov	r8d, dword ptr [rbp-0x8C]
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS002E+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	mov	byte ptr [rcx], 1
	jmp	$_456

$_438:	jmp	$_455

$_439:	cmp	dword ptr [rbp-0x8], 1
	jnz	$_440
	test	byte ptr [rdi+0x3B], 0x04
	jnz	$_440
	mov	r8d, dword ptr [ModuleInfo+0x340+rip]
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS002F+rip]
	call	AddLineQueueX@PLT
	jmp	$_442

$_440:	mov	ecx, 718
	cmp	byte ptr [rbp-0x48], 0
	jnz	$_441
	mov	ecx, 719
$_441:	mov	r9d, dword ptr [rbp-0x8C]
	lea	r8, [rbp-0x88C]
	mov	edx, ecx
	lea	rcx, [DS0030+rip]
	call	AddLineQueueX@PLT
$_442:	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	jmp	$_456

$_443:	cmp	byte ptr [rbp-0x48], 1
	jnz	$_446
	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jnz	$_444
	cmp	dword ptr [rbp-0x8], 2
	jnz	$_446
$_444:	cmp	dword ptr [rbp-0x10], 8
	jnz	$_445
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0031+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	mov	byte ptr [rcx], 1
$_445:	jmp	$_448

$_446:	mov	ecx, 718
	cmp	byte ptr [rbp-0x48], 1
	jnz	$_447
	mov	ecx, 719
$_447:	mov	r9d, dword ptr [rbp-0x8C]
	lea	r8, [rbp-0x88C]
	mov	edx, ecx
	lea	rcx, [DS0030+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
$_448:	jmp	$_456

$_449:	cmp	dword ptr [rbp-0x10], 8
	jnz	$_450
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0032+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	jmp	$_456

$_450:	cmp	dword ptr [rbp-0xC], 3
	jnz	$_453
	cmp	dword ptr [rbp-0x10], 2
	jle	$_451
	mov	r9d, dword ptr [rbp-0x8C]
	lea	r8, [rbp-0x88C]
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0033+rip]
	call	AddLineQueueX@PLT
	jmp	$_452

$_451:	lea	r8, [rbp-0x88C]
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0034+rip]
	call	AddLineQueueX@PLT
$_452:	jmp	$_454

$_453:	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
$_454:	jmp	$_456

$_455:	cmp	byte ptr [rbp-0x48], 0
	je	$_439
	cmp	byte ptr [rbp-0x48], 64
	je	$_439
	cmp	byte ptr [rbp-0x48], 1
	je	$_443
	cmp	byte ptr [rbp-0x48], 65
	je	$_443
	cmp	byte ptr [rbp-0x48], 3
	je	$_449
	cmp	byte ptr [rbp-0x48], 67
	je	$_449
	jmp	$_450

$_456:	jmp	$_461

$_457:	movzx	eax, byte ptr [rbp-0x48]
	and	al, 0xFFFFFFC0
	cmp	al, 64
	jnz	$_460
	mov	eax, dword ptr [rbp-0xC]
	cmp	dword ptr [rbp-0x8], eax
	jle	$_460
	cmp	dword ptr [rbp-0x8], 2
	jle	$_458
	cmp	dword ptr [rbp-0x8D0], 48
	jc	$_458
	mov	r8d, dword ptr [rbp-0x8C]
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS002E+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	mov	byte ptr [rcx], 1
	jmp	$_459

$_458:	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
$_459:	jmp	$_461

$_460:	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
$_461:	jmp	$_561

$_462:	cmp	dword ptr [rbp-0x4C], 2
	jne	$_509
	mov	rcx, qword ptr [rbp-0x70]
	mov	eax, dword ptr [rcx+0x4]
	mov	dword ptr [rbp-0x8E4], eax
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	eax, dword ptr [r11+rax]
	mov	dword ptr [rbp-0x8E8], eax
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_463
	mov	eax, dword ptr [rbp-0x10]
	cmp	dword ptr [rbp-0x8], eax
	jge	$_463
	mov	eax, dword ptr [rbp-0x10]
	mov	dword ptr [rbp-0x8], eax
$_463:	test	dword ptr [rbp-0x8E8], 0x32008070
	jz	$_464
	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
	jmp	$_562

$_464:	mov	rcx, qword ptr [rbp+0x50]
	test	byte ptr [rcx], 0x01
	jz	$_466
	cmp	dword ptr [rbp-0x8E4], 5
	jz	$_465
	test	dword ptr [rbp-0x8E8], 0x80
	jz	$_466
$_465:	and	byte ptr [rcx], 0xFFFFFFFE
	mov	ecx, 2133
	call	asmerr@PLT
	jmp	$_468

$_466:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp-0x8E4], 12
	test	byte ptr [rcx], 0x08
	jz	$_468
	cmp	dword ptr [rbp-0x8E4], 7
	jz	$_467
	cmp	byte ptr [r11+rax+0xA], 2
	jnz	$_468
$_467:	and	byte ptr [rcx], 0xFFFFFFF7
	mov	ecx, 2133
	call	asmerr@PLT
$_468:	mov	edx, 2
	mov	cl, byte ptr [rbp-0x8D5]
	shl	edx, cl
	mov	eax, dword ptr [rbp-0x8]
	cmp	dword ptr [rbp-0xC], eax
	jnz	$_469
	cmp	dword ptr [rbp-0xC], edx
	jge	$_507
$_469:	cmp	dword ptr [rbp-0x8], 4
	jle	$_470
	cmp	dword ptr [rbp-0x10], 8
	jge	$_470
	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
$_470:	cmp	dword ptr [rbp-0xC], 2
	jg	$_476
	cmp	dword ptr [rbp-0x8], 4
	jz	$_471
	cmp	dword ptr [rbp-0x10], 4
	jnz	$_476
$_471:	cmp	dword ptr [rbp-0x8D0], 48
	jc	$_475
	mov	eax, dword ptr [rbp-0x8]
	cmp	dword ptr [rbp-0xC], eax
	jnz	$_475
	cmp	dword ptr [rbp-0xC], 2
	jnz	$_472
	sub	dword ptr [rbp-0x8E4], 9
	add	dword ptr [rbp-0x8E4], 17
	jmp	$_475

$_472:	cmp	dword ptr [rbp-0x8E4], 5
	jge	$_473
	sub	dword ptr [rbp-0x8E4], 1
	add	dword ptr [rbp-0x8E4], 17
	jmp	$_474

$_473:	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0035+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	mov	dword ptr [rbp-0x8E4], 17
$_474:	mov	dword ptr [rbp-0xC], 2
$_475:	jmp	$_491

$_476:	cmp	dword ptr [rbp-0x10], 8
	jne	$_491
	mov	eax, dword ptr [rbp-0x8]
	cmp	dword ptr [rbp-0xC], eax
	jnz	$_477
	cmp	dword ptr [rbp-0x8], 8
	jl	$_478
$_477:	cmp	dword ptr [rbp-0xC], 4
	jne	$_491
	cmp	dword ptr [rbp-0x8], 8
	jne	$_491
$_478:	mov	ecx, dword ptr [rbp-0x8E4]
	call	SizeFromRegister@PLT
	mov	ecx, dword ptr [rbp-0x8E4]
	jmp	$_489

$_479:	cmp	ecx, 1
	jc	$_480
	cmp	ecx, 8
	ja	$_480
	add	ecx, 114
	jmp	$_482

$_480:	cmp	ecx, 87
	jc	$_481
	cmp	ecx, 90
	ja	$_481
	add	ecx, 32
	jmp	$_482

$_481:	cmp	ecx, 91
	jc	$_482
	cmp	ecx, 98
	ja	$_482
	add	ecx, 32
$_482:	jmp	$_490

$_483:	cmp	ecx, 9
	jc	$_484
	cmp	ecx, 16
	ja	$_484
	add	ecx, 106
	jmp	$_485

$_484:	cmp	ecx, 99
	jc	$_485
	cmp	ecx, 106
	ja	$_485
	add	ecx, 24
$_485:	jmp	$_490

$_486:	cmp	ecx, 17
	jc	$_487
	cmp	ecx, 24
	ja	$_487
	add	ecx, 98
	jmp	$_488

$_487:	cmp	ecx, 107
	jc	$_488
	cmp	ecx, 114
	ja	$_488
	add	ecx, 16
$_488:	jmp	$_490

$_489:	cmp	eax, 1
	jz	$_479
	cmp	eax, 2
	jz	$_483
	cmp	eax, 4
	jz	$_486
$_490:	mov	dword ptr [rbp-0x8E4], ecx
$_491:	cmp	dword ptr [rbp-0xC], 1
	jne	$_507
	mov	eax, dword ptr [rbp-0x8E4]
	cmp	eax, 5
	jc	$_492
	cmp	eax, 8
	jbe	$_493
$_492:	cmp	dword ptr [rbp-0x8], 1
	je	$_499
$_493:	cmp	dword ptr [rbp-0x8], 1
	jz	$_495
	cmp	dword ptr [rbp-0x8D0], 48
	jc	$_495
	mov	eax, 3
	mov	ecx, 719
	movzx	eax, byte ptr [rbp-0x48]
	and	al, 0xFFFFFFC0
	cmp	al, 64
	jnz	$_494
	mov	ecx, 718
	mov	eax, 1
$_494:	mov	rdx, qword ptr [rbp+0x50]
	mov	byte ptr [rdx], al
	lea	r9, [rbp-0x88C]
	mov	r8d, dword ptr [ModuleInfo+0x340+rip]
	mov	edx, ecx
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
	jmp	$_498

$_495:	cmp	eax, 1
	jz	$_496
	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0035+rip]
	call	AddLineQueueX@PLT
	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	and	byte ptr [rcx], 0xFFFFFFFB
$_496:	cmp	dword ptr [rbp-0x8], 1
	jz	$_498
	mov	rcx, qword ptr [rbp+0x50]
	movzx	eax, byte ptr [rbp-0x48]
	and	al, 0xFFFFFFC0
	cmp	al, 64
	jnz	$_497
	and	byte ptr [rcx], 0xFFFFFFF9
	lea	rcx, [DS0036+rip]
	call	AddLineQueue@PLT
	jmp	$_498

$_497:	test	byte ptr [rcx], 0x02
	jnz	$_498
	or	byte ptr [rcx], 0x02
	lea	rcx, [DS0037+rip]
	call	AddLineQueue@PLT
$_498:	mov	eax, dword ptr [ModuleInfo+0x340+rip]
	mov	dword ptr [rbp-0x8E4], eax
	jmp	$_507

$_499:	cmp	dword ptr [rbp-0x8D0], 48
	jc	$_501
	cmp	dword ptr [rbp-0x8], 4
	jz	$_500
	cmp	dword ptr [rbp-0x10], 4
	jnz	$_501
$_500:	sub	eax, 1
	add	eax, 17
	jmp	$_506

$_501:	cmp	dword ptr [rbp-0x10], 8
	jnz	$_505
	cmp	dword ptr [rbp-0x8D0], 112
	jc	$_505
	cmp	eax, 1
	jc	$_502
	cmp	eax, 4
	ja	$_502
	sub	eax, 1
	add	eax, 115
	jmp	$_504

$_502:	cmp	eax, 87
	jc	$_503
	cmp	eax, 90
	ja	$_503
	sub	eax, 87
	add	eax, 119
	jmp	$_504

$_503:	sub	eax, 91
	add	eax, 123
$_504:	jmp	$_506

$_505:	cmp	dword ptr [rbp-0x10], 8
	jge	$_506
	sub	eax, 1
	add	eax, 9
$_506:	mov	dword ptr [rbp-0x8E4], eax
$_507:	mov	edx, dword ptr [rbp-0x8E4]
	lea	rcx, [DS0033+0x3A+rip]
	call	AddLineQueueX@PLT
	mov	eax, dword ptr [rbp-0x10]
	cmp	dword ptr [rbp-0x8], eax
	jge	$_508
	mov	eax, dword ptr [rbp-0x10]
	mov	dword ptr [rbp-0x8], eax
$_508:	jmp	$_560

$_509:	cmp	dword ptr [rbp-0x8], 0
	je	$_520
	mov	eax, dword ptr [rbp-0x88]
	mov	edx, dword ptr [rbp-0x84]
	cmp	dword ptr [rbp-0x4C], 3
	jnz	$_510
	mov	ecx, 4
	jmp	$_519

$_510:	test	edx, edx
	jnz	$_511
	cmp	eax, 255
	jbe	$_512
$_511:	cmp	edx, -1
	jnz	$_513
	cmp	eax, 4294967041
	jl	$_513
$_512:	mov	ecx, 1
	jmp	$_519

$_513:	test	edx, edx
	jnz	$_514
	cmp	eax, 65535
	jbe	$_515
$_514:	cmp	edx, -1
	jnz	$_516
	cmp	eax, 4294901761
	jl	$_516
$_515:	mov	ecx, 2
	jmp	$_519

$_516:	test	edx, edx
	jz	$_517
	cmp	edx, -1
	jnz	$_518
$_517:	mov	ecx, 4
	jmp	$_519

$_518:	mov	ecx, 8
$_519:	cmp	dword ptr [rbp-0x8], ecx
	jge	$_520
	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
$_520:	mov	eax, 2
	mov	cl, byte ptr [rbp-0x8D5]
	shl	eax, cl
	mov	dword ptr [rbp-0xC], eax
	cmp	dword ptr [rbp-0x8], eax
	jge	$_525
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_524
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_524
	cmp	eax, 2
	jnz	$_522
	cmp	dword ptr [rbp-0x88], 65535
	jg	$_521
	cmp	dword ptr [rbp-0x88], -65535
	jge	$_522
$_521:	mov	dword ptr [rbp-0x8], 4
	jmp	$_523

$_522:	mov	dword ptr [rbp-0x8], eax
$_523:	jmp	$_525

$_524:	mov	dword ptr [rbp-0x8], eax
$_525:	cmp	dword ptr [rbp-0x8D0], 16
	jnc	$_540
	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	jmp	$_538

$_526:	cmp	dword ptr [rbp-0x88], 0
	jnz	$_527
	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_528
$_527:	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS001E+rip]
	call	AddLineQueueX@PLT
	jmp	$_530

$_528:	test	byte ptr [rcx], 0x04
	jnz	$_529
	lea	rcx, [DS0038+rip]
	call	AddLineQueue@PLT
$_529:	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x06
$_530:	jmp	$_539

$_531:	cmp	dword ptr [rbp-0x88], 65535
	ja	$_532
	lea	rcx, [DS0038+rip]
	call	AddLineQueue@PLT
	jmp	$_533

$_532:	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS0039+rip]
	call	AddLineQueueX@PLT
$_533:	lea	rcx, [DS003A+rip]
	call	AddLineQueue@PLT
	cmp	dword ptr [rbp-0x88], 0
	jnz	$_534
	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_535
$_534:	lea	rdx, [rbp-0x88C]
	lea	rcx, [DS003B+rip]
	call	AddLineQueueX@PLT
	jmp	$_536

$_535:	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x06
$_536:	jmp	$_539

$_537:	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
	jmp	$_539

$_538:	cmp	dword ptr [rbp-0x8], 2
	je	$_526
	cmp	dword ptr [rbp-0x8], 4
	je	$_531
	jmp	$_537

$_539:	lea	rcx, [DS003A+rip]
	call	AddLineQueue@PLT
	jmp	$_560

$_540:	mov	ebx, 677
	mov	esi, 4294967294
	mov	eax, dword ptr [rbp-0x10]
	cmp	dword ptr [rbp-0x8], eax
	je	$_558
	jmp	$_557

$_541:	mov	ebx, 679
	jmp	$_558

$_542:	lea	r8, [rbp-0x88C]
	mov	edx, ebx
	lea	rcx, [DS003C+rip]
	call	AddLineQueueX@PLT
$_543:	jmp	$_558

$_544:	cmp	byte ptr [rbp-0x8D5], 0
	jz	$_545
	cmp	byte ptr [Options+0xC6+rip], 1
	jz	$_545
	cmp	dword ptr [rbp-0x4C], 3
	jz	$_546
$_545:	jmp	$_558

$_546:	mov	edx, 10
	lea	rcx, [rbp-0x88]
	call	quad_resize@PLT
	mov	edx, dword ptr [rbp-0x80]
	lea	rcx, [DS003D+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x8D0], 112
	jc	$_547
	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	mov	rdx, qword ptr [rbp-0x88]
	lea	rcx, [DS003E+rip]
	call	AddLineQueueX@PLT
$_547:	jmp	$_560

$_548:	cmp	byte ptr [rbp-0x8D5], 0
	je	$_558
	cmp	byte ptr [Options+0xC6+rip], 1
	je	$_558
	cmp	dword ptr [rbp-0x7C], 0
	jz	$_549
	cmp	dword ptr [rbp-0x7C], -1
	jnz	$_550
$_549:	mov	rdx, qword ptr [rbp-0x80]
	lea	rcx, [DS003F+rip]
	call	AddLineQueueX@PLT
	jmp	$_551

$_550:	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	mov	rdx, qword ptr [rbp-0x80]
	lea	rcx, [DS003E+rip]
	call	AddLineQueueX@PLT
$_551:	cmp	dword ptr [rbp-0x84], 0
	jz	$_552
	cmp	dword ptr [rbp-0x84], -1
	jnz	$_553
$_552:	mov	rdx, qword ptr [rbp-0x88]
	lea	rcx, [DS003F+rip]
	call	AddLineQueueX@PLT
	jmp	$_554

$_553:	mov	rcx, qword ptr [rbp+0x50]
	or	byte ptr [rcx], 0x01
	mov	rdx, qword ptr [rbp-0x88]
	lea	rcx, [DS003E+rip]
	call	AddLineQueueX@PLT
$_554:	jmp	$_560

$_555:	cmp	byte ptr [rbp-0x8D5], 2
	jz	$_558
$_556:	mov	edx, dword ptr [rbp-0x8D4]
	mov	ecx, 2114
	call	asmerr@PLT
	jmp	$_558

$_557:	cmp	dword ptr [rbp-0x8], 2
	je	$_541
	cmp	dword ptr [rbp-0x8], 6
	je	$_542
	cmp	dword ptr [rbp-0x8], 4
	je	$_543
	cmp	dword ptr [rbp-0x8], 10
	je	$_544
	cmp	dword ptr [rbp-0x8], 16
	je	$_548
	cmp	dword ptr [rbp-0x8], 8
	jz	$_555
	jmp	$_556

$_558:	cmp	esi, -2
	jz	$_559
	lea	r9, [rbp-0x88C]
	mov	r8d, esi
	mov	edx, ebx
	lea	rcx, [DS0040+rip]
	call	AddLineQueueX@PLT
	jmp	$_560

$_559:	lea	r8, [rbp-0x88C]
	mov	edx, ebx
	lea	rcx, [DS0041+rip]
	call	AddLineQueueX@PLT
$_560:	test	byte ptr [rdi+0x3B], 0x04
	jz	$_561
	mov	eax, dword ptr [rbp-0x8]
	add	dword ptr [size_vararg+rip], eax
$_561:	xor	eax, eax
$_562:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

InvokeDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2872
	mov	dword ptr [rbp-0x48], 0
	mov	qword ptr [rbp-0x8C8], 0
	mov	qword ptr [rbp-0x8D8], 0
	inc	dword ptr [rbp+0x28]
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x3C], eax
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_565
$_563:	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	lea	rcx, [rbp-0x8C0]
	call	ExpandHllProc@PLT
	cmp	eax, -1
	je	$_662
	cmp	byte ptr [rbp-0x8C0], 0
	jz	$_565
	lea	rcx, [rbp-0x8C0]
	call	AddLineQueue@PLT
	call	RunLineQueue@PLT
	mov	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbx+0x4], 512
	jnz	$_564
	cmp	byte ptr [rbx+0x18], 2
	jnz	$_564
	cmp	dword ptr [ModuleInfo+0x220+rip], 2
	jnz	$_564
	xor	eax, eax
	jmp	$_662

$_564:	jmp	$_563

$_565:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 8
	jnz	$_566
	cmp	byte ptr [rbx+0x18], 44
	je	$_574
	cmp	byte ptr [rbx+0x18], 0
	je	$_574
$_566:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0xC0]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_662
	mov	rsi, qword ptr [rbp-0x60]
	test	rsi, rsi
	jz	$_568
	cmp	byte ptr [rsi+0x18], 7
	jnz	$_568
	mov	qword ptr [rbp-0x8], rsi
	mov	qword ptr [rbp-0x10], rsi
	cmp	byte ptr [rsi+0x19], -128
	jnz	$_567
	jmp	$_581

$_567:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_568
	jmp	$_582

$_568:	cmp	dword ptr [rbp-0x84], 2
	jnz	$_571
	mov	rbx, qword ptr [rbp-0xA8]
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	test	byte ptr [r11+rax], 0x0E
	jz	$_569
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	movzx	ecx, byte ptr [r11+rax+0xA]
	call	GetStdAssume@PLT
	mov	qword ptr [rbp-0x8], rax
	jmp	$_570

$_569:	mov	qword ptr [rbp-0x8], 0
$_570:	jmp	$_573

$_571:	mov	rax, qword ptr [rbp-0x68]
	test	rax, rax
	jnz	$_572
	mov	rax, qword ptr [rbp-0x70]
$_572:	mov	qword ptr [rbp-0x8], rax
$_573:	jmp	$_575

$_574:	mov	qword ptr [rbp-0xA8], 0
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x8], rax
	inc	dword ptr [rbp+0x28]
$_575:	mov	rsi, qword ptr [rbp-0x8]
	test	rsi, rsi
	jnz	$_576
	mov	ecx, 2190
	call	asmerr@PLT
	jmp	$_662

$_576:	mov	rdx, qword ptr [rsi+0x20]
	mov	rcx, qword ptr [rsi+0x40]
	test	byte ptr [rsi+0x15], 0x08
	jz	$_577
	jmp	$_585

$_577:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_578
	test	rcx, rcx
	jz	$_578
	test	byte ptr [rcx+0x15], 0x08
	jz	$_578
	mov	qword ptr [rbp-0x8], rcx
	jmp	$_585

$_578:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_579
	test	rcx, rcx
	jz	$_579
	cmp	byte ptr [rcx+0x19], -128
	jnz	$_579
	mov	qword ptr [rbp-0x10], rcx
	jmp	$_581

	jmp	$_585

$_579:	cmp	byte ptr [rsi+0x19], -60
	jnz	$_584
	cmp	byte ptr [rdx+0x19], -61
	jz	$_580
	cmp	byte ptr [rdx+0x19], -128
	jnz	$_584
$_580:	mov	qword ptr [rbp-0x10], rdx
	cmp	byte ptr [rdx+0x19], -128
	jz	$_581
	jmp	$_582

$_581:	mov	rsi, qword ptr [rbp-0x10]
	cmp	byte ptr [rsi+0x19], -128
	jz	$_582
	mov	ecx, 2190
	call	asmerr@PLT
	jmp	$_662

$_582:	mov	rsi, qword ptr [rbp-0x10]
	mov	rax, qword ptr [rsi+0x40]
	mov	qword ptr [rbp-0x8], rax
	test	rax, rax
	jnz	$_583
	mov	ecx, 2190
	call	asmerr@PLT
	jmp	$_662

$_583:	jmp	$_585

$_584:	mov	ecx, 2190
	call	asmerr@PLT
	jmp	$_662

$_585:	mov	rsi, qword ptr [rbp-0x8]
	mov	qword ptr [rbp-0x10], rsi
	mov	rcx, rsi
	mov	rax, qword ptr [rcx+0x68]
	mov	qword ptr [rbp-0x50], rax
	cmp	byte ptr [Options+0xC6+rip], 0
	jne	$_596
	imul	ebx, dword ptr [rbp-0x3C], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rsi+0x40]
	cmp	byte ptr [rsi+0x18], 2
	jnz	$_587
	test	rcx, rcx
	jz	$_587
	cmp	byte ptr [rcx+0x18], 9
	jnz	$_587
	mov	rax, qword ptr [rcx+0x58]
	test	rax, rax
	jz	$_586
	mov	qword ptr [rbp-0x8C8], rcx
	mov	qword ptr [rax], rcx
	mov	rdx, qword ptr [rcx+0x8]
	lea	rcx, [rbp-0x8C0]
	call	tstrcpy@PLT
$_586:	jmp	$_596

$_587:	cmp	byte ptr [rbx], 91
	jne	$_596
	cmp	byte ptr [rbx+0x48], 46
	jne	$_596
	cmp	qword ptr [rbp-0x68], 0
	je	$_596
	mov	rdi, qword ptr [rbp-0x68]
	test	byte ptr [rdi+0x15], 0xFFFFFF80
	je	$_595
	mov	rcx, qword ptr [rbx+0x68]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x8D0], rax
	test	rax, rax
	je	$_591
	test	byte ptr [rax+0x16], 0x04
	je	$_591
	test	byte ptr [rdi+0x16], 0x08
	jz	$_588
	mov	rax, qword ptr [rdi+0x30]
	mov	qword ptr [rbp-0x8C8], rax
	mov	rdx, qword ptr [rax+0x8]
	lea	rcx, [rbp-0x8C0]
	call	tstrcpy@PLT
	jmp	$_589

$_588:	mov	rcx, qword ptr [rax+0x30]
	mov	rdx, qword ptr [rcx+0x8]
	lea	rcx, [rbp-0x8C0]
	call	tstrcpy@PLT
	lea	rdx, [DS0042+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, qword ptr [rdi+0x8]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	SymFind@PLT
	mov	qword ptr [rbp-0x8C8], rax
$_589:	mov	rax, qword ptr [rbp-0x8C8]
	test	rax, rax
	jz	$_590
	cmp	byte ptr [rax+0x18], 10
	jnz	$_590
	mov	rcx, qword ptr [rax+0x28]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x8C8], rax
$_590:	test	rax, rax
	jz	$_591
	cmp	byte ptr [rax+0x18], 9
	jz	$_591
	mov	qword ptr [rbp-0x8C8], 0
$_591:	test	byte ptr [rdi+0x16], 0x40
	jz	$_595
	and	dword ptr [rdi+0x14], 0xFFBFFFFF
	mov	ecx, dword ptr [ModuleInfo+0x220+rip]
	dec	ecx
	imul	edx, ecx, 24
	add	rdx, qword ptr [rbp+0x30]
	jmp	$_593

$_592:	cmp	byte ptr [rdx], 44
	jz	$_594
	sub	rdx, 24
	dec	ecx
$_593:	cmp	rdx, rbx
	ja	$_592
$_594:	cmp	byte ptr [rdx], 44
	jnz	$_595
	lea	rax, [rdx+0x18]
	mov	qword ptr [rbp-0x8D8], rax
	mov	byte ptr [rdx], 0
	mov	dword ptr [ModuleInfo+0x220+rip], ecx
$_595:	or	byte ptr [rsi+0x15], 0xFFFFFF80
	cmp	qword ptr [rbp-0x8C8], 0
	jz	$_596
	or	byte ptr [rsi+0x16], 0x10
	test	byte ptr [rax+0x16], 0x20
	jz	$_596
	or	byte ptr [rsi+0x16], 0x20
$_596:	mov	rdx, qword ptr [rbp-0x50]
	mov	rcx, qword ptr [rdx+0x8]
	mov	dword ptr [rbp-0x2C], 0
$_597:	test	rcx, rcx
	jz	$_598
	mov	rcx, qword ptr [rcx+0x78]
	inc	dword ptr [rbp-0x2C]
	jmp	$_597

$_598:	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x44], eax
	test	byte ptr [rsi+0x16], 0x20
	jz	$_600
	inc	dword ptr [rbp+0x28]
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
$_599:	cmp	byte ptr [rbx], 0
	jz	$_600
	cmp	byte ptr [rbx], 44
	jz	$_600
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_599

$_600:	movzx	eax, byte ptr [rsi+0x1B]
	cmp	byte ptr [rsi+0x18], 7
	jz	$_601
	mov	rcx, rsi
	call	GetSymOfssize@PLT
$_601:	movzx	edx, byte ptr [rsi+0x1A]
	mov	ecx, eax
	call	get_fasttype@PLT
	mov	al, byte ptr [rax+0xF]
	mov	byte ptr [rbp-0x8D9], al
	test	al, 0x31
	jz	$_602
	call	$_001
	lea	rax, [rbp-0x30]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp+0x30]
	mov	r8d, dword ptr [rbp+0x28]
	mov	edx, dword ptr [rbp-0x2C]
	mov	rcx, rsi
	call	$_014
	mov	dword ptr [rbp-0x40], eax
$_602:	mov	rdx, qword ptr [rbp-0x50]
	mov	rdi, qword ptr [rdx+0x8]
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x38], eax
	test	byte ptr [rdx+0x40], 0x01
	jnz	$_604
	lea	rax, [rbp-0x48]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x20], eax
	xor	r9d, r9d
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp+0x28]
	call	$_375
	cmp	eax, -1
	jz	$_603
	mov	ecx, 2136
	call	asmerr@PLT
	jmp	$_662

$_603:	jmp	$_610

$_604:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	sub	eax, dword ptr [rbp+0x28]
	shr	eax, 1
	mov	dword ptr [rbp-0x8E0], eax
	dec	dword ptr [rbp-0x2C]
	mov	dword ptr [size_vararg+rip], 0
	jmp	$_606

$_605:	mov	rdi, qword ptr [rdi+0x78]
$_606:	test	rdi, rdi
	jz	$_607
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_605
$_607:	mov	eax, dword ptr [rbp-0x2C]
	cmp	dword ptr [rbp-0x8E0], eax
	jl	$_608
	lea	rax, [rbp-0x48]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x8E0]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, rdi
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp+0x28]
	call	$_375
	dec	dword ptr [rbp-0x8E0]
	jmp	$_607

$_608:	mov	rdx, qword ptr [rbp-0x50]
	mov	rdi, qword ptr [rdx+0x8]
$_609:	test	rdi, rdi
	jz	$_610
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_610
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_609

$_610:	test	byte ptr [rbp-0x8D9], 0x04
	jne	$_622
	mov	dword ptr [rbp-0x8E4], 0
$_611:	test	rdi, rdi
	je	$_618
	cmp	dword ptr [rbp-0x2C], 0
	je	$_618
	dec	dword ptr [rbp-0x2C]
	lea	rax, [rbp-0x48]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, rdi
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp+0x28]
	call	$_375
	cmp	eax, -1
	jnz	$_612
	cmp	qword ptr [rbp-0x8C8], 0
	jnz	$_612
	mov	edx, dword ptr [rbp-0x2C]
	mov	ecx, 2033
	call	asmerr@PLT
$_612:	movzx	eax, byte ptr [ModuleInfo+0x1CC+rip]
	lea	rcx, [ModuleInfo+rip]
	mov	eax, dword ptr [rcx+rax*4+0x224]
	cmp	qword ptr [CurrProc+rip], 0
	jz	$_617
	cmp	eax, 21
	jnz	$_617
	call	RunLineQueue@PLT
	mov	eax, dword ptr [rdi+0x50]
	cmp	eax, 4
	jnc	$_613
	mov	eax, 4
$_613:	cmp	eax, 4
	jbe	$_614
	mov	eax, 8
$_614:	add	dword ptr [rbp-0x8E4], eax
	mov	rcx, qword ptr [CurrProc+rip]
	mov	rdx, qword ptr [rcx+0x68]
	mov	rdx, qword ptr [rdx+0x8]
$_615:	test	rdx, rdx
	jz	$_617
	cmp	byte ptr [rdx+0x18], 10
	jz	$_616
	add	dword ptr [rdx+0x28], eax
$_616:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_615

$_617:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_611

$_618:	cmp	dword ptr [rbp-0x8E4], 0
	jz	$_621
	mov	rcx, qword ptr [CurrProc+rip]
	mov	rax, qword ptr [rcx+0x68]
	mov	rdx, qword ptr [rax+0x8]
$_619:	test	rdx, rdx
	jz	$_621
	cmp	byte ptr [rdx+0x18], 10
	jz	$_620
	mov	eax, dword ptr [rbp-0x8E4]
	sub	dword ptr [rdx+0x28], eax
$_620:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_619

$_621:	jmp	$_625

$_622:	mov	dword ptr [rbp-0x2C], 0
$_623:	test	rdi, rdi
	jz	$_625
	test	byte ptr [rdi+0x3B], 0x04
	jnz	$_625
	lea	rax, [rbp-0x48]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, rdi
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp+0x28]
	call	$_375
	cmp	eax, -1
	jnz	$_624
	cmp	qword ptr [rbp-0x8C8], 0
	jnz	$_624
	mov	edx, dword ptr [rbp-0x2C]
	mov	ecx, 2033
	call	asmerr@PLT
$_624:	mov	rdi, qword ptr [rdi+0x78]
	inc	dword ptr [rbp-0x2C]
	jmp	$_623

$_625:	mov	eax, dword ptr [rbp-0x44]
	mov	dword ptr [rbp+0x28], eax
	mov	rdx, qword ptr [rbp-0x50]
	mov	rcx, qword ptr [rbp-0x10]
	cmp	qword ptr [rbp-0x8C8], 0
	jnz	$_627
	cmp	byte ptr [rcx+0x1A], 2
	jnz	$_627
	test	byte ptr [rdx+0x40], 0x01
	jz	$_627
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_627
	cmp	dword ptr [rbp-0x40], 0
	jz	$_626
	mov	edx, dword ptr [rbp-0x40]
	lea	rcx, [DS0043+rip]
	call	AddLineQueueX@PLT
	jmp	$_627

$_626:	lea	rcx, [DS0044+rip]
	call	AddLineQueue@PLT
$_627:	mov	rcx, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbp-0xA8]
	cmp	qword ptr [rbp-0xA8], 0
	jz	$_628
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_628
	test	byte ptr [rbp-0x48], 0x01
	jz	$_628
	cmp	byte ptr [rdx+0x1], 0
	jnz	$_628
	test	byte ptr [rcx+0x15], 0xFFFFFF80
	jnz	$_628
	mov	ecx, 7002
	call	asmerr@PLT
$_628:	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	mov	qword ptr [rbp-0x20], rax
	lea	rdx, [DS0045+rip]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcpy@PLT
	add	qword ptr [rbp-0x20], 6
	cmp	qword ptr [rbp-0x8C8], 0
	jne	$_630
	cmp	byte ptr [rsi+0x18], 2
	jne	$_630
	cmp	qword ptr [rsi+0x50], 0
	je	$_630
	mov	rax, qword ptr [rbp-0x20]
	mov	qword ptr [rbp-0x8F0], rax
	mov	rdx, qword ptr [ModuleInfo+0x68+rip]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcpy@PLT
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrlen@PLT
	add	qword ptr [rbp-0x20], rax
	mov	rdx, qword ptr [rbp-0x20]
	mov	rcx, rsi
	call	Mangle@PLT
	add	qword ptr [rbp-0x20], rax
	inc	dword ptr [rbp-0x3C]
	test	byte ptr [rsi+0x14], 0x08
	jnz	$_630
	or	byte ptr [rsi+0x14], 0x08
	mov	rcx, qword ptr [rsi+0x50]
	inc	dword ptr [rcx+0x8]
	cmp	byte ptr [rsi+0x1A], 0
	jz	$_629
	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	cmp	byte ptr [rsi+0x1A], al
	jz	$_629
	movzx	eax, byte ptr [rsi+0x1A]
	add	eax, 276
	mov	r8, qword ptr [rbp-0x8F0]
	mov	edx, eax
	lea	rcx, [DS0046+rip]
	call	AddLineQueueX@PLT
	jmp	$_630

$_629:	mov	rdx, qword ptr [rbp-0x8F0]
	lea	rcx, [DS0047+rip]
	call	AddLineQueueX@PLT
$_630:	imul	ebx, dword ptr [rbp-0x3C], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp-0x68]
	cmp	qword ptr [rbp-0x8C8], 0
	jnz	$_631
	cmp	byte ptr [rbx], 91
	jne	$_652
	cmp	byte ptr [rbx+0x48], 46
	jne	$_652
	test	rcx, rcx
	je	$_652
	test	byte ptr [rcx+0x15], 0xFFFFFF80
	je	$_652
$_631:	cmp	qword ptr [rbp-0x8C8], 0
	je	$_648
	mov	dword ptr [rbp-0x8F4], 0
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	inc	rcx
	mov	qword ptr [rbp-0x20], rcx
	lea	rdx, [rbp-0x8C0]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcpy@PLT
	lea	rdx, [DS0048+rip]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcat@PLT
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrlen@PLT
	add	qword ptr [rbp-0x20], rax
	test	byte ptr [rbp-0x8D9], 0x31
	je	$_637
	mov	rdx, qword ptr [rbp-0x50]
	mov	rdi, qword ptr [rdx+0x8]
$_632:	test	rdi, rdi
	je	$_637
	mov	rax, qword ptr [rdi+0x8]
	cmp	byte ptr [rdi+0x19], -62
	jnz	$_633
	lea	rdx, [DS0048+0x2+rip]
	mov	qword ptr [rdi+0x8], rdx
	jmp	$_636

$_633:	cmp	byte ptr [rdi+0x18], 10
	jnz	$_634
	mov	rax, qword ptr [rdi+0x28]
	jmp	$_636

$_634:	test	byte ptr [rdi+0x17], 0x01
	jz	$_635
	movzx	ecx, byte ptr [rdi+0x48]
	lea	rdx, [rbp-0xB08]
	call	GetResWName@PLT
	mov	rcx, rax
	call	LclDup@PLT
	jmp	$_636

$_635:	movzx	eax, byte ptr [rdi+0x38]
	lea	rdx, [stackreg+rip]
	mov	edx, dword ptr [rdx+rax*4]
	movzx	ecx, byte ptr [rdi+0x4B]
	mov	r9d, ecx
	mov	r8d, edx
	lea	rdx, [DS0049+rip]
	lea	rcx, [rbp-0xB08]
	call	tsprintf@PLT
	lea	rcx, [rbp-0xB08]
	call	LclDup@PLT
$_636:	movzx	ecx, byte ptr [rdi+0x49]
	mov	qword ptr [rbp+rcx*8-0xAF8], rax
	mov	rdi, qword ptr [rdi+0x78]
	inc	dword ptr [rbp-0x8F4]
	jmp	$_632

$_637:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbp-0x50]
	mov	rdi, qword ptr [rbp-0x10]
	cmp	dword ptr [rbp-0x8F4], 0
	jnz	$_640
	cmp	byte ptr [rbx], 0
	jz	$_639
	mov	rdx, qword ptr [rbx+0x28]
	test	byte ptr [rdi+0x16], 0x20
	jz	$_638
	mov	rdx, qword ptr [rbx+0x40]
$_638:	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcat@PLT
$_639:	jmp	$_647

$_640:	test	byte ptr [rdx+0x40], 0x01
	jz	$_642
	mov	rdx, qword ptr [rbx+0x28]
	cmp	dword ptr [rbx+0x1C], 273
	jnz	$_641
	test	byte ptr [rdi+0x15], 0xFFFFFF80
	jz	$_641
	mov	rdx, qword ptr [rbx+0x40]
$_641:	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcat@PLT
	jmp	$_647

$_642:	mov	esi, 1
	mov	rdx, qword ptr [rbp-0xAF8]
	test	byte ptr [rdi+0x16], 0x20
	jz	$_643
	mov	rdx, qword ptr [rbx+0x38]
	xor	esi, esi
$_643:	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcat@PLT
$_644:	cmp	esi, dword ptr [rbp-0x8F4]
	jge	$_646
	lea	rdx, [DS004A+rip]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcat@PLT
	cmp	qword ptr [rbp+rsi*8-0xAF8], 0
	jz	$_645
	mov	rdx, qword ptr [rbp+rsi*8-0xAF8]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcat@PLT
$_645:	inc	esi
	jmp	$_644

$_646:	mov	rsi, qword ptr [rbp-0x8]
$_647:	lea	rdx, [DS0040+0xA+rip]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcat@PLT
$_648:	cmp	qword ptr [rbp-0x8D8], 0
	jz	$_650
	mov	edi, 115
	cmp	byte ptr [rsi+0x1A], 2
	jnz	$_649
	mov	edi, 125
$_649:	mov	rbx, qword ptr [rbp-0x8D8]
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rcx, rax
	mov	rax, qword ptr [rbp-0x8C8]
	mov	qword ptr [rsp+0x28], rax
	movzx	eax, byte ptr [rsi+0x1A]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x8D0]
	mov	r8, qword ptr [rbp-0x8D8]
	mov	edx, edi
	call	AssignPointer@PLT
	jmp	$_652

$_650:	cmp	qword ptr [rbp-0x8C8], 0
	jnz	$_652
	imul	ebx, dword ptr [rbp-0x38], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_652
	cmp	byte ptr [rsi+0x1A], 2
	jnz	$_651
	lea	rcx, [DS004B+rip]
	call	AddLineQueue@PLT
	jmp	$_652

$_651:	lea	rcx, [DS004C+rip]
	call	AddLineQueue@PLT
$_652:	mov	rbx, qword ptr [rbp+0x30]
	imul	edx, dword ptr [rbp-0x38], 24
	imul	ecx, dword ptr [rbp-0x3C], 24
	cmp	qword ptr [rbp-0x8C8], 0
	jnz	$_653
	mov	rax, qword ptr [rbx+rdx+0x10]
	sub	rax, qword ptr [rbx+rcx+0x10]
	mov	dword ptr [rbp-0x34], eax
	mov	r8d, dword ptr [rbp-0x34]
	mov	rdx, qword ptr [rbx+rcx+0x10]
	mov	rcx, qword ptr [rbp-0x20]
	call	tmemcpy@PLT
	mov	edx, dword ptr [rbp-0x34]
	mov	byte ptr [rax+rdx], 0
$_653:	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	AddLineQueue@PLT
	mov	rdi, qword ptr [rbp-0x50]
	mov	rsi, qword ptr [rbp-0x8]
	cmp	byte ptr [rsi+0x1A], 1
	jz	$_654
	cmp	byte ptr [rsi+0x1A], 2
	jne	$_659
	test	byte ptr [rbp-0x8D9], 0x31
	jnz	$_659
$_654:	cmp	dword ptr [rdi+0x20], 0
	jnz	$_655
	test	byte ptr [rdi+0x40], 0x01
	jz	$_659
	cmp	dword ptr [size_vararg+rip], 0
	jz	$_659
$_655:	movzx	eax, byte ptr [ModuleInfo+0x1CC+rip]
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jnz	$_656
	cmp	qword ptr [ModuleInfo+0x148+rip], 0
	jz	$_656
	mov	ecx, 2
	call	GetOfssizeAssume@PLT
$_656:	lea	rdx, [stackreg+rip]
	mov	eax, dword ptr [rdx+rax*4]
	test	byte ptr [rdi+0x40], 0x01
	jz	$_657
	mov	ecx, dword ptr [rdi+0x20]
	add	ecx, dword ptr [size_vararg+rip]
	mov	r8d, ecx
	mov	edx, eax
	lea	rcx, [DS004D+rip]
	call	AddLineQueueX@PLT
	jmp	$_658

$_657:	mov	r8d, dword ptr [rdi+0x20]
	mov	edx, eax
	lea	rcx, [DS004D+rip]
	call	AddLineQueueX@PLT
$_658:	jmp	$_660

$_659:	test	byte ptr [rbp-0x8D9], 0x31
	jz	$_660
	mov	r8d, dword ptr [rbp-0x30]
	mov	edx, dword ptr [rbp-0x2C]
	mov	rcx, qword ptr [rbp-0x10]
	call	$_055
$_660:	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
	call	RunLineQueue@PLT
	mov	rcx, qword ptr [rbp-0x8C8]
	test	rcx, rcx
	jz	$_661
	cmp	qword ptr [rcx+0x58], 0
	jz	$_661
	mov	rdx, qword ptr [rcx+0x58]
	mov	qword ptr [rdx], rsi
$_661:	xor	eax, eax
$_662:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

size_vararg:
	.int   0x00000000

simd_scratch:
	.int   0x00000000

wreg_scratch:
	.int   0x00000000

DS0000:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x73, 0x70
	.byte  0x2C, 0x20, 0x25, 0x64, 0x00

DS0001:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x73, 0x70
	.byte  0x2C, 0x20, 0x38, 0x00

DS0002:
	.byte  0x20, 0x61, 0x64, 0x64, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x64, 0x00

DS0003:
	.byte  0x20, 0x6C, 0x65, 0x61, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS0004:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x75, 0x0A, 0x20, 0x25, 0x72, 0x20
	.byte  0x5B, 0x25, 0x72, 0x5D, 0x2C, 0x20, 0x25, 0x72
	.byte  0x00

DS0005:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x72, 0x00

DS0006:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x75
	.byte  0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25
	.byte  0x75, 0x00

DS0007:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x34, 0x5D, 0x0A, 0x20, 0x70
	.byte  0x75, 0x73, 0x68, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x5B, 0x30, 0x5D, 0x00

DS0008:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x75
	.byte  0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25
	.byte  0x75, 0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20
	.byte  0x25, 0x75, 0x0A, 0x20, 0x70, 0x75, 0x73, 0x68
	.byte  0x20, 0x25, 0x75, 0x00

DS0009:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x31, 0x36, 0x00

DS000A:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x71, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20
	.byte  0x30, 0x00

DS000B:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x25, 0x75, 0x5D, 0x5B, 0x30
	.byte  0x5D, 0x2C, 0x20, 0x25, 0x75, 0x0A, 0x20, 0x6D
	.byte  0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x5B, 0x25, 0x72
	.byte  0x2B, 0x25, 0x75, 0x5D, 0x5B, 0x34, 0x5D, 0x2C
	.byte  0x20, 0x25, 0x75, 0x00

DS000C:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x25, 0x75, 0x5D, 0x5B, 0x38
	.byte  0x5D, 0x2C, 0x20, 0x25, 0x75, 0x0A, 0x20, 0x6D
	.byte  0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x5B, 0x25, 0x72
	.byte  0x2B, 0x25, 0x75, 0x5D, 0x5B, 0x31, 0x32, 0x5D
	.byte  0x2C, 0x20, 0x25, 0x75, 0x00

DS000D:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x78, 0x6D, 0x6D, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS000E:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x75, 0x00

DS000F:
	.byte  0x20, 0x25, 0x72, 0x20, 0x5B, 0x25, 0x72, 0x2B
	.byte  0x25, 0x75, 0x5D, 0x2C, 0x20, 0x25, 0x72, 0x00

DS0010:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x72, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x00

DS0011:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x25, 0x72
	.byte  0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20, 0x25, 0x72
	.byte  0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x5B, 0x25, 0x72
	.byte  0x2B, 0x25, 0x75, 0x2B, 0x25, 0x75, 0x5D, 0x2C
	.byte  0x20, 0x30, 0x00

DS0012:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x30, 0x0A
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72
	.byte  0x00

DS0013:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x72, 0x00

DS0014:
	.byte  0x20, 0x78, 0x6F, 0x72, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x72, 0x00

DS0015:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x25, 0x72
	.byte  0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20, 0x25, 0x72
	.byte  0x00

DS0016:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x6C, 0x75, 0x00

DS0017:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x2D, 0x31, 0x00

DS0018:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x75, 0x00

DS0019:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x72, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x25, 0x75, 0x5D, 0x00

DS001A:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x25, 0x72
	.byte  0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20, 0x25, 0x72
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS001B:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x71, 0x20, 0x25, 0x72
	.byte  0x2C, 0x20, 0x25, 0x72, 0x00

DS001C:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x25, 0x72, 0x00

DS001D:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20
	.byte  0x25, 0x75, 0x00

DS001E:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x78, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS001F:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x64, 0x20, 0x25, 0x72
	.byte  0x2C, 0x20, 0x65, 0x61, 0x78, 0x00

DS0020:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x64
	.byte  0x00

DS0021:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x73
	.byte  0x00

DS0022:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x73, 0x00

DS0023:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS0024:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x34, 0x5D, 0x0A, 0x20, 0x70
	.byte  0x75, 0x73, 0x68, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x00

DS0025:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x64, 0x20, 0x25
	.byte  0x72, 0x2C, 0x20, 0x25, 0x73, 0x00

DS0026:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20
	.byte  0x6C, 0x6F, 0x77, 0x33, 0x32, 0x28, 0x25, 0x73
	.byte  0x29, 0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64
	.byte  0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72
	.byte  0x20, 0x5B, 0x25, 0x72, 0x2B, 0x25, 0x75, 0x2B
	.byte  0x34, 0x5D, 0x2C, 0x20, 0x68, 0x69, 0x67, 0x68
	.byte  0x33, 0x32, 0x28, 0x25, 0x73, 0x29, 0x00

DS0027:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x70, 0x75, 0x73
	.byte  0x68, 0x20, 0x25, 0x72, 0x00

DS0028:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x5B, 0x25, 0x72, 0x2B
	.byte  0x25, 0x75, 0x5D, 0x2C, 0x20, 0x25, 0x73, 0x00

DS0029:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x30, 0x00

DS002A:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x72, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x25, 0x75, 0x5D, 0x00

DS002B:
	.byte  0x20, 0x73, 0x68, 0x6C, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x31, 0x36, 0x0A, 0x20, 0x6D, 0x6F, 0x76
	.byte  0x20, 0x25, 0x72, 0x2C, 0x20, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x5B, 0x25, 0x75, 0x5D, 0x00

DS002C:
	.byte  0x20, 0x73, 0x68, 0x6C, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x38, 0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x62, 0x79, 0x74, 0x65
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS002D:
	.byte  0x73, 0x65, 0x67, 0x20, 0x00

DS002E:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x73, 0x78, 0x20, 0x65
	.byte  0x61, 0x78, 0x2C, 0x20, 0x25, 0x73, 0x0A, 0x20
	.byte  0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72, 0x00

DS002F:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x6C, 0x2C
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x70, 0x75, 0x73
	.byte  0x68, 0x20, 0x25, 0x72, 0x00

DS0030:
	.byte  0x20, 0x25, 0x72, 0x20, 0x65, 0x61, 0x78, 0x2C
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x70, 0x75, 0x73
	.byte  0x68, 0x20, 0x25, 0x72, 0x00

DS0031:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x78, 0x2C
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x70, 0x75, 0x73
	.byte  0x68, 0x20, 0x72, 0x61, 0x78, 0x00

DS0032:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x65, 0x61, 0x78
	.byte  0x2C, 0x20, 0x25, 0x73, 0x0A, 0x20, 0x70, 0x75
	.byte  0x73, 0x68, 0x20, 0x72, 0x61, 0x78, 0x00

DS0033:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x6C, 0x2C
	.byte  0x20, 0x62, 0x79, 0x74, 0x65, 0x20, 0x70, 0x74
	.byte  0x72, 0x20, 0x25, 0x73, 0x5B, 0x32, 0x5D, 0x0A
	.byte  0x20, 0x73, 0x68, 0x6C, 0x20, 0x65, 0x61, 0x78
	.byte  0x2C, 0x20, 0x31, 0x36, 0x0A, 0x20, 0x6D, 0x6F
	.byte  0x76, 0x20, 0x61, 0x78, 0x2C, 0x20, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20
	.byte  0x25, 0x72, 0x00

DS0034:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x32, 0x5D, 0x0A, 0x20, 0x70, 0x75
	.byte  0x73, 0x68, 0x20, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS0035:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x6C, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS0036:
	.byte  0x20, 0x63, 0x62, 0x77, 0x00

DS0037:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x68, 0x2C
	.byte  0x20, 0x30, 0x00

DS0038:
	.byte  0x20, 0x78, 0x6F, 0x72, 0x20, 0x61, 0x78, 0x2C
	.byte  0x20, 0x61, 0x78, 0x00

DS0039:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x78, 0x2C
	.byte  0x20, 0x68, 0x69, 0x67, 0x68, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x28, 0x25, 0x73, 0x29, 0x00

DS003A:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x61, 0x78
	.byte  0x00

DS003B:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x78, 0x2C
	.byte  0x20, 0x6C, 0x6F, 0x77, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x28, 0x25, 0x73, 0x29, 0x00

DS003C:
	.byte  0x20, 0x25, 0x72, 0x20, 0x28, 0x25, 0x73, 0x29
	.byte  0x20, 0x73, 0x68, 0x72, 0x20, 0x33, 0x32, 0x74
	.byte  0x00

DS003D:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x30, 0x78
	.byte  0x25, 0x78, 0x00

DS003E:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x72, 0x61, 0x78
	.byte  0x2C, 0x20, 0x30, 0x78, 0x25, 0x6C, 0x78, 0x0A
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61
	.byte  0x78, 0x00

DS003F:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x30, 0x78
	.byte  0x25, 0x6C, 0x78, 0x00

DS0040:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x20, 0x28
	.byte  0x25, 0x73, 0x29, 0x00

DS0041:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x73, 0x00

DS0042:
	.byte  0x5F, 0x00

DS0043:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x65, 0x61, 0x78
	.byte  0x2C, 0x20, 0x25, 0x64, 0x00

DS0044:
	.byte  0x20, 0x78, 0x6F, 0x72, 0x20, 0x65, 0x61, 0x78
	.byte  0x2C, 0x20, 0x65, 0x61, 0x78, 0x00

DS0045:
	.byte  0x20, 0x63, 0x61, 0x6C, 0x6C, 0x20, 0x00

DS0046:
	.byte  0x20, 0x65, 0x78, 0x74, 0x65, 0x72, 0x6E, 0x64
	.byte  0x65, 0x66, 0x20, 0x25, 0x72, 0x20, 0x25, 0x73
	.byte  0x3A, 0x20, 0x70, 0x74, 0x72, 0x20, 0x70, 0x72
	.byte  0x6F, 0x63, 0x00

DS0047:
	.byte  0x20, 0x65, 0x78, 0x74, 0x65, 0x72, 0x6E, 0x64
	.byte  0x65, 0x66, 0x20, 0x25, 0x73, 0x3A, 0x20, 0x70
	.byte  0x74, 0x72, 0x20, 0x70, 0x72, 0x6F, 0x63, 0x00

DS0048:
	.byte  0x28, 0x20, 0x00

DS0049:
	.byte  0x5B, 0x25, 0x72, 0x2B, 0x25, 0x75, 0x5D, 0x00

DS004A:
	.byte  0x2C, 0x20, 0x00

DS004B:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x72, 0x31, 0x30
	.byte  0x2C, 0x20, 0x5B, 0x72, 0x64, 0x69, 0x5D, 0x00

DS004C:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x72, 0x61, 0x78
	.byte  0x2C, 0x20, 0x5B, 0x72, 0x63, 0x78, 0x5D, 0x00

DS004D:
	.byte  0x20, 0x61, 0x64, 0x64, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x75, 0x00


.att_syntax prefix
