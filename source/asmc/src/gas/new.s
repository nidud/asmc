
.intel_syntax noprefix

.global ClearStruct
.global NewDirective

.extern GetQualifiedType
.extern quad_resize
.extern __cvtq_ld
.extern Tokenize
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern EvalOperand
.extern SetLocalOffsets
.extern CurrProc
.extern tstrcat
.extern tstrcpy
.extern tsprintf
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind
.extern SymLCreate


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 328
	mov	rdx, qword ptr [rbp+0x40]
	lea	rcx, [rbp-0x110]
	call	tstrcpy@PLT
	lea	rdx, [DS0000+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbp+0x40]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rsi, rax
	mov	rcx, rsi
	call	SymFind@PLT
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_002
	test	rax, rax
	jz	$_002
	cmp	byte ptr [rax+0x18], 0
	jnz	$_002
	mov	byte ptr [rax+0x18], 9
$_002:	xor	ecx, ecx
	mov	dword ptr [rbp-0x8], ecx
	test	rax, rax
	jz	$_003
	cmp	byte ptr [rax+0x18], 9
	jnz	$_003
	mov	ecx, 18
	mov	dword ptr [rbp-0x8], 18
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_003
	mov	ecx, 24
	mov	dword ptr [rbp-0x8], 122
	cmp	byte ptr [rax+0x1A], 2
	jz	$_003
	mov	ecx, 18
	mov	dword ptr [rbp-0x8], 116
$_003:	xor	eax, eax
	mov	rbx, qword ptr [rbp+0x38]
	mov	edx, 0
	cmp	byte ptr [rbx-0x18], 58
	jnz	$_006
	mov	rdx, qword ptr [rbp+0x50]
	test	rdx, rdx
	jz	$_004
	cmp	byte ptr [rdx+0x19], -61
	jnz	$_004
	mov	edx, 2
	jmp	$_005

$_004:	mov	edx, 1
$_005:	jmp	$_007

$_006:	cmp	qword ptr [rbp+0x48], 0
	jz	$_007
	mov	edx, 2
$_007:	mov	dword ptr [rbp-0xC], edx
	cmp	byte ptr [rbx-0x18], 58
	jnz	$_008
	cmp	edx, 2
	jnz	$_009
$_008:	inc	eax
	cmp	qword ptr [rbp+0x48], 0
	jnz	$_009
	inc	eax
$_009:	mov	rdi, qword ptr [rbx+0x40]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rbx, qword ptr [rdx]
	cmp	byte ptr [rbx-0x30], 40
	jz	$_010
	add	eax, 3
	mov	rbx, qword ptr [rbx-0x8]
	mov	byte ptr [rbx], 0
	jmp	$_011

$_010:	xor	ebx, ebx
$_011:	mov	rdx, qword ptr [rbp+0x28]
	test	rcx, rcx
	je	$_024
	mov	dword ptr [rbp-0x10], eax
	jmp	$_014

$_012:	mov	r8, rdx
	mov	edx, dword ptr [rbp-0x8]
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
	jmp	$_015

$_013:	mov	r8d, ecx
	mov	edx, ecx
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
	jmp	$_015

$_014:	cmp	eax, 0
	jz	$_012
	cmp	eax, 3
	jz	$_012
	cmp	eax, 1
	jz	$_013
	cmp	eax, 2
	jz	$_013
	cmp	eax, 4
	jz	$_013
	cmp	eax, 5
	jz	$_013
$_015:	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp-0x8]
	mov	eax, dword ptr [rbp-0x10]
	jmp	$_022

$_016:	mov	r8d, ecx
	mov	rdx, rsi
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	jmp	$_023

$_017:	mov	r9d, ecx
	mov	r8, rsi
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	jmp	$_023

$_018:	mov	r8d, ecx
	mov	rdx, rsi
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	jmp	$_023

$_019:	mov	r9, rdi
	mov	r8d, ecx
	mov	rdx, rsi
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	jmp	$_023

$_020:	mov	qword ptr [rsp+0x20], rdi
	mov	r9d, ecx
	mov	r8, rsi
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
	jmp	$_023

$_021:	mov	r9, rdi
	mov	r8d, ecx
	mov	rdx, rsi
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	jmp	$_023

$_022:	cmp	eax, 0
	je	$_016
	cmp	eax, 1
	jz	$_017
	cmp	eax, 2
	jz	$_018
	cmp	eax, 3
	jz	$_019
	cmp	eax, 4
	jz	$_020
	cmp	eax, 5
	jz	$_021
$_023:	jmp	$_032

$_024:	jmp	$_031

$_025:	mov	r8, rdx
	mov	rdx, rsi
	lea	rcx, [DS0007+rip]
	call	AddLineQueueX@PLT
	jmp	$_032

$_026:	mov	r8, rsi
	lea	rcx, [DS0008+rip]
	call	AddLineQueueX@PLT
	jmp	$_032

$_027:	mov	rdx, rsi
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
	jmp	$_032

$_028:	mov	r9, rdi
	mov	r8, rdx
	mov	rdx, rsi
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
	jmp	$_032

$_029:	mov	r9, rdi
	mov	r8, rsi
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
	jmp	$_032

$_030:	mov	r8, rdi
	mov	rdx, rsi
	lea	rcx, [DS000C+rip]
	call	AddLineQueueX@PLT
	jmp	$_032

$_031:	cmp	eax, 0
	jz	$_025
	cmp	eax, 1
	jz	$_026
	cmp	eax, 2
	jz	$_027
	cmp	eax, 3
	jz	$_028
	cmp	eax, 4
	jz	$_029
	cmp	eax, 5
	jz	$_030
