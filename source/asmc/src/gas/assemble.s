
.intel_syntax noprefix

.global ConvertSectionName
.global OutputByte
.global FillDataBytes
.global OutputBytes
.global SetCurrOffset
.global WritePreprocessedLine
.global SetMasm510
.global close_files
.global AssembleModule
.global Parse_Pass
.global write_to_file
.global ModuleInfo
.global LinnumQueue
.global jmpenv

.extern MacroLocals
.extern LstWriteCRef
.extern LstInit
.extern ExprEvalInit
.extern ProcInit
.extern LabelInit
.extern CondInit
.extern CondCheckOpen
.extern RestoreState
.extern SkipSavedState
.extern FastpassInit
.extern UseSavedState
.extern StoreState
.extern LineStoreCurr
.extern elf_init
.extern coff_init
.extern bin_init
.extern QueueDeleteLinnum
.extern LinnumFini
.extern LinnumInit
.extern LclDup
.extern MemFini
.extern MemInit
.extern Tokenize
.extern AssumeInit
.extern MacroInit
.extern PragmaCheckOpen
.extern PragmaInit
.extern ClassCheckOpen
.extern ClassInit
.extern HllCheckOpen
.extern HllInit
.extern ContextInit
.extern RunLineQueue
.extern set_curr_srcfile
.extern ClearSrcStack
.extern InputFini
.extern InputPassInit
.extern InputInit
.extern AddStringToIncludePath
.extern SearchFile
.extern GetExtPart
.extern GetFNamePart
.extern Mangle
.extern omf_FlushCurrSeg
.extern omf_OutSelect
.extern omf_set_filepos
.extern omf_init
.extern TypesInit
.extern ResWordsFini
.extern ResWordsInit
.extern DisableKeyword
.extern SegmentFini
.extern SegmentInit
.extern ProcessFile
.extern ParseLine
.extern sym_remove_table
.extern SymTables
.extern store_fixup
.extern tgetenv
.extern tstrncpy
.extern tstrcat
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern tmemcmp
.extern tmemcpy
.extern tstrupr
.extern tfprintf
.extern tsprintf
.extern tprintf
.extern SetCPU
.extern asmerr
.extern LastCodeBufSize
.extern MacroLevel
.extern DefaultDir
.extern Options
.extern WriteError
.extern SymSetCmpFunc
.extern SymMakeAllSymbolsPublic
.extern SymPassInit
.extern SymInit
.extern SymFind
.extern SymCreate
.extern rewind
.extern fwrite
.extern fclose
.extern fopen
.extern remove


.SECTION .text
	.ALIGN	16

ConvertSectionName:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	lea	rbx, [cst+rip]
	mov	rdi, qword ptr [rbp+0x28]
	xor	esi, esi
$_001:	cmp	esi, 4
	jnc	$_007
	inc	esi
	mov	r8d, dword ptr [rbx]
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, qword ptr [rdi+0x8]
	call	tmemcmp@PLT
	test	rax, rax
	jnz	$_006
	mov	edx, dword ptr [rbx]
	add	rdx, qword ptr [rdi+0x8]
	mov	al, byte ptr [rdx]
	test	al, al
	jz	$_002
	cmp	al, 36
	jnz	$_006
	test	byte ptr [rbx+0x4], 0x01
	jnz	$_006
$_002:	mov	rcx, qword ptr [rbp+0x30]
	test	rcx, rcx
	jz	$_004
	mov	rax, qword ptr [rdi+0x68]
	cmp	esi, 4
	jnz	$_003
	cmp	dword ptr [rax+0x18], 0
	jnz	$_004
$_003:	lea	rax, [stt+rip]
	movzx	eax, byte ptr [rax+rsi-0x1]
	mov	dword ptr [rcx], eax
$_004:	mov	rax, qword ptr [rbx+0x10]
	cmp	byte ptr [rdx], 0
	jz	$_005
	mov	rbx, rdx
	mov	rdx, rax
	mov	rcx, qword ptr [rbp+0x38]
	call	tstrcpy@PLT
	mov	rdx, rbx
	mov	rcx, rax
	call	tstrcat@PLT
$_005:	jmp	$_008

$_006:	add	rbx, 24
	jmp	$_001

$_007:	mov	rax, qword ptr [rbp+0x28]
	mov	rax, qword ptr [rax+0x8]
$_008:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

OutputByte:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdi, qword ptr [rsi+0x68]
	cmp	dword ptr [write_to_file+rip], 0
	jz	$_010
	mov	ebx, dword ptr [rdi+0xC]
	sub	ebx, dword ptr [rdi+0x8]
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_009
	cmp	ebx, 1014
	jc	$_009
	call	omf_FlushCurrSeg@PLT
	mov	ebx, dword ptr [rdi+0xC]
	sub	ebx, dword ptr [rdi+0x8]
$_009:	mov	eax, dword ptr [rbp+0x28]
	mov	rcx, qword ptr [rdi+0x10]
	mov	byte ptr [rcx+rbx], al
	jmp	$_011

$_010:	mov	eax, dword ptr [rdi+0xC]
	cmp	eax, dword ptr [rdi+0x8]
	jnc	$_011
	mov	dword ptr [rdi+0x8], eax
$_011:	inc	dword ptr [rdi+0xC]
	inc	dword ptr [rdi+0x18]
	mov	byte ptr [rdi+0x70], 1
	mov	eax, dword ptr [rdi+0xC]
	cmp	eax, dword ptr [rsi+0x50]
	jle	$_012
	mov	dword ptr [rsi+0x50], eax
$_012:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

FillDataBytes:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [ModuleInfo+0x1EE+rip], 0
	jz	$_013
	mov	ecx, 1
	call	omf_OutSelect@PLT
$_013:	jmp	$_015

$_014:	movzx	ecx, byte ptr [rbp+0x10]
	call	OutputByte
	dec	dword ptr [rbp+0x18]
$_015:	cmp	dword ptr [rbp+0x18], 0
	jnz	$_014
	leave
	ret

OutputBytes:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdi, qword ptr [rsi+0x68]
	cmp	dword ptr [write_to_file+rip], 0
	jz	$_018
	mov	ebx, dword ptr [rdi+0xC]
	sub	ebx, dword ptr [rdi+0x8]
	add	edx, ebx
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_016
	cmp	edx, 1014
	jc	$_016
	call	omf_FlushCurrSeg@PLT
	mov	ebx, dword ptr [rdi+0xC]
	sub	ebx, dword ptr [rdi+0x8]
