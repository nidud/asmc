
.intel_syntax noprefix

.global elf_init

.extern GetSegIdx
.extern Mangle
.extern SymTables
.extern LclAlloc
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tmemset
.extern tmemcmp
.extern tmemcpy
.extern asmerr
.extern ModuleInfo
.extern WriteError
.extern fseek
.extern fwrite


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, qword ptr [rcx+0x8]
	lea	rdi, [cst+rip]
	xor	ebx, ebx
$_002:	cmp	ebx, 4
	jnc	$_005
	movzx	r8d, byte ptr [rdi]
	mov	rdx, qword ptr [rdi+0x8]
	mov	rcx, rsi
	call	tmemcmp@PLT
	test	rax, rax
	jnz	$_004
	movzx	edx, byte ptr [rdi]
	cmp	byte ptr [rsi+rdx], 0
	jnz	$_003
	mov	rax, qword ptr [rdi+0x10]
	jmp	$_006

	jmp	$_004

$_003:	test	byte ptr [rdi+0x1], 0x01
	jz	$_004
	cmp	byte ptr [rsi+rdx], 36
	jnz	$_004
	add	rsi, rdx
	mov	rdx, qword ptr [rdi+0x10]
	mov	rcx, qword ptr [rbp+0x30]
	call	tstrcpy@PLT
	mov	rdx, rsi
	mov	rcx, rax
	call	tstrcat@PLT
	jmp	$_006

$_004:	inc	ebx
	add	rdi, 24
	jmp	$_002

$_005:	mov	rax, rsi
$_006:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_007:
	sub	rsp, 8
	xor	eax, eax
	mov	rcx, qword ptr [SymTables+0x20+rip]
$_008:	test	rcx, rcx
	jz	$_010
	mov	rdx, qword ptr [rcx+0x68]
	cmp	qword ptr [rdx+0x28], 0
	jz	$_009
	inc	eax
$_009:	mov	rcx, qword ptr [rcx+0x70]
	jmp	$_008

$_010:
	add	rsp, 8
	ret

$_011:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	mov	dword ptr [rbp-0x8], 1
	mov	rbx, rcx
	imul	esi, dword ptr [rbp+0x30], 24
	mov	dword ptr [rbx+0x28], esi
	mov	ecx, esi
	call	LclAlloc@PLT
	mov	qword ptr [rbx+0x30], rax
	mov	rdi, rax
	mov	rcx, rsi
	xor	eax, eax
	mov	rdx, rdi
	rep stosb
	lea	rdi, [rdx+0x18]
	mov	dword ptr [rdi], 1
	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	inc	rax
	add	dword ptr [rbp-0x8], eax
	mov	byte ptr [rdi+0x4], 4
	mov	word ptr [rdi+0x6], -15
	add	rdi, 24
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_012:	test	rsi, rsi
	jz	$_013
	mov	byte ptr [rdi+0x4], 3
	mov	rcx, qword ptr [rsi+0x30]
	call	GetSegIdx@PLT
	mov	word ptr [rdi+0x6], ax
	add	rdi, 24
	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_012

$_013:
	mov	rsi, qword ptr [rbp+0x38]
$_014:	test	rsi, rsi
	jz	$_020
	lea	rdx, [rbp-0x108]
	mov	rcx, qword ptr [rsi+0x8]
	call	Mangle@PLT
	lea	rbx, [rax+0x1]
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rdi], eax
	mov	rcx, qword ptr [rsi+0x8]
	mov	rdx, qword ptr [rcx+0x30]
	test	rdx, rdx
	jz	$_015
	mov	rax, qword ptr [rdx+0x68]
$_015:	test	rdx, rdx
	jz	$_016
	cmp	dword ptr [rax+0x48], 1
	jz	$_016
	mov	byte ptr [rdi+0x4], 1
	jmp	$_017

$_016:	mov	byte ptr [rdi+0x4], 2
$_017:	mov	eax, dword ptr [rcx+0x28]
	mov	dword ptr [rdi+0x8], eax
	test	edx, edx
	jz	$_018
	mov	rcx, rdx
	call	GetSegIdx@PLT
	mov	word ptr [rdi+0x6], ax
	jmp	$_019

$_018:
	mov	word ptr [rdi+0x6], -15
$_019:	add	dword ptr [rbp-0x8], ebx
	add	rdi, 24
	mov	rsi, qword ptr [rsi]
	jmp	$_014

$_020:
	mov	rsi, qword ptr [SymTables+0x10+rip]
$_021:	test	rsi, rsi
	jz	$_028
	test	byte ptr [rsi+0x3B], 0x01
	jnz	$_022
	test	byte ptr [rsi+0x3B], 0x02
	jnz	$_027
