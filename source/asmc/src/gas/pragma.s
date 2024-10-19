
.intel_syntax noprefix

.global PragmaDirective
.global PragmaInit
.global PragmaCheckOpen
.global warning_disable

.extern RunLineQueue
.extern AddLineQueueX
.extern LstWrite
.extern GetCurrOffset
.extern EvalOperand
.extern SpecialTable
.extern LclAlloc
.extern MemFree
.extern MemAlloc
.extern get_fasttype
.extern get_register
.extern tstrcat
.extern tstrcpy
.extern tstrrchr
.extern tstrchr
.extern tstrupr
.extern tsprintf
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern QEnqueue


.SECTION .text
	.ALIGN	16

PragmaDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 952
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x8], 0
	inc	dword ptr [rbp+0x28]
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 40
	jz	$_001
	cmp	byte ptr [rbx], 44
	jnz	$_002
$_001:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_002:	mov	rsi, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rsi]
	or	eax, 0x20202020
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 40
	jz	$_003
	cmp	byte ptr [rbx], 44
	jnz	$_004
$_003:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_004:	bswap	eax
	jmp	$_099

$_005:	cmp	dword ptr [rbx+0x4], 678
	jnz	$_009
	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_006
	add	rbx, 24
$_006:	shr	dword ptr [wstringfl+rip], 1
	jnc	$_007
	or	byte ptr [ModuleInfo+0x334+rip], 0x02
	jmp	$_008

$_007:	and	byte ptr [ModuleInfo+0x334+rip], 0xFFFFFFFD
$_008:	jmp	$_100

$_009:	cmp	dword ptr [rbx+0x4], 677
	jne	$_016
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rbx+0x18], 44
	jnz	$_010
	inc	dword ptr [rbp+0x28]
$_010:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x70]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_100
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x34], 0
	jz	$_011
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_100

$_011:	mov	eax, dword ptr [rbp-0x70]
	cmp	eax, 1
	jbe	$_012
	mov	ecx, 2084
	call	asmerr@PLT
	jmp	$_100

$_012:	shl	dword ptr [wstringfl+rip], 1
	test	byte ptr [ModuleInfo+0x334+rip], 0x02
	jz	$_013
	or	byte ptr [wstringfl+rip], 0x01
$_013:	test	eax, eax
	jz	$_014
	or	byte ptr [ModuleInfo+0x334+rip], 0x02
	jmp	$_015

$_014:	and	byte ptr [ModuleInfo+0x334+rip], 0xFFFFFFFD
$_015:	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_016
	add	rbx, 24
$_016:	jmp	$_100

$_017:	cmp	byte ptr [rbx], 2
	jne	$_100
	mov	edx, 10
	movzx	ecx, byte ptr [ModuleInfo+0x1CC+rip]
	call	get_fasttype@PLT
	mov	rdx, rax
	mov	rdi, qword ptr [rdx]
	xor	eax, eax
	mov	ecx, 32
	rep stosb
	mov	rdi, rdx
	mov	byte ptr [rdi+0xC], 0
	mov	dword ptr [rdi+0x8], 0
	xor	esi, esi
$_018:	cmp	esi, 8
	jnc	$_022
	cmp	byte ptr [rbx], 2
	jne	$_022
	inc	byte ptr [rdi+0xC]
	mov	edx, 1
	mov	ecx, dword ptr [rbx+0x4]
	call	get_register@PLT
	mov	rdx, qword ptr [rdi]
	mov	byte ptr [rdx+rsi], al
	mov	edx, 2
	mov	ecx, dword ptr [rbx+0x4]
	call	get_register@PLT
	mov	rdx, qword ptr [rdi]
	mov	byte ptr [rdx+rsi+0x8], al
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jz	$_019
	mov	edx, 4
	mov	ecx, dword ptr [rbx+0x4]
	call	get_register@PLT
	mov	rdx, qword ptr [rdi]
	mov	byte ptr [rdx+rsi+0x10], al
