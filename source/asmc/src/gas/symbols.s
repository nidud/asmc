
.intel_syntax noprefix

.global define_name
.global undef_name
.global SymSetCmpFunc
.global SymClearLocal
.global SymGetLocal
.global SymSetLocal
.global SymAlloc
.global SymFind
.global SymLookup
.global SymLookupLocal
.global SymFree
.global SymAddLocal
.global SymAddGlobal
.global SymCreate
.global SymLCreate
.global SymGetCount
.global SymMakeAllSymbolsPublic
.global SymInit
.global SymPassInit
.global SymGetAll
.global SymEnum
.global QEnqueue
.global QAddItem
.global AddPublicData
.global szDate
.global szTime
.global SymCmpFunc
.global strFILE
.global strFUNC

.extern UpdateCurPC
.extern UpdateWordSize
.extern UpdateLineNumber
.extern symCurSeg
.extern LineCur
.extern FileCur
.extern UseSavedState
.extern ReleaseMacroData
.extern DeleteProc
.extern CurrProc
.extern LclAlloc
.extern tstrcmp
.extern tstrlen
.extern tmemicmp
.extern tmemcmp
.extern tsprintf
.extern asmerr
.extern ModuleInfo
.extern time
.extern localtime


.SECTION .text
	.ALIGN	16

$_001:	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	lea	rsi, [dyneqtable+rip]
	xor	edi, edi
$_002:	cmp	edi, dword ptr [dyneqcount+rip]
	jge	$_004
	lodsq
	mov	rdx, rax
	mov	rcx, rbx
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_003
	inc	edi
	mov	eax, edi
	jmp	$_005

$_003:	inc	edi
	jmp	$_002

$_004:	xor	eax, eax
$_005:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

define_name:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x10]
	call	$_001
	test	rax, rax
	jnz	$_006
	mov	ecx, dword ptr [dyneqcount+rip]
	lea	rdx, [dyneqtable+rip]
	mov	rax, qword ptr [rbp+0x10]
	mov	qword ptr [rdx+rcx*8], rax
	lea	rdx, [dyneqvalue+rip]
	mov	rax, qword ptr [rbp+0x18]
	mov	qword ptr [rdx+rcx*8], rax
	inc	dword ptr [dyneqcount+rip]
$_006:	leave
	ret

undef_name:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x10]
	call	$_001
	test	rax, rax
	jz	$_009
	mov	ecx, eax
$_007:	cmp	ecx, dword ptr [dyneqcount+rip]
	jge	$_008
	lea	rdx, [dyneqtable+rip]
	mov	rax, qword ptr [rdx+rcx*8]
	mov	qword ptr [rdx+rcx*8-0x8], rax
	lea	rdx, [dyneqvalue+rip]
	mov	rax, qword ptr [rdx+rcx*8]
	mov	qword ptr [rdx+rcx*8-0x8], rax
	inc	ecx
	jmp	$_007

$_008:	dec	dword ptr [dyneqcount+rip]
$_009:	leave
	ret

SymSetCmpFunc:
	lea	rax, [tmemicmp@PLT+rip]
	cmp	byte ptr [ModuleInfo+0x1D0+rip], 0
	jz	$_010
	lea	rax, [tmemcmp@PLT+rip]
$_010:	mov	qword ptr [SymCmpFunc+rip], rax
	ret

SymClearLocal:
	xor	eax, eax
	lea	rdx, [lsym_table+rip]
	mov	ecx, 257
	xchg	rdi, rdx
	rep stosq
	mov	rdi, rdx
	ret

SymGetLocal:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rdx, qword ptr [rcx+0x68]
	lea	rdx, [rdx+0x18]
	xor	ecx, ecx
	lea	rbx, [lsym_table+rip]
	jmp	$_012

$_011:	mov	rax, qword ptr [rbx+rcx*8]
	inc	ecx
	test	rax, rax
	jz	$_012
	mov	qword ptr [rdx], rax
	lea	rdx, [rax+0x68]
