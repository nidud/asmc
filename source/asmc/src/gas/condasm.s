
.intel_syntax noprefix

.global CondPrepare
.global CondAsmDirective
.global ErrorDirective
.global CondCheckOpen
.global GetIfNestLevel
.global SetIfNestLevel
.global CondInit
.global CurrIfState

.extern SearchNameInStruct
.extern TextItemError
.extern LstWriteSrcLine
.extern EvalOperand
.extern SpecialTable
.extern tstricmp
.extern tstrcmp
.extern tstrcpy
.extern asmerr
.extern MacroLevel
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind


.SECTION .text
	.ALIGN	16

CondPrepare:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	eax, ecx
	jmp	$_011
$C0002:
$C0003:
$C0004:
$C0005:
$C0006:
$C0007:
$C0008:
$C0009:
$C000A:
$C000B:
$C000C:
$C000D:
	cmp	dword ptr [CurrIfState+rip], 0
	jz	$_001
	inc	dword ptr [falseblocknestlevel+rip]
	jmp	$C000F

$_001:	cmp	dword ptr [blocknestlevel+rip], 30
	jnz	$_002
	mov	ecx, 1007
	call	asmerr@PLT
	jmp	$C000F

$_002:	mov	ecx, dword ptr [blocknestlevel+rip]
	mov	eax, 1
	shl	eax, cl
	not	eax
	and	dword ptr [elseoccured+rip], eax
	inc	dword ptr [blocknestlevel+rip]
	jmp	$C000F
$C0011:
$C0012:
$C0013:
$C0014:
$C0015:
$C0016:
$C0017:
$C0018:
$C0019:
$C001A:
$C001B:
$C001C:
$C001D:
	cmp	dword ptr [blocknestlevel+rip], 0
	jz	$_006
	cmp	dword ptr [falseblocknestlevel+rip], 0
	jg	$C000F
	mov	ecx, dword ptr [blocknestlevel+rip]
	dec	ecx
	mov	eax, 1
	shl	eax, cl
	test	dword ptr [elseoccured+rip], eax
	jz	$_003
	mov	ecx, 2142
	call	asmerr@PLT
	jmp	$C000F

$_003:	mov	eax, 2
	cmp	dword ptr [CurrIfState+rip], 1
	jnz	$_004
	mov	eax, 0
$_004:	mov	dword ptr [CurrIfState+rip], eax
	cmp	dword ptr [rbp+0x10], 452
	jnz	$_005
	mov	ecx, dword ptr [blocknestlevel+rip]
	dec	ecx
	mov	eax, 1
	shl	eax, cl
	or	dword ptr [elseoccured+rip], eax
$_005:	jmp	$_007

$_006:	mov	ecx, 1007
	call	asmerr@PLT
$_007:	jmp	$C000F
$C0023:
	cmp	dword ptr [blocknestlevel+rip], 0
	jz	$_009
	cmp	dword ptr [falseblocknestlevel+rip], 0
	jle	$_008
	dec	dword ptr [falseblocknestlevel+rip]
	jmp	$C000F
$_008:	dec	dword ptr [blocknestlevel+rip]
	mov	dword ptr [CurrIfState+rip], 0
	jmp	$_010
$_009:	mov	ecx, 1007
	call	asmerr@PLT
$_010:	jmp	$C000F

