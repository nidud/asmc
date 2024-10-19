
.intel_syntax noprefix

.global EqualSgnDirective
.global CreateVariable
.global CreateConstant
.global EquDirective

.extern ParseOperator
.extern EvalOperator
.extern _atoow
.extern LstWrite
.extern SaveVariableState
.extern StoreLine
.extern StoreState
.extern SetTextMacro
.extern ExpandLineItems
.extern EmitConstError
.extern EvalOperand
.extern sym_ext2int
.extern sym_remove_table
.extern SymTables
.extern BackPatch
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern NameSpace_
.extern SymFind
.extern SymCreate


.SECTION .text
	.ALIGN	16

$_001:	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	byte ptr [rcx+0x18], 1
	or	byte ptr [rcx+0x14], 0x12
	and	dword ptr [rcx+0x14], 0xFFFFF7FF
	cmp	dword ptr [rdx+0x3C], 0
	jz	$_002
	cmp	dword ptr [rdx+0x3C], 3
	jnz	$_004
	cmp	qword ptr [rdx+0x10], 0
	jnz	$_004
$_002:	mov	eax, dword ptr [rdx]
	mov	dword ptr [rcx+0x28], eax
	mov	eax, dword ptr [rdx+0x4]
	mov	dword ptr [rcx+0x50], eax
	mov	al, byte ptr [rdx+0x40]
	mov	byte ptr [rcx+0x19], al
	cmp	al, 47
	jnz	$_003
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_003
	mov	eax, dword ptr [rdx+0x8]
	mov	dword ptr [rcx+0x58], eax
	mov	eax, dword ptr [rdx+0xC]
	mov	dword ptr [rcx+0x60], eax
$_003:	mov	qword ptr [rcx+0x30], 0
	jmp	$_010

$_004:	mov	rdi, qword ptr [rdx+0x50]
	test	byte ptr [rdi+0x15], 0x08
	jz	$_005
	or	byte ptr [rcx+0x15], 0x08
	mov	al, byte ptr [rdi+0x1A]
	mov	byte ptr [rcx+0x1A], al
	mov	rax, qword ptr [rdi+0x68]
	mov	qword ptr [rcx+0x68], rax
$_005:	mov	al, byte ptr [rdx+0x40]
	mov	byte ptr [rcx+0x19], al
	cmp	byte ptr [rdi+0x19], -60
	jnz	$_006
	test	byte ptr [rdx+0x43], 0x02
	jnz	$_006
	mov	al, byte ptr [rdi+0x19]
	mov	byte ptr [rcx+0x19], al
	mov	rax, qword ptr [rdi+0x20]
	mov	qword ptr [rcx+0x20], rax
$_006:	mov	dword ptr [rcx+0x50], 0
	mov	rax, qword ptr [rdi+0x30]
	mov	qword ptr [rcx+0x30], rax
	mov	eax, dword ptr [rdi+0x28]
	add	eax, dword ptr [rdx]
	test	byte ptr [rcx+0x14], 0x40
	jz	$_008
	mov	dword ptr [rcx+0x28], eax
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_007
	test	byte ptr [rcx+0x15], 0x20
	jz	$_007
	mov	byte ptr [ModuleInfo+0x1ED+rip], 1
$_007:	jmp	$_010

$_008:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_009
	cmp	dword ptr [rcx+0x28], eax
	jz	$_009
	mov	byte ptr [ModuleInfo+0x1ED+rip], 1
$_009:	mov	dword ptr [rcx+0x28], eax
	call	BackPatch@PLT
$_010:	leave
	pop	rdi
	ret

$_011:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 280
	mov	dword ptr [rbp-0x14], 2
	mov	rbx, rcx
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x10], rax
	add	rbx, 48
	cmp	byte ptr [rbx], 10
	jnz	$_015
	cmp	byte ptr [rbx+0x18], 0
	jnz	$_015
	mov	r9d, dword ptr [rbx+0x4]
	movsx	r8d, byte ptr [rbx+0x1]
	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [rbp-0x80]
	call	_atoow@PLT