$_012:	cmp	ecx, 256
	jc	$_011
	xor	eax, eax
	mov	dword ptr [rdx], eax
	leave
	pop	rbx
	ret

SymSetLocal:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	xor	eax, eax
	mov	rsi, rcx
	lea	rdx, [lsym_table+rip]
	mov	rdi, rdx
	mov	ecx, 257
	rep stosq
	mov	rdi, rdx
	mov	rsi, qword ptr [rsi+0x68]
	mov	rsi, qword ptr [rsi+0x18]
	jmp	$_016

$_013:	mov	rcx, qword ptr [rsi+0x8]
	mov	eax, 2166136261
	mov	dl, byte ptr [rcx]
	jmp	$_015

$_014:	inc	rcx
	or	dl, 0x20
	imul	eax, eax, 16777619
	xor	al, dl
	mov	dl, byte ptr [rcx]
$_015:	test	dl, dl
	jnz	$_014
	and	eax, 0xFF
	mov	qword ptr [rdi+rax*8], rsi
	mov	rsi, qword ptr [rsi+0x68]
$_016:	test	rsi, rsi
	jnz	$_013
	leave
	pop	rdi
	pop	rsi
	ret

SymAlloc:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	edi, eax
	lea	ecx, [rdi+0x81]
	call	LclAlloc@PLT
	mov	dword ptr [rax+0x10], edi
	mov	byte ptr [rax+0x19], -64
	lea	rdx, [rax+0x80]
	mov	qword ptr [rax+0x8], rdx
	cmp	byte ptr [ModuleInfo+0x1DC+rip], 0
	jz	$_017
	or	byte ptr [rax+0x15], 0x01
$_017:	test	edi, edi
	jz	$_018
	mov	ecx, edi
	mov	rdi, rdx
	rep movsb
$_018:	leave
	pop	rdi
	pop	rsi
	ret

SymFind:
	movzx	eax, byte ptr [rcx]
	test	eax, eax
	je	$_042
	mov	r10, rcx
	or	al, 0x20
	xor	eax, 0x50C5D1F
	inc	rcx
	mov	dl, byte ptr [rcx]
	test	dl, dl
	jz	$_020
$_019:	inc	rcx
	or	dl, 0x20
	imul	eax, eax, 16777619
	xor	al, dl
	mov	dl, byte ptr [rcx]
	test	dl, dl
	jnz	$_019
$_020:	sub	rcx, r10
	mov	r8d, ecx
	cmp	qword ptr [CurrProc+rip], 0
	je	$_032
	mov	r9d, eax
	and	eax, 0xFF
	lea	rdx, [lsym_table+rip]
	lea	rdx, [rdx+rax*8]
	mov	rax, qword ptr [rdx]
	test	rax, rax
	je	$_031
	cmp	byte ptr [ModuleInfo+0x1D0+rip], 0
	jz	$_027
$_021:	cmp	r8d, dword ptr [rax+0x10]
	jnz	$_025
	mov	r11, qword ptr [rax+0x8]
$_022:	test	r8d, 0xFFFFFFFC
	jz	$_023
	sub	r8d, 4
	mov	ecx, dword ptr [r10+r8]
	cmp	ecx, dword ptr [r11+r8]
	jz	$_022
	jmp	$_024

$_023:	test	r8d, r8d
	jz	$_026
	sub	r8d, 1
	mov	cl, byte ptr [r10+r8]
	cmp	cl, byte ptr [r11+r8]
	jz	$_023
$_024:	mov	r8d, dword ptr [rax+0x10]
$_025:	mov	rdx, rax
	mov	rax, qword ptr [rax]
	test	rax, rax
	jnz	$_021
	jmp	$_031

$_026:	mov	qword ptr [lsym+rip], rdx
	jmp	$_042

