
.intel_syntax noprefix

.global ProcType
.global MacroInline
.global ClassDirective
.global ClassInit
.global ClassCheckOpen

.extern OperatorParam
.extern GetOpType
.extern GetOperator
.extern MacroLineQueue
.extern SearchNameInStruct
.extern CurrStruct
.extern LclAlloc
.extern MemFree
.extern MemAlloc
.extern LstWrite
.extern GetResWName
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern SpecialTable
.extern GetCurrOffset
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern tmemicmp
.extern tsprintf
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass
.extern NameSpace_
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 1072
	lea	rdi, [rbp-0x400]
	mov	rsi, r8
	lea	rcx, [rdi+0x3FF]
	mov	al, 1
	jmp	$_007

$_002:	lodsb
	cmp	al, 61
	jnz	$_006
	lodsb
	jmp	$_004

$_003:	lodsb
$_004:	test	al, al
	jz	$_005
	cmp	al, 62
	jnz	$_003
$_005:	test	al, al
	jz	$_006
	lodsb
$_006:	stosb
$_007:	test	al, al
	jz	$_008
	cmp	rdi, rcx
	jc	$_002
$_008:	cmp	dword ptr [rbp+0x28], 0
	jz	$_009
	lea	rax, [rbp-0x400]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp+0x28]
	mov	r8d, dword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	jmp	$_010

$_009:	lea	r9, [rbp-0x400]
	mov	r8d, dword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
$_010:	leave
	pop	rdi
	pop	rsi
	ret

$_011:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 1064
	mov	rsi, r8
	mov	rdi, qword ptr [rbp+0x40]
	mov	rbx, qword ptr [rbp+0x48]
	test	rbx, rbx
	jnz	$_012
	lea	rbx, [rbp-0x200]
	mov	r8, qword ptr [rbp+0x28]
	lea	rdx, [DS0002+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
$_012:	mov	r9, qword ptr [rbp+0x30]
	mov	r8, qword ptr [rbp+0x28]
	lea	rdx, [DS0003+rip]
	lea	rcx, [rbp-0x100]
	call	tsprintf@PLT
	cmp	dword ptr [rsi+0x20], 407
	jz	$_015
	cmp	byte ptr [rdi], 0
	jz	$_013
	mov	r9, rdi
	mov	r8, rbx
	lea	rdx, [DS0004+rip]
	lea	rcx, [rbp-0x400]
	call	tsprintf@PLT
	jmp	$_014

$_013:	mov	r8, rbx
	lea	rdx, [DS0005+rip]
	lea	rcx, [rbp-0x400]
	call	tsprintf@PLT
$_014:	lea	rdi, [rbp-0x400]
$_015:	mov	r9d, 507
	mov	r8, rdi
	mov	edx, dword ptr [rsi+0x10]
	lea	rcx, [rbp-0x100]
	call	$_001
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_016:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 552
	mov	rsi, rcx
	mov	rbx, rdx
	cmp	dword ptr [rbx+0x50], 0
	je	$_021
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_021
	mov	rdx, qword ptr [rbx+0x68]
	mov	rdi, qword ptr [rdx]
$_017:	test	rdi, rdi
	je	$_021
	cmp	qword ptr [rdi+0x20], 0
	jz	$_020
	mov	rdx, qword ptr [rdi+0x20]
	cmp	word ptr [rdx+0x5A], 1
	jnz	$_018
	mov	rcx, rsi
	call	$_016
	jmp	$_020

$_018:	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [rbp-0x200]
	call	tstrcpy@PLT
	mov	ecx, dword ptr [rbx+0x10]
	mov	word ptr [rax+rcx-0x4], 95
	mov	rdx, qword ptr [rdi+0x8]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jz	$_020
	mov	rdx, qword ptr [rax+0x8]
	cmp	byte ptr [rax+0x18], 10
	jnz	$_019
	mov	rdx, qword ptr [rax+0x28]
$_019:	mov	r9, rdx
	mov	r8, qword ptr [rdi+0x8]
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
$_020:	mov	rdi, qword ptr [rdi+0x68]
	jmp	$_017

$_021:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_022:
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 544
	mov	rsi, rcx
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS0007+rip]
	call	AddLineQueueX@PLT
	mov	rdx, qword ptr [rsi+0x18]
	test	rdx, rdx
	jnz	$_023
	xor	eax, eax
	jmp	$_025

