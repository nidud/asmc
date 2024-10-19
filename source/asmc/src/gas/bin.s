
.intel_syntax noprefix

.global pe_create_PE_header
.global bin_init

.extern SortSegments
.extern _atoow
.extern CreateVariable
.extern CreateIntSegment
.extern Mangle
.extern RunLineQueue
.extern AddLineQueueX
.extern LstNL
.extern LstPrintf
.extern SymTables
.extern LclAlloc
.extern tqsort
.extern tstrcmp
.extern tstrncpy
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern tmemset
.extern tmemicmp
.extern tmemcmp
.extern tmemcpy
.extern ConvertSectionName
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern WriteError
.extern SymFind
.extern ftell
.extern fseek
.extern fwrite
.extern time


.SECTION .text
	.ALIGN	16

$_001:	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, rcx
	mov	rbx, rdx
	mov	rdi, qword ptr [rsi+0x68]
	cmp	dword ptr [rdi+0x48], 5
	jnz	$_002
	mov	eax, dword ptr [rdi+0x58]
	shl	eax, 4
	mov	dword ptr [rdi+0xC], eax
	jmp	$_018

	jmp	$_003

$_002:	cmp	byte ptr [rdi+0x6C], 0
	jz	$_003
	jmp	$_018

$_003:	mov	edx, 1
	mov	al, byte ptr [rdi+0x6A]
	cmp	byte ptr [rbx+0x1], al
	jbe	$_004
	mov	cl, byte ptr [rbx+0x1]
	jmp	$_005

$_004:	mov	cl, byte ptr [rdi+0x6A]
$_005:	shl	edx, cl
	mov	dword ptr [rbp-0x4], edx
	mov	ecx, edx
	neg	ecx
	dec	edx
	add	edx, dword ptr [rbx+0x4]
	and	edx, ecx
	sub	edx, dword ptr [rbx+0x4]
	add	dword ptr [rbx+0x4], edx
	mov	dword ptr [rbp-0x8], edx
	mov	rax, qword ptr [rdi]
	mov	qword ptr [rbp-0x10], rax
	test	rax, rax
	jnz	$_006
	mov	eax, dword ptr [rbx+0x4]
	sub	eax, dword ptr [rbx+0x8]
	mov	dword ptr [rbp-0x14], eax
	jmp	$_010

$_006:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 2
	jz	$_007
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 3
	jnz	$_008
$_007:	mov	eax, dword ptr [rbx+0x1C]
	mov	dword ptr [rbp-0x14], eax
	jmp	$_010

$_008:	cmp	dword ptr [rax+0x50], 0
	jnz	$_009
	mov	ecx, dword ptr [rbx+0x4]
	sub	ecx, dword ptr [rbx+0x8]
	mov	dword ptr [rax+0x28], ecx
	mov	dword ptr [rbp-0x14], 0
	jmp	$_010

$_009:	mov	ecx, dword ptr [rax+0x50]
	add	ecx, dword ptr [rbp-0x8]
	mov	dword ptr [rbp-0x14], ecx
$_010:	cmp	byte ptr [rbx], 0
	jnz	$_012
	mov	rax, qword ptr [rbp-0x10]
	test	rax, rax
	jz	$_012
	cmp	rax, qword ptr [ModuleInfo+0x200+rip]
	jz	$_011
	mov	dword ptr [rdi+0x8], 0
	jmp	$_012

$_011:	mov	edx, 36
	mov	rcx, qword ptr [rsi+0x8]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_012
	mov	dword ptr [rdi+0x8], 0
$_012:	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rdi+0x38], eax
	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rdi+0xC], eax
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 0
	jnz	$_015
	mov	eax, dword ptr [rsi+0x50]
	sub	eax, dword ptr [rdi+0x8]
	add	dword ptr [rbx+0x4], eax
	cmp	byte ptr [rbx], 0
	jz	$_013
	mov	eax, dword ptr [rdi+0x8]
	mov	dword ptr [rbx+0x18], eax
$_013:	cmp	dword ptr [rbx+0xC], -1
	jnz	$_014
	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rbx+0xC], eax
	mov	qword ptr [rbx+0x10], rsi
$_014:	jmp	$_016

$_015:	mov	eax, dword ptr [rsi+0x50]
	sub	eax, dword ptr [rdi+0x8]
	add	dword ptr [rbx+0x1C], eax
	cmp	dword ptr [rdi+0x48], 3
	jz	$_016
	add	dword ptr [rbx+0x4], eax
$_016:	mov	eax, dword ptr [rsi+0x50]
	add	dword ptr [rbp-0x14], eax
	mov	rcx, qword ptr [rbp-0x10]
	test	rcx, rcx
	jz	$_017
	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rcx+0x50], eax
	cmp	dword ptr [rcx+0x50], 65536
	jbe	$_017
	cmp	byte ptr [rcx+0x38], 0
	jnz	$_017
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 8003
	call	asmerr@PLT
$_017:	mov	byte ptr [rbx], 0
$_018:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_019:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 0
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_020:	test	rsi, rsi
	je	$_034
	mov	rdi, qword ptr [rsi+0x68]
	cmp	dword ptr [rdi+0x48], 5
	jnz	$_021
	jmp	$_033

$_021:	mov	rbx, qword ptr [rdi+0x28]
$_022:	test	rbx, rbx
	je	$_033
	jmp	$_031

$_023:	mov	rcx, qword ptr [rbx+0x30]
	test	rcx, rcx
	jz	$_024
	mov	rcx, qword ptr [rcx+0x30]
	test	rcx, rcx
	jz	$_024
	cmp	qword ptr [rcx+0x68], 0
	jz	$_024
	mov	rax, qword ptr [rcx+0x68]
	cmp	dword ptr [rax+0x48], 5
	je	$_032
$_024:	inc	dword ptr [rbp-0x4]
	cmp	qword ptr [rbp+0x28], 0
	jz	$_030
	mov	eax, dword ptr [rbx+0x14]
	mov	ecx, dword ptr [rdi+0xC]
	and	ecx, 0x0F
	add	ecx, eax
	mov	eax, dword ptr [rdi+0xC]
	shr	eax, 4
	cmp	qword ptr [rdi], 0
	jz	$_025
	mov	rdx, qword ptr [rdi]
	mov	edx, dword ptr [rdx+0x28]
	and	edx, 0x0F
	add	ecx, edx
	mov	rdx, qword ptr [rdi]
	mov	edx, dword ptr [rdx+0x28]
	shr	edx, 4
	add	eax, edx
$_025:	cmp	byte ptr [rbx+0x18], 9
	jnz	$_026
	add	ecx, 2
	jmp	$_027

$_026:	cmp	byte ptr [rbx+0x18], 10
	jnz	$_027
	add	ecx, 4
$_027:	jmp	$_029

$_028:	sub	ecx, 16
	inc	eax
$_029:	cmp	ecx, 65536
	jnc	$_028
	mov	rdx, qword ptr [rbp+0x28]
	mov	word ptr [rdx], cx
	mov	word ptr [rdx+0x2], ax
	add	qword ptr [rbp+0x28], 4
$_030:	jmp	$_032

$_031:	cmp	byte ptr [rbx+0x18], 10
	je	$_023
	cmp	byte ptr [rbx+0x18], 9
	je	$_023
	cmp	byte ptr [rbx+0x18], 8
	je	$_023
$_032:	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_022

$_033:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_020

$_034:
	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_035:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 1
	mov	rsi, qword ptr [SymTables+0x20+rip]
	xor	eax, eax
	xor	ebx, ebx
$_036:	test	rsi, rsi
	jz	$_046
	mov	rdi, qword ptr [rsi+0x68]
	cmp	dword ptr [rdi+0x48], 5
	jz	$_037
	cmp	byte ptr [rdi+0x6C], 0
	jz	$_038
$_037:	jmp	$_045

$_038:	cmp	dword ptr [rbp+0x28], 0
	jnz	$_041
	cmp	dword ptr [rdi+0x18], 0
	jnz	$_041
	mov	rcx, qword ptr [rsi+0x70]
$_039:	test	rcx, rcx
	jz	$_040
	mov	rdx, qword ptr [rcx+0x68]
	cmp	dword ptr [rdx+0x18], 0
	jnz	$_040
	mov	rcx, qword ptr [rcx+0x70]
	jmp	$_039

$_040:	test	rcx, rcx
	jz	$_046
$_041:	mov	ecx, dword ptr [rsi+0x50]
	sub	ecx, dword ptr [rdi+0x8]
	add	ecx, dword ptr [rdi+0x38]
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_042
	add	ebx, dword ptr [rdi+0x8]
$_042:	cmp	dword ptr [rbp+0x28], 0
	jz	$_043
	add	ecx, ebx
$_043:	cmp	eax, ecx
	jnc	$_044
	mov	eax, ecx
$_044:	mov	dword ptr [rbp-0x4], 0
$_045:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_036

$_046:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_047:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	rsi, rcx
	mov	rdi, qword ptr [rsi+0x68]
	cmp	dword ptr [rdi+0x48], 5
	jnz	$_048
	xor	eax, eax
	jmp	$_096

$_048:	mov	rbx, qword ptr [rdi+0x28]
$_049:	test	rbx, rbx
	je	$_095
	mov	eax, dword ptr [rbx+0x14]
	sub	eax, dword ptr [rdi+0x8]
	add	rax, qword ptr [rdi+0x10]
	mov	rcx, qword ptr [rbx+0x30]
	mov	qword ptr [rbp-0x18], rax
	test	rcx, rcx
	je	$_067
	cmp	qword ptr [rcx+0x30], 0
	jnz	$_050
	test	byte ptr [rcx+0x14], 0x40
	je	$_067
$_050:	test	byte ptr [rcx+0x14], 0x40
	jz	$_051
	mov	rsi, qword ptr [rbx+0x20]
	mov	dword ptr [rbp-0x1C], 0
	jmp	$_052

$_051:	mov	rsi, qword ptr [rcx+0x30]
	mov	eax, dword ptr [rcx+0x28]
	mov	dword ptr [rbp-0x1C], eax
$_052:	mov	qword ptr [rbp-0x28], rsi
	mov	rsi, qword ptr [rsi+0x68]
	mov	al, byte ptr [rbx+0x18]
	jmp	$_065

$_053:	mov	eax, dword ptr [rbx+0x10]
	add	eax, dword ptr [rbp-0x1C]
	add	eax, dword ptr [rsi+0xC]
	mov	rdx, qword ptr [rbp+0x30]
	sub	eax, dword ptr [rdx+0x18]
	mov	dword ptr [rbp-0x4], eax
	jmp	$_066

$_054:	mov	eax, dword ptr [rbx+0x10]
	add	eax, dword ptr [rbp-0x1C]
	sub	eax, dword ptr [rsi+0x8]
	mov	dword ptr [rbp-0x4], eax
	mov	rcx, qword ptr [rbp-0x28]
	mov	edx, 36
	mov	rcx, qword ptr [rcx+0x8]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_057
	mov	rcx, qword ptr [rbp-0x28]
	sub	rax, qword ptr [rcx+0x8]
	mov	rdx, qword ptr [SymTables+0x20+rip]
$_055:	test	rdx, rdx
	jz	$_057
	cmp	dword ptr [rdx+0x10], eax
	jnz	$_056
	push	rsi
	push	rdi
	mov	rcx, qword ptr [rbp-0x28]
	mov	rdi, qword ptr [rdx+0x8]
	mov	rsi, qword ptr [rcx+0x8]
	mov	ecx, eax
	repe cmpsb
	pop	rdi
	pop	rsi
	jnz	$_056
	mov	eax, dword ptr [rbx+0x10]
	add	eax, dword ptr [rbp-0x1C]
	add	eax, dword ptr [rsi+0xC]
	mov	rcx, qword ptr [rdx+0x68]
	sub	eax, dword ptr [rcx+0xC]
	mov	dword ptr [rbp-0x4], eax
	jmp	$_057

$_056:	mov	rdx, qword ptr [rdx+0x70]
	jmp	$_055

$_057:	jmp	$_066

$_058:	mov	eax, dword ptr [rsi+0xC]
	add	eax, dword ptr [rbp-0x1C]
	mov	dword ptr [rbp-0x4], eax
	jmp	$_066

