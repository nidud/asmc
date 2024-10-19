
.intel_syntax noprefix

.global GetToken
.global Tokenize

.extern CurrEnum
.extern UseSavedState
.extern GetStdAssume
.extern CondPrepare
.extern CurrIfState
.extern InputExtend
.extern GetTextLine
.extern FindResWord
.extern optable_idx
.extern SpecialTable
.extern InstrTable
.extern tstrstart
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern CommentBuffer
.extern StringBuffer
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [rcx+0x18], 3
	jnz	$_002
	cmp	dword ptr [rcx+0x1C], 523
	jnz	$_002
	xor	eax, eax
	jmp	$_014

$_002:	cmp	byte ptr [rcx+0x18], 58
	jnz	$_003
	add	rcx, 48
$_003:	movzx	eax, byte ptr [rcx]
	jmp	$_012

$_004:	mov	ecx, dword ptr [rcx+0x4]
	jmp	$_006

$_005:	xor	eax, eax
	jmp	$_014

	jmp	$_007

$_006:	cmp	ecx, 521
	jz	$_005
	cmp	ecx, 478
	jz	$_005
	cmp	ecx, 467
	jz	$_005
	cmp	ecx, 469
	jz	$_005
$_007:	jmp	$_013

$_008:	xor	eax, eax
	jmp	$_014

$_009:	cmp	qword ptr [CurrEnum+rip], 0
	jz	$_010
	xor	eax, eax
	jmp	$_014

$_010:	mov	rcx, qword ptr [rcx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_011
	cmp	byte ptr [rax+0x18], 9
	jnz	$_011
	test	byte ptr [rax+0x38], 0x08
	jnz	$_011
	xor	eax, eax
	jmp	$_014

$_011:	jmp	$_013

$_012:	cmp	eax, 3
	jz	$_004
	cmp	eax, 1
	jz	$_008
	cmp	eax, 8
	jz	$_009
$_013:	mov	eax, 1
$_014:	leave
	ret

$_015:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, r8
	mov	rbx, r9
	lea	rcx, [rsi+0x1]
	call	tstrstart@PLT
	test	ecx, ecx
	jz	$_016
	cmp	ecx, 59
	jz	$_016
	mov	rax, -2
	jmp	$_020

$_016:	mov	rcx, rdi
	call	GetTextLine@PLT
	test	rax, rax
	jnz	$_017
	mov	rax, -2
	jmp	$_020

$_017:	mov	rcx, rdi
	call	tstrstart@PLT
	mov	rdi, rax
	mov	rcx, rdi
	call	tstrlen@PLT
	cmp	dword ptr [rbp+0x30], 0
	jnz	$_018
	mov	byte ptr [rsi], 32
	inc	rsi
$_018:	mov	rcx, rsi
	sub	rcx, qword ptr [rbx+0x10]
	add	ecx, eax
	cmp	ecx, dword ptr [ModuleInfo+0x174+rip]
	jc	$_019
	mov	ecx, 2039
	call	asmerr@PLT
	mov	rcx, rsi
	sub	rcx, qword ptr [rbx+0x10]
	inc	ecx
	mov	eax, dword ptr [ModuleInfo+0x174+rip]
	sub	eax, ecx
	mov	byte ptr [rdi+rax], 0
$_019:	lea	ecx, [rax+0x1]
	xchg	rdi, rsi
	rep movsb
	xor	eax, eax
$_020:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_021:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	qword ptr [rbp-0x30], rdx
	mov	rbx, rcx
	mov	rsi, qword ptr [rdx]
	mov	rdi, qword ptr [rdx+0x8]
	movzx	eax, byte ptr [rsi]
	mov	byte ptr [rbp-0x2], al
	xor	ecx, ecx
	jmp	$_089

$_022:	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	sub	ecx, 32
	mov	dword ptr [rbp-0x20], ecx
	xor	ecx, ecx
	mov	byte ptr [rbx+0x1], al
	mov	ah, al
	movsb
$_023:	mov	al, byte ptr [rsi]
	jmp	$_033

$_024:	mov	byte ptr [rbx+0x1], al
	inc	ecx
	jmp	$_036

$_025:	cmp	byte ptr [rsi-0x1], 92
	jnz	$_027
	cmp	word ptr [rsi-0x3], 23644
	jz	$_026
	cmp	byte ptr [rsi-0x2], 92
	jz	$_027
$_026:	stosb
	inc	rsi
	inc	ecx
	jmp	$_035

$_027:	lea	rax, [rsi+0x1]
	jmp	$_029

$_028:	add	rax, 1
$_029:	cmp	byte ptr [rax], 32
	jz	$_028
	cmp	byte ptr [rax], 9
	jz	$_028
	cmp	byte ptr [rax], 34
	jnz	$_030
	lea	rsi, [rax+0x1]
	mov	eax, 8738
	jmp	$_035

$_030:	mov	eax, 8738
$_031:	stosb
	inc	rsi
	cmp	byte ptr [rsi], al
	jnz	$_036
	dec	rdi
$_032:	mov	byte ptr [rdi], al
	inc	rdi
	inc	rsi
	inc	ecx
	jmp	$_035

$_033:	test	al, al
	jz	$_024
	cmp	ax, 8738
	jnz	$_034
	cmp	byte ptr [rdx+0x30], 0
	jnz	$_025
$_034:	cmp	al, ah
	jz	$_031
	jmp	$_032

$_035:	cmp	ecx, dword ptr [rbp-0x20]
	jc	$_023
$_036:	jmp	$_090

$_037:	test	byte ptr [rdx+0x1C], 0x02
	jne	$_078
	mov	byte ptr [rbp-0x1], 125
$_038:	mov	byte ptr [rbx+0x1], al
	mov	dword ptr [rbp-0x8], ecx
	cmp	al, 60
	jnz	$_039
	mov	byte ptr [rbp-0x1], 62
$_039:	inc	rsi
$_040:	mov	eax, dword ptr [ModuleInfo+0x174+rip]
	sub	eax, 32
	mov	dword ptr [rbp-0x20], eax
	dec	eax
	mov	dword ptr [rbp-0x24], eax
	jmp	$_076

$_041:	mov	ax, word ptr [rsi]
	jmp	$_071

$_042:	inc	dword ptr [rbp-0x8]
	jmp	$_075

$_043:	cmp	dword ptr [rbp-0x8], 0
	jz	$_044
	dec	dword ptr [rbp-0x8]
	jmp	$_045

$_044:	inc	rsi
	jmp	$_077

$_045:	jmp	$_075

$_046:	mov	byte ptr [rbp-0x3], al
	movsb
	inc	ecx
	mov	qword ptr [rbp-0x10], rdi
	mov	qword ptr [rbp-0x18], rsi
	mov	dword ptr [rbp-0x1C], ecx
	mov	ax, word ptr [rsi]
	jmp	$_049

$_047:	cmp	byte ptr [rbp-0x2], 60
	jnz	$_048
	cmp	al, 33
	jnz	$_048
	test	ah, ah
	jz	$_048
	inc	rsi
$_048:	movsb
	inc	ecx
	mov	ax, word ptr [rsi]
$_049:	cmp	al, byte ptr [rbp-0x3]
	jz	$_050
	test	al, al
	jz	$_050
	cmp	ecx, dword ptr [rbp-0x24]
	jc	$_047
$_050:	cmp	al, byte ptr [rbp-0x3]
	jz	$_051
	mov	rsi, qword ptr [rbp-0x18]
	mov	rdi, qword ptr [rbp-0x10]
	mov	ecx, dword ptr [rbp-0x1C]
	jmp	$_076

$_051:	jmp	$_075

$_052:	inc	rsi
	jmp	$_075

$_053:	mov	dword ptr [rbp-0x1C], ecx
	mov	r9, rdx
	mov	r8, rdi
	mov	edx, ecx
	mov	rcx, rsi
	call	$_015
	mov	ecx, dword ptr [rbp-0x1C]
	mov	rdx, qword ptr [rbp-0x30]
	cmp	eax, -2
	jz	$_054
	or	byte ptr [rdx+0x1E], 0x01
	jmp	$_076

$_054:	jmp	$_075

$_055:	cmp	byte ptr [rdx+0x1C], 0
	jne	$_070
	test	byte ptr [rdx+0x1D], 0x20
	jne	$_070
	mov	qword ptr [rbp-0x10], rdi
	mov	dword ptr [rbp-0x1C], ecx
	test	al, al
	jz	$_056
	cmp	al, 59
	jnz	$_057
$_056:	cmp	byte ptr [rbp-0x2], 123
	jnz	$_057
	mov	eax, 1
	jmp	$_061

$_057:	dec	rdi
	jmp	$_059

$_058:	cmp	rdi, qword ptr [rdx+0x8]
	jbe	$_060
	dec	rdi
$_059:	movzx	eax, byte ptr [rdi]
	test	byte ptr [r15+rax], 0x08
	jnz	$_058
$_060:	cmp	al, 44
	mov	al, 0
	sete	al
$_061:	test	eax, eax
	je	$_070
	mov	rcx, qword ptr [rdx+0x8]
	call	tstrlen@PLT
	mov	edi, eax
	mov	rdx, qword ptr [rbp-0x30]
	add	edi, 8
	and	edi, 0xFFFFFFF8
	add	rdi, qword ptr [rdx+0x8]
	mov	rcx, qword ptr [rdx+0x20]
	mov	eax, dword ptr [rcx+0x4]
	mov	edx, dword ptr [rcx+0x1C]
	mov	ecx, dword ptr [rcx+0x4C]
	cmp	eax, 407
	jz	$_062
	cmp	eax, 405
	jz	$_062
	cmp	eax, 406
	jz	$_062
	cmp	edx, 507
	jz	$_062
	cmp	ecx, 507
	jnz	$_066
$_062:	jmp	$_064

$_063:	cmp	byte ptr [rdi+0x1], 0
	jz	$_064
	inc	rdi
	mov	rcx, rdi
	call	tstrstart@PLT
	mov	rdi, rax
	dec	rdi
	mov	byte ptr [rdi], 10
	jmp	$_065

$_064:	lea	rcx, [rdi+0x1]
	call	GetTextLine@PLT
	test	rax, rax
	jnz	$_063
$_065:	jmp	$_067

$_066:	mov	rcx, rdi
	call	GetTextLine@PLT
	test	rax, rax
	jz	$_067
	mov	rcx, rdi
	call	tstrstart@PLT
	mov	rdi, rax
$_067:	test	rax, rax
	jz	$_070
	mov	rcx, rdi
	call	tstrlen@PLT
	add	eax, dword ptr [rbp-0x1C]
	cmp	eax, dword ptr [ModuleInfo+0x174+rip]
	jc	$_069
	mov	rdx, qword ptr [rbp-0x30]
	sub	rsi, qword ptr [rdx]
	sub	rdi, qword ptr [rdx+0x8]
	sub	rbx, qword ptr [rdx+0x20]
	mov	rax, qword ptr [rbp-0x10]
	sub	rax, qword ptr [rdx+0x8]
	mov	qword ptr [rbp-0x10], rax
	mov	rcx, rdx
	call	InputExtend@PLT
	test	rax, rax
	jnz	$_068
	mov	ecx, 2039
	call	asmerr@PLT
	jmp	$_092

$_068:	mov	rdx, qword ptr [rbp-0x30]
	add	rbx, qword ptr [rdx+0x20]
	add	rsi, qword ptr [rdx]
	mov	rax, qword ptr [rdx+0x8]
	add	rdi, rax
	add	qword ptr [rbp-0x10], rax
$_069:	mov	rdx, rdi
	mov	rcx, rsi
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbp-0x30]
	mov	rdi, qword ptr [rbp-0x10]
	mov	ecx, dword ptr [rbp-0x1C]
	jmp	$_040

