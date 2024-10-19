
.intel_syntax noprefix

.global WriteCodeLabel
.global DelayExpand
.global PreprocessLine

.extern directive_tab
.extern ExpandLine
.extern ExpandLineItems
.extern ExpandText
.extern CurrIfState
.extern CreateConstant
.extern StoreLine
.extern StoreState
.extern NoLineStore
.extern Tokenize
.extern LstWrite
.extern LstWriteSrcLine
.extern WritePreprocessedLine
.extern ParseLine
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

WriteCodeLabel:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rdx
	cmp	byte ptr [rbx], 8
	jz	$_001
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_004

$_001:	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_002
	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 7
	call	LstWrite@PLT
$_002:	mov	cl, byte ptr [rbx+0x30]
	mov	byte ptr [rbx+0x30], 0
	mov	rdi, qword ptr [rbx+0x40]
	mov	bl, byte ptr [rdi]
	mov	bh, cl
	mov	byte ptr [rdi], 0
	mov	esi, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [ModuleInfo+0x220+rip], 2
	mov	rcx, qword ptr [rbp+0x30]
	call	ParseLine@PLT
	cmp	byte ptr [Options+0x96+rip], 0
	jz	$_003
	mov	rcx, qword ptr [rbp+0x28]
	call	WritePreprocessedLine@PLT
$_003:	mov	byte ptr [rdi], bl
	mov	dword ptr [ModuleInfo+0x220+rip], esi
	mov	byte ptr [rbx+0x30], bh
	xor	eax, eax
$_004:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

DelayExpand:
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	xor	eax, eax
	test	byte ptr [rcx+0x2], 0x01
	jz	$_005
	cmp	al, byte ptr [ModuleInfo+0x337+rip]
	jnz	$_005
	cmp	eax, dword ptr [Parse_Pass+rip]
	jnz	$_005
	cmp	eax, dword ptr [NoLineStore+rip]
	jz	$_006
$_005:	jmp	$_017

$_006:	cmp	eax, dword ptr [ModuleInfo+0x220+rip]
	jl	$_007
	or	byte ptr [rcx+0x2], 0x02
	mov	eax, 1
	jmp	$_017

$_007:	imul	edx, eax, 24
	inc	eax
	test	byte ptr [rcx+rdx+0x2], 0x04
	jz	$_006
	cmp	byte ptr [rcx+rdx], 40
	jnz	$_006
	mov	edx, 1
$_008:	cmp	eax, dword ptr [ModuleInfo+0x220+rip]
	jl	$_009
	or	byte ptr [rcx+0x2], 0x02
	mov	eax, 1
	jmp	$_017

$_009:	imul	ebx, eax, 24
	jmp	$_014

$_010:	inc	edx
	jmp	$_015

$_011:	dec	edx
	jnz	$_015
	inc	eax
	jmp	$_006

$_012:	mov	rsi, qword ptr [rcx+rbx+0x8]
	cmp	byte ptr [rsi], 60
	jz	$_013
	mov	rsi, qword ptr [rcx+rbx+0x10]
	cmp	byte ptr [rsi], 60
	jnz	$_013
	mov	rdx, rsi
	mov	ecx, 7008
	call	asmerr@PLT
	jmp	$_016

$_013:	jmp	$_015

$_014:	cmp	byte ptr [rcx+rbx], 40
	jz	$_010
	cmp	byte ptr [rcx+rbx], 41
	jz	$_011
	cmp	byte ptr [rcx+rbx], 9
	jz	$_012
$_015:	inc	eax
	jmp	$_008

$_016:	xor	eax, eax
$_017:	leave
	pop	rbx
	pop	rsi
	ret

PreprocessLine:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	qword ptr [ModuleInfo+0x218+rip], 0
	mov	byte ptr [ModuleInfo+0x1C6+rip], 0
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x20]
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rbx, qword ptr [ModuleInfo+0x180+rip]
	cmp	dword ptr [ModuleInfo+0x220+rip], 0
	jnz	$_019
	cmp	dword ptr [CurrIfState+rip], 0
	jz	$_018
	cmp	byte ptr [ModuleInfo+0x1DD+rip], 0
	jz	$_019