$_059:	cmp	qword ptr [rsi], 0
	jz	$_063
	cmp	byte ptr [rbx+0x20], 0
	jz	$_063
	mov	rcx, qword ptr [rsi]
	mov	eax, dword ptr [rcx+0x28]
	and	eax, 0x0F
	add	eax, dword ptr [rsi+0xC]
	add	eax, dword ptr [rbx+0x10]
	add	eax, dword ptr [rbp-0x1C]
	mov	dword ptr [rbp-0x4], eax
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 2
	jz	$_060
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 3
	jnz	$_062
$_060:	mov	rcx, qword ptr [rbp+0x30]
	cmp	byte ptr [rdi+0x68], 2
	jnz	$_061
	mov	eax, dword ptr [rbp-0x4]
	add	rax, qword ptr [rcx+0x20]
	mov	qword ptr [rbp-0x10], rax
$_061:	mov	eax, dword ptr [rcx+0x20]
	add	dword ptr [rbp-0x4], eax
$_062:	jmp	$_064

$_063:	mov	eax, dword ptr [rsi+0xC]
	and	eax, 0x0F
	add	eax, dword ptr [rbx+0x10]
	add	eax, dword ptr [rbp-0x1C]
	mov	dword ptr [rbp-0x4], eax
$_064:	jmp	$_066

$_065:	cmp	al, 12
	je	$_053
	cmp	al, 13
	je	$_054
	cmp	al, 1
	je	$_058
	cmp	al, 2
	je	$_058
	cmp	al, 3
	je	$_058
	jmp	$_059

$_066:	jmp	$_068

$_067:	mov	qword ptr [rbp-0x28], 0
	mov	dword ptr [rbp-0x4], 0
$_068:	mov	rcx, qword ptr [rbp-0x18]
	mov	eax, dword ptr [rbp-0x4]
	movzx	edx, byte ptr [rbx+0x18]
	jmp	$_089
$C005F:
	sub	eax, dword ptr [rbx+0x14]
	sub	eax, dword ptr [rdi+0xC]
	dec	eax
	add	byte ptr [rcx], al
	jmp	$_093
$C0061:
	sub	eax, dword ptr [rbx+0x14]
	sub	eax, dword ptr [rdi+0xC]
	sub	eax, 2
	add	word ptr [rcx], ax
	jmp	$_093
$C0062:
	cmp	byte ptr [rdi+0x68], 2
	jnz	$_069
	movzx	edx, byte ptr [rbx+0x1A]
	sub	edx, 4
	add	dword ptr [rbx+0x14], edx
$_069:	sub	eax, dword ptr [rbx+0x14]
	sub	eax, dword ptr [rdi+0xC]
	sub	eax, 4
	add	dword ptr [rcx], eax
	jmp	$_093
$C0064:
	mov	byte ptr [rcx], al
	jmp	$_093
$C0065:
	mov	word ptr [rcx], ax
	jmp	$_093
$C0066:
$C0067:
$C0068:
	mov	dword ptr [rcx], eax
	jmp	$_093
$C0069:
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 2
	jnz	$_070
	cmp	byte ptr [rdi+0x68], 2
	jz	$_071
$_070:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 3
	jnz	$_072
$_071:	mov	rax, qword ptr [rbp-0x10]
$_072:	mov	qword ptr [rcx], rax
	jmp	$_093
$C006D:
	mov	al, ah
	mov	byte ptr [rcx], al
	jmp	$_093
$C006E:
	mov	rax, qword ptr [rbx+0x30]
	test	rax, rax
	jz	$_073
	cmp	byte ptr [rax+0x18], 3
	jnz	$_073
	mov	rdx, qword ptr [rax+0x68]
	cmp	dword ptr [rdx+0x48], 5
	jnz	$_073
	mov	edx, dword ptr [rdx+0x58]
	mov	word ptr [rcx], dx
	jmp	$_093

$_073:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 1
	jnz	$_079
	cmp	byte ptr [rax+0x18], 4
	jnz	$_074
	mov	qword ptr [rbp-0x28], rax
	mov	rsi, qword ptr [rax+0x68]
	mov	edx, dword ptr [rax+0x28]
	shr	edx, 4
	mov	word ptr [rcx], dx
	jmp	$_078

$_074:	cmp	byte ptr [rax+0x18], 3
	jnz	$_076
	mov	qword ptr [rbp-0x28], rax
	mov	rsi, qword ptr [rax+0x68]
	mov	edx, dword ptr [rsi+0xC]
	cmp	qword ptr [rsi], 0
	jz	$_075
	mov	rax, qword ptr [rsi]
	add	edx, dword ptr [rax+0x28]
$_075:	shr	edx, 4
	mov	word ptr [rcx], dx
	jmp	$_078

$_076:	cmp	byte ptr [rbx+0x20], 1
	jnz	$_077
	mov	rax, qword ptr [rsi]
	mov	eax, dword ptr [rax+0x28]
	shr	eax, 4
	mov	word ptr [rcx], ax
	jmp	$_078

$_077:	mov	eax, dword ptr [rsi+0xC]
	shr	eax, 4
	mov	word ptr [rcx], ax
$_078:	jmp	$_093

$_079:	mov	eax, dword ptr [rbp-0x4]
$C0077:
	cmp	qword ptr [rbp-0x28], 0
	jz	$_080
	cmp	dword ptr [rsi+0x48], 5
	jnz	$_080
	mov	word ptr [rcx], ax
	mov	eax, dword ptr [rsi+0x58]
	mov	word ptr [rcx+0x2], ax
	jmp	$_093

$_080:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 1
	jnz	$_084
	mov	word ptr [rcx], ax
	add	rcx, 2
	cmp	byte ptr [rbx+0x20], 1
	jnz	$_081
	mov	rax, qword ptr [rsi]
	mov	eax, dword ptr [rax+0x28]
	shr	eax, 4
	mov	word ptr [rcx], ax
	jmp	$_083

$_081:	mov	eax, dword ptr [rsi+0xC]
	cmp	qword ptr [rsi], 0
	jz	$_082
	mov	rdx, qword ptr [rsi]
	add	eax, dword ptr [rdx+0x28]
$_082:	shr	eax, 4
	mov	word ptr [rcx], ax
$_083:	jmp	$_093

$_084:	mov	eax, dword ptr [rbp-0x4]
$C007D:
	cmp	qword ptr [rbp-0x28], 0
	jz	$_085
	cmp	dword ptr [rsi+0x48], 5
	jnz	$_085
	mov	dword ptr [rcx], eax
	mov	eax, dword ptr [rsi+0x58]
	mov	word ptr [rcx+0x4], ax
	jmp	$_093

$_085:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 1
	jnz	$C0083
	mov	dword ptr [rcx], eax
	cmp	byte ptr [rbx+0x20], 1
	jnz	$_086
	mov	rax, qword ptr [rsi]
	mov	eax, dword ptr [rax+0x28]
	shr	eax, 4
	mov	word ptr [rcx+0x4], ax
	jmp	$_088

$_086:	mov	eax, dword ptr [rsi+0xC]
	cmp	qword ptr [rsi], 0
	jz	$_087
	mov	rdx, qword ptr [rsi]
	add	eax, dword ptr [rdx+0x28]
$_087:	shr	eax, 4
	mov	word ptr [rcx+0x4], ax
$_088:	jmp	$_093

$C0083: mov	rcx, qword ptr [ModuleInfo+0x1A8+rip]
	lea	rdx, [rcx+0xA]
	mov	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rbx+0x14]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rcx+0x8]
	movzx	r8d, byte ptr [rbx+0x18]
	mov	ecx, 3019
	call	asmerr@PLT
	jmp	$_093

$_089:	cmp	edx, 1
	jl	$C0083
	cmp	edx, 13
	jg	$C0083
	push	rax
	lea	r11, [$C0083+rip]
	movzx	eax, word ptr [r11+rdx*2-2+($C0084-$C0083)]
	sub	r11, rax
	pop	rax
	jmp	r11

	.ALIGN 2
$C0084:
	.word $C0083-$C005F
	.word $C0083-$C0061
	.word $C0083-$C0062
	.word $C0083-$C0064
	.word $C0083-$C0065
	.word $C0083-$C0066
	.word $C0083-$C0069
	.word $C0083-$C006E
	.word $C0083-$C0077
	.word $C0083-$C007D
	.word $C0083-$C006D
	.word $C0083-$C0067
	.word $C0083-$C0068
$_093:
	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_049
$_095:	xor	eax, eax
$_096:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_097:
	push	rsi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_098
	lea	rcx, [DS0000+rip]
	call	SymFind@PLT
	test	rax, rax
	jnz	$_098
	or	byte ptr [rsi+0x170], 0x01
$_098:	test	byte ptr [rsi+0x170], 0x01
	jz	$_099
	lea	r9, [DS0002+rip]
	lea	r8, [DS0003+rip]
	lea	rdx, [DS0002+rip]
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
	call	RunLineQueue@PLT
	lea	rcx, [DS0000+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_099
	cmp	byte ptr [rax+0x18], 3
	jnz	$_099
	mov	rcx, qword ptr [rax+0x68]
	mov	dword ptr [rcx+0x48], 6
$_099:	leave
	pop	rsi
	ret

set_file_flags:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rcx, [DS0004+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_101
	mov	rcx, qword ptr [rax+0x68]
	mov	rdx, qword ptr [rcx+0x10]
	movzx	eax, word ptr [rdx+0x16]
	cmp	qword ptr [rbp+0x18], 0
	jz	$_100
	mov	rcx, qword ptr [rbp+0x18]
	mov	eax, dword ptr [rcx]
	mov	word ptr [rdx+0x16], ax
$_100:	mov	rcx, qword ptr [rbp+0x10]
	mov	dword ptr [rcx+0x28], eax
$_101:	leave
	ret

pe_create_PE_header:
	push	rsi
	push	rdi
	push	rbx
	sub	rsp, 48
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_107
	cmp	byte ptr [ModuleInfo+0x1B5+rip], 7
	jz	$_102
	mov	ecx, 3002
	call	asmerr@PLT
$_102:	movzx	eax, byte ptr [Options+0xCE+rip]
	mov	ebx, 264
	lea	rdi, [pe64def+rip]
	mov	word ptr [rdi+0x5C], ax
	cmp	byte ptr [Options+0xCF+rip], 0
	jz	$_103
	or	byte ptr [rdi+0x17], 0x20
$_103:	lea	rcx, [DS0004+rip]
	call	SymFind@PLT
	test	rax, rax
	jnz	$_104
	mov	dword ptr [rsp+0x20], 1
	movzx	r9d, byte ptr [ModuleInfo+0x1CD+rip]
	mov	r8d, 2
	lea	rdx, [DS0005+rip]
	lea	rcx, [DS0004+rip]
	call	CreateIntSegment@PLT
	mov	dword ptr [rax+0x50], ebx
	mov	rsi, qword ptr [rax+0x68]
	mov	rcx, qword ptr [ModuleInfo+0x200+rip]
	mov	qword ptr [rsi], rcx
	mov	byte ptr [rsi+0x72], 2
	mov	byte ptr [rsi+0x69], 64
	mov	byte ptr [rsi+0x6B], 1
	mov	dword ptr [rsi+0x18], ebx
	jmp	$_106

$_104:	cmp	dword ptr [rax+0x50], ebx
	jge	$_105
	mov	dword ptr [rax+0x50], ebx
$_105:	mov	rsi, qword ptr [rax+0x68]
	mov	byte ptr [rsi+0x6F], 1
	mov	dword ptr [rsi+0x8], 0
$_106:	mov	dword ptr [rsi+0x48], 6
	mov	ecx, ebx
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x10], rax
	mov	r8d, ebx
	mov	rdx, rdi
	mov	rcx, rax
	call	tmemcpy@PLT
	mov	rbx, rax
	lea	rcx, [rbx+0x8]
	movzx	ebx, word ptr [rdi+0x16]
	mov	rdi, rcx
	call	time@PLT
	mov	edx, ebx
	lea	rcx, [DS0006+rip]
	call	CreateVariable@PLT
	test	rax, rax
	jz	$_107
	or	byte ptr [rax+0x14], 0x20
	lea	rcx, [set_file_flags+rip]
	mov	qword ptr [rax+0x58], rcx
$_107:	add	rsp, 48
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_108:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	dword ptr [rbp-0xC], 0
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_127
	lea	rcx, [DS0007+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_109
	mov	rdi, rax
	mov	rsi, qword ptr [rdi+0x68]
	jmp	$_110

$_109:	mov	dword ptr [rbp-0xC], 1
	mov	dword ptr [rsp+0x20], 1
	movzx	r9d, byte ptr [ModuleInfo+0x1CD+rip]
	mov	r8d, 2
	lea	rdx, [DS0005+rip]
	lea	rcx, [DS0007+rip]
	call	CreateIntSegment@PLT
	mov	rdi, rax
	mov	rsi, qword ptr [rdi+0x68]
	mov	rax, qword ptr [ModuleInfo+0x200+rip]
	mov	qword ptr [rsi], rax
	mov	byte ptr [rsi+0x72], 2
$_110:	mov	dword ptr [rsi+0x48], 6
	cmp	dword ptr [rbp-0xC], 0
	jnz	$_111
	jmp	$_127

$_111:	mov	qword ptr [rbp-0x8], rdi
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_112:	test	rdi, rdi
	je	$_121
	mov	rsi, qword ptr [rdi+0x68]
	mov	dword ptr [rsi+0x4C], 10
	cmp	dword ptr [rsi+0x48], 2
	jnz	$_116
	cmp	byte ptr [rsi+0x6B], 0
	jnz	$_113
	cmp	byte ptr [rsi+0x69], 64
	jnz	$_114
$_113:	mov	dword ptr [rsi+0x48], 7
	jmp	$_115

$_114:	cmp	qword ptr [rsi+0x50], 0
	jz	$_115
	mov	rcx, qword ptr [rsi+0x50]
	lea	rdx, [DS0008+rip]
	mov	rcx, qword ptr [rcx+0x8]
	call	tstrcmp@PLT
	test	eax, eax
	jnz	$_115
	mov	dword ptr [rsi+0x48], 7
$_115:	jmp	$_120

$_116:	cmp	dword ptr [rsi+0x48], 0
	jnz	$_120
	mov	rbx, qword ptr [rdi+0x8]
	mov	r8d, 5
	lea	rdx, [DS0009+rip]
	mov	rcx, rbx
	call	tmemcmp@PLT
	test	eax, eax
	jnz	$_119
	cmp	byte ptr [rbx+0x5], 0
	jz	$_117
	cmp	byte ptr [rbx+0x5], 36
	jnz	$_118
$_117:	mov	dword ptr [rsi+0x48], 9
$_118:	jmp	$_120

$_119:	lea	rdx, [DS000A+rip]
	mov	rcx, rbx
	call	tstrcmp@PLT
	test	eax, eax
	jnz	$_120
	mov	dword ptr [rsi+0x48], 8
$_120:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_112

$_121:	mov	ebx, 1
	xor	esi, esi
$_122:	cmp	ebx, 7
	jnc	$_126
	lea	rcx, [flat_order+rip]
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_123:	test	rdi, rdi
	jz	$_125
	mov	rdx, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rcx+rbx*4]
	cmp	dword ptr [rdx+0x48], eax
	jnz	$_124
	cmp	dword ptr [rdi+0x50], 0
	jz	$_124
	inc	esi
	jmp	$_125

$_124:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_123

$_125:	inc	ebx
	jmp	$_122

$_126:	test	esi, esi
	jz	$_127
	mov	rdi, qword ptr [rbp-0x8]
	imul	ebx, esi, 40
	mov	dword ptr [rdi+0x50], ebx
	mov	rsi, qword ptr [rdi+0x68]
	lea	ecx, [rbx+0x28]
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x10], rax
$_127:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

