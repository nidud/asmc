
.intel_syntax noprefix

.global data_dir

.extern SegOverride
.extern segm_override
.extern quad_resize
.extern omf_OutSelect
.extern ExpandLiterals
.extern Tokenize
.extern StoreLine
.extern UseSavedState
.extern StoreState
.extern UpdateStructSize
.extern CreateStructField
.extern CreateType
.extern CurrStruct
.extern SetCurrOffset
.extern GetCurrOffset
.extern GetSymOfssize
.extern SetSymSegOfs
.extern LstWrite
.extern EmitConstError
.extern EvalOperand
.extern set_frame2
.extern set_frame
.extern sym_ext2int
.extern sym_remove_table
.extern SizeFromMemtype
.extern SpecialTable
.extern SymTables
.extern BackPatch
.extern CreateFixup
.extern tstrcat
.extern tstrcpy
.extern tmemset
.extern OutputBytes
.extern FillDataBytes
.extern asmerr
.extern write_to_file
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern StringBuffer
.extern NameSpace_
.extern SymLookup


.SECTION .text
	.ALIGN	16

$_001:	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rax, [DS0000+rip]
	test	rdx, rdx
	jz	$_002
	mov	rax, qword ptr [rdx+0x8]
$_002:	mov	rdx, rax
	call	asmerr@PLT
	leave
	ret

$_003:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 120
	mov	eax, dword ptr [rdx]
	mov	dword ptr [rbp-0xC], eax
	imul	ebx, eax, 24
	add	rbx, qword ptr [rbp+0x38]
	mov	rdi, qword ptr [rbp+0x28]
	call	GetCurrOffset@PLT
	mov	dword ptr [rbp-0x4], eax
	mov	r8, qword ptr [rdi+0x20]
	mov	edx, 254
	movzx	ecx, byte ptr [rdi+0x19]
	call	SizeFromMemtype@PLT
	mov	dword ptr [rbp-0x8], eax
	cmp	byte ptr [rbx], 9
	jnz	$_004
	cmp	byte ptr [rbx+0x1], 60
	je	$_018
	cmp	byte ptr [rbx+0x1], 123
	je	$_018
$_004:	mov	edx, dword ptr [rbp-0xC]
	mov	rsi, rbx
	xor	ecx, ecx
	mov	byte ptr [rbp-0x19], 0
$_005:	cmp	byte ptr [rbx], 0
	jz	$_013
	cmp	byte ptr [rbx], 40
	jnz	$_006
	inc	ecx
	jmp	$_012

$_006:	cmp	byte ptr [rbx], 41
	jnz	$_007
	dec	ecx
	jmp	$_012

$_007:	test	ecx, ecx
	jnz	$_008
	cmp	byte ptr [rbx], 44
	jnz	$_008
	jmp	$_013

	jmp	$_012

$_008:	cmp	byte ptr [rbx], 7
	jnz	$_009
	cmp	dword ptr [rbx+0x4], 272
	jnz	$_009
	mov	byte ptr [rbp-0x19], 1
	jmp	$_012

$_009:	cmp	dword ptr [rbp-0x8], 1
	jz	$_010
	cmp	dword ptr [rbp-0x8], 2
	jnz	$_012
	test	byte ptr [ModuleInfo+0x334+rip], 0x06
	jz	$_012
$_010:	cmp	byte ptr [rbx], 9
	jnz	$_012
	cmp	byte ptr [rbx+0x1], 34
	jz	$_011
	cmp	byte ptr [rbx+0x1], 39
	jnz	$_012
$_011:	mov	byte ptr [rbp-0x19], 1
$_012:	inc	edx
	add	rbx, 24
	jmp	$_005

$_013:	mov	rcx, qword ptr [rbp+0x30]
	mov	dword ptr [rcx], edx
	cmp	byte ptr [rbp-0x19], 0
	jnz	$_014
	mov	rbx, rsi
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2181
	call	asmerr@PLT
	jmp	$_028

$_014:	mov	rcx, qword ptr [rbx+0x10]
	mov	rbx, rsi
	sub	rcx, qword ptr [rbx+0x10]
	mov	rsi, qword ptr [rbp+0x28]
	cmp	ecx, 2
	jnz	$_016
	mov	eax, dword ptr [rdi+0x58]
	cmp	dword ptr [rdi+0x50], eax
	jnz	$_016
	cmp	byte ptr [rbx+0x1], 34
	jz	$_015
	cmp	byte ptr [rbx+0x1], 39
	jnz	$_016
$_015:	mov	dword ptr [rbp-0x20], 0
	jmp	$_017

$_016:	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rbp-0x14], eax
	movzx	ecx, byte ptr [rdi+0x19]
	and	ecx, 0x20
	mov	dword ptr [rsp+0x48], edx
	mov	dword ptr [rsp+0x40], 0
	mov	dword ptr [rsp+0x38], ecx
	mov	dword ptr [rsp+0x30], 0
	mov	dword ptr [rsp+0x28], 1
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x8]
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0x14]
	call	$_093
	mov	dword ptr [rbp-0x20], eax
$_017:	jmp	$_021

$_018:	mov	rcx, qword ptr [rbp+0x30]
	inc	dword ptr [rcx]
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x18], eax
	inc	eax
	mov	dword ptr [rbp-0x10], eax
	cmp	dword ptr [rbx+0x4], 0
	jnz	$_019
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0x10]
	lea	rcx, [rdi+0x70]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	jmp	$_020

$_019:	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0x10]
	mov	rcx, qword ptr [rbx+0x8]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_020:	movzx	ecx, byte ptr [rdi+0x19]
	and	ecx, 0x20
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rsp+0x48], eax
	mov	dword ptr [rsp+0x40], 0
	mov	dword ptr [rsp+0x38], ecx
	mov	dword ptr [rsp+0x30], 0
	mov	dword ptr [rsp+0x28], 1
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x8]
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0x10]
	call	$_093
	mov	dword ptr [rbp-0x20], eax
	mov	eax, dword ptr [rbp-0x18]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_021:	call	GetCurrOffset@PLT
	sub	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rbp-0x8], eax
	cmp	eax, dword ptr [rdi+0x50]
	jbe	$_022
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2036
	call	asmerr@PLT
	mov	dword ptr [rbp-0x20], eax
	jmp	$_027

$_022:	cmp	eax, dword ptr [rdi+0x50]
	jnc	$_027
	mov	byte ptr [rbp-0x21], 0
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	test	rcx, rcx
	jz	$_023
	mov	rcx, qword ptr [rcx+0x68]
$_023:	test	rcx, rcx
	jz	$_024
	cmp	dword ptr [rcx+0x48], 3
	jnz	$_024
	mov	eax, dword ptr [rdi+0x50]
	sub	eax, dword ptr [rbp-0x8]
	mov	r9d, 1
	mov	r8d, 1
	mov	edx, eax
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	call	SetCurrOffset@PLT
	jmp	$_027

$_024:	mov	eax, dword ptr [rdi+0x58]
	cmp	dword ptr [rdi+0x50], eax
	jnz	$_026
	cmp	byte ptr [rdi+0x70], 34
	jz	$_025
	cmp	byte ptr [rdi+0x70], 39
	jnz	$_026