$_070:	mov	rdx, qword ptr [rbp-0x30]
	mov	rsi, qword ptr [rdx]
	mov	rdi, qword ptr [rdx+0x8]
	movsb
	mov	ecx, 1
	jmp	$_078

	jmp	$_075

$_071:	cmp	al, byte ptr [rbp-0x2]
	je	$_042
	cmp	al, byte ptr [rbp-0x1]
	je	$_043
	cmp	al, 34
	jz	$_072
	cmp	al, 39
	jnz	$_073
$_072:	test	byte ptr [rdx+0x1D], 0x02
	je	$_046
$_073:	cmp	al, 33
	jnz	$_074
	cmp	byte ptr [rbp-0x2], 60
	jnz	$_074
	test	ah, ah
	jne	$_052
$_074:	cmp	al, 92
	je	$_053
	test	al, al
	je	$_055
	cmp	al, 59
	jnz	$_075
	cmp	byte ptr [rbp-0x2], 123
	je	$_055
$_075:	movsb
	inc	ecx
$_076:	cmp	ecx, dword ptr [rbp-0x20]
	jc	$_041
$_077:	jmp	$_090

$_078:	mov	eax, dword ptr [ModuleInfo+0x174+rip]
	sub	eax, 32
	mov	dword ptr [rbp-0x20], eax
	dec	eax
	mov	dword ptr [rbp-0x24], eax
	mov	byte ptr [rbx+0x1], 0
	jmp	$_087

$_079:	movzx	eax, byte ptr [rsi]
	test	eax, eax
	je	$_088
	test	byte ptr [r15+rax], 0x08
	jne	$_088
	cmp	eax, 44
	je	$_088
	cmp	eax, 40
	jnz	$_080
	inc	byte ptr [rdx+0x1F]
	jmp	$_081

