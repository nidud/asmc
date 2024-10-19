
.intel_syntax noprefix

.global AddLinnumDataRef
.global QueueDeleteLinnum
.global LinnumFini
.global LinnumInit

.extern procidx
.extern omf_check_flush
.extern AddPublicData
.extern CreateProc
.extern CurrProc
.extern TypeFromClassName
.extern GetCurrOffset
.extern SetSymSegOfs
.extern GetLineNumber
.extern LclAlloc
.extern tsprintf
.extern asmerr
.extern LinnumQueue
.extern write_to_file
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdi, qword ptr [rbx+0x68]
	cmp	dword ptr [Options+0xA4+rip], 2
	jnz	$_003
	mov	rsi, qword ptr [rdi+0x38]
	test	rsi, rsi
	jnz	$_002
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	rsi, rax
	mov	qword ptr [rdi+0x38], rsi
	mov	qword ptr [rsi], 0
$_002:	jmp	$_004

$_003:	lea	rsi, [LinnumQueue+rip]
$_004:	mov	rdi, qword ptr [rbp+0x28]
	mov	qword ptr [rdi], 0
	cmp	qword ptr [rsi], 0
	jnz	$_005
	mov	qword ptr [rsi], rdi
	mov	qword ptr [rsi+0x8], rdi
	jmp	$_006

$_005:	mov	rcx, qword ptr [rsi+0x8]
	mov	qword ptr [rcx], rdi
	mov	qword ptr [rsi+0x8], rdi
$_006:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AddLinnumDataRef:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rbx, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [dmyproc+rip]
	test	rsi, rsi
	jz	$_007
	mov	rdi, qword ptr [rsi+0x58]
$_007:	cmp	dword ptr [Options+0xA4+rip], 2
	jne	$_012
	cmp	byte ptr [Options+0x2+rip], 4
	je	$_012
	test	rbx, rbx
	jne	$_012
	test	rsi, rsi
	jz	$_008
	mov	eax, dword ptr [rbp+0x28]
	cmp	word ptr [rdi+0xE], ax
	jnz	$_008
	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	cmp	qword ptr [rsi+0x30], rax
	je	$_012
$_008:	test	rsi, rsi
	jz	$_009
	mov	rcx, qword ptr [rsi+0x30]
	mov	rcx, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rcx+0xC]
	sub	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rsi+0x50], eax
$_009:	mov	r8d, dword ptr [procidx+rip]
	lea	rdx, [DS0000+rip]
	lea	rcx, [rbp-0xC]
	call	tsprintf@PLT
	lea	rcx, [rbp-0xC]
	call	SymFind@PLT
	mov	qword ptr [dmyproc+rip], rax
	mov	rsi, rax
	test	rsi, rsi
	jnz	$_010
	mov	r8d, 1
	lea	rdx, [rbp-0xC]
	xor	ecx, ecx
	call	CreateProc@PLT
	mov	qword ptr [dmyproc+rip], rax
	mov	rsi, rax
	or	byte ptr [rsi+0x15], 0x48
	mov	rcx, rsi
	call	AddPublicData@PLT
	jmp	$_011

$_010:	inc	dword ptr [procidx+rip]
$_011:	test	byte ptr [rsi+0x15], 0x08
	jz	$_012
	mov	rcx, rsi
	call	SetSymSegOfs@PLT
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rsi+0x38], al
	mov	al, byte ptr [ModuleInfo+0x1B6+rip]
	mov	byte ptr [rsi+0x1A], al
	cmp	dword ptr [write_to_file+rip], 1
	jnz	$_012
	mov	ecx, 24
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	qword ptr [rdi+0x10], rsi
	call	GetLineNumber@PLT
	mov	dword ptr [rdi+0xC], eax
	mov	eax, dword ptr [rbp+0x28]
	shl	eax, 20
	or	dword ptr [rdi+0xC], eax
	mov	dword ptr [rdi+0x8], 0
	mov	rcx, rdi
	call	$_001