compare_exp:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, qword ptr [rdx]
	mov	rcx, qword ptr [rcx]
	call	tstrcmp@PLT
	leave
	ret

$_128:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 120
	mov	rdi, qword ptr [SymTables+0x40+rip]
	xor	ebx, ebx
$_129:	test	rdi, rdi
	jz	$_131
	mov	rdx, qword ptr [rdi+0x68]
	test	byte ptr [rdx+0x40], 0x04
	jz	$_130
	inc	ebx
$_130:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_129

$_131:
	test	ebx, ebx
	je	$_148
	lea	rdi, [rbp-0x4]
	call	time@PLT
	lea	rsi, [ModuleInfo+0x230+rip]
	mov	qword ptr [rsp+0x50], rsi
	mov	qword ptr [rsp+0x48], rsi
	mov	qword ptr [rsp+0x40], rsi
	mov	dword ptr [rsp+0x38], ebx
	mov	dword ptr [rsp+0x30], ebx
	mov	dword ptr [rsp+0x28], 1
	mov	qword ptr [rsp+0x20], rsi
	mov	r9d, dword ptr [rbp-0x4]
	lea	r8, [DS000D+rip]
	lea	rdx, [DS000C+rip]
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
	mov	qword ptr [rbp-0x10], rsi
	mov	dword ptr [rbp-0x8], ebx
	imul	ecx, ebx, 16
	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x60]
	mov	qword ptr [rbp-0x18], rax
	mov	rdi, qword ptr [SymTables+0x40+rip]
	mov	rsi, rax
	xor	ebx, ebx
$_132:	test	rdi, rdi
	jz	$_134
	mov	rdx, qword ptr [rdi+0x68]
	test	byte ptr [rdx+0x40], 0x04
	jz	$_133
	mov	rax, qword ptr [rdi+0x8]
	mov	qword ptr [rsi], rax
	mov	dword ptr [rsi+0x8], ebx
	inc	ebx
	add	rsi, 16
$_133:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_132

$_134:	lea	r9, [compare_exp+rip]
	mov	r8d, 16
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, qword ptr [rbp-0x18]
	call	tqsort@PLT
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
	mov	rdi, qword ptr [SymTables+0x40+rip]
$_135:	test	rdi, rdi
	jz	$_137
	mov	rdx, qword ptr [rdi+0x68]
	test	byte ptr [rdx+0x40], 0x04
	jz	$_136
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
$_136:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_135

$_137:	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0010+rip]
	call	AddLineQueueX@PLT
	mov	rsi, qword ptr [rbp-0x18]
	xor	ebx, ebx
$_138:	cmp	ebx, dword ptr [rbp-0x8]
	jge	$_139
	mov	rdx, qword ptr [rsi]
	lea	rcx, [DS0011+rip]
	call	AddLineQueueX@PLT
	inc	ebx
	add	rsi, 16
	jmp	$_138

$_139:	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0012+rip]
	call	AddLineQueueX@PLT
	mov	rsi, qword ptr [rbp-0x18]
	xor	ebx, ebx
$_140:	cmp	ebx, dword ptr [rbp-0x8]
	jge	$_141
	mov	edx, dword ptr [rsi+0x8]
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
	inc	ebx
	add	rsi, 16
	jmp	$_140

$_141:	mov	rbx, qword ptr [ModuleInfo+0x98+rip]
	mov	rcx, rbx
	call	tstrlen@PLT
	add	rbx, rax
$_142:	cmp	rbx, qword ptr [ModuleInfo+0x98+rip]
	jbe	$_143
	cmp	byte ptr [rbx], 47
	jz	$_143
	cmp	byte ptr [rbx], 92
	jz	$_143
	cmp	byte ptr [rbx], 58
	jz	$_143
	dec	rbx
	jmp	$_142

$_143:	mov	r8, rbx
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
	mov	rdi, qword ptr [SymTables+0x40+rip]
$_144:	test	rdi, rdi
	jz	$_147
	mov	rdx, qword ptr [rdi+0x68]
	test	byte ptr [rdx+0x40], 0x04
	jz	$_146
	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	rcx, rdi
	call	Mangle@PLT
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	cmp	byte ptr [Options+0x90+rip], 0
	jz	$_145
	mov	rcx, qword ptr [rdi+0x8]
$_145:	mov	r8, rcx
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
$_146:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_144

$_147:	lea	rdx, [DS000C+rip]
	lea	rcx, [DS0016+rip]
	call	AddLineQueueX@PLT
	call	RunLineQueue@PLT
$_148:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_149:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 376
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x8], 214
	lea	rax, [DS0017+rip]
	mov	qword ptr [rbp-0x10], rax
	mov	rbx, qword ptr [ModuleInfo+0x60+rip]
$_150:	test	rbx, rbx
	je	$_166
	cmp	dword ptr [rbx+0x8], 0
	je	$_165
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_151
	mov	dword ptr [rbp-0x4], 1
	lea	rcx, [DS0018+rip]
	call	AddLineQueueX@PLT
$_151:	lea	rdx, [rbx+0xC]
	lea	rcx, [rbp-0x110]
	call	tstrcpy@PLT
	mov	rsi, rax
	jmp	$_153

$_152:	mov	byte ptr [rax], 95
$_153:	mov	edx, 46
	mov	rcx, rsi
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_152
	jmp	$_155

$_154:	mov	byte ptr [rax], 95
$_155:	mov	edx, 45
	mov	rcx, rsi
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_154
	lea	rcx, [DS0019+rip]
	lea	rdx, [DS000D+rip]
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x58], eax
	mov	qword ptr [rsp+0x50], rsi
	mov	qword ptr [rsp+0x48], rdx
	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rsp+0x40], rax
	mov	qword ptr [rsp+0x38], rcx
	mov	qword ptr [rsp+0x30], rcx
	mov	qword ptr [rsp+0x28], rsi
	mov	qword ptr [rsp+0x20], rsi
	mov	r9, rsi
	mov	r8, rdx
	mov	rdx, rcx
	lea	rcx, [DS001A+rip]
	call	AddLineQueueX@PLT
	mov	rdi, qword ptr [SymTables+0x10+rip]
$_156:	test	rdi, rdi
	jz	$_158
	test	byte ptr [rdi+0x14], 0x08
	jz	$_157
	cmp	qword ptr [rdi+0x50], rbx
	jnz	$_157
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
$_157:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_156

$_158:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x30], eax
	mov	qword ptr [rsp+0x28], rsi
	lea	rax, [DS000D+rip]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x10]
	lea	r8, [DS0019+rip]
	lea	rdx, [DS0019+rip]
	lea	rcx, [DS001C+rip]
	call	AddLineQueueX@PLT
	mov	rdi, qword ptr [SymTables+0x10+rip]
$_159:	test	rdi, rdi
	jz	$_161
	test	byte ptr [rdi+0x14], 0x08
	jz	$_160
	cmp	qword ptr [rdi+0x50], rbx
	jnz	$_160
	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	rcx, rdi
	call	Mangle@PLT
	mov	r9, qword ptr [rdi+0x8]
	mov	r8, qword ptr [ModuleInfo+0x188+rip]
	mov	rdx, qword ptr [ModuleInfo+0x68+rip]
	lea	rcx, [DS001D+rip]
	call	AddLineQueueX@PLT
$_160:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_159

$_161:	lea	r9, [DS000D+rip]
	lea	r8, [DS0019+rip]
	lea	rdx, [DS0019+rip]
	lea	rcx, [DS001E+rip]
	call	AddLineQueueX@PLT
	mov	rdi, qword ptr [SymTables+0x10+rip]
$_162:	test	rdi, rdi
	jz	$_164
	test	byte ptr [rdi+0x14], 0x08
	jz	$_163
	cmp	qword ptr [rdi+0x50], rbx
	jnz	$_163
	mov	r8, qword ptr [rdi+0x8]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS001F+rip]
	call	AddLineQueueX@PLT
$_163:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_162

$_164:	lea	r9, [DS0019+rip]
	lea	r8, [rbx+0xC]
	mov	rdx, rsi
	lea	rcx, [DS0020+rip]
	call	AddLineQueueX@PLT
$_165:	mov	rbx, qword ptr [rbx]
	jmp	$_150

$_166:
	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_167
	lea	r9, [DS0019+rip]
	lea	r8, [DS000D+rip]
	lea	rdx, [DS0019+rip]
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
	call	RunLineQueue@PLT
$_167:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_168:
	mov	eax, 4294967295
	jmp	$_170

$_169:	shr	ecx, 1
	inc	eax
$_170:	test	ecx, ecx
	jnz	$_169
	ret

$_171:
	mov	rcx, qword ptr [rcx+0x68]
	mov	eax, 3221225536
	jmp	$_178

$_172:	mov	eax, 1610612768
	jmp	$_180

$_173:	mov	eax, 3221225600
	jmp	$_180

$_174:	mov	eax, 3221225600
	jmp	$_180

$_175:	mov	eax, 1073741888
	jmp	$_180

$_176:	mov	rdx, qword ptr [rcx+0x50]
	mov	rdx, qword ptr [rdx+0x8]
	cmp	dword ptr [rdx], 1397641027
	jnz	$_177
	cmp	word ptr [rdx+0x4], 84
	jnz	$_177
	mov	eax, 1073741888
