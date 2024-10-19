
.intel_syntax noprefix

.global GetFNamePart
.global GetExtPart
.global GetFName
.global ClearSrcStack
.global UpdateLineNumber
.global GetLineNumber
.global my_fgetc
.global PushMacro
.global get_curr_srcfile
.global set_curr_srcfile
.global SetLineNumber
.global print_source_nesting_structure
.global SearchFile
.global GetTextLine
.global AddStringToIncludePath
.global GetInputState
.global SetInputState
.global PushInputStatus
.global PopInputStatus
.global InputInit
.global InputPassInit
.global InputExtend
.global InputFini
.global FileCur
.global LineCur
.global StringBuffer
.global CommentBuffer

.extern strFILE
.extern DeleteLineQueue
.extern fill_placeholders
.extern MemDup
.extern LclDup
.extern LclAlloc
.extern MemFree
.extern MemAlloc
.extern tstrstart
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern tmemcpy
.extern tsprintf
.extern asmerr
.extern ModuleInfo
.extern PrintNote
.extern fgetc
.extern fclose
.extern fopen


.SECTION .text
	.ALIGN	16

GetFNamePart:
	mov	rax, rcx
$_001:	cmp	byte ptr [rcx], 0
	jz	$_003
	cmp	byte ptr [rcx], 47
	jnz	$_002
	lea	rax, [rcx+0x1]
$_002:	inc	rcx
	jmp	$_001

$_003:
	ret

GetExtPart:
	mov	eax, 0
$_004:	cmp	byte ptr [rcx], 0
	jz	$_007
	cmp	byte ptr [rcx], 46
	jnz	$_005
	mov	rax, rcx
	jmp	$_006

$_005:	cmp	byte ptr [rcx], 47
	jnz	$_006
	xor	eax, eax
$_006:	inc	rcx
	jmp	$_004

$_007:
	test	rax, rax
	jnz	$_008
	mov	rax, rcx
$_008:	ret

$_009:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, qword ptr [ModuleInfo+0xB0+rip]
	xor	ebx, ebx
$_010:	cmp	ebx, dword ptr [ModuleInfo+0xB8+rip]
	jnc	$_012
	mov	rdx, qword ptr [rsi+rbx*8]
	mov	rcx, qword ptr [rbp+0x20]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_011
	mov	eax, ebx
	jmp	$_014

$_011:	inc	ebx
	jmp	$_010

$_012:	test	ebx, 0x3F
	jnz	$_013
	lea	ecx, [rbx*8+0x200]
	call	MemAlloc@PLT
	mov	qword ptr [ModuleInfo+0xB0+rip], rax
	test	rsi, rsi
	jz	$_013
	lea	ecx, [rbx*8]
	mov	r8d, ecx
	mov	rdx, rsi
	mov	rcx, rax
	call	tmemcpy@PLT
	mov	rcx, rsi
	call	MemFree@PLT
$_013:	inc	dword ptr [ModuleInfo+0xB8+rip]
	mov	rsi, qword ptr [ModuleInfo+0xB0+rip]
	mov	rcx, qword ptr [rbp+0x20]
	call	LclDup@PLT
	mov	qword ptr [rsi+rbx*8], rax
	mov	eax, ebx
$_014:	leave
	pop	rbx
	pop	rsi
	ret

GetFName:
	and	ecx, 0xFFFF
	mov	rax, qword ptr [ModuleInfo+0xB0+rip]
	mov	rax, qword ptr [rax+rcx*8]
	ret

$_015:
	sub	rsp, 40
	mov	qword ptr [ModuleInfo+0xD8+rip], 0
	cmp	qword ptr [ModuleInfo+0xB0+rip], 0
	jz	$_016
	mov	rcx, qword ptr [ModuleInfo+0xB0+rip]
	call	MemFree@PLT
	mov	qword ptr [ModuleInfo+0xB0+rip], 0
$_016:	add	rsp, 40
	ret

ClearSrcStack:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	call	DeleteLineQueue@PLT
	mov	rbx, qword ptr [ModuleInfo+0xD8+rip]