$_080:	cmp	eax, 41
	jnz	$_081
	dec	byte ptr [rdx+0x1F]
	jmp	$_088

$_081:	cmp	eax, 37
	jz	$_088
	cmp	eax, 59
	jnz	$_082
	cmp	byte ptr [rdx+0x1C], 0
	jz	$_088
$_082:	cmp	eax, 92
	jnz	$_085
	cmp	byte ptr [rdx+0x1C], 0
	jz	$_083
	test	byte ptr [rdx+0x1C], 0x04
	jz	$_084
$_083:	mov	dword ptr [rbp-0x1C], ecx
	mov	r9, rdx
	mov	r8, rdi
	mov	edx, ecx
	mov	rcx, rsi
	call	$_015
	mov	ecx, dword ptr [rbp-0x1C]
	mov	rdx, qword ptr [rbp-0x30]
	cmp	eax, -2
	jz	$_084
	or	byte ptr [rdx+0x1E], 0x01
	test	ecx, ecx
	jnz	$_087
	mov	rax, -2
	jmp	$_092

$_084:	jmp	$_086

$_085:	cmp	eax, 33
	jnz	$_086
	cmp	byte ptr [rsi+0x1], 0
	jz	$_086
	cmp	ecx, dword ptr [rbp-0x24]
	jnc	$_086
	movsb
$_086:	movsb
	inc	ecx
$_087:	cmp	ecx, dword ptr [rbp-0x20]
	jc	$_079
$_088:	jmp	$_090

$_089:	cmp	eax, 34
	je	$_022
	cmp	eax, 39
	je	$_022
	cmp	eax, 123
	je	$_037
	cmp	eax, 60
	je	$_038
	jmp	$_078

$_090:	cmp	ecx, dword ptr [rbp-0x20]
	jnz	$_091
	mov	ecx, 2041
	call	asmerr@PLT
	jmp	$_092

$_091:	xor	eax, eax
	mov	byte ptr [rdi], al
	inc	rdi
	mov	byte ptr [rbx], 9
	mov	dword ptr [rbx+0x4], ecx
	mov	qword ptr [rdx], rsi
	mov	qword ptr [rdx+0x8], rdi
$_092:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_093:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rsi, rdx
	mov	rdi, qword ptr [rsi]
	mov	eax, dword ptr [rdi]
	mov	dword ptr [rbx+0x4], 0
	jmp	$_146

$_094:	inc	qword ptr [rsi]
	lea	rcx, [__dcolon+rip]
	cmp	ah, 58
	jnz	$_095
	inc	qword ptr [rsi]
	mov	byte ptr [rbx], 13
	mov	qword ptr [rbx+0x8], rcx
	jmp	$_096

$_095:	inc	rcx
	mov	byte ptr [rbx], 58
	mov	qword ptr [rbx+0x8], rcx
$_096:	jmp	$_148

$_097:	shr	eax, 8
	or	eax, 0x202020
	cmp	eax, 7632239
	jnz	$_098
	mov	rax, qword ptr [rsi]
	movzx	eax, byte ptr [rax+0x4]
	test	byte ptr [r15+rax], 0x44
	jnz	$_098
	mov	byte ptr [rbx], 3
	mov	dword ptr [rbx+0x4], 521
	mov	byte ptr [rbx+0x1], 43
	mov	rdi, qword ptr [rsi+0x8]
	mov	rcx, qword ptr [rsi]
	add	qword ptr [rsi], 4
	add	qword ptr [rsi+0x8], 5
	mov	eax, dword ptr [rcx]
	mov	dword ptr [rdi], eax
	xor	eax, eax
	mov	byte ptr [rdi+0x4], al
	jmp	$_148

$_098:	inc	qword ptr [rsi]
	cmp	byte ptr [rsi+0x1C], 0
	jnz	$_099
	cmp	dword ptr [rsi+0x18], 0
	jnz	$_099
	or	byte ptr [rsi+0x1E], 0x02
	mov	rax, -2
	jmp	$_149

$_099:	lea	rax, [__percent+rip]
	mov	byte ptr [rbx], 37
	mov	qword ptr [rbx+0x8], rax
	jmp	$_148

$_100:	inc	byte ptr [rsi+0x1F]
	xor	ecx, ecx
	cmp	dword ptr [rsi+0x18], 2
	jnz	$_101
	cmp	dword ptr [rbx-0x2C], 422
	jnz	$_101
	inc	byte ptr [rsi+0x30]
	jmp	$_132

$_101:	cmp	ah, 41
	jnz	$_102
	cmp	byte ptr [rbx-0x18], 2
	jnz	$_102
	or	byte ptr [rbx-0x16], 0x08
	jmp	$_132

$_102:	cmp	dword ptr [rsi+0x18], 0
	jz	$_104
	cmp	byte ptr [rbx-0x18], 2
	jnz	$_104
	mov	ecx, dword ptr [rbx-0x14]
	mov	dword ptr [rbp-0x4], eax
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	test	byte ptr [r11+rax], 0x0E
	jz	$_103
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	movzx	ecx, byte ptr [r11+rax+0xA]
	call	GetStdAssume@PLT
	test	rax, rax
	jz	$_103
	or	byte ptr [rbx-0x16], 0x08
$_103:	mov	eax, dword ptr [rbp-0x4]
	xor	ecx, ecx
	jmp	$_132

$_104:	cmp	dword ptr [rsi+0x18], 0
	je	$_132
	cmp	byte ptr [rbx-0x18], 8
	jz	$_105
	cmp	byte ptr [rbx-0x18], 2
	jne	$_132
$_105:	xor	eax, eax
	cmp	dword ptr [rsi+0x18], 3
	jc	$_111
	cmp	byte ptr [rbx-0x30], 46
	jnz	$_111
	lea	rdi, [rbx-0x48]
	cmp	byte ptr [rdi], 93
	jnz	$_106
	add	rdi, 48
	inc	eax
	mov	edx, 7
	jmp	$_110

$_106:	jmp	$_108

$_107:	lea	rdi, [rdi-0x30]
$_108:	cmp	byte ptr [rdi-0x18], 46
	jnz	$_109
	cmp	byte ptr [rdi-0x30], 8
	jz	$_107
$_109:	mov	rcx, qword ptr [rdi+0x8]
	call	SymFind@PLT
	xor	edx, edx
$_110:	jmp	$_113

$_111:	lea	rdi, [rbx-0x18]
	mov	rcx, qword ptr [rbx-0x10]
	call	SymFind@PLT
	test	rax, rax
	jz	$_112
	cmp	byte ptr [rax+0x18], 10
	jnz	$_112
	mov	rcx, qword ptr [rax+0x28]
	call	SymFind@PLT
