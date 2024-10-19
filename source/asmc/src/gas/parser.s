
.intel_syntax noprefix

.global sym_add_table
.global sym_remove_table
.global sym_ext2int
.global GetLangType
.global SizeFromRegister
.global SizeFromMemtype
.global MemtypeFromSize
.global OperandSize
.global set_frame
.global set_frame2
.global segm_override
.global idata_fixup
.global ParseLine
.global ProcessFile
.global SegOverride
.global SymTables

.extern EnumDirective
.extern CurrEnum
.extern NewDirective
.extern imm2xmm
.extern mem2mem
.extern PublicDirective
.extern ProcType
.extern ExpandHllProcEx
.extern ExpandLine
.extern process_branch
.extern directive_tab
.extern ResWordTable
.extern Frame_Datum
.extern Frame_Type
.extern vex_flags
.extern opnd_clstab
.extern ProcStatus
.extern ProcessOperator
.extern GetOperator
.extern HandleIndirection
.extern quad_resize
.extern AddPublicData
.extern omf_OutSelect
.extern StoreLine
.extern UseSavedState
.extern StoreState
.extern data_dir
.extern LstWrite
.extern LstWriteSrcLine
.extern Tokenize
.extern GetTextLine
.extern write_prologue
.extern RetInstr
.extern CurrProc
.extern GetOverrideAssume
.extern GetAssume
.extern StdAssumeTable
.extern SegAssumeTable
.extern GetGroup
.extern GetCurrOffset
.extern GetSymOfssize
.extern CreateLabel
.extern CurrStruct
.extern EmitConstError
.extern EvalOperand
.extern codegen
.extern GetResWName
.extern RemoveResWord
.extern PreprocessLine
.extern WritePreprocessedLine
.extern optable_idx
.extern SpecialTable
.extern InstrTable
.extern SetFixupFrame
.extern CreateFixup
.extern MemFree
.extern MemAlloc
.extern tstricmp
.extern tstrcat
.extern tstrcpy
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind


.SECTION .text
	.ALIGN	16

sym_add_table:
	xor	eax, eax
	cmp	qword ptr [rcx], rax
	jnz	$_001
	mov	qword ptr [rcx], rdx
	mov	qword ptr [rcx+0x8], rdx
	mov	qword ptr [rdx+0x70], rax
	mov	qword ptr [rdx+0x78], rax
	jmp	$_002

$_001:	mov	rax, qword ptr [rcx+0x8]
	mov	qword ptr [rdx+0x78], rax
	mov	qword ptr [rax+0x70], rdx
	mov	qword ptr [rcx+0x8], rdx
	mov	qword ptr [rdx+0x70], 0
$_002:	ret

sym_remove_table:
	push	rbx
	push	rbp
	mov	rbp, rsp
	cmp	qword ptr [rdx+0x78], 0
	jz	$_003
	mov	rax, qword ptr [rdx+0x70]
	mov	rbx, qword ptr [rdx+0x78]
	mov	qword ptr [rbx+0x70], rax
$_003:	cmp	qword ptr [rdx+0x70], 0
	jz	$_004
	mov	rax, qword ptr [rdx+0x78]
	mov	rbx, qword ptr [rdx+0x70]
	mov	qword ptr [rbx+0x78], rax
$_004:	cmp	qword ptr [rcx], rdx
	jnz	$_005
	mov	rax, qword ptr [rdx+0x70]
	mov	qword ptr [rcx], rax
$_005:	cmp	qword ptr [rcx+0x8], rdx
	jnz	$_006
	mov	rax, qword ptr [rdx+0x78]
	mov	qword ptr [rcx+0x8], rax
$_006:	mov	qword ptr [rdx+0x70], 0
	mov	qword ptr [rdx+0x78], 0
	leave
	pop	rbx
	ret

sym_ext2int:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	test	byte ptr [rcx+0x15], 0x08
	jnz	$_007
	test	dword ptr [rcx+0x14], 0x80
	jnz	$_007
	or	dword ptr [rcx+0x14], 0x80
	call	AddPublicData@PLT
$_007:	mov	rdx, qword ptr [rbp+0x10]
	lea	rcx, [SymTables+0x10+rip]
	call	sym_remove_table
	mov	rcx, qword ptr [rbp+0x10]
	test	byte ptr [rcx+0x15], 0x08
	jnz	$_008
	mov	dword ptr [rcx+0x38], 0
$_008:	mov	byte ptr [rcx+0x18], 1
	leave
	ret

GetLangType:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	imul	eax, dword ptr [rcx], 24
	add	rdx, rax
	mov	rax, qword ptr [rdx+0x8]
	mov	eax, dword ptr [rax]
	or	al, 0x20
	cmp	byte ptr [rdx], 8
	jnz	$_010
	cmp	ax, 99
	jnz	$_010
	cmp	dword ptr [rdx-0x14], 508
	jnz	$_009
	cmp	byte ptr [rdx+0x18], 58
	jz	$_010
$_009:	mov	byte ptr [rdx], 7
	mov	dword ptr [rdx+0x4], 277
	mov	byte ptr [rdx+0x1], 1
$_010:	cmp	byte ptr [rdx], 7
	jnz	$_011
	cmp	dword ptr [rdx+0x4], 277
	jc	$_011
	cmp	dword ptr [rdx+0x4], 286
	ja	$_011
	inc	dword ptr [rcx]
	mov	al, byte ptr [rdx+0x1]
	mov	rcx, qword ptr [rbp+0x20]
	mov	byte ptr [rcx], al
	xor	eax, eax
	jmp	$_012

$_011:	mov	rax, -1
$_012:	leave
	ret

SizeFromRegister:
	lea	rdx, [SpecialTable+rip]
	imul	eax, ecx, 12
	add	rdx, rax
	mov	eax, dword ptr [rdx+0x4]
	and	eax, 0x7F
	jnz	$_013
	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	test	byte ptr [rdx+0x3], 0x0C
	jnz	$_013
	mov	eax, 4
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_013
	mov	eax, 8
$_013:	ret

SizeFromMemtype:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	movzx	eax, cl
	cmp	al, 63
	jnz	$_014
	mov	eax, 64
	jmp	$_026

$_014:	and	ecx, 0x80
	jnz	$_015
	and	eax, 0x1F
	inc	eax
	jmp	$_026

$_015:	mov	ecx, edx
	cmp	ecx, 254
	jnz	$_016
	movzx	ecx, byte ptr [ModuleInfo+0x1CC+rip]
$_016:	mov	edx, 2
	shl	edx, cl
	jmp	$_025

$_017:	mov	eax, edx
	jmp	$_026

$_018:	lea	eax, [rdx+0x2]
	jmp	$_026

$_019:	mov	eax, edx
	mov	rcx, qword ptr [rbp+0x20]
	test	rcx, rcx
	jz	$_020
	cmp	byte ptr [rcx+0x1C], 0
	jz	$_020
	add	eax, 2
$_020:	jmp	$_026

$_021:	mov	eax, edx
	movzx	ecx, byte ptr [ModuleInfo+0x1B5+rip]
	mov	edx, 1
	shl	edx, cl
	and	edx, 0x68
	jz	$_022
	add	eax, 2
$_022:	jmp	$_026

$_023:	mov	rcx, qword ptr [rbp+0x20]
	test	rcx, rcx
	jz	$_024
	mov	eax, dword ptr [rcx+0x50]
	jmp	$_026

$_024:	xor	eax, eax
	jmp	$_026

$_025:	cmp	eax, 129
	jz	$_017
	cmp	eax, 130
	jz	$_018
	cmp	eax, 128
	jz	$_019
	cmp	eax, 195
	jz	$_021
	cmp	eax, 196
	jz	$_023
	jmp	$_024

$_026:
	leave
	ret

MemtypeFromSize:
	push	rbx
	push	rbp
	mov	rbp, rsp
	lea	rbx, [SpecialTable+rip]
	add	rbx, 2460
$_027:	cmp	byte ptr [rbx+0xB], 6
	jnz	$_030
	mov	al, byte ptr [rbx+0xA]
	and	eax, 0x80
	jnz	$_029
	mov	al, byte ptr [rbx+0xA]
	cmp	al, 63
	jz	$_028
	and	eax, 0x1F
$_028:	inc	eax
	cmp	eax, ecx
	jnz	$_029
	mov	al, byte ptr [rbx+0xA]
	mov	byte ptr [rdx], al
	xor	eax, eax
	jmp	$_031

$_029:	add	rbx, 12
	jmp	$_027

$_030:	mov	rax, -1
$_031:	leave
	pop	rbx
	ret

OperandSize:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	jmp	$_045

$_032:	xor	eax, eax
	jmp	$_047

$_033:	mov	cl, byte ptr [rdx+0x60]
	xor	r8d, r8d
	movzx	edx, byte ptr [rdx+0x63]
	movzx	ecx, cl
	call	SizeFromMemtype
	jmp	$_047

$_034:	mov	eax, 1
	jmp	$_047

$_035:	mov	eax, 2
	jmp	$_047

$_036:	mov	eax, 4
	jmp	$_047

$_037:	mov	eax, 8
	jmp	$_047

$_038:	mov	eax, 6
	jmp	$_047

$_039:	mov	eax, 10
	jmp	$_047

$_040:	mov	eax, 16
	jmp	$_047

$_041:	mov	eax, 32
	jmp	$_047

$_042:	mov	eax, 64
	jmp	$_047

$_043:	mov	eax, 4
	cmp	byte ptr [rdx+0x63], 2
	jnz	$_044
	mov	eax, 8
$_044:	jmp	$_047

	jmp	$_046

$_045:	test	ecx, ecx
	je	$_032
	cmp	ecx, 4202240
	je	$_033
	test	ecx, 0x10101
	jne	$_034
	test	ecx, 0xC020202
	jne	$_035
	test	ecx, 0x40404
	jne	$_036
	test	ecx, 0x188808
	jne	$_037
	test	ecx, 0x40200000
	jne	$_038
	test	ecx, 0x30400000
	jne	$_039
	test	ecx, 0x1010
	jne	$_040
	test	ecx, 0x2020
	jne	$_041
	test	ecx, 0x4040
	jne	$_042
	test	ecx, 0x2000000
	jne	$_043
$_046:	xor	eax, eax
$_047:	leave
	ret

$_048:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	ecx, 12
	jnz	$_051
	cmp	edx, 15
	jnz	$_049
	xor	eax, eax
	jmp	$_056

$_049:	cmp	edx, 16
	jnz	$_050
	mov	eax, 1
	jmp	$_056

$_050:	jmp	$_055

$_051:	cmp	ecx, 14
	jnz	$_054
	cmp	edx, 15
	jnz	$_052
	mov	eax, 2
	jmp	$_056

$_052:	cmp	edx, 16
	jnz	$_053
	mov	eax, 3
	jmp	$_056

$_053:	jmp	$_055

$_054:	mov	ecx, 2030
	call	asmerr@PLT
	jmp	$_056

$_055:	mov	ecx, 2029
	call	asmerr@PLT
$_056:	leave
	ret

$_057:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	test	rdx, rdx
	jz	$_058
	cmp	byte ptr [rdx+0x18], 0
	jnz	$_058
	jmp	$_064

$_058:	lea	r9, [rbp-0x10]
	mov	r8d, dword ptr [rbp+0x20]
	mov	rcx, qword ptr [SegOverride+rip]
	call	GetAssume@PLT
	mov	dword ptr [rbp-0x4], eax
	xor	edx, edx
	mov	rcx, qword ptr [rbp-0x10]
	call	SetFixupFrame@PLT
	mov	rdx, qword ptr [rbp+0x18]
	cmp	dword ptr [rbp-0x4], -2
	jnz	$_063
	test	rdx, rdx
	jz	$_061
	cmp	qword ptr [rdx+0x30], 0
	jz	$_059
	mov	rdx, qword ptr [rdx+0x8]
	mov	ecx, 2074
	call	asmerr@PLT
	jmp	$_060

$_059:	mov	rax, qword ptr [rbp+0x10]
	mov	ecx, dword ptr [rbp+0x20]
	mov	dword ptr [rax+0x4], ecx
$_060:	jmp	$_062

$_061:	mov	rdx, qword ptr [SegOverride+rip]
	mov	rdx, qword ptr [rdx+0x8]
	mov	ecx, 2074
	call	asmerr@PLT
$_062:	jmp	$_064

$_063:	cmp	dword ptr [rbp+0x20], -2
	jz	$_064
	mov	rax, qword ptr [rbp+0x10]
	mov	ecx, dword ptr [rbp-0x4]
	mov	dword ptr [rax+0x4], ecx
$_064:	leave
	ret

$_065:
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rbx, rcx
	mov	ecx, edx
	mov	rax, qword ptr [rbx+0x58]
	movzx	eax, byte ptr [rax+0x2]
	and	eax, 0x07
	cmp	eax, 2
	je	$_080
	cmp	eax, 3
	je	$_080
	cmp	word ptr [rbx+0xE], 711
	jnz	$_066
	mov	dword ptr [rbx+0x4], -2
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x28]
	call	SetFixupFrame@PLT
	jmp	$_080

$_066:	jmp	$_069

$_067:	mov	dword ptr [rbp-0x4], 2
	jmp	$_070

$_068:	mov	dword ptr [rbp-0x4], 3
	jmp	$_070

$_069:	cmp	ecx, 14
	jz	$_067
	cmp	ecx, 22
	jz	$_067
	cmp	ecx, 21
	jz	$_067
	jmp	$_068

$_070:	cmp	dword ptr [rbx+0x4], -2
	jz	$_076
	mov	ecx, dword ptr [rbx+0x4]
	call	GetOverrideAssume@PLT
	mov	qword ptr [rbp-0x10], rax
	cmp	qword ptr [rbp+0x28], 0
	jz	$_072
	mov	rax, qword ptr [rbp-0x10]
	test	rax, rax
	jnz	$_071
	mov	rax, qword ptr [rbp+0x28]
$_071:	xor	edx, edx
	mov	rcx, rax
	call	SetFixupFrame@PLT
	jmp	$_075

$_072:	cmp	dword ptr [rbp+0x30], 0
	jz	$_075
	cmp	qword ptr [rbp-0x10], 0
	jz	$_073
	mov	rcx, qword ptr [rbp-0x10]
	call	GetSymOfssize@PLT
	cmp	byte ptr [rbx+0x63], al
	setne	al
	mov	byte ptr [rbx+0x9], al
	jmp	$_075

$_073:	cmp	byte ptr [ModuleInfo+0x1D6+rip], 0
	jz	$_074
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	cmp	byte ptr [rbx+0x63], al
	setne	al
	mov	byte ptr [rbx+0x9], al
	jmp	$_075

$_074:	mov	al, byte ptr [ModuleInfo+0x1CD+rip]
	cmp	byte ptr [rbx+0x63], al
	setne	al
	mov	byte ptr [rbx+0x9], al
$_075:	jmp	$_079

$_076:	cmp	qword ptr [rbp+0x28], 0
	jnz	$_077
	cmp	qword ptr [SegOverride+rip], 0
	jz	$_078
$_077:	mov	r8d, dword ptr [rbp-0x4]
	mov	rdx, qword ptr [rbp+0x28]
	mov	rcx, rbx
	call	$_057
$_078:	cmp	qword ptr [rbp+0x28], 0
	jnz	$_079
	cmp	qword ptr [SegOverride+rip], 0
	jz	$_079
	mov	rax, qword ptr [ModuleInfo+0x200+rip]
	cmp	qword ptr [SegOverride+rip], rax
	jz	$_079
	cmp	byte ptr [rbx+0x63], 2
	jz	$_079
	mov	rcx, qword ptr [SegOverride+rip]
	call	GetSymOfssize@PLT
	cmp	byte ptr [rbx+0x63], al
	setne	al
	mov	byte ptr [rbx+0x9], al
$_079:	mov	eax, dword ptr [rbp-0x4]
	cmp	dword ptr [rbx+0x4], eax
	jnz	$_080
	mov	dword ptr [rbx+0x4], -2
$_080:	leave
	pop	rbx
	ret

set_frame:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rax, qword ptr [SegOverride+rip]
	test	rax, rax
	jz	$_081
	mov	rcx, rax
$_081:	xor	edx, edx
	call	SetFixupFrame@PLT
	leave
	ret

set_frame2:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rax, qword ptr [SegOverride+rip]
	test	rax, rax
	jz	$_082
	mov	rcx, rax
$_082:	mov	edx, 1
	call	SetFixupFrame@PLT
	leave
	ret

$_083:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	byte ptr [rbp-0x6], 0
	mov	byte ptr [rbp-0x9], 0
	mov	byte ptr [rbp-0xA], 0
	mov	byte ptr [rbp-0xB], 0
	mov	rsi, qword ptr [rbp+0x28]
	imul	ebx, dword ptr [rbp+0x30], 24
	cmp	dword ptr [rbp+0x48], 131
	jnz	$_084
	or	byte ptr [rsi+0x66], 0xFFFFFF80
$_084:	cmp	qword ptr [rsi+rbx+0x18], 0
	jz	$_085
	mov	byte ptr [rbp-0x5], -128
	jmp	$_090

$_085:	cmp	dword ptr [rsi+rbx+0x20], 0
	jz	$_086
	cmp	dword ptr [rbp+0x48], 131
	jnz	$_087
$_086:	mov	byte ptr [rbp-0x5], 0
	jmp	$_090

$_087:	cmp	dword ptr [rsi+rbx+0x20], 127
	jg	$_088
	cmp	dword ptr [rsi+rbx+0x20], -128
	jge	$_089
$_088:	mov	byte ptr [rbp-0x5], -128
	jmp	$_090

$_089:	mov	byte ptr [rbp-0x5], 64
$_090:	cmp	dword ptr [rbp+0x40], -2
	jnz	$_093
	cmp	dword ptr [rbp+0x48], -2
	jnz	$_093
	or	byte ptr [rsi+0x66], 0x02
	mov	byte ptr [rbp-0x5], 0
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x50]
	mov	edx, 28
	mov	rcx, rsi
	call	$_065
	mov	byte ptr [rbp-0x6], 5
	mov	rax, qword ptr [rsi+rbx+0x18]
	test	rax, rax
	jnz	$_091
	mov	byte ptr [rbp-0x6], 4
	mov	byte ptr [rsi+0x62], 37
	jmp	$_092

$_091:	cmp	byte ptr [rax+0x18], 6
	jnz	$_092
	mov	byte ptr [rax+0x18], 3
$_092:	jmp	$_118

$_093:	cmp	dword ptr [rbp+0x40], -2
	jne	$_105
	cmp	dword ptr [rbp+0x48], -2
	je	$_105
	jmp	$_103

$_094:	mov	byte ptr [rbp-0x6], 4
	jmp	$_104

$_095:	mov	byte ptr [rbp-0x6], 5
	jmp	$_104

$_096:	mov	byte ptr [rbp-0x6], 6
	cmp	byte ptr [rbp-0x5], 0
	jnz	$_097
	cmp	dword ptr [rbp+0x48], 131
	jz	$_097
	mov	byte ptr [rbp-0x5], 64
$_097:	jmp	$_104

$_098:	mov	byte ptr [rbp-0x6], 7
	jmp	$_104

$_099:	mov	byte ptr [rbp-0x7], 5
	cmp	dword ptr [rbp+0x48], 131
	jz	$_100
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x48], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0x7], al
$_100:	mov	al, byte ptr [rbp-0x7]
	shr	al, 3
	mov	byte ptr [rbp-0x9], al
	and	byte ptr [rbp-0x7], 0x07
	mov	al, byte ptr [rbp-0x7]
	mov	byte ptr [rbp-0x6], al
	cmp	byte ptr [rbp-0x7], 4
	jnz	$_101
	mov	byte ptr [rsi+0x62], 36
	jmp	$_102

$_101:	cmp	byte ptr [rbp-0x7], 5
	jnz	$_102
	cmp	byte ptr [rbp-0x5], 0
	jnz	$_102
	cmp	dword ptr [rbp+0x48], 131
	jz	$_102
	mov	byte ptr [rbp-0x5], 64
$_102:	mov	al, byte ptr [rbp-0x9]
	mov	byte ptr [rbp-0xB], al
	jmp	$_104

$_103:	cmp	dword ptr [rbp+0x48], 15
	je	$_094
	cmp	dword ptr [rbp+0x48], 16
	je	$_095
	cmp	dword ptr [rbp+0x48], 14
	je	$_096
	cmp	dword ptr [rbp+0x48], 12
	je	$_098
	jmp	$_099

$_104:	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x50]
	mov	edx, dword ptr [rbp+0x48]
	mov	rcx, rsi
	call	$_065
	jmp	$_118