$_022:	lea	rdx, [rbp-0x108]
	mov	rcx, rsi
	call	Mangle@PLT
	lea	rbx, [rax+0x1]
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rdi], eax
	test	byte ptr [rsi+0x3B], 0x01
	jz	$_023
	mov	byte ptr [rdi+0x4], 21
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rdi+0x8], eax
	mov	word ptr [rdi+0x6], -14
	jmp	$_026

$_023:	mov	rax, rsi
	test	byte ptr [rax+0x3B], 0x01
	jnz	$_024
	cmp	qword ptr [rax+0x58], 0
	jz	$_024
	mov	byte ptr [rdi+0x4], 32
	jmp	$_025

$_024:	mov	byte ptr [rdi+0x4], 16
$_025:	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rdi+0x8], eax
	mov	word ptr [rdi+0x6], 0
$_026:	add	dword ptr [rbp-0x8], ebx
	add	rdi, 24
$_027:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_021

$_028:
	mov	rsi, qword ptr [ModuleInfo+0x10+rip]
$_029:	test	rsi, rsi
	je	$_037
	mov	rbx, qword ptr [rsi+0x8]
	lea	rdx, [rbp-0x108]
	mov	rcx, rbx
	call	Mangle@PLT
	mov	dword ptr [rbp-0x4], eax
	mov	rdx, qword ptr [rbx+0x30]
	test	rdx, rdx
	jz	$_030
	mov	rcx, qword ptr [rdx+0x68]
$_030:	test	rdx, rdx
	jz	$_031
	cmp	dword ptr [rcx+0x48], 1
	jz	$_031
	mov	byte ptr [rdi+0x4], 17
	jmp	$_032

$_031:	mov	byte ptr [rdi+0x4], 18
$_032:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rdi], eax
	mov	eax, dword ptr [rbx+0x28]
	mov	dword ptr [rdi+0x8], eax
	cmp	byte ptr [rbx+0x18], 1
	jnz	$_035
	test	rdx, rdx
	jz	$_033
	mov	rcx, rdx
	call	GetSegIdx@PLT
	mov	word ptr [rdi+0x6], ax
	jmp	$_034

$_033:
	mov	word ptr [rdi+0x6], -15
$_034:	jmp	$_036

$_035:
	mov	word ptr [rdi+0x6], 0
$_036:	mov	eax, dword ptr [rbp-0x4]
	add	dword ptr [rbp-0x8], eax
	inc	dword ptr [rbp-0x8]
	add	rdi, 24
	mov	rsi, qword ptr [rsi]
	jmp	$_029

$_037:
	mov	eax, dword ptr [rbp-0x8]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_038:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	qword ptr [rbp-0x18], 0
	mov	qword ptr [rbp-0x10], 0
	mov	rbx, rcx
	mov	dword ptr [rbx], 2
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_039:	test	rsi, rsi
	jz	$_040
	mov	eax, dword ptr [rbx]
	mov	dword ptr [rsi+0x60], eax
	inc	dword ptr [rbx]
	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_039

$_040:
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_041:	test	rsi, rsi
	je	$_048
	mov	rcx, qword ptr [rsi+0x68]
	cmp	dword ptr [rcx+0x40], 0
	jz	$_047
	mov	rdi, qword ptr [rcx+0x28]
$_042:	test	rdi, rdi
	jz	$_047
	mov	rcx, qword ptr [rdi+0x30]
	test	byte ptr [rcx+0x14], 0x40
	jz	$_043
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rdi+0x30], rax
	jmp	$_046

$_043:	cmp	byte ptr [rcx+0x18], 1
	jnz	$_046
	test	dword ptr [rcx+0x14], 0x4080
	jnz	$_046
	or	byte ptr [rcx+0x15], 0x40
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	qword ptr [rax], 0
	mov	rcx, qword ptr [rdi+0x30]
	mov	qword ptr [rax+0x8], rcx
	cmp	qword ptr [rbp-0x10], 0
	jz	$_044
	mov	rdx, qword ptr [rbp-0x10]
	mov	qword ptr [rdx], rax
	mov	qword ptr [rbp-0x10], rax
	jmp	$_045

$_044:	mov	qword ptr [rbp-0x18], rax
	mov	qword ptr [rbp-0x10], rax
$_045:	mov	eax, dword ptr [rbx]
	mov	dword ptr [rcx+0x60], eax
	inc	dword ptr [rbx]
$_046:	mov	rdi, qword ptr [rdi+0x8]
	jmp	$_042

$_047:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_041

$_048:
	mov	eax, dword ptr [rbx]
	mov	dword ptr [rbx+0x4], eax
	mov	rcx, qword ptr [SymTables+0x10+rip]
