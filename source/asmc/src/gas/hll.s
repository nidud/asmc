
.intel_syntax noprefix

.global GetLabelStr
.global ExpandCStrings
.global ExpandHllProc
.global ExpandHllProcEx
.global EvaluateHllExpression
.global ExpandHllExpression
.global HllStartDir
.global HllEndDir
.global HllContinueIf
.global HllExitDir
.global HllCheckOpen
.global HllInit

.extern CurrProc
.extern NoLineStore
.extern GetStdAssume
.extern SearchNameInStruct
.extern GenerateCString
.extern ExpandLine
.extern GetResWName
.extern PopInputStatus
.extern PushInputStatus
.extern Tokenize
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern LstWrite
.extern GetCurrOffset
.extern EmitConstError
.extern EvalOperand
.extern SizeFromRegister
.extern SizeFromMemtype
.extern SpecialTable
.extern LclDup
.extern LclAlloc
.extern tstrstr
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern tmemicmp
.extern tmemcpy
.extern tsprintf
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	mov	rdx, qword ptr [rcx+0x8]
	cmp	byte ptr [rcx], 9
	jne	$_017
	cmp	dword ptr [rcx+0x4], 2
	jnz	$_010
	movzx	eax, word ptr [rdx]
	jmp	$_008

$_002:	mov	eax, 1
	jmp	$_032

$_003:	mov	eax, 2
	jmp	$_032

$_004:	mov	eax, 5
	jmp	$_032

$_005:	mov	eax, 6
	jmp	$_032

$_006:	mov	eax, 7
	jmp	$_032

$_007:	mov	eax, 8
	jmp	$_032

	jmp	$_009

$_008:	cmp	eax, 15677
	jz	$_002
	cmp	eax, 15649
	jz	$_003
	cmp	eax, 15678
	jz	$_004
	cmp	eax, 15676
	jz	$_005
	cmp	eax, 9766
	jz	$_006
	cmp	eax, 31868
	jz	$_007
$_009:	jmp	$_016

$_010:	cmp	dword ptr [rcx+0x4], 1
	jnz	$_016
	movzx	eax, byte ptr [rdx]
	jmp	$_015

$_011:	mov	eax, 3
	jmp	$_032

$_012:	mov	eax, 4
	jmp	$_032

$_013:	mov	eax, 9
	jmp	$_032

$_014:	mov	eax, 10
	jmp	$_032

	jmp	$_016

$_015:	cmp	eax, 62
	jz	$_011
	cmp	eax, 60
	jz	$_012
	cmp	eax, 38
	jz	$_013
	cmp	eax, 33
	jz	$_014
$_016:	jmp	$_018

$_017:	cmp	byte ptr [rcx], 8
	jz	$_018
	xor	eax, eax
	jmp	$_032

$_018:	xor	eax, eax
$_019:	cmp	byte ptr [rdx+rax], 0
	jz	$_020
	inc	eax
	jmp	$_019

$_020:	cmp	byte ptr [rdx+rax-0x1], 63
	jne	$_031
	mov	ecx, dword ptr [rdx]
	and	ecx, 0xDFDFDFDF
	jmp	$_030

$_021:	cmp	ecx, 1330791770
	jnz	$_022
	mov	eax, 11
	jmp	$_032

$_022:	cmp	ecx, 1313294675
	jnz	$_023
	mov	eax, 13
	jmp	$_032

$_023:	jmp	$_031

$_024:	mov	al, byte ptr [rdx+0x4]
	and	eax, 0xFFFFFFDF
	cmp	eax, 89
	jnz	$_025
	cmp	ecx, 1381122371
	jnz	$_025
	mov	eax, 12
	jmp	$_032

$_025:	jmp	$_031

$_026:	mov	ax, word ptr [rdx+0x4]
	and	eax, 0xFFFFDFDF
	cmp	eax, 22868
	jnz	$_027
	cmp	ecx, 1230127440
	jnz	$_027
	mov	eax, 14
	jmp	$_032

$_027:	jmp	$_031

$_028:	mov	eax, dword ptr [rdx+0x4]
	and	eax, 0xDFDFDFDF
	cmp	eax, 1464814662
	jnz	$_029
	cmp	ecx, 1380275791
	jnz	$_029
	mov	eax, 15
	jmp	$_032

$_029:	jmp	$_031

$_030:	cmp	eax, 5
	je	$_021
	cmp	eax, 6
	jz	$_024
	cmp	eax, 7
	jz	$_026
	cmp	eax, 9
	jz	$_028
$_031:	xor	eax, eax
$_032:	ret

$_033:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 0
	mov	rdi, rcx
	mov	rbx, qword ptr [rbp+0x58]
	mov	ecx, dword ptr [rbp+0x48]
	cmp	ecx, -2
	jz	$_034
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jz	$_034
	imul	ecx, ecx, 24
	cmp	byte ptr [rbx+rcx], 9
	jnz	$_034
	mov	rax, qword ptr [rbx+rcx+0x8]
	cmp	word ptr [rax], 38
	jnz	$_034
	mov	eax, dword ptr [ModuleInfo+0x340+rip]
	mov	dword ptr [rbp-0x4], eax
	imul	edx, dword ptr [rbp+0x50], 24
	mov	rsi, qword ptr [rbx+rdx+0x10]
	mov	dl, byte ptr [rsi]
	mov	byte ptr [rbp-0x5], dl
	mov	byte ptr [rsi], 0
	mov	r9, qword ptr [rbx+rcx+0x28]
	mov	r8d, eax
	lea	rdx, [DS0000+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, rax
	mov	al, byte ptr [rbp-0x5]
	mov	byte ptr [rsi], al
$_034:	mov	r8d, dword ptr [rbp+0x30]
	lea	rdx, [DS0001+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, rax
	imul	ecx, dword ptr [rbp+0x40], 24
	imul	eax, dword ptr [rbp+0x38], 24
	mov	rcx, qword ptr [rbx+rcx+0x10]
	mov	rsi, qword ptr [rbx+rax+0x10]
	sub	rcx, rsi
	rep movsb
	mov	ecx, dword ptr [rbp+0x50]
	mov	eax, dword ptr [rbp+0x48]
	cmp	eax, -2
	jz	$_037
	cmp	dword ptr [rbp-0x4], 0
	jz	$_035
	mov	r8d, dword ptr [rbp-0x4]
	lea	rdx, [DS0002+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, rax
	jmp	$_036

$_035:
	mov	word ptr [rdi], 8236
	add	rdi, 2
	imul	ecx, ecx, 24
	imul	eax, eax, 24
	mov	rcx, qword ptr [rbx+rcx+0x10]
	mov	rsi, qword ptr [rbx+rax+0x10]
	sub	rcx, rsi
	rep movsb
$_036:	jmp	$_038

$_037:	cmp	ecx, -2
	jz	$_038
	mov	r8d, ecx
	lea	rdx, [DS0003+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, rax
$_038:
	mov	word ptr [rdi], 10
	lea	rax, [rdi+0x1]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

GetLabelStr:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	r8d, dword ptr [rbp+0x10]
	lea	rdx, [DS0004+rip]
	mov	rcx, qword ptr [rbp+0x18]
	call	tsprintf@PLT
	mov	rax, qword ptr [rbp+0x18]
	leave
	ret

$_039:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	mov	eax, 106
	stosb
	mov	ecx, dword ptr [rbp+0x28]
	test	ecx, ecx
	jz	$_040
	mov	eax, 110
	stosb
$_040:	mov	eax, dword ptr [rbp+0x20]
	stosb
	mov	eax, 32
	test	ecx, ecx
	jnz	$_041
	stosb
$_041:	stosb
	mov	r8d, dword ptr [rbp+0x30]
	lea	rdx, [DS0004+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	lea	rax, [rdi+rax+0x1]
	mov	word ptr [rax-0x1], 10
	leave
	pop	rdi
	ret

$_042:
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, rdx
	mov	edi, dword ptr [rsi]
	imul	ebx, edi, 24
	add	rbx, qword ptr [rbp+0x38]
$_043:	cmp	edi, dword ptr [ModuleInfo+0x220+rip]
	jge	$_044
	mov	rcx, rbx
	call	$_001
	test	rax, rax
	jnz	$_044
	add	rbx, 24
	inc	edi
	jmp	$_043

$_044:
	cmp	edi, dword ptr [rsi]
	jnz	$_045
	mov	rax, qword ptr [rbp+0x40]
	mov	dword ptr [rax+0x3C], -2
	mov	eax, 0
	jmp	$_046

$_045:	mov	byte ptr [rsp+0x20], 0
	mov	r9, qword ptr [rbp+0x40]
	mov	r8d, edi
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, rsi
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_046
	mov	eax, 0
	cmp	dword ptr [rsi], edi
	jbe	$_046
	mov	ecx, 2154
	call	asmerr@PLT
$_046:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_047:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 328
	mov	rsi, rdx
	mov	edi, dword ptr [rsi]
	imul	ebx, edi, 24
	add	rbx, qword ptr [rbp+0x38]
	mov	rax, qword ptr [rbx+0x8]
$_048:	cmp	word ptr [rax], 33
	jnz	$_049
	inc	edi
	add	rbx, 24
	mov	eax, 1
	sub	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rbp+0x48], eax
	mov	rax, qword ptr [rbx+0x8]
	jmp	$_048

$_049:
	mov	dword ptr [rsi], edi
	cmp	byte ptr [rbx], 40
	jne	$_057
	mov	edi, 1
	add	rbx, 24
	mov	al, byte ptr [rbx]
$_050:	test	al, al
	jz	$_054
	cmp	al, 40
	jnz	$_051
	inc	edi
	jmp	$_053

$_051:	cmp	al, 41
	jnz	$_052
	dec	edi
	jz	$_054
	jmp	$_053

$_052:	mov	rcx, rbx
	call	$_001
	test	rax, rax
	jnz	$_054
$_053:	add	rbx, 24
	mov	al, byte ptr [rbx]
	jmp	$_050

$_054:	test	edi, edi
	jz	$_057
	inc	dword ptr [rsi]
	mov	rax, qword ptr [rbp+0x58]
	mov	qword ptr [rsp+0x30], rax
	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	$_128
	cmp	eax, -1
	jnz	$_055
	jmp	$_107

$_055:	imul	ebx, dword ptr [rsi], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 41
	jz	$_056
	mov	ecx, 2154
	call	asmerr@PLT
	jmp	$_107

$_056:	inc	dword ptr [rsi]
	xor	eax, eax
	jmp	$_107

$_057:	mov	edi, dword ptr [rsi]
	mov	rbx, qword ptr [rbp+0x38]
	mov	byte ptr [rbp-0x1], 0
	mov	dword ptr [rbp-0x8], 588
	mov	dword ptr [rbp-0xC], edi
	lea	r9, [rbp-0x78]
	mov	r8, rbx
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	$_042
	cmp	eax, -1
	jnz	$_058
	jmp	$_107

$_058:	cmp	dword ptr [rbp-0x3C], 2
	jnz	$_060
	test	byte ptr [rbp-0x35], 0x01
	jnz	$_060
	mov	rax, qword ptr [rbp-0x60]
	test	rax, rax
	jz	$_060
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rax+0x4], 12
	test	byte ptr [r11+rax], 0x70
	jz	$_060
	mov	eax, 999
	cmp	byte ptr [ModuleInfo+0x351+rip], 4
	jnz	$_059
	mov	eax, 1000
$_059:	mov	dword ptr [rbp-0x8], eax
	inc	byte ptr [rbp-0x1]
$_060:	mov	edi, dword ptr [rsi]
	mov	dword ptr [rbp-0x7C], edi
	imul	eax, edi, 24
	add	rax, rbx
	mov	rcx, rax
	call	$_001
	cmp	rax, 7
	jz	$_061
	cmp	eax, 8
	jnz	$_062
$_061:	mov	eax, 0
	jmp	$_063

$_062:	test	eax, eax
	jz	$_063
	inc	edi
	mov	dword ptr [rsi], edi
$_063:	mov	dword ptr [rbp-0x80], eax
	mov	edx, dword ptr [rbp+0x40]
	mov	rax, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rax+rdx*4+0x10]
	mov	dword ptr [rbp-0x84], eax
	mov	edx, dword ptr [rbp-0x80]
	cmp	edx, 11
	jc	$_068
	cmp	dword ptr [rbp-0x3C], -2
	jz	$_064
	mov	ecx, 2154
	call	asmerr@PLT
	jmp	$_107

$_064:	mov	rcx, qword ptr [rbp+0x58]
	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rcx], rax
	lea	rcx, [flaginstr+rip]
	movzx	ecx, byte ptr [rcx+rdx-0xB]
	mov	edx, dword ptr [rbp+0x48]
	xor	edx, 0x01
	mov	dword ptr [rbp-0x88], ecx
	mov	dword ptr [rbp-0x8C], edx
	lea	eax, [rdi+0x1]
	cmp	eax, dword ptr [ModuleInfo+0x220+rip]
	jge	$_067
	cmp	dword ptr [rbp-0x80], 11
	jz	$_065
	cmp	dword ptr [rbp-0x80], 12
	jnz	$_067
$_065:	imul	eax, eax, 24
	add	rax, rbx
	mov	rcx, rax
	call	$_001
	mov	ecx, dword ptr [rbp-0x88]
	mov	edx, dword ptr [rbp-0x8C]
	cmp	eax, 11
	jz	$_066
	cmp	eax, 12
	jnz	$_067
$_066:	mov	ecx, 97
	xor	edx, 0x01
	add	edi, 2
	mov	dword ptr [rsi], edi
$_067:	mov	r9d, dword ptr [rbp-0x84]
	mov	r8d, edx
	mov	edx, ecx
	mov	rcx, qword ptr [rbp+0x50]
	call	$_039
	xor	eax, eax
	jmp	$_107

$_068:	mov	eax, dword ptr [rbp-0x3C]
	jmp	$_071

$_069:	mov	ecx, 2154
	call	asmerr@PLT
	jmp	$_107

$_070:	mov	ecx, 2050
	call	asmerr@PLT
	jmp	$_107

	jmp	$_072

$_071:	cmp	eax, -2
	jz	$_069
	cmp	eax, 3
	jz	$_070
$_072:	cmp	dword ptr [rbp-0x80], 0
	jne	$_084
	jmp	$_082

$_073:	test	byte ptr [rbp-0x35], 0x01
	jnz	$_075
	cmp	byte ptr [rbp-0x1], 0
	jnz	$_075
	mov	edx, 737
	cmp	byte ptr [Options+0x98+rip], 0
	jz	$_074
	mov	edx, 582
$_074:	mov	qword ptr [rsp+0x30], rbx
	mov	eax, dword ptr [rbp-0x7C]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x7C]
	mov	r8d, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_033
	mov	rdx, qword ptr [rbp+0x58]
	mov	qword ptr [rdx], rax
	mov	r9d, dword ptr [rbp-0x84]
	mov	r8d, dword ptr [rbp+0x48]
	mov	edx, 122
	mov	rcx, rax
	call	$_039
	jmp	$_083