$_177:	jmp	$_180

$_178:	cmp	dword ptr [rcx+0x48], 1
	jz	$_172
	cmp	dword ptr [rcx+0x48], 3
	jz	$_173
	cmp	byte ptr [rcx+0x72], 5
	jnz	$_179
	cmp	dword ptr [rcx+0x18], 0
	jz	$_174
$_179:	cmp	byte ptr [rcx+0x6B], 0
	jnz	$_175
	cmp	qword ptr [rcx+0x50], 0
	jnz	$_176
$_180:	cmp	byte ptr [rcx+0x69], 0
	jz	$_181
	and	eax, 0x1FFFFFF
	mov	dl, byte ptr [rcx+0x69]
	and	edx, 0xFE
	shl	edx, 24
	or	eax, edx
$_181:	ret

$_182:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x8], 0
	mov	dword ptr [rbp-0x10], -1
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_183:	test	rdi, rdi
	jz	$_190
	mov	rsi, qword ptr [rdi+0x68]
	cmp	dword ptr [rsi+0x48], 6
	jz	$_189
	mov	rbx, qword ptr [rsi+0x28]
$_184:	test	rbx, rbx
	jz	$_189
	jmp	$_187

$_185:	mov	eax, dword ptr [rbx+0x14]
	and	eax, 0xFFFFF000
	add	eax, dword ptr [rsi+0xC]
	cmp	eax, dword ptr [rbp-0x10]
	jz	$_186
	mov	dword ptr [rbp-0x10], eax
	inc	dword ptr [rbp-0x8]
	test	byte ptr [rbp-0x4], 0x01
	jz	$_186
	inc	dword ptr [rbp-0x4]
$_186:	inc	dword ptr [rbp-0x4]
	jmp	$_188

$_187:	cmp	byte ptr [rbx+0x18], 5
	jz	$_185
	cmp	byte ptr [rbx+0x18], 6
	jz	$_185
	cmp	byte ptr [rbx+0x18], 7
	jz	$_185
$_188:	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_184

$_189:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_183

$_190:
	imul	ecx, dword ptr [rbp-0x8], 8
	imul	eax, dword ptr [rbp-0x4], 2
	add	ecx, eax
	mov	rdi, qword ptr [rbp+0x28]
	mov	rsi, qword ptr [rdi+0x68]
	mov	dword ptr [rdi+0x50], ecx
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x10], rax
	mov	qword ptr [rbp-0x30], rax
	mov	dword ptr [rax], -1
	add	rax, 8
	mov	qword ptr [rbp-0x38], rax
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_191:	test	rdi, rdi
	je	$_203
	mov	rsi, qword ptr [rdi+0x68]
	cmp	dword ptr [rsi+0x48], 6
	je	$_202
	mov	rbx, qword ptr [rsi+0x28]
$_192:	test	rbx, rbx
	je	$_202
	xor	ecx, ecx
	mov	al, byte ptr [rbx+0x18]
	jmp	$_196

$_193:	mov	ecx, 2
	jmp	$_197

$_194:	mov	ecx, 3
	jmp	$_197

$_195:	mov	ecx, 10
	jmp	$_197

$_196:	cmp	al, 5
	jz	$_193
	cmp	al, 6
	jz	$_194
	cmp	al, 7
	jz	$_195
$_197:	test	ecx, ecx
	jz	$_201
	mov	dword ptr [rbp-0xC], ecx
	mov	eax, dword ptr [rbx+0x14]
	and	eax, 0xFFFFF000
	add	eax, dword ptr [rsi+0xC]
	mov	rdx, qword ptr [rbp-0x30]
	mov	rcx, qword ptr [rbp-0x38]
	cmp	eax, dword ptr [rdx]
	jz	$_200
	cmp	dword ptr [rdx], -1
	jz	$_199
	test	byte ptr [rdx+0x4], 0x02
	jz	$_198
	mov	word ptr [rcx], 0
	add	rcx, 2
	add	dword ptr [rdx+0x4], 2
$_198:	mov	rdx, rcx
	add	rcx, 8
$_199:	mov	dword ptr [rdx], eax
	mov	dword ptr [rdx+0x4], 8
$_200:	add	dword ptr [rdx+0x4], 2
	mov	qword ptr [rbp-0x30], rdx
	mov	eax, dword ptr [rbx+0x14]
	and	eax, 0xFFF
	mov	edx, dword ptr [rbp-0xC]
	shl	edx, 12
	or	eax, edx
	mov	word ptr [rcx], ax
	add	rcx, 2
	mov	qword ptr [rbp-0x38], rcx
$_201:	mov	rbx, qword ptr [rbx+0x8]
	jmp	$_192

$_202:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_191

$_203:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_204:
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	rbx, rcx
	mov	rsi, rdx
	jmp	$_230

$_205:	lodsb
	dec	dword ptr [rbp+0x38]
	cmp	al, 45
	jz	$_206
	cmp	al, 47
	jne	$_230
$_206:	lodsd
	sub	dword ptr [rbp+0x38], 4
	or	eax, 0x20202020
	jmp	$_229

$_207:	lodsb
	dec	dword ptr [rbp+0x38]
	cmp	al, 58
	jnz	$_210
	mov	eax, dword ptr [rsi]
	mov	ecx, 10
	cmp	al, 48
	jnz	$_208
	cmp	ah, 120
	jnz	$_208
	lodsw
	sub	dword ptr [rbp+0x38], 2
	mov	ecx, 16
$_208:	mov	r9d, dword ptr [rbp+0x38]
	mov	r8d, ecx
	lea	rdx, [rbp-0x10]
	mov	rcx, rsi
	call	_atoow@PLT
	mov	eax, dword ptr [rbp-0x10]
	mov	ecx, eax
	or	ecx, dword ptr [rbp-0xC]
	mov	edx, dword ptr [rbp-0x8]
	or	edx, dword ptr [rbp-0x4]
	test	ecx, ecx
	jz	$_210
	test	edx, edx
	jnz	$_210
	test	eax, 0xFFF
	jnz	$_210
	mov	edx, dword ptr [rbp-0xC]
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_209
	mov	dword ptr [rbx+0x30], eax
	mov	dword ptr [rbx+0x34], edx
	jmp	$_210

$_209:	test	edx, edx
	jnz	$_210
	cmp	eax, 4294963200
	ja	$_210
	mov	dword ptr [rbx+0x34], eax
$_210:	jmp	$_230

$_211:	lodsw
	dec	dword ptr [rbp+0x38]
	or	al, 0x20
	cmp	al, 121
	jnz	$_214
	cmp	ah, 58
	jnz	$_214
	lea	rdi, [rbp-0x90]
$_212:	cmp	dword ptr [rbp+0x38], 0
	jle	$_213
	lodsb
	test	al, al
	jz	$_213
	cmp	al, 32
	jz	$_213
	stosb
	dec	dword ptr [rbp+0x38]
	jmp	$_212

$_213:	xor	eax, eax
	stosb
	lea	rcx, [rbp-0x90]
	call	SymFind@PLT
	test	rax, rax
	jz	$_214
	mov	qword ptr [ModuleInfo+0xE0+rip], rax
$_214:	jmp	$_230

$_215:	lodsb
	dec	dword ptr [rbp+0x38]
	or	al, 0x20
	cmp	al, 100
	jnz	$_217
	lodsb
	dec	dword ptr [rbp+0x38]
	cmp	al, 58
	jnz	$_216
	and	word ptr [rbx+0x16], 0xFFFE
	jmp	$_217

$_216:	or	byte ptr [rbx+0x16], 0x01
$_217:	jmp	$_230

$_218:	mov	r8d, 13
	lea	rdx, [DS0022+rip]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_220
	sub	dword ptr [rbp+0x38], 13
	add	rsi, 13
	mov	r8d, 3
	lea	rdx, [DS0023+rip]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_219
	sub	dword ptr [rbp+0x38], 3
	add	rsi, 3
	and	word ptr [rbx+0x16], 0xFFDF
	jmp	$_220

$_219:	or	byte ptr [rbx+0x16], 0x20
$_220:	jmp	$_230

$_221:	mov	dword ptr [rbp-0x94], 0
	mov	r8d, 6
	lea	rdx, [DS0024+rip]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jne	$_224
	sub	dword ptr [rbp+0x38], 6
	add	rsi, 6
	mov	r8d, 7
	lea	rdx, [DS0025+rip]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_222
	sub	dword ptr [rbp+0x38], 7
	add	rsi, 7
	mov	dword ptr [rbp-0x94], 2
	jmp	$_224

$_222:	mov	r8d, 7
	lea	rdx, [DS0026+rip]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_223
	sub	dword ptr [rbp+0x38], 7
	add	rsi, 7
	mov	dword ptr [rbp-0x94], 3
	jmp	$_224

$_223:	mov	r8d, 6
	lea	rdx, [DS0027+rip]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_224
	sub	dword ptr [rbp+0x38], 6
	add	rsi, 6
	mov	dword ptr [rbp-0x94], 1
$_224:	cmp	dword ptr [rbp-0x94], 0
	jz	$_226
	mov	eax, dword ptr [rbp-0x94]
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_225
	mov	word ptr [rbx+0x5C], ax
	jmp	$_226

$_225:	mov	word ptr [rbx+0x5C], ax
$_226:	jmp	$_230

$_227:	and	eax, 0xFFFFFF
	cmp	eax, 7105636
	jnz	$_228
	or	byte ptr [rbx+0x17], 0x20
$_228:	jmp	$_230

$_229:	cmp	eax, 1702060386
	je	$_207
	cmp	eax, 1920233061
	je	$_211
	cmp	eax, 1702390118
	je	$_215
	cmp	eax, 1735549292
	je	$_218
	cmp	eax, 1935832435
	je	$_221
	jmp	$_227

$_230:
	cmp	dword ptr [rbp+0x38], 3
	jg	$_205
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_231:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 440
	mov	dword ptr [rbp-0x14], 0
	mov	dword ptr [rbp-0x18], 0
	mov	dword ptr [rbp-0x1C], 0
	mov	dword ptr [rbp-0x20], 0
	mov	dword ptr [rbp-0x24], 0
	mov	dword ptr [rbp-0x28], 0
	mov	qword ptr [rbp-0x48], 0
	lea	rcx, [DS0000+rip]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x30], rax
	mov	rsi, qword ptr [rax+0x68]
	lea	rcx, [DS0004+rip]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x38], rax
	lea	rcx, [DS0007+rip]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x40], rax
	mov	rax, qword ptr [ModuleInfo+0x200+rip]
	mov	qword ptr [rsi], rax
	mov	rax, qword ptr [rbp-0x38]
	mov	rsi, qword ptr [rax+0x68]
	mov	rcx, qword ptr [rsi+0x10]
	mov	qword ptr [rbp-0x50], rcx
	mov	ax, word ptr [rcx+0x16]
	mov	word ptr [rbp-0xE], ax
	mov	rdi, qword ptr [ModuleInfo+0x50+rip]
$_232:	test	rdi, rdi
	jz	$_233
	lea	rcx, [rdi+0x8]
	call	tstrlen@PLT
	mov	r8d, eax
	lea	rdx, [rdi+0x8]
	mov	rcx, qword ptr [rbp-0x50]
	call	$_204
	mov	rdi, qword ptr [rdi]
	jmp	$_232