$_049:	test	rcx, rcx
	jz	$_052
	test	byte ptr [rcx+0x3B], 0x01
	jnz	$_050
	test	byte ptr [rcx+0x3B], 0x02
	jz	$_050
	jmp	$_051

$_050:	mov	eax, dword ptr [rbx]
	mov	dword ptr [rcx+0x60], eax
	inc	dword ptr [rbx]
$_051:	mov	rcx, qword ptr [rcx+0x70]
	jmp	$_049

$_052:
	mov	rcx, qword ptr [ModuleInfo+0x10+rip]
$_053:	test	rcx, rcx
	jz	$_054
	mov	rdx, qword ptr [rcx+0x8]
	mov	eax, dword ptr [rbx]
	mov	dword ptr [rdx+0x60], eax
	inc	dword ptr [rbx]
	mov	rcx, qword ptr [rcx]
	jmp	$_053

$_054:
	mov	eax, dword ptr [rbx]
	mov	dword ptr [rbp-0x4], eax
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_055
	mov	r8, qword ptr [rbp-0x18]
	mov	edx, dword ptr [rbp-0x4]
	mov	rcx, rbx
	call	$_011
	mov	dword ptr [rbp-0x8], eax
$_055:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rbx+0x38], eax
	mov	ecx, dword ptr [rbp-0x8]
	call	LclAlloc@PLT
	mov	qword ptr [rbx+0x40], rax
	lea	rdi, [rax+0x1]
	mov	rsi, qword ptr [rbx+0x8]
	jmp	$_057

$_056:	movsb
$_057:	cmp	byte ptr [rsi], 0
	jnz	$_056
	movsb
	mov	rsi, qword ptr [rbp-0x18]
$_058:	test	rsi, rsi
	jz	$_059
	mov	rdx, rdi
	mov	rcx, qword ptr [rsi+0x8]
	call	Mangle@PLT
	lea	rdi, [rdi+rax+0x1]
	mov	rsi, qword ptr [rsi]
	jmp	$_058

$_059:
	mov	rsi, qword ptr [SymTables+0x10+rip]
$_060:	test	rsi, rsi
	jz	$_063
	test	byte ptr [rsi+0x3B], 0x01
	jnz	$_061
	test	byte ptr [rsi+0x3B], 0x02
	jz	$_061
	jmp	$_062

$_061:	mov	rdx, rdi
	mov	rcx, rsi
	call	Mangle@PLT
	lea	rdi, [rdi+rax+0x1]
$_062:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_060

$_063:
	mov	rsi, qword ptr [ModuleInfo+0x10+rip]
$_064:	test	rsi, rsi
	jz	$_065
	mov	rcx, qword ptr [rsi+0x8]
	mov	rdx, rdi
	call	Mangle@PLT
	lea	rdi, [rdi+rax+0x1]
	mov	rsi, qword ptr [rsi]
	jmp	$_064

$_065:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_066:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	mov	dword ptr [rbp-0x4], 1
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_067:	test	rsi, rsi
	jz	$_072
	mov	rbx, qword ptr [rsi+0x68]
	cmp	qword ptr [rbx+0x60], 0
	jz	$_068
	mov	rdi, qword ptr [rbx+0x60]
	jmp	$_069

$_068:	lea	rdx, [rbp-0xFC]
	mov	rcx, rsi
	call	$_001
	mov	rdi, rax
$_069:	mov	rcx, rdi
	call	tstrlen@PLT
	add	dword ptr [rbp-0x4], eax
	inc	dword ptr [rbp-0x4]
	cmp	qword ptr [rbx+0x28], 0
	jz	$_071
	mov	rcx, rdi
	call	tstrlen@PLT
	add	dword ptr [rbp-0x4], eax
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_070
	add	dword ptr [rbp-0x4], 6
	jmp	$_071

$_070:	add	dword ptr [rbp-0x4], 5
$_071:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_067

$_072:
	lea	rdi, [internal_segparms+rip]
	xor	ebx, ebx
$_073:	cmp	ebx, 3
	jnc	$_074
	mov	rcx, qword ptr [rdi]
	call	tstrlen@PLT
	inc	eax
	add	dword ptr [rbp-0x4], eax
	inc	ebx
	add	rdi, 16
	jmp	$_073

$_074:
	mov	rbx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rbx+0x18], eax
	mov	ecx, dword ptr [rbp-0x4]
	call	LclAlloc@PLT
	mov	qword ptr [rbx+0x20], rax
	mov	rdi, rax
	mov	byte ptr [rdi], 0
	inc	rdi
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_075:	test	rsi, rsi
	jz	$_078
	mov	rcx, qword ptr [rsi+0x68]
	cmp	qword ptr [rcx+0x60], 0
	jz	$_076
	mov	rax, qword ptr [rcx+0x60]
	jmp	$_077