$_105:	cmp	dword ptr [rbp+0x40], -2
	je	$_107
	cmp	dword ptr [rbp+0x48], -2
	jne	$_107
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x40], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0x8], al
	mov	al, byte ptr [rbp-0x8]
	shr	al, 3
	mov	byte ptr [rbp-0xA], al
	and	byte ptr [rbp-0x8], 0x07
	mov	byte ptr [rbp-0x5], 0
	mov	byte ptr [rbp-0x6], 4
	mov	al, byte ptr [rbp-0x8]
	shl	al, 3
	or	al, byte ptr [rbp+0x38]
	or	al, 0x05
	mov	byte ptr [rsi+0x62], al
	mov	al, byte ptr [rbp-0xA]
	shl	al, 1
	mov	byte ptr [rbp-0xB], al
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x50]
	mov	edx, 28
	mov	rcx, rsi
	call	$_065
	mov	rax, qword ptr [rsi+0x58]
	test	byte ptr [rax+0x3], 0x08
	jz	$_106
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x40], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rsi+0x64], al
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x40], 12
	cmp	dword ptr [r11+rax], 16
	jbe	$_106
	or	byte ptr [rsi+0x64], 0x40
$_106:	jmp	$_118

$_107:	mov	byte ptr [rbp-0x7], 5
	cmp	dword ptr [rbp+0x48], 131
	jz	$_108
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x48], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0x7], al
$_108:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x40], 12
	mov	al, byte ptr [r11+rax+0xA]
	mov	byte ptr [rbp-0x8], al
	mov	al, byte ptr [rbp-0x7]
	shr	al, 3
	mov	byte ptr [rbp-0x9], al
	mov	al, byte ptr [rbp-0x8]
	shr	al, 3
	mov	byte ptr [rbp-0xA], al
	and	byte ptr [rbp-0x7], 0x07
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x48], 12
	mov	ecx, dword ptr [r11+rax+0x4]
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x40], 12
	and	ecx, dword ptr [r11+rax+0x4]
	and	ecx, 0x7F
	test	ecx, ecx
	jnz	$_111
	mov	rcx, qword ptr [rsi+0x58]
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x40], 12
	cmp	dword ptr [r11+rax], 8
	jbe	$_110
	test	byte ptr [rcx+0x3], 0x08
	jz	$_110
	mov	al, byte ptr [rbp-0x8]
	mov	byte ptr [rsi+0x64], al
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp+0x40], 12
	cmp	dword ptr [r11+rax], 16
	jbe	$_109
	or	byte ptr [rsi+0x64], 0x40
$_109:	jmp	$_111

$_110:	mov	ecx, 2082
	call	asmerr@PLT
	jmp	$_122

$_111:	and	byte ptr [rbp-0x8], 0x07
	jmp	$_117

$_112:	mov	edx, dword ptr [rbp+0x48]
	mov	ecx, dword ptr [rbp+0x40]
	call	$_048
	cmp	eax, -1
	je	$_122
	mov	byte ptr [rbp-0x6], al
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x50]
	mov	edx, dword ptr [rbp+0x40]
	mov	rcx, rsi
	call	$_065
	jmp	$_118

$_113:	mov	edx, dword ptr [rbp+0x40]
	mov	ecx, dword ptr [rbp+0x48]
	call	$_048
	cmp	eax, -1
	je	$_122
	mov	byte ptr [rbp-0x6], al
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x50]
	mov	edx, dword ptr [rbp+0x48]
	mov	rcx, rsi
	call	$_065
	jmp	$_118

$_114:	mov	ecx, 2032
	call	asmerr@PLT
	jmp	$_122

$_115:	cmp	byte ptr [rbp-0x7], 5
	jnz	$_116
	cmp	dword ptr [rbp+0x48], 131
	jz	$_116
	cmp	byte ptr [rbp-0x5], 0
	jnz	$_116
	mov	byte ptr [rbp-0x5], 64
$_116:	or	byte ptr [rbp-0x6], 0x04
	mov	al, byte ptr [rbp-0x8]
	shl	al, 3
	or	al, byte ptr [rbp+0x38]
	or	al, byte ptr [rbp-0x7]
	mov	byte ptr [rsi+0x62], al
	mov	al, byte ptr [rbp-0xA]
	shl	al, 1
	add	al, byte ptr [rbp-0x9]
	mov	byte ptr [rbp-0xB], al
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x50]
	mov	edx, dword ptr [rbp+0x48]
	mov	rcx, rsi
	call	$_065
	jmp	$_118

$_117:	cmp	dword ptr [rbp+0x40], 12
	je	$_112
	cmp	dword ptr [rbp+0x40], 14
	je	$_112
	cmp	dword ptr [rbp+0x40], 15
	je	$_113
	cmp	dword ptr [rbp+0x40], 16
	je	$_113
	cmp	dword ptr [rbp+0x40], 119
	je	$_114
	cmp	dword ptr [rbp+0x40], 131
	je	$_114
	cmp	dword ptr [rbp+0x40], 21
	je	$_114
	jmp	$_115

$_118:	cmp	dword ptr [rbp+0x48], 131
	jnz	$_119
	and	byte ptr [rbp-0x5], 0x07
$_119:	cmp	dword ptr [rbp+0x30], 1
	jnz	$_120
	mov	al, byte ptr [rbp-0x6]
	shl	al, 3
	mov	cl, byte ptr [rsi+0x61]
	and	cl, 0x07
	or	al, byte ptr [rbp-0x5]
	or	al, cl
	mov	byte ptr [rsi+0x61], al
	mov	al, byte ptr [rbp-0xB]
	mov	cl, al
	mov	dl, al
	shr	al, 2
	and	cl, 0x02
	and	dl, 0x01
	shl	dl, 2
	or	al, cl
	or	al, dl
	or	byte ptr [rsi+0x8], al
	jmp	$_121

$_120:	cmp	dword ptr [rbp+0x30], 0
	jnz	$_121
	mov	al, byte ptr [rbp-0x5]
	or	al, byte ptr [rbp-0x6]
	mov	byte ptr [rsi+0x61], al
	mov	al, byte ptr [rbp-0xB]
	or	byte ptr [rsi+0x8], al
$_121:	xor	eax, eax
$_122:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

segm_override:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, qword ptr [rbp+0x30]
	mov	rdi, qword ptr [rcx+0x30]
	test	rdi, rdi
	je	$_129
	cmp	byte ptr [rdi], 2
	jnz	$_126
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rdi+0x4], 12
	movzx	ebx, byte ptr [r11+rax+0xA]
	imul	eax, ebx, 16
	lea	rcx, [SegAssumeTable+rip]
	cmp	byte ptr [rcx+rax+0x8], 0
	jz	$_123
	mov	ecx, 2108
	call	asmerr@PLT
	jmp	$_130

$_123:	test	rsi, rsi
	jz	$_124
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_124
	cmp	ebx, 4
	jnc	$_124
	mov	ecx, 2202
	call	asmerr@PLT
	jmp	$_130

$_124:	mov	ecx, ebx
	call	GetOverrideAssume@PLT
	test	rsi, rsi
	jz	$_125
	mov	ecx, dword ptr [rsi+0x4]
	mov	dword ptr [LastRegOverride+rip], ecx
	mov	dword ptr [rsi+0x4], ebx
$_125:	jmp	$_127

$_126:	mov	rcx, qword ptr [rdi+0x8]
	call	SymFind@PLT
$_127:	test	rax, rax
	jz	$_129
	cmp	byte ptr [rax+0x18], 4
	jz	$_128
	cmp	byte ptr [rax+0x18], 3
	jnz	$_129
$_128:	mov	qword ptr [SegOverride+rip], rax
$_129:	xor	eax, eax
$_130:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_131:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	dword ptr [rbp-0xC], 0
	mov	rsi, rcx
	mov	rdi, r8
	imul	ebx, dword ptr [rbp+0x30], 24
	cmp	word ptr [rsi+0xE], 531
	jc	$_132
	cmp	word ptr [rsi+0xE], 580
	ja	$_132
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x28]
	call	process_branch@PLT
	jmp	$_182

$_132:	cmp	byte ptr [rdi+0x40], 47
	jne	$_139
	mov	eax, 4
	movzx	ecx, word ptr [rsi+0xE]
	jmp	$_137

$_133:	mov	eax, 8
	mov	dword ptr [rbp-0xC], 8
	jmp	$_138

$_134:	cmp	edx, 1
	jnz	$_136
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_135
	test	byte ptr [rsi+0x10], 0x08
	jz	$_135
	mov	eax, 8
	jmp	$_136

$_135:	test	byte ptr [rsi+0x10], 0x02
	jz	$_136
	mov	eax, 2
$_136:	jmp	$_138

$_137:	cmp	ecx, 932
	jz	$_133
	cmp	ecx, 956
	jz	$_133
	cmp	ecx, 948
	jz	$_133
	cmp	ecx, 936
	jz	$_133
	cmp	ecx, 612
	jz	$_133
	cmp	ecx, 1028
	jz	$_133
	cmp	ecx, 999
	jz	$_133
	cmp	ecx, 1123
	jz	$_133
	cmp	ecx, 682
	jz	$_134
$_138:	mov	edx, eax
	mov	rcx, rdi
	call	quad_resize@PLT
$_139:	mov	eax, dword ptr [rdi]
	mov	dword ptr [rbp-0x8], eax
	mov	dword ptr [rsi+rbx+0x20], eax
	cmp	dword ptr [rdi+0x8], 0
	jnz	$_140
	cmp	dword ptr [rdi+0xC], 0
	jz	$_141
$_140:	mov	rcx, rdi
	call	EmitConstError@PLT
	jmp	$_182

$_141:	mov	edx, dword ptr [rdi+0x4]
	xor	ecx, ecx
	add	eax, -2147483648
	adc	edx, 0
	test	edx, edx
	seta	cl
	cmp	dword ptr [rbp-0xC], 0
	jnz	$_142
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_143
	cmp	word ptr [rsi+0xE], 682
	jnz	$_143
	cmp	dword ptr [rbp+0x30], 1
	jnz	$_143
	test	byte ptr [rsi+0x10], 0x08
	jz	$_143
	test	ecx, ecx
	jnz	$_142
	test	byte ptr [rdi+0x43], 0x02
	jz	$_143
	cmp	byte ptr [rdi+0x40], 7
	jz	$_142
	cmp	byte ptr [rdi+0x40], 71
	jnz	$_143
$_142:	mov	dword ptr [rsi+rbx+0x10], 524288
	mov	eax, dword ptr [rdi+0x4]
	mov	dword ptr [rsi+rbx+0x24], eax
	xor	eax, eax
	jmp	$_182

$_143:	mov	eax, dword ptr [rdi]
	mov	edx, dword ptr [rdi+0x4]
	add	eax, 0
	adc	edx, 1
	cmp	edx, 1
	jbe	$_145
	cmp	byte ptr [rsi+0x63], 1
	jc	$_144
	cmp	word ptr [rsi+0xE], 999
	jnz	$_144
	cmp	dword ptr [rbp+0x30], 1
	jnz	$_144
	cmp	dword ptr [rsi+0x10], 2048
	jnz	$_144
	mov	dword ptr [rsi+rbx+0x10], 524288
	mov	eax, dword ptr [rdi+0x4]
	mov	dword ptr [rsi+rbx+0x24], eax
	xor	eax, eax
	jmp	$_182

$_144:	mov	rcx, rdi
	call	EmitConstError@PLT
	jmp	$_182

$_145:	test	byte ptr [rdi+0x43], 0x02
	je	$_153
	or	byte ptr [rsi+0x66], 0x08
	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rdi+0x42]
	movzx	ecx, byte ptr [rdi+0x40]
	call	SizeFromMemtype
	jmp	$_151

$_146:	mov	dword ptr [rbp-0x4], 65536
	jmp	$_152

$_147:	mov	dword ptr [rbp-0x4], 131072
	jmp	$_152

$_148:	mov	dword ptr [rbp-0x4], 262144
	jmp	$_152

$_149:	cmp	byte ptr [rsi+0x63], 2
	jnz	$_150
	cmp	byte ptr [rdi+0x40], 39
	jnz	$_150
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_150
	cmp	dword ptr [rdi+0x4], 0
	jnz	$_150
	mov	dword ptr [rbp-0x4], 524288
	mov	dword ptr [rsi+rbx+0x24], 0
	jmp	$_152

$_150:	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_182

	jmp	$_152

$_151:	cmp	rax, 1
	jz	$_146
	cmp	rax, 2
	jz	$_147
	cmp	rax, 4
	jz	$_148
	cmp	rax, 8
	jz	$_149
	jmp	$_150

$_152:	jmp	$_156

$_153:	movsx	eax, byte ptr [rbp-0x8]
	cmp	eax, dword ptr [rbp-0x8]
	jnz	$_154
	mov	dword ptr [rbp-0x4], 65536
	jmp	$_156

$_154:	cmp	dword ptr [rbp-0x8], 65535
	jg	$_155
	cmp	dword ptr [rbp-0x8], -65535
	jl	$_155
	mov	dword ptr [rbp-0x4], 131072
	jmp	$_156

$_155:	mov	dword ptr [rbp-0x4], 262144
$_156:	jmp	$_179

$_157:	cmp	dword ptr [rdi+0x4], 0
	jne	$_180
	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jne	$_180
	mov	edx, dword ptr [rsi+0x10]
	test	byte ptr [rdi+0x43], 0x02
	jne	$_170
	cmp	byte ptr [rsi+0x63], 0
	jbe	$_170
	cmp	edx, 512
	jz	$_158
	cmp	edx, 1024
	jz	$_158
	cmp	edx, 2048
	jne	$_170
$_158:	sub	rdi, 104
	mov	byte ptr [rsi+0x8], 0
	cmp	dword ptr [rbp-0x4], 65536
	jnz	$_159
	mov	byte ptr [rdi+0x40], 0
	jmp	$_169

$_159:	mov	eax, dword ptr [rdi+0x68]
	xor	ecx, ecx
	jmp	$_163

$_160:	inc	ecx
	shr	eax, 8
$_161:	inc	ecx
	shr	eax, 8
$_162:	inc	ecx
	shr	eax, 8
	jmp	$_167

$_163:	cmp	edx, 512
	jz	$_164
	test	eax, 0xFFFFFF
	jz	$_160
$_164:	cmp	edx, 512
	jz	$_165
	test	eax, 0xFF00FFFF
	jz	$_161
$_165:	cmp	edx, 512
	jz	$_166
	test	eax, 0xFFFF00FF
	jz	$_162
$_166:	cmp	edx, 512
	jnz	$_167
	test	eax, 0xFF
	jz	$_162
$_167:	test	ecx, ecx
	jz	$_168
	mov	dword ptr [rbp-0x4], 65536
	mov	byte ptr [rdi+0x40], 0
	add	dword ptr [rdi], ecx
	adc	dword ptr [rdi+0x4], 0
	mov	dword ptr [rsi+rbx+0x20], eax
	mov	dword ptr [rdi+0x68], eax
	jmp	$_169

$_168:	mov	dword ptr [rbp-0x4], 262144
	mov	byte ptr [rdi+0x40], 3
$_169:	xor	r9d, r9d
	mov	r8, rdi
	xor	edx, edx
	mov	rcx, rsi
	call	$_309
$_170:	jmp	$_180

$_171:	test	byte ptr [rdi+0x43], 0x02
	jnz	$_172
	cmp	byte ptr [rsi+0x63], 0
	jbe	$_172
	cmp	dword ptr [rbp-0x4], 131072
	jnz	$_172
	mov	dword ptr [rbp-0x4], 262144
$_172:	cmp	dword ptr [rbp-0x4], 131072
	jnz	$_173
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	setne	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_174

$_173:	cmp	dword ptr [rbp-0x4], 262144
	jnz	$_174
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	mov	byte ptr [rsi+0xA], al
$_174:	jmp	$_180

$_175:	cmp	dword ptr [rbp-0x4], 262144
	jz	$_176
	mov	dword ptr [rbp-0x4], 131072
	movsx	eax, byte ptr [rbp-0x8]
	movsx	ecx, word ptr [rbp-0x8]
	cmp	eax, ecx
	jnz	$_176
	mov	dword ptr [rbp-0x4], 65536
$_176:	jmp	$_180

$_177:	cmp	dword ptr [rbp-0x4], 131072
	jnz	$_178
	mov	dword ptr [rbp-0x4], 262144
$_178:	jmp	$_180

$_179:
	cmp	word ptr [rsi+0xE], 582
	je	$_157
	cmp	word ptr [rsi+0xE], 737
	je	$_157
	cmp	word ptr [rsi+0xE], 677
	je	$_171
	cmp	word ptr [rsi+0xE], 679
	jz	$_175
	cmp	word ptr [rsi+0xE], 641
	jz	$_177
$_180:	cmp	dword ptr [rbp+0x30], 1
	jnz	$_181
	test	byte ptr [rsi+0x60], 0xFFFFFF80
	jnz	$_181
	test	byte ptr [rsi+0x60], 0x1F
	jz	$_181
	or	byte ptr [rsi+0x66], 0x01
$_181:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsi+rbx+0x10], eax
	xor	eax, eax
$_182:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

idata_fixup:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	dword ptr [rbp-0x8], 0
	mov	rsi, rcx
	mov	rdi, r8
	imul	ebx, dword ptr [rbp+0x30], 24
	cmp	word ptr [rsi+0xE], 531
	jc	$_183
	cmp	word ptr [rsi+0xE], 580
	ja	$_183
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp+0x30]
	mov	rcx, rsi
	call	process_branch@PLT
	jmp	$_268

$_183:	mov	eax, dword ptr [rdi]
	mov	dword ptr [rsi+rbx+0x20], eax
	mov	rcx, qword ptr [rdi+0x50]
	cmp	byte ptr [rdi+0x42], -2
	jz	$_184
	mov	al, byte ptr [rdi+0x42]
	mov	byte ptr [rbp-0xD], al
	jmp	$_190

$_184:	test	rcx, rcx
	jnz	$_186
	xor	edx, edx
	mov	rcx, rdi
	call	segm_override
	cmp	qword ptr [SegOverride+rip], 0
	jz	$_185
	mov	rcx, qword ptr [SegOverride+rip]
	call	GetSymOfssize@PLT
	mov	byte ptr [rbp-0xD], al
$_185:	jmp	$_190

$_186:	cmp	byte ptr [rcx+0x18], 3
	jz	$_187
	cmp	byte ptr [rcx+0x18], 4
	jz	$_187
	cmp	dword ptr [rdi+0x38], 252
	jnz	$_188
$_187:	mov	byte ptr [rbp-0xD], 0
	jmp	$_190

$_188:	test	byte ptr [rdi+0x43], 0x04
	jz	$_189
	mov	byte ptr [rbp-0xD], 0
	jmp	$_190

$_189:	call	GetSymOfssize@PLT
	mov	byte ptr [rbp-0xD], al
$_190:	cmp	dword ptr [rdi+0x38], 253
	jnz	$_191
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_268

$_191:	test	byte ptr [rdi+0x43], 0x02
	jz	$_192
	test	byte ptr [rdi+0x43], 0x04
	jnz	$_192
	or	byte ptr [rsi+0x66], 0x08
	cmp	byte ptr [rsi+0x60], -64
	jnz	$_192
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x60], al
$_192:	cmp	byte ptr [rsi+0x60], -64
	jne	$_213
	cmp	dword ptr [rbp+0x30], 0
	jbe	$_213
	cmp	byte ptr [rdi+0x42], -2
	jne	$_213
	mov	rdx, rsi
	mov	ecx, dword ptr [rsi+0x10]
	call	OperandSize
	mov	ecx, dword ptr [rdi+0x38]
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_199
	cmp	dword ptr [rdi+0x38], -2
	je	$_199
	jmp	$_198

$_193:	test	eax, eax
	jz	$_194
	cmp	eax, 2
	jnc	$_194
	mov	r8d, 2
	mov	edx, eax
	mov	ecx, 2022
	call	asmerr@PLT
	jmp	$_268

$_194:	jmp	$_199

$_195:	test	eax, eax
	jz	$_197
	cmp	eax, 2
	jc	$_196
	cmp	byte ptr [rbp-0xD], 0
	jz	$_197
	cmp	eax, 4
	jnc	$_197
$_196:	movzx	ecx, byte ptr [rbp-0xD]
	mov	edx, 2
	shl	edx, cl
	mov	r8d, edx
	mov	edx, eax
	mov	ecx, 2022
	call	asmerr@PLT
	jmp	$_268

$_197:	jmp	$_199

$_198:	cmp	ecx, 252
	jz	$_193
	cmp	ecx, 249
	jz	$_195
	cmp	ecx, 246
	jz	$_195
	cmp	ecx, 239
	jz	$_195
	cmp	ecx, 251
	jz	$_195