$_075:	mov	qword ptr [rsp+0x30], rbx
	mov	dword ptr [rsp+0x28], 0
	mov	dword ptr [rsp+0x20], -2
	mov	r9d, dword ptr [rbp-0x7C]
	mov	r8d, dword ptr [rbp-0xC]
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_033
	mov	rdx, qword ptr [rbp+0x58]
	mov	qword ptr [rdx], rax
	mov	r9d, dword ptr [rbp-0x84]
	mov	r8d, dword ptr [rbp+0x48]
	mov	edx, 122
	mov	rcx, rax
	call	$_039
	jmp	$_083

$_076:	cmp	dword ptr [rbp-0x74], 0
	jz	$_077
	cmp	dword ptr [rbp-0x74], -1
	jz	$_077
	lea	rcx, [rbp-0x78]
	call	EmitConstError@PLT
	jmp	$_107

$_077:	mov	rcx, qword ptr [rbp+0x58]
	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rcx], rax
	mov	edx, dword ptr [rbp+0x48]
	xor	edx, 0x01
	cmp	dword ptr [rbp+0x48], 0
	jz	$_078
	cmp	dword ptr [rbp-0x78], 0
	jnz	$_079
$_078:	test	edx, edx
	jz	$_080
	cmp	dword ptr [rbp-0x78], 0
	jnz	$_080
$_079:	lea	r9, [EOLSTR+rip]
	mov	r8d, dword ptr [rbp-0x84]
	lea	rdx, [DS0005+rip]
	mov	rcx, qword ptr [rbp+0x50]
	call	tsprintf@PLT
	jmp	$_081

$_080:	mov	byte ptr [rax], 0
$_081:	jmp	$_083

$_082:	cmp	eax, 2
	je	$_073
	cmp	eax, 1
	je	$_075
	cmp	eax, 0
	jz	$_076
$_083:	xor	eax, eax
	jmp	$_107

$_084:	mov	edi, dword ptr [rsi]
	mov	dword ptr [rbp-0x90], edi
	imul	eax, edi, 24
	cmp	byte ptr [rbx+rax], 9
	jnz	$_085
	mov	rax, qword ptr [rbx+rax+0x8]
	cmp	word ptr [rax], 38
	jnz	$_085
	inc	dword ptr [rsi]
$_085:	lea	r9, [rbp-0xF8]
	mov	r8, rbx
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	$_042
	cmp	eax, -1
	je	$_107
	mov	eax, dword ptr [rbp-0xBC]
	test	eax, eax
	jz	$_091
	cmp	eax, 1
	jz	$_091
	cmp	eax, 2
	jz	$_091
	cmp	eax, 3
	jnz	$_089
	cmp	byte ptr [rbp-0x1], 0
	jz	$_086
	mov	dword ptr [rbp-0xBC], 1
	jmp	$_088

$_086:	cmp	dword ptr [rbp-0x3C], 1
	jnz	$_088
	cmp	byte ptr [rbp-0x38], 35
	jnz	$_087
	mov	dword ptr [rbp-0x8], 1000
	jmp	$_088

$_087:	cmp	byte ptr [rbp-0x38], 39
	jnz	$_088
	mov	dword ptr [rbp-0x8], 999
$_088:	jmp	$_090

$_089:	mov	ecx, 2154
	call	asmerr@PLT
	jmp	$_107

$_090:	jmp	$_093

$_091:	cmp	eax, 1
	jnz	$_093
	cmp	byte ptr [rbp-0x1], 0
	jz	$_093
	cmp	byte ptr [rbp-0xB8], 35
	jnz	$_092
	mov	dword ptr [rbp-0x8], 1000
	jmp	$_093

$_092:	cmp	byte ptr [rbp-0xB8], 39
	jnz	$_093
	mov	dword ptr [rbp-0x8], 999
$_093:	mov	edi, dword ptr [rsi]
	mov	dword ptr [rbp-0xFC], edi
	mov	ecx, dword ptr [rbp-0x80]
	cmp	ecx, 9
	jnz	$_095
	mov	edx, 737
	cmp	byte ptr [Options+0x98+rip], 0
	jz	$_094
	mov	edx, 582
$_094:	mov	qword ptr [rsp+0x30], rbx
	mov	eax, dword ptr [rbp-0xFC]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x7C]
	mov	r8d, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_033
	mov	rcx, qword ptr [rbp+0x58]
	mov	qword ptr [rcx], rax
	mov	r9d, dword ptr [rbp-0x84]
	mov	r8d, dword ptr [rbp+0x48]
	mov	edx, 101
	mov	rcx, rax
	call	$_039
	jmp	$_106

$_095:	cmp	ecx, 6
	ja	$_105
	cmp	dword ptr [rbp-0xF8], 0
	jnz	$_098
	cmp	dword ptr [rbp-0xF4], 0
	jnz	$_098
	cmp	ecx, 1
	jz	$_096
	cmp	ecx, 2
	jnz	$_098
$_096:	cmp	dword ptr [rbp-0x3C], 2
	jnz	$_098
	test	byte ptr [rbp-0x35], 0x01
	jnz	$_098
	cmp	dword ptr [rbp-0xBC], 0
	jnz	$_098
	cmp	byte ptr [rbp-0x1], 0
	jnz	$_098
	mov	edx, 737
	cmp	byte ptr [Options+0x98+rip], 0
	jz	$_097
	mov	edx, 582
$_097:	mov	qword ptr [rsp+0x30], rbx
	mov	eax, dword ptr [rbp-0x7C]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x7C]
	mov	r8d, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_033
	jmp	$_099

$_098:	mov	qword ptr [rsp+0x30], rbx
	mov	eax, dword ptr [rbp-0xFC]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp-0x7C]
	mov	r8d, dword ptr [rbp-0xC]
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_033
$_099:	mov	rbx, qword ptr [rbp+0x58]
	mov	qword ptr [rbx], rax
	mov	rdx, qword ptr [rbp+0x28]
	xor	edi, edi
	mov	ecx, dword ptr [rdx+0x2C]
	test	ecx, 0x80000
	jz	$_100
	inc	edi
$_100:	mov	ecx, dword ptr [rbp-0x80]
	movzx	edx, byte ptr [rbp-0x38]
	movzx	eax, byte ptr [rbp-0xB8]
	and	edx, 0xC0
	and	eax, 0xC0
	test	edi, edi
	jnz	$_101
	cmp	edx, 64
	jz	$_101
	cmp	eax, 64
	jnz	$_102
$_101:	lea	rdi, [signed_cjmptype+rip]
	movzx	edx, byte ptr [rdi+rcx-0x1]
	jmp	$_103

$_102:	lea	rdi, [unsign_cjmptype+rip]
	movzx	edx, byte ptr [rdi+rcx-0x1]
$_103:	mov	eax, dword ptr [rbp+0x48]
	lea	rdi, [neg_cjmptype+rip]
	cmp	byte ptr [rdi+rcx-0x1], 0
	jnz	$_104
	xor	eax, 0x01
$_104:	mov	r9d, dword ptr [rbp-0x84]
	mov	r8d, eax
	mov	rcx, qword ptr [rbx]
	call	$_039
	jmp	$_106

$_105:	mov	ecx, 2154
	call	asmerr@PLT
	jmp	$_107

$_106:	xor	eax, eax
$_107:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_108:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [rcx], 0
	jnz	$_109
	lea	rdx, [DS0006+rip]
	call	tstrcpy@PLT
	jmp	$_110

$_109:	inc	rcx
	mov	eax, dword ptr [rcx]
	jmp	$_112
$C008B:
	mov	byte ptr [rcx+0x1], al
	mov	byte ptr [rcx], 110
$_110:	leave
	ret
$C0091:
	mov	byte ptr [rcx], ah
	mov	byte ptr [rcx+0x1], 32
	leave
	ret
$C0092: mov	byte ptr [rcx], 98
	jmp	$_113
$C0094: mov	byte ptr [rcx], 97
	jmp	$_113
$C0095: mov	byte ptr [rcx], 108
	jmp	$_113
$C0096: mov	byte ptr [rcx], 103
	jmp	$_113
$C0097: cmp	al, 109
	jnz	$_111
	dec	rcx
	mov	byte ptr [rcx], 0
$_111:	leave
	ret

$_112:	cmp	al, 97
	jl	$C0097
	cmp	al, 122
	jg	$C0097
	push	rax
	movsx	rax, al
	lea	r11, [$C0097+rip]
	movzx	eax, byte ptr [r11+rax-(97)+(IT$C0099-$C0097)]
	movzx	eax, byte ptr [r11+rax+($C0099-$C0097)]
	sub	r11, rax
	pop	rax
	jmp	r11
$C0099:
	.byte $C0097-$C008B
	.byte $C0097-$C0091
	.byte $C0097-$C0092
	.byte $C0097-$C0094
	.byte $C0097-$C0095
	.byte $C0097-$C0096
	.byte 0
IT$C0099:
	.byte 2
	.byte 3
	.byte 0
	.byte 6
	.byte 0
	.byte 6
	.byte 4
	.byte 6
	.byte 6
	.byte 6
	.byte 6
	.byte 5
	.byte 6
	.byte 1
	.byte 0
	.byte 0
	.byte 6
	.byte 6
	.byte 0
	.byte 6
	.byte 6
	.byte 6
	.byte 6
	.byte 6
	.byte 6
	.byte 0

$_113:	cmp	ah, 101
	jnz	$_114
	mov	byte ptr [rcx+0x1], 32
	jmp	$_115
$_114:	mov	byte ptr [rcx+0x1], 101
$_115:	leave
	ret

$_116:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rbx, rcx
	lea	rsi, [rbp-0x10]
	lea	rdi, [rbp-0x20]
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp+0x30]
	call	GetLabelStr
	mov	rdx, rdi
	mov	ecx, dword ptr [rbp+0x38]
	call	GetLabelStr
	mov	rcx, rdi
	call	tstrlen@PLT
	mov	ebx, eax
	mov	rax, qword ptr [rbp+0x28]
	jmp	$_118

$_117:	mov	r8d, ebx
	mov	rdx, rdi
	mov	rcx, rax
	call	tmemcpy@PLT
	add	rax, rbx
$_118:	mov	rdx, rsi
	mov	rcx, rax
	call	tstrstr@PLT
	test	rax, rax
	jnz	$_117
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_119:
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
	mov	rdi, qword ptr [rbp+0x58]
	mov	rsi, qword ptr [rbp+0x50]
	mov	dword ptr [rbp-0x4], 0
$_120:	mov	qword ptr [rsp+0x30], rdi
	mov	qword ptr [rsp+0x28], rsi
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_047
	cmp	eax, -1
	je	$_127
	mov	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbx]
	imul	eax, eax, 24
	add	rax, qword ptr [rbp+0x38]
	mov	rcx, rax
	call	$_001
	cmp	rax, 7
	jne	$_125
	inc	dword ptr [rbx]
	mov	rbx, qword ptr [rdi]
	test	rbx, rbx
	je	$_124
	cmp	dword ptr [rbp+0x48], 0
	je	$_124
	mov	rcx, rbx
	call	$_108
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_121
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rbp-0x4], eax
$_121:	cmp	byte ptr [rbx], 0
	jz	$_122
	lea	rdx, [rbx+0x4]
	mov	ecx, dword ptr [rbp-0x4]
	call	GetLabelStr
	lea	rdx, [EOLSTR+rip]
	mov	rcx, rax
	call	tstrcat@PLT
$_122:	mov	rbx, rsi
	cmp	dword ptr [rdi+0x8], 0
	jz	$_123
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rdi+0x8]
	mov	rcx, rbx
	call	$_116
