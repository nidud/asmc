
.intel_syntax noprefix

.global coff_init

.extern cv_write_debug_tables
.extern GetFName
.extern AddPublicData
.extern GetSegIdx
.extern CreateIntSegment
.extern SymTables
.extern Mangle
.extern LclAlloc
.extern tstrncpy
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern tmemset
.extern tmemcpy
.extern tsprintf
.extern ConvertSectionName
.extern asmerr
.extern Options
.extern ModuleInfo
.extern WriteError
.extern fseek
.extern fwrite
.extern time


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rdx
	mov	rbx, rcx
	mov	edi, dword ptr [rbx+0x70]
	mov	ecx, dword ptr [rbp+0x38]
	lea	eax, [rcx+0x1]
	add	dword ptr [rbx+0x70], eax
	lea	ecx, [rax+0xF]
	call	LclAlloc@PLT
	mov	ecx, dword ptr [rbp+0x38]
	mov	edx, edi
	mov	qword ptr [rax], 0
	lea	rdi, [rax+0x8]
	inc	ecx
	rep movsb
	cmp	qword ptr [rbx+0x60], 0
	jz	$_002
	mov	rcx, qword ptr [rbx+0x68]
	mov	qword ptr [rcx], rax
	mov	qword ptr [rbx+0x68], rax
	jmp	$_003

$_002:	mov	qword ptr [rbx+0x60], rax
	mov	qword ptr [rbx+0x68], rax
$_003:	mov	eax, edx
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_004:
	xor	eax, eax
	mov	rdx, qword ptr [rcx]
$_005:	test	rdx, rdx
	jz	$_006
	mov	rdx, qword ptr [rdx]
	inc	eax
	jmp	$_005

$_006:
	ret

$_007:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 328
	mov	rsi, rcx
	imul	esi, dword ptr [rsi+0x8], 40
	add	esi, 20
	mov	rbx, qword ptr [rbp+0x30]
	mov	dword ptr [rbx+0x20], esi
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_008:	test	rdi, rdi
	je	$_037
	mov	dword ptr [rbp-0x4], 0
	mov	rdx, qword ptr [rdi+0x68]
	mov	rax, qword ptr [rdx+0x60]
	test	rax, rax
	jnz	$_009
	lea	r8, [rbp-0x128]
	lea	rdx, [rbp-0x4]
	mov	rcx, rdi
	call	ConvertSectionName@PLT
$_009:	mov	rbx, rax
	mov	rcx, rax
	call	tstrlen@PLT
	cmp	rax, 8
	ja	$_010
	mov	r8d, 8
	mov	rdx, rbx
	lea	rcx, [rbp-0x30]
	call	tstrncpy@PLT
	jmp	$_011

$_010:	mov	r8d, eax
	mov	rdx, rbx
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	r8, rax
	lea	rdx, [DS0002+rip]
	lea	rcx, [rbp-0x30]
	call	tsprintf@PLT
$_011:	mov	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rbp-0x20], eax
	test	eax, eax
	jz	$_012
	mov	eax, esi
$_012:	mov	dword ptr [rbp-0x1C], eax
	xor	eax, eax
	mov	dword ptr [rbp-0x28], eax
	mov	dword ptr [rbp-0x24], eax
	mov	dword ptr [rbp-0x18], eax
	mov	dword ptr [rbp-0x14], eax
	mov	word ptr [rbp-0x10], ax
	mov	word ptr [rbp-0xE], ax
	mov	dword ptr [rbp-0xC], eax
	mov	rdx, qword ptr [rdi+0x68]
	cmp	byte ptr [rdx+0x6C], 0
	jz	$_015
	mov	rcx, qword ptr [rbp+0x30]
	cmp	rdi, qword ptr [rcx]
	jnz	$_013
	mov	dword ptr [rbp-0xC], 2560
	jmp	$_014

$_013:	mov	dword ptr [rbp-0xC], 576
$_014:	jmp	$_025

$_015:	cmp	byte ptr [rdx+0x6A], -1
	jz	$_016
	movzx	eax, byte ptr [rdx+0x6A]
	inc	eax
	shl	eax, 20
	or	dword ptr [rbp-0xC], eax
$_016:	cmp	byte ptr [rdx+0x73], 0
	jz	$_017
	or	byte ptr [rbp-0xB], 0x10
$_017:	xor	ecx, ecx
	cmp	qword ptr [rdx+0x50], 0
	jz	$_018
	mov	rax, qword ptr [rdx+0x50]
	mov	rax, qword ptr [rax+0x8]
	cmp	dword ptr [rax], 1397641027
	jnz	$_018
	cmp	word ptr [rax+0x4], 84
	jnz	$_018
	inc	ecx
$_018:	cmp	dword ptr [rdx+0x48], 1
	jnz	$_019
	or	dword ptr [rbp-0xC], 0x60000020
	jmp	$_025

$_019:	cmp	byte ptr [rdx+0x6B], 0
	jz	$_020
	or	dword ptr [rbp-0xC], 0x40000040
	jmp	$_025

$_020:	test	ecx, ecx
	jz	$_021
	or	dword ptr [rbp-0xC], 0x40000040
	jmp	$_025

$_021:	cmp	dword ptr [rdx+0x48], 3
	jz	$_022
	cmp	dword ptr [rbp-0x4], 3
	jnz	$_023
$_022:	mov	dword ptr [rdx+0x48], 3
	or	dword ptr [rbp-0xC], 0xC0000080
	mov	dword ptr [rbp-0x1C], 0
	jmp	$_025

$_023:	cmp	byte ptr [rdx+0x72], 5
	jnz	$_024
	cmp	dword ptr [rdx+0x18], 0
	jnz	$_024
	or	dword ptr [rbp-0xC], 0xC0000080
	mov	dword ptr [rbp-0x20], 0
	mov	dword ptr [rbp-0x1C], 0
	jmp	$_025

$_024:	or	dword ptr [rbp-0xC], 0xC0000040
$_025:	cmp	byte ptr [rdx+0x69], 0
	jz	$_026
	and	dword ptr [rbp-0xC], 0x1FFFFFF
	movzx	eax, byte ptr [rdx+0x69]
	and	eax, 0xFE
	shl	eax, 24
	or	dword ptr [rbp-0xC], eax
$_026:	cmp	dword ptr [rbp-0x1C], 0
	jz	$_027
	add	esi, dword ptr [rbp-0x20]
$_027:	mov	rcx, qword ptr [rdx+0x28]
	test	rcx, rcx
	jz	$_034
$_028:	test	rcx, rcx
	jz	$_032
	cmp	qword ptr [rcx+0x30], 0
	jnz	$_030
	cmp	byte ptr [rcx+0x18], 3
	jnz	$_029
	mov	eax, dword ptr [rcx+0x14]
	sub	eax, dword ptr [rdx+0x8]
	add	rax, qword ptr [rdx+0x10]
	movzx	edx, byte ptr [rcx+0x1A]
	add	edx, dword ptr [rcx+0x14]
	sub	dword ptr [rax], edx
	mov	rdx, qword ptr [rdi+0x68]
$_029:	mov	byte ptr [rcx+0x18], 0
	jmp	$_031

$_030:	inc	dword ptr [rdx+0x40]
$_031:	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_028

$_032:	inc	esi
	and	esi, 0xFFFFFFFE
	mov	dword ptr [rbp-0x18], esi
	imul	eax, dword ptr [rdx+0x40], 10
	add	esi, eax
	cmp	dword ptr [rdx+0x40], 65535
	ja	$_033
	mov	eax, dword ptr [rdx+0x40]
	mov	word ptr [rbp-0x10], ax
	jmp	$_034

$_033:
	mov	word ptr [rbp-0x10], -1
	or	byte ptr [rbp-0x9], 0x01
	add	esi, 10