$_233:
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_234:	test	rdi, rdi
	jz	$_236
	mov	rsi, qword ptr [rdi+0x68]
	cmp	byte ptr [rsi+0x6C], 0
	jz	$_235
	lea	rdx, [DS0028+rip]
	mov	rcx, qword ptr [rdi+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_235
	mov	r8d, dword ptr [rsi+0x18]
	mov	rdx, qword ptr [rsi+0x10]
	mov	rcx, qword ptr [rbp-0x50]
	call	$_204
$_235:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_234

$_236:
	test	eax, 0x1
	jnz	$_237
	mov	dword ptr [rsp+0x20], 1
	movzx	r9d, byte ptr [ModuleInfo+0x1CD+rip]
	mov	r8d, 2
	lea	rdx, [DS0029+rip]
	lea	rcx, [DS000A+rip]
	call	CreateIntSegment@PLT
	mov	qword ptr [rbp-0x48], rax
	test	rax, rax
	jz	$_237
	mov	rsi, qword ptr [rax+0x68]
	mov	dword ptr [rax+0x50], 8
	mov	rax, qword ptr [ModuleInfo+0x200+rip]
	mov	qword ptr [rsi], rax
	mov	byte ptr [rsi+0x72], 2
	mov	dword ptr [rsi+0x48], 8
	mov	byte ptr [rsi+0x69], 66
	mov	dword ptr [rsi+0x18], 8
	mov	rdx, qword ptr [rbp-0x40]
	mov	rsi, qword ptr [rdx+0x68]
	mov	edi, dword ptr [rdx+0x50]
	add	dword ptr [rdx+0x50], 40
	add	rdi, qword ptr [rsi+0x10]
	mov	ecx, 40
	xor	eax, eax
	rep stosb
$_237:	lea	rcx, [flat_order+rip]
	xor	ebx, ebx
$_238:	cmp	ebx, 7
	jnc	$_242
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_239:	test	rdi, rdi
	jz	$_241
	mov	rsi, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rcx+rbx*4]
	cmp	dword ptr [rsi+0x48], eax
	jnz	$_240
	mov	dword ptr [rsi+0x4C], ebx
$_240:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_239

$_241:	inc	ebx
	jmp	$_238

$_242:
	mov	ecx, 2
	call	SortSegments@PLT
	mov	rax, qword ptr [rbp-0x50]
	mov	eax, dword ptr [rax+0x3C]
	mov	ecx, eax
	call	$_168
	mov	dword ptr [rbp-0x8], eax
	mov	rax, qword ptr [rbp-0x50]
	mov	eax, dword ptr [rax+0x38]
	mov	dword ptr [rbp-0xC], eax
	mov	rdi, qword ptr [SymTables+0x20+rip]
	mov	ebx, 4294967295
$_243:	test	rdi, rdi
	jz	$_247
	mov	rsi, qword ptr [rdi+0x68]
	mov	rdx, qword ptr [rbp+0x28]
	cmp	dword ptr [rsi+0x4C], 10
	jz	$_244
	cmp	dword ptr [rsi+0x4C], ebx
	jz	$_245
$_244:	mov	ebx, dword ptr [rsi+0x4C]
	mov	eax, dword ptr [rbp-0x8]
	mov	byte ptr [rdx+0x1], al
	mov	eax, dword ptr [rbp-0xC]
	jmp	$_246

$_245:	mov	eax, 1
	mov	cl, byte ptr [rsi+0x6A]
	shl	eax, cl
	mov	byte ptr [rdx+0x1], 0
$_246:	dec	eax
	mov	ecx, eax
	not	ecx
	add	eax, dword ptr [rdx+0x1C]
	and	eax, ecx
	mov	dword ptr [rdx+0x1C], eax
	mov	rcx, rdi
	call	$_001
	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_243

$_247:
	mov	rbx, qword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp-0x48]
	test	rcx, rcx
	jz	$_249
	call	$_182
	mov	rcx, qword ptr [rbp-0x48]
	mov	eax, dword ptr [rcx+0x50]
	cmp	eax, 8
	jle	$_248
	mov	rsi, qword ptr [rcx+0x68]
	add	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rbx+0x1C], eax
	jmp	$_249

$_248:	mov	rdx, qword ptr [rbp-0x40]
	sub	dword ptr [rdx+0x50], 40
	sub	dword ptr [rbx+0x1C], 8
$_249:	mov	eax, dword ptr [rbx+0x1C]
	mov	dword ptr [rbp-0x28], eax
	mov	rax, qword ptr [rbp-0x30]
	mov	rcx, qword ptr [rbp-0x38]
	cmp	dword ptr [rax+0x50], 64
	jl	$_250
	mov	rsi, qword ptr [rax+0x68]
	mov	rdx, qword ptr [rsi+0x10]
	mov	rsi, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rsi+0x38]
	mov	dword ptr [rdx+0x3C], eax
$_250:	mov	rsi, qword ptr [rcx+0x68]
	mov	rdx, qword ptr [rsi+0x10]
	lea	rcx, [rdx+0x4]
	mov	qword ptr [rbp-0x58], rcx
	mov	rdi, qword ptr [rbp-0x40]
	mov	eax, dword ptr [rdi+0x50]
	mov	ecx, 40
	cdq
	div	ecx
	mov	rcx, qword ptr [rbp-0x58]
	mov	word ptr [rcx+0x2], ax
	mov	rax, qword ptr [rbp-0x50]
	mov	eax, dword ptr [rax+0x3C]
	mov	dword ptr [rbx+0x28], eax
	mov	rsi, qword ptr [rdi+0x68]
	mov	rax, qword ptr [rsi+0x10]
	mov	qword ptr [rbp-0x60], rax
	mov	rdi, qword ptr [SymTables+0x20+rip]
	mov	ebx, 4294967295
$_251:	test	rdi, rdi
	je	$_264
	mov	rsi, qword ptr [rdi+0x68]
	cmp	dword ptr [rsi+0x48], 6
	je	$_263
	cmp	dword ptr [rdi+0x50], 0
	je	$_263
	cmp	byte ptr [rsi+0x6C], 0
	jz	$_252
	jmp	$_263

$_252:	cmp	dword ptr [rsi+0x4C], ebx
	jz	$_255
	mov	ebx, dword ptr [rsi+0x4C]
	mov	rax, qword ptr [rsi+0x60]
	test	rax, rax
	jnz	$_253
	lea	r8, [rbp-0x168]
	xor	edx, edx
	mov	rcx, rdi
	call	ConvertSectionName@PLT
$_253:	mov	qword ptr [rbp-0x70], rax
	mov	rcx, qword ptr [rbp-0x60]
	mov	r8d, 8
	mov	rdx, qword ptr [rbp-0x70]

	call	tstrncpy@PLT
	mov	rcx, qword ptr [rbp-0x60]
	cmp	dword ptr [rsi+0x48], 3
	jz	$_254
	mov	eax, dword ptr [rsi+0x38]
	mov	dword ptr [rcx+0x14], eax
$_254:	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rcx+0xC], eax
	cmp	dword ptr [rbp-0x24], 0
	jnz	$_255
	mov	eax, dword ptr [rsi+0x38]
	mov	dword ptr [rbp-0x24], eax
$_255:	mov	rcx, rdi
	call	$_171
	mov	rcx, qword ptr [rbp-0x60]
	or	dword ptr [rcx+0x24], eax
	mov	eax, dword ptr [rdi+0x50]
	cmp	dword ptr [rsi+0x48], 3
	jz	$_256
	add	dword ptr [rcx+0x10], eax
$_256:	mov	edx, dword ptr [rsi+0xC]
	sub	edx, dword ptr [rcx+0xC]
	add	eax, edx
	mov	dword ptr [rcx+0x8], eax
	mov	rdx, qword ptr [rdi+0x70]
	test	rdx, rdx
	jz	$_257
	mov	rdx, qword ptr [rdx+0x68]
$_257:	test	rdx, rdx
	jz	$_258
	cmp	dword ptr [rdx+0x4C], ebx
	jz	$_262
$_258:	mov	rax, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rax+0x28]
	dec	eax
	add	dword ptr [rcx+0x10], eax
	not	eax
	and	dword ptr [rcx+0x10], eax
	test	byte ptr [rcx+0x27], 0x20
	jz	$_260
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_259
	mov	eax, dword ptr [rcx+0xC]
	mov	dword ptr [rbp-0x14], eax
$_259:	mov	eax, dword ptr [rcx+0x10]
	add	dword ptr [rbp-0x1C], eax
$_260:	test	byte ptr [rcx+0x24], 0x40
	jz	$_262
	cmp	dword ptr [rbp-0x18], 0
	jnz	$_261
	mov	eax, dword ptr [rcx+0xC]
	mov	dword ptr [rbp-0x18], eax
$_261:	mov	eax, dword ptr [rcx+0x10]
	add	dword ptr [rbp-0x20], eax
$_262:	test	rdx, rdx
	jz	$_263
	cmp	dword ptr [rdx+0x4C], ebx
	jz	$_263
	add	qword ptr [rbp-0x60], 40
$_263:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_251

$_264:
	cmp	qword ptr [ModuleInfo+0xE0+rip], 0
	jz	$_265
	mov	rax, qword ptr [ModuleInfo+0xE0+rip]
	mov	rdx, qword ptr [rax+0x30]
	mov	rsi, qword ptr [rdx+0x68]
	mov	ecx, dword ptr [rsi+0xC]
	add	ecx, dword ptr [rax+0x28]
	mov	rax, qword ptr [rbp-0x50]
	mov	dword ptr [rax+0x28], ecx
	jmp	$_266

$_265:	mov	ecx, 8009
	call	asmerr@PLT
$_266:	mov	rcx, qword ptr [rbp-0x50]
	mov	eax, dword ptr [rcx+0x38]
	dec	eax
	mov	edx, eax
	not	edx
	add	eax, dword ptr [rbp-0x28]
	and	eax, edx
	mov	dword ptr [rbp-0x28], eax
	mov	eax, dword ptr [rbp-0x1C]
	mov	dword ptr [rcx+0x1C], eax
	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rcx+0x2C], eax
	mov	eax, dword ptr [rbp-0x28]
	mov	dword ptr [rcx+0x50], eax
	mov	eax, dword ptr [rbp-0x24]
	mov	dword ptr [rcx+0x54], eax
	lea	rax, [rcx+0x88]
	mov	qword ptr [rbp-0x68], rax
	lea	rcx, [DS000C+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_267
	mov	rsi, qword ptr [rax+0x68]
	mov	rcx, qword ptr [rbp-0x68]
	mov	eax, dword ptr [rax+0x50]
	mov	dword ptr [rcx+0x4], eax
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rcx], eax
$_267:	lea	rcx, [DS002A+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_268
	mov	rdi, rax
	lea	rcx, [DS002B+rip]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x170], rax
	lea	rcx, [DS002C+rip]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x178], rax
	mov	rcx, qword ptr [rbp-0x170]
	mov	rsi, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rsi+0xC]
	add	eax, dword ptr [rcx+0x50]
	mov	rsi, qword ptr [rdi+0x68]
	sub	eax, dword ptr [rsi+0xC]
	mov	rdx, qword ptr [rbp-0x68]
	mov	dword ptr [rdx+0xC], eax
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rdx+0x8], eax
	mov	rcx, qword ptr [rbp-0x178]
	mov	rsi, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rdx+0x60], eax
	mov	eax, dword ptr [rcx+0x50]
	mov	dword ptr [rdx+0x64], eax
$_268:	lea	rcx, [DS0009+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_269
	mov	rsi, qword ptr [rax+0x68]
	mov	rdx, qword ptr [rbp-0x68]
	mov	eax, dword ptr [rax+0x50]
	mov	dword ptr [rdx+0x14], eax
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rdx+0x10], eax
$_269:	lea	rcx, [DS000A+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_270
	mov	rsi, qword ptr [rax+0x68]
	mov	rdx, qword ptr [rbp-0x68]
	mov	eax, dword ptr [rax+0x50]
	mov	dword ptr [rdx+0x2C], eax
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rdx+0x28], eax
$_270:	lea	rcx, [DS002D+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_271
	mov	rsi, qword ptr [rax+0x68]
	mov	rdx, qword ptr [rbp-0x68]
	mov	eax, dword ptr [rax+0x50]
	mov	dword ptr [rdx+0x4C], eax
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rdx+0x48], eax
$_271:	lea	rcx, [DS002E+rip]
	call	SymFind@PLT
	test	rax, rax
	jz	$_272
	mov	rsi, qword ptr [rax+0x68]
	mov	rdx, qword ptr [rbp-0x68]
	mov	eax, dword ptr [rax+0x50]
	mov	dword ptr [rdx+0x1C], eax
	mov	eax, dword ptr [rsi+0xC]
	mov	dword ptr [rdx+0x18], eax
$_272:	mov	rcx, qword ptr [rbp-0x50]
	mov	rax, qword ptr [rcx+0x30]
	cmp	eax, -1
	jnz	$_275
	movabs	rax, 0x140000000
	test	byte ptr [rbp-0xD], 0x20
	jz	$_273
	movabs	rax, 0x180000000
	jmp	$_274

$_273:	test	byte ptr [rcx+0x16], 0x20
	jnz	$_274
	mov	eax, 4194304
$_274:	mov	qword ptr [rcx+0x30], rax
$_275:	mov	rcx, qword ptr [rbp+0x28]
	mov	qword ptr [rcx+0x20], rax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