$_019:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_020
	mov	edx, 8
	mov	ecx, dword ptr [rbx+0x4]
	call	get_register@PLT
	mov	rdx, qword ptr [rdi]
	mov	byte ptr [rdx+rsi+0x18], al
$_020:	mov	ecx, dword ptr [rbx+0x4]
	lea	rdx, [SpecialTable+rip]
	imul	eax, ecx, 12
	mov	cl, byte ptr [rdx+rax+0xA]
	mov	eax, 1
	shl	eax, cl
	or	dword ptr [rdi+0x8], eax
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jnz	$_021
	add	rbx, 24
$_021:	inc	esi
	jmp	$_018

$_022:	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_023
	add	rbx, 24
$_023:	jmp	$_100

$_024:	cmp	dword ptr [rbx+0x4], 678
	jnz	$_028
	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_025
	add	rbx, 24
$_025:	cmp	dword ptr [WarnCount+rip], 0
	je	$_100
	lea	rcx, [WarnStack+rip]
	dec	dword ptr [WarnCount+rip]
	mov	eax, dword ptr [WarnCount+rip]
	mov	rdx, qword ptr [rcx+rax*8]
	lea	rsi, [pragma_wtable+rip]
	xor	ecx, ecx
$_026:	cmp	ecx, 40
	jnc	$_027
	mov	al, byte ptr [rdx+rcx]
	mov	byte ptr [rsi+0x2], al
	inc	ecx
	add	rsi, 4
	jmp	$_026

$_027:	mov	rcx, rdx
	call	MemFree@PLT
	jmp	$_100

$_028:	cmp	dword ptr [rbx+0x4], 677
	jnz	$_032
	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_029
	add	rbx, 24
$_029:	mov	edi, dword ptr [WarnCount+rip]
	inc	edi
	cmp	edi, 16
	jnc	$_100
	mov	dword ptr [WarnCount+rip], edi
	mov	ecx, 40
	call	MemAlloc@PLT
	lea	rcx, [WarnStack+rip]
	mov	qword ptr [rcx+rdi*8-0x8], rax
	lea	rsi, [pragma_wtable+rip]
	xor	ecx, ecx
$_030:	cmp	ecx, 40
	jnc	$_031
	mov	dl, byte ptr [rsi+0x2]
	mov	byte ptr [rax+rcx], dl
	inc	ecx
	add	rsi, 4
	jmp	$_030

$_031:	jmp	$_100

$_032:	mov	rsi, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rsi]
	or	eax, 0x20202020
	cmp	eax, 1634953572
	jne	$_100
	cmp	byte ptr [rbx+0x18], 58
	jne	$_100
	add	dword ptr [rbp+0x28], 2
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x70]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_100
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x34], 0
	jz	$_033
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_100

$_033:	mov	eax, dword ptr [rbp-0x70]
	lea	rsi, [pragma_wtable+rip]
	xor	ecx, ecx
$_034:	cmp	ecx, 40
	jnc	$_036
	cmp	word ptr [rsi], ax
	jnz	$_035
	mov	byte ptr [rsi+0x2], 1
	jmp	$_036

$_035:	inc	ecx
	add	rsi, 4
	jmp	$_034

$_036:	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_037
	add	rbx, 24
$_037:	jmp	$_100

$_038:	mov	eax, dword ptr [rsi+0x4]
	or	eax, 0x202020
	cmp	eax, 7630437
	jne	$_100
	cmp	byte ptr [rbx+0x18], 44
	jne	$_100
	mov	rsi, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rsi]
	or	eax, 0x202020
	and	eax, 0xFFFFFF
	cmp	eax, 6449516
	jne	$_058
	add	dword ptr [rbp+0x28], 2
	add	rbx, 48
	mov	byte ptr [rbp-0x170], 0
	mov	byte ptr [rbp-0x270], 0
	mov	byte ptr [rbp-0x279], 0
	mov	rsi, qword ptr [rbx+0x8]
	mov	rdx, rsi
	lea	rcx, [rbp-0x170]
	call	tstrcpy@PLT
	jmp	$_040