$_034:	cmp	qword ptr [rdx+0x38], 0
	jz	$_035
	cmp	byte ptr [Options+0x2+rip], 4
	jz	$_035
	mov	dword ptr [rbp-0x14], esi
	mov	rcx, qword ptr [rdx+0x38]
	call	$_004
	mov	word ptr [rbp-0xE], ax
	movzx	eax, word ptr [rbp-0xE]
	imul	eax, eax, 6
	add	esi, eax
$_035:	push	rsi
	push	rdi
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 40
	mov	esi, 1
	lea	rdi, [rbp-0x30]
	call	fwrite@PLT
	cmp	eax, 40
	jz	$_036
	call	WriteError@PLT
$_036:	pop	rdi
	pop	rsi
	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_008

$_037:
	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_038:
	test	byte ptr [rcx+0x15], 0x08
	jz	$_039
	mov	eax, 32
	jmp	$_040

$_039:	xor	eax, eax
$_040:	ret

$_041:
	cmp	byte ptr [rcx+0x18], 2
	jnz	$_044
	test	byte ptr [rcx+0x3B], 0x01
	jnz	$_042
	cmp	qword ptr [rcx+0x58], 0
	jz	$_042
	mov	eax, 105
	jmp	$_047

	jmp	$_043

$_042:	mov	eax, 2
	jmp	$_047

$_043:	jmp	$_046

$_044:	test	dword ptr [rcx+0x14], 0x80
	jz	$_045
	mov	eax, 2
	jmp	$_047

	jmp	$_046

$_045:	cmp	byte ptr [rcx+0x19], -127
	jnz	$_046
	test	byte ptr [rcx+0x15], 0x08
	jnz	$_046
	mov	eax, 6
	jmp	$_047

$_046:	mov	eax, 3
$_047:	ret

$_048:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	movzx	ecx, word ptr [rbp+0x10]
	call	GetFName@PLT
	cmp	qword ptr [rbp+0x18], 0
	jz	$_049
	mov	rcx, qword ptr [rbp+0x18]
	mov	qword ptr [rcx], rax
$_049:	mov	rcx, rax
	call	tstrlen@PLT
	cdq
	mov	ecx, 18
	div	ecx
	add	eax, edx
	mov	eax, 0
	setne	al
	leave
	ret

$_050:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	cmp	dword ptr [CRC32_Init+rip], 0
	jnz	$_054
	mov	dword ptr [CRC32_Init+rip], 1
	xor	ecx, ecx
$_051:	cmp	ecx, 256
	jnc	$_054
	xor	edx, edx
	mov	eax, ecx
$_052:	cmp	edx, 8
	jnc	$_053
	mov	ebx, eax
	and	ebx, 0x01
	imul	ebx, ebx, -306674912
	shr	eax, 1
	xor	eax, ebx
	inc	edx
	jmp	$_052

$_053:	lea	rdx, [CRC32Table+rip]
	mov	dword ptr [rdx+rcx*4], eax
	inc	ecx
	jmp	$_051

$_054:
	mov	eax, dword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x20]
	test	rcx, rcx
	jz	$_056
	mov	ebx, dword ptr [rbp+0x28]
	xor	edx, edx
$_055:	test	ebx, ebx
	jz	$_056
	mov	dl, byte ptr [rcx]
	inc	rcx
	xor	dl, al
	shr	eax, 8
	lea	rsi, [CRC32Table+rip]
	xor	eax, dword ptr [rsi+rdx*4]
	dec	ebx
	jmp	$_055

$_056:
	leave
	pop	rbx
	pop	rsi
	ret

$_057:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 64
	cmp	qword ptr [rbp+0x20], 0
	jz	$_058
	mov	r8d, 8
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [rbp-0x18]
	call	tstrncpy@PLT
	jmp	$_059

$_058:	mov	dword ptr [rbp-0x18], 0
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x14], eax
$_059:	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x10], eax
	mov	eax, dword ptr [rbp+0x38]
	mov	word ptr [rbp-0xC], ax
	mov	eax, dword ptr [rbp+0x40]
	mov	word ptr [rbp-0xA], ax
	mov	eax, dword ptr [rbp+0x48]
	mov	byte ptr [rbp-0x8], al
	mov	eax, dword ptr [rbp+0x50]
	mov	byte ptr [rbp-0x7], al
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 18
	mov	esi, 1
	lea	rdi, [rbp-0x18]
	call	fwrite@PLT
	cmp	eax, 18
	jz	$_060
	call	WriteError@PLT
$_060:	leave
	pop	rdi
	pop	rsi
	ret

$_061:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	qword ptr [rbp+0x28], 0
	jz	$_062
	mov	r8d, 18
	mov	rdx, qword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp+0x20]
	call	tstrncpy@PLT
$_062:	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 18
	mov	esi, 1
	mov	rdi, qword ptr [rbp+0x20]
	call	fwrite@PLT
	cmp	eax, 18
	jz	$_063
	call	WriteError@PLT
$_063:	leave
	pop	rdi
	pop	rsi
	ret

$_064:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 288
	mov	rsi, rcx
	lea	rdi, [rbp-0x100]
	xor	eax, eax
	cmp	qword ptr [rsi+0xE0], 0
	jz	$_070
	mov	rdx, rdi
	mov	rcx, qword ptr [rsi+0xE0]
	call	Mangle@PLT
	mov	rcx, rsi
	mov	rsi, qword ptr [rbp+0x28]
	cmp	byte ptr [Options+0x91+rip], 0
	jnz	$_069
	mov	rdx, qword ptr [rcx+0xE0]
	movzx	eax, byte ptr [rdx+0x1A]
	cmp	eax, 1
	jz	$_068
	cmp	eax, 3
	jz	$_068
	cmp	eax, 2
	jz	$_068
	mov	rdx, qword ptr [rdx+0x8]
	cmp	byte ptr [rdx], 95
	jz	$_066
	cmp	dword ptr [rbp+0x30], 0
	jz	$_065
	cmp	byte ptr [rcx+0x1CD], 2
	jz	$_065
	mov	ecx, 8011
	call	asmerr@PLT
$_065:	jmp	$_067

$_066:	inc	rdi
$_067:	jmp	$_069

$_068:	inc	rdi
$_069:	mov	rdx, rdi
	mov	rcx, rsi
	call	tstrcpy@PLT
	mov	rcx, rax
	call	tstrlen@PLT
	add	eax, 8
$_070:	leave
	pop	rdi
	pop	rsi
	ret

$_071:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 392
	mov	dword ptr [rbp-0x4], 0
	mov	word ptr [rbp-0x2A], 0
	mov	dword ptr [rbp-0x130], 0
	cmp	byte ptr [Options+0xA3+rip], 0
	jz	$_073
	mov	ecx, 1
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_072
	mov	ecx, 16
$_072:	mov	dword ptr [rsp+0x30], 0
	mov	dword ptr [rsp+0x28], 3
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 4294967295
	mov	r8d, ecx
	xor	edx, edx
	lea	rcx, [DS0003+rip]
	call	$_057
	inc	dword ptr [rbp-0x4]
$_073:	cmp	byte ptr [Options+0x8B+rip], 0
	jne	$_078
	mov	rbx, qword ptr [rbp+0x30]
	mov	rsi, qword ptr [rbx+0x18]
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	ecx, 18
	cdq
	div	ecx
	test	edx, edx
	jz	$_074
	inc	eax
$_074:	mov	dword ptr [rbp-0x140], eax
	xor	ecx, ecx
	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_075
	mov	ecx, dword ptr [rbx+0x28]