$_017:	cmp	qword ptr [rbx], 0
	jz	$_019
	mov	rax, qword ptr [rbx]
	mov	qword ptr [rbp-0x8], rax
	cmp	word ptr [rbx+0x8], 0
	jnz	$_018
	mov	rdi, qword ptr [rbx+0x10]
	call	fclose@PLT
$_018:	mov	rax, qword ptr [SrcFree+rip]
	mov	qword ptr [rbx], rax
	mov	qword ptr [SrcFree+rip], rbx
	mov	rbx, qword ptr [rbp-0x8]
	jmp	$_017

$_019:
	mov	qword ptr [ModuleInfo+0xD8+rip], rbx
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_020:
	mov	rdx, qword ptr [FileCur+rip]
	mov	qword ptr [rdx+0x28], rcx
	lea	rdx, [strFILE+rip]
	mov	byte ptr [rdx], 34
	inc	rdx
	jmp	$_022

$_021:	mov	al, byte ptr [rcx]
	mov	byte ptr [rdx], al
	inc	rcx
	inc	rdx
	cmp	al, 92
	jnz	$_022
	mov	byte ptr [rdx], al
	inc	rdx
$_022:	cmp	byte ptr [rcx], 0
	jnz	$_021
	mov	word ptr [rdx], 34
	ret

UpdateLineNumber:
	mov	rax, qword ptr [ModuleInfo+0xD8+rip]
$_023:	test	rax, rax
	jz	$_025
	cmp	word ptr [rax+0x8], 0
	jnz	$_024
	mov	eax, dword ptr [rax+0x18]
	mov	dword ptr [rcx+0x28], eax
	jmp	$_025

$_024:	mov	rax, qword ptr [rax]
	jmp	$_023

$_025:
	ret

GetLineNumber:
	sub	rsp, 40
	xor	edx, edx
	mov	rcx, qword ptr [LineCur+rip]
	call	UpdateLineNumber
	mov	rax, qword ptr [LineCur+rip]
	mov	eax, dword ptr [rax+0x28]
	add	rsp, 40
	ret

my_fgetc:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	call	fgetc@PLT
	leave
	pop	rdi
	pop	rsi
	ret

$_026:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rcx
	lea	rsi, [rdi+rdx]
	mov	rcx, qword ptr [rbp+0x30]
	call	my_fgetc
	jmp	$_035

$_027:	jmp	$_033

$_028:	jmp	$_034

$_029:	mov	byte ptr [rdi], 0
	mov	rax, qword ptr [rbp+0x20]
	jmp	$_036

$_030:	xor	eax, eax
	mov	byte ptr [rdi], al
	cmp	rdi, qword ptr [rbp+0x20]
	jbe	$_031
	mov	rax, qword ptr [rbp+0x20]
$_031:	jmp	$_036

$_032:	stosb
	jmp	$_034

$_033:	cmp	eax, 13
	jz	$_028
	cmp	eax, 10
	jz	$_029
	cmp	eax, 26
	jz	$_030
	cmp	eax, -1
	jz	$_030
	jmp	$_032

$_034:	mov	rcx, qword ptr [rbp+0x30]
	call	my_fgetc
$_035:	cmp	rdi, rsi
	jc	$_027
	mov	ecx, 2039
	call	asmerr@PLT
	mov	byte ptr [rdi-0x1], 0
	mov	rax, qword ptr [rbp+0x20]
$_036:	leave
	pop	rdi
	pop	rsi
	ret

$_037:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	qword ptr [SrcFree+rip], 0
	jz	$_038
	mov	rax, qword ptr [SrcFree+rip]
	mov	rcx, qword ptr [rax]
	mov	qword ptr [SrcFree+rip], rcx
	jmp	$_039

$_038:	mov	ecx, 32
	call	LclAlloc@PLT
$_039:	mov	rcx, qword ptr [ModuleInfo+0xD8+rip]
	mov	qword ptr [rax], rcx
	mov	qword ptr [ModuleInfo+0xD8+rip], rax
	movzx	ecx, byte ptr [rbp+0x10]
	mov	word ptr [rax+0x8], cx
	mov	rcx, qword ptr [rbp+0x18]
	mov	qword ptr [rax+0x10], rcx
	mov	dword ptr [rax+0x18], 0
	leave
	ret

