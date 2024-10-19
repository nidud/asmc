
.intel_syntax noprefix

.global directive_tab

.extern LdrDirective
.extern EnumDirective
.extern ReturnDirective
.extern NewDirective
.extern PragmaDirective
.extern ClassDirective
.extern UndefDirective
.extern AssertDirective
.extern SwitchDirective
.extern ForDirective
.extern ContextDirective
.extern OptionDirective
.extern EqualSgnDirective
.extern EquDirective
.extern LabelDirective
.extern AssumeDirective
.extern GrpDir
.extern EndsDir
.extern SegmentDir
.extern AlignDirective
.extern OrgDirective
.extern InvokeDirective
.extern LocalDir
.extern EndpDir
.extern ProcDir
.extern PublicDirective
.extern ProtoDirective
.extern ExterndefDirective
.extern ExternDirective
.extern CommDirective
.extern RecordDirective
.extern TypedefDirective
.extern ExcFrameDirective
.extern SizeStrDir
.extern InStrDir
.extern SafeSEHDirective
.extern HllEndDir
.extern HllExitDir
.extern HllStartDir
.extern SimplifiedSegDir
.extern ListMacroDirective
.extern ListingDirective
.extern ErrorDirective
.extern EndDirective
.extern SubStrDir
.extern CatStrDir
.extern MacroDir
.extern PurgeDirective
.extern LoopDirective
.extern CondAsmDirective
.extern omf_OutSelect
.extern LstWriteSrcLine
.extern StructDirective
.extern CurrStruct
.extern EvalOperand
.extern Tokenize
.extern SearchFile
.extern ProcessFile
.extern sym_remove_table
.extern sym_add_table
.extern SpecialTable
.extern SymTables
.extern LclAlloc
.extern tstrcmp
.extern tstrcpy
.extern tstrlen
.extern tstrupr
.extern tprintf
.extern OutputByte
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern NameSpaceDirective
.extern QEnqueue
.extern SymFind
.extern SymCreate
.extern feof
.extern fseek
.extern fgetc
.extern fclose


.SECTION .text
	.ALIGN	16

StubDir:
	mov	eax, 4294967295
	ret

EchoDirective:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_001
	cmp	byte ptr [Options+0x96+rip], 0
	jnz	$_001
	imul	ecx, ecx, 24
	mov	rdx, qword ptr [rdx+rcx+0x28]
	lea	rcx, [DS0000+rip]
	call	tprintf@PLT
$_001:	mov	eax, 0
	leave
	ret