$_025:	mov	byte ptr [rbp-0x21], 32
$_026:	mov	eax, dword ptr [rdi+0x50]
	sub	eax, dword ptr [rbp-0x8]
	mov	edx, eax
	movsx	ecx, byte ptr [rbp-0x21]
	call	FillDataBytes@PLT
$_027:	mov	eax, dword ptr [rbp-0x20]
$_028:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_029:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 248
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x14], eax
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	sub	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x20], rax
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rsi, qword ptr [rbp+0x40]
	cmp	byte ptr [rbx], 9
	jnz	$_031
	cmp	byte ptr [rbx+0x1], 60
	jz	$_030
	cmp	byte ptr [rbx+0x1], 123
	jz	$_030
	mov	ecx, 2045
	call	asmerr@PLT
	jmp	$_082

$_030:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	inc	eax
	mov	dword ptr [rbp-0x8], eax
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	jmp	$_034

$_031:	test	rsi, rsi
	jz	$_033
	cmp	byte ptr [rbx], 44
	jz	$_032
	cmp	byte ptr [rbx], 0
	jnz	$_033
$_032:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x8], eax
	jmp	$_034

$_033:	mov	rdx, rsi
	mov	ecx, 2181
	call	$_001
	jmp	$_082

$_034:	imul	ebx, dword ptr [rbp-0x8], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rsi, qword ptr [rbp+0x38]
	cmp	word ptr [rsi+0x5A], 4
	jnz	$_035
	xor	eax, eax
	mov	qword ptr [rbp-0x28], rax
	mov	dword ptr [rbp-0x2C], eax
$_035:	mov	rdx, qword ptr [rsi+0x68]
	mov	rdi, qword ptr [rdx]
$_036:	test	rdi, rdi
	je	$_073
	cmp	byte ptr [rdi+0x19], -63
	jne	$_048
	cmp	byte ptr [rbx], 44
	jz	$_037
	cmp	byte ptr [rbx], 0
	jnz	$_040
$_037:	cmp	byte ptr [rdi+0x70], 0
	jz	$_038
	cmp	byte ptr [rdi+0x70], 58
	jz	$_038
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0xC], eax
	inc	dword ptr [rbp-0xC]
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp-0xC]
	lea	rcx, [rdi+0x70]
	call	Tokenize@PLT
	mov	ecx, eax
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x98]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0xC]
	call	EvalOperand@PLT
	mov	dword ptr [rbp-0x2C], 1
	jmp	$_039

$_038:	mov	dword ptr [rbp-0x98], 0
	mov	dword ptr [rbp-0x5C], 0
	mov	qword ptr [rbp-0x88], 0
$_039:	jmp	$_041

$_040:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x98]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x8]
	call	EvalOperand@PLT
	mov	dword ptr [rbp-0x2C], 1
$_041:	cmp	dword ptr [rbp-0x5C], 0
	jnz	$_042
	cmp	qword ptr [rbp-0x88], 0
	jz	$_043
$_042:	mov	ecx, 2026
	call	asmerr@PLT
$_043:	mov	ecx, dword ptr [rdi+0x50]
	cmp	ecx, 32
	jnc	$_044
	mov	eax, 1
	shl	eax, cl
	cmp	dword ptr [rbp-0x98], eax
	jc	$_044
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2071
	call	asmerr@PLT
$_044:	mov	ecx, dword ptr [rdi+0x28]
	cmp	ecx, 64
	jnc	$_047
	mov	eax, dword ptr [rbp-0x98]
	mov	edx, dword ptr [rbp-0x94]
	cmp	cl, 32
	jnc	$_045
	shld	edx, eax, cl
	shl	eax, cl
	jmp	$_046

$_045:	and	ecx, 0x1F
	mov	edx, eax
	xor	eax, eax
	shl	edx, cl
$_046:	or	dword ptr [rbp-0x28], eax
	or	dword ptr [rbp-0x24], edx
$_047:	jmp	$_064

$_048:	cmp	byte ptr [rdi+0x70], 0
	jnz	$_050
	mov	r9, rdi
	mov	r8, qword ptr [rdi+0x20]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp-0x8]
	call	$_029
	cmp	byte ptr [rbx], 9
	jnz	$_049
	inc	dword ptr [rbp-0x8]
$_049:	jmp	$_064

$_050:	test	byte ptr [rdi+0x15], 0x02
	jz	$_052
	cmp	byte ptr [rbx], 0
	jz	$_052
	cmp	byte ptr [rbx], 44
	jz	$_052
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x8]
	mov	rcx, rdi
	call	$_003
	cmp	eax, -1
	jnz	$_051
	imul	ebx, dword ptr [rbp-0x8], 24
	add	rbx, qword ptr [rbp+0x30]
	jmp	$_073

$_051:	jmp	$_064

$_052:	mov	eax, dword ptr [rdi+0x58]
	cmp	dword ptr [rdi+0x50], eax
	jnz	$_054
	cmp	byte ptr [rbx], 9
	jnz	$_054
	cmp	dword ptr [rbx+0x4], 1
	jbe	$_054
	cmp	byte ptr [rbx+0x1], 34
	jz	$_053
	cmp	byte ptr [rbx+0x1], 39
	jnz	$_054
$_053:	mov	ecx, 2041
	call	asmerr@PLT
	inc	dword ptr [rbp-0x8]
	jmp	$_064

$_054:	mov	r8, qword ptr [rdi+0x20]
	mov	edx, 254
	movzx	ecx, byte ptr [rdi+0x19]
	call	SizeFromMemtype@PLT
	mov	dword ptr [rbp-0x10], eax
	cmp	byte ptr [rbx], 0
	jz	$_055
	cmp	byte ptr [rbx], 44
	jne	$_056
$_055:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x9C], eax
	inc	eax
	mov	dword ptr [rbp-0xC], eax
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, eax
	lea	rcx, [rdi+0x70]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	cl, byte ptr [rdi+0x19]
	and	ecx, 0x20
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rsp+0x48], eax
	mov	dword ptr [rsp+0x40], 0
	mov	dword ptr [rsp+0x38], ecx
	mov	dword ptr [rsp+0x30], 0
	mov	dword ptr [rsp+0x28], 1
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x10]
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0xC]
	call	$_093
	mov	eax, dword ptr [rbp-0x9C]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	jmp	$_064

$_056:	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rbp-0xC], eax
	mov	rax, rbx
	xor	edx, edx
	xor	ecx, ecx
$_057:	cmp	byte ptr [rbx], 0
	jz	$_062
	cmp	byte ptr [rbx], 40
	jnz	$_058
	inc	edx
	jmp	$_061

$_058:	cmp	byte ptr [rbx], 41
	jnz	$_059
	dec	edx
	jmp	$_061

$_059:	test	edx, edx
	jnz	$_060
	cmp	byte ptr [rbx], 44
	jnz	$_060
	jmp	$_062

	jmp	$_061

$_060:	cmp	byte ptr [rbx], 7
	jnz	$_061
	cmp	dword ptr [rbx+0x4], 272
	jnz	$_061
	inc	ecx
$_061:	add	rbx, 24
	inc	dword ptr [rbp-0x8]
	jmp	$_057

$_062:	test	ecx, ecx
	jz	$_063
	mov	rdx, qword ptr [rax+0x10]
	mov	ecx, 2181
	call	asmerr@PLT
	jmp	$_064

