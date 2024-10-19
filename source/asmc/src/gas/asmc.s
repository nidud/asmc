
.intel_syntax noprefix

.global cmpwarg
.global ReadFiles
.global AssembleSubdir
.global main
.global tgetenv
.global _pgmptr

.extern init_win64
.extern GetFNamePart
.extern MemInit
.extern MemFree
.extern MemAlloc
.extern tstrcat
.extern tstrcpy
.extern tstrrchr
.extern tstrchr
.extern tstrlen
.extern tmemicmp
.extern tprintf
.extern write_logo
.extern asmerr
.extern write_usage
.extern ParseCmdline
.extern CmdlineFini
.extern close_files
.extern AssembleModule
.extern Options
.extern _ltype
.extern CollectLinkObject
.extern CollectLinkOption
.extern closedir
.extern readdir
.extern opendir
.extern sigaction
.extern exit


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 312
	mov	qword ptr [rbp-0x8], 0
	mov	rbx, qword ptr [Options+0x18+rip]
	test	rbx, rbx
	jz	$_008
	mov	edx, 42
	mov	rcx, rbx
	call	tstrchr@PLT
	test	rax, rax
	jz	$_008
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x10C]
	call	tstrcpy@PLT
	mov	edx, 46
	mov	rcx, rax
	call	tstrrchr@PLT
	test	rax, rax
	jz	$_002
	mov	byte ptr [rax], 0
$_002:	mov	qword ptr [rbp-0x8], rbx
	mov	rdx, qword ptr [rbp+0x30]
	mov	qword ptr [Options+0x18+rip], rdx
$_003:	mov	al, byte ptr [rbx]
	cmp	al, 42
	jnz	$_006
	lea	rcx, [rbp-0x10C]
$_004:	mov	al, byte ptr [rcx]
	test	al, al
	jz	$_005
	mov	byte ptr [rdx], al
	inc	rcx
	inc	rdx
	jmp	$_004

$_005:	jmp	$_007

$_006:	mov	byte ptr [rdx], al
	inc	rdx
	test	al, al
	jz	$_008
$_007:	inc	rbx
	jmp	$_003

$_008:
	mov	rax, qword ptr [rbp-0x8]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

cmpwarg:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	mov	rsi, rdx
	xor	eax, eax
$_009:	lodsb
	mov	ah, byte ptr [rdi]
	inc	rdi
	cmp	ah, 42
	jnz	$_015
$_010:	mov	ah, byte ptr [rdi]
	test	ah, ah
	jnz	$_011
	mov	eax, 1
	jmp	$_018

$_011:	inc	rdi
	cmp	ah, 46
	jnz	$_010
	xor	edx, edx
	jmp	$_014

$_012:	cmp	al, ah
	jnz	$_013
	mov	rdx, rsi
$_013:	lodsb
$_014:	test	al, al
	jnz	$_012
	mov	rsi, rdx
	test	rdx, rdx
	jnz	$_009
	mov	ah, byte ptr [rdi]
	inc	rdi
	cmp	ah, 42
	jz	$_010
	test	eax, eax
	mov	ah, 0
	sete	al
	jmp	$_018

	jmp	$_010

$_015:	mov	edx, eax
	xor	eax, eax
	test	dl, dl
	jnz	$_016
	test	edx, edx
	jnz	$_018
	inc	eax
	jmp	$_018

$_016:	test	dh, dh
	jz	$_018
	cmp	dh, 63
	jz	$_009
	cmp	dh, 46
	jnz	$_017
	cmp	dl, 46
	jz	$_009
	jmp	$_018

$_017:	cmp	dl, 46
	jz	$_018
	or	edx, 0x2020
	cmp	dl, dh
	jnz	$_018
	jmp	$_009

$_018:
	leave
	pop	rdi
	pop	rsi
	ret

ReadFiles:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rbx, rcx
	cmp	byte ptr [rbx], 0
	jnz	$_019
	mov	word ptr [rbx], 46
