
.intel_syntax noprefix

.global GenerateCString
.global CreateFloat
.global TextItemError
.global CatStrDir
.global SetTextMacro
.global AddPredefinedText
.global SubStrDir
.global SizeStrDir
.global InStrDir
.global StringInit

.extern ComAlloc
.extern GetTypeId
.extern list_pos
.extern get_register
.extern GetResWName
.extern _atoow
.extern __cvtq_ld
.extern __cvtq_sd
.extern __cvtq_ss
.extern InsertLineQueue
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern GetCurrOffset
.extern LstWrite
.extern SkipSavedState
.extern StoreLine
.extern LineStoreCurr
.extern CreateMacro
.extern Tokenize
.extern CreateVariable
.extern EvalOperand
.extern sym_remove_table
.extern SymTables
.extern LclAlloc
.extern MemFree
.extern MemAlloc
.extern tstrstart
.extern tstrstr
.extern tstricmp
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrrchr
.extern tstrchr
.extern tstrlen
.extern tmemcmp
.extern tmemcpy
.extern tsprintf
.extern myltoa
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind
.extern SymCreate


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, r8
	mov	byte ptr [rbp-0x3], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_002
	mov	byte ptr [rbp-0x3], 1
	call	MemAlloc@PLT
	jmp	$_003

$_002:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
$_003:	mov	qword ptr [rbp-0x10], rax
	mov	rdi, qword ptr [rbp+0x30]
	mov	rdx, rax
	xor	ebx, ebx
	mov	qword ptr [rdx], rbx
	xor	eax, eax
	test	byte ptr [ModuleInfo+0x334+rip], 0x02
	jz	$_004
	mov	eax, 1
$_004:
	cmp	word ptr [rsi], 8780
	jnz	$_005
	or	byte ptr [ModuleInfo+0x334+rip], 0x04
	mov	eax, 1
	add	rsi, 1
$_005:	mov	rcx, qword ptr [rbp+0x48]
	mov	byte ptr [rcx], al
	mov	byte ptr [rbp-0x2], al
	movsb
	jmp	$_043

$_006:	mov	al, byte ptr [rsi]
	cmp	al, 92
	jne	$_034
	inc	rsi
	movzx	eax, byte ptr [rsi]
	jmp	$_029
$C0009:
	mov	byte ptr [rdx], 7
	mov	eax, 540486690
	jmp	$_007
$C000A:
	mov	byte ptr [rdx], 8
	mov	eax, 540552226
	jmp	$_007
$C000B:
	mov	byte ptr [rdx], 27
	mov	eax, 926034978
	jmp	$_007
$C000C:
	mov	byte ptr [rdx], 12
	mov	eax, 842083362
	jmp	$_007
$C000D:
	mov	byte ptr [rdx], 10
	mov	eax, 808528930
	jmp	$_007
$C000E:
	mov	byte ptr [rdx], 13
	mov	eax, 858860578
	jmp	$_007
$C000F:
	mov	byte ptr [rdx], 9
	mov	eax, 540617762
	jmp	$_007
$C0010:
	mov	byte ptr [rdx], 11
	mov	eax, 825306146
	jmp	$_007
$C0011:
	mov	byte ptr [rdx], 39
	mov	eax, 959654946
	jmp	$_007
$C0012:
	mov	byte ptr [rdx], 63
	mov	eax, 859188258
$_007:	mov	rcx, qword ptr [rbp+0x30]
	add	rcx, 1
	cmp	rcx, rdi
	jnz	$_008
	cmp	al, byte ptr [rdi-0x1]
	jz	$_009
$_008:	cmp	al, byte ptr [rdi-0x1]
	jnz	$_010
	cmp	ah, byte ptr [rdi-0x2]
	jnz	$_010
$_009:	shr	eax, 16
	sub	rdi, 1
	stosw
	jmp	$_011

$_010:	stosd
$_011:	mov	eax, 8748
	cmp	byte ptr [rdi-0x1], 32
	jnz	$_012
	sub	rdi, 1
$_012:	stosb
	mov	byte ptr [rdi], ah
	jmp	$_033
$C0019:
	mov	byte ptr [rbp-0x1], 8
	jmp	$_013
$C001A:
	mov	byte ptr [rbp-0x1], 4
	jmp	$_013
$C001B:
	mov	byte ptr [rbp-0x1], 2
$_013:	movzx	eax, byte ptr [rsi+0x1]
	test	byte ptr [r15+rax], 0xFFFFFF80
	jz	$_019
	xor	ecx, ecx
	jmp	$_015

$_014:	inc	rsi
	shl	ecx, 4
	and	eax, 0xFFFFFFCF
	bt	eax, 6
	sbb	ebx, ebx
	and	ebx, 0x37
	sub	eax, ebx
	add	ecx, eax
	dec	byte ptr [rbp-0x1]
$_015:	movzx	eax, byte ptr [rsi+0x1]
	test	byte ptr [r15+rax], 0xFFFFFF80
	jz	$_016
	cmp	byte ptr [rbp-0x1], 0
	jnz	$_014
$_016:	mov	byte ptr [rdi], cl
	mov	byte ptr [rdx], cl
	shr	ecx, 8
	jmp	$_018

$_017:	inc	rdi
	inc	rdx
	mov	byte ptr [rdi], cl
	mov	byte ptr [rdx], cl
	shr	ecx, 8
$_018:	test	ecx, ecx
	jnz	$_017
	jmp	$_020

$_019:	mov	byte ptr [rdi], 120
	mov	byte ptr [rdx], 120
$_020:	jmp	$_033
$C0024:
	movzx	eax, byte ptr [rsi+0x1]
	test	byte ptr [r15+rax], 0x04
	jnz	$_023
	lea	rax, [rdi-0x1]
	cmp	rax, qword ptr [rbp+0x30]
	jnz	$_021
	dec	rdi
	mov	eax, 11312
	stosw
	jmp	$_022

$_021:	mov	eax, 741354530
	stosd
$_022:	mov	byte ptr [rdi], 34
	mov	byte ptr [rdx], 0
	jmp	$_033

$_023:	mov	eax, 48
$C0028:
	sub	eax, 48
	mov	ecx, eax
	movzx	eax, byte ptr [rsi+0x1]
	test	byte ptr [r15+rax], 0x04
	jz	$_024
	inc	rsi
	sub	eax, 48
	imul	ecx, ecx, 8
	add	ecx, eax
	movzx	eax, byte ptr [rsi+0x1]
	test	byte ptr [r15+rax], 0x04
	jz	$_024
	inc	rsi
	sub	eax, 48
	imul	ecx, ecx, 8
	add	ecx, eax
$_024:	mov	byte ptr [rdi], cl
	mov	byte ptr [rdx], cl
	jmp	$_033
$C0033:
	mov	ah, 44
	mov	rcx, qword ptr [rbp+0x30]
	add	rcx, 1
	cmp	rcx, rdi
	jnz	$_025
	cmp	al, byte ptr [rdi-0x1]
	jz	$_026
$_025:	cmp	al, byte ptr [rdi-0x1]
	jnz	$_027
	cmp	ah, byte ptr [rdi-0x2]
	jnz	$_027
$_026:	sub	rdi, 1
	jmp	$_028

$_027:	stosw
$_028:	mov	eax, 740762151
	stosd
	mov	al, 34
$C0038: mov	byte ptr [rdi], al
	mov	byte ptr [rdx], al
	jmp	$_033

