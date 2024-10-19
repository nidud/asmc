
.intel_syntax noprefix

.global ExterndefDirective
.global ProtoDirective
.global MakeExtern
.global ExternDirective
.global CommDirective
.global PublicDirective

.extern AddPublicData
.extern CopyPrototype
.extern CreateProc
.extern ParseProc
.extern GetQualifiedType
.extern EmitConstError
.extern EvalOperand
.extern SetMangler
.extern sym_remove_table
.extern sym_add_table
.extern GetLangType
.extern MemtypeFromSize
.extern SymTables
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind
.extern SymCreate


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	test	rsi, rsi
	jnz	$_002
	mov	rcx, rdx
	call	SymCreate@PLT
	mov	rsi, rax
	jmp	$_003

$_002:	mov	rdx, rsi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
$_003:	test	rsi, rsi
	jz	$_005
	mov	byte ptr [rsi+0x18], 2
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rsi+0x1B], al
	and	byte ptr [rsi+0x3B], 0xFFFFFFFC
	cmp	byte ptr [rbp+0x28], 0
	jz	$_004
	or	byte ptr [rsi+0x3B], 0x02
$_004:	mov	rdx, rsi
	lea	rcx, [SymTables+0x10+rip]
	call	sym_add_table@PLT
$_005:	mov	rax, rsi
	leave
	pop	rsi
	ret

$_006:
	push	rsi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	test	rsi, rsi
	jnz	$_007
	mov	rcx, rdx
	call	SymCreate@PLT
	mov	rsi, rax
	jmp	$_008

$_007:	mov	rdx, rsi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
$_008:	test	rsi, rsi
	jz	$_009
	mov	byte ptr [rsi+0x18], 2
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rsi+0x1B], al
	mov	byte ptr [rsi+0x1C], 0
	and	byte ptr [rsi+0x3B], 0xFFFFFFFD
	or	byte ptr [rsi+0x3B], 0x01
	mov	rdx, rsi
	lea	rcx, [SymTables+0x10+rip]
	call	sym_add_table@PLT
$_009:	mov	rax, rsi
	leave
	pop	rsi
	ret

$_010:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rcx, qword ptr [rbp+0x38]
	call	SymFind@PLT
	mov	rsi, rax
	test	rsi, rsi
	jz	$_011
	cmp	byte ptr [rsi+0x18], 0
	jz	$_011
	cmp	byte ptr [rsi+0x18], 2
	jnz	$_013
	test	byte ptr [rsi+0x3B], 0x02
	jz	$_013
	test	byte ptr [rsi+0x15], 0x08
	jnz	$_013
$_011:	mov	r8d, 2
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, rsi
	call	CreateProc@PLT
	test	rax, rax
	jnz	$_012
	jmp	$_021

$_012:	mov	rsi, rax
	jmp	$_014

$_013:	test	byte ptr [rsi+0x15], 0x08
	jnz	$_014
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_021

$_014:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 8
	jnz	$_015
	mov	rdi, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rdi]
	or	al, 0x20
	cmp	ax, 99
	jnz	$_015
	mov	byte ptr [rbx], 7
	mov	dword ptr [rbx+0x4], 277
	mov	byte ptr [rbx+0x1], 1
$_015:	cmp	byte ptr [rbx], 8
	jnz	$_017
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rdi, rax
	test	rax, rax
	jz	$_017
	cmp	byte ptr [rax+0x18], 7
	jnz	$_017
	cmp	byte ptr [rax+0x19], -128
	jnz	$_017
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 0
	jz	$_016
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_021

$_016:	mov	rdx, qword ptr [rdi+0x40]
	mov	rcx, rsi
	call	CopyPrototype@PLT
	mov	rax, rsi
	jmp	$_021

$_017:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_019
	movzx	eax, byte ptr [rbp+0x40]
	mov	dword ptr [rsp+0x20], eax
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, rsi
	call	ParseProc@PLT
	cmp	eax, -1
	jnz	$_018
	xor	eax, eax
	jmp	$_021