$_019:	mov	rcx, rbx
	call	tstrlen@PLT
	lea	rax, [rbx+rax]
	mov	qword ptr [rbp-0x8], rax
	mov	rdi, qword ptr [rbp+0x28]
	call	opendir@PLT
	test	rax, rax
	je	$_027
	mov	qword ptr [rbp-0x10], rax
	mov	dword ptr [rbp-0x14], 0
	jmp	$_026

$_020:	mov	rbx, rax
	cmp	byte ptr [rbx+0x12], 4
	jz	$_023
	lea	rdx, [rbx+0x13]
	mov	rcx, qword ptr [rbp+0x30]
	call	cmpwarg
	test	rax, rax
	jz	$_022
	mov	rcx, qword ptr [rbp-0x8]
	mov	word ptr [rcx], 47
	lea	rdx, [rbx+0x13]
	call	tstrcat@PLT
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrlen@PLT
	add	rax, 16
	mov	ecx, eax
	call	MemAlloc@PLT
	test	rax, rax
	jz	$_021
	mov	rcx, qword ptr [rbp+0x38]
	mov	qword ptr [rcx], rax
	mov	qword ptr [rbp+0x38], rax
	mov	qword ptr [rax], 0
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rax+0x8]
	call	tstrcpy@PLT
	inc	dword ptr [rbp-0x14]
$_021:	mov	rcx, qword ptr [rbp-0x8]
	mov	byte ptr [rcx], 0
$_022:	jmp	$_026

$_023:	cmp	byte ptr [Options+0xF+rip], 0
	jz	$_026
	mov	eax, dword ptr [rbx+0x13]
	and	eax, 0xFFFFFF
	cmp	ax, 46
	jz	$_026
	cmp	eax, 11822
	jz	$_026
	mov	rcx, qword ptr [rbp-0x8]
	mov	word ptr [rcx], 47
	lea	rdx, [rbx+0x13]
	call	tstrcat@PLT
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x28]
	call	ReadFiles
	add	dword ptr [rbp-0x14], eax
	mov	rcx, qword ptr [rbp-0x8]
	mov	byte ptr [rcx], 0
	mov	rcx, qword ptr [rbp+0x38]
	jmp	$_025

$_024:	mov	rcx, qword ptr [rcx]
$_025:	cmp	qword ptr [rcx], 0
	jnz	$_024
	mov	qword ptr [rbp+0x38], rcx
$_026:	mov	rdi, qword ptr [rbp-0x10]
	call	readdir@PLT
	test	rax, rax
	jne	$_020
	mov	rdi, qword ptr [rbp-0x10]
	call	closedir@PLT
$_027:	mov	eax, dword ptr [rbp-0x14]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AssembleSubdir:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 344
	mov	qword ptr [rbp-0x138], rsi
	mov	qword ptr [rbp-0x130], rdi
	mov	dword ptr [rbp-0x110], 0
	xor	eax, eax
	mov	qword ptr [rbp-0x120], rax
	mov	qword ptr [rbp-0x118], rax
	lea	r8, [rbp-0x120]
	mov	rdx, qword ptr [rbp-0x138]
	mov	rcx, qword ptr [rbp-0x130]
	call	ReadFiles
	mov	dword ptr [rbp-0x124], eax
	mov	rbx, qword ptr [rbp-0x120]
$_028:	test	rbx, rbx
	jz	$_031
	lea	rdx, [rbp-0x10C]
	lea	rcx, [rbx+0x8]
	call	$_001
	mov	qword ptr [rbp-0x8], rax
	lea	rcx, [rbx+0x8]
	call	AssembleModule@PLT
	test	rax, rax
	jz	$_029
	mov	dword ptr [rbp-0x110], eax
$_029:	mov	rax, qword ptr [rbp-0x8]
	test	rax, rax
	jz	$_030
	mov	qword ptr [Options+0x18+rip], rax
$_030:	mov	rcx, rbx
	mov	rbx, qword ptr [rbx]
	call	MemFree@PLT
	jmp	$_028