PushMacro:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, rcx
	mov	ecx, 1
	call	$_037
	leave
	ret

get_curr_srcfile:
	mov	rax, qword ptr [ModuleInfo+0xD8+rip]
$_040:	test	rax, rax
	jz	$_042
	cmp	word ptr [rax+0x8], 0
	jnz	$_041
	movzx	eax, word ptr [rax+0xA]
	jmp	$_043

$_041:	mov	rax, qword ptr [rax]
	jmp	$_040

$_042:	mov	eax, dword ptr [ModuleInfo+0x1F4+rip]
$_043:	ret

set_curr_srcfile:
	mov	rax, qword ptr [ModuleInfo+0xD8+rip]
	mov	word ptr [rax+0xA], cx
	mov	dword ptr [rax+0x18], edx
	ret

SetLineNumber:
	mov	rax, qword ptr [ModuleInfo+0xD8+rip]
	mov	dword ptr [rax+0x18], ecx
	ret

	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rcx, qword ptr [ModuleInfo+0xD8+rip]
$_044:	test	rcx, rcx
	jz	$_047
	cmp	word ptr [rcx+0x8], 0
	jnz	$_046
	movzx	eax, word ptr [rcx+0xA]
	mov	rax, qword ptr [ModuleInfo+0xB0+rip]
	mov	rax, qword ptr [rdx+rax*8]
	lea	rdx, [DS0000+rip]
	cmp	byte ptr [ModuleInfo+0x1E0+rip], 0
	jnz	$_045
	lea	rdx, [DS0001+rip]
$_045:	mov	r9d, dword ptr [rcx+0x18]
	mov	r8, rax
	mov	rcx, rbx
	call	tsprintf@PLT
	jmp	$_048

$_046:	mov	rcx, qword ptr [rcx]
	jmp	$_044

$_047:	xor	eax, eax
	mov	byte ptr [rbx], al
$_048:	leave
	pop	rbx
	ret

print_source_nesting_structure:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rbx, qword ptr [ModuleInfo+0xD8+rip]
	test	rbx, rbx
	jz	$_049
	cmp	qword ptr [rbx], 0
	jnz	$_050
$_049:	jmp	$_056

$_050:	mov	edi, 1
$_051:	cmp	qword ptr [rbx], 0
	je	$_055
	cmp	word ptr [rbx+0x8], 0
	jnz	$_052
	movzx	ecx, word ptr [rbx+0xA]
	call	GetFName
	mov	qword ptr [rbp-0x8], rax
	mov	eax, dword ptr [rbx+0x18]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x8]
	lea	r8, [DS0001+0x9+rip]
	mov	edx, edi
	xor	ecx, ecx
	call	PrintNote@PLT
	jmp	$_054

$_052:	mov	rax, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rax+0x20]
	mov	rax, qword ptr [rcx+0x8]
	cmp	byte ptr [rax], 0
	jnz	$_053
	mov	edx, dword ptr [rcx+0x28]
	inc	edx
	mov	dword ptr [rsp+0x28], edx
	mov	eax, dword ptr [rbx+0x18]
	mov	dword ptr [rsp+0x20], eax
	lea	r9, [DS0002+rip]
	lea	r8, [DS0001+0x9+rip]
	mov	edx, edi
	mov	ecx, 2
	call	PrintNote@PLT
	jmp	$_054

$_053:	mov	qword ptr [rbp-0x8], rax
	mov	rdx, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rdx+0x18]
	mov	ecx, eax
	call	GetFName
	mov	rcx, rax
	call	GetFNamePart
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbx+0x18]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x8]
	lea	r8, [DS0002+0x9+rip]
	mov	edx, edi
	mov	ecx, 1
	call	PrintNote@PLT
$_054:	mov	rbx, qword ptr [rbx]
	inc	edi
	jmp	$_051

$_055:	movzx	ecx, word ptr [rbx+0xA]
	call	GetFName
	mov	qword ptr [rbp-0x8], rax
	mov	eax, dword ptr [rbx+0x18]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x8]
	lea	r8, [DS0002+0x9+rip]
	mov	edx, edi
	mov	ecx, 3
	call	PrintNote@PLT
