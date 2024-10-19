
.intel_syntax noprefix

.global TypesInit
.global CreateTypeSymbol
.global SearchNameInStruct
.global StructDirective
.global EndstructDirective
.global CreateStructField
.global AlignInStruct
.global UpdateStructSize
.global SetStructCurrentOffset
.global GetQualifiedType
.global CreateType
.global TypedefDirective
.global RecordDirective
.global CurrStruct

.extern LstWrite
.extern EvalOperand
.extern CreateProc
.extern ParseProc
.extern sym_remove_table
.extern SizeFromMemtype
.extern SpecialTable
.extern SymTables
.extern LclDup
.extern LclAlloc
.extern tstricmp
.extern tstrcmp
.extern tstrlen
.extern myltoa
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass
.extern SymCmpFunc
.extern SymFind
.extern SymLookup
.extern SymAddGlobal
.extern SymCreate
.extern SymFree
.extern SymAlloc


.SECTION .text
	.ALIGN	16

TypesInit:
	sub	rsp, 8
	mov	qword ptr [CurrStruct+rip], 0
	mov	qword ptr [redef_struct+rip], 0
	add	rsp, 8
	ret

CreateTypeSymbol:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	test	rsi, rsi
	jz	$_001
	mov	rdx, rsi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	jmp	$_004

$_001:	cmp	dword ptr [rbp+0x30], 0
	jz	$_002
	mov	rcx, qword ptr [rbp+0x28]
	call	SymCreate@PLT
	jmp	$_003

$_002:	mov	rcx, qword ptr [rbp+0x28]
	call	SymAlloc@PLT
$_003:	mov	rsi, rax
$_004:	test	rsi, rsi
	jz	$_005
	mov	byte ptr [rsi+0x18], 7
	mov	word ptr [rsi+0x5A], 0
	mov	ecx, 24
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	qword ptr [rsi+0x68], rdi
	mov	qword ptr [rdi], 0
	mov	qword ptr [rdi+0x8], 0
	mov	byte ptr [rdi+0x10], 0
	mov	byte ptr [rdi+0x11], 0
$_005:	mov	rax, rsi
	leave
	pop	rdi
	pop	rsi
	ret

SearchNameInStruct:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rcx, qword ptr [rbp+0x30]
	call	tstrlen@PLT
	mov	edi, eax
	xor	esi, esi
	mov	rcx, qword ptr [rbp+0x28]
	mov	rdx, qword ptr [rcx+0x68]
	mov	rbx, qword ptr [rdx]
	cmp	dword ptr [rbp+0x40], 32
	jl	$_006
	mov	ecx, 1007
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_016

$_006:	inc	dword ptr [rbp+0x40]
$_007:	test	rbx, rbx
	je	$_015
	mov	rax, qword ptr [rbx+0x8]
	cmp	byte ptr [rax], 0
	jnz	$_013
	cmp	byte ptr [rbx+0x18], 7
	jnz	$_010
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rbx
	call	SearchNameInStruct
	test	rax, rax
	jz	$_009
	mov	rsi, rax
	mov	rcx, qword ptr [rbp+0x38]
	test	rcx, rcx
	jz	$_008
	mov	eax, dword ptr [rbx+0x28]
	add	dword ptr [rcx], eax
$_008:	jmp	$_015

$_009:	jmp	$_012

$_010:	cmp	byte ptr [rbx+0x19], -60
	jnz	$_012
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbx+0x20]
	call	SearchNameInStruct
	test	rax, rax
	jz	$_012
	mov	rsi, rax
	mov	rcx, qword ptr [rbp+0x38]
	test	rcx, rcx
	jz	$_011
	mov	eax, dword ptr [rbx+0x28]
	add	dword ptr [rcx], eax
$_011:	jmp	$_015

$_012:	jmp	$_014

$_013:	cmp	edi, dword ptr [rbx+0x10]
	jnz	$_014
	mov	r8d, edi
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, qword ptr [rbp+0x30]
	call	qword ptr [SymCmpFunc+rip]
	test	rax, rax
	jnz	$_014
	mov	rsi, rbx
	jmp	$_015

$_014:	mov	rbx, qword ptr [rbx+0x68]
	jmp	$_007

$_015:	mov	rax, rsi
$_016:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_017:
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rax, qword ptr [rdx+0x68]
	mov	rbx, qword ptr [rax]
	mov	rcx, qword ptr [rcx+0x68]
	mov	rdi, qword ptr [rcx]
	mov	ax, word ptr [rdi+0x5A]
	cmp	word ptr [rbx+0x5A], ax
	jz	$_018
	xor	eax, eax
	jmp	$_026

$_018:	test	rbx, rbx
	jz	$_024
	test	rdi, rdi
	jnz	$_019
	xor	eax, eax
	jmp	$_026

$_019:	mov	rax, qword ptr [rdi+0x8]
	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jz	$_020
	cmp	byte ptr [rax], 0
	jnz	$_020
	jmp	$_021

$_020:	mov	rdx, qword ptr [rdi+0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jz	$_021
	xor	eax, eax
	jmp	$_026

$_021:	mov	eax, dword ptr [rdi+0x28]
	cmp	dword ptr [rbx+0x28], eax
	jz	$_022
	xor	eax, eax
	jmp	$_026

$_022:	mov	eax, dword ptr [rdi+0x50]
	cmp	dword ptr [rbx+0x50], eax
	jz	$_023
	xor	eax, eax
	jmp	$_026

$_023:	mov	rbx, qword ptr [rbx+0x68]
	mov	rdi, qword ptr [rdi+0x68]
	jmp	$_018

$_024:	test	rdi, rdi
	jz	$_025
	xor	eax, eax
	jmp	$_026

$_025:	mov	eax, 1
$_026:	leave
	pop	rbx
	pop	rdi
	ret

StructDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	rbx, rdx
	mov	rsi, qword ptr [rbx+0x8]
	imul	ecx, ecx, 24
	add	rbx, rcx
	mov	al, 1
	cmp	dword ptr [rbx+0x4], 499
	jnz	$_027
	mov	al, 2
	jmp	$_028

$_027:	cmp	dword ptr [rbx+0x4], 501
	jnz	$_028
	mov	al, 4
$_028:	mov	byte ptr [rbp-0x9], al
	mov	rax, qword ptr [CurrStruct+rip]
	test	rax, rax
	jnz	$_029
	cmp	dword ptr [rbp+0x28], 1
	jnz	$_030
$_029:	test	rax, rax
	jz	$_031
	cmp	dword ptr [rbp+0x28], 0
	jz	$_031
$_030:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_067

$_031:	mov	eax, 1
	mov	cl, byte ptr [ModuleInfo+0x1C5+rip]
	shl	eax, cl
	mov	dword ptr [rbp-0x4], eax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	dword ptr [rbp+0x28], 1
	jnz	$_032
	lea	rsi, [DS0000+rip]
	cmp	byte ptr [rbx], 8
	jnz	$_032
	mov	rsi, qword ptr [rbx+0x8]
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_032:	cmp	qword ptr [CurrStruct+rip], 0
	jne	$_042
	cmp	byte ptr [rbx], 0
	je	$_042
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x78]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_041
	mov	rcx, qword ptr [rbp-0x28]
	cmp	dword ptr [rbp-0x3C], -2
	jnz	$_033
	jmp	$_041