$_063:	mov	cl, byte ptr [rdi+0x19]
	and	ecx, 0x20
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rsp+0x48], eax
	mov	dword ptr [rsp+0x40], 0
	mov	dword ptr [rsp+0x38], ecx
	mov	dword ptr [rsp+0x30], 0
	mov	dword ptr [rsp+0x28], 1
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x10]
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0xC]
	call	$_093
	cmp	eax, -1
	jnz	$_064
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2104
	call	asmerr@PLT
$_064:	imul	ebx, dword ptr [rbp-0x8], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	word ptr [rsi+0x5A], 4
	jz	$_068
	cmp	qword ptr [rdi+0x68], 0
	jz	$_065
	cmp	word ptr [rsi+0x5A], 2
	jnz	$_066
$_065:	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rbp-0x4], eax
	jmp	$_067

$_066:	mov	rcx, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rcx+0x28]
	mov	dword ptr [rbp-0x4], eax
$_067:	mov	ecx, dword ptr [rdi+0x28]
	add	ecx, dword ptr [rdi+0x50]
	cmp	ecx, eax
	jnc	$_068
	sub	eax, ecx
	mov	r9d, 1
	mov	r8d, 1
	mov	edx, eax
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	call	SetCurrOffset@PLT
$_068:	cmp	word ptr [rsi+0x5A], 2
	jz	$_073
	cmp	qword ptr [rdi+0x68], 0
	jz	$_072
	cmp	byte ptr [rbx], 0
	jz	$_072
	cmp	byte ptr [rbx], 44
	jnz	$_069
	inc	dword ptr [rbp-0x8]
	add	rbx, 24
	jmp	$_072

$_069:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_071

$_070:	inc	dword ptr [rbp-0x8]
	add	rbx, 24
$_071:	cmp	byte ptr [rbx], 0
	jz	$_072
	cmp	byte ptr [rbx], 44
	jnz	$_070
$_072:	mov	rdi, qword ptr [rdi+0x68]
	jmp	$_036

$_073:	cmp	word ptr [rsi+0x5A], 4
	jnz	$_080
	mov	al, byte ptr [rsi+0x19]
	mov	ecx, 4
	jmp	$_077

$_074:	mov	ecx, 1
	jmp	$_078

$_075:	mov	ecx, 2
	jmp	$_078

$_076:	mov	ecx, 8
	jmp	$_078

$_077:	cmp	al, 0
	jz	$_074
	cmp	al, 1
	jz	$_075
	cmp	al, 7
	jz	$_076
$_078:	cmp	dword ptr [rbp-0x2C], 0
	jz	$_079
	xor	r8d, r8d
	mov	edx, ecx
	lea	rcx, [rbp-0x28]
	call	OutputBytes@PLT
	jmp	$_080

$_079:	mov	r9d, 1
	mov	r8d, 1
	mov	edx, ecx
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	call	SetCurrOffset@PLT
$_080:	cmp	byte ptr [rbx], 0
	jz	$_081
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2036
	call	asmerr@PLT
$_081:	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rax, qword ptr [rbp-0x20]
	add	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	xor	eax, eax
$_082:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_083:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, qword ptr [ModuleInfo+0x188+rip]
$_084:	cmp	edx, 1
	jbe	$_085
	dec	edx
	mov	al, byte ptr [rcx+rdx]
	mov	byte ptr [rbx], al
	mov	al, byte ptr [rcx]
	mov	byte ptr [rbx+rdx], al
	inc	rbx
	inc	rcx
	dec	edx
	jmp	$_084

$_085:
	test	edx, edx
	jz	$_086
	mov	al, byte ptr [rcx]
	mov	byte ptr [rbx], al
$_086:	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	leave
	pop	rbx
	ret

$_087:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rsi, rcx
	cmp	byte ptr [rsi+0x40], 47
	jz	$_090
	mov	r8d, 32
	xor	edx, edx
	lea	rcx, [rbp-0x24]
	call	tmemset@PLT
	xor	r8d, r8d
	mov	edx, 254
	movzx	ecx, byte ptr [rsi+0x40]
	call	SizeFromMemtype@PLT
	cmp	eax, dword ptr [rbp+0x20]
	jbe	$_088
	mov	ecx, 2156
	call	asmerr@PLT
	jmp	$_089

$_088:	mov	edx, eax
	mov	rcx, rsi
	call	quad_resize@PLT
$_089:	xor	r8d, r8d
	mov	edx, dword ptr [rbp+0x20]
	lea	rcx, [rsi]
	call	OutputBytes@PLT
	jmp	$_092

$_090:	cmp	dword ptr [rbp+0x20], 16
	jz	$_091
	mov	edx, dword ptr [rbp+0x20]
	mov	rcx, rsi
	call	quad_resize@PLT
$_091:	xor	r8d, r8d
	mov	edx, dword ptr [rbp+0x20]
	lea	rcx, [rsi]
	call	OutputBytes@PLT
$_092:	leave
	pop	rsi
	ret

$_093:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 232
	mov	dword ptr [rbp-0xC], 0
	mov	dword ptr [rbp-0x10], 0
$_094:	cmp	dword ptr [rbp+0x50], 0
	je	$_231
	mov	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rcx]
	mov	dword ptr [rbp-0x4], eax
	imul	ebx, eax, 24
	add	rbx, qword ptr [rbp+0x30]
$_095:	cmp	byte ptr [rbx], 9
	jnz	$_102
	cmp	byte ptr [rbx+0x1], 60
	jz	$_096
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_102
$_096:	mov	rsi, qword ptr [rbp+0x48]
	test	rsi, rsi
	jz	$_102
	jmp	$_098

$_097:	mov	rsi, qword ptr [rsi+0x20]
$_098:	cmp	qword ptr [rsi+0x20], 0
	jnz	$_097
	mov	qword ptr [rbp+0x48], rsi
	cmp	dword ptr [rbp+0x58], 0
	jnz	$_100
	xor	r9d, r9d
	mov	r8, rsi
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp-0x4]
	call	$_029
	cmp	eax, -1
	jnz	$_099
	jmp	$_233

$_099:	jmp	$_101

$_100:	cmp	word ptr [rsi+0x5A], 3
	jnz	$_101
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_101
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 8001
	call	asmerr@PLT
$_101:	inc	dword ptr [rbp-0xC]
	inc	dword ptr [rbp-0x4]
	jmp	$_227

$_102:	mov	rsi, qword ptr [CurrStruct+rip]
	test	rsi, rsi
	je	$_107
	cmp	word ptr [rsi+0x5A], 4
	jne	$_107
	cmp	byte ptr [rbx], 58
	jne	$_107
	inc	dword ptr [rbp-0x4]
	mov	ecx, dword ptr [rbp+0x70]
	dec	ecx
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x90]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_233
	cmp	dword ptr [rbp-0x54], 0
	jz	$_103
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_233

$_103:	mov	ecx, dword ptr [rbp-0x90]
	mov	eax, 32
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_104
	mov	eax, 64
$_104:	test	ecx, ecx
	jnz	$_105
	mov	rdx, qword ptr [rbx-0x28]
	mov	ecx, 2172
	call	asmerr@PLT
	jmp	$_233

	jmp	$_106

$_105:	cmp	ecx, eax
	jbe	$_106
	mov	rdx, qword ptr [rbx-0x28]
	mov	ecx, 2089
	call	asmerr@PLT
	jmp	$_233