pe_enddirhook:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	call	$_097
	call	$_128
	cmp	qword ptr [rbx+0x60], 0
	jz	$_276
	call	$_149
$_276:	call	$_108
	xor	eax, eax
	leave
	pop	rbx
	ret

bin_write_module:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	qword ptr [rbp-0x38], 0
	xor	eax, eax
	push	rdi
	push	rcx
	lea	rdi, [rbp-0x70]
	mov	ecx, 48
	rep stosb
	pop	rcx
	pop	rdi
	mov	byte ptr [rbp-0x70], 1
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_277:	test	rdi, rdi
	jz	$_279
	mov	rsi, qword ptr [rdi+0x68]
	mov	dword ptr [rsi+0xC], 0
	cmp	byte ptr [rsi+0x72], 5
	jnz	$_278
	mov	dword ptr [rsi+0x48], 4
$_278:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_277

$_279:
	mov	rbx, qword ptr [rbp+0x28]
	cmp	byte ptr [rbx+0x1B8], 1
	jnz	$_280
	xor	ecx, ecx
	call	$_019
	mov	word ptr [rbp-0x2A], ax
	shl	eax, 2
	movzx	edx, word ptr [rbx+0x1E4]
	add	eax, edx
	movzx	edx, word ptr [rbx+0x1E6]
	dec	edx
	add	eax, edx
	mov	ecx, edx
	not	ecx
	and	eax, ecx
	jmp	$_281

$_280:	xor	eax, eax
$_281:	mov	dword ptr [rbp-0x68], eax
	mov	dword ptr [rbp-0x6C], eax
	test	eax, eax
	jz	$_282
	mov	ecx, eax
	call	LclAlloc@PLT
	mov	qword ptr [rbp-0x40], rax
$_282:	mov	dword ptr [rbp-0x64], -1
	mov	dword ptr [rbp-0x54], 0
	cmp	byte ptr [rbx+0x1B8], 2
	jz	$_283
	cmp	byte ptr [rbx+0x1B8], 3
	jnz	$_285
$_283:	cmp	byte ptr [ModuleInfo+0x1B5+rip], 0
	jnz	$_284
	mov	ecx, 2013
	call	asmerr@PLT
	jmp	$_337

$_284:	lea	rcx, [rbp-0x70]
	call	$_231
	jmp	$_294

$_285:	cmp	byte ptr [rbx+0x1BA], 1
	jnz	$_291
	xor	ebx, ebx
$_286:	cmp	ebx, 6
	jnc	$_290
	mov	rdi, qword ptr [SymTables+0x20+rip]
$_287:	test	rdi, rdi
	jz	$_289
	mov	rsi, qword ptr [rdi+0x68]
	lea	rcx, [dosseg_order+rip]
	mov	eax, dword ptr [rcx+rbx*4]
	cmp	dword ptr [rsi+0x48], eax
	jnz	$_288
	lea	rdx, [rbp-0x70]
	mov	rcx, rdi
	call	$_001
$_288:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_287

$_289:	inc	ebx
	jmp	$_286

$_290:	xor	ecx, ecx
	call	SortSegments@PLT
	mov	rbx, qword ptr [rbp+0x28]
	jmp	$_294

$_291:	cmp	byte ptr [rbx+0x1BA], 2
	jnz	$_292
	mov	ecx, 1
	call	SortSegments@PLT
$_292:	mov	rdi, qword ptr [SymTables+0x20+rip]
$_293:	test	rdi, rdi
	jz	$_294
	lea	rdx, [rbp-0x70]
	mov	rcx, rdi
	call	$_001
	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_293

$_294:	mov	rdi, qword ptr [SymTables+0x20+rip]
$_295:	test	rdi, rdi
	jz	$_297
	lea	rdx, [rbp-0x70]
	mov	rcx, rdi
	call	$_047
	mov	rsi, qword ptr [rdi+0x68]
	cmp	qword ptr [rbp-0x38], 0
	jnz	$_296
	cmp	byte ptr [rsi+0x72], 5
	jnz	$_296
	mov	qword ptr [rbp-0x38], rdi
$_296:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_295

$_297:	cmp	dword ptr [rbx], 0
	jz	$_298
	mov	rax, -1
	jmp	$_337

$_298:	cmp	byte ptr [rbx+0x1B8], 0
	jnz	$_300
	cmp	qword ptr [rbx+0xE0], 0
	jz	$_300
	mov	rax, qword ptr [rbx+0xE0]
	cmp	dword ptr [rbp-0x64], -1
	jz	$_299
	mov	rax, qword ptr [rax+0x30]
	cmp	qword ptr [rbp-0x60], rax
	jz	$_300
$_299:	mov	ecx, 3003
	call	asmerr@PLT
	jmp	$_337

$_300:	xor	ecx, ecx
	call	$_035
	mov	dword ptr [rbp-0x10], eax
	cmp	byte ptr [rbx+0x1B8], 1
	jne	$_313
	mov	rdi, qword ptr [rbp-0x40]
	mov	word ptr [rdi], 23117
	mov	ecx, 512
	mov	eax, dword ptr [rbp-0x10]
	cdq
	div	ecx
	mov	word ptr [rdi+0x2], dx
	test	edx, edx
	jz	$_301
	inc	eax
$_301:	mov	word ptr [rdi+0x4], ax
	mov	ax, word ptr [rbp-0x2A]
	mov	word ptr [rdi+0x6], ax
	mov	eax, dword ptr [rbp-0x68]
	shr	eax, 4
	mov	word ptr [rdi+0x8], ax
	mov	ecx, 1
	call	$_035
	sub	eax, dword ptr [rbp-0x10]
	mov	dword ptr [rbp-0x1C], eax
	mov	edx, eax
	shr	eax, 4
	and	edx, 0x0F
	jz	$_302
	inc	eax
$_302:	mov	word ptr [rdi+0xA], ax
	cmp	ax, word ptr [rbx+0x1E8]
	jnc	$_303
	mov	ax, word ptr [rbx+0x1E8]
	mov	word ptr [rdi+0xA], ax
$_303:	mov	ax, word ptr [rbx+0x1EA]
	mov	word ptr [rdi+0xC], ax
	cmp	ax, word ptr [rdi+0xA]
	jnc	$_304
	mov	ax, word ptr [rdi+0xA]
	mov	word ptr [rdi+0xC], ax
$_304:	cmp	qword ptr [rbp-0x38], 0
	jz	$_307
	mov	rcx, qword ptr [rbp-0x38]
	mov	rsi, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rsi+0xC]
	cmp	qword ptr [rsi], 0
	jz	$_305
	mov	rdx, qword ptr [rsi]
	add	eax, dword ptr [rdx+0x28]
$_305:	xor	edx, edx
	test	eax, 0xF
	jz	$_306
	inc	edx
$_306:	shr	eax, 4
	add	eax, edx
	mov	word ptr [rdi+0xE], ax
	mov	eax, dword ptr [rcx+0x50]
	mov	word ptr [rdi+0x10], ax
	jmp	$_308

$_307:	mov	ecx, 8010
	call	asmerr@PLT
$_308:
	mov	word ptr [rdi+0x12], 0
	cmp	qword ptr [rbx+0xE0], 0
	jz	$_311
	mov	rcx, qword ptr [rbx+0xE0]
	mov	rdx, qword ptr [rcx+0x30]
	mov	rsi, qword ptr [rdx+0x68]
	cmp	qword ptr [rsi], 0
	jz	$_309
	mov	rax, qword ptr [rsi]
	mov	eax, dword ptr [rax+0x28]
	mov	edx, eax
	shr	edx, 4
	and	eax, 0x0F
	add	eax, dword ptr [rsi+0xC]
	add	eax, dword ptr [rcx+0x28]
	mov	word ptr [rdi+0x14], ax
	mov	word ptr [rdi+0x16], dx
	jmp	$_310

$_309:	mov	eax, dword ptr [rsi+0xC]
	mov	edx, eax
	shr	edx, 4
	and	eax, 0x0F
	add	eax, dword ptr [rcx+0x28]
	mov	word ptr [rdi+0x14], ax
	mov	word ptr [rdi+0x16], dx
$_310:	jmp	$_312

$_311:	mov	ecx, 8009
	call	asmerr@PLT
$_312:	mov	ax, word ptr [rbx+0x1E4]
	mov	word ptr [rdi+0x18], ax
	add	rax, qword ptr [rbp-0x40]
	mov	rcx, rax
	call	$_019
$_313:	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_314
	mov	edx, 2
	xor	esi, esi
	mov	rdi, qword ptr [ModuleInfo+0x80+rip]
	call	fseek@PLT
	call	LstNL@PLT
	call	LstNL@PLT
	lea	rcx, [DS002F+rip]
	call	LstPrintf@PLT
	call	LstNL@PLT
	call	LstNL@PLT
	lea	rcx, [DS0030+rip]
	call	LstPrintf@PLT
	call	LstNL@PLT
	lea	rcx, [DS0031+rip]
	call	LstPrintf@PLT
	call	LstNL@PLT
$_314:	cmp	dword ptr [rbp-0x68], 0
	jz	$_316
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, dword ptr [rbp-0x68]
	mov	esi, 1
	mov	rdi, qword ptr [rbp-0x40]
	call	fwrite@PLT
	cmp	eax, dword ptr [rbp-0x68]
	jz	$_315
	call	WriteError@PLT
$_315:	mov	qword ptr [rsp+0x28], 0
	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [rsp+0x20], eax
	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, [DS0033+rip]
	lea	rcx, [DS0032+rip]
	call	LstPrintf@PLT
	call	LstNL@PLT
$_316:	mov	rdi, qword ptr [SymTables+0x20+rip]
	mov	dword ptr [rbp-0x18], 1
$_317:	test	rdi, rdi
	je	$_330
	mov	rsi, qword ptr [rdi+0x68]
	cmp	dword ptr [rsi+0x48], 5
	je	$_329
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 2
	jz	$_318
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 3
	jnz	$_321
$_318:	cmp	dword ptr [rsi+0x48], 3
	jz	$_319
	cmp	byte ptr [rsi+0x6C], 0
	jz	$_321
$_319:	xor	eax, eax
	cmp	byte ptr [rsi+0x6C], 0
	jz	$_320
	jmp	$_329

$_320:	jmp	$_322

$_321:	mov	eax, dword ptr [rdi+0x50]
	cmp	dword ptr [rbp-0x18], 0
	jz	$_322
	cmp	byte ptr [rbx+0x1B8], 0
	jnz	$_322
	sub	eax, dword ptr [rsi+0x8]
$_322:	mov	dword ptr [rbp-0xC], eax
	cmp	dword ptr [rbp-0x18], 0
	jnz	$_323
	mov	eax, dword ptr [rdi+0x50]
$_323:	mov	dword ptr [rbp-0x30], eax
	cmp	dword ptr [rsi+0x18], 0
	jnz	$_326
	mov	rdx, qword ptr [rdi+0x70]
$_324:	test	rdx, rdx
	jz	$_325
	mov	rcx, qword ptr [rdx+0x68]
	cmp	dword ptr [rcx+0x18], 0
	jnz	$_325
	mov	rdx, qword ptr [rdx+0x70]
	jmp	$_324

$_325:	test	rdx, rdx
	jnz	$_326
	mov	dword ptr [rbp-0xC], edx
$_326:	mov	ecx, dword ptr [rsi+0xC]
	cmp	dword ptr [rbp-0x18], 0
	jz	$_327
	add	ecx, dword ptr [rsi+0x8]
$_327:	mov	eax, dword ptr [rbp-0x30]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, ecx
	mov	r8d, dword ptr [rsi+0x38]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0032+rip]
	call	LstPrintf@PLT
	call	LstNL@PLT
	cmp	dword ptr [rbp-0xC], 0
	jz	$_328
	cmp	qword ptr [rsi+0x10], 0
	jz	$_328
	mov	qword ptr [rbp-0x78], rdi
	mov	qword ptr [rbp-0x80], rsi
	xor	edx, edx
	mov	esi, dword ptr [rsi+0x38]
	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	fseek@PLT
	mov	rdi, qword ptr [rbp-0x80]
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, dword ptr [rbp-0xC]
	mov	esi, 1
	mov	rdi, qword ptr [rdi+0x10]
	call	fwrite@PLT
	mov	rsi, qword ptr [rbp-0x80]
	mov	rdi, qword ptr [rbp-0x78]
	cmp	eax, dword ptr [rbp-0xC]
	jz	$_328
	call	WriteError@PLT