$_033:	cmp	dword ptr [rbp-0x3C], 0
	jz	$_036
	test	rcx, rcx
	jz	$_034
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_034
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_035

$_034:	mov	ecx, 2026
	call	asmerr@PLT
$_035:	jmp	$_041

$_036:	cmp	dword ptr [rbp-0x78], 32
	jle	$_037
	mov	ecx, 2064
	call	asmerr@PLT
	jmp	$_041

$_037:	mov	eax, 1
$_038:	cmp	eax, dword ptr [rbp-0x78]
	jge	$_039
	shl	eax, 1
	jmp	$_038

$_039:	cmp	eax, dword ptr [rbp-0x78]
	jz	$_040
	mov	edx, dword ptr [rbp-0x78]
	mov	ecx, 2063
	call	asmerr@PLT
	jmp	$_041

$_040:	mov	eax, dword ptr [rbp-0x78]
	mov	dword ptr [rbp-0x4], eax
$_041:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 44
	jnz	$_042
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 8
	jnz	$_042
	lea	rdx, [DS0001+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_042
	lea	rdx, [DS0001+rip]
	mov	ecx, 8017
	call	asmerr@PLT
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_042:	cmp	byte ptr [rbx], 0
	jz	$_043
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_067

$_043:	cmp	byte ptr [rsi], 0
	jz	$_046
	cmp	qword ptr [CurrStruct+rip], 0
	jnz	$_044
	mov	rcx, rsi
	call	SymFind@PLT
	mov	rdi, rax
	jmp	$_045

$_044:	xor	r9d, r9d
	lea	r8, [rbp-0x8]
	mov	rdx, rsi
	mov	rcx, qword ptr [CurrStruct+rip]
	call	SearchNameInStruct
	mov	rdi, rax
$_045:	jmp	$_047

$_046:	mov	edi, 0
$_047:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_049
	mov	rcx, qword ptr [CurrStruct+rip]
	test	rcx, rcx
	jz	$_048
	xor	r8d, r8d
	mov	edx, dword ptr [rcx+0x50]
	mov	ecx, 6
	call	LstWrite@PLT
	jmp	$_049

$_048:	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 6
	call	LstWrite@PLT
$_049:	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_051
	mov	rcx, qword ptr [CurrStruct+rip]
	test	rcx, rcx
	jz	$_050
	mov	rcx, qword ptr [rcx+0x68]
	mov	rdx, qword ptr [rcx+0x8]
	mov	rdi, qword ptr [rdx+0x20]
	mov	rax, qword ptr [rdx+0x68]
	mov	qword ptr [rcx+0x8], rax
$_050:	mov	rcx, qword ptr [rdi+0x68]
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rcx+0x8], rax
	mov	dword ptr [rdi+0x28], 0
	or	byte ptr [rdi+0x14], 0x02
	mov	byte ptr [rdi+0x18], 7
	mov	rax, qword ptr [CurrStruct+rip]
	mov	qword ptr [rdi+0x70], rax
	mov	qword ptr [CurrStruct+rip], rdi
	xor	eax, eax
	jmp	$_067

$_051:	test	rdi, rdi
	jnz	$_054
	cmp	qword ptr [CurrStruct+rip], 0
	jnz	$_052
	mov	r8d, 1
	mov	rdx, rsi
	xor	ecx, ecx
	call	CreateTypeSymbol
	mov	rdi, rax
	jmp	$_053

$_052:	xor	r8d, r8d
	mov	rdx, rsi
	xor	ecx, ecx
	call	CreateTypeSymbol
	mov	rdi, rax
	mov	rcx, qword ptr [CurrStruct+rip]
	mov	rcx, qword ptr [rcx+0x68]
	movzx	eax, byte ptr [rcx+0x10]
	mov	dword ptr [rbp-0x4], eax
$_053:	jmp	$_063

$_054:	cmp	byte ptr [rdi+0x18], 0
	jnz	$_056
	xor	eax, eax
	cmp	qword ptr [CurrStruct+rip], 0
	jnz	$_055
	inc	eax
$_055:	mov	r8d, eax
	xor	edx, edx
	mov	rcx, rdi
	call	CreateTypeSymbol
	jmp	$_063

$_056:	cmp	byte ptr [rdi+0x18], 7
	jnz	$_062
	cmp	qword ptr [CurrStruct+rip], 0
	jnz	$_062
	jmp	$_060

$_057:	mov	qword ptr [redef_struct+rip], rdi
	xor	r8d, r8d
	mov	rdx, rsi
	xor	ecx, ecx
	call	CreateTypeSymbol
	mov	rdi, rax
	jmp	$_061

$_058:	jmp	$_061

$_059:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_067

	jmp	$_061

$_060:	cmp	word ptr [rdi+0x5A], 1
	jz	$_057
	cmp	word ptr [rdi+0x5A], 2
	jz	$_057
	cmp	word ptr [rdi+0x5A], 0
	jz	$_058
	jmp	$_059

$_061:	jmp	$_063

$_062:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_067

$_063:	mov	dword ptr [rdi+0x28], 0
	movzx	eax, byte ptr [rbp-0x9]
	mov	word ptr [rdi+0x5A], ax
	mov	rcx, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rbp-0x4]
	mov	byte ptr [rcx+0x10], al
	or	byte ptr [rcx+0x11], 0x02
	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_064
	or	byte ptr [rcx+0x11], 0x01
$_064:	mov	rax, qword ptr [CurrStruct+rip]
	mov	qword ptr [rdi+0x70], rax
	cmp	qword ptr [ModuleInfo+0x108+rip], 0
	jz	$_066
	mov	rbx, qword ptr [ModuleInfo+0x108+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	mov	ecx, eax
	mov	rdx, rdi
	mov	rdi, qword ptr [rbx+0x8]
	repe cmpsb
	mov	rdi, rdx
	jnz	$_066
	mov	eax, dword ptr [rsi]
	test	al, al
	jnz	$_065
	mov	qword ptr [rbx+0x28], rdi
	or	byte ptr [rdi+0x16], 0x01
	jmp	$_066

$_065:	cmp	eax, 1818391638
	jnz	$_066
	cmp	byte ptr [rsi+0x4], 0
	jnz	$_066
	mov	rcx, qword ptr [rbx+0x28]
	or	byte ptr [rcx+0x16], 0x02
	mov	qword ptr [rcx+0x30], rdi
	mov	qword ptr [rdi+0x30], rcx
	or	byte ptr [rdi+0x16], 0x04
$_066:	mov	qword ptr [CurrStruct+rip], rdi
	xor	eax, eax
$_067:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

EndstructDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rdi, qword ptr [CurrStruct+rip]
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_070
	mov	dword ptr [rdi+0x28], 0
	mov	ebx, dword ptr [rdi+0x50]
	mov	rax, qword ptr [rdi+0x70]
	mov	qword ptr [CurrStruct+rip], rax
	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_068
	mov	rcx, rdi
	call	UpdateStructSize
$_068:	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_069
	mov	r8, rdi
	mov	edx, ebx
	mov	ecx, 6
	call	LstWrite@PLT
$_069:	xor	eax, eax
	jmp	$_102

$_070:	mov	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp+0x28], 1
	jnz	$_071
	cmp	qword ptr [rdi+0x70], 0
	jz	$_072