$_056:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_057:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rcx, qword ptr [rbp+0x28]
	jmp	$_059

$_058:	add	rcx, 1
$_059:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_058
	xchg	rax, rcx
	mov	qword ptr [rbp+0x28], rax
	mov	rcx, rax
	call	tstrlen@PLT
	mov	dword ptr [rbp-0xC], eax
	xor	eax, eax
	mov	rbx, qword ptr [ModuleInfo+0xC0+rip]
$_060:	test	rbx, rbx
	je	$_067
	test	rax, rax
	jne	$_067
	mov	edx, 58
	mov	rcx, rbx
	call	tstrchr@PLT
	mov	qword ptr [rbp-0x8], rax
	test	rax, rax
	jz	$_061
	sub	rax, rbx
	inc	qword ptr [rbp-0x8]
	jmp	$_062

$_061:	mov	rcx, rbx
	call	tstrlen@PLT
$_062:	mov	edi, eax
	mov	ecx, dword ptr [rbp-0xC]
	add	ecx, edi
	test	edi, edi
	jz	$_063
	cmp	ecx, 260
	jc	$_064
$_063:	jmp	$_066

$_064:	mov	r8d, edi
	mov	rdx, rbx
	mov	rcx, qword ptr [rbp+0x30]
	call	tmemcpy@PLT
	mov	cl, byte ptr [rax+rdi-0x1]
	cmp	cl, 47
	jz	$_065
	mov	byte ptr [rax+rdi], 47
	inc	edi
$_065:	mov	rcx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rcx+rdi]
	call	tstrcpy@PLT
	lea	rsi, [DS0003+rip]
	mov	rdi, qword ptr [rbp+0x30]
	call	fopen@PLT
$_066:	mov	rbx, qword ptr [rbp-0x8]
	jmp	$_060

$_067:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SearchFile:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 312
	mov	qword ptr [rbp-0x110], 0
	mov	rax, qword ptr [rbp+0x28]
	cmp	byte ptr [rax], 47
	mov	eax, 0
	sete	al
	mov	dword ptr [rbp-0x114], eax
	cmp	dword ptr [rbp-0x114], 0
	jnz	$_072
	mov	rbx, qword ptr [ModuleInfo+0xD8+rip]
$_068:	test	rbx, rbx
	jz	$_072
	cmp	word ptr [rbx+0x8], 0
	jnz	$_071
	movzx	ecx, word ptr [rbx+0xA]
	call	GetFName
	mov	rsi, rax
	mov	rcx, rsi
	call	GetFNamePart
	cmp	rsi, rax
	jz	$_070
	sub	rax, rsi
	lea	rdi, [rbp-0x104]
	mov	ecx, eax
	rep movsb
	mov	rsi, qword ptr [rbp+0x28]
$_069:	lodsb
	stosb
	test	al, al
	jnz	$_069
	lea	rsi, [DS0003+rip]
	lea	rdi, [rbp-0x104]
	call	fopen@PLT
	mov	qword ptr [rbp-0x110], rax
	test	rax, rax
	jz	$_070
	lea	rax, [rbp-0x104]
	mov	qword ptr [rbp+0x28], rax
$_070:	jmp	$_072

$_071:	mov	rbx, qword ptr [rbx]
	jmp	$_068

$_072:
	cmp	qword ptr [rbp-0x110], 0
	jnz	$_074
	mov	byte ptr [rbp-0x104], 0
	lea	rsi, [DS0003+rip]
	mov	rdi, qword ptr [rbp+0x28]
	call	fopen@PLT
	mov	qword ptr [rbp-0x110], rax
	cmp	qword ptr [rbp-0x110], 0
	jnz	$_073
	cmp	qword ptr [ModuleInfo+0xC0+rip], 0
	jz	$_073
	cmp	dword ptr [rbp-0x114], 0
	jnz	$_073
	lea	rdx, [rbp-0x104]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_057
	test	rax, rax
	jz	$_073
	mov	qword ptr [rbp-0x110], rax
	lea	rax, [rbp-0x104]
	mov	qword ptr [rbp+0x28], rax