$_016:	cmp	qword ptr [rbp+0x38], 0
	jz	$_017
	mov	r8, qword ptr [rbp+0x28]
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x38]
	call	store_fixup@PLT
$_017:	mov	rdx, rdi
	mov	rax, rsi
	mov	rdi, qword ptr [rdi+0x10]
	add	rdi, rbx
	mov	ecx, dword ptr [rbp+0x30]
	mov	rsi, qword ptr [rbp+0x28]
	rep movsb
	mov	rdi, rdx
	mov	rsi, rax
	jmp	$_019

$_018:	mov	eax, dword ptr [rdi+0xC]
	cmp	eax, dword ptr [rdi+0x8]
	jnc	$_019
	mov	dword ptr [rdi+0x8], eax
$_019:	mov	eax, dword ptr [rbp+0x30]
	add	dword ptr [rdi+0xC], eax
	add	dword ptr [rdi+0x18], eax
	mov	byte ptr [rdi+0x70], 1
	mov	eax, dword ptr [rdi+0xC]
	cmp	eax, dword ptr [rsi+0x50]
	jle	$_020
	mov	dword ptr [rsi+0x50], eax
$_020:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SetCurrOffset:
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	ebx, edx
	mov	rsi, rcx
	mov	eax, r8d
	mov	ecx, dword ptr [write_to_file+rip]
	mov	rdi, qword ptr [rsi+0x68]
	test	eax, eax
	jz	$_021
	add	ebx, dword ptr [rdi+0xC]
$_021:	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_025
	cmp	rsi, qword ptr [ModuleInfo+0x1F8+rip]
	jnz	$_024
	test	ecx, ecx
	jz	$_022
	call	omf_FlushCurrSeg@PLT
$_022:	cmp	dword ptr [rbp+0x40], 0
	jz	$_023
	cmp	byte ptr [ModuleInfo+0x1EE+rip], 0
	jz	$_023
	mov	ecx, 1
	call	omf_OutSelect@PLT
$_023:	mov	dword ptr [LastCodeBufSize+rip], ebx
$_024:	mov	dword ptr [rdi+0x8], ebx
	jmp	$_026

$_025:	test	ecx, ecx
	jnz	$_026
	test	eax, eax
	jnz	$_026
	cmp	dword ptr [rdi+0x18], 0
	jnz	$_026
	mov	dword ptr [rdi+0x8], ebx
$_026:	mov	dword ptr [rdi+0xC], ebx
	mov	byte ptr [rdi+0x70], 0
	mov	eax, dword ptr [rdi+0xC]
	cmp	eax, dword ptr [rsi+0x50]
	jle	$_027
	mov	dword ptr [rsi+0x50], eax
$_027:	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_028:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rbx, qword ptr [SymTables+0x20+rip]
	jmp	$_031

$_029:	mov	rax, qword ptr [rbx+0x68]
	cmp	byte ptr [rax+0x68], 0
	jnz	$_030
	cmp	dword ptr [rbx+0x50], 65536
	jle	$_030
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_030
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2103
	call	asmerr@PLT
$_030:	mov	rbx, qword ptr [rbx+0x70]
$_031:	test	rbx, rbx
	jnz	$_029
	mov	rcx, qword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x28]
	call	qword ptr [rax+0x158]
	mov	rbx, qword ptr [Options+0x30+rip]
	test	rbx, rbx
	je	$_037
	lea	rsi, [DS0000+rip]
	mov	rdi, rbx
	call	fopen@PLT
	test	rax, rax
	jnz	$_032
	mov	rdx, rbx
	mov	ecx, 3020
	call	asmerr@PLT
	jmp	$_037

$_032:	mov	qword ptr [rbp-0x8], rax
	mov	rbx, qword ptr [SymTables+0x10+rip]
	jmp	$_036

$_033:	mov	rcx, qword ptr [rbx+0x50]
	test	byte ptr [rbx+0x15], 0x08
	jz	$_035
	test	rcx, rcx
	jz	$_035
	cmp	byte ptr [rcx+0xC], 0
	jz	$_035
	test	byte ptr [rbx+0x3B], 0x02
	jz	$_034
	test	byte ptr [rbx+0x14], 0x08
	jz	$_035
$_034:	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	rcx, rbx
	call	Mangle@PLT
	mov	rcx, qword ptr [rbx+0x50]
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rcx+0xC]
	mov	r8, qword ptr [ModuleInfo+0x188+rip]
	lea	rdx, [DS0001+rip]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tsprintf@PLT
	mov	dword ptr [rbp-0xC], eax
	mov	rcx, qword ptr [rbp-0x8]
	mov	edx, dword ptr [rbp-0xC]
	mov	esi, 1
	mov	rdi, qword ptr [ModuleInfo+0x178+rip]
	call	fwrite@PLT
	cmp	dword ptr [rbp-0xC], eax
	jz	$_035
	call	WriteError@PLT
$_035:	mov	rbx, qword ptr [rbx+0x70]
$_036:	test	rbx, rbx
	jne	$_033
	mov	rdi, qword ptr [rbp-0x8]
	call	fclose@PLT
$_037:	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_038:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, qword ptr [Options+0x60+rip]
	jmp	$_049

$_039:	lea	rdi, [rsi+0x8]
	mov	edx, 61
	mov	rcx, rdi
	call	tstrchr@PLT
	test	rax, rax
	jnz	$_040
	mov	rcx, rdi
	call	tstrlen@PLT
	lea	rbx, [rdi+rax]
	jmp	$_041

$_040:	mov	rbx, rax
	mov	rax, rbx
	sub	rax, rdi
	inc	eax
	mov	dword ptr [rbp-0x4], eax
	mov	eax, dword ptr [rbp-0x4]
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
	mov	r8d, dword ptr [rbp-0x4]
	mov	rdx, rdi
	mov	rcx, rax
	call	tmemcpy@PLT
	mov	ecx, dword ptr [rbp-0x4]
	mov	byte ptr [rax+rcx-0x1], 0
	inc	rbx
	mov	rdi, rax
$_041:	xor	ecx, ecx
	movzx	eax, byte ptr [rdi]
	cmp	al, 46
	jz	$_042
	test	byte ptr [r15+rax], 0x44
	jnz	$_042
	inc	ecx
	jmp	$_045

$_042:	lea	rdx, [rdi+0x1]
	mov	al, byte ptr [rdx]
$_043:	test	eax, eax
	jz	$_045
	test	byte ptr [r15+rax], 0x44
	jnz	$_044
	inc	ecx
	jmp	$_045

$_044:	inc	rdx
	mov	al, byte ptr [rdx]
	jmp	$_043