$_029:	cmp	eax, 34
	jl	$C0038
	cmp	eax, 120
	jg	$C0038
	push	rax
	lea	r11, [$C0038+rip]
	movzx	eax, byte ptr [r11+rax-(34)+(IT$C0039-$C0038)]
	movzx	eax, word ptr [r11+rax*2+($C0039-$C0038)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C0039:
	.word $C0038-$C0009
	.word $C0038-$C000A
	.word $C0038-$C000B
	.word $C0038-$C000C
	.word $C0038-$C000D
	.word $C0038-$C000E
	.word $C0038-$C000F
	.word $C0038-$C0010
	.word $C0038-$C0011
	.word $C0038-$C0012
	.word $C0038-$C0019
	.word $C0038-$C001A
	.word $C0038-$C001B
	.word $C0038-$C0024
	.word $C0038-$C0028
	.word $C0038-$C0033
	.word 0
IT$C0039:
	.byte 15
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 8
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 13
	.byte 14
	.byte 14
	.byte 14
	.byte 14
	.byte 14
	.byte 14
	.byte 14
	.byte 14
	.byte 14
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 9
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 10
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 0
	.byte 1
	.byte 16
	.byte 16
	.byte 2
	.byte 3
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 4
	.byte 16
	.byte 16
	.byte 16
	.byte 5
	.byte 16
	.byte 6
	.byte 11
	.byte 7
	.byte 16
	.byte 12
	.ALIGN 2
$C0018:
$_033:	jmp	$_042

$_034:	cmp	al, 34
	jnz	$_041
	add	rsi, 1
	mov	rcx, rsi
	mov	al, byte ptr [rcx]
$_035:	cmp	al, 32
	jz	$_036
	cmp	al, 9
	jnz	$_037
$_036:	inc	rcx
	mov	al, byte ptr [rcx]
	jmp	$_035

$_037:	cmp	al, 76
	jnz	$_038
	cmp	byte ptr [rcx+0x1], 34
	jnz	$_038
	inc	rcx
	mov	al, 34
$_038:	cmp	al, 34
	jnz	$_039
	mov	rsi, rcx
	dec	rdi
	dec	rdx
	jmp	$_040

$_039:	mov	eax, 34
	stosb
	jmp	$_044

$_040:	jmp	$_042

$_041:	mov	byte ptr [rdi], al
	mov	byte ptr [rdx], al
$_042:	add	rdi, 1
	add	rdx, 1
	cmp	byte ptr [rsi], 0
	jz	$_043
	add	rsi, 1
$_043:	cmp	byte ptr [rsi], 0
	jne	$_006
$_044:	xor	eax, eax
	mov	byte ptr [rdi], al
	mov	byte ptr [rdx], al
	cmp	dword ptr [rdi-0x3], 2236972
	jnz	$_045
	mov	byte ptr [rdi-0x3], 0
$_045:	mov	rax, qword ptr [rbp+0x40]
	mov	qword ptr [rax], rsi
	mov	rax, qword ptr [rbp-0x10]
	sub	rdx, rax
	mov	rbx, rdx
	xor	edi, edi
	mov	rsi, qword ptr [ModuleInfo+0xF0+rip]
$_046:	test	rsi, rsi
	je	$_053
	mov	cl, byte ptr [rsi+0x16]
	mov	eax, dword ptr [rsi+0x8]
	cmp	eax, ebx
	jc	$_052
	cmp	cl, byte ptr [rbp-0x2]
	jnz	$_052
	mov	rdx, qword ptr [rsi]
	cmp	eax, ebx
	jbe	$_047
	add	rdx, rax
	sub	rdx, rbx
$_047:	mov	qword ptr [rbp-0x18], rdx
	mov	r8d, ebx
	mov	rcx, qword ptr [rbp-0x10]
	call	tmemcmp@PLT
	mov	rdx, qword ptr [rbp-0x18]
	test	eax, eax
	jnz	$_052
	movzx	eax, word ptr [rsi+0x14]
	sub	rdx, qword ptr [rsi]
	test	edx, edx
	jz	$_049
	cmp	byte ptr [rbp-0x2], 0
	jz	$_048
	add	edx, edx
$_048:	mov	r9d, edx
	mov	r8d, eax
	lea	rdx, [DS0000+rip]
	mov	rcx, qword ptr [rbp+0x28]
	call	tsprintf@PLT
	jmp	$_050

$_049:	mov	r8d, eax
	lea	rdx, [DS0001+rip]
	mov	rcx, qword ptr [rbp+0x28]
	call	tsprintf@PLT
$_050:	cmp	byte ptr [rbp-0x3], 0
	jz	$_051
	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_051:	xor	eax, eax
	jmp	$_055

$_052:	inc	edi
	mov	rsi, qword ptr [rsi+0xC]
	jmp	$_046

$_053:	mov	r8d, edi
	lea	rdx, [DS0001+rip]
	mov	rcx, qword ptr [rbp+0x28]
	call	tsprintf@PLT
	lea	ecx, [rbx+0x19]
	call	LclAlloc@PLT
	mov	dword ptr [rax+0x8], ebx
	mov	word ptr [rax+0x14], di
	mov	cl, byte ptr [rbp-0x2]
	mov	byte ptr [rax+0x16], cl
	mov	byte ptr [rax+0x17], 0
	mov	rcx, qword ptr [ModuleInfo+0xF0+rip]
	mov	qword ptr [rax+0xC], rcx
	mov	qword ptr [ModuleInfo+0xF0+rip], rax
	lea	rcx, [rax+0x18]
	mov	qword ptr [rax], rcx
	lea	r8d, [rbx+0x1]
	mov	rdx, qword ptr [rbp-0x10]
	call	tmemcpy@PLT
	cmp	byte ptr [rbp-0x3], 0
	jz	$_054
	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_054:	mov	eax, 1
$_055:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_056:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	test	rax, rax
	jz	$_057
	mov	rdx, qword ptr [rax+0x8]
	mov	rcx, qword ptr [rbp+0x10]
	call	tstrcpy@PLT
	lea	rdx, [DS0002+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	jmp	$_058

$_057:	lea	rdx, [DS0003+rip]
	mov	rcx, qword ptr [rbp+0x10]
	call	tstrcpy@PLT
$_058:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_059
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_059:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_060
	call	RunLineQueue@PLT
	and	byte ptr [ModuleInfo+0x1C6+rip], 0xFFFFFFFE
$_060:	leave
	ret

GenerateCString:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 136
	mov	byte ptr [rbp-0x4D], 0
	xor	eax, eax
	mov	dword ptr [rbp-0x4], eax
	mov	byte ptr [rbp-0x4B], al
	cmp	byte ptr [Options+0xC6+rip], 0
	jne	$_108
	mov	rsi, rdx
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, rsi
	mov	byte ptr [rbp-0x49], al
	mov	edx, eax
	jmp	$_068

$_061:	mov	rcx, qword ptr [rbx+0x8]
	movzx	ecx, word ptr [rcx]
	jmp	$_066

$_062:	cmp	ch, 34
	jnz	$_067
$_063:	mov	eax, 1
	jmp	$_069

$_064:	cmp	byte ptr [rbp-0x49], 0
	jz	$_069
	sub	byte ptr [rbp-0x49], 1
	jmp	$_067

$_065:	add	byte ptr [rbp-0x49], 1
	add	edx, 1
	jmp	$_067

$_066:	cmp	cl, 76
	jz	$_062
	cmp	cl, 34
	jz	$_063
	cmp	cl, 41
	jz	$_064
	cmp	cl, 40
	jz	$_065
$_067:	add	rbx, 24
$_068:	cmp	byte ptr [rbx], 0
	jnz	$_061
$_069:	test	eax, eax
	je	$_108
	xor	eax, eax
	test	edx, edx
	je	$_108
	inc	eax
	mov	dword ptr [rbp-0x4], eax
	mov	edi, dword ptr [ModuleInfo+0x174+rip]
	lea	ecx, [rdi*4+0x80]
	cmp	edi, 2048
	jbe	$_070
	inc	byte ptr [rbp-0x4D]
	call	MemAlloc@PLT
	jmp	$_071

$_070:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
$_071:	mov	ecx, edi
	shr	ecx, 2
	add	edi, ecx
	mov	qword ptr [rbp-0x38], rax
	add	rax, rdi
	mov	qword ptr [rbp-0x28], rax
	add	rax, rdi
	mov	qword ptr [rbp-0x20], rax
	add	rax, rdi
	mov	qword ptr [rbp-0x18], rax
	add	rax, 64
	mov	qword ptr [rbp-0x10], rax
	mov	edi, 32
	add	rdi, qword ptr [LineStoreCurr+rip]
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrcpy@PLT
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_072
	mov	byte ptr [rdi], 59
	mov	rdx, qword ptr [rsi+0x10]
	mov	rcx, rax
	call	tstrcmp@PLT
	jmp	$_073

$_072:	xor	eax, eax
$_073:	mov	dword ptr [rbp-0x8], eax
	mov	al, byte ptr [ModuleInfo+0x1C6+rip]
	mov	byte ptr [rbp-0x4C], al
	jmp	$_103

$_074:	mov	rcx, qword ptr [rbx+0x10]
	mov	ax, word ptr [rcx]
	cmp	al, 34
	jz	$_075
	cmp	ax, 8780
	jne	$_100
$_075:	mov	rdi, rcx
	mov	rsi, rcx
	mov	qword ptr [rbp-0x40], rbx
	cmp	byte ptr [rbx-0x18], 8
	jnz	$_076
	mov	rax, qword ptr [rbx-0x10]
	mov	eax, dword ptr [rax]
	cmp	ax, 76
	jnz	$_076
	sub	qword ptr [rbp-0x40], 24
	dec	rsi
$_076:	lea	rax, [rbp-0x4A]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rbp-0x30]
	mov	r8, rsi
	mov	rdx, qword ptr [rbp-0x38]
	mov	rcx, qword ptr [rbp-0x10]
	call	$_001
	test	rax, rax
	jz	$_077
	mov	eax, 1
$_077:	mov	dword ptr [rbp-0x44], eax
	mov	rsi, qword ptr [rbp-0x30]
	cmp	dword ptr [rbp-0x8], 0
	je	$_087
	mov	rcx, rsi
	sub	rcx, rdi
	mov	dword ptr [rbp-0x48], ecx
	mov	r8d, ecx
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x28]
	call	tmemcpy@PLT
	mov	ecx, dword ptr [rbp-0x48]
	mov	byte ptr [rax+rcx], 0
	cmp	byte ptr [rbp-0x4B], 0
	jnz	$_085
	inc	byte ptr [rbp-0x4B]
	mov	edx, 34
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_085
	mov	esi, 1
	lea	rdi, [rax+0x1]