$_071:	cmp	dword ptr [rbp+0x28], 0
	jnz	$_073
	cmp	qword ptr [rdi+0x70], 0
	jz	$_073
$_072:	jmp	$_075

$_073:	lea	rdx, [DS0001+0x9+rip]
	cmp	dword ptr [rbp+0x28], 1
	jnz	$_074
	mov	rdx, qword ptr [rbx+0x8]
$_074:	mov	ecx, 1010
	call	asmerr@PLT
	jmp	$_102

$_075:	cmp	dword ptr [rbp+0x28], 1
	jnz	$_076
	movsxd	r8, dword ptr [rdi+0x10]
	mov	rdx, qword ptr [rdi+0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	qword ptr [SymCmpFunc+rip]
	test	rax, rax
	jz	$_076
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	jmp	$_102

$_076:	inc	dword ptr [rbp+0x28]
	imul	ecx, dword ptr [rbp+0x28], 24
	add	rbx, rcx
	mov	rsi, qword ptr [rdi+0x68]
	test	byte ptr [rsi+0x11], 0x04
	jz	$_080
	xor	ecx, ecx
	mov	rdx, qword ptr [rsi]
$_077:	test	rdx, rdx
	jz	$_079
	cmp	dword ptr [rdx+0x28], ecx
	jge	$_078
	mov	ecx, dword ptr [rdx+0x28]
$_078:	mov	rdx, qword ptr [rdx+0x68]
	jmp	$_077

$_079:	mov	eax, dword ptr [rdi+0x50]
	sub	eax, ecx
	mov	dword ptr [rdi+0x50], eax
$_080:	movzx	edx, byte ptr [rsi+0x10]
	cmp	edx, 1
	jbe	$_083
	mov	eax, dword ptr [rdi+0x40]
	test	eax, eax
	jnz	$_081
	inc	eax
$_081:	cmp	eax, edx
	jbe	$_082
	mov	eax, edx
$_082:	mov	ecx, eax
	neg	ecx
	add	eax, dword ptr [rdi+0x50]
	dec	eax
	and	eax, ecx
	mov	dword ptr [rdi+0x50], eax
$_083:	and	byte ptr [rsi+0x11], 0xFFFFFFFD
	or	byte ptr [rdi+0x14], 0x02
	mov	esi, dword ptr [rdi+0x50]
	mov	dword ptr [rdi+0x28], 0
	mov	rax, qword ptr [rdi+0x70]
	mov	qword ptr [CurrStruct+rip], rax
	cmp	dword ptr [rbp+0x28], 1
	jnz	$_085
	mov	rcx, qword ptr [rdi+0x8]
	cmp	byte ptr [rcx], 0
	jnz	$_084
	xor	ecx, ecx
$_084:	mov	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rsp+0x28], eax
	mov	qword ptr [rsp+0x20], rdi
	mov	r9d, 196
	mov	r8, rcx
	xor	edx, edx
	mov	ecx, 4294967295
	call	CreateStructField
	mov	ecx, dword ptr [rdi+0x50]
	mov	dword ptr [rax+0x50], ecx
	lea	rax, [DS0001+0x9+rip]
	mov	qword ptr [rdi+0x8], rax
	mov	dword ptr [rdi+0x10], 0
$_085:	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_086
	mov	r8, rdi
	movzx	edx, si
	mov	ecx, 6
	call	LstWrite@PLT
$_086:	test	byte ptr [rdi+0x3B], 0x08
	jz	$_087
	movzx	eax, word ptr [rdi+0x4A]
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rdi+0x19], al
	jmp	$_095

$_087:	mov	eax, dword ptr [rdi+0x50]
	jmp	$_094

$_088:	mov	byte ptr [rdi+0x19], 0
	jmp	$_095

$_089:	mov	byte ptr [rdi+0x19], 1
	jmp	$_095

$_090:	mov	byte ptr [rdi+0x19], 3
	jmp	$_095

$_091:	mov	byte ptr [rdi+0x19], 5
	jmp	$_095

$_092:	mov	byte ptr [rdi+0x19], 7
	jmp	$_095

$_093:	mov	byte ptr [rdi+0x19], -64
	jmp	$_095

$_094:	cmp	eax, 1
	jz	$_088
	cmp	eax, 2
	jz	$_089
	cmp	eax, 4
	jz	$_090
	cmp	eax, 6
	jz	$_091
	cmp	eax, 8
	jz	$_092
	jmp	$_093

$_095:	cmp	qword ptr [CurrStruct+rip], 0
	jnz	$_098
	cmp	qword ptr [redef_struct+rip], 0
	jz	$_097
	mov	rdx, qword ptr [redef_struct+rip]
	mov	rcx, rdi
	call	$_017
	test	rax, rax
	jnz	$_096
	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS0002+rip]
	mov	ecx, 2007
	call	asmerr@PLT
$_096:	mov	rcx, rdi
	call	SymFree@PLT
	mov	qword ptr [redef_struct+rip], 0
$_097:	jmp	$_100

$_098:	mov	rcx, qword ptr [CurrStruct+rip]
	mov	eax, dword ptr [rdi+0x40]
	cmp	eax, dword ptr [rcx+0x40]
	jbe	$_099
	mov	dword ptr [rcx+0x40], eax
$_099:	mov	rcx, rdi
	call	UpdateStructSize
$_100:	cmp	byte ptr [rbx], 0
	jz	$_101
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_102

$_101:	xor	eax, eax
$_102:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_103:
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rcx, qword ptr [rcx+0x68]
	mov	rdi, qword ptr [rcx]
$_104:	test	rdi, rdi
	jz	$_109
	mov	rax, qword ptr [rdi+0x8]
	cmp	byte ptr [rax], 0
	jz	$_106
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rdi+0x8]
	mov	rcx, qword ptr [CurrStruct+rip]
	call	SearchNameInStruct
	test	rax, rax
	jz	$_105
	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_110

$_105:	jmp	$_108

$_106:	cmp	qword ptr [rdi+0x20], 0
	jz	$_108
	mov	rax, qword ptr [rdi+0x20]
	cmp	word ptr [rax+0x5A], 1
	jz	$_107
	cmp	word ptr [rax+0x5A], 2
	jnz	$_108
$_107:	mov	rcx, rax
	call	$_103
	cmp	eax, -1
	jnz	$_108
	mov	rax, -1
	jmp	$_110