$_045:	test	ecx, ecx
	jz	$_046
	mov	rdx, rdi
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_050

$_046:	mov	rcx, rdi
	call	SymFind@PLT
	test	rax, rax
	jnz	$_047
	mov	rcx, rdi
	call	SymCreate@PLT
	mov	byte ptr [rax+0x18], 10
$_047:	cmp	byte ptr [rax+0x18], 10
	jz	$_048
	mov	rdx, rdi
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_050

$_048:	or	byte ptr [rax+0x14], 0x22
	mov	qword ptr [rax+0x28], rbx
	mov	rsi, qword ptr [rsi]
$_049:	test	rsi, rsi
	jne	$_039
$_050:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_051:
	push	rsi
	sub	rsp, 32
	mov	rsi, qword ptr [Options+0x68+rip]
	jmp	$_053

$_052:	lea	rcx, [rsi+0x8]
	call	AddStringToIncludePath@PLT
	mov	rsi, qword ptr [rsi]
$_053:	test	rsi, rsi
	jnz	$_052
	add	rsp, 32
	pop	rsi
	ret

$_054:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	dword ptr [rbp+0x10], 0
	jnz	$_055
	call	$_038
	call	$_051
	cmp	byte ptr [Options+0xC7+rip], 0
	jnz	$_055
	lea	rcx, [DS0002+rip]
	call	tgetenv@PLT
	test	rax, rax
	jz	$_055
	mov	rcx, rax
	call	AddStringToIncludePath@PLT
$_055:	leave
	ret

WritePreprocessedLine:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	dword ptr [ModuleInfo+0x220+rip], 0
	jle	$_060
	jmp	$_057

$_056:	inc	rcx
$_057:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_056
	cmp	eax, 37
	jnz	$_058
	inc	rcx
	jmp	$_059

$_058:	mov	rcx, qword ptr [rbp+0x10]
$_059:	mov	rdx, rcx
	lea	rcx, [DS0001+0x10+rip]
	call	tprintf@PLT
	mov	byte ptr [PrintEmptyLine+rip], 1
	jmp	$_061

$_060:	cmp	byte ptr [PrintEmptyLine+rip], 0
	jz	$_061
	mov	byte ptr [PrintEmptyLine+rip], 0
	lea	rcx, [DS0001+0x12+rip]
	call	tprintf@PLT
$_061:	leave
	ret

SetMasm510:
	mov	eax, ecx
	lea	rcx, [ModuleInfo+rip]
	mov	byte ptr [rcx+0x1D6], al
	mov	byte ptr [rcx+0x1D8], al
	mov	byte ptr [rcx+0x1D4], al
	mov	byte ptr [rcx+0x1DA], al
	test	eax, eax
	jz	$_062
	cmp	byte ptr [rcx+0x1B5], 0
	jnz	$_062
	mov	byte ptr [rcx+0x1BB], 2
	cmp	byte ptr [rcx+0x1B6], 0
	jnz	$_062
	mov	byte ptr [rcx+0x1D7], 0
	mov	byte ptr [rcx+0x1D2], 0
$_062:	ret

$_063:
	push	rsi
	push	rdi
	push	rbx
	sub	rsp, 32
	lea	rdi, [Options+rip]
	lea	rbx, [ModuleInfo+rip]
	mov	ecx, dword ptr [rdi+0xB4]
	mov	esi, dword ptr [rdi+0xB0]
	mov	byte ptr [rbx+0x1D2], 0
	mov	byte ptr [rbx+0x1D3], 0
	mov	byte ptr [rbx+0x1BB], 0
	mov	byte ptr [rbx+0x1D7], 1
	mov	dword ptr [rbx+0x340], 115
	cmp	dword ptr [UseSavedState+rip], 0
	jnz	$_068
	mov	eax, dword ptr [rdi+0xAC]
	mov	byte ptr [rbx+0x1B6], al
	mov	eax, dword ptr [rdi+0xB8]
	mov	byte ptr [rbx+0x1B9], al
	mov	eax, ecx
	and	eax, 0xF0
	cmp	eax, 112
	jnc	$_064
	mov	ecx, 120
$_064:	mov	esi, 7
	cmp	byte ptr [rbx+0x1B6], 0
	jnz	$_067
	cmp	dword ptr [rdi+0xA4], 2
	jz	$_065
	cmp	dword ptr [rdi+0xA4], 0
	jnz	$_066
$_065:	mov	byte ptr [rbx+0x1B6], 7
	jmp	$_067

$_066:	cmp	dword ptr [rdi+0xA4], 3
	jnz	$_067
	mov	byte ptr [rbx+0x1B6], 2
$_067:	call	SetCPU@PLT
$_068:	movzx	eax, byte ptr [rdi+0x97]
	mov	ecx, eax
	call	SetMasm510
	mov	byte ptr [rbx+0x1CD], 2
	mov	byte ptr [rbx+0x1D5], 1
	mov	al, byte ptr [rdi+0x92]
	mov	byte ptr [rbx+0x1DB], al
	mov	byte ptr [rbx+0x1DC], 1
	mov	al, byte ptr [rdi+0x9A]
	mov	byte ptr [rbx+0x1DD], al
	mov	al, byte ptr [rdi+0x9B]
	mov	byte ptr [rbx+0x1DE], al
	mov	eax, dword ptr [rdi+0x9C]
	mov	dword ptr [rbx+0x1C8], eax
	mov	al, byte ptr [rdi+0x94]
	mov	byte ptr [rbx+0x1D0], al
	mov	al, byte ptr [rdi+0x95]
	mov	byte ptr [rbx+0x1D1], al
	call	SymSetCmpFunc@PLT
	mov	byte ptr [rbx+0x1BA], 0
	mov	byte ptr [rbx+0x1C4], 10
	mov	al, byte ptr [rdi+0xC8]
	mov	byte ptr [rbx+0x1C5], al
	mov	byte ptr [rbx+0x1C7], 0
	mov	al, byte ptr [rbx+0x334]
	and	al, 0x04
	or	al, byte ptr [rdi+0xCA]
	mov	byte ptr [rbx+0x334], al
	mov	al, byte ptr [rdi+0xCB]
	mov	byte ptr [rbx+0x335], al
	mov	al, byte ptr [rdi+0xCC]
	mov	byte ptr [rbx+0x336], al
	mov	eax, dword ptr [rdi+0xBC]
	mov	dword ptr [rbx+0x344], eax
	mov	al, byte ptr [rdi+0xD0]
	mov	byte ptr [rbx+0x1E5], al
	mov	al, byte ptr [rdi+0xD4]
	mov	byte ptr [rbx+0x1E1], al
	mov	al, byte ptr [rdi+0xC4]
	mov	byte ptr [rbx+0x350], al
	mov	eax, dword ptr [rdi+0xC0]
	mov	dword ptr [rbx+0x34C], eax
	mov	al, byte ptr [rdi+0xC5]
	mov	byte ptr [rbx+0x351], al
	mov	al, byte ptr [rdi+0xD5]
	mov	byte ptr [rbx+0x352], al
	mov	al, byte ptr [rdi+0xD6]
	mov	byte ptr [rbx+0x353], al
	mov	al, byte ptr [rdi+0xD8]
	mov	byte ptr [rbx+0x1D4], al
	mov	al, byte ptr [rdi+0xD9]
	mov	byte ptr [rbx+0x354], al
	mov	al, byte ptr [rdi+0xDA]
	mov	byte ptr [rbx+0x355], al
	mov	al, byte ptr [rdi+0x98]
	mov	byte ptr [rbx+0x337], al
	mov	byte ptr [rbx+0x356], 0
	cmp	qword ptr [rbx+0x60], 0
	jz	$_071
	mov	rax, qword ptr [SymTables+0x10+rip]
	jmp	$_070