$_078:	mov	al, byte ptr [rdi]
	test	al, al
	jz	$_084
	cmp	al, 34
	jnz	$_083
	cmp	byte ptr [rdi-0x1], 92
	jnz	$_079
	jmp	$_083

$_079:	test	esi, esi
	jnz	$_080
	inc	esi
	jmp	$_083

$_080:	cmp	byte ptr [rdi-0x1], 34
	jnz	$_081
	xor	esi, esi
	jmp	$_083

$_081:	cmp	byte ptr [rdi+0x1], 34
	jnz	$_082
	lea	rdx, [rdi+0x2]
	mov	rcx, rdi
	call	tstrcpy@PLT
	dec	rdi
	jmp	$_083

$_082:	xor	esi, esi
$_083:	inc	rdi
	jmp	$_078

$_084:	mov	rsi, qword ptr [rbp-0x30]
$_085:	mov	rdx, qword ptr [rbp-0x28]
	mov	rcx, qword ptr [rbp-0x20]
	call	tstrstr@PLT
	test	rax, rax
	jz	$_087
	mov	rdi, rax
	mov	ecx, dword ptr [rbp-0x48]
	lea	rcx, [rdi+rcx]
	call	tstrstart@PLT
	cmp	ecx, 44
	jz	$_086
	cmp	ecx, 41
	jz	$_086
	mov	edx, 34
	lea	rcx, [rdi+0x1]
	call	tstrrchr@PLT
	test	rax, rax
	jz	$_086
	add	rax, 1
$_086:	test	rax, rax
	jz	$_087
	mov	rdx, rax
	mov	rcx, qword ptr [rbp-0x28]
	call	tstrcpy@PLT
	lea	rdx, [DS0004+rip]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbp-0x10]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbp-0x28]
	mov	rcx, rdi
	call	tstrcat@PLT
$_087:	cmp	dword ptr [rbp-0x44], 0
	jz	$_093
	mov	rdx, qword ptr [rbp-0x38]
	mov	eax, dword ptr [rdx]
	and	eax, 0xFFFFFF
	cmp	eax, 8738
	jz	$_090
	cmp	byte ptr [rbp-0x4A], 0
	jz	$_088
	lea	rcx, [DS0005+rip]
	jmp	$_089

$_088:	lea	rcx, [DS0006+rip]
$_089:	mov	r9, rdx
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, rcx
	mov	rcx, qword ptr [rbp-0x28]
	call	tsprintf@PLT
	jmp	$_093

$_090:	cmp	byte ptr [rbp-0x4A], 0
	jz	$_091
	lea	rcx, [DS0007+rip]
	jmp	$_092

$_091:	lea	rcx, [DS0008+rip]
$_092:	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, rcx
	mov	rcx, qword ptr [rbp-0x28]
	call	tsprintf@PLT
$_093:	mov	rax, qword ptr [rbp-0x40]
	mov	rax, qword ptr [rax+0x10]
	mov	di, word ptr [rax]
	mov	byte ptr [rax], 0
	mov	rax, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rax+0x10]
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrcpy@PLT
	lea	rdx, [DS0004+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbp-0x10]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rax, qword ptr [rbp-0x40]
	mov	rax, qword ptr [rax+0x10]
	mov	word ptr [rax], di
	mov	rcx, rsi
	jmp	$_095

$_094:	add	rcx, 1
$_095:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_094
	xchg	rax, rcx
	mov	rsi, rax
	test	ecx, ecx
	jz	$_097
	cmp	ecx, 41
	jz	$_096
	lea	rdx, [DS0004+0x4+rip]
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrcat@PLT
$_096:	mov	rdx, rsi
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrcat@PLT
$_097:	cmp	dword ptr [rbp-0x44], 0
	jz	$_099
	mov	rcx, qword ptr [rbp-0x18]
	call	$_056
	lea	rcx, [DS0009+rip]
	call	AddLineQueue@PLT
	cmp	byte ptr [rbp-0x4A], 0
	jz	$_098
	lea	rcx, [DS000A+rip]
	call	AddLineQueue@PLT
$_098:	mov	rcx, qword ptr [rbp-0x28]
	call	AddLineQueue@PLT
	lea	rcx, [DS000B+rip]
	call	AddLineQueue@PLT
	mov	rcx, qword ptr [rbp-0x18]
	call	AddLineQueue@PLT
	call	InsertLineQueue@PLT
$_099:	mov	rdx, qword ptr [rbp-0x38]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rcx, qword ptr [ModuleInfo+0x180+rip]
	sub	rbx, qword ptr [rbp+0x30]
	add	rbx, rcx
	mov	qword ptr [rbp+0x30], rcx
	imul	eax, dword ptr [rbp+0x28], 24
	add	rax, rcx
	mov	qword ptr [rbp-0x40], rax
	jmp	$_102

$_100:	cmp	al, 41
	jnz	$_101
	cmp	byte ptr [rbp-0x49], 0
	jz	$_104
	dec	byte ptr [rbp-0x49]
	jz	$_104
	jmp	$_102

$_101:	cmp	al, 40
	jnz	$_102
	inc	byte ptr [rbp-0x49]
$_102:	add	rbx, 24
$_103:	cmp	byte ptr [rbx], 0
	jne	$_074
$_104:	cmp	dword ptr [rbp-0x8], 0
	jnz	$_105
	xor	r8d, r8d
	mov	edx, dword ptr [list_pos+rip]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
	jmp	$_106

$_105:	mov	ebx, dword ptr [ModuleInfo+0x210+rip]
	mov	dword ptr [ModuleInfo+0x210+rip], 0
	xor	r8d, r8d
	mov	edx, dword ptr [list_pos+rip]
	mov	rcx, qword ptr [rbp-0x20]
	call	StoreLine@PLT
	mov	dword ptr [ModuleInfo+0x210+rip], ebx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
$_106:	mov	al, byte ptr [rbp-0x4C]
	mov	byte ptr [ModuleInfo+0x1C6+rip], al
	cmp	byte ptr [rbp-0x4D], 0
	jz	$_107
	mov	rcx, qword ptr [rbp-0x38]
	call	MemFree@PLT
$_107:	mov	eax, dword ptr [rbp-0x4]
$_108:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_109:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	mov	byte ptr [rbp-0x26], 0
	mov	rbx, rdx
	mov	edi, dword ptr [ModuleInfo+0x174+rip]
	lea	ecx, [rdi+rdi+0x20]
	cmp	edi, 2048
	jbe	$_110
	inc	byte ptr [rbp-0x26]
	call	MemAlloc@PLT
	jmp	$_111