$_023:	mov	rdx, qword ptr [rdx+0x8]
	lea	rcx, [rbp-0x200]
	call	tstrcpy@PLT
	lea	rdx, [DS0008+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jnz	$_024
	mov	eax, 1
	jmp	$_025

$_024:	mov	rbx, rax
	xor	eax, eax
	cmp	dword ptr [rbx+0x50], 0
	jz	$_025
	lea	rdx, [rbp-0x200]
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
	mov	rdx, rbx
	mov	rcx, rsi
	call	$_016
	mov	eax, 1
$_025:	leave
	pop	rbx
	pop	rsi
	ret

$_026:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	byte ptr [rbp-0x1], 0
	mov	rdi, rdx
	mov	rbx, rcx
	mov	rsi, qword ptr [rbx+0x10]
	xor	eax, eax
	mov	rcx, qword ptr [rbp+0x48]
	mov	qword ptr [rcx], rax
	mov	rcx, qword ptr [rbp+0x40]
	mov	dword ptr [rcx], eax
	mov	rdx, rdi
	mov	rcx, rbx
	call	GetOpType@PLT
	cmp	eax, -1
	jnz	$_028
	cmp	byte ptr [rbx], 8
	jz	$_027
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_035

$_027:	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rcx, qword ptr [rbp+0x40]
	inc	dword ptr [rcx]
	add	rbx, 24
	jmp	$_029

$_028:	mov	rbx, rax
	inc	byte ptr [rbp-0x1]
$_029:	cmp	byte ptr [rbx], 7
	jnz	$_030
	mov	rcx, qword ptr [rbp+0x50]
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rcx], eax
	add	rbx, 24
$_030:	mov	rdi, rbx
	mov	esi, 1
$_031:	cmp	byte ptr [rbx], 0
	jz	$_034
	cmp	byte ptr [rbx], 9
	jnz	$_032
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_032
	mov	rcx, qword ptr [rbp+0x48]
	mov	qword ptr [rcx], rbx
	jmp	$_034

	jmp	$_033

$_032:	cmp	byte ptr [rbx], 58
	jnz	$_033
	inc	esi
	cmp	byte ptr [rbp-0x1], 0
	jz	$_033
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbx+0x18]
	call	OperatorParam@PLT
$_033:	add	rbx, 24
	jmp	$_031

$_034:	mov	rcx, qword ptr [rbp+0x38]
	mov	dword ptr [rcx], esi
	mov	rax, rdi
$_035:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ProcType:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 152
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	call	MemAlloc@PLT
	mov	qword ptr [rbp-0x68], rax
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x5C], 0
	mov	dword ptr [rbp-0x38], 0
	mov	rax, qword ptr [rbx-0x10]
	mov	qword ptr [rbp-0x10], rax
	mov	dword ptr [rbp-0x4], 0
	mov	rsi, qword ptr [ModuleInfo+0x108+rip]
	test	rsi, rsi
	jz	$_036
	mov	eax, dword ptr [rsi+0x10]
	mov	dword ptr [rbp-0x38], eax
	mov	rdx, qword ptr [rbp-0x10]
	mov	rax, qword ptr [rbp-0x10]
	call	NameSpace_@PLT
	mov	rdi, rax
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rdi
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_036
	mov	qword ptr [rsp+0x20], 0
	mov	r9, qword ptr [rbx+0x28]
	mov	r8, rsi
	mov	rdx, rdi
	mov	rcx, rdi
	call	$_011
	mov	dword ptr [rbp-0x5C], 1
	jmp	$_056

$_036:	mov	byte ptr [rbp-0x11], 0
	mov	rax, qword ptr [CurrStruct+rip]
	test	rax, rax
	jz	$_037
	mov	rdi, qword ptr [rax+0x8]
	mov	rcx, rdi
	call	tstrlen@PLT
	cmp	rax, 4
	jbe	$_037
	mov	eax, dword ptr [rdi+rax-0x4]
$_037:	mov	rdi, qword ptr [rbp-0x68]
	cmp	eax, 1818391638
	jnz	$_038
	inc	byte ptr [rbp-0x11]
	jmp	$_040

$_038:	test	rsi, rsi
	jz	$_040
	cmp	dword ptr [ModuleInfo+0x220+rip], 2
	jle	$_039
	cmp	dword ptr [rbx+0x1C], 510
	jnz	$_039
	add	rbx, 24
	jmp	$_040

$_039:	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
	mov	rcx, rsi
	call	$_022
	mov	dword ptr [rbp-0x4], eax
	inc	byte ptr [rbp-0x11]