$_106:	mov	eax, dword ptr [rsi+0x28]
	add	dword ptr [rsi+0x28], ecx
	mov	rdx, qword ptr [rbp+0x38]
	mov	byte ptr [rdx+0x19], -63
	mov	dword ptr [rdx+0x28], eax
	mov	eax, dword ptr [rbp+0x40]
	mov	dword ptr [rsi+0x50], eax
	mov	dword ptr [rbp+0x40], ecx
	imul	ebx, dword ptr [rbp-0x4], 24
	add	rbx, qword ptr [rbp+0x30]
$_107:	cmp	byte ptr [rbx], 63
	jnz	$_108
	mov	dword ptr [rbp-0x54], -2
	jmp	$_110

$_108:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x90]
	mov	r8d, dword ptr [rbp+0x70]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_109
	jmp	$_233

$_109:	imul	ebx, dword ptr [rbp-0x4], 24
	add	rbx, qword ptr [rbp+0x30]
$_110:	cmp	byte ptr [rbx], 7
	jne	$_126
	cmp	dword ptr [rbx+0x4], 272
	jne	$_126
	cmp	dword ptr [rbp-0x54], 0
	jz	$_113
	mov	rcx, qword ptr [rbp-0x40]
	test	rcx, rcx
	jz	$_111
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_111
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_112

$_111:	mov	ecx, 2026
	call	asmerr@PLT
$_112:	mov	rax, -1
	jmp	$_233

$_113:	cmp	dword ptr [rbp-0x90], 0
	jge	$_114
	mov	ecx, 2092
	call	asmerr@PLT
	jmp	$_233

$_114:	inc	dword ptr [rbp-0x4]
	add	rbx, 24
	cmp	byte ptr [rbx], 40
	jz	$_115
	lea	rdx, [DS0001+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_233

$_115:	inc	dword ptr [rbp-0x4]
	add	rbx, 24
	mov	rax, qword ptr [rbp+0x38]
	test	rax, rax
	jz	$_116
	or	byte ptr [rax+0x15], 0x02
$_116:	cmp	dword ptr [rbp-0x90], 0
	jnz	$_121
	mov	ecx, 1
$_117:	cmp	byte ptr [rbx], 0
	jz	$_120
	cmp	byte ptr [rbx], 40
	jnz	$_118
	inc	ecx
	jmp	$_119

$_118:	cmp	byte ptr [rbx], 41
	jnz	$_119
	dec	ecx
$_119:	test	ecx, ecx
	jz	$_120
	inc	dword ptr [rbp-0x4]
	add	rbx, 24
	jmp	$_117

$_120:	jmp	$_123

$_121:	mov	eax, dword ptr [rbp+0x70]
	mov	dword ptr [rsp+0x48], eax
	mov	eax, dword ptr [rbp+0x68]
	mov	dword ptr [rsp+0x40], eax
	mov	eax, dword ptr [rbp+0x60]
	mov	dword ptr [rsp+0x38], eax
	mov	eax, dword ptr [rbp+0x58]
	mov	dword ptr [rsp+0x30], eax
	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [rsp+0x28], eax
	mov	rax, qword ptr [rbp+0x48]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x4]
	call	$_093
	cmp	eax, -1
	jnz	$_122
	jmp	$_233

$_122:	imul	ebx, dword ptr [rbp-0x4], 24
	add	rbx, qword ptr [rbp+0x30]