$_110:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
$_111:	mov	qword ptr [rbp-0x10], rax
	lea	rcx, [rax+rdi]
	lea	rdx, [rax+rdi*2]
	mov	qword ptr [rbp-0x8], rcx
	mov	qword ptr [rbp-0x18], rdx
	lea	rdx, [DS000C+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	mov	edi, eax
	test	edi, edi
	jz	$_118
	jmp	$_114

$_112:	cmp	byte ptr [rbx], 8
	jnz	$_113
	lea	rdx, [DS000C+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jz	$_115
$_113:	add	rbx, 24
$_114:	cmp	byte ptr [rbx], 0
	jnz	$_112
$_115:	cmp	byte ptr [rbx], 0
	jnz	$_116
	cmp	byte ptr [rbx+0x18], 40
	jnz	$_116
	add	rbx, 24
	jmp	$_118

$_116:	cmp	byte ptr [rbx], 0
	jz	$_117
	add	rbx, 24
	jmp	$_118

$_117:	mov	rbx, qword ptr [rbp+0x30]
$_118:	cmp	byte ptr [rbx], 40
	jnz	$_119
	cmp	byte ptr [rbx+0x18], 10
	jnz	$_119
	cmp	byte ptr [rbx+0x30], 41
	jz	$_120
$_119:	cmp	byte ptr [rbx+0x18], 45
	jne	$_131
	cmp	byte ptr [rbx+0x30], 10
	jne	$_131
	cmp	byte ptr [rbx+0x48], 41
	jne	$_131
$_120:	cmp	byte ptr [rbp-0x26], 0
	jz	$_121
	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_121:	cmp	byte ptr [rbx+0x18], 45
	jnz	$_122
	add	rbx, 24
$_122:	add	rbx, 24
	mov	r9d, dword ptr [rbx+0x4]
	movsx	r8d, byte ptr [rbx+0x1]
	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [rbp-0x90]
	call	_atoow@PLT
	cmp	dword ptr [rbp-0x88], 0
	jnz	$_123
	cmp	dword ptr [rbp-0x84], 0
	jz	$_124
$_123:	mov	ecx, 2156
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_155

$_124:	mov	ecx, dword ptr [rbp-0x90]
	mov	rdx, qword ptr [ModuleInfo+0xF0+rip]
	cmp	byte ptr [rbx-0x18], 45
	jnz	$_126
	xor	eax, eax
	test	rdx, rdx
	jz	$_125
	movzx	eax, word ptr [rdx+0x14]
$_125:	add	eax, ecx
	jmp	$_130

$_126:	mov	eax, ecx
$_127:	test	eax, eax
	jz	$_128
	test	rdx, rdx
	jz	$_128
	dec	eax
	mov	rdx, qword ptr [rdx+0xC]
	jmp	$_127

$_128:	test	rdx, rdx
	jnz	$_129
	mov	ecx, 2156
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_155

$_129:	movzx	eax, word ptr [rdx+0x14]
$_130:	mov	r8d, eax
	lea	rdx, [DS0001+rip]
	mov	rcx, qword ptr [rbp+0x28]
	call	tsprintf@PLT
	mov	eax, 1
	jmp	$_155

$_131:	cmp	byte ptr [rbx], 0
	je	$_153
	mov	rsi, qword ptr [rbx+0x10]
	cmp	byte ptr [rbx], 8
	jnz	$_133
	cmp	byte ptr [rbx-0x18], 40
	jnz	$_133
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_133
	mov	rax, qword ptr [rax+0x28]
	cmp	byte ptr [rax], 34
	jz	$_132
	cmp	word ptr [rax], 8780
	jnz	$_133
$_132:	mov	rsi, rax
$_133:	cmp	byte ptr [rsi], 34
	jz	$_134
	cmp	word ptr [rsi], 8780
	jne	$_152
$_134:	lea	rax, [rbp-0x25]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rbp-0x20]
	mov	r8, rsi
	mov	rdx, qword ptr [rbp-0x8]
	mov	rcx, qword ptr [rbp-0x18]
	call	$_001
	mov	esi, eax
	test	edi, edi
	jz	$_135
	mov	rdx, qword ptr [rbp-0x18]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcat@PLT
	jmp	$_136

$_135:	mov	rax, qword ptr [rbp-0x18]
	mov	word ptr [rax], 32
$_136:	test	esi, esi
	je	$_150
	mov	rax, qword ptr [rbp-0x8]
	mov	eax, dword ptr [rax]
	and	eax, 0xFFFFFF
	cmp	eax, 8738
	jz	$_139
	cmp	byte ptr [rbp-0x25], 0
	jz	$_137
	lea	rdx, [DS0005+rip]
	jmp	$_138

$_137:	lea	rdx, [DS0006+rip]
$_138:	mov	r9, qword ptr [rbp-0x8]
	mov	r8, qword ptr [rbp-0x18]
	mov	rcx, qword ptr [rbp-0x10]
	call	tsprintf@PLT
	jmp	$_142

$_139:	cmp	byte ptr [rbp-0x25], 0
	jz	$_140
	lea	rdx, [DS0007+rip]
	jmp	$_141

$_140:	lea	rdx, [DS0008+rip]
$_141:	mov	r8, qword ptr [rbp-0x18]
	mov	rcx, qword ptr [rbp-0x10]
	call	tsprintf@PLT
$_142:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_143
	call	RunLineQueue@PLT
$_143:	xor	esi, esi
	mov	rbx, qword ptr [ModuleInfo+0x1F8+rip]
	test	rbx, rbx
	jz	$_144
	lea	rdx, [DS000D+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jz	$_144
	inc	esi
	lea	rcx, [DS0009+rip]
	call	AddLineQueue@PLT
$_144:	test	edi, edi
	jz	$_145
	test	esi, esi
	jnz	$_145
	mov	esi, 2
	lea	rcx, [DS000E+rip]
	call	AddLineQueue@PLT
$_145:	cmp	byte ptr [rbp-0x25], 0
	jz	$_146
	lea	rcx, [DS000A+rip]
	call	AddLineQueue@PLT
$_146:	mov	rcx, qword ptr [rbp-0x10]
	call	AddLineQueue@PLT
	test	esi, esi
	jz	$_149
	lea	rdx, [DS000F+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_147
	lea	rcx, [DS000E+rip]
	call	AddLineQueue@PLT
	jmp	$_149

$_147:	cmp	esi, 2
	jnz	$_148
	lea	rcx, [DS0009+rip]
	call	AddLineQueue@PLT
	jmp	$_149

$_148:	lea	rcx, [DS0003+rip]
	call	AddLineQueue@PLT
$_149:	call	InsertLineQueue@PLT
$_150:	cmp	byte ptr [rbp-0x26], 0
	jz	$_151
	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_151:	mov	eax, 1
	jmp	$_155

$_152:	add	rbx, 24
	jmp	$_131

$_153:	cmp	byte ptr [rbp-0x26], 0
	jz	$_154
	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_154:	xor	eax, eax
$_155:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CreateFloat:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	mov	rbx, rdx
	mov	rax, qword ptr [rbx]
	mov	qword ptr [rbp-0xA8], rax
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0xA0], rax
	jmp	$_164

$_156:	cmp	byte ptr [rbx+0x40], 35
	je	$_165
	mov	byte ptr [rbp-0x65], 0
	test	byte ptr [rbx+0xF], 0xFFFFFF80
	jz	$_157
	mov	byte ptr [rbp-0x65], 32
	and	byte ptr [rbp-0x99], 0x7F
$_157:	mov	rdx, rbx
	lea	rcx, [rbp-0xA8]
	call	__cvtq_ss@PLT
	cmp	byte ptr [rbp-0x65], 32
	jnz	$_158
	or	byte ptr [rbp-0xA5], 0xFFFFFF80
$_158:	jmp	$_165

$_159:	cmp	byte ptr [rbx+0x40], 39
	jz	$_165
	mov	byte ptr [rbp-0x65], 0
	test	byte ptr [rbx+0xF], 0xFFFFFF80
	jz	$_160
	mov	byte ptr [rbp-0x65], 32
	and	byte ptr [rbp-0x99], 0x7F
$_160:	mov	rdx, rbx
	lea	rcx, [rbp-0xA8]
	call	__cvtq_sd@PLT
	cmp	byte ptr [rbp-0x65], 32
	jnz	$_161
	or	byte ptr [rbp-0xA1], 0xFFFFFF80
$_161:	jmp	$_165

$_162:	mov	rdx, rbx
	lea	rcx, [rbp-0xA8]
	call	__cvtq_ld@PLT
	mov	dword ptr [rbp-0x9C], 0
	mov	word ptr [rbp-0x9E], 0
$_163:	jmp	$_165

$_164:	cmp	dword ptr [rbp+0x28], 4
	je	$_156
	cmp	dword ptr [rbp+0x28], 8
	jz	$_159
	cmp	dword ptr [rbp+0x28], 10
	jz	$_162
	cmp	dword ptr [rbp+0x28], 16
	jz	$_163
$_165:	xor	edi, edi
	mov	rsi, qword ptr [ModuleInfo+0x118+rip]
$_166:	test	rsi, rsi
	jz	$_168
	mov	eax, dword ptr [rsi+0x8]
	cmp	dword ptr [rbp+0x28], eax
	jnz	$_167
	mov	rax, qword ptr [rsi]
	mov	edx, dword ptr [rbp-0xA0]
	mov	ecx, dword ptr [rbp-0x9C]
	cmp	edx, dword ptr [rax+0x8]
	jnz	$_167
	cmp	ecx, dword ptr [rax+0xC]
	jnz	$_167
	mov	edx, dword ptr [rbp-0xA8]
	mov	ecx, dword ptr [rbp-0xA4]
	cmp	edx, dword ptr [rax]
	jnz	$_167
	cmp	ecx, dword ptr [rax+0x4]
	jnz	$_167
	mov	eax, dword ptr [rsi+0x18]
	mov	r8d, eax
	lea	rdx, [DS0010+rip]
	mov	rcx, qword ptr [rbp+0x38]
	call	tsprintf@PLT
	mov	eax, 1
	jmp	$_176

$_167:	inc	edi
	mov	rsi, qword ptr [rsi+0x10]
	jmp	$_166

$_168:	mov	r8d, edi
	lea	rdx, [DS0010+rip]
	mov	rcx, qword ptr [rbp+0x38]
	call	tsprintf@PLT
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_175
	mov	ecx, 48
	call	LclAlloc@PLT
	mov	dword ptr [rax+0x18], edi
	mov	ecx, dword ptr [rbp+0x28]
	mov	dword ptr [rax+0x8], ecx
	mov	rcx, qword ptr [ModuleInfo+0x118+rip]
	mov	qword ptr [rax+0x10], rcx
	mov	qword ptr [ModuleInfo+0x118+rip], rax
	lea	rcx, [rax+0x20]
	mov	qword ptr [rax], rcx
	mov	r8d, 16
	lea	rdx, [rbp-0xA8]
	call	tmemcpy@PLT
	lea	rcx, [rbp-0x40]
	call	$_056
	lea	rcx, [DS0009+rip]
	call	AddLineQueue@PLT
	mov	ecx, dword ptr [rbp+0x28]
	cmp	ecx, 10
	jnz	$_169
	mov	ecx, 16
$_169:	mov	edx, ecx
	lea	rcx, [DS0011+rip]
	call	AddLineQueueX@PLT
	jmp	$_173

$_170:	mov	r8d, dword ptr [rbp-0xA8]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [DS0012+rip]
	call	AddLineQueueX@PLT
	jmp	$_174

$_171:	mov	r8, qword ptr [rbp-0xA8]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
	jmp	$_174

$_172:	mov	r8d, dword ptr [rbp+0x28]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
	mov	r8, qword ptr [rbp-0xA8]
	mov	rdx, qword ptr [rbp-0xA0]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	jmp	$_174

$_173:	cmp	dword ptr [rbp+0x28], 4
	jz	$_170
	cmp	dword ptr [rbp+0x28], 8
	jz	$_171
	cmp	dword ptr [rbp+0x28], 10
	jz	$_172
	cmp	dword ptr [rbp+0x28], 16
	jz	$_172
$_174:	lea	rcx, [DS000B+rip]
	call	AddLineQueue@PLT
	lea	rcx, [rbp-0x40]
	call	AddLineQueue@PLT
	call	InsertLineQueue@PLT
$_175:	xor	eax, eax
$_176:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

TextItemError:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rax, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 9
	jnz	$_177
	cmp	byte ptr [rax], 60
	jnz	$_177
	mov	ecx, 2045
	call	asmerr@PLT
	jmp	$_180

$_177:	cmp	byte ptr [rbx], 8
	jnz	$_179
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_178
	cmp	byte ptr [rax+0x18], 0
	jnz	$_179
$_178:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_180

$_179:	mov	ecx, 2051
	call	asmerr@PLT
$_180:	leave
	pop	rbx
	ret

CatStrDir:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	edi, ecx
	inc	edi
	imul	ebx, edi, 24
	add	rbx, rdx
	xor	esi, esi
$_181:	cmp	edi, dword ptr [ModuleInfo+0x220+rip]
	jge	$_186
	cmp	byte ptr [rbx], 9
	jnz	$_182
	cmp	byte ptr [rbx+0x1], 60
	jz	$_183
$_182:	mov	rcx, rbx
	call	TextItemError
	jmp	$_194

$_183:	add	esi, dword ptr [rbx+0x4]
	cmp	esi, 2048
	jc	$_184
	mov	ecx, 2041
	call	asmerr@PLT
	jmp	$_194

$_184:	inc	edi
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jz	$_185
	cmp	byte ptr [rbx], 0
	jz	$_185
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_194

$_185:	inc	edi
	add	rbx, 24
	jmp	$_181

$_186:	mov	rbx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rdi, rax
	test	rdi, rdi
	jnz	$_187
	mov	rcx, qword ptr [rbx+0x8]
	call	SymCreate@PLT
	mov	rdi, rax
	jmp	$_189

$_187:	cmp	byte ptr [rdi+0x18], 0
	jnz	$_188
	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	call	SkipSavedState@PLT
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 6005
	call	asmerr@PLT
	jmp	$_189

$_188:	cmp	byte ptr [rdi+0x18], 10
	jz	$_189
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_194

$_189:	mov	byte ptr [rdi+0x18], 10
	or	byte ptr [rdi+0x14], 0x02
	inc	esi
	cmp	dword ptr [rdi+0x50], esi
	jnc	$_190
	mov	dword ptr [rdi+0x50], esi
	mov	ecx, esi
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x28], rax
$_190:	mov	qword ptr [rbp-0x8], rdi
	add	rbx, 48
	mov	edx, 2
	mov	rdi, qword ptr [rdi+0x28]
$_191:	cmp	edx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_192
	mov	ecx, dword ptr [rbx+0x4]
	mov	rsi, qword ptr [rbx+0x8]
	rep movsb
	add	edx, 2
	add	rbx, 48
	jmp	$_191

$_192:	mov	byte ptr [rdi], 0
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_193
	mov	r8, qword ptr [rbp-0x8]
	xor	edx, edx
	mov	ecx, 3
	call	LstWrite@PLT
$_193:	xor	eax, eax
$_194:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SetTextMacro:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rdx
	test	rdi, rdi
	jnz	$_195
	mov	rcx, qword ptr [rbp+0x38]
	call	SymCreate@PLT
	mov	rdi, rax
	jmp	$_197

$_195:	cmp	byte ptr [rdi+0x18], 0
	jnz	$_196
	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	call	SkipSavedState@PLT
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 6005
	call	asmerr@PLT
	jmp	$_197

$_196:	cmp	byte ptr [rdi+0x18], 10
	jz	$_197
	mov	rdx, qword ptr [rbp+0x38]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_203

$_197:	mov	byte ptr [rdi+0x18], 10
	or	byte ptr [rdi+0x14], 0x02
	mov	rbx, qword ptr [rbp+0x28]
	cmp	byte ptr [rbx+0x30], 9
	jnz	$_199
	cmp	byte ptr [rbx+0x31], 60
	jnz	$_199
	cmp	byte ptr [rbx+0x48], 0
	jz	$_198
	mov	rdx, qword ptr [rbx+0x58]
	mov	ecx, 2008
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_203

$_198:	mov	rax, qword ptr [rbx+0x38]
	mov	qword ptr [rbp+0x40], rax
	mov	esi, dword ptr [rbx+0x34]
	jmp	$_201

$_199:	mov	rcx, qword ptr [rbp+0x40]
	call	tstrlen@PLT
	mov	esi, eax
	mov	rdx, qword ptr [rbp+0x40]
$_200:	test	esi, esi
	jz	$_201
	movzx	eax, byte ptr [rdx+rsi-0x1]
	test	byte ptr [r15+rax], 0x08
	jz	$_201
	dec	esi
	jmp	$_200

$_201:	lea	ecx, [rsi+0x1]
	cmp	dword ptr [rdi+0x50], ecx
	jnc	$_202
	mov	dword ptr [rdi+0x50], ecx
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x28], rax
$_202:	mov	r8d, esi
	mov	rdx, qword ptr [rbp+0x40]
	mov	rcx, qword ptr [rdi+0x28]
	call	tmemcpy@PLT
	mov	rdx, qword ptr [rdi+0x28]
	mov	byte ptr [rdx+rsi], 0
	mov	rax, rdi