$_032:	test	rbx, rbx
	jz	$_033
	mov	byte ptr [rbx], 41
$_033:	mov	rdx, qword ptr [rbp+0x30]
	mov	rbx, qword ptr [rdx]
	cmp	byte ptr [rbx], 58
	jne	$_045
	add	rbx, 24
	mov	eax, dword ptr [ModuleInfo+0x340+rip]
	mov	dword ptr [rbp-0x4], eax
	cmp	dword ptr [rbp-0x8], 0
	jz	$_034
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rbp-0x4], eax
$_034:	jmp	$_043

$_035:	mov	rdx, qword ptr [rbx+0x8]
	add	rbx, 48
	mov	rdi, qword ptr [rbx+0x10]
	mov	eax, 1
$_036:	cmp	byte ptr [rbx], 0
	jz	$_039
	cmp	byte ptr [rbx], 40
	jnz	$_037
	inc	eax
	jmp	$_038

$_037:	cmp	byte ptr [rbx], 41
	jnz	$_038
	dec	eax
	jz	$_039
$_038:	add	rbx, 24
	jmp	$_036

$_039:	cmp	byte ptr [rbx], 41
	jz	$_040
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_045

$_040:	mov	rsi, qword ptr [rbx+0x10]
	mov	byte ptr [rsi], 0
	cmp	dword ptr [rbp-0xC], 1
	jnz	$_041
	mov	r9, rdi
	mov	r8, rdx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS000D+rip]
	call	AddLineQueueX@PLT
	jmp	$_042

$_041:	mov	qword ptr [rsp+0x20], rdi
	mov	r9, rdx
	mov	r8, qword ptr [rbp+0x40]
	mov	edx, dword ptr [rbp-0x4]
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
$_042:	mov	byte ptr [rsi], 41
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jnz	$_043
	add	rbx, 24
$_043:	cmp	byte ptr [rbx], 8
	jnz	$_044
	cmp	byte ptr [rbx+0x18], 40
	je	$_035
$_044:	mov	rdx, qword ptr [rbp+0x30]
	mov	qword ptr [rdx], rbx
$_045:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_046:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	ebx, dword ptr [rdx+0x50]
	mov	rdi, qword ptr [rdx+0x8]
	cmp	ebx, 4
	jbe	$_054
	mov	esi, dword ptr [ModuleInfo+0x220+rip]
	add	esi, 1
	mov	dword ptr [rbp-0x4], esi
	xor	r9d, r9d
	mov	r8, qword ptr [ModuleInfo+0x180+rip]
	mov	edx, esi
	mov	rcx, qword ptr [rbp+0x38]
	call	Tokenize@PLT
	mov	edx, eax
	imul	eax, esi, 24
	add	rax, qword ptr [ModuleInfo+0x180+rip]
	cmp	byte ptr [rax], 10
	jz	$_047
	cmp	byte ptr [rax], 11
	jne	$_054
$_047:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x70]
	mov	r8d, edx
	mov	rdx, qword ptr [ModuleInfo+0x180+rip]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_054
	cmp	dword ptr [rbp-0x34], 3
	jnz	$_048
	mov	dword ptr [rbp-0x34], 0
	cmp	ebx, 16
	jz	$_048
	mov	edx, ebx
	lea	rcx, [rbp-0x70]
	call	quad_resize@PLT
$_048:	cmp	dword ptr [rbp-0x34], 0
	jne	$_054
	cmp	ebx, 8
	jnz	$_049
	cmp	dword ptr [rbp-0x6C], 0
	jnz	$_049
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	je	$_054
$_049:	jmp	$_053

$_050:	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [rsp+0x30], eax
	mov	qword ptr [rsp+0x28], rdi
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x64]
	mov	r8, rdi
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
$_051:	cmp	ebx, 10
	jnz	$_052
	mov	r9d, dword ptr [rbp-0x68]
	mov	r8, rdi
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0010+rip]
	call	AddLineQueueX@PLT
$_052:	mov	eax, dword ptr [rbp-0x70]
	mov	dword ptr [rsp+0x30], eax
	mov	qword ptr [rsp+0x28], rdi
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x6C]
	mov	r8, rdi
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0011+rip]
	call	AddLineQueueX@PLT
	jmp	$_055

	jmp	$_054

$_053:	cmp	ebx, 16
	jz	$_050
	cmp	ebx, 10
	jz	$_051
	cmp	ebx, 8
	jz	$_052
$_054:	mov	r9, qword ptr [rbp+0x38]
	mov	r8, rdi
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS000D+rip]
	call	AddLineQueueX@PLT
$_055:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_056:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	mov	dword ptr [rbp-0x104], 0
	mov	rax, r8
	lea	rsi, [rax+0x1]
	test	rdx, rdx
	jz	$_060
	jmp	$_058

$_057:	cmp	rdx, qword ptr [rdx+0x20]
	jz	$_059
	mov	rdx, qword ptr [rdx+0x20]
$_058:	cmp	byte ptr [rdx+0x18], 7
	jnz	$_059
	cmp	qword ptr [rdx+0x20], 0
	jnz	$_057
$_059:	mov	rcx, qword ptr [rdx+0x68]
	mov	rbx, qword ptr [rcx]
	jmp	$_061