$_199:	jmp	$_212

$_200:	test	byte ptr [rdi+0x43], 0x04
	jnz	$_201
	cmp	ecx, 242
	jz	$_201
	cmp	ecx, 235
	jz	$_201
	cmp	ecx, 243
	jz	$_201
	cmp	ecx, 236
	jnz	$_202
$_201:	mov	byte ptr [rsi+0x60], 0
$_202:	jmp	$_213

$_203:	test	byte ptr [rdi+0x43], 0x04
	jnz	$_204
	cmp	byte ptr [rsi+0x63], 0
	jz	$_204
	cmp	ecx, 245
	jz	$_204
	cmp	ecx, 238
	jnz	$_205
$_204:	mov	byte ptr [rsi+0x60], 1
$_205:	jmp	$_213

$_206:	mov	byte ptr [rsi+0x60], 3
	jmp	$_213

$_207:	cmp	byte ptr [rbp-0xD], 2
	jnz	$_211
	cmp	ecx, 261
	jz	$_208
	cmp	ecx, 260
	jz	$_208
	cmp	word ptr [rsi+0xE], 682
	jnz	$_209
	test	byte ptr [rsi+0x10], 0x08
	jz	$_209
$_208:	mov	byte ptr [rsi+0x60], 7
	jmp	$_211

$_209:	cmp	ecx, 244
	jz	$_210
	cmp	ecx, 237
	jnz	$_211
$_210:	mov	byte ptr [rsi+0x60], 3
$_211:	jmp	$_213

$_212:	cmp	eax, 1
	je	$_200
	cmp	eax, 2
	jz	$_203
	cmp	eax, 4
	jz	$_206
	cmp	eax, 8
	jz	$_207
$_213:	cmp	byte ptr [rsi+0x60], -64
	jne	$_234
	test	byte ptr [rdi+0x43], 0x04
	jz	$_218
	cmp	byte ptr [rdi+0x40], -64
	jz	$_214
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x60], al
	jmp	$_217

$_214:
	cmp	word ptr [rsi+0xE], 679
	jnz	$_215
	mov	byte ptr [rsi+0x60], 1
	jmp	$_217

$_215:	mov	ecx, 1
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	cmp	byte ptr [rsi+0xA], al
	jnz	$_216
	mov	ecx, 3
$_216:	mov	byte ptr [rsi+0x60], cl
$_217:	jmp	$_234

$_218:	movzx	eax, word ptr [rsi+0xE]
	jmp	$_228

$_219:	cmp	byte ptr [rdi+0x40], -64
	jnz	$_223
	mov	eax, dword ptr [rdi+0x38]
	jmp	$_222

$_220:	mov	byte ptr [rdi+0x40], 0
	jmp	$_223

$_221:	mov	byte ptr [rdi+0x40], 3
	jmp	$_223

$_222:	cmp	eax, -2
	jz	$_220
	cmp	eax, 242
	jz	$_220
	cmp	eax, 235
	jz	$_220
	cmp	eax, 243
	jz	$_220
	cmp	eax, 236
	jz	$_220
	cmp	eax, 244
	jz	$_221
	cmp	eax, 239
	jz	$_221
	cmp	eax, 251
	jz	$_221
$_223:	cmp	byte ptr [rdi+0x40], -126
	jnz	$_224
	test	byte ptr [rdi+0x43], 0x02
	jnz	$_224
	mov	byte ptr [rdi+0x40], -127
$_224:
	cmp	word ptr [rsi+0xE], 679
	jnz	$_226
	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rbp-0xD]
	movzx	ecx, byte ptr [rdi+0x40]
	call	SizeFromMemtype
	cmp	rax, 2
	jnc	$_225
	mov	byte ptr [rdi+0x40], 1
$_225:	jmp	$_227

$_226:
	cmp	word ptr [rsi+0xE], 641
	jnz	$_227
	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rbp-0xD]
	movzx	ecx, byte ptr [rdi+0x40]
	call	SizeFromMemtype
	cmp	rax, 4
	jnc	$_227
	mov	byte ptr [rdi+0x40], 3
$_227:	jmp	$_229

$_228:	cmp	eax, 679
	je	$_219
	cmp	eax, 641
	je	$_219
	cmp	eax, 677
	je	$_219
$_229:	mov	rcx, qword ptr [rdi+0x50]
	cmp	byte ptr [rdi+0x40], -64
	jz	$_230
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x60], al
	jmp	$_234

$_230:	cmp	byte ptr [rcx+0x18], 0
	jnz	$_231
	mov	byte ptr [rsi+0x60], 0
	mov	dword ptr [rbp-0x8], 5
	jmp	$_234

$_231:	mov	eax, 1
	cmp	byte ptr [rbp-0xD], 2
	jnz	$_232
	mov	eax, 7
	jmp	$_233

$_232:	cmp	byte ptr [rbp-0xD], 1
	jnz	$_233
	mov	eax, 3
$_233:	mov	byte ptr [rsi+0x60], al
$_234:	xor	r8d, r8d
	movzx	edx, byte ptr [rbp-0xD]
	movzx	ecx, byte ptr [rsi+0x60]
	call	SizeFromMemtype
	mov	dword ptr [rbp-0xC], eax
	jmp	$_246

$_235:	mov	dword ptr [rsi+rbx+0x10], 65536
	mov	byte ptr [rsi+0xA], 0
	jmp	$_247

$_236:	mov	dword ptr [rsi+rbx+0x10], 131072
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	setne	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_247

$_237:	mov	dword ptr [rsi+rbx+0x10], 262144
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_247

$_238:	mov	al, byte ptr [rdi+0x40]
	and	eax, 0x1F
	xor	ecx, ecx
	mov	edx, dword ptr [rdi+0x4]
	cmp	edx, ecx
	jnz	$_239
	cmp	dword ptr [rdi], 2147483647
$_239:	setg	cl
	cmp	edx, -1
	jnz	$_240
	cmp	dword ptr [rdi], -2147483648
$_240:	setl	ch
	test	ecx, ecx
	jnz	$_241
	test	byte ptr [rdi+0x43], 0x02
	jz	$_242
	cmp	eax, 7
	jnz	$_242
$_241:	mov	dword ptr [rsi+rbx+0x10], 524288
	mov	eax, dword ptr [rdi+0x4]
	mov	dword ptr [rsi+rbx+0x24], eax
	jmp	$_245

$_242:	cmp	byte ptr [rbp-0xD], 2
	jnz	$_244
	cmp	dword ptr [rdi+0x38], 249
	jz	$_243
	cmp	word ptr [rsi+0xE], 682
	jnz	$_244
	test	byte ptr [rsi+0x10], 0x08
	jz	$_244
$_243:	mov	dword ptr [rsi+rbx+0x10], 524288
	mov	eax, dword ptr [rdi+0x4]
	mov	dword ptr [rsi+rbx+0x24], eax
	jmp	$_245

$_244:	mov	dword ptr [rsi+rbx+0x10], 262144
$_245:	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_247

$_246:	cmp	eax, 1
	je	$_235
	cmp	eax, 2
	je	$_236
	cmp	eax, 4
	je	$_237
	cmp	eax, 8
	je	$_238
$_247:	cmp	dword ptr [rdi+0x38], 252
	jnz	$_248
	mov	dword ptr [rbp-0x4], 8
	jmp	$_260

$_248:	cmp	byte ptr [rsi+0x60], 0
	jnz	$_252
	cmp	dword ptr [rdi+0x38], 235
	jz	$_249
	cmp	dword ptr [rdi+0x38], 236
	jnz	$_250
$_249:	mov	dword ptr [rbp-0x4], 11
	jmp	$_251

$_250:	mov	dword ptr [rbp-0x4], 4
$_251:	jmp	$_260

$_252:	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	cmp	byte ptr [rsi+0xA], al
	jnz	$_259
	cmp	dword ptr [rsi+rbx+0x10], 524288
	jnz	$_254
	cmp	dword ptr [rdi+0x38], -2
	jz	$_253
	cmp	dword ptr [rdi+0x38], 249
	jnz	$_254
$_253:	mov	dword ptr [rbp-0x4], 7
	jmp	$_258

$_254:	cmp	dword ptr [rbp-0xC], 4
	jl	$_257
	cmp	dword ptr [rdi+0x38], 245
	jz	$_257
	test	byte ptr [rdi+0x43], 0x02
	jz	$_255
	cmp	byte ptr [rbp-0xD], 0
	jnz	$_255
	cmp	byte ptr [rdi+0x40], -126
	jnz	$_255
	mov	dword ptr [rbp-0x4], 9
	jmp	$_256

$_255:	mov	dword ptr [rbp-0x4], 6
$_256:	jmp	$_258

$_257:	mov	dword ptr [rbp-0x4], 5
$_258:	jmp	$_260

$_259:	mov	dword ptr [rbp-0x4], 5
$_260:	cmp	dword ptr [rbp+0x30], 1
	jnz	$_261
	cmp	dword ptr [rbp-0xC], 1
	jz	$_261
	or	byte ptr [rsi+0x66], 0x01
$_261:	xor	edx, edx
	mov	rcx, rdi
	call	segm_override
	cmp	byte ptr [ModuleInfo+0x1BB+rip], 2
	jnz	$_263
	cmp	dword ptr [rdi+0x38], 249
	jz	$_262
	cmp	dword ptr [rdi+0x38], 252
	jnz	$_263
$_262:	mov	rcx, qword ptr [rdi+0x50]
	call	set_frame2
	jmp	$_264

$_263:	mov	rcx, qword ptr [rdi+0x50]
	call	set_frame
$_264:	mov	r8d, dword ptr [rbp-0x8]
	mov	edx, dword ptr [rbp-0x4]
	mov	rcx, qword ptr [rdi+0x50]
	call	CreateFixup@PLT
	mov	qword ptr [rsi+rbx+0x18], rax
	cmp	dword ptr [rdi+0x38], 246
	jnz	$_265
	or	byte ptr [rax+0x1B], 0x01
$_265:	cmp	dword ptr [rdi+0x38], 239
	jnz	$_266
	cmp	dword ptr [rbp-0x4], 6
	jnz	$_266
	mov	byte ptr [rax+0x18], 12
$_266:	cmp	dword ptr [rdi+0x38], 251
	jnz	$_267
	cmp	dword ptr [rbp-0x4], 6
	jnz	$_267
	mov	byte ptr [rax+0x18], 13
$_267:	xor	eax, eax
$_268:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_269:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, rdx
	xor	ebx, ebx
	mov	rdx, qword ptr [rdi+0x50]
	cmp	qword ptr [rdi+0x58], 0
	jz	$_270
	mov	rdx, qword ptr [rdi+0x58]
$_270:	test	byte ptr [rdi+0x43], 0x02
	jz	$_273
	cmp	qword ptr [rdi+0x60], 0
	jz	$_273
	mov	rcx, qword ptr [rdi+0x60]
	mov	ebx, dword ptr [rcx+0x50]
	cmp	byte ptr [rcx+0x1C], 0
	jz	$_271
	or	byte ptr [rsi+0x66], 0x04
	jmp	$_272

$_271:	and	byte ptr [rsi+0x66], 0xFFFFFFFB
$_272:	jmp	$_285

$_273:	test	rdx, rdx
	je	$_283
	cmp	qword ptr [rdx+0x20], 0
	jz	$_277
	mov	rcx, qword ptr [rdx+0x20]
	mov	ebx, dword ptr [rcx+0x50]
	cmp	byte ptr [rcx+0x1C], 0
	jz	$_274
	or	byte ptr [rsi+0x66], 0x04
	jmp	$_275

$_274:	and	byte ptr [rsi+0x66], 0xFFFFFFFB
$_275:	mov	al, byte ptr [rcx+0x38]
	cmp	ebx, 4
	jnz	$_276
	cmp	al, byte ptr [rsi+0x63]
	jz	$_276
	mov	byte ptr [rdi+0x42], al
$_276:	jmp	$_282

$_277:	cmp	byte ptr [rdx+0x19], -61
	jnz	$_280
	mov	ecx, 129
	cmp	byte ptr [rdx+0x1C], 0
	jz	$_278
	mov	ecx, 130
$_278:	mov	qword ptr [rbp-0x8], rdx
	xor	r8d, r8d
	movzx	edx, byte ptr [rdx+0x38]
	movzx	ecx, cl
	call	SizeFromMemtype
	mov	ebx, eax
	and	byte ptr [rsi+0x66], 0xFFFFFFFB
	mov	rdx, qword ptr [rbp-0x8]
	cmp	byte ptr [rdx+0x1C], 0
	jz	$_279
	or	byte ptr [rsi+0x66], 0x04
$_279:	jmp	$_282

$_280:	test	byte ptr [rdx+0x15], 0x02
	jz	$_281
	mov	ecx, dword ptr [rdx+0x58]
	mov	eax, dword ptr [rdx+0x50]
	xor	edx, edx
	div	ecx
	mov	ebx, eax
	jmp	$_282

$_281:	mov	ebx, dword ptr [rdx+0x50]
$_282:	jmp	$_285

$_283:	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	mov	eax, 1
	shl	eax, cl
	test	cl, 0x68
	jz	$_284
	mov	ebx, 2
$_284:	mov	cl, byte ptr [ModuleInfo+0x1CD+rip]
	mov	eax, 2
	shl	eax, cl
	add	ebx, eax
$_285:	test	ebx, ebx
	jz	$_286
	lea	rdx, [rdi+0x40]
	mov	ecx, ebx
	call	MemtypeFromSize
$_286:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_287:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	cmp	word ptr [rsi+0xE], 711
	jnz	$_288
	jmp	$_308

$_288:	movzx	eax, byte ptr [rbp+0x30]
	cmp	al, -64
	je	$_308
	cmp	al, -60
	je	$_308
	cmp	al, -127
	je	$_308
	cmp	al, -126
	je	$_308
	mov	byte ptr [rsi+0x60], al
	mov	rbx, qword ptr [rsi+0x58]
	cmp	byte ptr [rsi+0x63], 0
	jbe	$_300
	cmp	al, 1
	jz	$_289
	cmp	al, 65
	jnz	$_290
$_289:	mov	byte ptr [rsi+0xA], 1
	jmp	$_299

$_290:	mov	ah, al
	and	al, 0xFFFFFFC0
	and	ah, 0x1F
	cmp	al, -128
	jnc	$_299
	cmp	ah, 7
	jne	$_299
	movzx	eax, word ptr [rsi+0xE]
	jmp	$_298

$_291:	jmp	$_299

$_292:	movzx	eax, byte ptr [rbx]
	imul	eax, eax, 12
	lea	rcx, [opnd_clstab+rip]
	cmp	dword ptr [rcx+rax], 6323968
	je	$_299
	test	byte ptr [rbx+0x4], 0x07
	jne	$_299
	test	byte ptr [rbx+0x5], 0xFFFFFFFF
	jz	$_296
	movzx	eax, word ptr [rsi+0xE]
	jmp	$_294

$_293:	or	byte ptr [rsi+0x8], 0x08
	jmp	$_295

$_294:	cmp	eax, 1009
	jz	$_293
	cmp	eax, 1010
	jz	$_293
	cmp	eax, 1209
	jz	$_293
	cmp	eax, 1210
	jz	$_293
	cmp	eax, 1027
	jz	$_293
	cmp	eax, 1372
	jz	$_293
	cmp	eax, 1373
	jz	$_293
	cmp	eax, 1462
	jz	$_293
	cmp	eax, 1463
	jz	$_293
	cmp	eax, 1395
	jz	$_293
$_295:	jmp	$_297

$_296:	or	byte ptr [rsi+0x8], 0x08
$_297:	jmp	$_299

$_298:	cmp	eax, 677
	je	$_291
	cmp	eax, 678
	je	$_291
	cmp	eax, 694
	je	$_291
	cmp	eax, 1293
	je	$_291
	cmp	eax, 1294
	je	$_291
	cmp	eax, 1295
	je	$_291
	cmp	eax, 1296
	je	$_291
	jmp	$_292

$_299:	jmp	$_308

$_300:	mov	ah, al
	and	al, 0xFFFFFFC0
	and	ah, 0x1F
	cmp	al, -128
	jnc	$_305
	cmp	ah, 3
	jnz	$_305
	movzx	eax, word ptr [rsi+0xE]
	jmp	$_303

$_301:	jmp	$_304

$_302:	mov	byte ptr [rsi+0xA], 1
	jmp	$_304

$_303:	cmp	eax, 631
	jz	$_301
	cmp	eax, 632
	jz	$_301
	cmp	eax, 713
	jz	$_301
	cmp	eax, 714
	jz	$_301
	cmp	eax, 715
	jz	$_301
	cmp	eax, 531
	jz	$_301
	cmp	eax, 532
	jz	$_301
	jmp	$_302

$_304:	jmp	$_308

$_305:	mov	al, byte ptr [rbp+0x30]
	mov	ah, al
	and	al, 0xFFFFFFC0
	and	ah, 0x1F
	cmp	al, -128
	jnc	$_308
	cmp	ah, 7
	jnz	$_308
	movzx	eax, byte ptr [rbx]
	imul	eax, eax, 12
	lea	rcx, [opnd_clstab+rip]
	cmp	dword ptr [rcx+rax], 6323968
	jnz	$_306
	jmp	$_308

$_306:	test	dword ptr [rbx+0x4], 0xFF07
	jz	$_307
	jmp	$_308

$_307:
	cmp	word ptr [rsi+0xE], 694
	jz	$_308
	or	byte ptr [rsi+0x8], 0x08
$_308:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_309:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	byte ptr [rbp-0x16], 0
	mov	rsi, rcx
	mov	rdi, r8
	imul	ebx, dword ptr [rbp+0x30], 24
	mov	rax, qword ptr [rdi]
	mov	qword ptr [rsi+rbx+0x20], rax
	mov	dword ptr [rsi+rbx+0x10], 4202240
	mov	rax, qword ptr [rdi+0x50]
	mov	qword ptr [rbp-0x8], rax
	mov	rdx, rsi
	mov	rcx, rdi
	call	segm_override
	mov	al, byte ptr [rdi+0x40]
	mov	ah, al
	and	ah, 0xFFFFFFC0
	cmp	al, -61
	jnz	$_310
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_269
	jmp	$_312

$_310:	cmp	ah, -128
	jnz	$_312
	cmp	byte ptr [rdi+0x42], -2
	jnz	$_311
	cmp	qword ptr [rbp-0x8], 0
	jz	$_311
	mov	rcx, qword ptr [rbp-0x8]
	call	GetSymOfssize@PLT
	mov	byte ptr [rdi+0x42], al
$_311:	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rdi+0x42]
	movzx	ecx, byte ptr [rdi+0x40]
	call	SizeFromMemtype
	mov	ecx, eax
	lea	rdx, [rdi+0x40]
	call	MemtypeFromSize
$_312:	movzx	edx, byte ptr [rdi+0x40]
	mov	rcx, rsi
	call	$_287
	mov	rcx, qword ptr [rdi+0x58]
	test	rcx, rcx
	jz	$_314
	cmp	byte ptr [rcx+0x19], -60
	jnz	$_313
	cmp	byte ptr [rdi+0x40], -64
	jnz	$_313
	lea	rdx, [rbp-0x15]
	mov	ecx, dword ptr [rcx+0x50]
	call	MemtypeFromSize
	test	eax, eax
	jnz	$_313
	movzx	edx, byte ptr [rbp-0x15]
	mov	rcx, rsi
	call	$_287
$_313:	mov	rcx, qword ptr [rdi+0x58]
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_314
	or	byte ptr [rsi+0x66], 0x40
$_314:	jmp	$_326

$_315:	cmp	byte ptr [rsi+0x60], -64
	jnz	$_319
	cmp	byte ptr [ModuleInfo+0x1D6+rip], 0
	jnz	$_316
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_316
	cmp	qword ptr [rdi+0x50], 0
	jnz	$_316
	mov	ecx, 2023
	call	asmerr@PLT
	jmp	$_398

$_316:	mov	eax, 1
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_317
	mov	eax, 7
	jmp	$_318

$_317:	cmp	byte ptr [rsi+0x63], 1
	jnz	$_318
	mov	eax, 3
$_318:	mov	byte ptr [rdi+0x40], al
	movzx	edx, al
	mov	rcx, rsi
	call	$_287
$_319:	xor	r8d, r8d
	movzx	edx, byte ptr [rsi+0x63]
	movzx	ecx, byte ptr [rsi+0x60]
	call	SizeFromMemtype
	cmp	eax, 1
	jz	$_320
	cmp	eax, 6
	jbe	$_321
$_320:	cmp	byte ptr [rsi+0x63], 2
	jz	$_321
	mov	ecx, 2024
	call	asmerr@PLT
	jmp	$_398

