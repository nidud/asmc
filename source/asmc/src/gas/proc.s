
.intel_syntax noprefix

.global get_fasttype
.global LocalDir
.global UpdateStackBase
.global UpdateProcStatus
.global ParseProc
.global CreateProc
.global DeleteProc
.global ProcDir
.global CopyPrototype
.global EndpDir
.global ExcFrameDirective
.global ProcCheckOpen
.global SetLocalOffsets
.global write_prologue
.global RetInstr
.global ProcInit
.global CurrProc
.global sym_ReservedStack
.global procidx
.global ProcStatus
.global stackreg
.global StackAdj

.extern strFUNC
.extern list_pos
.extern _atoqw
.extern GetLabelStr
.extern GetResWName
.extern FindResWord
.extern AlignCurrOffset
.extern LstWrite
.extern LstSetPosition
.extern SkipSavedState
.extern UseSavedState
.extern LineStoreCurr
.extern MacroInline
.extern RunMacro
.extern GetQualifiedType
.extern EmitConstError
.extern EvalOperand
.extern Tokenize
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern get_curr_srcfile
.extern GetLineNumber
.extern AddPublicData
.extern SimGetSegName
.extern GetSegIdx
.extern GetCurrOffset
.extern GetSymOfssize
.extern SetSymSegOfs
.extern ParseLine
.extern sym_ext2int
.extern sym_remove_table
.extern sym_add_table
.extern GetLangType
.extern SizeFromRegister
.extern SizeFromMemtype
.extern SpecialTable
.extern SymTables
.extern BackPatch
.extern LclDup
.extern LclAlloc
.extern tstricmp
.extern tstrcmp
.extern tstrcpy
.extern tstrlen
.extern tmemset
.extern tmemcpy
.extern tsprintf
.extern tprintf
.extern AddLinnumDataRef
.extern asmerr
.extern szDgroup
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymGetLocal
.extern SymSetLocal
.extern SymClearLocal
.extern SymCmpFunc
.extern SymFind
.extern SymAddLocal
.extern SymLCreate
.extern SymCreate
.extern SymFree
.extern SymAlloc
.extern fwrite


.SECTION .text
	.ALIGN	16

get_fasttype:
	imul	edx, edx, 48
	imul	ecx, ecx, 16
	lea	rax, [lang_table+rip]
	add	rax, rcx
	add	rax, rdx
	ret

$_001:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rdi, r8
	mov	rsi, rdx
	xor	eax, eax
	mov	qword ptr [rsi+0x28], rax
	mov	al, byte ptr [rdi+0x2]
	inc	byte ptr [rdi+0x2]
	mov	byte ptr [rsi+0x49], al
	movzx	edx, byte ptr [rcx+0x1A]
	movzx	ecx, byte ptr [rsi+0x38]
	call	get_fasttype
	mov	rbx, rax
	mov	r8, qword ptr [rsi+0x20]
	movzx	edx, byte ptr [rsi+0x38]
	movzx	ecx, byte ptr [rsi+0x19]
	call	SizeFromMemtype@PLT
	movzx	ecx, byte ptr [rsi+0x38]
	mov	edx, 2
	shl	edx, cl
	mov	dword ptr [rbp-0x24], edx
	test	eax, eax
	jnz	$_002
	cmp	byte ptr [rsi+0x19], -62
	jnz	$_002
	mov	eax, edx
$_002:	mov	ecx, eax
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	cmp	eax, dword ptr [rbp-0x24]
	jge	$_003
	mov	eax, dword ptr [rbp-0x24]
$_003:	mov	rdx, qword ptr [rbp+0x28]
	cmp	al, byte ptr [rdx+0x1F]
	jbe	$_004
	mov	byte ptr [rdx+0x1F], al
$_004:	mov	al, byte ptr [rsi+0x19]
	cmp	al, -60
	jnz	$_005
	mov	rax, qword ptr [rsi+0x20]
	mov	al, byte ptr [rax+0x19]
$_005:	test	al, 0x20
	jnz	$_006
	cmp	al, 31
	jnz	$_014
$_006:	test	byte ptr [rbx+0xF], 0x10
	jz	$_007
	movzx	eax, byte ptr [rsi+0x49]
	jmp	$_008

$_007:	movzx	eax, byte ptr [rdi+0x1]
$_008:	lea	edx, [rax+0x28]
	cmp	eax, 7
	jbe	$_009
	add	edx, 84
$_009:	cmp	ecx, 64
	jnz	$_011
	lea	edx, [rax+0x40]
	cmp	eax, 7
	jbe	$_010
	add	edx, 108
$_010:	jmp	$_012

$_011:	cmp	ecx, 32
	jnz	$_012
	lea	edx, [rax+0x30]
	cmp	eax, 7
	jbe	$_012
	add	edx, 100
$_012:	mov	byte ptr [rsi+0x48], dl
	cmp	al, byte ptr [rbx+0xD]
	jc	$_013
	xor	eax, eax
	jmp	$_030

$_013:	inc	byte ptr [rdi+0x1]
	inc	byte ptr [rsi+0x4A]
	jmp	$_028

$_014:	mov	eax, dword ptr [rbp-0x24]
	add	eax, eax
	cmp	ecx, eax
	jbe	$_015
	lea	edx, [rax+rax]
	cmp	edx, ecx
	jnz	$_015
	cmp	dl, byte ptr [rbx+0xE]
	ja	$_015
	mov	dl, byte ptr [rdi]
	add	dl, 4
	cmp	dl, byte ptr [rbx+0xC]
	ja	$_015
	add	byte ptr [rdi], 2
	mov	byte ptr [rsi+0x4A], 2
	mov	eax, ecx
$_015:	test	byte ptr [rbx+0xF], 0x10
	jz	$_017
	movzx	edx, byte ptr [rsi+0x49]
	cmp	dl, byte ptr [rdi]
	jnc	$_016
	mov	dl, byte ptr [rdi]
$_016:	jmp	$_018

$_017:	movzx	edx, byte ptr [rdi]
$_018:	cmp	dl, byte ptr [rbx+0xC]
	jc	$_019
	xor	eax, eax
	jmp	$_030

$_019:	cmp	eax, ecx
	jnz	$_023
	cmp	al, byte ptr [rbx+0xE]
	ja	$_023
	mov	al, dl
	inc	al
	cmp	al, byte ptr [rbx+0xC]
	jc	$_020
	xor	eax, eax
	jmp	$_030

$_020:	mov	eax, 1
$_021:	cmp	eax, dword ptr [rbp-0x24]
	jge	$_022
	add	edx, 8
	add	eax, eax
	jmp	$_021

$_022:	add	rdx, qword ptr [rbx]
	mov	al, byte ptr [rdx]
	mov	byte ptr [rsi+0x48], al
	or	byte ptr [rsi+0x17], 0x02
	add	byte ptr [rdi], 2
	add	byte ptr [rsi+0x4A], 2
	jmp	$_028

$_023:	cmp	ecx, dword ptr [rbp-0x24]
	jle	$_025
	test	byte ptr [rbx+0xF], 0x10
	jnz	$_024
	xor	eax, eax
	jmp	$_030

$_024:	mov	ecx, dword ptr [rbp-0x24]
$_025:	mov	eax, 1
$_026:	cmp	eax, ecx
	jnc	$_027
	add	edx, 8
	add	eax, eax
	jmp	$_026

$_027:	add	rdx, qword ptr [rbx]
	mov	al, byte ptr [rdx]
	mov	byte ptr [rsi+0x48], al
	inc	byte ptr [rdi]
	inc	byte ptr [rsi+0x4A]
$_028:	xor	eax, eax
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_029
	jmp	$_030

$_029:	mov	ecx, dword ptr [rdi]
	mov	rdx, qword ptr [rbp+0x28]
	mov	byte ptr [rdx+0x1D], cl
	mov	byte ptr [rdx+0x1E], ch
	or	byte ptr [rsi+0x17], 0x01
	test	byte ptr [rbx+0xF], 0x01
	jz	$_030
	mov	byte ptr [rsi+0x18], 10
	lea	rdx, [rbp-0x20]
	mov	al, byte ptr [rsi+0x48]
	mov	ecx, eax
	call	GetResWName@PLT
	mov	rcx, rax
	call	LclDup@PLT
	mov	qword ptr [rsi+0x28], rax
	mov	eax, 1
$_030:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

LocalDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_031
	xor	eax, eax
	jmp	$_059

$_031:	test	dword ptr [ProcStatus+rip], 0x80
	jz	$_032
	cmp	qword ptr [CurrProc+rip], 0
	jnz	$_033
$_032:	mov	ecx, 2012
	call	asmerr@PLT
	jmp	$_059

$_033:	mov	rsi, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rsi+0x68]
	movzx	eax, word ptr [rsi+0x42]
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	cmp	byte ptr [r11+rax+0xA], 4
	jnz	$_034
	or	byte ptr [rsi+0x40], 0xFFFFFF80
	or	byte ptr [ProcStatus+rip], 0x04
$_034:	inc	dword ptr [rbp+0x28]
	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
$_035:	cmp	byte ptr [rbx], 8
	jz	$_036
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_059

$_036:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	mov	qword ptr [rbp-0x20], 0
	mov	byte ptr [rbp-0x17], 0
	mov	byte ptr [rbp-0x14], -64
	mov	eax, 1
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	shl	eax, cl
	mov	byte ptr [rbp-0x16], 0
	test	eax, 0x68
	jz	$_037
	mov	byte ptr [rbp-0x16], 1
$_037:	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x15], al
	mov	rcx, qword ptr [rbp-0x8]
	call	SymLCreate@PLT
	mov	qword ptr [rbp-0x10], rax
	test	eax, eax
	jnz	$_038
	mov	rax, -1
	jmp	$_059

$_038:	mov	byte ptr [rax+0x18], 5
	or	byte ptr [rax+0x14], 0x02
	mov	dword ptr [rax+0x58], 1
	jmp	$_041

$_039:	mov	byte ptr [rax+0x19], 1
	mov	dword ptr [rbp-0x28], 2
	jmp	$_042

$_040:	mov	byte ptr [rax+0x19], 3
	mov	dword ptr [rbp-0x28], 4
	jmp	$_042

$_041:	cmp	byte ptr [rbp-0x15], 0
	jz	$_039
	jmp	$_040

$_042:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 91
	jne	$_049
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	ecx, dword ptr [rbp+0x28]
	mov	rdx, rbx
$_043:	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_044
	cmp	byte ptr [rdx], 44
	jz	$_044
	cmp	byte ptr [rdx], 58
	jz	$_044
	inc	ecx
	add	rdx, 24
	jmp	$_043

$_044:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x90]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_059
	cmp	dword ptr [rbp-0x54], 0
	jz	$_045
	mov	ecx, 2026
	call	asmerr@PLT
	mov	dword ptr [rbp-0x90], 1
$_045:	cmp	dword ptr [rbp-0x8C], 0
	jz	$_047
	cmp	dword ptr [rbp-0x8C], -1
	jnz	$_046
	cmp	dword ptr [rbp-0x90], 0
	jl	$_047
$_046:	lea	rcx, [rbp-0x90]
	call	EmitConstError@PLT
$_047:	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	mov	rcx, qword ptr [rbp-0x10]
	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [rcx+0x58], eax
	or	byte ptr [rcx+0x15], 0x02
	cmp	byte ptr [rbx], 93
	jnz	$_048
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_049

$_048:	mov	ecx, 2045
	call	asmerr@PLT
$_049:	cmp	byte ptr [rbx], 58
	jnz	$_051
	inc	dword ptr [rbp+0x28]
	lea	r8, [rbp-0x28]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	je	$_059
	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	mov	rcx, qword ptr [rbp-0x10]
	mov	al, byte ptr [rbp-0x18]
	mov	byte ptr [rcx+0x19], al
	cmp	byte ptr [rbp-0x18], -60
	jnz	$_050
	mov	rax, qword ptr [rbp-0x20]
	mov	qword ptr [rcx+0x20], rax
	jmp	$_051

$_050:	mov	rax, qword ptr [rbp-0x20]
	mov	qword ptr [rcx+0x40], rax
$_051:	mov	rcx, qword ptr [rbp-0x10]
	mov	al, byte ptr [rbp-0x17]
	mov	byte ptr [rcx+0x39], al
	mov	al, byte ptr [rbp-0x16]
	mov	byte ptr [rcx+0x1C], al
	mov	al, byte ptr [rbp-0x15]
	mov	byte ptr [rcx+0x38], al
	mov	al, byte ptr [rbp-0x14]
	mov	byte ptr [rcx+0x3A], al
	mov	eax, dword ptr [rbp-0x28]
	mul	dword ptr [rcx+0x58]
	mov	dword ptr [rcx+0x50], eax
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_052
	mov	qword ptr [rsi+0x10], rcx
	jmp	$_055

$_052:	mov	rdx, qword ptr [rsi+0x10]
$_053:	cmp	qword ptr [rdx+0x78], 0
	jz	$_054
	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_053

$_054:	mov	qword ptr [rdx+0x78], rcx
$_055:	cmp	byte ptr [rbx], 0
	jz	$_058
	cmp	byte ptr [rbx], 44
	jnz	$_057
	mov	eax, dword ptr [rbp+0x28]
	inc	eax
	cmp	eax, dword ptr [ModuleInfo+0x220+rip]
	jge	$_056
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_056:	jmp	$_058

$_057:	lea	rdx, [DS0000+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_059

$_058:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jl	$_035
	xor	eax, eax
$_059:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

UpdateStackBase:
	test	rdx, rdx
	jz	$_060
	mov	eax, dword ptr [rdx]
	mov	dword ptr [StackAdj+rip], eax
	mov	eax, dword ptr [rdx+0x4]
	mov	dword ptr [StackAdjHigh+rip], eax
$_060:	mov	eax, dword ptr [StackAdj+rip]
	mov	dword ptr [rcx+0x28], eax
	mov	eax, dword ptr [StackAdjHigh+rip]
	mov	dword ptr [rcx+0x50], eax
	ret

UpdateProcStatus:
	xor	eax, eax
	cmp	qword ptr [CurrProc+rip], 0
	jz	$_061
	mov	eax, dword ptr [ProcStatus+rip]
$_061:	mov	dword ptr [rcx+0x28], eax
	ret

$_062:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_071
	or	byte ptr [rcx+0x16], 0x10
	xor	esi, esi
	xor	eax, eax
	mov	rbx, qword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp+0x30]
	add	rcx, 48
	cmp	byte ptr [rcx], 7
	jnz	$_063
	cmp	dword ptr [rcx+0x4], 277
	jc	$_063
	cmp	dword ptr [rcx+0x4], 286
	ja	$_063
	add	rcx, 24
$_063:	mov	rdx, rcx
$_064:	cmp	rdx, rbx
	jnc	$_067
	cmp	byte ptr [rdx], 58
	jnz	$_065
	inc	esi
	jmp	$_066

$_065:	cmp	rdx, rcx
	jbe	$_066
	cmp	byte ptr [rdx], 44
	jnz	$_066
	inc	eax
$_066:	add	rdx, 24
	jmp	$_064

$_067:	cmp	eax, esi
	jbe	$_068
	inc	eax
	mov	esi, eax
$_068:	mov	byte ptr [rbx], 0
	mov	rax, qword ptr [rbx+0x10]
	mov	byte ptr [rax], 0
	cmp	byte ptr [rdx-0x18], 7
	jnz	$_069
	cmp	dword ptr [rdx-0x14], 275
	jnz	$_069
	mov	edx, 1
	jmp	$_070

$_069:	xor	edx, edx
$_070:	mov	rax, qword ptr [rbp+0x30]
	mov	dword ptr [rsp+0x20], edx
	mov	r9, qword ptr [rbx+0x8]
	mov	r8, qword ptr [rcx+0x10]
	mov	edx, esi
	mov	rcx, qword ptr [rax+0x8]
	call	MacroInline@PLT
$_071:	leave
	pop	rbx
	pop	rsi
	ret

$_072:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 152
	mov	dword ptr [rbp-0x1C], 0
	mov	rsi, qword ptr [rcx+0x68]
	movzx	edi, byte ptr [rcx+0x1A]
	mov	rdi, qword ptr [rsi+0x8]
	test	byte ptr [rbp+0x48], 0x04
	jnz	$_074
$_073:	test	rdi, rdi
	jz	$_074
	cmp	qword ptr [rdi+0x78], 0
	jz	$_074
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_073

$_074:
	mov	qword ptr [rbp-0x50], rdi
	mov	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rcx+0x14]
	and	eax, 0x800
	mov	dword ptr [rbp-0x40], eax
	mov	edx, dword ptr [rbp+0x30]
	mov	rax, qword ptr [rbp+0x38]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	mov	dword ptr [rbp-0x14], 0
$_075:	cmp	byte ptr [rbx], 0
	je	$_137
	cmp	byte ptr [rbx], 8
	jnz	$_076
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	jmp	$_080

$_076:	cmp	dword ptr [rbp+0x40], 0
	jnz	$_079
	cmp	byte ptr [rbx], 58
	jnz	$_079
	test	rdi, rdi
	jz	$_077
	mov	rax, qword ptr [rdi+0x8]
	mov	qword ptr [rbp-0x8], rax
	jmp	$_078

$_077:	lea	rax, [DS0000+0x1+rip]
	mov	qword ptr [rbp-0x8], rax
$_078:	jmp	$_080

$_079:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_146

$_080:	mov	qword ptr [rbp-0x30], 0
	mov	byte ptr [rbp-0x27], 0
	mov	byte ptr [rbp-0x24], -64
	mov	eax, 1
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	shl	eax, cl
	test	eax, 0x68
	jz	$_081
	mov	byte ptr [rbp-0x26], 1
	jmp	$_082

$_081:	mov	byte ptr [rbp-0x26], 0
$_082:	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x25], al
	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	mov	dword ptr [rbp-0x38], eax
	mov	dword ptr [rbp-0x3C], 0
	cmp	byte ptr [rbx], 58
	jz	$_085
	cmp	dword ptr [rbp+0x40], 0
	jnz	$_083
	lea	rdx, [DS0001+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_146

$_083:	mov	byte ptr [rbp-0x28], 1
	cmp	byte ptr [rbp-0x25], 0
	jz	$_084
	mov	byte ptr [rbp-0x28], 3
$_084:	jmp	$_095

$_085:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	cmp	byte ptr [rbx], 7
	jnz	$_092
	cmp	dword ptr [rbx+0x4], 275
	jnz	$_092
	mov	rcx, qword ptr [rbp+0x28]
	movzx	eax, byte ptr [rcx+0x1A]
	jmp	$_087

$_086:	mov	ecx, 2131
	call	asmerr@PLT
	jmp	$_146

	jmp	$_088

$_087:	cmp	eax, 0
	jz	$_086
	cmp	eax, 6
	jz	$_086
	cmp	eax, 5
	jz	$_086
	cmp	eax, 4
	jz	$_086
	cmp	eax, 3
	jz	$_086
$_088:	cmp	byte ptr [rbx+0x18], 0
	jz	$_089
	cmp	byte ptr [rbx+0x18], 9
	jnz	$_090
	cmp	byte ptr [rbx+0x19], 123
	jnz	$_090
$_089:	mov	dword ptr [rbp-0x3C], 1
	jmp	$_091

$_090:	mov	ecx, 2129
	call	asmerr@PLT
$_091:	mov	byte ptr [rbp-0x28], -64
	mov	dword ptr [rbp-0x38], 0
	inc	dword ptr [rbp+0x30]
	jmp	$_095

$_092:	xor	eax, eax
	cmp	byte ptr [rbx], 8
	jnz	$_093
	mov	rcx, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rcx]
	or	eax, 0x202020
$_093:	cmp	eax, 7561825
	jnz	$_094
	mov	byte ptr [rbp-0x28], -62
	inc	dword ptr [rbp+0x30]
	jmp	$_095

$_094:	lea	r8, [rbp-0x38]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp+0x30]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	jnz	$_095
	jmp	$_146

$_095:	cmp	dword ptr [rbp+0x40], 0
	jz	$_096
	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_096
	cmp	byte ptr [rax+0x18], 0
	jz	$_096
	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_146

$_096:	cmp	qword ptr [rbp-0x50], 0
	je	$_114
	mov	byte ptr [rbp-0x6B], 0
	mov	rcx, qword ptr [rbp-0x30]
$_097:	test	rcx, rcx
	jz	$_098
	cmp	qword ptr [rcx+0x20], 0
	jz	$_098
	mov	rcx, qword ptr [rcx+0x20]
	jmp	$_097

$_098:	mov	qword ptr [rbp-0x68], rcx
	mov	rdi, qword ptr [rbp-0x50]
	mov	al, byte ptr [rbp+0x48]
	and	eax, 0x27
	cmp	eax, 3
	jz	$_099
	cmp	eax, 32
	jnz	$_100
	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jnz	$_100
$_099:	mov	qword ptr [rdi+0x40], 0
	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jnz	$_100
	mov	byte ptr [rbp-0x6B], 1
$_100:	cmp	byte ptr [rdi+0x19], -60
	jnz	$_101
	mov	rdx, qword ptr [rdi+0x20]
	jmp	$_102

$_101:	xor	edx, edx
	cmp	byte ptr [rdi+0x19], -61
	jnz	$_102
	mov	rdx, qword ptr [rdi+0x40]
$_102:	test	rdx, rdx
	jz	$_103
	cmp	qword ptr [rdx+0x20], 0
	jz	$_103
	mov	rdx, qword ptr [rdx+0x20]
	jmp	$_102

$_103:	mov	qword ptr [rbp-0x60], rdx
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	ah, al
	cmp	byte ptr [rdi+0x38], -2
	jz	$_104
	mov	al, byte ptr [rdi+0x38]
