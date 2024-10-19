
.intel_syntax noprefix

.global Mangle
.global SetMangler

.extern tstricmp
.extern tstrcpy
.extern tstrupr
.extern tsprintf
.extern Options
.extern ModuleInfo


.SECTION .text
	.ALIGN	16

VoidMangler:
	mov	rdi, rdx
	mov	rsi, qword ptr [rcx+0x8]
	mov	eax, dword ptr [rcx+0x10]
	lea	ecx, [rax+0x1]
	rep movsb
	ret

UCaseMangler:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rdx
	mov	rsi, qword ptr [rcx+0x8]
	mov	eax, dword ptr [rcx+0x10]
	lea	ecx, [rax+0x1]
	rep movsb
	mov	rsi, rax
	mov	rcx, rdx
	call	tstrupr@PLT
	mov	rax, rsi
	leave
	ret

UScoreMangler:
	lea	rdi, [rdx+0x1]
	mov	rsi, qword ptr [rcx+0x8]
	mov	eax, dword ptr [rcx+0x10]
	inc	eax
	mov	ecx, eax
	rep movsb
	mov	byte ptr [rdx], 95
	ret

StdcallMangler:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [Options+0x8F+rip], 0
	jnz	$_002
	test	byte ptr [rcx+0x15], 0x08
	jz	$_002
	mov	rax, rdx
	mov	rdx, qword ptr [rcx+0x68]
	test	rdx, rdx
	jz	$_001
	mov	edx, dword ptr [rdx+0x20]
$_001:	mov	r9d, edx
	mov	r8, qword ptr [rcx+0x8]
	lea	rdx, [DS0000+rip]
	mov	rcx, rax
	call	tsprintf@PLT
	jmp	$_003

$_002:	call	UScoreMangler
$_003:	leave
	ret

ms32_decorate:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	test	byte ptr [rcx+0x15], 0x08
	jz	$_005
	mov	rax, rdx
	mov	rdx, qword ptr [rcx+0x68]
	test	rdx, rdx
	jz	$_004
	mov	edx, dword ptr [rdx+0x20]
$_004:	mov	r9d, edx
	mov	r8, qword ptr [rcx+0x8]
	lea	rdx, [DS0001+rip]
	mov	rcx, rax
	call	tsprintf@PLT
	jmp	$_006

$_005:	call	UScoreMangler
$_006:	leave
	ret

ow_decorate:
	mov	eax, 0
	test	byte ptr [rcx+0x15], 0x08
	jz	$_007
	or	eax, 0x02
	jmp	$_011

$_007:	jmp	$_010

$_008:	or	eax, 0x02
	jmp	$_011

$_009:	or	eax, 0x01
	jmp	$_011

$_010:	cmp	byte ptr [rcx+0x19], -127
	jz	$_008
	cmp	byte ptr [rcx+0x19], -126
	jz	$_008
	cmp	byte ptr [rcx+0x19], -64
	jz	$_008
	jmp	$_009

$_011:
	mov	rdi, rdx
	test	eax, 0x1
	jz	$_012
	mov	byte ptr [rdi], 95
	inc	rdi
$_012:	mov	rsi, qword ptr [rcx+0x8]
	mov	ecx, dword ptr [rcx+0x10]
	inc	ecx
	rep movsb
	dec	rdi
	test	eax, 0x2
	jz	$_013
	mov	word ptr [rdi], 95
	inc	rdi
$_013:	sub	rdi, rdx
	mov	rax, rdi
	ret

ms64_decorate:
	mov	rdi, rdx
	mov	rsi, qword ptr [rcx+0x8]
	mov	eax, dword ptr [rcx+0x10]
	lea	ecx, [rax+0x1]
	rep movsb
	ret

vect_decorate:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rdx
	mov	rsi, rcx
	mov	eax, 1
	test	byte ptr [rcx+0x15], 0x08
	jnz	$_014
	xor	eax, eax
	jmp	$_015

$_014:	lea	rdx, [DS0002+rip]
	mov	rcx, qword ptr [rcx+0x8]
	call	tstricmp@PLT
	mov	rcx, rsi
$_015:	test	eax, eax
	jnz	$_016
	mov	rdx, qword ptr [rcx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	eax, dword ptr [rsi+0x10]
	jmp	$_018

$_016:	mov	rdx, qword ptr [rsi+0x68]
	test	rdx, rdx
	jz	$_017
	mov	edx, dword ptr [rdx+0x20]
$_017:	mov	r9d, edx
	mov	r8, qword ptr [rcx+0x8]
	lea	rdx, [DS0003+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
$_018:	leave
	ret

Mangle:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	movzx	eax, byte ptr [rcx+0x1A]
	lea	rsi, [VoidMangler+rip]
	jmp	$C0016
$C0017: cmp	byte ptr [Options+0x8E+rip], 0
	jnz	$C0019
	lea	rsi, [UScoreMangler+rip]
	jmp	$C0019
$C001A: cmp	byte ptr [Options+0x8F+rip], 1
	jz	$C0019
	lea	rsi, [StdcallMangler+rip]
	jmp	$C0019
$C001C:
$C001D:
$C001E: lea	rsi, [UCaseMangler+rip]
	jmp	$C0019
$C001F: lea	rsi, [ow_decorate+rip]
	jmp	$C0019
$C0020:
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_021
	lea	rsi, [ms64_decorate+rip]
	jmp	$C0019
$_021:	cmp	byte ptr [ModuleInfo+0x1B9+rip], 1
	jnz	$_022
	lea	rsi, [ow_decorate+rip]
	jmp	$C0019
$_022:	lea	rsi, [ms32_decorate+rip]
	jmp	$C0019
$C0024: lea	rsi, [vect_decorate+rip]
$C0025:
$C0026:
$C0027: jmp	$C0019
$C0016: cmp	eax,0
	jl	$C0019
	cmp	eax,10
	jg	$C0019
	lea	r11, [$C0019+rip]
	movzx	eax, byte ptr [r11+rax+($C0028-$C0019)]
	sub	r11, rax
	jmp	r11
$C0028:
	.byte $C0019-$C0025
	.byte $C0019-$C0017
	.byte $C0019-$C0026
	.byte $C0019-$C001A
	.byte $C0019-$C001C
	.byte $C0019-$C001D
	.byte $C0019-$C001E
	.byte $C0019-$C0020
	.byte $C0019-$C0024
	.byte $C0019-$C001F
	.byte $C0019-$C0027
$C0019:
	mov	rdx, qword ptr [rbp+0x28]
	call	rsi
	leave
	pop	rdi
	pop	rsi
	ret

SetMangler:
	test	edx, edx
	jz	$_024
	mov	byte ptr [rcx+0x1A], dl
$_024:	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x5F, 0x25, 0x73, 0x40, 0x25, 0x64, 0x00

DS0001:
	.byte  0x40, 0x25, 0x73, 0x40, 0x25, 0x75, 0x00

DS0002:
	.byte  0x6D, 0x61, 0x69, 0x6E, 0x00

DS0003:
	.byte  0x25, 0x73, 0x40, 0x40, 0x25, 0x75, 0x00


.att_syntax prefix