$_321:	cmp	byte ptr [rdi+0x40], -126
	jz	$_324
	cmp	byte ptr [rsi+0x60], 5
	jz	$_324
	cmp	byte ptr [rsi+0x60], 9
	jnz	$_322
	cmp	byte ptr [rsi+0x63], 2
	jz	$_324
$_322:	cmp	byte ptr [rsi+0x60], 3
	jnz	$_325
	cmp	byte ptr [rsi+0x63], 0
	jnz	$_323
	cmp	byte ptr [rdi+0x42], 1
	jnz	$_324
$_323:	cmp	byte ptr [rsi+0x63], 1
	jnz	$_325
	cmp	byte ptr [rdi+0x42], 0
	jnz	$_325
$_324:	or	byte ptr [rsi+0x66], 0x04
$_325:	jmp	$_327

$_326:
	cmp	word ptr [rsi+0xE], 532
	je	$_315
	cmp	word ptr [rsi+0xE], 531
	je	$_315
$_327:	mov	al, byte ptr [rsi+0x60]
	and	eax, 0x80
	jne	$_340
	mov	al, byte ptr [rsi+0x60]
	and	eax, 0x3F
	cmp	eax, 63
	jnz	$_328
	mov	dword ptr [rsi+rbx+0x10], 16384
	jmp	$_339

$_328:	mov	al, byte ptr [rsi+0x60]
	and	eax, 0x1F
	mov	ecx, dword ptr [rsi+rbx+0x10]
	jmp	$_337

$_329:	mov	ecx, 256
	jmp	$_338

$_330:	mov	ecx, 512
	jmp	$_338

$_331:	mov	ecx, 1024
	jmp	$_338

$_332:	mov	ecx, 2097152
	jmp	$_338

$_333:	mov	ecx, 2048
	jmp	$_338

$_334:	mov	ecx, 4194304
	jmp	$_338

$_335:	mov	ecx, 4096
	jmp	$_338

$_336:	mov	ecx, 8192
	jmp	$_338

$_337:	cmp	eax, 0
	jz	$_329
	cmp	eax, 1
	jz	$_330
	cmp	eax, 3
	jz	$_331
	cmp	eax, 5
	jz	$_332
	cmp	eax, 7
	jz	$_333
	cmp	eax, 9
	jz	$_334
	cmp	eax, 15
	jz	$_335
	cmp	eax, 31
	jz	$_336
$_338:	mov	dword ptr [rsi+rbx+0x10], ecx
$_339:	jmp	$_346

$_340:	cmp	byte ptr [rsi+0x60], -64
	jnz	$_346
	movzx	eax, word ptr [rsi+0xE]
	jmp	$_345

$_341:	cmp	qword ptr [rdi+0x50], 0
	jnz	$_342
	mov	ecx, 2023
	call	asmerr@PLT
	jmp	$_398

$_342:	jmp	$_346

$_343:	cmp	byte ptr [rdi+0x40], -60
	jnz	$_344
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_398

$_344:	jmp	$_346

$_345:	cmp	eax, 675
	jz	$_341
	cmp	eax, 676
	jz	$_341
	cmp	eax, 677
	jz	$_343
	cmp	eax, 678
	jz	$_343
$_346:	mov	rax, qword ptr [rdi+0x18]
	mov	ecx, 4294967294
	test	rax, rax
	jz	$_347
	mov	ecx, dword ptr [rax+0x4]
$_347:	mov	dword ptr [rbp-0x10], ecx
	mov	rax, qword ptr [rdi+0x20]
	mov	edx, 4294967294
	test	rax, rax
	jz	$_348
	mov	edx, dword ptr [rax+0x4]
$_348:	mov	dword ptr [rbp-0xC], edx
	cmp	ecx, -2
	jz	$_353
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	mov	eax, dword ptr [r11+rax]
	mov	cl, byte ptr [rsi+0x63]
	test	eax, 0x4
	jz	$_349
	cmp	cl, 1
	jz	$_351
$_349:	test	eax, 0x8
	jz	$_350
	cmp	cl, 2
	jz	$_351
$_350:	test	eax, 0x2
	jz	$_352
	test	cl, cl
	jnz	$_352
$_351:	mov	byte ptr [rsi+0x9], 0
	jmp	$_353

$_352:	mov	byte ptr [rsi+0x9], 1
	test	eax, 0x2
	jz	$_353
	cmp	cl, 2
	jnz	$_353
	mov	ecx, 2085
	call	asmerr@PLT
	jmp	$_398

$_353:	cmp	dword ptr [rbp-0xC], -2
	je	$_374
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp-0xC], 12
	mov	eax, dword ptr [r11+rax]
	mov	cl, byte ptr [rsi+0x63]
	test	eax, 0x4
	jz	$_354
	cmp	cl, 1
	jz	$_356
$_354:	test	eax, 0x8
	jz	$_355
	cmp	cl, 2
	jz	$_356
$_355:	test	eax, 0x2
	jz	$_357
	test	cl, cl
	jnz	$_357
$_356:	mov	byte ptr [rsi+0x9], 0
	jmp	$_358

$_357:	mov	byte ptr [rsi+0x9], 1
$_358:	mov	rax, qword ptr [rsi+0x58]
	mov	cl, byte ptr [rax+0x3]
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp-0xC], 12
	cmp	byte ptr [r11+rax+0xA], 4
	jnz	$_361
	test	cl, 0x08
	jnz	$_361
	cmp	byte ptr [rdi+0x41], 0
	jz	$_359
	xor	edx, edx
	mov	ecx, dword ptr [rbp-0xC]
	call	GetResWName@PLT
	mov	rdx, rax
	mov	ecx, 2031
	call	asmerr@PLT
	jmp	$_360

$_359:	mov	ecx, 2029
	call	asmerr@PLT
$_360:	jmp	$_398

$_361:	mov	cl, byte ptr [rsi+0x63]
	test	cl, cl
	jnz	$_362
	cmp	byte ptr [rsi+0x9], 1
	jz	$_363
$_362:	cmp	cl, 2
	jz	$_363
	cmp	cl, 1
	jnz	$_373
	cmp	byte ptr [rsi+0x9], 0
	jnz	$_373
$_363:	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 48
	jc	$_371
	movzx	eax, byte ptr [rdi+0x41]
	jmp	$_369

$_364:	jmp	$_370

$_365:	mov	byte ptr [rbp-0x16], 64
	jmp	$_370

$_366:	mov	byte ptr [rbp-0x16], -128
	jmp	$_370

$_367:	mov	byte ptr [rbp-0x16], -64
	jmp	$_370

$_368:	mov	ecx, 2083
	call	asmerr@PLT
	jmp	$_398

	jmp	$_370

$_369:	cmp	eax, 0
	jz	$_364
	cmp	eax, 1
	jz	$_364
	cmp	eax, 2
	jz	$_365
	cmp	eax, 4
	jz	$_366
	cmp	eax, 8
	jz	$_367
	jmp	$_368

$_370:	jmp	$_372

$_371:	mov	ecx, 2085
	call	asmerr@PLT
	jmp	$_398

$_372:	jmp	$_374

$_373:	cmp	byte ptr [rdi+0x41], 0
	jz	$_374
	mov	ecx, 2032
	call	asmerr@PLT
	jmp	$_398

$_374:	cmp	dword ptr [rbp+0x40], 0
	je	$_392
	mov	byte ptr [rbp-0x17], 0
	mov	dword ptr [rbp-0x1C], 0
	test	byte ptr [rdi+0x43], 0x04
	jz	$_376
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	cmp	byte ptr [rsi+0x9], al
	jnz	$_375
	inc	byte ptr [rbp-0x17]
$_375:	jmp	$_379

$_376:	cmp	qword ptr [rbp-0x8], 0
	jz	$_377
	mov	rcx, qword ptr [rbp-0x8]
	call	GetSymOfssize@PLT
	mov	byte ptr [rbp-0x17], al
	jmp	$_379

$_377:	cmp	qword ptr [SegOverride+rip], 0
	jz	$_378
	mov	rcx, qword ptr [SegOverride+rip]
	call	GetSymOfssize@PLT
	mov	byte ptr [rbp-0x17], al
	jmp	$_379

$_378:	mov	al, byte ptr [rsi+0x63]
	mov	byte ptr [rbp-0x17], al
$_379:	cmp	dword ptr [rbp-0x10], -2
	jnz	$_386
	cmp	dword ptr [rbp-0xC], -2
	jnz	$_386
	mov	al, byte ptr [rbp-0x17]
	cmp	byte ptr [rsi+0x63], al
	setne	al
	mov	byte ptr [rsi+0x9], al
	cmp	byte ptr [rbp-0x17], 2
	jz	$_380
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_383
$_380:	cmp	qword ptr [rdi+0x30], 0
	jz	$_381
	mov	rax, qword ptr [ModuleInfo+0x200+rip]
	cmp	qword ptr [SegOverride+rip], rax
	jz	$_381
	mov	dword ptr [rbp-0x1C], 6
	jmp	$_382

$_381:	mov	dword ptr [rbp-0x1C], 3
$_382:	jmp	$_385

$_383:	cmp	byte ptr [rbp-0x17], 0
	jz	$_384
	mov	dword ptr [rbp-0x1C], 6
	jmp	$_385

$_384:	mov	dword ptr [rbp-0x1C], 5
$_385:	jmp	$_389

$_386:	cmp	byte ptr [rbp-0x17], 2
	jnz	$_387
	mov	dword ptr [rbp-0x1C], 6
	jmp	$_389

$_387:	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	cmp	byte ptr [rsi+0x9], al
	jnz	$_388
	mov	dword ptr [rbp-0x1C], 6
	jmp	$_389

$_388:	mov	dword ptr [rbp-0x1C], 5
	cmp	byte ptr [rbp-0x17], 0
	jz	$_389
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_389
	mov	rax, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 8007
	call	asmerr@PLT
$_389:	cmp	dword ptr [rbp-0x1C], 6
	jnz	$_391
	cmp	dword ptr [rdi+0x38], 239
	jnz	$_390
	mov	dword ptr [rbp-0x1C], 12
	jmp	$_391

$_390:	cmp	dword ptr [rdi+0x38], 251
	jnz	$_391
	mov	dword ptr [rbp-0x1C], 13
$_391:
	cmp	word ptr [rsi+0xE], 744
	jz	$_392
	cmp	word ptr [rsi+0xE], 745
	jz	$_392
	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0x1C]
	mov	rcx, qword ptr [rbp-0x8]
	call	CreateFixup@PLT
	mov	qword ptr [rsi+rbx+0x18], rax
$_392:	cmp	dword ptr [rdi+0x4], 0
	jz	$_395
	cmp	dword ptr [rdi+0x4], -1
	jnz	$_393
	cmp	dword ptr [rdi], 0
	jl	$_395
$_393:	cmp	byte ptr [rsi+0x63], 2
	jnz	$_394
	test	byte ptr [rdi+0x43], 0x01
	jz	$_395
$_394:	mov	rcx, rdi
	call	EmitConstError@PLT
	jmp	$_398

$_395:	mov	rax, qword ptr [rbp-0x8]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x10]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0xC]
	movzx	r8d, byte ptr [rbp-0x16]
	mov	edx, dword ptr [rbp+0x30]
	mov	rcx, rsi
	call	$_083
	cmp	eax, -1
	jnz	$_396
	jmp	$_398

$_396:	mov	rcx, qword ptr [rsi+rbx+0x18]
	test	rcx, rcx
	jz	$_397
	mov	al, byte ptr [Frame_Type+rip]
	mov	byte ptr [rcx+0x20], al
	mov	ax, word ptr [Frame_Datum+rip]
	mov	word ptr [rcx+0x22], ax
$_397:	xor	eax, eax
$_398:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_399:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, r8
	mov	ebx, edx
	mov	rcx, qword ptr [rdi+0x50]
	test	byte ptr [rdi+0x43], 0x01
	jz	$_402
	mov	rcx, qword ptr [rdi+0x50]
	test	rcx, rcx
	jz	$_400
	cmp	byte ptr [rcx+0x18], 5
	jnz	$_401
$_400:	xor	r9d, r9d
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_309
	jmp	$_433

$_401:	jmp	$_432

$_402:	cmp	dword ptr [rdi+0x38], -2
	jz	$_407
	mov	rcx, qword ptr [rdi+0x30]
	cmp	qword ptr [rdi+0x50], 0
	jnz	$_404
	test	rcx, rcx
	jz	$_403
	cmp	byte ptr [rcx], 2
	jnz	$_404
$_403:	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_131
	jmp	$_433

	jmp	$_406

$_404:
	cmp	word ptr [rsi+0xE], 711
	jnz	$_405
	cmp	dword ptr [rdi+0x38], 249
	jnz	$_405
	mov	r9d, 1
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_309
	jmp	$_433

$_405:	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	idata_fixup
	jmp	$_433

$_406:	jmp	$_432

$_407:	cmp	qword ptr [rdi+0x50], 0
	jnz	$_413
	cmp	qword ptr [rdi+0x30], 0
	jz	$_411
	mov	rcx, qword ptr [rdi+0x30]
	cmp	byte ptr [rcx], 2
	jz	$_408
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_409
$_408:	xor	r9d, r9d
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_309
	jmp	$_433

	jmp	$_410

$_409:	mov	r9d, 1
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_309
	jmp	$_433

$_410:	jmp	$_412

$_411:	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_131
	jmp	$_433

$_412:	jmp	$_432

$_413:	cmp	byte ptr [rcx+0x18], 0
	jne	$_424
	test	byte ptr [rdi+0x43], 0x02
	jne	$_424
	cmp	word ptr [rsi+0xE], 531
	jc	$_414
	cmp	word ptr [rsi+0xE], 580
	ja	$_414
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	process_branch@PLT
	jmp	$_433

$_414:	jmp	$_422

$_415:	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 0
	jbe	$_416
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	idata_fixup
	jmp	$_433

$_416:	jmp	$_423

$_417:	mov	eax, dword ptr [rsi+0x10]
	and	eax, 0xC000000
	cmp	ebx, 1
	jnz	$_420
	test	eax, eax
	jnz	$_420
	mov	rcx, qword ptr [rsi+0x58]
$_418:	movzx	eax, byte ptr [rcx]
	imul	eax, eax, 12
	lea	rdx, [opnd_clstab+rip]
	test	byte ptr [rdx+rax+0x6], 0x07
	jz	$_419
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	idata_fixup
	jmp	$_433

$_419:	add	rcx, 8
	test	byte ptr [rcx+0x2], 0x08
	jz	$_418
$_420:	cmp	ebx, 2
	jnz	$_421
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	idata_fixup
	jmp	$_433

$_421:	jmp	$_423

$_422:
	cmp	word ptr [rsi+0xE], 677
	je	$_415
	cmp	word ptr [rsi+0xE], 679
	je	$_415
	cmp	word ptr [rsi+0xE], 641
	je	$_415
	jmp	$_417

$_423:	jmp	$_432

$_424:	cmp	byte ptr [rcx+0x18], 3
	jz	$_425
	cmp	byte ptr [rcx+0x18], 4
	jnz	$_426
$_425:	mov	dword ptr [rdi+0x38], 252
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	idata_fixup
	jmp	$_433

	jmp	$_432

$_426:	test	byte ptr [rdi+0x43], 0x04
	jz	$_427
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	idata_fixup
	jmp	$_433

$_427:	cmp	byte ptr [rdi+0x40], -127
	jz	$_428
	cmp	byte ptr [rdi+0x40], -126
	jnz	$_432
$_428:	xor	eax, eax
	mov	rcx, qword ptr [rdi+0x28]
	test	rcx, rcx
	jz	$_429
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_429
	cmp	byte ptr [rcx-0x18], 38
	jnz	$_429
	inc	eax
$_429:	test	eax, eax
	jnz	$_430
	cmp	word ptr [rsi+0xE], 711
	jz	$_430
	cmp	qword ptr [rdi+0x58], 0
	jz	$_431
$_430:	mov	r9d, 1
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_309
	jmp	$_433

$_431:	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	idata_fixup
	jmp	$_433

$_432:	mov	r9d, 1
	mov	r8, rdi
	mov	edx, ebx
	mov	rcx, rsi
	call	$_309
$_433:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_434:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, r8
	test	byte ptr [rbx+0x40], 0x20
	jz	$_435
	mov	qword ptr [rbx+0x10], 0
$_435:	mov	rax, qword ptr [rbx+0x10]
	test	rax, rax
	jz	$_436
	cmp	dword ptr [rax+0x4], 0
	jnz	$_436
	mov	ecx, 2047
	call	asmerr@PLT
	jmp	$_438

$_436:	mov	rax, qword ptr [rcx+0x58]
	mov	al, byte ptr [rax+0x6]
	and	eax, 0xF7
	cmp	eax, 194
	jnz	$_437
	test	edx, edx
	jnz	$_437
	cmp	dword ptr [rbx], 0
	jnz	$_437
	xor	eax, eax
	jmp	$_438

$_437:	mov	r8, rbx
	call	$_131
$_438:	leave
	pop	rbx
	ret

$_439:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, rcx
	mov	rdi, r8
	imul	ebx, dword ptr [rbp+0x30], 24
	imul	eax, dword ptr [rbp+0x30], 104
	mov	rax, qword ptr [rdi+rax+0x18]
	mov	eax, dword ptr [rax+0x4]
	mov	dword ptr [rbp-0x4], eax
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	movzx	eax, byte ptr [r11+rax+0xA]
	mov	dword ptr [rbp-0x8], eax
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp-0x4], 12
	mov	eax, dword ptr [r11+rax]
	mov	dword ptr [rbp-0xC], eax
	mov	dword ptr [rsi+rbx+0x10], eax
	cmp	eax, 16
	jz	$_440
	cmp	eax, 32
	jnz	$_441
$_440:	cmp	dword ptr [rbp-0x8], 15
	jg	$_442
$_441:	test	eax, 0x40
	jz	$_446
$_442:	mov	byte ptr [rsi+0xB], 1
	cmp	eax, 64
	jnz	$_443
	or	byte ptr [rsi+0xD], 0x10
$_443:	cmp	dword ptr [rbp-0x8], 15
	jle	$_445
	mov	ecx, dword ptr [rbp+0x40]
	mov	edx, 1
	shl	edx, cl
	cmp	eax, 64
	jnz	$_444
	cmp	dword ptr [rbp-0x8], 23
	jle	$_444
	or	edx, 0x80
$_444:	or	byte ptr [rsi+0xD], dl
	jmp	$_446

$_445:	cmp	eax, 64
	jnz	$_446
	cmp	dword ptr [rbp-0x8], 7
	jle	$_446
	or	byte ptr [rsi+0xD], 0x40
$_446:	test	eax, 0x1
	jz	$_452
	cmp	eax, 8388609
	jz	$_447
	and	byte ptr [rsi+0x66], 0xFFFFFFFE
$_447:	cmp	byte ptr [rsi+0x63], 2
	jnz	$_449
	cmp	dword ptr [rbp-0x8], 4
	jl	$_449
	cmp	dword ptr [rbp-0x8], 7
	jg	$_449
	mov	eax, dword ptr [rbp-0x4]
	imul	eax, eax, 12
	lea	rcx, [SpecialTable+rip]
	cmp	word ptr [rcx+rax+0x8], 0
	jnz	$_448
	or	byte ptr [rsi+0x66], 0x10
	jmp	$_449

$_448:	or	byte ptr [rsi+0x66], 0x20
$_449:	imul	eax, dword ptr [rbp-0x8], 16
	mov	ecx, 1
	cmp	dword ptr [rbp-0x4], 5
	jl	$_450
	cmp	dword ptr [rbp-0x4], 8
	jg	$_450
	mov	ecx, 16
$_450:	lea	rdx, [StdAssumeTable+rip]
	test	byte ptr [rdx+rax+0x8], cl
	jz	$_451
	mov	ecx, 2108
	call	asmerr@PLT
	jmp	$_478

$_451:	jmp	$_473

$_452:	test	eax, 0xF
	jz	$_457
	or	byte ptr [rsi+0x66], 0x01
	imul	ecx, dword ptr [rbp-0x8], 16
	and	al, 0x0F
	lea	rdx, [StdAssumeTable+rip]
	test	byte ptr [rdx+rcx+0x8], al
	jz	$_453
	mov	ecx, 2108
	call	asmerr@PLT
	jmp	$_478

$_453:	test	byte ptr [rbp-0xC], 0x02
	jz	$_455
	cmp	byte ptr [rsi+0x63], 0
	jbe	$_454
	mov	byte ptr [rsi+0xA], 1
$_454:	jmp	$_456