$_018:	mov	rax, qword ptr [ModuleInfo+0x1A0+rip]
	mov	qword ptr [rsi+0x50], rax
	jmp	$_020

$_019:	or	byte ptr [rsi+0x14], 0x02
$_020:	mov	rax, rsi
$_021:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ExterndefDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	inc	dword ptr [rbp+0x28]
$_022:	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x15], al
	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	mov	byte ptr [rbp-0x9], al
	lea	r8, [rbp-0x9]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetLangType@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 8
	jz	$_023
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_054

$_023:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 58
	jz	$_024
	lea	rdx, [DS0000+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_054

$_024:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	mov	rsi, rax
	mov	byte ptr [rbp-0x18], -64
	mov	dword ptr [rbp-0x28], 0
	mov	byte ptr [rbp-0x17], 0
	mov	byte ptr [rbp-0x16], 0
	mov	byte ptr [rbp-0x14], -64
	mov	qword ptr [rbp-0x20], 0
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x15], al
	mov	rcx, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rcx]
	or	eax, 0x202020
	cmp	byte ptr [rbx], 8
	jnz	$_025
	cmp	eax, 7561825
	jnz	$_025
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_028

$_025:	cmp	byte ptr [rbx], 3
	jnz	$_027
	cmp	dword ptr [rbx+0x4], 507
	jnz	$_027
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	movzx	r9d, byte ptr [rbp-0x9]
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rbp+0x30]
	call	$_010
	test	rax, rax
	jz	$_026
	xor	eax, eax
	jmp	$_054

$_026:	mov	rax, -1
	jmp	$_054

	jmp	$_028

$_027:	cmp	byte ptr [rbx], 0
	jz	$_028
	cmp	byte ptr [rbx], 44
	jz	$_028
	lea	r8, [rbp-0x28]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	je	$_054
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
$_028:	mov	byte ptr [rbp-0xA], 0
	test	rsi, rsi
	jz	$_029
	cmp	byte ptr [rsi+0x18], 0
	jnz	$_030
$_029:	mov	r8d, 1
	mov	rdx, qword ptr [rbp-0x8]
	mov	rcx, rsi
	call	$_001
	mov	rsi, rax
	mov	byte ptr [rbp-0xA], 1
	jmp	$_031

$_030:	cmp	byte ptr [rsi+0x18], 1
	jz	$_031
	cmp	byte ptr [rsi+0x18], 2
	jz	$_031
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2014
	call	asmerr@PLT
	jmp	$_054

$_031:	mov	rdi, qword ptr [rbp-0x20]
	cmp	byte ptr [rbp-0xA], 0
	je	$_041
	cmp	byte ptr [rbp-0x17], 0
	jnz	$_032
	test	rdi, rdi
	jz	$_032
	test	byte ptr [rdi+0x15], 0x08
	jz	$_032
	mov	r8d, 2
	xor	edx, edx
	mov	rcx, rsi
	call	CreateProc@PLT
	mov	rdx, rdi
	mov	rcx, rsi
	call	CopyPrototype@PLT
	mov	al, byte ptr [rdi+0x19]
	mov	byte ptr [rbp-0x18], al
	mov	qword ptr [rbp-0x20], 0
$_032:	jmp	$_036

$_033:	jmp	$_037

$_034:	cmp	byte ptr [Options+0x98+rip], 0
	jnz	$_037
$_035:	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	mov	qword ptr [rsi+0x30], rax
	jmp	$_037

$_036:	cmp	byte ptr [rbp-0x18], -64
	jz	$_033
	cmp	byte ptr [rbp-0x18], -126
	jz	$_034
	jmp	$_035

$_037:	mov	al, byte ptr [rbp-0x15]
	mov	byte ptr [rsi+0x38], al
	mov	al, byte ptr [rbp-0x15]
	cmp	byte ptr [rbp-0x17], 0
	jnz	$_038
	cmp	al, byte ptr [ModuleInfo+0x1CC+rip]
	jz	$_038
	mov	byte ptr [rsi+0x1B], al
	mov	rcx, qword ptr [rsi+0x30]
	test	rcx, rcx
	jz	$_038
	mov	rdx, qword ptr [rcx+0x68]
	cmp	al, byte ptr [rdx+0x68]
	jz	$_038
	mov	qword ptr [rsi+0x30], 0