$_027:	cmp	r8d, dword ptr [rax+0x10]
	jnz	$_030
	mov	r11, qword ptr [rax+0x8]
$_028:	test	r8d, 0xFFFFFFFC
	jz	$_029
	sub	r8d, 4
	mov	ecx, dword ptr [r10+r8]
	cmp	ecx, dword ptr [r11+r8]
	jz	$_028
	add	r8d, 4
$_029:	test	r8d, r8d
	jz	$_026
	sub	r8d, 1
	mov	cl, byte ptr [r10+r8]
	cmp	cl, byte ptr [r11+r8]
	jz	$_029
	mov	ch, cl
	mov	cl, byte ptr [r11+r8]
	or	ecx, 0x2020
	cmp	cl, ch
	jz	$_029
	mov	r8d, dword ptr [rax+0x10]
$_030:	mov	rdx, rax
	mov	rax, qword ptr [rax]
	test	rax, rax
	jnz	$_027
$_031:	mov	qword ptr [lsym+rip], rdx
	mov	eax, r9d
$_032:	and	eax, 0x7FFF
	lea	rdx, [gsym_table+rip]
	lea	rdx, [rdx+rax*8]
	mov	rax, qword ptr [rdx]
	test	rax, rax
	je	$_041
	cmp	byte ptr [ModuleInfo+0x1D0+rip], 0
	jz	$_037
$_033:	cmp	r8d, dword ptr [rax+0x10]
	jnz	$_036
	mov	r11, qword ptr [rax+0x8]
	mov	r9d, r8d
$_034:	test	r9d, 0xFFFFFFFC
	jz	$_035
	sub	r9d, 4
	mov	ecx, dword ptr [r10+r9]
	cmp	ecx, dword ptr [r11+r9]
	jz	$_034
	jmp	$_036

$_035:	test	r9d, r9d
	jz	$_041
	sub	r9d, 1
	mov	cl, byte ptr [r10+r9]
	cmp	cl, byte ptr [r11+r9]
	jz	$_035
$_036:	mov	rdx, rax
	mov	rax, qword ptr [rax]
	test	rax, rax
	jnz	$_033
	jmp	$_041

$_037:	cmp	r8d, dword ptr [rax+0x10]
	jnz	$_040
	mov	r11, qword ptr [rax+0x8]
	mov	r9d, r8d
$_038:	test	r9d, 0xFFFFFFFC
	jz	$_039
	sub	r9d, 4
	mov	ecx, dword ptr [r10+r9]
	cmp	ecx, dword ptr [r11+r9]
	jz	$_038
	add	r9d, 4
$_039:	test	r9d, r9d
	jz	$_041
	sub	r9d, 1
	mov	cl, byte ptr [r10+r9]
	cmp	cl, byte ptr [r11+r9]
	jz	$_039
	mov	ch, cl
	mov	cl, byte ptr [r11+r9]
	or	ecx, 0x2020
	cmp	cl, ch
	jz	$_039
	mov	r8d, dword ptr [rax+0x10]
$_040:	mov	rdx, rax
	mov	rax, qword ptr [rax]
	test	rax, rax
	jnz	$_037
$_041:	mov	qword ptr [gsym+rip], rdx
$_042:	ret

SymLookup:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x10]
	call	SymFind
	test	rax, rax
	jnz	$_043
	mov	rcx, qword ptr [rbp+0x10]
	call	SymAlloc
	mov	rcx, qword ptr [gsym+rip]
	mov	qword ptr [rcx], rax
	inc	dword ptr [SymCount+rip]
$_043:	leave
	ret

SymLookupLocal:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x10]
	call	SymFind
	test	rax, rax
	jnz	$_044
	mov	rcx, qword ptr [rbp+0x10]
	call	SymAlloc
	or	byte ptr [rax+0x14], 0x04
	mov	rcx, qword ptr [lsym+rip]
	mov	qword ptr [rcx], rax
	jmp	$_045