$_031:
	mov	eax, dword ptr [rbp-0x110]
	leave
	pop	rbx
	ret

GeneralFailure:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 192
	mov	dword ptr [rbp-0x10], edi
	cmp	dword ptr [rbp-0x10], 15
	je	$_033
	lea	rdi, [DS0000+rip]
	mov	rbx, rdx
	add	rbx, 40
	mov	rax, qword ptr [rbx+0x88]
	mov	ecx, 16
$_032:	shr	eax, 1
	adc	byte ptr [rdi+rcx+0x108], 0
	dec	rcx
	jnz	$_032
	mov	rcx, qword ptr [rbx+0x80]
	mov	rdx, qword ptr [rcx]
	mov	r10, qword ptr [rcx-0x8]
	mov	r11, qword ptr [rcx+0x8]
	mov	qword ptr [rsp+0xA0], r11
	mov	qword ptr [rsp+0x98], r10
	mov	qword ptr [rsp+0x90], rdx
	mov	qword ptr [rsp+0x88], rcx
	mov	rax, qword ptr [rbx+0x38]
	mov	qword ptr [rsp+0x80], rax
	mov	rax, qword ptr [rbx+0x78]
	mov	qword ptr [rsp+0x78], rax
	mov	rax, qword ptr [rbx+0x30]
	mov	qword ptr [rsp+0x70], rax
	mov	rax, qword ptr [rbx+0x50]
	mov	qword ptr [rsp+0x68], rax
	mov	rax, qword ptr [rbx+0x28]
	mov	qword ptr [rsp+0x60], rax
	mov	rax, qword ptr [rbx+0x40]
	mov	qword ptr [rsp+0x58], rax
	mov	rax, qword ptr [rbx+0x20]
	mov	qword ptr [rsp+0x50], rax
	mov	rax, qword ptr [rbx+0x48]
	mov	qword ptr [rsp+0x48], rax
	mov	rax, qword ptr [rbx+0x18]
	mov	qword ptr [rsp+0x40], rax
	mov	rax, qword ptr [rbx+0x60]
	mov	qword ptr [rsp+0x38], rax
	mov	rax, qword ptr [rbx+0x10]
	mov	qword ptr [rsp+0x30], rax
	mov	rax, qword ptr [rbx+0x70]
	mov	qword ptr [rsp+0x28], rax
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbx+0x58]
	mov	r8, qword ptr [rbx]
	mov	rdx, qword ptr [rbx+0x68]
	mov	rcx, rdi
	call	tprintf@PLT
	mov	ecx, 1901
	call	asmerr@PLT
$_033:	call	close_files@PLT
	mov	edi, 1
	call	exit@PLT

main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 496
	mov	qword ptr [rbp-0x1D0], rdx
	mov	qword ptr [rbp-0x1C8], rsi
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x8], 0
	mov	dword ptr [rbp-0xC], 0
	mov	rax, qword ptr [rbp-0x1D0]
	mov	qword ptr [my_environ+rip], rax
	lea	rax, [rbp-0x110]
	mov	qword ptr [rbp-0x118], rax
	call	MemInit@PLT
	lea	rax, [GeneralFailure+rip]
	mov	qword ptr [rbp-0x1B0], rax
	mov	dword ptr [rbp-0x1A8], 4
	xor	edx, edx
	lea	rsi, [rbp-0x1B0]
	mov	edi, 11
	call	sigaction@PLT
	call	init_win64@PLT
	lea	rcx, [DS0001+rip]
	call	tgetenv
	test	rax, rax
	jnz	$_034
	lea	rax, [DS0001+0x4+rip]
$_034:	mov	rcx, qword ptr [rbp-0x1C8]
	mov	rdx, qword ptr [rcx]
	mov	qword ptr [_pgmptr+rip], rdx
	mov	qword ptr [rcx], rax
	lea	r15, [_ltype+rip]
	jmp	$_039

