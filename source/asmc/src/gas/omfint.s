
.intel_syntax noprefix

.global omf_write_record

.extern asmerr
.extern ModuleInfo
.extern WriteError
.extern fwrite


.SECTION .text
	.ALIGN	16

$_001:	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	cmp	ax, 127
	jbe	$_002
	or	ah, 0xFFFFFF80
	mov	byte ptr [rbx+rcx+0x7], ah
	inc	dword ptr [rbx]
	inc	ecx
$_002:	mov	byte ptr [rbx+rcx+0x7], al
	ret

$_003:
	push	rdi
	mov	rdi, rax
	movzx	eax, word ptr [rdi]
	call	$_001
	movzx	eax, word ptr [rdi+0x2]
	call	$_001
	cmp	word ptr [rdi], 0
	jnz	$_004
	cmp	word ptr [rdi+0x2], 0
	jnz	$_004
	movzx	eax, word ptr [rdi+0x4]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 2
	mov	word ptr [rbx+rcx+0x7], ax
$_004:	pop	rdi
	ret

omf_write_record:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 4136
	mov	dword ptr [rbp-0xFF8], 0
	lea	rbx, [rbp-0xFF8]
	mov	rsi, rcx
	movzx	ecx, byte ptr [rsi+0x10]
	sub	ecx, 128
	shr	ecx, 1
	lea	rax, [func_index+rip]
	movzx	eax, byte ptr [rax+rcx]
	jmp	$_018
$C0004:
	mov	ecx, 1901
	call	asmerr@PLT
$C0005:
$_005:	mov	al, byte ptr [rsi+0x10]
	mov	byte ptr [rbp-0xFF4], al
	jmp	$C0006
$C0007:
	mov	al, byte ptr [rsi+0x10]
	or	al, byte ptr [rsi+0x11]
	mov	byte ptr [rbp-0xFF4], al
	jmp	$C0006
$C0008:
	mov	al, byte ptr [rsi+0x11]
	mov	byte ptr [rbp-0xFF9], al
	add	al, -104
	mov	byte ptr [rbp-0xFF4], al
	mov	al, byte ptr [rsi+0x18]
	shl	al, 2
	or	al, byte ptr [rsi+0x16]
	mov	cl, byte ptr [rsi+0x17]
	mov	byte ptr [rbp-0xFFA], cl
	shl	cl, 5
	or	al, cl
	cmp	byte ptr [rbp-0xFF9], 0
	jnz	$_006
	cmp	dword ptr [rsi+0x24], 65536
	jnz	$_006
	or	al, 0x02
$_006:	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	cmp	byte ptr [rbp-0xFFA], 0
	jnz	$_007
	movzx	eax, word ptr [rsi+0x1C]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 2
	mov	word ptr [rbx+rcx+0x7], ax
	movzx	eax, byte ptr [rsi+0x20]
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
$_007:	cmp	byte ptr [rbp-0xFF9], 0
	jz	$_008
	mov	eax, dword ptr [rsi+0x24]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 4
	mov	dword ptr [rbx+rcx+0x7], eax
	jmp	$_009

$_008:	movzx	eax, word ptr [rsi+0x24]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 2
	mov	word ptr [rbx+rcx+0x7], ax
$_009:	movzx	eax, word ptr [rsi+0x28]
	call	$_001
	movzx	eax, word ptr [rsi+0x2A]
	call	$_001
	movzx	eax, word ptr [rsi+0x2C]
	call	$_001
	jmp	$_021
$C000D:
	mov	al, byte ptr [rsi+0x10]
	add	al, byte ptr [rsi+0x11]
	mov	byte ptr [rbp-0xFF4], al
	movzx	eax, word ptr [rsi+0x14]
	call	$_001
	cmp	byte ptr [rsi+0x11], 0
	jz	$_010
	mov	eax, dword ptr [rsi+0x18]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 4
	mov	dword ptr [rbx+rcx+0x7], eax
	jmp	$C0006
$_010:	movzx	eax, word ptr [rsi+0x18]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 2
	mov	word ptr [rbx+rcx+0x7], ax
	jmp	$C0006
$C0010:
	mov	byte ptr [rbp-0xFF4], -120
	movzx	eax, byte ptr [rsi+0x14]
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	movzx	eax, byte ptr [rsi+0x15]
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	jmp	$C0006
$C0011:
	jmp	$_005
$C0012:
	xor	eax, eax
	cmp	byte ptr [rsi+0x11], 0
	jz	$_012
	cmp	byte ptr [rsi+0x15], 0
	jz	$_012
	inc	eax
$_012:	add	eax, 138
	mov	byte ptr [rbp-0xFF4], al
	xor	eax, eax
	cmp	byte ptr [rsi+0x14], 0
	jz	$_013
	mov	eax, 128