$_104:	mov	byte ptr [rbp-0x69], al
	cmp	byte ptr [rbp-0x25], -2
	jz	$_105
	mov	ah, byte ptr [rbp-0x25]
$_105:	mov	byte ptr [rbp-0x6A], ah
	mov	al, byte ptr [rdi+0x19]
	cmp	byte ptr [rbp-0x28], al
	jnz	$_107
	cmp	byte ptr [rbp-0x28], -60
	jnz	$_106
	mov	rax, qword ptr [rbp-0x60]
	cmp	qword ptr [rbp-0x68], rax
	jnz	$_107
$_106:	cmp	byte ptr [rbp-0x28], -61
	jnz	$_108
	mov	al, byte ptr [rdi+0x1C]
	cmp	byte ptr [rbp-0x26], al
	jnz	$_107
	mov	al, byte ptr [rbp-0x69]
	cmp	byte ptr [rbp-0x6A], al
	jnz	$_107
	cmp	byte ptr [rbp-0x6B], 0
	jnz	$_108
	mov	al, byte ptr [rdi+0x3A]
	cmp	byte ptr [rbp-0x24], al
	jnz	$_107
	mov	rax, qword ptr [rbp-0x60]
	cmp	qword ptr [rbp-0x68], rax
	jz	$_108
$_107:	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2111
	call	asmerr@PLT
$_108:	cmp	dword ptr [rbp+0x40], 0
	jz	$_109
	mov	rdx, qword ptr [rbp-0x8]
	mov	rcx, rdi
	call	SymAddLocal@PLT
$_109:	test	byte ptr [rbp+0x48], 0x04
	jnz	$_112
	mov	rcx, qword ptr [rsi+0x8]
$_110:	test	rcx, rcx
	jz	$_111
	cmp	qword ptr [rcx+0x78], rdi
	jz	$_111
	mov	rcx, qword ptr [rcx+0x78]
	jmp	$_110

$_111:	jmp	$_113

$_112:	mov	rcx, qword ptr [rdi+0x78]
$_113:	mov	qword ptr [rbp-0x50], rcx
	jmp	$_130

$_114:	cmp	dword ptr [rbp-0x40], 0
	jz	$_115
	lea	rdx, [DS0001+0x1+rip]
	mov	ecx, 2111
	call	asmerr@PLT
	jmp	$_146

	jmp	$_130

$_115:	cmp	dword ptr [rbp+0x40], 0
	jz	$_116
	mov	rcx, qword ptr [rbp-0x8]
	call	SymLCreate@PLT
	mov	rdi, rax
	jmp	$_117

$_116:	lea	rcx, [DS0001+0x1+rip]
	call	SymAlloc@PLT
	mov	rdi, rax
$_117:	test	rdi, rdi
	jnz	$_118
	mov	rax, -1
	jmp	$_146

$_118:	mov	qword ptr [rbp-0x48], rdi
	or	byte ptr [rdi+0x14], 0x02
	mov	al, byte ptr [rbp-0x28]
	mov	byte ptr [rdi+0x19], al
	cmp	byte ptr [rbp-0x28], -60
	jnz	$_119
	mov	rax, qword ptr [rbp-0x30]
	mov	qword ptr [rdi+0x20], rax
	jmp	$_120

$_119:	mov	rax, qword ptr [rbp-0x30]
	mov	qword ptr [rdi+0x40], rax
$_120:	mov	al, byte ptr [rbp-0x26]
	mov	byte ptr [rdi+0x1C], al
	mov	al, byte ptr [rbp-0x25]
	mov	byte ptr [rdi+0x38], al
	mov	al, byte ptr [rbp-0x27]
	mov	byte ptr [rdi+0x39], al
	mov	al, byte ptr [rbp-0x24]
	mov	byte ptr [rdi+0x3A], al
	cmp	dword ptr [rbp-0x3C], 0
	jz	$_121
	or	byte ptr [rdi+0x3B], 0x04
$_121:	movzx	eax, byte ptr [rbp+0x48]
	and	eax, 0x31
	test	eax, eax
	jz	$_122
	lea	r8, [rbp-0x1C]
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp+0x28]
	call	$_001
$_122:	test	eax, eax
	jnz	$_123
	mov	byte ptr [rdi+0x18], 5
$_123:	mov	dword ptr [rdi+0x58], 1
	mov	eax, dword ptr [rbp-0x38]
	mov	dword ptr [rdi+0x50], eax
	test	byte ptr [rdi+0x3B], 0x04
	jnz	$_125
	mov	eax, 2
	mov	rcx, qword ptr [rbp+0x28]
	mov	cl, byte ptr [rcx+0x1B]
	shl	eax, cl
	cmp	dword ptr [rbp+0x40], 0
	jz	$_124
	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
$_124:	mov	edx, eax
	mov	eax, dword ptr [rbp-0x38]
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	mov	ecx, eax
	add	dword ptr [rsi+0x20], ecx
$_125:	test	byte ptr [rbp+0x48], 0x04
	jnz	$_126
	mov	rax, qword ptr [rsi+0x8]
	mov	qword ptr [rdi+0x78], rax
	mov	qword ptr [rsi+0x8], rdi
	jmp	$_130

$_126:	mov	qword ptr [rdi+0x78], 0
	cmp	qword ptr [rsi+0x8], 0
	jnz	$_127
	mov	qword ptr [rsi+0x8], rdi
	jmp	$_130

$_127:	mov	rdx, qword ptr [rsi+0x8]
$_128:	test	rdx, rdx
	jz	$_129
	cmp	qword ptr [rdx+0x78], 0
	jz	$_129
	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_128

$_129:	mov	qword ptr [rdx+0x78], rdi
	mov	qword ptr [rbp-0x50], 0
$_130:	mov	edx, dword ptr [rbp+0x30]
	mov	rax, qword ptr [rbp+0x38]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	byte ptr [rbx], 0
	je	$_136
	cmp	byte ptr [rbx], 44
	je	$_135
	cmp	byte ptr [rbx], 3
	jnz	$_133
	cmp	dword ptr [rbx+0x4], 523
	jnz	$_133
	cmp	byte ptr [rbx+0x18], 9
	jnz	$_133
	cmp	byte ptr [rbx+0x19], 60
	jnz	$_133
	mov	rcx, qword ptr [rbx-0x10]
	mov	eax, dword ptr [rcx]
	or	eax, 0x202020
	cmp	byte ptr [rbx-0x18], 8
	jnz	$_131
	cmp	eax, 7561825
	jz	$_132
$_131:	mov	rdx, qword ptr [rbx-0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_146

$_132:	add	dword ptr [rbp+0x30], 2
	add	rbx, 48
$_133:	mov	rcx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 9
	jnz	$_134
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_134
	cmp	dword ptr [rcx+0x1C], 507
	jnz	$_134
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, rbx
	mov	rcx, qword ptr [rbp+0x28]
	call	$_062
	jmp	$_135

$_134:	cmp	byte ptr [rbx], 44
	jz	$_135
	lea	rdx, [DS0000+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_146

$_135:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
$_136:	inc	dword ptr [rbp-0x14]
	jmp	$_075

$_137:	cmp	dword ptr [rbp-0x40], 0
	jz	$_138
	cmp	qword ptr [rbp-0x50], 0
	jz	$_138
	lea	rdx, [DS0001+0x1+rip]
	mov	ecx, 2111
	call	asmerr@PLT
	jmp	$_146

$_138:	cmp	dword ptr [rbp+0x40], 0
	jz	$_145
	mov	eax, 2
	mov	rcx, qword ptr [rbp+0x28]
	cmp	byte ptr [rcx+0x19], -126
	jnz	$_139
	inc	eax
$_139:	movzx	ecx, byte ptr [ModuleInfo+0x1CE+rip]
	mul	ecx
	mov	dword ptr [rbp-0x18], eax
$_140:	cmp	dword ptr [rbp-0x14], 0
	jz	$_145
	mov	ebx, 1
	mov	rdi, qword ptr [rsi+0x8]
$_141:	cmp	ebx, dword ptr [rbp-0x14]
	jge	$_142
	mov	rdi, qword ptr [rdi+0x78]
	inc	ebx
	jmp	$_141

$_142:	cmp	byte ptr [rdi+0x18], 10
	jz	$_144
	mov	eax, dword ptr [rbp-0x18]
	mov	dword ptr [rdi+0x28], eax
	or	byte ptr [rsi+0x40], 0x20
	movzx	ecx, byte ptr [ModuleInfo+0x1CE+rip]
	mov	edx, ecx
	mov	eax, dword ptr [rdi+0x50]
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	mov	ebx, eax
	movzx	ecx, byte ptr [ModuleInfo+0x1CE+rip]
	cmp	ebx, ecx
	jbe	$_143
	cmp	byte ptr [rdi+0x19], -60
	jnz	$_143
	mov	ebx, ecx
$_143:	add	dword ptr [rbp-0x18], ebx
$_144:	dec	dword ptr [rbp-0x14]
	jmp	$_140

$_145:	xor	eax, eax
$_146:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ParseProc:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 120
	mov	rdi, rcx
	mov	rsi, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rdi+0x14]
	and	eax, 0x80
	mov	dword ptr [rbp-0x18], eax
	cmp	dword ptr [rbp+0x40], 0
	je	$_155
	and	byte ptr [rsi+0x40], 0xFFFFFFFB
	cmp	byte ptr [ModuleInfo+0x1D3+rip], 0
	jz	$_147
	or	byte ptr [rsi+0x40], 0x04
$_147:	cmp	byte ptr [ModuleInfo+0x1D2+rip], 0
	jnz	$_148
	or	dword ptr [rdi+0x14], 0x80
$_148:	mov	ebx, dword ptr [ModuleInfo+0x1C0+rip]
	and	ebx, 0xF0
	xor	edi, edi
	movzx	ecx, word ptr [rsi+0x42]
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	cmp	byte ptr [r11+rax+0xA], 5
	jz	$_149
	jmp	$_154

$_149:	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jz	$_152
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	ja	$_150
	cmp	ebx, 32
	jz	$_150
	cmp	ebx, 80
	jc	$_151
$_150:	inc	edi
$_151:	jmp	$_154

$_152:	cmp	ebx, 32
	jz	$_153
	cmp	ebx, 112
	jz	$_153
	cmp	ebx, 48
	jnz	$_154
$_153:	inc	edi
$_154:	test	edi, edi
	jz	$_155
	or	byte ptr [rsi+0x40], 0x02
$_155:	mov	rdi, qword ptr [rbp+0x28]
	mov	edx, dword ptr [rbp+0x30]
	mov	rax, qword ptr [rbp+0x38]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	byte ptr [rbx], 6
	jnz	$_160
	cmp	dword ptr [rbx+0x4], 226
	jc	$_160
	cmp	dword ptr [rbx+0x4], 231
	ja	$_160
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	mov	eax, dword ptr [r11+rax+0x4]
	mov	byte ptr [rbp-0x19], al
	cmp	dword ptr [rbp+0x40], 0
	jz	$_158
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 1
	jc	$_156
	test	al, al
	jz	$_157
$_156:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jnz	$_158
	cmp	al, 1
	jnz	$_158
$_157:	mov	ecx, 2011
	call	asmerr@PLT
$_158:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0x11], al
	mov	al, byte ptr [rbp-0x19]
	cmp	al, -2
	jnz	$_159
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
$_159:	mov	byte ptr [rbp-0x12], al
	inc	dword ptr [rbp+0x30]
	jmp	$_162

$_160:	mov	eax, 1
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	shl	eax, cl
	and	eax, 0x70
	mov	eax, 130
	jnz	$_161
	mov	eax, 129
$_161:	mov	byte ptr [rbp-0x11], al
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x12], al
$_162:	cmp	byte ptr [rdi+0x18], 7
	jnz	$_163
	mov	al, byte ptr [rdi+0x1B]
	mov	byte ptr [rbp-0x13], al
	jmp	$_164

$_163:	mov	rcx, rdi
	call	GetSymOfssize@PLT
	mov	byte ptr [rbp-0x13], al
$_164:	mov	cl, byte ptr [rbp-0x11]
	mov	dl, byte ptr [rbp-0x12]
	cmp	byte ptr [rdi+0x19], -64
	jz	$_169
	cmp	cl, byte ptr [rdi+0x19]
	jnz	$_165
	cmp	al, dl
	jz	$_169
$_165:	cmp	byte ptr [rdi+0x19], -127
	jz	$_166
	cmp	byte ptr [rdi+0x19], -126
	jnz	$_167
$_166:	mov	ecx, 2112
	call	asmerr@PLT
	jmp	$_168

$_167:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_233

$_168:	jmp	$_170

$_169:	mov	byte ptr [rdi+0x19], cl
	mov	byte ptr [rdi+0x1B], dl
$_170:	lea	r8, [rbp+0x48]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp+0x30]
	call	GetLangType@PLT
	cmp	byte ptr [rdi+0x1A], 0
	jz	$_171
	mov	al, byte ptr [rbp+0x48]
	cmp	byte ptr [rdi+0x1A], al
	jz	$_171
	mov	ecx, 2112
	call	asmerr@PLT
	jmp	$_172

$_171:	mov	al, byte ptr [rbp+0x48]
	mov	byte ptr [rdi+0x1A], al
$_172:	movzx	edx, byte ptr [rbp+0x48]
	movzx	ecx, byte ptr [rbp-0x12]
	call	get_fasttype
	mov	al, byte ptr [rax+0xF]
	mov	byte ptr [rbp-0x1A], al
	mov	edx, dword ptr [rbp+0x30]
	mov	rax, qword ptr [rbp+0x38]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	byte ptr [rbx], 8
	jz	$_173
	cmp	byte ptr [rbx], 3
	jne	$_180
$_173:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x8], rax
	lea	rdx, [DS0002+rip]
	mov	rcx, rax
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_176
	cmp	dword ptr [rbp+0x40], 0
	jz	$_175
	and	dword ptr [rdi+0x14], 0xFFFFFF7F
	or	byte ptr [rdi+0x14], 0x04
	cmp	dword ptr [rbp-0x18], 0
	jz	$_174
	call	SkipSavedState@PLT
$_174:	and	byte ptr [rsi+0x40], 0xFFFFFFFB
$_175:	inc	dword ptr [rbp+0x30]
	jmp	$_180

$_176:	lea	rdx, [DS0003+rip]
	mov	rcx, qword ptr [rbp-0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_178
	cmp	dword ptr [rbp+0x40], 0
	jz	$_177
	or	dword ptr [rdi+0x14], 0x80
	and	byte ptr [rsi+0x40], 0xFFFFFFFB
$_177:	inc	dword ptr [rbp+0x30]
	jmp	$_180

$_178:	lea	rdx, [DS0004+rip]
	mov	rcx, qword ptr [rbp-0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_180
	cmp	dword ptr [rbp+0x40], 0
	jz	$_179
	or	dword ptr [rdi+0x14], 0x80
	or	byte ptr [rsi+0x40], 0x04
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jnz	$_179
	cmp	byte ptr [rdi+0x19], -127
	jnz	$_179
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 2145
	call	asmerr@PLT
$_179:	inc	dword ptr [rbp+0x30]
$_180:	cmp	dword ptr [rbp+0x40], 0
	je	$_195
	cmp	byte ptr [rbx], 9
	jne	$_195
	cmp	byte ptr [rbx+0x1], 60
	jne	$_195
	mov	edi, dword ptr [ModuleInfo+0x220+rip]
	inc	edi
	cmp	byte ptr [ModuleInfo+0x1EF+rip], 2
	jnz	$_181
	jmp	$_194

$_181:	cmp	byte ptr [ModuleInfo+0x1EF+rip], 1
	jnz	$_182
	mov	rcx, qword ptr [rbx+0x8]
	call	LclDup@PLT
	mov	qword ptr [rsi+0x28], rax
	jmp	$_194

$_182:	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, edi
	mov	rcx, qword ptr [rbx+0x8]
	call	Tokenize@PLT
	mov	dword ptr [rbp-0x20], eax
$_183:	cmp	edi, dword ptr [rbp-0x20]
	jge	$_194
	mov	edx, edi
	mov	rax, qword ptr [rbp+0x38]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	byte ptr [rbx], 8
	jne	$_192
	lea	rdx, [DS0005+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_184
	or	byte ptr [rsi+0x40], 0x08
	jmp	$_190

$_184:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jz	$_189
	lea	rdx, [DS0006+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_187
	cmp	byte ptr [ModuleInfo+0x1B5+rip], 7
	jnz	$_185
	mov	ecx, 8014
	call	asmerr@PLT
	jmp	$_186

$_185:	or	byte ptr [rsi+0x40], 0x10
$_186:	jmp	$_188

$_187:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 4005
	call	asmerr@PLT
	jmp	$_233

$_188:	jmp	$_190

$_189:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 4005
	call	asmerr@PLT
	jmp	$_233

$_190:	cmp	byte ptr [rbx+0x18], 44
	jnz	$_191
	cmp	byte ptr [rbx+0x30], 0
	jz	$_191
	inc	edi
$_191:	jmp	$_193

$_192:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_233

$_193:	inc	edi
	jmp	$_183

$_194:	inc	dword ptr [rbp+0x30]
$_195:	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	rdi, qword ptr [rbp+0x28]
	mov	cl, byte ptr [rdi+0x1A]
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jne	$_204
	cmp	dword ptr [rbp+0x40], 0
	je	$_204
	mov	qword ptr [rsi+0x30], 0
	cmp	byte ptr [rbx], 7
	jne	$_202
	cmp	dword ptr [rbx+0x4], 276
	jne	$_202
	cmp	dword ptr [Options+0xA4+rip], 3
	jz	$_196
	cmp	dword ptr [Options+0xA4+rip], 1
	jz	$_196
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 1
	jnz	$_197
$_196:	xor	edx, edx
	mov	ecx, 276
	call	GetResWName@PLT
	mov	rdx, rax
	mov	ecx, 3006
	call	asmerr@PLT
	jmp	$_233

$_197:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	cmp	byte ptr [rbx], 58
	jne	$_201
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	cmp	byte ptr [rbx], 8
	jz	$_198
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_233

$_198:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rdi, rax
	test	rax, rax
	jnz	$_199
	mov	rcx, qword ptr [rbx+0x8]
	call	SymCreate@PLT
	mov	rdi, rax
	mov	byte ptr [rax+0x18], 0
	or	byte ptr [rax+0x14], 0x01
	mov	rdx, rax
	lea	rcx, [SymTables+rip]
	call	sym_add_table@PLT
	jmp	$_200

$_199:	cmp	byte ptr [rax+0x18], 0
	jz	$_200
	cmp	byte ptr [rax+0x18], 1
	jz	$_200
	cmp	byte ptr [rax+0x18], 2
	jz	$_200
	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_233

$_200:	mov	qword ptr [rsi+0x30], rdi
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
$_201:	or	byte ptr [rsi+0x40], 0x40
	jmp	$_204

$_202:	cmp	byte ptr [ModuleInfo+0x1E1+rip], 3
	jnz	$_204
	cmp	cl, 7
	jz	$_203
	cmp	cl, 8
	jnz	$_204
$_203:	or	byte ptr [rsi+0x40], 0x40
$_204:	cmp	byte ptr [rbx], 8
	jne	$_221
	mov	rcx, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rcx]
	or	eax, 0x20202020
	cmp	eax, 1936028533
	jne	$_221
	cmp	byte ptr [rcx+0x4], 0
	jne	$_221
	mov	dword ptr [rbp-0x3C], 0
	cmp	byte ptr [rbp+0x48], 2
	jnz	$_205
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_205
	cmp	byte ptr [ModuleInfo+0x355+rip], 0
	jz	$_205
	inc	dword ptr [rbp-0x3C]
$_205:	cmp	dword ptr [rbp+0x40], 0
	jnz	$_206
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
$_206:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	mov	dword ptr [rbp-0x24], 0
$_207:	cmp	byte ptr [rbx], 2
	jz	$_210
	cmp	byte ptr [rbx], 8
	jne	$_213
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_213
	cmp	byte ptr [rax+0x18], 10
	jnz	$_213
	mov	rdi, rax
	mov	edx, dword ptr [rdi+0x10]
	mov	rcx, qword ptr [rdi+0x28]
	call	FindResWord@PLT
	mov	ecx, eax
	imul	eax, ecx, 12
	lea	rdx, [SpecialTable+rip]
	cmp	byte ptr [rdx+rax+0xB], 2
	jnz	$_213
	mov	byte ptr [rbx], 2
	mov	dword ptr [rbx+0x4], ecx
	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rbx+0x8], rax
	cmp	dword ptr [rbp-0x3C], 0
	jz	$_209
	cmp	ecx, 121
	jz	$_208
	cmp	ecx, 122
	jnz	$_209
$_208:	dec	dword ptr [rbp-0x24]
	inc	dword ptr [rbp-0x3C]
$_209:	jmp	$_212

$_210:	cmp	dword ptr [rbp-0x3C], 0
	jz	$_212
	cmp	dword ptr [rbx+0x4], 121
	jz	$_211
	cmp	dword ptr [rbx+0x4], 122
	jnz	$_212
$_211:	dec	dword ptr [rbp-0x24]
	inc	dword ptr [rbp-0x3C]
$_212:	inc	dword ptr [rbp-0x24]
	add	rbx, 24
	jmp	$_207

$_213:	mov	edx, dword ptr [rbp+0x30]
	mov	rax, qword ptr [rbp+0x38]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	dword ptr [rbp-0x24], 0
	jnz	$_216
	cmp	dword ptr [rbp-0x3C], 0
	jz	$_214
	mov	eax, dword ptr [rbp-0x3C]
	dec	eax
	add	dword ptr [rbp+0x30], eax
	imul	eax, eax, 24
	add	rbx, rax
	jmp	$_215

$_214:	mov	rdx, qword ptr [rbx-0x8]
	mov	ecx, 2008
	call	asmerr@PLT
$_215:	jmp	$_221

$_216:	mov	ecx, dword ptr [rbp-0x24]
	inc	ecx
	imul	ecx, ecx, 2
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	qword ptr [rsi], rdi
	mov	eax, dword ptr [rbp-0x24]
	stosw
$_217:	cmp	byte ptr [rbx], 2
	jnz	$_221
	cmp	dword ptr [rbp-0x3C], 0
	jz	$_218
	cmp	dword ptr [rbx+0x4], 121
	jz	$_220
	cmp	dword ptr [rbx+0x4], 122
	jz	$_220
$_218:	mov	ecx, dword ptr [rbx+0x4]
	call	SizeFromRegister@PLT
	cmp	rax, 1
	jnz	$_219
	mov	ecx, 2032
	call	asmerr@PLT
$_219:	mov	eax, dword ptr [rbx+0x4]
	stosw
$_220:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	jmp	$_217

$_221:	cmp	byte ptr [rbx], 6
	jz	$_222
	cmp	byte ptr [rbx], 7
	jz	$_222
	cmp	byte ptr [rbx], 3
	jnz	$_223
$_222:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_233

$_223:	cmp	byte ptr [rbx], 44
	jnz	$_224
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
$_224:	mov	rdi, qword ptr [rbp+0x28]
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x30], eax
	jge	$_225
	cmp	byte ptr [rbx], 9
	jnz	$_228
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_228
$_225:	cmp	qword ptr [rsi+0x8], 0
	jz	$_226
	lea	rdx, [DS0006+0x6+rip]
	mov	ecx, 2111
	call	asmerr@PLT
$_226:	cmp	byte ptr [rbx], 9
	jnz	$_227
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_227
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, rbx
	mov	rcx, rdi
	call	$_062
$_227:	jmp	$_232

$_228:	cmp	byte ptr [rdi+0x1A], 0
	jnz	$_229
	mov	ecx, 2119
	call	asmerr@PLT
	jmp	$_232

$_229:	mov	ebx, dword ptr [ModuleInfo+0x220+rip]
	dec	ebx
	mov	edx, ebx
	mov	rax, qword ptr [rbp+0x38]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	byte ptr [rbx], 9
	jnz	$_230
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_230
	sub	rbx, 24
$_230:	cmp	byte ptr [rbx], 7
	jnz	$_231
	cmp	dword ptr [rbx+0x4], 275
	jnz	$_231
	or	byte ptr [rsi+0x40], 0x01
$_231:	movzx	eax, byte ptr [rbp-0x1A]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp+0x30]
	mov	rcx, rdi
	call	$_072
	cmp	eax, -1
	jnz	$_232