$_112:	xor	edx, edx
$_113:	xor	ecx, ecx
	test	rax, rax
	je	$_130
	test	edx, edx
	jnz	$_114
	movzx	edx, byte ptr [rax+0x18]
$_114:	jmp	$_128

$_115:	cmp	edx, 9
	jne	$_129
	test	byte ptr [rax+0x38], 0x02
	je	$_129
	and	byte ptr [rsi+0x1D], 0xFFFFFFFE
	jmp	$_129

$_116:	test	byte ptr [rax+0x38], 0x02
	jz	$_118
	and	byte ptr [rsi+0x1D], 0xFFFFFFFE
	test	byte ptr [rax+0x14], 0x20
	jz	$_117
	mov	rdx, qword ptr [rax+0x8]
	mov	edx, dword ptr [rdx]
	cmp	edx, 1951613760
	jnz	$_117
	inc	byte ptr [rsi+0x30]
	jmp	$_129

$_117:	mov	ecx, 4
	jmp	$_129

$_118:	test	byte ptr [rax+0x14], 0x20
	jne	$_129
	cmp	qword ptr [rax+0x28], 0
	je	$_129
	mov	rcx, qword ptr [rax+0x28]
	call	SymFind@PLT
	test	rax, rax
	je	$_129
	xor	ecx, ecx
	test	byte ptr [rax+0x15], 0x08
	je	$_129
	mov	ecx, 8
	inc	byte ptr [rsi+0x30]
	jmp	$_129

$_119:	mov	eax, dword ptr [rsi+0x18]
	cmp	eax, 1
	jz	$_120
	cmp	byte ptr [rdi-0x18], 46
	jz	$_121
$_120:	cmp	byte ptr [rdi-0x18], 8
	je	$_129
	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	je	$_129
	mov	rdx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdx, qword ptr [rdx+0x68]
	cmp	dword ptr [rdx+0x48], 1
	jne	$_129
	jmp	$_126

$_121:	cmp	eax, 5
	jc	$_129
	cmp	byte ptr [rdi-0x18], 46
	jne	$_129
	cmp	byte ptr [rdi-0x30], 93
	jne	$_129
	sub	rdi, 72
	sub	eax, 3
	mov	edx, 1
$_122:	cmp	byte ptr [rdi], 91
	jnz	$_123
	dec	edx
	jz	$_125
	jmp	$_124

$_123:	cmp	byte ptr [rdi], 93
	jnz	$_124
	inc	edx
$_124:	sub	rdi, 24
	dec	eax
	jnz	$_122
$_125:	cmp	byte ptr [rdi], 91
	jnz	$_129
	cmp	eax, 1
	jbe	$_126
	cmp	byte ptr [rdi-0x18], 8
	jnz	$_126
	sub	rdi, 24
$_126:	mov	ecx, 8
	inc	byte ptr [rsi+0x30]
	jmp	$_129

$_127:	mov	rdx, qword ptr [rsi]
	cmp	byte ptr [rdx+0x1], 41
	jnz	$_129
	mov	ecx, 8
	jmp	$_129

$_128:	cmp	byte ptr [Options+0xC6+rip], 1
	je	$_115
	cmp	edx, 9
	je	$_116
	cmp	edx, 7
	je	$_119
	cmp	edx, 5
	jz	$_126
	cmp	edx, 1
	jz	$_126
	cmp	edx, 2
	jz	$_126
	test	byte ptr [rax+0x15], 0x08
	jnz	$_126
	test	edx, edx
	jz	$_127
$_129:	or	byte ptr [rdi+0x2], cl
	jmp	$_131

$_130:	mov	rdi, qword ptr [rsi]
	cmp	byte ptr [rdi+0x1], 41
	jnz	$_131
	or	byte ptr [rbx-0x16], 0x08
$_131:	mov	rdi, qword ptr [rsi]
	mov	eax, dword ptr [rdi]
$_132:	or	cl, byte ptr [rbx-0x16]
	test	cl, 0x08
	jz	$_133
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_133
	mov	rcx, qword ptr [rsi+0x20]
	or	byte ptr [rcx+0x2], 0x40
$_133:	cmp	al, 41
	jnz	$_134
	cmp	byte ptr [rsi+0x1F], 0
	jz	$_134
	dec	byte ptr [rsi+0x1F]
	dec	byte ptr [rsi+0x30]
$_134:	inc	qword ptr [rsi]
	mov	byte ptr [rbx], al
	mov	byte ptr [rbx+0x1], 0
	movzx	eax, al
	sub	al, 40
	lea	rcx, [stokstr1+rip]
	lea	rax, [rcx+rax*2]
	mov	qword ptr [rbx+0x8], rax
	jmp	$_148

$_135:	inc	qword ptr [rsi]
	mov	byte ptr [rbx], al
	movzx	eax, al
	sub	al, 91
	lea	rcx, [stokstr2+rip]
	lea	rax, [rcx+rax*2]
	mov	qword ptr [rbx+0x8], rax
	jmp	$_148

$_136:	cmp	ah, 61
	jz	$_137
	mov	byte ptr [rbx], 3
	mov	dword ptr [rbx+0x4], 523
	mov	byte ptr [rbx+0x1], 45
	lea	rax, [__equ+rip]
	mov	qword ptr [rbx+0x8], rax
	inc	qword ptr [rsi]
	jmp	$_148

$_137:	mov	edx, eax
	lea	rcx, [DS0000+rip]
	call	tstrchr@PLT
	mov	edx, dword ptr [rdi]
	test	rax, rax
	je	$_144
	test	byte ptr [rsi+0x1D], 0x01
	je	$_144
	mov	al, byte ptr [rax]
	mov	rcx, qword ptr [rsi+0x8]
	inc	qword ptr [rsi+0x8]
	mov	byte ptr [rcx], al
	inc	qword ptr [rsi]
	mov	dword ptr [rbx+0x4], 1
	mov	rdx, qword ptr [rsi]
	cmp	al, 38
	jz	$_138
	cmp	al, 124
	jnz	$_142
$_138:	cmp	byte ptr [rdx], al
	jnz	$_139
	inc	rcx
	mov	byte ptr [rcx], al
	inc	qword ptr [rsi+0x8]
	inc	qword ptr [rsi]
	mov	dword ptr [rbx+0x4], 2
	jmp	$_141

$_139:	cmp	al, 38
	jnz	$_141
	cmp	byte ptr [rbx-0x18], 44
	jz	$_140
	cmp	byte ptr [rbx-0x18], 40
	jnz	$_141
$_140:	mov	byte ptr [rbx], al
	lea	rax, [__amp+rip]
	mov	qword ptr [rbx+0x8], rax
	jmp	$_148

$_141:	jmp	$_143