$_108:	mov	rdi, qword ptr [rdi+0x68]
	jmp	$_104

$_109:	xor	eax, eax
$_110:	leave
	pop	rdi
	ret

CreateStructField:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	dword ptr [rbp-0x14], 0
	mov	rcx, qword ptr [CurrStruct+rip]
	cmp	word ptr [rcx+0x5A], 4
	jnz	$_111
	mov	dword ptr [rbp-0x14], 1
$_111:	mov	rax, qword ptr [rcx+0x68]
	mov	qword ptr [rbp-0x10], rax
	mov	eax, dword ptr [rcx+0x28]
	mov	dword ptr [rbp-0x4], eax
	cmp	qword ptr [rbp+0x38], 0
	jz	$_114
	mov	rcx, qword ptr [rbp+0x38]
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x8], eax
	cmp	eax, 247
	jbe	$_112
	mov	ecx, 2043
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_143

$_112:	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [CurrStruct+rip]
	call	SearchNameInStruct
	test	rax, rax
	jz	$_113
	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_143

$_113:	jmp	$_117

$_114:	mov	rcx, qword ptr [rbp+0x48]
	test	rcx, rcx
	jz	$_116
	cmp	word ptr [rcx+0x5A], 1
	jz	$_115
	cmp	word ptr [rcx+0x5A], 2
	jnz	$_116
$_115:	call	$_103
$_116:	lea	rax, [DS0002+0x9+rip]
	mov	qword ptr [rbp+0x38], rax
	mov	dword ptr [rbp-0x8], 0
$_117:	mov	ecx, dword ptr [rbp+0x28]
	cmp	ecx, -1
	je	$_124
	mov	rdi, qword ptr [ModuleInfo+0x188+rip]
	inc	ecx
	imul	ebx, ecx, 24
	add	rbx, qword ptr [rbp+0x30]
$_118:	cmp	byte ptr [rbx], 0
	je	$_123
	cmp	byte ptr [rbx], 8
	jnz	$_121
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rsi, rax
	test	eax, eax
	jz	$_121
	test	byte ptr [rax+0x14], 0x40
	jz	$_121
	test	byte ptr [rax+0x14], 0x20
	jz	$_119
	cmp	qword ptr [rax+0x58], 0
	jz	$_119
	xor	edx, edx
	mov	rcx, rax
	call	qword ptr [rax+0x58]
	mov	rax, rsi
$_119:	xor	ecx, ecx
	cmp	dword ptr [rax+0x50], 0
	jge	$_120
	inc	ecx
$_120:	mov	esi, dword ptr [rax+0x28]
	mov	dword ptr [rsp+0x20], 1
	mov	r9d, ecx
	movzx	r8d, byte ptr [ModuleInfo+0x1C4+rip]
	mov	rdx, rdi
	mov	rcx, rsi
	call	myltoa@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	mov	al, 32
	stosb
	jmp	$_122

$_121:	mov	rsi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, rsi
	rep movsb
$_122:	add	rbx, 24
	jmp	$_118

$_123:	mov	byte ptr [rdi], 0
	mov	rcx, rdi
	sub	rcx, qword ptr [ModuleInfo+0x188+rip]
	mov	rsi, rcx
	add	ecx, 120
	call	LclAlloc@PLT
	mov	rdi, rax
	xor	eax, eax
	mov	ecx, 120
	mov	rdx, rdi
	rep stosb
	lea	rdi, [rdx+0x70]
	mov	rcx, rsi
	mov	rsi, qword ptr [ModuleInfo+0x188+rip]
	inc	ecx
	rep movsb
	mov	rdi, rdx
	jmp	$_125

$_124:	mov	ecx, 120
	call	LclAlloc@PLT
	mov	rdi, rax
	xor	eax, eax
	mov	ecx, 120
	mov	rdx, rdi
	rep stosb
	mov	rdi, rdx
$_125:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rdi+0x10], eax
	test	eax, eax
	jz	$_126
	mov	rcx, qword ptr [rbp+0x38]
	call	LclDup@PLT
	mov	qword ptr [rdi+0x8], rax
	jmp	$_127

$_126:	lea	rax, [DS0002+0x9+rip]
	mov	qword ptr [rdi+0x8], rax
$_127:	mov	byte ptr [rdi+0x18], 6
	cmp	byte ptr [ModuleInfo+0x1DC+rip], 0
	jz	$_128
	or	byte ptr [rdi+0x15], 0x01
$_128:	or	byte ptr [rdi+0x14], 0x02
	mov	al, byte ptr [rbp+0x40]
	mov	byte ptr [rdi+0x19], al
	mov	rax, qword ptr [rbp+0x48]
	mov	qword ptr [rdi+0x20], rax
	mov	qword ptr [rdi+0x68], 0
	mov	rsi, qword ptr [rbp-0x10]
	mov	rcx, qword ptr [rsi]
	cmp	qword ptr [rsi], 0
	jnz	$_129
	mov	dword ptr [rbp-0x14], 0
	mov	qword ptr [rsi], rdi
	mov	qword ptr [rsi+0x8], rdi
	jmp	$_130

$_129:	mov	rcx, qword ptr [rsi+0x8]
	mov	qword ptr [rcx+0x68], rdi
	mov	qword ptr [rsi+0x8], rdi
$_130:	mov	rcx, qword ptr [rbp+0x48]
	cmp	byte ptr [rbp+0x40], -60
	jnz	$_134
	jmp	$_132

$_131:	mov	rcx, qword ptr [rcx+0x20]
$_132:	cmp	qword ptr [rcx+0x20], 0
	jnz	$_131
	cmp	word ptr [rcx+0x5A], 1
	jz	$_133
	cmp	word ptr [rcx+0x5A], 2
	jnz	$_134
$_133:	mov	eax, dword ptr [rcx+0x40]
	mov	dword ptr [rbp+0x50], eax
$_134:	movzx	eax, byte ptr [rsi+0x10]
	cmp	eax, 1
	jbe	$_137
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_137
	mov	ecx, dword ptr [rbp+0x50]
	cmp	eax, ecx
	jnc	$_135
	lea	ecx, [rax-0x1]
	mov	edx, dword ptr [rbp-0x4]
	add	edx, ecx
	neg	eax
	and	edx, eax
	mov	dword ptr [rbp-0x4], edx
	jmp	$_136

$_135:	test	ecx, ecx
	jz	$_136
	mov	eax, ecx
	lea	ecx, [rax-0x1]
	mov	edx, dword ptr [rbp-0x4]
	add	edx, ecx
	neg	eax
	and	edx, eax
	mov	dword ptr [rbp-0x4], edx
$_136:	mov	rcx, qword ptr [CurrStruct+rip]
	cmp	word ptr [rcx+0x5A], 2
	jz	$_137
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rcx+0x28], eax
	mov	eax, dword ptr [rcx+0x50]
	cmp	dword ptr [rbp-0x4], eax
	jle	$_137
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rcx+0x50], eax
$_137:	mov	rcx, qword ptr [CurrStruct+rip]
	mov	eax, dword ptr [rcx+0x40]
	cmp	dword ptr [rbp+0x50], eax
	jbe	$_138
	mov	eax, dword ptr [rbp+0x50]
	mov	dword ptr [rcx+0x40], eax