$_232:	or	byte ptr [rdi+0x14], 0x02
	or	byte ptr [rdi+0x15], 0x08
	xor	eax, eax
$_233:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CreateProc:
	mov	qword ptr [rsp+0x18], r8
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	test	rdi, rdi
	jnz	$_237
	mov	rcx, rdx
	cmp	byte ptr [rcx], 0
	jz	$_234
	call	SymCreate@PLT
	jmp	$_235

$_234:	call	SymAlloc@PLT
$_235:	mov	rdi, rax
	test	rdi, rdi
	jz	$_236
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rdi+0x1B], al
$_236:	jmp	$_240

$_237:	cmp	byte ptr [rdi+0x18], 0
	jnz	$_238
	lea	rcx, [SymTables+rip]
	jmp	$_239

$_238:	lea	rcx, [SymTables+0x10+rip]
$_239:	mov	rdx, rdi
	call	sym_remove_table@PLT
$_240:	test	rdi, rdi
	je	$_247
	mov	eax, dword ptr [rbp+0x28]
	mov	byte ptr [rdi+0x18], al
	mov	ecx, 72
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x68], rax
	jmp	$_246

$_241:	cmp	qword ptr [SymTables+0x40+rip], 0
	jnz	$_242
	mov	qword ptr [SymTables+0x40+rip], rdi
	jmp	$_243

$_242:	mov	rcx, qword ptr [SymTables+0x48+rip]
	mov	qword ptr [rcx+0x78], rdi
$_243:	mov	qword ptr [SymTables+0x48+rip], rdi
	inc	dword ptr [procidx+rip]
	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_244
	mov	ecx, 24
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x58], rax
	call	get_curr_srcfile@PLT
	mov	rdx, qword ptr [rdi+0x58]
	mov	word ptr [rdx+0xE], ax
$_244:	jmp	$_247

$_245:	or	byte ptr [rdi+0x3B], 0x02
	mov	rdx, rdi
	lea	rcx, [SymTables+0x10+rip]
	call	sym_add_table@PLT
	jmp	$_247

$_246:	cmp	byte ptr [rdi+0x18], 1
	jz	$_241
	cmp	byte ptr [rdi+0x18], 2
	jz	$_245
$_247:	mov	rax, rdi
	leave
	pop	rdi
	ret

DeleteProc:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rcx
	cmp	byte ptr [rdi+0x18], 1
	jnz	$_249
	mov	rsi, qword ptr [rdi+0x68]
	mov	rdi, qword ptr [rsi+0x18]
$_248:	test	rdi, rdi
	jz	$_249
	mov	rsi, qword ptr [rdi+0x68]
	mov	rcx, rdi
	call	SymFree@PLT
	mov	rdi, rsi
	jmp	$_248

$_249:
	leave
	pop	rdi
	pop	rsi
	ret

ProcDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	rbx, rdx
	cmp	ecx, 1
	jz	$_250
	imul	ecx, ecx, 24
	mov	rdx, qword ptr [rbx+rcx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_283

$_250:	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jnz	$_252
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_251
	mov	ecx, 2034
	call	asmerr@PLT
	jmp	$_283

$_251:	xor	eax, eax
	jmp	$_283

$_252:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x18], rax
	add	rbx, 24
	mov	rdi, qword ptr [CurrProc+rip]
	test	rdi, rdi
	jz	$_256
	mov	rsi, qword ptr [rdi+0x68]
	cmp	qword ptr [rsi+0x8], 0
	jnz	$_253
	test	byte ptr [rsi+0x40], 0x40
	jnz	$_253
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_253
	cmp	qword ptr [rsi], 0
	jz	$_254
$_253:	mov	rdx, qword ptr [rbp-0x18]
	mov	ecx, 2144
	call	asmerr@PLT
	jmp	$_283

$_254:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_255
	mov	rcx, rdi
	call	SymGetLocal@PLT
$_255:	mov	ecx, 16
	call	LclAlloc@PLT
	lea	rdx, [ProcStack+rip]
	mov	rcx, qword ptr [rdx]
	mov	qword ptr [rax], rcx
	mov	qword ptr [rax+0x8], rdi
	mov	qword ptr [rdx], rax
$_256:	cmp	byte ptr [ModuleInfo+0x1C7+rip], 0
	jz	$_257
	movzx	ecx, byte ptr [ModuleInfo+0x1C7+rip]
	call	AlignCurrOffset@PLT
$_257:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	rcx, qword ptr [rbp-0x18]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x8], rax
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_273
	mov	dword ptr [rbp-0x1C], 0
	test	rax, rax
	jz	$_258
	test	dword ptr [rax+0x14], 0x80
	jz	$_258
	inc	dword ptr [rbp-0x1C]
$_258:	test	rax, rax
	jz	$_259
	cmp	byte ptr [rax+0x18], 0
	jnz	$_260
$_259:	mov	r8d, 1
	mov	rdx, qword ptr [rbp-0x18]
	mov	rcx, rax
	call	CreateProc
	mov	qword ptr [rbp-0x8], rax
	mov	dword ptr [rbp-0x20], 0
	jmp	$_265

$_260:	cmp	byte ptr [rax+0x18], 2
	jnz	$_264
	test	byte ptr [rax+0x3B], 0x02
	jz	$_264
	mov	dword ptr [rbp-0x20], 1
	test	byte ptr [rax+0x15], 0x08
	jz	$_262
	inc	dword ptr [procidx+rip]
	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_261
	mov	ecx, 24
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	rcx, qword ptr [rbp-0x8]
	mov	qword ptr [rcx+0x58], rdi
	call	get_curr_srcfile@PLT
	mov	word ptr [rdi+0xE], ax
$_261:	jmp	$_263

$_262:	mov	r8d, 1
	mov	rdx, qword ptr [rbp-0x18]
	mov	rcx, qword ptr [rbp-0x8]
	call	CreateProc
	mov	qword ptr [rbp-0x8], rax
$_263:	jmp	$_265

$_264:	mov	rcx, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_283

$_265:	mov	rdi, qword ptr [rbp-0x8]
	mov	rcx, rdi
	call	SetSymSegOfs@PLT
	call	SymClearLocal@PLT
	mov	rsi, qword ptr [rdi+0x68]
	movzx	ecx, byte ptr [ModuleInfo+0x1CC+rip]
	lea	rdx, [ModuleInfo+rip]
	mov	ecx, dword ptr [rdx+rcx*4+0x224]
	mov	word ptr [rsi+0x42], cx
	mov	qword ptr [CurrProc+rip], rdi
	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS0007+rip]
	lea	rcx, [strFUNC+rip]
	call	tsprintf@PLT
	movzx	eax, byte ptr [ModuleInfo+0x1B6+rip]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, rdi
	call	ParseProc
	cmp	eax, -1
	jnz	$_266
	mov	qword ptr [CurrProc+rip], 0
	mov	byte ptr [strFUNC+rip], 0
	jmp	$_283

$_266:	cmp	dword ptr [rbp-0x20], 0
	jz	$_267
	cmp	byte ptr [Options+0x99+rip], 0
	jz	$_267
	or	dword ptr [rdi+0x14], 0x80
$_267:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_270
	test	byte ptr [rdi+0x15], 0x08
	jz	$_270
	mov	rcx, rdi
	call	sym_ext2int@PLT
	cmp	qword ptr [SymTables+0x40+rip], 0
	jnz	$_268
	mov	qword ptr [SymTables+0x40+rip], rdi
	jmp	$_269

$_268:	mov	rcx, qword ptr [SymTables+0x48+rip]
	mov	qword ptr [rcx+0x78], rdi
$_269:	mov	qword ptr [SymTables+0x48+rip], rdi
$_270:	mov	rcx, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rcx+0x68]
	movzx	ecx, word ptr [rsi+0x42]
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	cmp	qword ptr [rsi+0x8], 0
	jz	$_271
	cmp	byte ptr [r11+rax+0xA], 4
	jnz	$_271
	or	byte ptr [rsi+0x40], 0xFFFFFF80
$_271:	test	dword ptr [rdi+0x14], 0x80
	jz	$_272
	cmp	dword ptr [rbp-0x1C], 0
	jnz	$_272
	mov	rcx, rdi
	call	AddPublicData@PLT
$_272:	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdx, qword ptr [rcx+0x68]
	mov	rax, qword ptr [rdx+0x20]
	mov	qword ptr [rdi+0x70], rax
	mov	qword ptr [rdx+0x20], rdi
	jmp	$_276

$_273:	mov	rdi, qword ptr [rbp-0x8]
	test	rdi, rdi
	jnz	$_274
	xor	eax, eax
	jmp	$_283

$_274:	inc	dword ptr [procidx+rip]
	or	byte ptr [rdi+0x14], 0x02
	mov	rcx, rdi
	call	SymSetLocal@PLT
	call	GetCurrOffset@PLT
	mov	ecx, eax
	cmp	ecx, dword ptr [rdi+0x28]
	jz	$_275
	mov	dword ptr [rdi+0x28], ecx
	mov	byte ptr [ModuleInfo+0x1ED+rip], 1
$_275:	mov	qword ptr [CurrProc+rip], rdi
	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS0007+rip]
	lea	rcx, [strFUNC+rip]
	call	tsprintf@PLT
	mov	rsi, qword ptr [rdi+0x68]
	mov	rcx, qword ptr [rsi+0x30]
	test	byte ptr [rsi+0x40], 0x40
	jz	$_276
	test	rcx, rcx
	jz	$_276
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_276
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2006
	call	asmerr@PLT
$_276:	mov	rcx, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rcx+0x68]
	mov	ecx, 128
	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jz	$_277
	or	ecx, 0x04
$_277:	mov	dword ptr [ProcStatus+rip], ecx
	mov	dword ptr [StackAdj+rip], 0
	mov	dword ptr [StackAdjHigh+rip], 0
	test	byte ptr [rsi+0x40], 0x40
	jz	$_278
	mov	dword ptr [endprolog_found+rip], 0
	mov	r8d, 4
	xor	edx, edx
	lea	rcx, [unw_info+rip]
	call	tmemset@PLT
	cmp	qword ptr [rsi+0x30], 0
	jz	$_278
	mov	eax, 3
	and	byte ptr [unw_info+rip], 0x03
	shl	al, 2
	or	byte ptr [unw_info+rip], al
$_278:	mov	rcx, qword ptr [rbp-0x8]
	mov	eax, dword ptr [Parse_Pass+rip]
	mov	byte ptr [rcx+0x3A], al
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_279
	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 7
	call	LstWrite@PLT
$_279:	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_282
	call	get_curr_srcfile@PLT
	mov	edi, eax
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_280
	call	GetLineNumber@PLT
	mov	edx, eax
	mov	ecx, edi
	call	AddLinnumDataRef@PLT
	jmp	$_282

$_280:	xor	eax, eax
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_281
	call	GetLineNumber@PLT
$_281:	mov	edx, eax
	mov	ecx, edi
	call	AddLinnumDataRef@PLT
$_282:	mov	rcx, qword ptr [rbp-0x8]
	call	BackPatch@PLT
	mov	eax, 0
$_283:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CopyPrototype:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rcx
	mov	rsi, qword ptr [rdi+0x68]
	mov	rcx, qword ptr [rbp+0x28]
	test	byte ptr [rcx+0x15], 0x08
	jnz	$_284
	mov	rax, -1
	jmp	$_292

$_284:	mov	r8d, 72
	mov	rdx, qword ptr [rcx+0x68]
	mov	rcx, rsi
	call	tmemcpy@PLT
	mov	rcx, qword ptr [rbp+0x28]
	mov	al, byte ptr [rcx+0x19]
	mov	byte ptr [rdi+0x19], al
	mov	al, byte ptr [rcx+0x1A]
	mov	byte ptr [rdi+0x1A], al
	and	dword ptr [rdi+0x14], 0xFFFFFF7F
	test	dword ptr [rcx+0x14], 0x80
	jz	$_285
	or	dword ptr [rdi+0x14], 0x80
$_285:	mov	al, byte ptr [rcx+0x1B]
	mov	byte ptr [rdi+0x1B], al
	or	byte ptr [rdi+0x15], 0x08
	mov	qword ptr [rsi+0x8], 0
	mov	rdx, qword ptr [rcx+0x68]
	mov	rdi, qword ptr [rdx+0x8]
$_286:	test	rdi, rdi
	jz	$_291
	mov	ecx, 128
	call	LclAlloc@PLT
	mov	r8d, 128
	mov	rdx, rdi
	mov	rcx, rax
	call	tmemcpy@PLT
	mov	qword ptr [rax+0x78], 0
	cmp	qword ptr [rsi+0x8], 0
	jnz	$_287
	mov	qword ptr [rsi+0x8], rax
	jmp	$_290

$_287:	mov	rcx, qword ptr [rsi+0x8]
$_288:	cmp	qword ptr [rcx+0x78], 0
	jz	$_289
	mov	rcx, qword ptr [rcx+0x78]
	jmp	$_288

$_289:	mov	qword ptr [rcx+0x78], rax
$_290:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_286

$_291:	xor	eax, eax
$_292:	leave
	pop	rdi
	pop	rsi
	ret

$_293:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 248
	lea	rax, [DS0008+rip]
	mov	qword ptr [rbp-0x10], rax
	mov	dword ptr [rbp-0x20], 0
	mov	rdi, rcx
	cmp	dword ptr [endprolog_found+rip], 0
	jnz	$_294
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 3007
	call	asmerr@PLT
$_294:	cmp	byte ptr [unw_segs_defined+rip], 0
	jz	$_295
	mov	r8d, 516
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
	jmp	$_296

$_295:	mov	r9d, 8
	mov	r8d, 516
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
$_296:	mov	dword ptr [rbp-0x20], 0
	mov	rcx, qword ptr [rbp-0x10]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x8], rax
	test	rax, rax
	jz	$_297
	mov	eax, dword ptr [rax+0x50]
	mov	dword ptr [rbp-0x20], eax
$_297:	movzx	eax, byte ptr [unw_info+rip]
	shr	eax, 2
	mov	ecx, eax
	mov	al, byte ptr [unw_info+0x3+rip]
	and	eax, 0x0F
	mov	edx, eax
	movzx	eax, byte ptr [unw_info+0x3+rip]
	shr	eax, 4
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], edx
	movzx	eax, byte ptr [unw_info+0x2+rip]
	mov	dword ptr [rsp+0x20], eax
	movzx	r9d, byte ptr [unw_info+0x1+rip]
	mov	r8d, ecx
	mov	edx, 1
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [unw_info+0x2+rip], 0
	je	$_301
	lea	rax, [DS000C+rip]
	mov	qword ptr [rbp-0xB8], rax
	mov	byte ptr [rbp-0xAC], 0
	movzx	esi, byte ptr [unw_info+0x2+rip]
	lea	rdi, [rbp-0xAC]
$_298:	test	esi, esi
	jz	$_301
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rbx, [rdi+rax]
	lea	rcx, [unw_code+rip]
	mov	rdx, rsi
	movzx	r9d, word ptr [rcx+rdx*2-0x2]
	mov	r8, qword ptr [rbp-0xB8]
	lea	rdx, [DS000D+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	lea	rax, [DS0000+rip]
	mov	qword ptr [rbp-0xB8], rax
	mov	rcx, rdi
	call	tstrlen@PLT
	cmp	esi, 1
	jz	$_299
	cmp	rax, 72
	jbe	$_300
$_299:	mov	rcx, rdi
	call	AddLineQueue@PLT
	mov	byte ptr [rdi], 0
	lea	rax, [DS000C+rip]
	mov	qword ptr [rbp-0xB8], rax
$_300:	dec	esi
	jmp	$_298

$_301:
	lea	rcx, [DS000E+rip]
	call	AddLineQueue@PLT
	mov	rdi, qword ptr [rbp+0x28]
	mov	rsi, qword ptr [rdi+0x68]
	cmp	qword ptr [rsi+0x30], 0
	jz	$_302
	mov	rcx, qword ptr [rsi+0x30]
	mov	rdx, qword ptr [rcx+0x8]
	lea	rcx, [DS000F+rip]
	call	AddLineQueueX@PLT
$_302:	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0010+rip]
	call	AddLineQueueX@PLT
	xor	ecx, ecx
	call	SimGetSegName@PLT
	mov	rcx, qword ptr [rdi+0x30]
	mov	rdx, qword ptr [rcx+0x8]
	mov	rcx, rax
	call	tstrcmp@PLT
	test	eax, eax
	jnz	$_303
	lea	rax, [DS0011+rip]
	mov	qword ptr [rbp-0x10], rax
	mov	al, byte ptr [unw_segs_defined+rip]
	and	eax, 0x01
	mov	dword ptr [rbp-0x18], eax
	mov	byte ptr [unw_segs_defined+rip], 3
	jmp	$_304

$_303:	movzx	eax, byte ptr [rbp-0x2C]
	mov	qword ptr [rbp-0x10], rax
	mov	rcx, qword ptr [rdi+0x30]
	call	GetSegIdx@PLT
	mov	r8, rax
	lea	rdx, [DS0012+rip]
	mov	rcx, qword ptr [rbp-0x10]
	call	tsprintf@PLT
	mov	dword ptr [rbp-0x18], 0
	or	byte ptr [unw_segs_defined+rip], 0x02
$_304:	cmp	dword ptr [rbp-0x18], 0
	jz	$_305
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
	jmp	$_306

$_305:	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
$_306:	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x20]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rdi+0x50]
	mov	r8, qword ptr [rdi+0x8]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0015+rip]
	call	AddLineQueueX@PLT
	mov	al, byte ptr [ModuleInfo+0x1D4+rip]
	mov	byte ptr [rbp-0x19], al
	mov	byte ptr [ModuleInfo+0x1D4+rip], 1
	call	RunLineQueue@PLT
	mov	al, byte ptr [rbp-0x19]
	mov	byte ptr [ModuleInfo+0x1D4+rip], al
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_307:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rcx
	mov	rax, qword ptr [rdi+0x30]
	cmp	qword ptr [ModuleInfo+0x1F8+rip], rax
	jnz	$_308
	call	GetCurrOffset@PLT
	mov	ecx, eax
	sub	ecx, dword ptr [rdi+0x28]
	mov	dword ptr [rdi+0x50], ecx
	jmp	$_309

$_308:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	mov	rdx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rcx, qword ptr [rdx+0x30]
	mov	ecx, dword ptr [rcx+0x28]
	sub	ecx, dword ptr [rdi+0x28]
	mov	dword ptr [rdi+0x50], ecx
$_309:	mov	rsi, qword ptr [rdi+0x68]
	cmp	byte ptr [Options+0xD+rip], 2
	jbe	$_315
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_315
	mov	rdi, qword ptr [rsi+0x8]