$_040:	inc	dword ptr [ModuleInfo+0x348+rip]
	mov	r8d, dword ptr [ModuleInfo+0x348+rip]
	lea	rdx, [DS000B+rip]
	lea	rcx, [rbp-0x58]
	call	tsprintf@PLT
	mov	r8d, dword ptr [ModuleInfo+0x348+rip]
	lea	rdx, [DS000C+rip]
	lea	rcx, [rbp-0x48]
	call	tsprintf@PLT
	lea	rdx, [rbp-0x58]
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdx, [DS000D+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	test	rsi, rsi
	jz	$_041
	cmp	dword ptr [rsi], 403
	jnz	$_041
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 1
	jnz	$_041
	cmp	byte ptr [ModuleInfo+0x1B6+rip], 3
	jz	$_041
	lea	rdx, [DS000E+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_041:	add	rbx, 24
	xor	esi, esi
	cmp	byte ptr [rbx], 0
	je	$_050
	cmp	byte ptr [rbp-0x11], 0
	je	$_046
	cmp	dword ptr [rbx+0x4], 277
	jc	$_042
	cmp	dword ptr [rbx+0x4], 286
	ja	$_042
	inc	esi
$_042:	cmp	byte ptr [rbx+0x18], 0
	jz	$_043
	test	esi, esi
	jnz	$_043
	cmp	byte ptr [rbx], 58
	jz	$_044
	cmp	byte ptr [rbx+0x18], 58
	jz	$_044
$_043:	lea	rdx, [DS000F+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcat@PLT
	add	rbx, 24
	jmp	$_045

$_044:	test	esi, esi
	jnz	$_045
	cmp	dword ptr [rbp-0x38], 0
	jz	$_045
	lea	rdx, [rbp-0x31]
	mov	ecx, dword ptr [rbp-0x38]
	call	GetResWName@PLT
	lea	rdx, [DS000F+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [rbp-0x31]
	mov	rcx, rdi
	call	tstrcat@PLT
$_045:	xor	esi, esi
$_046:	mov	rax, rbx
$_047:	cmp	byte ptr [rax], 0
	jz	$_049
	cmp	byte ptr [rax], 58
	jnz	$_048
	inc	esi
	jmp	$_049

$_048:	add	rax, 24
	jmp	$_047

$_049:	jmp	$_051

$_050:	cmp	byte ptr [rbp-0x11], 0
	jz	$_051
	cmp	qword ptr [ModuleInfo+0x108+rip], 0
	jz	$_051
	mov	rax, qword ptr [ModuleInfo+0x108+rip]
	mov	ecx, dword ptr [rax+0x10]
	test	ecx, ecx
	jz	$_051
	lea	rdx, [rbp-0x31]
	call	GetResWName@PLT
	lea	rdx, [DS000F+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [rbp-0x31]
	mov	rcx, rdi
	call	tstrcat@PLT
$_051:	mov	rax, qword ptr [ModuleInfo+0x108+rip]
	test	rax, rax
	jz	$_052
	cmp	dword ptr [rax+0x20], 407
	jz	$_052
	xor	eax, eax
$_052:	cmp	byte ptr [rbp-0x11], 0
	jz	$_054
	test	rax, rax
	jnz	$_054
	lea	rdx, [DS0010+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rax, qword ptr [ModuleInfo+0x108+rip]
	test	rax, rax
	jz	$_053
	cmp	dword ptr [rax], 402
	jnz	$_053
	lea	rdx, [DS000F+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rax, qword ptr [ModuleInfo+0x108+rip]
	mov	rdx, qword ptr [rax+0x8]
	mov	rcx, rdi
	call	tstrcat@PLT
$_053:	test	rsi, rsi
	jz	$_054
	lea	rdx, [DS0011+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_054:	test	rsi, rsi
	jz	$_055
	lea	rdx, [DS000F+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rdi
	call	tstrcat@PLT
$_055:	mov	rcx, rdi
	call	AddLineQueue@PLT
	lea	r8, [rbp-0x58]
	lea	rdx, [rbp-0x48]
	lea	rcx, [DS0012+rip]
	call	AddLineQueueX@PLT
	lea	r8, [rbp-0x48]
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
$_056:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_057
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_057:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_058
	call	RunLineQueue@PLT
$_058:	cmp	dword ptr [rbp-0x5C], 0
	jz	$_059
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x68]
	call	tstrcpy@PLT
	lea	rdx, [DS0014+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, rdi
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jz	$_059
	or	byte ptr [rax+0x15], 0xFFFFFF80
$_059:	mov	rcx, qword ptr [rbp-0x68]
	call	MemFree@PLT
	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_060:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, qword ptr [rbp+0x38]
	mov	rdi, qword ptr [rbp+0x28]
	mov	esi, 1
$_061:	cmp	esi, dword ptr [rbp+0x30]
	jge	$_072
	mov	rcx, rbx
	jmp	$_063

$_062:	add	rcx, 1
$_063:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_062
	xchg	rax, rcx
	mov	rbx, rax
	movzx	eax, cl
	test	byte ptr [r15+rax], 0x44
	jnz	$_064
	mov	r8d, esi
	lea	rdx, [DS0015+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, rax
	jmp	$_067

$_064:	jmp	$_066

$_065:	stosb
	inc	rbx
$_066:	movzx	eax, byte ptr [rbx]
	test	byte ptr [r15+rax], 0x44
	jnz	$_065
	mov	eax, 8236
	stosw
	mov	byte ptr [rdi], 0
$_067:	mov	edx, 44
	mov	rcx, rbx
	call	tstrchr@PLT
	test	rax, rax
	jz	$_068
	inc	rax
	jmp	$_069

$_068:	mov	rcx, rbx
	call	tstrlen@PLT
	add	rax, rbx
$_069:	xchg	rax, rbx
	mov	edx, 61
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jz	$_071
	cmp	rax, rbx
	jnc	$_071
	dec	rdi
	mov	byte ptr [rdi-0x1], 58
	mov	rcx, rbx
	sub	rcx, rax
	cmp	byte ptr [rbx-0x1], 44
	jnz	$_070
	dec	ecx
$_070:	mov	rdx, rsi
	mov	rsi, rax
	rep movsb
	mov	rsi, rdx
	mov	dword ptr [rdi], 8236
	add	rdi, 2
$_071:	inc	esi
	jmp	$_061

$_072:
	mov	rax, rdi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

MacroInline:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 1064
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_073
	xor	eax, eax
	jmp	$_087

$_073:	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0x200]
	call	tstrcpy@PLT
	mov	byte ptr [rbp-0x400], 0
	lea	rdi, [rbp-0x400]
	mov	rbx, qword ptr [ModuleInfo+0x180+rip]
	cmp	dword ptr [rbx+0x1C], 507
	jnz	$_075
	mov	edx, dword ptr [rbp+0x30]
	test	edx, edx
	jz	$_074
	inc	edx
	lea	r8, [rbp-0x200]
	mov	rcx, rdi
	call	$_060
	mov	rdi, rax
	sub	rdi, 2
$_074:	mov	byte ptr [rdi], 0
	jmp	$_076

$_075:	lea	rdx, [DS0016+rip]
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdi, [rax+0x4]
	cmp	dword ptr [rbp+0x30], 1
	jle	$_076
	lea	rdx, [DS0015+0x3+rip]
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdi, [rax+0x2]
	lea	r8, [rbp-0x200]
	mov	edx, dword ptr [rbp+0x30]
	mov	rcx, rdi
	call	$_060
	mov	rdi, rax
	sub	rdi, 2
	mov	byte ptr [rdi], 0
$_076:	cmp	dword ptr [rbp+0x48], 0
	jz	$_077
	lea	rdx, [DS0017+rip]
	mov	rcx, rdi
	call	tstrcpy@PLT
$_077:	lea	r8, [rbp-0x400]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0018+rip]
	call	AddLineQueueX@PLT
	mov	rsi, qword ptr [rbp+0x40]
	jmp	$_079

$_078:	inc	rsi
$_079:	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x08
	jnz	$_078
	xor	rdi, rdi
$_080:	mov	edx, 10
	mov	rcx, rsi
	call	tstrchr@PLT
	test	rax, rax
	jz	$_082
	mov	rbx, rax
	mov	byte ptr [rbx], 0
	cmp	byte ptr [rsi], 0
	jz	$_081
	mov	rdi, rsi
	mov	rcx, rsi
	call	AddLineQueue@PLT
$_081:	mov	byte ptr [rbx], 10
	lea	rsi, [rbx+0x1]
	jmp	$_080

$_082:	cmp	byte ptr [rsi], 0
	jz	$_083
	mov	rdi, rsi
	mov	rcx, rsi
	call	AddLineQueue@PLT
$_083:	test	rdi, rdi
	jnz	$_084
	lea	rcx, [DS0019+rip]
	call	AddLineQueue@PLT
	jmp	$_086

$_084:	mov	r8d, 5
	lea	rdx, [DS001A+rip]
	mov	rcx, rdi
	call	tmemicmp@PLT
	test	eax, eax
	jz	$_085
	mov	r8d, 4
	lea	rdx, [DS001B+rip]
	mov	rcx, rdi
	call	tmemicmp@PLT
$_085:	test	eax, eax
	jz	$_086
	lea	rcx, [DS0019+rip]
	call	AddLineQueue@PLT
$_086:	lea	rcx, [DS001C+rip]
	call	AddLineQueue@PLT
	call	MacroLineQueue@PLT
$_087:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ClassDirective:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 1656
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x10], 0
	mov	dword ptr [rbp-0x14], 0
	mov	word ptr [rbp-0x40], 0
	mov	rbx, rdx
	lea	rdi, [rbp-0x140]
	imul	edx, dword ptr [rbp+0x28], 24
	mov	eax, dword ptr [rbx+rdx+0x4]
	mov	dword ptr [rbp-0xC], eax
	inc	dword ptr [rbp+0x28]
	jmp	$_134

$_088:	mov	rdi, qword ptr [ModuleInfo+0x108+rip]
	mov	rsi, qword ptr [CurrStruct+rip]
	test	rdi, rdi
	jnz	$_090
	test	rsi, rsi
	jz	$_089
	mov	ecx, 1011
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], eax
$_089:	mov	eax, dword ptr [rbp-0x4]
	jmp	$_140

$_090:	test	rsi, rsi
	jnz	$_091
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_140

$_091:	mov	dword ptr [rbp-0x14], 1
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
	mov	rdx, qword ptr [rdi+0x18]
	test	rdx, rdx
	jz	$_092
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, qword ptr [rdi+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_092
	mov	rdx, qword ptr [rdi+0x18]
	mov	rdx, qword ptr [rdx+0x8]
	lea	rcx, [rbp-0x140]
	call	tstrcpy@PLT
	lea	rdx, [DS0008+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jz	$_092
	mov	rcx, rdi
	call	$_022
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS001D+rip]
	call	AddLineQueueX@PLT
$_092:	jmp	$_135

$_093:	mov	qword ptr [rbp-0x648], 0
	mov	rsi, qword ptr [ModuleInfo+0x108+rip]
	mov	rcx, qword ptr [CurrStruct+rip]
	test	rcx, rcx
	jz	$_094
	test	rsi, rsi
	jnz	$_095
$_094:	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_140

$_095:	mov	dword ptr [rsi+0x20], eax
	mov	rax, qword ptr [rsi+0x28]
	lea	rbx, [rbx+rdx+0x18]
	test	rax, rax
	jnz	$_096
	mov	rcx, qword ptr [rsi+0x8]
	call	SymFind@PLT
$_096:	test	rax, rax
	jz	$_097
	movzx	eax, word ptr [rax+0x4A]
$_097:	test	eax, eax
	jz	$_098
	mov	r8d, eax
	lea	rdx, [DS001E+rip]
	lea	rcx, [rbp-0x640]
	call	tsprintf@PLT
	lea	rax, [rbp-0x640]
	mov	qword ptr [rbp-0x648], rax
$_098:	mov	eax, dword ptr [rsi+0x10]
	mov	dword ptr [rbp-0x3C], eax
	mov	dword ptr [rbp-0x1C], 0
	cmp	byte ptr [rbx], 9
	jnz	$_099
	mov	rcx, rbx
	call	GetOperator@PLT
	test	rax, rax
	jnz	$_099
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x648], rax
	add	rbx, 24
$_099:	lea	rax, [rbp-0x3C]
	mov	qword ptr [rsp+0x28], rax
	lea	rax, [rbp-0x28]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rbp-0x18]
	lea	r8, [rbp-0x8]
	lea	rdx, [rbp-0x340]
	mov	rcx, rbx
	call	$_026
	mov	rbx, rax
	cmp	eax, -1
	je	$_140
	cmp	qword ptr [rbp-0x28], 0
	jz	$_105
	mov	rcx, qword ptr [rbp-0x28]
	mov	qword ptr [rbp-0x28], 0
	cmp	byte ptr [rcx], 9
	jnz	$_104
	cmp	byte ptr [rcx+0x1], 123
	jnz	$_104
	cmp	byte ptr [rcx-0x18], 7
	jnz	$_100
	cmp	dword ptr [rcx-0x14], 275
	jnz	$_100
	inc	dword ptr [rbp-0x1C]
$_100:	mov	rax, qword ptr [rcx+0x8]
	mov	qword ptr [rbp-0x28], rax
	mov	rax, qword ptr [rcx+0x10]
	mov	byte ptr [rax], 0
	jmp	$_102

$_101:	cmp	rax, qword ptr [rcx-0x8]
	jbe	$_103
	sub	rax, 1
$_102:	cmp	byte ptr [rax-0x1], 32
	jbe	$_101
$_103:	mov	byte ptr [rax], 0
	mov	byte ptr [rcx], 0
$_104:	jmp	$_106

$_105:	cmp	dword ptr [rbp-0xC], 405
	jnz	$_106
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_106
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
$_106:	lea	rdx, [rbp-0x340]
	lea	rcx, [rbp-0x540]
	call	tstrcpy@PLT
	mov	rdi, rax
	mov	rcx, qword ptr [rsi+0x8]
	mov	qword ptr [rbp-0x30], rcx
	cmp	qword ptr [rsi+0x18], 0
	jz	$_107
	mov	rcx, qword ptr [rsi+0x18]
	mov	rcx, qword ptr [rcx+0x8]
$_107:	mov	rdx, rcx
	lea	rcx, [rbp-0x140]
	call	tstrcpy@PLT
	lea	rdx, [DS0008+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	SymFind@PLT
	mov	qword ptr [rbp-0x38], rax
	test	rax, rax
	jnz	$_108
	mov	rax, qword ptr [CurrStruct+rip]
$_108:	test	rax, rax
	jz	$_111
	mov	rcx, rax
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, rdi
	call	SearchNameInStruct@PLT
	test	rax, rax
	jz	$_109
	cmp	qword ptr [rbp-0x38], 0
	jnz	$_111
$_109:	mov	rdx, qword ptr [rbp-0x30]
	mov	rcx, rdi
	call	tstrcmp@PLT
	test	rax, rax
	jz	$_110
	cmp	dword ptr [rsi+0x20], 405
	jz	$_110
	mov	r9d, 508
	mov	r8, qword ptr [rbx+0x10]
	mov	edx, dword ptr [rbp-0x3C]
	mov	rcx, rdi
	call	$_001
	jmp	$_111

$_110:	mov	rax, qword ptr [rbp-0x648]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbx+0x10]
	mov	r8, rsi
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x30]
	call	$_011
	cmp	dword ptr [rbp-0xC], 405
	jz	$_111
	inc	dword ptr [rbp-0x10]
$_111:	cmp	qword ptr [rbp-0x28], 0
	je	$_135
	cmp	dword ptr [Parse_Pass+rip], 0
	ja	$_135
	lea	r9, [rbp-0x540]
	mov	r8, qword ptr [rbp-0x30]
	lea	rdx, [DS0003+rip]
	lea	rcx, [rbp-0x340]
	call	tsprintf@PLT
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_112
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_112:	call	RunLineQueue@PLT
	cmp	dword ptr [rbp-0x10], 0
	jz	$_115
	lea	rcx, [rbp-0x340]
	call	SymFind@PLT
	test	rax, rax
	jz	$_114
	cmp	dword ptr [rbp-0xC], 407
	jz	$_113
	or	byte ptr [rax+0x15], 0xFFFFFF80
$_113:	cmp	dword ptr [rbp-0xC], 407
	jnz	$_114
	cmp	dword ptr [rbp-0x1C], 0
	jnz	$_114
	or	byte ptr [rax+0x16], 0x20
$_114:	jmp	$_116

$_115:	cmp	dword ptr [rbp-0xC], 405
	jnz	$_116
	mov	rax, qword ptr [rsi+0x28]
	test	rax, rax
	jz	$_116
	or	byte ptr [rax+0x16], 0xFFFFFF80
$_116:	mov	eax, dword ptr [rbp-0x1C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x28]
	mov	r8, qword ptr [rbx+0x10]
	mov	edx, dword ptr [rbp-0x8]
	lea	rcx, [rbp-0x340]
	call	MacroInline
	cmp	dword ptr [rbp-0x10], 0
	jnz	$_117
	cmp	dword ptr [rbp-0xC], 407
	jnz	$_117
	cmp	dword ptr [rbp-0x1C], 0
	jnz	$_117
	lea	rcx, [rbp-0x340]
	call	SymFind@PLT
	test	rax, rax
	jz	$_117
	or	byte ptr [rax+0x16], 0x20
$_117:	mov	eax, dword ptr [rbp-0x4]
	jmp	$_140

$_118:	cmp	qword ptr [ModuleInfo+0x108+rip], 0
	jz	$_119
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_140

$_119:	lea	rbx, [rbx+rdx+0x18]
	cmp	byte ptr [rbx], 9
	jnz	$_121
	mov	eax, dword ptr [rbx+0x1C]
	mov	word ptr [rbp-0x40], ax
	cmp	byte ptr [rbx+0x30], 44
	jz	$_120
	lea	rdx, [DS0011+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_140

$_120:	mov	eax, dword ptr [rbx+0x4C]
	mov	word ptr [rbp-0x3E], ax
	add	rbx, 120
$_121:	mov	ecx, 48
	call	LclAlloc@PLT
	mov	qword ptr [ModuleInfo+0x108+rip], rax
	mov	ecx, dword ptr [rbp-0xC]
	xor	edx, edx
	mov	dword ptr [rax], ecx
	mov	dword ptr [rax+0x10], edx
	mov	qword ptr [rax+0x18], rdx
	mov	dword ptr [rax+0x20], edx
	mov	qword ptr [rax+0x28], rdx
	xor	edx, edx
	mov	rax, qword ptr [rbx+0x8]
	call	NameSpace_@PLT
	mov	rsi, rax
	mov	rcx, qword ptr [ModuleInfo+0x108+rip]
	mov	qword ptr [rcx+0x8], rax
	mov	rdx, rsi
	mov	rcx, rdi
	call	tstrcpy@PLT
	add	rbx, 24
	cmp	byte ptr [rbx], 8
	jnz	$_122
	mov	rax, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rax]
	or	al, 0x20
	cmp	ax, 99
	jnz	$_122
	mov	byte ptr [rbx], 7
	mov	dword ptr [rbx+0x4], 277
	mov	byte ptr [rbx+0x1], 1
$_122:	mov	edx, dword ptr [rbx+0x4]
	cmp	byte ptr [rbx], 0
	jz	$_123
	cmp	edx, 277
	jc	$_123
	cmp	edx, 286
	ja	$_123
	mov	rcx, qword ptr [ModuleInfo+0x108+rip]
	mov	dword ptr [rcx+0x10], edx
	add	rbx, 24
$_123:	cmp	byte ptr [rbx], 58
	jnz	$_126
	cmp	byte ptr [rbx+0x18], 3
	jnz	$_125
	cmp	dword ptr [rbx+0x1C], 506
	jnz	$_125
	mov	rbx, qword ptr [rbx+0x38]
	mov	rcx, rbx
	call	SymFind@PLT
	test	rax, rax
	jnz	$_124
	mov	rdx, rbx
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_140

$_124:	mov	rcx, qword ptr [ModuleInfo+0x108+rip]
	mov	qword ptr [rcx+0x18], rax
	jmp	$_126

$_125:	mov	rdx, qword ptr [rbx+0x20]
	mov	ecx, 2006
	call	asmerr@PLT
$_126:	cmp	dword ptr [rbp-0xC], 402
	jnz	$_129
	movzx	eax, byte ptr [ModuleInfo+0x1CC+rip]
	shl	eax, 2
	mov	cl, byte ptr [ModuleInfo+0x1C5+rip]
	mov	edx, 1
	shl	edx, cl
	test	eax, eax
	jz	$_127
	cmp	edx, eax
	jnc	$_127
	mov	r8d, eax
	mov	rdx, rsi
	lea	rcx, [DS001F+rip]
	call	AddLineQueueX@PLT
	jmp	$_128

$_127:	mov	rdx, rsi
	lea	rcx, [DS0020+rip]
	call	AddLineQueueX@PLT
$_128:	jmp	$_130

$_129:	mov	rdx, rsi
	lea	rcx, [DS0020+rip]
	call	AddLineQueueX@PLT
$_130:	mov	rcx, qword ptr [ModuleInfo+0x108+rip]
	mov	rsi, qword ptr [rcx+0x18]
	test	rsi, rsi
	jz	$_132
	cmp	dword ptr [rbp-0xC], 404
	jz	$_131
	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, [DS0021+rip]
	mov	rcx, rsi
	call	SearchNameInStruct@PLT
	test	rax, rax
	jnz	$_131
	lea	rdx, [rbp-0x140]
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
$_131:	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
	jmp	$_133

$_132:	cmp	dword ptr [rbp-0xC], 404
	jz	$_133
	lea	rdx, [rbp-0x140]
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
$_133:	jmp	$_135

$_134:	cmp	eax, 408
	je	$_088
	cmp	eax, 406
	je	$_093
	cmp	eax, 407
	je	$_093
	cmp	eax, 405
	je	$_093
	cmp	eax, 403
	je	$_118
	cmp	eax, 402
	je	$_118
	cmp	eax, 404
	je	$_118
$_135:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_136
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_136:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_137
	call	RunLineQueue@PLT
$_137:	cmp	word ptr [rbp-0x40], 0
	jz	$_138
	mov	rcx, qword ptr [ModuleInfo+0x108+rip]
	mov	rsi, qword ptr [rcx+0x28]
	test	rsi, rsi
	jz	$_138
	movzx	eax, word ptr [rbp-0x40]
	movzx	ecx, word ptr [rbp-0x3E]
	mov	word ptr [rsi+0x48], ax
	mov	word ptr [rsi+0x4A], cx
	or	byte ptr [rsi+0x3B], 0x08
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rsi+0x19], al
$_138:	cmp	dword ptr [rbp-0x14], 0
	jz	$_139
	mov	qword ptr [ModuleInfo+0x108+rip], 0
$_139:	mov	eax, dword ptr [rbp-0x4]
$_140:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ClassInit:
	mov	dword ptr [ModuleInfo+0x348+rip], 0
	ret

ClassCheckOpen:
	sub	rsp, 40
	cmp	qword ptr [ModuleInfo+0x108+rip], 0
	jz	$_141
	lea	rdx, [DS0023+rip]
	mov	ecx, 1010
	call	asmerr@PLT
$_141:	add	rsp, 40
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x25, 0x73, 0x20, 0x25, 0x72, 0x20, 0x25, 0x72
	.byte  0x20, 0x25, 0x73, 0x00

DS0001:
	.byte  0x25, 0x73, 0x20, 0x25, 0x72, 0x20, 0x25, 0x73
	.byte  0x00

DS0002:
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x00

DS0003:
	.byte  0x25, 0x73, 0x5F, 0x25, 0x73, 0x00

DS0004:
	.byte  0x3A, 0x25, 0x73, 0x2C, 0x20, 0x25, 0x73, 0x00

DS0005:
	.byte  0x3A, 0x25, 0x73, 0x00

DS0006:
	.byte  0x25, 0x73, 0x5F, 0x25, 0x73, 0x20, 0x65, 0x71
	.byte  0x75, 0x20, 0x3C, 0x25, 0x73, 0x3E, 0x00

DS0007:
	.byte  0x25, 0x73, 0x56, 0x74, 0x62, 0x6C, 0x20, 0x73
	.byte  0x74, 0x72, 0x75, 0x63, 0x74, 0x00

DS0008:
	.byte  0x56, 0x74, 0x62, 0x6C, 0x00

DS0009:
	.byte  0x25, 0x73, 0x20, 0x3C, 0x3E, 0x00

DS000A:
	.byte  0x25, 0x73, 0x20, 0x65, 0x6E, 0x64, 0x73, 0x00

DS000B:
	.byte  0x54, 0x24, 0x25, 0x30, 0x34, 0x58, 0x00

DS000C:
	.byte  0x50, 0x24, 0x25, 0x30, 0x34, 0x58, 0x00

DS000D:
	.byte  0x20, 0x74, 0x79, 0x70, 0x65, 0x64, 0x65, 0x66
	.byte  0x20, 0x70, 0x72, 0x6F, 0x74, 0x6F, 0x00

DS000E:
	.byte  0x20, 0x73, 0x74, 0x64, 0x63, 0x61, 0x6C, 0x6C
	.byte  0x00

DS000F:
	.byte  0x20, 0x00

DS0010:
	.byte  0x20, 0x3A, 0x70, 0x74, 0x72, 0x00

DS0011:
	.byte  0x2C, 0x00

DS0012:
	.byte  0x25, 0x73, 0x20, 0x74, 0x79, 0x70, 0x65, 0x64
	.byte  0x65, 0x66, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x00

DS0013:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x3F, 0x00

DS0014:
	.byte  0x5F, 0x00

DS0015:
	.byte  0x5F, 0x25, 0x75, 0x2C, 0x20, 0x00

DS0016:
	.byte  0x74, 0x68, 0x69, 0x73, 0x00

DS0017:
	.byte  0x3A, 0x76, 0x61, 0x72, 0x61, 0x72, 0x67, 0x00

DS0018:
	.byte  0x25, 0x73, 0x20, 0x6D, 0x61, 0x63, 0x72, 0x6F
	.byte  0x20, 0x25, 0x73, 0x00

DS0019:
	.byte  0x65, 0x78, 0x69, 0x74, 0x6D, 0x3C, 0x3E, 0x00

DS001A:
	.byte  0x65, 0x78, 0x69, 0x74, 0x6D, 0x00

DS001B:
	.byte  0x72, 0x65, 0x74, 0x6D, 0x00

DS001C:
	.byte  0x65, 0x6E, 0x64, 0x6D, 0x00

DS001D:
	.byte  0x25, 0x73, 0x56, 0x74, 0x62, 0x6C, 0x20, 0x65
	.byte  0x6E, 0x64, 0x73, 0x00

DS001E:
	.byte  0x25, 0x72, 0x00

DS001F:
	.byte  0x25, 0x73, 0x20, 0x73, 0x74, 0x72, 0x75, 0x63
	.byte  0x74, 0x20, 0x25, 0x64, 0x00

DS0020:
	.byte  0x25, 0x73, 0x20, 0x73, 0x74, 0x72, 0x75, 0x63
	.byte  0x74, 0x00

DS0021:
	.byte  0x6C, 0x70, 0x56, 0x74, 0x62, 0x6C, 0x00

DS0022:
	.byte  0x6C, 0x70, 0x56, 0x74, 0x62, 0x6C, 0x20, 0x70
	.byte  0x74, 0x72, 0x20, 0x25, 0x73, 0x56, 0x74, 0x62
	.byte  0x6C, 0x20, 0x3F, 0x00

DS0023:
	.byte  0x2E, 0x63, 0x6F, 0x6D, 0x64, 0x65, 0x66, 0x2D
	.byte  0x2E, 0x63, 0x6C, 0x61, 0x73, 0x73, 0x64, 0x65
	.byte  0x66, 0x2D, 0x2E, 0x65, 0x6E, 0x64, 0x73, 0x00


.att_syntax prefix