$_123:	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rbp-0x8], eax
	mov	edx, dword ptr [rbp+0x40]
	mov	rax, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rax+rdx*4+0x10]
	mov	dword ptr [rbp-0xC], eax
	mov	rcx, rbx
	call	tstrlen@PLT
	add	rbx, rax
	lea	rdx, [rbp-0x1C]
	mov	ecx, dword ptr [rbp-0xC]
	call	GetLabelStr
	mov	rcx, rax
	lea	rax, [EOLSTR+rip]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [DS0008+rip]
	mov	r8, rcx
	lea	rdx, [DS0007+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	mov	r8d, dword ptr [rbp-0x8]
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_116
	mov	qword ptr [rdi], 0
$_124:	mov	rcx, rsi
	call	tstrlen@PLT
	add	rsi, rax
	mov	dword ptr [rdi+0x8], 0
	jmp	$_120

$_125:	cmp	dword ptr [rbp-0x4], 0
	jz	$_126
	mov	rcx, rsi
	call	tstrlen@PLT
	add	rsi, rax
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	GetLabelStr
	lea	rdx, [DS0008+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	lea	rdx, [EOLSTR+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	qword ptr [rdi], 0
$_126:	mov	eax, 0
$_127:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_128:
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
	mov	rsi, qword ptr [rbp+0x50]
	mov	rdi, qword ptr [rbp+0x58]
	mov	dword ptr [rbp-0x4], 0
$_129:	mov	qword ptr [rsp+0x30], rdi
	mov	qword ptr [rsp+0x28], rsi
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_119
	cmp	eax, -1
	je	$_138
	mov	rbx, qword ptr [rbp+0x30]
	imul	eax, dword ptr [rbx], 24
	add	rax, qword ptr [rbp+0x38]
	mov	rcx, rax
	call	$_001
	cmp	rax, 8
	jne	$_135
	inc	dword ptr [rbx]
	mov	rbx, qword ptr [rdi]
	test	rbx, rbx
	je	$_134
	cmp	dword ptr [rbp+0x48], 0
	jne	$_134
	mov	rcx, rbx
	call	$_108
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_130
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rbp-0x4], eax
$_130:	cmp	byte ptr [rbx], 0
	jz	$_131
	lea	rdx, [rbx+0x4]
	mov	ecx, dword ptr [rbp-0x4]
	call	GetLabelStr
	lea	rdx, [EOLSTR+rip]
	mov	rcx, rax
	call	tstrcat@PLT
$_131:	mov	rbx, rsi
	cmp	dword ptr [rdi+0x8], 0
	jz	$_132
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rdi+0x8]
	mov	rcx, rbx
	call	$_116
$_132:	mov	qword ptr [rdi], 0
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rbp-0x8], eax
	mov	edx, dword ptr [rbp+0x40]
	mov	rax, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rax+rdx*4+0x10]
	mov	dword ptr [rbp-0xC], eax
	mov	rcx, rbx
	call	tstrlen@PLT
	add	rbx, rax
	mov	rax, qword ptr [rbp+0x28]
	cmp	dword ptr [rax+0x28], 2
	jnz	$_133
	mov	r8d, dword ptr [rbp-0x8]
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_116
	lea	rdx, [rbp-0x1C]
	mov	ecx, dword ptr [rbp-0x8]
	call	GetLabelStr
	mov	rcx, rax
	lea	rax, [EOLSTR+rip]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [DS0008+rip]
	mov	r8, rcx
	lea	rdx, [DS0007+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	jmp	$_134

$_133:	lea	rdx, [rbp-0x1C]
	mov	ecx, dword ptr [rbp-0xC]
	call	GetLabelStr
	mov	rcx, rax
	lea	rax, [EOLSTR+rip]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [DS0008+rip]
	mov	r8, rcx
	lea	rdx, [DS0007+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	mov	r8d, dword ptr [rbp-0x8]
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x50]
	call	$_116
$_134:	mov	rcx, rsi
	call	tstrlen@PLT
	add	rsi, rax
	mov	dword ptr [rdi+0x8], 0
	jmp	$_129

$_135:	cmp	dword ptr [rbp-0x4], 0
	jz	$_137
	mov	rbx, qword ptr [rdi]
	test	rbx, rbx
	jz	$_136
	cmp	dword ptr [rdi+0x8], 0
	jz	$_136
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rdi+0x8]
	mov	rcx, rsi
	call	$_116
	mov	edx, 10
	mov	rcx, rbx
	call	tstrchr@PLT
	mov	byte ptr [rax+0x1], 0
$_136:	mov	rcx, rsi
	call	tstrlen@PLT
	add	rsi, rax
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp-0x4]
	call	GetLabelStr
	lea	rdx, [DS0008+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	lea	rdx, [EOLSTR+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rdi+0x8], eax
$_137:	mov	eax, 0
$_138:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ExpandCStrings:
	mov	qword ptr [rsp+0x8], rcx
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	xor	eax, eax
	test	byte ptr [rcx+0x2], 0x40
	je	$_156
	cmp	byte ptr [Options+0xC6+rip], 1
	je	$_156
	xor	edi, edi
	mov	rbx, rcx
$_139:	cmp	byte ptr [rbx], 0
	je	$_156
	test	byte ptr [rbx+0x2], 0x08
	je	$_155
	mov	rdx, qword ptr [rbp+0x20]
	mov	ecx, edi
	call	GenerateCString@PLT
	test	rax, rax
	jne	$_156
	cmp	byte ptr [rbx], 8
	jnz	$_140
	cmp	byte ptr [rbx+0x18], 91
	jnz	$_140
	add	rbx, 24
	inc	edi
$_140:	cmp	byte ptr [rbx], 91
	jnz	$_145
	mov	eax, 1
$_141:	add	rbx, 24
	cmp	byte ptr [rbx], 93
	jnz	$_142
	dec	eax
	jz	$_144
	jmp	$_143

$_142:	cmp	byte ptr [rbx], 91
	jnz	$_143
	inc	eax
$_143:	cmp	byte ptr [rbx], 0
	jnz	$_141
$_144:	add	rbx, 24
	cmp	byte ptr [rbx], 46
	jnz	$_145
	add	rbx, 24
$_145:	jmp	$_147

$_146:	add	rbx, 48
$_147:	cmp	byte ptr [rbx+0x18], 46
	jz	$_146
	mov	ecx, 1
	add	rbx, 48
	cmp	byte ptr [rbx-0x18], 40
	jz	$_148
	mov	r8, qword ptr [rbx-0x10]
	mov	rdx, qword ptr [rbx-0x28]
	mov	ecx, 3018
	call	asmerr@PLT
	jmp	$_156

$_148:	cmp	byte ptr [rbx], 0
	jz	$_154
	mov	rdx, qword ptr [rbx+0x8]
	movzx	eax, byte ptr [rdx]
	jmp	$_152

$_149:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2004
	call	asmerr@PLT
	jmp	$_156

$_150:	dec	ecx
	jz	$_154
	jmp	$_153

$_151:	inc	ecx
	jmp	$_153

$_152:	cmp	eax, 34
	jz	$_149
	cmp	eax, 41
	jz	$_150
	cmp	eax, 40
	jz	$_151
$_153:	add	rbx, 24
	jmp	$_148

$_154:	xor	eax, eax
	jmp	$_156

$_155:	add	rbx, 24
	inc	edi
	jmp	$_139

$_156:
	leave
	pop	rbx
	pop	rdi
	ret

$_157:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	xor	eax, eax
	cmp	byte ptr [rcx+0x19], -60
	jnz	$_158
	cmp	qword ptr [rcx+0x20], 0
	jz	$_158
	mov	rcx, qword ptr [rcx+0x20]
$_158:	cmp	qword ptr [rcx+0x40], 0
	jz	$_160
	cmp	byte ptr [rcx+0x19], -61
	jz	$_159
	cmp	byte ptr [rcx+0x3A], -60
	jnz	$_160
$_159:	mov	rcx, qword ptr [rcx+0x40]
$_160:	test	byte ptr [rcx+0x16], 0x02
	jz	$_161
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rcx, qword ptr [rcx+0x30]
	call	SearchNameInStruct@PLT
$_161:	leave
	ret

$_162:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 91
	jnz	$_167
	mov	ecx, dword ptr [rbp+0x28]
$_163:	cmp	byte ptr [rbx], 0
	jz	$_164
	cmp	byte ptr [rbx], 93
	jz	$_164
	add	rbx, 24
	inc	ecx
	jmp	$_163

$_164:	add	ecx, 3
	add	rbx, 48
	cmp	byte ptr [rbx+0x18], 46
	jz	$_165
	xor	eax, eax
	jmp	$_176

$_165:	mov	byte ptr [rsp+0x20], 0
	mov	r9, qword ptr [rbp+0x38]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_166
	xor	eax, eax
	jmp	$_176

$_166:	mov	rcx, qword ptr [rbp+0x38]
	mov	rax, qword ptr [rcx+0x60]
	jmp	$_169

$_167:	cmp	byte ptr [rbx], 2
	jnz	$_168
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	movzx	ecx, byte ptr [r11+rax+0xA]
	call	GetStdAssume@PLT
	jmp	$_169

$_168:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
$_169:	test	rax, rax
	je	$_176
	test	byte ptr [rax+0x15], 0x08
	jne	$_176
	cmp	byte ptr [rbx], 8
	jnz	$_170
	cmp	byte ptr [rbx+0x18], 46
	jnz	$_170
	cmp	byte ptr [rbx+0x30], 8
	jnz	$_170
	mov	rdx, qword ptr [rbx+0x38]
	mov	rcx, rax
	call	$_157
	jmp	$_176

$_170:	mov	rcx, qword ptr [rax+0x40]
	mov	dl, byte ptr [rax+0x19]
	cmp	dl, -61
	jnz	$_171
	test	rcx, rcx
	jz	$_171
	test	byte ptr [rcx+0x15], 0x08
	jz	$_171
	mov	rax, rcx
	jmp	$_176

$_171:	cmp	dl, -61
	jnz	$_172
	test	rcx, rcx
	jz	$_172
	cmp	byte ptr [rcx+0x19], -128
	jnz	$_172
	mov	rax, qword ptr [rax+0x40]
	jmp	$_174

$_172:	mov	rcx, qword ptr [rax+0x20]
	cmp	dl, -60
	jnz	$_174
	cmp	byte ptr [rcx+0x19], -61
	jz	$_173
	cmp	byte ptr [rcx+0x19], -128
	jnz	$_174
$_173:	mov	rax, rcx
	cmp	byte ptr [rax+0x19], -128
	jz	$_174
	jmp	$_175

$_174:	cmp	byte ptr [rax+0x19], -128
	jz	$_175
	xor	eax, eax
	jmp	$_176

$_175:	mov	rax, qword ptr [rax+0x40]
$_176:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_177:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, qword ptr [rdx+0x68]
	mov	rax, qword ptr [rsi+0x8]
	test	rax, rax
	jnz	$_178
	jmp	$_190

$_178:	xor	edi, edi
	jmp	$_180

$_179:	mov	rax, qword ptr [rax+0x78]
	inc	edi
$_180:	cmp	qword ptr [rax+0x78], 0
	jnz	$_179
	cmp	edi, ecx
	jnc	$_181
	xor	eax, eax
	jmp	$_190

$_181:	mov	bl, byte ptr [rdx+0x1A]
	cmp	bl, 3
	jz	$_182
	cmp	bl, 1
	jz	$_182
	cmp	bl, 2
	jz	$_182
	cmp	bl, 8
	jz	$_182
	cmp	bl, 7
	jnz	$_187
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	jz	$_187
$_182:	mov	rbx, rax
	jmp	$_186

$_183:	mov	rax, qword ptr [rsi+0x8]
$_184:	cmp	rbx, qword ptr [rax+0x78]
	jz	$_185
	mov	rax, qword ptr [rax+0x78]
	jmp	$_184

$_185:	mov	rbx, rax
	dec	ecx
$_186:	test	ecx, ecx
	jnz	$_183
	jmp	$_189

$_187:	mov	rax, qword ptr [rsi+0x8]
$_188:	test	ecx, ecx
	jz	$_189
	dec	ecx
	mov	rax, qword ptr [rax+0x78]
	jmp	$_188

$_189:	test	rax, rax
	jz	$_190
	cmp	byte ptr [rax+0x19], -60
	jnz	$_190
	mov	rax, qword ptr [rax+0x20]
$_190:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_191:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 656
	lea	r8, [rbp-0x268]
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp+0x20]
	call	$_162
	test	rax, rax
	je	$_206
	cmp	byte ptr [rax+0x18], 6
	jne	$_198
	mov	rsi, rax
	imul	ebx, dword ptr [rbp+0x20], 24
	add	rbx, qword ptr [rbp+0x28]
	cmp	byte ptr [rbx], 91
	jnz	$_192
	mov	rcx, qword ptr [rbp-0x208]
	jmp	$_194

$_192:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	je	$_206
	xor	ecx, ecx
	cmp	byte ptr [rax+0x19], -60
	jnz	$_193
	mov	rcx, qword ptr [rax+0x20]
	jmp	$_194

$_193:	cmp	byte ptr [rax+0x19], -61
	jnz	$_194
	mov	rcx, qword ptr [rax+0x40]
$_194:	test	rcx, rcx
	jz	$_195
	cmp	word ptr [rcx+0x5A], 1
	jz	$_196
$_195:	xor	eax, eax
	jmp	$_206

