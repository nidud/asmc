
.intel_syntax noprefix

.global LabelInit
.global GetAnonymousLabel
.global CreateLabel
.global LabelDirective

.extern EvalOperand
.extern LstWrite
.extern GetQualifiedType
.extern SegAssumeTable
.extern CopyPrototype
.extern CreateProc
.extern CurrProc
.extern SetSymSegOfs
.extern sym_ext2int
.extern sym_remove_table
.extern SymTables
.extern BackPatch
.extern tsprintf
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymLookupLocal
.extern SymLookup


.SECTION .text
	.ALIGN	16

LabelInit:
	mov	dword ptr [ModuleInfo+0x144+rip], 0
	ret

GetAnonymousLabel:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	eax, dword ptr [ModuleInfo+0x144+rip]
	add	eax, dword ptr [rbp+0x18]
	mov	r8d, eax
	lea	rdx, [DS0000+rip]
	mov	rcx, qword ptr [rbp+0x10]
	call	tsprintf@PLT
	mov	rax, qword ptr [rbp+0x10]
	leave
	ret

CreateLabel:
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
	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jnz	$_001
	mov	ecx, 2034
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_021

$_001:	mov	al, byte ptr [rbp+0x30]
	and	al, 0xFFFFFFC0
	cmp	al, -128
	jnz	$_002
	cmp	byte ptr [SegAssumeTable+0x18+rip], 0
	jz	$_002
	mov	ecx, 2108
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_021

$_002:	mov	rsi, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rsi]
	and	eax, 0xFFFFFF
	cmp	eax, 16448
	jnz	$_003
	lea	rsi, [rbp-0x18]
	inc	dword ptr [ModuleInfo+0x144+rip]
	mov	r8d, dword ptr [ModuleInfo+0x144+rip]
	lea	rdx, [DS0000+rip]
	mov	rcx, rsi
	call	tsprintf@PLT
$_003:	cmp	dword ptr [rbp+0x40], 0
	jz	$_004
	mov	rcx, rsi
	call	SymLookupLocal@PLT
	jmp	$_005

$_004:	mov	rcx, rsi
	call	SymLookup@PLT
$_005:	mov	rdi, rax
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_017
	cmp	byte ptr [rdi+0x18], 2
	jnz	$_009
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_009
	test	byte ptr [rdi+0x15], 0x08
	jnz	$_006
	cmp	dword ptr [rbp+0x40], 0
	jz	$_007
	cmp	qword ptr [CurrProc+rip], 0
	jz	$_007
$_006:	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_021

$_007:	cmp	byte ptr [rdi+0x19], -64
	jz	$_008
	mov	al, byte ptr [rbp+0x30]
	cmp	byte ptr [rdi+0x19], al
	jz	$_008
	mov	rdx, rsi
	mov	ecx, 2004
	call	asmerr@PLT
$_008:	mov	rcx, rdi
	call	sym_ext2int@PLT
	jmp	$_011

$_009:	cmp	byte ptr [rdi+0x18], 0
	jnz	$_010
	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	mov	byte ptr [rdi+0x18], 1
	jmp	$_011

$_010:	mov	rdx, rsi
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_021

$_011:	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rcx, qword ptr [rcx+0x68]
	mov	rax, qword ptr [rcx+0x20]
	mov	qword ptr [rdi+0x70], rax
	mov	qword ptr [rcx+0x20], rdi
	cmp	byte ptr [rdi+0x1A], 0
	jnz	$_012
	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	mov	byte ptr [rdi+0x1A], al
$_012:	mov	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbp+0x30], -128
	jnz	$_014
	test	byte ptr [rdi+0x15], 0x08
	jnz	$_013
	mov	r8d, 1
	xor	edx, edx
	mov	rcx, rdi
	call	CreateProc@PLT
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	CopyPrototype@PLT
$_013:	mov	rcx, qword ptr [rbx+0x8]
	mov	al, byte ptr [rcx+0x19]
	mov	byte ptr [rbp+0x30], al
	mov	qword ptr [rbx+0x8], 0
$_014:	mov	al, byte ptr [rbp+0x30]
	mov	byte ptr [rdi+0x19], al
	test	rbx, rbx
	jz	$_016
	cmp	byte ptr [rbp+0x30], -60
	jnz	$_015
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rdi+0x20], rax
	jmp	$_016

$_015:	mov	al, byte ptr [rbx+0x13]
	mov	byte ptr [rdi+0x38], al
	mov	al, byte ptr [rbx+0x11]
	mov	byte ptr [rdi+0x39], al
	mov	al, byte ptr [rbx+0x12]
	mov	byte ptr [rdi+0x1C], al
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rdi+0x40], rax
	mov	al, byte ptr [rbx+0x14]
	mov	byte ptr [rdi+0x3A], al