$_076:	lea	rdx, [rbp-0xFC]
	mov	rcx, rsi
	call	$_001
$_077:	mov	rdx, rax
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rdi, [rdi+rax+0x1]
	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_075

$_078:
	xor	esi, esi
$_079:	cmp	esi, 3
	jnc	$_080
	imul	ecx, esi, 16
	lea	rdx, [internal_segparms+rip]
	mov	rdx, qword ptr [rdx+rcx]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rdi, [rdi+rax+0x1]
	inc	esi
	jmp	$_079

$_080:
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_081:	test	rsi, rsi
	je	$_087
	mov	rcx, qword ptr [rsi+0x68]
	cmp	qword ptr [rcx+0x28], 0
	jz	$_086
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_082
	lea	rdx, [DS000B+rip]
	mov	rcx, rdi
	call	tstrcpy@PLT
	jmp	$_083

$_082:	lea	rdx, [DS000C+rip]
	mov	rcx, rdi
	call	tstrcpy@PLT
$_083:	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	mov	rcx, qword ptr [rsi+0x68]
	cmp	qword ptr [rcx+0x60], 0
	jz	$_084
	mov	rax, qword ptr [rcx+0x60]
	jmp	$_085

$_084:	lea	rdx, [rbp-0xFC]
	mov	rcx, rsi
	call	$_001
$_085:	mov	rdx, rax
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rdi, [rdi+rax+0x1]
$_086:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_081

$_087:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_088:
	mov	rcx, qword ptr [rax+0x68]
	xor	eax, eax
	mov	rcx, qword ptr [rcx+0x28]
$_089:	test	rcx, rcx
	jz	$_090
	mov	rcx, qword ptr [rcx+0x8]
	inc	eax
	jmp	$_089

$_090:
	ret

$_091:
	mov	rcx, qword ptr [rax+0x68]
	cmp	byte ptr [rcx+0x6A], -1
	jnz	$_092
	xor	eax, eax
	jmp	$_093

$_092:	mov	cl, byte ptr [rcx+0x6A]
	mov	eax, 1
	shl	eax, cl
$_093:	ret

$_094:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 104
	add	dword ptr [rbp+0x38], 15
	and	dword ptr [rbp+0x38], 0xFFFFFFF0
	mov	rcx, qword ptr [rbp+0x30]
	call	$_066
	mov	r8d, 64
	xor	edx, edx
	lea	rcx, [rbp-0x40]
	call	tmemset@PLT
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 64
	mov	esi, 1
	lea	rdi, [rbp-0x40]
	call	fwrite@PLT
	cmp	rax, 64
	jz	$_095
	call	WriteError@PLT
$_095:	mov	rbx, qword ptr [rbp+0x30]
	mov	rdi, qword ptr [rbx+0x20]
	inc	rdi
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_096:	test	rsi, rsi
	je	$_105
	mov	r8d, 64
	xor	edx, edx
	lea	rcx, [rbp-0x40]
	call	tmemset@PLT
	mov	rax, rdi
	sub	rax, qword ptr [rbx+0x20]
	mov	dword ptr [rbp-0x40], eax
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rdi, [rdi+rax+0x1]
	mov	rcx, qword ptr [rsi+0x68]
	cmp	byte ptr [rcx+0x6C], 1
	jnz	$_097
	mov	dword ptr [rbp-0x3C], 7
	jmp	$_102

$_097:	cmp	dword ptr [rcx+0x48], 3
	jz	$_098
	mov	dword ptr [rbp-0x3C], 1
	jmp	$_099

$_098:	mov	dword ptr [rbp-0x3C], 8
$_099:	cmp	dword ptr [rcx+0x48], 1
	jnz	$_100
	mov	dword ptr [rbp-0x38], 6
	jmp	$_102

$_100:	cmp	byte ptr [rcx+0x6B], 1
	jnz	$_101
	mov	dword ptr [rbp-0x38], 2
	jmp	$_102

$_101:	mov	dword ptr [rbp-0x38], 3
	cmp	qword ptr [rcx+0x50], 0
	jz	$_102
	mov	rcx, qword ptr [rcx+0x50]
	lea	rdx, [DS0007+rip]
	mov	rcx, qword ptr [rcx+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_102
	mov	dword ptr [rbp-0x38], 2
$_102:	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x28], eax
	mov	rcx, qword ptr [rsi+0x68]
	mov	dword ptr [rcx+0x38], eax
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rbp-0x20], eax
	mov	rax, rsi
	call	$_091
	mov	dword ptr [rbp-0x10], eax
	push	rsi
	push	rdi
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 64
	mov	esi, 1
	lea	rdi, [rbp-0x40]
	call	fwrite@PLT
	pop	rdi
	pop	rsi
	cmp	eax, 64
	jz	$_103
	call	WriteError@PLT