$_196:	mov	rdx, qword ptr [rcx+0x8]
	lea	rcx, [rbp-0x200]
	call	tstrcpy@PLT
	lea	rdx, [DS0009+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	je	$_206
	cmp	byte ptr [rax+0x18], 10
	jnz	$_197
	mov	rcx, qword ptr [rax+0x28]
	call	SymFind@PLT
	test	rax, rax
	je	$_206
$_197:	or	byte ptr [rsi+0x16], 0x08
	mov	qword ptr [rsi+0x30], rax
	mov	rcx, rax
	xor	eax, eax
	jmp	$_200

$_198:	mov	rcx, qword ptr [rax+0x40]
	mov	rdx, rax
	xor	eax, eax
	cmp	byte ptr [rdx+0x18], 2
	jz	$_199
	cmp	byte ptr [rdx+0x18], 5
	jnz	$_206
$_199:	test	rcx, rcx
	jz	$_206
$_200:	cmp	byte ptr [rcx+0x18], 9
	jnz	$_206
	mov	rcx, qword ptr [rcx+0x68]
	mov	rcx, qword ptr [rcx+0x10]
	test	rcx, rcx
	jz	$_206
	jmp	$_202

$_201:	mov	rcx, qword ptr [rcx]
$_202:	cmp	qword ptr [rcx], 0
	jnz	$_201
	lea	rcx, [rcx+0x9]
	mov	edx, dword ptr [rcx]
	cmp	edx, 1836344690
	jnz	$_206
	add	rcx, 4
	mov	dl, byte ptr [rcx]
$_203:	test	dl, dl
	jz	$_204
	cmp	dl, 60
	jz	$_204
	inc	rcx
	mov	dl, byte ptr [rcx]
	jmp	$_203

$_204:	cmp	dl, 60
	jnz	$_206
$_205:	inc	rcx
	mov	dl, byte ptr [rcx]
	cmp	dl, 32
	jz	$_205
	cmp	dl, 9
	jz	$_205
	test	dl, dl
	jz	$_206
	cmp	dl, 62
	jz	$_206
	mov	rax, rcx
$_206:	leave
	pop	rbx
	pop	rsi
	ret

$_207:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2248
	mov	qword ptr [rbp-0x8], 0
	mov	qword ptr [rbp-0x18], 0
	mov	dword ptr [rbp-0x1C], 0
	mov	dword ptr [rbp-0x8C], 0
	mov	dword ptr [rbp-0x90], 0
	lea	rdi, [rbp-0x890]
	mov	rbx, qword ptr [rbp+0x38]
	xor	edx, edx
$_208:	cmp	edx, dword ptr [rbp+0x28]
	jge	$_216
	test	edx, edx
	jz	$_215
	test	byte ptr [rbx+0x2], 0x08
	jz	$_209
	mov	qword ptr [rbp-0x18], rbx
	mov	dword ptr [rbp-0x1C], 0
$_209:	jmp	$_214

$_210:	dec	dword ptr [rbp-0x8C]
	jmp	$_215

$_211:	inc	dword ptr [rbp-0x8C]
	jmp	$_215

$_212:	cmp	qword ptr [rbp-0x18], 0
	jz	$_213
	inc	dword ptr [rbp-0x1C]
$_213:	jmp	$_215

$_214:	cmp	byte ptr [rbx], 41
	jz	$_210
	cmp	byte ptr [rbx], 40
	jz	$_211
	cmp	byte ptr [rbx], 44
	jz	$_212
$_215:	mov	rsi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, rsi
	rep movsb
	inc	edx
	add	rbx, 24
	jmp	$_208

$_216:
	mov	byte ptr [rdi], 0
	mov	rdi, qword ptr [rbp+0x38]
	xor	esi, esi
	cmp	dword ptr [rbp-0x8C], 0
	jnz	$_217
	mov	qword ptr [rbp-0x18], rsi
$_217:	mov	rdx, rdi
	mov	ecx, dword ptr [rbp+0x28]
	call	$_191
	test	rax, rax
	jz	$_218
	mov	qword ptr [rbp-0x8], rax
	jmp	$_272

$_218:	mov	rax, qword ptr [rbp-0x18]
	test	rax, rax
	je	$_238
	sub	rax, qword ptr [rbp+0x38]
	mov	ecx, 24
	xor	edx, edx
	div	ecx
	mov	ecx, eax
	lea	r8, [rbp-0x88]
	mov	rdx, qword ptr [rbp+0x38]
	call	$_162
	test	rax, rax
	je	$_238
	cmp	byte ptr [rax+0x19], -60
	jnz	$_219
	mov	rax, qword ptr [rax+0x20]
$_219:	mov	rdx, rax
	mov	ecx, dword ptr [rbp-0x1C]
	call	$_177
	mov	rcx, rax
	test	rcx, rcx
	je	$_238
	mov	eax, dword ptr [rcx+0x50]
	jmp	$_237

$_220:	mov	esi, 1
	jmp	$_238

$_221:	mov	esi, 9
	jmp	$_238

$_222:	mov	esi, 17
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_223
	test	byte ptr [rcx+0x19], 0x20
	jz	$_223
	mov	esi, 40
$_223:	jmp	$_238

$_224:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_227
	test	byte ptr [rcx+0x19], 0x20
	jz	$_225
	mov	esi, 40
	jmp	$_226

$_225:	mov	esi, 115
$_226:	jmp	$_229

$_227:	cmp	byte ptr [rbx-0x18], 13
	jnz	$_228
	mov	esi, 17
	jmp	$_229

$_228:	mov	esi, 19
	mov	dword ptr [rbp-0x90], 17
$_229:	jmp	$_238

$_230:	test	byte ptr [rcx+0x19], 0x20
	jz	$_231
	mov	esi, 40
	jmp	$_232

$_231:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_232
	mov	esi, 117
	mov	dword ptr [rbp-0x90], 115
$_232:	jmp	$_238

$_233:	cmp	byte ptr [rcx+0x19], 31
	jnz	$_234
	mov	esi, 48
$_234:	jmp	$_238

$_235:	cmp	byte ptr [rcx+0x19], 63
	jnz	$_236
	mov	esi, 64
$_236:	jmp	$_238

$_237:	cmp	eax, 1
	je	$_220
	cmp	eax, 2
	je	$_221
	cmp	eax, 4
	je	$_222
	cmp	eax, 8
	je	$_224
	cmp	eax, 16
	jz	$_230
	cmp	eax, 32
	jz	$_233
	cmp	eax, 64
	jz	$_235
$_238:	test	esi, esi
	jne	$_271
	mov	esi, 115
	mov	eax, dword ptr [rbp+0x28]
	cmp	qword ptr [rbp-0x18], 0
	jne	$_271
	cmp	eax, 1
	jbe	$_271
	imul	eax, eax, 24
	lea	rbx, [rdi+rax-0x30]
	cmp	byte ptr [rbx+0x18], 44
	jne	$_270
	cmp	byte ptr [rbx], 93
	je	$_270
	xor	eax, eax
	cmp	byte ptr [rbx], 2
	jnz	$_239
	mov	ecx, dword ptr [rbx+0x4]
	call	SizeFromRegister@PLT
	jmp	$_259

$_239:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_243
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_241
	cmp	byte ptr [rax+0x19], 35
	jz	$_240
	cmp	byte ptr [rax+0x19], 39
	jnz	$_241
$_240:	mov	eax, 16
	jmp	$_242

$_241:	mov	r8, qword ptr [rax+0x20]
	mov	edx, 254
	movzx	ecx, byte ptr [rax+0x19]
	call	SizeFromMemtype@PLT
$_242:	jmp	$_259

$_243:	cmp	byte ptr [rbx-0x18], 46
	jne	$_259
	mov	edx, dword ptr [rbp+0x28]
	sub	dword ptr [rbp+0x28], 4
	sub	rbx, 48
	cmp	byte ptr [rbx-0x18], 46
	jnz	$_244
	sub	rbx, 48
	sub	dword ptr [rbp+0x28], 2
$_244:	cmp	byte ptr [rbx], 93
	jnz	$_247
	jmp	$_246

$_245:	dec	dword ptr [rbp+0x28]
	sub	rbx, 24
$_246:	cmp	dword ptr [rbp+0x28], 0
	jz	$_247
	cmp	byte ptr [rbx], 91
	jnz	$_245
$_247:	cmp	dword ptr [rbx-0x14], 270
	jnz	$_248
	sub	rbx, 48
	sub	dword ptr [rbp+0x28], 2
$_248:	sub	edx, dword ptr [rbp+0x28]
	mov	byte ptr [rsp+0x20], 1
	lea	r9, [rbp-0x88]
	mov	r8d, edx
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_258
	xor	eax, eax
	cmp	dword ptr [rbp-0x4C], 1
	jz	$_249
	test	byte ptr [rbp-0x45], 0x01
	jz	$_257
$_249:	mov	cl, byte ptr [rbp-0x48]
	jmp	$_256

$_250:	mov	eax, 1
	jmp	$_257

$_251:	mov	eax, 2
	jmp	$_257

$_252:	mov	eax, 4
	jmp	$_257

$_253:	mov	eax, 16
	jmp	$_257

$_254:	mov	eax, 32
	jmp	$_257

$_255:	mov	eax, 64
	jmp	$_257

$_256:	cmp	cl, 0
	jz	$_250
	cmp	cl, 64
	jz	$_250
	cmp	cl, 1
	jz	$_251
	cmp	cl, 65
	jz	$_251
	cmp	cl, 3
	jz	$_252
	cmp	cl, 67
	jz	$_252
	cmp	cl, 15
	jz	$_253
	cmp	cl, 79
	jz	$_253
	cmp	cl, 33
	jz	$_253
	cmp	cl, 35
	jz	$_253
	cmp	cl, 39
	jz	$_253
	cmp	cl, 41
	jz	$_253
	cmp	cl, 47
	jz	$_253
	cmp	cl, 31
	jz	$_254
	cmp	cl, 63
	jz	$_255
$_257:	jmp	$_259

$_258:	xor	eax, eax
$_259:	test	eax, eax
	jz	$_269
	jmp	$_268

$_260:	mov	esi, 1
	jmp	$_269

$_261:	mov	esi, 9
	jmp	$_269

$_262:	mov	esi, 17
	jmp	$_269

$_263:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_264
	mov	esi, 115
$_264:	jmp	$_269

$_265:	mov	esi, 40
	jmp	$_269

$_266:	mov	esi, 48
	jmp	$_269

$_267:	mov	esi, 64
	jmp	$_269

$_268:	cmp	eax, 1
	jz	$_260
	cmp	eax, 2
	jz	$_261
	cmp	eax, 4
	jz	$_262
	cmp	eax, 8
	jz	$_263
	cmp	eax, 16
	jz	$_265
	cmp	eax, 32
	jz	$_266
	cmp	eax, 64
	jz	$_267
$_269:	jmp	$_271

$_270:	cmp	byte ptr [rbx+0x18], 44
	jnz	$_271
	cmp	byte ptr [rbx], 93
	jnz	$_271
	mov	edx, dword ptr [rbp+0x28]
	sub	dword ptr [rbp+0x28], 2
	jmp	$_244

$_271:	xor	edx, edx
	mov	ecx, esi
	call	GetResWName@PLT
	mov	rbx, rax
$_272:	lea	rsi, [rbp-0x890]
	lea	rdx, [DS0006+0x3+rip]
	mov	rcx, rsi
	call	tstrcat@PLT
	cmp	qword ptr [rbp-0x8], 0
	jz	$_275
	mov	rcx, rsi
	call	tstrlen@PLT
	lea	rdi, [rsi+rax]
	mov	rsi, qword ptr [rbp-0x8]
$_273:	lodsb
	mov	ah, byte ptr [rsi]
	test	al, al
	jz	$_274
	cmp	ax, 15393
	jz	$_273
	cmp	ax, 15905
	jz	$_273
	stosb
	jmp	$_273

$_274:	mov	byte ptr [rdi-0x1], al
	lea	rsi, [rbp-0x890]
	mov	rdi, qword ptr [rbp+0x38]
	jmp	$_276

$_275:	mov	rdx, rbx
	mov	rcx, rsi
	call	tstrcat@PLT
$_276:	cmp	dword ptr [rbp-0x90], 0
	jz	$_277
	lea	rdx, [DS000A+rip]
	mov	rcx, rsi
	call	tstrcat@PLT
	xor	edx, edx
	mov	ecx, dword ptr [rbp-0x90]
	call	GetResWName@PLT
	mov	rdx, rax
	mov	rcx, rsi
	call	tstrcat@PLT
$_277:	imul	ebx, dword ptr [rbp+0x30], 24
	cmp	byte ptr [rbx+rdi], 0
	jz	$_278
	lea	rdx, [DS0006+0x3+rip]
	mov	rcx, rsi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbx+rdi+0x10]
	mov	rcx, rsi
	call	tstrcat@PLT
$_278:	mov	rcx, rsi
	call	tstrlen@PLT
	lea	ecx, [eax+0x1]
	call	LclAlloc@PLT
	mov	rdx, rsi
	mov	rcx, rax
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, rdi
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	eax, 1
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_279:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2664
	mov	dword ptr [rbp-0x8D4], 0
	mov	qword ptr [rbp-0x9E0], 0
	mov	qword ptr [rbp-0x9E8], 0
	mov	qword ptr [rbp-0x9F0], 0
	mov	qword ptr [rbp-0xA00], 0
	mov	dword ptr [rbp-0xA04], 0
	mov	dword ptr [rbp-0xA08], 0
	mov	dword ptr [rbp-0xA0C], 0
	mov	dword ptr [rbp-0xA10], 0
	mov	dword ptr [rbp-0xA14], 0
	mov	qword ptr [rbp-0xA20], 0
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0xA24], eax
	mov	qword ptr [rbp-0xA30], 0
	imul	eax, dword ptr [rbp+0x30], 24
	add	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x878], rax
	mov	rbx, rax
$_280:	cmp	byte ptr [rbx], 0
	je	$_292
	cmp	byte ptr [rbx], 91
	jne	$_289
	inc	dword ptr [rbp-0xA10]
	add	rbx, 24
	inc	dword ptr [rbp-0xA24]
$_281:	cmp	dword ptr [rbp-0xA10], 0
	je	$_288
	cmp	byte ptr [rbx], 0
	je	$_288
	test	byte ptr [rbx+0x2], 0x08
	jz	$_282
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0xA24]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_279
	cmp	eax, -1
	je	$_372
	jmp	$_287

$_282:	cmp	byte ptr [rbx], 40
	jnz	$_283
	inc	dword ptr [rbp-0xA0C]
	jmp	$_287

$_283:	cmp	byte ptr [rbx], 41
	jnz	$_284
	dec	dword ptr [rbp-0xA0C]
	jmp	$_287

$_284:	cmp	dword ptr [rbp-0xA0C], 0
	jnz	$_285
	cmp	byte ptr [rbx], 91
	jnz	$_285
	inc	dword ptr [rbp-0xA10]
	jmp	$_287

$_285:	cmp	dword ptr [rbp-0xA0C], 0
	jnz	$_287
	cmp	byte ptr [rbx], 93
	jnz	$_287
	dec	dword ptr [rbp-0xA10]
	jnz	$_287
	cmp	qword ptr [rbp-0xA20], 0
	jnz	$_286
	mov	qword ptr [rbp-0xA20], rbx
$_286:	jmp	$_288

$_287:	add	rbx, 24
	inc	dword ptr [rbp-0xA24]
	jmp	$_281

$_288:	jmp	$_291

$_289:	cmp	byte ptr [rbx], 46
	jnz	$_290
	mov	eax, dword ptr [rbp-0xA14]
	mov	qword ptr [rbp+rax*8-0x8D0], rbx
	inc	dword ptr [rbp-0xA14]
	jmp	$_291

$_290:	cmp	byte ptr [rbx], 40
	jnz	$_291
	jmp	$_292

$_291:	add	rbx, 24
	inc	dword ptr [rbp-0xA24]
	jmp	$_280

$_292:	cmp	byte ptr [rbx], 40
	jz	$_293
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_372

$_293:	mov	qword ptr [rbp-0x880], rbx
	mov	rax, qword ptr [rbx-0x10]
	mov	qword ptr [rbp-0x870], rax
	mov	rbx, qword ptr [rbp-0x878]
	cmp	byte ptr [rbx], 91
	jne	$_299
	xor	eax, eax
	cmp	dword ptr [rbp-0xA14], 0
	je	$_298
	mov	rdx, qword ptr [rbp-0x8D0]
	cmp	dword ptr [rbp-0xA14], 1
	jle	$_294
	mov	rdi, qword ptr [rbp-0x870]
	mov	rcx, qword ptr [rdx+0x20]
	call	SymFind@PLT
	jmp	$_296

$_294:	cmp	byte ptr [rdx+0x30], 40
	jnz	$_296
	mov	rdi, qword ptr [rdx+0x20]
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0xA0C], eax
	mov	rax, qword ptr [rbp-0x8D0]
	sub	rax, qword ptr [rbp+0x38]
	mov	ecx, 24
	xor	edx, edx
	div	ecx
	mov	ecx, eax
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x68]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0xA0C]
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_295
	mov	rax, qword ptr [rbp-0x8]
	jmp	$_296

$_295:	xor	eax, eax
$_296:	test	rax, rax
	jz	$_298
	cmp	byte ptr [rax+0x18], 7
	jnz	$_297
	cmp	word ptr [rax+0x5A], 1
	jnz	$_297
	jmp	$_311

	jmp	$_298

$_297:	xor	eax, eax
$_298:	mov	rcx, rax
	jmp	$_317