$_011:	cmp	eax, 440
	jl	$C000F
	cmp	eax, 465
	jg	$C000F
	push	rax
	lea	r11, [$C000F+rip]
	movzx	eax, word ptr [r11+rax*2-(440*2)+($C0027-$C000F)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C0027:
	.word $C000F-$C0002
	.word $C000F-$C0009
	.word $C000F-$C0003
	.word $C000F-$C0004
	.word $C000F-$C0007
	.word $C000F-$C0008
	.word $C000F-$C000A
	.word $C000F-$C000B
	.word $C000F-$C0005
	.word $C000F-$C000C
	.word $C000F-$C0006
	.word $C000F-$C000D
	.word $C000F-$C0011
	.word $C000F-$C0012
	.word $C000F-$C0019
	.word $C000F-$C0013
	.word $C000F-$C0014
	.word $C000F-$C0017
	.word $C000F-$C0018
	.word $C000F-$C001A
	.word $C000F-$C001B
	.word $C000F-$C0015
	.word $C000F-$C001C
	.word $C000F-$C0016
	.word $C000F-$C001D
	.word $C000F-$C0023
$C000F: leave
	ret

$_012:	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	xor	eax, eax
	cmp	byte ptr [rcx], 0
	jz	Unnamed_1_197
	call	SymFind@PLT
	test	rax, rax
	jz	Unnamed_1_197
	mov	eax, dword ptr [rax+0x14]
	and	eax, 0x02
Unnamed_1_197:
	leave
	ret

$_013:
	cmp	byte ptr [rcx], 0
	jz	$_015
	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_014
	xor	eax, eax
	jmp	$_016

$_014:	inc	rcx
	jmp	$_013

$_015:	mov	eax, 1
$_016:	ret

$_017:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	dword ptr [rbp+0x20], 0
	jz	$_018
	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	tstrcmp@PLT
	jmp	$_019

$_018:	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	tstricmp@PLT
$_019:	leave
	ret

CondAsmDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	cmp	dword ptr [CurrIfState+rip], 0
	jz	$_022
	cmp	dword ptr [rbp+0x28], 0
	jnz	$_020
	cmp	byte ptr [ModuleInfo+0x1DD+rip], 0
	jz	$_021
$_020:	call	LstWriteSrcLine@PLT
$_021:	xor	eax, eax
	jmp	$_096

$_022:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 1
	jnz	$_024
	cmp	dword ptr [MacroLevel+rip], 0
	jz	$_023
	cmp	dword ptr [ModuleInfo+0x1C8+rip], 2
	jz	$_023
	cmp	byte ptr [ModuleInfo+0x1DD+rip], 0
	jz	$_024
$_023:	call	LstWriteSrcLine@PLT
$_024:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbx+0x4]
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	dword ptr [rbp-0x6C], eax
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	eax, dword ptr [r11+rax+0x4]
	jmp	$_093

$_025:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_026
	mov	dword ptr [rbp-0x2C], 0
	mov	dword ptr [rbp-0x68], 0
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x28], eax
$_026:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_027
	jmp	$_029

$_027:	cmp	dword ptr [rbp-0x2C], 1
	jnz	$_028
	test	byte ptr [rbp-0x25], 0x01
	jnz	$_028
	mov	rdx, qword ptr [rbp-0x18]
	mov	eax, dword ptr [rdx+0x28]
	add	dword ptr [rbp-0x68], eax
	mov	ecx, 8020
	call	asmerr@PLT
	jmp	$_029

$_028:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_096

$_029:	mov	esi, 1
	cmp	dword ptr [rbp-0x6C], 440
	jz	$_030
	cmp	dword ptr [rbp-0x6C], 453
	jnz	$_032
$_030:	cmp	dword ptr [rbp-0x68], 0
	jz	$_031
	mov	esi, 0
$_031:	jmp	$_033

$_032:	cmp	dword ptr [rbp-0x68], 0
	jnz	$_033
	mov	esi, 0
$_033:	jmp	$_094

$_034:	mov	rsi, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 9
	jnz	$_035
	cmp	byte ptr [rbx+0x1], 60
	jz	$_038
$_035:	mov	rcx, rsi
	call	SymFind@PLT
	test	eax, eax
	jnz	$_036
	cmp	byte ptr [rbx], 8
	jnz	$_036
	mov	rdx, rsi
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_037

$_036:	mov	ecx, 2051
	call	asmerr@PLT
$_037:	mov	rax, -1
	jmp	$_096

$_038:	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jz	$_039
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_096

$_039:	add	rbx, 24
	mov	rdi, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 9
	jnz	$_040
	cmp	byte ptr [rbx+0x1], 60
	jz	$_043
$_040:	mov	rcx, rdi
	call	SymFind@PLT
	cmp	byte ptr [rbx], 8
	jnz	$_041
	test	eax, eax
	jnz	$_041
	mov	rdx, rdi
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_042