$_075:	mov	eax, dword ptr [rbp-0x140]
	mov	dword ptr [rsp+0x30], eax
	mov	dword ptr [rsp+0x28], 103
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 4294967294
	mov	r8d, ecx
	xor	edx, edx
	lea	rcx, [DS0004+rip]
	call	$_057
	mov	edi, dword ptr [rbp-0x140]
$_076:	test	edi, edi
	jz	$_077
	mov	rdx, rsi
	lea	rcx, [rbp-0x28]
	call	$_061
	dec	edi
	add	rsi, 18
	jmp	$_076

$_077:	mov	eax, dword ptr [rbp-0x140]
	inc	eax
	add	dword ptr [rbp-0x4], eax
$_078:	mov	ebx, 1
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_079:	test	rdi, rdi
	je	$_088
	mov	rdx, qword ptr [rdi+0x68]
	mov	rax, qword ptr [rdx+0x60]
	test	rax, rax
	jnz	$_080
	lea	r8, [rbp-0x12A]
	xor	edx, edx
	mov	rcx, rdi
	call	ConvertSectionName@PLT
$_080:	mov	rsi, rax
	mov	rcx, rax
	call	tstrlen@PLT
	cmp	eax, 8
	jbe	$_081
	mov	r8d, eax
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	dword ptr [rbp-0x130], eax
	mov	esi, 0
$_081:	xor	ecx, ecx
	cmp	byte ptr [Options+0x8D+rip], 0
	jnz	$_082
	inc	ecx
$_082:	mov	dword ptr [rsp+0x30], ecx
	mov	dword ptr [rsp+0x28], 3
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, ebx
	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0x130]
	mov	rcx, rsi
	call	$_057
	inc	dword ptr [rbp-0x4]
	mov	rsi, qword ptr [rdi+0x68]
	cmp	byte ptr [Options+0x8D+rip], 0
	jz	$_083
	cmp	byte ptr [rsi+0x73], 0
	jz	$_087
$_083:	mov	r8d, 18
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	tmemset@PLT
	mov	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rbp-0x28], eax
	mov	eax, dword ptr [rsi+0x40]
	cmp	eax, 65535
	jbe	$_084
	mov	eax, 65535
$_084:	mov	word ptr [rbp-0x24], ax
	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_085
	cmp	byte ptr [Options+0x2+rip], 4
	jz	$_085
	mov	eax, dword ptr [rsi+0x38]
	mov	word ptr [rbp-0x22], ax
$_085:	cmp	byte ptr [rsi+0x73], 0
	jz	$_086
	xor	r8d, r8d
	mov	edx, dword ptr [rdi+0x50]
	mov	rcx, qword ptr [rsi+0x10]
	call	$_050
	mov	dword ptr [rbp-0x20], eax
	mov	eax, dword ptr [rsi+0x58]
	mov	word ptr [rbp-0x1C], ax
	mov	al, byte ptr [rsi+0x73]
	mov	byte ptr [rbp-0x1A], al
$_086:	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	$_061
	inc	dword ptr [rbp-0x4]
$_087:	mov	rdi, qword ptr [rdi+0x70]
	inc	ebx
	jmp	$_079

$_088:
	mov	rdi, qword ptr [SymTables+0x10+rip]
$_089:	test	rdi, rdi
	je	$_096
	test	byte ptr [rdi+0x3B], 0x01
	jnz	$_090
	test	byte ptr [rdi+0x3B], 0x02
	jne	$_095
$_090:	lea	rbx, [rbp-0x12A]
	mov	rdx, rbx
	mov	rcx, rdi
	call	Mangle@PLT
	mov	ecx, eax
	test	byte ptr [rdi+0x3B], 0x01
	jz	$_091
	mov	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rbp-0x134], eax
	jmp	$_092

$_091:	mov	eax, dword ptr [rdi+0x28]
	mov	dword ptr [rbp-0x134], eax
$_092:	cmp	ecx, 8
	jbe	$_093
	mov	r8d, ecx
	mov	rdx, rbx
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	dword ptr [rbp-0x130], eax
	xor	ebx, ebx
$_093:	mov	rcx, rdi
	call	$_041
	mov	esi, eax
	mov	rcx, rdi
	call	$_038
	mov	ecx, eax
	xor	eax, eax
	test	byte ptr [rdi+0x3B], 0x01
	jnz	$_094
	cmp	qword ptr [rdi+0x58], 0
	jz	$_094
	inc	eax
$_094:	mov	dword ptr [rsp+0x30], eax
	mov	dword ptr [rsp+0x28], esi
	mov	dword ptr [rsp+0x20], ecx
	xor	r9d, r9d
	mov	r8d, dword ptr [rbp-0x134]
	mov	edx, dword ptr [rbp-0x130]
	mov	rcx, rbx
	call	$_057
	inc	dword ptr [rbp-0x4]
	test	byte ptr [rdi+0x3B], 0x01
	jnz	$_095
	cmp	qword ptr [rdi+0x58], 0
	jz	$_095
	mov	r8d, 18
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	tmemset@PLT
	mov	rcx, qword ptr [rdi+0x58]
	mov	eax, dword ptr [rcx+0x60]
	mov	dword ptr [rbp-0x28], eax
	mov	dword ptr [rbp-0x24], 2
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	$_061
	inc	dword ptr [rbp-0x4]
$_095:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_089

$_096:
	mov	rdi, qword ptr [ModuleInfo+0x10+rip]
$_097:	test	rdi, rdi
	je	$_110
	mov	rsi, qword ptr [rdi+0x8]
	lea	rdx, [rbp-0x12A]
	mov	rcx, rsi
	call	Mangle@PLT
	mov	ebx, eax
	mov	rcx, qword ptr [rsi+0x58]
	cmp	byte ptr [Options+0x1+rip], 0
	je	$_100
	cmp	byte ptr [Options+0x2+rip], 4
	je	$_100
	test	byte ptr [rsi+0x15], 0x08
	je	$_100
	mov	ax, word ptr [rbp-0x2A]
	cmp	word ptr [rcx+0xE], ax
	jz	$_100
	mov	ax, word ptr [rcx+0xE]
	mov	word ptr [rbp-0x2A], ax
	lea	rdx, [rbp-0x10]
	movzx	ecx, word ptr [rcx+0xE]
	call	$_048
	mov	dword ptr [rbp-0x140], eax
	mov	rdx, qword ptr [rsi+0x58]
	mov	eax, dword ptr [rbp-0x140]
	mov	dword ptr [rsp+0x30], eax
	mov	dword ptr [rsp+0x28], 103
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 4294967294
	mov	r8d, dword ptr [rdx+0x14]
	xor	edx, edx
	lea	rcx, [DS0004+rip]
	call	$_057
	mov	rdx, qword ptr [rbp-0x10]
	mov	eax, dword ptr [rbp-0x140]
$_098:	test	eax, eax
	jz	$_099
	add	rdx, 18
	dec	eax
	jmp	$_098

$_099:	lea	rcx, [rbp-0x28]
	call	$_061
	mov	eax, dword ptr [rbp-0x140]
	inc	eax
	add	dword ptr [rbp-0x4], eax
$_100:	cmp	byte ptr [rsi+0x18], 1
	jnz	$_103
	cmp	qword ptr [rsi+0x30], 0
	jz	$_101
	mov	rcx, qword ptr [rsi+0x30]
	call	GetSegIdx@PLT
	mov	dword ptr [rbp-0x138], eax
	jmp	$_102

$_101:	mov	dword ptr [rbp-0x138], -1
$_102:	jmp	$_104

$_103:	mov	dword ptr [rbp-0x138], 0
$_104:	mov	dword ptr [rbp-0x140], 0
	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_105
	test	byte ptr [rsi+0x15], 0x08
	jz	$_105
	cmp	byte ptr [Options+0x2+rip], 4
	jz	$_105
	inc	dword ptr [rbp-0x140]
