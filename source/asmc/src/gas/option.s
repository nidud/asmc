
.intel_syntax noprefix

.global OptionDirective

.extern UpdateProcStatus
.extern UpdateStackBase
.extern InputExtend
.extern CreateVariable
.extern EmitConstError
.extern EvalOperand
.extern RenameKeyword
.extern DisableKeyword
.extern IsKeywordDisabled
.extern FindResWord
.extern GetLangType
.extern SpecialTable
.extern LclDup
.extern LclAlloc
.extern tstricmp
.extern tstrcmp
.extern tstrcpy
.extern tstrlen
.extern tstrupr
.extern SetMasm510
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern StringBuffer
.extern SymSetCmpFunc


.SECTION .text
	.ALIGN	16

$_001:	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	movzx	eax, byte ptr [ModuleInfo+0x1CC+rip]
	lea	rdx, [ModuleInfo+rip]
	mov	dword ptr [rdx+rax*4+0x224], ecx
	cmp	qword ptr [ModuleInfo+0x148+rip], 0
	jnz	$_002
	xor	edx, edx
	lea	rcx, [DS0032+rip]
	call	CreateVariable@PLT
	mov	qword ptr [ModuleInfo+0x148+rip], rax
	mov	rcx, rax
	or	byte ptr [rcx+0x14], 0x20
	lea	rax, [UpdateStackBase@PLT+rip]
	mov	qword ptr [rcx+0x58], rax
	xor	edx, edx
	lea	rcx, [DS0033+rip]
	call	CreateVariable@PLT
	mov	qword ptr [ModuleInfo+0x150+rip], rax
	mov	rcx, rax
	mov	dword ptr [rcx+0x14], 32
	lea	rax, [UpdateProcStatus@PLT+rip]
	mov	qword ptr [rcx+0x58], rax
$_002:	leave
	ret

$_003:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 160
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_004
	jmp	$_011

$_004:	cmp	dword ptr [rbp-0x2C], 0
	jz	$_005
	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_011

$_005:	mov	eax, dword ptr [rbp+0x20]
	cmp	dword ptr [rbp-0x68], eax
	jle	$_006
	mov	ecx, 2064
	call	asmerr@PLT
	jmp	$_011

$_006:	cmp	dword ptr [rbp-0x68], 0
	jz	$_010
	xor	eax, eax
	mov	ecx, 1
$_007:	cmp	ecx, dword ptr [rbp-0x68]
	jnc	$_008
	shl	ecx, 1
	inc	eax
	jmp	$_007

$_008:	cmp	ecx, dword ptr [rbp-0x68]
	jz	$_009
	mov	edx, dword ptr [rbp-0x68]
	mov	ecx, 2063
	call	asmerr@PLT
	jmp	$_011

$_009:	mov	rdx, qword ptr [rbp+0x28]
	mov	byte ptr [rdx], al
$_010:	xor	eax, eax
$_011:	leave
	ret

OptionDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 232
	mov	dword ptr [rbp-0x6C], -1
	inc	dword ptr [rbp+0x28]
	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	jmp	$_173

$_012:	mov	rsi, qword ptr [rbx+0x8]
	mov	rcx, rsi
	call	tstrupr@PLT
	xor	edi, edi
$_013:	cmp	edi, 50
	jnc	$_014
	lea	rdx, [optiontab+rip]
	mov	rdx, qword ptr [rdx+rdi*8]
	mov	rcx, rsi
	call	tstrcmp@PLT
	test	eax, eax
	jz	$_014
	inc	edi
	jmp	$_013