$_041:	mov	ecx, 2051
	call	asmerr@PLT
$_042:	mov	rax, -1
	jmp	$_096

$_043:	add	rbx, 24
	mov	eax, dword ptr [rbp-0x6C]
	jmp	$_056

$_044:	mov	r8d, 1
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jz	$_045
	mov	esi, 0
	jmp	$_046

$_045:	mov	esi, 1
$_046:	jmp	$_057

$_047:	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jz	$_048
	mov	esi, 0
	jmp	$_049

$_048:	mov	esi, 1
$_049:	jmp	$_057

$_050:	mov	r8d, 1
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jnz	$_051
	mov	esi, 0
	jmp	$_052

$_051:	mov	esi, 1
$_052:	jmp	$_057

$_053:	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jnz	$_054
	mov	esi, 0
	jmp	$_055

$_054:	mov	esi, 1
$_055:	jmp	$_057

$_056:	cmp	eax, 444
	je	$_044
	cmp	eax, 457
	je	$_044
	cmp	eax, 445
	je	$_047
	cmp	eax, 458
	je	$_047
	cmp	eax, 446
	jz	$_050
	cmp	eax, 459
	jz	$_050
	jmp	$_053

$_057:	jmp	$_094

$_058:	mov	rsi, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 9
	jnz	$_059
	cmp	byte ptr [rbx+0x1], 60
	jz	$_062
$_059:	mov	rcx, rsi
	call	SymFind@PLT
	cmp	byte ptr [rbx], 8
	jnz	$_060
	test	rax, rax
	jnz	$_060
	mov	rdx, rsi
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_061

$_060:	mov	ecx, 2051
	call	asmerr@PLT
$_061:	mov	rax, -1
	jmp	$_096

$_062:	add	rbx, 24
	cmp	dword ptr [rbp-0x6C], 448
	jz	$_063
	cmp	dword ptr [rbp-0x6C], 461
	jnz	$_066
$_063:	mov	rcx, rsi
	call	$_013
	test	rax, rax
	jz	$_064
	mov	esi, 0
	jmp	$_065

$_064:	mov	esi, 1
$_065:	jmp	$_068

$_066:	mov	rcx, rsi
	call	$_013
	test	rax, rax
	jnz	$_067
	mov	esi, 0
	jmp	$_068

$_067:	mov	esi, 1
$_068:	jmp	$_094

$_069:	mov	esi, 0
	jmp	$_094

$_070:	cmp	byte ptr [ModuleInfo+0x1DA+rip], 0
	jnz	$_071
	mov	ecx, 2061
	call	asmerr@PLT
	jmp	$_094

$_071:	mov	esi, 0
	jmp	$_094

$_072:	mov	esi, 1
	mov	al, byte ptr [rbx]
	test	al, al
	jnz	$_073
	jmp	$_085

$_073:	cmp	al, 8
	jne	$_082
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_079
	cmp	byte ptr [rbx+0x18], 46
	jnz	$_079
	test	rax, rax
	jz	$_079
	cmp	byte ptr [rax+0x18], 7
	jz	$_074
	cmp	qword ptr [rax+0x20], 0
	jz	$_079
$_074:	add	rbx, 24
	cmp	byte ptr [rax+0x18], 7
	jz	$_075
	mov	rax, qword ptr [rax+0x20]
$_075:	mov	rcx, rax
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbx+0x8]
	call	SearchNameInStruct@PLT
	test	rax, rax
	jz	$_076
	cmp	byte ptr [rbx+0x18], 46
	jz	$_074
$_076:	test	rax, rax
	jz	$_077
	mov	esi, 0
	jmp	$_078

$_077:	mov	esi, 1
$_078:	jmp	$_081

$_079:	mov	rcx, qword ptr [rbx+0x8]
	call	$_012
	test	rax, rax
	jz	$_080
	mov	esi, 0
	jmp	$_081

$_080:	mov	esi, 1
$_081:	add	rbx, 24
	jmp	$_085