$_018:	call	LstWriteSrcLine@PLT
$_019:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	test	eax, eax
	je	$_038
	cmp	dword ptr [CurrIfState+rip], 0
	jnz	$_023
	imul	eax, eax, 24
	test	byte ptr [rbx+rax+0x1], 0x02
	jz	$_020
	mov	r8d, 1
	mov	rdx, rbx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	ExpandText@PLT
	mov	esi, eax
	jmp	$_022

$_020:	xor	esi, esi
	mov	rcx, rbx
	call	DelayExpand
	test	rax, rax
	jnz	$_021
	mov	rdx, rbx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	ExpandLine@PLT
	mov	esi, eax
	jmp	$_022

$_021:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_022
	mov	dword ptr [rsp+0x20], 1
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	ExpandLineItems@PLT
$_022:	cmp	esi, 0
	jge	$_023
	xor	eax, eax
	jmp	$_038

$_023:	mov	rbx, qword ptr [ModuleInfo+0x180+rip]
	xor	esi, esi
	cmp	dword ptr [ModuleInfo+0x220+rip], 2
	jle	$_025
	cmp	byte ptr [rbx+0x18], 58
	jz	$_024
	cmp	byte ptr [rbx+0x18], 13
	jnz	$_025
$_024:	mov	esi, 48
$_025:	cmp	byte ptr [rbx+rsi], 3
	jnz	$_027
	cmp	byte ptr [rbx+rsi+0x1], 3
	ja	$_027
	cmp	esi, 24
	jbe	$_026
	mov	rdx, rbx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	WriteCodeLabel
	cmp	eax, -1
	jnz	$_026
	xor	eax, eax
	jmp	$_038

$_026:	movzx	ebx, byte ptr [rbx+rsi+0x1]
	xor	edx, edx
	mov	ecx, 24
	mov	eax, esi
	div	ecx
	mov	esi, eax
	lea	rcx, [directive_tab+rip]
	mov	rax, qword ptr [rcx+rbx*8]
	mov	rdx, qword ptr [ModuleInfo+0x180+rip]
	mov	ecx, esi
	call	rax
	xor	eax, eax
	jmp	$_038

$_027:	mov	rbx, qword ptr [ModuleInfo+0x180+rip]
	xor	eax, eax
	cmp	byte ptr [rbx], 8
	jnz	$_028
	cmp	byte ptr [rbx+0x18], 3
	jnz	$_028
	movzx	eax, byte ptr [rbx+0x19]
	jmp	$_029

$_028:	cmp	byte ptr [rbx], 3
	jnz	$_029
	cmp	dword ptr [rbx+0x4], 524
	jnz	$_029
	cmp	byte ptr [rbx+0x18], 8
	jnz	$_029
	movzx	eax, byte ptr [rbx+0x1]
$_029:	test	eax, eax
	je	$_037
	jmp	$_036

$_030:	mov	rcx, rbx
	call	CreateConstant@PLT
	test	rax, rax
	jz	$_034
	mov	rsi, rax
	cmp	byte ptr [rax+0x18], 10
	jz	$_032
	cmp	dword ptr [StoreState+rip], 0
	jz	$_031
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_031
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_031:	cmp	byte ptr [Options+0x96+rip], 0
	jz	$_032
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	WritePreprocessedLine@PLT
$_032:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_034
	mov	eax, 3
	cmp	byte ptr [rsi+0x18], 1
	jnz	$_033
	mov	eax, 2
$_033:	mov	r8, rsi
	xor	edx, edx
	mov	ecx, eax
	call	LstWrite@PLT
$_034:	xor	eax, eax
	jmp	$_038

$_035:	movzx	eax, byte ptr [rbx+0x19]
	lea	rcx, [directive_tab+rip]
	mov	rax, qword ptr [rcx+rax*8]
	mov	rdx, rbx
	mov	ecx, 1
	call	rax
	xor	eax, eax
	jmp	$_038

	jmp	$_037

$_036:	cmp	eax, 44
	je	$_030
	cmp	eax, 4
	jz	$_035
	cmp	eax, 5
	jz	$_035
	cmp	eax, 6
	jz	$_035
$_037:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
$_038:	leave
	pop	rbx
	pop	rsi
	ret

.att_syntax prefix