$_069:	and	dword ptr [rax+0x14], 0xFFFFFFF7
	mov	rax, qword ptr [rax+0x70]
$_070:	test	rax, rax
	jnz	$_069
$_071:	add	rsp, 32
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_072:
	push	rsi
	push	rdi
	sub	rsp, 40
	call	HllCheckOpen@PLT
	call	CondCheckOpen@PLT
	call	ClassCheckOpen@PLT
	call	PragmaCheckOpen@PLT
	cmp	byte ptr [ModuleInfo+0x1E0+rip], 0
	jnz	$_073
	mov	ecx, 2088
	call	asmerr@PLT
$_073:	lea	rdx, [ModuleInfo+0x10+rip]
	mov	rcx, qword ptr [rdx]
	jmp	$_078

$_074:	mov	rax, qword ptr [rcx+0x8]
	cmp	byte ptr [rax+0x18], 1
	jnz	$_075
	mov	rdx, rcx
	jmp	$_077

$_075:	cmp	byte ptr [rax+0x18], 2
	jnz	$_076
	test	byte ptr [rax+0x3B], 0x02
	jz	$_076
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rdx], rax
	mov	rcx, rdx
	jmp	$_077

$_076:	mov	dword ptr [UseSavedState+rip], 0
	jmp	$_086

$_077:	mov	rcx, qword ptr [rcx]
$_078:	test	rcx, rcx
	jnz	$_074
	mov	rax, qword ptr [SymTables+0x20+rip]
	jmp	$_081

$_079:	cmp	qword ptr [rax+0x30], 0
	jnz	$_080
	mov	dword ptr [UseSavedState+rip], 0
	jmp	$_086

$_080:	mov	rax, qword ptr [rax+0x70]
$_081:	test	rax, rax
	jnz	$_079
	mov	rax, qword ptr [ModuleInfo+0x30+rip]
	jmp	$_085

$_082:	cmp	byte ptr [rax+0x18], 1
	jnz	$_083
	test	byte ptr [rax+0x15], 0x08
	jnz	$_084
$_083:	mov	dword ptr [UseSavedState+rip], 0
	jmp	$_086

$_084:	mov	rax, qword ptr [rax+0x70]
$_085:	test	rax, rax
	jnz	$_082
$_086:	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_087
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_093
$_087:	mov	rcx, qword ptr [SymTables+0x50+rip]
	jmp	$_092

$_088:	mov	rax, qword ptr [rcx+0x28]
	test	rax, rax
	jz	$_089
	cmp	byte ptr [rax+0x18], 2
	jz	$_090
	cmp	byte ptr [rax+0x18], 1
	jnz	$_089
	test	dword ptr [rax+0x14], 0x80
	jnz	$_090
$_089:	mov	dword ptr [UseSavedState+rip], 0
	jmp	$_093

$_090:	cmp	byte ptr [rax+0x18], 2
	jnz	$_091
	or	byte ptr [rax+0x14], 0x01
$_091:	mov	rcx, qword ptr [rcx+0x70]
$_092:	test	rcx, rcx
	jnz	$_088
$_093:	mov	rdi, qword ptr [SymTables+0x10+rip]
	jmp	$_100

$_094:	mov	rsi, rdi
	mov	rdi, qword ptr [rsi+0x70]
	test	byte ptr [rsi+0x14], 0x01
	jz	$_095
	and	byte ptr [rsi+0x3B], 0xFFFFFFFD
$_095:	test	byte ptr [rsi+0x3B], 0x02
	jz	$_096
	test	byte ptr [rsi+0x14], 0x08
	jnz	$_096
	mov	rdx, rsi
	lea	rcx, [SymTables+0x10+rip]
	call	sym_remove_table@PLT
	jmp	$_100

$_096:	test	byte ptr [rsi+0x3B], 0x01
	jnz	$_100
	mov	rax, qword ptr [rsi+0x58]
	test	rax, rax
	jz	$_100
	cmp	byte ptr [rax+0x18], 1
	jnz	$_099
	test	dword ptr [rax+0x14], 0x80
	jnz	$_098
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_097
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_098
$_097:	call	SkipSavedState@PLT
$_098:	jmp	$_100

$_099:	cmp	byte ptr [rax+0x18], 2
	jz	$_100
	mov	dword ptr [UseSavedState+rip], 0
$_100:	test	rdi, rdi
	jnz	$_094
	cmp	dword ptr [ModuleInfo+rip], 0
	jnz	$_103
	cmp	byte ptr [Options+0xA2+rip], 0
	jz	$_101
	call	SymMakeAllSymbolsPublic@PLT
$_101:	cmp	byte ptr [Options+0xC9+rip], 0
	jnz	$_102
	mov	dword ptr [write_to_file+rip], 1
$_102:	cmp	qword ptr [ModuleInfo+0x168+rip], 0
	jz	$_103
	lea	rcx, [ModuleInfo+rip]
	call	qword ptr [ModuleInfo+0x168+rip]
$_103:	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