$_082:	cmp	al, 7
	jnz	$_085
	cmp	dword ptr [rbx+0x4], 274
	jnz	$_085
	mov	rax, qword ptr [ModuleInfo+0x200+rip]
	test	rax, rax
	jz	$_083
	test	byte ptr [rax+0x14], 0x02
	jz	$_083
	mov	esi, 0
	jmp	$_084

$_083:	mov	esi, 1
$_084:	add	rbx, 24
$_085:	cmp	byte ptr [rbx], 0
	jz	$_088
	mov	rdx, qword ptr [rbx-0x8]
	mov	ecx, 8005
	call	asmerr@PLT
	jmp	$_087

$_086:	add	rbx, 24
$_087:	cmp	byte ptr [rbx], 0
	jnz	$_086
$_088:	cmp	dword ptr [rbp-0x6C], 451
	jz	$_089
	cmp	dword ptr [rbp-0x6C], 464
	jnz	$_091
$_089:	test	esi, esi
	jnz	$_090
	mov	esi, 1
	jmp	$_091

$_090:	mov	esi, 0
$_091:	jmp	$_094

$_092:	mov	esi, 0
	jmp	$_094

$_093:	cmp	eax, 1
	je	$_025
	cmp	eax, 2
	je	$_034
	cmp	eax, 3
	je	$_058
	cmp	eax, 5
	je	$_069
	cmp	eax, 6
	je	$_070
	cmp	eax, 4
	je	$_072
	jmp	$_092

$_094:	cmp	byte ptr [rbx], 0
	jz	$_095
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_096

$_095:	mov	dword ptr [CurrIfState+rip], esi
	xor	eax, eax
$_096:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_097:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	imul	ebx, dword ptr [rbp+0x18], 24
	add	rbx, qword ptr [rbp+0x20]
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	mov	byte ptr [rcx], 0
	cmp	dword ptr [rbp+0x18], 0
	jz	$_100
	cmp	byte ptr [rbx], 9
	jnz	$_098
	cmp	byte ptr [rbx+0x1], 60
	jz	$_099
$_098:	mov	rcx, rbx
	call	TextItemError@PLT
	jmp	$_100

$_099:	mov	rdx, qword ptr [rbx+0x8]
	call	tstrcpy@PLT
$_100:	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	leave
	pop	rbx
	ret

ErrorDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	edi, dword ptr [rbx+0x4]
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	lea	r11, [SpecialTable+rip]
	imul	eax, edi, 12
	mov	eax, dword ptr [r11+rax+0x4]
	jmp	$_151

$_101:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_154
	mov	rdx, qword ptr [rbp-0x18]
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_102
	jmp	$_104

$_102:	cmp	dword ptr [rbp-0x2C], 1
	jnz	$_103
	test	byte ptr [rbp-0x25], 0x01
	jnz	$_103
	test	rdx, rdx
	jz	$_103
	cmp	byte ptr [rdx+0x18], 0
	jnz	$_103
	jmp	$_104

$_103:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_154

$_104:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	xor	ecx, ecx
	cmp	byte ptr [rbx], 44
	jnz	$_105
	cmp	byte ptr [rbx+0x18], 0
	jz	$_105
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	add	rbx, 48
$_105:	cmp	dword ptr [Parse_Pass+rip], 0
	je	$_152
	xor	esi, esi
	cmp	edi, 430
	jnz	$_106
	cmp	dword ptr [rbp-0x68], 0
	jz	$_106
	mov	esi, 2054
	jmp	$_107

$_106:	cmp	edi, 429
	jnz	$_107
	cmp	dword ptr [rbp-0x68], 0
	jnz	$_107
	mov	esi, 2053
$_107:	test	esi, esi
	jz	$_108
	mov	rdx, qword ptr [rbp+0x30]
	call	$_097
	mov	r8, rax
	mov	edx, dword ptr [rbp-0x68]
	mov	ecx, esi
	call	asmerr@PLT
$_108:	jmp	$_152

$_109:	cmp	byte ptr [rbx], 8
	jz	$_110
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_154