$_310:	test	rdi, rdi
	jz	$_312
	test	byte ptr [rdi+0x14], 0x01
	jnz	$_311
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 6004
	call	asmerr@PLT
$_311:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_310

$_312:	mov	rdi, qword ptr [rsi+0x10]
$_313:	test	rdi, rdi
	jz	$_315
	test	byte ptr [rdi+0x14], 0x01
	jnz	$_314
	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 6004
	call	asmerr@PLT
$_314:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_313

$_315:
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_320
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 2
	jz	$_316
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 5
	jz	$_316
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 3
	jnz	$_320
$_316:	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jz	$_320
	mov	rcx, qword ptr [sym_ReservedStack+rip]
	mov	ecx, dword ptr [rcx+0x28]
	mov	dword ptr [rsi+0x38], ecx
	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jz	$_320
	mov	rdi, qword ptr [rsi+0x10]
$_317:	test	rdi, rdi
	jz	$_318
	add	dword ptr [rdi+0x28], ecx
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_317

$_318:	mov	rdi, qword ptr [rsi+0x8]
$_319:	test	rdi, rdi
	jz	$_320
	add	dword ptr [rdi+0x28], ecx
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_319

$_320:
	test	byte ptr [rsi+0x40], 0x40
	jz	$_321
	call	LstSetPosition@PLT
	mov	rcx, qword ptr [rbp+0x20]
	call	$_293
$_321:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_322
	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 7
	call	LstWrite@PLT
$_322:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_324
	test	dword ptr [ProcStatus+rip], 0x80
	jz	$_323
	mov	rcx, qword ptr [CurrProc+rip]
	mov	rcx, qword ptr [rcx+0x68]
	call	SetLocalOffsets
$_323:	mov	rcx, qword ptr [CurrProc+rip]
	call	SymGetLocal@PLT
$_324:	lea	rdx, [ProcStack+rip]
	mov	rax, qword ptr [rdx]
	test	rax, rax
	jz	$_325
	mov	rcx, rax
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rdx], rax
	mov	rax, qword ptr [rcx+0x8]
$_325:	mov	qword ptr [CurrProc+rip], rax
	test	rax, rax
	jz	$_326
	mov	r8, qword ptr [rax+0x8]
	lea	rdx, [DS0007+rip]
	lea	rcx, [strFUNC+rip]
	call	tsprintf@PLT
	mov	rcx, qword ptr [CurrProc+rip]
	call	SymSetLocal@PLT
	jmp	$_327

$_326:	mov	byte ptr [strFUNC+rip], al
$_327:	mov	dword ptr [ProcStatus+rip], 0
	leave
	pop	rdi
	pop	rsi
	ret

EndpDir:
	mov	qword ptr [rsp+0x8], rcx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	rbx, rdx
	cmp	dword ptr [rbp+0x18], 1
	jnz	$_328
	cmp	byte ptr [rbx+0x30], 0
	jz	$_329
$_328:	imul	ecx, dword ptr [rbp+0x18], 24
	mov	rdx, qword ptr [rbx+rcx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_334

$_329:	cmp	qword ptr [ModuleInfo+0x110+rip], 0
	jz	$_330
	lea	rcx, [DS0016+rip]
	call	AddLineQueue@PLT
	lea	rcx, [DS0017+rip]
	call	AddLineQueue@PLT
	call	RunLineQueue@PLT
$_330:	mov	rcx, qword ptr [CurrProc+rip]
	test	rcx, rcx
	jz	$_332
	mov	edx, dword ptr [rcx+0x10]
	inc	edx
	mov	r8d, edx
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, qword ptr [rcx+0x8]
	call	qword ptr [SymCmpFunc+rip]
	test	rax, rax
	jnz	$_331
	mov	rcx, qword ptr [CurrProc+rip]
	call	$_307
	mov	ecx, 1
	jmp	$_332

$_331:	xor	ecx, ecx
$_332:	test	ecx, ecx
	jnz	$_333
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	jmp	$_334

$_333:	xor	eax, eax
$_334:	leave
	pop	rbx
	ret

ExcFrameDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	al, byte ptr [unw_info+0x2+rip]
	mov	byte ptr [rbp-0x71], al
	mov	rdi, qword ptr [CurrProc+rip]
	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	dword ptr [Options+0xA4+rip], 3
	jz	$_335
	cmp	dword ptr [Options+0xA4+rip], 1
	jz	$_335
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 1
	jnz	$_336
$_335:	xor	edx, edx
	mov	ecx, dword ptr [rbx+0x4]
	call	GetResWName@PLT
	mov	rdx, rax
	mov	ecx, 3006
	call	asmerr@PLT
	jmp	$_382

$_336:	test	rdi, rdi
	jz	$_337
	cmp	dword ptr [endprolog_found+rip], 1
	jnz	$_338
$_337:	mov	ecx, 3008
	call	asmerr@PLT
	jmp	$_382

$_338:	mov	rsi, qword ptr [rdi+0x68]
	test	byte ptr [rsi+0x40], 0x40
	jnz	$_339
	mov	ecx, 3009
	call	asmerr@PLT
	jmp	$_382

$_339:	movzx	ecx, byte ptr [unw_info+0x2+rip]
	lea	rax, [unw_code+rip]
	lea	rax, [rax+rcx*2]
	mov	qword ptr [rbp-0x80], rax
	call	GetCurrOffset@PLT
	mov	ecx, eax
	sub	ecx, dword ptr [rdi+0x28]
	mov	byte ptr [rbp-0x73], cl
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0x6C], eax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_378

$_340:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_382
	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	mov	rcx, qword ptr [rbp-0x18]
	cmp	dword ptr [rbp-0x2C], 1
	jnz	$_341
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_341
	jmp	$_342

$_341:	cmp	dword ptr [rbp-0x2C], 0
	jz	$_342
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_382

$_342:	cmp	dword ptr [rbp-0x64], 0
	jz	$_343
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_382

$_343:	cmp	dword ptr [rbp-0x68], 0
	jnz	$_344
	mov	ecx, 2090
	call	asmerr@PLT
	jmp	$_382

$_344:	test	byte ptr [rbp-0x68], 0x07
	jz	$_345
	mov	edx, dword ptr [rbp-0x68]
	mov	ecx, 2189
	call	asmerr@PLT
	jmp	$_382

$_345:	cmp	dword ptr [rbp-0x68], 128
	jbe	$_348
	cmp	dword ptr [rbp-0x68], 524288
	jc	$_346
	mov	edx, dword ptr [rbp-0x68]
	shr	edx, 16
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	movzx	edx, word ptr [rbp-0x68]
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	add	byte ptr [unw_info+0x2+rip], 2
	mov	edx, 1
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	jmp	$_347

$_346:	mov	edx, dword ptr [rbp-0x68]
	shr	edx, 3
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	inc	byte ptr [unw_info+0x2+rip]
	xor	edx, edx
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
$_347:	mov	edx, 1
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	jmp	$_349

$_348:	mov	edx, 2
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	mov	edx, dword ptr [rbp-0x68]
	sub	edx, 8
	shr	edx, 3
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
$_349:	movzx	edx, byte ptr [rbp-0x73]
	mov	rax, qword ptr [rbp-0x80]
	mov	byte ptr [rax], dl
	inc	byte ptr [unw_info+0x2+rip]
	jmp	$_379

$_350:	call	GetCurrOffset@PLT
	mov	ecx, eax
	sub	ecx, dword ptr [rdi+0x28]
	mov	dword ptr [rbp-0x68], ecx
	cmp	ecx, 255
	jbe	$_351
	mov	ecx, 3010
	call	asmerr@PLT
	jmp	$_382

$_351:	mov	eax, dword ptr [rbp-0x68]
	mov	byte ptr [unw_info+0x1+rip], al
	mov	dword ptr [endprolog_found+rip], 1
	jmp	$_379

$_352:	movzx	edx, byte ptr [rbp-0x73]
	mov	rax, qword ptr [rbp-0x80]
	mov	byte ptr [rax], dl
	mov	edx, 10
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	xor	edx, edx
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	cmp	byte ptr [rbx], 8
	jnz	$_353
	mov	rcx, qword ptr [rbx+0x8]
	mov	eax, dword ptr [rcx]
	or	eax, 0x20202020
	cmp	eax, 1701080931
	jnz	$_353
	cmp	byte ptr [rcx+0x4], 0
	jnz	$_353
	mov	edx, 1
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_353:	inc	byte ptr [unw_info+0x2+rip]
	jmp	$_379

$_354:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	mov	ecx, dword ptr [r11+rax]
	and	ecx, 0x08
	cmp	byte ptr [rbx], 2
	jnz	$_355
	test	ecx, ecx
	jnz	$_356
$_355:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_382

$_356:	movzx	edx, byte ptr [rbp-0x73]
	mov	rax, qword ptr [rbp-0x80]
	mov	byte ptr [rax], dl
	xor	edx, edx
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	movzx	edx, byte ptr [r11+rax+0xA]
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	inc	byte ptr [unw_info+0x2+rip]
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_379

$_357:	cmp	byte ptr [rbx], 2
	jz	$_358
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_382

$_358:	cmp	dword ptr [rbp-0x6C], 495
	jnz	$_360
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	test	byte ptr [r11+rax], 0x10
	jnz	$_359
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_382

$_359:	jmp	$_361

$_360:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	test	byte ptr [r11+rax], 0x08
	jnz	$_361
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_382

$_361:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0x72], al
	cmp	dword ptr [rbp-0x6C], 494
	jnz	$_362
	mov	dword ptr [rbp-0x70], 8
	jmp	$_363

$_362:	mov	dword ptr [rbp-0x70], 16
$_363:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jz	$_364
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_382

$_364:	inc	dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_382
	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	mov	rcx, qword ptr [rbp-0x18]
	cmp	dword ptr [rbp-0x2C], 1
	jnz	$_365
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_365
	jmp	$_366

$_365:	cmp	dword ptr [rbp-0x2C], 0
	jz	$_366
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_382

$_366:	mov	eax, dword ptr [rbp-0x70]
	dec	eax
	test	dword ptr [rbp-0x68], eax
	jz	$_367
	mov	edx, dword ptr [rbp-0x70]
	mov	ecx, 2189
	call	asmerr@PLT
	jmp	$_382

$_367:	jmp	$_376

$_368:	movzx	edx, byte ptr [rbp-0x72]
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	imul	ecx, dword ptr [rbp-0x70], 65536
	cmp	dword ptr [rbp-0x68], ecx
	jle	$_369
	mov	ecx, dword ptr [rbp-0x68]
	shr	ecx, 19
	movzx	edx, cx
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	mov	ecx, dword ptr [rbp-0x68]
	shr	ecx, 3
	movzx	edx, cx
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	mov	edx, 5
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	add	byte ptr [unw_info+0x2+rip], 3
	jmp	$_370

$_369:	mov	ecx, dword ptr [rbp-0x68]
	shr	ecx, 3
	movzx	edx, cx
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	mov	edx, 4
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	add	byte ptr [unw_info+0x2+rip], 2
$_370:	movzx	edx, byte ptr [rbp-0x73]
	mov	rax, qword ptr [rbp-0x80]
	mov	byte ptr [rax], dl
	movzx	edx, byte ptr [rbp-0x72]
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	jmp	$_377

$_371:	imul	ecx, dword ptr [rbp-0x70], 65536
	cmp	dword ptr [rbp-0x68], ecx
	jle	$_372
	mov	ecx, dword ptr [rbp-0x68]
	shr	ecx, 20
	movzx	edx, cx
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	mov	ecx, dword ptr [rbp-0x68]
	shr	ecx, 4
	movzx	edx, cx
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	mov	edx, 9
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	add	byte ptr [unw_info+0x2+rip], 3
	jmp	$_373

$_372:	mov	ecx, dword ptr [rbp-0x68]
	shr	ecx, 4
	movzx	edx, cx
	mov	rax, qword ptr [rbp-0x80]
	mov	word ptr [rax], dx
	add	qword ptr [rbp-0x80], 2
	mov	edx, 8
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	add	byte ptr [unw_info+0x2+rip], 2
$_373:	movzx	edx, byte ptr [rbp-0x73]
	mov	rax, qword ptr [rbp-0x80]
	mov	byte ptr [rax], dl
	movzx	edx, byte ptr [rbp-0x72]
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	jmp	$_377

$_374:	cmp	dword ptr [rbp-0x68], 240
	jbe	$_375
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_382

$_375:	movzx	eax, byte ptr [rbp-0x72]
	and	byte ptr [unw_info+0x3+rip], 0xFFFFFFF0
	or	byte ptr [unw_info+0x3+rip], al
	mov	edx, dword ptr [rbp-0x68]
	shr	edx, 4
	movzx	eax, dl
	and	byte ptr [unw_info+0x3+rip], 0x0F
	shl	al, 4
	or	byte ptr [unw_info+0x3+rip], al
	movzx	edx, byte ptr [rbp-0x73]
	mov	rax, qword ptr [rbp-0x80]
	mov	byte ptr [rax], dl
	mov	edx, 3
	mov	rax, qword ptr [rbp-0x80]
	and	byte ptr [rax+0x1], 0xFFFFFFF0
	or	byte ptr [rax+0x1], dl
	movzx	edx, byte ptr [rbp-0x72]
	mov	rax, qword ptr [rbp-0x80]
	shl	dl, 4
	and	byte ptr [rax+0x1], 0x0F
	or	byte ptr [rax+0x1], dl
	inc	byte ptr [unw_info+0x2+rip]
	jmp	$_377

$_376:	cmp	dword ptr [rbp-0x6C], 494
	je	$_368
	cmp	dword ptr [rbp-0x6C], 495
	je	$_371
	cmp	dword ptr [rbp-0x6C], 496
	je	$_374
$_377:	jmp	$_379

$_378:	cmp	dword ptr [rbp-0x6C], 490
	je	$_340
	cmp	dword ptr [rbp-0x6C], 491
	je	$_350
	cmp	dword ptr [rbp-0x6C], 492
	je	$_352
	cmp	dword ptr [rbp-0x6C], 493
	je	$_354
	cmp	dword ptr [rbp-0x6C], 494
	je	$_357
	cmp	dword ptr [rbp-0x6C], 495
	je	$_357
	cmp	dword ptr [rbp-0x6C], 496
	je	$_357
$_379:	cmp	byte ptr [rbx], 0
	jz	$_380
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_382

$_380:	mov	al, byte ptr [unw_info+0x2+rip]
	cmp	byte ptr [rbp-0x71], al
	jbe	$_381
	mov	ecx, 3011
	call	asmerr@PLT
	jmp	$_382

$_381:	xor	eax, eax
$_382:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ProcCheckOpen:
	push	rdi
	sub	rsp, 32
	mov	rdi, qword ptr [CurrProc+rip]
	jmp	$_384

$_383:	mov	rdx, qword ptr [rdi+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	mov	rcx, rdi
	call	$_307
	mov	rdi, qword ptr [CurrProc+rip]
$_384:	test	rdi, rdi
	jnz	$_383
	add	rsp, 32
	pop	rdi
	ret

$_385:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2296
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_386
	cmp	dword ptr [UseSavedState+rip], 0
	jz	$_386
	xor	eax, eax
	jmp	$_402

$_386:	mov	rdi, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rdi+0x68]
	movzx	ebx, byte ptr [rdi+0x1A]
	mov	qword ptr [rbp-0x8], rsi
	cmp	ebx, 7
	jnz	$_387
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 2
	jnz	$_387
	mov	ebx, 0
$_387:	cmp	ebx, 1
	jz	$_388
	cmp	ebx, 2
	jz	$_388
	cmp	ebx, 7
	jnz	$_389
$_388:	or	ebx, 0x10
$_389:	cmp	byte ptr [rdi+0x19], -126
	jnz	$_390
	or	ebx, 0x20
$_390:	test	dword ptr [rdi+0x14], 0x80
	jnz	$_391
	or	ebx, 0x40
$_391:	test	byte ptr [rsi+0x40], 0x04
	jz	$_392
	or	ebx, 0x80
$_392:	mov	dword ptr [rbp-0x8B4], ebx
	mov	rcx, qword ptr [ModuleInfo+0x190+rip]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x28], rax
	test	eax, eax
	jz	$_393
	cmp	byte ptr [rax+0x18], 9
	jnz	$_393
	test	byte ptr [rax+0x38], 0x02
	jnz	$_394
$_393:	mov	ecx, 2120
	call	asmerr@PLT
	jmp	$_402

$_394:	cmp	byte ptr [Options+0x96+rip], 0
	jz	$_395
	lea	rcx, [DS0018+rip]
	call	tprintf@PLT
$_395:	lea	rdi, [rbp-0xB0]
	mov	rsi, qword ptr [rsi]
	test	rsi, rsi
	jz	$_398
	movzx	ebx, word ptr [rsi]
	add	rsi, 2
$_396:	test	ebx, ebx
	jz	$_398
	movzx	ecx, word ptr [rsi]
	mov	rdx, rdi
	call	GetResWName@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	add	rdi, rax
	cmp	ebx, 1
	jbe	$_397
	mov	byte ptr [rdi], 44
	inc	rdi
$_397:	dec	ebx
	add	rsi, 2
	jmp	$_396

$_398:	mov	byte ptr [rdi], 0
	mov	rsi, qword ptr [rbp-0x8]
	mov	rdi, qword ptr [CurrProc+rip]
	mov	rcx, qword ptr [rsi+0x28]
	test	rcx, rcx
	jnz	$_399
	lea	rcx, [DS0018+0x15+rip]
$_399:	mov	qword ptr [rsp+0x38], rcx
	lea	rax, [rbp-0xB0]
	mov	qword ptr [rsp+0x30], rax
	mov	eax, dword ptr [rsi+0x24]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rsi+0x20]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x8B4]
	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS0019+rip]
	lea	rcx, [rbp-0x8B0]
	call	tsprintf@PLT
	mov	ebx, dword ptr [ModuleInfo+0x220+rip]
	inc	ebx
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x28]
	mov	edx, ebx
	lea	rcx, [rbp-0x8B0]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	lea	rax, [rbp-0x1C]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 0
	lea	r9, [rbp-0x8B0]
	mov	r8, qword ptr [rbp+0x28]
	mov	edx, ebx
	mov	rcx, qword ptr [rbp-0x28]
	call	RunMacro@PLT
	dec	ebx
	mov	dword ptr [ModuleInfo+0x220+rip], ebx
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_401
	lea	rcx, [rbp-0x8B0]
	call	_atoqw@PLT
	mov	ebx, eax
	sub	ebx, dword ptr [rsi+0x24]
	mov	rdi, qword ptr [rsi+0x10]
$_400:	test	rdi, rdi
	jz	$_401
	sub	dword ptr [rdi+0x28], ebx
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_400

$_401:	xor	eax, eax
$_402:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_403:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rcx, qword ptr [CurrProc+rip]
	mov	al, byte ptr [rcx+0x1A]
	mov	byte ptr [rbp-0x1], al
	xor	esi, esi
	mov	rdi, qword ptr [rbp+0x38]
	mov	al, byte ptr [rdi+0x19]
	cmp	al, -60
	jnz	$_404
	mov	rdx, qword ptr [rdi+0x20]
	mov	al, byte ptr [rdx+0x19]
$_404:	mov	ecx, dword ptr [rbp+0x28]
	lea	edx, [rcx+0x28]
	xor	ebx, ebx
	test	al, 0x20
	jnz	$_405
	cmp	al, 31
	jz	$_405
	cmp	byte ptr [rbp-0x1], 8
	jnz	$_412
	cmp	al, 15
	jz	$_405
	cmp	al, 79
	jnz	$_412
$_405:	cmp	al, 35
	jz	$_406
	cmp	al, 33
	jnz	$_407
$_406:	mov	esi, 1027
	jmp	$_411

$_407:	cmp	al, 39
	jnz	$_408
	mov	esi, 1028
	jmp	$_411

$_408:	cmp	dword ptr [rdi+0x50], 16
	ja	$_409
	mov	esi, 1030
	jmp	$_411

$_409:	cmp	dword ptr [rdi+0x50], 32
	jnz	$_410
	mov	esi, 1414
	lea	edx, [rcx+0x30]
	jmp	$_411

$_410:	cmp	dword ptr [rdi+0x50], 64
	jnz	$_411
	mov	esi, 1414
	lea	edx, [rcx+0x40]
$_411:	jmp	$_414

$_412:	cmp	ecx, 4
	jnc	$_414
	lea	rdi, [fast_regs+0x18+rip]
	movzx	edx, byte ptr [rdi+rcx]
	mov	esi, 682
	cmp	al, 15
	jz	$_413
	cmp	al, 79
	jnz	$_414
$_413:	cmp	byte ptr [rbp-0x1], 8
	jz	$_414
	movzx	ebx, byte ptr [rdi+rcx+0x1]
	inc	dword ptr [rbp+0x28]
$_414:	test	esi, esi
	jz	$_415
	imul	ecx, dword ptr [rbp+0x30]
	lea	edi, [rcx+0x8]
	mov	r9d, edx
	mov	r8d, edi
	mov	edx, esi
	lea	rcx, [DS001A+rip]
	call	AddLineQueueX@PLT
	test	ebx, ebx
	jz	$_415
	add	edi, 8
	mov	r9d, ebx
	mov	r8d, edi
	mov	edx, esi
	lea	rcx, [DS001A+rip]
	call	AddLineQueueX@PLT
$_415:	mov	eax, dword ptr [rbp+0x28]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_416:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rdx
	mov	rdi, r8
	mov	rcx, qword ptr [CurrProc+rip]
	mov	cl, byte ptr [rcx+0x1A]
	cmp	cl, 8
	jnz	$_417
	mov	dword ptr [rsi], 16
	jmp	$_418