$_044:	cmp	byte ptr [rax+0x18], 0
	jnz	$_045
	test	byte ptr [rax+0x14], 0x04
	jnz	$_045
	mov	rdx, qword ptr [rax]
	mov	rcx, qword ptr [gsym+rip]
	mov	qword ptr [rcx], rdx
	dec	dword ptr [SymCount+rip]
	or	byte ptr [rax+0x14], 0x04
	mov	qword ptr [rax], 0
	mov	rcx, qword ptr [lsym+rip]
	mov	qword ptr [rcx], rax
$_045:	leave
	ret

SymFree:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	movzx	eax, byte ptr [rcx+0x18]
	jmp	$_051

$_046:	test	byte ptr [rcx+0x15], 0x08
	jz	$_047
	call	DeleteProc@PLT
$_047:	jmp	$_052

$_048:	test	byte ptr [rcx+0x15], 0x08
	jz	$_049
	call	DeleteProc@PLT
$_049:	mov	rcx, qword ptr [rbp+0x10]
	mov	dword ptr [rcx+0x38], 0
	jmp	$_052

$_050:	call	ReleaseMacroData@PLT
	jmp	$_052

$_051:	cmp	eax, 1
	jz	$_046
	cmp	eax, 2
	jz	$_048
	cmp	eax, 9
	jz	$_050
$_052:	leave
	ret

SymAddLocal:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rsi, rdx
	mov	rcx, rsi
	call	SymFind
	test	rax, rax
	jz	$_053
	cmp	byte ptr [rax+0x18], 0
	jz	$_053
	mov	rdx, rsi
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_054

$_053:	mov	rcx, rsi
	call	tstrlen@PLT
	mov	dword ptr [rbx+0x10], eax
	lea	edi, [rax+0x1]
	mov	ecx, edi
	call	LclAlloc@PLT
	mov	qword ptr [rbx+0x8], rax
	mov	ecx, edi
	mov	rdi, rax
	rep movsb
	mov	rcx, qword ptr [lsym+rip]
	mov	qword ptr [rcx], rbx
	mov	qword ptr [rbx], 0
	mov	rax, rbx
$_054:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SymAddGlobal:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rcx+0x8]
	call	SymFind
	test	rax, rax
	jz	$_055
	mov	rcx, qword ptr [rbp+0x10]
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_056

$_055:	mov	rax, qword ptr [rbp+0x10]
	inc	dword ptr [SymCount+rip]
	mov	rcx, qword ptr [gsym+rip]
	mov	qword ptr [rcx], rax
	mov	qword ptr [rax], 0
$_056:	leave
	ret

SymCreate:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x10]
	call	SymFind
	test	rax, rax
	jz	$_057
	mov	rdx, qword ptr [rbp+0x10]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_058

$_057:	mov	rcx, qword ptr [rbp+0x10]
	call	SymAlloc
	inc	dword ptr [SymCount+rip]
	mov	rcx, qword ptr [gsym+rip]
	mov	qword ptr [rcx], rax
$_058:	leave
	ret

SymLCreate:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x10]
	call	SymFind
	test	rax, rax
	jz	$_059
	cmp	byte ptr [rax+0x18], 0
	jz	$_059
	mov	rdx, qword ptr [rbp+0x10]
	mov	ecx, 2005
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_060

$_059:	mov	rcx, qword ptr [rbp+0x10]
	call	SymAlloc
	mov	rcx, qword ptr [lsym+rip]
	mov	qword ptr [rcx], rax
$_060:	leave
	ret

SymGetCount:
	mov	eax, dword ptr [SymCount+rip]
	ret

SymMakeAllSymbolsPublic:
	push	rsi
	push	rdi
	sub	rsp, 40
	xor	esi, esi
$_061:	lea	rax, [gsym_table+rip]
	mov	rdi, qword ptr [rax+rsi*8]
	jmp	$_064