$_455:	cmp	byte ptr [rsi+0x63], 0
	jnz	$_456
	mov	byte ptr [rsi+0xA], 1
$_456:	jmp	$_473

$_457:	test	eax, 0xC000000
	jz	$_462
	cmp	dword ptr [rbp-0x8], 1
	jnz	$_458
	cmp	word ptr [rsi+0xE], 678
	jnz	$_458
	lea	rdx, [DS0000+rip]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_478

$_458:	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_461
	cmp	word ptr [rsi+0xE], 641
	jnz	$_459
	cmp	byte ptr [rsi+0x63], 0
	jz	$_460
$_459:
	cmp	word ptr [rsi+0xE], 679
	jnz	$_461
	cmp	byte ptr [rsi+0x63], 0
	jbe	$_461
$_460:	mov	ecx, 8021
	call	asmerr@PLT
$_461:	jmp	$_473

$_462:	test	eax, 0x10000000
	jz	$_465
	imul	eax, dword ptr [rbp+0x30], 104
	mov	eax, dword ptr [rdi+rax]
	mov	dword ptr [rbp-0x8], eax
	cmp	eax, 7
	jbe	$_463
	mov	ecx, 2032
	call	asmerr@PLT
	jmp	$_478

$_463:	or	byte ptr [rsi+0x61], al
	test	eax, eax
	jz	$_464
	mov	dword ptr [rsi+rbx+0x10], 536870912
$_464:	xor	eax, eax
	jmp	$_478

	jmp	$_473

$_465:	test	eax, 0x2000000
	je	$_473
	cmp	word ptr [rsi+0xE], 682
	jz	$_467
	cmp	word ptr [rsi+0xE], 677
	jnz	$_466
	mov	ecx, 2151
	call	asmerr@PLT
	jmp	$_478

$_466:	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_478

$_467:	cmp	dword ptr [rbp-0x8], 32
	jl	$_471
	or	byte ptr [rsi+0x64], 0x04
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 96
	jc	$_470
	mov	eax, 3
	cmp	dword ptr [rbp-0x8], 37
	jle	$_468
	mov	eax, 6
$_468:	mov	ecx, 5
	cmp	dword ptr [rbp-0x8], 37
	jle	$_469
	mov	ecx, 7
$_469:	mov	r8d, ecx
	mov	edx, eax
	mov	ecx, 3004
	call	asmerr@PLT
	jmp	$_478

$_470:	jmp	$_472

$_471:	cmp	dword ptr [rbp-0x8], 16
	jl	$_472
	or	byte ptr [rsi+0x64], 0x01
$_472:	and	dword ptr [rbp-0x8], 0x0F
$_473:	imul	eax, dword ptr [rbp-0x4], 12
	lea	rcx, [SpecialTable+rip]
	movzx	eax, word ptr [rcx+rax+0x8]
	and	eax, 0xF0
	cmp	eax, 112
	jnz	$_474
	or	byte ptr [rsi+0x8], 0x40
	test	byte ptr [rbp-0xC], 0x08
	jz	$_474
	or	byte ptr [rsi+0x8], 0x08
$_474:	cmp	dword ptr [rbp+0x30], 0
	jnz	$_475
	mov	eax, dword ptr [rbp-0x8]
	mov	ecx, eax
	and	eax, 0x08
	shr	eax, 3
	or	byte ptr [rsi+0x8], al
	and	ecx, 0x07
	or	ecx, 0xC0
	or	byte ptr [rsi+0x61], cl
	jmp	$_477

$_475:
	cmp	word ptr [rsi+0xE], 743
	jnz	$_476
	test	dword ptr [rsi+0x10], 0x80
	jz	$_476
	test	byte ptr [rsi+0x10], 0x01
	jnz	$_476
	mov	eax, dword ptr [rbp-0x8]
	mov	ecx, eax
	and	eax, 0x08
	shr	eax, 3
	or	byte ptr [rsi+0x8], al
	and	ecx, 0x07
	and	byte ptr [rsi+0x61], 0xFFFFFFC0
	or	byte ptr [rsi+0x61], cl
	jmp	$_477

$_476:	mov	eax, dword ptr [rbp-0x8]
	mov	ecx, eax
	and	eax, 0x08
	shr	eax, 1
	or	byte ptr [rsi+0x8], al
	and	ecx, 0x07
	and	byte ptr [rsi+0x61], 0xFFFFFFC7
	shl	ecx, 3
	or	byte ptr [rsi+0x61], cl
$_477:	xor	eax, eax
$_478:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_479:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	imul	edx, edx, 16
	lea	rax, [SegAssumeTable+rip]
	mov	rbx, qword ptr [rdx+rax]
	cmp	qword ptr [rcx+0x30], 0
	jz	$_480
	test	rbx, rbx
	jz	$_480
	cmp	qword ptr [rcx+0x30], rbx
	jz	$_480
	call	GetGroup@PLT
	cmp	rax, rbx
	jz	$_480
	xor	eax, eax
	jmp	$_481

$_480:	mov	eax, 1
$_481:	leave
	pop	rbx
	ret

$_482:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 0
	mov	rsi, rcx
	mov	rdi, rdx
	movzx	eax, word ptr [rsi+0xE]
	jmp	$_511
$C0295:
$_483:	test	dword ptr [rsi+0x10], 0x8010
	jz	$_484
	and	byte ptr [rsi+0x8], 0xFFFFFFF7
	jmp	$_527
$C0298:
$_484:	cmp	dword ptr [rsi+0x28], 0
	jz	$_485
	cmp	qword ptr [rdi+0x98], 0
	jnz	$_485
	cmp	qword ptr [rdi+0xB8], 0
	jz	$_485
	xor	edx, edx
	mov	rcx, qword ptr [rdi+0xB8]
	call	$_479
	test	eax, eax
	jnz	$_485
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_513

$_485:	cmp	dword ptr [rsi+0x4], -2
	jz	$_490
	cmp	qword ptr [rdi+0x98], 0
	jz	$_489
	cmp	dword ptr [rsi+0x4], 0
	jnz	$_488
	cmp	dword ptr [LastRegOverride+rip], 3
	jnz	$_486
	mov	dword ptr [rsi+0x4], -2
	jmp	$_487

$_486:	mov	eax, dword ptr [LastRegOverride+rip]
	mov	dword ptr [rsi+0x4], eax
$_487:	jmp	$_489

$_488:	mov	ecx, 2070
	call	asmerr@PLT
$_489:	jmp	$_491

$_490:	cmp	dword ptr [rsi+0x10], 0
	jz	$_491
	cmp	qword ptr [rdi+0x30], 0
	jnz	$_491
	cmp	qword ptr [rdi+0x50], 0
	jz	$_491
	mov	r8d, 3
	mov	rdx, qword ptr [rdi+0x50]
	mov	rcx, rsi
	call	$_057
$_491:	cmp	dword ptr [rsi+0x4], 3
	jnz	$_492
	mov	dword ptr [rsi+0x4], -2
$_492:	jmp	$_513
$C02A8:
$_493:	test	dword ptr [rsi+0x10], 0x8010
	jnz	$_494
	test	dword ptr [rsi+0x28], 0x8010
	jz	$_495
$_494:	and	byte ptr [rsi+0x8], 0xFFFFFFF7
	jmp	$_527
$C02AD:
$_495:	cmp	dword ptr [rsi+0x10], 0
	jz	$_496
	cmp	qword ptr [rdi+0x30], 0
	jnz	$_496
	cmp	qword ptr [rdi+0x50], 0
	jz	$_496
	xor	edx, edx
	mov	rcx, qword ptr [rdi+0x50]
	call	$_479
	test	eax, eax
	jnz	$_496
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_513

$_496:	cmp	dword ptr [rsi+0x4], -2
	jz	$_500
	mov	rcx, qword ptr [rdi+0x30]
	test	rcx, rcx
	jz	$_497
	cmp	byte ptr [rcx], 2
	jnz	$_497
	cmp	dword ptr [rcx+0x4], 25
	jz	$_497
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_499

$_497:	cmp	qword ptr [rdi+0x98], 0
	jnz	$_499
	cmp	dword ptr [rsi+0x4], 0
	jnz	$_498
	mov	dword ptr [rsi+0x4], -2
	jmp	$_499

$_498:	mov	ecx, 2070
	call	asmerr@PLT
$_499:	jmp	$_501
$C02BC:
$_500:	cmp	dword ptr [rsi+0x28], 0
	jz	$_501
	cmp	qword ptr [rdi+0x98], 0
	jnz	$_501
	cmp	qword ptr [rdi+0xB8], 0
	jz	$_501
	mov	r8d, 3
	mov	rdx, qword ptr [rdi+0xB8]
	mov	rcx, rsi
	call	$_057
$_501:	cmp	dword ptr [rsi+0x4], 3
	jnz	$_502
	mov	dword ptr [rsi+0x4], -2
$_502:	jmp	$_513
$C02C2:
	cmp	dword ptr [rsi+0x28], 0
	jz	$_503
	cmp	qword ptr [rdi+0x98], 0
	jnz	$_503
	cmp	qword ptr [rdi+0xB8], 0
	jz	$_503
	mov	r8d, 3
	mov	rdx, qword ptr [rdi+0xB8]
	mov	rcx, rsi
	call	$_057
$_503:	cmp	dword ptr [rsi+0x4], 3
	jnz	$_504
	mov	dword ptr [rsi+0x4], -2
$_504:	mov	dword ptr [rbp-0x4], 1
	jmp	$_513

$_505:	cmp	dword ptr [rsi+0x10], 0
	jz	$_506
	cmp	qword ptr [rdi+0x30], 0
	jnz	$_506
	cmp	qword ptr [rdi+0x50], 0
	jz	$_506
	mov	r8d, 3
	mov	rdx, qword ptr [rdi+0x50]
	mov	rcx, rsi
	call	$_057
$_506:	cmp	dword ptr [rsi+0x4], 3
	jnz	$_507
	mov	dword ptr [rsi+0x4], -2
$_507:	jmp	$_513

$C02C9: cmp	dword ptr [rsi+0x10], 0
	jz	$_508
	cmp	qword ptr [rdi+0x30], 0
	jnz	$_508
	cmp	qword ptr [rdi+0x50], 0
	jz	$_508
	xor	edx, edx
	mov	rcx, qword ptr [rdi+0x50]
	call	$_479
	test	eax, eax
	jnz	$_508
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_513

$_508:	cmp	dword ptr [rsi+0x4], -2
	jz	$_510
	cmp	dword ptr [rsi+0x4], 0
	jnz	$_509
	mov	dword ptr [rsi+0x4], -2
	jmp	$_510

$_509:	mov	ecx, 2070
	call	asmerr@PLT
$_510:	jmp	$_513

$_511:	cmp	eax, 597
	jl	$_512
	cmp	eax, 616
	jg	$_512
	push	rax
	lea	r11, [$C02C9+rip]
	movzx	eax, byte ptr [r11+rax-(597)+(IT$C02CF-$C02C9)]
	movzx	eax, word ptr [r11+rax*2+($C02CF-$C02C9)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C02CF:
	.word $C02C9-$C0295
	.word $C02C9-$C0298
	.word $C02C9-$C02A8
	.word $C02C9-$C02AD
	.word $C02C9-$C02BC
	.word $C02C9-$C02C2
	.word 0
IT$C02CF:
	.byte 1
	.byte 1
	.byte 1
	.byte 0
	.byte 6
	.byte 6
	.byte 6
	.byte 6
	.byte 5
	.byte 5
	.byte 5
	.byte 5
	.byte 3
	.byte 3
	.byte 3
	.byte 2
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.ALIGN 2
$C02D0:
$_512:	cmp	eax, 1321
	je	$_483
	cmp	eax, 1204
	je	$_484
	cmp	eax, 1405
	je	$_493
	cmp	eax, 1206
	je	$_495
	cmp	eax, 1205
	je	$_505
	jmp	$C02C9

$_513:	mov	ecx, dword ptr [rbp-0x4]
	shl	ecx, 2
	mov	rax, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rax]
	imul	eax, eax, 12
	lea	rdx, [opnd_clstab+rip]
	add	rdx, rax
	cmp	dword ptr [rdx+rcx], 0
	jnz	$_514
	and	byte ptr [rsi+0x66], 0xFFFFFFFE
	mov	byte ptr [rsi+0xA], 0
$_514:	mov	ebx, dword ptr [rbp-0x4]
	imul	ebx, ebx, 24
	cmp	dword ptr [rdx+rcx], 0
	je	$_527
	cmp	dword ptr [rsi+rbx+0x10], 0
	je	$_527
	mov	rdx, rsi
	mov	ecx, dword ptr [rsi+rbx+0x10]
	call	OperandSize
	mov	dword ptr [rbp-0x8], eax
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_518
	mov	rdx, qword ptr [rsi+rbx+0x18]
	xor	eax, eax
	test	rdx, rdx
	jz	$_515
	mov	rcx, qword ptr [rdx+0x30]
	cmp	byte ptr [rcx+0x18], 0
	jz	$_515
	inc	eax
$_515:	test	rdx, rdx
	jz	$_516
	test	eax, eax
	jz	$_517
$_516:	mov	ecx, 2023
	call	asmerr@PLT
$_517:	mov	dword ptr [rbp-0x8], 1
$_518:	jmp	$_526

$_519:	and	byte ptr [rsi+0x66], 0xFFFFFFFE
	mov	byte ptr [rsi+0xA], 0
	jmp	$_527

$_520:	or	byte ptr [rsi+0x66], 0x01
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], 0
	jz	$_521
	inc	eax
$_521:	mov	byte ptr [rsi+0xA], al
	jmp	$_527

$_522:	or	byte ptr [rsi+0x66], 0x01
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], 0
	jnz	$_523
	inc	eax
$_523:	mov	byte ptr [rsi+0xA], al
	jmp	$_527

$_524:	cmp	byte ptr [rsi+0x63], 2
	jnz	$_525
	or	byte ptr [rsi+0x66], 0x01
	mov	byte ptr [rsi+0xA], 0
	mov	byte ptr [rsi+0x8], 8
$_525:	jmp	$_527

$_526:	cmp	dword ptr [rbp-0x8], 1
	jz	$_519
	cmp	dword ptr [rbp-0x8], 2
	jz	$_520
	cmp	dword ptr [rbp-0x8], 4
	jz	$_522
	cmp	dword ptr [rbp-0x8], 8
	jz	$_524
$_527:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_528:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, rcx
	mov	rdi, rdx
	mov	ecx, dword ptr [rsi+0x10]
	mov	edx, dword ptr [rsi+0x28]
	mov	dword ptr [rbp-0xC], 0
	mov	dword ptr [rbp-0x4], ecx
	mov	dword ptr [rbp-0x8], edx
	movzx	eax, word ptr [rsi+0xE]
	jmp	$_619
$C02E3:
	cmp	ecx, 65536
	jz	$_529
	cmp	edx, 132
	jz	$_529
	jmp	$C035E
$_529:	jmp	$_621

$C02E6:
	cmp	dword ptr [rbp-0x8], 16777218
	jnz	$_535
	jmp	$_534
$_530:	jmp	$_535
$_531:	and	byte ptr [rsi+0x66], 0xFFFFFFFE
$_532:	cmp	byte ptr [rsi+0x63], 0
	jz	$_533
	mov	byte ptr [rsi+0xA], 0
$_533:	jmp	$_535

$_534:	cmp	ecx, 130
	jz	$_530
	cmp	ecx, 129
	jz	$_531
	cmp	ecx, 132
	jz	$_532
$_535:	jmp	$_621
$C02EE:
	cmp	ecx, 16777218
	jnz	$_541
	jmp	$_540

$_536:	jmp	$_541

$_537:	and	byte ptr [rsi+0x66], 0xFFFFFFFE
$_538:	cmp	byte ptr [rsi+0x63], 0
	jz	$_539
	mov	byte ptr [rsi+0xA], 0
$_539:	jmp	$_541

$_540:	cmp	edx, 130
	jz	$_536
	cmp	edx, 129
	jz	$_537
	cmp	edx, 132
	jz	$_538
$_541:	jmp	$_621
$C02F6:
	jmp	$_621
$C02F7:
	mov	rcx, qword ptr [rdi+0x50]
	cmp	dword ptr [rsi+0x10], 4202240
	jnz	$_543
	test	byte ptr [rsi+0x66], 0x40
	jnz	$_543
	test	rcx, rcx
	jz	$_542
	cmp	byte ptr [rcx+0x18], 0
	jz	$_543
$_542:	mov	ecx, 2023
	call	asmerr@PLT
	mov	dword ptr [rbp-0xC], eax
	jmp	$_621

$_543:	mov	rcx, qword ptr [rdi+0xB8]
	cmp	dword ptr [rdi+0xA4], 1
	jnz	$_544
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_544
	test	byte ptr [rdi+0xAB], 0x01
	jnz	$_544
	test	rcx, rcx
	jz	$_544
	cmp	byte ptr [rcx+0x18], 0
	jnz	$_544
	mov	dword ptr [rsi+0x28], 65536
	mov	dword ptr [rsi+0x38], 1
$_544:	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	OperandSize
	cmp	rax, 1
	jbe	$_545
	or	byte ptr [rsi+0x66], 0x01
$_545:	cmp	dword ptr [rbp-0x8], 8388609
	jnz	$_546
	and	byte ptr [rsi+0x61], 0xFFFFFFC7
$_546:	jmp	$_621
$C0305:
$C0307:
	mov	rdx, rsi
	call	OperandSize
	add	eax, 2
	mov	dword ptr [rbp-0x10], eax
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x8]
	call	OperandSize
	mov	dword ptr [rbp-0x14], eax
	cmp	dword ptr [rbp-0x14], 0
	jz	$_547
	mov	eax, dword ptr [rbp-0x14]
	cmp	dword ptr [rbp-0x10], eax
	jz	$_547
	mov	ecx, 2024
	call	asmerr@PLT
	jmp	$_622

$_547:	jmp	$_621
$C030C:
	jmp	$_621
$C030D:
	and	byte ptr [rsi+0x66], 0xFFFFFFFE
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	OperandSize
	mov	dword ptr [rbp-0x10], eax
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x8]
	call	OperandSize
	mov	dword ptr [rbp-0x14], eax
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_549
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_549
	cmp	dword ptr [rbp-0x10], 2
	jnz	$_548
	lea	rdx, [DS0001+rip]
	mov	ecx, 8019
	call	asmerr@PLT
	jmp	$_549

$_548:	mov	ecx, 2023
	call	asmerr@PLT
$_549:	jmp	$_557

$_550:	cmp	dword ptr [rbp-0x14], 2
	jge	$_551
	jmp	$_553

$_551:	cmp	dword ptr [rbp-0x14], 2
	jnz	$_552
	or	byte ptr [rsi+0x66], 0x01
	jmp	$_553

$_552:	mov	ecx, 2024
	call	asmerr@PLT
	mov	dword ptr [rbp-0xC], eax
$_553:	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_558

$_554:	cmp	dword ptr [rbp-0x14], 2
	jl	$_555
	mov	ecx, 2024
	call	asmerr@PLT
	mov	dword ptr [rbp-0xC], eax
$_555:	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	setne	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_558

$_556:	mov	ecx, 2024
	call	asmerr@PLT
	mov	dword ptr [rbp-0xC], eax
	jmp	$_558

$_557:	cmp	dword ptr [rbp-0x10], 8
	jz	$_550
	cmp	dword ptr [rbp-0x10], 4
	jz	$_550
	cmp	dword ptr [rbp-0x10], 2
	jz	$_554
	jmp	$_556

$_558:	jmp	$_621
$C031C:
	jmp	$_621
$C031D:
	mov	byte ptr [rsi+0xA], 0
	jmp	$C035E
$C031E:
	and	edx, 0x401F00
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_559
	test	edx, edx
	jnz	$_560
$_559:	jmp	$C035E

$_560:	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x8]
	call	OperandSize
	mov	dword ptr [rbp-0x14], eax
	cmp	eax, 2
	jz	$_561
	test	eax, eax
	jz	$_561
	mov	ecx, 2024
	call	asmerr@PLT
	jmp	$_622

$_561:	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	OperandSize
	mov	dword ptr [rbp-0x10], eax
	cmp	eax, 2
	jz	$_562
	mov	byte ptr [rsi+0xA], 0
$_562:	jmp	$_621
$C0325:
	cmp	dword ptr [rsi+0x40], 0
	jz	$_565
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	OperandSize
	mov	dword ptr [rbp-0x10], eax
	mov	rdx, rsi
	mov	ecx, dword ptr [rsi+0x40]
	call	OperandSize
	cmp	dword ptr [rbp-0x10], 2
	jnz	$_563
	cmp	eax, 2
	jbe	$_563
	mov	r8d, eax
	mov	edx, dword ptr [rbp-0x10]
	mov	ecx, 2022
	call	asmerr@PLT
	mov	dword ptr [rbp-0xC], eax
	jmp	$_621