$_142:	cmp	byte ptr [rdx], 61
	jnz	$_143
	inc	rcx
	mov	byte ptr [rcx], 61
	inc	qword ptr [rsi+0x8]
	inc	qword ptr [rsi]
	mov	dword ptr [rbx+0x4], 2
$_143:	xor	eax, eax
	mov	byte ptr [rbx], 9
	mov	byte ptr [rbx+0x1], al
	mov	byte ptr [rcx+0x1], al
	inc	qword ptr [rsi+0x8]
	jmp	$_148

$_144:	cmp	dl, 38
	jnz	$_145
	inc	qword ptr [rsi]
	mov	byte ptr [rbx], dl
	lea	rax, [__amp+rip]
	mov	qword ptr [rbx+0x8], rax
	jmp	$_148

$_145:	mov	rdx, rsi
	mov	rcx, rbx
	call	$_021
	jmp	$_149

	jmp	$_148

$_146:	cmp	al, 58
	je	$_094
	cmp	al, 37
	je	$_097
	cmp	al, 40
	je	$_100
	cmp	al, 41
	je	$_133
	cmp	al, 42
	jc	$_147
	cmp	al, 47
	jbe	$_134
$_147:	cmp	al, 91
	je	$_135
	cmp	al, 93
	je	$_135
	cmp	al, 61
	je	$_136
	jmp	$_137

$_148:	xor	eax, eax
$_149:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_150:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rsi, rdx
	mov	rdx, qword ptr [rsi]
	xor	edi, edi
	mov	byte ptr [rbp-0x1], 0
	mov	eax, dword ptr [rdx]
	or	eax, 0x2000
	cmp	ax, 30768
	jnz	$_151
	add	rdx, 2
	inc	byte ptr [rbp-0x1]
$_151:	movzx	eax, byte ptr [rdx]
	test	byte ptr [r15+rax], 0x04
	jz	$_152
	sub	eax, 48
	mov	ecx, eax
	mov	eax, 1
	shl	eax, cl
	or	edi, eax
	jmp	$_154

$_152:	test	byte ptr [r15+rax], 0xFFFFFF80
	jz	$_153
	or	eax, 0x20
	add	eax, -87
	mov	ecx, eax
	mov	eax, 1
	shl	eax, cl
	or	edi, eax
	jmp	$_154

$_153:	or	eax, 0x20
	jmp	$_155

$_154:	inc	rdx
	jmp	$_151

$_155:
	mov	rcx, rdx
	cmp	byte ptr [rbp-0x1], 0
	jz	$_157
	mov	eax, 16
	test	edi, edi
	jnz	$_156
	xor	eax, eax
$_156:	jmp	$_187

$_157:	jmp	$_186

$_158:	xor	edi, edi
	mov	eax, 1
	jmp	$_166

$_159:	mov	al, byte ptr [rdx]
	cmp	eax, 46
	jnz	$_160
	add	ah, 1
	jmp	$_165

$_160:	cmp	al, 48
	jc	$_161
	cmp	al, 57
	jbe	$_165
$_161:	or	al, 0x20
	cmp	al, 101
	jnz	$_162
	test	edi, edi
	jz	$_163
$_162:	jmp	$_167

$_163:	inc	edi
	mov	al, byte ptr [rdx+0x1]
	cmp	al, 43
	jz	$_164
	cmp	al, 45
	jnz	$_165
$_164:	inc	rdx
$_165:	inc	rdx
$_166:	test	al, al
	jnz	$_159
$_167:	mov	byte ptr [rbx], 11
	mov	byte ptr [rbx+0x1], 0
	jmp	$_191

$_168:	mov	byte ptr [rbx], 11
	mov	byte ptr [rbx+0x1], 114
	inc	rdx
	jmp	$_191

$_169:	mov	eax, 16
	inc	rdx
	jmp	$_187

$_170:	xor	eax, eax
	test	edi, 0x3
	jz	$_171
	mov	eax, 2
	inc	rdx
$_171:	jmp	$_187

$_172:	xor	eax, eax
	test	edi, 0x3FF
	jz	$_173
	mov	eax, 10
	inc	rdx
$_173:	jmp	$_187

$_174:	test	edi, 0xFF
	jnz	$_175
	mov	byte ptr [rbx], 11
	mov	byte ptr [rbx+0x1], 113
	inc	rdx
	jmp	$_191

$_175:	xor	eax, eax
	test	edi, 0xFF
	jz	$_176
	mov	eax, 8
	inc	rdx
$_176:	jmp	$_187

$_177:	mov	cl, byte ptr [ModuleInfo+0x1C4+rip]
	mov	eax, 1
	shl	eax, cl
	dec	rdx
	mov	cl, byte ptr [rdx]
	or	cl, 0x20
	cmp	cl, 98
	jz	$_178
	cmp	cl, 100
	jnz	$_184
$_178:	cmp	edi, eax
	jc	$_184
	mov	rax, qword ptr [rsi]
	mov	ch, 49
	cmp	cl, 98
	jz	$_179
	mov	ch, 57
$_179:	jmp	$_181

$_180:	inc	rax
$_181:	cmp	rax, rdx
	jnc	$_182
	cmp	byte ptr [rax], ch
	jbe	$_180
$_182:	cmp	rax, rdx
	jnz	$_184
	mov	eax, 2
	cmp	cl, 98
	jz	$_183
	mov	eax, 10
$_183:	mov	rcx, rdx
	inc	rdx
	jmp	$_187

$_184:	inc	rdx
	mov	cl, byte ptr [ModuleInfo+0x1C4+rip]
	mov	eax, 1
	shl	eax, cl
	cmp	edi, eax
	mov	eax, 0
	mov	rcx, rdx
	jnc	$_185
	movzx	eax, byte ptr [ModuleInfo+0x1C4+rip]
$_185:	jmp	$_187

$_186:	cmp	eax, 46
	je	$_158
	cmp	eax, 114
	je	$_168
	cmp	eax, 104
	je	$_169
	cmp	eax, 121
	je	$_170
	cmp	eax, 116
	je	$_172
	cmp	eax, 113
	je	$_174
	cmp	eax, 111
	je	$_175
	jmp	$_177

$_187:	test	eax, eax
	jz	$_188
	mov	byte ptr [rbx], 10
	mov	byte ptr [rbx+0x1], al
	sub	rcx, qword ptr [rsi]
	mov	dword ptr [rbx+0x4], ecx
	jmp	$_191

$_188:	mov	byte ptr [rbx], 12
	jmp	$_190

$_189:	inc	rdx
$_190:	movzx	eax, byte ptr [rdx]
	test	byte ptr [r15+rax], 0x44
	jnz	$_189