$_062:	cmp	byte ptr [rdi+0x18], 1
	jnz	$_063
	mov	rcx, qword ptr [rdi+0x8]
	mov	al, byte ptr [rcx+0x1]
	test	dword ptr [rdi+0x14], 0xB0
	jnz	$_063
	test	byte ptr [rdi+0x15], 0x40
	jnz	$_063
	cmp	al, 38
	jz	$_063
	or	dword ptr [rdi+0x14], 0x80
	mov	rcx, rdi
	call	AddPublicData
$_063:	mov	rdi, qword ptr [rdi]
$_064:	test	rdi, rdi
	jnz	$_062
	add	esi, 1
	cmp	esi, 32768
	jnz	$_061
	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

SymInit:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	xor	eax, eax
	mov	dword ptr [SymCount+rip], eax
	mov	qword ptr [CurrProc+rip], rax
	lea	rdi, [gsym_table+rip]
	mov	ecx, 65536
	rep stosd
	lea	rdi, [rbp-0x8]
	call	time@PLT
	lea	rdi, [rbp-0x8]
	call	localtime@PLT
	mov	rsi, rax
	mov	edx, dword ptr [rsi+0x14]
	sub	edx, 100
	mov	ecx, dword ptr [rsi+0x10]
	add	ecx, 1
	mov	dword ptr [rsp+0x20], edx
	mov	r9d, dword ptr [rsi+0xC]
	mov	r8d, ecx
	lea	rdx, [DS0010+rip]
	lea	rcx, [szDate+rip]
	call	tsprintf@PLT
	mov	eax, dword ptr [rsi]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rsi+0x4]
	mov	r8d, dword ptr [rsi+0x8]
	lea	rdx, [DS0011+rip]
	lea	rcx, [szTime+rip]
	call	tsprintf@PLT
	lea	rsi, [tmtab+rip]
	jmp	$_066

$_065:	mov	rcx, qword ptr [rsi]
	call	SymCreate
	mov	byte ptr [rax+0x18], 10
	or	byte ptr [rax+0x14], 0x22
	mov	rcx, qword ptr [rsi+0x8]
	mov	qword ptr [rax+0x28], rcx
	mov	rcx, qword ptr [rsi+0x10]
	add	rsi, 24
	test	rcx, rcx
	jz	$_066
	mov	qword ptr [rcx], rax
$_066:	cmp	qword ptr [rsi], 0
	jnz	$_065
	lea	rsi, [eqtab+rip]
	jmp	$_068

$_067:	mov	rcx, qword ptr [rsi]
	call	SymCreate
	mov	byte ptr [rax+0x18], 1
	or	byte ptr [rax+0x14], 0x22
	mov	rcx, qword ptr [rsi+0x8]
	mov	dword ptr [rax+0x28], ecx
	mov	rcx, qword ptr [rsi+0x10]
	mov	qword ptr [rax+0x58], rcx
	mov	rcx, qword ptr [rsi+0x18]
	add	rsi, 32
	test	rcx, rcx
	jz	$_068
	mov	qword ptr [rcx], rax
$_068:	cmp	qword ptr [rsi], 0
	jnz	$_067
	and	dword ptr [rax+0x14], 0xFFFFFEFF
	xor	esi, esi
	jmp	$_070

$_069:	lea	rax, [dyneqtable+rip]
	mov	rcx, qword ptr [rax+rsi*8]
	call	SymCreate
	mov	byte ptr [rax+0x18], 10
	or	byte ptr [rax+0x14], 0x22
	lea	rdx, [dyneqvalue+rip]
	mov	rcx, qword ptr [rdx+rsi*8]
	mov	qword ptr [rax+0x28], rcx
	mov	qword ptr [rax+0x58], 0
	inc	esi