$_417:	mov	dword ptr [rsi], 8
$_418:	mov	rdx, qword ptr [rbp+0x28]
	test	rdi, rdi
	jz	$_419
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_419
	mov	dword ptr [rdx], 1
	mov	eax, 4
	jmp	$_428

$_419:	mov	dword ptr [rdx], 0
	xor	ebx, ebx
$_420:	test	rdi, rdi
	jz	$_427
	mov	eax, dword ptr [rsi]
	cmp	dword ptr [rdi+0x50], eax
	jbe	$_426
	jmp	$_424

$_421:	mov	eax, 16
	jmp	$_425

$_422:	mov	eax, 32
	jmp	$_425

$_423:	mov	eax, 64
	jmp	$_425

$_424:	cmp	byte ptr [rdi+0x19], 41
	jz	$_421
	cmp	byte ptr [rdi+0x19], 15
	jz	$_421
	cmp	byte ptr [rdi+0x19], 79
	jz	$_421
	cmp	byte ptr [rdi+0x19], 47
	jz	$_421
	cmp	byte ptr [rdi+0x19], 31
	jz	$_422
	cmp	byte ptr [rdi+0x19], 63
	jz	$_423
$_425:	mov	dword ptr [rsi], eax
$_426:	inc	ebx
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_420

$_427:	mov	eax, ebx
$_428:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_429:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	dword ptr [rbp-0x14], 4
	mov	rsi, rcx
	mov	rdi, qword ptr [CurrProc+rip]
	cmp	byte ptr [rdi+0x1A], 8
	jnz	$_430
	mov	dword ptr [rbp-0x14], 6
$_430:	mov	r8, qword ptr [rsi+0x8]
	lea	rdx, [rbp-0x4]
	lea	rcx, [rbp-0x8]
	call	$_416
	mov	dword ptr [rbp-0xC], eax
	cmp	dword ptr [rbp-0x8], 0
	jz	$_433
	xor	eax, eax
	mov	rdi, qword ptr [rsi+0x8]
$_431:	test	rdi, rdi
	jz	$_432
	cmp	eax, ebx
	jnc	$_432
	mov	rdi, qword ptr [rdi+0x78]
	inc	eax
	jmp	$_431

$_432:	mov	dword ptr [rbp-0x8], eax
$_433:	mov	dword ptr [rbp-0x10], 0
	xor	ebx, ebx
$_434:	cmp	ebx, dword ptr [rbp-0xC]
	jge	$_444
	mov	rdi, qword ptr [rsi+0x8]
	mov	ecx, dword ptr [rbp-0xC]
	sub	ecx, ebx
	dec	ecx
$_435:	test	ecx, ecx
	jz	$_436
	cmp	ecx, dword ptr [rbp-0x8]
	jle	$_436
	mov	rdi, qword ptr [rdi+0x78]
	dec	ecx
	jmp	$_435

$_436:	mov	eax, dword ptr [rbp-0x14]
	cmp	dword ptr [rbp-0x10], eax
	jge	$_442
	test	byte ptr [rdi+0x3B], 0x04
	jnz	$_440
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_437
	cmp	dword ptr [rbp-0x4], 16
	jl	$_437
	mov	eax, dword ptr [rbp-0x4]
	mul	ebx
	add	eax, 16
	mov	dword ptr [rdi+0x28], eax
$_437:	test	byte ptr [rdi+0x14], 0x01
	jnz	$_438
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_438
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_439
$_438:	mov	r8, rdi
	mov	edx, dword ptr [rbp-0x4]
	mov	ecx, dword ptr [rbp-0x10]
	call	$_403
	mov	dword ptr [rbp-0x10], eax
$_439:	jmp	$_441

$_440:	cmp	ebx, 4
	jnc	$_441
	mov	eax, dword ptr [rbp-0x4]
	mul	ebx
	add	eax, 8
	lea	rcx, [fast_regs+0x18+rip]
	movzx	ecx, byte ptr [rcx+rbx]
	mov	r8d, ecx
	mov	edx, eax
	lea	rcx, [DS001B+rip]
	call	AddLineQueueX@PLT
$_441:	jmp	$_443

$_442:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_443
	test	byte ptr [rdi+0x3B], 0x04
	jnz	$_443
	cmp	dword ptr [rbp-0x4], 16
	jl	$_443
	mov	eax, dword ptr [rbp-0x4]
	mul	ebx
	add	eax, 16
	mov	dword ptr [rdi+0x28], eax
$_443:	inc	ebx
	inc	dword ptr [rbp-0x10]
	jmp	$_434

$_444:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_445:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 0
	mov	rsi, rcx
	test	rsi, rsi
	je	$_449
	lodsw
	movzx	ebx, ax
$_446:	test	ebx, ebx
	jz	$_449
	movzx	edi, word ptr [rsi]
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	test	byte ptr [r11+rax], 0x10
	jz	$_447
	inc	dword ptr [rbp-0x4]
	jmp	$_448

$_447:	mov	rcx, qword ptr [rbp+0x38]
	movzx	eax, byte ptr [ModuleInfo+0x1CC+rip]
	shl	eax, 2
	add	dword ptr [rcx], eax
	mov	edx, edi
	lea	rcx, [DS001C+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp+0x30], 0
	jz	$_448
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	mov	cl, byte ptr [r11+rax+0xA]
	mov	eax, 1
	shl	eax, cl
	test	ax, 0xF0E8
	jz	$_448
	mov	r8d, edi
	mov	edx, 493
	lea	rcx, [DS001D+rip]
	call	AddLineQueueX@PLT
$_448:	dec	ebx
	add	rsi, 2
	jmp	$_446

$_449:
	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_450:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	dword ptr [rbp-0x24], 0
	mov	dword ptr [rbp-0x30], 0
	mov	dword ptr [rbp-0x34], 0
	mov	dword ptr [rbp-0x38], 1
	mov	dword ptr [rbp-0x3C], 0
	mov	dword ptr [rbp-0x44], 0
	mov	byte ptr [rbp-0x45], 0
	mov	byte ptr [rbp-0x46], 0
	mov	rdi, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rdi+0x68]
	mov	qword ptr [rbp-0x8], rsi
	movzx	edx, byte ptr [rdi+0x1A]
	movzx	ecx, byte ptr [rdi+0x1B]
	call	get_fasttype
	mov	al, byte ptr [rax+0xF]
	mov	byte ptr [rbp-0x47], al
	lea	rbx, [ModuleInfo+rip]
	test	al, 0x40
	jz	$_451
	test	byte ptr [rbx+0x334], 0x01
	jz	$_451
	inc	byte ptr [rbp-0x46]
$_451:	test	al, 0x20
	jz	$_452
	cmp	qword ptr [rsi+0x8], 0
	jz	$_452
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_452
	inc	byte ptr [rbp-0x45]
$_452:	test	al, 0x11
	jz	$_453
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_453
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_453
	test	byte ptr [rdi+0x3B], 0x10
	jnz	$_453
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_453
	inc	dword ptr [rbp-0x34]
	test	byte ptr [rdi+0x3B], 0x60
	jnz	$_453
	cmp	dword ptr [rsi+0x24], 0
	jnz	$_453
	cmp	qword ptr [rsi], 0
	jnz	$_453
	mov	dword ptr [rbp-0x38], 0
$_453:	test	byte ptr [rsi+0x40], 0x40
	je	$_476
	test	byte ptr [rbx+0x1E1], 0x01
	je	$_475
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_454
	mov	rcx, qword ptr [sym_ReservedStack+rip]
	mov	eax, dword ptr [rcx+0x28]
	mov	dword ptr [rbp-0x30], eax
$_454:	test	byte ptr [rbx+0x1E5], 0x01
	jz	$_455
	mov	rcx, rsi
	call	$_429
$_455:	cmp	byte ptr [rbp-0x46], 1
	jne	$_462
	mov	rsi, qword ptr [rsi]
	test	rsi, rsi
	jz	$_462
	mov	dword ptr [rbp-0x2C], 0
	lea	r8, [rbp-0x2C]
	mov	edx, 1
	mov	rcx, rsi
	call	$_445
	mov	dword ptr [rbp-0x24], eax
	mov	rsi, qword ptr [rbp-0x8]
	mov	rdi, qword ptr [rsi+0x8]
$_456:	test	rdi, rdi
	jz	$_457
	cmp	qword ptr [rdi+0x78], 0
	jz	$_457
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_456

$_457:	test	rdi, rdi
	jz	$_462
	movzx	ecx, byte ptr [rbx+0x1CC]
	mov	ecx, dword ptr [rbx+rcx*4+0x224]
	cmp	dword ptr [rdi+0x28], 8
	jnz	$_458
	cmp	ecx, 22
	jz	$_459
$_458:	cmp	dword ptr [rdi+0x28], 16
	jnz	$_462
	cmp	ecx, 120
	jnz	$_462
$_459:	mov	rdi, qword ptr [rsi+0x8]
$_460:	test	rdi, rdi
	jz	$_462
	cmp	byte ptr [rdi+0x18], 10
	jz	$_461
	mov	eax, dword ptr [rbp-0x2C]
	add	dword ptr [rdi+0x28], eax
$_461:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_460

$_462:	mov	rsi, qword ptr [rbp-0x8]
	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jnz	$_463
	cmp	dword ptr [rsi+0x20], 0
	jnz	$_464
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_464
$_463:	jmp	$_465

$_464:	cmp	dword ptr [rbp-0x38], 0
	jz	$_465
	movzx	ecx, word ptr [rsi+0x42]
	mov	dword ptr [rsp+0x38], ecx
	mov	dword ptr [rsp+0x30], 496
	mov	dword ptr [rsp+0x28], 119
	mov	dword ptr [rsp+0x20], ecx
	mov	r9d, ecx
	mov	r8d, 493
	mov	edx, ecx
	lea	rcx, [DS001E+rip]
	call	AddLineQueueX@PLT
$_465:	cmp	byte ptr [rbp-0x46], 0
	jnz	$_466
	mov	rsi, qword ptr [rsi]
	test	rsi, rsi
	jz	$_466
	mov	dword ptr [rbp-0x2C], 0
	lea	r8, [rbp-0x2C]
	mov	edx, 1
	mov	rcx, rsi
	call	$_445
	mov	dword ptr [rbp-0x24], eax
$_466:	mov	rsi, qword ptr [rbp-0x8]
	mov	ebx, dword ptr [rsi+0x24]
	add	ebx, dword ptr [rbp-0x30]
	test	ebx, ebx
	je	$_474
	cmp	byte ptr [Options+0xD1+rip], 0
	jz	$_467
	cmp	ebx, 4096
	jbe	$_467
	mov	edx, ebx
	lea	rcx, [DS001F+rip]
	call	AddLineQueueX@PLT
	jmp	$_468

$_467:	mov	edx, ebx
	lea	rcx, [DS0020+rip]
	call	AddLineQueueX@PLT
$_468:	mov	r8d, ebx
	mov	edx, 490
	lea	rcx, [DS0021+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0x24], 0
	je	$_474
	imul	ecx, dword ptr [rbp-0x24], 16
	mov	eax, dword ptr [rsi+0x24]
	sub	eax, ecx
	and	eax, 0xFFFFFFF0
	mov	dword ptr [rbp-0x4C], eax
	mov	rsi, qword ptr [rsi]
	lodsw
	movzx	ebx, ax
$_469:	test	ebx, ebx
	je	$_474
	movzx	edi, word ptr [rsi]
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	test	byte ptr [r11+rax], 0x10
	je	$_473
	cmp	dword ptr [rbp-0x30], 0
	jz	$_471
	mov	rcx, qword ptr [sym_ReservedStack+rip]
	mov	dword ptr [rsp+0x20], edi
	mov	r9, qword ptr [rcx+0x8]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, 119
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	mov	cl, byte ptr [r11+rax+0xA]
	mov	eax, 1
	shl	eax, cl
	test	ax, 0xFFC0
	jz	$_470
	mov	rcx, qword ptr [sym_ReservedStack+rip]
	mov	rax, qword ptr [rcx+0x8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x4C]
	mov	r8d, edi
	mov	edx, 495
	lea	rcx, [DS0023+rip]
	call	AddLineQueueX@PLT
$_470:	jmp	$_472

$_471:	mov	r9d, edi
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, 119
	lea	rcx, [DS0024+rip]
	call	AddLineQueueX@PLT
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	mov	cl, byte ptr [r11+rax+0xA]
	mov	eax, 1
	shl	eax, cl
	test	ax, 0xFFC0
	jz	$_472
	mov	r9d, dword ptr [rbp-0x4C]
	mov	r8d, edi
	mov	edx, 495
	lea	rcx, [DS0025+rip]
	call	AddLineQueueX@PLT
$_472:	add	dword ptr [rbp-0x4C], 16
$_473:	dec	ebx
	add	rsi, 2
	jmp	$_469

$_474:	mov	edx, 491
	lea	rcx, [DS0024+0x10+rip]
	call	AddLineQueueX@PLT
	jmp	$_517

$_475:	xor	eax, eax
	jmp	$_553

$_476:	mov	rsi, qword ptr [rbp-0x8]
	cmp	byte ptr [rbx+0x1CC], 2
	jne	$_484
	test	byte ptr [rbx+0x1E5], 0x02
	je	$_484
	cmp	byte ptr [rbx+0x1B9], 2
	jz	$_477
	cmp	byte ptr [rbx+0x1B9], 5
	jz	$_477
	cmp	byte ptr [rbx+0x1B9], 3
	jne	$_484
$_477:	mov	rdi, qword ptr [CurrProc+rip]
	mov	rcx, qword ptr [sym_ReservedStack+rip]
	cmp	byte ptr [rdi+0x1A], 2
	jne	$_483
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_483
	test	byte ptr [rsi+0x40], 0x01
	jz	$_478
	add	dword ptr [rcx+0x28], 208
$_478:	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_483
	mov	al, byte ptr [rdi+0x1D]
	add	al, byte ptr [rdi+0x1E]
	test	eax, eax
	jz	$_483
	mov	ebx, 8
	xor	eax, eax
	mov	rdx, qword ptr [rsi+0x8]
$_479:	test	rdx, rdx
	jz	$_481
	test	byte ptr [rdx+0x14], 0x01
	jz	$_480
	test	byte ptr [rdx+0x17], 0x01
	jz	$_480
	inc	eax
	cmp	ebx, dword ptr [rdx+0x50]
	jnc	$_480
	mov	ebx, dword ptr [rdx+0x50]
$_480:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_479

$_481:	test	eax, eax
	jz	$_482
	add	ebx, 7
	and	ebx, 0xFFFFFFF8
	mov	byte ptr [rdi+0x1F], bl
	mul	bl
	mov	edx, 16
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	add	dword ptr [rcx+0x28], eax
	mov	dword ptr [rbp-0x3C], eax
$_482:	lea	rbx, [ModuleInfo+rip]
$_483:	mov	eax, dword ptr [rcx+0x28]
	mov	dword ptr [rbp-0x30], eax
$_484:	test	byte ptr [rsi+0x40], 0x29
	jnz	$_485
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_485
	cmp	dword ptr [rsi+0x24], 0
	jnz	$_485
	cmp	byte ptr [rbp-0x45], 0
	jnz	$_485
	cmp	dword ptr [rbp-0x30], 0
	jnz	$_485
	cmp	qword ptr [rsi], 0
	jnz	$_485
	xor	eax, eax
	jmp	$_553

$_485:	mov	rax, qword ptr [rsi]
	mov	qword ptr [rbp-0x10], rax
	test	byte ptr [rbp-0x47], 0x10
	jz	$_490
	test	byte ptr [rbx+0x1E5], 0x01
	jz	$_486
	mov	rcx, rsi
	call	$_429
	jmp	$_490

$_486:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_490
	cmp	byte ptr [rbx+0x1B9], 5
	jnz	$_490
	xor	eax, eax
	mov	ecx, 16
	mov	rdx, qword ptr [rsi+0x8]
$_487:	test	rdx, rdx
	jz	$_488
	cmp	qword ptr [rdx+0x78], 0
	jz	$_488
	mov	rdx, qword ptr [rdx+0x78]
	inc	eax
	add	ecx, 16
	jmp	$_487

$_488:	mov	rdx, qword ptr [rsi+0x8]
$_489:	test	rdx, rdx
	jz	$_490
	test	eax, eax
	jz	$_490
	mov	dword ptr [rdx+0x28], ecx
	mov	rdx, qword ptr [rdx+0x78]
	dec	eax
	sub	ecx, 16
	jmp	$_489

$_490:	cmp	qword ptr [rbp-0x10], 0
	je	$_497
	cmp	byte ptr [rbp-0x46], 0
	je	$_497
	mov	dword ptr [rbp-0x2C], 0
	lea	r8, [rbp-0x2C]
	xor	edx, edx
	mov	rcx, qword ptr [rbp-0x10]
	call	$_445
	mov	dword ptr [rbp-0x24], eax
	mov	qword ptr [rbp-0x10], 0
	mov	eax, dword ptr [rbp-0x2C]
	add	dword ptr [rbp-0x44], eax
	mov	rdi, qword ptr [rsi+0x8]
$_491:	test	rdi, rdi
	jz	$_492
	cmp	qword ptr [rdi+0x78], 0
	jz	$_492
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_491

$_492:	test	rdi, rdi
	jz	$_497
	movzx	ecx, byte ptr [rbx+0x1CC]
	mov	ecx, dword ptr [rbx+rcx*4+0x224]
	cmp	dword ptr [rdi+0x28], 8
	jnz	$_493
	cmp	ecx, 22
	jz	$_494
$_493:	cmp	dword ptr [rdi+0x28], 16
	jnz	$_497
	cmp	ecx, 120
	jnz	$_497
$_494:	mov	rdi, qword ptr [rsi+0x8]
$_495:	test	rdi, rdi
	jz	$_497
	cmp	byte ptr [rdi+0x18], 10
	jz	$_496
	mov	eax, dword ptr [rbp-0x2C]
	add	dword ptr [rdi+0x28], eax
$_496:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_495

$_497:	cmp	byte ptr [rbp-0x45], 0
	jnz	$_498
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_498
	test	byte ptr [rsi+0x40], 0x29
	jz	$_499
$_498:	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jnz	$_499
	cmp	dword ptr [rbp-0x38], 0
	jz	$_499
	movzx	edx, word ptr [rsi+0x42]
	movzx	ecx, byte ptr [rbx+0x1CC]
	lea	rax, [stackreg+rip]
	mov	ecx, dword ptr [rax+rcx*4]
	mov	r9d, ecx
	mov	r8d, edx
	lea	rcx, [DS0026+rip]
	call	AddLineQueueX@PLT
$_499:	cmp	dword ptr [rbp-0x30], 0
	jnz	$_500
	cmp	dword ptr [rbp-0x34], 0
	jz	$_504
$_500:	cmp	qword ptr [rbp-0x10], 0
	jz	$_501
	lea	r8, [rbp-0x2C]
	xor	edx, edx
	mov	rcx, qword ptr [rbp-0x10]
	call	$_445
	mov	dword ptr [rbp-0x24], eax
	mov	qword ptr [rbp-0x10], 0
$_501:	mov	ecx, dword ptr [rsi+0x24]
	add	ecx, dword ptr [rbp-0x30]
	cmp	byte ptr [Options+0xD1+rip], 0
	jz	$_502
	cmp	ecx, 4096
	jbe	$_502
	mov	edx, ecx
	lea	rcx, [DS001F+rip]
	call	AddLineQueueX@PLT
	jmp	$_503

$_502:	test	ecx, ecx
	jz	$_503
	movzx	eax, byte ptr [rbx+0x1CC]
	lea	rdx, [stackreg+rip]
	mov	edx, dword ptr [rdx+rax*4]
	mov	r8d, ecx
	lea	rcx, [DS0027+rip]
	call	AddLineQueueX@PLT
$_503:	jmp	$_509

$_504:	cmp	dword ptr [rsi+0x24], 0
	je	$_509
	movzx	ecx, byte ptr [rbx+0x1CC]
	lea	rdx, [stackreg+rip]
	mov	eax, dword ptr [rdx+rcx*4]
	mov	dword ptr [rbp-0x40], eax
	cmp	byte ptr [Options+0xD1+rip], 0
	jz	$_506
	cmp	dword ptr [rsi+0x24], 4096
	jbe	$_506
	mov	edx, dword ptr [rsi+0x24]
	lea	rcx, [DS0028+rip]
	call	AddLineQueueX@PLT
	cmp	byte ptr [rbx+0x1CC], 2
	jnz	$_505
	mov	edx, dword ptr [rbp-0x40]
	lea	rcx, [DS0029+rip]
	call	AddLineQueueX@PLT
$_505:	jmp	$_509

$_506:	xor	ecx, ecx
	sub	ecx, dword ptr [rsi+0x24]
	cmp	byte ptr [rbx+0x337], 0
	jnz	$_507
	cmp	dword ptr [rsi+0x24], 128
	jnz	$_508
$_507:	mov	r8d, ecx
	mov	edx, dword ptr [rbp-0x40]
	lea	rcx, [DS002A+rip]
	call	AddLineQueueX@PLT
	jmp	$_509

$_508:	mov	r8d, dword ptr [rsi+0x24]
	mov	edx, dword ptr [rbp-0x40]
	lea	rcx, [DS0027+rip]
	call	AddLineQueueX@PLT
$_509:	test	byte ptr [rsi+0x40], 0x10
	jz	$_511
	mov	ecx, 9
	cmp	byte ptr [rbx+0x1CC], 0
	jz	$_510
	mov	ecx, 17