$_138:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rdi+0x28], eax
	mov	rdx, qword ptr [rbp+0x38]
	cmp	byte ptr [ModuleInfo+0x1D8+rip], 1
	jnz	$_142
	cmp	byte ptr [rdx], 0
	jz	$_142
	mov	rcx, qword ptr [rbp+0x38]
	call	SymLookup@PLT
	cmp	byte ptr [rax+0x18], 0
	jnz	$_139
	mov	byte ptr [rax+0x18], 6
$_139:	cmp	byte ptr [rax+0x18], 6
	jnz	$_142
	mov	rcx, rax
	mov	al, byte ptr [rbp+0x40]
	mov	byte ptr [rcx+0x19], al
	mov	rax, qword ptr [rbp+0x48]
	mov	qword ptr [rcx+0x20], rax
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rcx+0x28], eax
	mov	rdx, qword ptr [CurrStruct+rip]
	mov	rdx, qword ptr [rdx+0x70]
$_140:	test	rdx, rdx
	jz	$_141
	mov	eax, dword ptr [rdx+0x28]
	add	dword ptr [rcx+0x28], eax
	mov	rdx, qword ptr [rdx+0x70]
	jmp	$_140

$_141:	or	byte ptr [rcx+0x14], 0x02
$_142:	mov	rax, rdi
$_143:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AlignInStruct:
	mov	rdx, qword ptr [CurrStruct+rip]
	cmp	word ptr [rdx+0x5A], 2
	jz	$_144
	mov	eax, dword ptr [rdx+0x28]
	lea	eax, [rax+rcx-0x1]
	neg	ecx
	and	eax, ecx
	mov	dword ptr [rdx+0x28], eax
	cmp	eax, dword ptr [rdx+0x50]
	jbe	$_144
	mov	dword ptr [rdx+0x50], eax
$_144:	xor	eax, eax
	ret

UpdateStructSize:
	mov	rdx, qword ptr [CurrStruct+rip]
	cmp	word ptr [rdx+0x5A], 4
	jnz	$_145
	jmp	$_148

$_145:	cmp	word ptr [rdx+0x5A], 2
	jnz	$_147
	mov	eax, dword ptr [rdx+0x50]
	cmp	dword ptr [rcx+0x50], eax
	jbe	$_146
	mov	eax, dword ptr [rcx+0x50]
	mov	dword ptr [rdx+0x50], eax
$_146:	jmp	$_148

$_147:	mov	eax, dword ptr [rcx+0x50]
	add	dword ptr [rdx+0x28], eax
	mov	eax, dword ptr [rdx+0x50]
	cmp	dword ptr [rdx+0x28], eax
	jle	$_148
	mov	eax, dword ptr [rdx+0x28]
	mov	dword ptr [rdx+0x50], eax
$_148:	ret

SetStructCurrentOffset:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, qword ptr [CurrStruct+rip]
	cmp	word ptr [rdx+0x5A], 2
	jnz	$_149
	mov	ecx, 2200
	call	asmerr@PLT
	jmp	$_151

$_149:	mov	dword ptr [rdx+0x28], ecx
	mov	rax, qword ptr [rdx+0x68]
	or	byte ptr [rax+0x11], 0x04
	cmp	ecx, dword ptr [rdx+0x50]
	jle	$_150
	mov	dword ptr [rdx+0x50], ecx
$_150:	xor	eax, eax
$_151:	leave
	ret

GetQualifiedType:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	dword ptr [rbp-0x10], 0
	mov	eax, dword ptr [rcx]
	mov	dword ptr [rbp-0x14], eax
	imul	ebx, eax, 24
	add	rbx, rdx
	mov	rdx, rbx
$_152:	cmp	byte ptr [rbx], 0
	jz	$_155
	cmp	byte ptr [rbx], 44
	jz	$_155
	cmp	byte ptr [rbx], 3
	jnz	$_154
	cmp	dword ptr [rbx+0x4], 508
	jnz	$_154
	mov	byte ptr [rbx], 6
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	mov	eax, 1
	shl	eax, cl
	and	eax, 0x70
	mov	ecx, 226
	jz	$_153
	mov	ecx, 227
$_153:	mov	dword ptr [rbx+0x4], ecx
$_154:	add	rbx, 24
	jmp	$_152

$_155:
	mov	rbx, rdx
	mov	rsi, qword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x4], -1
$_156:	cmp	byte ptr [rbx], 6
	jz	$_157
	cmp	byte ptr [rbx], 5
	jne	$_169
$_157:	cmp	byte ptr [rbx], 6
	jnz	$_166
	mov	edi, dword ptr [rbx+0x4]
	cmp	dword ptr [rbp-0x4], -1
	jnz	$_158
	mov	dword ptr [rbp-0x4], edi
$_158:	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0x9], al
	cmp	al, -126
	jz	$_159
	cmp	al, -127
	jnz	$_163
$_159:	cmp	dword ptr [rbp-0x10], 0
	jnz	$_161
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	mov	eax, dword ptr [r11+rax+0x4]
	cmp	byte ptr [rbp-0x9], -126
	sete	cl
	mov	byte ptr [rsi+0x12], cl
	cmp	eax, 254
	jz	$_160
	mov	byte ptr [rsi+0x13], al
$_160:	mov	dword ptr [rbp-0x10], 1
	jmp	$_162

$_161:	cmp	dword ptr [rbx-0x14], 270
	jz	$_162
	jmp	$_169

$_162:	jmp	$_165

$_163:	cmp	byte ptr [rsi+0x11], 0
	jz	$_164
	mov	al, byte ptr [rbp-0x9]
	mov	byte ptr [rsi+0x14], al
$_164:	add	rbx, 24
	jmp	$_169

$_165:	jmp	$_168

$_166:	cmp	dword ptr [rbx+0x4], 270
	jnz	$_167
	mov	dword ptr [rbp-0x4], -2
	inc	byte ptr [rsi+0x11]
	jmp	$_168

$_167:	jmp	$_169

$_168:	add	rbx, 24
	jmp	$_156

$_169:
	cmp	dword ptr [rbp-0x4], -2
	jne	$_180
	cmp	byte ptr [rbx], 8
	jne	$_180
	cmp	dword ptr [rbx-0x14], 270
	jne	$_180
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	rdi, qword ptr [rsi+0x8]
	test	rdi, rdi
	jz	$_170
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_171
$_170:	mov	r8d, 1
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	CreateTypeSymbol
	mov	qword ptr [rsi+0x8], rax
	jmp	$_179

$_171:	cmp	byte ptr [rdi+0x18], 7
	jz	$_172
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_200

	jmp	$_179