$_013:	cmp	byte ptr [rsi+0x15], 0
	jz	$_014
	or	eax, 0x41
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	jmp	$C0006
$_014:	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	jmp	$_021
$C0016:
	mov	al, byte ptr [rsi+0x10]
	add	al, byte ptr [rsi+0x11]
	mov	byte ptr [rbp-0xFF4], al
	lea	rax, [rsi+0x14]
	call	$_003
	jmp	$C0006
$C0017:
	mov	al, -108
	add	al, byte ptr [rsi+0x11]
	mov	byte ptr [rbp-0xFF4], al
	lea	rax, [rsi+0x14]
	call	$_003
	jmp	$C0006
$C0018:
	mov	al, byte ptr [rsi+0x10]
	add	al, byte ptr [rsi+0x11]
	mov	byte ptr [rbp-0xFF4], al
	movzx	eax, byte ptr [rsi+0x14]
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	movzx	eax, byte ptr [rsi+0x15]
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	movzx	eax, byte ptr [rsi+0x16]
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	cmp	byte ptr [rsi+0x11], 0
	jz	$_015
	mov	eax, dword ptr [rsi+0x18]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 4
	mov	dword ptr [rbx+rcx+0x7], eax
	jmp	$_016
$_015:	movzx	eax, word ptr [rsi+0x18]
	mov	ecx, dword ptr [rbx]
	add	dword ptr [rbx], 2
	mov	word ptr [rbx+rcx+0x7], ax
$_016:	movzx	eax, word ptr [rsi+0x1C]
	call	$_001
	mov	al, byte ptr [rsi+0x15]
	and	eax, 0x0F
	test	eax, eax
	jnz	$_017
	lea	rax, [rsi+0x1E]
	call	$_003
$_017:	movzx	eax, word ptr [rsi+0x24]
	call	$_001
	jmp	$C0006
$C001C:
	mov	al, -60
	add	al, byte ptr [rsi+0x11]
	mov	byte ptr [rbp-0xFF4], al
	movzx	eax, byte ptr [rsi+0x14]
	mov	ecx, dword ptr [rbx]
	inc	dword ptr [rbx]
	mov	byte ptr [rbx+rcx+0x7], al
	movzx	eax, word ptr [rsi+0x16]
	call	$_001
	jmp	$C0006

$_018:	cmp	eax, 0
	jl	$C0006
	cmp	eax, 11
	jg	$C0006
	push	rax
	lea	r11, [$C0006+rip]
	movzx	eax, word ptr [r11+rax*2+($C001D-$C0006)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C001D:
	.word $C0006-$C0004
	.word $C0006-$C0005
	.word $C0006-$C0007
	.word $C0006-$C0008
	.word $C0006-$C000D
	.word $C0006-$C0010
	.word $C0006-$C0011
	.word $C0006-$C0012
	.word $C0006-$C0016
	.word $C0006-$C0017
	.word $C0006-$C0018
	.word $C0006-$C001C

$C0006: mov	ecx, dword ptr [rsi]
	mov	eax, 4079
	sub	eax, dword ptr [rbp-0xFF8]
	cmp	ecx, eax
	jg	$_020
	mov	rsi, qword ptr [rsi+0x8]
	lea	rdi, [rbp-0xFF1]
	mov	eax, dword ptr [rbp-0xFF8]
	add	rdi, rax
	add	dword ptr [rbp-0xFF8], ecx
	rep movsb
	jmp	$_021

$_020:	mov	ecx, 1901
	call	asmerr@PLT
$_021:	mov	eax, dword ptr [rbp-0xFF8]
	inc	eax
	mov	word ptr [rbp-0xFF3], ax
	add	al, ah
	add	al, byte ptr [rbp-0xFF4]
	lea	rdx, [rbp-0xFF1]
	mov	ecx, dword ptr [rbp-0xFF8]
	add	rcx, rdx
$_022:	cmp	rdx, rcx
	jnc	$_023
	add	al, byte ptr [rdx]
	inc	rdx
	jmp	$_022

$_023:
	neg	al
	mov	byte ptr [rdx], al
	mov	ebx, dword ptr [rbp-0xFF8]
	add	ebx, 4
	mov	rcx, qword ptr [ModuleInfo+0x78+rip]
	mov	edx, ebx
	mov	esi, 1
	lea	rdi, [rbp-0xFF4]
	call	fwrite@PLT
	cmp	rax, rbx
	jz	$_024
	call	WriteError@PLT
$_024:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

func_index:
	.byte  0x06, 0x00, 0x00, 0x00, 0x05, 0x07, 0x01, 0x00
	.byte  0x08, 0x00, 0x09, 0x01, 0x03, 0x01, 0x02, 0x00
	.byte  0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x01, 0x02, 0x01, 0x08, 0x01, 0x00, 0x01, 0x00
	.byte  0x00, 0x0A, 0x0B, 0x01, 0x02, 0x01


.att_syntax prefix