$_070:	cmp	esi, dword ptr [dyneqcount+rip]
	jl	$_069
	mov	rax, qword ptr [symPC+rip]
	and	dword ptr [rax+0x14], 0xFFFFFEFF
	or	byte ptr [rax+0x14], 0x40
	mov	rax, qword ptr [LineCur+rip]
	and	dword ptr [rax+0x14], 0xFFFFFEFF
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SymPassInit:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	cmp	dword ptr [rbp+0x10], 0
	jz	$_075
	cmp	dword ptr [UseSavedState+rip], 0
	jnz	$_075
	xor	ecx, ecx
$_071:	lea	rax, [gsym_table+rip]
	mov	rax, qword ptr [rax+rcx*8]
	jmp	$_074

$_072:	test	byte ptr [rax+0x14], 0x20
	jnz	$_073
	and	dword ptr [rax+0x14], 0xFFFFFFFD
$_073:	mov	rax, qword ptr [rax]
$_074:	test	rax, rax
	jnz	$_072
	add	ecx, 1
	cmp	ecx, 32768
	jnz	$_071
$_075:	leave
	ret

SymGetAll:
	mov	rdx, rcx
	xor	ecx, ecx
$_076:	lea	rax, [gsym_table+rip]
	mov	rax, qword ptr [rax+rcx*8]
	jmp	$_078

$_077:	mov	qword ptr [rdx], rax
	add	rdx, 8
	mov	rax, qword ptr [rax]
$_078:	test	rax, rax
	jnz	$_077
	add	ecx, 1
	cmp	ecx, 32768
	jnz	$_076
	ret

SymEnum:
	push	rbx
	push	rbp
	mov	rbp, rsp
	lea	rbx, [gsym_table+rip]
	mov	rax, rcx
	test	rax, rax
	jz	$_079
	mov	rax, qword ptr [rax]
	mov	ecx, dword ptr [rdx]
	jmp	$_080

$_079:	xor	ecx, ecx
	mov	dword ptr [rdx], ecx
	mov	rax, qword ptr [rbx]
$_080:	jmp	$_082

$_081:	add	ecx, 1
	mov	dword ptr [rdx], ecx
	mov	rax, qword ptr [rbx+rcx*8]
$_082:	test	rax, rax
	jnz	$_083
	cmp	ecx, 32767
	jc	$_081
$_083:	leave
	pop	rbx
	ret

QEnqueue:
	xor	eax, eax
	cmp	rax, qword ptr [rcx]
	jnz	$_084
	mov	qword ptr [rcx], rdx
	mov	qword ptr [rcx+0x8], rdx
	mov	qword ptr [rdx], rax
	jmp	$_085

$_084:	mov	rax, qword ptr [rcx+0x8]
	mov	qword ptr [rcx+0x8], rdx
	mov	qword ptr [rax], rdx
	xor	eax, eax
	mov	qword ptr [rdx], rax
$_085:	ret

QAddItem:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	mov	rdi, rdx
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	qword ptr [rax+0x8], rdi
	mov	rdx, rax
	mov	rcx, rsi
	call	QEnqueue
	leave
	pop	rdi
	pop	rsi
	ret

AddPublicData:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, rcx
	lea	rcx, [ModuleInfo+0x10+rip]
	call	QAddItem
	leave
	ret


.SECTION .data
	.ALIGN	16

symPC:
	.quad  0x0000000000000000

tmtab:
	.quad  DS0000
	.quad  DS0001
	.quad  0x0000000000000000
	.quad  DS0002
	.quad  szDate
	.quad  0x0000000000000000
	.quad  DS0003
	.quad  szTime
	.quad  0x0000000000000000
	.quad  DS0004
	.quad  ModuleInfo+0x230
	.quad  0x0000000000000000
	.quad  DS0005
	.quad  0x0000000000000000
	.quad  FileCur
	.quad  DS0006
	.quad  strFILE
	.quad  0x0000000000000000
	.quad  DS0007
	.quad  DS0008
	.quad  0x0000000000000000
	.quad  DS0009
	.quad  strFUNC
	.quad  0x0000000000000000
	.quad  DS000A
	.quad  DS000A+0x7
	.quad  symCurSeg
	.quad  0x0000000000000000