$_172:	cmp	word ptr [rdi+0x5A], 3
	jne	$_179
	mov	al, byte ptr [rdi+0x39]
	add	byte ptr [rsi+0x11], al
	cmp	byte ptr [rdi+0x39], 0
	jnz	$_176
	mov	al, -64
	cmp	byte ptr [rdi+0x19], -60
	jz	$_173
	mov	al, byte ptr [rdi+0x19]
$_173:	mov	byte ptr [rsi+0x14], al
	cmp	dword ptr [rbp-0x10], 0
	jnz	$_175
	cmp	byte ptr [rsi+0x11], 1
	jnz	$_175
	cmp	byte ptr [rdi+0x19], -127
	jz	$_174
	cmp	byte ptr [rdi+0x19], -128
	jz	$_174
	cmp	byte ptr [rdi+0x19], -126
	jnz	$_175
$_174:	mov	al, byte ptr [rdi+0x1C]
	mov	byte ptr [rsi+0x12], al
	cmp	byte ptr [rdi+0x38], -2
	jz	$_175
	mov	al, byte ptr [rdi+0x38]
	mov	byte ptr [rsi+0x13], al
$_175:	jmp	$_177

$_176:	mov	al, byte ptr [rdi+0x3A]
	mov	byte ptr [rsi+0x14], al
	cmp	dword ptr [rbp-0x10], 0
	jnz	$_177
	cmp	byte ptr [rsi+0x11], 1
	jnz	$_177
	mov	al, byte ptr [rdi+0x1C]
	mov	byte ptr [rsi+0x12], al
	cmp	byte ptr [rdi+0x38], -2
	jz	$_177
	mov	al, byte ptr [rdi+0x38]
	mov	byte ptr [rsi+0x13], al
$_177:	cmp	byte ptr [rdi+0x19], -60
	jnz	$_178
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rsi+0x8], rax
	jmp	$_179

$_178:	mov	rax, qword ptr [rdi+0x40]
	mov	qword ptr [rsi+0x8], rax
$_179:	add	rbx, 24
$_180:	cmp	dword ptr [rbp-0x4], -1
	jne	$_194
	cmp	byte ptr [rbx], 8
	jz	$_184
	cmp	byte ptr [rbx], 0
	jz	$_181
	cmp	byte ptr [rbx], 44
	jnz	$_182
$_181:	mov	ecx, 2175
	call	asmerr@PLT
	jmp	$_183

$_182:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
$_183:	mov	rax, -1
	jmp	$_200

$_184:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	rdi, rax
	test	rdi, rdi
	jz	$_185
	cmp	byte ptr [rdi+0x18], 7
	jz	$_189
$_185:	cmp	qword ptr [rsi+0x8], 0
	jz	$_186
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_187
$_186:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_188

$_187:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2004
	call	asmerr@PLT
$_188:	mov	rax, -1
	jmp	$_200

$_189:	mov	rdi, qword ptr [rsi+0x8]
	cmp	word ptr [rdi+0x5A], 3
	jnz	$_192
	mov	al, byte ptr [rdi+0x19]
	mov	byte ptr [rsi+0x10], al
	mov	al, byte ptr [rdi+0x1C]
	mov	byte ptr [rsi+0x12], al
	mov	al, byte ptr [rdi+0x39]
	mov	byte ptr [rsi+0x11], al
	mov	al, byte ptr [rdi+0x38]
	mov	byte ptr [rsi+0x13], al
	mov	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rsi], eax
	mov	al, byte ptr [rdi+0x3A]
	mov	byte ptr [rsi+0x14], al
	cmp	byte ptr [rdi+0x19], -60
	jnz	$_190
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rsi+0x8], rax
	jmp	$_191

$_190:	mov	rax, qword ptr [rdi+0x40]
	mov	qword ptr [rsi+0x8], rax
$_191:	jmp	$_193

$_192:	mov	byte ptr [rsi+0x10], -60
	mov	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rsi], eax
$_193:	add	rbx, 24
	jmp	$_199

$_194:	cmp	byte ptr [rsi+0x11], 0
	jz	$_195
	mov	byte ptr [rsi+0x10], -61
	jmp	$_196

$_195:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp-0x4], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rsi+0x10], al
$_196:	cmp	byte ptr [rsi+0x10], -61
	jnz	$_198
	mov	ecx, 129
	cmp	byte ptr [rsi+0x12], 0
	jz	$_197
	mov	ecx, 130
$_197:	xor	r8d, r8d
	movzx	edx, byte ptr [rsi+0x13]
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	mov	dword ptr [rsi], eax
	jmp	$_199

$_198:	xor	r8d, r8d
	movzx	edx, byte ptr [rsi+0x13]
	movzx	ecx, byte ptr [rsi+0x10]
	call	SizeFromMemtype@PLT
	mov	dword ptr [rsi], eax
$_199:	mov	rax, rbx
	sub	rax, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	ecx, 24
	div	ecx
	mov	rcx, qword ptr [rbp+0x28]
	mov	dword ptr [rcx], eax
	xor	eax, eax
$_200:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CreateType:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rcx, qword ptr [rbp+0x38]
	call	SymFind@PLT
	mov	rdi, rax
	test	rdi, rdi
	jz	$_201
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_203
$_201:	mov	r8d, 1
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, rdi
	call	CreateTypeSymbol
	mov	rdi, rax
	test	rdi, rdi
	jnz	$_202
	mov	rax, -1
	jmp	$_229

$_202:	jmp	$_205

$_203:	cmp	byte ptr [rdi+0x18], 7
	jnz	$_204
	cmp	word ptr [rdi+0x5A], 3
	jz	$_205
	cmp	word ptr [rdi+0x5A], 0
	jz	$_205
$_204:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_229

$_205:	mov	rcx, qword ptr [rbp+0x40]
	test	rcx, rcx
	jz	$_206
	mov	qword ptr [rcx], rdi
$_206:	or	byte ptr [rdi+0x14], 0x02
	test	rcx, rcx
	jnz	$_207
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_207
	xor	eax, eax
	jmp	$_229

$_207:
	mov	word ptr [rdi+0x5A], 3
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 3
	jne	$_212
	cmp	dword ptr [rbx+0x4], 507
	jne	$_212
	cmp	qword ptr [rdi+0x40], 0
	jnz	$_208
	cmp	byte ptr [rdi+0x19], -64
	jnz	$_208
	mov	r8d, 7
	lea	rdx, [DS0002+0x9+rip]
	xor	ecx, ecx
	call	CreateProc@PLT
	jmp	$_210

$_208:	cmp	byte ptr [rdi+0x19], -128
	jnz	$_209
	mov	rax, qword ptr [rdi+0x40]
	jmp	$_210

$_209:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_229

$_210:	inc	dword ptr [rbp+0x28]
	mov	rsi, rax
	movzx	eax, byte ptr [ModuleInfo+0x1B6+rip]
	mov	dword ptr [rsp+0x20], eax
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, rsi
	call	ParseProc@PLT
	cmp	eax, -1
	je	$_229
	mov	byte ptr [rdi+0x19], -128
	mov	al, byte ptr [rsi+0x1B]
	mov	byte ptr [rdi+0x38], al
	mov	eax, 2
	mov	cl, byte ptr [rdi+0x38]
	shl	eax, cl
	mov	dword ptr [rdi+0x50], eax
	cmp	byte ptr [rsi+0x19], -127
	jz	$_211
	mov	byte ptr [rdi+0x1C], 1
	add	dword ptr [rdi+0x50], 2