$_104:
	push	rsi
	push	rdi
	sub	rsp, 40
	call	InputPassInit@PLT
	call	$_063
	mov	ecx, dword ptr [Parse_Pass+rip]
	call	SymPassInit@PLT
	call	LabelInit@PLT
	mov	ecx, dword ptr [Parse_Pass+rip]
	call	SegmentInit@PLT
	mov	ecx, dword ptr [Parse_Pass+rip]
	call	ContextInit@PLT
	call	ProcInit@PLT
	call	TypesInit@PLT
	mov	ecx, dword ptr [Parse_Pass+rip]
	call	HllInit@PLT
	call	ClassInit@PLT
	call	PragmaInit@PLT
	mov	ecx, dword ptr [Parse_Pass+rip]
	call	MacroInit@PLT
	mov	ecx, dword ptr [Parse_Pass+rip]
	call	AssumeInit@PLT
	mov	ecx, dword ptr [Parse_Pass+rip]
	call	$_054
	xor	eax, eax
	mov	byte ptr [ModuleInfo+0x1E0+rip], al
	mov	byte ptr [ModuleInfo+0x1ED+rip], al
	call	LinnumInit@PLT
	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_105
	call	RunLineQueue@PLT
$_105:	mov	dword ptr [StoreState+rip], 0
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_110
	cmp	dword ptr [UseSavedState+rip], 1
	jne	$_110
	call	RestoreState@PLT
	mov	qword ptr [LineStoreCurr+rip], rax
	mov	rsi, rax
	jmp	$_108

$_106:	mov	edx, dword ptr [rsi+0x10]
	mov	ecx, dword ptr [rsi+0x14]
	call	set_curr_srcfile@PLT
	mov	byte ptr [ModuleInfo+0x1C6+rip], 0
	mov	eax, dword ptr [rsi+0x18]
	mov	dword ptr [MacroLevel+rip], eax
	mov	qword ptr [ModuleInfo+0x218+rip], 0
	xor	r9d, r9d
	mov	r8, qword ptr [ModuleInfo+0x180+rip]
	xor	edx, edx
	lea	rcx, [rsi+0x20]
	call	Tokenize@PLT
	test	rax, rax
	jz	$_107
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rcx, qword ptr [ModuleInfo+0x180+rip]
	call	ParseLine@PLT
$_107:	mov	rsi, qword ptr [rsi]
	mov	qword ptr [LineStoreCurr+rip], rsi
$_108:	test	rsi, rsi
	jz	$_109
	cmp	byte ptr [ModuleInfo+0x1E0+rip], 0
	jz	$_106
$_109:	jmp	$_113

$_110:	mov	rsi, qword ptr [Options+0x58+rip]
	jmp	$_112

$_111:	lea	rax, [rsi+0x8]
	mov	rsi, qword ptr [rsi]
	mov	edx, 1
	mov	rcx, rax
	call	SearchFile@PLT
	test	rax, rax
	jz	$_112
	mov	rcx, qword ptr [ModuleInfo+0x180+rip]
	call	ProcessFile@PLT
$_112:	test	rsi, rsi
	jnz	$_111
	mov	rcx, qword ptr [ModuleInfo+0x180+rip]
	call	ProcessFile@PLT
$_113:	call	LinnumFini@PLT
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_114
	call	$_072
$_114:	call	ClearSrcStack@PLT
	mov	eax, 1
	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

$_115:
	push	rsi
	push	rdi
	sub	rsp, 40
	mov	rsi, qword ptr [Options+0x38+rip]
	test	rsi, rsi
	jz	$_116
	mov	r8d, 260
	mov	rdx, rsi
	lea	rcx, [ModuleInfo+0x230+rip]
	call	tstrncpy@PLT
	mov	byte ptr [ModuleInfo+0x333+rip], 0
	jmp	$_118

$_116:	mov	rcx, qword ptr [ModuleInfo+0x90+rip]
	call	GetFNamePart@PLT
	mov	rsi, rax
	mov	rcx, rax
	call	GetExtPart@PLT
	cmp	rax, rsi
	jnz	$_117
	mov	rcx, rsi
	call	tstrlen@PLT
	add	rax, rsi
$_117:	sub	rax, rsi
	lea	rcx, [ModuleInfo+0x230+rip]
	mov	byte ptr [rcx+rax], 0
	mov	r8d, eax
	mov	rdx, rsi
	call	tmemcpy@PLT
$_118:	lea	rsi, [ModuleInfo+0x230+rip]
	mov	rcx, rsi
	call	tstrupr@PLT
	xor	eax, eax
$_119:	lodsb
	test	al, al
	jz	$_120
	test	byte ptr [r15+rax], 0x44
	jnz	$_119
	mov	byte ptr [rsi-0x1], 95
	jmp	$_119

$_120:
	cmp	byte ptr [ModuleInfo+0x230+rip], 57
	ja	$_121
	cmp	byte ptr [ModuleInfo+0x230+rip], 48
	jc	$_121
	mov	byte ptr [ModuleInfo+0x230+rip], 95
$_121:	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

$_122:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	eax, dword ptr [Options+0xA8+rip]
	mov	byte ptr [ModuleInfo+0x1B8+rip], al
	mov	eax, dword ptr [Options+0xA4+rip]
	mov	ecx, 16
	mul	ecx
	lea	rdx, [formatoptions+rip]
	add	rax, rdx
	mov	qword ptr [ModuleInfo+0x1A8+rip], rax
	mov	qword ptr [rbp-0x8], rax
	xor	eax, eax
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_123
	cmp	byte ptr [Options+0x89+rip], 0
	jnz	$_123
	inc	eax
$_123:	mov	byte ptr [ModuleInfo+0x1EE+rip], al
	mov	dword ptr [ModuleInfo+rip], 0
	mov	dword ptr [ModuleInfo+0x4+rip], 0
	mov	byte ptr [ModuleInfo+0x1B5+rip], 0
	mov	byte ptr [ModuleInfo+0x1B7+rip], 0
	mov	byte ptr [ModuleInfo+0x1D9+rip], 0
	cmp	dword ptr [Options+0x4+rip], 1
	jnz	$_124
	inc	byte ptr [ModuleInfo+0x1D9+rip]
$_124:	call	$_115
	mov	rdx, rdi
	lea	rdi, [SymTables+rip]
	mov	ecx, 96
	xor	eax, eax
	rep stosb
	mov	rdi, rdx
	lea	rcx, [ModuleInfo+rip]
	mov	rax, qword ptr [rbp-0x8]
	call	qword ptr [rax]
	leave
	ret

$_125:
	sub	rsp, 40
	call	ResWordsInit@PLT
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_126
	mov	ecx, 239
	call	DisableKeyword@PLT
	mov	ecx, 251
	call	DisableKeyword@PLT