eqtab:
	.quad  DS000B
	.quad  0x00000000000000EC
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  DS000C
	.quad  0x00000000000000EC
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  DS000D
	.quad  0x00000000000000D4
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  DS000E
	.quad  0x0000000000000000
	.quad  UpdateCurPC
	.quad  symPC
	.quad  DS0008
	.quad  0x0000000000000000
	.quad  UpdateLineNumber
	.quad  LineCur
	.quad  DS000F
	.quad  0x0000000000000000
	.quad  UpdateWordSize
	.quad  0x0000000000000000
	.quad  0x0000000000000000

dyneqcount:
	.int   0x00000000

DS0010:
	.byte  0x25, 0x30, 0x32, 0x75, 0x2F, 0x25, 0x30, 0x32
	.byte  0x75, 0x2F, 0x25, 0x30, 0x32, 0x75, 0x00

DS0011:
	.byte  0x25, 0x30, 0x32, 0x75, 0x3A, 0x25, 0x30, 0x32
	.byte  0x75, 0x3A, 0x25, 0x30, 0x32, 0x75, 0x00


.SECTION .bss
	.ALIGN	16

gsym:
	.zero	8

lsym:	.zero	8

szDate:
	.zero	16 * 1

szTime:
	.zero	16 * 1

lsym_table:
	.zero	2056 * 1

gsym_table:
	.zero	262144 * 1

SymCmpFunc:
	.zero	8

dyneqtable:
	.zero	160 * 1

dyneqvalue:
	.zero	160 * 1

SymCount: .zero 4

strFILE:
	.zero	1024 * 1

strFUNC:
	.zero	256 * 1


.SECTION .rodata
	.ALIGN	16

DS0000:
	.byte  0x40, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E
	.byte  0x00

DS0001:
	.byte  0x31, 0x30, 0x30, 0x30, 0x00

DS0002:
	.byte  0x40, 0x44, 0x61, 0x74, 0x65, 0x00

DS0003:
	.byte  0x40, 0x54, 0x69, 0x6D, 0x65, 0x00

DS0004:
	.byte  0x40, 0x46, 0x69, 0x6C, 0x65, 0x4E, 0x61, 0x6D
	.byte  0x65, 0x00

DS0005:
	.byte  0x40, 0x46, 0x69, 0x6C, 0x65, 0x43, 0x75, 0x72
	.byte  0x00

DS0006:
	.byte  0x5F, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x5F, 0x5F
	.byte  0x00

DS0007:
	.byte  0x5F, 0x5F, 0x4C, 0x49, 0x4E, 0x45, 0x5F, 0x5F
	.byte  0x00

DS0008:
	.byte  0x40, 0x4C, 0x69, 0x6E, 0x65, 0x00

DS0009:
	.byte  0x5F, 0x5F, 0x66, 0x75, 0x6E, 0x63, 0x5F, 0x5F
	.byte  0x00

DS000A:
	.byte  0x40, 0x43, 0x75, 0x72, 0x53, 0x65, 0x67, 0x00

DS000B:
	.byte  0x5F, 0x5F, 0x41, 0x53, 0x4D, 0x43, 0x5F, 0x5F
	.byte  0x00

DS000C:
	.byte  0x5F, 0x5F, 0x41, 0x53, 0x4D, 0x43, 0x36, 0x34
	.byte  0x5F, 0x5F, 0x00

DS000D:
	.byte  0x5F, 0x5F, 0x4A, 0x57, 0x41, 0x53, 0x4D, 0x5F
	.byte  0x5F, 0x00

DS000E:
	.byte  0x24, 0x00

DS000F:
	.byte  0x40, 0x57, 0x6F, 0x72, 0x64, 0x53, 0x69, 0x7A
	.byte  0x65, 0x00


.att_syntax prefix