$_060:	inc	dword ptr [rbp-0x104]
$_061:	lodsb
	cmp	al, 32
	jz	$_061
	cmp	al, 9
	jz	$_061
	cmp	al, 125
	je	$_090
	dec	rsi
	test	al, al
	je	$_090
	lea	rdi, [rbp-0x100]
	cmp	byte ptr [rsi], 123
	jnz	$_065
	mov	rdx, qword ptr [rbp+0x28]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rcx, qword ptr [rbx+0x8]
	cmp	byte ptr [rcx], 0
	jz	$_062
	lea	rdx, [DS0012+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcat@PLT
$_062:	mov	r8, rsi
	mov	rdx, qword ptr [rbx+0x20]
	mov	rcx, rdi
	call	$_056
	mov	rsi, rax
	test	eax, eax
	je	$_090
	jmp	$_064

$_063:	add	rsi, 1
$_064:	cmp	byte ptr [rsi], 32
	jz	$_063
	cmp	byte ptr [rsi], 9
	jz	$_063
	jmp	$_087

$_065:	xor	eax, eax
	xor	edx, edx
	mov	byte ptr [rbp-0x105], al
	mov	byte ptr [rdi], al
	lea	rcx, [rdi+0xFF]
	jmp	$_074

$_066:	mov	al, byte ptr [rsi]
	jmp	$_071

$_067:	jmp	$_075

$_068:	cmp	byte ptr [rbp-0x105], 0
	jz	$_075
	jmp	$_072

$_069:	inc	byte ptr [rbp-0x105]
	jmp	$_072

$_070:	dec	byte ptr [rbp-0x105]
	jmp	$_072

$_071:	cmp	al, 0
	jz	$_067
	cmp	al, 44
	jz	$_068
	cmp	al, 125
	jz	$_068
	cmp	al, 40
	jz	$_069
	cmp	al, 41
	jz	$_070
$_072:	test	byte ptr [r15+rax], 0x44
	jnz	$_073
	inc	edx
$_073:	movsb
$_074:	cmp	rdi, rcx
	jc	$_066
$_075:	xor	eax, eax
	mov	byte ptr [rdi], al
	lea	rcx, [rbp-0x100]
$_076:	cmp	rcx, rdi
	jnc	$_078
	cmp	byte ptr [rdi-0x1], 32
	jz	$_077
	cmp	byte ptr [rdi-0x1], 9
	jnz	$_078
$_077:	dec	edx
	dec	rdi
	mov	byte ptr [rdi], 0
	jmp	$_076

$_078:	test	edx, edx
	jne	$_080
	mov	rdi, rcx
	mov	rcx, rdi
	call	SymFind@PLT
	test	rax, rax
	jz	$_080
	cmp	byte ptr [rax+0x18], 10
	jnz	$_080
	mov	rcx, qword ptr [rax+0x28]
	cmp	byte ptr [rcx], 123
	jnz	$_079
	cmp	dword ptr [rbp-0x104], 0
	jnz	$_079
	test	byte ptr [rbx+0x15], 0x02
	jz	$_079
	mov	rdx, rax
	xor	eax, eax
	mov	rdi, rsi
	mov	ecx, 4294967295
	repne scasb
	not	ecx
	mov	edi, dword ptr [rdx+0x50]
	lea	rax, [rdi+rcx+0xF]
	and	rax, 0xFFFFFFFFFFFFFFF0
	sub	rsp, rax
	mov	eax, ecx
	lea	rcx, [rdi-0x1]
	mov	rdi, rsp
	mov	rdx, qword ptr [rdx+0x28]
	xchg	rsi, rdx
	rep movsb
	mov	rsi, rdx
	mov	ecx, eax
	rep movsb
	mov	rsi, rsp
	sub	rsp, 32
	jmp	$_061

	jmp	$_080

$_079:	mov	rdx, rsi
	mov	rsi, rcx
	mov	ecx, dword ptr [rax+0x50]
	inc	ecx
	and	ecx, 0xFF
	rep movsb
	mov	rsi, rdx
$_080:	cmp	byte ptr [rbp-0x100], 0
	je	$_087
	cmp	dword ptr [rbp-0x104], 0
	jz	$_081
	mov	eax, dword ptr [rbx+0x50]
	xor	edx, edx
	div	dword ptr [rbx+0x58]
	mov	ecx, dword ptr [rbp-0x104]
	dec	ecx
	mul	ecx
	mov	ecx, eax
$_081:	cmp	byte ptr [rbp-0x100], 34
	jz	$_082
	cmp	byte ptr [rbp-0x100], 76
	jnz	$_085
	cmp	byte ptr [rbp-0xFF], 34
	jnz	$_085
$_082:	cmp	dword ptr [rbp-0x104], 0
	jz	$_083
	lea	r9, [rbp-0x100]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
	jmp	$_084

$_083:	lea	r9, [rbp-0x100]
	mov	r8, qword ptr [rbx+0x8]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
$_084:	jmp	$_087

$_085:	cmp	dword ptr [rbp-0x104], 0
	jz	$_086
	lea	r9, [rbp-0x100]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	jmp	$_087

$_086:	lea	r8, [rbp-0x100]
	mov	rdx, rbx
	mov	rcx, qword ptr [rbp+0x28]
	call	$_046
$_087:	cmp	byte ptr [rsi], 0
	jz	$_090
	lodsb
	cmp	al, 44
	jnz	$_090
	cmp	dword ptr [rbp-0x104], 0
	jz	$_088
	inc	dword ptr [rbp-0x104]
	jmp	$_089

$_088:	mov	rbx, qword ptr [rbx+0x68]
$_089:	test	rbx, rbx
	jz	$_090
	jmp	$_061

$_090:
	mov	rax, rsi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_091:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	cmp	qword ptr [rbp+0x38], 0
	jnz	$_092
	mov	rsi, qword ptr [rbp+0x30]
	lea	rdi, [rbp-0x100]
	mov	ecx, 104
	rep movsb
	mov	qword ptr [rbp-0x98], 0
	lea	rbx, [rbp-0x100]
	mov	r8, qword ptr [rbp+0x40]
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x28]
	call	$_056
	jmp	$_099