$_123:	cmp	byte ptr [rbx], 41
	jz	$_124
	lea	rdx, [DS0002+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_233

$_124:	mov	rcx, qword ptr [rbp+0x38]
	test	rcx, rcx
	jz	$_125
	cmp	dword ptr [rbp+0x68], 0
	jz	$_125
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_125
	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [rcx+0x40], eax
	mul	dword ptr [rbp+0x40]
	mov	dword ptr [rcx+0x38], eax
	mov	dword ptr [rbp+0x68], 0
$_125:	inc	dword ptr [rbp-0x4]
	jmp	$_227

$_126:	mov	rcx, qword ptr [rbp+0x48]
	test	rcx, rcx
	jz	$_129
	jmp	$_128

$_127:	mov	rcx, qword ptr [rcx+0x20]
$_128:	cmp	qword ptr [rcx+0x20], 0
	jnz	$_127
	cmp	word ptr [rcx+0x5A], 3
	jz	$_129
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2179
	call	asmerr@PLT
	jmp	$_233

$_129:	cmp	dword ptr [rbp-0x54], -2
	jnz	$_133
	cmp	byte ptr [rbx], 63
	jnz	$_133
	mov	eax, dword ptr [rbp+0x40]
	mov	dword ptr [rbp-0x90], eax
	mov	rcx, qword ptr [rbp+0x28]
	mov	edx, dword ptr [rbp-0x4]
	cmp	byte ptr [rbx+0x18], 44
	jz	$_130
	cmp	edx, dword ptr [rcx]
	jnz	$_130
	mul	dword ptr [rbp+0x50]
	mov	dword ptr [rbp-0x90], eax
	mov	eax, dword ptr [rbp+0x50]
	add	dword ptr [rbp-0xC], eax
	mov	dword ptr [rbp+0x50], 1
	jmp	$_131

$_130:	inc	dword ptr [rbp-0xC]
$_131:	cmp	dword ptr [rbp+0x58], 0
	jnz	$_132
	mov	r9d, 1
	mov	r8d, 1
	mov	edx, dword ptr [rbp-0x90]
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	call	SetCurrOffset@PLT
$_132:	inc	dword ptr [rbp-0x4]
	jmp	$_227

$_133:	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_136
	cmp	dword ptr [rbp+0x58], 0
	jnz	$_136
	cmp	dword ptr [rbp-0x10], 0
	jnz	$_136
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rcx, qword ptr [rcx+0x68]
	cmp	dword ptr [rcx+0x48], 3
	jz	$_134
	cmp	dword ptr [rcx+0x48], 5
	jnz	$_136
$_134:	lea	rax, [DS0003+rip]
	cmp	dword ptr [rcx+0x48], 3
	jnz	$_135
	lea	rax, [DS0004+rip]
$_135:	mov	rdx, rax
	mov	ecx, 8006
	call	asmerr@PLT
	mov	dword ptr [rbp-0x10], 1
$_136:	mov	eax, dword ptr [rbp-0x54]
	jmp	$_226

$_137:	cmp	byte ptr [rbx], 0
	jz	$_138
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_139

$_138:	lea	rdx, [DS0004+0x3+rip]
	mov	ecx, 2008
	call	asmerr@PLT
$_139:	jmp	$_233

$_140:	cmp	dword ptr [rbp+0x58], 0
	jnz	$_141
	mov	edx, dword ptr [rbp+0x40]
	lea	rcx, [rbp-0x90]
	call	$_087
$_141:	inc	dword ptr [rbp-0xC]
	jmp	$_227

$_142:	cmp	dword ptr [rbp+0x60], 0
	jz	$_143
	mov	ecx, 2187
	call	asmerr@PLT
	jmp	$_233

$_143:	cmp	qword ptr [rbp-0x80], 0
	je	$_158
	mov	rcx, qword ptr [rbp-0x80]
	mov	rsi, qword ptr [rcx+0x8]
	inc	rsi
	mov	rdi, qword ptr [rbp+0x38]
	mov	eax, dword ptr [rcx+0x4]
	mov	dword ptr [rbp-0x8], eax
	test	eax, eax
	jnz	$_145
	cmp	dword ptr [rbp+0x58], 1
	jnz	$_144
	or	byte ptr [rdi+0x15], 0x02
	jmp	$_145

$_144:	mov	ecx, 2047
	call	asmerr@PLT
	jmp	$_233

$_145:	cmp	dword ptr [rbp+0x40], 1
	jz	$_147
	cmp	eax, dword ptr [rbp+0x40]
	jbe	$_147
	cmp	dword ptr [rbp+0x58], 1
	jz	$_146
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_146
	test	byte ptr [ModuleInfo+0x334+rip], 0x06
	jz	$_146
	cmp	dword ptr [rbp+0x40], 2
	jz	$_147
$_146:	mov	ecx, 2071
	call	asmerr@PLT
	jmp	$_233

$_147:	test	rdi, rdi
	jz	$_150
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_150
	cmp	eax, 0
	jbe	$_150
	inc	dword ptr [rbp-0xC]
	xor	ecx, ecx
	cmp	dword ptr [rbp+0x40], 1
	jnz	$_148
	cmp	eax, 1
	jbe	$_148
	inc	ecx
	jmp	$_149

$_148:	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_149
	test	byte ptr [ModuleInfo+0x334+rip], 0x06
	jz	$_149
	cmp	dword ptr [rbp+0x40], 2
	jnz	$_149
	cmp	eax, 1
	jbe	$_149
	mov	ecx, 2
$_149:	test	ecx, ecx
	jz	$_150
	dec	eax
	add	dword ptr [rbp-0xC], eax
	or	byte ptr [rdi+0x15], 0x02
	cmp	dword ptr [rbp+0x68], 0
	jz	$_150
	mov	dword ptr [rdi+0x40], 1
	mov	dword ptr [rdi+0x38], ecx
	mov	dword ptr [rbp+0x68], 0
$_150:	cmp	dword ptr [rbp+0x58], 0
	jne	$_157
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_154
	test	byte ptr [ModuleInfo+0x334+rip], 0x06
	jz	$_154
	cmp	dword ptr [rbp-0x8], 1
	jle	$_154
	cmp	dword ptr [rbp+0x40], 2
	jnz	$_154
	test	rdi, rdi
	jnz	$_153
	mov	edi, dword ptr [rbp-0x8]
	jmp	$_152

$_151:	xor	r8d, r8d
	mov	edx, 1
	mov	rcx, rsi
	call	OutputBytes@PLT
	mov	edx, 1
	xor	ecx, ecx
	call	FillDataBytes@PLT
	inc	rsi
	dec	edi
$_152:	test	edi, edi
	jnz	$_151
$_153:	jmp	$_156

$_154:	cmp	dword ptr [rbp-0x8], 1
	jle	$_155
	cmp	dword ptr [rbp+0x40], 1
	jbe	$_155
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, rsi
	call	$_083
	mov	rsi, rax
$_155:	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, rsi
	call	OutputBytes@PLT
$_156:	mov	eax, dword ptr [rbp-0x8]
	cmp	dword ptr [rbp+0x40], eax
	jle	$_157
	mov	eax, dword ptr [rbp+0x40]
	sub	eax, dword ptr [rbp-0x8]
	mov	edx, eax
	xor	ecx, ecx
	call	FillDataBytes@PLT
$_157:	jmp	$_168

$_158:	cmp	dword ptr [rbp+0x58], 0
	jne	$_167
	cmp	dword ptr [rbp+0x40], 16
	jbe	$_160
	xor	r8d, r8d
	mov	edx, 16
	lea	rcx, [rbp-0x90]
	call	OutputBytes@PLT
	mov	ecx, 255
	cmp	byte ptr [rbp-0x81], -128
	jnc	$_159
	xor	ecx, ecx
$_159:	mov	edx, dword ptr [rbp+0x40]
	sub	edx, 16
	movzx	ecx, cl
	call	FillDataBytes@PLT
	jmp	$_167

$_160:	cmp	dword ptr [rbp+0x40], 8
	jbe	$_161
	xor	eax, eax
	test	byte ptr [rbp-0x4D], 0x20
	jz	$_161
	test	byte ptr [rbp-0x89], 0xFFFFFF80
	jz	$_161
	cmp	dword ptr [rbp-0x88], eax
	jnz	$_161
	cmp	dword ptr [rbp-0x84], eax
	jnz	$_161
	dec	eax
	mov	dword ptr [rbp-0x88], eax
	mov	dword ptr [rbp-0x84], eax
$_161:	xor	r8d, r8d
	mov	edx, dword ptr [rbp+0x40]
	lea	rcx, [rbp-0x90]
	call	OutputBytes@PLT
	cmp	dword ptr [rbp+0x40], 8
	ja	$_165
	mov	eax, 255
	cmp	byte ptr [rbp-0x89], -128
	jnc	$_162
	xor	eax, eax
$_162:	lea	rdi, [rbp-0x90]
	mov	ecx, dword ptr [rbp+0x40]
	rep stosb
	mov	eax, dword ptr [rbp-0x90]
	mov	edx, dword ptr [rbp-0x8C]
	test	eax, eax
	jnz	$_163
	test	edx, edx
	jz	$_164
$_163:	cmp	eax, -1
	jz	$_164
	cmp	edx, -1
	jz	$_164
	mov	rdx, qword ptr [rbp-0x40]
	mov	ecx, 2071
	call	$_001
	jmp	$_233

$_164:	jmp	$_167

$_165:	cmp	dword ptr [rbp+0x40], 10
	jnz	$_167
	cmp	dword ptr [rbp-0x84], 0
	jnz	$_166
	cmp	dword ptr [rbp-0x88], 65535
	jbe	$_167
$_166:	cmp	dword ptr [rbp-0x84], -1
	ja	$_167
	cmp	dword ptr [rbp-0x88], -65535
	jnc	$_167
	mov	rdx, qword ptr [rbp-0x40]
	mov	ecx, 2071
	call	$_001
	jmp	$_233

$_167:	inc	dword ptr [rbp-0xC]
$_168:	jmp	$_227

$_169:	cmp	dword ptr [rbp+0x40], 8
	jbe	$_170
	mov	rdx, qword ptr [rbp+0x38]
	mov	ecx, 2104
	call	$_001
	jmp	$_227

$_170:	test	byte ptr [rbp-0x4D], 0x01
	jz	$_171
	mov	ecx, 2032
	call	asmerr@PLT
	jmp	$_227

$_171:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jz	$_173
	cmp	dword ptr [rbp-0x8C], 0
	jz	$_173
	cmp	dword ptr [rbp-0x8C], -1
	jnz	$_172
	cmp	dword ptr [rbp-0x90], 0
	jl	$_173
$_172:	lea	rcx, [rbp-0x90]
	call	EmitConstError@PLT
	jmp	$_233

$_173:	cmp	dword ptr [rbp+0x60], 0
	jz	$_174
	mov	ecx, 2187
	call	asmerr@PLT
	jmp	$_227

$_174:	inc	dword ptr [rbp-0xC]
	cmp	dword ptr [rbp+0x58], 1
	je	$_227
	mov	eax, dword ptr [rbp-0x58]
	xor	edi, edi
	mov	rsi, qword ptr [rbp-0x40]
	jmp	$_222
$C00E9:
	cmp	dword ptr [rbp+0x40], 2
	jnc	$_175
	mov	ecx, 2071
	call	asmerr@PLT
$_175:	mov	edi, 8
	jmp	$_223
$C00EC:
	mov	eax, dword ptr [rbp+0x40]
	jmp	$_183

$_176:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_177
	test	rsi, rsi
	jz	$_177
	cmp	byte ptr [rsi+0x18], 0
	jnz	$_177
	mov	edi, 0
	jmp	$_178

$_177:	mov	ecx, 2071
	call	asmerr@PLT
	mov	edi, 4
$_178:	jmp	$_184

$_179:	mov	edi, 5
	jmp	$_184

$_180:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_181
	mov	edi, 7
	jmp	$_184

$_181:	mov	edi, 6
	test	rsi, rsi
	jz	$_182
	mov	rcx, rsi
	call	GetSymOfssize@PLT
	test	rax, rax
	jnz	$_182
	mov	edi, 5
$_182:	jmp	$_184

$_183:	cmp	eax, 1
	jz	$_176
	cmp	eax, 2
	jz	$_179
	cmp	eax, 8
	jz	$_180
	jmp	$_181

$_184:	jmp	$_223
$C00F8:
	cmp	dword ptr [rbp+0x40], 4
	jnc	$_185
	mov	ecx, 2071
	call	asmerr@PLT
$_185:	mov	edi, 12
	jmp	$_223
$C00FA:
	cmp	dword ptr [rbp+0x40], 4
	jnc	$_186
	mov	ecx, 2071
	call	asmerr@PLT
$_186:	mov	edi, 13
	jmp	$_223
$C00FC:
	mov	edi, 4
	jmp	$_223
$C00FE:
	mov	edi, 11
	jmp	$_223
$C0100:
	mov	edi, 5
	cmp	dword ptr [rbp+0x40], 2
	jnc	$_187
	mov	ecx, 2071
	call	asmerr@PLT
$_187:	jmp	$_223
$C0102:
	mov	edi, 0
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_223
$C0104:
	mov	edi, 6
	cmp	dword ptr [rbp+0x40], 4
	jnc	$_188
	mov	ecx, 2071
	call	asmerr@PLT
$_188:	jmp	$_223

$C0106: cmp	dword ptr [rbp+0x40], 2
	jnc	$_192
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_189
	test	rsi, rsi
	jz	$_189
	cmp	byte ptr [rsi+0x18], 0
	jnz	$_189
	jmp	$_192

$_189:	test	rsi, rsi
	jz	$_190
	cmp	byte ptr [rsi+0x18], 2
	jnz	$_190
	test	byte ptr [rbp-0x4D], 0x04
	jz	$_190
	jmp	$_191

$_190:	mov	ecx, 2071
	call	asmerr@PLT
$_191:	mov	edi, 4
	jmp	$_223

$_192:	test	rsi, rsi
	jz	$_194
	cmp	byte ptr [rsi+0x18], 3
	jz	$_193
	cmp	byte ptr [rsi+0x18], 4
	jnz	$_194
$_193:	mov	edi, 8
	jmp	$_223

$_194:	jmp	$_220

$_195:	test	byte ptr [rbp-0x4D], 0x02
	jz	$_197
	mov	r8, qword ptr [rbp-0x30]
	movzx	edx, byte ptr [rbp-0x4E]
	movzx	ecx, byte ptr [rbp-0x50]
	call	SizeFromMemtype@PLT
	cmp	eax, dword ptr [rbp+0x40]
	jbe	$_196
	mov	rdx, rsi
	mov	ecx, 2071
	call	$_001
$_196:	jmp	$_199

$_197:	test	rsi, rsi
	jz	$_198
	cmp	byte ptr [rsi+0x18], 2
	jnz	$_198
	test	byte ptr [rbp-0x4D], 0x04
	jz	$_198
	jmp	$_199

$_198:	test	rsi, rsi
	jz	$_199
	cmp	byte ptr [rsi+0x18], 0
	jz	$_199
	mov	rcx, rsi
	call	GetSymOfssize@PLT
	cmp	rax, 0
	jbe	$_199
	mov	rdx, rsi
	mov	ecx, 2071
	call	$_001
$_199:	mov	edi, 5
	jmp	$_221

$_200:	test	byte ptr [rbp-0x4D], 0x02
	jz	$_205
	cmp	byte ptr [rbp-0x50], -126
	jnz	$_202
	cmp	byte ptr [rbp-0x4E], -2
	jz	$_201
	cmp	byte ptr [rbp-0x4E], 0
	jz	$_201
	mov	rdx, rsi
	mov	ecx, 2071
	call	$_001
$_201:	mov	edi, 9
	jmp	$_204

$_202:	cmp	byte ptr [rbp-0x50], -127
	jnz	$_204
	mov	edi, 6
	cmp	byte ptr [rbp-0x4E], 0
	jnz	$_203
	mov	edi, 5
	jmp	$_204

$_203:	test	rsi, rsi
	jz	$_204
	mov	rcx, rsi
	call	GetSymOfssize@PLT
	test	rax, rax
	jnz	$_204
	mov	edi, 5
$_204:	jmp	$_210

$_205:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jnz	$_209
	cmp	byte ptr [rbp-0x50], -127
	jnz	$_207
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_206
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_207
$_206:	mov	edi, 5
	mov	rdx, qword ptr [rbp+0x38]
	mov	ecx, 2004
	call	$_001
	jmp	$_208

$_207:	mov	edi, 9
$_208:	jmp	$_210

$_209:	mov	edi, 6
$_210:	jmp	$_221

$_211:	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_212
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_213
$_212:	mov	edi, 6
	jmp	$_214

$_213:	mov	edi, 10
$_214:	jmp	$_221

$_215:	test	byte ptr [rbp-0x4D], 0x02
	jz	$_216
	cmp	byte ptr [rbp-0x50], -126
	jnz	$_216
	cmp	byte ptr [rbp-0x4E], 1
	jnz	$_216
	mov	edi, 10
	jmp	$_219

$_216:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 1
	jnz	$_217
	mov	edi, 6
	jmp	$_219

$_217:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_218
	mov	edi, 7
	jmp	$_219

$_218:	mov	edi, 9
$_219:	jmp	$_221

$_220:	cmp	dword ptr [rbp+0x40], 2
	je	$_195
	cmp	dword ptr [rbp+0x40], 4
	je	$_200
	cmp	dword ptr [rbp+0x40], 6
	jz	$_211
	jmp	$_215

$_221:	jmp	$_223

$_222:	cmp	eax, 235
	jl	$C0106
	cmp	eax, 252
	jg	$C0106
	push	rax
	lea	r11, [$C0106+rip]
	movzx	eax, byte ptr [r11+rax-(235)+(IT$C0133-$C0106)]
	movzx	eax, word ptr [r11+rax*2+($C0133-$C0106)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C0133:
	.word $C0106-$C00E9
	.word $C0106-$C00EC
	.word $C0106-$C00F8
	.word $C0106-$C00FA
	.word $C0106-$C00FC
	.word $C0106-$C00FE
	.word $C0106-$C0100
	.word $C0106-$C0102
	.word $C0106-$C0104
	.word 0
IT$C0133:
	.byte 5
	.byte 5
	.byte 7
	.byte 7
	.byte 2
	.byte 9
	.byte 9
	.byte 4
	.byte 4
	.byte 8
	.byte 6
	.byte 9
	.byte 9
	.byte 9
	.byte 1
	.byte 9
	.byte 3
	.byte 0
	.ALIGN 2
$C00EB:
$_223:	mov	dword ptr [rbp-0x20], edi
	mov	eax, 1
	mov	ecx, edi
	shl	eax, cl
	mov	rcx, qword ptr [ModuleInfo+0x1A8+rip]
	movzx	edx, word ptr [rcx+0x8]
	test	edx, eax
	jz	Unnamed_1_1463
	lea	rdx, [DS0004+0x3+rip]
	test	rsi, rsi
	jz	Unnamed_1_144D
	mov	rdx, qword ptr [rsi+0x8]
Unnamed_1_144D:
	mov	r8, rdx
	lea	rdx, [rcx+0xA]
	mov	ecx, 3001
	call	asmerr@PLT
	jmp	$_233

Unnamed_1_1463:
	mov	qword ptr [rbp-0x28], 0
	cmp	dword ptr [write_to_file+rip], 0
	jz	Unnamed_1_14CF
	mov	qword ptr [SegOverride+rip], 0
	xor	edx, edx
	lea	rcx, [rbp-0x90]
	call	segm_override@PLT
	cmp	byte ptr [ModuleInfo+0x1BB+rip], 2
	jnz	Unnamed_1_14B3
	cmp	dword ptr [rbp-0x58], 249
	jz	Unnamed_1_14A8
	cmp	dword ptr [rbp-0x58], 252
	jnz	Unnamed_1_14B3
Unnamed_1_14A8:
	mov	rcx, qword ptr [rbp-0x40]
	call	set_frame2@PLT
	jmp	Unnamed_1_14BC

Unnamed_1_14B3:
	mov	rcx, qword ptr [rbp-0x40]
	call	set_frame@PLT
Unnamed_1_14BC:
	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0x20]
	mov	rcx, qword ptr [rbp-0x40]
	call	CreateFixup@PLT
	mov	qword ptr [rbp-0x28], rax
Unnamed_1_14CF:
	mov	r8, qword ptr [rbp-0x28]
	mov	edx, dword ptr [rbp+0x40]
	lea	rcx, [rbp-0x90]
	call	OutputBytes@PLT
	jmp	$_227

$_224:	mov	ecx, 2032
	call	asmerr@PLT
	jmp	$_227

$_225:	lea	rdx, [DS0004+0x3+rip]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_233

	jmp	$_227

$_226:	cmp	eax, -2
	je	$_137
	cmp	eax, 3
	je	$_140
	cmp	eax, 0
	je	$_142
	cmp	eax, 1
	je	$_169
	cmp	eax, 2
	jz	$_224
	jmp	$_225

$_227:	mov	rcx, qword ptr [rbp+0x38]
	test	rcx, rcx
	jz	$_228
	cmp	dword ptr [rbp+0x68], 0
	jz	$_228
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_228
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rcx+0x40], eax
	mul	dword ptr [rbp+0x40]
	mov	dword ptr [rcx+0x38], eax