$_103:	mov	rax, rsi
	call	$_088
	mov	rcx, qword ptr [rsi+0x68]
	mov	dword ptr [rcx+0x40], eax
	cmp	dword ptr [rbp-0x3C], 8
	jz	$_104
	mov	eax, dword ptr [rbp-0x20]
	add	dword ptr [rbp+0x38], eax
	add	dword ptr [rbp+0x38], 15
	and	dword ptr [rbp+0x38], 0xFFFFFFF0
$_104:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_096

$_105:
	mov	rcx, rbx
	call	$_038
	mov	r8d, 64
	xor	edx, edx
	lea	rcx, [rbp-0x40]
	call	tmemset@PLT
	xor	esi, esi
$_106:	cmp	esi, 3
	jnc	$_110
	mov	rax, rdi
	sub	rax, qword ptr [rbx+0x20]
	mov	dword ptr [rbp-0x40], eax
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rdi, [rdi+rax+0x1]
	imul	ecx, esi, 16
	lea	rdx, [internal_segparms+rip]
	mov	eax, dword ptr [rdx+rcx+0x8]
	mov	dword ptr [rbp-0x3C], eax
	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x28], eax
	imul	ecx, esi, 16
	mov	dword ptr [rbx+rcx+0x1C], eax
	mov	eax, dword ptr [rbx+rcx+0x18]
	mov	dword ptr [rbp-0x20], eax
	cmp	esi, 1
	jnz	$_107
	mov	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rcx+0x8]
	add	eax, 3
	mov	dword ptr [rbp-0x18], eax
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0x14], eax
	mov	dword ptr [rbp-0x10], 4
	mov	dword ptr [rbp-0x8], 24
	jmp	$_108

$_107:	mov	dword ptr [rbp-0x18], 0
	mov	dword ptr [rbp-0x14], 0
	mov	dword ptr [rbp-0x10], 1
	mov	dword ptr [rbp-0x8], 0
$_108:	push	rsi
	push	rdi
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 64
	mov	esi, 1
	lea	rdi, [rbp-0x40]
	call	fwrite@PLT
	pop	rdi
	pop	rsi
	cmp	eax, 64
	jz	$_109
	call	WriteError@PLT
$_109:	mov	eax, dword ptr [rbp-0x20]
	add	dword ptr [rbp+0x38], eax
	add	dword ptr [rbp+0x38], 15
	and	dword ptr [rbp+0x38], 0xFFFFFFF0
	inc	esi
	jmp	$_106

$_110:
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_111:	test	rsi, rsi
	je	$_114
	mov	rcx, qword ptr [rsi+0x68]
	cmp	qword ptr [rcx+0x28], 0
	je	$_113
	mov	r8d, 64
	xor	edx, edx
	lea	rcx, [rbp-0x40]
	call	tmemset@PLT
	mov	rax, rdi
	sub	rax, qword ptr [rbx+0x20]
	mov	dword ptr [rbp-0x40], eax
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rdi, [rdi+rax+0x1]
	mov	dword ptr [rbp-0x3C], 4
	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x28], eax
	mov	rcx, qword ptr [rsi+0x68]
	mov	dword ptr [rcx+0xC], eax
	mov	eax, 24
	mul	dword ptr [rcx+0x40]
	mov	dword ptr [rbp-0x20], eax
	mov	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rcx+0x8]
	add	eax, 2
	mov	dword ptr [rbp-0x18], eax
	mov	rcx, qword ptr [rsi+0x30]
	call	GetSegIdx@PLT
	mov	dword ptr [rbp-0x14], eax
	mov	dword ptr [rbp-0x10], 4
	mov	dword ptr [rbp-0x8], 24
	push	rsi
	push	rdi
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 64
	mov	esi, 1
	lea	rdi, [rbp-0x40]
	call	fwrite@PLT
	pop	rdi
	pop	rsi
	cmp	eax, 64
	jz	$_112
	call	WriteError@PLT
$_112:	mov	eax, dword ptr [rbp-0x20]
	add	dword ptr [rbp+0x38], eax
	add	dword ptr [rbp+0x38], 15
	and	dword ptr [rbp+0x38], 0xFFFFFFF0
$_113:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_111

$_114:
	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_115:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rbx, rcx
	mov	rcx, qword ptr [rdx+0x68]
	mov	rsi, qword ptr [rcx+0x28]
$_116:	test	rsi, rsi
	je	$_131
	mov	eax, dword ptr [rsi+0x14]
	mov	dword ptr [rbp-0x10], eax
	jmp	$_128