$_092:	mov	rdi, qword ptr [rbp+0x30]
	test	byte ptr [rdi+0x15], 0x02
	jnz	$_093
	mov	r8, qword ptr [rbp+0x40]
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_056
	jmp	$_099

$_093:	mov	rsi, qword ptr [rbp+0x40]
	inc	rsi
	jmp	$_095

$_094:	add	rsi, 1
$_095:	cmp	byte ptr [rsi], 32
	jz	$_094
	cmp	byte ptr [rsi], 9
	jz	$_094
	mov	eax, dword ptr [rdi+0x50]
	mov	ebx, dword ptr [rdi+0x58]
	xor	edx, edx
	div	ebx
	mov	dword ptr [rbp-0x84], eax
	xor	edi, edi
$_096:	test	ebx, ebx
	jz	$_098
	mov	r9d, edi
	mov	r8, qword ptr [rbp+0x28]
	lea	rdx, [DS0016+rip]
	lea	rcx, [rbp-0x80]
	call	tsprintf@PLT
	mov	r8, rsi
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0x80]
	call	$_056
	mov	rsi, rax
	lodsb
	test	al, al
	jz	$_098
$_097:	lodsb
	cmp	al, 32
	jz	$_097
	cmp	al, 9
	jz	$_097
	dec	rsi
	cmp	al, 123
	jnz	$_098
	dec	ebx
	add	edi, dword ptr [rbp-0x84]
	jmp	$_096

$_098:	mov	rax, rsi
$_099:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ClearStruct:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rdx
	lea	rcx, [DS0017+rip]
	call	AddLineQueue@PLT
	mov	edi, dword ptr [rsi+0x50]
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_105
	cmp	edi, 32
	jbe	$_100
	mov	r8d, edi
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0018+rip]
	call	AddLineQueueX@PLT
	jmp	$_104

$_100:	xor	ebx, ebx
$_101:	cmp	edi, 8
	jc	$_102
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0019+rip]
	call	AddLineQueueX@PLT
	sub	edi, 8
	add	ebx, 8
	jmp	$_101

$_102:	cmp	edi, 4
	jc	$_103
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS001A+rip]
	call	AddLineQueueX@PLT
	sub	edi, 4
	add	ebx, 4
$_103:	test	edi, edi
	jz	$_104
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
	dec	edi
	inc	ebx
	jmp	$_103

$_104:	jmp	$_109

$_105:	cmp	edi, 16
	jbe	$_106
	mov	r8d, edi
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS001C+rip]
	call	AddLineQueueX@PLT
	jmp	$_109

$_106:	xor	ebx, ebx
$_107:	cmp	edi, 4
	jc	$_108
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS001A+rip]
	call	AddLineQueueX@PLT
	sub	edi, 4
	add	ebx, 4
	jmp	$_107

$_108:	test	edi, edi
	jz	$_109
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
	dec	edi
	inc	ebx
	jmp	$_108

$_109:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_110:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 712
	inc	dword ptr [rbp+0x30]
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	rsi, r9
	mov	al, byte ptr [rbx+0x2]
	mov	byte ptr [rbp-0x201], al
	mov	byte ptr [rbp-0x200], 0
	cmp	byte ptr [rbx], 9
	jne	$_119
	cmp	byte ptr [rbx+0x1], 123
	jne	$_119
	mov	rcx, qword ptr [rbp+0x28]
	call	SymFind@PLT
	test	rax, rax
	jnz	$_111
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_151

$_111:	xor	edx, edx
	mov	rcx, qword ptr [rbx+0x8]
	jmp	$_113

$_112:	inc	rcx
$_113:	cmp	byte ptr [rcx], 32
	jz	$_112
	cmp	byte ptr [rcx], 9
	jz	$_112
	cmp	byte ptr [rcx], 48
	jnz	$_116
	inc	rcx
	jmp	$_115

$_114:	inc	rcx
$_115:	cmp	byte ptr [rcx], 32
	jz	$_114
	cmp	byte ptr [rcx], 9
	jz	$_114
	cmp	byte ptr [rcx], 0
	jnz	$_116
	inc	rdx
$_116:	test	edx, edx
	jz	$_117
	mov	rdx, rax
	mov	rcx, qword ptr [rbp+0x28]
	call	ClearStruct
	jmp	$_118

$_117:	mov	r9, qword ptr [rbx+0x10]
	mov	r8, qword ptr [rax+0x20]
	mov	rdx, rax
	mov	rcx, qword ptr [rbp+0x28]
	call	$_091
$_118:	lea	rax, [rbx+0x18]
	jmp	$_151

$_119:	lea	rdi, [rbp-0x100]
	mov	eax, 682
	cmp	byte ptr [rbx], 11
	jz	$_122
	cmp	byte ptr [rbx], 45
	jz	$_122
	cmp	byte ptr [rsi+0x10], 35
	jnz	$_120
	mov	eax, 1050
	jmp	$_122

$_120:	cmp	byte ptr [rsi+0x10], 39
	jnz	$_121
	mov	eax, 612
	jmp	$_122

$_121:	cmp	byte ptr [rsi+0x10], 47
	jnz	$_122
	mov	eax, 1030