$_510:	mov	r8d, ecx
	lea	rdx, [szDgroup+rip]
	lea	rcx, [DS002B+rip]
	call	AddLineQueueX@PLT
$_511:	cmp	qword ptr [rbp-0x10], 0
	jz	$_512
	cmp	byte ptr [rbp-0x46], 0
	jnz	$_512
	lea	r8, [rbp-0x2C]
	xor	edx, edx
	mov	rcx, qword ptr [rbp-0x10]
	call	$_445
	mov	dword ptr [rbp-0x24], eax
$_512:	cmp	dword ptr [rbp-0x24], 0
	je	$_517
	cmp	byte ptr [rbx+0x1CC], 2
	jne	$_517
	test	byte ptr [rbx+0x1E5], 0x02
	je	$_517
	imul	ecx, dword ptr [rbp-0x24], 16
	mov	eax, dword ptr [rsi+0x24]
	sub	eax, ecx
	and	eax, 0xFFFFFFF0
	mov	dword ptr [rbp-0x4C], eax
	mov	rsi, qword ptr [rsi]
	lodsw
	movzx	ebx, ax
$_513:	test	ebx, ebx
	jz	$_517
	movzx	edi, word ptr [rsi]
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	test	byte ptr [r11+rax], 0x10
	jz	$_516
	lea	rdx, [ModuleInfo+rip]
	movzx	ecx, byte ptr [rdx+0x1CC]
	lea	rax, [stackreg+rip]
	mov	ecx, dword ptr [rax+rcx*4]
	cmp	dword ptr [rbp-0x30], 0
	jz	$_514
	mov	rdx, qword ptr [sym_ReservedStack+rip]
	mov	dword ptr [rsp+0x20], edi
	mov	r9, qword ptr [rdx+0x8]
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, ecx
	lea	rcx, [DS0022+rip]
	call	AddLineQueueX@PLT
	jmp	$_515

$_514:	mov	r9d, edi
	mov	r8d, dword ptr [rbp-0x4C]
	mov	edx, ecx
	lea	rcx, [DS0024+rip]
	call	AddLineQueueX@PLT
$_515:	add	dword ptr [rbp-0x4C], 16
$_516:	dec	ebx
	add	rsi, 2
	jmp	$_513

$_517:	mov	rdi, qword ptr [CurrProc+rip]
	test	byte ptr [rbp-0x47], 0x20
	je	$_543
	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	je	$_543
	cmp	dword ptr [rbp-0x30], 0
	je	$_528
	cmp	dword ptr [rbp-0x3C], 0
	je	$_528
	cmp	dword ptr [rbp-0x30], 0
	je	$_528
	cmp	qword ptr [rsi], 0
	jz	$_518
	cmp	byte ptr [rbp-0x46], 0
	jnz	$_518
	lea	rdx, [DS002C+rip]
	mov	ecx, 2008
	call	asmerr@PLT
$_518:	mov	eax, dword ptr [rbp-0x3C]
	mov	ecx, dword ptr [rbp-0x30]
	mov	ebx, ecx
	sub	ecx, eax
	sub	ebx, ecx
	add	ebx, dword ptr [rsi+0x24]
	movzx	eax, byte ptr [rdi+0x1F]
	mov	dword ptr [rbp-0x28], eax
	cmp	word ptr [rsi+0x42], 119
	jnz	$_519
	mov	ebx, ecx
	add	ebx, dword ptr [rsi+0x24]
	jmp	$_520

$_519:	neg	ebx
$_520:	mov	rdi, qword ptr [rsi+0x8]
	test	rdi, rdi
	jz	$_521
	test	byte ptr [rsi+0x40], 0x01
	jz	$_521
	mov	rdi, qword ptr [rdi+0x78]
$_521:	test	rdi, rdi
	jz	$_528
	test	byte ptr [rdi+0x17], 0x01
	jz	$_527
	test	byte ptr [rdi+0x14], 0x01
	jz	$_527
	mov	edx, 682
	mov	al, byte ptr [rdi+0x19]
	cmp	al, -60
	jnz	$_522
	mov	rcx, qword ptr [rdi+0x20]
	mov	al, byte ptr [rcx+0x19]
$_522:	test	al, 0x20
	jz	$_526
	mov	edx, 1030
	cmp	al, 35
	jz	$_523
	cmp	dword ptr [rdi+0x50], 4
	jnz	$_524
$_523:	mov	edx, 1050
	jmp	$_526

$_524:	cmp	al, 39
	jz	$_525
	cmp	dword ptr [rdi+0x50], 8
	jnz	$_526
$_525:	mov	edx, 612
$_526:	mov	byte ptr [rdi+0x18], 5
	mov	dword ptr [rdi+0x28], ebx
	movzx	eax, word ptr [rsi+0x42]
	movzx	ecx, byte ptr [rdi+0x48]
	mov	dword ptr [rsp+0x20], ecx
	mov	r9d, ebx
	mov	r8d, eax
	lea	rcx, [DS002D+rip]
	call	AddLineQueueX@PLT
	add	ebx, dword ptr [rbp-0x28]
$_527:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_521

$_528:	test	byte ptr [rsi+0x40], 0x01
	je	$_543
	cmp	qword ptr [rsi], 0
	jz	$_529
	cmp	byte ptr [rbp-0x46], 0
	jnz	$_529
	lea	rdx, [DS002C+rip]
	mov	ecx, 2008
	call	asmerr@PLT
$_529:	mov	eax, dword ptr [rbp-0x3C]
	add	eax, 208
	mov	ecx, dword ptr [rbp-0x30]
	mov	ebx, ecx
	sub	ecx, eax
	sub	ebx, ecx
	add	ebx, dword ptr [rsi+0x24]
	cmp	word ptr [rsi+0x42], 119
	jnz	$_530
	mov	ebx, ecx
	add	ebx, dword ptr [rsi+0x24]
	jmp	$_531

$_530:	neg	ebx
$_531:	mov	dword ptr [rbp-0x2C], ebx
	mov	rdi, qword ptr [rsi+0x8]
	test	rdi, rdi
	jz	$_532
	mov	dword ptr [rdi+0x28], ebx
	mov	rdi, qword ptr [rdi+0x78]
$_532:	xor	ebx, ebx
	mov	dword ptr [rbp-0x28], 0
$_533:	test	rdi, rdi
	jz	$_536
	test	byte ptr [rdi+0x19], 0x20
	jz	$_534
	inc	dword ptr [rbp-0x28]
	jmp	$_535

$_534:	inc	ebx
$_535:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_533

$_536:	movzx	edi, word ptr [rsi+0x42]
	imul	ecx, dword ptr [rbp-0x28], 16
	mov	dword ptr [rsp+0x30], ecx
	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x28], eax
	mov	dword ptr [rsp+0x20], edi
	lea	r9, [rbx*8]
	mov	r8d, dword ptr [rbp-0x2C]
	mov	edx, edi
	lea	rcx, [DS002E+rip]
	call	AddLineQueueX@PLT
$_537:	cmp	ebx, 6
	jnc	$_538
	lea	rcx, [sysv_regs+0x18+rip]
	movzx	ecx, byte ptr [rcx+rbx]
	lea	edx, [rbx*8+0x20]
	mov	dword ptr [rsp+0x20], ecx
	mov	r9d, dword ptr [rbp-0x2C]
	mov	r8d, edx
	mov	edx, edi
	lea	rcx, [DS002F+rip]
	call	AddLineQueueX@PLT
	inc	ebx
	jmp	$_537

$_538:	lea	rcx, [DS0030+rip]
	call	AddLineQueue@PLT
	mov	ebx, dword ptr [rbp-0x28]
	imul	edi, ebx, 16
	add	edi, 80
$_539:	cmp	ebx, 8
	jnc	$_540
	movzx	ecx, word ptr [rsi+0x42]
	lea	rax, [rbx+0x28]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x2C]
	mov	r8d, edi
	mov	edx, ecx
	lea	rcx, [DS0031+rip]
	call	AddLineQueueX@PLT
	inc	ebx
	add	edi, 16
	jmp	$_539

$_540:	lea	rcx, [DS0032+rip]
	call	AddLineQueue@PLT
	movzx	edi, word ptr [rsi+0x42]
	cmp	byte ptr [Options+0xD1+rip], 0
	jz	$_541
	mov	r8d, dword ptr [rbp-0x2C]
	mov	edx, edi
	lea	rcx, [DS0033+rip]
	call	AddLineQueueX@PLT
$_541:	mov	ecx, dword ptr [rbp-0x44]
	cmp	edi, 119
	jnz	$_542
	add	ecx, dword ptr [rbp-0x2C]
$_542:	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x50], eax
	mov	dword ptr [rsp+0x48], edi
	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x40], eax
	mov	dword ptr [rsp+0x38], edi
	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x30], eax
	mov	dword ptr [rsp+0x28], edi
	mov	eax, dword ptr [rbp-0x2C]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, edi
	mov	r8d, ecx
	mov	edx, edi
	lea	rcx, [DS0034+rip]
	call	AddLineQueueX@PLT
$_543:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_547
	cmp	dword ptr [UseSavedState+rip], 0
	jz	$_547
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_544
	cmp	byte ptr [Options+0xA1+rip], 0
	jnz	$_545
$_544:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_546
$_545:	mov	eax, dword ptr [list_pos+rip]
	mov	dword ptr [rsi+0x3C], eax
	jmp	$_547

$_546:	mov	eax, dword ptr [rsi+0x3C]
	mov	dword ptr [list_pos+rip], eax
$_547:	mov	al, byte ptr [Options+0x1+rip]
	mov	byte ptr [rbp-0x11], al
	mov	byte ptr [Options+0x1+rip], 0
	call	RunLineQueue@PLT
	mov	al, byte ptr [rbp-0x11]
	mov	byte ptr [Options+0x1+rip], al
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	je	$_552
	cmp	dword ptr [UseSavedState+rip], 0
	je	$_552
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_552
	mov	rcx, qword ptr [LineStoreCurr+rip]
	mov	ebx, dword ptr [rcx+0x1C]
	mov	eax, dword ptr [list_pos+rip]
	mov	dword ptr [rcx+0x1C], eax
	cmp	ebx, dword ptr [list_pos+rip]
	jbe	$_552
	cmp	byte ptr [Options+0xA1+rip], 0
	jnz	$_552
	mov	rcx, qword ptr [rcx]
	test	rcx, rcx
	jz	$_548
	cmp	dword ptr [rcx+0x1C], ebx
	jbe	$_548
	mov	ebx, dword ptr [rcx+0x1C]
$_548:	sub	ebx, dword ptr [list_pos+rip]
	test	ebx, ebx
	jz	$_549
	dec	ebx
$_549:	jmp	$_551

$_550:	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, 8
	mov	esi, 1
	lea	rdi, [DS0035+rip]
	call	fwrite@PLT
	sub	ebx, 8
$_551:	cmp	ebx, 8
	jnc	$_550
	test	ebx, ebx
	jz	$_552
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, ebx
	mov	esi, 1
	lea	rdi, [DS0035+rip]
	call	fwrite@PLT
$_552:	xor	eax, eax
$_553:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SetLocalOffsets:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	dword ptr [rbp-0xC], 0
	mov	dword ptr [rbp-0x10], 0
	mov	dword ptr [rbp-0x14], 0
	mov	dword ptr [rbp-0x18], 0
	mov	dword ptr [rbp-0x1C], 0
	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	mov	dword ptr [rbp-0x20], eax
	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	mov	dword ptr [rbp-0x24], eax
	mov	byte ptr [rbp-0x25], 0
	mov	rdi, qword ptr [CurrProc+rip]
	lea	rbx, [ModuleInfo+rip]
	movzx	edx, byte ptr [rdi+0x1A]
	movzx	ecx, byte ptr [rdi+0x1B]
	call	get_fasttype
	test	byte ptr [rax+0xF], 0x40
	jz	$_554
	test	byte ptr [rbx+0x334], 0x01
	jz	$_554
	inc	byte ptr [rbp-0x25]
$_554:	cmp	byte ptr [rbx+0x1B9], 5
	jnz	$_555
	mov	dword ptr [rbp-0x24], 16
$_555:	mov	rsi, qword ptr [rbp+0x28]
	test	byte ptr [rsi+0x40], 0x40
	jnz	$_556
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_558
	cmp	byte ptr [rbx+0x1B9], 2
	jz	$_556
	cmp	byte ptr [rbx+0x1B9], 5
	jz	$_556
	cmp	byte ptr [rbx+0x1B9], 3
	jnz	$_558
$_556:	mov	dword ptr [rbp-0x1C], 1
	test	byte ptr [rbx+0x1E5], 0x04
	jnz	$_557
	cmp	byte ptr [rbx+0x1B9], 5
	jnz	$_558
$_557:	mov	dword ptr [rbp-0x20], 16
$_558:	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jnz	$_559
	cmp	dword ptr [rbp-0x1C], 0
	je	$_567
$_559:	cmp	qword ptr [rsi], 0
	jz	$_563
	mov	rdi, qword ptr [rsi]
	movzx	ebx, word ptr [rdi]
	add	rdi, 2
$_560:	test	ebx, ebx
	jz	$_563
	movzx	edx, word ptr [rdi]
	lea	r11, [SpecialTable+rip]
	imul	eax, edx, 12
	test	byte ptr [r11+rax], 0x10
	jz	$_561
	inc	dword ptr [rbp-0xC]
	jmp	$_562

$_561:	inc	dword ptr [rbp-0x10]
$_562:	dec	ebx
	add	rdi, 2
	jmp	$_560

$_563:	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jnz	$_565
	cmp	byte ptr [rdi+0x1A], 9
	jnz	$_564
	cmp	dword ptr [rsi+0x20], 32
	ja	$_564
	cmp	qword ptr [rsi+0x10], 0
	jz	$_565
$_564:	cmp	dword ptr [rsi+0x20], 0
	jnz	$_566
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_566
$_565:	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	mov	dword ptr [rbp-0x14], eax
$_566:	cmp	dword ptr [rbp-0x1C], 0
	jz	$_567
	mov	eax, dword ptr [rbp-0x10]
	mul	dword ptr [rbp-0x24]
	add	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rsi+0x24], eax
	cmp	dword ptr [rbp-0xC], 0
	jz	$_567
	imul	eax, dword ptr [rbp-0xC], 16
	add	eax, dword ptr [rsi+0x24]
	mov	edx, 16
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	mov	dword ptr [rsi+0x24], eax
$_567:	cmp	dword ptr [rbp-0xC], 0
	jz	$_568
	mov	rcx, qword ptr [CurrProc+rip]
	or	byte ptr [rcx+0x3B], 0x40
$_568:	lea	rdx, [ModuleInfo+rip]
	movzx	ecx, byte ptr [rdx+0x1CC]
	mov	ebx, dword ptr [rdx+rcx*4+0x224]
	imul	ecx, dword ptr [rbp-0xC], 16
	mov	eax, dword ptr [rbp-0x24]
	mul	dword ptr [rbp-0x10]
	add	eax, ecx
	test	eax, eax
	jz	$_572
	cmp	byte ptr [rbp-0x25], 0
	jz	$_572
	cmp	dword ptr [rbp-0x20], 16
	jnz	$_569
	cmp	ebx, 119
	jnz	$_569
	mov	edx, 16
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
$_569:	cmp	ebx, 22
	jz	$_570
	cmp	ebx, 120
	jnz	$_571
$_570:	mov	dword ptr [rbp-0x18], eax
	jmp	$_572

$_571:	cmp	ebx, 21
	jnz	$_572
	neg	eax
	mov	dword ptr [rbp-0x18], eax
$_572:	mov	rdi, qword ptr [rsi+0x10]
$_573:	test	rdi, rdi
	jz	$_577
	xor	eax, eax
	cmp	dword ptr [rdi+0x50], 0
	jz	$_574
	mov	eax, dword ptr [rdi+0x50]
	cdq
	div	dword ptr [rdi+0x58]
$_574:	mov	ecx, eax
	mov	eax, dword ptr [rdi+0x50]
	add	dword ptr [rsi+0x24], eax
	cmp	ecx, dword ptr [rbp-0x20]
	jle	$_575
	mov	edx, dword ptr [rbp-0x20]
	mov	eax, dword ptr [rsi+0x24]
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	mov	dword ptr [rsi+0x24], eax
	jmp	$_576

$_575:	test	ecx, ecx
	jz	$_576
	mov	edx, ecx
	mov	eax, dword ptr [rsi+0x24]
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	mov	dword ptr [rsi+0x24], eax
$_576:	mov	eax, dword ptr [rsi+0x24]
	neg	eax
	add	eax, dword ptr [rbp-0x18]
	mov	dword ptr [rdi+0x28], eax
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_573

$_577:
	mov	edx, dword ptr [rbp-0x24]
	mov	eax, dword ptr [rsi+0x24]
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	mov	dword ptr [rsi+0x24], eax
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_578
	mov	edx, 16
	mov	eax, dword ptr [rsi+0x24]
	dec	edx
	add	eax, edx
	not	edx
	and	eax, edx
	mov	dword ptr [rsi+0x24], eax
$_578:	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jz	$_585
	movzx	edi, byte ptr [ModuleInfo+0x1CE+rip]
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_579
	mov	ecx, dword ptr [rsi+0x24]
	mov	ebx, ecx
	sub	ebx, edi
	sub	ebx, dword ptr [rbp-0x14]
	jmp	$_580

$_579:	mov	eax, dword ptr [rbp-0x10]
	mul	edi
	mov	ecx, dword ptr [rsi+0x24]
	add	ecx, eax
	mov	ebx, ecx
	sub	ebx, edi
$_580:	mov	rdi, qword ptr [rsi+0x10]
$_581:	test	rdi, rdi
	jz	$_582
	add	dword ptr [rdi+0x28], ecx
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_581

$_582:	mov	rdi, qword ptr [rsi+0x8]
$_583:	test	rdi, rdi
	jz	$_585
	cmp	byte ptr [rdi+0x18], 10
	jz	$_584
	add	dword ptr [rdi+0x28], ebx
$_584:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_583

$_585:
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_586
	mov	eax, dword ptr [rbp-0x10]
	mul	dword ptr [rbp-0x24]
	add	eax, dword ptr [rbp-0x14]
	sub	dword ptr [rsi+0x24], eax
$_586:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

write_prologue:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rdi+0x68]
	lea	rbx, [ModuleInfo+rip]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_587
	and	byte ptr [rdi+0x3B], 0xFFFFFF8F
$_587:	and	dword ptr [ProcStatus+rip], 0xFFFFFF7F
	cmp	byte ptr [rbx+0x353], 0
	jz	$_589
	cmp	byte ptr [rbx+0x1EF], 2
	jz	$_589
	cmp	byte ptr [rbx+0x1B6], 2
	jnz	$_589
	cmp	byte ptr [rbx+0x1CC], 2
	jnz	$_588
	lea	rcx, [DS0036+rip]
	call	AddLineQueue@PLT
	jmp	$_589

$_588:	cmp	byte ptr [rbx+0x1CC], 1
	jnz	$_589
	lea	rcx, [DS0037+rip]
	call	AddLineQueue@PLT
$_589:	test	byte ptr [rbx+0x1E5], 0x02
	je	$_599
	cmp	byte ptr [rbx+0x1B9], 2
	jz	$_590
	cmp	byte ptr [rbx+0x1B9], 5
	jz	$_590
	cmp	byte ptr [rbx+0x1B9], 3
	jnz	$_599
$_590:	mov	rcx, qword ptr [sym_ReservedStack+rip]
	movzx	edx, byte ptr [rdi+0x1A]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_598
	mov	dword ptr [rcx+0x28], 32
	cmp	dl, 8
	jnz	$_591
	mov	dword ptr [rcx+0x28], 96
	jmp	$_597

$_591:	cmp	dl, 2
	jnz	$_597
	mov	dword ptr [rcx+0x28], 0
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_597
	xor	ecx, ecx
	mov	rdx, qword ptr [rsi+0x8]
$_592:	test	rdx, rdx
	jz	$_594
	test	byte ptr [rdx+0x17], 0x01
	jz	$_593
	add	ecx, 8
$_593:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_592

$_594:	mov	rdx, qword ptr [rsi+0x8]
$_595:	test	rdx, rdx
	jz	$_597
	test	byte ptr [rdx+0x17], 0x01
	jnz	$_596
	sub	dword ptr [rdx+0x28], ecx
$_596:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_595

$_597:	jmp	$_599

$_598:	mov	eax, dword ptr [rsi+0x38]
	mov	dword ptr [rcx+0x28], eax
$_599:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_600
	mov	rcx, rsi
	call	SetLocalOffsets
$_600:	or	byte ptr [ProcStatus+rip], 0x01
	cmp	byte ptr [rbx+0x1EF], 0
	jnz	$_601
	call	$_450
	jmp	$_603

$_601:	cmp	byte ptr [rbx+0x1EF], 2
	jnz	$_602
	jmp	$_603

$_602:	mov	rcx, qword ptr [rbp+0x28]
	call	$_385
$_603:	and	dword ptr [ProcStatus+rip], 0xFFFFFFFE
	call	GetCurrOffset@PLT
	mov	ecx, eax
	sub	ecx, dword ptr [rdi+0x28]
	mov	byte ptr [rsi+0x41], cl
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_604:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	test	rsi, rsi
	jz	$_607
	movzx	edi, word ptr [rsi]
	lea	rsi, [rsi+rdi*2]
$_605:	test	edi, edi
	jz	$_607
	movzx	ecx, word ptr [rsi]
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	test	byte ptr [r11+rax], 0x10
	jnz	$_606
	mov	edx, ecx
	lea	rcx, [DS0038+rip]
	call	AddLineQueueX@PLT