$_203:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AddPredefinedText:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x10]
	call	SymFind@PLT
	test	rax, rax
	jnz	$_204
	mov	rcx, qword ptr [rbp+0x10]
	call	SymCreate@PLT
$_204:	mov	byte ptr [rax+0x18], 10
	or	byte ptr [rax+0x14], 0x22
	mov	rcx, qword ptr [rbp+0x18]
	mov	qword ptr [rax+0x28], rcx
	mov	dword ptr [rax+0x50], 0
	leave
	ret

SubStrDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	rbx, rdx
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	inc	dword ptr [rbp+0x28]
	imul	eax, dword ptr [rbp+0x28], 24
	add	rbx, rax
	cmp	byte ptr [rbx], 9
	jnz	$_205
	cmp	byte ptr [rbx+0x1], 60
	jz	$_206
$_205:	mov	rcx, rbx
	call	TextItemError
	jmp	$_225

$_206:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x10], rax
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0x18], eax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jz	$_207
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_225

$_207:	inc	dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_208
	mov	rax, -1
	jmp	$_225

$_208:	cmp	dword ptr [rbp-0x4C], 0
	jz	$_209
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_225

$_209:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbp-0x88]
	mov	dword ptr [rbp-0x14], eax
	cmp	dword ptr [rbp-0x14], 0
	jg	$_210
	mov	ecx, 2090
	call	asmerr@PLT
	jmp	$_225