$_122:	mov	r8d, eax
	lea	rdx, [DS001D+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	mov	eax, dword ptr [rsi]
	cmp	eax, 8
	jc	$_134
	mov	rdx, qword ptr [rbx+0x8]
	cmp	eax, 8
	jnz	$_124
	cmp	byte ptr [rsi+0x13], 1
	jnz	$_124
	test	byte ptr [rbp-0x201], 0x08
	jz	$_124
	cmp	byte ptr [rsi+0x10], 7
	jz	$_123
	cmp	byte ptr [rsi+0x10], 71
	jnz	$_124
$_123:	lea	rdx, [DS001E+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [DS001F+rip]
	lea	rcx, [rbp-0x200]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbp+0x28]
	mov	rcx, rax
	call	tstrcat@PLT
	lea	rdx, [DS0020+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	jmp	$_134

$_124:	cmp	eax, 8
	jnz	$_126
	cmp	byte ptr [rsi+0x13], 2
	jnz	$_126
	test	byte ptr [rbp-0x201], 0x08
	jnz	$_125
	cmp	word ptr [rdx], 38
	jnz	$_126
$_125:	jmp	$_134

$_126:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x270]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp+0x30]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_134
	mov	eax, dword ptr [rsi]
	cmp	eax, 8
	jnz	$_129
	cmp	dword ptr [rbp-0x234], 0
	jnz	$_129
	cmp	byte ptr [rsi+0x13], 1
	jz	$_127
	cmp	byte ptr [rbx], 9
	jz	$_128
	cmp	dword ptr [rbp-0x26C], 0
	jg	$_127
	cmp	dword ptr [rbp-0x26C], -1
	jge	$_128
$_127:	mov	eax, dword ptr [rbp-0x26C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp+0x28]
	mov	r8d, dword ptr [rbp-0x270]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
	imul	eax, dword ptr [rbp+0x30], 24
	add	rax, qword ptr [rbp+0x38]
	jmp	$_151

$_128:	jmp	$_134

$_129:	cmp	dword ptr [rbp-0x234], 3
	jne	$_134
	cmp	eax, 8
	jz	$_130
	cmp	eax, 10
	jz	$_130
	cmp	eax, 16
	jne	$_134
$_130:	cmp	eax, 8
	jnz	$_131
	mov	rax, qword ptr [rbx+0x10]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp+0x28]
	mov	r8, qword ptr [rbx+0x10]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
	jmp	$_133

$_131:	cmp	eax, 10
	jnz	$_132
	lea	rdx, [rbp-0x270]
	lea	rcx, [rbp-0x270]
	call	__cvtq_ld@PLT
	mov	eax, dword ptr [rbp-0x268]
	mov	dword ptr [rsp+0x30], eax
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x26C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp+0x28]
	mov	r8d, dword ptr [rbp-0x270]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0023+rip]
	call	AddLineQueueX@PLT
	jmp	$_133

$_132:	mov	eax, dword ptr [rbp-0x264]
	mov	dword ptr [rsp+0x40], eax
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x38], rax
	mov	eax, dword ptr [rbp-0x268]
	mov	dword ptr [rsp+0x30], eax
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x26C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp+0x28]
	mov	r8d, dword ptr [rbp-0x270]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0024+rip]
	call	AddLineQueueX@PLT
$_133:	imul	eax, dword ptr [rbp+0x30], 24
	add	rax, qword ptr [rbp+0x38]
	jmp	$_151