$_012:	mov	dword ptr [rbp-0x44], 0
	mov	byte ptr [rbp-0x40], -64
	mov	rax, qword ptr [rbp-0x78]
	test	rax, rax
	jnz	$_013
	movzx	ecx, byte ptr [ModuleInfo+0x1CC+rip]
	lea	rsi, [minintvalues+rip]
	lea	rdi, [maxintvalues+rip]
	mov	rdx, qword ptr [rbp-0x80]
	cmp	rdx, qword ptr [rsi+rcx*8]
	setl	al
	cmp	rdx, qword ptr [rdi+rcx*8]
	setg	ah
$_013:	test	rax, rax
	jz	$_014
	lea	rcx, [rbp-0x80]
	call	EmitConstError@PLT
	xor	eax, eax
	jmp	$_040

$_014:	jmp	$_027

$_015:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x80]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x14]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_040
	imul	ebx, dword ptr [rbp-0x14], 24
	add	rbx, qword ptr [rbp+0x28]
	cmp	byte ptr [rbx], 0
	jz	$_016
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_040

$_016:	mov	rcx, qword ptr [rbp-0x30]
	cmp	dword ptr [rbp-0x44], 0
	jz	$_017
	cmp	dword ptr [rbp-0x44], 1
	jnz	$_018
	test	byte ptr [rbp-0x3D], 0x01
	jnz	$_018
$_017:	test	rcx, rcx
	je	$_024
	cmp	byte ptr [rcx+0x18], 1
	je	$_024
$_018:	test	rcx, rcx
	jz	$_020
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_020
	test	byte ptr [rbp-0x3D], 0x01
	jnz	$_020
	cmp	dword ptr [StoreState+rip], 0
	jnz	$_019
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_019
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_019:	jmp	$_023

$_020:	test	rcx, rcx
	jnz	$_021
	cmp	dword ptr [rbp-0x44], 3
	jnz	$_021
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_021
	mov	byte ptr [rbp-0x40], 47
	mov	dword ptr [rbp-0x44], 0
	mov	qword ptr [rbp-0x70], 0
	jmp	$_027

	jmp	$_023

$_021:	mov	dword ptr [rbp-0x14], 0
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0xE8]
	mov	r8d, 1
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x14]
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_022
	mov	rcx, qword ptr [rbp+0x28]
	add	rcx, 24
	mov	r8, rcx
	lea	rdx, [rbp-0x80]
	lea	rcx, [rbp-0xE8]
	call	EvalOperator@PLT
	cmp	eax, -1
	jz	$_022
	mov	rdx, qword ptr [rbp-0xA0]
	mov	rcx, qword ptr [rbp+0x28]
	call	ParseOperator@PLT
	cmp	eax, -1
	jz	$_022
	mov	rax, qword ptr [rbp-0x98]
	jmp	$_040

$_022:	mov	ecx, 2026
	call	asmerr@PLT
$_023:	xor	eax, eax
	jmp	$_040

$_024:	cmp	dword ptr [rbp-0x78], 0
	jnz	$_025
	cmp	dword ptr [rbp-0x74], 0
	jz	$_026
$_025:	lea	rcx, [rbp-0x80]
	call	EmitConstError@PLT
	xor	eax, eax
	jmp	$_040

$_026:	cmp	qword ptr [rbp-0x70], 0
	jz	$_027
	jmp	$_012

$_027:	mov	rcx, qword ptr [rbp-0x10]
	call	SymFind@PLT
	mov	rdi, rax
	test	rdi, rdi
	jz	$_028
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_032
$_028:	test	rdi, rdi
	jnz	$_029
	mov	rcx, qword ptr [rbp-0x10]
	call	SymCreate@PLT
	mov	rdi, rax
	jmp	$_030

$_029:	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	or	byte ptr [rdi+0x15], 0x20
$_030:	and	dword ptr [rdi+0x14], 0xFFFFEFFF
	cmp	dword ptr [StoreState+rip], 0
	jz	$_031
	or	byte ptr [rdi+0x15], 0x10
$_031:	jmp	$_037

$_032:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_034
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_034
	cmp	byte ptr [rdi+0x19], -64
	jnz	$_034
	mov	rcx, rdi
	call	sym_ext2int@PLT
	and	dword ptr [rdi+0x14], 0xFFFFEFFF
	cmp	dword ptr [StoreState+rip], 0
	jz	$_033
	or	byte ptr [rdi+0x15], 0x10