$_038:	mov	al, byte ptr [rbp-0x18]
	mov	byte ptr [rsi+0x19], al
	mov	al, byte ptr [rbp-0x17]
	mov	byte ptr [rsi+0x39], al
	mov	al, byte ptr [rbp-0x16]
	mov	byte ptr [rsi+0x1C], al
	mov	al, byte ptr [rbp-0x14]
	mov	byte ptr [rsi+0x3A], al
	mov	rax, qword ptr [rbp-0x20]
	cmp	byte ptr [rbp-0x18], -60
	jnz	$_039
	mov	qword ptr [rsi+0x20], rax
	jmp	$_040

$_039:	mov	qword ptr [rsi+0x40], rax
$_040:	xor	r8d, r8d
	movzx	edx, byte ptr [rbp-0x9]
	mov	rcx, rsi
	call	SetMangler@PLT
	jmp	$_050

$_041:	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_050
	cmp	byte ptr [rbp-0x17], 0
	jnz	$_042
	test	rdi, rdi
	jz	$_042
	test	byte ptr [rdi+0x15], 0x08
	jz	$_042
	mov	al, byte ptr [rdi+0x19]
	mov	byte ptr [rbp-0x18], al
	mov	qword ptr [rbp-0x20], 0
$_042:	mov	al, byte ptr [rbp-0x18]
	cmp	byte ptr [rsi+0x19], al
	jz	$_043
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 8004
	call	asmerr@PLT
	jmp	$_048

$_043:	cmp	byte ptr [rsi+0x19], -60
	jnz	$_048
	mov	rax, qword ptr [rbp-0x20]
	cmp	qword ptr [rsi+0x20], rax
	jz	$_048
	mov	rcx, rsi
	jmp	$_045

$_044:	mov	rcx, qword ptr [rcx+0x20]
$_045:	cmp	qword ptr [rcx+0x20], 0
	jnz	$_044
	jmp	$_047

$_046:	mov	rdi, qword ptr [rdi+0x20]
$_047:	cmp	qword ptr [rdi+0x20], 0
	jnz	$_046
	cmp	rcx, rdi
	jz	$_048
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 8004
	call	asmerr@PLT
$_048:	cmp	byte ptr [rbp-0x9], 0
	jz	$_049
	mov	al, byte ptr [rbp-0x9]
	cmp	byte ptr [rsi+0x1A], al
	jz	$_049
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 7000
	call	asmerr@PLT
$_049:	cmp	byte ptr [rsi+0x18], 1
	jnz	$_050
	test	dword ptr [rsi+0x14], 0x80
	jnz	$_050
	or	dword ptr [rsi+0x14], 0x80
	mov	rcx, rsi
	call	AddPublicData@PLT
$_050:	or	byte ptr [rsi+0x14], 0x02
	cmp	byte ptr [rbx], 0
	jz	$_053
	cmp	byte ptr [rbx], 44
	jnz	$_052
	mov	eax, dword ptr [rbp+0x28]
	inc	eax
	cmp	eax, dword ptr [ModuleInfo+0x220+rip]
	jge	$_051
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_051:	jmp	$_053

$_052:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_054

$_053:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jl	$_022
	xor	eax, eax
$_054:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ProtoDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rdx
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_056
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_055
	test	byte ptr [rax+0x15], 0x08
	jz	$_055
	or	byte ptr [rax+0x14], 0x02
$_055:	xor	eax, eax
	jmp	$_059

