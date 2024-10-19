
.intel_syntax noprefix

.global MemInit
.global MemAlloc
.global MemFree
.global MemFini
.global LclAlloc
.global LclDup
.global MemDup

.extern tstrcpy
.extern tstrlen
.extern asmerr
.extern malloc
.extern free


.SECTION .text
	.ALIGN	16

MemInit:
	sub	rsp, 8
	mov	qword ptr [pBase+rip], 0
	mov	dword ptr [currfree+rip], 0
	add	rsp, 8
	ret

MemAlloc:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	ebx, ecx
	mov	edi, ecx
	call	malloc@PLT
	test	rax, rax
	jz	$_001
	mov	ecx, ebx
	mov	rdx, rax
	mov	rdi, rax
	xor	eax, eax
	rep stosb
	mov	rax, rdx
	jmp	$_002

$_001:	mov	dword ptr [currfree+rip], eax
	mov	ecx, 1018
	call	asmerr@PLT
$_002:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

MemFree:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	call	free@PLT
	leave
	pop	rdi
	pop	rsi
	ret

MemFini:
	push	rbx
	sub	rsp, 32
	mov	rbx, qword ptr [pBase+rip]
	jmp	$_004

$_003:	mov	rcx, rbx
	mov	rbx, qword ptr [rbx]
	call	MemFree
$_004:	test	rbx, rbx
	jnz	$_003
	mov	qword ptr [pBase+rip], rbx
	add	rsp, 32
	pop	rbx
	ret

LclAlloc:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rax, qword ptr [pCurr+rip]
	add	ecx, 15
	and	ecx, 0xFFFFFFF0
	cmp	ecx, dword ptr [currfree+rip]
	ja	$_005
	sub	dword ptr [currfree+rip], ecx
	add	qword ptr [pCurr+rip], rcx
	jmp	$_009

$_005:	mov	dword ptr [currfree+rip], ecx
	mov	eax, 1048560
	cmp	ecx, eax
	jbe	$_006
	mov	eax, ecx
$_006:	add	eax, 16
	mov	ecx, eax
	call	MemAlloc
	test	rax, rax
	jnz	$_007
	mov	dword ptr [currfree+rip], eax
	mov	ecx, 1018
	call	asmerr@PLT
$_007:	mov	rcx, qword ptr [pBase+rip]
	mov	qword ptr [rax], rcx
	mov	qword ptr [pBase+rip], rax
	add	rax, 16
	mov	ecx, dword ptr [currfree+rip]
	mov	edx, ecx
	add	rdx, rax
	mov	qword ptr [pCurr+rip], rdx
	mov	edx, 1048560
	cmp	ecx, edx
	jbe	$_008
	mov	edx, ecx
$_008:	sub	edx, ecx
	mov	dword ptr [currfree+rip], edx
$_009:	leave
	ret

LclDup:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	call	tstrlen@PLT
	lea	rcx, [rax+0x1]
	call	LclAlloc
	mov	rdx, rbx
	mov	rcx, rax
	call	tstrcpy@PLT
	leave
	pop	rbx
	ret

MemDup:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	call	tstrlen@PLT
	lea	rcx, [rax+0x1]
	call	MemAlloc
	mov	rdx, rbx
	mov	rcx, rax
	call	tstrcpy@PLT
	leave
	pop	rbx
	ret


.SECTION .data
	.ALIGN	16

pBase:
	.quad  0x0000000000000000

pCurr:	.quad  0x0000000000000000

currfree: .int	 0x00000000


.att_syntax prefix