$_073:	cmp	qword ptr [rbp-0x110], 0
	jnz	$_074
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 1000
	call	asmerr@PLT
$_074:	cmp	dword ptr [rbp+0x30], 0
	jz	$_075
	mov	rdx, qword ptr [rbp-0x110]
	xor	ecx, ecx
	call	$_037
	mov	rbx, rax
	mov	rcx, qword ptr [rbp+0x28]
	call	$_009
	mov	word ptr [rbx+0xA], ax
	mov	ecx, eax
	call	GetFName
	mov	rcx, rax
	call	$_020
$_075:	mov	rax, qword ptr [rbp-0x110]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

GetTextLine:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rbx, qword ptr [ModuleInfo+0xD8+rip]
	cmp	word ptr [rbx+0x8], 0
	jnz	$_080
	mov	r8, qword ptr [rbx+0x10]
	mov	edx, dword ptr [ModuleInfo+0x174+rip]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_026
	test	rax, rax
	jz	$_076
	inc	dword ptr [rbx+0x18]
	mov	rax, qword ptr [rbp+0x28]
	jmp	$_087

$_076:	cmp	qword ptr [rbx], 0
	jz	$_077
	mov	rdi, qword ptr [rbx+0x10]
	call	fclose@PLT
	mov	rax, qword ptr [rbx]
	mov	qword ptr [ModuleInfo+0xD8+rip], rax
	mov	rax, qword ptr [SrcFree+rip]
	mov	qword ptr [rbx], rax
	mov	qword ptr [SrcFree+rip], rbx
$_077:	mov	rbx, qword ptr [ModuleInfo+0xD8+rip]
$_078:	cmp	word ptr [rbx+0x8], 0
	jz	$_079
	mov	rbx, qword ptr [rbx]
	jmp	$_078

$_079:	movzx	ecx, word ptr [rbx+0xA]
	call	GetFName
	mov	rcx, rax
	call	$_020
	jmp	$_086

$_080:	mov	rdi, qword ptr [rbx+0x10]
	cmp	qword ptr [rdi], 0
	jz	$_081
	mov	rcx, qword ptr [rdi]
	mov	rax, qword ptr [rcx]
	jmp	$_082

$_081:	mov	rax, qword ptr [rdi+0x8]
$_082:	mov	qword ptr [rdi], rax
	test	rax, rax
	jz	$_085
	cmp	byte ptr [rax+0x8], 0
	jz	$_083
	lea	rdx, [rax+0x9]
	mov	rax, qword ptr [rdi+0x18]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rdi+0x10]
	mov	r8d, dword ptr [rdi+0x28]
	mov	rcx, qword ptr [rbp+0x28]
	call	fill_placeholders@PLT
	jmp	$_084

$_083:	lea	rdx, [rax+0x9]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcpy@PLT
$_084:	inc	dword ptr [rbx+0x18]
	mov	rax, qword ptr [rbp+0x28]
	jmp	$_087

$_085:	mov	rax, qword ptr [rbx]
	mov	qword ptr [ModuleInfo+0xD8+rip], rax
	mov	rax, qword ptr [SrcFree+rip]
	mov	qword ptr [rbx], rax
	mov	qword ptr [SrcFree+rip], rbx
$_086:	xor	eax, eax
$_087:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AddStringToIncludePath:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrstart@PLT
	mov	rsi, rax
	mov	rcx, rsi
	call	tstrlen@PLT
	test	rax, rax
	jz	$_089
	cmp	qword ptr [ModuleInfo+0xC0+rip], 0
	jnz	$_088
	mov	rcx, rsi
	call	MemDup@PLT
	mov	qword ptr [ModuleInfo+0xC0+rip], rax
	jmp	$_089