$_126:	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_127
	mov	ecx, 527
	call	DisableKeyword@PLT
	mov	ecx, 302
	call	DisableKeyword@PLT
	mov	ecx, 299
	call	DisableKeyword@PLT
	mov	ecx, 254
	call	DisableKeyword@PLT
	mov	ecx, 240
	call	DisableKeyword@PLT
	mov	ecx, 256
	call	DisableKeyword@PLT
	mov	ecx, 247
	call	DisableKeyword@PLT
	mov	ecx, 259
	call	DisableKeyword@PLT
	mov	ecx, 257
	call	DisableKeyword@PLT
	mov	ecx, 235
	call	DisableKeyword@PLT
	mov	ecx, 242
	call	DisableKeyword@PLT
$_127:	add	rsp, 40
	ret

$_128:
	push	rsi
	push	rdi
	sub	rsp, 40
	lea	rsi, [DS0003+rip]
	mov	rdi, qword ptr [ModuleInfo+0x90+rip]
	call	fopen@PLT
	test	rax, rax
	jnz	$_129
	mov	rdx, qword ptr [ModuleInfo+0x90+rip]
	mov	ecx, 1000
	call	asmerr@PLT
$_129:	mov	qword ptr [ModuleInfo+0x70+rip], rax
	cmp	byte ptr [Options+0xC9+rip], 0
	jnz	$_131
	lea	rsi, [DS0004+rip]
	mov	rdi, qword ptr [ModuleInfo+0x98+rip]
	call	fopen@PLT
	test	rax, rax
	jnz	$_130
	mov	rdx, qword ptr [ModuleInfo+0x98+rip]
	mov	ecx, 1000
	call	asmerr@PLT
$_130:	mov	qword ptr [ModuleInfo+0x78+rip], rax
$_131:	cmp	byte ptr [Options+0x92+rip], 0
	jz	$_133
	lea	rsi, [DS0004+rip]
	mov	rdi, qword ptr [ModuleInfo+0xA0+rip]
	call	fopen@PLT
	test	rax, rax
	jnz	$_132
	mov	rdx, qword ptr [ModuleInfo+0xA0+rip]
	mov	ecx, 1000
	call	asmerr@PLT
$_132:	mov	qword ptr [ModuleInfo+0x80+rip], rax
$_133:	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

$_134:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 344
	mov	rcx, qword ptr [rbp+0x28]
	call	GetFNamePart@PLT
	mov	rdx, rax
	lea	rcx, [rbp-0x104]
	call	tstrcpy@PLT
	mov	rbx, rax
	mov	rcx, rbx
	call	GetExtPart@PLT
	cmp	rax, rbx
	jnz	$_135
	lea	rdx, [DS0005+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	jmp	$_136

$_135:	lea	rdx, [DS0005+rip]
	mov	rcx, rax
	call	tstrcpy@PLT
$_136:	mov	rdx, rbx
	lea	rcx, [iddcfile+rip]
	call	tstrcpy@PLT
	mov	qword ptr [rbp-0x110], rax
	lea	rsi, [DS0004+rip]
	mov	rdi, rax
	call	fopen@PLT
	test	rax, rax
	jnz	$_137
	mov	rdx, qword ptr [rbp-0x110]
	mov	ecx, 1000
	call	asmerr@PLT
$_137:	mov	qword ptr [rbp-0x118], rax
	mov	rcx, rbx
	call	GetExtPart@PLT
	mov	byte ptr [rax], 0
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x30], rax
	mov	qword ptr [rsp+0x28], rbx
	mov	qword ptr [rsp+0x20], rbx
	mov	r9, rbx
	mov	r8, rbx
	lea	rdx, [DS0006+rip]
	mov	rcx, qword ptr [rbp-0x118]
	call	tfprintf@PLT
	cmp	byte ptr [Options+0xD7+rip], 2
	jnz	$_138
	lea	rdx, [DS0007+rip]
	mov	rcx, qword ptr [rbp-0x118]
	call	tfprintf@PLT
$_138:	lea	rdx, [DS0008+rip]
	mov	rcx, qword ptr [rbp-0x118]
	call	tfprintf@PLT
	mov	rdi, qword ptr [rbp-0x118]
	call	fclose@PLT
	mov	rax, qword ptr [rbp-0x110]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

close_files:
	push	rsi
	push	rdi
	sub	rsp, 40
	mov	rax, qword ptr [ModuleInfo+0x70+rip]
	test	rax, rax
	jz	$_139
	mov	rdi, rax
	call	fclose@PLT
	test	rax, rax
	jz	$_139
	mov	rdx, qword ptr [ModuleInfo+0x90+rip]
	mov	ecx, 3021
	call	asmerr@PLT
$_139:	mov	rax, qword ptr [ModuleInfo+0x78+rip]
	test	rax, rax
	jz	$_140
	mov	rdi, rax
	call	fclose@PLT
	test	rax, rax
	jz	$_140
	mov	rdx, qword ptr [ModuleInfo+0x98+rip]
	mov	ecx, 3021
	call	asmerr@PLT
$_140:	cmp	byte ptr [Options+0xC9+rip], 0
	jnz	$_141
	cmp	dword ptr [ModuleInfo+rip], 0
	jnz	$_142
$_141:	cmp	dword ptr [remove_obj+rip], 0
	jz	$_143
$_142:	mov	dword ptr [remove_obj+rip], 0
	mov	rdi, qword ptr [ModuleInfo+0x98+rip]
	call	remove@PLT
$_143:	mov	rax, qword ptr [ModuleInfo+0x80+rip]
	test	rax, rax
	jz	$_144
	mov	rdi, rax
	call	fclose@PLT
	mov	qword ptr [ModuleInfo+0x80+rip], 0
$_144:	mov	rax, qword ptr [ModuleInfo+0x88+rip]
	test	rax, rax
	jz	$_145
	mov	rdi, rax
	call	fclose@PLT
	mov	qword ptr [ModuleInfo+0x88+rip], 0
	jmp	$_146

$_145:	cmp	qword ptr [ModuleInfo+0xA8+rip], 0
	jz	$_146
	mov	rdi, qword ptr [ModuleInfo+0xA8+rip]
	call	remove@PLT
$_146:	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

$_147:
	lea	rax, [currentftype+rip]
	mov	edx, 1836278062
	jmp	$_155

$_148:	mov	edx, 1784835886
	cmp	dword ptr [Options+0xA4+rip], 0
	jnz	$_151
	mov	edx, 1852400174
	cmp	dword ptr [Options+0xA8+rip], 1
	jz	$_149
	cmp	dword ptr [Options+0xA8+rip], 2
	jz	$_149
	cmp	dword ptr [Options+0xA8+rip], 3
	jnz	$_150