$_056:	cmp	dword ptr [rbp+0x18], 1
	jz	$_057
	imul	ecx, dword ptr [rbp+0x18], 24
	mov	rdx, qword ptr [rbx+rcx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_059

$_057:	movzx	r9d, byte ptr [ModuleInfo+0x1B6+rip]
	mov	r8, qword ptr [rbx+0x8]
	mov	rdx, qword ptr [rbp+0x20]
	mov	ecx, 2
	call	$_010
	test	rax, rax
	jz	$_058
	mov	eax, 0
	jmp	$_059

$_058:	mov	eax, 4294967295
$_059:	leave
	pop	rbx
	ret

MakeExtern:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_001
	test	rax, rax
	jnz	$_060
	jmp	$_063

$_060:	mov	rcx, rax
	cmp	byte ptr [rbp+0x18], -64
	jz	$_062
	cmp	byte ptr [Options+0x98+rip], 0
	jz	$_061
	cmp	byte ptr [rbp+0x18], -126
	jz	$_062
$_061:	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	mov	qword ptr [rcx+0x30], rax
$_062:	or	byte ptr [rcx+0x14], 0x02
	mov	al, byte ptr [rbp+0x18]
	mov	byte ptr [rcx+0x19], al
	mov	al, byte ptr [rbp+0x30]
	mov	byte ptr [rcx+0x1B], al
	mov	rax, qword ptr [rbp+0x20]
	mov	qword ptr [rcx+0x20], rax
	mov	rax, rcx
$_063:	leave
	ret

$_064:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, qword ptr [rbp+0x30]
	cmp	qword ptr [rbp+0x28], 0
	je	$_076
	cmp	byte ptr [rsi+0x18], 2
	jne	$_076
	mov	rcx, qword ptr [rbp+0x28]
	call	SymFind@PLT
	mov	rdi, rax
	cmp	qword ptr [rsi+0x58], 0
	jz	$_065
	cmp	qword ptr [rsi+0x58], rdi
	jz	$_065
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_077

$_065:	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_071
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_066
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_070

$_066:	cmp	byte ptr [rdi+0x18], 1
	jz	$_067
	cmp	byte ptr [rdi+0x18], 2
	jz	$_067
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_070

$_067:	cmp	byte ptr [rdi+0x18], 1
	jnz	$_069
	test	dword ptr [rdi+0x14], 0x80
	jnz	$_069
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_068
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_069
$_068:	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 2217
	call	asmerr@PLT
$_069:	mov	al, byte ptr [rdi+0x19]
	cmp	byte ptr [rsi+0x19], al
	jz	$_070
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 2004
	call	asmerr@PLT
$_070:	jmp	$_076

$_071:	test	rdi, rdi
	jz	$_073
	cmp	byte ptr [rdi+0x18], 1
	jz	$_072
	cmp	byte ptr [rdi+0x18], 2
	jz	$_072
	cmp	byte ptr [rdi+0x18], 0
	jz	$_072
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_077

$_072:	jmp	$_074

$_073:	mov	rcx, qword ptr [rbp+0x28]
	call	SymCreate@PLT
	mov	rdi, rax
	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_add_table@PLT
$_074:	cmp	dword ptr [Options+0xA4+rip], 1
	jz	$_075
	or	byte ptr [rdi+0x14], 0x01
$_075:	cmp	qword ptr [rsi+0x58], 0
	jnz	$_076
	mov	qword ptr [rsi+0x58], rdi
$_076:	xor	eax, eax
$_077:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ExternDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 104
	inc	dword ptr [rbp+0x28]
$_078:	mov	qword ptr [rbp-0x28], 0
	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	mov	byte ptr [rbp-0x1], al
	lea	r8, [rbp-0x1]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetLangType@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 8
	jz	$_079
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_110

$_079:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x30], rax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 40
	jnz	$_082
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 8
	jz	$_080
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_110