$_088:	mov	edi, eax
	mov	rbx, qword ptr [ModuleInfo+0xC0+rip]
	mov	rcx, rbx
	call	tstrlen@PLT
	lea	ecx, [rax+rdi+0x2]
	call	MemAlloc@PLT
	mov	qword ptr [ModuleInfo+0xC0+rip], rax
	mov	rdx, rbx
	mov	rcx, rax
	call	tstrcpy@PLT
	lea	rdx, [DS0004+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, rsi
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rbx
	call	MemFree@PLT
$_089:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

GetInputState:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	mov	rax, qword ptr [ModuleInfo+0x178+rip]
	sub	rax, qword ptr [srclinebuffer+rip]
	mov	dword ptr [rbx], eax
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	sub	rax, qword ptr [StringBuffer+rip]
	mov	dword ptr [rbx+0xC], eax
	mov	rax, qword ptr [ModuleInfo+0x180+rip]
	sub	rax, qword ptr [token_buffer+rip]
	mov	dword ptr [rbx+0x4], eax
	mov	rax, qword ptr [StringBuffer+rip]
	sub	rax, qword ptr [string_buffer+rip]
	mov	dword ptr [rbx+0x8], eax
	mov	rax, rbx
	leave
	pop	rbx
	ret

SetInputState:
	mov	rbx, rcx
	mov	eax, dword ptr [rbx]
	add	rax, qword ptr [srclinebuffer+rip]
	mov	qword ptr [ModuleInfo+0x178+rip], rax
	mov	eax, dword ptr [rbx+0x4]
	add	rax, qword ptr [token_buffer+rip]
	mov	qword ptr [ModuleInfo+0x180+rip], rax
	mov	eax, dword ptr [rbx+0x8]
	add	rax, qword ptr [string_buffer+rip]
	mov	qword ptr [StringBuffer+rip], rax
	mov	ecx, dword ptr [rbx+0xC]
	add	rax, rcx
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	mov	rax, rbx
	ret

PushInputStatus:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	al, byte ptr [ModuleInfo+0x1C6+rip]
	mov	byte ptr [rbx+0x14], al
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbx+0x10], eax
	mov	rax, qword ptr [ModuleInfo+0x178+rip]
	sub	rax, qword ptr [srclinebuffer+rip]
	mov	dword ptr [rbx], eax
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	sub	rax, qword ptr [StringBuffer+rip]
	mov	dword ptr [rbx+0xC], eax
	mov	rax, qword ptr [ModuleInfo+0x180+rip]
	sub	rax, qword ptr [token_buffer+rip]
	mov	dword ptr [rbx+0x4], eax
	mov	rax, qword ptr [StringBuffer+rip]
	sub	rax, qword ptr [string_buffer+rip]
	mov	dword ptr [rbx+0x8], eax
	mov	rax, qword ptr [ModuleInfo+0x218+rip]
	test	rax, rax
	jz	$_090
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrlen@PLT
	add	rax, qword ptr [ModuleInfo+0x178+rip]
	mov	rdx, qword ptr [ModuleInfo+0x218+rip]
	mov	rcx, rax
	call	tstrcpy@PLT
$_090:	mov	qword ptr [rbx+0x18], rax
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	mov	qword ptr [StringBuffer+rip], rax
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	inc	eax
	imul	eax, eax, 24
	add	qword ptr [ModuleInfo+0x180+rip], rax
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrlen@PLT
	mov	edx, eax
	mov	rax, qword ptr [ModuleInfo+0x178+rip]
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
	mov	qword ptr [ModuleInfo+0x178+rip], rax
	mov	rax, qword ptr [ModuleInfo+0x180+rip]
	leave
	pop	rbx
	ret

PopInputStatus:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	al, byte ptr [rbx+0x14]
	mov	byte ptr [ModuleInfo+0x1C6+rip], al
	mov	eax, dword ptr [rbx+0x10]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	eax, dword ptr [rbx]
	add	rax, qword ptr [srclinebuffer+rip]
	mov	qword ptr [ModuleInfo+0x178+rip], rax
	mov	eax, dword ptr [rbx+0x4]
	add	rax, qword ptr [token_buffer+rip]
	mov	qword ptr [ModuleInfo+0x180+rip], rax
	mov	eax, dword ptr [rbx+0x8]
	add	rax, qword ptr [string_buffer+rip]
	mov	qword ptr [StringBuffer+rip], rax
	mov	ecx, dword ptr [rbx+0xC]
	add	rax, rcx
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	cmp	qword ptr [rbx+0x18], 0
	jz	$_091
	mov	rax, qword ptr [CommentBuffer+rip]
	mov	qword ptr [ModuleInfo+0x218+rip], rax
	mov	rdx, qword ptr [rbx+0x18]
	mov	rcx, rax
	call	tstrcpy@PLT
	mov	rax, qword ptr [rbx+0x18]
	mov	byte ptr [rax], 0
	jmp	$_092