$_039:	mov	rdx, qword ptr [rbx+0x20]
	lea	rcx, [rbp-0x170]
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbx+0x38]
	lea	rcx, [rbp-0x170]
	call	tstrcat@PLT
	add	dword ptr [rbp+0x28], 2
	add	rbx, 48
$_040:	cmp	byte ptr [rbx+0x18], 46
	jz	$_039
	cmp	byte ptr [rsi], 34
	jnz	$_041
	inc	rsi
	inc	byte ptr [rbp-0x279]
	mov	rdx, rsi
	lea	rcx, [rbp-0x170]
	call	tstrcpy@PLT
	mov	edx, 34
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jz	$_041
	mov	byte ptr [rax], 0
$_041:	cmp	byte ptr [rbx+0x18], 44
	jnz	$_044
	add	dword ptr [rbp+0x28], 2
	add	rbx, 48
	mov	rsi, qword ptr [rbx+0x8]
	mov	rdx, rsi
	lea	rcx, [rbp-0x270]
	call	tstrcpy@PLT
	jmp	$_043

$_042:	mov	rdx, qword ptr [rbx+0x20]
	lea	rcx, [rbp-0x270]
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbx+0x38]
	lea	rcx, [rbp-0x270]
	call	tstrcat@PLT
	add	dword ptr [rbp+0x28], 2
	add	rbx, 48
$_043:	cmp	byte ptr [rbx+0x18], 46
	jz	$_042
	cmp	byte ptr [rsi], 34
	jnz	$_044
	inc	rsi
	mov	rdx, rsi
	lea	rcx, [rbp-0x270]
	call	tstrcpy@PLT
	mov	edx, 34
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jz	$_044
	mov	byte ptr [rax], 0
$_044:	lea	rsi, [rbp-0x270]
	lea	rdi, [rbp-0x170]
	mov	edx, 46
	mov	rcx, rsi
	call	tstrrchr@PLT
	test	rax, rax
	jz	$_046
	mov	ecx, dword ptr [rax+0x1]
	and	ecx, 0xFFFFFF
	cmp	ecx, 6449516
	jz	$_045
	cmp	ecx, 7105636
	jnz	$_046
$_045:	mov	byte ptr [rax], 0
$_046:	mov	edx, 46
	mov	rcx, rdi
	call	tstrrchr@PLT
	test	rax, rax
	jz	$_048
	mov	ecx, dword ptr [rax+0x1]
	and	ecx, 0xFFFFFF
	cmp	ecx, 6449516
	jz	$_047
	cmp	ecx, 7105636
	jnz	$_048
$_047:	mov	byte ptr [rax], 0
$_048:	cmp	dword ptr [Options+0xA4+rip], 0
	jnz	$_050
	cmp	byte ptr [rbp-0x270], 0
	jnz	$_049
	mov	rsi, rdi
$_049:	mov	rdx, rsi
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	jmp	$_057

$_050:	cmp	byte ptr [rsi], 0
	jnz	$_053
	cmp	byte ptr [rbp-0x279], 0
	jz	$_051
	mov	rdx, rdi
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
	jmp	$_052

$_051:	mov	rdx, rdi
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
$_052:	jmp	$_057

$_053:	mov	rdx, rsi
	lea	rcx, [rbp-0x379]
	call	tstrcpy@PLT
	mov	rcx, rax
	call	tstrupr@PLT
	jmp	$_055

$_054:	mov	byte ptr [rax], 95
$_055:	mov	edx, 45
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_054
	mov	edx, 46
	lea	rcx, [rbp-0x379]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_056
	mov	byte ptr [rax], 0
$_056:	mov	r9, rdi
	mov	r8, rsi
	lea	rdx, [rbp-0x379]
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
$_057:	jmp	$_066

$_058:	cmp	eax, 7235948
	jne	$_066
	mov	eax, dword ptr [rsi+0x3]
	or	eax, 0x202020
	and	eax, 0xFFFFFF
	cmp	eax, 7497067
	jne	$_100
	add	rbx, 48
	mov	rsi, qword ptr [rbx+0x10]
	cmp	byte ptr [rsi], 34
	jne	$_100
	inc	rsi
	lea	rdi, [rbp-0x270]
	mov	rcx, rdi
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_063
$_059:	lodsb
	cmp	al, 34
	jnz	$_060
	cmp	byte ptr [rsi], 34
	jnz	$_060
	lodsb
	add	rbx, 24
	jmp	$_059