$_299:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x9F8], rax
	mov	edi, dword ptr [rbp-0xA14]
	test	edi, edi
	jz	$_300
	dec	edi
$_300:	xor	esi, esi
$_301:	test	rax, rax
	jz	$_304
	test	edi, edi
	jz	$_304
	mov	rcx, rax
	cmp	byte ptr [rcx+0x19], -60
	jnz	$_302
	mov	rcx, qword ptr [rcx+0x20]
$_302:	cmp	byte ptr [rcx+0x19], -61
	jnz	$_303
	mov	rcx, qword ptr [rcx+0x40]
$_303:	test	rcx, rcx
	jz	$_304
	mov	rbx, qword ptr [rbp+rsi*8-0x8D0]
	add	rbx, 24
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbx+0x8]
	call	SearchNameInStruct@PLT
	mov	qword ptr [rbp-0xA30], rax
	inc	esi
	dec	edi
	jmp	$_301

$_304:	mov	qword ptr [rbp-0x9E0], rax
	xor	ecx, ecx
	cmp	qword ptr [rbp-0xA30], 0
	jz	$_306
	mov	rdx, qword ptr [rbp-0x9F8]
	cmp	rdx, rax
	jz	$_306
	cmp	byte ptr [rdx+0x19], -61
	jz	$_306
	cmp	dword ptr [rbp-0xA14], 2
	jnz	$_305
	mov	qword ptr [rbp-0xA30], 0
	jmp	$_306

$_305:	inc	dword ptr [rbp-0x8D4]
$_306:	cmp	dword ptr [rbp-0xA14], 0
	jz	$_307
	mov	rdi, qword ptr [rbp-0x870]
	jmp	$_309

$_307:	test	rax, rax
	jz	$_308
	cmp	byte ptr [rax+0x18], 7
	jnz	$_308
	cmp	byte ptr [rbx+0x18], 40
	jnz	$_308
	mov	rdi, qword ptr [rbx+0x8]
	mov	rcx, rax
	mov	qword ptr [rbp-0x9E8], rdi
	jmp	$_309

$_308:	xor	eax, eax
$_309:	mov	rbx, qword ptr [rbp-0x878]
	test	rax, rax
	je	$_317
	cmp	byte ptr [rax+0x19], -60
	jne	$_315
	cmp	qword ptr [rax+0x20], 0
	je	$_315
	mov	rax, qword ptr [rax+0x20]
	cmp	word ptr [rax+0x5A], 3
	jnz	$_310
	mov	rcx, qword ptr [rax+0x40]
	jmp	$_314

$_310:	cmp	word ptr [rax+0x5A], 1
	jnz	$_314
	inc	dword ptr [rbp-0x8D4]
$_311:	mov	qword ptr [rbp-0x9E0], rax
	mov	rcx, rax
	xor	eax, eax
	test	byte ptr [rcx+0x16], 0x02
	jz	$_312
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, qword ptr [rcx+0x30]
	call	SearchNameInStruct@PLT
$_312:	test	rax, rax
	jnz	$_313
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x9E0]
	call	SearchNameInStruct@PLT
	test	rax, rax
	jz	$_313
	mov	qword ptr [rbp-0x9F0], rax
	mov	qword ptr [rbp-0x9E0], 0
$_313:	mov	rcx, qword ptr [rbp-0x9E0]
$_314:	jmp	$_317

$_315:	cmp	byte ptr [rax+0x19], -61
	jnz	$_317
	cmp	byte ptr [rax+0x18], 5
	jz	$_316
	cmp	byte ptr [rax+0x18], 2
	jnz	$_317
$_316:	mov	rcx, qword ptr [rax+0x40]
$_317:	mov	qword ptr [rbp-0x870], rdi
	mov	rdx, rcx
	lea	rdi, [rbp-0x868]
	mov	eax, 1870032489
	stosd
	mov	eax, 2123115
	stosd
	dec	rdi
	test	rdx, rdx
	je	$_322
	cmp	byte ptr [rdx+0x18], 7
	jne	$_322
	cmp	word ptr [rdx+0x5A], 1
	jne	$_322
	mov	rsi, rdx
	mov	rax, qword ptr [rsi+0x8]
	mov	qword ptr [rbp-0xA00], rax
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp-0x870]
	mov	rcx, rsi
	call	SearchNameInStruct@PLT
	test	rax, rax
	jz	$_318
	mov	qword ptr [rbp-0x9F0], rax
$_318:	test	byte ptr [rsi+0x16], 0x02
	jz	$_319
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp-0x870]
	mov	rcx, qword ptr [rsi+0x30]
	call	SearchNameInStruct@PLT
	test	rax, rax
	jz	$_319
	inc	dword ptr [rbp-0xA08]
	mov	qword ptr [rbp-0x9F0], rax
	mov	rsi, qword ptr [rsi+0x30]
	mov	rax, qword ptr [rsi+0x8]
	mov	qword ptr [rbp-0xA00], rax
$_319:	cmp	qword ptr [rbp-0x9F0], 0
	jnz	$_321
	mov	rdx, qword ptr [rbp-0x870]
	mov	rcx, qword ptr [rsi+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_320
	inc	dword ptr [rbp-0xA08]
	inc	dword ptr [rbp-0xA04]
$_320:	jmp	$_322

$_321:	cmp	qword ptr [rbp-0xA30], 0
	jz	$_322
	mov	rax, qword ptr [rbp-0x9F0]
	or	byte ptr [rax+0x16], 0x40
$_322:	cmp	qword ptr [rbp-0xA00], 0
	je	$_343
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_328
	cmp	dword ptr [rbp-0xA04], 0
	jnz	$_328
	mov	rax, qword ptr [rbp-0x9F0]
	test	rax, rax
	jz	$_326
	cmp	byte ptr [rax+0x19], -60
	jnz	$_323
	cmp	qword ptr [rax+0x20], 0
	jz	$_323
	mov	rax, qword ptr [rax+0x20]
	cmp	word ptr [rax+0x5A], 3
	jnz	$_323
	mov	rax, qword ptr [rax+0x40]
$_323:	cmp	byte ptr [rax+0x1A], 2
	jnz	$_324
	mov	eax, 808546907
	jmp	$_325

$_324:	mov	eax, 2019652187
$_325:	jmp	$_327

$_326:	mov	eax, 2019652187
$_327:	jmp	$_329

$_328:	mov	eax, 2019648859
$_329:	cmp	dword ptr [rbp-0xA04], 0
	jnz	$_330
	stosd
	mov	eax, 11869
	stosw
$_330:	mov	rsi, qword ptr [rbp-0xA00]
	jmp	$_332

$_331:	movsb
$_332:	cmp	byte ptr [rsi], 0
	jnz	$_331
	cmp	qword ptr [rbp-0x9E8], 0
	jz	$_336
	mov	al, 46
	cmp	dword ptr [rbp-0xA04], 0
	jz	$_333
	mov	al, 95
$_333:	stosb
	mov	rsi, qword ptr [rbp-0x9E8]
	jmp	$_335

$_334:	movsb
$_335:	cmp	byte ptr [rsi], 0
	jnz	$_334
$_336:	cmp	byte ptr [rbx], 91
	jnz	$_340
	cmp	byte ptr [rbx+0x30], 93
	jnz	$_337
	mov	rax, qword ptr [rbx+0x20]
	jmp	$_339

$_337:	lea	rdx, [DS000B+rip]
	lea	rcx, [rbp-0x9D4]
	call	tstrcpy@PLT
	lea	rsi, [rbx+0x18]
$_338:	cmp	rsi, qword ptr [rbp-0xA20]
	jnc	$_339
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rax
	call	tstrcat@PLT
	add	rsi, 24
	jmp	$_338

$_339:	jmp	$_342

$_340:	cmp	dword ptr [rbp-0xA14], 0
	jz	$_341
	lea	rax, [rbp-0x9D4]
	mov	rsi, qword ptr [rbx+0x10]
	mov	rdx, qword ptr [rbp-0x880]
	sub	rdx, 48
	mov	rcx, qword ptr [rdx+0x10]
	sub	rcx, rsi
	mov	rdx, rdi
	mov	rdi, rax
	rep movsb
	mov	byte ptr [rdi], 0
	mov	rdi, rdx
	jmp	$_342

$_341:	mov	rax, qword ptr [rbx+0x8]
$_342:	mov	qword ptr [rbp-0xA00], rax
	mov	rax, qword ptr [rbp-0x9F0]
	test	rax, rax
	jz	$_343
	or	byte ptr [rax+0x15], 0xFFFFFF80
	cmp	dword ptr [rbp-0xA08], 0
	jnz	$_343
	or	byte ptr [rax+0x16], 0x40
$_343:	inc	dword ptr [rbp-0xA24]
	cmp	qword ptr [rbp-0xA00], 0
	jz	$_344
	mov	rbx, qword ptr [rbp-0x880]
	sub	rbx, 48
	cmp	rbx, qword ptr [rbp-0x878]
	ja	$_344
	add	rbx, 48
$_344:	mov	rsi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbp-0x880]
	lea	rbx, [rcx+0x18]
	mov	rcx, qword ptr [rcx+0x10]
	sub	rcx, rsi
	rep movsb
	mov	byte ptr [rdi], 0
	cmp	qword ptr [rbp-0x9E8], 0
	jz	$_345
	mov	eax, 3153964
	stosd
	dec	rdi
	jmp	$_350

$_345:	cmp	qword ptr [rbp-0xA00], 0
	jz	$_350
	cmp	dword ptr [rbp-0xA08], 0
	jz	$_350
	mov	eax, 8236
	stosw
	cmp	dword ptr [rbp-0x8D4], 0
	jz	$_346
	mov	eax, 1919181921
	stosd
	mov	eax, 32
	stosb
$_346:	mov	rsi, qword ptr [rbp-0xA00]
	jmp	$_349

$_347:	lodsb
	cmp	al, 46
	jnz	$_348
	cmp	qword ptr [rbp-0xA30], 0
	jz	$_348
	mov	dword ptr [rbp-0xA08], 0
	jmp	$_350

$_348:	stosb
$_349:	cmp	byte ptr [rsi], 0
	jnz	$_347
$_350:	mov	byte ptr [rdi], 0
	cmp	byte ptr [rbx], 41
	jnz	$_351
	inc	dword ptr [rbp-0xA24]
	lea	rsi, [rbp-0x868]
	jmp	$_360

$_351:	mov	eax, 8236
	stosw
	mov	dword ptr [rbp-0xA0C], 1
$_352:	cmp	byte ptr [rbx], 0
	je	$_359
	test	byte ptr [rbx+0x2], 0x08
	jz	$_353
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0xA24]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_279
	cmp	eax, -1
	je	$_372
$_353:	mov	al, byte ptr [rbx]
	cmp	al, 41
	jnz	$_354
	dec	dword ptr [rbp-0xA0C]
	jz	$_359
	jmp	$_355

$_354:	cmp	al, 40
	jnz	$_355
	inc	dword ptr [rbp-0xA0C]
$_355:	cmp	al, 38
	jnz	$_356
	lea	rsi, [DS000C+rip]
	mov	ecx, 5
	jmp	$_358

$_356:	cmp	al, 44
	jnz	$$357
	cmp	byte ptr [rbx+0x18], 41
	jnz	$$357
	cmp	dword ptr [rbp-0xA0C], 1
	jnz	$$357
	inc	dword ptr [rbp-0xA24]
	add	rbx, 24
	jmp	$_359

$$357:	cmp	al, 3
	jnz	$_357
	cmp	dword ptr [rbx+0x4], 423
	jnz	$_357
	add	rbx, 48
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_358
	cmp	byte ptr [rax+0x18], 5
	jnz	$_358
	test	byte ptr [rax+0x17], 0x01
	jz	$$360
	movzx	ecx, byte ptr [rax+0x48]
	xor	edx, edx
	call	GetResWName@PLT
	mov	rsi, rax
	xor	ecx, ecx
$$358:	cmp	byte ptr [rsi+rcx], 0
	jz	$_358
	inc	ecx
	jmp	$$358
$$360:	mov	rsi, qword ptr [rax+0x8]
	mov	ecx, dword ptr [rax+0x10]
	add	rbx, 24
	add	dword ptr [rbp-0xA24], 3
	jmp	$_358

$_357:	mov	rsi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, rsi
$_358:	rep movsb
	inc	dword ptr [rbp-0xA24]
	add	rbx, 24
	jmp	$_352

$_359:	inc	dword ptr [rbp-0xA24]
	mov	byte ptr [rdi], 0
$_360:	cmp	qword ptr [rbp-0xA00], 0
	jz	$_363
	cmp	dword ptr [rbp-0xA08], 0
	jnz	$_363
	mov	eax, 8236
	stosw
	mov	rsi, qword ptr [rbp-0xA00]
	jmp	$_362

$_361:	movsb
$_362:	cmp	byte ptr [rsi], 0
	jnz	$_361
	mov	byte ptr [rdi], 0
$_363:	mov	eax, dword ptr [rbp+0x30]
	lea	ecx, [rax+0x3]
	inc	eax
	cmp	qword ptr [rbp-0xA00], 0
	jne	$_370
	cmp	dword ptr [rbp-0xA24], eax
	jnz	$_364
	cmp	eax, 1
	ja	$_365
$_364:	cmp	dword ptr [rbp-0xA24], ecx
	jne	$_370
$_365:	xor	eax, eax
	mov	rcx, qword ptr [rbp-0x9E0]
	test	rcx, rcx
	jz	$_367
	cmp	byte ptr [rcx+0x18], 2
	jnz	$_367
	cmp	qword ptr [rcx+0x50], 0
	jz	$_366
	mov	rax, rcx
	jmp	$_367

$_366:	test	byte ptr [rcx+0x16], 0x10
	jz	$_367
	mov	rcx, qword ptr [rcx+0x40]
	test	rcx, rcx
	jz	$_367
	cmp	byte ptr [rcx+0x18], 9
	jnz	$_367
	mov	rax, rcx
$_367:	test	rax, rax
	jnz	$_370
	test	rcx, rcx
	jz	$_369
	cmp	byte ptr [rcx+0x1A], 7
	jz	$_368
	cmp	byte ptr [rcx+0x1A], 8
	jnz	$_369
$_368:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_369
	test	byte ptr [ModuleInfo+0x1E5+rip], 0x02
	jz	$_369
	mov	rdx, qword ptr [CurrProc+rip]
	test	rdx, rdx
	jz	$_369
	or	byte ptr [rdx+0x3B], 0x10