$_606:	dec	edi
	sub	rsi, 2
	jmp	$_605

$_607:
	leave
	pop	rdi
	pop	rsi
	ret

$_608:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	dword ptr [rbp-0x18], edi
	cmp	qword ptr [rsi], 0
	je	$_616
	mov	rdi, qword ptr [rsi]
	movzx	ebx, word ptr [rdi]
	add	rdi, 2
	xor	ecx, ecx
$_609:	test	ebx, ebx
	jz	$_611
	movzx	eax, word ptr [rdi]
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	test	byte ptr [r11+rax], 0x10
	jz	$_610
	inc	ecx
$_610:	dec	ebx
	add	rdi, 2
	jmp	$_609

$_611:	test	ecx, ecx
	je	$_616
	imul	ecx, ecx, 16
	mov	ebx, dword ptr [rsi+0x24]
	sub	ebx, ecx
	and	ebx, 0xFFFFFFF0
	mov	rdi, qword ptr [rsi]
	movzx	esi, word ptr [rdi]
	add	rdi, 2
$_612:	test	esi, esi
	jz	$_616
	movzx	ecx, word ptr [rdi]
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	test	byte ptr [r11+rax], 0x10
	jz	$_615
	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jz	$_613
	mov	rdx, qword ptr [sym_ReservedStack+rip]
	mov	rax, qword ptr [rdx+0x8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, ebx
	mov	r8d, dword ptr [rbp-0x18]
	mov	edx, ecx
	lea	rcx, [DS0039+rip]
	call	AddLineQueueX@PLT
	jmp	$_614

$_613:	mov	r9d, ebx
	mov	r8d, dword ptr [rbp-0x18]
	mov	edx, ecx
	lea	rcx, [DS003A+rip]
	call	AddLineQueueX@PLT
$_614:	add	ebx, 16
$_615:	dec	esi
	add	rdi, 2
	jmp	$_612

$_616:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_617:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	dword ptr [rbp-0xC], 0
	mov	dword ptr [rbp-0x10], 0
	mov	dword ptr [rbp-0x18], 1
	mov	byte ptr [rbp-0x19], 0
	mov	byte ptr [rbp-0x1A], 0
	mov	rdi, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rdi+0x68]
	mov	qword ptr [rbp-0x8], rsi
	lea	rbx, [ModuleInfo+rip]
	movzx	edx, byte ptr [rdi+0x1A]
	movzx	ecx, byte ptr [rdi+0x1B]
	call	get_fasttype
	mov	al, byte ptr [rax+0xF]
	test	al, 0x40
	jz	$_618
	test	byte ptr [rbx+0x334], 0x01
	jz	$_618
	inc	byte ptr [rbp-0x1A]
$_618:	test	al, 0x20
	jz	$_619
	cmp	qword ptr [rsi+0x8], 0
	jz	$_619
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_619
	inc	byte ptr [rbp-0x19]
$_619:	test	al, 0x11
	je	$_628
	test	byte ptr [rbx+0x1E5], 0x02
	je	$_628
	test	byte ptr [rsi+0x40], 0x01
	jz	$_620
	or	byte ptr [rdi+0x3B], 0x20
	jmp	$_623

$_620:	mov	rdx, qword ptr [rsi+0x8]
$_621:	test	rdx, rdx
	jz	$_623
	test	byte ptr [rdx+0x14], 0x01
	jz	$_622
	or	byte ptr [rdi+0x3B], 0x20
$_622:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_621

$_623:	test	byte ptr [rdi+0x3B], 0x10
	jnz	$_628
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_628
	mov	rdx, qword ptr [sym_ReservedStack+rip]
	test	rdx, rdx
	jz	$_624
	mov	dword ptr [rdx+0x28], 0
$_624:	test	byte ptr [rdi+0x3B], 0x40
	jnz	$_627
	cmp	dword ptr [rsi+0x24], 8
	jnz	$_627
	mov	dword ptr [rsi+0x24], 0
	cmp	dword ptr [rbx+0x22C], 119
	jnz	$_627
	mov	rdx, qword ptr [rsi+0x8]
$_625:	test	rdx, rdx
	jz	$_627
	cmp	byte ptr [rdx+0x18], 10
	jz	$_626
	sub	dword ptr [rdx+0x28], 8
$_626:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_625

$_627:	test	byte ptr [rdi+0x3B], 0x60
	jnz	$_628
	cmp	dword ptr [rsi+0x24], 0
	jnz	$_628
	cmp	qword ptr [rsi], 0
	jnz	$_628
	mov	dword ptr [rbp-0x18], 0
$_628:	cmp	qword ptr [rsi+0x10], 0
	jnz	$_629
	cmp	byte ptr [rbp-0x19], 0
	jnz	$_629
	test	byte ptr [rsi+0x40], 0x29
	jz	$_630
$_629:	inc	dword ptr [rbp-0xC]
$_630:	movzx	ecx, byte ptr [rbx+0x1CC]
	lea	rdx, [stackreg+rip]
	mov	eax, dword ptr [rdx+rcx*4]
	mov	dword ptr [rbp-0x14], eax
	test	byte ptr [rsi+0x40], 0x40
	je	$_647
	test	byte ptr [rbx+0x1E1], 0x01
	je	$_646
	mov	edi, dword ptr [rbp-0x14]
	call	$_608
	cmp	dword ptr [rbp-0xC], 0
	je	$_638
	test	byte ptr [rsi+0x40], 0x02
	jz	$_638
	cmp	byte ptr [rbp-0x1A], 0
	jnz	$_632
	cmp	byte ptr [rbp-0x19], 0
	jnz	$_631
	cmp	qword ptr [rsi], 0
	jnz	$_638
$_631:	cmp	word ptr [rsi+0x42], 120
	jnz	$_638
$_632:	cmp	byte ptr [rbp-0x1A], 0
	jnz	$_633
	mov	rcx, qword ptr [rsi]
	call	$_604
$_633:	cmp	byte ptr [rbp-0x19], 0
	jnz	$_635
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_635
	test	byte ptr [rsi+0x40], 0x29
	jnz	$_635
	cmp	dword ptr [rbp-0x10], 0
	jnz	$_635
	cmp	byte ptr [rbp-0x1A], 0
	jz	$_634
	mov	rcx, qword ptr [rsi]
	call	$_604
$_634:	jmp	$_667

$_635:	cmp	dword ptr [rbp-0x18], 0
	jz	$_636
	lea	rcx, [DS003B+rip]
	call	AddLineQueue@PLT
$_636:	cmp	byte ptr [rbp-0x1A], 0
	jz	$_637
	mov	rcx, qword ptr [rsi]
	call	$_604
$_637:	jmp	$_646

$_638:	mov	ebx, dword ptr [rbp-0x14]
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 2
	jz	$_639
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 5
	jnz	$_641
$_639:	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jz	$_641
	mov	rdx, qword ptr [sym_ReservedStack+rip]
	mov	edx, dword ptr [rdx+0x28]
	add	edx, dword ptr [rsi+0x24]
	jz	$_640
	mov	r8d, edx
	mov	edx, ebx
	lea	rcx, [DS002A+rip]
	call	AddLineQueueX@PLT
$_640:	jmp	$_642

$_641:	cmp	dword ptr [rsi+0x24], 0
	jz	$_642
	mov	r8d, dword ptr [rsi+0x24]
	mov	edx, ebx
	lea	rcx, [DS002A+rip]
	call	AddLineQueueX@PLT
$_642:	cmp	byte ptr [rbp-0x1A], 0
	jnz	$_643
	mov	rcx, qword ptr [rsi]
	call	$_604
$_643:	movzx	ecx, word ptr [rsi+0x42]
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	cmp	byte ptr [r11+rax+0xA], 4
	jz	$_645
	cmp	dword ptr [rsi+0x20], 0
	jnz	$_644
	cmp	qword ptr [rsi+0x10], 0
	jz	$_645
$_644:	mov	edx, ecx
	lea	rcx, [DS0038+rip]
	call	AddLineQueueX@PLT
$_645:	cmp	byte ptr [rbp-0x1A], 0
	jz	$_646
	mov	rcx, qword ptr [rsi]
	call	$_604
$_646:	jmp	$_667

$_647:	cmp	byte ptr [rbx+0x1CC], 2
	jnz	$_648
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_648
	mov	edi, dword ptr [rbp-0x14]
	call	$_608
$_648:	cmp	byte ptr [rbx+0x1CC], 2
	jne	$_654
	cmp	byte ptr [rbx+0x1B9], 2
	jz	$_649
	cmp	byte ptr [rbx+0x1B9], 5
	jz	$_649
	cmp	byte ptr [rbx+0x1B9], 3
	jne	$_654
$_649:	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_654
	mov	rcx, qword ptr [sym_ReservedStack+rip]
	mov	eax, dword ptr [rcx+0x28]
	mov	dword ptr [rbp-0x10], eax
	cmp	byte ptr [rbp-0x1A], 0
	jz	$_650
	cmp	dword ptr [rbp-0xC], 0
	jz	$_650
	test	byte ptr [rsi+0x40], 0x02
	jz	$_650
	jmp	$_654

$_650:	cmp	byte ptr [rbp-0x1A], 0
	jnz	$_652
	cmp	dword ptr [rbp-0xC], 0
	jz	$_652
	test	byte ptr [rsi+0x40], 0x02
	jz	$_652
	cmp	byte ptr [rbp-0x19], 0
	jnz	$_651
	cmp	qword ptr [rsi], 0
	jnz	$_652
$_651:	cmp	word ptr [rsi+0x42], 120
	jnz	$_652
	jmp	$_654

$_652:	cmp	dword ptr [rbp-0x10], 0
	jnz	$_653
	cmp	dword ptr [rsi+0x24], 0
	jz	$_654
$_653:	mov	ecx, dword ptr [rbp-0x14]
	mov	rdx, qword ptr [sym_ReservedStack+rip]
	mov	r9, qword ptr [rdx+0x8]
	mov	r8d, dword ptr [rsi+0x24]
	mov	edx, ecx
	lea	rcx, [DS003C+rip]
	call	AddLineQueueX@PLT
$_654:	cmp	byte ptr [rbp-0x1A], 0
	jnz	$_655
	mov	rcx, qword ptr [rsi]
	call	$_604
	test	byte ptr [rsi+0x40], 0x10
	jz	$_655
	lea	rcx, [DS003D+rip]
	call	AddLineQueue@PLT
$_655:	cmp	byte ptr [rbp-0x19], 0
	jnz	$_657
	cmp	qword ptr [rsi+0x10], 0
	jnz	$_657
	test	byte ptr [rsi+0x40], 0x29
	jnz	$_657
	cmp	dword ptr [rbp-0x10], 0
	jnz	$_657
	cmp	byte ptr [rbp-0x1A], 0
	jz	$_656
	mov	rcx, qword ptr [rsi]
	call	$_604
	test	byte ptr [rsi+0x40], 0x10
	jz	$_656
	lea	rcx, [DS003D+rip]
	call	AddLineQueue@PLT
$_656:	jmp	$_667

$_657:	cmp	dword ptr [rbp-0xC], 0
	jnz	$_658
	jmp	$_666

$_658:	test	byte ptr [rsi+0x40], 0x02
	jz	$_660
	cmp	dword ptr [rbp-0x18], 0
	jz	$_659
	lea	rcx, [DS003B+rip]
	call	AddLineQueue@PLT
$_659:	jmp	$_666

$_660:	test	byte ptr [rsi+0x40], 0xFFFFFF80
	jz	$_664
	cmp	byte ptr [rbx+0x1CC], 2
	jnz	$_662
	test	byte ptr [rbx+0x1E5], 0x02
	jz	$_662
	cmp	byte ptr [rbx+0x1B9], 2
	jz	$_661
	cmp	byte ptr [rbx+0x1B9], 5
	jz	$_661
	cmp	byte ptr [rbx+0x1B9], 3
	jnz	$_662
$_661:	jmp	$_663

$_662:	cmp	dword ptr [rsi+0x24], 0
	jz	$_663
	mov	r8d, dword ptr [rsi+0x24]
	mov	edx, dword ptr [rbp-0x14]
	lea	rcx, [DS002A+rip]
	call	AddLineQueueX@PLT
$_663:	jmp	$_666

$_664:	cmp	dword ptr [rbp-0x18], 0
	jz	$_666
	cmp	dword ptr [rsi+0x24], 0
	jz	$_665
	movzx	r8d, word ptr [rsi+0x42]
	mov	edx, dword ptr [rbp-0x14]
	lea	rcx, [DS0026+0x8+rip]
	call	AddLineQueueX@PLT
$_665:	movzx	edx, word ptr [rsi+0x42]
	lea	rcx, [DS0038+rip]
	call	AddLineQueueX@PLT
$_666:	cmp	byte ptr [rbp-0x1A], 0
	jz	$_667
	mov	rcx, qword ptr [rsi]
	call	$_604
	test	byte ptr [rsi+0x40], 0x10
	jz	$_667
	lea	rcx, [DS003D+rip]
	call	AddLineQueue@PLT
$_667:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_668:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2296
	mov	rdi, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rdi+0x68]
	mov	qword ptr [rbp-0x28], rsi
	mov	rcx, qword ptr [ModuleInfo+0x198+rip]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x38], rax
	test	eax, eax
	jz	$_669
	cmp	byte ptr [rax+0x18], 9
	jnz	$_669
	test	byte ptr [rax+0x38], 0x02
	jz	$_670
$_669:	mov	rdx, qword ptr [ModuleInfo+0x198+rip]
	mov	ecx, 2121
	call	asmerr@PLT
	jmp	$_683

$_670:	movzx	ebx, byte ptr [rdi+0x1A]
	mov	edx, ebx
	cmp	ebx, 7
	jnz	$_671
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 2
	jnz	$_671
	mov	edx, 0
$_671:	cmp	ebx, 1
	jz	$_672
	cmp	ebx, 2
	jz	$_672
	cmp	ebx, 7
	jnz	$_673
$_672:	or	edx, 0x10
$_673:	cmp	byte ptr [rdi+0x19], -126
	jnz	$_674
	or	edx, 0x20
$_674:	test	dword ptr [rdi+0x14], 0x80
	jnz	$_675
	or	edx, 0x40
$_675:	test	byte ptr [rsi+0x40], 0x04
	jz	$_676
	or	edx, 0x80
$_676:	cmp	dword ptr [rbp+0x28], 0
	jz	$_677
	or	edx, 0x100
$_677:	mov	dword ptr [rbp-0x2C], edx
	mov	rdi, qword ptr [rsi]
	lea	rsi, [rbp-0xB8]
	test	rdi, rdi
	jz	$_680
	movzx	ebx, word ptr [rdi]
	lea	rdi, [rdi+rbx*2]
$_678:	test	ebx, ebx
	jz	$_680
	movzx	ecx, word ptr [rdi]
	mov	rdx, rsi
	call	GetResWName@PLT
	mov	rcx, rsi
	call	tstrlen@PLT
	add	rsi, rax
	cmp	ebx, 1
	jz	$_679
	mov	byte ptr [rsi], 44
	inc	rsi
$_679:	sub	rdi, 2
	dec	ebx
	jmp	$_678

$_680:	mov	byte ptr [rsi], 0
	mov	rsi, qword ptr [rbp-0x28]
	mov	rdi, qword ptr [CurrProc+rip]
	lea	rcx, [DS003D+0x6+rip]
	cmp	qword ptr [rsi+0x28], 0
	jz	$_681
	mov	rcx, qword ptr [rsi+0x28]
$_681:	mov	qword ptr [rsp+0x38], rcx
	lea	rax, [rbp-0xB8]
	mov	qword ptr [rsp+0x30], rax
	mov	eax, dword ptr [rsi+0x24]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rsi+0x20]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x2C]
	mov	r8, qword ptr [rdi+0x8]
	lea	rdx, [DS003E+rip]
	lea	rcx, [rbp-0x8B8]
	call	tsprintf@PLT
	mov	ecx, dword ptr [ModuleInfo+0x220+rip]
	inc	ecx
	mov	dword ptr [rbp-0xC], ecx
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp-0xC]
	lea	rcx, [rbp-0x8B8]
	call	Tokenize@PLT
	cmp	byte ptr [Options+0x96+rip], 0
	jz	$_682
	lea	rcx, [DS003F+rip]
	call	tprintf@PLT
$_682:	lea	rax, [rbp-0x1C]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 0
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp-0x38]
	call	RunMacro@PLT
	mov	eax, dword ptr [rbp-0xC]
	dec	eax
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	xor	eax, eax
$_683:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

RetInstr:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2104
	mov	dword ptr [rbp-0x814], 0
	lea	rdi, [ModuleInfo+rip]
	imul	ebx, ecx, 24
	add	rbx, rdx
	mov	eax, dword ptr [rbx+0x4]
	cmp	eax, 704
	jz	$_684
	cmp	eax, 705
	jz	$_684
	cmp	eax, 1201
	jnz	$_685
$_684:	mov	dword ptr [rbp-0x814], 1
	jmp	$_686

$_685:	cmp	eax, 726
	jnz	$_686
	cmp	qword ptr [rdi+0x110], 0
	jz	$_686
	mov	rcx, qword ptr [rdi+0x110]
	mov	ecx, dword ptr [rcx+0x14]
	lea	rdx, [rbp-0x810]
	call	GetLabelStr@PLT
	lea	r8, [DS0001+rip]
	mov	rdx, rax
	lea	rcx, [DS0040+rip]
	call	AddLineQueueX@PLT
	mov	qword ptr [rdi+0x110], 0
$_686:	cmp	byte ptr [rdi+0x1F0], 1
	jnz	$_689
	cmp	dword ptr [UseSavedState+rip], 0
	jz	$_688
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_687
	mov	rcx, qword ptr [rbp+0x30]
	call	ParseLine@PLT
	jmp	$_709

$_687:	mov	rcx, qword ptr [LineStoreCurr+rip]
	mov	byte ptr [rcx+0x20], 59
$_688:	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp-0x814]
	call	$_668
	jmp	$_709

$_689:	cmp	byte ptr [rdi+0x1DB], 0
	jz	$_690
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_690:	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [rbp-0x810]
	call	tstrcpy@PLT
	mov	rdi, rax
	mov	rcx, rax
	call	tstrlen@PLT
	add	rdi, rax
	call	$_617
	mov	rcx, qword ptr [CurrProc+rip]
	mov	rsi, qword ptr [rcx+0x68]
	cmp	dword ptr [rbp-0x814], 0
	jnz	$_693
	cmp	byte ptr [rcx+0x19], -126
	jnz	$_691
	mov	al, 102
	jmp	$_692

$_691:	mov	al, 110
$_692:	stosb
$_693:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	edx, dword ptr [rbp+0x38]
	cmp	dword ptr [rsi+0x20], 0
	jnz	$_694
	cmp	edx, dword ptr [rbp+0x28]
	jz	$_695
$_694:	mov	al, 32
	stosb
$_695:	mov	byte ptr [rdi], 0
	cmp	dword ptr [rbp-0x814], 0
	jne	$_707
	cmp	edx, dword ptr [rbp+0x28]
	jne	$_707
	cmp	byte ptr [ModuleInfo+0x1F0+rip], 2
	je	$_706
	movzx	eax, byte ptr [rcx+0x1A]
	jmp	$_705

$_696:	test	byte ptr [rsi+0x40], 0x01
	jne	$_706