$_191:	mov	rcx, rdx
	mov	rdx, rsi
	mov	rdi, qword ptr [rdx+0x8]
	mov	rsi, qword ptr [rdx]
	sub	rcx, rsi
	rep movsb
	xor	eax, eax
	mov	byte ptr [rdi], al
	inc	rdi
	mov	qword ptr [rdx], rsi
	mov	qword ptr [rdx+0x8], rdi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_192:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	inc	qword ptr [rdx]
	mov	rsi, qword ptr [rdx]
	mov	rdi, qword ptr [rdx+0x8]
	mov	byte ptr [rbx], 8
	mov	dword ptr [rbx+0x4], 0
	mov	al, byte ptr [rsi]
	jmp	$_196

$_193:	test	al, al
	jz	$_194
	cmp	al, 59
	jnz	$_195
$_194:	mov	byte ptr [rdi], 0
	mov	ecx, 2046
	call	asmerr@PLT
	jmp	$_197

$_195:	lodsb
	stosb
	inc	qword ptr [rdx]
$_196:	cmp	al, 96
	jnz	$_193
	inc	qword ptr [rdx]
	xor	eax, eax
	stosb
	mov	qword ptr [rdx+0x8], rdi
$_197:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_198:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rsi, qword ptr [rdx]
	mov	rdi, qword ptr [rdx+0x8]
	mov	byte ptr [rbx+0x1], 0
	mov	eax, dword ptr [rsi]
	cmp	ax, 8780
	jnz	$_199
	cmp	byte ptr [rdx+0x1F], 0
	jz	$_199
	stosb
	inc	qword ptr [rdx]
	inc	qword ptr [rdx+0x8]
	mov	rcx, rbx
	call	$_021
	jmp	$_225

$_199:	stosb
	inc	rsi
	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x44
	jnz	$_199
	cmp	al, 46
	jnz	$_202
	cmp	byte ptr [ModuleInfo+0x354+rip], 0
	jz	$_202
	mov	rcx, qword ptr [rdx+0x8]
	cmp	al, byte ptr [rcx]
	jnz	$_202
	cmp	al, byte ptr [rsi+0x1]
	jz	$_200
	cmp	byte ptr [rsi+0x1], 48
	jc	$_201
	cmp	byte ptr [rsi+0x1], 57
	ja	$_201
$_200:	jmp	$_199

$_201:	movzx	eax, byte ptr [rsi+0x1]
	test	byte ptr [r15+rax], 0x44
	jz	$_202
	mov	al, 46
	jmp	$_199

$_202:	mov	rcx, rdi
	sub	rcx, qword ptr [rdx+0x8]
	cmp	ecx, 247
	jbe	$_203
	mov	ecx, 2043
	call	asmerr@PLT
	mov	rdx, qword ptr [rbp+0x30]
	mov	rdi, qword ptr [rdx+0x8]
	add	rdi, 247
$_203:	mov	byte ptr [rdi], 0
	inc	rdi
	mov	rax, qword ptr [rdx+0x8]
	mov	al, byte ptr [rax]
	cmp	ecx, 1
	jnz	$_204
	cmp	al, 63
	jnz	$_204
	mov	qword ptr [rdx], rsi
	mov	byte ptr [rbx], 63
	lea	rax, [__quest+rip]
	mov	qword ptr [rbx+0x8], rax
	jmp	$_225

$_204:	mov	rax, qword ptr [rdx+0x8]
	mov	edx, ecx
	mov	rcx, rax
	call	FindResWord@PLT
	mov	rdx, qword ptr [rbp+0x30]
	test	eax, eax
	jnz	$_206
	mov	rax, qword ptr [rdx+0x8]
	mov	al, byte ptr [rax]
	cmp	al, 46
	jnz	$_205
	cmp	byte ptr [ModuleInfo+0x1D4+rip], 0
	jnz	$_205
	mov	byte ptr [rbx], 46
	lea	rax, [stokstr1+0xC+rip]
	mov	qword ptr [rbx+0x8], rax
	inc	qword ptr [rdx]
	jmp	$_225

$_205:	mov	qword ptr [rdx], rsi
	mov	qword ptr [rdx+0x8], rdi
	mov	byte ptr [rbx], 8
	mov	dword ptr [rbx+0x4], 0
	jmp	$_225

$_206:	mov	qword ptr [rdx], rsi
	mov	qword ptr [rdx+0x8], rdi
	jmp	$_210

$_207:	cmp	dword ptr [rdx+0x18], 0
	jnz	$_208
	mov	eax, 1212
$_208:	jmp	$_211

$_209:	mov	byte ptr [rbx+0x2], 1
	jmp	$_211

$_210:	cmp	eax, 278
	jz	$_207
	cmp	eax, 321
	jz	$_209
	cmp	eax, 317
	jz	$_209
	cmp	eax, 416
	jz	$_209
$_211:	mov	dword ptr [rbx+0x4], eax
	cmp	eax, 531
	jc	$_214
	cmp	byte ptr [ModuleInfo+0x1D6+rip], 0
	jz	$_213
	mov	eax, dword ptr [rbx+0x4]
	sub	eax, 531
	lea	rdx, [optable_idx+rip]
	lea	rcx, [InstrTable+rip]
	movzx	eax, word ptr [rdx+rax*2]
	movzx	ecx, word ptr [rcx+rax*8+0x4]
	mov	eax, ecx
	and	eax, 0xF0
	and	ecx, 0xFF00
	mov	edi, dword ptr [ModuleInfo+0x1C0+rip]
	mov	esi, edi
	and	edi, 0xF0
	and	esi, 0xFF00
	cmp	eax, edi
	ja	$_212
	cmp	ecx, esi
	jbe	$_213
$_212:	mov	byte ptr [rbx], 8
	mov	dword ptr [rbx+0x4], 0
	jmp	$_225

$_213:	mov	byte ptr [rbx], 1
	jmp	$_225

$_214:	imul	esi, dword ptr [rbx+0x4], 12
	lea	rcx, [SpecialTable+rip]
	add	rcx, rsi
	mov	al, byte ptr [rcx+0xA]
	mov	byte ptr [rbx+0x1], al
	movzx	eax, byte ptr [rcx+0xB]
	jmp	$_223

$_215:	mov	ecx, 2
	jmp	$_224

$_216:	mov	rdx, qword ptr [rbp+0x30]
	cmp	byte ptr [rdx+0x1D], 0
	jnz	$_217
	mov	eax, dword ptr [rcx]
	mov	byte ptr [rdx+0x1D], al
$_217:	mov	ecx, 3
	jmp	$_224

$_218:	mov	ecx, 4
	jmp	$_224

$_219:	mov	ecx, 5
	jmp	$_224

$_220:	mov	ecx, 6
	jmp	$_224

$_221:	mov	ecx, 7
	jmp	$_224

$_222:	mov	ecx, 8
	mov	dword ptr [rbx+0x4], 0
	jmp	$_224