$_035:	call	write_logo@PLT
	inc	dword ptr [rbp-0xC]
	mov	rbx, qword ptr [Options+0x10+rip]
	mov	rdx, rbx
	mov	rcx, qword ptr [rbp-0x118]
	call	tstrcpy@PLT
	mov	edx, 42
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_036
	mov	edx, 63
	mov	rcx, qword ptr [rbp-0x118]
	call	tstrchr@PLT
$_036:	test	rax, rax
	jz	$_038
	mov	rcx, qword ptr [rbp-0x118]
	call	GetFNamePart@PLT
	cmp	rax, qword ptr [rbp-0x118]
	jbe	$_037
	dec	rax
$_037:	mov	byte ptr [rax], 0
	mov	rcx, rbx
	call	GetFNamePart@PLT
	mov	rsi, rax
	mov	rdi, qword ptr [rbp-0x118]
	call	AssembleSubdir
	mov	dword ptr [rbp-0x4], eax
	jmp	$_039

$_038:	mov	rcx, qword ptr [rbp-0x118]
	call	AssembleModule@PLT
	mov	dword ptr [rbp-0x4], eax
$_039:	lea	rdx, [rbp-0x8]
	mov	rcx, qword ptr [rbp-0x1C8]
	call	ParseCmdline@PLT
	test	rax, rax
	jne	$_035
	call	CmdlineFini@PLT
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_040
	call	write_usage@PLT
	jmp	$_060

$_040:	cmp	dword ptr [rbp-0xC], 0
	jnz	$_041
	mov	ecx, 1017
	call	asmerr@PLT
	jmp	$_060

$_041:	cmp	dword ptr [rbp-0x4], 1
	jne	$_060
	cmp	dword ptr [Options+0xA4+rip], 3
	jne	$_060
	cmp	byte ptr [Options+0xDB+rip], 0
	jne	$_060
	mov	dword ptr [rbp-0x1C0], -1
	mov	rbx, qword ptr [Options+0x78+rip]
	test	rbx, rbx
	jne	$_045
	cmp	dword ptr [Options+0xB8+rip], 3
	jz	$_042
	lea	rcx, [DS0002+rip]
	call	CollectLinkOption@PLT
	lea	rcx, [DS0003+rip]
	call	CollectLinkOption@PLT
	lea	rcx, [DS0004+rip]
	call	CollectLinkOption@PLT
	lea	rcx, [DS0005+rip]
	call	CollectLinkObject@PLT
	jmp	$_043

$_042:	cmp	byte ptr [Options+0xD5+rip], 0
	jnz	$_043
	lea	rcx, [DS0004+rip]
	call	CollectLinkOption@PLT
	lea	rcx, [DS0006+rip]
	call	CollectLinkObject@PLT
$_043:	lea	rcx, [DS0007+rip]
	call	CollectLinkOption@PLT
	mov	rcx, qword ptr [Options+0x80+rip]
	lea	rdx, [rcx+0x8]
	lea	rcx, [rbp-0xF0]
	call	tstrcpy@PLT
	mov	edx, 46
	mov	rcx, rax
	call	tstrrchr@PLT
	test	rax, rax
	jz	$_044
	mov	byte ptr [rax], 0
$_044:	lea	rcx, [rbp-0xF0]
	call	CollectLinkOption@PLT
$_045:	lea	rax, [DS0008+rip]
	cmp	qword ptr [Options+0x70+rip], 0
	jz	$_046
	mov	rax, qword ptr [Options+0x70+rip]
$_046:	mov	qword ptr [rbp-0x118], rax
	mov	ebx, 2
	mov	rcx, qword ptr [Options+0x78+rip]
$_047:	test	rcx, rcx
	jz	$_048
	mov	rcx, qword ptr [rcx]
	inc	ebx
	jmp	$_047

$_048:	mov	rcx, qword ptr [Options+0x80+rip]
$_049:	test	rcx, rcx
	jz	$_050
	mov	rcx, qword ptr [rcx]
	inc	ebx
	jmp	$_049