$_211:	mov	qword ptr [rdi+0x40], rsi
	xor	eax, eax
	jmp	$_229

$_212:	mov	dword ptr [rbp-0x18], 0
	mov	byte ptr [rbp-0x7], 0
	mov	byte ptr [rbp-0x6], 0
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	mov	eax, 1
	shl	eax, cl
	test	eax, 0x68
	jz	$_213
	mov	byte ptr [rbp-0x6], 1
$_213:	mov	byte ptr [rbp-0x8], -64
	mov	byte ptr [rbp-0x4], -64
	mov	qword ptr [rbp-0x10], 0
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x5], al
	cmp	byte ptr [rbx], 0
	jz	$_214
	cmp	byte ptr [rbx], 44
	jnz	$_215
$_214:	jmp	$_216

$_215:	lea	r8, [rbp-0x18]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetQualifiedType
	cmp	eax, -1
	jnz	$_216
	jmp	$_229

$_216:	cmp	byte ptr [rdi+0x19], -64
	je	$_225
	mov	rcx, qword ptr [rbp-0x10]
$_217:	test	rcx, rcx
	jz	$_218
	cmp	qword ptr [rcx+0x20], 0
	jz	$_218
	mov	rcx, qword ptr [rcx+0x20]
	jmp	$_217

$_218:	mov	rdx, qword ptr [rdi+0x40]
	cmp	byte ptr [rdi+0x19], -60
	jnz	$_219
	mov	rdx, qword ptr [rdi+0x20]
$_219:	test	rdx, rdx
	jz	$_220
	cmp	qword ptr [rdx+0x20], 0
	jz	$_220
	mov	rdx, qword ptr [rdx+0x20]
	jmp	$_219

$_220:	mov	bl, byte ptr [ModuleInfo+0x1CC+rip]
	mov	bh, bl
	cmp	byte ptr [rdi+0x38], -2
	jz	$_221
	mov	bl, byte ptr [rdi+0x38]
$_221:	cmp	byte ptr [rbp-0x5], -2
	jz	$_222
	mov	bh, byte ptr [rbp-0x5]
$_222:	cmp	bl, bh
	setne	bl
	mov	al, byte ptr [rdi+0x19]
	cmp	byte ptr [rbp-0x8], al
	jnz	$_224
	cmp	byte ptr [rbp-0x8], -60
	jnz	$_223
	cmp	rcx, rdx
	jnz	$_224
$_223:	cmp	byte ptr [rbp-0x8], -61
	jnz	$_225
	mov	al, byte ptr [rdi+0x1C]
	cmp	byte ptr [rbp-0x6], al
	jnz	$_224
	test	bl, bl
	jnz	$_224
	mov	al, byte ptr [rdi+0x3A]
	cmp	byte ptr [rbp-0x4], al
	jnz	$_224
	cmp	rcx, rdx
	jz	$_225
$_224:	mov	rdx, qword ptr [rbp+0x38]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_229

$_225:	mov	al, byte ptr [rbp-0x8]
	mov	byte ptr [rdi+0x19], al
	mov	al, byte ptr [rbp-0x5]
	mov	byte ptr [rdi+0x38], al
	mov	eax, dword ptr [rbp-0x18]
	mov	dword ptr [rdi+0x50], eax
	mov	al, byte ptr [rbp-0x7]
	mov	byte ptr [rdi+0x39], al
	mov	al, byte ptr [rbp-0x6]
	mov	byte ptr [rdi+0x1C], al
	cmp	byte ptr [rbp-0x8], -60
	jnz	$_226
	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rdi+0x20], rax
	jmp	$_227

$_226:	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rdi+0x40], rax
$_227:	mov	al, byte ptr [rbp-0x4]
	mov	byte ptr [rdi+0x3A], al
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	qword ptr [rbp+0x40], 0
	jnz	$_228
	cmp	byte ptr [rbx], 0
	jz	$_228
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_229

$_228:	xor	eax, eax
$_229:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

TypedefDirective:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	ecx, 1
	jz	$_230
	imul	eax, ecx, 24
	mov	rdx, qword ptr [rdx+rax+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_231

$_230:	inc	ecx
	xor	r9d, r9d
	mov	r8, qword ptr [rdx+0x8]
	call	CreateType
$_231:	leave
	ret

RecordDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 216
	mov	qword ptr [rbp-0x18], 0
	mov	rbx, rdx
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	imul	ecx, ecx, 24
	add	rbx, rcx
	cmp	dword ptr [rbp+0x28], 1
	jz	$_233
	cmp	dword ptr [rbp+0x28], 0
	jnz	$_232
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp+0x28]
	call	StructDirective
	jmp	$_277

$_232:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_277

$_233:	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	mov	rsi, rax
	test	rsi, rsi
	jz	$_234
	cmp	byte ptr [rsi+0x18], 0
	jnz	$_235
$_234:	mov	r8d, 1
	mov	rdx, qword ptr [rbp-0x8]
	mov	rcx, rsi
	call	CreateTypeSymbol
	mov	rsi, rax
	jmp	$_239

$_235:	cmp	byte ptr [rsi+0x18], 7
	jnz	$_238
	cmp	word ptr [rsi+0x5A], 4
	jz	$_236
	cmp	word ptr [rsi+0x5A], 0
	jnz	$_238
$_236:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_237
	cmp	word ptr [rsi+0x5A], 4
	jnz	$_237
	mov	qword ptr [rbp-0x18], rsi
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp-0x8]
	xor	ecx, ecx
	call	CreateTypeSymbol
	mov	rsi, rax
	mov	dword ptr [rbp-0x28], 0
$_237:	jmp	$_239

$_238:	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_277

$_239:	or	byte ptr [rsi+0x14], 0x02
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_240
	xor	eax, eax
	jmp	$_277

$_240:	mov	qword ptr [rbp-0x10], rsi
	mov	word ptr [rsi+0x5A], 4
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	dword ptr [rbp-0x1C], 0
$_241:	cmp	byte ptr [rbx], 8
	jz	$_242
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_265

$_242:	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x24], eax
	cmp	eax, 247
	jbe	$_243
	mov	ecx, 2043
	call	asmerr@PLT
	jmp	$_265

$_243:	mov	rdi, rbx
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rbx+0x18], 58
	jz	$_244
	lea	rdx, [DS0002+0x9+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_265

$_244:	inc	dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0xA0]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_265
	cmp	dword ptr [rbp-0x64], 0
	jz	$_245
	mov	ecx, 2026
	call	asmerr@PLT
	mov	dword ptr [rbp-0xA0], 1
$_245:	mov	ecx, dword ptr [rbp-0xA0]
	add	ecx, dword ptr [rbp-0x1C]
	mov	eax, 32
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_246
	mov	eax, 64