$_105:	mov	ecx, ebx
	lea	rbx, [rbp-0x12A]
	cmp	ecx, 8
	jbe	$_106
	mov	r8d, ecx
	mov	rdx, rbx
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	dword ptr [rbp-0x130], eax
	xor	ebx, ebx
$_106:	mov	qword ptr [rbp-0x10], rbx
	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rbp-0x134], eax
	mov	rcx, rsi
	call	$_038
	mov	ebx, eax
	mov	rcx, rsi
	call	$_041
	mov	ecx, eax
	mov	eax, dword ptr [rbp-0x140]
	mov	dword ptr [rsp+0x30], eax
	mov	dword ptr [rsp+0x28], ecx
	mov	dword ptr [rsp+0x20], ebx
	mov	r9d, dword ptr [rbp-0x138]
	mov	r8d, dword ptr [rbp-0x134]
	mov	edx, dword ptr [rbp-0x130]
	mov	rcx, qword ptr [rbp-0x10]
	call	$_057
	inc	dword ptr [rbp-0x4]
	cmp	byte ptr [Options+0x1+rip], 0
	je	$_109
	test	byte ptr [rsi+0x15], 0x08
	je	$_109
	cmp	byte ptr [Options+0x2+rip], 4
	je	$_109
	mov	eax, dword ptr [rbp-0x4]
	inc	eax
	mov	dword ptr [rbp-0x28], eax
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rbp-0x24], eax
	mov	rdx, qword ptr [rsi+0x58]
	mov	eax, dword ptr [rdx+0x8]
	mov	dword ptr [rbp-0x20], eax
	mov	eax, dword ptr [rdx+0x10]
	mov	dword ptr [rbp-0x1C], eax
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	$_061
	mov	dword ptr [rbp-0x13C], 0
	mov	ebx, 101
	mov	dword ptr [rsp+0x30], 1
	mov	dword ptr [rsp+0x28], ebx
	mov	eax, dword ptr [rbp-0x13C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x138]
	mov	r8d, dword ptr [rbp-0x134]
	xor	edx, edx
	lea	rcx, [DS0005+rip]
	call	$_057
	mov	dword ptr [rbp-0x28], 0
	mov	rdx, qword ptr [rsi+0x58]
	mov	eax, dword ptr [rdx]
	mov	word ptr [rbp-0x24], ax
	cmp	dword ptr [rdx+0x10], 0
	jz	$_107
	mov	eax, dword ptr [rdx+0x10]
	add	eax, 2
	mov	dword ptr [rbp-0x1C], eax
	jmp	$_108

$_107:	mov	dword ptr [rbp-0x1C], 0
$_108:	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	$_061
	mov	rdx, qword ptr [rsi+0x58]
	movzx	eax, word ptr [rdx+0xC]
	mov	dword ptr [rbp-0x134], eax
	mov	dword ptr [rsp+0x30], 0
	mov	dword ptr [rsp+0x28], ebx
	mov	eax, dword ptr [rbp-0x13C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x138]
	mov	r8d, dword ptr [rbp-0x134]
	xor	edx, edx
	lea	rcx, [DS0006+rip]
	call	$_057
	mov	eax, dword ptr [rsi+0x28]
	add	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rbp-0x134], eax
	mov	dword ptr [rsp+0x30], 1
	mov	dword ptr [rsp+0x28], ebx
	mov	eax, dword ptr [rbp-0x13C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x138]
	mov	r8d, dword ptr [rbp-0x134]
	xor	edx, edx
	lea	rcx, [DS0007+rip]
	call	$_057
	mov	dword ptr [rbp-0x28], 0
	mov	rdx, qword ptr [rsi+0x58]
	mov	eax, dword ptr [rdx+0x4]
	mov	word ptr [rbp-0x24], ax
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	$_061
	add	dword ptr [rbp-0x4], 6
$_109:	mov	rdi, qword ptr [rdi]
	jmp	$_097

$_110:
	mov	rdi, qword ptr [SymTables+0x50+rip]
$_111:	test	rdi, rdi
	je	$_114
	lea	rdx, [rbp-0x12A]
	mov	rcx, rdi
	call	Mangle@PLT
	mov	edx, eax
	lea	rcx, [rbp-0x12A]
	cmp	edx, 8
	jbe	$_112
	mov	r8d, edx
	mov	rdx, rcx
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	dword ptr [rbp-0x130], eax
	xor	ecx, ecx
$_112:	mov	dword ptr [rsp+0x30], 1
	mov	dword ptr [rsp+0x28], 105
	mov	dword ptr [rsp+0x20], 0
	xor	r9d, r9d
	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0x130]
	call	$_057
	inc	dword ptr [rbp-0x4]
	mov	r8d, 18
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	tmemset@PLT
	mov	rdx, qword ptr [rdi+0x28]
	test	rdx, rdx
	jz	$_113
	mov	eax, dword ptr [rdx+0x60]
	mov	dword ptr [rbp-0x28], eax
$_113:	mov	dword ptr [rbp-0x24], 3
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	$_061
	inc	dword ptr [rbp-0x4]
	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_111

$_114:
	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

coff_flushfunc:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	mov	rsi, qword ptr [rdi+0x68]
	mov	rbx, rdx
	sub	rbx, qword ptr [rsi+0x10]
	mov	eax, r8d
	add	eax, ebx
	cmp	eax, 4096
	jbe	$_119
	test	ebx, ebx
	jz	$_118
	lea	ecx, [rbx+0x10]
	call	LclAlloc@PLT
	mov	qword ptr [rax], 0
	mov	dword ptr [rax+0x8], ebx
	mov	rdx, rsi
	mov	rcx, rbx
	lea	rdi, [rax+0x10]
	mov	rsi, qword ptr [rsi+0x10]
	rep movsb
	mov	rsi, rdx
	mov	rdx, qword ptr [rbp+0x40]
	lea	rcx, [rdx+0x48]
	mov	rdi, qword ptr [rcx]
	cmp	rdi, qword ptr [rbp+0x28]
	jz	$_115
	sub	rcx, 24
$_115:	cmp	qword ptr [rcx+0x8], 0
	jnz	$_116
	mov	qword ptr [rcx+0x8], rax
	mov	qword ptr [rcx+0x10], rax
	jmp	$_117

$_116:	mov	rdx, qword ptr [rcx+0x10]
	mov	qword ptr [rdx], rax
	mov	qword ptr [rcx+0x10], rax
$_117:	mov	eax, dword ptr [rsi+0x8]
	add	eax, ebx
	mov	dword ptr [rsi+0xC], eax
	mov	dword ptr [rsi+0x8], eax
$_118:	mov	rax, qword ptr [rsi+0x10]
	jmp	$_120

$_119:	mov	rax, qword ptr [rbp+0x30]
$_120:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_121:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	xor	esi, esi
	mov	rbx, rdx
	mov	dword ptr [rbp-0x14], esi
	mov	qword ptr [rbx+0x10], rsi
	mov	dword ptr [rbx+0x28], esi
	cmp	byte ptr [Options+0xA3+rip], 0
	jz	$_122
	inc	esi
$_122:	cmp	byte ptr [Options+0x8B+rip], 0
	jnz	$_124
	mov	rcx, qword ptr [rbx+0x18]
	call	tstrlen@PLT
	cdq
	mov	ecx, 18
	div	ecx
	inc	eax
	test	edx, edx
	jz	$_123
	inc	eax
$_123:	add	esi, eax
$_124:	mov	dword ptr [rbx+0x2C], esi
	mov	rcx, qword ptr [rbp+0x28]
	add	esi, dword ptr [rcx+0x8]
	cmp	byte ptr [Options+0x8D+rip], 0
	jnz	$_125
	add	esi, dword ptr [rcx+0x8]