$_328:	mov	dword ptr [rbp-0x18], 0
$_329:	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_317

$_330:	cmp	byte ptr [rbx+0x1B8], 2
	jz	$_331
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 3
	jnz	$_332
$_331:	mov	rdi, qword ptr [ModuleInfo+0x78+rip]
	call	ftell@PLT
	mov	dword ptr [rbp-0xC], eax
	mov	eax, dword ptr [rbp-0x48]
	dec	eax
	test	dword ptr [rbp-0xC], eax
	jz	$_332
	lea	ecx, [rax+0x1]
	and	eax, dword ptr [rbp-0xC]
	sub	ecx, eax
	mov	dword ptr [rbp-0xC], ecx
	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
	mov	r8d, dword ptr [rbp-0xC]
	xor	edx, edx
	mov	rcx, rax
	call	tmemset@PLT
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, dword ptr [rbp-0xC]
	mov	esi, 1
	mov	rdi, rax
	call	fwrite@PLT
$_332:	lea	rcx, [DS0031+rip]
	call	LstPrintf@PLT
	call	LstNL@PLT
	cmp	byte ptr [rbx+0x1B8], 1
	jnz	$_333
	mov	eax, dword ptr [rbp-0x10]
	sub	eax, dword ptr [rbp-0x68]
	add	dword ptr [rbp-0x1C], eax
	jmp	$_336

$_333:	cmp	byte ptr [rbx+0x1B8], 2
	jz	$_334
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 3
	jnz	$_335
$_334:	mov	eax, dword ptr [rbp-0x54]
	mov	dword ptr [rbp-0x1C], eax
	jmp	$_336

$_335:	mov	ecx, 1
	call	$_035
	mov	dword ptr [rbp-0x1C], eax
$_336:	mov	r9d, dword ptr [rbp-0x1C]
	mov	r8d, dword ptr [rbp-0x10]
	lea	rdx, [DS0035+rip]
	lea	rcx, [DS0034+rip]
	call	LstPrintf@PLT
	call	LstNL@PLT
	xor	eax, eax
$_337:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

bin_check_external:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, qword ptr [SymTables+0x10+rip]
$_338:	test	rdx, rdx
	jz	$_341
	test	byte ptr [rdx+0x3B], 0x02
	jz	$_339
	test	byte ptr [rdx+0x14], 0x01
	jz	$_340
$_339:	test	byte ptr [rdx+0x16], 0x10
	jnz	$_340
	mov	rdx, qword ptr [rdx+0x8]
	mov	ecx, 2014
	call	asmerr@PLT
	jmp	$_342
$_340:	mov	rdx, qword ptr [rdx+0x70]
	jmp	$_338
$_341:	xor	eax, eax
$_342:	leave
	ret

bin_init:
	lea	rax, [bin_write_module+rip]
	mov	qword ptr [rcx+0x158], rax
	lea	rax, [bin_check_external+rip]
	mov	qword ptr [rcx+0x168], rax
	mov	al, byte ptr [rcx+0x1B8]
	jmp	$_344
$_343:	lea	rax, [pe_enddirhook+rip]
	mov	qword ptr [rcx+0x160], rax
	jmp	$_345
$_344:	cmp	al, 2
	jz	$_343
	cmp	al, 3
	jz	$_343
$_345:	ret


.SECTION .data
	.ALIGN	16

dosseg_order:
	.byte  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte  0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

flat_order:
	.byte  0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte  0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte  0x03, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

pe64def:
	.byte  0x50, 0x45, 0x00, 0x00, 0x64, 0x86, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x2F, 0x01
	.byte  0x0B, 0x02, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
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
	.byte  0x2E, 0x68, 0x64, 0x72, 0x24, 0x31, 0x00

DS0001:
	.byte  0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x64
	.byte  0x6F, 0x74, 0x6E, 0x61, 0x6D, 0x65, 0x0A, 0x49
	.byte  0x4D, 0x41, 0x47, 0x45, 0x5F, 0x44, 0x4F, 0x53
	.byte  0x5F, 0x48, 0x45, 0x41, 0x44, 0x45, 0x52, 0x20
	.byte  0x53, 0x54, 0x52, 0x55, 0x43, 0x0A, 0x65, 0x5F
	.byte  0x6D, 0x61, 0x67, 0x69, 0x63, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x64, 0x77
	.byte  0x20, 0x3F, 0x0A, 0x65, 0x5F, 0x63, 0x62, 0x6C
	.byte  0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x64, 0x77, 0x20, 0x3F, 0x0A
	.byte  0x65, 0x5F, 0x63, 0x70, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x64, 0x77, 0x20, 0x3F, 0x0A, 0x65, 0x5F, 0x63
	.byte  0x72, 0x6C, 0x63, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x64, 0x77, 0x20
	.byte  0x3F, 0x0A, 0x65, 0x5F, 0x63, 0x70, 0x61, 0x72
	.byte  0x68, 0x64, 0x72, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x64, 0x77, 0x20, 0x3F, 0x0A, 0x65
	.byte  0x5F, 0x6D, 0x69, 0x6E, 0x61, 0x6C, 0x6C, 0x6F
	.byte  0x63, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x64
	.byte  0x77, 0x20, 0x3F, 0x0A, 0x65, 0x5F, 0x6D, 0x61
	.byte  0x78, 0x61, 0x6C, 0x6C, 0x6F, 0x63, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x64, 0x77, 0x20, 0x3F
	.byte  0x0A, 0x65, 0x5F, 0x73, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x64, 0x77, 0x20, 0x3F, 0x0A, 0x65, 0x5F
	.byte  0x73, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x64, 0x77
	.byte  0x20, 0x3F, 0x0A, 0x65, 0x5F, 0x63, 0x73, 0x75
	.byte  0x6D, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x64, 0x77, 0x20, 0x3F, 0x0A
	.byte  0x65, 0x5F, 0x69, 0x70, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x64, 0x77, 0x20, 0x3F, 0x0A, 0x65, 0x5F, 0x63
	.byte  0x73, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x64, 0x77, 0x20
	.byte  0x3F, 0x0A, 0x65, 0x5F, 0x6C, 0x66, 0x61, 0x72
	.byte  0x6C, 0x63, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x64, 0x77, 0x20, 0x3F, 0x0A, 0x65
	.byte  0x5F, 0x6F, 0x76, 0x6E, 0x6F, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x64
	.byte  0x77, 0x20, 0x3F, 0x0A, 0x65, 0x5F, 0x72, 0x65
	.byte  0x73, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x64, 0x77, 0x20, 0x34
	.byte  0x20, 0x64, 0x75, 0x70, 0x28, 0x3F, 0x29, 0x0A
	.byte  0x65, 0x5F, 0x6F, 0x65, 0x6D, 0x69, 0x64, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x64, 0x77, 0x20, 0x3F, 0x0A, 0x65, 0x5F, 0x6F
	.byte  0x65, 0x6D, 0x69, 0x6E, 0x66, 0x6F, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x64, 0x77, 0x20
	.byte  0x3F, 0x0A, 0x65, 0x5F, 0x72, 0x65, 0x73, 0x32
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x64, 0x77, 0x20, 0x31, 0x30, 0x20
	.byte  0x64, 0x75, 0x70, 0x28, 0x3F, 0x29, 0x0A, 0x65
	.byte  0x5F, 0x6C, 0x66, 0x61, 0x6E, 0x65, 0x77, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x64
	.byte  0x64, 0x20, 0x3F, 0x0A, 0x49, 0x4D, 0x41, 0x47
	.byte  0x45, 0x5F, 0x44, 0x4F, 0x53, 0x5F, 0x48, 0x45
	.byte  0x41, 0x44, 0x45, 0x52, 0x20, 0x45, 0x4E, 0x44
	.byte  0x53, 0x0A, 0x25, 0x73, 0x31, 0x20, 0x73, 0x65
	.byte  0x67, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x55, 0x53
	.byte  0x45, 0x31, 0x36, 0x20, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x25, 0x73, 0x0A, 0x49, 0x4D, 0x41, 0x47
	.byte  0x45, 0x5F, 0x44, 0x4F, 0x53, 0x5F, 0x48, 0x45
	.byte  0x41, 0x44, 0x45, 0x52, 0x20, 0x7B, 0x20, 0x30
	.byte  0x78, 0x35, 0x41, 0x34, 0x44, 0x2C, 0x20, 0x30
	.byte  0x78, 0x36, 0x38, 0x2C, 0x20, 0x31, 0x2C, 0x20
	.byte  0x30, 0x2C, 0x20, 0x34, 0x2C, 0x20, 0x30, 0x2C
	.byte  0x20, 0x2D, 0x31, 0x2C, 0x20, 0x30, 0x2C, 0x20
	.byte  0x30, 0x78, 0x42, 0x38, 0x2C, 0x20, 0x30, 0x2C
	.byte  0x20, 0x30, 0x2C, 0x20, 0x30, 0x2C, 0x20, 0x30
	.byte  0x78, 0x34, 0x30, 0x20, 0x7D, 0x0A, 0x70, 0x75
	.byte  0x73, 0x68, 0x20, 0x63, 0x73, 0x0A, 0x70, 0x6F
	.byte  0x70, 0x20, 0x64, 0x73, 0x0A, 0x6D, 0x6F, 0x76
	.byte  0x20, 0x64, 0x78, 0x2C, 0x40, 0x46, 0x2D, 0x34
	.byte  0x30, 0x68, 0x0A, 0x6D, 0x6F, 0x76, 0x20, 0x61
	.byte  0x68, 0x2C, 0x39, 0x0A, 0x69, 0x6E, 0x74, 0x20
	.byte  0x32, 0x31, 0x68, 0x0A, 0x6D, 0x6F, 0x76, 0x20
	.byte  0x61, 0x78, 0x2C, 0x34, 0x43, 0x30, 0x31, 0x68
	.byte  0x0A, 0x69, 0x6E, 0x74, 0x20, 0x32, 0x31, 0x68
	.byte  0x0A, 0x40, 0x40, 0x3A, 0x0A, 0x64, 0x62, 0x20
	.byte  0x27, 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73
	.byte  0x20, 0x61, 0x20, 0x50, 0x45, 0x20, 0x65, 0x78
	.byte  0x65, 0x63, 0x75, 0x74, 0x61, 0x62, 0x6C, 0x65
	.byte  0x27, 0x2C, 0x30, 0x44, 0x68, 0x2C, 0x30, 0x41
	.byte  0x68, 0x2C, 0x27, 0x24, 0x27, 0x0A, 0x25, 0x73
	.byte  0x31, 0x20, 0x65, 0x6E, 0x64, 0x73, 0x00

DS0002:
	.byte  0x2E, 0x68, 0x64, 0x72, 0x24, 0x00

DS0003:
	.byte  0x72, 0x65, 0x61, 0x64, 0x20, 0x70, 0x75, 0x62
	.byte  0x6C, 0x69, 0x63, 0x20, 0x27, 0x48, 0x44, 0x52
	.byte  0x27, 0x00

DS0004:
	.byte  0x2E, 0x68, 0x64, 0x72, 0x24, 0x32, 0x00

DS0005:
	.byte  0x48, 0x44, 0x52, 0x00

DS0006:
	.byte  0x40, 0x70, 0x65, 0x5F, 0x66, 0x69, 0x6C, 0x65
	.byte  0x5F, 0x66, 0x6C, 0x61, 0x67, 0x73, 0x00

DS0007:
	.byte  0x2E, 0x68, 0x64, 0x72, 0x24, 0x33, 0x00

DS0008:
	.byte  0x43, 0x4F, 0x4E, 0x53, 0x54, 0x00

DS0009:
	.byte  0x2E, 0x72, 0x73, 0x72, 0x63, 0x00

DS000A:
	.byte  0x2E, 0x72, 0x65, 0x6C, 0x6F, 0x63, 0x00

