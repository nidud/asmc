
.intel_syntax noprefix

.global CreateFixup
.global FreeFixup
.global SetFixupFrame
.global store_fixup
.global Frame_Type
.global Frame_Datum

.extern SegOverride
.extern GetGroup
.extern GetSegIdx
.extern GetCurrOffset
.extern LclAlloc
.extern Options
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

CreateFixup:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	ecx, 56
	call	LclAlloc@PLT
	mov	rbx, rax
	mov	rsi, qword ptr [rbp+0x28]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_002
	test	rbx, rbx
	jz	$_001
	mov	rax, qword ptr [rsi+0x60]
	mov	qword ptr [rbx], rax
	mov	qword ptr [rsi+0x60], rbx
$_001:	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	test	rcx, rcx
	jz	$_002
	mov	rdx, qword ptr [rcx+0x68]
	mov	rax, qword ptr [rdx+0x28]
	mov	qword ptr [rbx+0x8], rax
	mov	qword ptr [rdx+0x28], rbx
$_002:	call	GetCurrOffset@PLT
	mov	dword ptr [rbx+0x14], eax
	mov	dword ptr [rbx+0x10], 0
	mov	eax, dword ptr [rbp+0x30]
	mov	byte ptr [rbx+0x18], al
	mov	eax, dword ptr [rbp+0x38]
	mov	byte ptr [rbx+0x19], al
	mov	word ptr [rbx+0x1A], 0
	mov	al, byte ptr [Frame_Type+rip]
	mov	byte ptr [rbx+0x20], al
	mov	ax, word ptr [Frame_Datum+rip]
	mov	word ptr [rbx+0x22], ax
	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	mov	qword ptr [rbx+0x28], rax
	mov	qword ptr [rbx+0x30], rsi
	mov	rax, rbx
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

FreeFixup:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_006
	mov	rcx, qword ptr [rbx+0x28]
	test	rcx, rcx
	jz	$_006
	mov	rdx, qword ptr [rcx+0x68]
	cmp	rbx, qword ptr [rdx+0x28]
	jnz	$_003
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rdx+0x28], rax
	jmp	$_006

$_003:	mov	rcx, qword ptr [rdx+0x28]
$_004:	test	rcx, rcx
	jz	$_006
	cmp	qword ptr [rcx+0x8], rbx
	jnz	$_005
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rcx+0x8], rax
	jmp	$_006

$_005:	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_004

$_006:
	leave
	pop	rbx
	ret

SetFixupFrame:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	test	rsi, rsi
	je	$_013
	jmp	$_012

$_007:	cmp	qword ptr [rsi+0x30], 0
	jz	$_009
	mov	rcx, rsi
	call	GetGroup@PLT
	cmp	byte ptr [rbp+0x28], 0
	jnz	$_008
	test	rax, rax
	jz	$_008
	mov	rcx, qword ptr [rax+0x68]
	mov	byte ptr [Frame_Type+rip], 1
	mov	eax, dword ptr [rcx+0x8]
	mov	word ptr [Frame_Datum+rip], ax
	jmp	$_009

$_008:	mov	byte ptr [Frame_Type+rip], 0
	mov	rcx, qword ptr [rsi+0x30]
	call	GetSegIdx@PLT
	mov	word ptr [Frame_Datum+rip], ax
$_009:	jmp	$_013

$_010:	mov	byte ptr [Frame_Type+rip], 0
	mov	rcx, qword ptr [rsi+0x30]
	call	GetSegIdx@PLT
	mov	word ptr [Frame_Datum+rip], ax
	jmp	$_013

$_011:	mov	byte ptr [Frame_Type+rip], 1
	mov	rcx, qword ptr [rsi+0x68]
	mov	eax, dword ptr [rcx+0x8]
	mov	word ptr [Frame_Datum+rip], ax
	jmp	$_013

$_012:	cmp	byte ptr [rsi+0x18], 1
	jz	$_007
	cmp	byte ptr [rsi+0x18], 2
	je	$_007
	cmp	byte ptr [rsi+0x18], 3
	jz	$_010
	cmp	byte ptr [rsi+0x18], 4
	jz	$_011
$_013:	leave
	pop	rdi
	pop	rsi
	ret

store_fixup:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	mov	rsi, r8
	mov	eax, dword ptr [rsi]
	mov	dword ptr [rbx+0x10], eax
	mov	qword ptr [rbx+0x8], 0
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_015
	cmp	byte ptr [rbx+0x18], 8
	jz	$_014
	cmp	qword ptr [rbx+0x30], 0
	jz	$_014
	mov	rcx, qword ptr [rbx+0x30]
	mov	eax, dword ptr [rcx+0x28]
	add	dword ptr [rsi], eax
$_014:	jmp	$_023

$_015:	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_020
	mov	eax, dword ptr [rsi]
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_016
	xor	eax, eax
	jmp	$_019

$_016:	cmp	byte ptr [rbx+0x18], 3
	jnz	$_017
	mov	eax, 4294967292
	jmp	$_019

$_017:	cmp	byte ptr [rbx+0x18], 2
	jnz	$_018
	mov	eax, 4294967294
	jmp	$_019

$_018:	cmp	byte ptr [rbx+0x18], 1
	jnz	$_019
	mov	eax, 4294967295
$_019:	mov	dword ptr [rsi], eax
$_020:	mov	rcx, qword ptr [rbx+0x30]
	test	rcx, rcx
	jz	$_023
	test	byte ptr [rcx+0x14], 0x40
	jz	$_023
	mov	eax, dword ptr [rcx+0x28]
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_021
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jz	$_022
$_021:	add	dword ptr [rsi], eax
$_022:	add	dword ptr [rbx+0x10], eax
	mov	rax, qword ptr [rcx+0x30]
	mov	qword ptr [rbx+0x20], rax
$_023:	mov	rsi, qword ptr [rbp+0x28]
	mov	rsi, qword ptr [rsi+0x68]
	cmp	qword ptr [rsi+0x28], 0
	jnz	$_024
	mov	qword ptr [rsi+0x30], rbx
	mov	qword ptr [rsi+0x28], rbx
	jmp	$_025

$_024:	mov	rcx, qword ptr [rsi+0x30]
	mov	qword ptr [rcx+0x8], rbx
	mov	qword ptr [rsi+0x30], rbx
$_025:	leave
	pop	rbx
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

Frame_Type:
	.byte  0x00

Frame_Datum:
	.short 0x0000


.att_syntax prefix