$_002:
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	mov	rbx, qword ptr [ModuleInfo+0x40+rip]
$_003:	test	rbx, rbx
	jz	$_005
	mov	rdx, rsi
	lea	rcx, [rbx+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_004
	lea	rax, [rbx+0x8]
	jmp	$_006

$_004:	mov	rbx, qword ptr [rbx]
	jmp	$_003

$_005:	mov	rcx, rsi
	call	tstrlen@PLT
	lea	ecx, [eax+0x10]
	call	LclAlloc@PLT
	mov	rbx, rax
	mov	rdx, rsi
	lea	rcx, [rbx+0x8]
	call	tstrcpy@PLT
	mov	rdx, rbx
	lea	rcx, [ModuleInfo+0x40+rip]
	call	QEnqueue@PLT
	lea	rax, [rbx+0x8]
$_006:	leave
	pop	rbx
	pop	rsi
	ret

IncludeDirective:
	mov	qword ptr [rsp+0x8], rcx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rdx
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_007
	call	LstWriteSrcLine@PLT
$_007:	inc	dword ptr [rbp+0x18]
	imul	edx, dword ptr [rbp+0x18], 24
	add	rdx, rbx
	cmp	byte ptr [rdx], 0
	jnz	$_008
	mov	ecx, 1017
	call	asmerr@PLT
	jmp	$_014

$_008:	cmp	byte ptr [rdx], 9
	jnz	$_010
	cmp	byte ptr [rdx+0x1], 60
	jnz	$_010
	cmp	byte ptr [rdx+0x18], 0
	jz	$_009
	mov	rdx, qword ptr [rdx+0x28]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_014

$_009:	mov	rcx, qword ptr [rdx+0x8]
	jmp	$_012

$_010:	mov	rcx, qword ptr [rdx+0x10]
	imul	eax, dword ptr [ModuleInfo+0x220+rip], 24
	mov	rdx, qword ptr [rbx+rax+0x10]
	dec	rdx
$_011:	cmp	rdx, rcx
	jbe	$_012
	movzx	eax, byte ptr [rdx]
	test	byte ptr [r15+rax], 0x08
	jz	$_012
	mov	byte ptr [rdx], ah
	dec	rdx
	jmp	$_011

$_012:	mov	edx, 1
	call	SearchFile@PLT
	test	rax, rax
	jz	$_013
	mov	rcx, rbx
	call	ProcessFile@PLT
$_013:	xor	eax, eax
$_014:	leave
	pop	rbx
	ret

IncludeLibDirective:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_015
	cmp	byte ptr [Options+0xD2+rip], 0
	jz	$_016
$_015:	xor	eax, eax
	jmp	$_022

$_016:	mov	rbx, rdx
	inc	ecx
	imul	ecx, ecx, 24
	cmp	byte ptr [rbx+rcx], 0
	jnz	$_017
	mov	ecx, 8012
	call	asmerr@PLT
$_017:	cmp	byte ptr [rbx+rcx], 9
	jnz	$_019
	cmp	byte ptr [rbx+rcx+0x1], 60
	jnz	$_019
	cmp	byte ptr [rbx+rcx+0x18], 0
	jz	$_018
	mov	rdx, qword ptr [rbx+rcx+0x28]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_022

$_018:	mov	rcx, qword ptr [rbx+rcx+0x8]
	jmp	$_021

$_019:	mov	rcx, qword ptr [rbx+rcx+0x10]
	imul	eax, dword ptr [ModuleInfo+0x220+rip], 24
	mov	rdx, qword ptr [rbx+rax+0x10]
	dec	rdx
$_020:	cmp	rdx, rcx
	jbe	$_021
	movzx	eax, byte ptr [rdx]
	test	byte ptr [r15+rax], 0x08
	jz	$_021
	mov	byte ptr [rdx], ah
	dec	rdx
	jmp	$_020

$_021:	call	$_002
	xor	eax, eax
$_022:	leave
	pop	rbx
	ret

IncBinDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	rbx, rdx
	inc	dword ptr [rbp+0x28]
	imul	eax, dword ptr [rbp+0x28], 24
	add	rbx, rax
	cmp	byte ptr [rbx], 0
	jnz	$_023
	mov	ecx, 1017
	call	asmerr@PLT
	jmp	$_042

$_023:	cmp	byte ptr [rbx], 9
	jnz	$_028
	mov	rdi, qword ptr [ModuleInfo+0x188+rip]
	cmp	byte ptr [rbx+0x1], 34
	jz	$_024
	cmp	byte ptr [rbx+0x1], 39
	jnz	$_025
$_024:	mov	ecx, dword ptr [rbx+0x4]
	mov	rsi, qword ptr [rbx+0x8]
	inc	rsi
	rep movsb
	mov	byte ptr [rdi], 0
	jmp	$_027

$_025:	cmp	byte ptr [rbx+0x1], 60
	jnz	$_026
	mov	ecx, dword ptr [rbx+0x4]
	mov	rsi, qword ptr [rbx+0x8]
	inc	ecx
	rep movsb
	jmp	$_027

$_026:	mov	ecx, 3015
	call	asmerr@PLT
	jmp	$_042

$_027:	jmp	$_029

$_028:	mov	ecx, 3015
	call	asmerr@PLT
	jmp	$_042

$_029:	xor	esi, esi
	mov	edi, 4294967295
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jne	$_034
	inc	dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_042
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_030
	mov	esi, dword ptr [rbp-0x68]
	jmp	$_031

$_030:	cmp	dword ptr [rbp-0x2C], -2
	jz	$_031
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_042

$_031:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 44
	jnz	$_034
	inc	dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_032
	jmp	$_042

$_032:	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_033
	mov	edi, dword ptr [rbp-0x68]
	jmp	$_034

$_033:	cmp	dword ptr [rbp-0x2C], -2
	jz	$_034
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_042

$_034:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_035
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_042

$_035:	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jnz	$_036
	mov	ecx, 2034
	call	asmerr@PLT
	jmp	$_042

$_036:	cmp	byte ptr [ModuleInfo+0x1EE+rip], 0
	jz	$_037
	mov	ecx, 1
	call	omf_OutSelect@PLT
$_037:	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	SearchFile@PLT
	test	rax, rax
	jz	$_041
	mov	qword ptr [rbp-0x70], rax
	mov	dword ptr [rbp-0x74], edi
	test	rsi, rsi
	jz	$_038
	xor	edx, edx
	mov	rdi, qword ptr [rbp-0x70]
	call	fseek@PLT
$_038:	cmp	dword ptr [rbp-0x74], 0
	jz	$_040
	mov	rdi, qword ptr [rbp-0x70]
	call	fgetc@PLT
	mov	ebx, eax
	cmp	ebx, -1
	jnz	$_039
	mov	rdi, qword ptr [rbp-0x70]
	call	feof@PLT
	test	rax, rax
	jnz	$_040
$_039:	movzx	ecx, bl
	call	OutputByte@PLT
	dec	dword ptr [rbp-0x74]
	jmp	$_038

$_040:	mov	rdi, qword ptr [rbp-0x70]
	call	fclose@PLT
$_041:	xor	eax, eax
$_042:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AliasDirective:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rdx
	inc	ecx
	imul	eax, ecx, 24
	add	rbx, rax
	cmp	byte ptr [rbx], 9
	jnz	$_043
	cmp	byte ptr [rbx+0x1], 60
	jz	$_044
$_043:	mov	ecx, 2051
	call	asmerr@PLT
	jmp	$_063

$_044:	cmp	byte ptr [rbx+0x18], 3
	jnz	$_045
	cmp	byte ptr [rbx+0x19], 45
	jz	$_046
$_045:	mov	rdx, qword ptr [rbx+0x20]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_063

$_046:	cmp	byte ptr [rbx+0x30], 9
	jnz	$_047
	cmp	byte ptr [rbx+0x31], 60
	jz	$_048
$_047:	mov	ecx, 2051
	call	asmerr@PLT
	jmp	$_063

$_048:	mov	rax, qword ptr [rbx+0x38]
	mov	qword ptr [rbp-0x8], rax
	cmp	byte ptr [rbx+0x48], 0
	jz	$_049
	mov	rdx, qword ptr [rbx+0x50]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_063

$_049:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rsi, rax
	test	rsi, rsi
	jz	$_050
	cmp	byte ptr [rsi+0x18], 0
	jne	$_055
$_050:	mov	rcx, qword ptr [rbp-0x8]
	call	SymFind@PLT
	mov	rdi, rax
	test	rdi, rdi
	jnz	$_051
	mov	rcx, qword ptr [rbp-0x8]
	call	SymCreate@PLT
	mov	rdi, rax
	mov	byte ptr [rdi+0x18], 0
	mov	rdx, rdi
	lea	rcx, [SymTables+rip]
	call	sym_add_table@PLT
	jmp	$_052

$_051:	cmp	byte ptr [rdi+0x18], 0
	jz	$_052
	cmp	byte ptr [rdi+0x18], 1
	jz	$_052
	cmp	byte ptr [rdi+0x18], 2
	jz	$_052
	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2217
	call	asmerr@PLT
	jmp	$_063

$_052:	test	rsi, rsi
	jnz	$_053
	mov	rcx, qword ptr [rbx+0x8]
	call	SymCreate@PLT
	mov	rsi, rax
	jmp	$_054

$_053:	mov	rdx, rsi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
$_054:	mov	byte ptr [rsi+0x18], 8
	mov	qword ptr [rsi+0x28], rdi
	mov	al, byte ptr [rdi+0x1A]
	mov	byte ptr [rsi+0x1A], al
	mov	rdx, rsi
	lea	rcx, [SymTables+0x50+rip]
	call	sym_add_table@PLT
	xor	eax, eax
	jmp	$_063

$_055:	xor	eax, eax
	cmp	byte ptr [rsi+0x18], 8
	jz	$_056
	inc	eax
	jmp	$_057

$_056:	mov	rdi, qword ptr [rsi+0x28]
	mov	rdx, qword ptr [rbp-0x8]
	mov	rcx, qword ptr [rdi+0x8]
	call	tstrcmp@PLT
$_057:	test	eax, eax
	jz	$_058
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_063

$_058:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_062
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_059
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_062
$_059:	mov	rdi, qword ptr [rsi+0x28]
	cmp	byte ptr [rdi+0x18], 0
	jnz	$_060
	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_063

	jmp	$_062

$_060:	cmp	byte ptr [rdi+0x18], 2
	jz	$_062
	cmp	byte ptr [rdi+0x18], 1
	jnz	$_061
	test	dword ptr [rdi+0x14], 0x80
	jnz	$_062
$_061:	mov	rdx, qword ptr [rbp-0x8]
	mov	ecx, 2217
	call	asmerr@PLT
	jmp	$_063

$_062:	xor	eax, eax
$_063:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

NameDirective:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_065
	imul	ecx, ecx, 24
	lea	rdx, [rdx+rcx+0x18]
	mov	ecx, dword ptr [rdx+0x4]
	mov	al, byte ptr [rdx]
	cmp	qword ptr [CurrStruct+rip], 0
	jnz	$_064
	cmp	al, 58
	jz	$_064
	cmp	al, 3
	jnz	$_065
	cmp	ecx, 516
	jz	$_064
	cmp	ecx, 498
	jz	$_064
	cmp	ecx, 497
	jz	$_064
	cmp	ecx, 499
	jz	$_064
	cmp	ecx, 500
	jz	$_064
	cmp	ecx, 501
	jnz	$_065
$_064:	mov	rdx, qword ptr [rdx-0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_066

$_065:	xor	eax, eax
$_066:	leave
	ret

RadixDirective:
	mov	qword ptr [rsp+0x8], rcx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	rbx, rdx
	mov	al, byte ptr [ModuleInfo+0x1C4+rip]
	mov	byte ptr [rbp-0x69], al
	mov	byte ptr [ModuleInfo+0x1C4+rip], 10
	inc	dword ptr [rbp+0x18]
	imul	ecx, dword ptr [rbp+0x18], 24
	mov	r9d, 1
	mov	r8, rbx
	mov	edx, dword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbx+rcx+0x10]
	call	Tokenize@PLT
	mov	al, byte ptr [rbp-0x69]
	mov	byte ptr [ModuleInfo+0x1C4+rip], al
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, rbx
	lea	rcx, [rbp+0x18]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_067
	jmp	$_072

$_067:	cmp	dword ptr [rbp-0x2C], 0
	jz	$_068
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_072

$_068:	imul	edx, dword ptr [rbp+0x18], 24
	cmp	byte ptr [rbx+rdx], 0
	jz	$_069
	mov	rdx, qword ptr [rbx+rdx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_072

$_069:	cmp	dword ptr [rbp-0x68], 16
	jg	$_070
	cmp	dword ptr [rbp-0x68], 2
	jl	$_070
	cmp	dword ptr [rbp-0x64], 0
	jz	$_071
$_070:	mov	ecx, 2113
	call	asmerr@PLT
	jmp	$_072

$_071:	mov	eax, dword ptr [rbp-0x68]
	mov	byte ptr [ModuleInfo+0x1C4+rip], al
	mov	eax, 0
$_072:	leave
	pop	rbx
	ret

SegOrderDirective:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	imul	ecx, ecx, 24
	add	rcx, rdx
	cmp	byte ptr [rcx+0x18], 0
	jz	$_073
	mov	rdx, qword ptr [rcx+0x28]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_078

$_073:	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_074
	cmp	dword ptr [Options+0xA4+rip], 3
	jz	$_074
	cmp	dword ptr [Options+0xA4+rip], 0
	jnz	$_076
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 2
	jnz	$_076
$_074:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_075
	mov	rcx, qword ptr [rcx+0x8]
	call	tstrupr@PLT
	mov	rdx, rax
	mov	ecx, 3006
	call	asmerr@PLT
$_075:	jmp	$_077

$_076:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rcx+0x4], 12
	mov	eax, dword ptr [r11+rax+0x4]
	mov	byte ptr [ModuleInfo+0x1BA+rip], al
$_077:	xor	eax, eax
$_078:	leave
	ret


.SECTION .data
	.ALIGN	16

directive_tab:
	.quad  CondAsmDirective
	.quad  LoopDirective
	.quad  PurgeDirective
	.quad  IncludeDirective
	.quad  MacroDir
	.quad  CatStrDir
	.quad  SubStrDir
	.quad  StubDir
	.quad  StubDir
	.quad  EndDirective
	.quad  ErrorDirective
	.quad  ListingDirective
	.quad  ListMacroDirective
	.quad  SegOrderDirective
	.quad  SimplifiedSegDir
	.quad  HllStartDir
	.quad  HllExitDir
	.quad  HllEndDir
	.quad  RadixDirective
	.quad  SafeSEHDirective
	.quad  InStrDir
	.quad  SizeStrDir
	.quad  ExcFrameDirective
	.quad  StructDirective
	.quad  TypedefDirective
	.quad  RecordDirective
	.quad  CommDirective
	.quad  ExternDirective
	.quad  ExterndefDirective
	.quad  ProtoDirective
	.quad  PublicDirective
	.quad  ProcDir
	.quad  EndpDir
	.quad  LocalDir
	.quad  InvokeDirective
	.quad  OrgDirective
	.quad  AlignDirective
	.quad  SegmentDir
	.quad  EndsDir
	.quad  GrpDir
	.quad  AssumeDirective
	.quad  LabelDirective
	.quad  AliasDirective
	.quad  EchoDirective
	.quad  EquDirective
	.quad  EqualSgnDirective
	.quad  IncBinDirective
	.quad  IncludeLibDirective
	.quad  NameDirective
	.quad  OptionDirective
	.quad  ContextDirective
	.quad  ForDirective
	.quad  SwitchDirective
	.quad  AssertDirective
	.quad  UndefDirective
	.quad  ClassDirective
	.quad  PragmaDirective
	.quad  NewDirective
	.quad  ReturnDirective
	.quad  EnumDirective
	.quad  NameSpaceDirective
	.quad  LdrDirective

DS0000:
	.byte  0x25, 0x73, 0x0A, 0x00


.att_syntax prefix