$_014:	cmp	edi, 50
	jnc	$_174
	mov	dword ptr [rbp-0x6C], edi
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	edi, 19
	jc	$_017
	cmp	byte ptr [rbx], 58
	jz	$_015
	lea	rdx, [DS0033+0xB+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_177

$_015:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 0
	jnz	$_016
	sub	rbx, 48
	jmp	$_174

$_016:	cmp	edi, 29
	jc	$_017
	cmp	byte ptr [Options+0xC6+rip], 0
	jz	$_017
	sub	rbx, 48
	jmp	$_174

$_017:	mov	rsi, qword ptr [rbx+0x8]
	jmp	$_172
$C0017: mov	byte ptr [ModuleInfo+0x1D4+rip], 1
	jmp	$C0018
$C0019: mov	byte ptr [ModuleInfo+0x1D4+rip], 0
	jmp	$C0018
$C001A: mov	ecx, 1
	call	SetMasm510@PLT
	jmp	$C0018
$C001B: xor	ecx, ecx
	call	SetMasm510@PLT
	jmp	$C0018
$C001C: mov	byte ptr [ModuleInfo+0x1D7+rip], 1
	jmp	$C0018
$C001D: mov	byte ptr [ModuleInfo+0x1D7+rip], 0
	jmp	$C0018
$C001E: mov	byte ptr [ModuleInfo+0x1D8+rip], 1
	jmp	$C0018
$C001F: mov	byte ptr [ModuleInfo+0x1D8+rip], 0
	jmp	$C0018
$C0020: mov	byte ptr [ModuleInfo+0x1D9+rip], 1
	jmp	$C0018
$C0021: mov	byte ptr [ModuleInfo+0x1D9+rip], 0
	jmp	$C0018
$C0022: mov	byte ptr [ModuleInfo+0x1D5+rip], 1
	jmp	$C0018
$C0023: mov	byte ptr [ModuleInfo+0x1D5+rip], 0
$C0024:
$C0025:
$C0026:
$C0027:
$C0028:
$C0029: jmp	$C0018
$C002A: mov	byte ptr [ModuleInfo+0x1E2+rip], 1
	jmp	$C0018
$C002B: cmp	byte ptr [rbx], 8
	jne	$_174
	lea	rdx, [DS0034+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_018
	mov	byte ptr [ModuleInfo+0x1D0+rip], 1
	mov	byte ptr [ModuleInfo+0x1D1+rip], 0
	jmp	$_021
$_018:	lea	rdx, [DS0035+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_019
	mov	byte ptr [ModuleInfo+0x1D0+rip], 0
	mov	byte ptr [ModuleInfo+0x1D1+rip], 0
	jmp	$_021
$_019:	lea	rdx, [DS0036+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_020
	mov	byte ptr [ModuleInfo+0x1D0+rip], 0
	mov	byte ptr [ModuleInfo+0x1D1+rip], 1
	jmp	$_021
$_020:	jmp	$_174
$_021:	inc	dword ptr [rbp+0x28]
	call	SymSetCmpFunc@PLT
	jmp	$C0018
$C0030:
	jmp	$_027

$_022:	lea	rdx, [DS0037+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_023
	mov	byte ptr [ModuleInfo+0x1D2+rip], 1
	mov	byte ptr [ModuleInfo+0x1D3+rip], 0
	inc	dword ptr [rbp+0x28]
	jmp	$_024

$_023:	lea	rdx, [DS0038+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_024
	mov	byte ptr [ModuleInfo+0x1D2+rip], 0
	mov	byte ptr [ModuleInfo+0x1D3+rip], 1
	inc	dword ptr [rbp+0x28]
$_024:	jmp	$_028

$_025:	cmp	dword ptr [rbx+0x4], 506
	jnz	$_026
	mov	byte ptr [ModuleInfo+0x1D2+rip], 0
	mov	byte ptr [ModuleInfo+0x1D3+rip], 0
	inc	dword ptr [rbp+0x28]
$_026:	jmp	$_028

$_027:	cmp	byte ptr [rbx], 8
	jz	$_022
	cmp	byte ptr [rbx], 3
	jz	$_025
$_028:	jmp	$C0018
$C0039:
	cmp	byte ptr [rbx], 8
	jz	$_029
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_177
$_029:	cmp	qword ptr [ModuleInfo+0x190+rip], 0
	jz	$_030
	mov	qword ptr [ModuleInfo+0x190+rip], 0
$_030:	lea	rdx, [DS0034+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_031
	mov	byte ptr [ModuleInfo+0x1EF+rip], 2
	jmp	$_033
$_031:	lea	rdx, [DS0039+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_032
	mov	byte ptr [ModuleInfo+0x1EF+rip], 0
	jmp	$_033
$_032:	mov	byte ptr [ModuleInfo+0x1EF+rip], 1
	mov	rcx, rsi
	call	LclDup@PLT
	mov	qword ptr [ModuleInfo+0x190+rip], rax
$_033:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C003F:
	cmp	byte ptr [rbx], 8
	jz	$_034
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_177
$_034:	mov	qword ptr [ModuleInfo+0x198+rip], 0
	lea	rdx, [DS0034+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_035
	mov	byte ptr [ModuleInfo+0x1F0+rip], 2
	jmp	$_037
$_035:	lea	rdx, [DS003A+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_036
	mov	byte ptr [ModuleInfo+0x1F0+rip], 0
	jmp	$_037
$_036:	mov	byte ptr [ModuleInfo+0x1F0+rip], 1
	mov	rcx, rsi
	call	LclDup@PLT
	mov	qword ptr [ModuleInfo+0x198+rip], rax
$_037:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C0044:
	cmp	byte ptr [rbx], 8
	jnz	$_038
	mov	eax, dword ptr [rsi]
	or	al, 0x20
	cmp	ax, 99
	jnz	$_038
	mov	byte ptr [rbx], 7
	mov	dword ptr [rbx+0x4], 277
	mov	byte ptr [rbx+0x1], 1
$_038:	cmp	byte ptr [rbx], 7
	jnz	$_039
	lea	r8, [ModuleInfo+0x1B6+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetLangType@PLT
	test	eax, eax
	jnz	$_039
	jmp	$C0018
$_039:	jmp	$_174
$C0049:
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_043
	jmp	$_041
$_040:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_041:	cmp	byte ptr [rbx], 0
	jz	$_042
	cmp	byte ptr [rbx], 44
	jnz	$_040
$_042:	jmp	$C0018
$_043:	cmp	byte ptr [rbx], 9
	jne	$_174
	cmp	byte ptr [rbx+0x1], 60
	jne	$_174
$_044:	cmp	byte ptr [rsi], 0
	je	$_054
	jmp	$_046
$_045:	inc	rsi
$_046:	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x08
	jnz	$_045
	cmp	byte ptr [rsi], 0
	jz	$_050
	mov	rdi, rsi
$_047:	cmp	byte ptr [rsi], 0
	jz	$_048
	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x08
	jnz	$_048
	cmp	byte ptr [rsi], 44
	jz	$_048
	inc	rsi
	jmp	$_047
$_048:	mov	rcx, rsi
	sub	rcx, rdi
	mov	edx, ecx
	mov	rcx, rdi
	call	FindResWord@PLT
	test	rax, rax
	jz	$_049
	mov	ecx, eax
	call	DisableKeyword@PLT
	jmp	$_050
$_049:	mov	rcx, rsi
	sub	rcx, rdi
	mov	edx, ecx
	mov	rcx, rdi
	call	IsKeywordDisabled@PLT
	test	rax, rax
	jz	$_050
	mov	ecx, 2086
	call	asmerr@PLT
	jmp	$_177
$_050:	jmp	$_052
$_051:	inc	rsi
$_052:	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x08
	jnz	$_051
	cmp	byte ptr [rsi], 44
	jnz	$_053
	inc	rsi
$_053:	jmp	$_044
$_054:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C005E:
	lea	rdx, [DS003B+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_055
	mov	byte ptr [ModuleInfo+0x1DA+rip], 1
	inc	dword ptr [rbp+0x28]
	jmp	$_056
$_055:	lea	rdx, [DS003C+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_056
	mov	byte ptr [ModuleInfo+0x1DA+rip], 0
	inc	dword ptr [rbp+0x28]
$_056:	jmp	$C0018
$C0062:
	lea	rdx, [DS003D+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_057
	mov	byte ptr [ModuleInfo+0x1BB+rip], 0
	jmp	$_060
$_057:	lea	rdx, [DS003E+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_058
	mov	byte ptr [ModuleInfo+0x1BB+rip], 1
	jmp	$_060
$_058:	lea	rdx, [DS001B+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_059
	mov	byte ptr [ModuleInfo+0x1BB+rip], 2
	jmp	$_060
$_059:	jmp	$_174
$_060:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C0067:
	cmp	byte ptr [rbx], 7
	jnz	$_063
	cmp	dword ptr [rbx+0x4], 274
	jnz	$_063
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 112
	jc	$_061
	mov	byte ptr [ModuleInfo+0x1CD+rip], 2
	jmp	$_062
$_061:	mov	byte ptr [ModuleInfo+0x1CD+rip], 1
$_062:	jmp	$_069
$_063:	cmp	byte ptr [rbx], 8
	jnz	$_068
	lea	rdx, [DS003F+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_064
	mov	byte ptr [ModuleInfo+0x1CD+rip], 0
	jmp	$_067
$_064:	lea	rdx, [DS0040+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_065
	mov	byte ptr [ModuleInfo+0x1CD+rip], 1
	jmp	$_067
$_065:	lea	rdx, [DS0041+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_066
	mov	byte ptr [ModuleInfo+0x1CD+rip], 2
	jmp	$_067
$_066:	jmp	$_174
$_067:	jmp	$_069
$_068:	jmp	$_174
$_069:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C0071:
	lea	rdx, [DS0042+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_070
	mov	byte ptr [ModuleInfo+0x356+rip], 0
	jmp	$_075
$_070:	lea	rdx, [DS0043+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_071
	mov	byte ptr [ModuleInfo+0x356+rip], 1
	jmp	$_075
$_071:	lea	rdx, [DS0044+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_072
	mov	byte ptr [ModuleInfo+0x356+rip], 2
	jmp	$_075
$_072:	lea	rdx, [DS0045+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_073
	mov	byte ptr [ModuleInfo+0x356+rip], 4
	jmp	$_075
$_073:	lea	rdx, [DS0046+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_074
	mov	byte ptr [ModuleInfo+0x356+rip], 8
	jmp	$_075
$_074:	jmp	$_174
$_075:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C0078:
	lea	r9, [ModuleInfo+0x1C5+rip]
	mov	r8d, 32
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_003
	cmp	eax, -1
	je	$_177
	jmp	$C0018
$C0079:
	lea	r9, [ModuleInfo+0x1C7+rip]
	mov	r8d, 32
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_003
	cmp	eax, -1
	je	$_177
	jmp	$C0018
$C007A:
	mov	dword ptr [rbp-0xAC], 0
	lea	rdi, [ModuleInfo+0x1E4+rip]
$_076:	cmp	dword ptr [rbp-0xAC], 4
	jge	$_086
	mov	ecx, dword ptr [rbp+0x28]
	mov	rdx, rbx
$_077:	cmp	byte ptr [rdx], 0
	jz	$_078
	cmp	byte ptr [rdx], 44
	jz	$_078
	cmp	byte ptr [rdx], 58
	jz	$_078
	cmp	byte ptr [rdx], 13
	jz	$_078
	inc	ecx
	add	rdx, 24
	jmp	$_077

$_078:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_177
	mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	dword ptr [rbp-0x2C], -2
	jnz	$_079
	jmp	$_083

$_079:	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_082
	cmp	dword ptr [rbp-0x68], 65535
	jle	$_080
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_177

$_080:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 1
	jnz	$_081
	mov	eax, dword ptr [rbp-0x68]
	mov	ecx, dword ptr [rbp-0xAC]
	mov	word ptr [rdi+rcx*2], ax
$_081:	jmp	$_083

$_082:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177

$_083:	cmp	byte ptr [rbx], 58
	jnz	$_084
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_085

$_084:	cmp	byte ptr [rbx], 13
	jnz	$_085
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	inc	dword ptr [rbp-0xAC]
$_085:	inc	dword ptr [rbp-0xAC]
	jmp	$_076

$_086:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 1
	jnz	$_091
	cmp	word ptr [ModuleInfo+0x1E4+rip], 30
	jnc	$_087
	mov	word ptr [ModuleInfo+0x1E4+rip], 30
$_087:	mov	ecx, 16
$_088:	cmp	cx, word ptr [ModuleInfo+0x1E6+rip]
	jnc	$_089
	shl	ecx, 1
	jmp	$_088

$_089:	cmp	cx, word ptr [ModuleInfo+0x1E6+rip]
	jz	$_090
	mov	edx, ecx
	mov	ecx, 2189
	call	asmerr@PLT
$_090:	mov	ax, word ptr [ModuleInfo+0x1E8+rip]
	cmp	word ptr [ModuleInfo+0x1EA+rip], ax
	jnc	$_091
	mov	word ptr [ModuleInfo+0x1EA+rip], ax
$_091:	jmp	$C0018
$C0090:
	lea	rdx, [DS0047+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_092
	or	byte ptr [ModuleInfo+0x1E1+rip], 0x01
	jmp	$_095
$_092:	cmp	dword ptr [rbx+0x4], 581
	jnz	$_093
	mov	byte ptr [ModuleInfo+0x1E1+rip], 3
	jmp	$_095
$_093:	lea	rdx, [DS0048+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_094
	mov	byte ptr [ModuleInfo+0x1E1+rip], 0
	jmp	$_095
$_094:	jmp	$_174
$_095:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C0095:
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_177
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_098
	cmp	dword ptr [rbp-0x68], 255
	jle	$_096
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_177
$_096:	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_097
	mov	eax, dword ptr [rbp-0x68]
	mov	byte ptr [ModuleInfo+0x1E4+rip], al
$_097:	jmp	$_099
$_098:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177
$_099:	jmp	$C0018
$C009A:
	cmp	byte ptr [rbx], 9
	jne	$_174
	cmp	byte ptr [rbx+0x1], 60
	jne	$_174
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 3
	jne	$_174
	cmp	byte ptr [rbx+0x1], 45
	jne	$_174
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 8
	jne	$_174
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	edx, eax
	mov	rcx, rsi
	call	FindResWord@PLT
	mov	esi, eax
	test	esi, esi
	jnz	$_100
	mov	ecx, 2086
	call	asmerr@PLT
	jmp	$_177
$_100:	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	movzx	r8d, al
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, esi
	call	RenameKeyword@PLT
	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C009C:
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jz	$_104
	jmp	$_102
$_101:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_102:	cmp	byte ptr [rbx], 0
	jz	$_103
	cmp	byte ptr [rbx], 44
	jnz	$_101
$_103:	jmp	$C0018
$_104:	cmp	byte ptr [rbx], 10
	jnz	$_107
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_177
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_106
	test	dword ptr [rbp-0x68], 0xFFFFFFF8
	jz	$_105
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_177
$_105:	mov	eax, dword ptr [rbp-0x68]
	mov	byte ptr [ModuleInfo+0x1E5+rip], al
$_106:	jmp	$_122
$_107:	jmp	$_121
$_108:	cmp	byte ptr [rbx], 58
	je	$_120
	cmp	byte ptr [rbx], 44
	je	$_120
	mov	rsi, qword ptr [rbx+0x8]
	mov	edi, dword ptr [rbx+0x4]
	cmp	edi, 119
	jnz	$_109
	mov	ecx, 119
	call	$_001
	or	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jmp	$_120
$_109:	cmp	edi, 120
	jnz	$_110
	mov	ecx, 120
	call	$_001
	or	byte ptr [ModuleInfo+0x1E1+rip], 0x01
	or	byte ptr [ModuleInfo+0x1E5+rip], 0x03
	jmp	$_120
$_110:	cmp	edi, 514
	jnz	$_112
	cmp	byte ptr [ModuleInfo+0x1E5+rip], 0
	jnz	$_111
	or	byte ptr [ModuleInfo+0x1E5+rip], 0x02
$_111:	or	byte ptr [ModuleInfo+0x1E5+rip], 0x04
	jmp	$_120
$_112:	lea	rdx, [DS0049+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_113
	and	byte ptr [ModuleInfo+0x1E5+rip], 0xFFFFFFFB
	jmp	$_120
$_113:	lea	rdx, [DS004A+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_114
	or	byte ptr [ModuleInfo+0x1E5+rip], 0x01
	jmp	$_120
$_114:	lea	rdx, [DS004B+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_115
	and	byte ptr [ModuleInfo+0x1E5+rip], 0xFFFFFFFE
	jmp	$_120
$_115:	lea	rdx, [DS0048+0x2+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_116
	or	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jmp	$_120
$_116:	lea	rdx, [DS0048+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_117
	and	byte ptr [ModuleInfo+0x1E5+rip], 0xFFFFFFFD
	jmp	$_120
$_117:	cmp	edi, 276
	jnz	$_118
	mov	byte ptr [ModuleInfo+0x1E1+rip], 3
	jmp	$_120
$_118:	lea	rdx, [DS004C+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_119
	mov	byte ptr [ModuleInfo+0x1E1+rip], 0
	jmp	$_120
$_119:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177
$_120:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_121:	cmp	byte ptr [rbx], 0
	jne	$_108
$_122:	jmp	$C0018
$C00B5:
	cmp	byte ptr [rbx], 8
	jnz	$_124
	lea	rdx, [DS0034+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_123
	mov	qword ptr [ModuleInfo+0x1A0+rip], 0
$_123:	jmp	$_131
$_124:	cmp	byte ptr [rbx], 9
	jne	$_131
	cmp	byte ptr [rbx+0x1], 60
	jne	$_131
	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_131
	cmp	byte ptr [rsi], 0
	jnz	$_125
	xor	esi, esi
	jmp	$_130
$_125:	lea	rdi, [ModuleInfo+0x60+rip]
$_126:	cmp	qword ptr [rdi], 0
	jz	$_128
	mov	rcx, qword ptr [rdi]
	mov	rdx, rsi
	lea	rcx, [rcx+0xC]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_127
	mov	rsi, qword ptr [rdi]
	jmp	$_130
$_127:	mov	rdi, qword ptr [rdi]
	jmp	$_126
$_128:	mov	rcx, rsi
	call	tstrlen@PLT
	add	rax, 16
	mov	ecx, eax
	call	LclAlloc@PLT
	mov	qword ptr [rdi], rax
	mov	rdi, rax
	mov	qword ptr [rdi], 0
	mov	dword ptr [rdi+0x8], 0
	mov	rdx, rsi
	lea	rcx, [rdi+0xC]
	call	tstrcpy@PLT
	lea	rax, [DS004D+rip]
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jz	$_129
	inc	rax
$_129:	mov	qword ptr [ModuleInfo+0x68+rip], rax
	mov	rsi, rdi
$_130:	mov	qword ptr [ModuleInfo+0x1A0+rip], rsi
$_131:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C00C4:
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_177
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_132
	mov	eax, dword ptr [rbp-0x68]
	mov	byte ptr [ModuleInfo+0x1F2+rip], al
	jmp	$_133
$_132:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177
$_133:	jmp	$C0018
$C00C7:
	cmp	byte ptr [rbx], 2
	jne	$_174
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	test	dword ptr [r11+rax+0x4], 0x80
	jnz	$_134
	mov	ecx, 2031
	call	asmerr@PLT
	jmp	$_177
$_134:	mov	ecx, dword ptr [rbx+0x4]
	call	$_001
	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C00C9:
	lea	rdx, [DS004E+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_135
	or	byte ptr [ModuleInfo+0x334+rip], 0x01
	jmp	$_137
$_135:	lea	rdx, [DS004F+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_136
	and	byte ptr [ModuleInfo+0x334+rip], 0xFFFFFFFE
	jmp	$_137
$_136:	jmp	$_174
$_137:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C00CD:
	lea	rdx, [DS004E+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_138
	mov	byte ptr [ModuleInfo+0x354+rip], 1
	jmp	$_140
$_138:	lea	rdx, [DS004F+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_139
	mov	byte ptr [ModuleInfo+0x354+rip], 0
	jmp	$_140
$_139:	jmp	$_174
$_140:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C00D1:
	lea	rdx, [DS0035+0x8+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_141
	and	byte ptr [ModuleInfo+0x334+rip], 0xFFFFFFF7
	jmp	$_147
$_141:	lea	rdx, [DS0050+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_142
	or	byte ptr [ModuleInfo+0x334+rip], 0x08
	jmp	$_147
$_142:	lea	rdx, [DS0051+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_143
	and	byte ptr [ModuleInfo+0x334+rip], 0xFFFFFFEF
	jmp	$_147
$_143:	lea	rdx, [DS0052+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_144
	or	byte ptr [ModuleInfo+0x334+rip], 0x10
	jmp	$_147
$_144:	lea	rdx, [DS0053+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_145
	or	byte ptr [ModuleInfo+0x334+rip], 0x20
	jmp	$_147
$_145:	lea	rdx, [DS0054+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_146
	and	byte ptr [ModuleInfo+0x334+rip], 0xFFFFFFDF
	jmp	$_147
$_146:	jmp	$_174
$_147:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C00D9:
	lea	r9, [ModuleInfo+0x335+rip]
	mov	r8d, 16
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_003
	cmp	eax, -1
	je	$_177
	jmp	$C0018
$C00DA:
	lea	r9, [ModuleInfo+0x336+rip]
	mov	r8d, 16
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_003
	cmp	eax, -1
	je	$_177
	jmp	$C0018
$C00DB:
	lea	rdx, [DS004E+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_148
	or	byte ptr [ModuleInfo+0x334+rip], 0x02
	jmp	$_150
$_148:	lea	rdx, [DS004F+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_149
	and	byte ptr [ModuleInfo+0x334+rip], 0xFFFFFFFD
	jmp	$_150
$_149:	jmp	$_174
$_150:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C00DF:
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_177
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_152
	cmp	dword ptr [rbp-0x68], 65535
	jle	$_151
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_177
$_151:	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [ModuleInfo+0x344+rip], eax
	jmp	$_153
$_152:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177
$_153:	jmp	$C0018
$C00E3:
	lea	rdx, [DS0052+0x6+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_154
	mov	byte ptr [ModuleInfo+0x350+rip], 101
	jmp	$_158
$_154:	lea	rdx, [DS004F+0x2+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_155
	mov	byte ptr [ModuleInfo+0x350+rip], 0
	jmp	$_158
$_155:	lea	rdx, [DS002B+0x6+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_156
	mov	byte ptr [ModuleInfo+0x350+rip], 103
	jmp	$_158
$_156:	lea	rdx, [DS0053+0x4+rip]
	mov	rcx, rsi
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_157
	mov	byte ptr [ModuleInfo+0x350+rip], 120
	jmp	$_158
$_157:	jmp	$_174
$_158:	inc	dword ptr [rbp+0x28]
	jmp	$C0018
$C00E9:
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	rax, -1
	je	$_177
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_160
	cmp	dword ptr [rbp-0x68], 4
	jz	$_159
	cmp	dword ptr [rbp-0x68], 8
	jz	$_159
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_177
$_159:	mov	eax, dword ptr [rbp-0x68]
	mov	byte ptr [ModuleInfo+0x351+rip], al
	jmp	$_161
$_160:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177
$_161:	jmp	$C0018
$C00ED:
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_177
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_163
	cmp	dword ptr [rbp-0x68], 255
	jle	$_162
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_177
$_162:	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [ModuleInfo+0x34C+rip], eax
	jmp	$_164
$_163:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177
$_164:	jmp	$C0018
$C00F1:
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_177
	cmp	dword ptr [rbp-0x2C], 0
	jne	$_170
	cmp	dword ptr [rbp-0x68], 65535
	jle	$_165
	lea	rcx, [rbp-0x68]
	call	EmitConstError@PLT
	jmp	$_177
$_165:	mov	rax, qword ptr [ModuleInfo+0x178+rip]
	mov	qword ptr [rbp-0xA8], rax
	mov	qword ptr [rbp-0x98], rax
	mov	rax, qword ptr [ModuleInfo+0x180+rip]
	mov	qword ptr [rbp-0x88], rax
	mov	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x80], rax
	mov	qword ptr [rbp-0xA0], rax
	mov	dword ptr [rbp-0x90], 0
	mov	esi, dword ptr [ModuleInfo+0x174+rip]
	jmp	$_169
$_166:	lea	rcx, [rbp-0xA8]
	call	InputExtend@PLT
	test	eax, eax
	jnz	$_167
	mov	ecx, 1009
	call	asmerr@PLT
	jmp	$_177
$_167:	cmp	esi, dword ptr [ModuleInfo+0x174+rip]
	jnz	$_168
	mov	ecx, 1901
	call	asmerr@PLT
	jmp	$_177
$_168:	mov	esi, dword ptr [ModuleInfo+0x174+rip]
$_169:	cmp	esi, dword ptr [rbp-0x68]
	jl	$_166
	jmp	$_171
$_170:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_177
$_171:	jmp	$C0018
$_172:	cmp	edi, 0
	jl	$C0018
	cmp	edi, 49
	jg	$C0018
	push	rax
	lea	r11, [$C0018+rip]
	movzx	eax, word ptr [r11+rdi*2+($C00F9-$C0018)]
	sub	r11, rax
	pop	rax
	jmp	r11

	.ALIGN 2
$C00F9:
	.word $C0018-$C0017
	.word $C0018-$C0019
	.word $C0018-$C001A
	.word $C0018-$C001B
	.word $C0018-$C001C
	.word $C0018-$C001D
	.word $C0018-$C001E
	.word $C0018-$C001F
	.word $C0018-$C0020
	.word $C0018-$C0021
	.word $C0018-$C0022
	.word $C0018-$C0023
	.word $C0018-$C0024
	.word $C0018-$C0025
	.word $C0018-$C0026
	.word $C0018-$C0027
	.word $C0018-$C0028
	.word $C0018-$C0029
	.word $C0018-$C002A
	.word $C0018-$C002B
	.word $C0018-$C0030
	.word $C0018-$C0039
	.word $C0018-$C003F
	.word $C0018-$C0044
	.word $C0018-$C0049
	.word $C0018-$C005E
	.word $C0018-$C0062
	.word $C0018-$C0067
	.word $C0018-$C0071
	.word $C0018-$C0078
	.word $C0018-$C0079
	.word $C0018-$C007A
	.word $C0018-$C0090
	.word $C0018-$C0095
	.word $C0018-$C009A
	.word $C0018-$C009C
	.word $C0018-$C00B5
	.word $C0018-$C00C4
	.word $C0018-$C00C7
	.word $C0018-$C00C9
	.word $C0018-$C00D1
	.word $C0018-$C00D9
	.word $C0018-$C00DA
	.word $C0018-$C00DB
	.word $C0018-$C00DF
	.word $C0018-$C00E3
	.word $C0018-$C00ED
	.word $C0018-$C00F1
	.word $C0018-$C00E9
	.word $C0018-$C00CD

$C0018: mov	edx, dword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	edx, edx, 24
	add	rax, rdx
	mov	rbx, rax
	cmp	byte ptr [rbx], 44
	jnz	$_174
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_173:	cmp	byte ptr [rbx], 0
	jne	$_012
$_174:	cmp	dword ptr [rbp-0x6C], 50
	jge	$_175
	cmp	byte ptr [rbx], 0
	jz	$_176
$_175:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_177

$_176:	xor	eax, eax
$_177:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

optiontab:
	.quad  DS0000
	.quad  DS0001
	.quad  DS0002
	.quad  DS0003
	.quad  DS0004
	.quad  DS0005
	.quad  DS0006
	.quad  DS0007
	.quad  DS0008
	.quad  DS0009
	.quad  DS000A
	.quad  DS000B
	.quad  DS000C
	.quad  DS000D
	.quad  DS000E
	.quad  DS000F
	.quad  DS0010
	.quad  DS0011
	.quad  DS0012
	.quad  DS0013
	.quad  DS0014
	.quad  DS0015
	.quad  DS0016
	.quad  DS0017
	.quad  DS0018
	.quad  DS0019
	.quad  DS001A
	.quad  DS001B
	.quad  DS001C
	.quad  DS001D
	.quad  DS001E
	.quad  DS001F
	.quad  DS0020
	.quad  DS0021
	.quad  DS0022
	.quad  DS0023
	.quad  DS0024
	.quad  DS0025
	.quad  DS0026
	.quad  DS0027
	.quad  DS0028
	.quad  DS0029
	.quad  DS002A
	.quad  DS002B
	.quad  DS002C
	.quad  DS002D
	.quad  DS002E
	.quad  DS002F
	.quad  DS0030
	.quad  DS0031

DS0032:
	.byte  0x40, 0x53, 0x74, 0x61, 0x63, 0x6B, 0x42, 0x61
	.byte  0x73, 0x65, 0x00

DS0033:
	.byte  0x40, 0x50, 0x72, 0x6F, 0x63, 0x53, 0x74, 0x61
	.byte  0x74, 0x75, 0x73, 0x00

DS0034:
	.byte  0x4E, 0x4F, 0x4E, 0x45, 0x00

DS0035:
	.byte  0x4E, 0x4F, 0x54, 0x50, 0x55, 0x42, 0x4C, 0x49
	.byte  0x43, 0x00

DS0036:
	.byte  0x41, 0x4C, 0x4C, 0x00

DS0037:
	.byte  0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x00

DS0038:
	.byte  0x45, 0x58, 0x50, 0x4F, 0x52, 0x54, 0x00

DS0039:
	.byte  0x50, 0x52, 0x4F, 0x4C, 0x4F, 0x47, 0x55, 0x45
	.byte  0x44, 0x45, 0x46, 0x00

DS003A:
	.byte  0x45, 0x50, 0x49, 0x4C, 0x4F, 0x47, 0x55, 0x45
	.byte  0x44, 0x45, 0x46, 0x00

DS003B:
	.byte  0x54, 0x52, 0x55, 0x45, 0x00

DS003C:
	.byte  0x46, 0x41, 0x4C, 0x53, 0x45, 0x00

DS003D:
	.byte  0x47, 0x52, 0x4F, 0x55, 0x50, 0x00

DS003E:
	.byte  0x46, 0x4C, 0x41, 0x54, 0x00

DS003F:
	.byte  0x55, 0x53, 0x45, 0x31, 0x36, 0x00

DS0040:
	.byte  0x55, 0x53, 0x45, 0x33, 0x32, 0x00

DS0041:
	.byte  0x55, 0x53, 0x45, 0x36, 0x34, 0x00

DS0042:
	.byte  0x50, 0x52, 0x45, 0x46, 0x45, 0x52, 0x5F, 0x46
	.byte  0x49, 0x52, 0x53, 0x54, 0x00

DS0043:
	.byte  0x50, 0x52, 0x45, 0x46, 0x45, 0x52, 0x5F, 0x56
	.byte  0x45, 0x58, 0x00

DS0044:
	.byte  0x50, 0x52, 0x45, 0x46, 0x45, 0x52, 0x5F, 0x56
	.byte  0x45, 0x58, 0x33, 0x00

DS0045:
	.byte  0x50, 0x52, 0x45, 0x46, 0x45, 0x52, 0x5F, 0x45
	.byte  0x56, 0x45, 0x58, 0x00

DS0046:
	.byte  0x4E, 0x4F, 0x5F, 0x45, 0x56, 0x45, 0x58, 0x00

DS0047:
	.byte  0x41, 0x55, 0x54, 0x4F, 0x00

DS0048:
	.byte  0x4E, 0x4F, 0x41, 0x55, 0x54, 0x4F, 0x00

DS0049:
	.byte  0x4E, 0x4F, 0x41, 0x4C, 0x49, 0x47, 0x4E, 0x00

DS004A:
	.byte  0x53, 0x41, 0x56, 0x45, 0x00

DS004B:
	.byte  0x4E, 0x4F, 0x53, 0x41, 0x56, 0x45, 0x00

DS004C:
	.byte  0x4E, 0x4F, 0x46, 0x52, 0x41, 0x4D, 0x45, 0x00

DS004D:
	.byte  0x5F, 0x5F, 0x69, 0x6D, 0x70, 0x5F, 0x00

DS004E:
	.byte  0x4F, 0x4E, 0x00

DS004F:
	.byte  0x4F, 0x46, 0x46, 0x00

DS0050:
	.byte  0x50, 0x41, 0x53, 0x43, 0x41, 0x4C, 0x00

DS0051:
	.byte  0x54, 0x41, 0x42, 0x4C, 0x45, 0x00

DS0052:
	.byte  0x4E, 0x4F, 0x54, 0x41, 0x42, 0x4C, 0x45, 0x00

DS0053:
	.byte  0x52, 0x45, 0x47, 0x41, 0x58, 0x00

DS0054:
	.byte  0x4E, 0x4F, 0x52, 0x45, 0x47, 0x53, 0x00


.SECTION .rodata
	.ALIGN	16

DS0000:
	.byte  0x44, 0x4F, 0x54, 0x4E, 0x41, 0x4D, 0x45, 0x00

DS0001:
	.byte  0x4E, 0x4F, 0x44, 0x4F, 0x54, 0x4E, 0x41, 0x4D
	.byte  0x45, 0x00

DS0002:
	.byte  0x4D, 0x35, 0x31, 0x30, 0x00

DS0003:
	.byte  0x4E, 0x4F, 0x4D, 0x35, 0x31, 0x30, 0x00

DS0004:
	.byte  0x53, 0x43, 0x4F, 0x50, 0x45, 0x44, 0x00

DS0005:
	.byte  0x4E, 0x4F, 0x53, 0x43, 0x4F, 0x50, 0x45, 0x44
	.byte  0x00

DS0006:
	.byte  0x4F, 0x4C, 0x44, 0x53, 0x54, 0x52, 0x55, 0x43
	.byte  0x54, 0x53, 0x00

DS0007:
	.byte  0x4E, 0x4F, 0x4F, 0x4C, 0x44, 0x53, 0x54, 0x52
	.byte  0x55, 0x43, 0x54, 0x53, 0x00

DS0008:
	.byte  0x45, 0x4D, 0x55, 0x4C, 0x41, 0x54, 0x4F, 0x52
	.byte  0x00

DS0009:
	.byte  0x4E, 0x4F, 0x45, 0x4D, 0x55, 0x4C, 0x41, 0x54
	.byte  0x4F, 0x52, 0x00

DS000A:
	.byte  0x4C, 0x4A, 0x4D, 0x50, 0x00

DS000B:
	.byte  0x4E, 0x4F, 0x4C, 0x4A, 0x4D, 0x50, 0x00

DS000C:
	.byte  0x52, 0x45, 0x41, 0x44, 0x4F, 0x4E, 0x4C, 0x59
	.byte  0x00

DS000D:
	.byte  0x4E, 0x4F, 0x52, 0x45, 0x41, 0x44, 0x4F, 0x4E
	.byte  0x4C, 0x59, 0x00

DS000E:
	.byte  0x4F, 0x4C, 0x44, 0x4D, 0x41, 0x43, 0x52, 0x4F
	.byte  0x53, 0x00

DS000F:
	.byte  0x4E, 0x4F, 0x4F, 0x4C, 0x44, 0x4D, 0x41, 0x43
	.byte  0x52, 0x4F, 0x53, 0x00

DS0010:
	.byte  0x45, 0x58, 0x50, 0x52, 0x31, 0x36, 0x00

DS0011:
	.byte  0x45, 0x58, 0x50, 0x52, 0x33, 0x32, 0x00

DS0012:
	.byte  0x4E, 0x4F, 0x53, 0x49, 0x47, 0x4E, 0x45, 0x58
	.byte  0x54, 0x45, 0x4E, 0x44, 0x00

DS0013:
	.byte  0x43, 0x41, 0x53, 0x45, 0x4D, 0x41, 0x50, 0x00

DS0014:
	.byte  0x50, 0x52, 0x4F, 0x43, 0x00

DS0015:
	.byte  0x50, 0x52, 0x4F, 0x4C, 0x4F, 0x47, 0x55, 0x45
	.byte  0x00

DS0016:
	.byte  0x45, 0x50, 0x49, 0x4C, 0x4F, 0x47, 0x55, 0x45
	.byte  0x00

DS0017:
	.byte  0x4C, 0x41, 0x4E, 0x47, 0x55, 0x41, 0x47, 0x45
	.byte  0x00

DS0018:
	.byte  0x4E, 0x4F, 0x4B, 0x45, 0x59, 0x57, 0x4F, 0x52
	.byte  0x44, 0x00

DS0019:
	.byte  0x53, 0x45, 0x54, 0x49, 0x46, 0x32, 0x00

DS001A:
	.byte  0x4F, 0x46, 0x46, 0x53, 0x45, 0x54, 0x00

DS001B:
	.byte  0x53, 0x45, 0x47, 0x4D, 0x45, 0x4E, 0x54, 0x00

DS001C:
	.byte  0x41, 0x56, 0x58, 0x45, 0x4E, 0x43, 0x4F, 0x44
	.byte  0x49, 0x4E, 0x47, 0x00

DS001D:
	.byte  0x46, 0x49, 0x45, 0x4C, 0x44, 0x41, 0x4C, 0x49
	.byte  0x47, 0x4E, 0x00

DS001E:
	.byte  0x50, 0x52, 0x4F, 0x43, 0x41, 0x4C, 0x49, 0x47
	.byte  0x4E, 0x00

DS001F:
	.byte  0x4D, 0x5A, 0x00

DS0020:
	.byte  0x46, 0x52, 0x41, 0x4D, 0x45, 0x00

DS0021:
	.byte  0x45, 0x4C, 0x46, 0x00

DS0022:
	.byte  0x52, 0x45, 0x4E, 0x41, 0x4D, 0x45, 0x4B, 0x45
	.byte  0x59, 0x57, 0x4F, 0x52, 0x44, 0x00

DS0023:
	.byte  0x57, 0x49, 0x4E, 0x36, 0x34, 0x00

DS0024:
	.byte  0x44, 0x4C, 0x4C, 0x49, 0x4D, 0x50, 0x4F, 0x52
	.byte  0x54, 0x00

DS0025:
	.byte  0x43, 0x4F, 0x44, 0x45, 0x56, 0x49, 0x45, 0x57
	.byte  0x00

DS0026:
	.byte  0x53, 0x54, 0x41, 0x43, 0x4B, 0x42, 0x41, 0x53
	.byte  0x45, 0x00

DS0027:
	.byte  0x43, 0x53, 0x54, 0x41, 0x43, 0x4B, 0x00

DS0028:
	.byte  0x53, 0x57, 0x49, 0x54, 0x43, 0x48, 0x00

DS0029:
	.byte  0x4C, 0x4F, 0x4F, 0x50, 0x41, 0x4C, 0x49, 0x47
	.byte  0x4E, 0x00

DS002A:
	.byte  0x43, 0x41, 0x53, 0x45, 0x41, 0x4C, 0x49, 0x47
	.byte  0x4E, 0x00

DS002B:
	.byte  0x57, 0x53, 0x54, 0x52, 0x49, 0x4E, 0x47, 0x00

DS002C:
	.byte  0x43, 0x4F, 0x44, 0x45, 0x50, 0x41, 0x47, 0x45
	.byte  0x00

DS002D:
	.byte  0x46, 0x4C, 0x4F, 0x41, 0x54, 0x46, 0x4F, 0x52
	.byte  0x4D, 0x41, 0x54, 0x00

DS002E:
	.byte  0x46, 0x4C, 0x4F, 0x41, 0x54, 0x44, 0x49, 0x47
	.byte  0x49, 0x54, 0x53, 0x00

DS002F:
	.byte  0x4C, 0x49, 0x4E, 0x45, 0x53, 0x49, 0x5A, 0x45
	.byte  0x00

DS0030:
	.byte  0x46, 0x4C, 0x4F, 0x41, 0x54, 0x00

DS0031:
	.byte  0x44, 0x4F, 0x54, 0x4E, 0x41, 0x4D, 0x45, 0x58
	.byte  0x00


.att_syntax prefix