$_012:	cmp	dword ptr [rbp+0x30], 0
	jz	$_014
	cmp	dword ptr [write_to_file+rip], 0
	jz	$_013
	mov	eax, dword ptr [rbp+0x30]
	cmp	dword ptr [lastLineNumber+rip], eax
	jnz	$_014
$_013:	jmp	$_023

$_014:	mov	ecx, 24
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rdi+0x8], eax
	cmp	dword ptr [rbp+0x30], 0
	jne	$_019
	mov	rcx, qword ptr [CurrProc+rip]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_015
	cmp	dword ptr [Options+0xA4+rip], 2
	jnz	$_015
	test	rcx, rcx
	jz	$_015
	test	dword ptr [rcx+0x14], 0x80
	jnz	$_015
	or	byte ptr [rcx+0x15], 0x40
	call	AddPublicData@PLT
$_015:	mov	rax, qword ptr [dmyproc+rip]
	cmp	qword ptr [CurrProc+rip], 0
	jz	$_016
	mov	rax, qword ptr [CurrProc+rip]
$_016:	mov	qword ptr [rdi+0x10], rax
	call	GetLineNumber@PLT
	mov	dword ptr [rdi+0xC], eax
	mov	eax, dword ptr [rbp+0x28]
	shl	eax, 20
	or	dword ptr [rdi+0xC], eax
	mov	rsi, qword ptr [dmyproc+rip]
	test	rsi, rsi
	jz	$_017
	mov	rcx, qword ptr [rsi+0x30]
	mov	rcx, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rcx+0xC]
	sub	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rsi+0x50], eax
	mov	qword ptr [dmyproc+rip], 0
$_017:	mov	rcx, qword ptr [CurrProc+rip]
	mov	rdx, qword ptr [rcx+0x68]
	test	ecx, ecx
	jz	$_018
	cmp	byte ptr [rdx+0x41], 0
	jz	$_018
	mov	rcx, rdi
	call	$_001
	mov	ecx, 24
	call	LclAlloc@PLT
	mov	rdi, rax
	call	GetLineNumber@PLT
	mov	dword ptr [rdi+0x8], eax
	call	GetCurrOffset@PLT
	mov	dword ptr [rdi+0xC], eax
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rdi+0x10], eax
$_018:	jmp	$_020

$_019:	call	GetCurrOffset@PLT
	mov	dword ptr [rdi+0xC], eax
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rdi+0x10], eax
$_020:	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [lastLineNumber+rip], eax
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_021
	mov	rcx, rdi
	call	omf_check_flush@PLT
$_021:	mov	rbx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rsi, qword ptr [rbx+0x68]
	cmp	byte ptr [rsi+0x71], 0
	jnz	$_022
	mov	byte ptr [rsi+0x71], 1
	mov	rdx, qword ptr [rsi+0x50]
	mov	rcx, rbx
	call	TypeFromClassName@PLT
	cmp	rax, 1
	jz	$_022
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 4012
	call	asmerr@PLT
$_022:	mov	rcx, rdi
	call	$_001
$_023:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

QueueDeleteLinnum:
	test	rcx, rcx
	jz	$_025
	mov	rdx, qword ptr [rcx]
$_024:	test	rdx, rdx
	jz	$_025
	mov	rax, qword ptr [rdx]
	mov	rdx, rax
	jmp	$_024

$_025:
	ret

LinnumFini:
	mov	rax, qword ptr [dmyproc+rip]
	test	rax, rax
	jz	$_026
	mov	rcx, qword ptr [rax+0x30]
	mov	rcx, qword ptr [rcx+0x68]
	mov	edx, dword ptr [rcx+0xC]
	sub	edx, dword ptr [rax+0x28]
	mov	dword ptr [rax+0x50], edx
$_026:	ret

LinnumInit:
	mov	dword ptr [lastLineNumber+rip], 0
	mov	qword ptr [dmyproc+rip], 0
	ret


.SECTION .data
	.ALIGN	16

dmyproc:
	.quad  0x0000000000000000

lastLineNumber:
	.int   0x00000000

DS0000:
	.byte  0x24, 0x24, 0x24, 0x25, 0x30, 0x35, 0x75, 0x00


.att_syntax prefix