$_080:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x28], rax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 41
	jz	$_081
	lea	rdx, [DS0001+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_110

$_081:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_082:	cmp	byte ptr [rbx], 58
	jz	$_083
	lea	rdx, [DS0002+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_110

$_083:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	rcx, qword ptr [rbp-0x30]
	call	SymFind@PLT
	mov	rdi, rax
	mov	byte ptr [rbp-0x10], -64
	mov	dword ptr [rbp-0x20], 0
	mov	byte ptr [rbp-0xF], 0
	mov	byte ptr [rbp-0xE], 0
	mov	byte ptr [rbp-0xC], -64
	mov	qword ptr [rbp-0x18], 0
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0xD], al
	xor	eax, eax
	cmp	byte ptr [rbx], 8
	jnz	$_084
	mov	rcx, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rcx]
	or	eax, 0x202020
$_084:	cmp	eax, 7561825
	jnz	$_085
	inc	dword ptr [rbp+0x28]
	jmp	$_090

$_085:	cmp	byte ptr [rbx], 3
	jnz	$_089
	cmp	dword ptr [rbx+0x4], 507
	jnz	$_089
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	movzx	r9d, byte ptr [rbp-0x1]
	mov	r8, qword ptr [rbp-0x30]
	mov	rdx, qword ptr [rbp+0x30]
	call	$_010
	mov	rdi, rax
	test	rdi, rdi
	jnz	$_086
	mov	rax, -1
	jmp	$_110

$_086:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_087
	and	byte ptr [rdi+0x3B], 0xFFFFFFFD
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x28]
	call	$_064
	jmp	$_110

	jmp	$_088

$_087:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_110

$_088:	jmp	$_090

$_089:	cmp	byte ptr [rbx], 0
	jz	$_090
	cmp	byte ptr [rbx], 44
	jz	$_090
	lea	r8, [rbp-0x20]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	jnz	$_090
	mov	rax, -1
	jmp	$_110

$_090:	test	rdi, rdi
	jz	$_091
	cmp	byte ptr [rdi+0x18], 0
	jne	$_096
$_091:	xor	ecx, ecx
	cmp	byte ptr [rbp-0x10], -60
	jnz	$_092
	mov	rcx, qword ptr [rbp-0x18]
$_092:	movzx	edx, byte ptr [rbp-0xD]
	cmp	byte ptr [rbp-0xF], 0
	jz	$_093
	mov	dl, byte ptr [ModuleInfo+0x1CC+rip]
$_093:	mov	byte ptr [rsp+0x20], dl
	mov	r9, rdi
	mov	r8, rcx
	movzx	edx, byte ptr [rbp-0x10]
	mov	rcx, qword ptr [rbp-0x30]
	call	MakeExtern
	test	rax, rax
	jnz	$_094
	mov	rax, -1
	jmp	$_110

$_094:	mov	rdi, rax
	mov	rsi, qword ptr [rbp-0x18]
	cmp	byte ptr [rbp-0xF], 0
	jnz	$_095
	test	rsi, rsi
	jz	$_095
	test	byte ptr [rsi+0x15], 0x08
	jz	$_095
	mov	r8d, 2
	xor	edx, edx
	mov	rcx, rdi
	call	CreateProc@PLT
	and	byte ptr [rdi+0x3B], 0xFFFFFFFD
	mov	rdx, rsi
	mov	rcx, rdi
	call	CopyPrototype@PLT
	mov	al, byte ptr [rsi+0x19]
	mov	byte ptr [rbp-0x10], al
	mov	qword ptr [rbp-0x18], 0
$_095:	jmp	$_103

$_096:	cmp	byte ptr [rdi+0x18], 1
	jnz	$_097
	cmp	byte ptr [rdi+0x19], -64
	jnz	$_097
	jmp	$_098

$_097:	cmp	byte ptr [rdi+0x18], 2
	jz	$_098
	mov	rdx, qword ptr [rbp-0x30]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_110

$_098:	mov	rsi, qword ptr [rbp-0x18]
	cmp	byte ptr [rbp-0xF], 0
	jnz	$_099
	test	rsi, rsi
	jz	$_099
	test	byte ptr [rsi+0x15], 0x08
	jz	$_099
	mov	al, byte ptr [rsi+0x19]
	mov	byte ptr [rbp-0x10], al
	mov	qword ptr [rbp-0x18], 0