$_369:	lea	rdx, [rbp-0x868]
	mov	eax, 1819042147
	mov	dword ptr [rdx], eax
	mov	rcx, rdi
	lea	rdi, [rdx+0x4]
	lea	rsi, [rdx+0x6]
	sub	rcx, rsi
	inc	ecx
	rep movsb
$_370:	mov	rax, qword ptr [rbp+0x28]
	cmp	byte ptr [rax], 0
	jz	$_371
	lea	rdx, [EOLSTR+rip]
	mov	rcx, rax
	call	tstrcat@PLT
$_371:	lea	rdx, [rbp-0x868]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcat@PLT
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0xA24]
	mov	ecx, dword ptr [rbp+0x30]
	call	$_207
$_372:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_373:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	al, byte ptr [ModuleInfo+0x1C6+rip]
	mov	byte ptr [rbp-0x1], al
	mov	r8, qword ptr [rbp+0x20]
	mov	edx, dword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	$_279
	mov	cl, byte ptr [rbp-0x1]
	mov	byte ptr [ModuleInfo+0x1C6+rip], cl
	leave
	ret

ExpandHllProc:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	dword ptr [rbp-0x4], 0
	mov	rax, qword ptr [rbp+0x20]
	mov	byte ptr [rax], 0
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_377
	mov	esi, dword ptr [rbp+0x28]
	mov	edi, esi
	imul	edi, edi, 24
	add	rdi, qword ptr [rbp+0x30]
	jmp	$_376

$_374:	test	byte ptr [rdi+0x2], 0x08
	jz	$_375
	mov	rcx, qword ptr [rbp+0x30]
	call	ExpandCStrings
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, esi
	mov	rcx, qword ptr [rbp+0x20]
	call	$_373
	mov	dword ptr [rbp-0x4], eax
$_375:	add	rdi, 24
	add	esi, 1
$_376:	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jl	$_374
$_377:	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rdi
	pop	rsi
	ret

ExpandHllProcEx:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp+0x20]
	call	ExpandHllProc
	mov	dword ptr [rbp-0x4], eax
	cmp	eax, -1
	jz	$_378
	mov	rsi, qword ptr [rbp+0x20]
	cmp	byte ptr [rsi], 0
	jz	$_378
	lea	rdx, [DS0000+0xA+rip]
	mov	rcx, rsi
	call	tstrcat@PLT
	mov	rbx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rsi
	call	tstrcat@PLT
	mov	rcx, rsi
	call	AddLineQueue@PLT
	mov	dword ptr [rbp-0x4], 1
$_378:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_379
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_379:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_380
	call	RunLineQueue@PLT
$_380:	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rdi
	pop	rsi
	ret

EvaluateHllExpression:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2136
	mov	rsi, rdx
	mov	rbx, r8
	mov	qword ptr [rbp-0x10], 0
	mov	dword ptr [rbp-0x8], 0
	mov	rdx, rcx
	mov	eax, dword ptr [rdx+0x2C]
	and	eax, 0x08
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_385
	test	eax, eax
	jnz	$_385
	test	byte ptr [rbx+0x2], 0x01
	jz	$_385
	mov	edi, dword ptr [rsi]
	jmp	$_384

$_381:	imul	eax, edi, 24
	test	byte ptr [rbx+rax+0x2], 0x04
	jz	$_383
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbp+0x50]
	call	tstrcpy@PLT
	mov	rax, qword ptr [rbp+0x28]
	or	byte ptr [rax+0x2C], 0x08
	test	byte ptr [rbx+0x2], 0x02
	jz	$_382
	or	byte ptr [rax+0x2C], 0x20
$_382:	xor	eax, eax
	jmp	$_405

$_383:	add	edi, 1
$_384:	cmp	edi, dword ptr [ModuleInfo+0x220+rip]
	jl	$_381
$_385:	lea	rdi, [rbp-0x810]
	mov	r8, rbx
	mov	edx, dword ptr [rsi]
	mov	rcx, rdi
	call	ExpandHllProc
	cmp	eax, -1
	je	$_405
	mov	rcx, qword ptr [rbp+0x50]
	mov	byte ptr [rcx], 0
	lea	rax, [rbp-0x10]
	mov	qword ptr [rsp+0x30], rax
	mov	qword ptr [rsp+0x28], rcx
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, rbx
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	$_128
	cmp	eax, -1
	je	$_405
	mov	eax, dword ptr [rsi]
	imul	eax, eax, 24
	add	rbx, rax
	cmp	byte ptr [rbx], 0
	jz	$_386
	mov	ecx, 2154
	call	asmerr@PLT
	jmp	$_405

$_386:	mov	rax, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rax+0x2C]
	and	eax, 0x70000
	test	eax, eax
	je	$_403
	cmp	byte ptr [rdi], 0
	je	$_403
	mov	rdx, qword ptr [rbp+0x50]
	mov	ecx, dword ptr [rdx]
	jmp	$_388

$_387:	add	rdx, 1
$_388:	cmp	byte ptr [rdx], 32
	ja	$_387
	jmp	$_390

$_389:	add	rdx, 1
$_390:	cmp	byte ptr [rdx], 32
	jz	$_389
	mov	ebx, dword ptr [rdx]
	cmp	bl, 101
	jz	$_391
	cmp	bl, 114
	jnz	$_392
$_391:	shr	ebx, 8
$_392:	cmp	bh, 120
	jnz	$_403
	cmp	ecx, 1953719668
	jnz	$_393
	xor	ecx, ecx
$_393:	lea	rbx, [rdx+0x4]
	jmp	$_395

$_394:	inc	rbx
$_395:	cmp	byte ptr [rbx], 32
	jz	$_394
	cmp	byte ptr [rbx], 44
	jz	$_394
	jmp	$_402

$_396:	mov	ax, word ptr [rdx]
	mov	byte ptr [rdx], 101
	test	ecx, ecx
	jnz	$_397
	cmp	ax, word ptr [rbx]
	jnz	$_397
	mov	byte ptr [rbx], 101
$_397:	jmp	$_403

$_398:	mov	ax, word ptr [rdx]
	mov	byte ptr [rdx], 32
	test	ecx, ecx
	jnz	$_399
	cmp	ax, word ptr [rbx]
	jnz	$_399
	mov	byte ptr [rbx], 32
$_399:	jmp	$_403

$_400:	mov	ax, word ptr [rdx]
	mov	byte ptr [rdx], 32
	mov	byte ptr [rdx+0x2], 108
	test	ecx, ecx
	jnz	$_401
	cmp	ax, word ptr [rbx]
	jnz	$_401
	mov	byte ptr [rbx], 32
	mov	byte ptr [rbx+0x2], 108
$_401:	jmp	$_403

$_402:	cmp	eax, 262144
	jz	$_396
	cmp	eax, 131072
	jz	$_398
	cmp	eax, 65536
	jz	$_400
$_403:	cmp	byte ptr [rdi], 0
	jz	$_404
	mov	rcx, rdi
	call	tstrlen@PLT
	mov	word ptr [rdi+rax], 10
	mov	rdx, qword ptr [rbp+0x50]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp+0x50]
	call	tstrcpy@PLT
$_404:	mov	eax, 0
$_405:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ExpandHllExpression:
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
	mov	dword ptr [rbp-0x4], 0
	mov	byte ptr [rbp-0x29], 0
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x30], eax
	mov	rsi, rcx
	mov	rbx, r8
	mov	rdi, qword ptr [rbp+0x50]
	test	byte ptr [rsi+0x2C], 0x04
	jz	$_406
	mov	rdi, qword ptr [rsi+0x20]
	inc	byte ptr [rbp-0x29]
	jmp	$_408

$_406:	test	byte ptr [rsi+0x2C], 0x20
	jz	$_407
	inc	byte ptr [rbp-0x29]
	jmp	$_408

$_407:	mov	rcx, qword ptr [rbp+0x30]
	imul	edx, dword ptr [rcx], 24
	cmp	byte ptr [rbx+rdx-0x18], 3
	jnz	$_408
	cmp	dword ptr [rbx+rdx-0x14], 321
	jnz	$_408
	inc	byte ptr [rbp-0x29]
$_408:	lea	rcx, [rbp-0x28]
	call	PushInputStatus@PLT
	mov	rbx, rax
	mov	rdx, rdi
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_411
	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_409
	call	RunLineQueue@PLT
$_409:	cmp	byte ptr [rbp-0x29], 0
	jz	$_410
	mov	dword ptr [NoLineStore+rip], 1
	mov	rdx, rbx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	ExpandLine@PLT
	mov	dword ptr [NoLineStore+rip], 0
	test	eax, eax
	jne	$_415
$_410:	and	dword ptr [rsi+0x2C], 0xFFFFFFFB
	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, rbx
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp+0x28]
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	mov	rcx, qword ptr [rbp+0x50]
	call	AddLineQueue@PLT
	jmp	$_414

$_411:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_412
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_412:	call	RunLineQueue@PLT
	mov	rdx, rbx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	ExpandLine@PLT
	mov	dword ptr [rbp-0x4], eax
	test	eax, eax
	jnz	$_414
	test	byte ptr [rsi+0x2C], 0x04
	jz	$_413
	and	dword ptr [rsi+0x2C], 0xFFFFFFFB
$_413:	mov	rax, qword ptr [rbp+0x50]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, rbx
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rsi
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	mov	rcx, qword ptr [rbp+0x50]
	call	AddLineQueue@PLT
$_414:	lea	rcx, [rbp-0x28]
	call	PopInputStatus@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x38]
	xor	edx, edx
	mov	rcx, qword ptr [rbx+0x10]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rax, qword ptr [rbp+0x28]
	and	dword ptr [rax+0x2C], 0xFFFFFFF7
	mov	eax, dword ptr [rbp-0x4]
$_415:	leave
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
	sub	rsp, 40
	mov	rsi, qword ptr [rbp+0x28]
	mov	edi, 1
	xor	ebx, ebx
	mov	eax, dword ptr [rsi]
	jmp	$_426

$_417:	cmp	al, 10
	jnz	$_418
	mov	edi, 1
	add	ebx, edi
	jmp	$_425

$_418:	test	edi, edi
	jz	$_425
	xor	edi, edi
	cmp	al, 106
	jnz	$_425
	shr	eax, 8
	cmp	al, 109
	jnz	$_419
	test	ebx, ebx
	jnz	$_419
	mov	edi, 2
	jmp	$_422

$_419:	cmp	ebx, 1
	jnz	$_421
	cmp	al, 122
	jz	$_420
	cmp	ax, 31342
	jnz	$_421
$_420:	mov	edi, 3
	jmp	$_422

$_421:	mov	ebx, 3
	jmp	$_427

$_422:	mov	rcx, rsi
	call	tstrlen@PLT
	jmp	$_424

$_423:	add	rsi, rax
	mov	cl, byte ptr [rsi]
	mov	byte ptr [rsi+rdi], cl
	sub	rsi, rax
	dec	eax
$_424:	cmp	eax, 0
	jge	$_423
	xor	edi, edi
	mov	eax, 1886351212
	mov	dword ptr [rsi], eax
	cmp	edx, 2
	jnz	$_425
	mov	byte ptr [rsi+0x4], 101
$_425:	inc	rsi
	mov	eax, dword ptr [rsi]
$_426:	test	al, al
	jnz	$_417
$_427:	mov	eax, 0
	cmp	ebx, 2
	jbe	$_428
	mov	eax, 4294967295
$_428:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_429:
	mov	qword ptr [rsp+0x8], rcx
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	eax, edx
	mov	ecx, 1
	add	ecx, 115
	mov	r8d, ecx
	mov	edx, 676
	lea	rcx, [DS000D+rip]
	call	AddLineQueueX@PLT
	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, dword ptr [rdx+0x18]
	lea	rdx, [rbp-0x20]
	call	GetLabelStr
	mov	rdx, rax
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
	leave
	pop	rdi
	ret

$_430:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 64
	mov	eax, ecx
	xor	ecx, ecx
	jmp	$_431
$C0230: mov	ecx, 536
	jmp	$_432
$C0234: mov	ecx, 534
	jmp	$_432
$C0238: mov	ecx, 542
	jmp	$_432
$C023B: mov	ecx, 540
	jmp	$_432
$C023E: mov	ecx, 553
	jmp	$_432
$C0241: mov	ecx, 554
	jmp	$_432
$C0244: mov	ecx, 555
	jmp	$_432
$C0247: mov	ecx, 548
	jmp	$_432
$C024A: mov	ecx, 533
	jmp	$_432
$C024D: mov	ecx, 535
	jmp	$_432
$C0251: mov	ecx, 539
	jmp	$_432
$C0254: mov	ecx, 541
	jmp	$_432
$C0257: mov	ecx, 557
	jmp	$_432
$C025A: mov	ecx, 558
	jmp	$_432
$C025D: mov	ecx, 561
	jmp	$_432
$C0260: mov	ecx, 562
	jmp	$_432
$C0263: mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_432
$_431:	cmp	eax, 326
	jl	$C0263
	cmp	eax, 388
	jg	$C0263
	lea	r11, [$C0263+rip]
	movzx	eax, byte ptr [r11+rax-(326)+(IT$C0264-$C0263)]
	movzx	eax, byte ptr [r11+rax+($C0264-$C0263)]
	sub	r11, rax
	jmp	r11
$C0264:
	.byte $C0263-$C0230
	.byte $C0263-$C0234
	.byte $C0263-$C0238
	.byte $C0263-$C023B
	.byte $C0263-$C023E
	.byte $C0263-$C0241
	.byte $C0263-$C0244
	.byte $C0263-$C0247
	.byte $C0263-$C024A
	.byte $C0263-$C024D
	.byte $C0263-$C0251
	.byte $C0263-$C0254
	.byte $C0263-$C0257
	.byte $C0263-$C025A
	.byte $C0263-$C025D
	.byte $C0263-$C0260
	.byte 0