$_016:	jmp	$_018

$_017:	mov	eax, dword ptr [rdi+0x28]
	mov	dword ptr [rbp-0x4], eax
$_018:	or	byte ptr [rdi+0x14], 0x02
	test	byte ptr [rdi+0x15], 0x04
	jnz	$_019
	mov	eax, dword ptr [Parse_Pass+rip]
	mov	byte ptr [rdi+0x3A], al
$_019:	mov	rcx, rdi
	call	SetSymSegOfs@PLT
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_020
	mov	eax, dword ptr [rbp-0x4]
	cmp	dword ptr [rdi+0x28], eax
	jz	$_020
	mov	byte ptr [ModuleInfo+0x1ED+rip], 1
$_020:	mov	rcx, rdi
	call	BackPatch@PLT
	mov	rax, rdi
$_021:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

LabelDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	imul	ebx, dword ptr [rbp+0x18], 24
	add	rbx, qword ptr [rbp+0x20]
	cmp	dword ptr [rbp+0x18], 1
	jz	$_022
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_035

$_022:	inc	dword ptr [rbp+0x18]
	mov	dword ptr [rbp-0x18], 0
	mov	byte ptr [rbp-0x7], 0
	mov	byte ptr [rbp-0x6], 0
	mov	byte ptr [rbp-0x8], -64
	mov	byte ptr [rbp-0x4], -64
	mov	qword ptr [rbp-0x10], 0
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x5], al
	lea	r8, [rbp-0x18]
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [rbp+0x18]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	jnz	$_023
	jmp	$_035

$_023:	imul	ebx, dword ptr [rbp+0x18], 24
	add	rbx, qword ptr [rbp+0x20]
	mov	dword ptr [rbp-0x1C], -1
	mov	al, byte ptr [rbp-0x8]
	and	al, 0xFFFFFFC0
	cmp	al, -128
	jnz	$_025
	cmp	byte ptr [rbp-0x5], -2
	jz	$_024
	mov	al, byte ptr [rbp-0x5]
	cmp	byte ptr [ModuleInfo+0x1CC+rip], al
	jz	$_024
	mov	ecx, 2098
	call	asmerr@PLT
	jmp	$_035

$_024:	jmp	$_029

$_025:	cmp	byte ptr [rbx], 58
	jnz	$_029
	cmp	byte ptr [rbx+0x18], 0
	jz	$_029
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_029
	inc	dword ptr [rbp+0x18]
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [rbp+0x18]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_026
	jmp	$_035

$_026:	imul	ebx, dword ptr [rbp+0x18], 24
	add	rbx, qword ptr [rbp+0x20]
	cmp	dword ptr [rbp-0x4C], 0
	jz	$_028
	mov	rcx, qword ptr [rbp-0x38]
	test	rcx, rcx
	jz	$_027
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_027
	mov	dword ptr [rbp-0x88], 1
	jmp	$_028

$_027:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_035

$_028:	mov	eax, dword ptr [rbp-0x88]
	mov	dword ptr [rbp-0x1C], eax
$_029:	cmp	byte ptr [rbx], 0
	jz	$_030
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_035

$_030:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_031
	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 7
	call	LstWrite@PLT
$_031:	mov	rbx, qword ptr [rbp+0x20]
	xor	r9d, r9d
	lea	r8, [rbp-0x18]
	movzx	edx, byte ptr [rbp-0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	CreateLabel
	test	rax, rax
	jz	$_034
	mov	rcx, rax
	mov	al, byte ptr [rcx+0x19]
	and	al, 0xFFFFFFC0
	test	byte ptr [rcx+0x15], 0x04
	jnz	$_033
	cmp	al, -128
	jz	$_033
	cmp	dword ptr [rbp-0x1C], -1
	jz	$_032
	mov	eax, dword ptr [rbp-0x18]
	mul	dword ptr [rbp-0x1C]
	mov	dword ptr [rcx+0x50], eax
	mov	eax, dword ptr [rbp-0x1C]
	mov	dword ptr [rcx+0x58], eax
	or	byte ptr [rcx+0x15], 0x02
	jmp	$_033

$_032:	mov	eax, dword ptr [rbp-0x18]
	mov	dword ptr [rcx+0x50], eax
	mov	dword ptr [rcx+0x58], 1
$_033:	xor	eax, eax
	jmp	$_035

$_034:	mov	rax, -1
$_035:	leave
	pop	rbx
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x4C, 0x26, 0x5F, 0x25, 0x30, 0x34, 0x75, 0x00


.att_syntax prefix