$_060:	cmp	al, 92
	jnz	$_061
	cmp	byte ptr [rsi], 34
	jnz	$_061
	movsb
	jmp	$_059

$_061:	cmp	al, 34
	jnz	$_062
	xor	eax, eax
$_062:	stosb
	test	al, al
	jnz	$_059
	sub	rdi, rcx
	add	rdi, 16
	mov	ecx, edi
	call	LclAlloc@PLT
	mov	rdi, rax
	lea	rdx, [rbp-0x270]
	lea	rcx, [rdi+0x8]
	call	tstrcpy@PLT
	mov	rdx, rdi
	lea	rcx, [ModuleInfo+0x50+rip]
	call	QEnqueue@PLT
	jmp	$_066

$_063:	jmp	$_065

$_064:	add	rbx, 24
$_065:	cmp	byte ptr [rbx], 9
	jz	$_064
$_066:	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_067
	add	rbx, 24
$_067:	jmp	$_100

$_068:	mov	edi, eax
	cmp	byte ptr [ModuleInfo+0x1D4+rip], 0
	jnz	$_069
	mov	edx, 528
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
$_069:	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_072
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rbx+0x18], 44
	jnz	$_070
	inc	dword ptr [rbp+0x28]
$_070:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x70]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_100
	mov	edx, 528
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	lea	rsi, [DS0006+rip]
	cmp	edi, 1768843636
	jnz	$_071
	lea	rsi, [DS0007+rip]
$_071:	mov	r9d, dword ptr [rbp-0x70]
	mov	r8, rsi
	lea	rdx, [DS0008+rip]
	lea	rcx, [rbp-0x170]
	call	tsprintf@PLT
	lea	rsi, [rbp-0x170]
	jmp	$_073

$_072:	lea	rsi, [DS0009+rip]
	cmp	edi, 1768843636
	jnz	$_073
	lea	rsi, [DS000A+rip]
$_073:	mov	eax, 2
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 1
	jc	$_074
	mov	eax, 8
$_074:	mov	dword ptr [rsp+0x20], eax
	mov	r9d, 514
	mov	r8d, 516
	mov	rdx, rsi
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
	mov	rdx, qword ptr [rbx+0x8]
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jnz	$_075
	add	rbx, 24
$_075:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_078
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_076
	mov	r8, rdx
	mov	edx, 239
	lea	rcx, [DS000C+rip]
	call	AddLineQueueX@PLT
	jmp	$_077

$_076:	mov	r9, qword ptr [rbx+0x8]
	mov	r8, rdx
	mov	edx, 239
	lea	rcx, [DS000D+rip]
	call	AddLineQueueX@PLT
$_077:	jmp	$_079

$_078:	mov	r8, qword ptr [rbx+0x8]
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
$_079:	mov	r8d, 517
	mov	rdx, rsi
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_080
	add	rbx, 24
$_080:	jmp	$_100

$_081:	cmp	dword ptr [rbx+0x4], 678
	jnz	$_083
	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_082
	add	rbx, 24
$_082:	cmp	dword ptr [PackCount+rip], 0
	je	$_100
	dec	dword ptr [PackCount+rip]
	mov	eax, dword ptr [PackCount+rip]
	lea	rcx, [PackStack+rip]
	mov	al, byte ptr [rcx+rax]
	mov	byte ptr [ModuleInfo+0x1C5+rip], al
	jmp	$_100

$_083:	cmp	dword ptr [rbx+0x4], 677
	jne	$_100
	cmp	dword ptr [PackCount+rip], 16
	jnc	$_100
	mov	edx, dword ptr [PackCount+rip]
	inc	dword ptr [PackCount+rip]
	mov	al, byte ptr [ModuleInfo+0x1C5+rip]
	lea	rcx, [PackStack+rip]
	mov	byte ptr [rcx+rdx], al
	add	rbx, 24
	cmp	byte ptr [rbx], 40
	jz	$_084
	cmp	byte ptr [rbx], 44
	jnz	$_085