$_125:	mov	rdi, qword ptr [SymTables+0x10+rip]
$_126:	test	rdi, rdi
	jz	$_129
	test	byte ptr [rdi+0x3B], 0x01
	jnz	$_127
	test	byte ptr [rdi+0x3B], 0x02
	jnz	$_128
$_127:	mov	dword ptr [rdi+0x60], esi
	inc	esi
	test	byte ptr [rdi+0x3B], 0x01
	jnz	$_128
	cmp	qword ptr [rdi+0x58], 0
	jz	$_128
	inc	esi
$_128:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_126

$_129:
	mov	dword ptr [rbp-0x4], esi
	cmp	byte ptr [Options+0x8C+rip], 0
	jnz	$_132
	mov	rdi, qword ptr [SymTables+0x40+rip]
$_130:	test	rdi, rdi
	jz	$_132
	cmp	byte ptr [rdi+0x18], 1
	jnz	$_131
	test	dword ptr [rdi+0x14], 0x80
	jnz	$_131
	test	byte ptr [rdi+0x15], 0x40
	jnz	$_131
	or	byte ptr [rdi+0x15], 0x40
	mov	rcx, rdi
	call	AddPublicData@PLT
$_131:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_130

$_132:
	mov	rsi, qword ptr [rbp+0x28]
	mov	rdi, qword ptr [rsi+0x10]
$_133:	test	rdi, rdi
	je	$_139
	mov	rsi, qword ptr [rdi+0x8]
	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_137
	test	byte ptr [rsi+0x15], 0x08
	jz	$_137
	cmp	byte ptr [Options+0x2+rip], 4
	jz	$_137
	mov	rdx, qword ptr [rsi+0x58]
	mov	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbp-0x14]
	cmp	word ptr [rdx+0xE], ax
	jz	$_136
	cmp	dword ptr [rbx+0x28], 0
	jnz	$_134
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rbx+0x28], eax
	jmp	$_135

$_134:	mov	rcx, qword ptr [rbp-0x10]
	mov	rcx, qword ptr [rcx+0x58]
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rcx+0x14], eax
$_135:	mov	qword ptr [rbp-0x10], rsi
	mov	rcx, qword ptr [rsi+0x58]
	xor	edx, edx
	movzx	ecx, word ptr [rcx+0xE]
	call	$_048
	inc	rax
	add	dword ptr [rbp-0x4], eax
	mov	rdx, qword ptr [rsi+0x58]
	movzx	eax, word ptr [rdx+0xE]
	mov	dword ptr [rbp-0x14], eax
$_136:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsi+0x60], eax
	add	dword ptr [rbp-0x4], 7
	jmp	$_138

$_137:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsi+0x60], eax
	inc	dword ptr [rbp-0x4]
$_138:	mov	rdi, qword ptr [rdi]
	jmp	$_133

$_139:
	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_140:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	eax, dword ptr [rbp+0x20]
	mov	dword ptr [rbp-0x10], eax
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0xC], eax
	mov	ax, word ptr [rbp+0x30]
	mov	word ptr [rbp-0x8], ax
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 10
	mov	esi, 1
	lea	rdi, [rbp-0x10]
	call	fwrite@PLT
	cmp	eax, 10
	jz	$_141
	call	WriteError@PLT
$_141:	leave
	pop	rdi
	pop	rsi
	ret

$_142:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	eax, dword ptr [rdx]
	mov	dword ptr [rbp-0x4], eax
	mov	rdx, r8
	mov	esi, dword ptr [rdx]
	mov	rdi, qword ptr [rcx+0x68]
	cmp	dword ptr [rdi+0x40], 65535
	jbe	$_143
	mov	ecx, dword ptr [rdi+0x40]
	inc	ecx
	xor	r8d, r8d
	xor	edx, edx
	call	$_140
	add	dword ptr [rbp-0x4], 10
$_143:	mov	dword ptr [rdi+0x40], 0
	mov	rbx, qword ptr [rdi+0x28]
$_144:	test	rbx, rbx
	je	$_169
	mov	al, byte ptr [rbx+0x18]
	xor	ecx, ecx
	cmp	byte ptr [rdi+0x68], 2
	jnz	$_154
	jmp	$_152

$_145:	jmp	$_168

$_146:	movzx	ecx, byte ptr [rbx+0x1A]
	sub	ecx, 4
	add	ecx, 4
	jmp	$_153

$_147:	mov	ecx, 2
	jmp	$_153

$_148:	mov	ecx, 3
	jmp	$_153

$_149:	mov	ecx, 11
	jmp	$_153

$_150:	mov	ecx, 1
	jmp	$_153

$_151:	mov	ecx, 10
	jmp	$_153

$_152:	cmp	al, 0
	jz	$_145
	cmp	al, 3
	jz	$_146
	cmp	al, 6
	jz	$_147
	cmp	al, 12
	jz	$_148
	cmp	al, 13
	jz	$_149
	cmp	al, 7
	jz	$_150
	cmp	al, 8
	jz	$_151
$_153:	jmp	$_164

$_154:	jmp	$_163

$_155:	jmp	$_168

$_156:	mov	ecx, 2
	jmp	$_164

$_157:	mov	ecx, 1
	jmp	$_164

$_158:	mov	ecx, 20
	jmp	$_164

$_159:	mov	ecx, 6
	jmp	$_164

$_160:	mov	ecx, 7
	jmp	$_164

$_161:	mov	ecx, 11
	jmp	$_164

$_162:	mov	ecx, 10
	jmp	$_164

$_163:	cmp	al, 0
	jz	$_155
	cmp	al, 2
	jz	$_156
	cmp	al, 5
	jz	$_157
	cmp	al, 3
	jz	$_158
	cmp	al, 6
	jz	$_159
	cmp	al, 12
	jz	$_160
	cmp	al, 13
	jz	$_161
	cmp	al, 8
	jz	$_162
$_164:	test	ecx, ecx
	jnz	$_165
	mov	rcx, qword ptr [rbp+0x28]
	mov	r9d, dword ptr [rbx+0x14]
	mov	r8, qword ptr [rcx+0x8]
	movzx	edx, byte ptr [rbx+0x18]
	mov	ecx, 3014
	call	asmerr@PLT
	jmp	$_168

$_165:	mov	word ptr [rbp-0x6], cx
	mov	rcx, qword ptr [rbx+0x30]
	test	byte ptr [rcx+0x14], 0x40
	jz	$_166
	mov	rax, qword ptr [rbx+0x20]
	mov	qword ptr [rbx+0x30], rax
	mov	rcx, rax
	jmp	$_167

$_166:	cmp	byte ptr [rcx+0x18], 1
	jnz	$_167
	test	dword ptr [rcx+0x14], 0x80
	jnz	$_167
	test	byte ptr [rcx+0x15], 0x40
	jnz	$_167
	or	byte ptr [rcx+0x15], 0x40
	call	AddPublicData@PLT
	mov	rcx, qword ptr [rbx+0x30]
	mov	dword ptr [rcx+0x60], esi
	inc	esi
	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_167
	test	byte ptr [rcx+0x15], 0x08
	jz	$_167
	cmp	byte ptr [Options+0x2+rip], 4
	jz	$_167
	add	esi, 6
$_167:	movzx	r8d, word ptr [rbp-0x6]
	mov	edx, dword ptr [rcx+0x60]
	mov	ecx, dword ptr [rbx+0x14]
	call	$_140
	add	dword ptr [rbp-0x4], 10
	inc	dword ptr [rdi+0x40]
$_168:	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_144