$_210:	cmp	byte ptr [rbx], 0
	je	$_216
	cmp	byte ptr [rbx], 44
	jz	$_211
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_225

$_211:	inc	dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_212
	mov	rax, -1
	jmp	$_225

$_212:	cmp	dword ptr [rbp-0x4C], 0
	jz	$_213
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_225

$_213:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	edi, dword ptr [rbp-0x88]
	cmp	byte ptr [rbx], 0
	jz	$_214
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_225

$_214:	cmp	edi, 0
	jge	$_215
	mov	ecx, 2092
	call	asmerr@PLT
	jmp	$_225

$_215:	mov	dword ptr [rbp-0x1C], 1
	jmp	$_217

$_216:	mov	edi, 4294967295
	mov	dword ptr [rbp-0x1C], 0
$_217:	mov	ebx, dword ptr [rbp-0x14]
	cmp	ebx, dword ptr [rbp-0x18]
	jle	$_218
	mov	edx, ebx
	mov	ecx, 2091
	call	asmerr@PLT
	jmp	$_225

$_218:	lea	eax, [rbx+rdi-0x1]
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_219
	cmp	eax, dword ptr [rbp-0x18]
	jle	$_219
	mov	ecx, 2093
	call	asmerr@PLT
	jmp	$_225

$_219:	lea	rax, [rbx-0x1]
	add	qword ptr [rbp-0x10], rax
	cmp	edi, -1
	jnz	$_220
	mov	eax, dword ptr [rbp-0x18]
	sub	eax, ebx
	lea	edi, [rax+0x1]
$_220:	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	mov	rsi, rax
	test	rsi, rsi
	jnz	$_221
	mov	rcx, qword ptr [rbp-0x8]
	call	SymCreate@PLT
	mov	rsi, rax
	jmp	$_223

$_221:	cmp	byte ptr [rsi+0x18], 0
	jnz	$_222
	mov	rdx, rsi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
	call	SkipSavedState@PLT
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 6005
	call	asmerr@PLT
	jmp	$_223

$_222:	cmp	byte ptr [rsi+0x18], 10
	jz	$_223
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_225

$_223:	mov	byte ptr [rsi+0x18], 10
	or	byte ptr [rsi+0x14], 0x02
	inc	edi
	cmp	dword ptr [rsi+0x50], edi
	jnc	$_224
	mov	dword ptr [rsi+0x50], edi
	mov	ecx, edi
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x28], rax
$_224:	dec	edi
	mov	r8d, edi
	mov	rdx, qword ptr [rbp-0x10]
	mov	rcx, qword ptr [rsi+0x28]
	call	tmemcpy@PLT
	mov	byte ptr [rax+rdi], 0
	mov	r8, rsi
	xor	edx, edx
	mov	ecx, 3
	call	LstWrite@PLT
	xor	eax, eax
$_225:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SizeStrDir:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	cmp	ecx, 1
	jz	$_226
	imul	ebx, ecx, 24
	add	rbx, rdx
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_231

$_226:	mov	rbx, rdx
	cmp	byte ptr [rbx+0x30], 9
	jnz	$_227
	cmp	byte ptr [rbx+0x31], 60
	jz	$_228
$_227:	lea	rcx, [rbx+0x30]
	call	TextItemError
	jmp	$_231

$_228:	cmp	dword ptr [ModuleInfo+0x220+rip], 3
	jle	$_229
	mov	rdx, qword ptr [rbx+0x50]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_231

$_229:	mov	edx, dword ptr [rbx+0x34]
	mov	rcx, qword ptr [rbx+0x8]
	call	CreateVariable@PLT
	test	rax, rax
	jz	$_230
	mov	r8, rax
	xor	edx, edx
	mov	ecx, 2
	call	LstWrite@PLT
	xor	eax, eax
	jmp	$_231

$_230:	mov	rax, -1
$_231:	leave
	pop	rbx
	ret

InStrDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	dword ptr [rbp-0x6C], 1
	imul	ebx, ecx, 24
	add	rbx, rdx
	cmp	ecx, 1
	jz	$_232
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_248

$_232:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 9
	jnz	$_233
	cmp	byte ptr [rbx+0x1], 60
	je	$_238
$_233:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_234
	mov	rax, -1
	jmp	$_248

$_234:	cmp	dword ptr [rbp-0x2C], 0
	jz	$_235
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_248

$_235:	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [rbp-0x6C], eax
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x6C], 0
	jg	$_236
	mov	ecx, 7001
	call	asmerr@PLT
$_236:	cmp	byte ptr [rbx], 44
	jz	$_237
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_248

$_237:	add	rbx, 24
$_238:	cmp	byte ptr [rbx], 9
	jnz	$_239
	cmp	byte ptr [rbx+0x1], 60
	jz	$_240
$_239:	mov	rcx, rbx
	call	TextItemError
	jmp	$_248

$_240:	mov	rsi, qword ptr [rbx+0x8]
	mov	edi, dword ptr [rbx+0x4]
	cmp	dword ptr [rbp-0x6C], edi
	jle	$_241
	mov	edx, dword ptr [rbp-0x6C]
	mov	ecx, 2091
	call	asmerr@PLT
	jmp	$_248

$_241:	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jz	$_242
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_248

$_242:	add	rbx, 24
	cmp	byte ptr [rbx], 9
	jnz	$_243
	cmp	byte ptr [rbx+0x1], 60
	jz	$_244
$_243:	mov	rcx, rbx
	call	TextItemError
	jmp	$_248

$_244:	cmp	byte ptr [rbx+0x18], 0
	jz	$_245
	mov	rdx, qword ptr [rbx+0x20]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_248