$_117:	mov	byte ptr [rbp-0x1], 2
	mov	rcx, qword ptr [rsi+0x30]
	cmp	byte ptr [ModuleInfo+0x352+rip], 0
	jz	$_118
	cmp	byte ptr [rcx+0x18], 2
	jnz	$_118
	test	byte ptr [rcx+0x15], 0x08
	jz	$_118
	mov	byte ptr [rbp-0x1], 4
$_118:	jmp	$_129

$_119:	mov	byte ptr [rbp-0x1], 1
	jmp	$_129

$_120:	mov	byte ptr [rbp-0x1], 8
	jmp	$_129

$_121:	mov	dword ptr [rbx+0x10], 1
	mov	byte ptr [rbp-0x1], 20
	jmp	$_129

$_122:	mov	dword ptr [rbx+0x10], 1
	mov	byte ptr [rbp-0x1], 21
	jmp	$_129

$_123:	mov	dword ptr [rbx+0x10], 1
	mov	byte ptr [rbp-0x1], 22
	jmp	$_129

$_124:	mov	dword ptr [rbx+0x10], 1
	mov	byte ptr [rbp-0x1], 23
	jmp	$_129

$_125:	mov	byte ptr [rbp-0x1], 0
	mov	rcx, qword ptr [rbp+0x30]
	cmp	byte ptr [rsi+0x18], 14
	jnc	$_126
	mov	rdx, qword ptr [ModuleInfo+0x1A8+rip]
	mov	eax, dword ptr [rsi+0x14]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rcx+0x8]
	movzx	r8d, byte ptr [rsi+0x18]
	movsx	edx, byte ptr [rdx+0xA]
	mov	ecx, 3019
	call	asmerr@PLT
	jmp	$_127

$_126:	mov	r9d, dword ptr [rsi+0x14]
	mov	r8, qword ptr [rcx+0x8]
	movzx	edx, byte ptr [rsi+0x18]
	mov	ecx, 3014
	call	asmerr@PLT
$_127:	jmp	$_129

$_128:	cmp	byte ptr [rsi+0x18], 3
	je	$_117
	cmp	byte ptr [rsi+0x18], 6
	je	$_119
	cmp	byte ptr [rsi+0x18], 12
	je	$_120
	cmp	byte ptr [rsi+0x18], 5
	je	$_121
	cmp	byte ptr [rsi+0x18], 2
	je	$_122
	cmp	byte ptr [rsi+0x18], 4
	je	$_123
	cmp	byte ptr [rsi+0x18], 1
	je	$_124
	jmp	$_125

$_129:	mov	rcx, qword ptr [rsi+0x30]
	movzx	edx, byte ptr [rbp-0x1]
	mov	eax, dword ptr [rcx+0x60]
	shl	eax, 8
	add	eax, edx
	mov	dword ptr [rbp-0xC], eax
	mov	rbx, rsi
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 8
	mov	esi, 1
	lea	rdi, [rbp-0x10]
	call	fwrite@PLT
	cmp	eax, 8
	jz	$_130
	call	WriteError@PLT
$_130:	mov	rsi, rbx
	mov	rbx, qword ptr [rbp+0x28]
	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_116

$_131:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_132:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	rdx, rcx
	mov	rcx, qword ptr [rdx+0x68]
	mov	rsi, qword ptr [rcx+0x28]
$_133:	test	rsi, rsi
	je	$_149
	mov	rcx, qword ptr [rsi+0x30]
	mov	edi, dword ptr [rcx+0x60]
	mov	eax, dword ptr [rsi+0x14]
	mov	qword ptr [rbp-0x18], rax
	mov	edx, dword ptr [rsi+0x10]
	movzx	rax, byte ptr [rsi+0x1A]
	sub	rax, rdx
	neg	rax
	mov	qword ptr [rbp-0x8], rax
	movzx	eax, byte ptr [rsi+0x18]
	jmp	$_146

$_134:	mov	ebx, 2
	cmp	byte ptr [ModuleInfo+0x352+rip], 0
	jz	$_135
	cmp	byte ptr [rcx+0x18], 2
	jnz	$_135
	test	byte ptr [rcx+0x15], 0x08
	jz	$_135
	mov	ebx, 4
$_135:	jmp	$_147

$_136:	mov	ebx, 1
	jmp	$_147

$_137:	mov	ebx, 8
	jmp	$_147

$_138:	mov	ebx, 10
	jmp	$_147

$_139:	mov	ebx, 12
	jmp	$_147

$_140:	mov	ebx, 13
	jmp	$_147

$_141:	mov	ebx, 14
	jmp	$_147

$_142:	mov	ebx, 15
	jmp	$_147