$_169:
	mov	rdx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rdx], eax
	mov	rdx, qword ptr [rbp+0x38]
	mov	dword ptr [rdx], esi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_170:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 104
	mov	dword ptr [rbp-0xC], 0
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_121
	mov	dword ptr [rbp-0x14], eax
	mov	rbx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x28]
	cmp	qword ptr [rcx+0x30], 0
	jz	$_172
	mov	rax, qword ptr [rbx+0x8]
	mov	rax, qword ptr [rax+0x68]
	mov	rdx, qword ptr [rcx+0x30]
	mov	rcx, qword ptr [rax+0x10]
$_171:	test	rdx, rdx
	jz	$_172
	mov	rax, qword ptr [rdx+0x8]
	mov	eax, dword ptr [rax+0x60]
	mov	dword ptr [rcx], eax
	mov	rdx, qword ptr [rdx]
	add	rcx, 4
	jmp	$_171

$_172:
	xor	ecx, ecx
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_173:	test	rdi, rdi
	jz	$_175
	mov	eax, dword ptr [rbx+0x2C]
	add	eax, ecx
	mov	dword ptr [rdi+0x60], eax
	cmp	byte ptr [Options+0x8D+rip], 0
	jnz	$_174
	add	dword ptr [rdi+0x60], ecx
$_174:	inc	ecx
	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_173

$_175:
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_176:	test	rdi, rdi
	je	$_191
	mov	ebx, dword ptr [rdi+0x50]
	mov	rsi, qword ptr [rdi+0x68]
	cmp	byte ptr [rsi+0x72], 5
	jnz	$_177
	cmp	dword ptr [rsi+0x18], 0
	je	$_190
$_177:	cmp	dword ptr [rsi+0x48], 3
	je	$_190
	mov	qword ptr [rbp-0x20], rsi
	mov	qword ptr [rbp-0x28], rdi
	test	ebx, ebx
	je	$_182
	add	dword ptr [rbp-0xC], ebx
	test	byte ptr [rbp-0xC], 0x01
	jz	$_178
	cmp	qword ptr [rsi+0x28], 0
	jz	$_178
	inc	dword ptr [rbp-0xC]
	inc	ebx
$_178:	cmp	qword ptr [rsi+0x10], 0
	jnz	$_179
	mov	edx, 1
	mov	esi, ebx
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	jmp	$_181

$_179:	cmp	dword ptr [rsi+0x8], 0
	jz	$_180
	mov	edx, 1
	mov	esi, dword ptr [rsi+0x8]
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rsi, qword ptr [rbp-0x20]
	sub	ebx, dword ptr [rsi+0x8]
$_180:	mov	rax, qword ptr [rsi+0x10]
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, ebx
	mov	esi, 1
	mov	rdi, rax
	call	fwrite@PLT
	cmp	rax, rbx
	jz	$_181
	call	WriteError@PLT
$_181:	mov	rsi, qword ptr [rbp-0x20]
	mov	rdi, qword ptr [rbp-0x28]
	lea	r8, [rbp-0x14]
	lea	rdx, [rbp-0xC]
	mov	rcx, rdi
	call	$_142
$_182:	mov	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [Options+0x1+rip], 0
	je	$_190
	cmp	qword ptr [rsi+0x38], 0
	je	$_190
	cmp	byte ptr [Options+0x2+rip], 4
	je	$_190
	mov	dword ptr [rbp-0x44], 0
	mov	rax, qword ptr [rsi+0x38]
	mov	qword ptr [rbp-0x40], 0
	mov	rsi, qword ptr [rax]
$_183:	test	rsi, rsi
	je	$_189
	cmp	dword ptr [rsi+0x8], 0
	jnz	$_185
	mov	rax, qword ptr [rsi+0x10]
	mov	qword ptr [rbp-0x40], rax
	cmp	qword ptr [rbx+0x10], 0
	jz	$_184
	mov	rcx, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rcx+0x58]
	mov	edx, dword ptr [rax+0x60]
	mov	dword ptr [rcx+0x10], edx
$_184:	mov	qword ptr [rbx+0x10], rax
	mov	rcx, qword ptr [rax+0x58]
	mov	dword ptr [rcx+0x10], 0
	mov	word ptr [rbp-0x2E], 0
	mov	eax, dword ptr [rax+0x60]
	mov	dword ptr [rbp-0x32], eax
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rcx], eax
	mov	eax, dword ptr [rbx+0x20]
	add	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rcx+0x8], eax
	jmp	$_187

$_185:	mov	rcx, qword ptr [rbp-0x40]
	mov	rcx, qword ptr [rcx+0x58]
	mov	eax, dword ptr [rsi+0x8]
	sub	eax, dword ptr [rcx]
	mov	word ptr [rbp-0x2E], ax
	cmp	word ptr [rbp-0x2E], 0
	jnz	$_186
	mov	word ptr [rbp-0x2E], 32767
$_186:	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rbp-0x32], eax
$_187:	mov	rcx, qword ptr [rbp-0x40]
	mov	rcx, qword ptr [rcx+0x58]
	inc	word ptr [rcx+0xC]
	mov	eax, dword ptr [rsi+0x8]
	mov	dword ptr [rcx+0x4], eax
	mov	qword ptr [rbp-0x20], rsi
	mov	qword ptr [rbp-0x28], rdi
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 6
	mov	esi, 1
	lea	rdi, [rbp-0x32]
	call	fwrite@PLT
	cmp	eax, 6
	jz	$_188
	call	WriteError@PLT
$_188:	mov	rsi, qword ptr [rbp-0x20]
	mov	rdi, qword ptr [rbp-0x28]
	add	dword ptr [rbp-0xC], 6
	inc	dword ptr [rbp-0x44]
	mov	rsi, qword ptr [rsi]
	jmp	$_183

$_189:	mov	rdx, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rbp-0x44]
	mov	dword ptr [rdx+0x38], eax
$_190:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_176

$_191:
	mov	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rbx+0x24], eax
	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_192:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 328
	mov	qword ptr [rbp-0x10], 0
	mov	rdi, qword ptr [SymTables+0x40+rip]
$_193:	test	rdi, rdi
	jz	$_194
	mov	rcx, qword ptr [rdi+0x68]
	test	byte ptr [rcx+0x40], 0x04
	jnz	$_194
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_193

$_194:
	mov	qword ptr [rbp-0x8], rdi
	cmp	byte ptr [Options+0x93+rip], 0
	jz	$_199
	cmp	qword ptr [Options+0x30+rip], 0
	jnz	$_199
	mov	rdi, qword ptr [SymTables+0x10+rip]
$_195:	test	rdi, rdi
	jz	$_198
	test	byte ptr [rdi+0x15], 0x08
	jz	$_197
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_196
	test	byte ptr [rdi+0x14], 0x08
	jz	$_197
$_196:	mov	rdx, qword ptr [rdi+0x50]
	test	rdx, rdx
	jz	$_197
	cmp	byte ptr [rdx+0xC], 0
	jnz	$_198
$_197:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_195

$_198:	mov	qword ptr [rbp-0x10], rdi
$_199:	mov	rsi, qword ptr [rbp+0x28]
	cmp	qword ptr [rsi+0xE0], 0
	jnz	$_200
	cmp	qword ptr [rsi+0x40], 0
	jnz	$_200
	cmp	qword ptr [rbp-0x10], 0
	jnz	$_200
	cmp	qword ptr [rbp-0x8], 0
	jnz	$_200
	cmp	qword ptr [rsi+0x50], 0
	je	$_227