$_245:	mov	edx, dword ptr [rbx+0x4]
	xor	eax, eax
	cmp	dword ptr [rbp-0x6C], 0
	jle	$_246
	cmp	edi, edx
	jc	$_246
	test	edx, edx
	jz	$_246
	mov	ecx, dword ptr [rbp-0x6C]
	lea	rax, [rsi-0x1]
	add	rcx, rax
	mov	rdx, qword ptr [rbx+0x8]
	call	tstrstr@PLT
	test	rax, rax
	jz	$_246
	sub	rax, rsi
	add	rax, 1
$_246:	mov	rbx, qword ptr [rbp+0x30]
	mov	edx, eax
	mov	rcx, qword ptr [rbx+0x8]
	call	CreateVariable@PLT
	test	rax, rax
	jz	$_247
	mov	r8, rax
	xor	edx, edx
	mov	ecx, 2
	call	LstWrite@PLT
	xor	eax, eax
	jmp	$_248

$_247:	mov	rax, -1
$_248:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CatStrFunc:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	mov	rsi, qword ptr [rdi+0x18]
	mov	rsi, qword ptr [rsi]
$_249:	cmp	dword ptr [rdi+0x28], 0
	jz	$_250
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	ebx, eax
	mov	r8d, ebx
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x30]
	call	tmemcpy@PLT
	mov	edx, ebx
	mov	rax, rsi
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
	mov	rsi, rax
	add	qword ptr [rbp+0x30], rbx
	dec	dword ptr [rdi+0x28]
	jmp	$_249

$_250:
	mov	rdx, qword ptr [rbp+0x30]
	mov	byte ptr [rdx], 0
	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ComAllocFunc:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, qword ptr [rbp+0x20]
	mov	rcx, qword ptr [rbp+0x18]
	call	ComAlloc@PLT
	test	rax, rax
	jnz	$_251
	mov	rdx, qword ptr [rbp+0x10]
	mov	rdx, qword ptr [rdx+0x18]
	mov	rdx, qword ptr [rdx]
	mov	rcx, qword ptr [rbp+0x18]
	call	tstrcpy@PLT
$_251:	xor	eax, eax
	leave
	ret

TypeIdFunc:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, qword ptr [rbp+0x20]
	mov	rcx, qword ptr [rbp+0x18]
	call	GetTypeId@PLT
	test	rax, rax
	jnz	$_252
	mov	rdx, qword ptr [rbp+0x10]
	mov	rdx, qword ptr [rdx+0x18]
	mov	rdx, qword ptr [rdx]
	mov	rcx, qword ptr [rbp+0x18]
	call	tstrcpy@PLT
$_252:	xor	eax, eax
	leave
	ret

CStringFunc:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, qword ptr [rbp+0x20]
	mov	rcx, qword ptr [rbp+0x18]
	call	$_109
	test	rax, rax
	jnz	$_253
	mov	rdx, qword ptr [rbp+0x10]
	mov	rdx, qword ptr [rdx+0x18]
	mov	rdx, qword ptr [rdx]
	mov	rcx, qword ptr [rbp+0x18]
	call	tstrcpy@PLT
$_253:	xor	eax, eax
	leave
	ret

RegFunc:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	dword ptr [rbp-0x70], 4
	mov	rbx, qword ptr [rcx+0x18]
	mov	rcx, qword ptr [rbx]
	test	rcx, rcx
	jnz	$_254
	xor	eax, eax
	jmp	$_260

$_254:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	inc	eax
	mov	dword ptr [rbp-0x6C], eax
	mov	dword ptr [rbp-0x74], eax
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x28]
	mov	edx, eax
	call	Tokenize@PLT
	mov	ecx, eax
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x74]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_255
	jmp	$_260

$_255:	cmp	dword ptr [rbp-0x2C], 2
	jz	$_256
	imul	ecx, dword ptr [rbp-0x74], 24
	add	rcx, qword ptr [rbp+0x28]
	mov	rdx, qword ptr [rcx-0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_260

$_256:	mov	rcx, qword ptr [rbp-0x50]
	mov	eax, dword ptr [rcx+0x4]
	mov	dword ptr [rbp-0x74], eax
	mov	rcx, qword ptr [rbx+0x8]
	test	rcx, rcx
	jz	$_259
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x28]
	mov	edx, dword ptr [rbp-0x6C]
	call	Tokenize@PLT
	mov	ecx, eax
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x6C]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_257
	jmp	$_260

$_257:	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [rbp-0x70], eax
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_258
	cmp	eax, 1
	jc	$_258
	cmp	eax, 8
	jbe	$_259
$_258:	imul	ecx, dword ptr [rbp-0x6C], 24
	add	rcx, qword ptr [rbp+0x28]
	mov	rdx, qword ptr [rcx-0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_260

$_259:	mov	edx, dword ptr [rbp-0x70]
	mov	ecx, dword ptr [rbp-0x74]
	call	get_register@PLT
	mov	ecx, eax
	mov	rdx, qword ptr [rbp+0x20]
	call	GetResWName@PLT
	xor	eax, eax
$_260:	leave
	pop	rbx
	ret

$_261:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 160
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	inc	eax
	mov	dword ptr [rbp-0x6C], eax
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x20]
	mov	edx, eax
	mov	rcx, qword ptr [rbp+0x10]
	call	Tokenize@PLT
	mov	edx, eax
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, edx
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [rbp-0x6C]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_262
	mov	rax, -1
	jmp	$_265

$_262:	imul	ecx, dword ptr [rbp-0x6C], 24
	add	rcx, qword ptr [rbp+0x20]
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_263
	cmp	byte ptr [rcx], 0
	jz	$_264
$_263:	mov	rdx, qword ptr [rbp+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_265

$_264:	mov	rcx, qword ptr [rbp+0x18]
	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [rcx], eax
	xor	eax, eax
$_265:	leave
	ret

InStrFunc:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	dword ptr [rbp-0x4], 1
	mov	rdi, rdx
	mov	eax, 48
	mov	word ptr [rdi], ax
	mov	rsi, qword ptr [rcx+0x18]
	mov	rbx, qword ptr [rsi]
	test	rbx, rbx
	jz	$_267
	mov	r8, qword ptr [rbp+0x38]
	lea	rdx, [rbp-0x4]
	mov	rcx, rbx
	call	$_261
	cmp	eax, -1
	jnz	$_266
	mov	rax, -1
	jmp	$_270

$_266:	cmp	dword ptr [rbp-0x4], 0
	jnz	$_267
	inc	dword ptr [rbp-0x4]
$_267:	mov	rbx, qword ptr [rsi+0x8]
	mov	rcx, rbx
	call	tstrlen@PLT
	cmp	dword ptr [rbp-0x4], eax
	jle	$_268
	mov	edx, dword ptr [rbp-0x4]
	mov	ecx, 2091
	call	asmerr@PLT
	jmp	$_270

$_268:	mov	rdx, qword ptr [rsi+0x10]
	cmp	byte ptr [rdx], 0
	jz	$_269
	mov	ecx, dword ptr [rbp-0x4]
	add	rcx, rbx
	dec	rcx
	call	tstrstr@PLT
	test	rax, rax
	jz	$_269
	sub	rax, rbx
	lea	rcx, [rax+0x1]
	mov	dword ptr [rsp+0x20], 1
	xor	r9d, r9d
	movzx	r8d, byte ptr [ModuleInfo+0x1C4+rip]
	mov	rdx, qword ptr [rbp+0x30]
	call	myltoa@PLT
$_269:	xor	eax, eax
$_270:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SizeStrFunc:
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	rdx, qword ptr [rcx+0x18]
	mov	rcx, qword ptr [rdx]
	test	rcx, rcx
	jz	$_271
	call	tstrlen@PLT
	mov	ecx, eax
	mov	dword ptr [rsp+0x20], 1
	xor	r9d, r9d
	movzx	r8d, byte ptr [ModuleInfo+0x1C4+rip]
	mov	rdx, qword ptr [rbp+0x18]
	call	myltoa@PLT
	jmp	$_272

$_271:	mov	rdx, qword ptr [rbp+0x18]
	mov	eax, 48
	mov	word ptr [rdx], ax
$_272:	xor	eax, eax
	leave
	ret

SubStrFunc:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, qword ptr [rcx+0x18]
	mov	rdi, qword ptr [rsi]
	mov	r8, qword ptr [rbp+0x38]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rsi+0x8]
	call	$_261
	cmp	eax, -1
	je	$_279
	cmp	dword ptr [rbp-0x4], 0
	jg	$_274
	cmp	dword ptr [rbp-0x4], 0
	jz	$_273
	mov	edx, dword ptr [rbp-0x4]
	mov	ecx, 2091
	call	asmerr@PLT
	jmp	$_279