$_099:	mov	rdx, qword ptr [rdi+0x40]
	cmp	byte ptr [rdi+0x19], -60
	jnz	$_100
	mov	rdx, qword ptr [rdi+0x20]
$_100:	mov	al, byte ptr [rbp-0x10]
	cmp	byte ptr [rdi+0x19], al
	jnz	$_102
	mov	al, byte ptr [rbp-0xF]
	cmp	byte ptr [rdi+0x39], al
	jnz	$_102
	mov	al, byte ptr [rbp-0xE]
	cmp	byte ptr [rdi+0x1C], al
	jnz	$_102
	cmp	byte ptr [rdi+0x39], 0
	jz	$_101
	mov	al, byte ptr [rbp-0xC]
	cmp	byte ptr [rdi+0x3A], al
	jnz	$_102
$_101:	cmp	rdx, qword ptr [rbp-0x18]
	jnz	$_102
	cmp	byte ptr [rbp-0x1], 0
	jz	$_103
	cmp	byte ptr [rdi+0x1A], 0
	jz	$_103
	mov	al, byte ptr [rbp-0x1]
	cmp	byte ptr [rdi+0x1A], al
	jz	$_103
$_102:	mov	rdx, qword ptr [rbp-0x30]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_110

$_103:	or	byte ptr [rdi+0x14], 0x02
	mov	al, byte ptr [rbp-0xD]
	mov	byte ptr [rdi+0x38], al
	cmp	byte ptr [rbp-0xF], 0
	jnz	$_105
	cmp	al, byte ptr [ModuleInfo+0x1CC+rip]
	jz	$_105
	mov	byte ptr [rdi+0x1B], al
	mov	rcx, qword ptr [rdi+0x30]
	test	rcx, rcx
	jz	$_104
	mov	rdx, qword ptr [rcx+0x68]
$_104:	test	rcx, rcx
	jz	$_105
	cmp	byte ptr [rdx+0x68], al
	jz	$_105
	mov	qword ptr [rdi+0x30], 0
$_105:	mov	al, byte ptr [rbp-0x10]
	mov	byte ptr [rdi+0x19], al
	mov	al, byte ptr [rbp-0xF]
	mov	byte ptr [rdi+0x39], al
	mov	al, byte ptr [rbp-0xE]
	mov	byte ptr [rdi+0x1C], al
	mov	al, byte ptr [rbp-0xC]
	mov	byte ptr [rdi+0x3A], al
	cmp	byte ptr [rbp-0x10], -60
	jnz	$_106
	mov	rax, qword ptr [rbp-0x18]
	mov	qword ptr [rdi+0x20], rax
	jmp	$_107

$_106:	mov	rax, qword ptr [rbp-0x18]
	mov	qword ptr [rdi+0x40], rax
$_107:	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x28]
	call	$_064
	xor	r8d, r8d
	movzx	edx, byte ptr [rbp-0x1]
	mov	rcx, rdi
	call	SetMangler@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_109
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	cmp	byte ptr [rbx], 44
	jnz	$_108
	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_108
	inc	dword ptr [rbp+0x28]
	jmp	$_109

$_108:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_110

$_109:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jl	$_078
	xor	eax, eax
$_110:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_111:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x20]
	call	$_006
	mov	rdi, rax
	test	rdi, rdi
	jz	$_115
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rdi+0x58], eax
	mov	al, byte ptr [rbp+0x38]
	mov	byte ptr [rdi+0x1C], al
	cmp	byte ptr [Options+0x98+rip], 0
	jz	$_112
	cmp	byte ptr [rbp+0x38], 0
	jnz	$_113
$_112:	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	mov	qword ptr [rdi+0x30], rax
$_113:	lea	rdx, [rdi+0x19]
	mov	ecx, dword ptr [rbp+0x28]
	call	MemtypeFromSize@PLT
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jnz	$_114
	mov	eax, dword ptr [rbp+0x28]
	mul	dword ptr [rbp+0x30]
	cmp	eax, 65536
	jbe	$_114
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 8003
	call	asmerr@PLT