$_563:	test	byte ptr [rsi+0x42], 0x06
	jz	$_565
	mov	eax, 262144
	cmp	dword ptr [rbp-0x10], 2
	jnz	$_564
	mov	eax, 131072
$_564:	mov	dword ptr [rsi+0x40], eax
$_565:	jmp	$C035E

	jmp	$_621
$C032A:
$C032B:
$C032C:
$C032D:
$C032E:
$C0332:
$C0333:
$C0334:
$C0335: jmp	$_621
$C0338: cmp	edx, 4202240
	jnz	$_566
	test	byte ptr [rdi+0xAB], 0x01
	jz	$_566
	mov	ecx, 2023
	call	asmerr@PLT
	jmp	$_622
$_566:	jmp	$_621
$C033C:
	test	ecx, 0x20
	je	$_621
$C033D:
	cmp	edx, 4202240
	jnz	$_567
	or	byte ptr [rsi+0x29], 0x20
$_567:	jmp	$_621
$C033F:
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x8]
	call	OperandSize
	mov	dword ptr [rbp-0x14], eax
	cmp	eax, 2
	jnc	$_568
	mov	byte ptr [rsi+0xA], 0
	jmp	$_570

$_568:	cmp	eax, 2
	jnz	$_569
	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	setne	al
	mov	byte ptr [rsi+0xA], al
	jmp	$_570

$_569:	xor	eax, eax
	cmp	byte ptr [rsi+0x63], al
	sete	al
	mov	byte ptr [rsi+0xA], al
$_570:	jmp	$_621
$C0343:
	jmp	$_621
$C0344:
	test	byte ptr [rbp-0x1], 0x0C
	jz	$_573
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x8]
	call	OperandSize
	mov	dword ptr [rbp-0x14], eax
	cmp	eax, 2
	jz	$_571
	cmp	eax, 4
	jz	$_571
	cmp	eax, 8
	jnz	$_572
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_572
$_571:	xor	eax, eax
	jmp	$_622

$_572:	jmp	$C035E

$_573:	test	byte ptr [rbp-0x5], 0x0C
	jz	$_576
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	OperandSize
	mov	dword ptr [rbp-0x10], eax
	cmp	eax, 2
	jz	$_574
	cmp	eax, 4
	jz	$_574
	cmp	eax, 8
	jnz	$_575
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_575
$_574:	xor	eax, eax
	jmp	$_622

$_575:	jmp	$C035E

$_576:	test	dword ptr [rbp-0x4], 0x401F00
	jz	$_580
	test	dword ptr [rbp-0x8], 0x80
	jz	$_580
	test	byte ptr [rsi+0x66], 0x02
	jnz	$_577
	and	dword ptr [rsi+0x28], 0xFFFFFF7F
	jmp	$_579

$_577:	cmp	byte ptr [rsi+0x63], 2
	jnz	$_579
	movabs	rax, 0x80000000
	mov	rdx, -2147483648
	cmp	qword ptr [rsi+0x20], rax
	jc	$_578
	cmp	qword ptr [rsi+0x20], rdx
	jc	$_579
$_578:	and	dword ptr [rsi+0x28], 0xFFFFFF7F
$_579:	jmp	$C035E

$_580:	test	dword ptr [rbp-0x4], 0x80
	jz	$C035E
	test	dword ptr [rbp-0x8], 0x401F00
	jz	$C035E
	test	byte ptr [rsi+0x66], 0x02
	jnz	$_581
	and	dword ptr [rsi+0x10], 0xFFFFFF7F
	jmp	$C035E

$_581:	cmp	byte ptr [rsi+0x63], 2
	jnz	$C035E
	mov	eax, 2147483648
	mov	rdx, -2147483648
	cmp	qword ptr [rsi+0x38], rax
	jc	$_582
	cmp	qword ptr [rsi+0x38], rdx
	jc	$C035E
$_582:	and	dword ptr [rsi+0x10], 0xFFFFFF7F
$C035E: mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	OperandSize
	mov	dword ptr [rbp-0x10], eax
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x8]
	call	OperandSize
	mov	dword ptr [rbp-0x14], eax
	cmp	dword ptr [rbp-0x10], eax
	jle	$_583
	cmp	dword ptr [rbp-0x8], 65536
	jl	$_583
	cmp	dword ptr [rbp-0x8], 262144
	jg	$_583
	mov	eax, dword ptr [rbp-0x10]
	mov	dword ptr [rbp-0x14], eax
$_583:	cmp	dword ptr [rbp-0x10], 1
	jnz	$_584
	cmp	dword ptr [rbp-0x8], 131072
	jnz	$_584
	cmp	dword ptr [rsi+0x38], 255
	jg	$_584
	cmp	dword ptr [rsi+0x38], -255
	jl	$_584
	mov	eax, dword ptr [rbp-0xC]
	jmp	$_622

$_584:	mov	eax, dword ptr [rbp-0x14]
	cmp	dword ptr [rbp-0x10], eax
	je	$_618
	mov	eax, dword ptr [rbp-0x4]
	or	eax, dword ptr [rbp-0x8]
	test	eax, 0x108070
	jnz	$_585
	cmp	word ptr [rsi+0xE], 1301
	jc	$_586
$_585:	jmp	$_590

$_586:	cmp	dword ptr [rbp-0x10], 0
	je	$_590
	cmp	dword ptr [rbp-0x14], 0
	je	$_590
	mov	eax, 1
	cmp	byte ptr [rsi+0x63], 0
	jbe	$_589
	test	dword ptr [rbp-0x4], 0x607F00
	jz	$_589
	test	dword ptr [rbp-0x8], 0x607F00
	jz	$_589
	movzx	ecx, word ptr [rsi+0xE]
	jmp	$_588

$_587:	xor	eax, eax
	jmp	$_589

$_588:	cmp	ecx, 682
	jz	$_587
	cmp	ecx, 588
	jz	$_587
	cmp	ecx, 737
	jz	$_587
	cmp	ecx, 583
	jz	$_587
	cmp	ecx, 581
	jz	$_587
	cmp	ecx, 584
	jz	$_587
	cmp	ecx, 586
	jz	$_587
	cmp	ecx, 585
	jz	$_587
	cmp	ecx, 582
	jz	$_587
	cmp	ecx, 587
	jz	$_587
$_589:	test	eax, eax
	jz	$_590
	mov	r8d, dword ptr [rbp-0x14]
	mov	edx, dword ptr [rbp-0x10]
	mov	ecx, 2022
	call	asmerr@PLT
	mov	dword ptr [rbp-0xC], eax
$_590:	cmp	dword ptr [rbp-0x10], 0
	jne	$_618
	mov	eax, dword ptr [rbp-0x4]
	or	eax, dword ptr [rbp-0x8]
	test	dword ptr [rbp-0x4], 0x607F00
	je	$_603
	test	byte ptr [rbp-0x6], 0x07
	je	$_603
	mov	eax, dword ptr [rsi+0x38]
	cmp	dword ptr [rbp-0x14], 1
	jz	$_592
	cmp	dword ptr [rbp-0x4], 4202240
	jnz	$_594
	test	byte ptr [rdi+0xAB], 0x02
	jnz	$_594
	cmp	eax, 0
	jge	$_591
	cmp	eax, -128
	jl	$_594
$_591:	cmp	eax, 255
	jg	$_594
$_592:	mov	byte ptr [rsi+0x60], 0
	mov	dword ptr [rsi+0x28], 65536
	lea	rcx, [DS0001+rip]
	cmp	dword ptr [rbp-0x4], 4202240
	jnz	$_593
	test	byte ptr [rdi+0xAB], 0x02
	jnz	$_593
	mov	dword ptr [rsi+0x10], 256
$_593:	jmp	$_599

$_594:	cmp	dword ptr [rbp-0x14], 2
	jnz	$_596
	cmp	eax, 0
	jge	$_595
	cmp	eax, 4294934528
	jl	$_596
$_595:	cmp	eax, 65535
	jg	$_596
	mov	byte ptr [rsi+0x60], 1
	or	byte ptr [rsi+0x66], 0x01
	mov	dword ptr [rsi+0x28], 131072
	lea	rcx, [DS0002+rip]
	jmp	$_599

$_596:	or	byte ptr [rsi+0x66], 0x01
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jnz	$_597
	cmp	dword ptr [rbp-0x14], 2
	jle	$_597
	cmp	dword ptr [rsi+0x38], 65535
	jg	$_597
	cmp	dword ptr [rsi+0x38], -65535
	jl	$_597
	mov	dword ptr [rbp-0x14], 2
$_597:	cmp	dword ptr [rbp-0x14], 2
	jg	$_598
	cmp	eax, 4294934528
	jle	$_598
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jnz	$_598
	mov	byte ptr [rsi+0x60], 1
	mov	dword ptr [rsi+0x28], 131072
	jmp	$_599

$_598:	mov	byte ptr [rsi+0x60], 3
	mov	dword ptr [rsi+0x28], 262144
	lea	rcx, [DS0003+rip]
$_599:	test	byte ptr [rdi+0xAB], 0x02
	jnz	$_602
	mov	rax, qword ptr [rsi+0x18]
	test	rax, rax
	jnz	$_600
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_600
	test	byte ptr [rsi+0x66], 0x40
	jz	$_601
$_600:	test	rax, rax
	jz	$_602
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_602
$_601:	mov	rdx, rcx
	mov	ecx, 8019
	call	asmerr@PLT
$_602:	jmp	$_618

$_603:	test	dword ptr [rbp-0x4], 0x607F00
	jz	$_604
	test	dword ptr [rbp-0x8], 0xC00000F
	jz	$_604
	jmp	$_618

$_604:	test	dword ptr [rbp-0x4], 0x8010
	jz	$_608
	test	byte ptr [rbp-0x6], 0x07
	jz	$_608
	mov	eax, dword ptr [rsi+0x38]
	cmp	eax, 65535
	jbe	$_605
	mov	dword ptr [rsi+0x28], 262144
	jmp	$_607

$_605:	cmp	eax, 255
	jbe	$_606
	mov	dword ptr [rsi+0x28], 131072
	jmp	$_607

$_606:	mov	dword ptr [rsi+0x28], 65536
$_607:	jmp	$_618

$_608:	test	eax, 0x8010
	jz	$_609
	jmp	$_618

$_609:	jmp	$_617

$_610:	mov	byte ptr [rsi+0x60], 0
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_611
	test	byte ptr [rbp-0x6], 0x07
	jz	$_611
	lea	rdx, [DS0001+rip]
	mov	ecx, 8019
	call	asmerr@PLT
$_611:	jmp	$_618

$_612:	mov	byte ptr [rsi+0x60], 1
	or	byte ptr [rsi+0x66], 0x01
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_613
	test	byte ptr [rbp-0x6], 0x07
	jz	$_613
	lea	rdx, [DS0003+0x1+rip]
	mov	ecx, 8019
	call	asmerr@PLT
$_613:	cmp	byte ptr [rsi+0x63], 0
	jz	$_614
	mov	byte ptr [rsi+0xA], 1
$_614:	jmp	$_618

$_615:	mov	byte ptr [rsi+0x60], 3
	or	byte ptr [rsi+0x66], 0x01
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_616
	test	byte ptr [rbp-0x6], 0x07
	jz	$_616
	lea	rdx, [DS0003+rip]
	mov	ecx, 8019
	call	asmerr@PLT
$_616:	jmp	$_618

$_617:	cmp	dword ptr [rbp-0x14], 1
	je	$_610
	cmp	dword ptr [rbp-0x14], 2
	jz	$_612
	cmp	dword ptr [rbp-0x14], 4
	jz	$_615
$_618:	jmp	$_621

$_619:	cmp	eax, 682
	jl	$_620
	cmp	eax, 721
	jg	$_620
	push	rax
	lea	r11, [$C035E+rip]
	movzx	eax, byte ptr [r11+rax-(682)+(IT$C0399-$C035E)]
	movzx	eax, word ptr [r11+rax*2+($C0399-$C035E)]
	sub	r11, rax
	pop	rax
	jmp	r11

	.ALIGN 2
$C0399:
	.word $C035E-$C02E6
	.word $C035E-$C02EE
	.word $C035E-$C02F6
	.word $C035E-$C0307
	.word $C035E-$C030C
	.word $C035E-$C030D
	.word $C035E-$C031E
	.word $C035E-$C0325
	.word $C035E-$C0344
	.word 0
IT$C0399:
	.byte 8
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 4
	.byte 9
	.byte 7
	.byte 0
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 9
	.byte 6
	.byte 6
	.byte 2
	.byte 9
	.byte 3
	.byte 3
	.byte 3
	.byte 9
	.byte 9
	.byte 5
	.byte 5
	.byte 9
	.byte 1
	.ALIGN 2
$C039A:

$_620:	cmp	eax, 1299
	jl	$C039C
	cmp	eax, 1326
	jg	$C039C
	push	rax
	lea	r11, [$C035E+rip]
	movzx	eax, byte ptr [r11+rax-(1299)+(IT$C039B-$C035E)]
	movzx	eax, word ptr [r11+rax*2+($C039B-$C035E)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C039B:
	.word $C035E-$C032E
	.word $C035E-$C0338
	.word $C035E-$C033C
	.word $C035E-$C033D
	.word 0
IT$C039B:
	.byte 0
	.byte 0
	.byte 4
	.byte 0
	.byte 0
	.byte 4
	.byte 4
	.byte 0
	.byte 0
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 3
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 4
	.byte 1
	.byte 1
	.byte 1
	.byte 2
	.ALIGN 2
$C039C:
	cmp	eax, 589
	jl	$C039E
	cmp	eax, 632
	jg	$C039E
	push	rax
	lea	r11, [$C035E+rip]
	movzx	eax, byte ptr [r11+rax-(589)+(IT$C039D-$C035E)]
	movzx	eax, word ptr [r11+rax*2+($C039D-$C035E)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C039D:
	.word $C035E-$C02F7
	.word $C035E-$C0305
	.word 0
IT$C039D:
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 2
	.byte 1
	.byte 1
	.ALIGN 2
$C039E:
	cmp	eax, 1196
	je	$C02E3
	cmp	eax, 1203
	je	$C031C
	cmp	eax, 644
	je	$C031D
	cmp	eax, 1005
	je	$C032A
	cmp	eax, 1013
	je	$C032B
	cmp	eax, 1006
	je	$C032C
	cmp	eax, 1014
	je	$C032D
	cmp	eax, 1369
	je	$C0332
	cmp	eax, 1370
	je	$C0333
	cmp	eax, 1375
	je	$C0334
	cmp	eax, 1376
	je	$C0335
	cmp	eax, 1266
	je	$C033F
	cmp	eax, 1027
	je	$C0343
	jmp	$C035E

$_621:	mov	eax, dword ptr [rbp-0xC]
$_622:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_623:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call	SymFind@PLT
	test	rax, rax
	jz	$_624
	cmp	byte ptr [rax+0x18], 7
	jnz	$_624
	jmp	$_625

$_624:	xor	eax, eax
$_625:	leave
	ret

$_626:
	mov	eax, dword ptr [rcx]
	jmp	$_644

$_627:	inc	rcx
	mov	eax, dword ptr [rcx]
	jmp	$_644

$_628:	cmp	ah, 49
	jc	$_645
	cmp	ah, 55
	ja	$_645
	test	eax, 0xFF0000
	jne	$_645
	sub	ah, 48
	or	byte ptr [rdx], ah
	mov	eax, 1
	jmp	$_646

$_629:	cmp	ah, 116
	jne	$_645
	shr	eax, 24
	jmp	$_632

$_630:	cmp	byte ptr [rcx+0x4], 54
	jnz	$_633
$_631:	or	byte ptr [rdx], 0x10
	mov	eax, 1
	jmp	$_646

	jmp	$_633

$_632:	cmp	al, 49
	jz	$_630
	cmp	al, 50
	jz	$_631
	cmp	al, 52
	jz	$_631
	cmp	al, 56
	jz	$_631
$_633:	jmp	$_645

$_634:	test	ah, ah
	jne	$_645
	or	byte ptr [rdx], 0xFFFFFF80
	mov	eax, 1
	jmp	$_646

$_635:	cmp	byte ptr [rcx+0x2], 45
	jne	$_645
	cmp	byte ptr [rcx+0x3], 115
	jne	$_645
	mov	ecx, 8192
	jmp	$_640

$_636:	or	cl, 0x50
	jmp	$_641

$_637:	or	cl, 0x70
$_638:	or	cl, 0x30
$_639:	or	cl, 0x10
	jmp	$_641

$_640:	cmp	ah, 117
	jz	$_636
	cmp	ah, 122
	jz	$_637
	cmp	ah, 100
	jz	$_638
	cmp	ah, 110
	jz	$_639
$_641:	test	cl, cl
	jz	$_642
	or	word ptr [rdx], cx
	mov	eax, 1
	jmp	$_646

$_642:	jmp	$_645

$_643:	cmp	eax, 6644083
	jnz	$_645
	mov	ecx, 8208
	or	word ptr [rdx], cx
	mov	eax, 1
	jmp	$_646

	jmp	$_645

$_644:	cmp	al, 9
	je	$_627
	cmp	al, 32
	je	$_627
	cmp	al, 107
	je	$_628
	cmp	al, 49
	je	$_629
	cmp	al, 122
	je	$_634
	cmp	al, 114
	je	$_635
	cmp	al, 115
	jz	$_643
$_645:	xor	eax, eax
$_646:	ret

ParseLine:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 616
	mov	rbx, rcx
	cmp	qword ptr [CurrEnum+rip], 0
	jz	$_647
	cmp	byte ptr [rbx], 8
	jnz	$_647
	mov	rdx, rbx
	xor	ecx, ecx
	call	EnumDirective@PLT
	jmp	$_866

$_647:	mov	dword ptr [rbp-0x4], 0
	cmp	dword ptr [ModuleInfo+0x220+rip], 2
	jle	$_653
	cmp	byte ptr [rbx], 8
	jne	$_653
	cmp	byte ptr [rbx+0x18], 58
	jz	$_648
	cmp	byte ptr [rbx+0x18], 13
	jne	$_653
$_648:	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	call	MemAlloc@PLT
	mov	rdi, rax
	mov	rdx, qword ptr [rbx+0x40]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbx+0x20]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcat@PLT
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rcx, rbx
	call	ParseLine
	cmp	eax, -1
	jnz	$_649
	mov	rcx, rdi
	call	MemFree@PLT
	mov	rax, -1
	jmp	$_866

$_649:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_650
	and	byte ptr [ModuleInfo+0x1C6+rip], 0xFFFFFFFE
$_650:	mov	rdx, rdi
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	mov	rcx, rdi
	call	MemFree@PLT
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rdx, rbx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	ExpandLine@PLT
	cmp	eax, -2
	jz	$_651
	cmp	eax, -1
	jnz	$_652
$_651:	jmp	$_866

$_652:	mov	dword ptr [rbp-0x4], 0
	jmp	$_661

$_653:	cmp	byte ptr [rbx], 8
	jne	$_661
	cmp	byte ptr [rbx+0x18], 58
	jz	$_654
	cmp	byte ptr [rbx+0x18], 13
	jne	$_661
$_654:	mov	dword ptr [rbp-0x4], 2
	test	dword ptr [ProcStatus+rip], 0x80
	jz	$_655
	mov	rcx, rbx
	call	write_prologue@PLT
$_655:	xor	eax, eax
	cmp	byte ptr [ModuleInfo+0x1D7+rip], 0
	jz	$_656
	cmp	qword ptr [CurrProc+rip], 0
	jz	$_656
	cmp	byte ptr [rbx+0x18], 13
	jz	$_656
	inc	eax
$_656:	mov	r9d, eax
	xor	r8d, r8d
	mov	edx, 129
	mov	rcx, qword ptr [rbx+0x8]
	call	CreateLabel@PLT
	test	rax, rax
	jnz	$_657
	mov	rax, -1
	jmp	$_866

$_657:	cmp	byte ptr [rbx+0x18], 13
	jnz	$_658
	cmp	byte ptr [ModuleInfo+0x1D7+rip], 0
	jz	$_658
	cmp	qword ptr [CurrProc+rip], 0
	jnz	$_658
	mov	byte ptr [rbx+0x18], 0
	mov	dword ptr [ModuleInfo+0x220+rip], 1
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 4294967295
	call	PublicDirective@PLT
$_658:	lea	rsi, [rbx+0x30]
	cmp	byte ptr [rsi], 0
	jnz	$_661
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_659
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_659:	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_660
	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 7
	call	LstWrite@PLT
$_660:	xor	eax, eax
	jmp	$_866

$_661:	imul	esi, dword ptr [rbp-0x4], 24
	add	rsi, rbx
	mov	dword ptr [rbp-0x8], 0
	cmp	qword ptr [ModuleInfo+0x108+rip], 0
	jz	$_663
	cmp	byte ptr [rbx], 6
	jnz	$_662
	cmp	byte ptr [rbx+0x18], 3
	jnz	$_662
	cmp	dword ptr [rbx+0x1C], 508
	jnz	$_662
	inc	dword ptr [rbp-0x8]
$_662:	jmp	$_664

$_663:	cmp	byte ptr [rbx], 3
	jnz	$_664
	cmp	dword ptr [rbx+0x4], 406
	jnz	$_664
	mov	byte ptr [rbx], 8
	mov	rax, qword ptr [rbx+0x20]
	mov	qword ptr [rbx+0x8], rax
	mov	byte ptr [rbx+0x18], 3
	mov	dword ptr [rbx+0x1C], 507
	mov	byte ptr [rbx+0x19], 29
$_664:	cmp	dword ptr [rbp-0x8], 0
	jnz	$_665
	cmp	byte ptr [rsi], 1
	je	$_714
$_665:	mov	byte ptr [Frame_Type+rip], 6
	mov	qword ptr [SegOverride+rip], 0
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_671
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_666
	cmp	byte ptr [rbx], 8
	jnz	$_671
$_666:	cmp	byte ptr [rbx+0x18], 3
	jnz	$_667
	inc	dword ptr [rbp-0x4]
	add	rsi, 24
	jmp	$_671

$_667:	mov	rcx, qword ptr [rbx+0x8]
	call	$_623
	mov	qword ptr [rbp-0x20], rax
	test	rax, rax
	jnz	$_668
	inc	dword ptr [rbp-0x4]
	add	rsi, 24
	jmp	$_671

$_668:	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_671
	xor	eax, eax
	cmp	byte ptr [rbx+0x18], 6
	jnz	$_669
	inc	eax
	jmp	$_670

$_669:	cmp	byte ptr [rbx+0x18], 8
	jnz	$_670
	mov	rcx, qword ptr [rbx+0x20]
	call	$_623
$_670:	test	rax, rax
	jz	$_671
	inc	dword ptr [rbp-0x4]
	add	rsi, 24
$_671:	movzx	eax, byte ptr [rsi]
	jmp	$_704

$_672:	cmp	byte ptr [rsi+0x1], 8
	jnz	$_673
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp-0x4]
	call	data_dir@PLT
	jmp	$_866