$_084:	add	rbx, 24
$_085:	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [DS0010+rip]
	call	AddLineQueueX@PLT
	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_086
	add	rbx, 24
$_086:	jmp	$_100

$_087:	inc	dword ptr [rbp-0x8]
	lea	rcx, [ListCount+rip]
	lea	rdx, [ListStack+rip]
	lea	rdi, [ModuleInfo+0x1DB+rip]
	cmp	dword ptr [rbx+0x4], 678
	jnz	$_088
	mov	eax, 678
	jmp	$_099

$_088:	mov	eax, 677
	jmp	$_099

$_089:	inc	dword ptr [rbp-0x8]
	lea	rcx, [CrefCount+rip]
	lea	rdx, [CrefStack+rip]
	lea	rdi, [ModuleInfo+0x1DC+rip]
	cmp	dword ptr [rbx+0x4], 678
	jnz	$_090
	mov	eax, 678
	jmp	$_099

$_090:	cmp	dword ptr [rbx+0x4], 677
	jne	$_100
	mov	eax, dword ptr [rcx]
	inc	eax
	cmp	eax, 16
	jnc	$_100
	mov	dword ptr [rcx], eax
	mov	cl, byte ptr [rdi]
	mov	byte ptr [rdx+rax-0x1], cl
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rbx+0x18], 44
	jnz	$_091
	inc	dword ptr [rbp+0x28]
$_091:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x70]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_100
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x34], 0
	jz	$_092
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_100

$_092:	mov	eax, dword ptr [rbp-0x70]
	cmp	eax, 1
	jbe	$_093
	mov	ecx, 2084
	call	asmerr@PLT
	jmp	$_100

$_093:	mov	byte ptr [rdi], al
	test	al, al
	jz	$_094
	cmp	dword ptr [rbp-0x8], 0
	jz	$_094
	or	byte ptr [ModuleInfo+0x1C6+rip], 0x01
$_094:	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_095
	add	rbx, 24
$_095:	jmp	$_100

$_096:	mov	eax, dword ptr [rcx]
	test	eax, eax
	je	$_100
	dec	eax
	mov	dword ptr [rcx], eax
	mov	al, byte ptr [rdx+rax]
	mov	byte ptr [rdi], al
	test	al, al
	jz	$_097
	cmp	dword ptr [rbp-0x8], 0
	jz	$_097
	or	byte ptr [ModuleInfo+0x1C6+rip], 0x01
$_097:	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jnz	$_098
	add	rbx, 24
$_098:	jmp	$_100

$_099:	cmp	eax, 2004055154
	je	$_005
	cmp	eax, 1635088416
	je	$_017
	cmp	eax, 2002874990
	je	$_024
	cmp	eax, 1668246893
	je	$_038
	cmp	eax, 1768843636
	je	$_068
	cmp	eax, 1702390132
	je	$_068
	cmp	eax, 1885430635
	je	$_081
	cmp	eax, 1818850164
	je	$_087
	cmp	eax, 1668441446
	je	$_089
	cmp	eax, 677
	je	$_090
	cmp	eax, 678
	je	$_096
$_100:	cmp	byte ptr [rbx], 41
	jnz	$_101
	add	rbx, 24
$_101:	cmp	byte ptr [rbx], 0
	jz	$_102
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], eax
$_102:	cmp	dword ptr [rbp-0x8], 0
	jnz	$_104
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_103
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_103:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_104
	call	RunLineQueue@PLT
$_104:	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

PragmaInit:
	mov	dword ptr [ListCount+rip], 0
	mov	dword ptr [PackCount+rip], 0
	mov	dword ptr [CrefCount+rip], 0
	ret

PragmaCheckOpen:
	sub	rsp, 40
	cmp	dword ptr [ListCount+rip], 0
	jnz	$_105
	cmp	dword ptr [PackCount+rip], 0
	jnz	$_105
	cmp	dword ptr [CrefCount+rip], 0
	jz	$_106