$_223:	cmp	eax, 2
	jz	$_215
	cmp	eax, 3
	jz	$_216
	cmp	eax, 4
	jz	$_218
	cmp	eax, 5
	jz	$_219
	cmp	eax, 6
	jz	$_220
	cmp	eax, 7
	jz	$_221
	jmp	$_222

$_224:	mov	byte ptr [rbx], cl
	xor	eax, eax
$_225:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_226:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call	tstrstart@PLT
	test	ecx, ecx
	jz	$_228
	mov	byte ptr [ModuleInfo+0x1CF+rip], cl
	inc	rax
	mov	edx, ecx
	mov	rcx, rax
	call	tstrchr@PLT
	test	rax, rax
	jz	$_227
	mov	byte ptr [ModuleInfo+0x1CF+rip], 0
$_227:	jmp	$_229

$_228:	mov	ecx, 2110
	call	asmerr@PLT
$_229:	leave
	ret

GetToken:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	byte ptr [rcx+0x2], 0
	mov	rax, qword ptr [rdx]
	jmp	$_247

$_230:	call	$_150
	jmp	$_249

$_231:	call	$_198
	jmp	$_249

$_232:	cmp	byte ptr [Options+0xC6+rip], 0
	jne	$_248
	call	$_192
	jmp	$_249

$_233:	mov	rax, qword ptr [rdx]
	movzx	eax, byte ptr [rax+0x1]
	test	byte ptr [r15+rax], 0x44
	je	$_248
	xor	eax, eax
	cmp	eax, dword ptr [rdx+0x18]
	jz	$_234
	movzx	eax, byte ptr [rcx-0x18]
$_234:	cmp	dword ptr [rdx+0x18], 0
	jz	$_235
	cmp	eax, 2
	jz	$_236
	cmp	eax, 41
	jz	$_236
	cmp	eax, 93
	jz	$_236
	cmp	eax, 8
	jz	$_236
$_235:	call	$_198
	jmp	$_249

$_236:	cmp	eax, 41
	jnz	$_243
	mov	rsi, rcx
	lea	rbx, [rcx-0x30]
	mov	eax, 1
	mov	ecx, dword ptr [rdx+0x18]
	sub	ecx, 2
$_237:	cmp	ecx, 1
	jle	$_240
	cmp	byte ptr [rbx], 40
	jnz	$_238
	dec	eax
	jz	$_240
	jmp	$_239

$_238:	cmp	byte ptr [rbx], 41
	jnz	$_239
	inc	eax
$_239:	dec	ecx
	sub	rbx, 24
	jmp	$_237

$_240:	cmp	ecx, 1
	jbe	$_242
	sub	ecx, 1
	sub	rbx, 24
	cmp	byte ptr [rbx-0x18], 46
	jnz	$_242
	sub	ecx, 2
	sub	rbx, 48
	cmp	byte ptr [rbx], 93
	jnz	$_242
	sub	rbx, 24
	dec	ecx
$_241:	test	ecx, ecx
	jz	$_242
	cmp	byte ptr [rbx], 91
	jz	$_242
	dec	ecx
	sub	rbx, 24
	jmp	$_241

$_242:	mov	eax, dword ptr [rbx-0x14]
	mov	rcx, rsi
	jmp	$_244

$_243:	xor	eax, eax
	cmp	dword ptr [rdx+0x18], 1
	jbe	$_244
	mov	eax, dword ptr [rcx-0x2C]
$_244:	cmp	eax, 318
	jz	$_245
	cmp	eax, 418
	jz	$_245
	cmp	eax, 319
	jz	$_245
	cmp	eax, 421
	jnz	$_246
$_245:	call	$_198
	jmp	$_249

$_246:	jmp	$_248

$_247:	movzx	eax, byte ptr [rax]
	test	byte ptr [r15+rax], 0x04
	jne	$_230
	test	byte ptr [r15+rax], 0x40
	jne	$_231
	cmp	al, 96
	je	$_232
	cmp	al, 46
	je	$_233
$_248:	call	$_093
$_249:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

Tokenize:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 104
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rbp-0x40], rax
	mov	qword ptr [rbp-0x30], rax
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x20], rax
	mov	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x18], rax
	mov	eax, dword ptr [rbp+0x40]
	mov	byte ptr [rbp-0x24], al
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x28], eax
	mov	byte ptr [rbp-0x23], 0
	mov	byte ptr [rbp-0x22], 0
	mov	byte ptr [rbp-0x10], 0
	mov	byte ptr [rbp-0x21], 0
	cmp	dword ptr [rbp+0x30], 0
	jnz	$_252
	mov	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x38], rax
	cmp	byte ptr [ModuleInfo+0x1CF+rip], 0
	jz	$_251
	movzx	edx, byte ptr [ModuleInfo+0x1CF+rip]
	mov	rcx, qword ptr [rbp-0x30]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_250
	mov	byte ptr [ModuleInfo+0x1CF+rip], 0
$_250:	jmp	$_290

$_251:	jmp	$_253

$_252:	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	mov	qword ptr [rbp-0x38], rax
$_253:	mov	rsi, qword ptr [rbp-0x40]
	jmp	$_255

$_254:	inc	rsi
$_255:	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x08
	jnz	$_254
	mov	qword ptr [rbp-0x40], rsi
	cmp	al, 59
	jnz	$_259
	cmp	dword ptr [rbp+0x40], 0
	jnz	$_259
	jmp	$_257

$_256:	movzx	eax, byte ptr [rsi-0x1]
	test	byte ptr [r15+rax], 0x08
	jz	$_258
	dec	rsi
$_257:	cmp	rsi, qword ptr [rbp-0x30]
	ja	$_256
$_258:	mov	qword ptr [rbp-0x40], rsi
	mov	rdx, rsi
	mov	rcx, qword ptr [CommentBuffer+rip]
	call	tstrcpy@PLT
	mov	qword ptr [ModuleInfo+0x218+rip], rax
	mov	byte ptr [rsi], 0
$_259:	imul	ebx, dword ptr [rbp-0x28], 24
	add	rbx, qword ptr [rbp-0x20]
	mov	qword ptr [rbx+0x10], rsi
	cmp	byte ptr [rsi], 0
	jne	$_267
	cmp	dword ptr [rbp-0x28], 1
	jbe	$_266
	cmp	byte ptr [rbx-0x18], 44
	jz	$_260
	cmp	byte ptr [rbp-0x21], 0
	je	$_266
$_260:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_261
	cmp	dword ptr [UseSavedState+rip], 0
	jne	$_266
$_261:	cmp	dword ptr [rbp+0x30], 0
	jne	$_266
	mov	rcx, qword ptr [rbp-0x20]
	call	$_001
	test	rax, rax
	jnz	$_262
	cmp	byte ptr [rbp-0x21], 0
	je	$_266