$_273:	mov	dword ptr [rbp-0x4], 1
$_274:	mov	rcx, rdi
	call	tstrlen@PLT
	mov	ebx, eax
	cmp	dword ptr [rbp-0x4], ebx
	jle	$_275
	mov	edx, dword ptr [rbp-0x4]
	mov	ecx, 2091
	call	asmerr@PLT
	jmp	$_279

$_275:	sub	ebx, dword ptr [rbp-0x4]
	inc	ebx
	mov	rdi, qword ptr [rsi+0x10]
	test	rdi, rdi
	jz	$_278
	mov	r8, qword ptr [rbp+0x38]
	lea	rdx, [rbp-0xC]
	mov	rcx, rdi
	call	$_261
	cmp	eax, -1
	jz	$_279
	cmp	dword ptr [rbp-0xC], 0
	jge	$_276
	mov	ecx, 2092
	call	asmerr@PLT
	jmp	$_279

$_276:	cmp	dword ptr [rbp-0xC], ebx
	jle	$_277
	mov	ecx, 2093
	call	asmerr@PLT
	jmp	$_279

$_277:	mov	ebx, dword ptr [rbp-0xC]
$_278:	mov	rdi, qword ptr [rbp+0x30]
	mov	ecx, ebx
	mov	eax, dword ptr [rbp-0x4]
	add	rax, qword ptr [rsi]
	lea	rsi, [rax-0x1]
	rep movsb
	mov	byte ptr [rdi], 0
	xor	eax, eax
$_279:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

StringInit:
	push	rsi
	push	rdi
	sub	rsp, 40
	lea	rcx, [DS0016+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [ComAllocFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 2
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 2
	mov	ecx, 32
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 1
	mov	qword ptr [rax+0x10], 0
	mov	byte ptr [rax+0x18], 0
	lea	rcx, [DS0017+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [TypeIdFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 2
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 2
	mov	ecx, 32
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 0
	mov	qword ptr [rax+0x10], 0
	mov	byte ptr [rax+0x18], 0
	lea	rcx, [DS000C+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [CStringFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 2
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 1
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 1
	lea	rcx, [DS0018+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [RegFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 2
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 2
	mov	ecx, 32
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 1
	mov	qword ptr [rax+0x10], 0
	mov	byte ptr [rax+0x18], 0
	lea	rcx, [DS0019+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [CatStrFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 3
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 1
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 0
	lea	rcx, [DS001A+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [InStrFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 2
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 3
	mov	word ptr [rsi+0x2], 1
	mov	ecx, 48
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 0
	mov	qword ptr [rax+0x10], 0
	mov	byte ptr [rax+0x18], 1
	mov	qword ptr [rax+0x20], 0
	mov	byte ptr [rax+0x28], 1
	lea	rcx, [DS001B+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [SizeStrFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 2
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 1
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 0
	lea	rcx, [DS001C+rip]
	call	CreateMacro@PLT
	mov	rdi, rax
	mov	dword ptr [rdi+0x14], 34
	lea	rax, [SubStrFunc+rip]
	mov	qword ptr [rdi+0x28], rax
	mov	byte ptr [rdi+0x38], 2
	mov	rsi, qword ptr [rdi+0x68]
	mov	word ptr [rsi], 3
	mov	word ptr [rsi+0x2], 6
	mov	ecx, 48
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 1
	mov	qword ptr [rax+0x10], 0
	mov	byte ptr [rax+0x18], 1
	mov	qword ptr [rax+0x20], 0
	mov	byte ptr [rax+0x28], 0
	add	rsp, 40
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x44, 0x53, 0x25, 0x30, 0x34, 0x58, 0x5B, 0x25
	.byte  0x64, 0x5D, 0x00

DS0001:
	.byte  0x44, 0x53, 0x25, 0x30, 0x34, 0x58, 0x00

DS0002:
	.byte  0x20, 0x73, 0x65, 0x67, 0x6D, 0x65, 0x6E, 0x74
	.byte  0x00

DS0003:
	.byte  0x2E, 0x63, 0x6F, 0x64, 0x65, 0x00

DS0004:
	.byte  0x61, 0x64, 0x64, 0x72, 0x20, 0x00

DS0005:
	.byte  0x20, 0x25, 0x73, 0x20, 0x64, 0x77, 0x20, 0x25
	.byte  0x73, 0x2C, 0x30, 0x00

DS0006:
	.byte  0x20, 0x25, 0x73, 0x20, 0x73, 0x62, 0x79, 0x74
	.byte  0x65, 0x20, 0x25, 0x73, 0x2C, 0x30, 0x00

DS0007:
	.byte  0x20, 0x25, 0x73, 0x20, 0x64, 0x77, 0x20, 0x30
	.byte  0x00

DS0008:
	.byte  0x20, 0x25, 0x73, 0x20, 0x73, 0x62, 0x79, 0x74
	.byte  0x65, 0x20, 0x30, 0x00

DS0009:
	.byte  0x2E, 0x64, 0x61, 0x74, 0x61, 0x00

DS000A:
	.byte  0x61, 0x6C, 0x69, 0x67, 0x6E, 0x20, 0x32, 0x00

DS000B:
	.byte  0x5F, 0x44, 0x41, 0x54, 0x41, 0x20, 0x65, 0x6E
	.byte  0x64, 0x73, 0x00

DS000C:
	.byte  0x40, 0x43, 0x53, 0x74, 0x72, 0x00

DS000D:
	.byte  0x5F, 0x44, 0x41, 0x54, 0x41, 0x00

DS000E:
	.byte  0x2E, 0x63, 0x6F, 0x6E, 0x73, 0x74, 0x00

DS000F:
	.byte  0x43, 0x4F, 0x4E, 0x53, 0x54, 0x00

DS0010:
	.byte  0x46, 0x25, 0x30, 0x34, 0x58, 0x00

DS0011:
	.byte  0x61, 0x6C, 0x69, 0x67, 0x6E, 0x20, 0x25, 0x64
	.byte  0x00

DS0012:
	.byte  0x25, 0x73, 0x20, 0x64, 0x64, 0x20, 0x30, 0x78
	.byte  0x25, 0x78, 0x00

DS0013:
	.byte  0x25, 0x73, 0x20, 0x64, 0x71, 0x20, 0x30, 0x78
	.byte  0x25, 0x6C, 0x78, 0x00

DS0014:
	.byte  0x25, 0x73, 0x20, 0x6C, 0x61, 0x62, 0x65, 0x6C
	.byte  0x20, 0x72, 0x65, 0x61, 0x6C, 0x25, 0x64, 0x00

DS0015:
	.byte  0x6F, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x30, 0x78
	.byte  0x25, 0x30, 0x31, 0x36, 0x6C, 0x58, 0x25, 0x30
	.byte  0x31, 0x36, 0x6C, 0x58, 0x00

DS0016:
	.byte  0x40, 0x43, 0x6F, 0x6D, 0x41, 0x6C, 0x6C, 0x6F
	.byte  0x63, 0x00

DS0017:
	.byte  0x74, 0x79, 0x70, 0x65, 0x69, 0x64, 0x00

DS0018:
	.byte  0x40, 0x52, 0x65, 0x67, 0x00

DS0019:
	.byte  0x40, 0x43, 0x61, 0x74, 0x53, 0x74, 0x72, 0x00

DS001A:
	.byte  0x40, 0x49, 0x6E, 0x53, 0x74, 0x72, 0x00

DS001B:
	.byte  0x40, 0x53, 0x69, 0x7A, 0x65, 0x53, 0x74, 0x72
	.byte  0x00

DS001C:
	.byte  0x40, 0x53, 0x75, 0x62, 0x53, 0x74, 0x72, 0x00


.att_syntax prefix