IT$C0264:
	.byte 0
	.byte 2
	.byte 3
	.byte 4
	.byte 5
	.byte 7
	.byte 8
	.byte 9
	.byte 9
	.byte 10
	.byte 11
	.byte 12
	.byte 13
	.byte 14
	.byte 15
	.byte 1
	.byte 1
	.byte 6
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 0
	.byte 2
	.byte 3
	.byte 4
	.byte 5
	.byte 7
	.byte 8
	.byte 9
	.byte 10
	.byte 11
	.byte 12
	.byte 13
	.byte 14
	.byte 15
	.byte 1
	.byte 6
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 16
	.byte 0
	.byte 2
	.byte 3
	.byte 4
	.byte 5
	.byte 7
	.byte 8
	.byte 9
	.byte 10
	.byte 11
	.byte 12
	.byte 13
	.byte 14
	.byte 15
	.byte 1
	.byte 6
$_432:	lea	rdx, [rbp-0x20]
	call	GetResWName@PLT
	cmp	byte ptr [rax+0x2], 0
	jnz	$_433
	mov	word ptr [rax+0x2], 32
$_433:	leave
	ret

HllStartDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2136
	mov	dword ptr [rbp-0x4], 0
	mov	rbx, rdx
	lea	rdi, [rbp-0x818]
	imul	eax, dword ptr [rbp+0x28], 24
	movzx	ecx, byte ptr [rbx+rax+0x18]
	mov	dword ptr [rbp-0x81C], ecx
	mov	eax, dword ptr [rbx+rax+0x4]
	mov	dword ptr [rbp-0x8], eax
	inc	dword ptr [rbp+0x28]
	mov	rsi, qword ptr [ModuleInfo+0x100+rip]
	test	rsi, rsi
	jnz	$_434
	mov	ecx, 56
	call	LclAlloc@PLT
	mov	rsi, rax
$_434:	mov	rcx, qword ptr [rbp+0x30]
	call	ExpandCStrings
	xor	eax, eax
	mov	dword ptr [rsi+0x14], eax
	mov	dword ptr [rsi+0x2C], eax
	mov	eax, dword ptr [rbp-0x8]
	mov	ecx, dword ptr [rbp-0x81C]
	jmp	$_459

$C0268: # T_DOT_IF

$_435:	mov	dword ptr [rsi+0x28], 0
	mov	dword ptr [rsi+0x18], 0
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x10], eax
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 0
	xor	r9d, r9d
	mov	r8, rbx
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	test	eax, eax
	jnz	$_436
	mov	rcx, rdi
	call	AddLineQueue@PLT
	cmp	byte ptr [rdi], 0
	jnz	$_436
	mov	dword ptr [rsi+0x10], 0
$_436:	jmp	$C026B

$C026C: # T_DOT_WHILE

$_437:	or	byte ptr [rsi+0x2C], 0x04

$C026D: # T_DOT_REPEAT

	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x18], eax
	mov	dword ptr [rsi+0x10], 0
	cmp	dword ptr [rbp-0x8], 316
	je	$_452
	mov	dword ptr [rsi+0x28], 1
	mov	qword ptr [rsi+0x20], 0
	imul	eax, dword ptr [rbp+0x28], 24
	cmp	byte ptr [rbx+rax], 0
	je	$_447
	mov	ecx, dword ptr [rsi+0x2C]
	mov	eax, dword ptr [rbp-0x8]
	jmp	$_445

$_438:	or	ecx, 0x80000
$_439:	or	ecx, 0x10000
	jmp	$_446

$_440:	or	ecx, 0x80000
$_441:	or	ecx, 0x20000
	jmp	$_446

$_442:	or	ecx, 0x80000
$_443:	or	ecx, 0x40000
	jmp	$_446

$_444:	or	ecx, 0x80000
	jmp	$_446

$_445:	cmp	eax, 370
	jz	$_438
	cmp	eax, 366
	jz	$_439
	cmp	eax, 371
	jz	$_440
	cmp	eax, 368
	jz	$_441
	cmp	eax, 372
	jz	$_442
	cmp	eax, 369
	jz	$_443
	cmp	eax, 367
	jz	$_444
$_446:	mov	dword ptr [rsi+0x2C], ecx
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 1
	mov	r9d, 2
	mov	r8, rbx
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	jmp	$_449

$_447:	cmp	dword ptr [rbp-0x8], 317
	jz	$_448
	lea	rdx, [rdi+0x14]
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr
	mov	ecx, dword ptr [rbp-0x8]
	call	$_430
	mov	rdx, rax
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdx, [DS000C+0x4+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [rdi+0x14]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	$_108
	mov	eax, 0
	jmp	$_449

$_448:	mov	byte ptr [rdi], 0
	mov	eax, 4294967295
$_449:	test	eax, eax
	jnz	$_450
	mov	rcx, rdi
	call	LclDup@PLT
	mov	qword ptr [rsi+0x20], rax
$_450:	mov	r8d, 3
	lea	rdx, [DS000F+rip]
	mov	rcx, rdi
	call	tmemicmp@PLT
	test	eax, eax
	jz	$_451
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x10], eax
	lea	rdx, [rbp-0x18]
	mov	ecx, dword ptr [rsi+0x10]
	call	GetLabelStr
	mov	rdx, rax
	lea	rcx, [DS0010+rip]
	call	AddLineQueueX@PLT
$_451:	jmp	$_453

$_452:	mov	dword ptr [rsi+0x28], 2
$_453:	mov	cl, byte ptr [ModuleInfo+0x335+rip]
	test	cl, cl
	jz	$_454
	mov	eax, 1
	shl	eax, cl
	mov	edx, eax
	lea	rcx, [DS0011+rip]
	call	AddLineQueueX@PLT
$_454:	lea	rdx, [rbp-0x18]
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr
	lea	r8, [DS000A+0x1+rip]
	mov	rdx, rax
	lea	rcx, [DS0007+0x2+rip]
	call	AddLineQueueX@PLT
	jmp	$C026B

$C027F: # T_DOT_IFS

	test	ecx, ecx
	jz	$_455
	or	byte ptr [rsi+0x2E], 0x08
	jmp	$_435

$C0281: # T_DOT_IFB / T_DOT_IFC

$_455:	test	ecx, ecx
	jz	$_456
	or	byte ptr [rsi+0x2E], 0x01
	jmp	$_435

$_456:	mov	dword ptr [rsi+0x28], 0
	mov	dword ptr [rsi+0x18], 0
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x10], eax
	lea	rdx, [rbp-0x18]
	mov	ecx, dword ptr [rsi+0x10]
	call	GetLabelStr
	mov	ecx, dword ptr [rbp-0x8]
	call	$_430
	test	rax, rax
	jz	$_457
	mov	rdx, rax
	lea	rcx, [rbp-0x818]
	call	tstrcpy@PLT
	lea	rdx, [DS000C+0x4+rip]
	mov	rcx, rax
	call	tstrcat@PLT
	lea	rcx, [rbp-0x18]
	mov	rdx, rcx
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rcx, rax
	call	AddLineQueue@PLT
$_457:	jmp	$C026B

$C0286: # T_DOT_IFSD

	or	byte ptr [rsi+0x2E], 0x08

$C0287: # T_DOT_IFD

	or	byte ptr [rsi+0x2E], 0x04
	jmp	$_435

$C0288: # T_DOT_IFSW

	or	byte ptr [rsi+0x2E], 0x08

$C0289: # T_DOT_IFW

	or	byte ptr [rsi+0x2E], 0x02
	jmp	$_435

$C028A: # T_DOT_IFSB

	or	byte ptr [rsi+0x2E], 0x09
	jmp	$_435

$_458:	jmp	$_437

$_459:	cmp	eax, 326
	jc	$_460
	cmp	eax, 340
	jbe	$_456
$_460:	cmp	eax, 352
	jc	$_461
	cmp	eax, 372
	jbe	$_458
$_461:	cmp	eax, 315
	jl	$C026B
	cmp	eax, 348
	jg	$C026B
	push	rax
	lea	r11, [$C026B+rip]
	movzx	eax, byte ptr [r11+rax-(315)+(IT$C028E-$C026B)]
	movzx	eax, word ptr [r11+rax*2+($C028E-$C026B)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C028E:
	.word $C026B-$C0268
	.word $C026B-$C026C
	.word $C026B-$C026D
	.word $C026B-$C027F
	.word $C026B-$C0281
	.word $C026B-$C0286
	.word $C026B-$C0287
	.word $C026B-$C0288
	.word $C026B-$C0289
	.word $C026B-$C028A
	.word 0
IT$C028E:
	.byte 0
	.byte 2
	.byte 1
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 10
	.byte 4
	.byte 4
	.byte 3
	.byte 8
	.byte 6
	.byte 9
	.byte 7
	.byte 5
	.ALIGN 2

$C026B: imul	eax, dword ptr [rbp+0x28], 24
	cmp	dword ptr [rsi+0x2C], 0
	jnz	$C028F
	cmp	byte ptr [rbx+rax], 0
	jz	$C028F
	cmp	dword ptr [rbp-0x4], 0
	jnz	$C028F
	mov	rdx, qword ptr [rbx+rax+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], eax
$C028F:
	cmp	rsi, qword ptr [ModuleInfo+0x100+rip]
	jnz	$C0290
	mov	rax, qword ptr [rsi]
	mov	qword ptr [ModuleInfo+0x100+rip], rax
$C0290:
	mov	rax, qword ptr [ModuleInfo+0xF8+rip]
	mov	qword ptr [rsi], rax
	mov	qword ptr [ModuleInfo+0xF8+rip], rsi
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$C0291
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$C0291:
	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$C0292
	call	RunLineQueue@PLT
$C0292:
	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

HllEndDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2104
	mov	dword ptr [rbp-0x4], 0
	mov	rsi, qword ptr [ModuleInfo+0xF8+rip]
	test	rsi, rsi
	jnz	$_462
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_505

$_462:	mov	rax, qword ptr [rsi]
	mov	rcx, qword ptr [ModuleInfo+0x100+rip]
	mov	qword ptr [ModuleInfo+0xF8+rip], rax
	mov	qword ptr [rsi], rcx
	mov	qword ptr [ModuleInfo+0x100+rip], rsi
	lea	rdi, [rbp-0x808]
	mov	rbx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rsi+0x28]
	imul	edx, dword ptr [rbp+0x28], 24
	mov	eax, dword ptr [rbx+rdx+0x4]
	mov	dword ptr [rbp-0x8], eax
	jmp	$_498

$_463:	test	ecx, ecx
	jz	$_464
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_505

$_464:	inc	dword ptr [rbp+0x28]
	mov	eax, dword ptr [rsi+0x10]
	test	eax, eax
	jz	$_465
	mov	rdx, rdi
	mov	ecx, eax
	call	GetLabelStr
	lea	r8, [DS000A+0x1+rip]
	mov	rdx, rax
	lea	rcx, [DS0007+0x2+rip]
	call	AddLineQueueX@PLT
$_465:	jmp	$_500

$_466:	cmp	ecx, 1
	jz	$_467
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_505

$_467:	mov	eax, dword ptr [rsi+0x10]
	test	eax, eax
	jz	$_468
	mov	rdx, rdi
	mov	ecx, eax
	call	GetLabelStr
	lea	r8, [DS000A+0x1+rip]
	mov	rdx, rax
	lea	rcx, [DS0007+0x2+rip]
	call	AddLineQueueX@PLT
$_468:	inc	dword ptr [rbp+0x28]
	test	byte ptr [rsi+0x2C], 0x08
	jz	$_469
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 1
	mov	r9d, 2
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	ExpandHllExpression
	jmp	$_470

$_469:	mov	rcx, qword ptr [rsi+0x20]
	call	AddLineQueue@PLT
$_470:	jmp	$_500