$_697:	cmp	dword ptr [rsi+0x20], 0
	jz	$_698
	mov	r8d, dword ptr [rsi+0x20]
	lea	rdx, [DS002E+0x36+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
$_698:	jmp	$_706

$_699:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jne	$_706
	test	byte ptr [rsi+0x40], 0x01
	jne	$_706
$_700:	mov	ebx, eax
	call	GetSymOfssize@PLT
	mov	ecx, eax
	mov	eax, 2
	shl	eax, cl
	mov	dword ptr [rbp-0x818], eax
	mov	edx, ebx
	call	get_fasttype
	test	byte ptr [rax+0xF], 0x02
	jz	$_704
	xor	ecx, ecx
	mov	rdx, qword ptr [rsi+0x8]
$_701:	test	rdx, rdx
	jz	$_703
	cmp	byte ptr [rdx+0x18], 10
	jz	$_702
	add	ecx, dword ptr [rdx+0x50]
	mov	eax, dword ptr [rbp-0x818]
	dec	eax
	add	ecx, eax
	not	eax
	and	ecx, eax
$_702:	mov	rdx, qword ptr [rdx+0x78]
	jmp	$_701

$_703:	test	ecx, ecx
	jz	$_704
	mov	r8d, ecx
	lea	rdx, [DS002E+0x36+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
$_704:	jmp	$_706

$_705:	cmp	eax, 3
	je	$_696
	cmp	eax, 6
	je	$_697
	cmp	eax, 5
	je	$_697
	cmp	eax, 4
	je	$_697
	cmp	eax, 9
	je	$_699
	cmp	eax, 7
	je	$_700
	cmp	eax, 8
	je	$_700
$_706:	jmp	$_708

$_707:	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rdi
	call	tstrcpy@PLT
$_708:	lea	rcx, [rbp-0x810]
	call	AddLineQueue@PLT
	call	RunLineQueue@PLT
	xor	eax, eax
$_709:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ProcInit:
	xor	eax, eax
	mov	qword ptr [ProcStack+rip], rax
	mov	qword ptr [CurrProc+rip], rax
	mov	byte ptr [strFUNC+rip], al
	mov	dword ptr [procidx+rip], 1
	mov	dword ptr [ProcStatus+rip], eax
	lea	rcx, [ModuleInfo+rip]
	mov	byte ptr [rcx+0x1EF], 0
	mov	byte ptr [rcx+0x1F0], 0
	cmp	byte ptr [Options+0xC6+rip], 0
	jz	$_710
	mov	al, 2
$_710:	mov	byte ptr [rcx+0x1F1], al
	mov	dword ptr [rcx+0x224], 14
	mov	dword ptr [rcx+0x228], 22
	mov	dword ptr [rcx+0x22C], 120
	mov	byte ptr [unw_segs_defined+rip], 0
	ret


.SECTION .data
	.ALIGN	16

CurrProc:
	.quad  0x0000000000000000

ProcStack:
	.quad  0x0000000000000000

sym_ReservedStack:
	.quad  0x0000000000000000

procidx: .int	0x00000000

ProcStatus:
	.int   0x00000000

endprolog_found:
	.int   0x00000000

stackreg:
	.byte  0x0D, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00
	.byte  0x77, 0x00, 0x00, 0x00

StackAdj: .int	 0x00000000

StackAdjHigh:
	.int   0x00000000

fast_regs:
	.byte  0x02, 0x03, 0x5B, 0x5C, 0x00, 0x00, 0x00, 0x00
	.byte  0x0A, 0x0B, 0x63, 0x64, 0x00, 0x00, 0x00, 0x00
	.byte  0x12, 0x13, 0x6B, 0x6C, 0x00, 0x00, 0x00, 0x00
	.byte  0x74, 0x75, 0x7B, 0x7C, 0x00, 0x00, 0x00, 0x00

sysv_regs:
	.byte  0x5A, 0x59, 0x03, 0x02, 0x5B, 0x5C, 0x00, 0x00
	.byte  0x10, 0x0F, 0x0B, 0x0A, 0x63, 0x64, 0x00, 0x00
	.byte  0x18, 0x17, 0x13, 0x12, 0x6B, 0x6C, 0x00, 0x00
	.byte  0x7A, 0x79, 0x75, 0x74, 0x7B, 0x7C, 0x00, 0x00

watc_regs:
	.byte  0x01, 0x03, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte  0x09, 0x0B, 0x0C, 0x0A, 0x00, 0x00, 0x00, 0x00
	.byte  0x11, 0x13, 0x14, 0x12, 0x00, 0x00, 0x00, 0x00
	.byte  0x73, 0x75, 0x76, 0x74, 0x00, 0x00, 0x00, 0x00

user_regs:
	.byte  0x01, 0x03, 0x02, 0x5B, 0x5C, 0x5D, 0x5E, 0x00
	.byte  0x09, 0x0B, 0x0A, 0x63, 0x64, 0x65, 0x66, 0x00
	.byte  0x11, 0x13, 0x12, 0x6B, 0x6C, 0x6D, 0x6E, 0x00
	.byte  0x73, 0x75, 0x74, 0x7B, 0x7C, 0x7D, 0x7E, 0x00

lang_table:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40
	.quad  sysv_regs
	.quad  0x6810080600FF03C6
	.quad  0x0000000000000000
	.quad  0x0200000000000000
	.quad  0x0000000000000000
	.quad  0x4200000000000000
	.quad  0x0000000000000000
	.quad  0x4200000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  0x0000000000000000
	.quad  0x0600000000000000
	.quad  watc_regs
	.quad  0x0F0400030000000D
	.quad  fast_regs
	.quad  0x0B04000200000006
	.quad  fast_regs
	.quad  0x58080404000F0306
	.quad  watc_regs
	.quad  0x0B0400030000000D
	.quad  fast_regs
	.quad  0x0B040802003F0006
	.quad  fast_regs
	.quad  0x58080604003F0306
	.quad  watc_regs
	.quad  0x030800040000000F
	.quad  watc_regs
	.quad  0x091000040000000F
	.quad  watc_regs
	.quad  0x09100404000F000F
	.quad  user_regs
	.quad  0x0904000300000007
	.quad  user_regs
	.quad  0x09081003FFFF0007
	.quad  user_regs
	.quad  0x09101007FFFF0F07

DS0000:
	.byte  0x2C, 0x00

DS0001:
	.byte  0x3A, 0x00

DS0002:
	.byte  0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x00

DS0003:
	.byte  0x50, 0x55, 0x42, 0x4C, 0x49, 0x43, 0x00

DS0004:
	.byte  0x45, 0x58, 0x50, 0x4F, 0x52, 0x54, 0x00

DS0005:
	.byte  0x46, 0x4F, 0x52, 0x43, 0x45, 0x46, 0x52, 0x41
	.byte  0x4D, 0x45, 0x00

DS0006:
	.byte  0x4C, 0x4F, 0x41, 0x44, 0x44, 0x53, 0x00

DS0007:
	.byte  0x22, 0x25, 0x73, 0x22, 0x00

DS0008:
	.byte  0x2E, 0x78, 0x64, 0x61, 0x74, 0x61, 0x00

DS0009:
	.byte  0x25, 0x73, 0x20, 0x25, 0x72, 0x00

DS000A:
	.byte  0x25, 0x73, 0x20, 0x25, 0x72, 0x20, 0x61, 0x6C
	.byte  0x69, 0x67, 0x6E, 0x28, 0x25, 0x75, 0x29, 0x20
	.byte  0x66, 0x6C, 0x61, 0x74, 0x20, 0x72, 0x65, 0x61
	.byte  0x64, 0x20, 0x27, 0x44, 0x41, 0x54, 0x41, 0x27
	.byte  0x0A, 0x24, 0x78, 0x64, 0x61, 0x74, 0x61, 0x73
	.byte  0x79, 0x6D, 0x20, 0x6C, 0x61, 0x62, 0x65, 0x6C
	.byte  0x20, 0x6E, 0x65, 0x61, 0x72, 0x00

DS000B:
	.byte  0x64, 0x62, 0x20, 0x25, 0x75, 0x74, 0x20, 0x2B
	.byte  0x20, 0x28, 0x30, 0x25, 0x78, 0x68, 0x20, 0x73
	.byte  0x68, 0x6C, 0x20, 0x33, 0x29, 0x2C, 0x20, 0x25
	.byte  0x75, 0x74, 0x2C, 0x20, 0x25, 0x75, 0x74, 0x2C
	.byte  0x20, 0x30, 0x25, 0x78, 0x68, 0x20, 0x2B, 0x20
	.byte  0x28, 0x30, 0x25, 0x78, 0x68, 0x20, 0x73, 0x68
	.byte  0x6C, 0x20, 0x34, 0x29, 0x00

DS000C:
	.byte  0x64, 0x77, 0x00

DS000D:
	.byte  0x25, 0x73, 0x20, 0x30, 0x25, 0x78, 0x68, 0x00

DS000E:
	.byte  0x41, 0x4C, 0x49, 0x47, 0x4E, 0x20, 0x34, 0x00

DS000F:
	.byte  0x64, 0x64, 0x20, 0x49, 0x4D, 0x41, 0x47, 0x45
	.byte  0x52, 0x45, 0x4C, 0x20, 0x25, 0x73, 0x0A, 0x41
	.byte  0x4C, 0x49, 0x47, 0x4E, 0x20, 0x38, 0x00

DS0010:
	.byte  0x25, 0x73, 0x20, 0x45, 0x4E, 0x44, 0x53, 0x00

DS0011:
	.byte  0x2E, 0x70, 0x64, 0x61, 0x74, 0x61, 0x00

DS0012:
	.byte  0x2E, 0x70, 0x64, 0x61, 0x74, 0x61, 0x24, 0x25
	.byte  0x30, 0x34, 0x75, 0x00

DS0013:
	.byte  0x25, 0x73, 0x20, 0x53, 0x45, 0x47, 0x4D, 0x45
	.byte  0x4E, 0x54, 0x00

DS0014:
	.byte  0x25, 0x73, 0x20, 0x53, 0x45, 0x47, 0x4D, 0x45
	.byte  0x4E, 0x54, 0x20, 0x41, 0x4C, 0x49, 0x47, 0x4E
	.byte  0x28, 0x34, 0x29, 0x20, 0x66, 0x6C, 0x61, 0x74
	.byte  0x20, 0x72, 0x65, 0x61, 0x64, 0x20, 0x27, 0x44
	.byte  0x41, 0x54, 0x41, 0x27, 0x00

DS0015:
	.byte  0x64, 0x64, 0x20, 0x49, 0x4D, 0x41, 0x47, 0x45
	.byte  0x52, 0x45, 0x4C, 0x20, 0x25, 0x73, 0x2C, 0x20
	.byte  0x49, 0x4D, 0x41, 0x47, 0x45, 0x52, 0x45, 0x4C
	.byte  0x20, 0x25, 0x73, 0x2B, 0x30, 0x25, 0x78, 0x68
	.byte  0x2C, 0x20, 0x49, 0x4D, 0x41, 0x47, 0x45, 0x52
	.byte  0x45, 0x4C, 0x20, 0x24, 0x78, 0x64, 0x61, 0x74
	.byte  0x61, 0x73, 0x79, 0x6D, 0x2B, 0x30, 0x25, 0x78
	.byte  0x68, 0x0A, 0x25, 0x73, 0x20, 0x45, 0x4E, 0x44
	.byte  0x53, 0x00

DS0016:
	.byte  0x6F, 0x72, 0x67, 0x20, 0x24, 0x20, 0x2D, 0x20
	.byte  0x32, 0x00

DS0017:
	.byte  0x72, 0x65, 0x74, 0x00

DS0018:
	.byte  0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x70
	.byte  0x72, 0x6F, 0x6C, 0x6F, 0x67, 0x75, 0x65, 0x3A
	.byte  0x6E, 0x6F, 0x6E, 0x65, 0x0A, 0x00

DS0019:
	.byte  0x20, 0x28, 0x25, 0x73, 0x2C, 0x20, 0x30, 0x25
	.byte  0x58, 0x48, 0x2C, 0x20, 0x30, 0x25, 0x58, 0x48
	.byte  0x2C, 0x20, 0x30, 0x25, 0x58, 0x48, 0x2C, 0x20
	.byte  0x3C, 0x3C, 0x25, 0x73, 0x3E, 0x3E, 0x2C, 0x20
	.byte  0x3C, 0x25, 0x73, 0x3E, 0x29, 0x00

DS001A:
	.byte  0x25, 0x72, 0x20, 0x5B, 0x72, 0x73, 0x70, 0x2B
	.byte  0x25, 0x75, 0x5D, 0x2C, 0x20, 0x25, 0x72, 0x00

DS001B:
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x72, 0x73, 0x70
	.byte  0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20, 0x25, 0x72
	.byte  0x00

DS001C:
	.byte  0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72, 0x00

DS001D:
	.byte  0x25, 0x72, 0x20, 0x25, 0x72, 0x00

DS001E:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72
	.byte  0x0A, 0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x0A
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x72, 0x0A, 0x20, 0x25, 0x72, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x30, 0x00

DS001F:
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2C
	.byte  0x20, 0x25, 0x64, 0x0A, 0x65, 0x78, 0x74, 0x65
	.byte  0x72, 0x6E, 0x64, 0x65, 0x66, 0x20, 0x5F, 0x63
	.byte  0x68, 0x6B, 0x73, 0x74, 0x6B, 0x3A, 0x50, 0x52
	.byte  0x4F, 0x43, 0x0A, 0x63, 0x61, 0x6C, 0x6C, 0x20
	.byte  0x5F, 0x63, 0x68, 0x6B, 0x73, 0x74, 0x6B, 0x0A
	.byte  0x73, 0x75, 0x62, 0x20, 0x72, 0x73, 0x70, 0x2C
	.byte  0x20, 0x72, 0x61, 0x78, 0x00

DS0020:
	.byte  0x73, 0x75, 0x62, 0x20, 0x72, 0x73, 0x70, 0x2C
	.byte  0x20, 0x25, 0x64, 0x00

DS0021:
	.byte  0x25, 0x72, 0x20, 0x25, 0x64, 0x00

DS0022:
	.byte  0x6D, 0x6F, 0x76, 0x64, 0x71, 0x61, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x25, 0x75, 0x2B, 0x25, 0x73
	.byte  0x5D, 0x2C, 0x20, 0x25, 0x72, 0x00

DS0023:
	.byte  0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20, 0x25
	.byte  0x75, 0x2B, 0x25, 0x73, 0x00

DS0024:
	.byte  0x6D, 0x6F, 0x76, 0x64, 0x71, 0x61, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x25, 0x75, 0x5D, 0x2C, 0x20
	.byte  0x25, 0x72, 0x00

DS0025:
	.byte  0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20, 0x25
	.byte  0x75, 0x00

DS0026:
	.byte  0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72, 0x0A
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x72, 0x00

DS0027:
	.byte  0x73, 0x75, 0x62, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x64, 0x00

DS0028:
	.byte  0x65, 0x78, 0x74, 0x65, 0x72, 0x6E, 0x64, 0x65
	.byte  0x66, 0x20, 0x5F, 0x63, 0x68, 0x6B, 0x73, 0x74
	.byte  0x6B, 0x3A, 0x50, 0x52, 0x4F, 0x43, 0x0A, 0x6D
	.byte  0x6F, 0x76, 0x20, 0x65, 0x61, 0x78, 0x2C, 0x20
	.byte  0x25, 0x64, 0x0A, 0x63, 0x61, 0x6C, 0x6C, 0x20
	.byte  0x5F, 0x63, 0x68, 0x6B, 0x73, 0x74, 0x6B, 0x00

DS0029:
	.byte  0x73, 0x75, 0x62, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x72, 0x61, 0x78, 0x00

DS002A:
	.byte  0x61, 0x64, 0x64, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x64, 0x00

DS002B:
	.byte  0x70, 0x75, 0x73, 0x68, 0x20, 0x64, 0x73, 0x0A
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x61, 0x78, 0x2C, 0x20
	.byte  0x25, 0x73, 0x0A, 0x6D, 0x6F, 0x76, 0x20, 0x64
	.byte  0x73, 0x2C, 0x20, 0x25, 0x72, 0x00

DS002C:
	.byte  0x55, 0x73, 0x65, 0x72, 0x20, 0x72, 0x65, 0x67
	.byte  0x69, 0x73, 0x74, 0x65, 0x72, 0x73, 0x20, 0x69
	.byte  0x6E, 0x73, 0x69, 0x64, 0x65, 0x20, 0x66, 0x72
	.byte  0x61, 0x6D, 0x65, 0x3A, 0x20, 0x75, 0x73, 0x65
	.byte  0x20, 0x2D, 0x43, 0x73, 0x20, 0x6F, 0x72, 0x20
	.byte  0x4F, 0x50, 0x54, 0x49, 0x4F, 0x4E, 0x20, 0x43
	.byte  0x53, 0x54, 0x41, 0x43, 0x4B, 0x3A, 0x4F, 0x4E
	.byte  0x00

DS002D:
	.byte  0x25, 0x72, 0x20, 0x5B, 0x25, 0x72, 0x5D, 0x5B
	.byte  0x25, 0x64, 0x5D, 0x2C, 0x25, 0x72, 0x00

DS002E:
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x44, 0x57, 0x4F, 0x52
	.byte  0x44, 0x20, 0x50, 0x54, 0x52, 0x20, 0x5B, 0x25
	.byte  0x72, 0x5D, 0x5B, 0x25, 0x64, 0x5D, 0x2C, 0x25
	.byte  0x64, 0x0A, 0x6D, 0x6F, 0x76, 0x20, 0x44, 0x57
	.byte  0x4F, 0x52, 0x44, 0x20, 0x50, 0x54, 0x52, 0x20
	.byte  0x5B, 0x25, 0x72, 0x2B, 0x34, 0x5D, 0x5B, 0x25
	.byte  0x64, 0x5D, 0x2C, 0x34, 0x38, 0x2B, 0x25, 0x64
	.byte  0x00

DS002F:
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x25, 0x72, 0x2B
	.byte  0x30, 0x78, 0x25, 0x58, 0x5D, 0x5B, 0x25, 0x64
	.byte  0x5D, 0x2C, 0x25, 0x72, 0x00

DS0030:
	.byte  0x2E, 0x69, 0x66, 0x20, 0x61, 0x6C, 0x00

DS0031:
	.byte  0x6D, 0x6F, 0x76, 0x61, 0x70, 0x73, 0x20, 0x5B
	.byte  0x25, 0x72, 0x2B, 0x30, 0x78, 0x25, 0x58, 0x5D
	.byte  0x5B, 0x25, 0x64, 0x5D, 0x2C, 0x25, 0x72, 0x00

DS0032:
	.byte  0x2E, 0x65, 0x6E, 0x64, 0x69, 0x66, 0x00

DS0033:
	.byte  0x61, 0x73, 0x73, 0x75, 0x6D, 0x65, 0x20, 0x66
	.byte  0x73, 0x3A, 0x6E, 0x6F, 0x74, 0x68, 0x69, 0x6E
	.byte  0x67, 0x0A, 0x6D, 0x6F, 0x76, 0x20, 0x72, 0x61
	.byte  0x78, 0x2C, 0x66, 0x73, 0x3A, 0x5B, 0x30, 0x78
	.byte  0x32, 0x38, 0x5D, 0x0A, 0x61, 0x73, 0x73, 0x75
	.byte  0x6D, 0x65, 0x20, 0x66, 0x73, 0x3A, 0x65, 0x72
	.byte  0x72, 0x6F, 0x72, 0x0A, 0x6D, 0x6F, 0x76, 0x20
	.byte  0x5B, 0x25, 0x72, 0x2B, 0x30, 0x78, 0x31, 0x38
	.byte  0x5D, 0x5B, 0x25, 0x64, 0x5D, 0x2C, 0x72, 0x61
	.byte  0x78, 0x00

DS0034:
	.byte  0x6C, 0x65, 0x61, 0x20, 0x72, 0x61, 0x78, 0x2C
	.byte  0x5B, 0x25, 0x72, 0x2B, 0x30, 0x78, 0x31, 0x30
	.byte  0x5D, 0x5B, 0x25, 0x64, 0x5D, 0x0A, 0x6D, 0x6F
	.byte  0x76, 0x20, 0x5B, 0x25, 0x72, 0x2B, 0x30, 0x78
	.byte  0x30, 0x38, 0x5D, 0x5B, 0x25, 0x64, 0x5D, 0x2C
	.byte  0x72, 0x61, 0x78, 0x0A, 0x6C, 0x65, 0x61, 0x20
	.byte  0x72, 0x61, 0x78, 0x2C, 0x5B, 0x25, 0x72, 0x2B
	.byte  0x30, 0x78, 0x32, 0x30, 0x5D, 0x5B, 0x25, 0x64
	.byte  0x5D, 0x0A, 0x6D, 0x6F, 0x76, 0x20, 0x5B, 0x25
	.byte  0x72, 0x2B, 0x30, 0x78, 0x31, 0x30, 0x5D, 0x5B
	.byte  0x25, 0x64, 0x5D, 0x2C, 0x72, 0x61, 0x78, 0x0A
	.byte  0x6C, 0x65, 0x61, 0x20, 0x72, 0x61, 0x78, 0x2C
	.byte  0x5B, 0x25, 0x72, 0x5D, 0x5B, 0x25, 0x64, 0x5D
	.byte  0x00

DS0035:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x00

DS0036:
	.byte  0x65, 0x6E, 0x64, 0x62, 0x72, 0x36, 0x34, 0x00

DS0037:
	.byte  0x65, 0x6E, 0x64, 0x62, 0x72, 0x33, 0x32, 0x00

DS0038:
	.byte  0x70, 0x6F, 0x70, 0x20, 0x25, 0x72, 0x00

DS0039:
	.byte  0x6D, 0x6F, 0x76, 0x64, 0x71, 0x61, 0x20, 0x25
	.byte  0x72, 0x2C, 0x20, 0x5B, 0x25, 0x72, 0x20, 0x2B
	.byte  0x20, 0x25, 0x75, 0x20, 0x2B, 0x20, 0x25, 0x73
	.byte  0x5D, 0x00

DS003A:
	.byte  0x6D, 0x6F, 0x76, 0x64, 0x71, 0x61, 0x20, 0x25
	.byte  0x72, 0x2C, 0x20, 0x5B, 0x25, 0x72, 0x20, 0x2B
	.byte  0x20, 0x25, 0x75, 0x5D, 0x00

DS003B:
	.byte  0x6C, 0x65, 0x61, 0x76, 0x65, 0x00

DS003C:
	.byte  0x61, 0x64, 0x64, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x64, 0x20, 0x2B, 0x20, 0x25, 0x73, 0x00

DS003D:
	.byte  0x70, 0x6F, 0x70, 0x20, 0x64, 0x73, 0x00

DS003E:
	.byte  0x25, 0x73, 0x2C, 0x20, 0x30, 0x25, 0x58, 0x48
	.byte  0x2C, 0x20, 0x30, 0x25, 0x58, 0x48, 0x2C, 0x20
	.byte  0x30, 0x25, 0x58, 0x48, 0x2C, 0x20, 0x3C, 0x3C
	.byte  0x25, 0x73, 0x3E, 0x3E, 0x2C, 0x20, 0x3C, 0x25
	.byte  0x73, 0x3E, 0x00

DS003F:
	.byte  0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x65
	.byte  0x70, 0x69, 0x6C, 0x6F, 0x67, 0x75, 0x65, 0x3A
	.byte  0x6E, 0x6F, 0x6E, 0x65, 0x0A, 0x00

DS0040:
	.byte  0x25, 0x73, 0x25, 0x73, 0x00


.SECTION .bss
	.ALIGN	16

unw_code:
	.zero	516 * 1

unw_info:
	.zero	4 * 1

unw_segs_defined:
	.zero	1


.att_syntax prefix