DS000B:
	.byte  0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x64
	.byte  0x6F, 0x74, 0x6E, 0x61, 0x6D, 0x65, 0x0A, 0x25
	.byte  0x73, 0x20, 0x73, 0x65, 0x67, 0x6D, 0x65, 0x6E
	.byte  0x74, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x25, 0x73, 0x0A, 0x44, 0x44, 0x20, 0x30, 0x2C
	.byte  0x20, 0x30, 0x25, 0x78, 0x68, 0x2C, 0x20, 0x30
	.byte  0x2C, 0x20, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x72
	.byte  0x65, 0x6C, 0x20, 0x40, 0x25, 0x73, 0x5F, 0x6E
	.byte  0x61, 0x6D, 0x65, 0x2C, 0x20, 0x25, 0x75, 0x2C
	.byte  0x20, 0x25, 0x75, 0x2C, 0x20, 0x25, 0x75, 0x2C
	.byte  0x20, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x72, 0x65
	.byte  0x6C, 0x20, 0x40, 0x25, 0x73, 0x5F, 0x66, 0x75
	.byte  0x6E, 0x63, 0x2C, 0x20, 0x69, 0x6D, 0x61, 0x67
	.byte  0x65, 0x72, 0x65, 0x6C, 0x20, 0x40, 0x25, 0x73
	.byte  0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x73, 0x2C, 0x20
	.byte  0x69, 0x6D, 0x61, 0x67, 0x65, 0x72, 0x65, 0x6C
	.byte  0x20, 0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D
	.byte  0x65, 0x6F, 0x72, 0x64, 0x00

DS000C:
	.byte  0x2E, 0x65, 0x64, 0x61, 0x74, 0x61, 0x00

DS000D:
	.byte  0x46, 0x4C, 0x41, 0x54, 0x20, 0x72, 0x65, 0x61
	.byte  0x64, 0x20, 0x70, 0x75, 0x62, 0x6C, 0x69, 0x63
	.byte  0x20, 0x61, 0x6C, 0x69, 0x61, 0x73, 0x28, 0x27
	.byte  0x2E, 0x72, 0x64, 0x61, 0x74, 0x61, 0x27, 0x29
	.byte  0x20, 0x27, 0x44, 0x41, 0x54, 0x41, 0x27, 0x00

DS000E:
	.byte  0x40, 0x25, 0x73, 0x5F, 0x66, 0x75, 0x6E, 0x63
	.byte  0x20, 0x6C, 0x61, 0x62, 0x65, 0x6C, 0x20, 0x64
	.byte  0x77, 0x6F, 0x72, 0x64, 0x00

DS000F:
	.byte  0x64, 0x64, 0x20, 0x69, 0x6D, 0x61, 0x67, 0x65
	.byte  0x72, 0x65, 0x6C, 0x20, 0x25, 0x73, 0x00

DS0010:
	.byte  0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D, 0x65
	.byte  0x73, 0x20, 0x6C, 0x61, 0x62, 0x65, 0x6C, 0x20
	.byte  0x64, 0x77, 0x6F, 0x72, 0x64, 0x00

DS0011:
	.byte  0x64, 0x64, 0x20, 0x69, 0x6D, 0x61, 0x67, 0x65
	.byte  0x72, 0x65, 0x6C, 0x20, 0x40, 0x25, 0x73, 0x00

DS0012:
	.byte  0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D, 0x65
	.byte  0x6F, 0x72, 0x64, 0x20, 0x6C, 0x61, 0x62, 0x65
	.byte  0x6C, 0x20, 0x77, 0x6F, 0x72, 0x64, 0x00

DS0013:
	.byte  0x64, 0x77, 0x20, 0x25, 0x75, 0x00

DS0014:
	.byte  0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D, 0x65
	.byte  0x20, 0x64, 0x62, 0x20, 0x27, 0x25, 0x73, 0x27
	.byte  0x2C, 0x30, 0x00

DS0015:
	.byte  0x40, 0x25, 0x73, 0x20, 0x64, 0x62, 0x20, 0x27
	.byte  0x25, 0x73, 0x27, 0x2C, 0x30, 0x00

DS0016:
	.byte  0x25, 0x73, 0x20, 0x65, 0x6E, 0x64, 0x73, 0x00

DS0017:
	.byte  0x41, 0x4C, 0x49, 0x47, 0x4E, 0x28, 0x38, 0x29
	.byte  0x00

DS0018:
	.byte  0x40, 0x4C, 0x50, 0x50, 0x52, 0x4F, 0x43, 0x20
	.byte  0x74, 0x79, 0x70, 0x65, 0x64, 0x65, 0x66, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x70, 0x72, 0x6F, 0x63
	.byte  0x0A, 0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20
	.byte  0x64, 0x6F, 0x74, 0x6E, 0x61, 0x6D, 0x65, 0x00

DS0019:
	.byte  0x2E, 0x69, 0x64, 0x61, 0x74, 0x61, 0x24, 0x00

DS001A:
	.byte  0x25, 0x73, 0x32, 0x20, 0x73, 0x65, 0x67, 0x6D
	.byte  0x65, 0x6E, 0x74, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x25, 0x73, 0x0A, 0x64, 0x64, 0x20
	.byte  0x69, 0x6D, 0x61, 0x67, 0x65, 0x72, 0x65, 0x6C
	.byte  0x20, 0x40, 0x25, 0x73, 0x5F, 0x69, 0x6C, 0x74
	.byte  0x2C, 0x20, 0x30, 0x2C, 0x20, 0x30, 0x2C, 0x20
	.byte  0x69, 0x6D, 0x61, 0x67, 0x65, 0x72, 0x65, 0x6C
	.byte  0x20, 0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D
	.byte  0x65, 0x2C, 0x20, 0x69, 0x6D, 0x61, 0x67, 0x65
	.byte  0x72, 0x65, 0x6C, 0x20, 0x40, 0x25, 0x73, 0x5F
	.byte  0x69, 0x61, 0x74, 0x0A, 0x25, 0x73, 0x32, 0x20
	.byte  0x65, 0x6E, 0x64, 0x73, 0x0A, 0x25, 0x73, 0x34
	.byte  0x20, 0x73, 0x65, 0x67, 0x6D, 0x65, 0x6E, 0x74
	.byte  0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x0A, 0x40
	.byte  0x25, 0x73, 0x5F, 0x69, 0x6C, 0x74, 0x20, 0x6C
	.byte  0x61, 0x62, 0x65, 0x6C, 0x20, 0x25, 0x72, 0x00

DS001B:
	.byte  0x40, 0x4C, 0x50, 0x50, 0x52, 0x4F, 0x43, 0x20
	.byte  0x69, 0x6D, 0x61, 0x67, 0x65, 0x72, 0x65, 0x6C
	.byte  0x20, 0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D
	.byte  0x65, 0x00

DS001C:
	.byte  0x40, 0x4C, 0x50, 0x50, 0x52, 0x4F, 0x43, 0x20
	.byte  0x30, 0x0A, 0x25, 0x73, 0x34, 0x20, 0x65, 0x6E
	.byte  0x64, 0x73, 0x0A, 0x25, 0x73, 0x35, 0x20, 0x73
	.byte  0x65, 0x67, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x25
	.byte  0x73, 0x20, 0x25, 0x73, 0x0A, 0x40, 0x25, 0x73
	.byte  0x5F, 0x69, 0x61, 0x74, 0x20, 0x6C, 0x61, 0x62
	.byte  0x65, 0x6C, 0x20, 0x25, 0x72, 0x00

DS001D:
	.byte  0x25, 0x73, 0x25, 0x73, 0x20, 0x40, 0x4C, 0x50
	.byte  0x50, 0x52, 0x4F, 0x43, 0x20, 0x69, 0x6D, 0x61
	.byte  0x67, 0x65, 0x72, 0x65, 0x6C, 0x20, 0x40, 0x25
	.byte  0x73, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x00

DS001E:
	.byte  0x40, 0x4C, 0x50, 0x50, 0x52, 0x4F, 0x43, 0x20
	.byte  0x30, 0x0A, 0x25, 0x73, 0x35, 0x20, 0x65, 0x6E
	.byte  0x64, 0x73, 0x0A, 0x25, 0x73, 0x36, 0x20, 0x73
	.byte  0x65, 0x67, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x25, 0x73, 0x00

DS001F:
	.byte  0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D, 0x65
	.byte  0x20, 0x64, 0x77, 0x20, 0x30, 0x0A, 0x64, 0x62
	.byte  0x20, 0x27, 0x25, 0x73, 0x27, 0x2C, 0x30, 0x0A
	.byte  0x65, 0x76, 0x65, 0x6E, 0x00

DS0020:
	.byte  0x40, 0x25, 0x73, 0x5F, 0x6E, 0x61, 0x6D, 0x65
	.byte  0x20, 0x64, 0x62, 0x20, 0x27, 0x25, 0x73, 0x27
	.byte  0x2C, 0x30, 0x0A, 0x65, 0x76, 0x65, 0x6E, 0x0A
	.byte  0x25, 0x73, 0x36, 0x20, 0x65, 0x6E, 0x64, 0x73
	.byte  0x00

DS0021:
	.byte  0x25, 0x73, 0x33, 0x20, 0x73, 0x65, 0x67, 0x6D
	.byte  0x65, 0x6E, 0x74, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x25, 0x73, 0x0A, 0x44, 0x44, 0x20
	.byte  0x30, 0x2C, 0x20, 0x30, 0x2C, 0x20, 0x30, 0x2C
	.byte  0x20, 0x30, 0x2C, 0x20, 0x30, 0x0A, 0x25, 0x73
	.byte  0x33, 0x20, 0x65, 0x6E, 0x64, 0x73, 0x00

DS0022:
	.byte  0x65, 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73
	.byte  0x61, 0x77, 0x61, 0x72, 0x65, 0x00

DS0023:
	.byte  0x3A, 0x6E, 0x6F, 0x00

DS0024:
	.byte  0x79, 0x73, 0x74, 0x65, 0x6D, 0x3A, 0x00

DS0025:
	.byte  0x77, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73, 0x00

DS0026:
	.byte  0x63, 0x6F, 0x6E, 0x73, 0x6F, 0x6C, 0x65, 0x00

DS0027:
	.byte  0x6E, 0x61, 0x74, 0x69, 0x76, 0x65, 0x00

DS0028:
	.byte  0x2E, 0x64, 0x72, 0x65, 0x63, 0x74, 0x76, 0x65
	.byte  0x00

DS0029:
	.byte  0x52, 0x45, 0x4C, 0x4F, 0x43, 0x00

DS002A:
	.byte  0x2E, 0x69, 0x64, 0x61, 0x74, 0x61, 0x24, 0x32
	.byte  0x00

DS002B:
	.byte  0x2E, 0x69, 0x64, 0x61, 0x74, 0x61, 0x24, 0x33
	.byte  0x00

DS002C:
	.byte  0x2E, 0x69, 0x64, 0x61, 0x74, 0x61, 0x24, 0x35
	.byte  0x00

DS002D:
	.byte  0x2E, 0x74, 0x6C, 0x73, 0x00

DS002E:
	.byte  0x2E, 0x70, 0x64, 0x61, 0x74, 0x61, 0x00

DS002F:
	.byte  0x42, 0x69, 0x6E, 0x61, 0x72, 0x79, 0x20, 0x4D
	.byte  0x61, 0x70, 0x3A, 0x00

DS0030:
	.byte  0x53, 0x65, 0x67, 0x6D, 0x65, 0x6E, 0x74, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x50, 0x6F, 0x73, 0x28, 0x66, 0x69, 0x6C
	.byte  0x65, 0x29, 0x20, 0x20, 0x20, 0x20, 0x20, 0x52
	.byte  0x56, 0x41, 0x20, 0x20, 0x53, 0x69, 0x7A, 0x65
	.byte  0x28, 0x66, 0x69, 0x6C, 0x29, 0x20, 0x53, 0x69
	.byte  0x7A, 0x65, 0x28, 0x6D, 0x65, 0x6D, 0x29, 0x00

DS0031:
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D
	.byte  0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x00

DS0032:
	.byte  0x25, 0x2D, 0x32, 0x34, 0x73, 0x20, 0x25, 0x38
	.byte  0x58, 0x20, 0x25, 0x38, 0x58, 0x20, 0x25, 0x39
	.byte  0x58, 0x20, 0x25, 0x39, 0x58, 0x00

DS0033:
	.byte  0x3C, 0x68, 0x65, 0x61, 0x64, 0x65, 0x72, 0x3E
	.byte  0x00

DS0034:
	.byte  0x25, 0x2D, 0x34, 0x32, 0x73, 0x20, 0x25, 0x39
	.byte  0x58, 0x20, 0x25, 0x39, 0x58, 0x00

DS0035:
	.byte  0x20, 0x00


.att_syntax prefix