$_228:	imul	ebx, dword ptr [rbp-0x4], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbp+0x70]
	cmp	dword ptr [rbp-0x4], eax
	jge	$_230
	cmp	byte ptr [rbx], 44
	jnz	$_230
	inc	dword ptr [rbp-0x4]
	add	rbx, 24
	cmp	byte ptr [rbx], 0
	jz	$_230
	cmp	byte ptr [rbx], 41
	jz	$_230
	mov	dword ptr [rbp+0x68], 0
	test	rcx, rcx
	jz	$_229
	or	byte ptr [rcx+0x15], 0x02
$_229:	jmp	$_095

$_230:	dec	dword ptr [rbp+0x50]
	jmp	$_094

$_231:	mov	rcx, qword ptr [rbp+0x38]
	test	rcx, rcx
	jz	$_232
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_232
	mov	eax, dword ptr [rbp-0xC]
	add	dword ptr [rcx+0x58], eax
	mul	dword ptr [rbp+0x40]
	add	dword ptr [rcx+0x50], eax
$_232:	mov	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rcx], eax
	xor	eax, eax
$_233:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_234:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	al, byte ptr [rcx+0x19]
	cmp	al, -64
	jz	$_239
	mov	ah, byte ptr [rbp+0x18]
	mov	rdx, qword ptr [rbp+0x20]
	jmp	$_236