$_105:	lea	rdx, [DS0011+rip]
	mov	ecx, 1010
	call	asmerr@PLT
$_106:	add	rsp, 40
	ret

warning_disable:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	mov	eax, dword ptr [rbp+0x10]
	lea	rdx, [pragma_wtable+rip]
	xor	ecx, ecx
$_107:	cmp	ecx, 40
	jnc	$_109
	cmp	ax, word ptr [rdx]
	jnz	$_108
	movzx	eax, byte ptr [rdx+0x2]
	jmp	$_110

$_108:	inc	ecx
	add	rdx, 4
	jmp	$_107

$_109:	xor	eax, eax
$_110:	leave
	ret


.SECTION .data
	.ALIGN	16

pragma_wtable:
	.byte  0xA3, 0x0F, 0x00, 0x00, 0xA5, 0x0F, 0x00, 0x00
	.byte  0xA6, 0x0F, 0x00, 0x00, 0xA7, 0x0F, 0x00, 0x00
	.byte  0xA8, 0x0F, 0x00, 0x00, 0xAB, 0x0F, 0x00, 0x00
	.byte  0xAC, 0x0F, 0x00, 0x00, 0x2E, 0x13, 0x00, 0x00
	.byte  0x73, 0x17, 0x00, 0x00, 0x74, 0x17, 0x00, 0x00
	.byte  0x75, 0x17, 0x00, 0x00, 0x40, 0x1F, 0x00, 0x00
	.byte  0x41, 0x1F, 0x00, 0x00, 0x42, 0x1F, 0x00, 0x00
	.byte  0x43, 0x1F, 0x00, 0x00, 0x44, 0x1F, 0x00, 0x00
	.byte  0x45, 0x1F, 0x00, 0x00, 0x46, 0x1F, 0x00, 0x00
	.byte  0x47, 0x1F, 0x00, 0x00, 0x48, 0x1F, 0x00, 0x00
	.byte  0x49, 0x1F, 0x00, 0x00, 0x4A, 0x1F, 0x00, 0x00
	.byte  0x4B, 0x1F, 0x00, 0x00, 0x4C, 0x1F, 0x00, 0x00
	.byte  0x4D, 0x1F, 0x00, 0x00, 0x4E, 0x1F, 0x00, 0x00
	.byte  0x4F, 0x1F, 0x00, 0x00, 0x51, 0x1F, 0x00, 0x00
	.byte  0x52, 0x1F, 0x00, 0x00, 0x53, 0x1F, 0x00, 0x00
	.byte  0x54, 0x1F, 0x00, 0x00, 0x58, 0x1B, 0x00, 0x00
	.byte  0x59, 0x1B, 0x00, 0x00, 0x5A, 0x1B, 0x00, 0x00
	.byte  0x5B, 0x1B, 0x00, 0x00, 0x5C, 0x1B, 0x00, 0x00
	.byte  0x5D, 0x1B, 0x00, 0x00, 0x5E, 0x1B, 0x00, 0x00
	.byte  0x5F, 0x1B, 0x00, 0x00, 0x60, 0x1B, 0x00, 0x00

ListCount:
	.int   0x00000000

PackCount:
	.int   0x00000000

CrefCount:
	.int   0x00000000

WarnCount:
	.int   0x00000000

wstringfl:
	.int   0x00000000

PackStack:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

ListStack:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

CrefStack:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

WarnStack:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

DS0000:
	.byte  0x20, 0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20
	.byte  0x64, 0x6C, 0x6C, 0x69, 0x6D, 0x70, 0x6F, 0x72
	.byte  0x74, 0x3A, 0x3C, 0x25, 0x73, 0x3E, 0x00

DS0001:
	.byte  0x69, 0x6E, 0x63, 0x6C, 0x75, 0x64, 0x65, 0x6C
	.byte  0x69, 0x62, 0x20, 0x22, 0x25, 0x73, 0x2E, 0x6C
	.byte  0x69, 0x62, 0x22, 0x00