$_149:	mov	edx, 1702389038
	cmp	byte ptr [Options+0xCF+rip], 0
	jz	$_150
	mov	edx, 1819042862
$_150:	jmp	$_152

$_151:	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_152
	and	edx, 0xFFFF
$_152:	jmp	$_156

$_153:	mov	edx, 1953721390
	jmp	$_156

$_154:	mov	edx, 1920099630
	jmp	$_156

$_155:	cmp	ecx, 1
	jz	$_148
	cmp	ecx, 2
	jz	$_153
	cmp	ecx, 3
	jz	$_154
$_156:	mov	dword ptr [rax], edx
	ret

$_157:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	mov	rcx, qword ptr [rbp+0x28]
	call	LclDup@PLT
	mov	qword ptr [ModuleInfo+0x90+rip], rax
	mov	rcx, rax
	call	GetFNamePart@PLT
	mov	rsi, rax
	mov	edi, 1
	lea	rbx, [rbp-0x104]
	jmp	$_163

$_158:	lea	rax, [Options+rip]
	mov	rax, qword ptr [rax+rdi*8+0x10]
	test	rax, rax
	jnz	$_160
	mov	byte ptr [rbx], 0
	lea	rcx, [DefaultDir+rip]
	mov	rax, qword ptr [rcx+rdi*8]
	test	rax, rax
	jz	$_159
	mov	rdx, rax
	mov	rcx, rbx
	call	tstrcpy@PLT
$_159:	mov	rdx, rsi
	mov	rcx, rbx
	call	tstrcat@PLT
	mov	rcx, rax
	call	GetExtPart@PLT
	mov	rbx, rax
	mov	ecx, edi
	call	$_147
	mov	rdx, rax
	mov	rcx, rbx
	call	tstrcpy@PLT
	lea	rbx, [rbp-0x104]
	jmp	$_162

$_160:	mov	rdx, rax
	mov	rcx, rbx
	call	tstrcpy@PLT
	mov	rcx, rax
	call	GetFNamePart@PLT
	cmp	byte ptr [rax], 0
	jnz	$_161
	mov	rdx, rsi
	mov	rcx, rax
	call	tstrcpy@PLT
$_161:	mov	rcx, rax
	call	GetExtPart@PLT
	cmp	byte ptr [rax], 0
	jnz	$_162
	mov	rbx, rax
	mov	ecx, edi
	call	$_147
	mov	rdx, rax
	mov	rcx, rbx
	call	tstrcpy@PLT
	lea	rbx, [rbp-0x104]
$_162:	mov	rcx, rbx
	call	LclDup@PLT
	lea	rcx, [ModuleInfo+rip]
	mov	qword ptr [rcx+rdi*8+0x90], rax
	inc	edi
$_163:	cmp	rdi, 4
	jc	$_158
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_164:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call	MemInit@PLT
	mov	dword ptr [write_to_file+rip], 0
	mov	qword ptr [LinnumQueue+rip], 0
	mov	rcx, qword ptr [rbp+0x10]
	call	$_157
	call	FastpassInit@PLT
	call	$_128
	call	$_125
	call	SymInit@PLT
	call	InputInit@PLT
	call	$_122
	call	CondInit@PLT
	call	ExprEvalInit@PLT
	call	LstInit@PLT
	leave
	ret

$_165:
	sub	rsp, 40
	call	SegmentFini@PLT
	call	ResWordsFini@PLT
	mov	qword ptr [ModuleInfo+0x10+rip], 0
	call	InputFini@PLT
	call	close_files
	xor	eax, eax
	mov	ecx, 4
	lea	rdx, [ModuleInfo+0x90+rip]
$_166:	mov	qword ptr [rdx+rcx*8-0x8], rax
	dec	rcx
	jnz	$_166
	call	MemFini@PLT
	add	rsp, 40
	ret

AssembleModule:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	xor	eax, eax
	mov	dword ptr [MacroLocals+rip], eax
	mov	qword ptr [ModuleInfo+0xF0+rip], rax
	lea	rdi, [ModuleInfo+rip]
	mov	ecx, 856
	rep stosb
	mov	byte ptr [ModuleInfo+0x1C4+rip], 10
	dec	eax
	mov	dword ptr [rbp-0x8], eax
	cmp	byte ptr [Options+rip], 0
	jnz	$_167
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [DS0009+rip]
	call	tprintf@PLT
$_167:	lea	rcx, [jmpenv+rip]
	xor	eax, eax
	mov	qword ptr [rcx+0x10], rbp
	mov	qword ptr [rcx], rbx
	mov	qword ptr [rcx+0x8], rsp
	mov	qword ptr [rcx+0x18], r12
	mov	qword ptr [rcx+0x20], r13
	mov	qword ptr [rcx+0x28], r14
	mov	qword ptr [rcx+0x30], r15
	lea	rdx, [$_168+rip]
	mov	qword ptr [rcx+0x38], rdx
$_168:	test	rax, rax
	jz	$_171
	cmp	eax, 1
	jnz	$_169
	call	ClearSrcStack@PLT
	call	$_165
	xor	eax, eax
	mov	dword ptr [MacroLocals+rip], eax
	lea	rdi, [ModuleInfo+rip]
	mov	ecx, 856
	rep stosb
	dec	eax
	mov	dword ptr [rbp-0x8], eax
	jmp	$_171

$_169:	cmp	qword ptr [ModuleInfo+0xD8+rip], 0
	jz	$_170
	call	ClearSrcStack@PLT
$_170:	jmp	$_189

$_171:	cmp	byte ptr [Options+0xD7+rip], 0
	jz	$_172
	mov	rcx, qword ptr [rbp+0x28]
	call	$_134
	mov	qword ptr [rbp+0x28], rax
$_172:	mov	rcx, qword ptr [rbp+0x28]
	call	$_164
	mov	dword ptr [Parse_Pass+rip], 0
$_173:	call	$_104
	xor	eax, eax
	cmp	dword ptr [ModuleInfo+rip], eax
	ja	$_187
	mov	dword ptr [rbp-0x4], eax
	mov	rsi, qword ptr [SymTables+0x20+rip]
	jmp	$_175

$_174:	mov	eax, dword ptr [rsi+0x50]
	add	dword ptr [rbp-0x4], eax
	mov	rsi, qword ptr [rsi+0x70]
$_175:	test	rsi, rsi
	jnz	$_174
	mov	eax, dword ptr [rbp-0x4]
	cmp	byte ptr [ModuleInfo+0x1ED+rip], 0
	jnz	$_176
	cmp	eax, dword ptr [rbp-0x8]
	je	$_187