$_673:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rsi+0x4], 12
	mov	eax, dword ptr [r11+rax]
	mov	dword ptr [rbp-0x14], eax
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_674
	cmp	qword ptr [CurrStruct+rip], 0
	je	$_681
	test	byte ptr [rbp-0x14], 0x10
	je	$_681
$_674:	cmp	dword ptr [rsi+0x4], 508
	jz	$_675
	mov	ecx, 2037
	call	asmerr@PLT
	jmp	$_866

$_675:	cmp	dword ptr [StoreState+rip], 0
	jz	$_678
	test	byte ptr [rbp-0x13], 0x01
	jz	$_677
	cmp	qword ptr [ModuleInfo+0x218+rip], 0
	jz	$_677
	cmp	byte ptr [ModuleInfo+0x1DE+rip], 0
	jz	$_677
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_676
	xor	r8d, r8d
	mov	edx, 1
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_676:	jmp	$_678

$_677:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_678
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_678:	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp-0x4]
	call	ProcType@PLT
	mov	edi, eax
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_680
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_679
	cmp	dword ptr [ModuleInfo+0x210+rip], 0
	jnz	$_679
	cmp	dword ptr [UseSavedState+rip], 0
	jnz	$_680
$_679:	call	LstWriteSrcLine@PLT
$_680:	mov	eax, edi
	jmp	$_866

$_681:	test	byte ptr [rbp-0x14], 0x08
	jz	$_683
	cmp	dword ptr [rbp-0x4], 0
	jz	$_682
	cmp	byte ptr [rbx], 8
	jz	$_682
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_682:	jmp	$_684

$_683:	cmp	dword ptr [rbp-0x4], 0
	jz	$_684
	cmp	byte ptr [rsi-0x18], 58
	jz	$_684
	cmp	byte ptr [rsi-0x18], 13
	jz	$_684
	mov	rdx, qword ptr [rsi-0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_684:	test	dword ptr [ProcStatus+rip], 0x80
	jz	$_685
	test	byte ptr [rbp-0x14], 0x40
	jz	$_685
	mov	rcx, qword ptr [rbp+0x28]
	call	write_prologue@PLT
$_685:	cmp	dword ptr [StoreState+rip], 0
	jnz	$_686
	test	dword ptr [rbp-0x14], 0x80
	jz	$_689
$_686:	test	byte ptr [rbp-0x13], 0x01
	jz	$_688
	cmp	qword ptr [ModuleInfo+0x218+rip], 0
	jz	$_688
	cmp	byte ptr [ModuleInfo+0x1DE+rip], 0
	jz	$_688
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_687
	xor	r8d, r8d
	mov	edx, 1
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_687:	jmp	$_689

$_688:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_689
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_689:	cmp	byte ptr [rsi+0x1], 8
	jbe	$_690
	movzx	eax, byte ptr [rsi+0x1]
	lea	rcx, [directive_tab+rip]
	mov	rax, qword ptr [rcx+rax*8]
	mov	rdx, rbx
	mov	ecx, dword ptr [rbp-0x4]
	call	rax
	mov	edi, eax
	jmp	$_695

$_690:	mov	edi, 4294967295
	mov	eax, dword ptr [rsi+0x4]
	jmp	$_694

$_691:	mov	ecx, 1008
	call	asmerr@PLT
	jmp	$_695

$_692:	mov	ecx, 2170
	call	asmerr@PLT
	jmp	$_695

$_693:	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_695

$_694:	cmp	eax, 475
	jz	$_691
	cmp	eax, 409
	jz	$_692
	cmp	eax, 474
	jz	$_692
	cmp	eax, 476
	jz	$_692
	jmp	$_693

$_695:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_697
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_696
	cmp	dword ptr [ModuleInfo+0x210+rip], 0
	jnz	$_696
	cmp	dword ptr [UseSavedState+rip], 0
	jnz	$_697
$_696:	call	LstWriteSrcLine@PLT
$_697:	mov	eax, edi
	jmp	$_866

$_698:	cmp	dword ptr [rsi+0x4], 270
	jnz	$_705
$_699:	xor	r8d, r8d
	mov	rdx, rbx
	mov	ecx, dword ptr [rbp-0x4]
	call	data_dir@PLT
	jmp	$_866

$_700:	mov	rcx, qword ptr [rsi+0x8]
	call	$_623
	test	rax, rax
	jz	$_701
	test	byte ptr [rsi+0x2], 0x08
	jnz	$_705
	mov	r8, rax
	mov	rdx, rbx
	mov	ecx, dword ptr [rbp-0x4]
	call	data_dir@PLT
	jmp	$_866

$_701:	jmp	$_705

$_702:	cmp	byte ptr [rsi], 58
	jnz	$_703
	lea	rdx, [DS0004+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_866

$_703:	jmp	$_705

$_704:	cmp	eax, 3
	je	$_672
	cmp	eax, 5
	jz	$_698
	cmp	eax, 6
	jz	$_699
	cmp	eax, 8
	jz	$_700
	jmp	$_702

$_705:	cmp	dword ptr [rbp-0x4], 0
	jz	$_706
	cmp	byte ptr [rsi-0x18], 8
	jnz	$_706
	dec	dword ptr [rbp-0x4]
	sub	rsi, 24
$_706:	cmp	dword ptr [rbp-0x4], 0
	jnz	$_707
	cmp	byte ptr [rbx+0x1], 123
	je	$_714
$_707:	cmp	qword ptr [CurrEnum+rip], 0
	jz	$_708
	cmp	byte ptr [rbx], 9
	jnz	$_708
	mov	rdx, rbx
	xor	ecx, ecx
	call	EnumDirective@PLT
	jmp	$_866

$_708:	cmp	dword ptr [rbp-0x4], 0
	jnz	$_713
	cmp	dword ptr [ModuleInfo+0x220+rip], 1
	jle	$_713
	lea	rcx, [rbx+0x18]
	call	GetOperator@PLT
	test	rax, rax
	jz	$_709
	mov	rcx, qword ptr [rbp+0x28]
	call	ProcessOperator@PLT
	jmp	$_866

$_709:	cmp	byte ptr [rbx], 5
	jnz	$_710
	cmp	dword ptr [rbx+0x4], 271
	jz	$_711
$_710:	cmp	byte ptr [rbx], 4
	jnz	$_713
	cmp	dword ptr [rbx+0x4], 262
	jnz	$_713
$_711:	mov	ecx, dword ptr [rbx+0x4]
	call	RemoveResWord@PLT
	mov	byte ptr [rbx], 8
	mov	rcx, rbx
	call	PreprocessLine@PLT
	test	rax, rax
	jz	$_712
	mov	rcx, rbx
	call	ParseLine
$_712:	jmp	$_866

$_713:	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_714:	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_715
	mov	ecx, 2037
	call	asmerr@PLT
	jmp	$_866

$_715:	test	dword ptr [ProcStatus+rip], 0x80
	jz	$_716
	mov	rcx, rbx
	call	write_prologue@PLT
$_716:	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_717
	call	GetCurrOffset@PLT
	mov	dword ptr [rbp-0x24], eax
$_717:	xor	eax, eax
	mov	ecx, 26
	lea	rdi, [rbp-0x90]
	rep stosd
	mov	dword ptr [rbp-0x90], -2
	mov	dword ptr [rbp-0x8C], -2
	mov	byte ptr [rbp-0x30], -64
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x2D], al
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_719
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_719
	lea	rdx, [DS0005+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_718
	mov	byte ptr [rbp-0x85], 1
	inc	dword ptr [rbp-0x4]
	add	rsi, 24
	jmp	$_719

$_718:	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_719:	cmp	dword ptr [rsi+0x4], 658
	jc	$_720
	cmp	dword ptr [rsi+0x4], 663
	ja	$_720
	mov	eax, dword ptr [rsi+0x4]
	mov	dword ptr [rbp-0x90], eax
	inc	dword ptr [rbp-0x4]
	add	rsi, 24
	cmp	byte ptr [rsi], 1
	jz	$_720
	mov	ecx, 2068
	call	asmerr@PLT
	jmp	$_866

$_720:	cmp	qword ptr [CurrProc+rip], 0
	je	$_727
	jmp	$_726

$_721:	test	byte ptr [ProcStatus+rip], 0x02
	jnz	$_724
	cmp	byte ptr [ModuleInfo+0x1F0+rip], 2
	jz	$_724
	xor	eax, eax
	cmp	qword ptr [ModuleInfo+0x218+rip], 0
	jz	$_722
	cmp	byte ptr [ModuleInfo+0x1DE+rip], 0
	jz	$_722
	inc	eax
$_722:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_723
	xor	r8d, r8d
	mov	edx, eax
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_723:	or	byte ptr [ProcStatus+rip], 0x02
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp-0x4]
	call	RetInstr@PLT
	and	dword ptr [ProcStatus+rip], 0xFFFFFFFD
	jmp	$_866

$_724:	cmp	dword ptr [rsi+0x4], 726
	jnz	$_725
	mov	rax, qword ptr [CurrProc+rip]
	cmp	byte ptr [rax+0x19], -126
	jnz	$_725
	mov	dword ptr [rsi+0x4], 728
$_725:	jmp	$_727

$_726:	cmp	dword ptr [rsi+0x4], 726
	je	$_721
	cmp	dword ptr [rsi+0x4], 704
	je	$_721
	cmp	dword ptr [rsi+0x4], 705
	je	$_721
	cmp	dword ptr [rsi+0x4], 1201
	je	$_721
$_727:	test	byte ptr [rbx+0x2], 0x40
	je	$_736
	lea	rsi, [rbx+0x18]
	mov	dword ptr [rbp-0x8], 1
$_728:	cmp	byte ptr [rsi], 0
	je	$_736
	test	byte ptr [rsi+0x2], 0x08
	je	$_735
	mov	byte ptr [rbp-0x231], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_729
	mov	byte ptr [rbp-0x231], 1
	call	MemAlloc@PLT
	jmp	$_730

$_729:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
$_730:	mov	rdi, rax
	mov	r8, rbx
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, rdi
	call	ExpandHllProcEx@PLT
	mov	dword ptr [rbp-0x10], eax
	cmp	byte ptr [rbp-0x231], 0
	jz	$_731
	mov	rcx, rdi
	call	MemFree@PLT
$_731:	cmp	dword ptr [rbp-0x10], -1
	jnz	$_732
	mov	rax, -1
	jmp	$_866

$_732:	cmp	dword ptr [rbp-0x10], 1
	jnz	$_734
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_733
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_733:	xor	eax, eax
	jmp	$_866

$_734:	jmp	$_736

$_735:	inc	dword ptr [rbp-0x8]
	add	rsi, 24
	jmp	$_728

$_736:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_737
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_737:	imul	esi, dword ptr [rbp-0x4], 24
	add	rsi, rbx
	mov	eax, dword ptr [rsi+0x4]
	mov	word ptr [rbp-0x82], ax
	sub	eax, 531
	lea	rcx, [optable_idx+rip]
	movzx	eax, word ptr [rcx+rax*2]
	lea	rcx, [InstrTable+rip]
	lea	rax, [rcx+rax*8]
	mov	qword ptr [rbp-0x38], rax
	inc	dword ptr [rbp-0x4]
	add	rsi, 24
	mov	rax, qword ptr [ModuleInfo+0x1F8+rip]
	test	rax, rax
	jnz	$_738
	mov	ecx, 2034
	call	asmerr@PLT
	jmp	$_866

$_738:	mov	rax, qword ptr [rax+0x68]
	cmp	dword ptr [rax+0x48], 0
	jnz	$_739
	mov	dword ptr [rax+0x48], 1
$_739:	cmp	byte ptr [ModuleInfo+0x1EE+rip], 0
	jz	$_740
	xor	ecx, ecx
	call	omf_OutSelect@PLT
$_740:	mov	dword ptr [rbp-0x8], 0
$_741:	cmp	dword ptr [rbp-0x8], 4
	jge	$_771
	cmp	byte ptr [rsi], 0
	je	$_771
	cmp	dword ptr [rbp-0x8], 0
	jz	$_742
	cmp	byte ptr [rsi], 44
	jne	$_771
	inc	dword ptr [rbp-0x4]
$_742:	imul	edi, dword ptr [rbp-0x8], 104
	lea	rcx, [rbp+rdi-0x230]
	mov	byte ptr [rsp+0x20], 0
	mov	r9, rcx
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_743
	jmp	$_866

$_743:	imul	esi, dword ptr [rbp-0x4], 24
	add	rsi, qword ptr [rbp+0x28]
	test	byte ptr [rsi-0x16], 0x10
	jz	$_746
	mov	byte ptr [rbp-0x85], 1
	lea	rbx, [rsi-0x18]
$_744:	lea	rdx, [rbp-0x84]
	mov	rcx, qword ptr [rbx+0x8]
	call	$_626
	test	rax, rax
	jnz	$_745
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_745:	sub	rbx, 24
	test	byte ptr [rbx+0x2], 0x10
	jnz	$_744
	cmp	dword ptr [rbp+rdi-0x1F4], -2
	jnz	$_746
	dec	dword ptr [rbp-0x8]
	jmp	$_770

$_746:	jmp	$_769

$_747:	cmp	dword ptr [rbp-0x8], 1
	jz	$_748
	cmp	word ptr [rbp-0x82], 677
	jz	$_748
	cmp	word ptr [rbp-0x82], 641
	jne	$_760
$_748:	cmp	byte ptr [Options+0xC6+rip], 0
	jne	$_759
	cmp	byte ptr [rbp+rdi-0x1F0], -64
	je	$_759
	movzx	eax, byte ptr [ModuleInfo+0x1CE+rip]
	cmp	dword ptr [rbp-0x8], 0
	jz	$_751
	cmp	dword ptr [rbp+rdi-0x25C], 2
	jnz	$_749
	test	byte ptr [rbp+rdi-0x255], 0x01
	jnz	$_749
	mov	rax, qword ptr [rbp+rdi-0x280]
	mov	ecx, dword ptr [rax+0x4]
	call	SizeFromRegister
	jmp	$_751

$_749:	cmp	dword ptr [rbp+rdi-0x25C], 1
	jz	$_750
	cmp	dword ptr [rbp+rdi-0x25C], 2
	jnz	$_751
$_750:	mov	r8, qword ptr [rbp+rdi-0x238]
	movzx	edx, byte ptr [rbp+rdi-0x256]
	movzx	ecx, byte ptr [rbp+rdi-0x258]
	call	SizeFromMemtype
$_751:	xor	ecx, ecx
	jmp	$_756

$_752:	mov	ecx, 33
	jmp	$_757

$_753:	mov	ecx, 35
	jmp	$_757

$_754:	mov	ecx, 39
	jmp	$_757

$_755:	mov	ecx, 47
	jmp	$_757

$_756:	cmp	eax, 2
	jz	$_752
	cmp	eax, 4
	jz	$_753
	cmp	eax, 8
	jz	$_754
	cmp	eax, 16
	jz	$_755
$_757:	test	ecx, ecx
	jz	$_759
	lea	rdx, [rbp+rdi-0x230]
	mov	dword ptr [rbp+rdi-0x1F4], 0
	mov	byte ptr [rbp+rdi-0x1F0], cl
	cmp	eax, 16
	jz	$_758
	mov	rcx, rdx
	mov	edx, eax
	call	quad_resize@PLT
$_758:	jmp	$_770

$_759:	mov	ecx, 2050
	call	asmerr@PLT
	jmp	$_866

$_760:	cmp	dword ptr [rbp-0x4], 1
	jle	$_767
	cmp	byte ptr [rsi], 3
	jne	$_767
	cmp	dword ptr [rsi+0x4], 410
	jne	$_767
	mov	byte ptr [rbp-0x231], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_761
	mov	byte ptr [rbp-0x231], 1
	call	MemAlloc@PLT
	jmp	$_762

$_761:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
$_762:	mov	rbx, rax
	mov	rax, qword ptr [rbp+0x28]
	mov	rax, qword ptr [rax+0x10]
	mov	rcx, qword ptr [rsi+0x10]
	sub	rcx, rax
	mov	rsi, rax
	mov	rdi, rbx
	rep movsb
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_763
	mov	eax, 7889266
	jmp	$_764

$_763:	mov	eax, 7889253
$_764:	stosd
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp-0x4]
	call	NewDirective@PLT
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_765
	mov	rdx, rbx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x28]
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rcx, rbx
	call	MemFree@PLT
	mov	rcx, qword ptr [rbp+0x28]
	call	ParseLine
	jmp	$_866

$_765:	cmp	byte ptr [rbp-0x231], 0
	jz	$_766
	mov	rcx, rbx
	call	MemFree@PLT
$_766:	xor	eax, eax
	jmp	$_866

$_767:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp-0x4], eax
	jnz	$_768
	sub	rsi, 24
$_768:	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

	jmp	$_770

$_769:	cmp	dword ptr [rbp+rdi-0x1F4], 3
	je	$_747
	cmp	dword ptr [rbp+rdi-0x1F4], -2
	je	$_760
	cmp	dword ptr [rbp+rdi-0x1F4], -1
	jz	$_768
$_770:	inc	dword ptr [rbp-0x8]
	jmp	$_741