$_262:	mov	rcx, qword ptr [rbp-0x38]
	call	tstrlen@PLT
	mov	edi, eax
	add	edi, 8
	and	edi, 0xFFFFFFF8
	add	rdi, qword ptr [rbp-0x38]
	mov	rcx, rdi
	call	GetTextLine@PLT
	test	rax, rax
	jz	$_266
	mov	rcx, rdi
	jmp	$_264

$_263:	add	rcx, 1
$_264:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_263
	xchg	rax, rcx
	mov	rdi, rax
	test	ecx, ecx
	jz	$_266
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x40]
	call	tstrcpy@PLT
	mov	rcx, qword ptr [rbp-0x30]
	call	tstrlen@PLT
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	sub	ecx, 32
	cmp	eax, ecx
	jc	$_265
	lea	rcx, [rbp-0x40]
	call	InputExtend@PLT
	test	rax, rax
	jnz	$_265
	mov	ecx, 2039
	call	asmerr@PLT
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x28], eax
	jmp	$_289

$_265:	jmp	$_253

$_266:	jmp	$_289

$_267:	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rbx+0x8], rax
	lea	rdx, [rbp-0x40]
	mov	rcx, rbx
	call	GetToken
	mov	dword ptr [rbp-0x4], eax
	imul	ebx, dword ptr [rbp-0x28], 24
	add	rbx, qword ptr [rbp-0x20]
	jmp	$_272

$_268:	jmp	$_253

$_269:	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x28], eax
	jmp	$_289

$_270:	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_271
	mov	rax, qword ptr [rbp-0x20]
	or	byte ptr [rax+0x2], 0x40
$_271:	jmp	$_273

$_272:	cmp	eax, -2
	jz	$_268
	cmp	eax, -1
	jz	$_269
	cmp	byte ptr [rbx], 13
	jz	$_270
$_273:	test	byte ptr [rbp+0x40], 0x01
	jne	$_286
	mov	rax, qword ptr [rbp-0x20]
	mov	cl, byte ptr [rax+0x18]
	mov	eax, dword ptr [rbp-0x28]
	test	eax, eax
	jz	$_274
	cmp	eax, 2
	jne	$_286
	cmp	cl, 58
	jz	$_274
	cmp	cl, 13
	jne	$_286
$_274:	mov	ecx, dword ptr [rbx+0x4]
	cmp	byte ptr [rbx], 3
	jne	$_285
	cmp	byte ptr [rbx+0x1], 0
	jz	$_275
	cmp	ecx, 394
	jne	$_285
$_275:	cmp	ecx, 439
	jnz	$_276
	mov	rcx, qword ptr [rbp-0x40]
	call	$_226
	jmp	$_289

$_276:	mov	edx, 1
	cmp	ecx, 394
	jnz	$_281
	dec	edx
	test	byte ptr [ModuleInfo+0x334+rip], 0x40
	jnz	$_281
	mov	rax, qword ptr [rbp-0x40]
	mov	cl, byte ptr [rax]
	jmp	$_278

$_277:	inc	rax
	mov	cl, byte ptr [rax]
$_278:	cmp	cl, 32
	jz	$_277
	cmp	cl, 9
	jz	$_277
	cmp	cl, 58
	jnz	$_281
	inc	rax
	mov	cl, byte ptr [rax]
	jmp	$_280

$_279:	inc	rax
	mov	cl, byte ptr [rax]
$_280:	cmp	cl, 32
	jz	$_279
	cmp	cl, 9
	jz	$_279
	mov	eax, dword ptr [rax]
	or	eax, 0x20202020
	cmp	eax, 1935961701
	jnz	$_281
	mov	ecx, 465
	inc	edx
$_281:	test	edx, edx
	jz	$_283
	call	CondPrepare@PLT
	cmp	dword ptr [CurrIfState+rip], 0
	jz	$_282
	inc	dword ptr [rbp-0x28]
	jmp	$_289

$_282:	jmp	$_284

$_283:	cmp	dword ptr [CurrIfState+rip], 0
	jnz	$_289
$_284:	jmp	$_286

$_285:	cmp	dword ptr [CurrIfState+rip], 0
	jz	$_286
	jmp	$_289

$_286:	inc	dword ptr [rbp-0x28]
	mov	eax, dword ptr [ModuleInfo+0x174+rip]
	shr	eax, 2
	cmp	dword ptr [rbp-0x28], eax
	jl	$_288
	dec	dword ptr [rbp-0x28]
	lea	rcx, [rbp-0x40]
	call	InputExtend@PLT
	test	rax, rax
	jnz	$_287
	mov	ecx, 2141
	call	asmerr@PLT
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x28], eax
	jmp	$_290

$_287:	inc	dword ptr [rbp-0x28]
$_288:	mov	rax, qword ptr [rbp-0x38]
	sub	rax, qword ptr [StringBuffer+rip]
	add	rax, 8
	and	rax, 0xFFFFFFFFFFFFFFF8
	add	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x38], rax
	jmp	$_253

$_289:	mov	rax, qword ptr [rbp-0x38]
	sub	rax, qword ptr [StringBuffer+rip]
	add	rax, 8
	and	rax, 0xFFFFFFFFFFFFFFF8
	add	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x38], rax
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	cmp	byte ptr [rbp-0x21], 0
	jz	$_290
	cmp	dword ptr [rbp+0x40], 1
	jz	$_290
	cmp	dword ptr [CurrIfState+rip], 0
	jnz	$_290
	mov	ecx, 2157
	call	asmerr@PLT
$_290:	mov	rbx, qword ptr [rbp-0x20]
	imul	eax, dword ptr [rbp-0x28], 24
	add	rbx, rax
	mov	byte ptr [rbx], 0
	mov	al, byte ptr [rbp-0x22]
	mov	byte ptr [rbx+0x1], al
	lea	rax, [__null+rip]
	mov	qword ptr [rbx+0x8], rax
	mov	eax, dword ptr [rbp-0x28]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

stokstr1:
	.byte  0x28, 0x00, 0x29, 0x00, 0x2A, 0x00, 0x2B, 0x00
	.byte  0x2C, 0x00, 0x2D, 0x00, 0x2E, 0x00, 0x2F, 0x00

stokstr2:
	.byte  0x5B, 0x00, 0x00, 0x00, 0x5D, 0x00

__equ:
	.byte  0x3D, 0x00

__dcolon:
	.byte  0x3A, 0x3A, 0x00

__amp:
	.byte  0x26, 0x00

__percent:
	.byte  0x25, 0x00

__quest:
	.byte  0x3F, 0x00

__null:
	.byte  0x00

DS0000:
	.byte  0x3D, 0x21, 0x3C, 0x3E, 0x26, 0x7C, 0x00


.att_syntax prefix