$_110:	add	rbx, 24
	cmp	byte ptr [rbx], 46
	jz	$_110
	cmp	byte ptr [rbx], 8
	jz	$_110
	cmp	byte ptr [rbx], 44
	jnz	$_111
	cmp	byte ptr [rbx+0x18], 0
	jz	$_111
	add	rbx, 48
$_111:	cmp	dword ptr [Parse_Pass+rip], 0
	je	$_152
	mov	dword ptr [rbp-0x6C], edi
	imul	edi, dword ptr [rbp+0x28], 24
	add	rdi, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rdi+0x8]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x88], rax
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_118
	cmp	byte ptr [rdi+0x18], 46
	jnz	$_118
	test	rax, rax
	jz	$_118
	cmp	byte ptr [rax+0x18], 7
	jz	$_112
	cmp	qword ptr [rax+0x20], 0
	jz	$_118
$_112:	mov	rsi, rdi
$_113:	add	rsi, 48
	cmp	byte ptr [rax+0x18], 7
	jz	$_114
	mov	rax, qword ptr [rax+0x20]
$_114:	mov	rcx, rax
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rsi+0x8]
	call	SearchNameInStruct@PLT
	test	rax, rax
	jz	$_115
	cmp	byte ptr [rsi+0x18], 46
	jz	$_113
$_115:	cmp	byte ptr [rsi], 8
	jnz	$_116
	add	rsi, 24
	jmp	$_117

$_116:	cmp	byte ptr [rsi], 0
	jz	$_117
	cmp	byte ptr [rsi], 44
	jz	$_117
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_154

$_117:	mov	rcx, qword ptr [rsi+0x10]
	mov	rsi, qword ptr [rdi+0x10]
	sub	rcx, rsi
	jmp	$_119

$_118:	mov	rsi, qword ptr [rdi+0x8]
	mov	rcx, qword ptr [rdi+0x28]
	sub	rcx, qword ptr [rdi+0x10]
$_119:	mov	rdi, qword ptr [ModuleInfo+0x188+rip]
	rep movsb
	mov	byte ptr [rdi], 0
	mov	rax, qword ptr [rbp-0x88]
	test	rax, rax
	jz	$_120
	cmp	byte ptr [rax+0x18], 0
	jnz	$_120
	xor	eax, eax
$_120:	cmp	dword ptr [rbp-0x6C], 437
	jnz	$_121
	test	rax, rax
	jz	$_121
	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	ecx, 2056
	call	asmerr@PLT
	jmp	$_122

$_121:	cmp	dword ptr [rbp-0x6C], 438
	jnz	$_122
	test	rax, rax
	jnz	$_122
	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	ecx, 2055
	call	asmerr@PLT
$_122:	jmp	$_152

$_123:	mov	rsi, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 9
	jnz	$_124
	cmp	byte ptr [rbx+0x1], 60
	jz	$_125
$_124:	mov	rcx, rbx
	call	TextItemError@PLT
	jmp	$_154

$_125:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	xor	ecx, ecx
	cmp	byte ptr [rbx], 44
	jnz	$_126
	cmp	byte ptr [rbx+0x18], 0
	jz	$_126
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	add	rbx, 48
$_126:	cmp	dword ptr [Parse_Pass+rip], 0
	je	$_152
	mov	dword ptr [rbp-0x7C], ecx
	xor	edx, edx
	mov	rcx, rsi
	call	$_013
	cmp	edi, 435
	jnz	$_127
	test	rax, rax
	jz	$_127
	mov	edx, 2057
	jmp	$_128

$_127:	mov	rcx, rsi
	call	$_013
	cmp	edi, 436
	jnz	$_128
	test	rax, rax
	jnz	$_128
	mov	edx, 2058
$_128:	test	edx, edx
	jz	$_129
	mov	edi, edx
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp-0x7C]
	call	$_097
	mov	r8, rax
	mov	rdx, rsi
	mov	ecx, edi
	call	asmerr@PLT
$_129:	jmp	$_152

$_130:	mov	rsi, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 9
	jnz	$_131
	cmp	byte ptr [rbx+0x1], 60
	jz	$_132