$_114:	mov	eax, dword ptr [rbp+0x28]
	mul	dword ptr [rbp+0x30]
	mov	dword ptr [rdi+0x50], eax
	mov	rax, rdi
$_115:	leave
	pop	rdi
	ret

CommDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	inc	dword ptr [rbp+0x28]
$_116:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jge	$_144
	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	mov	byte ptr [rbp-0x91], al
	lea	r8, [rbp-0x91]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetLangType@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	byte ptr [rbp-0x9], 0
	cmp	byte ptr [rbx], 6
	jnz	$_121
	jmp	$_120

$_117:	cmp	byte ptr [ModuleInfo+0x1B5+rip], 7
	jnz	$_118
	mov	ecx, 2178
	call	asmerr@PLT
	jmp	$_119

$_118:	mov	byte ptr [rbp-0x9], 1
$_119:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_121

$_120:	cmp	dword ptr [rbx+0x4], 227
	jz	$_117
	cmp	dword ptr [rbx+0x4], 230
	jz	$_117
	cmp	dword ptr [rbx+0x4], 231
	jz	$_117
	cmp	dword ptr [rbx+0x4], 226
	jz	$_119
	cmp	dword ptr [rbx+0x4], 228
	jz	$_119
	cmp	dword ptr [rbx+0x4], 229
	jz	$_119
$_121:	cmp	byte ptr [rbx], 8
	jz	$_122
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_145

$_122:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 58
	jz	$_123
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_145

$_123:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	ecx, dword ptr [rbp+0x28]
	mov	rdx, rbx
$_124:	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_125
	cmp	byte ptr [rdx], 58
	jz	$_125
	inc	ecx
	add	rdx, 24
	jmp	$_124

$_125:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x90]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_126
	mov	rax, -1
	jmp	$_145

$_126:	mov	al, byte ptr [rbp-0x50]
	and	al, 0xFFFFFFC0
	cmp	dword ptr [rbp-0x54], 0
	jz	$_127
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_130

$_127:	cmp	al, -128
	jnz	$_128
	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2104
	call	asmerr@PLT
	jmp	$_130

$_128:	cmp	dword ptr [rbp-0x8C], 0
	jz	$_129
	cmp	dword ptr [rbp-0x8C], -1
	jz	$_129
	lea	rcx, [rbp-0x90]
	call	EmitConstError@PLT
	jmp	$_130

$_129:	cmp	dword ptr [rbp-0x90], 0
	jnz	$_130
	mov	ecx, 2090
	call	asmerr@PLT
$_130:	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [rbp-0x14], eax
	mov	rax, qword ptr [rbp-0x30]
	mov	qword ptr [rbp-0x28], rax
	mov	dword ptr [rbp-0x18], 1
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 58
	jne	$_135
	inc	dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x90]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_131
	mov	rax, -1
	jmp	$_145

$_131:	cmp	dword ptr [rbp-0x54], 0
	jz	$_132
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_134

$_132:	cmp	dword ptr [rbp-0x8C], 0
	jz	$_133
	cmp	dword ptr [rbp-0x8C], -1
	jz	$_133
	lea	rcx, [rbp-0x90]
	call	EmitConstError@PLT
	jmp	$_134

$_133:	cmp	dword ptr [rbp-0x90], 0
	jnz	$_134
	mov	ecx, 2090
	call	asmerr@PLT
$_134:	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [rbp-0x18], eax
$_135:	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	mov	rdi, rax
	test	rdi, rdi
	jz	$_136
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_138
$_136:	movzx	eax, byte ptr [rbp-0x9]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x18]
	mov	r8d, dword ptr [rbp-0x14]
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x8]
	call	$_111
	mov	rdi, rax
	test	rdi, rdi
	jnz	$_137
	mov	rax, -1
	jmp	$_145

$_137:	mov	rax, qword ptr [rbp-0x28]
	mov	qword ptr [rdi+0x20], rax
	jmp	$_142