$_050:	lea	ecx, [rbx*8]
	call	MemAlloc@PLT
	mov	qword ptr [rbp-0x1B8], rax
	mov	rcx, qword ptr [rbp-0x118]
	mov	qword ptr [rax], rcx
	lea	rbx, [rax+0x8]
	mov	rcx, qword ptr [Options+0x78+rip]
$_051:	test	rcx, rcx
	jz	$_052
	lea	rax, [rcx+0x8]
	mov	qword ptr [rbx], rax
	mov	rcx, qword ptr [rcx]
	add	rbx, 8
	jmp	$_051

$_052:	mov	rcx, qword ptr [Options+0x80+rip]
$_053:	test	rcx, rcx
	jz	$_054
	lea	rax, [rcx+0x8]
	mov	qword ptr [rbx], rax
	mov	rcx, qword ptr [rcx]
	add	rbx, 8
	jmp	$_053

$_054:	xor	eax, eax
	mov	qword ptr [rbx], rax
	mov	eax, 57
	syscall
	mov	dword ptr [rbp-0x1BC], eax
	cmp	dword ptr [rbp-0x1BC], 0
	jnz	$_055
	mov	rdx, qword ptr [rbp-0x1D0]
	mov	rsi, qword ptr [rbp-0x1B8]
	mov	rdi, qword ptr [rbp-0x118]
	mov	eax, 59
	syscall
	xor	edi, edi
	mov	eax, 60
	syscall
	jmp	$_059

$_055:	cmp	dword ptr [rbp-0x1BC], 0
	jle	$_058
	xor	ecx, ecx
	xor	edx, edx
	lea	rsi, [rbp-0x1C0]
	mov	edi, dword ptr [rbp-0x1BC]
	mov	r10, rcx
	mov	eax, 61
	syscall
	cmp	eax, 0
	jge	$_056
	mov	eax, 4294967295
	jmp	$_057

$_056:	mov	eax, dword ptr [rbp-0x1C0]
$_057:	jmp	$_059

$_058:	mov	eax, 4294967295
$_059:	cmp	eax, -1
	jnz	$_060
	mov	rdx, qword ptr [rbp-0x118]
	mov	ecx, 2018
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], 0
$_060:	mov	eax, 1
	sub	eax, dword ptr [rbp-0x4]
	leave
	ret

tgetenv:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	call	tstrlen@PLT
	test	eax, eax
	jz	$_064
	mov	edi, eax
	mov	rsi, qword ptr [my_environ+rip]
	lodsq
	jmp	$_063

$_061:	mov	r8d, edi
	mov	rdx, rbx
	mov	rcx, rax
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_062
	mov	rax, qword ptr [rsi-0x8]
	add	rax, rdi
	cmp	byte ptr [rax], 61
	jnz	$_062
	lea	rax, [rax+0x1]
	jmp	$_064

$_062:	lodsq
$_063:	test	rax, rax
	jnz	$_061
$_064:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

_pgmptr:
	.quad  0x0000000000000000

my_environ:
	.quad  0x0000000000000000