$_091:	mov	qword ptr [ModuleInfo+0x218+rip], 0
$_092:	leave
	pop	rbx
	ret

$_093:
	push	rsi
	push	rdi
	sub	rsp, 40
	mov	eax, dword ptr [ModuleInfo+0x174+rip]
	imul	rsi, rax, 101
	imul	rdx, rax, 100
	shr	rax, 2
	imul	rdi, rax, 2400
	add	rdx, rdi
	add	rdx, rsi
	shl	rax, 2
	add	rax, rdx
	mov	ecx, eax
	call	MemAlloc@PLT
	mov	qword ptr [srclinebuffer+rip], rax
	lea	rcx, [rax+rsi]
	mov	qword ptr [ModuleInfo+0x180+rip], rcx
	mov	qword ptr [token_buffer+rip], rcx
	add	rdi, rcx
	mov	qword ptr [string_buffer+rip], rdi
	mov	qword ptr [StringBuffer+rip], rdi
	mov	qword ptr [ModuleInfo+0x188+rip], rdi
	mov	edx, dword ptr [ModuleInfo+0x174+rip]
	sub	rcx, rdx
	mov	qword ptr [CommentBuffer+rip], rcx
	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

InputInit:
	push	rsi
	sub	rsp, 32
	mov	qword ptr [SrcFree+rip], 0
	mov	dword ptr [ModuleInfo+0x174+rip], 2048
	call	$_093
	mov	rdx, qword ptr [ModuleInfo+0x70+rip]
	xor	ecx, ecx
	call	$_037
	mov	rsi, rax
	mov	rcx, qword ptr [ModuleInfo+0x90+rip]
	call	$_009
	mov	word ptr [rsi+0xA], ax
	mov	dword ptr [ModuleInfo+0x1F4+rip], eax
	mov	ecx, eax
	call	GetFName
	mov	rcx, rax
	call	$_020
	add	rsp, 32
	pop	rsi
	ret

InputPassInit:
	mov	rax, qword ptr [ModuleInfo+0xD8+rip]
	mov	dword ptr [rax+0x18], 0
	mov	rax, qword ptr [srclinebuffer+rip]
	mov	qword ptr [ModuleInfo+0x178+rip], rax
	mov	byte ptr [rax], 0
	mov	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	ret

InputExtend:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	rax, qword ptr [srclinebuffer+rip]
	mov	qword ptr [rbp-0x10], rax
	mov	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x18], rax
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	mov	qword ptr [rbp-0x20], rax
	mov	rax, qword ptr [ModuleInfo+0x180+rip]
	mov	qword ptr [rbp-0x28], rax
	mov	eax, dword ptr [ModuleInfo+0x174+rip]
	mov	dword ptr [rbp-0x2C], eax
	cmp	eax, 1048576
	jbe	$_094
	mov	eax, 1048576
$_094:	add	dword ptr [ModuleInfo+0x174+rip], eax
	mov	rax, qword ptr [srclinebuffer+rip]
	mov	rsi, rcx
	cmp	qword ptr [rsi+0x10], rax
	jz	$_095
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	call	LclAlloc@PLT
	mov	rbx, rax
	mov	rdx, qword ptr [rsi+0x10]
	sub	qword ptr [rsi], rdx
	add	qword ptr [rsi], rbx
	mov	qword ptr [rsi+0x10], rbx
	mov	ecx, dword ptr [rbp-0x2C]
	mov	rdi, rbx
	mov	rsi, rdx
	rep movsb