$_246:	cmp	dword ptr [rbp-0xA0], 0
	jnz	$_247
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2172
	call	asmerr@PLT
	jmp	$_265

	jmp	$_248

$_247:	cmp	ecx, eax
	jbe	$_248
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2089
	call	asmerr@PLT
	jmp	$_265

$_248:	mov	dword ptr [rbp-0x2C], 0
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 3
	jnz	$_252
	cmp	byte ptr [rbx+0x1], 45
	jnz	$_252
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	rcx, rbx
	mov	qword ptr [rbp-0x38], rbx
$_249:	cmp	byte ptr [rbx], 0
	jz	$_250
	cmp	byte ptr [rbx], 44
	jz	$_250
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_249

$_250:	cmp	rcx, rbx
	jnz	$_251
	mov	rdx, qword ptr [rdi+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_265

$_251:	cmp	qword ptr [rbp-0x18], 0
	jnz	$_252
	mov	rax, qword ptr [rbx+0x10]
	sub	rax, qword ptr [rcx+0x10]
	mov	dword ptr [rbp-0x2C], eax
$_252:	mov	rcx, qword ptr [rdi+0x8]
	call	SymFind@PLT
	mov	rsi, rax
	mov	dword ptr [rbp-0x20], 1
	cmp	qword ptr [rbp-0x18], 0
	jz	$_255
	test	rsi, rsi
	jz	$_253
	cmp	byte ptr [rsi+0x18], 6
	jnz	$_253
	cmp	byte ptr [rsi+0x19], -63
	jnz	$_253
	mov	eax, dword ptr [rbp-0xA0]
	cmp	dword ptr [rsi+0x50], eax
	jz	$_254
$_253:	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS0003+rip]
	mov	ecx, 2007
	call	asmerr@PLT
	inc	dword ptr [rbp-0x28]
	mov	dword ptr [rbp-0x20], 0
$_254:	jmp	$_256

$_255:	test	rsi, rsi
	jz	$_256
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_265

$_256:	cmp	dword ptr [rbp-0x20], 0
	je	$_261
	mov	rsi, qword ptr [rdi+0x8]
	mov	eax, dword ptr [rbp-0xA0]
	add	dword ptr [rbp-0x1C], eax
	mov	ecx, dword ptr [rbp-0x2C]
	lea	ecx, [rcx+0x78]
	call	LclAlloc@PLT
	mov	rdx, rax
	mov	ecx, 120
	mov	rdi, rax
	xor	eax, eax
	rep stosb
	mov	rdi, rdx
	mov	eax, dword ptr [rbp-0x24]
	mov	dword ptr [rdi+0x10], eax
	mov	rcx, rsi
	call	LclDup@PLT
	mov	qword ptr [rdi+0x8], rax
	and	dword ptr [rdi+0x14], 0xFFFFFEFF
	cmp	byte ptr [ModuleInfo+0x1DC+rip], 0
	jz	$_257
	or	byte ptr [rdi+0x15], 0x01
$_257:	mov	byte ptr [rdi+0x18], 6
	mov	byte ptr [rdi+0x19], -63
	mov	eax, dword ptr [rbp-0xA0]
	mov	dword ptr [rdi+0x50], eax
	cmp	qword ptr [rbp-0x18], 0
	jnz	$_258
	mov	rcx, rdi
	call	SymAddGlobal@PLT
$_258:	mov	qword ptr [rdi+0x68], 0
	mov	byte ptr [rdi+0x70], 0
	mov	rcx, qword ptr [rbp-0x10]
	mov	rcx, qword ptr [rcx+0x68]
	cmp	qword ptr [rcx], 0
	jnz	$_259
	mov	qword ptr [rcx], rdi
	mov	qword ptr [rcx+0x8], rdi
	jmp	$_260

$_259:	mov	rdx, qword ptr [rcx+0x8]
	mov	qword ptr [rdx+0x68], rdi
	mov	qword ptr [rcx+0x8], rdi
$_260:	cmp	dword ptr [rbp-0x2C], 0
	jz	$_261
	mov	rcx, qword ptr [rbp-0x38]
	mov	rdx, rdi
	mov	rsi, qword ptr [rcx+0x10]
	lea	rdi, [rdi+0x70]
	mov	ecx, dword ptr [rbp-0x2C]
	rep movsb
	mov	byte ptr [rdi], 0
	mov	rdi, rdx
$_261:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jge	$_264
	cmp	byte ptr [rbx], 44
	jnz	$_262
	cmp	byte ptr [rbx+0x18], 0
	jnz	$_263
$_262:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_265

$_263:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_264:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jl	$_241
$_265:	mov	rsi, qword ptr [rbp-0x10]
	mov	eax, dword ptr [rbp-0x1C]
	cmp	eax, 16
	jbe	$_268
	cmp	eax, 32
	jbe	$_266
	mov	dword ptr [rsi+0x50], 8
	mov	byte ptr [rsi+0x19], 7
	jmp	$_267

$_266:	mov	dword ptr [rsi+0x50], 4
	mov	byte ptr [rsi+0x19], 3
$_267:	jmp	$_270

$_268:	cmp	eax, 8
	jbe	$_269
	mov	dword ptr [rsi+0x50], 2
	mov	byte ptr [rsi+0x19], 1
	jmp	$_270

$_269:	mov	dword ptr [rsi+0x50], 1
	mov	byte ptr [rsi+0x19], 0
$_270:	mov	rcx, qword ptr [rsi+0x68]
	mov	rdi, qword ptr [rcx]
$_271:	test	rdi, rdi
	jz	$_272
	sub	eax, dword ptr [rdi+0x50]
	mov	dword ptr [rdi+0x28], eax
	mov	rdi, qword ptr [rdi+0x68]
	jmp	$_271

$_272:	cmp	qword ptr [rbp-0x18], 0
	jz	$_276
	mov	eax, 1
	cmp	dword ptr [rbp-0x28], 0
	jle	$_273
	dec	eax
	jmp	$_274

$_273:	mov	rdx, qword ptr [rbp-0x18]
	mov	rcx, qword ptr [rbp-0x10]
	call	$_017
$_274:	test	eax, eax
	jnz	$_275
	mov	r8, qword ptr [rsi+0x8]
	lea	rdx, [DS0003+rip]
	mov	ecx, 2007
	call	asmerr@PLT
$_275:	mov	rcx, qword ptr [rbp-0x10]
	call	SymFree@PLT
$_276:	xor	eax, eax
$_277:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

CurrStruct:
	.quad  0x0000000000000000

redef_struct:
	.quad  0x0000000000000000

DS0000:
	.byte  0x00

DS0001:
	.byte  0x4E, 0x4F, 0x4E, 0x55, 0x4E, 0x49, 0x51, 0x55
	.byte  0x45, 0x00

DS0002:
	.byte  0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x75, 0x72
	.byte  0x65, 0x00

DS0003:
	.byte  0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x00


.att_syntax prefix