$_200:	mov	rbx, qword ptr [rbp+0x30]
	mov	dword ptr [rsp+0x20], 0
	movzx	r9d, byte ptr [rsi+0x1CC]
	mov	r8d, 255
	lea	rdx, [DS0008+0x8+rip]
	lea	rcx, [DS0008+rip]
	call	CreateIntSegment@PLT
	mov	qword ptr [rbx], rax
	test	eax, eax
	je	$_227
	xor	ebx, ebx
	mov	rdi, qword ptr [rax+0x68]
	mov	byte ptr [rdi+0x6C], 1
	mov	rdi, qword ptr [rbp-0x8]
$_201:	test	rdi, rdi
	jz	$_203
	mov	rcx, qword ptr [rdi+0x68]
	test	byte ptr [rcx+0x40], 0x04
	jz	$_202
	lea	rdx, [rbp-0x110]
	mov	rcx, rdi
	call	Mangle@PLT
	lea	rbx, [rbx+rax+0x9]
	cmp	byte ptr [Options+0x90+rip], 1
	jnz	$_202
	add	ebx, dword ptr [rdi+0x10]
	inc	ebx
$_202:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_201

$_203:	mov	rdi, qword ptr [rsi+0x40]
$_204:	test	rdi, rdi
	jz	$_206
	lea	rcx, [rdi+0x8]
	call	tstrlen@PLT
	lea	rbx, [rbx+rax+0xD]
	cmp	byte ptr [rdi+0x8], 34
	jz	$_205
	mov	edx, 32
	lea	rcx, [rdi+0x8]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_205
	add	rbx, 2
$_205:	mov	rdi, qword ptr [rdi]
	jmp	$_204

$_206:	mov	r8d, 1
	lea	rdx, [rbp-0x110]
	mov	rcx, rsi
	call	$_064
	add	ebx, eax
	mov	rdi, qword ptr [rbp-0x10]
$_207:	test	rdi, rdi
	jz	$_210
	test	byte ptr [rdi+0x15], 0x08
	jz	$_209
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_208
	test	byte ptr [rdi+0x14], 0x08
	jz	$_209
$_208:	cmp	qword ptr [rdi+0x50], 0
	jz	$_209
	mov	rdx, qword ptr [rdi+0x50]
	cmp	byte ptr [rdx+0xC], 0
	jz	$_209
	lea	rcx, [rdx+0xC]
	call	tstrlen@PLT
	lea	rbx, [rbx+rax+0xA]
	lea	rdx, [rbp-0x110]
	mov	rcx, rdi
	call	Mangle@PLT
	add	ebx, eax
	add	ebx, dword ptr [rdi+0x10]
	inc	ebx
$_209:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_207

$_210:	mov	rdi, qword ptr [rsi+0x50]
$_211:	test	rdi, rdi
	jz	$_212
	lea	rcx, [rdi+0x8]
	call	tstrlen@PLT
	lea	rbx, [rbx+rax+0x1]
	mov	rdi, qword ptr [rdi]
	jmp	$_211

$_212:	mov	ecx, ebx
	mov	rbx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbx]
	mov	dword ptr [rdx+0x50], ecx
	mov	rdi, qword ptr [rdx+0x68]
	inc	ecx
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x10], rax
	mov	rbx, rax
	mov	rdi, qword ptr [rbp-0x8]