$_095:	mov	rsi, qword ptr [srclinebuffer+rip]
	mov	ebx, dword ptr [rbp-0x2C]
	call	$_093
	mov	rdi, qword ptr [srclinebuffer+rip]
	mov	qword ptr [ModuleInfo+0x178+rip], rdi
	imul	ecx, ebx, 101
	rep movsb
	mov	rdi, qword ptr [ModuleInfo+0x180+rip]
	mov	eax, ebx
	shr	eax, 2
	imul	ecx, eax, 2400
	rep movsb
	mov	rdi, qword ptr [StringBuffer+rip]
	mov	rax, qword ptr [rbp-0x20]
	sub	rax, qword ptr [rbp-0x18]
	add	qword ptr [ModuleInfo+0x188+rip], rax
	imul	ecx, ebx, 100
	rep movsb
	mov	rsi, qword ptr [rbp+0x28]
	mov	rax, qword ptr [rsi+0x28]
	cmp	rax, qword ptr [rbp-0x18]
	jnz	$_096
	sub	qword ptr [rsi+0x8], rax
	mov	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rsi+0x28], rax
	add	qword ptr [rsi+0x8], rax
$_096:	mov	rax, qword ptr [rsi+0x10]
	cmp	rax, qword ptr [rbp-0x10]
	jnz	$_097
	sub	qword ptr [rsi], rax
	mov	rax, qword ptr [srclinebuffer+rip]
	mov	qword ptr [rsi+0x10], rax
	add	qword ptr [rsi], rax
$_097:	mov	rax, qword ptr [rsi+0x20]
	cmp	qword ptr [rbp-0x28], rax
	jnz	$_101
	mov	rdx, qword ptr [ModuleInfo+0x180+rip]
	mov	qword ptr [rsi+0x20], rdx
	mov	eax, dword ptr [rsi+0x18]
	mov	dword ptr [rbp-0x4], eax
	mov	rdi, qword ptr [srclinebuffer+rip]
	sub	rdi, qword ptr [rbp-0x10]
	mov	rsi, qword ptr [StringBuffer+rip]
	mov	rax, qword ptr [rbp-0x18]
	sub	rsi, rax
	imul	ebx, ebx, 101
	add	rbx, rax
	xor	ecx, ecx
$_098:	cmp	ecx, dword ptr [rbp-0x4]
	jg	$_100
	add	qword ptr [rdx+0x10], rdi
	cmp	qword ptr [rdx+0x8], rax
	jc	$_099
	cmp	qword ptr [rdx+0x8], rbx
	ja	$_099
	add	qword ptr [rdx+0x8], rsi
$_099:	inc	ecx
	add	rdx, 24
	jmp	$_098

$_100:	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_101:	mov	eax, 1
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

InputFini:
	sub	rsp, 40
	cmp	qword ptr [ModuleInfo+0xC0+rip], 0
	jz	$_102
	mov	rcx, qword ptr [ModuleInfo+0xC0+rip]
	call	MemFree@PLT
$_102:	cmp	qword ptr [srclinebuffer+rip], 0
	jz	$_103
	mov	rcx, qword ptr [srclinebuffer+rip]
	call	MemFree@PLT
	mov	qword ptr [srclinebuffer+rip], 0
$_103:	call	$_015
	mov	qword ptr [ModuleInfo+0x180+rip], 0
	add	rsp, 40
	ret


.SECTION .data
	.ALIGN	16

FileCur:
	.quad  0x0000000000000000

LineCur: .quad	0x0000000000000000

SrcFree: .quad	0x0000000000000000

srclinebuffer:
	.quad  0x0000000000000000

StringBuffer:
	.quad  0x0000000000000000

CommentBuffer:
	.quad  0x0000000000000000

token_buffer:
	.quad  0x0000000000000000

string_buffer:
	.quad  0x0000000000000000

DS0000:
	.byte  0x25, 0x73, 0x20, 0x3A, 0x20, 0x00

DS0001:
	.byte  0x25, 0x73, 0x28, 0x25, 0x75, 0x29, 0x20, 0x3A
	.byte  0x20, 0x00

DS0002:
	.byte  0x4D, 0x61, 0x63, 0x72, 0x6F, 0x4C, 0x6F, 0x6F
	.byte  0x70, 0x00

DS0003:
	.byte  0x72, 0x62, 0x00

DS0004:
	.byte  0x3A, 0x00


.att_syntax prefix