$_033:	jmp	$_037

$_034:	cmp	byte ptr [rdi+0x18], 1
	jnz	$_035
	test	byte ptr [rdi+0x14], 0x40
	jnz	$_036
	mov	eax, dword ptr [rdi+0x28]
	cmp	dword ptr [rbp-0x80], eax
	jnz	$_035
	mov	eax, dword ptr [rdi+0x50]
	cmp	dword ptr [rbp-0x7C], eax
	jz	$_036
$_035:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_040

$_036:	cmp	dword ptr [StoreState+rip], 0
	jz	$_037
	test	byte ptr [rdi+0x15], 0x10
	jnz	$_037
	mov	rcx, rdi
	call	SaveVariableState@PLT
$_037:	or	byte ptr [rdi+0x14], 0x40
	test	byte ptr [rdi+0x14], 0x20
	jz	$_038
	cmp	qword ptr [rdi+0x58], 0
	jz	$_038
	lea	rdx, [rbp-0x80]
	mov	rcx, rdi
	call	qword ptr [rdi+0x58]
	jmp	$_039

$_038:	lea	rdx, [rbp-0x80]
	mov	rcx, rdi
	call	$_001
$_039:	mov	rax, rdi
$_040:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

EqualSgnDirective:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [rdx], 8
	jz	$_041
	mov	rdx, qword ptr [rdx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_044

$_041:	mov	rcx, rdx
	call	$_011
	test	rax, rax
	jz	$_043
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 1
	jnz	$_042
	mov	r8, rax
	xor	edx, edx
	mov	ecx, 2
	call	LstWrite@PLT
$_042:	xor	eax, eax
	jmp	$_044

$_043:	mov	rax, -1
$_044:	leave
	ret

CreateVariable:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rcx, qword ptr [rbp+0x18]
	call	SymFind@PLT
	mov	rdi, rax
	test	rdi, rdi
	jnz	$_046
	mov	rcx, qword ptr [rbp+0x18]
	call	SymCreate@PLT
	mov	rdi, rax
	and	dword ptr [rdi+0x14], 0xFFFFEFFF
	cmp	dword ptr [StoreState+rip], 0
	jz	$_045
	or	byte ptr [rdi+0x15], 0x10
$_045:	jmp	$_050

$_046:	cmp	byte ptr [rdi+0x18], 0
	jnz	$_048
	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	or	byte ptr [rdi+0x15], 0x20
	and	dword ptr [rdi+0x14], 0xFFFFEFFF
	cmp	dword ptr [StoreState+rip], 0
	jz	$_047
	or	byte ptr [rdi+0x15], 0x10
$_047:	jmp	$_050

$_048:	test	byte ptr [rdi+0x14], 0x10
	jnz	$_049
	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_051

$_049:	mov	dword ptr [rdi+0x50], 0
	cmp	dword ptr [StoreState+rip], 0
	jz	$_050
	test	byte ptr [rdi+0x15], 0x10
	jnz	$_050
	mov	rcx, rdi
	call	SaveVariableState@PLT
$_050:	or	byte ptr [rdi+0x14], 0x52
	mov	byte ptr [rdi+0x18], 1
	mov	eax, dword ptr [rbp+0x20]
	mov	dword ptr [rdi+0x28], eax
	mov	rax, rdi
$_051:	leave
	pop	rdi
	ret

CreateConstant:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2232
	mov	rbx, rcx
	cmp	byte ptr [rbx], 3
	jnz	$_052
	cmp	dword ptr [rbx+0x4], 524
	jnz	$_052
	mov	rax, qword ptr [rbx+0x20]
	jmp	$_053

$_052:	mov	rdx, qword ptr [rbx+0x8]
	mov	rax, qword ptr [rbx+0x8]
	call	NameSpace_@PLT
$_053:	mov	qword ptr [rbp-0x8], rax
	mov	dword ptr [rbp-0xC], 2
	mov	dword ptr [rbp-0x1C], 0
	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	mov	rdi, rax
	lea	rsi, [rbx+0x30]
	jmp	$_062

$_054:	xor	eax, eax
	mov	qword ptr [rbp-0x88], rax
	mov	qword ptr [rbp-0x80], rax
	mov	qword ptr [rbp-0x38], rax
	dec	dword ptr [rbp-0xC]
	jmp	$_068

$_055:	xor	r9d, r9d
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, rdi
	mov	rcx, rbx
	call	SetTextMacro@PLT
	jmp	$_090

$_056:	jmp	$_066

$_057:	jmp	$_066

$_058:	mov	r9, qword ptr [rsi+0x10]
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, rdi
	mov	rcx, rbx
	call	SetTextMacro@PLT
	jmp	$_090

$_059:	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_090

$_060:	mov	eax, dword ptr [Parse_Pass+rip]
	cmp	byte ptr [rdi+0x3A], al
	jnz	$_061
	mov	dword ptr [rbp-0x1C], 1
$_061:	mov	byte ptr [rdi+0x3A], al
	jmp	$_066

$_062:	cmp	dword ptr [rbx+0x4], 524
	jnz	$_063
	cmp	byte ptr [rsi], 0
	je	$_054
$_063:	cmp	byte ptr [rsi], 9
	jnz	$_064
	cmp	byte ptr [rsi+0x1], 60
	je	$_055
$_064:	test	rdi, rdi
	jz	$_056
	cmp	byte ptr [rdi+0x18], 0
	jz	$_057
	cmp	byte ptr [rdi+0x18], 2
	jnz	$_065
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_065
	test	byte ptr [rdi+0x15], 0x08
	je	$_057
$_065:	cmp	byte ptr [rdi+0x18], 10
	je	$_058
	test	byte ptr [rdi+0x14], 0x10
	jz	$_059
	jmp	$_060

$_066:	cmp	byte ptr [rsi], 10
	jne	$_071
	cmp	dword ptr [ModuleInfo+0x220+rip], 3
	jne	$_071
	mov	rax, qword ptr [rsi+0x8]
	mov	qword ptr [rbp-0x18], rax
$_067:	mov	r9d, dword ptr [rsi+0x4]
	movsx	r8d, byte ptr [rsi+0x1]
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [rbp-0x88]
	call	_atoow@PLT
$_068:	mov	dword ptr [rbp-0x50], -2
	mov	dword ptr [rbp-0x4C], 0
	mov	byte ptr [rbp-0x48], -64
	mov	byte ptr [rbp-0x45], 0
	mov	rax, qword ptr [rbp-0x80]
	mov	dword ptr [rbp-0x10], 0
	inc	dword ptr [rbp-0xC]
	test	rax, rax
	jnz	$_069
	movzx	ecx, byte ptr [ModuleInfo+0x1CC+rip]
	mov	rdx, qword ptr [rbp-0x88]
	lea	r8, [minintvalues+rip]
	cmp	rdx, qword ptr [r8+rcx*8]
	setl	al
	lea	r8, [maxintvalues+rip]
	cmp	rdx, qword ptr [r8+rcx*8]
	setg	ah
$_069:	test	rax, rax
	jz	$_070
	mov	r9, qword ptr [rbp-0x18]
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, rdi
	mov	rcx, rbx
	call	SetTextMacro@PLT
	jmp	$_090

$_070:	jmp	$_075

$_071:	mov	rax, qword ptr [rsi+0x10]
	mov	qword ptr [rbp-0x18], rax
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_074
	mov	rdx, rdi
	mov	rdi, rax
	xor	eax, eax
	mov	ecx, 4294967295
	repne scasb
	not	ecx
	cmp	ecx, 2048
	jc	$_072
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_090

$_072:	mov	rax, rsi
	lea	rdi, [rbp-0x888]
	mov	rsi, qword ptr [rbp-0x18]
	rep movsb
	mov	rsi, rax
	mov	rdi, rdx
	mov	dword ptr [rsp+0x20], 1
	xor	r9d, r9d
	mov	r8, rbx
	mov	edx, 2
	mov	rcx, qword ptr [rbp-0x18]
	call	ExpandLineItems@PLT
	test	rax, rax
	jz	$_073
	lea	rax, [rbp-0x888]
	mov	qword ptr [rbp-0x18], rax
$_073:	cmp	byte ptr [rsi], 10
	jnz	$_074
	cmp	dword ptr [ModuleInfo+0x220+rip], 3
	jnz	$_074
	jmp	$_067

$_074:	mov	byte ptr [rsp+0x20], 3
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, rbx
	lea	rcx, [rbp-0xC]
	call	EvalOperand@PLT
	mov	dword ptr [rbp-0x10], eax
	cmp	qword ptr [rbp-0x78], 0
	jz	$_075
	cmp	dword ptr [rbp-0x4C], 0
	jnz	$_075
	dec	dword ptr [rbp-0xC]
	jmp	$_068

$_075:	imul	eax, dword ptr [rbp-0xC], 24
	mov	rcx, qword ptr [rbp-0x38]
	mov	rdx, qword ptr [rbp-0x80]
	cmp	dword ptr [rbp-0x10], -1
	je	$_089
	cmp	byte ptr [rbx+rax], 0
	jne	$_089
	cmp	dword ptr [rbp-0x50], -2
	jne	$_089
	cmp	dword ptr [rbp-0x4C], 0
	jnz	$_076
	test	rdx, rdx
	jz	$_077
$_076:	cmp	dword ptr [rbp-0x4C], 1
	jne	$_089
	test	byte ptr [rbp-0x45], 0x01
	jne	$_089
	test	rcx, rcx
	je	$_089
	cmp	byte ptr [rcx+0x18], 1
	jne	$_089
$_077:	jmp	$_087

$_078:	mov	rcx, qword ptr [rbp-0x8]
	call	SymCreate@PLT
	mov	rdi, rax
	mov	eax, dword ptr [Parse_Pass+rip]
	mov	byte ptr [rdi+0x3A], al
	jmp	$_088

$_079:	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	or	byte ptr [rdi+0x15], 0x20
	jmp	$_088

$_080:	mov	rcx, rdi
	call	sym_ext2int@PLT
	jmp	$_088

$_081:	cmp	dword ptr [rbp-0x4C], 0
	jnz	$_084
	mov	eax, dword ptr [rbp-0x88]
	cmp	dword ptr [rdi+0x28], eax
	jnz	$_082
	mov	eax, dword ptr [rbp-0x84]
	cmp	dword ptr [rdi+0x50], eax
	jz	$_083
$_082:	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_090

$_083:	jmp	$_086

$_084:	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_086
	mov	rcx, qword ptr [rbp-0x38]
	mov	edx, dword ptr [rcx+0x28]
	add	edx, dword ptr [rbp-0x88]
	cmp	dword ptr [rdi+0x28], edx
	jnz	$_085
	mov	rax, qword ptr [rcx+0x30]
	cmp	qword ptr [rdi+0x30], rax
	jz	$_086
$_085:	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_090

$_086:	jmp	$_088

$_087:	test	rdi, rdi
	je	$_078
	cmp	byte ptr [rdi+0x18], 0
	je	$_079
	cmp	byte ptr [rdi+0x18], 2
	je	$_080
	cmp	dword ptr [rbp-0x1C], 0
	jne	$_081
$_088:	and	byte ptr [rdi+0x14], 0xFFFFFFBF
	lea	rdx, [rbp-0x88]
	mov	rcx, rdi
	call	$_001
	mov	rax, rdi
	jmp	$_090

$_089:	lea	r9, [rbp-0x888]
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, rdi
	mov	rcx, rbx
	call	SetTextMacro@PLT
$_090:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

EquDirective:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, rdx
	mov	al, byte ptr [rcx]
	cmp	byte ptr [rcx], 3
	jnz	$_091
	cmp	dword ptr [rcx+0x4], 524
	jnz	$_091
	mov	al, byte ptr [rcx+0x18]
$_091:	cmp	al, 8
	jz	$_092
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_095

$_092:	call	CreateConstant
	test	rax, rax
	jz	$_094
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 1
	jnz	$_093
	mov	r8, rax
	xor	edx, edx
	mov	ecx, 2
	call	LstWrite@PLT
$_093:	xor	eax, eax
	jmp	$_095

$_094:	mov	rax, -1
$_095:	leave
	ret


.SECTION .data
	.ALIGN	16

maxintvalues:
	.byte  0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte  0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F

minintvalues:
	.byte  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80


.att_syntax prefix