$_134:	mov	rdx, qword ptr [rbp+0x28]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [DS0025+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	xor	esi, esi
$_135:	jmp	$_140

$_136:	jmp	$_148

$_137:	test	esi, esi
	je	$_148
	jmp	$_141

$_138:	inc	esi
	jmp	$_141

$_139:	dec	esi
	jmp	$_141

$_140:	cmp	byte ptr [rbx], 0
	jz	$_136
	cmp	byte ptr [rbx], 44
	jz	$_137
	cmp	byte ptr [rbx], 40
	jz	$_138
	cmp	byte ptr [rbx], 41
	jz	$_139
$_141:	cmp	byte ptr [rbx], 1
	jnz	$_142
	lea	rdx, [DS0025+0x1+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_142:	test	esi, esi
	jnz	$_143
	cmp	byte ptr [rbx], 9
	jnz	$_143
	cmp	byte ptr [rbx+0x1], 34
	jnz	$_143
	mov	rcx, qword ptr [rbp+0x28]
	call	SymFind@PLT
	test	rax, rax
	jz	$_143
	test	byte ptr [rax+0x19], 0xFFFFFFC3
	jz	$_143
	lea	rdx, [DS0026+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [DS0022+0x3F+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	add	rbx, 24
	jmp	$_148

$_143:	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	al, byte ptr [rbx]
	jmp	$_146

$_144:	cmp	dword ptr [rbx+0x4], 273
	jnz	$_147
$_145:	lea	rdx, [DS0025+0x1+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	jmp	$_147

$_146:	cmp	al, 7
	jz	$_144
	cmp	al, 5
	jz	$_145
	cmp	al, 1
	jz	$_145
	cmp	al, 10
	jz	$_145
$_147:	add	rbx, 24
	jmp	$_135

$_148:	test	esi, esi
	jz	$_149
	mov	ecx, 2157
	call	asmerr@PLT
$_149:	mov	rcx, rdi
	call	AddLineQueue@PLT
	cmp	byte ptr [rbp-0x200], 0
	jz	$_150
	lea	rcx, [rbp-0x200]
	call	AddLineQueue@PLT
$_150:	mov	rax, rbx
$_151:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_152:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 216
	inc	dword ptr [rbp+0x28]
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
$_153:	cmp	byte ptr [rbx], 8
	jz	$_154
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_194

$_154:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	mov	qword ptr [rbp-0x10], 0
	mov	qword ptr [rbp-0x30], 0
	mov	byte ptr [rbp-0x27], 0
	mov	byte ptr [rbp-0x24], -64
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	mov	eax, 1
	shl	eax, cl
	test	eax, 0x68
	jz	$_155
	mov	byte ptr [rbp-0x26], 1
	jmp	$_156

$_155:	mov	byte ptr [rbp-0x26], 0
$_156:	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x25], al
	mov	dword ptr [rbp-0x1C], 0
	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	test	rax, rax
	jnz	$_157
	mov	rcx, qword ptr [rbp-0x8]
	call	SymLCreate@PLT
	mov	dword ptr [rbp-0x1C], 1
$_157:	test	rax, rax
	jnz	$_158
	mov	rax, -1
	jmp	$_194

$_158:	mov	qword ptr [rbp-0x18], rax
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_159
	mov	byte ptr [rax+0x18], 5
	or	byte ptr [rax+0x14], 0x02
	mov	dword ptr [rax+0x58], 1
	jmp	$_160

$_159:	cmp	byte ptr [rax+0x18], 5
	jz	$_160
	test	byte ptr [rax+0x16], 0x01
	jnz	$_160
	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_194

$_160:	cmp	byte ptr [rbp-0x25], 0
	jnz	$_162
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_161
	mov	byte ptr [rax+0x19], 1
$_161:	mov	dword ptr [rbp-0x38], 2
	jmp	$_164

$_162:	cmp	dword ptr [rbp-0x1C], 0
	jz	$_163
	mov	byte ptr [rax+0x19], 3
$_163:	mov	dword ptr [rbp-0x38], 4
$_164:	add	rbx, 24
	cmp	byte ptr [rbx], 91
	jne	$_169
	add	rbx, 24
	mov	rdi, rbx
	sub	rdi, qword ptr [rbp+0x30]
	mov	eax, edi
	mov	ecx, 24
	xor	edx, edx
	div	ecx
	mov	edi, eax
	mov	dword ptr [rbp+0x28], edi
	mov	rsi, rbx
$_165:	cmp	edi, dword ptr [ModuleInfo+0x220+rip]
	jge	$_166
	cmp	byte ptr [rbx], 44
	jz	$_166
	cmp	byte ptr [rbx], 58
	jz	$_166
	inc	edi
	add	rbx, 24
	jmp	$_165

$_166:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0xA0]
	mov	r8d, edi
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_194
	cmp	dword ptr [rbp-0x64], 0
	jz	$_167
	mov	ecx, 2026
	call	asmerr@PLT
	mov	dword ptr [rbp-0xA0], 1
$_167:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp-0x18]
	mov	eax, dword ptr [rbp-0xA0]
	mov	dword ptr [rcx+0x58], eax
	or	byte ptr [rcx+0x15], 0x02
	cmp	byte ptr [rbx], 93
	jnz	$_168
	add	rbx, 24
	jmp	$_169

$_168:	mov	ecx, 2045
	call	asmerr@PLT
$_169:	mov	rsi, qword ptr [rbp-0x18]
	cmp	byte ptr [rbx], 58
	jnz	$_171
	mov	rax, qword ptr [rbx+0x20]
	mov	qword ptr [rbp-0x10], rax
	sub	rbx, qword ptr [rbp+0x30]
	mov	ecx, 24
	mov	eax, ebx
	xor	edx, edx
	div	ecx
	mov	ebx, eax
	inc	ebx
	mov	dword ptr [rbp+0x28], ebx
	lea	r8, [rbp-0x38]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	je	$_194
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	al, byte ptr [rbp-0x28]
	mov	byte ptr [rsi+0x19], al
	cmp	byte ptr [rbp-0x28], -60
	jnz	$_170
	mov	rax, qword ptr [rbp-0x30]
	mov	qword ptr [rsi+0x20], rax
	jmp	$_171

$_170:	mov	rax, qword ptr [rbp-0x30]
	mov	qword ptr [rsi+0x40], rax
$_171:	cmp	dword ptr [rbp-0x1C], 0
	jz	$_172
	mov	al, byte ptr [rbp-0x27]
	mov	byte ptr [rsi+0x39], al
	mov	al, byte ptr [rbp-0x26]
	mov	byte ptr [rsi+0x1C], al
	mov	al, byte ptr [rbp-0x25]
	mov	byte ptr [rsi+0x38], al
	mov	al, byte ptr [rbp-0x24]
	mov	byte ptr [rsi+0x3A], al
	mov	eax, dword ptr [rbp-0x38]
	mul	dword ptr [rsi+0x58]
	mov	dword ptr [rsi+0x50], eax
$_172:	cmp	dword ptr [rbp-0x1C], 0
	jz	$_176
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_176
	mov	rax, qword ptr [CurrProc+rip]
	mov	rdx, qword ptr [rax+0x68]
	cmp	qword ptr [rdx+0x10], 0
	jnz	$_173
	mov	qword ptr [rdx+0x10], rsi
	jmp	$_176

$_173:	mov	rcx, qword ptr [rdx+0x10]
$_174:	cmp	qword ptr [rcx+0x78], 0
	jz	$_175
	mov	rcx, qword ptr [rcx+0x78]
	jmp	$_174

$_175:	mov	qword ptr [rcx+0x78], rsi
$_176:	cmp	byte ptr [rbx], 0
	je	$_191
	cmp	byte ptr [rbx], 44
	jnz	$_178
	mov	rax, rbx
	sub	rax, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	ecx, 24
	div	ecx
	inc	eax
	cmp	eax, dword ptr [ModuleInfo+0x220+rip]
	jge	$_177
	add	rbx, 24
$_177:	jmp	$_191

$_178:	cmp	byte ptr [rbx], 40
	jne	$_189
	lea	rdi, [rbx-0x18]
	mov	rsi, qword ptr [rbx-0x10]
	add	rbx, 24
	mov	eax, 1
$_179:	cmp	byte ptr [rbx], 0
	jz	$_182
	cmp	byte ptr [rbx], 40
	jnz	$_180
	inc	eax
	jmp	$_181

$_180:	cmp	byte ptr [rbx], 41
	jnz	$_181
	dec	eax
	jz	$_182
$_181:	add	rbx, 24
	jmp	$_179

$_182:	cmp	byte ptr [rbx], 41
	jz	$_183
	mov	ecx, 2045
	call	asmerr@PLT
	jmp	$_194

$_183:	add	rbx, 24
	mov	qword ptr [rbp-0xA8], rbx
	mov	rcx, rsi
	call	SymFind@PLT
	test	rax, rax
	jz	$_188
	mov	rcx, rax
	cmp	byte ptr [rcx+0x18], 7
	jnz	$_187
	jmp	$_185

$_184:	mov	rcx, qword ptr [rcx+0x20]
$_185:	cmp	qword ptr [rcx+0x20], 0
	jnz	$_184
	cmp	qword ptr [rcx+0x40], 0
	jz	$_187
	cmp	byte ptr [rcx+0x19], -61
	jz	$_186
	cmp	byte ptr [rcx+0x3A], -60
	jnz	$_187
$_186:	mov	rcx, qword ptr [rcx+0x40]
$_187:	mov	rsi, qword ptr [rcx+0x8]
$_188:	mov	qword ptr [rsp+0x28], rax
	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, rsi
	mov	r8, rdi
	lea	rdx, [rbp-0xA8]
	mov	rcx, qword ptr [rbp-0x8]
	call	$_001
	mov	rbx, qword ptr [rbp-0xA8]
	jmp	$_191

$_189:	cmp	byte ptr [rbx], 3
	jnz	$_190
	cmp	byte ptr [rbx+0x1], 45
	jnz	$_190
	lea	r9, [rbp-0x38]
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp-0x8]
	call	$_110
	mov	rbx, rax
	jmp	$_191

$_190:	lea	rdx, [DS0027+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_194

$_191:	mov	rax, rbx
	sub	rax, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	ecx, 24
	div	ecx
	cmp	eax, dword ptr [ModuleInfo+0x220+rip]
	jge	$_192
	jmp	$_153

$_192:	cmp	dword ptr [rbp-0x1C], 0
	jz	$_193
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_193
	mov	rax, qword ptr [CurrProc+rip]
	mov	rcx, qword ptr [rax+0x68]
	mov	dword ptr [rcx+0x24], 0
	call	SetLocalOffsets@PLT
$_193:	xor	eax, eax
$_194:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

NewDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	cmp	qword ptr [CurrProc+rip], 0
	jnz	$_195
	mov	ecx, 2012
	call	asmerr@PLT
	jmp	$_197

$_195:	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, dword ptr [rbp+0x10]
	call	$_152
	mov	dword ptr [rbp-0x4], eax
	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_196
	call	RunLineQueue@PLT
$_196:	mov	eax, dword ptr [rbp-0x4]
$_197:	leave
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x5F, 0x00

DS0001:
	.byte  0x20, 0x6C, 0x65, 0x61, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS0002:
	.byte  0x20, 0x78, 0x6F, 0x72, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x72, 0x00

DS0003:
	.byte  0x20, 0x25, 0x73, 0x28, 0x25, 0x72, 0x29, 0x00

DS0004:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2C
	.byte  0x25, 0x73, 0x28, 0x25, 0x72, 0x29, 0x00

DS0005:
	.byte  0x20, 0x25, 0x73, 0x28, 0x25, 0x72, 0x2C, 0x25
	.byte  0x73, 0x29, 0x00

DS0006:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2C
	.byte  0x25, 0x73, 0x28, 0x25, 0x72, 0x2C, 0x25, 0x73
	.byte  0x29, 0x00

DS0007:
	.byte  0x20, 0x25, 0x73, 0x28, 0x26, 0x25, 0x73, 0x29
	.byte  0x00

DS0008:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2C
	.byte  0x25, 0x73, 0x28, 0x30, 0x29, 0x00

DS0009:
	.byte  0x20, 0x25, 0x73, 0x28, 0x30, 0x29, 0x00

DS000A:
	.byte  0x20, 0x25, 0x73, 0x28, 0x26, 0x25, 0x73, 0x2C
	.byte  0x25, 0x73, 0x29, 0x00

DS000B:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2C
	.byte  0x25, 0x73, 0x28, 0x30, 0x2C, 0x25, 0x73, 0x29
	.byte  0x00

DS000C:
	.byte  0x20, 0x25, 0x73, 0x28, 0x30, 0x2C, 0x25, 0x73
	.byte  0x29, 0x00

DS000D:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2E
	.byte  0x25, 0x73, 0x2C, 0x20, 0x25, 0x73, 0x00

DS000E:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x25, 0x72
	.byte  0x5D, 0x2E, 0x25, 0x73, 0x2E, 0x25, 0x73, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS000F:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x2E, 0x25, 0x73, 0x5B, 0x31, 0x32, 0x5D
	.byte  0x2C, 0x20, 0x30, 0x78, 0x25, 0x78, 0x0A, 0x20
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x2E, 0x25, 0x73, 0x5B, 0x38, 0x5D, 0x2C, 0x20
	.byte  0x30, 0x78, 0x25, 0x78, 0x00

DS0010:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x2E, 0x25, 0x73, 0x5B, 0x38, 0x5D, 0x2C, 0x20
	.byte  0x30, 0x78, 0x25, 0x78, 0x00

DS0011:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x2E, 0x25, 0x73, 0x5B, 0x34, 0x5D, 0x2C
	.byte  0x20, 0x30, 0x78, 0x25, 0x78, 0x0A, 0x20, 0x6D
	.byte  0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x2E
	.byte  0x25, 0x73, 0x5B, 0x30, 0x5D, 0x2C, 0x20, 0x30
	.byte  0x78, 0x25, 0x78, 0x00

DS0012:
	.byte  0x2E, 0x00

DS0013:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x5B
	.byte  0x25, 0x64, 0x5D, 0x2C, 0x20, 0x26, 0x40, 0x43
	.byte  0x53, 0x74, 0x72, 0x28, 0x25, 0x73, 0x29, 0x00

DS0014:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2E
	.byte  0x25, 0x73, 0x2C, 0x20, 0x26, 0x40, 0x43, 0x53
	.byte  0x74, 0x72, 0x28, 0x25, 0x73, 0x29, 0x00

DS0015:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x5B
	.byte  0x25, 0x64, 0x5D, 0x2C, 0x20, 0x25, 0x73, 0x00

DS0016:
	.byte  0x25, 0x73, 0x5B, 0x25, 0x64, 0x5D, 0x00

DS0017:
	.byte  0x20, 0x78, 0x6F, 0x72, 0x20, 0x65, 0x61, 0x78
	.byte  0x2C, 0x20, 0x65, 0x61, 0x78, 0x00

DS0018:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x64
	.byte  0x69, 0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20
	.byte  0x72, 0x63, 0x78, 0x0A, 0x20, 0x6C, 0x65, 0x61
	.byte  0x20, 0x72, 0x64, 0x69, 0x2C, 0x20, 0x25, 0x73
	.byte  0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x65, 0x63
	.byte  0x78, 0x2C, 0x20, 0x25, 0x64, 0x0A, 0x20, 0x72
	.byte  0x65, 0x70, 0x20, 0x73, 0x74, 0x6F, 0x73, 0x62
	.byte  0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x72, 0x63
	.byte  0x78, 0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x72
	.byte  0x64, 0x69, 0x00

DS0019:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x71, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x25, 0x64, 0x5D, 0x2C, 0x20, 0x72
	.byte  0x61, 0x78, 0x00

DS001A:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x25, 0x64, 0x5D, 0x2C, 0x20, 0x65
	.byte  0x61, 0x78, 0x00

DS001B:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x62, 0x79, 0x74
	.byte  0x65, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x5B, 0x25, 0x64, 0x5D, 0x2C, 0x20, 0x61, 0x6C
	.byte  0x00

DS001C:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x65, 0x64
	.byte  0x69, 0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20
	.byte  0x65, 0x63, 0x78, 0x0A, 0x20, 0x6C, 0x65, 0x61
	.byte  0x20, 0x65, 0x64, 0x69, 0x2C, 0x20, 0x25, 0x73
	.byte  0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x65, 0x63
	.byte  0x78, 0x2C, 0x20, 0x25, 0x64, 0x0A, 0x20, 0x72
	.byte  0x65, 0x70, 0x20, 0x73, 0x74, 0x6F, 0x73, 0x62
	.byte  0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x65, 0x63
	.byte  0x78, 0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x65
	.byte  0x64, 0x69, 0x00

DS001D:
	.byte  0x20, 0x25, 0x72, 0x20, 0x00

DS001E:
	.byte  0x64, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74
	.byte  0x72, 0x20, 0x00

DS001F:
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x00

DS0020:
	.byte  0x5B, 0x34, 0x5D, 0x2C, 0x20, 0x65, 0x64, 0x78
	.byte  0x00

DS0021:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x30, 0x5D, 0x2C, 0x20, 0x25, 0x75
	.byte  0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x34, 0x5D, 0x2C, 0x20, 0x25
	.byte  0x75, 0x00

DS0022:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x30, 0x5D, 0x2C, 0x20, 0x4C, 0x4F
	.byte  0x57, 0x33, 0x32, 0x28, 0x25, 0x73, 0x29, 0x0A
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x34, 0x5D, 0x2C, 0x20, 0x48, 0x49
	.byte  0x47, 0x48, 0x33, 0x32, 0x28, 0x25, 0x73, 0x29
	.byte  0x00

DS0023:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x30, 0x5D, 0x2C, 0x20, 0x25, 0x75
	.byte  0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x34, 0x5D, 0x2C, 0x20, 0x25
	.byte  0x75, 0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x38, 0x5D, 0x2C, 0x20, 0x25
	.byte  0x75, 0x00

DS0024:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x30, 0x5D, 0x2C, 0x20, 0x25, 0x75
	.byte  0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x34, 0x5D, 0x2C, 0x20, 0x25
	.byte  0x75, 0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x64
	.byte  0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72
	.byte  0x20, 0x25, 0x73, 0x5B, 0x38, 0x5D, 0x2C, 0x20
	.byte  0x25, 0x75, 0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20
	.byte  0x64, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74
	.byte  0x72, 0x20, 0x25, 0x73, 0x5B, 0x31, 0x32, 0x5D
	.byte  0x2C, 0x25, 0x75, 0x00

DS0025:
	.byte  0x2C, 0x20, 0x00

DS0026:
	.byte  0x26, 0x40, 0x43, 0x53, 0x74, 0x72, 0x28, 0x00

DS0027:
	.byte  0x2C, 0x00


.att_syntax prefix