$_143:	mov	rcx, qword ptr [rbp+0x28]
	mov	ebx, 0
	cmp	byte ptr [rsi+0x18], 14
	jnc	$_144
	mov	rdx, qword ptr [ModuleInfo+0x1A8+rip]
	mov	eax, dword ptr [rsi+0x14]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rcx+0x8]
	movzx	r8d, byte ptr [rsi+0x18]
	lea	rdx, [rdx+0xA]
	mov	ecx, 3019
	call	asmerr@PLT
	jmp	$_145

$_144:	mov	r9d, dword ptr [rsi+0x14]
	mov	r8, qword ptr [rcx+0x8]
	movzx	edx, byte ptr [rsi+0x18]
	mov	ecx, 3014
	call	asmerr@PLT
$_145:	jmp	$_147

$_146:	cmp	eax, 3
	je	$_134
	cmp	eax, 7
	je	$_136
	cmp	eax, 12
	je	$_137
	cmp	eax, 6
	je	$_138
	cmp	eax, 5
	je	$_139
	cmp	eax, 2
	je	$_140
	cmp	eax, 4
	je	$_141
	cmp	eax, 1
	je	$_142
	jmp	$_143

$_147:	mov	dword ptr [rbp-0x10], ebx
	mov	dword ptr [rbp-0xC], edi
	mov	qword ptr [rbp-0x20], rsi
	mov	qword ptr [rbp-0x28], rdi
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 24
	mov	esi, 1
	lea	rdi, [rbp-0x18]
	call	fwrite@PLT
	cmp	rax, 24
	jz	$_148
	call	WriteError@PLT
$_148:	mov	rsi, qword ptr [rbp-0x20]
	mov	rdi, qword ptr [rbp-0x28]
	mov	rsi, qword ptr [rsi+0x8]
	jmp	$_133

$_149:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_150:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_151:	test	rsi, rsi
	je	$_155
	mov	rdi, qword ptr [rsi+0x68]
	mov	ebx, dword ptr [rsi+0x50]
	sub	ebx, dword ptr [rdi+0x8]
	cmp	dword ptr [rdi+0x48], 3
	jz	$_154
	test	ebx, ebx
	jz	$_154
	mov	qword ptr [rbp-0x8], rsi
	cmp	qword ptr [rdi+0x10], 0
	jnz	$_152
	mov	edx, 1
	mov	esi, ebx
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	jmp	$_153

$_152:	mov	ecx, dword ptr [rdi+0x38]
	add	ecx, dword ptr [rdi+0x8]
	xor	edx, edx
	mov	esi, ecx
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rsi, qword ptr [rbp-0x8]
	mov	rdi, qword ptr [rsi+0x68]
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, ebx
	mov	esi, 1
	mov	rdi, qword ptr [rdi+0x10]
	call	fwrite@PLT
	cmp	rax, rbx
	jz	$_153
	call	WriteError@PLT
$_153:	mov	rsi, qword ptr [rbp-0x8]
$_154:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_151

$_155:
	mov	rbx, qword ptr [rbp+0x30]
	xor	esi, esi
$_156:	cmp	esi, 3
	jnc	$_158
	imul	edi, esi, 16
	cmp	qword ptr [rbx+rdi+0x20], 0
	jz	$_157
	mov	qword ptr [rbp-0x8], rsi
	mov	qword ptr [rbp-0x10], rdi
	xor	edx, edx
	mov	esi, dword ptr [rbx+rdi+0x1C]
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rdi, qword ptr [rbp-0x10]
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, dword ptr [rbx+rdi+0x18]
	mov	esi, 1
	mov	rdi, qword ptr [rbx+rdi+0x20]
	call	fwrite@PLT
	mov	rsi, qword ptr [rbp-0x8]
	mov	rdi, qword ptr [rbp-0x10]
	cmp	eax, dword ptr [rbx+rdi+0x18]
	jz	$_157
	call	WriteError@PLT
$_157:	inc	esi
	jmp	$_156

$_158:
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_159:	test	rsi, rsi
	jz	$_162
	mov	rdi, qword ptr [rsi+0x68]
	cmp	dword ptr [rdi+0x40], 0
	jz	$_161
	mov	qword ptr [rbp-0x8], rsi
	mov	qword ptr [rbp-0x10], rdi
	xor	edx, edx
	mov	esi, dword ptr [rdi+0xC]
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rsi, qword ptr [rbp-0x8]
	mov	rdi, qword ptr [rbp-0x10]
	mov	rcx, qword ptr [rbp+0x28]
	cmp	byte ptr [rcx+0x1CD], 2
	jnz	$_160
	mov	rcx, rsi
	call	$_132
	jmp	$_161

$_160:	mov	rdx, rsi
	mov	rcx, rbx
	call	$_115
$_161:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_159

$_162:
	cmp	dword ptr [rbx+0x10], 0
	jz	$_163
	mov	ecx, 8013
	call	asmerr@PLT