$_235:	mov	ah, byte ptr [rdx+0x19]
	mov	rdx, qword ptr [rdx+0x20]
$_236:	cmp	ah, -60
	jz	$_235
	mov	rdx, rcx
	jmp	$_238

$_237:	mov	al, byte ptr [rdx+0x19]
	mov	rdx, qword ptr [rdx+0x20]
$_238:	cmp	al, -60
	jz	$_237
	cmp	al, ah
	jz	$_239
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_240

$_239:	xor	eax, eax
$_240:	leave
	ret

data_dir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 376
	mov	dword ptr [rbp-0x14], 0
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp+0x28], 1
	jle	$_241
	cmp	byte ptr [ModuleInfo+0x1D6+rip], 0
	jnz	$_241
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_288

$_241:	cmp	byte ptr [rbx+0x18], 0
	jnz	$_242
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_288

$_242:	mov	dword ptr [rbp-0x18], 1
	cmp	byte ptr [rbx], 5
	jne	$_245
	mov	esi, dword ptr [rbp+0x28]
	lea	rdx, [DS0005+rip]
	lea	rcx, [rbp-0x128]
	call	tstrcpy@PLT
	cmp	byte ptr [rbx+0x18], 63
	jz	$_244
	cmp	byte ptr [rbx+0x18], 10
	jz	$_244
	inc	dword ptr [rbp-0x18]
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 5
	jnz	$_243
	lea	rdx, [DS0005+rip]
	lea	rcx, [rbp-0x128]
	call	tstrcat@PLT
	cmp	byte ptr [rbx+0x18], 63
	jz	$_243
	cmp	byte ptr [rbx+0x18], 10
	jz	$_243
	inc	dword ptr [rbp+0x28]
	inc	dword ptr [rbp-0x18]
	add	rbx, 24
$_243:	cmp	byte ptr [rbx], 63
	jz	$_244
	cmp	byte ptr [rbx], 10
	jz	$_244
	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [rbp-0x128]
	call	tstrcat@PLT
$_244:	lea	r9, [rbp+0x38]
	lea	r8, [rbp-0x128]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, esi
	call	CreateType@PLT
	cmp	eax, -1
	jnz	$_245
	jmp	$_288

$_245:	mov	rsi, qword ptr [rbp+0x38]
	test	rsi, rsi
	jz	$_251
	mov	byte ptr [rbp-0xD], -60
	mov	rdi, qword ptr [rsi+0x68]
	cmp	word ptr [rsi+0x5A], 3
	jz	$_247
	cmp	dword ptr [rsi+0x50], 0
	jz	$_246
	test	byte ptr [rdi+0x11], 0x04
	jz	$_247
$_246:	mov	ecx, 2159
	call	asmerr@PLT
	jmp	$_288

$_247:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_248
	cmp	dword ptr [UseSavedState+rip], 0
	jnz	$_249
$_248:	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	mov	rdx, qword ptr [rbp+0x30]
	call	ExpandLiterals@PLT