$_138:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_139
	test	byte ptr [rdi+0x3B], 0x01
	jnz	$_140
$_139:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_145

	jmp	$_142

$_140:	mov	eax, dword ptr [rdi+0x50]
	cdq
	div	dword ptr [rdi+0x58]
	mov	ecx, dword ptr [rbp-0x18]
	cmp	ecx, dword ptr [rdi+0x58]
	jnz	$_141
	cmp	dword ptr [rbp-0x14], eax
	jz	$_142
$_141:	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS0003+rip]
	mov	ecx, 2007
	call	asmerr@PLT
	jmp	$_145

$_142:	or	byte ptr [rdi+0x14], 0x02
	xor	r8d, r8d
	movzx	edx, byte ptr [rbp-0x91]
	mov	rcx, rdi
	call	SetMangler@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_143
	cmp	byte ptr [rbx], 44
	jz	$_143
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_145

$_143:	inc	dword ptr [rbp+0x28]
	jmp	$_116

$_144:	xor	eax, eax
$_145:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

PublicDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	inc	dword ptr [rbp+0x28]
$_146:	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	mov	byte ptr [rbp-0x12], al
	lea	r8, [rbp-0x12]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetLangType@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 8
	jz	$_147
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_167

$_147:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	mov	rdi, rax
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_150
	test	rdi, rdi
	jnz	$_149
	mov	rcx, qword ptr [rbp-0x8]
	call	SymCreate@PLT
	test	rax, rax
	jz	$_148
	mov	rdi, rax
	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_add_table@PLT
	jmp	$_149

$_148:	mov	rax, -1
	jmp	$_167

$_149:	mov	byte ptr [rbp-0x11], 0
	jmp	$_152

$_150:	test	rdi, rdi
	jz	$_151
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_152
$_151:	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2006
	call	asmerr@PLT
$_152:	test	rdi, rdi
	je	$_163
	jmp	$_160

$_153:	jmp	$_161

$_154:	test	byte ptr [rdi+0x14], 0x04
	jz	$_155
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2014
	call	asmerr@PLT
	mov	byte ptr [rbp-0x11], 1
$_155:	jmp	$_161

$_156:	test	byte ptr [rdi+0x3B], 0x01
	jz	$_157
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2014
	call	asmerr@PLT
	mov	byte ptr [rbp-0x11], 1
	jmp	$_158

$_157:	test	byte ptr [rdi+0x3B], 0x02
	jnz	$_158
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	mov	byte ptr [rbp-0x11], 1
$_158:	jmp	$_161

$_159:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2014
	call	asmerr@PLT
	mov	byte ptr [rbp-0x11], 1
	jmp	$_161

$_160:	cmp	byte ptr [rdi+0x18], 0
	jz	$_153
	cmp	byte ptr [rdi+0x18], 1
	jz	$_154
	cmp	byte ptr [rdi+0x18], 2
	jz	$_156
	jmp	$_159

$_161:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_163
	cmp	byte ptr [rbp-0x11], 0
	jnz	$_163
	test	dword ptr [rdi+0x14], 0x80
	jnz	$_162
	or	dword ptr [rdi+0x14], 0x80
	mov	rcx, rdi
	call	AddPublicData@PLT
$_162:	xor	r8d, r8d
	movzx	edx, byte ptr [rbp-0x12]
	mov	rcx, rdi
	call	SetMangler@PLT
$_163:	cmp	byte ptr [rbx], 0
	jz	$_166
	cmp	byte ptr [rbx], 44
	jnz	$_165
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_164
	inc	dword ptr [rbp+0x28]
$_164:	jmp	$_166

$_165:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_167

$_166:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jl	$_146
	xor	eax, eax
$_167:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x63, 0x6F, 0x6C, 0x6F, 0x6E, 0x00

DS0001:
	.byte  0x29, 0x00

DS0002:
	.byte  0x3A, 0x00

DS0003:
	.byte  0x43, 0x4F, 0x4D, 0x4D, 0x00


.att_syntax prefix