$_163:	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

elf_write_module:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	r8d, 136
	xor	edx, edx
	lea	rcx, [rbp-0x88]
	call	tmemset@PLT
	mov	rdi, qword ptr [ModuleInfo+0x90+rip]
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rdx, [rdi+rax]
	jmp	$_165

$_164:	cmp	byte ptr [rdx-0x1], 92
	jz	$_166
	cmp	byte ptr [rdx-0x1], 47
	jz	$_166
	dec	rdx
$_165:	cmp	rdx, rdi
	ja	$_164
$_166:	mov	qword ptr [rbp-0x80], rdx
	xor	edx, edx
	xor	esi, esi
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rdi, qword ptr [rbp+0x28]
	mov	r8d, 4
	lea	rdx, [DS000D+rip]
	lea	rcx, [rbp-0x40]
	call	tmemcpy@PLT
	mov	byte ptr [rbp-0x3C], 2
	mov	byte ptr [rbp-0x3B], 1
	mov	byte ptr [rbp-0x3A], 1
	mov	al, byte ptr [rdi+0x1E4]
	mov	byte ptr [rbp-0x39], al
	mov	word ptr [rbp-0x30], 1
	mov	word ptr [rbp-0x2E], 62
	mov	dword ptr [rbp-0x2C], 1
	mov	dword ptr [rbp-0x18], 64
	mov	word ptr [rbp-0xC], 64
	mov	word ptr [rbp-0x6], 64
	call	$_007
	add	eax, dword ptr [rdi+0x8]
	add	eax, 4
	mov	word ptr [rbp-0x4], ax
	mov	eax, dword ptr [rdi+0x8]
	add	eax, 1
	mov	word ptr [rbp-0x2], ax
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 64
	mov	esi, 1
	lea	rdi, [rbp-0x40]
	call	fwrite@PLT
	cmp	rax, 64
	jz	$_167
	call	WriteError@PLT
$_167:	mov	rdi, qword ptr [rbp+0x28]
	movzx	eax, word ptr [rbp-0x4]
	mul	word ptr [rbp-0x6]
	add	eax, 64
	mov	r8d, eax
	lea	rdx, [rbp-0x88]
	mov	rcx, rdi
	call	$_094
	lea	rdx, [rbp-0x88]
	mov	rcx, rdi
	call	$_150
	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

elf_init:
	mov	byte ptr [rcx+0x1E4], 0
	lea	rax, [elf_write_module+rip]
	mov	qword ptr [rcx+0x158], rax
	ret


.SECTION .data
	.ALIGN	16

internal_segparms:
	.quad  DS0000
	.quad  0x0000000000000003
	.quad  DS0001
	.quad  0x0000000000000002
	.quad  DS0002
	.quad  0x0000000000000003

cst:
	.byte  0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.quad  DS0003
	.quad  DS0004
	.quad  0x0000000000000105
	.quad  DS0005
	.quad  DS0006
	.quad  0x0000000000000105
	.quad  DS0007
	.quad  DS0008
	.quad  0x0000000000000004
	.quad  DS0009
	.quad  DS000A

DS000B:
	.byte  0x2E, 0x72, 0x65, 0x6C, 0x61, 0x00

DS000C:
	.byte  0x2E, 0x72, 0x65, 0x6C, 0x00

DS000D:
	.byte  0x7F, 0x45, 0x4C, 0x46, 0x00


.SECTION .rodata
	.ALIGN	16

DS0000:
	.byte  0x2E, 0x73, 0x68, 0x73, 0x74, 0x72, 0x74, 0x61
	.byte  0x62, 0x00

DS0001:
	.byte  0x2E, 0x73, 0x79, 0x6D, 0x74, 0x61, 0x62, 0x00

DS0002:
	.byte  0x2E, 0x73, 0x74, 0x72, 0x74, 0x61, 0x62, 0x00

DS0003:
	.byte  0x5F, 0x54, 0x45, 0x58, 0x54, 0x00

DS0004:
	.byte  0x2E, 0x74, 0x65, 0x78, 0x74, 0x00

DS0005:
	.byte  0x5F, 0x44, 0x41, 0x54, 0x41, 0x00

DS0006:
	.byte  0x2E, 0x64, 0x61, 0x74, 0x61, 0x00

DS0007:
	.byte  0x43, 0x4F, 0x4E, 0x53, 0x54, 0x00

DS0008:
	.byte  0x2E, 0x72, 0x6F, 0x64, 0x61, 0x74, 0x61, 0x00

DS0009:
	.byte  0x5F, 0x42, 0x53, 0x53, 0x00

DS000A:
	.byte  0x2E, 0x62, 0x73, 0x73, 0x00


.att_syntax prefix