$_176:	mov	dword ptr [rbp-0x8], eax
	cmp	dword ptr [Parse_Pass+rip], 199
	jc	$_177
	mov	edx, 200
	mov	ecx, 3000
	call	asmerr@PLT
$_177:	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_183
	cmp	dword ptr [Options+0xA4+rip], 2
	jnz	$_182
	mov	rsi, qword ptr [SymTables+0x20+rip]
	jmp	$_181

$_178:	mov	rbx, qword ptr [rsi+0x68]
	test	rbx, rbx
	jz	$_180
	cmp	qword ptr [rbx+0x38], 0
	jz	$_179
	mov	rcx, qword ptr [rbx+0x38]
	call	QueueDeleteLinnum@PLT
$_179:	mov	qword ptr [rbx+0x38], 0
$_180:	mov	rsi, qword ptr [rsi+0x70]
$_181:	test	rsi, rsi
	jnz	$_178
	jmp	$_183

$_182:	lea	rcx, [LinnumQueue+rip]
	call	QueueDeleteLinnum@PLT
	mov	qword ptr [LinnumQueue+rip], 0
$_183:	mov	rdi, qword ptr [ModuleInfo+0x70+rip]
	call	rewind@PLT
	cmp	dword ptr [write_to_file+rip], 0
	jz	$_184
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_184
	call	omf_set_filepos@PLT
$_184:	inc	dword ptr [Parse_Pass+rip]
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_186
	cmp	dword ptr [UseSavedState+rip], 0
	jnz	$_185
	mov	rdi, qword ptr [ModuleInfo+0x80+rip]
	call	rewind@PLT
	call	LstInit@PLT
	jmp	$_186

$_185:	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_186
	cmp	byte ptr [Options+0xA1+rip], 0
	jz	$_186
	call	LstInit@PLT
$_186:	jmp	$_173

$_187:	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_188
	cmp	dword ptr [write_to_file+rip], 0
	jz	$_188
	lea	rcx, [ModuleInfo+rip]
	call	$_028
$_188:	call	LstWriteCRef@PLT
$_189:	call	$_165
	xor	eax, eax
	cmp	eax, dword ptr [ModuleInfo+rip]
	jnz	$_190
	inc	eax
$_190:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

Parse_Pass:
	.int   0x00000000

write_to_file:
	.int   0x00000000

cp_text1:
	.byte  0x5F, 0x54, 0x45, 0x58, 0x54, 0x00

cp_text2:
	.byte  0x2E, 0x74, 0x65, 0x78, 0x74, 0x00

cp_data1:
	.byte  0x5F, 0x44, 0x41, 0x54, 0x41, 0x00

cp_data2:
	.byte  0x2E, 0x64, 0x61, 0x74, 0x61, 0x00

cp_const:
	.byte  0x43, 0x4F, 0x4E, 0x53, 0x54, 0x00

cp_rdata:
	.byte  0x2E, 0x72, 0x64, 0x61, 0x74, 0x61, 0x00

cp_bss1:
	.byte  0x5F, 0x42, 0x53, 0x53, 0x00

cp_bss2:
	.byte  0x2E, 0x62, 0x73, 0x73, 0x00, 0x00

formatoptions:
	.quad  bin_init
	.quad  0x0000004E49420000
	.quad  omf_init
	.quad  0x000000464D4F0000
	.quad  coff_init
	.quad  0x000046464F430E12
	.quad  elf_init
	.quad  0x000000464C450F00

cst:
	.byte  0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.quad  cp_text1
	.quad  cp_text2
	.quad  0x0000000100000005
	.quad  cp_data1
	.quad  cp_data2
	.quad  0x0000000100000005
	.quad  cp_const
	.quad  cp_rdata
	.quad  0x0000000000000004
	.quad  cp_bss1
	.quad  cp_bss2

stt:
	.byte  0x01, 0x02, 0x02, 0x03

currentftype:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

remove_obj:
	.int   0x00000000

DS0000:
	.byte  0x77, 0x00

DS0001:
	.byte  0x69, 0x6D, 0x70, 0x6F, 0x72, 0x74, 0x20, 0x27
	.byte  0x25, 0x73, 0x27, 0x20, 0x20, 0x25, 0x73, 0x2E
	.byte  0x25, 0x73, 0x0A, 0x00

DS0002:
	.byte  0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x00

PrintEmptyLine:
	.byte  0x01

DS0003:
	.byte  0x72, 0x62, 0x00

DS0004:
	.byte  0x77, 0x62, 0x00

DS0005:
	.byte  0x2E, 0x73, 0x00

DS0006:
	.byte  0x70, 0x75, 0x62, 0x6C, 0x69, 0x63, 0x20, 0x49
	.byte  0x44, 0x44, 0x5F, 0x25, 0x73, 0x0A, 0x2E, 0x64
	.byte  0x61, 0x74, 0x61, 0x0A, 0x50, 0x49, 0x44, 0x44
	.byte  0x20, 0x74, 0x79, 0x70, 0x65, 0x64, 0x65, 0x66
	.byte  0x20, 0x70, 0x74, 0x72, 0x0A, 0x49, 0x44, 0x44
	.byte  0x5F, 0x25, 0x73, 0x20, 0x50, 0x49, 0x44, 0x44
	.byte  0x20, 0x25, 0x73, 0x5F, 0x52, 0x43, 0x0A, 0x25
	.byte  0x73, 0x5F, 0x52, 0x43, 0x20, 0x6C, 0x61, 0x62
	.byte  0x65, 0x6C, 0x20, 0x62, 0x79, 0x74, 0x65, 0x0A
	.byte  0x69, 0x6E, 0x63, 0x62, 0x69, 0x6E, 0x20, 0x3C
	.byte  0x25, 0x73, 0x3E, 0x0A, 0x00

DS0007:
	.byte  0x64, 0x62, 0x20, 0x30, 0x0A, 0x00

DS0008:
	.byte  0x65, 0x6E, 0x64, 0x0A, 0x00

DS0009:
	.byte  0x20, 0x41, 0x73, 0x73, 0x65, 0x6D, 0x62, 0x6C
	.byte  0x69, 0x6E, 0x67, 0x3A, 0x20, 0x25, 0x73, 0x0A
	.byte  0x00


.SECTION .bss
	.ALIGN	16

ModuleInfo:
	.zero	107 * 8

LinnumQueue:
	.zero	2 * 8

jmpenv:
	.zero	64 * 1

iddcfile:
	.zero	256 * 1


.att_syntax prefix