$_213:	test	rdi, rdi
	jz	$_216
	mov	rcx, qword ptr [rdi+0x68]
	test	byte ptr [rcx+0x40], 0x04
	jz	$_215
	lea	rdx, [rbp-0x110]
	mov	rcx, rdi
	call	Mangle@PLT
	cmp	byte ptr [Options+0x90+rip], 0
	jnz	$_214
	lea	r8, [rbp-0x110]
	lea	rdx, [DS0009+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	add	rbx, rax
	jmp	$_215

$_214:	lea	r9, [rbp-0x110]
	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS000A+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	add	rbx, rax
$_215:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_213

$_216:	mov	rdi, qword ptr [rsi+0x40]
$_217:	test	rdi, rdi
	jz	$_220
	mov	edx, 32
	lea	rcx, [rdi+0x8]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_218
	cmp	byte ptr [rdi+0x8], 34
	jz	$_218
	lea	r8, [rdi+0x8]
	lea	rdx, [DS000B+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	add	rbx, rax
	jmp	$_219

$_218:	lea	r8, [rdi+0x8]
	lea	rdx, [DS000C+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	add	rbx, rax
$_219:	mov	rdi, qword ptr [rdi]
	jmp	$_217

$_220:	cmp	qword ptr [rsi+0xE0], 0
	jz	$_221
	xor	r8d, r8d
	lea	rdx, [rbp-0x110]
	mov	rcx, rsi
	call	$_064
	lea	r8, [rbp-0x110]
	lea	rdx, [DS000D+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	add	rbx, rax
$_221:	mov	rdi, qword ptr [rbp-0x10]
$_222:	test	rdi, rdi
	je	$_225
	test	byte ptr [rdi+0x15], 0x08
	je	$_224
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_223
	test	byte ptr [rdi+0x14], 0x08
	jz	$_224
$_223:	cmp	qword ptr [rdi+0x50], 0
	jz	$_224
	mov	rdx, qword ptr [rdi+0x50]
	cmp	byte ptr [rdx+0xC], 0
	jz	$_224
	lea	rdx, [DS000E+rip]
	mov	rcx, rbx
	call	tstrcpy@PLT
	add	rbx, 8
	mov	rdx, rbx
	mov	rcx, rdi
	call	Mangle@PLT
	add	rbx, rax
	mov	byte ptr [rbx], 61
	inc	rbx
	mov	rcx, qword ptr [rdi+0x50]
	lea	rdx, [rcx+0xC]
	mov	rcx, rbx
	call	tstrcpy@PLT
	mov	rcx, rbx
	call	tstrlen@PLT
	add	rbx, rax
	mov	byte ptr [rbx], 46
	inc	rbx
	mov	r8d, dword ptr [rdi+0x10]
	mov	rdx, qword ptr [rdi+0x8]
	mov	rcx, rbx
	call	tmemcpy@PLT
	mov	edx, dword ptr [rdi+0x10]
	add	rbx, rdx
	mov	byte ptr [rbx], 32
	inc	rbx
$_224:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_222

$_225:	mov	rdi, qword ptr [rsi+0x50]
$_226:	test	rdi, rdi
	jz	$_227
	lea	r8, [rdi+0x8]
	lea	rdx, [DS000D+0x7+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	add	rbx, rax
	mov	rdi, qword ptr [rdi]
	jmp	$_226

$_227:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

coff_write_module:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 216
	mov	r8d, 120
	xor	edx, edx
	lea	rcx, [rbp-0x78]
	call	tmemset@PLT
	mov	dword ptr [rbp-0x8], 4
	mov	rax, qword ptr [ModuleInfo+0x90+rip]
	mov	qword ptr [rbp-0x60], rax
	cmp	byte ptr [Options+0x2+rip], 0
	je	$_234
	xor	ebx, ebx
$_228:	cmp	ebx, 2
	jnc	$_229
	imul	edi, ebx, 24
	lea	rcx, [SymDebName+rip]
	mov	dword ptr [rsp+0x20], 1
	mov	r9d, 1
	xor	r8d, r8d
	lea	rdx, [DS000E+0x8+rip]
	mov	rcx, qword ptr [rcx+rbx*8]
	call	CreateIntSegment@PLT
	mov	qword ptr [rbp+rdi-0x48], rax
	test	eax, eax
	jz	$_229
	mov	rcx, qword ptr [rax+0x68]
	mov	byte ptr [rcx+0x69], 66
	imul	eax, ebx, 4096
	add	rax, qword ptr [ModuleInfo+0x178+rip]
	mov	qword ptr [rcx+0x10], rax
	lea	rax, [coff_flushfunc+rip]
	mov	qword ptr [rcx+0x20], rax
	mov	qword ptr [rbp+rdi-0x40], 0
	inc	ebx
	jmp	$_228

$_229:	cmp	ebx, 2
	jnz	$_234
	lea	r8, [rbp-0x78]
	mov	rdx, qword ptr [rbp-0x30]
	mov	rcx, qword ptr [rbp-0x48]
	call	cv_write_debug_tables@PLT
	xor	ebx, ebx
$_230:	cmp	ebx, 2
	jnc	$_234
	imul	edi, ebx, 24
	mov	rcx, qword ptr [rbp+rdi-0x48]
	mov	rsi, qword ptr [rcx+0x68]
	cmp	dword ptr [rcx+0x50], 0
	jz	$_233
	cmp	dword ptr [rcx+0x50], 4096
	jle	$_231
	mov	ecx, dword ptr [rcx+0x50]
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x10], rax
$_231:	mov	rdx, qword ptr [rsi+0x10]
	mov	rsi, qword ptr [rbp+rdi-0x40]
	mov	rdi, rdx
$_232:	test	rsi, rsi
	jz	$_233
	mov	ecx, dword ptr [rsi+0x8]
	lea	rdx, [rsi+0x10]
	xchg	rdx, rsi
	rep movsb
	mov	rsi, rdx
	mov	rsi, qword ptr [rsi]
	jmp	$_232

$_233:	inc	ebx
	jmp	$_230

$_234:
	mov	rsi, qword ptr [rbp+0x28]
	cmp	qword ptr [rsi+0x30], 0
	jz	$_237
	mov	dword ptr [rsp+0x20], 0
	movzx	r9d, byte ptr [rsi+0x1CC]
	mov	r8d, 255
	lea	rdx, [DS000F+0x7+rip]
	lea	rcx, [DS000F+rip]
	call	CreateIntSegment@PLT
	mov	qword ptr [rbp-0x70], rax
	test	rax, rax
	jz	$_237
	mov	rdi, qword ptr [rax+0x68]
	mov	byte ptr [rdi+0x6C], 1
	mov	rdx, qword ptr [rsi+0x30]
	xor	ecx, ecx
$_235:	test	rdx, rdx
	jz	$_236
	mov	rdx, qword ptr [rdx]
	inc	ecx
	jmp	$_235

$_236:	shl	ecx, 2
	mov	rdx, qword ptr [rbp-0x70]
	mov	dword ptr [rdx+0x50], ecx
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x10], rax
$_237:	lea	rdx, [rbp-0x78]
	mov	rcx, rsi
	call	$_192
	cmp	byte ptr [rsi+0x1CD], 2
	jnz	$_238
	mov	word ptr [rbp-0x90], -31132
	jmp	$_239

$_238:
	mov	word ptr [rbp-0x90], 332
$_239:	mov	eax, dword ptr [rsi+0x8]
	mov	word ptr [rbp-0x8E], ax
	mov	qword ptr [rbp-0x98], rsi
	mov	qword ptr [rbp-0xA0], rdi
	lea	rdi, [rbp-0x8C]
	call	time@PLT
	mov	word ptr [rbp-0x80], 0
	mov	word ptr [rbp-0x7E], 0
	xor	edx, edx
	mov	esi, 20
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rsi, qword ptr [rbp-0x98]
	mov	rdi, qword ptr [rbp-0xA0]
	lea	rdx, [rbp-0x78]
	mov	rcx, rsi
	call	$_007
	lea	rdx, [rbp-0x78]
	mov	rcx, rsi
	call	$_170
	lea	rdx, [rbp-0x78]
	mov	rcx, rsi
	call	$_071
	mov	dword ptr [rbp-0x84], eax
	xor	eax, eax
	cmp	dword ptr [rbp-0x84], 0
	jz	$_240
	mov	eax, dword ptr [rbp-0x58]
	add	eax, dword ptr [rbp-0x54]
$_240:	mov	dword ptr [rbp-0x88], eax
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 4
	mov	esi, 1
	lea	rdi, [rbp-0x8]
	call	fwrite@PLT
	cmp	eax, 4
	jz	$_241
	call	WriteError@PLT
$_241:	mov	rbx, qword ptr [rbp-0x18]
$_242:	test	rbx, rbx
	jz	$_244
	lea	rcx, [rbx+0x8]
	call	tstrlen@PLT
	inc	rax
	mov	dword ptr [rbp-0xA4], eax
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, dword ptr [rbp-0xA4]
	mov	esi, 1
	lea	rdi, [rbx+0x8]
	call	fwrite@PLT
	cmp	eax, dword ptr [rbp-0xA4]
	jz	$_243
	call	WriteError@PLT
$_243:	mov	rbx, qword ptr [rbx]
	jmp	$_242

$_244:
	xor	edx, edx
	xor	esi, esi
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, 20
	mov	esi, 1
	lea	rdi, [rbp-0x90]
	call	fwrite@PLT
	cmp	eax, 20
	jz	$_245
	call	WriteError@PLT
$_245:	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

coff_init:
	lea	rax, [coff_write_module+rip]
	mov	qword ptr [rcx+0x158], rax
	ret


.SECTION .data
	.ALIGN	16

CRC32_Init:
	.int   0x00000000

SymDebName:
	.quad  DS0000
	.quad  DS0001

DS0002:
	.byte  0x2F, 0x25, 0x75, 0x00

DS0003:
	.byte  0x40, 0x66, 0x65, 0x61, 0x74, 0x2E, 0x30, 0x30
	.byte  0x00

DS0004:
	.byte  0x2E, 0x66, 0x69, 0x6C, 0x65, 0x00

DS0005:
	.byte  0x2E, 0x62, 0x66, 0x00

DS0006:
	.byte  0x2E, 0x6C, 0x66, 0x00

DS0007:
	.byte  0x2E, 0x65, 0x66, 0x00

DS0008:
	.byte  0x2E, 0x64, 0x72, 0x65, 0x63, 0x74, 0x76, 0x65
	.byte  0x00

DS0009:
	.byte  0x2D, 0x65, 0x78, 0x70, 0x6F, 0x72, 0x74, 0x3A
	.byte  0x25, 0x73, 0x20, 0x00

DS000A:
	.byte  0x2D, 0x65, 0x78, 0x70, 0x6F, 0x72, 0x74, 0x3A
	.byte  0x25, 0x73, 0x3D, 0x25, 0x73, 0x20, 0x00

DS000B:
	.byte  0x2D, 0x64, 0x65, 0x66, 0x61, 0x75, 0x6C, 0x74
	.byte  0x6C, 0x69, 0x62, 0x3A, 0x22, 0x25, 0x73, 0x22
	.byte  0x20, 0x00

DS000C:
	.byte  0x2D, 0x64, 0x65, 0x66, 0x61, 0x75, 0x6C, 0x74
	.byte  0x6C, 0x69, 0x62, 0x3A, 0x25, 0x73, 0x20, 0x00

DS000D:
	.byte  0x2D, 0x65, 0x6E, 0x74, 0x72, 0x79, 0x3A, 0x25
	.byte  0x73, 0x20, 0x00

DS000E:
	.byte  0x2D, 0x69, 0x6D, 0x70, 0x6F, 0x72, 0x74, 0x3A
	.byte  0x00

DS000F:
	.byte  0x2E, 0x73, 0x78, 0x64, 0x61, 0x74, 0x61, 0x00


.SECTION .bss
	.ALIGN	16

CRC32Table:
	.zero	1024 * 1


.SECTION .rodata
	.ALIGN	16

DS0000:
	.byte  0x2E, 0x64, 0x65, 0x62, 0x75, 0x67, 0x24, 0x53
	.byte  0x00

DS0001:
	.byte  0x2E, 0x64, 0x65, 0x62, 0x75, 0x67, 0x24, 0x54
	.byte  0x00


.att_syntax prefix