$_249:	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rbp-0x4], eax
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_250
	cmp	word ptr [rsi+0x5A], 3
	jnz	$_250
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_288

$_250:	jmp	$_257

$_251:	mov	eax, dword ptr [rbx+0x4]
	cmp	byte ptr [rbx], 6
	jnz	$_252
	jmp	$_254

$_252:	cmp	byte ptr [rbx], 3
	jnz	$_253
	cmp	byte ptr [rbx+0x1], 8
	jnz	$_253
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	eax, dword ptr [r11+rax+0x4]
	jmp	$_254

$_253:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_288

$_254:	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0xD], al
	mov	ecx, eax
	and	ecx, 0xC0
	cmp	cl, -128
	jnz	$_255
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_288

$_255:	test	eax, 0x20
	jz	$_256
	mov	dword ptr [rbp-0x14], 1
$_256:	and	eax, 0x1F
	inc	eax
	mov	dword ptr [rbp-0x4], eax
$_257:	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rdx+0x8]
	mov	eax, dword ptr [rbp-0x18]
	cmp	dword ptr [rbp+0x28], eax
	jz	$_258
	xor	ecx, ecx
$_258:	mov	qword ptr [rbp-0x28], rcx
	xor	esi, esi
	cmp	qword ptr [CurrStruct+rip], 0
	je	$_263
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_261
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsp+0x28], eax
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rsp+0x20], rax
	movzx	r9d, byte ptr [rbp-0xD]
	mov	r8, qword ptr [rbp-0x28]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp+0x28]
	call	CreateStructField@PLT
	mov	rsi, rax
	test	rax, rax
	jnz	$_259
	mov	rax, -1
	jmp	$_288

$_259:	cmp	dword ptr [StoreState+rip], 0
	jz	$_260
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_260
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_260:	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rbp-0xC], eax
	or	byte ptr [rsi+0x15], 0x04
	jmp	$_262

$_261:	mov	rdx, qword ptr [CurrStruct+rip]
	mov	rdi, qword ptr [rdx+0x68]
	mov	rsi, qword ptr [rdi+0x8]
	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rbp-0xC], eax
	mov	rax, qword ptr [rsi+0x68]
	mov	qword ptr [rdi+0x8], rax
$_262:	jmp	$_282

$_263:	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jnz	$_264
	mov	ecx, 2034
	call	asmerr@PLT
	jmp	$_288

$_264:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_265
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_265:	cmp	byte ptr [ModuleInfo+0x1EE+rip], 0
	jz	$_266
	mov	ecx, 1
	call	omf_OutSelect@PLT
$_266:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_267
	call	GetCurrOffset@PLT
	mov	dword ptr [rbp-0xC], eax
$_267:	cmp	qword ptr [rbp-0x28], 0
	je	$_279
	mov	rdx, qword ptr [rbp-0x28]
	mov	rax, qword ptr [rbp-0x28]
	call	NameSpace_@PLT
	mov	qword ptr [rbp-0x28], rax
	mov	rcx, qword ptr [rbp-0x28]
	call	SymLookup@PLT
	mov	rsi, rax
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_276
	cmp	byte ptr [rsi+0x18], 2
	jnz	$_268
	test	byte ptr [rsi+0x3B], 0x02
	jz	$_268
	test	byte ptr [rsi+0x15], 0x08
	jnz	$_268
	mov	r8, qword ptr [rbp+0x38]
	movzx	edx, byte ptr [rbp-0xD]
	mov	rcx, rsi
	call	$_234
	mov	rcx, rsi
	call	sym_ext2int@PLT
	mov	dword ptr [rsi+0x50], 0
	mov	dword ptr [rsi+0x58], 0
	mov	dword ptr [rsi+0x40], 0
	jmp	$_275

$_268:	cmp	byte ptr [rsi+0x18], 0
	jnz	$_270
	mov	rdx, rsi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	mov	byte ptr [rsi+0x18], 1
	cmp	byte ptr [rsi+0x1A], 0
	jnz	$_269
	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	mov	byte ptr [rsi+0x1A], al
$_269:	jmp	$_275

$_270:	cmp	byte ptr [rsi+0x18], 1
	jnz	$_274
	call	GetCurrOffset@PLT
	mov	ecx, eax
	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	cmp	qword ptr [rsi+0x30], rax
	jnz	$_271
	cmp	dword ptr [rsi+0x28], ecx
	jz	$_272
$_271:	mov	rdx, qword ptr [rbp-0x28]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_288

$_272:	mov	r8, qword ptr [rbp+0x38]
	movzx	edx, byte ptr [rbp-0xD]
	mov	rcx, rsi
	call	$_234
	cmp	eax, -1
	jnz	$_273
	mov	rax, -1
	jmp	$_288

$_273:	mov	dword ptr [rsi+0x50], 0
	mov	dword ptr [rsi+0x58], 0
	jmp	$_277

	jmp	$_275

$_274:	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_288

$_275:	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdx, qword ptr [rcx+0x68]
	mov	rax, qword ptr [rdx+0x20]
	mov	qword ptr [rsi+0x70], rax
	mov	qword ptr [rdx+0x20], rsi
	jmp	$_277

$_276:	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rbp-0x8], eax
$_277:	mov	rcx, rsi
	call	SetSymSegOfs@PLT
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_278
	mov	eax, dword ptr [rbp-0x8]
	cmp	dword ptr [rsi+0x28], eax
	jz	$_278
	mov	byte ptr [ModuleInfo+0x1ED+rip], 1
$_278:	or	dword ptr [rsi+0x14], 0x402
	mov	al, byte ptr [rbp-0xD]
	mov	byte ptr [rsi+0x19], al
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rsi+0x20], rax
	mov	rcx, rsi
	call	BackPatch@PLT
$_279:	mov	rdi, qword ptr [rbp+0x38]
	test	rdi, rdi
	jz	$_282
	jmp	$_281

$_280:	mov	rdi, qword ptr [rdi+0x20]
$_281:	cmp	byte ptr [rdi+0x19], -60
	jz	$_280
	cmp	word ptr [rdi+0x5A], 3
	jnz	$_282
	mov	qword ptr [rbp+0x38], 0
$_282:	inc	dword ptr [rbp+0x28]
	xor	ecx, ecx
	cmp	rcx, qword ptr [CurrStruct+rip]
	setne	cl
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rsp+0x48], eax
	mov	dword ptr [rsp+0x40], 1
	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rsp+0x38], eax
	mov	dword ptr [rsp+0x30], ecx
	mov	dword ptr [rsp+0x28], 1
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x4]
	mov	r8, rsi
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_093
	cmp	eax, -1
	jnz	$_283
	jmp	$_288

$_283:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_284
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_288

$_284:	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_285
	mov	rcx, rsi
	call	UpdateStructSize@PLT
$_285:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_287
	mov	ecx, 0
	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_286
	mov	ecx, 6
$_286:	mov	r8, rsi
	mov	edx, dword ptr [rbp-0xC]
	call	LstWrite@PLT
$_287:	xor	eax, eax
$_288:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x00

DS0001:
	.byte  0x28, 0x00

DS0002:
	.byte  0x29, 0x00

DS0003:
	.byte  0x41, 0x54, 0x00

DS0004:
	.byte  0x42, 0x53, 0x53, 0x00

DS0005:
	.byte  0x70, 0x74, 0x72, 0x3F, 0x00


.att_syntax prefix