$_471:	cmp	ecx, 2
	jz	$_472
	mov	rdx, qword ptr [rbx+rdx+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	jmp	$_505

$_472:	inc	dword ptr [rbp+0x28]
	lea	rbx, [rbx+rdx+0x18]
	mov	eax, dword ptr [rsi+0x10]
	test	eax, eax
	jz	$_473
	mov	rdx, rdi
	mov	ecx, eax
	call	GetLabelStr
	lea	r8, [DS000A+0x1+rip]
	mov	rdx, rax
	lea	rcx, [DS0007+0x2+rip]
	call	AddLineQueueX@PLT
$_473:	cmp	byte ptr [rbx], 0
	je	$_480
	mov	ecx, 2
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_475
	cmp	dword ptr [rsi+0x14], 0
	jnz	$_474
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_474:	mov	ecx, 1
$_475:	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, ecx
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	test	eax, eax
	jnz	$_479
	cmp	byte ptr [ModuleInfo+0x337+rip], 1
	jnz	$_476
	cmp	dword ptr [rbp-0x8], 325
	jnz	$_476
	mov	rcx, rdi
	call	$_416
	mov	dword ptr [rbp-0x4], eax
$_476:	test	eax, eax
	jnz	$_478
	mov	rcx, rdi
	call	AddLineQueue@PLT
	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jnz	$_477
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, rsi
	call	$_429
$_477:	jmp	$_479

$_478:	mov	ecx, 2062
	call	asmerr@PLT
$_479:	jmp	$_482

$_480:	cmp	byte ptr [ModuleInfo+0x337+rip], 1
	jnz	$_481
	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr
	mov	rdx, rax
	lea	rcx, [DS0012+rip]
	call	AddLineQueueX@PLT
	jmp	$_482

$_481:	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, rsi
	call	$_429
$_482:	jmp	$_500

$_483:	cmp	ecx, 2
	jz	$_484
	mov	rdx, qword ptr [rbx+rdx+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	jmp	$_505

$_484:	inc	dword ptr [rbp+0x28]
	lea	rbx, [rbx+rdx+0x18]
	mov	eax, dword ptr [rsi+0x10]
	test	eax, eax
	jz	$_485
	mov	rdx, rdi
	mov	ecx, eax
	call	GetLabelStr
	lea	r8, [DS000A+0x1+rip]
	mov	rdx, rax
	lea	rcx, [DS0007+0x2+rip]
	call	AddLineQueueX@PLT
$_485:	cmp	byte ptr [rbx], 0
	je	$_496
	mov	ecx, dword ptr [rsi+0x2C]
	mov	eax, dword ptr [rbp-0x8]
	jmp	$_493

$_486:	or	ecx, 0x80000
$_487:	or	ecx, 0x10000
	jmp	$_494

$_488:	or	ecx, 0x80000
$_489:	or	ecx, 0x20000
	jmp	$_494

$_490:	or	ecx, 0x80000
$_491:	or	ecx, 0x40000
	jmp	$_494

$_492:	or	ecx, 0x80000
	jmp	$_494

$_493:	cmp	eax, 391
	jz	$_486
	cmp	eax, 387
	jz	$_487
	cmp	eax, 392
	jz	$_488
	cmp	eax, 389
	jz	$_489
	cmp	eax, 393
	jz	$_490
	cmp	eax, 390
	jz	$_491
	cmp	eax, 388
	jz	$_492
$_494:	mov	dword ptr [rsi+0x2C], ecx
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 2
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	test	eax, eax
	jnz	$_495
	mov	rcx, rdi
	call	AddLineQueue@PLT
$_495:	jmp	$_497

$_496:	cmp	dword ptr [rbp-0x8], 324
	jz	$_497
	lea	rdx, [rdi+0x14]
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr
	mov	ecx, dword ptr [rbp-0x8]
	call	$_430
	mov	rdx, rax
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdx, [DS000C+0x4+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [rdi+0x14]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, rdi
	call	AddLineQueue@PLT
$_497:	jmp	$_500

$_498:	cmp	eax, 322
	je	$_463
	cmp	eax, 323
	je	$_466
	cmp	eax, 325
	je	$_471
	cmp	eax, 373
	jc	$_499
	cmp	eax, 393
	jbe	$_483
$_499:	cmp	eax, 324
	je	$_483
$_500:	mov	eax, dword ptr [rsi+0x14]
	test	eax, eax
	jz	$_501
	mov	rdx, rdi
	mov	ecx, eax
	call	GetLabelStr
	lea	r8, [DS000A+0x1+rip]
	mov	rdx, rax
	lea	rcx, [DS0007+0x2+rip]
	call	AddLineQueueX@PLT
$_501:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_502
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_502
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], -1
$_502:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_503
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_503:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_504
	call	RunLineQueue@PLT
$_504:	mov	eax, dword ptr [rbp-0x4]
$_505:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

HllContinueIf:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 344
	mov	dword ptr [rbp-0x4], 0
	lea	rdi, [rbp-0x114]
	mov	ecx, dword ptr [rbp+0x40]
	mov	rsi, qword ptr [rbp+0x28]
	mov	rax, qword ptr [rbp+0x30]
	imul	ebx, dword ptr [rax], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 0
	je	$_520
	cmp	byte ptr [rbx], 3
	jne	$_519
	xor	edx, edx
	mov	eax, dword ptr [rbx+0x4]
	jmp	$_517

$_506:	or	edx, 0x80000
$_507:	or	edx, 0x40000
$_508:	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rbp-0x118], eax
	mov	rax, qword ptr [rsi+0x20]
	mov	qword ptr [rbp-0x120], rax
	mov	eax, dword ptr [rsi+0x2C]
	mov	dword ptr [rbp-0x124], eax
	mov	dword ptr [rsi+0x2C], edx
	mov	dword ptr [rsi+0x28], 3
	mov	rdx, qword ptr [rbp+0x30]
	inc	dword ptr [rdx]
	mov	qword ptr [rsp+0x28], rdi
	mov	eax, dword ptr [rbp+0x50]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rcx, rsi
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	test	eax, eax
	jnz	$_509
	mov	rcx, rdi
	call	AddLineQueue@PLT
$_509:	mov	eax, dword ptr [rbp-0x118]
	mov	dword ptr [rsi+0x28], eax
	mov	rax, qword ptr [rbp-0x120]
	mov	qword ptr [rsi+0x20], rax
	mov	eax, dword ptr [rbp-0x124]
	mov	dword ptr [rsi+0x2C], eax
	jmp	$_519

$_510:	or	edx, 0x90000
	jmp	$_508

$_511:	or	edx, 0x80000
$_512:	or	edx, 0x20000
	jmp	$_508

$_513:	cmp	byte ptr [rbx+0x18], 0
	jz	$_514
	or	edx, 0x80000
	jmp	$_508

$_514:	cmp	byte ptr [rbx+0x18], 0
	jz	$_515
	or	edx, 0x10000
	jmp	$_508

$_515:	mov	rax, qword ptr [rbp+0x30]
	inc	dword ptr [rax]
	lea	rdx, [rbp-0x14]
	mov	ecx, dword ptr [rsi+rcx*4+0x10]
	call	GetLabelStr
	mov	ecx, dword ptr [rbx+0x4]
	call	$_430
	mov	rdx, rax
	mov	rcx, rdi
	call	tstrcpy@PLT
	lea	rdx, [DS000C+0x4+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [rbp-0x14]
	mov	rcx, rdi
	call	tstrcat@PLT
	cmp	dword ptr [rbp+0x50], 0
	jz	$_516
	mov	rcx, rdi
	call	$_108
$_516:	mov	rcx, rdi
	call	AddLineQueue@PLT
	jmp	$_519

$_517:	cmp	eax, 326
	jc	$_518
	cmp	eax, 340
	jbe	$_515
$_518:	cmp	eax, 348
	je	$_506
	cmp	eax, 345
	je	$_507
	cmp	eax, 315
	je	$_508
	cmp	eax, 346
	je	$_510
	cmp	eax, 347
	je	$_511
	cmp	eax, 344
	je	$_512
	cmp	eax, 343
	je	$_513
	cmp	eax, 341
	je	$_514
	cmp	eax, 342
	je	$_514
$_519:	jmp	$_523

$_520:	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+rcx*4+0x10]
	call	GetLabelStr
	mov	rdx, rax
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
	mov	rdx, qword ptr [rbp+0x48]
	cmp	dword ptr [rdx+0x28], 4
	jnz	$_523
	mov	rsi, rdx
	mov	rax, rsi
	jmp	$_522

$_521:	mov	rsi, qword ptr [rsi+0x8]
$_522:	cmp	qword ptr [rsi+0x8], 0
	jnz	$_521
	cmp	rax, rsi
	jz	$_523
	or	byte ptr [rsi+0x2D], 0xFFFFFF80
$_523:	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

HllExitDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 2136
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x8], 0
	mov	rax, qword ptr [ModuleInfo+0xF8+rip]
	mov	qword ptr [rbp-0x828], rax
	mov	rsi, rax
	test	rsi, rsi
	jnz	$_524
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_562

$_524:	mov	rcx, qword ptr [rbp+0x30]
	call	ExpandCStrings
	lea	rdi, [rbp-0x81C]
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0xC], eax
	xor	ecx, ecx
	jmp	$_557

$_525:	or	byte ptr [rsi+0x2E], 0x04
$_526:	or	byte ptr [rsi+0x2E], 0x08
$_527:	or	byte ptr [rsi+0x2C], 0x02
$_528:	cmp	dword ptr [rsi+0x28], 0
	jz	$_529
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
	jmp	$_562

$_529:	test	byte ptr [rsi+0x2C], 0x01
	jz	$_530
	mov	ecx, 2142
	call	asmerr@PLT
	jmp	$_562

$_530:	cmp	dword ptr [rsi+0x14], 0
	jnz	$_531
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_531:	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x14]
	call	GetLabelStr
	mov	rdx, rax
	lea	rcx, [DS0013+0x1+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rsi+0x10], 0
	jbe	$_532
	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x10]
	call	GetLabelStr
	lea	r8, [DS000A+0x1+rip]
	mov	rdx, rax
	lea	rcx, [DS0007+0x2+rip]
	call	AddLineQueueX@PLT
	mov	dword ptr [rsi+0x10], 0
$_532:	inc	dword ptr [rbp+0x28]
	cmp	dword ptr [rbp-0xC], 320
	jz	$_535
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x10], eax
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 0
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	EvaluateHllExpression
	mov	dword ptr [rbp-0x4], eax
	test	eax, eax
	jnz	$_534
	test	byte ptr [rsi+0x2C], 0x08
	jz	$_533
	mov	qword ptr [rsp+0x28], rdi
	mov	dword ptr [rsp+0x20], 0
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	ExpandHllExpression
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x28], eax
	jmp	$_534

$_533:	mov	rcx, rdi
	call	AddLineQueue@PLT
$_534:	jmp	$_536

$_535:	or	byte ptr [rsi+0x2C], 0x01
$_536:	jmp	$_558

$_537:	or	byte ptr [rsi+0x2E], 0x04
	jmp	$_527

$_538:	cmp	byte ptr [rbx+0x18], 40
	jnz	$_542
	cmp	byte ptr [rbx+0x48], 41
	jnz	$_542
	mov	rcx, qword ptr [rbx+0x38]
	mov	eax, dword ptr [rcx]
	cmp	dword ptr [rbp-0xC], 319
	jnz	$_539
	cmp	al, 48
	jnz	$_539
	mov	dword ptr [rbp-0x8], 1
$_539:	xor	ecx, ecx
	jmp	$_541

$_540:	imul	ecx, ecx, 10
	sub	al, 48
	movzx	edx, al
	add	ecx, edx
	shr	eax, 8
$_541:	test	al, al
	jnz	$_540
	add	dword ptr [rbp+0x28], 3
	add	rbx, 72
	mov	eax, dword ptr [rbp-0xC]
$_542:	test	rsi, rsi
	jz	$_544
	cmp	dword ptr [rsi+0x28], 0
	jz	$_543
	cmp	dword ptr [rsi+0x28], 4
	jnz	$_544
$_543:	mov	rsi, qword ptr [rsi]
	jmp	$_542

$_544:	jmp	$_549

$_545:	mov	rsi, qword ptr [rsi]
$_546:	test	rsi, rsi
	jz	$_548
	cmp	dword ptr [rsi+0x28], 0
	jz	$_547
	cmp	dword ptr [rsi+0x28], 4
	jnz	$_548
$_547:	mov	rsi, qword ptr [rsi]
	jmp	$_546

$_548:	dec	ecx
$_549:	test	rsi, rsi
	jz	$_550
	test	ecx, ecx
	jnz	$_545
$_550:	test	rsi, rsi
	jnz	$_551
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_562

$_551:	cmp	eax, 318
	jnz	$_553
	cmp	dword ptr [rsi+0x14], 0
	jnz	$_552
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_552:	mov	ecx, 1
	jmp	$_556

$_553:	cmp	dword ptr [rsi+0x28], 2
	jnz	$_554
	cmp	dword ptr [rsi+0x10], 0
	jnz	$_554
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x10], eax
$_554:	mov	ecx, 0
	cmp	dword ptr [rbp-0x8], 1
	jnz	$_555
	mov	ecx, 2
	jmp	$_556

$_555:	cmp	dword ptr [rsi+0x10], 0
	jnz	$_556
	mov	ecx, 2
$_556:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	dword ptr [rsp+0x28], 1
	mov	rax, qword ptr [rbp-0x828]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, ecx
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	HllContinueIf
	mov	dword ptr [rbp-0x4], eax
	jmp	$_558

$_557:	cmp	eax, 351
	je	$_525
	cmp	eax, 349
	je	$_526
	cmp	eax, 321
	je	$_527
	cmp	eax, 320
	je	$_528
	cmp	eax, 350
	je	$_537
	cmp	eax, 318
	je	$_538
	cmp	eax, 319
	je	$_538
$_558:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_559
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_559
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x4], -1
$_559:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_560
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_560:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_561
	call	RunLineQueue@PLT
$_561:	mov	eax, dword ptr [rbp-0x4]
$_562:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

HllCheckOpen:
	sub	rsp, 40
	cmp	qword ptr [ModuleInfo+0xF8+rip], 0
	jz	$_563
	lea	rdx, [DS0014+rip]
	mov	ecx, 1010
	call	asmerr@PLT
$_563:	cmp	qword ptr [ModuleInfo+0x120+rip], 0
	jz	$_564
	lea	rdx, [DS0015+rip]
	mov	ecx, 1010
	call	asmerr@PLT
$_564:	add	rsp, 40
	ret

HllInit:
	mov	dword ptr [ModuleInfo+0x1B0+rip], 0
	ret


.SECTION .data
	.ALIGN	16

EOLSTR:
	.byte  0x0A, 0x00

flaginstr:
	.byte  0x7A, 0x63, 0x73, 0x70, 0x6F

unsign_cjmptype:
	.byte  0x7A, 0x7A, 0x61, 0x62, 0x62, 0x61

signed_cjmptype:
	.byte  0x7A, 0x7A, 0x67, 0x6C, 0x6C, 0x67

neg_cjmptype:
	.byte  0x00, 0x01, 0x00, 0x00, 0x01, 0x01

DS0000:
	.byte  0x6C, 0x65, 0x61, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x73, 0x0A, 0x00

DS0001:
	.byte  0x25, 0x72, 0x20, 0x00

DS0002:
	.byte  0x2C, 0x20, 0x25, 0x72, 0x00

DS0003:
	.byte  0x2C, 0x20, 0x25, 0x64, 0x00

DS0004:
	.byte  0x24, 0x43, 0x25, 0x30, 0x34, 0x58, 0x00

DS0005:
	.byte  0x6A, 0x6D, 0x70, 0x20, 0x24, 0x43, 0x25, 0x30
	.byte  0x34, 0x58, 0x25, 0x73, 0x00

DS0006:
	.byte  0x6A, 0x6D, 0x70, 0x20, 0x00

DS0007:
	.byte  0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x00

DS0008:
	.byte  0x3A, 0x00

DS0009:
	.byte  0x5F, 0x00

DS000A:
	.byte  0x3A, 0x3A, 0x00

DS000B:
	.byte  0x61, 0x64, 0x64, 0x72, 0x20, 0x5B, 0x00

DS000C:
	.byte  0x61, 0x64, 0x64, 0x72, 0x20, 0x00

DS000D:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x00

DS000E:
	.byte  0x20, 0x6A, 0x6E, 0x7A, 0x20, 0x25, 0x73, 0x00

DS000F:
	.byte  0x6A, 0x6D, 0x70, 0x00

DS0010:
	.byte  0x6A, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x00

DS0011:
	.byte  0x41, 0x4C, 0x49, 0x47, 0x4E, 0x20, 0x25, 0x64
	.byte  0x00

DS0012:
	.byte  0x6C, 0x6F, 0x6F, 0x70, 0x20, 0x25, 0x73, 0x00

DS0013:
	.byte  0x20, 0x6A, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x00

DS0014:
	.byte  0x2E, 0x69, 0x66, 0x2D, 0x2E, 0x72, 0x65, 0x70
	.byte  0x65, 0x61, 0x74, 0x2D, 0x2E, 0x77, 0x68, 0x69
	.byte  0x6C, 0x65, 0x00

DS0015:
	.byte  0x2E, 0x6E, 0x61, 0x6D, 0x65, 0x73, 0x70, 0x61
	.byte  0x63, 0x65, 0x00



.att_syntax prefix