$_131:	mov	rcx, rbx
	call	TextItemError@PLT
	jmp	$_154

$_132:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 44
	jz	$_133
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_154

$_133:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	rdx, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 9
	jnz	$_134
	cmp	byte ptr [rbx+0x1], 60
	jz	$_135
$_134:	mov	rcx, rbx
	call	TextItemError@PLT
	jmp	$_154

$_135:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	xor	ecx, ecx
	cmp	byte ptr [rbx], 44
	jnz	$_136
	cmp	byte ptr [rbx+0x18], 0
	jz	$_136
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	add	rbx, 48
$_136:	cmp	dword ptr [Parse_Pass+rip], 0
	je	$_152
	mov	dword ptr [rbp-0x7C], ecx
	mov	eax, edi
	xor	edi, edi
	mov	qword ptr [rbp-0x78], rdx
	jmp	$_145

$_137:	mov	r8d, 1
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jz	$_138
	mov	edi, 2060
$_138:	jmp	$_146

$_139:	xor	r8d, r8d
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jz	$_140
	mov	edi, 2060
$_140:	jmp	$_146

$_141:	mov	r8d, 1
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jnz	$_142
	mov	edi, 2059
$_142:	jmp	$_146

$_143:	xor	r8d, r8d
	mov	rcx, rsi
	call	$_017
	test	rax, rax
	jnz	$_144
	mov	edi, 2059
$_144:	jmp	$_146

$_145:	cmp	eax, 431
	jz	$_137
	cmp	eax, 432
	jz	$_139
	cmp	eax, 433
	jz	$_141
	jmp	$_143

$_146:	test	edi, edi
	jz	$_147
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp-0x7C]
	call	$_097
	mov	r9, rax
	mov	r8, qword ptr [rbp-0x78]
	mov	rdx, rsi
	mov	ecx, edi
	call	asmerr@PLT
$_147:	jmp	$_152

$_148:	cmp	byte ptr [ModuleInfo+0x1DA+rip], 0
	jnz	$_149
	mov	ecx, 2061
	call	asmerr@PLT
	jmp	$_154

$_149:	xor	ecx, ecx
	cmp	byte ptr [rbx], 0
	jz	$_150
	mov	ecx, dword ptr [rbp+0x28]
	add	rbx, 24
$_150:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_152
	mov	rdx, qword ptr [rbp+0x30]
	call	$_097
	mov	rdx, rax
	mov	ecx, 2052
	call	asmerr@PLT
	jmp	$_152

$_151:	cmp	eax, 1
	je	$_101
	cmp	eax, 4
	je	$_109
	cmp	eax, 3
	je	$_123
	cmp	eax, 2
	je	$_130
	cmp	eax, 6
	jz	$_148
	cmp	eax, 5
	jz	$_149
	jmp	$_149

$_152:	cmp	byte ptr [rbx], 0
	jz	$_153
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_154

$_153:	xor	eax, eax
$_154:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CondCheckOpen:
	sub	rsp, 40
	cmp	dword ptr [blocknestlevel+rip], 0
	jle	$_155
	lea	rdx, [DS0000+rip]
	mov	ecx, 1010
	call	asmerr@PLT
$_155:	add	rsp, 40
	ret

GetIfNestLevel:
	mov	eax, dword ptr [blocknestlevel+rip]
	ret

SetIfNestLevel:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	mov	eax, dword ptr [rbp+0x10]
	mov	dword ptr [blocknestlevel+rip], eax
	leave
	ret

CondInit:
	xor	eax, eax
	mov	dword ptr [CurrIfState+rip], eax
	mov	dword ptr [blocknestlevel+rip], eax
	mov	dword ptr [falseblocknestlevel+rip], eax
	ret


.SECTION .data
	.ALIGN	16

CurrIfState:
	.int   0x00000000

blocknestlevel:
	.int   0x00000000

falseblocknestlevel:
	.int   0x00000000

elseoccured:
	.int   0x00000000

DS0000:
	.byte  0x69, 0x66, 0x2D, 0x65, 0x6C, 0x73, 0x65, 0x00


.att_syntax prefix