$_771:	cmp	byte ptr [rsi], 0
	jz	$_772
	mov	rdx, qword ptr [rsi+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_772:	cmp	dword ptr [rbp-0x8], 3
	jl	$_773
	or	byte ptr [rbp-0x83], 0x08
$_773:	mov	dword ptr [rbp-0xC], 0
	xor	ebx, ebx
$_774:	cmp	ebx, dword ptr [rbp-0x8]
	jge	$_815
	cmp	ebx, 3
	jnc	$_815
	mov	byte ptr [Frame_Type+rip], 6
	mov	qword ptr [SegOverride+rip], 0
	imul	edx, ebx, 104
	movzx	eax, word ptr [rbp-0x82]
	mov	ecx, dword ptr [rbp-0x80]
	cmp	eax, 1301
	jc	$_802
	cmp	ebx, 1
	jne	$_802
	test	ecx, 0x507F7C
	je	$_802
	lea	rdi, [vex_flags+rip]
	movzx	edi, byte ptr [rdi+rax-0x515]
	cmp	eax, 1582
	jc	$_775
	cmp	eax, 1590
	jbe	$_776
$_775:	test	ecx, 0xC
	jz	$_776
	jmp	$_802

$_776:	test	edi, 0x2
	jz	$_777
	jmp	$_802

$_777:	test	edi, 0x8
	jz	$_778
	cmp	dword ptr [rbp-0x124], 0
	jnz	$_778
	cmp	dword ptr [rbp-0x8], 2
	jle	$_778
	jmp	$_802

$_778:	test	edi, 0x20
	jz	$_779
	test	ecx, 0x70
	jz	$_779
	test	byte ptr [rbp+rdx-0x1ED], 0x01
	jz	$_779
	mov	byte ptr [rbp-0x2F], 0
	jmp	$_802

$_779:	test	edi, 0x10
	jz	$_782
	test	ecx, 0x401F00
	jnz	$_781
	cmp	eax, 1405
	jz	$_780
	cmp	eax, 1406
	jnz	$_782
$_780:	cmp	dword ptr [rbp-0x18C], 2
	jnz	$_781
	test	byte ptr [rbp-0x185], 0x01
	jz	$_782
$_781:	jmp	$_802

$_782:	cmp	dword ptr [rbp-0x18C], 2
	jz	$_783
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_866

$_783:	mov	rax, qword ptr [rbp+rdx-0x218]
	mov	eax, dword ptr [rax+0x4]
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	test	dword ptr [r11+rax], 0x10007C
	jnz	$_784
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_866

$_784:	cmp	dword ptr [rbp-0x8], 2
	jg	$_786
	movzx	eax, word ptr [rbp-0x82]
	lea	rcx, [ResWordTable+rip]
	imul	eax, eax, 16
	test	byte ptr [rcx+rax+0x3], 0x10
	jz	$_785
	inc	dword ptr [rbp-0x8]
$_785:	jmp	$_801

$_786:	test	edi, 0x4
	je	$_791
	cmp	dword ptr [rbp-0x124], 0
	jne	$_791
	cmp	qword ptr [rbp-0x218], 0
	je	$_790
	mov	rcx, qword ptr [rbp+rdx-0x218]
	mov	eax, dword ptr [rcx+0x4]
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	eax, dword ptr [r11+rax]
	mov	rcx, qword ptr [rbp-0x218]
	mov	cl, byte ptr [rcx+0x1]
	inc	cl
	mov	byte ptr [rbp-0x2B], cl
	test	eax, 0x40
	jz	$_787
	or	byte ptr [rbp-0x2B], 0xFFFFFF80
	jmp	$_788

$_787:	test	eax, 0x20
	jz	$_788
	or	byte ptr [rbp-0x2B], 0x40
$_788:	lea	rdi, [rbp-0x230]
	lea	rax, [rbp+rdx-0x230]
	xchg	rax, rsi
	mov	ecx, 312
	rep movsb
	mov	rsi, rax
	mov	byte ptr [rbp-0x2F], 0
	mov	r9d, dword ptr [rbp-0xC]
	lea	r8, [rbp-0x230]
	xor	edx, edx
	lea	rcx, [rbp-0x90]
	call	$_439
	cmp	eax, -1
	jnz	$_789
	jmp	$_866

$_789:	inc	dword ptr [rbp-0xC]
$_790:	jmp	$_801

$_791:	mov	rcx, qword ptr [rbp+rdx-0x218]
	mov	eax, dword ptr [rcx+0x4]
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	eax, dword ptr [r11+rax]
	cmp	dword ptr [rbp-0x80], 4202240
	jnz	$_792
	jmp	$_795

$_792:	test	eax, 0x1010
	jz	$_793
	test	dword ptr [rbp-0x80], 0x2020
	jnz	$_794
$_793:	test	eax, 0x2020
	jz	$_795
	test	dword ptr [rbp-0x80], 0x1010
	jz	$_795
$_794:	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_866

$_795:	mov	edi, eax
	mov	al, byte ptr [rcx+0x1]
	inc	al
	mov	byte ptr [rbp-0x2B], al
	cmp	byte ptr [rbp-0x2B], 16
	ja	$_796
	test	edi, 0x40
	jz	$_799
$_796:	mov	byte ptr [rbp-0x85], 1
	cmp	byte ptr [rbp-0x2B], 16
	jbe	$_797
	or	byte ptr [rbp-0x83], 0x02
$_797:	test	edi, 0x40
	jz	$_798
	or	byte ptr [rbp-0x2B], 0xFFFFFF80
	or	byte ptr [rbp-0x83], 0x10
$_798:	jmp	$_800

$_799:	test	edi, 0x20
	jz	$_800
	or	byte ptr [rbp-0x2B], 0x40
$_800:	inc	dword ptr [rbp-0xC]
	lea	rdi, [rbp+rdx-0x230]
	lea	rax, [rbp+rdx-0x1C8]
	xchg	rax, rsi
	mov	ecx, 208
	rep movsb
	mov	rsi, rax
$_801:	dec	dword ptr [rbp-0x8]
$_802:	imul	edx, ebx, 104
	jmp	$_813

$_803:	lea	r8, [rbp+rdx-0x230]
	mov	edx, ebx
	lea	rcx, [rbp-0x90]
	call	$_399
	cmp	eax, -1
	jnz	$_804
	jmp	$_866

$_804:	jmp	$_814

$_805:	lea	r8, [rbp+rdx-0x230]
	mov	edx, ebx
	lea	rcx, [rbp-0x90]
	call	$_434
	cmp	eax, -1
	jnz	$_806
	jmp	$_866

$_806:	jmp	$_814

$_807:	test	byte ptr [rbp+rdx-0x1ED], 0x01
	jz	$_809
	lea	r8, [rbp+rdx-0x230]
	mov	edx, ebx
	lea	rcx, [rbp-0x90]
	call	$_399
	cmp	eax, -1
	jnz	$_808
	jmp	$_866

$_808:	jmp	$_812

$_809:	cmp	ebx, 2
	jnz	$_811
	mov	rcx, qword ptr [rbp+rdx-0x218]
	mov	eax, dword ptr [rcx+0x4]
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	eax, dword ptr [r11+rax]
	mov	dword ptr [rbp-0x50], eax
	movzx	eax, byte ptr [rcx+0x1]
	mov	dword ptr [rbp-0x40], eax
	mov	rcx, qword ptr [rbp-0x38]
	test	byte ptr [rcx+0x3], 0x08
	jz	$_810
	mov	cl, byte ptr [rbp-0x2C]
	and	cl, 0xFFFFFFF0
	or	al, cl
	mov	byte ptr [rbp-0x2C], al
$_810:	jmp	$_812

$_811:	mov	r9d, dword ptr [rbp-0xC]
	lea	r8, [rbp-0x230]
	mov	edx, ebx
	lea	rcx, [rbp-0x90]
	call	$_439
	cmp	eax, -1
	jnz	$_812
	jmp	$_866

$_812:	jmp	$_814

$_813:	cmp	dword ptr [rbp+rdx-0x1F4], 1
	je	$_803
	cmp	dword ptr [rbp+rdx-0x1F4], 0
	je	$_805
	cmp	dword ptr [rbp+rdx-0x1F4], 2
	je	$_807
$_814:	inc	ebx
	inc	dword ptr [rbp-0xC]
	jmp	$_774

$_815:	cmp	ebx, 2
	jne	$_823
	cmp	dword ptr [rbp-0x1F4], 2
	jnz	$_816
	cmp	dword ptr [rbp-0x18C], 1
	jz	$_817
$_816:	cmp	dword ptr [rbp-0x1F4], 1
	jne	$_823
	cmp	dword ptr [rbp-0x18C], 1
	je	$_823
$_817:	mov	ecx, 1
	lea	rdi, [rbp-0x230]
	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_818
	add	rdi, 104
	dec	ecx
$_818:	mov	rbx, qword ptr [rdi+0x18]
	mov	rax, qword ptr [rdi+0x50]
	mov	rdx, qword ptr [rdi+0x58]
	test	rbx, rbx
	jz	$_822
	test	rax, rax
	jz	$_822
	test	rdx, rdx
	jz	$_822
	test	byte ptr [rdi+0x43], 0xFFFFFF80
	jz	$_822
	mov	rdx, qword ptr [rax+0x40]
	test	rdx, rdx
	jz	$_822
	cmp	byte ptr [rax+0x19], -61
	jnz	$_822
	cmp	byte ptr [rax+0x39], 0
	jz	$_822
	cmp	byte ptr [rdx+0x18], 7
	jnz	$_822
	cmp	byte ptr [rbx], 8
	jnz	$_822
	cmp	byte ptr [rbx+0x18], 46
	jz	$_819
	cmp	byte ptr [rbx+0x18], 91
	jnz	$_822
$_819:	test	ecx, ecx
	jnz	$_820
	cmp	byte ptr [rbx-0x48], 1
	jnz	$_820
	cmp	byte ptr [rbx-0x30], 2
	jnz	$_820
	cmp	byte ptr [rbx-0x18], 44
	jz	$_821
$_820:	test	ecx, ecx
	jz	$_822
	cmp	byte ptr [rbx-0x18], 1
	jnz	$_822
$_821:	mov	r8d, ecx
	mov	rdx, rbx
	mov	rcx, rax
	call	HandleIndirection@PLT
	jmp	$_866

$_822:	mov	ebx, 2
$_823:	cmp	ebx, dword ptr [rbp-0x8]
	jz	$_826
$_824:	cmp	byte ptr [rsi], 44
	jz	$_825
	dec	dword ptr [rbp-0x4]
	sub	rsi, 24
	jmp	$_824

$_825:	mov	rdx, qword ptr [rsi+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_826:	test	byte ptr [rbp-0x2A], 0x04
	jz	$_828
	cmp	word ptr [rbp-0x82], 531
	jz	$_827
	cmp	word ptr [rbp-0x82], 532
	jnz	$_828
$_827:	add	qword ptr [rbp-0x38], 8
	mov	rdx, qword ptr [rbp-0x38]
	test	byte ptr [rdx+0x2], 0x08
	jz	$_827
$_828:	mov	rdx, qword ptr [rbp-0x38]
	mov	al, byte ptr [rdx+0x2]
	and	eax, 0x07
	cmp	eax, 2
	jz	$_829
	cmp	eax, 3
	jnz	$_831
$_829:	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jnz	$_830
	cmp	word ptr [rbp-0x82], 612
	jnz	$_830
	cmp	dword ptr [rbp-0x80], 16
	jnz	$_830
	test	dword ptr [rbp-0x68], 0x400F0000
	jz	$_830
	mov	r8d, 8
	lea	rdx, [rbp-0x1C8]
	mov	rcx, qword ptr [rbp+0x28]
	call	imm2xmm@PLT
	jmp	$_866

$_830:	lea	rdx, [rbp-0x230]
	lea	rcx, [rbp-0x90]
	call	$_482
	jmp	$_865

$_831:	cmp	ebx, 1
	jbe	$_842
	cmp	ebx, 2
	jbe	$_837
	mov	rdx, qword ptr [rbp-0x38]
$_832:	movzx	eax, byte ptr [rdx]
	imul	eax, eax, 12
	lea	rcx, [opnd_clstab+rip]
	cmp	byte ptr [rcx+rax+0x8], 0
	jnz	$_836
	add	rdx, 8
	test	byte ptr [rdx+0x2], 0x08
	jz	$_835
$_833:	cmp	byte ptr [rsi], 44
	jz	$_834
	sub	rsi, 24
	jmp	$_833

$_834:	mov	rdx, qword ptr [rsi+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_866

$_835:	jmp	$_832

$_836:	mov	qword ptr [rbp-0x38], rdx
$_837:
	cmp	word ptr [rbp-0x82], 698
	jnz	$_841
	mov	rax, qword ptr [rbp-0x60]
	test	rax, rax
	jz	$_838
	mov	rax, qword ptr [rax+0x30]
$_838:	cmp	dword ptr [rbp-0x50], 0
	jnz	$_840
	test	byte ptr [rbp-0x66], 0x07
	jz	$_840
	test	byte ptr [rbp-0x88], 0x01
	jz	$_839
	or	byte ptr [rbp-0x88], 0x04
$_839:	mov	al, byte ptr [rbp-0x2F]
	mov	dl, al
	and	al, 0xFFFFFFC7
	and	dl, 0x07
	shl	dl, 3
	or	al, dl
	mov	byte ptr [rbp-0x2F], al
	jmp	$_841

$_840:	cmp	dword ptr [rbp-0x50], 0
	jz	$_841
	test	byte ptr [rbp-0x66], 0x07
	jz	$_841
	test	rax, rax
	jz	$_841
	cmp	byte ptr [rax+0x18], 0
	jnz	$_841
	mov	dword ptr [rbp-0x68], 4202240
$_841:	lea	rdx, [rbp-0x230]
	lea	rcx, [rbp-0x90]
	call	$_528
	cmp	eax, -1
	jnz	$_842
	jmp	$_866

$_842:	cmp	byte ptr [rbp-0x2D], 2
	jne	$_854
	test	byte ptr [rbp-0x2A], 0x10
	jz	$_843
	cmp	byte ptr [rbp-0x88], 0
	jz	$_843
	mov	ecx, 3012
	call	asmerr@PLT
$_843:	movzx	eax, word ptr [rbp-0x82]
	cmp	eax, 1301
	jnc	$_844
	cmp	eax, 930
	jc	$_844
	cmp	dword ptr [rbp-0x8], 1
	jle	$_844
	cmp	dword ptr [rbp-0x18C], 0
	jnz	$_844
	mov	rdx, qword ptr [rbp-0x1B8]
	test	rdx, rdx
	jz	$_844
	cmp	byte ptr [rdx], 9
	jnz	$_844
	cmp	byte ptr [rdx+0x1], 123
	jnz	$_844
	mov	eax, 1030
$_844:	mov	ecx, 4
	jmp	$_853

$_845:	and	byte ptr [rbp-0x88], 0x07
	jmp	$_854

$_846:	and	byte ptr [rbp-0x88], 0x07
	jmp	$_854

$_847:	add	ecx, 8
$_848:	add	ecx, 4
$_849:	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jne	$_854
	cmp	dword ptr [rbp-0x80], 16
	jne	$_854
	test	dword ptr [rbp-0x68], 0x400F0000
	je	$_854
	mov	r8d, ecx
	lea	rdx, [rbp-0x1C8]
	mov	rcx, qword ptr [rbp+0x28]
	call	imm2xmm@PLT
	jmp	$_866

$_850:	test	byte ptr [rbp-0x7D], 0x02
	jnz	$_851
	test	byte ptr [rbp-0x65], 0x02
	jz	$_852
$_851:	and	byte ptr [rbp-0x88], 0x07
$_852:	jmp	$_854

$_853:	cmp	eax, 677
	jz	$_845
	cmp	eax, 678
	jz	$_845
	cmp	eax, 531
	jz	$_846
	cmp	eax, 532
	je	$_846
	cmp	eax, 1297
	je	$_846
	cmp	eax, 1298
	je	$_846
	cmp	eax, 1030
	je	$_847
	cmp	eax, 1028
	je	$_848
	cmp	eax, 612
	je	$_848
	cmp	eax, 932
	je	$_848
	cmp	eax, 956
	je	$_848
	cmp	eax, 948
	je	$_848
	cmp	eax, 936
	je	$_848
	cmp	eax, 999
	je	$_848
	cmp	eax, 1123
	je	$_848
	cmp	eax, 933
	je	$_849
	cmp	eax, 957
	je	$_849
	cmp	eax, 949
	je	$_849
	cmp	eax, 937
	je	$_849
	cmp	eax, 1000
	je	$_849
	cmp	eax, 1124
	je	$_849
	cmp	eax, 1027
	je	$_849
	cmp	eax, 1050
	je	$_849
	cmp	eax, 682
	je	$_850
$_854:	cmp	byte ptr [rbp-0x2D], 0
	jbe	$_865
	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jne	$_865
	movzx	eax, word ptr [rbp-0x82]
	mov	ecx, dword ptr [rbp-0x80]
	mov	edx, dword ptr [rbp-0x68]
	test	ecx, 0x607F00
	jz	$_857
	test	edx, 0x607F00
	jz	$_857
	jmp	$_856

$_855:	lea	r9, [rbp-0x230]
	mov	r8, qword ptr [rbp+0x28]
	call	mem2mem@PLT
	jmp	$_866

	jmp	$_857

$_856:	cmp	eax, 682
	jz	$_855
	cmp	eax, 588
	jz	$_855
	cmp	eax, 737
	jz	$_855
	cmp	eax, 583
	jz	$_855
	cmp	eax, 581
	jz	$_855
	cmp	eax, 584
	jz	$_855
	cmp	eax, 586
	jz	$_855
	cmp	eax, 585
	jz	$_855
	cmp	eax, 582
	jz	$_855
	cmp	eax, 587
	jz	$_855
	cmp	eax, 1000
	jz	$_855
	cmp	eax, 999
	jz	$_855
$_857:	xor	ebx, ebx
	cmp	eax, 1000
	jnz	$_858
	cmp	ecx, 1024
	jnz	$_858
	test	edx, 0x400F0000
	jz	$_858
	inc	ebx
	mov	ecx, 4
	jmp	$_864

$_858:	cmp	eax, 999
	jnz	$_859
	cmp	ecx, 2048
	jnz	$_859
	test	edx, 0x400F0000
	jz	$_859
	inc	ebx
	mov	ecx, 8
	jmp	$_864

$_859:	cmp	ecx, 16
	jne	$_864
	test	edx, 0x400F0000
	je	$_864
	mov	ecx, 4
	jmp	$_863

$_860:	add	ecx, 8
$_861:	add	ecx, 4
$_862:	inc	ebx
	jmp	$_864

$_863:	cmp	eax, 1030
	jz	$_860
	cmp	eax, 1028
	jz	$_861
	cmp	eax, 612
	jz	$_861
	cmp	eax, 932
	jz	$_861
	cmp	eax, 956
	jz	$_861
	cmp	eax, 948
	jz	$_861
	cmp	eax, 936
	jz	$_861
	cmp	eax, 999
	jz	$_861
	cmp	eax, 1123
	jz	$_861
	cmp	eax, 933
	jz	$_862
	cmp	eax, 957
	jz	$_862
	cmp	eax, 949
	jz	$_862
	cmp	eax, 937
	jz	$_862
	cmp	eax, 1000
	jz	$_862
	cmp	eax, 1124
	jz	$_862
	cmp	eax, 1027
	jz	$_862
	cmp	eax, 1050
	jz	$_862
$_864:	test	ebx, ebx
	jz	$_865
	mov	r8d, ecx
	lea	rdx, [rbp-0x1C8]
	mov	rcx, qword ptr [rbp+0x28]
	call	imm2xmm@PLT
	jmp	$_866

$_865:	mov	edx, dword ptr [rbp-0x24]
	lea	rcx, [rbp-0x90]
	call	codegen@PLT
$_866:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ProcessFile:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	GetTextLine@PLT
	cmp	byte ptr [ModuleInfo+0x1E0+rip], 0
	jnz	$_869
	test	rax, rax
	jz	$_869
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	mov	eax, dword ptr [rcx]
	and	eax, 0xFFFFFF
	cmp	eax, 12565487
	jnz	$_867
	lea	rax, [rcx+0x3]
	mov	rdx, rax
	call	tstrcpy@PLT
$_867:	mov	rcx, qword ptr [ModuleInfo+0x180+rip]
	call	PreprocessLine@PLT
	test	rax, rax
	jz	$_868
	mov	rcx, qword ptr [ModuleInfo+0x180+rip]
	call	ParseLine
	cmp	byte ptr [Options+0x96+rip], 1
	jnz	$_868
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_868
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	WritePreprocessedLine@PLT
$_868:	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	GetTextLine@PLT
	cmp	byte ptr [ModuleInfo+0x1E0+rip], 0
	jnz	$_869
	test	rax, rax
	jnz	$_867
$_869:	leave
	ret


.SECTION .data
	.ALIGN	16

SegOverride:
	.quad  0x0000000000000000

LastRegOverride:
	.int   0x00000000

DS0000:
	.byte  0x50, 0x4F, 0x50, 0x20, 0x43, 0x53, 0x00

DS0001:
	.byte  0x42, 0x59, 0x54, 0x45, 0x00

DS0002:
	.byte  0x57, 0x4F, 0x52, 0x44, 0x00

DS0003:
	.byte  0x44, 0x57, 0x4F, 0x52, 0x44, 0x00

DS0004:
	.byte  0x3A, 0x00

DS0005:
	.byte  0x65, 0x76, 0x65, 0x78, 0x00


.SECTION .bss
	.ALIGN	16

SymTables:
	.zero	96 * 1


.att_syntax prefix