DS0002:
	.byte  0x69, 0x6E, 0x63, 0x6C, 0x75, 0x64, 0x65, 0x6C
	.byte  0x69, 0x62, 0x20, 0x25, 0x73, 0x2E, 0x6C, 0x69
	.byte  0x62, 0x00

DS0003:
	.byte  0x69, 0x66, 0x64, 0x65, 0x66, 0x20, 0x5F, 0x25
	.byte  0x73, 0x0A, 0x69, 0x6E, 0x63, 0x6C, 0x75, 0x64
	.byte  0x65, 0x6C, 0x69, 0x62, 0x20, 0x25, 0x73, 0x2E
	.byte  0x6C, 0x69, 0x62, 0x0A, 0x65, 0x6C, 0x73, 0x65
	.byte  0x0A, 0x69, 0x6E, 0x63, 0x6C, 0x75, 0x64, 0x65
	.byte  0x6C, 0x69, 0x62, 0x20, 0x25, 0x73, 0x2E, 0x6C
	.byte  0x69, 0x62, 0x0A, 0x65, 0x6E, 0x64, 0x69, 0x66
	.byte  0x00

DS0004:
	.byte  0x20, 0x25, 0x72, 0x20, 0x64, 0x6F, 0x74, 0x6E
	.byte  0x61, 0x6D, 0x65, 0x00

DS0005:
	.byte  0x20, 0x25, 0x72, 0x20, 0x64, 0x6F, 0x74, 0x6E
	.byte  0x61, 0x6D, 0x65, 0x78, 0x3A, 0x6F, 0x6E, 0x00

DS0006:
	.byte  0x2E, 0x66, 0x69, 0x6E, 0x69, 0x5F, 0x61, 0x72
	.byte  0x72, 0x61, 0x79, 0x00

DS0007:
	.byte  0x2E, 0x69, 0x6E, 0x69, 0x74, 0x5F, 0x61, 0x72
	.byte  0x72, 0x61, 0x79, 0x00

DS0008:
	.byte  0x25, 0x73, 0x2E, 0x25, 0x30, 0x35, 0x64, 0x00

DS0009:
	.byte  0x2E, 0x43, 0x52, 0x54, 0x24, 0x58, 0x54, 0x41
	.byte  0x00

DS000A:
	.byte  0x2E, 0x43, 0x52, 0x54, 0x24, 0x58, 0x49, 0x41
	.byte  0x00

DS000B:
	.byte  0x20, 0x25, 0x73, 0x20, 0x25, 0x72, 0x20, 0x25
	.byte  0x72, 0x28, 0x25, 0x64, 0x29, 0x20, 0x27, 0x43
	.byte  0x4F, 0x4E, 0x53, 0x54, 0x27, 0x00

DS000C:
	.byte  0x20, 0x64, 0x71, 0x20, 0x25, 0x72, 0x20, 0x25
	.byte  0x73, 0x00

DS000D:
	.byte  0x20, 0x64, 0x64, 0x20, 0x25, 0x72, 0x20, 0x25
	.byte  0x73, 0x2C, 0x20, 0x25, 0x73, 0x00

DS000E:
	.byte  0x20, 0x64, 0x64, 0x20, 0x25, 0x73, 0x2C, 0x20
	.byte  0x25, 0x73, 0x00

DS000F:
	.byte  0x20, 0x25, 0x73, 0x20, 0x25, 0x72, 0x00

DS0010:
	.byte  0x4F, 0x50, 0x54, 0x49, 0x4F, 0x4E, 0x20, 0x46
	.byte  0x49, 0x45, 0x4C, 0x44, 0x41, 0x4C, 0x49, 0x47
	.byte  0x4E, 0x3A, 0x20, 0x25, 0x73, 0x00

DS0011:
	.byte  0x2E, 0x70, 0x72, 0x61, 0x67, 0x6D, 0x61, 0x2D
	.byte  0x70, 0x75, 0x73, 0x68, 0x2D, 0x70, 0x6F, 0x70
	.byte  0x00


.att_syntax prefix