DS0000:
	.byte  0x0A, 0x54, 0x68, 0x69, 0x73, 0x20, 0x6D, 0x65
	.byte  0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x69, 0x73
	.byte  0x20, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64
	.byte  0x20, 0x64, 0x75, 0x65, 0x20, 0x74, 0x6F, 0x20
	.byte  0x75, 0x6E, 0x72, 0x65, 0x63, 0x6F, 0x76, 0x65
	.byte  0x72, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x65, 0x72
	.byte  0x72, 0x6F, 0x72, 0x0A, 0x61, 0x6E, 0x64, 0x20
	.byte  0x6D, 0x61, 0x79, 0x20, 0x63, 0x6F, 0x6E, 0x74
	.byte  0x61, 0x69, 0x6E, 0x20, 0x64, 0x61, 0x74, 0x61
	.byte  0x20, 0x6E, 0x65, 0x63, 0x65, 0x73, 0x73, 0x61
	.byte  0x72, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x6C, 0x6F
	.byte  0x63, 0x61, 0x74, 0x65, 0x20, 0x69, 0x74, 0x2E
	.byte  0x0A, 0x0A, 0x09, 0x52, 0x41, 0x58, 0x3A, 0x20
	.byte  0x25, 0x70, 0x20, 0x52, 0x38, 0x3A, 0x20, 0x20
	.byte  0x25, 0x70, 0x0A, 0x09, 0x52, 0x42, 0x58, 0x3A
	.byte  0x20, 0x25, 0x70, 0x20, 0x52, 0x39, 0x3A, 0x20
	.byte  0x20, 0x25, 0x70, 0x0A, 0x09, 0x52, 0x43, 0x58
	.byte  0x3A, 0x20, 0x25, 0x70, 0x20, 0x52, 0x31, 0x30
	.byte  0x3A, 0x20, 0x25, 0x70, 0x0A, 0x09, 0x52, 0x44
	.byte  0x58, 0x3A, 0x20, 0x25, 0x70, 0x20, 0x52, 0x31
	.byte  0x31, 0x3A, 0x20, 0x25, 0x70, 0x0A, 0x09, 0x52
	.byte  0x53, 0x49, 0x3A, 0x20, 0x25, 0x70, 0x20, 0x52
	.byte  0x31, 0x32, 0x3A, 0x20, 0x25, 0x70, 0x0A, 0x09
	.byte  0x52, 0x44, 0x49, 0x3A, 0x20, 0x25, 0x70, 0x20
	.byte  0x52, 0x31, 0x33, 0x3A, 0x20, 0x25, 0x70, 0x0A
	.byte  0x09, 0x52, 0x42, 0x50, 0x3A, 0x20, 0x25, 0x70
	.byte  0x20, 0x52, 0x31, 0x34, 0x3A, 0x20, 0x25, 0x70
	.byte  0x0A, 0x09, 0x52, 0x53, 0x50, 0x3A, 0x20, 0x25
	.byte  0x70, 0x20, 0x52, 0x31, 0x35, 0x3A, 0x20, 0x25
	.byte  0x70, 0x0A, 0x09, 0x52, 0x49, 0x50, 0x3A, 0x20
	.byte  0x25, 0x70, 0x20, 0x25, 0x70, 0x0A, 0x09, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x25, 0x70, 0x20, 0x25
	.byte  0x70, 0x0A, 0x0A, 0x09, 0x45, 0x46, 0x4C, 0x3A
	.byte  0x20, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30
	.byte  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30
	.byte  0x30, 0x0A, 0x09, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x72, 0x20, 0x6E, 0x20, 0x6F, 0x64, 0x69, 0x74
	.byte  0x73, 0x7A, 0x20, 0x61, 0x20, 0x70, 0x20, 0x63
	.byte  0x0A, 0x0A, 0x00

DS0001:
	.byte  0x41, 0x53, 0x4D, 0x43, 0x00

DS0002:
	.byte  0x2D, 0x6D, 0x33, 0x32, 0x00

DS0003:
	.byte  0x2D, 0x73, 0x74, 0x61, 0x74, 0x69, 0x63, 0x00

DS0004:
	.byte  0x2D, 0x6E, 0x6F, 0x73, 0x74, 0x64, 0x6C, 0x69
	.byte  0x62, 0x00

DS0005:
	.byte  0x2D, 0x6C, 0x3A, 0x78, 0x38, 0x36, 0x2F, 0x6C
	.byte  0x69, 0x62, 0x61, 0x73, 0x6D, 0x63, 0x2E, 0x61
	.byte  0x00

DS0006:
	.byte  0x2D, 0x6C, 0x3A, 0x6C, 0x69, 0x62, 0x61, 0x73
	.byte  0x6D, 0x63, 0x2E, 0x61, 0x00

DS0007:
	.byte  0x2D, 0x6F, 0x00

DS0008:
	.byte  0x2F, 0x75, 0x73, 0x72, 0x2F, 0x62, 0x69, 0x6E
	.byte  0x2F, 0x67, 0x63, 0x63, 0x00


.att_syntax prefix
