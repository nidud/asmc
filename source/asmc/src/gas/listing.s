
.intel_syntax noprefix

.global LstWrite
.global LstWriteSrcLine
.global LstPrintf
.global LstNL
.global LstSetPosition
.global LstWriteCRef
.global ListingDirective
.global ListMacroDirective
.global LstInit
.global list_pos

.extern szTime
.extern szDate
.extern cp_logo
.extern CurrStruct
.extern UseSavedState
.extern LineStoreCurr
.extern GetFName
.extern get_curr_srcfile
.extern GetCurrOffset
.extern GetSymOfssize
.extern GetResWName
.extern SpecialTable
.extern MemFree
.extern MemAlloc
.extern tqsort
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tmemset
.extern tvfprintf
.extern tsprintf
.extern asmerr
.extern LastCodeBufSize
.extern MacroLevel
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymGetCount
.extern SymGetAll
.extern SymLookup
.extern fseek
.extern fwrite


.SECTION .text
	.ALIGN	16

LstWrite:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 152
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x10], rax
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_001
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_001
	test	byte ptr [ModuleInfo+0x1C6+rip], 0x01
	jz	$_002
$_001:	jmp	$_053

$_002:	cmp	dword ptr [ModuleInfo+0x210+rip], 0
	jz	$_003
	cmp	byte ptr [ModuleInfo+0x1DE+rip], 0
	jnz	$_003
	jmp	$_053

$_003:	cmp	dword ptr [MacroLevel+rip], 0
	jz	$_007
	jmp	$_006

$_004:	jmp	$_053

$_005:	jmp	$_007

$_006:	cmp	dword ptr [ModuleInfo+0x1C8+rip], 0
	jz	$_004
	cmp	dword ptr [ModuleInfo+0x1C8+rip], 1
	jz	$_005
$_007:	or	byte ptr [ModuleInfo+0x1C6+rip], 0x01
	mov	rax, qword ptr [ModuleInfo+0x178+rip]
	mov	qword ptr [rbp-0x38], rax
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_011
	cmp	dword ptr [UseSavedState+rip], 0
	jz	$_011
	cmp	dword ptr [ModuleInfo+0x210+rip], 0
	jnz	$_010
	mov	rcx, qword ptr [LineStoreCurr+rip]
	test	byte ptr [ModuleInfo+0x1C6+rip], 0x02
	jnz	$_009
	cmp	dword ptr [Parse_Pass+rip], 1
	jnz	$_008
	cmp	byte ptr [Options+0xA1+rip], 0
	jz	$_008
	mov	eax, dword ptr [list_pos+rip]
	mov	dword ptr [rcx+0x1C], eax
	jmp	$_009

$_008:	mov	eax, dword ptr [rcx+0x1C]
	mov	dword ptr [list_pos+rip], eax
$_009:	lea	rax, [rcx+0x20]
	mov	qword ptr [rbp-0x38], rax
	cmp	qword ptr [ModuleInfo+0x218+rip], 0
	jz	$_010
	mov	rbx, rax
	mov	rcx, rax
	call	tstrlen@PLT
	mov	byte ptr [rbx+rax], 59
	mov	qword ptr [ModuleInfo+0x218+rip], 0
$_010:	xor	edx, edx
	mov	esi, dword ptr [list_pos+rip]
	mov	rdi, qword ptr [ModuleInfo+0x80+rip]
	call	fseek@PLT
$_011:	mov	qword ptr [rbp-0x70], 0
	mov	r8d, 32
	mov	edx, 32
	lea	rcx, [rbp-0x68]
	call	tmemset@PLT
	call	get_curr_srcfile@PLT
	mov	dword ptr [rbp-0x20], eax
	mov	rbx, qword ptr [ModuleInfo+0x1F8+rip]
	jmp	$_044

$_012:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_013
	cmp	byte ptr [Options+0xA1+rip], 0
	je	$_045
$_013:	call	GetCurrOffset@PLT
	mov	dword ptr [rbp-0x4], eax
	mov	r8d, dword ptr [rbp+0x30]
	lea	rdx, [DS0044+rip]
	lea	rcx, [rbp-0x68]
	call	tsprintf@PLT
	mov	byte ptr [rbp-0x60], 32
	test	rbx, rbx
	je	$_045
	cmp	dword ptr [Parse_Pass+rip], 0
	je	$_045
	mov	dword ptr [rbp-0x14], 9
	lea	rdi, [rbp-0x5E]
	mov	rdx, qword ptr [rbx+0x68]
	cmp	qword ptr [rdx+0x10], 0
	jz	$_014
	cmp	byte ptr [rdx+0x70], 0
	jnz	$_018
$_014:	mov	eax, 12336
	mov	ecx, dword ptr [rbp-0x4]
	jmp	$_016

$_015:	stosw
	inc	dword ptr [rbp+0x30]
	dec	dword ptr [rbp-0x14]
$_016:	cmp	dword ptr [rbp+0x30], ecx
	jnc	$_017
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_015
$_017:	jmp	$_045

$_018:	mov	eax, dword ptr [rdx+0xC]
	sub	eax, dword ptr [rdx+0x8]
	mov	ecx, dword ptr [rbp-0x4]
	sub	ecx, dword ptr [rbp+0x30]
	sub	eax, ecx
	mov	dword ptr [rbp-0x1C], eax
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_022
	add	eax, dword ptr [LastCodeBufSize+rip]
	cmp	eax, 0
	jl	$_045
	mov	rsi, qword ptr [rdx+0x10]
	add	rsi, rax
	jmp	$_020

$_019:	movzx	eax, byte ptr [rsi]
	inc	rsi
	mov	r8d, eax
	lea	rdx, [DS0045+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, 2
	inc	dword ptr [rbp-0x1C]
	inc	dword ptr [rbp+0x30]
	dec	dword ptr [rbp-0x14]
$_020:	cmp	dword ptr [rbp-0x1C], 0
	jge	$_021
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_019
$_021:	jmp	$_023

$_022:	cmp	dword ptr [rbp-0x1C], 0
	jge	$_023
	mov	dword ptr [rbp-0x1C], 0
$_023:	mov	rdx, qword ptr [rbx+0x68]
	mov	rsi, qword ptr [rdx+0x10]
	mov	eax, dword ptr [rbp-0x1C]
	add	rsi, rax
	jmp	$_025

$_024:	movzx	eax, byte ptr [rsi]
	inc	rsi
	mov	r8d, eax
	lea	rdx, [DS0045+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, 2
	inc	dword ptr [rbp-0x1C]
	inc	dword ptr [rbp+0x30]
	dec	dword ptr [rbp-0x14]
$_025:	mov	eax, dword ptr [rbp-0x4]
	cmp	dword ptr [rbp+0x30], eax
	jnc	$_026
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_024
$_026:	mov	byte ptr [rdi], 32
	jmp	$_045

$_027:	mov	edi, 1
	mov	rsi, qword ptr [rbp-0x10]
	cmp	qword ptr [rsi+0x30], 0
	jz	$_028
	cmp	qword ptr [rsi+0x30], rbx
	jnz	$_028
	call	GetCurrOffset@PLT
	mov	r8, rax
	lea	rdx, [DS0044+rip]
	lea	rcx, [rbp-0x68]
	call	tsprintf@PLT
	mov	edi, 10
$_028:	mov	byte ptr [rbp+rdi-0x68], 61
	cmp	dword ptr [rsi+0x50], 0
	jz	$_030
	cmp	dword ptr [rsi+0x50], -1
	jnz	$_029
	cmp	dword ptr [rsi+0x28], 0
	jl	$_030
$_029:	mov	r9d, dword ptr [rsi+0x50]
	mov	r8d, dword ptr [rsi+0x28]
	lea	rdx, [DS0046+rip]
	lea	rcx, [rbp+rdi-0x66]
	call	tsprintf@PLT
	jmp	$_031

$_030:	mov	r8d, dword ptr [rsi+0x28]
	lea	rdx, [DS0047+rip]
	lea	rcx, [rbp+rdi-0x66]
	call	tsprintf@PLT
$_031:	mov	byte ptr [rbp+rdi-0x52], 32
	jmp	$_045

$_032:	mov	byte ptr [rbp-0x67], 61
	mov	rcx, qword ptr [rbp-0x10]
	mov	rsi, qword ptr [rcx+0x28]
	lea	rdi, [rbp-0x65]
	lea	rbx, [rbp-0x70]
$_033:	cmp	byte ptr [rsi], 0
	jz	$_035
	lea	rax, [rbx+0x24]
	cmp	rdi, rax
	jc	$_034
	mov	eax, 48
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
	mov	qword ptr [rbx], rax
	mov	rbx, rax
	mov	qword ptr [rbx], 0
	mov	r8d, 32
	mov	edx, 32
	lea	rcx, [rbx+0x8]
	call	tmemset@PLT
	lea	rdi, [rbx+0xB]
$_034:	movsb
	jmp	$_033

$_035:	jmp	$_045

$_036:	mov	byte ptr [rbp-0x67], 62
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x38], rax
	jmp	$_045

$_037:	call	GetCurrOffset@PLT
	mov	dword ptr [rbp+0x30], eax
$_038:	mov	r8d, dword ptr [rbp+0x30]
	lea	rdx, [DS0044+rip]
	lea	rcx, [rbp-0x68]
	call	tsprintf@PLT
	mov	byte ptr [rbp-0x60], 32
	jmp	$_045

$_039:	test	rbx, rbx
	jnz	$_040
	cmp	qword ptr [rbp+0x38], 0
	jz	$_041
$_040:	mov	r8d, dword ptr [rbp+0x30]
	lea	rdx, [DS0044+rip]
	lea	rcx, [rbp-0x68]
	call	tsprintf@PLT
	mov	byte ptr [rbp-0x60], 32
$_041:	jmp	$_045

$_042:	mov	rcx, qword ptr [rbp-0x38]
	mov	dl, byte ptr [rcx]
	test	dl, dl
	jnz	$_043
	cmp	qword ptr [ModuleInfo+0x218+rip], 0
	jnz	$_043
	mov	eax, dword ptr [ModuleInfo+0x1F4+rip]
	cmp	dword ptr [rbp-0x20], eax
	jnz	$_043
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, 1
	mov	esi, 1
	lea	rdi, [DS0048+rip]
	call	fwrite@PLT
	add	dword ptr [list_pos+rip], 1
	jmp	$_053

$_043:	jmp	$_045

$_044:	cmp	dword ptr [rbp+0x28], 0
	je	$_012
	cmp	dword ptr [rbp+0x28], 1
	je	$_013
	cmp	dword ptr [rbp+0x28], 2
	je	$_027
	cmp	dword ptr [rbp+0x28], 3
	je	$_032
	cmp	dword ptr [rbp+0x28], 8
	je	$_036
	cmp	dword ptr [rbp+0x28], 7
	je	$_037
	cmp	dword ptr [rbp+0x28], 6
	je	$_038
	cmp	dword ptr [rbp+0x28], 4
	je	$_039
	jmp	$_042

$_045:	mov	dword ptr [rbp-0x1C], 32
	cmp	dword ptr [ModuleInfo+0x210+rip], 0
	jz	$_046
	mov	byte ptr [rbp-0x4C], 42
$_046:	cmp	dword ptr [MacroLevel+rip], 0
	jz	$_047
	mov	r8d, dword ptr [MacroLevel+rip]
	lea	rdx, [DS0049+rip]
	lea	rcx, [rbp-0x4B]
	call	tsprintf@PLT
	mov	dword ptr [rbp-0x14], eax
	mov	byte ptr [rbp+rax-0x4B], 32
$_047:	mov	eax, dword ptr [ModuleInfo+0x1F4+rip]
	cmp	dword ptr [rbp-0x20], eax
	jz	$_048
	mov	byte ptr [rbp-0x4A], 67
$_048:	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, dword ptr [rbp-0x1C]
	mov	esi, 1
	lea	rdi, [rbp-0x68]
	call	fwrite@PLT
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x14], eax
	mov	dword ptr [rbp-0x18], 0
	cmp	qword ptr [ModuleInfo+0x218+rip], 0
	jz	$_049
	mov	rcx, qword ptr [ModuleInfo+0x218+rip]
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x18], eax
$_049:	mov	eax, dword ptr [rbp-0x18]
	add	eax, dword ptr [rbp-0x14]
	add	eax, 33
	add	dword ptr [list_pos+rip], eax
	cmp	dword ptr [rbp-0x14], 0
	jz	$_050
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, dword ptr [rbp-0x14]
	mov	esi, 1
	mov	rdi, qword ptr [rbp-0x38]
	call	fwrite@PLT
$_050:	cmp	dword ptr [rbp-0x18], 0
	jz	$_051
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, dword ptr [rbp-0x18]
	mov	esi, 1
	mov	rdi, qword ptr [ModuleInfo+0x218+rip]
	call	fwrite@PLT
$_051:	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, 1
	mov	esi, 1
	lea	rdi, [DS0048+rip]
	call	fwrite@PLT
	mov	rbx, qword ptr [rbp-0x70]
$_052:	test	rbx, rbx
	jz	$_053
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, 32
	mov	esi, 1
	lea	rdi, [rbx+0x8]
	call	fwrite@PLT
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, 1
	mov	esi, 1
	lea	rdi, [DS0048+rip]
	call	fwrite@PLT
	add	dword ptr [list_pos+rip], 33
	mov	rbx, qword ptr [rbx]
	jmp	$_052

$_053:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

LstWriteSrcLine:
	sub	rsp, 40
	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 5
	call	LstWrite
	add	rsp, 40
	ret

LstPrintf:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_054
	lea	r8, [rbp+0x18]
	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	call	tvfprintf@PLT
	add	dword ptr [list_pos+rip], eax
$_054:	leave
	ret

LstNL:
	push	rsi
	push	rdi
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_055
	mov	rcx, qword ptr [ModuleInfo+0x80+rip]
	mov	edx, 1
	mov	esi, 1
	lea	rdi, [DS0048+rip]
	call	fwrite@PLT
	add	dword ptr [list_pos+rip], 1
$_055:	pop	rdi
	pop	rsi
	ret

LstSetPosition:
	push	rsi
	push	rdi
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_056
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_056
	cmp	dword ptr [UseSavedState+rip], 0
	jz	$_056
	cmp	dword ptr [ModuleInfo+0x210+rip], 0
	jnz	$_056
	mov	rcx, qword ptr [LineStoreCurr+rip]
	mov	eax, dword ptr [rcx+0x1C]
	mov	dword ptr [list_pos+rip], eax
	xor	edx, edx
	mov	esi, dword ptr [list_pos+rip]
	mov	rdi, qword ptr [ModuleInfo+0x80+rip]
	call	fseek@PLT
	or	byte ptr [ModuleInfo+0x1C6+rip], 0x02
$_056:	pop	rdi
	pop	rsi
	ret

$_057:
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	movzx	ecx, byte ptr [rcx+0x6A]
	lea	rdx, [strings+rip]
	jmp	$_066

$_058:	mov	rax, qword ptr [rdx]
	jmp	$_067

$_059:	mov	rax, qword ptr [rdx+0x8]
	jmp	$_067

$_060:	mov	rax, qword ptr [rdx+0x10]
	jmp	$_067

$_061:	mov	rax, qword ptr [rdx+0x20]
	jmp	$_067

$_062:	mov	rax, qword ptr [rdx+0x30]
	jmp	$_067

$_063:	mov	rax, qword ptr [rdx+0x50]
	jmp	$_067

$_064:	mov	rax, qword ptr [rdx+0x148]
	jmp	$_067

$_065:	mov	eax, 1
	shl	eax, cl
	mov	r8d, eax
	lea	rdx, [DS0049+rip]
	mov	rcx, qword ptr [rbp+0x18]
	call	tsprintf@PLT
	mov	rax, qword ptr [rbp+0x18]
	jmp	$_067

$_066:	cmp	ecx, 0
	jz	$_058
	cmp	ecx, 1
	jz	$_059
	cmp	ecx, 2
	jz	$_060
	cmp	ecx, 3
	jz	$_061
	cmp	ecx, 4
	jz	$_062
	cmp	ecx, 8
	jz	$_063
	cmp	ecx, 255
	jz	$_064
	jmp	$_065

$_067:
	leave
	ret

$_068:
	lea	rdx, [strings+rip]
	jmp	$_073

$_069:	mov	rax, qword ptr [rdx+0xF8]
	jmp	$_075

$_070:	mov	rax, qword ptr [rdx+0x100]
	jmp	$_075

$_071:	mov	rax, qword ptr [rdx+0x108]
	jmp	$_075

$_072:	mov	rax, qword ptr [rdx+0x110]
	jmp	$_075

	jmp	$_074

$_073:	cmp	byte ptr [rcx+0x72], 0
	jz	$_069
	cmp	byte ptr [rcx+0x72], 5
	jz	$_070
	cmp	byte ptr [rcx+0x72], 2
	jz	$_071
	cmp	byte ptr [rcx+0x72], 6
	jz	$_072
$_074:	lea	rax, [DS004A+rip]
$_075:	ret

log_macro:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	lea	rax, [strings+rip]
	mov	rdx, qword ptr [rax+0xE0]
	test	byte ptr [rcx+0x38], 0x02
	jz	$_076
	mov	rdx, qword ptr [rax+0xE8]
$_076:	mov	eax, dword ptr [rcx+0x10]
	cmp	eax, 32
	jc	$_077
	lea	rax, [DS004A+0x1+rip]
	jmp	$_078

$_077:	lea	rbx, [dots+rip]
	lea	rax, [rbx+rax+0x1]
$_078:	mov	r9, rdx
	mov	r8, rax
	mov	rdx, qword ptr [rcx+0x8]
	lea	rcx, [DS004B+rip]
	call	LstPrintf
	call	LstNL
	leave
	pop	rbx
	ret

$_079:
	cmp	ecx, 63
	jnz	$_080
	mov	ecx, 64
	jmp	$_081

$_080:	and	ecx, 0x1F
	inc	ecx
$_081:	lea	rdx, [strings+rip]
	jmp	$_091

$_082:	mov	rax, qword ptr [rdx]
	jmp	$_093

$_083:	mov	rax, qword ptr [rdx+0x8]
	jmp	$_093

$_084:	mov	rax, qword ptr [rdx+0x10]
	jmp	$_093

$_085:	mov	rax, qword ptr [rdx+0x18]
	jmp	$_093

$_086:	mov	rax, qword ptr [rdx+0x20]
	jmp	$_093

$_087:	mov	rax, qword ptr [rdx+0x28]
	jmp	$_093

$_088:	mov	rax, qword ptr [rdx+0x38]
	jmp	$_093

$_089:	mov	rax, qword ptr [rdx+0x40]
	jmp	$_093

$_090:	mov	rax, qword ptr [rdx+0x48]
	jmp	$_093

	jmp	$_092

$_091:	cmp	ecx, 1
	jz	$_082
	cmp	ecx, 2
	jz	$_083
	cmp	ecx, 4
	jz	$_084
	cmp	ecx, 6
	jz	$_085
	cmp	ecx, 8
	jz	$_086
	cmp	ecx, 10
	jz	$_087
	cmp	ecx, 16
	jz	$_088
	cmp	ecx, 32
	jz	$_089
	cmp	ecx, 64
	jz	$_090
$_092:	lea	rax, [DS0072+0xF+rip]
$_093:	ret

$_094:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	test	byte ptr [rsi+0x19], 0xFFFFFF80
	jnz	$_095
	movzx	ecx, byte ptr [rsi+0x19]
	call	$_079
	jmp	$_115

$_095:	mov	al, byte ptr [rsi+0x19]
	mov	byte ptr [rbp-0x5], al
	cmp	byte ptr [rsi+0x18], 5
	jnz	$_096
	cmp	byte ptr [rsi+0x39], 0
	jz	$_096
	mov	byte ptr [rbp-0x5], -61
$_096:	lea	rdx, [strings+rip]
	jmp	$_113

$_097:	cmp	byte ptr [rsi+0x38], 2
	jnz	$_098
	mov	rdi, qword ptr [rdx+0x58]
	jmp	$_100

$_098:	movzx	ecx, byte ptr [rsi+0x38]
	cmp	byte ptr [rsi+0x1C], 0
	jz	$_099
	mov	rdi, qword ptr [rdx+rcx*8+0x80]
	jmp	$_100

$_099:	mov	rdi, qword ptr [rdx+rcx*8+0x60]
$_100:	cmp	qword ptr [rbp+0x30], 0
	je	$_105
	mov	rbx, qword ptr [rbp+0x30]
	movzx	eax, byte ptr [rsi+0x39]
	mov	dword ptr [rbp-0x4], eax
$_101:	cmp	dword ptr [rbp-0x4], 0
	jz	$_102
	lea	rdx, [strings+rip]
	mov	r9, qword ptr [rdx+0xD8]
	mov	r8, rdi
	lea	rdx, [DS004C+rip]
	mov	rcx, rbx
	call	tsprintf@PLT
	add	rbx, rax
	dec	dword ptr [rbp-0x4]
	jmp	$_101

$_102:	cmp	byte ptr [rsi+0x18], 7
	jnz	$_104
	cmp	word ptr [rsi+0x5A], 3
	jnz	$_104
	cmp	qword ptr [rsi+0x40], 0
	jz	$_103
	mov	rcx, qword ptr [rsi+0x40]
	mov	rdx, qword ptr [rcx+0x8]
	mov	rcx, rbx
	call	tstrcpy@PLT
	jmp	$_104

$_103:	test	byte ptr [rsi+0x3A], 0xFFFFFF80
	jnz	$_104
	movzx	ecx, byte ptr [rsi+0x3A]
	call	$_079
	mov	rdx, rax
	mov	rcx, rbx
	call	tstrcpy@PLT
$_104:	mov	rax, qword ptr [rbp+0x30]
	jmp	$_115

$_105:	mov	rax, rdi
	jmp	$_115

$_106:	cmp	qword ptr [rsi+0x30], 0
	jz	$_107
	mov	rax, qword ptr [rdx+0xB8]
	jmp	$_115

$_107:	mov	rcx, rsi
	call	GetSymOfssize@PLT
	mov	ecx, eax
	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+rcx*8+0xC0]
	jmp	$_115

$_108:	cmp	qword ptr [rsi+0x30], 0
	jz	$_109
	mov	rax, qword ptr [rdx+0x98]
	jmp	$_115

$_109:	mov	rcx, rsi
	call	GetSymOfssize@PLT
	mov	ecx, eax
	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+rcx*8+0xA0]
	jmp	$_115

$_110:	mov	rcx, qword ptr [rsi+0x20]
	mov	rax, qword ptr [rcx+0x8]
	cmp	byte ptr [rax], 0
	jz	$_111
	jmp	$_115

$_111:	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rsi+0x20]
	call	$_094
	jmp	$_115

$_112:	mov	rax, qword ptr [rdx+0xF0]
	jmp	$_115

	jmp	$_114

$_113:	cmp	byte ptr [rbp-0x5], -61
	je	$_097
	cmp	byte ptr [rbp-0x5], -126
	je	$_106
	cmp	byte ptr [rbp-0x5], -127
	jz	$_108
	cmp	byte ptr [rbp-0x5], -60
	jz	$_110
	cmp	byte ptr [rbp-0x5], -64
	jz	$_112
$_114:	lea	rax, [DS004A+rip]
$_115:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_116:
	movzx	eax, byte ptr [rcx+0x1A]
	cmp	eax, 10
	ja	$_117
	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+rax*8+0x160]
	jmp	$_118

$_117:	lea	rax, [DS004A+rip]
$_118:	ret

log_struct:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rdi, rcx
	mov	rsi, qword ptr [rdi+0x68]
	cmp	qword ptr [rbp+0x30], 0
	jnz	$_119
	mov	rax, qword ptr [rdi+0x8]
	mov	qword ptr [rbp+0x30], rax
$_119:	mov	rcx, qword ptr [rbp+0x30]
	call	tstrlen@PLT
	cmp	rax, 32
	jc	$_120
	lea	rcx, [DS004C+0x6+rip]
	jmp	$_121

$_120:	lea	rcx, [dots+rip]
	lea	rcx, [rcx+rax+0x1]
$_121:	cmp	byte ptr [rsi+0x10], 1
	jbe	$_122
	movzx	eax, byte ptr [rsi+0x10]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rdi+0x50]
	mov	r8, rcx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [DS004D+rip]
	call	LstPrintf
	jmp	$_123

$_122:	mov	r9d, dword ptr [rdi+0x50]
	mov	r8, rcx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [DS004E+rip]
	call	LstPrintf
$_123:	call	LstNL
	add	dword ptr [prefix+rip], 2
	mov	rbx, qword ptr [rsi]
$_124:	test	rbx, rbx
	je	$_132
	cmp	byte ptr [rbx+0x19], -60
	jnz	$_125
	cmp	byte ptr [rbx+0x70], 0
	jnz	$_125
	mov	ecx, dword ptr [rbx+0x28]
	add	ecx, dword ptr [rbp+0x38]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, qword ptr [rbx+0x20]
	call	log_struct
	jmp	$_131

$_125:	mov	rcx, qword ptr [rbx+0x8]
	cmp	byte ptr [rcx], 0
	jnz	$_126
	cmp	byte ptr [rbx+0x19], -60
	jne	$_131
$_126:	mov	eax, dword ptr [rbx+0x10]
	add	eax, dword ptr [prefix+rip]
	mov	ecx, eax
	lea	rdx, [dots+rip]
	lea	rax, [rax+rdx+0x1]
	cmp	ecx, 32
	jc	$_127
	lea	rax, [DS004E+0x10+rip]
$_127:	mov	qword ptr [rbp-0x8], rax
	xor	esi, esi
$_128:
	cmp	esi, dword ptr [prefix+rip]
	jge	$_129
	lea	rcx, [DS004C+0x5+rip]
	call	LstPrintf
	inc	esi
	jmp	$_128

$_129:	mov	ecx, dword ptr [rbx+0x28]
	add	ecx, dword ptr [rdi+0x28]
	add	ecx, dword ptr [rbp+0x38]
	mov	r9d, ecx
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [DS004F+rip]
	call	LstPrintf
	xor	edx, edx
	mov	rcx, rbx
	call	$_094
	mov	rdx, rax
	lea	rcx, [DS004B+0xD+rip]
	call	LstPrintf
	test	byte ptr [rbx+0x15], 0x02
	jz	$_130
	mov	edx, dword ptr [rbx+0x58]
	lea	rcx, [DS0050+rip]
	call	LstPrintf
$_130:	call	LstNL
$_131:	mov	rbx, qword ptr [rbx+0x68]
	jmp	$_124

$_132:
	sub	dword ptr [prefix+rip], 2
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

log_record:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	rdi, rcx
	lea	rdx, [dots+rip]
	lea	rax, [rdx+0x1]
	cmp	dword ptr [rdi+0x10], 32
	jl	$_133
	lea	rax, [DS0050+0x4+rip]
$_133:	mov	qword ptr [rbp-0x10], rax
	mov	rsi, qword ptr [rdi+0x68]
	xor	edx, edx
	mov	rbx, qword ptr [rsi]
$_134:	test	rbx, rbx
	jz	$_135
	mov	rbx, qword ptr [rbx+0x68]
	inc	edx
	jmp	$_134

$_135:
	imul	ecx, dword ptr [rdi+0x50], 8
	mov	dword ptr [rsp+0x20], edx
	mov	r9d, ecx
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0051+rip]
	call	LstPrintf
	call	LstNL
	mov	rbx, qword ptr [rsi]
$_136:	test	rbx, rbx
	je	$_145
	mov	eax, dword ptr [rbx+0x10]
	add	eax, 2
	mov	ecx, eax
	lea	rdx, [dots+rip]
	lea	rax, [rdx+rax+0x1]
	cmp	ecx, 32
	jc	$_137
	lea	rax, [DS0051+0x13+rip]
$_137:	mov	qword ptr [rbp-0x10], rax
	xor	eax, eax
	mov	qword ptr [rbp-0x8], rax
	mov	esi, dword ptr [rbx+0x28]
	add	esi, dword ptr [rbx+0x50]
	mov	ecx, dword ptr [rbx+0x28]
	xor	edx, edx
$_138:	cmp	ecx, esi
	jnc	$_141
	mov	eax, 1
	cmp	ecx, 32
	jc	$_139
	sub	ecx, 32
	shl	eax, cl
	or	dword ptr [rbp-0x4], eax
	add	ecx, 32
	jmp	$_140

$_139:	shl	eax, cl
	or	dword ptr [rbp-0x8], eax
$_140:	inc	ecx
	jmp	$_138

$_141:	lea	rcx, [DS004A+rip]
	cmp	byte ptr [rbx+0x70], 0
	jz	$_142
	lea	rcx, [rbx+0x70]
$_142:	cmp	dword ptr [rdi+0x50], 4
	jbe	$_143
	mov	qword ptr [rsp+0x30], rcx
	mov	rax, qword ptr [rbp-0x8]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbx+0x28]
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [DS0052+rip]
	call	LstPrintf
	jmp	$_144

$_143:	mov	qword ptr [rsp+0x30], rcx
	mov	rax, qword ptr [rbp-0x8]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [rbx+0x28]
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbx+0x8]
	lea	rcx, [DS0053+rip]
	call	LstPrintf
$_144:	call	LstNL
	mov	rbx, qword ptr [rbx+0x68]
	jmp	$_136

$_145:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

log_typedef:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, rcx
	mov	ecx, dword ptr [rsi+0x10]
	lea	rdx, [dots+rip]
	lea	rax, [rdx+rcx+0x1]
	cmp	ecx, 32
	jc	$_146
	lea	rax, [DS0053+0x1E+rip]
$_146:	mov	qword ptr [rbp-0x8], rax
	mov	rdi, qword ptr [ModuleInfo+0x188+rip]
	mov	byte ptr [rdi], 0
	mov	rbx, qword ptr [rsi+0x40]
	cmp	byte ptr [rsi+0x19], -128
	jne	$_149
	test	rbx, rbx
	je	$_149
	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+0xE0]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [DS004F+0x12+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, qword ptr [rbx+0x8]
	cmp	byte ptr [rcx], 0
	jz	$_147
	mov	rdx, rcx
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [DS004F+0x12+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
$_147:	mov	ecx, 192
	cmp	byte ptr [rbx+0x19], -127
	jnz	$_148
	mov	ecx, 160
$_148:	movzx	eax, byte ptr [rsi+0x38]
	lea	rcx, [rcx+rax*8]
	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+rcx]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [DS004F+0x12+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rcx, qword ptr [rsi+0x40]
	call	$_116
	mov	rdx, rax
	mov	rcx, rdi
	call	tstrcat@PLT
	jmp	$_150

$_149:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_094
	mov	rdi, rax
$_150:	mov	qword ptr [rsp+0x20], rdi
	mov	r9d, dword ptr [rsi+0x50]
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS0054+rip]
	call	LstPrintf
	call	LstNL
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

log_segment:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rsi, rcx
	mov	rdi, qword ptr [rsi+0x68]
	mov	rax, qword ptr [rbp+0x30]
	cmp	qword ptr [rdi], rax
	jne	$_156
	mov	eax, dword ptr [rsi+0x10]
	lea	rdx, [dots+rip]
	lea	rcx, [rdx+rax+0x1]
	cmp	eax, 32
	jc	$_151
	lea	rcx, [DS0054+0x10+rip]
$_151:	mov	r8, rcx
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS0055+rip]
	call	LstPrintf
	cmp	byte ptr [rdi+0x68], 1
	jnz	$_152
	mov	edx, dword ptr [rsi+0x50]
	lea	rcx, [DS0056+rip]
	call	LstPrintf
	jmp	$_154

$_152:	cmp	byte ptr [rdi+0x68], 2
	jnz	$_153
	mov	edx, dword ptr [rsi+0x50]
	lea	rcx, [DS0057+rip]
	call	LstPrintf
	jmp	$_154

$_153:	mov	edx, dword ptr [rsi+0x50]
	lea	rcx, [DS0058+rip]
	call	LstPrintf
$_154:	lea	rdx, [rbp-0x20]
	mov	rcx, rdi
	call	$_057
	mov	rbx, rax
	mov	rcx, rdi
	call	$_068
	mov	r8, rax
	mov	rdx, rbx
	lea	rcx, [DS0059+rip]
	call	LstPrintf
	lea	rcx, [DS0059+0x9+rip]
	mov	rdx, qword ptr [rdi+0x50]
	test	rdx, rdx
	jz	$_155
	mov	rcx, qword ptr [rdx+0x8]
$_155:	mov	rdx, rcx
	lea	rcx, [DS005A+rip]
	call	LstPrintf
	call	LstNL
$_156:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

log_group:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	mov	eax, dword ptr [rsi+0x10]
	lea	rcx, [dots+rip]
	lea	rdx, [rcx+rax+0x1]
	cmp	eax, 32
	jc	$_157
	lea	rdx, [DS005A+0x4+rip]
$_157:	lea	rdi, [strings+rip]
	mov	rdi, qword ptr [rdi+0x128]
	mov	r9, rdi
	mov	r8, rdx
	mov	rdx, qword ptr [rsi+0x8]
	lea	rcx, [DS004B+rip]
	call	LstPrintf
	call	LstNL
	cmp	rsi, qword ptr [ModuleInfo+0x200+rip]
	jnz	$_160
	mov	rdi, qword ptr [rbp+0x28]
$_158:	test	rdi, rdi
	jz	$_159
	mov	rdx, rsi
	mov	rcx, rdi
	call	log_segment
	mov	rdi, qword ptr [rdi+0x70]
	jmp	$_158

$_159:	jmp	$_162

$_160:	mov	rdi, qword ptr [rsi+0x68]
	mov	rdi, qword ptr [rdi]
$_161:	test	rdi, rdi
	jz	$_162
	mov	rdx, rsi
	mov	rcx, qword ptr [rdi+0x8]
	call	log_segment
	mov	rdi, qword ptr [rdi]
	jmp	$_161

$_162:
	leave
	pop	rdi
	pop	rsi
	ret

$_163:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	jmp	$_168

$_164:	cmp	qword ptr [rcx+0x30], 0
	jnz	$_165
	call	GetSymOfssize@PLT
	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+rax*8+0x60]
	jmp	$_170

$_165:	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+0x58]
	jmp	$_170

$_166:	cmp	qword ptr [rcx+0x30], 0
	jnz	$_167
	call	GetSymOfssize@PLT
	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+rax*8+0x80]
	jmp	$_170

$_167:	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+0x78]
	jmp	$_170

	jmp	$_169

$_168:	cmp	byte ptr [rcx+0x19], -127
	jz	$_164
	cmp	byte ptr [rcx+0x19], -126
	jz	$_166
$_169:	lea	rax, [DS006D+0x3+rip]
$_170:	leave
	ret

$_171:
	cmp	qword ptr [rcx+0x30], 0
	jz	$_172
	mov	rcx, qword ptr [rcx+0x30]
	mov	rax, qword ptr [rcx+0x8]
	jmp	$_173

	jmp	$_173

$_172:	lea	rdx, [strings+rip]
	mov	rax, qword ptr [rdx+0x130]
	jmp	$_173

$_173:
	ret

log_proc:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 360
	mov	rsi, rcx
	mov	rcx, rsi
	call	GetSymOfssize@PLT
	mov	byte ptr [rbp-0x1], al
	mov	eax, dword ptr [rsi+0x10]
	lea	rdx, [dots+rip]
	lea	rcx, [rdx+rax+0x1]
	cmp	eax, 32
	jc	$_174
	lea	rcx, [DS005A+0x4+rip]
$_174:	mov	qword ptr [rbp-0x18], rcx
	lea	rdi, [DS005B+rip]
	cmp	byte ptr [rbp-0x1], 0
	jz	$_175
	lea	rdi, [DS005C+rip]
$_175:	mov	qword ptr [rbp-0x10], rdi
	mov	rcx, rsi
	call	$_163
	mov	rbx, rax
	mov	rcx, rsi
	call	$_171
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, rbx
	mov	r8, qword ptr [rbp-0x18]
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rdi
	call	LstPrintf
	mov	ecx, 4
	cmp	byte ptr [rbp-0x1], 0
	jbe	$_176
	mov	ecx, 8
$_176:	xor	edx, edx
	cmp	byte ptr [rsi+0x18], 1
	jnz	$_177
	mov	edx, dword ptr [rsi+0x50]
$_177:	mov	r8d, edx
	mov	edx, ecx
	lea	rcx, [DS005D+rip]
	call	LstPrintf
	lea	rdx, [strings+rip]
	test	dword ptr [rsi+0x14], 0x80
	jz	$_178
	mov	rdx, qword ptr [rdx+0x108]
	lea	rcx, [DS005E+rip]
	call	LstPrintf
	jmp	$_181

$_178:	cmp	byte ptr [rsi+0x18], 1
	jnz	$_179
	mov	rdx, qword ptr [rdx+0xF8]
	lea	rcx, [DS005E+rip]
	call	LstPrintf
	jmp	$_181

$_179:	lea	rcx, [DS005F+rip]
	test	byte ptr [rsi+0x3B], 0x02
	jz	$_180
	lea	rcx, [DS0060+rip]
$_180:	mov	rdx, qword ptr [rdx+0x118]
	call	LstPrintf
	mov	rcx, qword ptr [rsi+0x50]
	test	rcx, rcx
	jz	$_181
	lea	rdx, [rcx+0xC]
	lea	rcx, [DS0061+rip]
	call	LstPrintf
$_181:	mov	rcx, rsi
	call	$_116
	mov	rdx, rax
	lea	rcx, [DS0054+0xE+rip]
	call	LstPrintf
	call	LstNL
	cmp	byte ptr [rsi+0x18], 2
	jnz	$_182
	cmp	qword ptr [rsi+0x58], 0
	jz	$_182
	lea	rcx, [DS0058+0x10+rip]
	call	LstPrintf
	mov	rbx, qword ptr [rsi+0x58]
	mov	rcx, rbx
	call	$_163
	mov	qword ptr [rbp-0x118], rax
	mov	rcx, rbx
	call	$_171
	mov	rdx, qword ptr [rbp-0x18]
	add	rdx, 2
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbx+0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x118]
	mov	r8, rdx
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	LstPrintf
	call	LstNL
$_182:	cmp	byte ptr [rsi+0x18], 1
	jne	$_212
	movzx	eax, byte ptr [rsi+0x1A]
	cmp	eax, 3
	jz	$_183
	cmp	eax, 1
	jz	$_183
	cmp	eax, 2
	jz	$_183
	cmp	eax, 8
	jz	$_183
	cmp	eax, 7
	jne	$_193
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 0
	je	$_193
$_183:	mov	rcx, qword ptr [rsi+0x68]
	mov	dword ptr [rbp-0x11C], 0
	mov	rcx, qword ptr [rcx+0x8]
$_184:	test	rcx, rcx
	jz	$_185
	inc	dword ptr [rbp-0x11C]
	mov	rcx, qword ptr [rcx+0x78]
	jmp	$_184

$_185:	cmp	dword ptr [rbp-0x11C], 0
	je	$_192
	mov	rdi, qword ptr [rsi+0x68]
	mov	ecx, 1
	mov	rdi, qword ptr [rdi+0x8]
$_186:	cmp	ecx, dword ptr [rbp-0x11C]
	jge	$_187
	mov	rdi, qword ptr [rdi+0x78]
	inc	ecx
	jmp	$_186

$_187:	mov	eax, dword ptr [rdi+0x10]
	lea	rdx, [dots+rip]
	lea	rcx, [rdx+rax+0x3]
	cmp	eax, 30
	jc	$_188
	lea	rcx, [DS0061+0x7+rip]
$_188:	mov	qword ptr [rbp-0x18], rcx
	cmp	byte ptr [rdi+0x18], 10
	jnz	$_189
	xor	edx, edx
	mov	rcx, rdi
	call	$_094
	mov	rcx, rax
	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, rcx
	mov	r8, qword ptr [rbp-0x18]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0062+rip]
	call	LstPrintf
	jmp	$_191

$_189:	mov	rcx, qword ptr [rsi+0x68]
	xor	edx, edx
	movzx	ecx, word ptr [rcx+0x42]
	call	GetResWName@PLT
	mov	qword ptr [rbp-0x118], rax
	xor	edx, edx
	mov	rcx, rdi
	call	$_094
	mov	rcx, rax
	test	byte ptr [rdi+0x3B], 0x04
	jz	$_190
	lea	rcx, [strings+rip]
	mov	rcx, qword ptr [rcx+0x158]
$_190:	mov	eax, dword ptr [rdi+0x28]
	mov	dword ptr [rsp+0x30], eax
	mov	dword ptr [rsp+0x28], 43
	mov	rax, qword ptr [rbp-0x118]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, rcx
	mov	r8, qword ptr [rbp-0x18]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0063+rip]
	call	LstPrintf
$_191:	call	LstNL
	dec	dword ptr [rbp-0x11C]
	jmp	$_185

$_192:	jmp	$_196

$_193:	mov	rdi, qword ptr [rsi+0x68]
	mov	rdi, qword ptr [rdi+0x8]
$_194:	test	rdi, rdi
	jz	$_196
	mov	eax, dword ptr [rdi+0x10]
	lea	rdx, [dots+rip]
	lea	rcx, [rdx+rax+0x3]
	cmp	eax, 30
	jc	$_195
	lea	rcx, [DS0063+0x1F+rip]
$_195:	mov	qword ptr [rbp-0x18], rcx
	mov	rcx, qword ptr [rsi+0x68]
	xor	edx, edx
	movzx	ecx, word ptr [rcx+0x42]
	call	GetResWName@PLT
	mov	rbx, rax
	xor	edx, edx
	mov	rcx, rdi
	call	$_094
	mov	rdx, rax
	mov	eax, dword ptr [rdi+0x28]
	mov	dword ptr [rsp+0x30], eax
	mov	dword ptr [rsp+0x28], 43
	mov	qword ptr [rsp+0x20], rbx
	mov	r9, rdx
	mov	r8, qword ptr [rbp-0x18]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0063+rip]
	call	LstPrintf
	call	LstNL
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_194

$_196:	mov	rdi, qword ptr [rsi+0x68]
	mov	rdi, qword ptr [rdi+0x10]
$_197:	test	rdi, rdi
	je	$_202
	mov	eax, dword ptr [rdi+0x10]
	lea	rdx, [dots+rip]
	lea	rcx, [rdx+rax+0x3]
	cmp	eax, 30
	jc	$_198
	lea	rcx, [DS0063+0x1F+rip]
$_198:	mov	qword ptr [rbp-0x18], rcx
	test	byte ptr [rdi+0x15], 0x02
	jz	$_199
	xor	edx, edx
	mov	rcx, rdi
	call	$_094
	mov	r9d, dword ptr [rdi+0x58]
	mov	r8, rax
	lea	rdx, [DS0064+rip]
	lea	rcx, [rbp-0x110]
	call	tsprintf@PLT
	jmp	$_200

$_199:	xor	edx, edx
	mov	rcx, rdi
	call	$_094
	mov	rdx, rax
	lea	rcx, [rbp-0x110]
	call	tstrcpy@PLT
$_200:	mov	rcx, qword ptr [rsi+0x68]
	xor	edx, edx
	movzx	ecx, word ptr [rcx+0x42]
	call	GetResWName@PLT
	mov	rbx, rax
	mov	ecx, 43
	mov	edx, dword ptr [rdi+0x28]
	cmp	edx, 0
	jge	$_201
	mov	ecx, 45
	neg	edx
$_201:	mov	dword ptr [rsp+0x30], edx
	mov	dword ptr [rsp+0x28], ecx
	mov	qword ptr [rsp+0x20], rbx
	lea	r9, [rbp-0x110]
	mov	r8, qword ptr [rbp-0x18]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0063+rip]
	call	LstPrintf
	call	LstNL
	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_197

$_202:	mov	rdi, qword ptr [rsi+0x68]
	mov	rdi, qword ptr [rdi+0x18]
$_203:	test	rdi, rdi
	je	$_212
	mov	rbx, rdi
$_204:	test	rbx, rbx
	je	$_211
	cmp	byte ptr [rbx+0x18], 5
	jz	$_205
	cmp	byte ptr [rbx+0x18], 10
	jnz	$_206
$_205:	jmp	$_210

$_206:	mov	eax, dword ptr [rdi+0x10]
	lea	rdx, [dots+rip]
	lea	rcx, [rdx+rax+0x3]
	cmp	eax, 30
	jc	$_207
	lea	rcx, [DS0064+0x6+rip]
$_207:	mov	qword ptr [rbp-0x18], rcx
	cmp	byte ptr [rbp-0x1], 0
	jz	$_208
	lea	rax, [DS0065+rip]
	jmp	$_209

$_208:	lea	rax, [DS0066+rip]
$_209:	mov	qword ptr [rbp-0x10], rax
	mov	rcx, rbx
	call	$_163
	mov	qword ptr [rbp-0x118], rax
	mov	rcx, rbx
	call	$_171
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbx+0x28]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x118]
	mov	r8, qword ptr [rbp-0x18]
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, qword ptr [rbp-0x10]
	call	LstPrintf
	call	LstNL
$_210:	mov	rbx, qword ptr [rbx]
	jmp	$_204

$_211:	mov	rdi, qword ptr [rdi+0x68]
	jmp	$_203

$_212:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_213:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rdi, rcx
	mov	eax, dword ptr [rdi+0x10]
	lea	rdx, [dots+rip]
	lea	rcx, [rdx+rax+0x1]
	cmp	eax, 32
	jc	$_214
	lea	rcx, [DS0066+0x21+rip]
$_214:	mov	qword ptr [rbp-0x8], rcx
	jmp	$_233

$_215:	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS0055+rip]
	call	LstPrintf
	test	byte ptr [rdi+0x15], 0x02
	jz	$_216
	xor	edx, edx
	mov	rcx, rdi
	call	$_094
	mov	r9d, dword ptr [rdi+0x58]
	mov	r8, rax
	lea	rdx, [DS0064+rip]
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	tsprintf@PLT
	mov	ebx, eax
	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	lea	rcx, [DS0067+rip]
	call	LstPrintf
	jmp	$_218

$_216:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_217
	test	byte ptr [rdi+0x3B], 0x01
	jz	$_217
	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+0x150]
	lea	rcx, [DS0067+rip]
	call	LstPrintf
	jmp	$_218

$_217:	xor	edx, edx
	mov	rcx, rdi
	call	$_094
	mov	rdx, rax
	lea	rcx, [DS0067+rip]
	call	LstPrintf
$_218:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_219
	test	byte ptr [rdi+0x3B], 0x01
	jz	$_219
	mov	eax, dword ptr [rdi+0x50]
	cdq
	div	dword ptr [rdi+0x58]
	mov	edx, eax
	lea	rcx, [DS0068+rip]
	call	LstPrintf
	jmp	$_224

$_219:	cmp	byte ptr [rdi+0x19], -64
	jnz	$_223
	cmp	dword ptr [rdi+0x50], 0
	jz	$_220
	cmp	dword ptr [rdi+0x50], -1
	jz	$_220
	mov	r8d, dword ptr [rdi+0x50]
	mov	edx, dword ptr [rdi+0x28]
	lea	rcx, [DS0069+rip]
	call	LstPrintf
	jmp	$_222

$_220:	cmp	dword ptr [rdi+0x50], 0
	jge	$_221
	xor	ecx, ecx
	sub	ecx, dword ptr [rdi+0x28]
	mov	edx, ecx
	lea	rcx, [DS006A+rip]
	call	LstPrintf
	jmp	$_222

$_221:	mov	edx, dword ptr [rdi+0x28]
	lea	rcx, [DS0068+rip]
	call	LstPrintf
$_222:	jmp	$_224

$_223:	mov	edx, dword ptr [rdi+0x28]
	lea	rcx, [DS0068+rip]
	call	LstPrintf
$_224:	cmp	qword ptr [rdi+0x30], 0
	jz	$_225
	mov	rcx, rdi
	call	$_171
	mov	rdx, rax
	lea	rcx, [DS004C+0x3+rip]
	call	LstPrintf
$_225:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_226
	test	byte ptr [rdi+0x3B], 0x01
	jz	$_226
	mov	r8d, dword ptr [rdi+0x58]
	lea	rdx, [DS006C+rip]
	lea	rcx, [DS006B+rip]
	call	LstPrintf
$_226:	test	dword ptr [rdi+0x14], 0x80
	jz	$_227
	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+0x108]
	lea	rcx, [DS004C+0x3+rip]
	call	LstPrintf
$_227:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_229
	lea	rcx, [DS004C+0x3+rip]
	test	byte ptr [rdi+0x3B], 0x02
	jz	$_228
	lea	rcx, [DS006D+rip]
$_228:	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+0x118]
	call	LstPrintf
	jmp	$_230

$_229:	cmp	byte ptr [rdi+0x18], 0
	jnz	$_230
	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+0x120]
	lea	rcx, [DS006D+0x1+rip]
	call	LstPrintf
$_230:	mov	rcx, rdi
	call	$_116
	mov	rdx, rax
	lea	rcx, [DS0066+0x1F+rip]
	call	LstPrintf
	call	LstNL
	jmp	$_234

$_231:	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+0x138]
	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, rdx
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS006E+rip]
	call	LstPrintf
	call	LstNL
	jmp	$_234

$_232:	mov	rcx, qword ptr [rdi+0x28]
	lea	rdx, [strings+rip]
	mov	rdx, qword ptr [rdx+0x140]
	mov	rax, qword ptr [rcx+0x8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, rdx
	mov	r8, qword ptr [rbp-0x8]
	mov	rdx, qword ptr [rdi+0x8]
	lea	rcx, [DS006F+rip]
	call	LstPrintf
	call	LstNL
	jmp	$_234

$_233:	cmp	byte ptr [rdi+0x18], 0
	je	$_215
	cmp	byte ptr [rdi+0x18], 1
	je	$_215
	cmp	byte ptr [rdi+0x18], 2
	je	$_215
	cmp	byte ptr [rdi+0x18], 10
	je	$_231
	cmp	byte ptr [rdi+0x18], 8
	jz	$_232
$_234:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_235:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	esi, dword ptr [rbp+0x20]
$_236:	test	esi, esi
	jz	$_237
	call	LstNL
	dec	esi
	jmp	$_236

$_237:
	mov	rcx, qword ptr [rbp+0x18]
	call	LstPrintf
	call	LstNL
	call	LstNL
	leave
	pop	rsi
	ret

compare_syms:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rcx]
	mov	rdx, qword ptr [rdx]
	mov	rdx, qword ptr [rdx+0x8]
	mov	rcx, qword ptr [rcx+0x8]
	call	tstrcmp@PLT
	leave
	ret

LstWriteCRef:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_238
	cmp	byte ptr [Options+0xA0+rip], 1
	jnz	$_239
$_238:	jmp	$_270

$_239:	mov	edx, 2
	xor	esi, esi
	mov	rdi, qword ptr [ModuleInfo+0x80+rip]
	call	fseek@PLT
	call	SymGetCount@PLT
	mov	dword ptr [rbp-0x24], eax
	lea	ecx, [rax*8]
	call	MemAlloc@PLT
	mov	qword ptr [rbp-0x8], rax
	mov	rcx, qword ptr [rbp-0x8]
	call	SymGetAll@PLT
	lea	r9, [compare_syms+rip]
	mov	r8d, 8
	mov	edx, dword ptr [rbp-0x24]
	mov	rcx, qword ptr [rbp-0x8]
	call	tqsort@PLT
	mov	r8d, 112
	xor	edx, edx
	lea	rcx, [rbp-0x98]
	call	tmemset@PLT
	xor	ebx, ebx
$_240:	cmp	ebx, dword ptr [rbp-0x24]
	jnc	$_258
	mov	rcx, qword ptr [rbp-0x8]
	mov	rdi, qword ptr [rcx+rbx*8]
	test	byte ptr [rdi+0x15], 0x01
	je	$_257
	jmp	$_253

$_241:	mov	rax, qword ptr [rdi+0x68]
	mov	qword ptr [rbp-0x18], rax
	jmp	$_246

$_242:	mov	ecx, 2
	jmp	$_247

$_243:	mov	ecx, 3
	jmp	$_247

$_244:	mov	ecx, 1
	jmp	$_247

$_245:	jmp	$_257

$_246:	cmp	word ptr [rdi+0x5A], 4
	jz	$_242
	cmp	word ptr [rdi+0x5A], 3
	jz	$_243
	cmp	word ptr [rdi+0x5A], 1
	jz	$_244
	cmp	word ptr [rdi+0x5A], 2
	jz	$_244
	jmp	$_245

$_247:	jmp	$_254

$_248:	mov	ecx, 0
	jmp	$_254

$_249:	mov	ecx, 4
	jmp	$_254

$_250:	mov	ecx, 5
	jmp	$_254

$_251:	test	byte ptr [rdi+0x15], 0x08
	jz	$_252
	mov	ecx, 6
	jmp	$_254

$_252:	jmp	$_257

$_253:	cmp	byte ptr [rdi+0x18], 7
	jz	$_241
	cmp	byte ptr [rdi+0x18], 9
	jz	$_248
	cmp	byte ptr [rdi+0x18], 3
	jz	$_249
	cmp	byte ptr [rdi+0x18], 4
	jz	$_250
	cmp	byte ptr [rdi+0x18], 1
	jz	$_251
	cmp	byte ptr [rdi+0x18], 2
	jz	$_251
	jmp	$_252

$_254:	imul	ecx, ecx, 16
	lea	rax, [rbp-0x98]
	lea	rdx, [rax+rcx]
	cmp	qword ptr [rdx], 0
	jnz	$_255
	mov	qword ptr [rdx], rdi
	jmp	$_256

$_255:	mov	rax, qword ptr [rdx+0x8]
	mov	qword ptr [rax+0x70], rdi
$_256:	mov	qword ptr [rdx+0x8], rdi
	mov	qword ptr [rdi+0x70], 0
$_257:	inc	ebx
	jmp	$_240

$_258:	lea	rdi, [cr+rip]
	xor	ebx, ebx
$_259:	cmp	ebx, 7
	jnc	$_266
	movzx	ecx, word ptr [rdi]
	imul	ecx, ecx, 16
	lea	rax, [rbp-0x98]
	cmp	qword ptr [rax+rcx], 0
	jz	$_265
	cmp	qword ptr [rdi+0x8], 0
	jz	$_262
	mov	rsi, qword ptr [rdi+0x8]
$_260:	cmp	word ptr [rsi], 0
	jz	$_262
	mov	eax, 2
	cmp	rsi, qword ptr [rdi+0x8]
	jz	$_261
	xor	eax, eax
$_261:	movzx	ecx, word ptr [rsi]
	lea	rdx, [strings+rip]
	mov	rcx, qword ptr [rdx+rcx]
	mov	edx, eax
	call	$_235
	add	rsi, 2
	jmp	$_260

$_262:	movzx	ecx, word ptr [rdi]
	imul	ecx, ecx, 16
	lea	rax, [rbp-0x98]
	mov	rsi, qword ptr [rax+rcx]
$_263:	test	rsi, rsi
	jz	$_265
	xor	ecx, ecx
	test	byte ptr [rdi+0x2], 0x01
	jz	$_264
	mov	rcx, qword ptr [rbp-0x58]
$_264:	xor	r8d, r8d
	mov	rdx, rcx
	mov	rcx, rsi
	call	qword ptr [rdi+0x10]
	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_263

$_265:	inc	ebx
	add	rdi, 24
	jmp	$_259

$_266:	lea	rcx, [strings+rip]
	mov	edx, 2
	mov	rcx, qword ptr [rcx+0x218]
	call	$_235
	lea	rcx, [strings+rip]
	xor	edx, edx
	mov	rcx, qword ptr [rcx+0x220]
	call	$_235
	xor	ebx, ebx
$_267:	cmp	ebx, dword ptr [rbp-0x24]
	jnc	$_269
	mov	rcx, qword ptr [rbp-0x8]
	mov	rdi, qword ptr [rcx+rbx*8]
	test	byte ptr [rdi+0x15], 0x01
	jz	$_268
	test	byte ptr [rdi+0x15], 0x08
	jnz	$_268
	mov	rcx, rdi
	call	$_213
$_268:	inc	ebx
	jmp	$_267

$_269:	call	LstNL
	mov	rcx, qword ptr [rbp-0x8]
	call	MemFree@PLT
$_270:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ListingDirective:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	esi, ecx
	imul	ebx, esi, 24
	add	rbx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rbx+0x4]
	inc	esi
	add	rbx, 24
	jmp	$_281
$C0146:
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_271
	mov	byte ptr [ModuleInfo+0x1DB+rip], 1
$_271:	jmp	$C0148
$C0149:
	mov	byte ptr [ModuleInfo+0x1DC+rip], 1
	jmp	$C0148
$C014A:
$C014B:
	mov	byte ptr [ModuleInfo+0x1DB+rip], 0
	jmp	$C0148
$C014C:
$C014D:
	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jnz	$_272
	mov	byte ptr [ModuleInfo+0x1DC+rip], 0
	jmp	$C0148

$_272:	cmp	byte ptr [rbx], 8
	jz	$_273
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_283

$_273:	mov	rcx, qword ptr [rbx+0x8]
	call	SymLookup@PLT
	and	dword ptr [rax+0x14], 0xFFFFFEFF
	inc	esi
	add	rbx, 24
	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jge	$_275
	cmp	byte ptr [rbx], 44
	jz	$_274
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_283

$_274:	mov	ecx, dword ptr [ModuleInfo+0x220+rip]
	dec	ecx
	cmp	esi, ecx
	jnc	$_275
	inc	esi
	add	rbx, 24
$_275:	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jl	$_272
	jmp	$C0148
$C0155:
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_276
	mov	byte ptr [ModuleInfo+0x1DB+rip], 1
$_276:	mov	byte ptr [ModuleInfo+0x1DE+rip], 1
$C0157:
$C0158:
	mov	byte ptr [ModuleInfo+0x1DD+rip], 1
	jmp	$C0148
$C0159:
$C015A:
	mov	byte ptr [ModuleInfo+0x1DD+rip], 0
	jmp	$C0148
$C015B:
	xor	byte ptr [ModuleInfo+0x1DD+rip], 0x01
	jmp	$C0148
$C015C:
$C015D: cmp	byte ptr [rbx], 58
	jz	$C0148
	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_277
	mov	ecx, 2037
	call	asmerr@PLT
	jmp	$_283

$_277:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_278
	mov	rdx, qword ptr [rbx-0x10]
	mov	ecx, 7005
	call	asmerr@PLT
$_278:	jmp	$_280

$_279:	inc	esi
	add	rbx, 24
$_280:	cmp	byte ptr [rbx], 0
	jnz	$_279
	jmp	$C0148

$_281:	cmp	eax, 287
	jl	$C015D
	cmp	eax, 299
	jg	$C015D
	push	rax
	lea	r11, [$C015D+rip]
	movzx	eax, byte ptr [r11+rax-287+($C0162-$C015D)]
	sub	r11, rax
	pop	rax
	jmp	r11
$C0162:
	.byte $C015D-$C0149
	.byte $C015D-$C0158
	.byte $C015D-$C0146
	.byte $C015D-$C0155
	.byte $C015D-$C0157
	.byte $C015D-$C014C
	.byte $C015D-$C014A
	.byte $C015D-$C0159
	.byte $C015D-$C015A
	.byte $C015D-$C015B
	.byte $C015D-$C014D
	.byte $C015D-$C014B
	.byte $C015D-$C015C
$C0148:
	cmp	byte ptr [rbx+0x18], 0
	jz	$_282
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_283
$_282:
	xor	eax, eax
$_283:	leave
	pop	rbx
	pop	rsi
	ret

ListMacroDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	imul	ecx, dword ptr [rbp+0x10], 24
	add	rcx, qword ptr [rbp+0x18]
	cmp	byte ptr [rcx+0x18], 0
	jz	$_284
	mov	rdx, qword ptr [rcx+0x20]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_285

$_284:	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rcx+0x4], 12
	mov	eax, dword ptr [r11+rax+0x4]
	mov	dword ptr [ModuleInfo+0x1C8+rip], eax
	xor	eax, eax
$_285:	leave
	ret

LstInit:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 112
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_286
	mov	dword ptr [list_pos+rip], 0
$_286:	cmp	byte ptr [Options+0x92+rip], 0
	je	$_289
	mov	qword ptr [rsp+0x20], 0
	mov	r9d, 36
	mov	r8d, 2
	lea	rdx, [cp_logo+rip]
	lea	rcx, [rbp-0x40]
	call	tsprintf@PLT
	mov	ecx, dword ptr [ModuleInfo+0x1F4+rip]
	call	GetFName@PLT
	mov	rdx, rax
	lea	rcx, [DS0070+rip]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_287
	cmp	byte ptr [Options+0xA1+rip], 0
	jz	$_287
	lea	rcx, [DS0071+rip]
	jmp	$_288

$_287:	cmp	byte ptr [Options+0xA1+rip], 0
	jz	$_288
	lea	rcx, [DS0072+rip]
$_288:	mov	qword ptr [rsp+0x20], rdx
	lea	r9, [szTime+rip]
	lea	r8, [szDate+rip]
	lea	rdx, [rbp-0x40]
	call	LstPrintf
$_289:	leave
	ret


.SECTION .data
	.ALIGN	16

list_pos:
	.int   0x00000000

dots:
	.byte  0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E
	.byte  0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E
	.byte  0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E
	.byte  0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E
	.byte  0x00

strings:
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
	.quad  DS002B+0x6
	.quad  DS002C
	.quad  DS002D
	.quad  DS002E
	.quad  DS002F
	.quad  DS0030
	.quad  DS0031
	.quad  DS0032
	.quad  DS0033
	.quad  DS0034
	.quad  DS0035
	.quad  DS0036
	.quad  DS0037
	.quad  DS0038
	.quad  DS0039
	.quad  DS003A
	.quad  DS003B
	.quad  DS003C
	.quad  DS003D
	.quad  DS003E
	.quad  DS003F
	.quad  DS0040
	.quad  DS0041
	.quad  DS0042
	.quad  DS0043

maccap:
	.byte  0xB8, 0x01, 0xC0, 0x01, 0x00, 0x00

strcap:
	.byte  0xC8, 0x01, 0xD0, 0x01, 0x00, 0x00

reccap:
	.byte  0xD8, 0x01, 0xE0, 0x01, 0x00, 0x00

tdcap:
	.byte  0xE8, 0x01, 0xF0, 0x01, 0x00, 0x00

segcap:
	.byte  0xF8, 0x01, 0x00, 0x02, 0x00, 0x00

prccap:
	.byte  0x08, 0x02, 0x10, 0x02, 0x00, 0x00

cr:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.quad  maccap
	.quad  log_macro
	.quad  0x0000000000000001
	.quad  strcap
	.quad  log_struct
	.quad  0x0000000000000002
	.quad  reccap
	.quad  log_record
	.quad  0x0000000000000003
	.quad  tdcap
	.quad  log_typedef
	.quad  0x0000000000000004
	.quad  segcap
	.quad  log_segment
	.quad  0x0000000000010005
	.quad  0x0000000000000000
	.quad  log_group
	.quad  0x0000000000000006
	.quad  prccap
	.quad  log_proc

DS0044:
	.byte  0x25, 0x30, 0x38, 0x58, 0x00

DS0045:
	.byte  0x25, 0x30, 0x32, 0x58, 0x00

DS0046:
	.byte  0x25, 0x2D, 0x32, 0x30, 0x6C, 0x58, 0x00

DS0047:
	.byte  0x25, 0x2D, 0x32, 0x30, 0x58, 0x00

DS0048:
	.byte  0x0A, 0x00

DS0049:
	.byte  0x25, 0x75, 0x00

DS004A:
	.byte  0x3F, 0x00

DS004B:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x73, 0x00

DS004C:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x00

prefix: .int   0x00000000

DS004D:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x38, 0x58
	.byte  0x20, 0x28, 0x25, 0x75, 0x29, 0x00

DS004E:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x38, 0x58
	.byte  0x00

DS004F:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x38, 0x58
	.byte  0x20, 0x20, 0x20, 0x00

DS0050:
	.byte  0x5B, 0x25, 0x75, 0x5D, 0x00

DS0051:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x25, 0x36, 0x58, 0x20, 0x20
	.byte  0x25, 0x37, 0x58, 0x00

DS0052:
	.byte  0x20, 0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x36, 0x58
	.byte  0x20, 0x20, 0x25, 0x37, 0x58, 0x20, 0x20, 0x25
	.byte  0x30, 0x31, 0x36, 0x6C, 0x58, 0x20, 0x25, 0x73
	.byte  0x00

DS0053:
	.byte  0x20, 0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x36, 0x58
	.byte  0x20, 0x20, 0x25, 0x37, 0x58, 0x20, 0x20, 0x25
	.byte  0x30, 0x38, 0x58, 0x20, 0x25, 0x73, 0x00

DS0054:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x25, 0x38, 0x75, 0x20, 0x20, 0x25, 0x73
	.byte  0x00

DS0055:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x00

DS0056:
	.byte  0x33, 0x32, 0x20, 0x42, 0x69, 0x74, 0x20, 0x20
	.byte  0x20, 0x25, 0x30, 0x38, 0x58, 0x20, 0x00

DS0057:
	.byte  0x36, 0x34, 0x20, 0x42, 0x69, 0x74, 0x20, 0x20
	.byte  0x20, 0x25, 0x30, 0x38, 0x58, 0x20, 0x00

DS0058:
	.byte  0x31, 0x36, 0x20, 0x42, 0x69, 0x74, 0x20, 0x20
	.byte  0x20, 0x25, 0x30, 0x34, 0x58, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x00

DS0059:
	.byte  0x25, 0x2D, 0x37, 0x73, 0x20, 0x25, 0x2D, 0x38
	.byte  0x73, 0x00

DS005A:
	.byte  0x27, 0x25, 0x73, 0x27, 0x00

DS005B:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20, 0x25
	.byte  0x2D, 0x36, 0x73, 0x20, 0x25, 0x30, 0x34, 0x58
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x2D, 0x38
	.byte  0x73, 0x20, 0x00

DS005C:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20, 0x25
	.byte  0x2D, 0x36, 0x73, 0x20, 0x25, 0x30, 0x38, 0x58
	.byte  0x20, 0x25, 0x2D, 0x38, 0x73, 0x20, 0x00

DS005D:
	.byte  0x25, 0x30, 0x2A, 0x58, 0x20, 0x00

DS005E:
	.byte  0x25, 0x2D, 0x39, 0x73, 0x00

DS005F:
	.byte  0x25, 0x2D, 0x39, 0x73, 0x20, 0x00

DS0060:
	.byte  0x2A, 0x25, 0x2D, 0x38, 0x73, 0x20, 0x00

DS0061:
	.byte  0x28, 0x25, 0x2E, 0x38, 0x73, 0x29, 0x20, 0x00

DS0062:
	.byte  0x20, 0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x25
	.byte  0x2D, 0x31, 0x37, 0x73, 0x20, 0x25, 0x73, 0x00

DS0063:
	.byte  0x20, 0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x25
	.byte  0x2D, 0x31, 0x37, 0x73, 0x20, 0x25, 0x73, 0x20
	.byte  0x25, 0x63, 0x20, 0x25, 0x30, 0x34, 0x58, 0x00

DS0064:
	.byte  0x25, 0x73, 0x5B, 0x25, 0x75, 0x5D, 0x00

DS0065:
	.byte  0x20, 0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x4C
	.byte  0x20, 0x25, 0x2D, 0x36, 0x73, 0x20, 0x25, 0x30
	.byte  0x38, 0x58, 0x20, 0x25, 0x73, 0x00

DS0066:
	.byte  0x20, 0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x4C
	.byte  0x20, 0x25, 0x2D, 0x36, 0x73, 0x20, 0x25, 0x30
	.byte  0x34, 0x58, 0x20, 0x20, 0x20, 0x20, 0x20, 0x25
	.byte  0x73, 0x00

DS0067:
	.byte  0x25, 0x2D, 0x31, 0x30, 0x73, 0x20, 0x00

DS0068:
	.byte  0x20, 0x25, 0x38, 0x58, 0x68, 0x20, 0x00

DS0069:
	.byte  0x20, 0x25, 0x6C, 0x58, 0x68, 0x20, 0x00

DS006A:
	.byte  0x2D, 0x25, 0x30, 0x38, 0x58, 0x68, 0x20, 0x00

DS006B:
	.byte  0x25, 0x73, 0x3D, 0x25, 0x75, 0x20, 0x00

DS006C:
	.byte  0x63, 0x6F, 0x75, 0x6E, 0x74, 0x00

DS006D:
	.byte  0x2A, 0x25, 0x73, 0x20, 0x00

DS006E:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x20, 0x25, 0x73, 0x00

DS006F:
	.byte  0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 0x73, 0x20
	.byte  0x20, 0x25, 0x73, 0x00

DS0070:
	.byte  0x25, 0x73, 0x20, 0x20, 0x25, 0x73, 0x20, 0x25
	.byte  0x73, 0x0A, 0x25, 0x73, 0x0A, 0x00

DS0071:
	.byte  0x25, 0x73, 0x20, 0x20, 0x25, 0x73, 0x20, 0x25
	.byte  0x73, 0x20, 0x2D, 0x20, 0x46, 0x69, 0x72, 0x73
	.byte  0x74, 0x20, 0x50, 0x61, 0x73, 0x73, 0x0A, 0x25
	.byte  0x73, 0x0A, 0x00

DS0072:
	.byte  0x0A, 0x25, 0x73, 0x20, 0x20, 0x25, 0x73, 0x20
	.byte  0x25, 0x73, 0x0A, 0x25, 0x73, 0x0A, 0x0A, 0x00


.SECTION .rodata
	.ALIGN	16

DS0000:
	.byte  0x42, 0x79, 0x74, 0x65, 0x00

DS0001:
	.byte  0x57, 0x6F, 0x72, 0x64, 0x00

DS0002:
	.byte  0x44, 0x57, 0x6F, 0x72, 0x64, 0x00

DS0003:
	.byte  0x46, 0x57, 0x6F, 0x72, 0x64, 0x00

DS0004:
	.byte  0x51, 0x57, 0x6F, 0x72, 0x64, 0x00

DS0005:
	.byte  0x54, 0x42, 0x79, 0x74, 0x65, 0x00

DS0006:
	.byte  0x50, 0x61, 0x72, 0x61, 0x00

DS0007:
	.byte  0x58, 0x6D, 0x6D, 0x57, 0x6F, 0x72, 0x64, 0x00

DS0008:
	.byte  0x59, 0x57, 0x6F, 0x72, 0x64, 0x00

DS0009:
	.byte  0x5A, 0x57, 0x6F, 0x72, 0x64, 0x00

DS000A:
	.byte  0x50, 0x61, 0x67, 0x65, 0x00

DS000B:
	.byte  0x4E, 0x65, 0x61, 0x72, 0x00

DS000C:
	.byte  0x4E, 0x65, 0x61, 0x72, 0x31, 0x36, 0x00

DS000D:
	.byte  0x4E, 0x65, 0x61, 0x72, 0x33, 0x32, 0x00

DS000E:
	.byte  0x4E, 0x65, 0x61, 0x72, 0x36, 0x34, 0x00

DS000F:
	.byte  0x46, 0x61, 0x72, 0x00

DS0010:
	.byte  0x46, 0x61, 0x72, 0x31, 0x36, 0x00

DS0011:
	.byte  0x46, 0x61, 0x72, 0x33, 0x32, 0x00

DS0012:
	.byte  0x46, 0x61, 0x72, 0x36, 0x34, 0x00

DS0013:
	.byte  0x4C, 0x20, 0x4E, 0x65, 0x61, 0x72, 0x00

DS0014:
	.byte  0x4C, 0x20, 0x4E, 0x65, 0x61, 0x72, 0x31, 0x36
	.byte  0x00

DS0015:
	.byte  0x4C, 0x20, 0x4E, 0x65, 0x61, 0x72, 0x33, 0x32
	.byte  0x00

DS0016:
	.byte  0x4C, 0x20, 0x4E, 0x65, 0x61, 0x72, 0x36, 0x34
	.byte  0x00

DS0017:
	.byte  0x4C, 0x20, 0x46, 0x61, 0x72, 0x00

DS0018:
	.byte  0x4C, 0x20, 0x46, 0x61, 0x72, 0x31, 0x36, 0x00

DS0019:
	.byte  0x4C, 0x20, 0x46, 0x61, 0x72, 0x33, 0x32, 0x00

DS001A:
	.byte  0x4C, 0x20, 0x46, 0x61, 0x72, 0x36, 0x34, 0x00

DS001B:
	.byte  0x50, 0x74, 0x72, 0x00

DS001C:
	.byte  0x50, 0x72, 0x6F, 0x63, 0x00

DS001D:
	.byte  0x46, 0x75, 0x6E, 0x63, 0x00

DS001E:
	.byte  0x4E, 0x75, 0x6D, 0x62, 0x65, 0x72, 0x00

DS001F:
	.byte  0x50, 0x72, 0x69, 0x76, 0x61, 0x74, 0x65, 0x00

DS0020:
	.byte  0x53, 0x74, 0x61, 0x63, 0x6B, 0x00

DS0021:
	.byte  0x50, 0x75, 0x62, 0x6C, 0x69, 0x63, 0x00

DS0022:
	.byte  0x43, 0x6F, 0x6D, 0x6D, 0x6F, 0x6E, 0x00

DS0023:
	.byte  0x45, 0x78, 0x74, 0x65, 0x72, 0x6E, 0x61, 0x6C
	.byte  0x00

DS0024:
	.byte  0x55, 0x6E, 0x64, 0x65, 0x66, 0x69, 0x6E, 0x65
	.byte  0x64, 0x00

DS0025:
	.byte  0x47, 0x52, 0x4F, 0x55, 0x50, 0x00

DS0026:
	.byte  0x4E, 0x6F, 0x20, 0x53, 0x65, 0x67, 0x00

DS0027:
	.byte  0x54, 0x65, 0x78, 0x74, 0x00

DS0028:
	.byte  0x41, 0x6C, 0x69, 0x61, 0x73, 0x00

DS0029:
	.byte  0x41, 0x62, 0x73, 0x00

DS002A:
	.byte  0x43, 0x4F, 0x4D, 0x4D, 0x00

DS002B:
	.byte  0x56, 0x41, 0x52, 0x41, 0x52, 0x47, 0x00

DS002C:
	.byte  0x43, 0x00

DS002D:
	.byte  0x53, 0x59, 0x53, 0x43, 0x41, 0x4C, 0x4C, 0x00

DS002E:
	.byte  0x53, 0x54, 0x44, 0x43, 0x41, 0x4C, 0x4C, 0x00

DS002F:
	.byte  0x50, 0x41, 0x53, 0x43, 0x41, 0x4C, 0x00

DS0030:
	.byte  0x46, 0x4F, 0x52, 0x54, 0x52, 0x41, 0x4E, 0x00

DS0031:
	.byte  0x42, 0x41, 0x53, 0x49, 0x43, 0x00

DS0032:
	.byte  0x46, 0x41, 0x53, 0x54, 0x43, 0x41, 0x4C, 0x4C
	.byte  0x00

DS0033:
	.byte  0x56, 0x45, 0x43, 0x54, 0x4F, 0x52, 0x43, 0x41
	.byte  0x4C, 0x4C, 0x00

DS0034:
	.byte  0x57, 0x41, 0x54, 0x43, 0x41, 0x4C, 0x4C, 0x00

DS0035:
	.byte  0x41, 0x53, 0x4D, 0x43, 0x41, 0x4C, 0x4C, 0x00

DS0036:
	.byte  0x4D, 0x61, 0x63, 0x72, 0x6F, 0x73, 0x3A, 0x00

DS0037:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x4E, 0x20, 0x61, 0x20, 0x6D, 0x20, 0x65, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x54, 0x79, 0x70, 0x65, 0x00

DS0038:
	.byte  0x53, 0x74, 0x72, 0x75, 0x63, 0x74, 0x75, 0x72
	.byte  0x65, 0x73, 0x20, 0x61, 0x6E, 0x64, 0x20, 0x55
	.byte  0x6E, 0x69, 0x6F, 0x6E, 0x73, 0x3A, 0x00

DS0039:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x4E, 0x20, 0x61, 0x20, 0x6D, 0x20, 0x65, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x53, 0x69, 0x7A, 0x65, 0x2F, 0x4F, 0x66, 0x73
	.byte  0x20, 0x20, 0x20, 0x54, 0x79, 0x70, 0x65, 0x00

DS003A:
	.byte  0x52, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x73, 0x3A
	.byte  0x00

DS003B:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x4E, 0x20, 0x61, 0x20, 0x6D, 0x20, 0x65, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x57, 0x69, 0x64, 0x74, 0x68, 0x20, 0x20, 0x20
	.byte  0x23, 0x20, 0x66, 0x69, 0x65, 0x6C, 0x64, 0x73
	.byte  0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x53, 0x68, 0x69, 0x66, 0x74, 0x20, 0x20
	.byte  0x20, 0x57, 0x69, 0x64, 0x74, 0x68, 0x20, 0x20
	.byte  0x20, 0x20, 0x4D, 0x61, 0x73, 0x6B, 0x20, 0x20
	.byte  0x20, 0x49, 0x6E, 0x69, 0x74, 0x69, 0x61, 0x6C
	.byte  0x00

DS003C:
	.byte  0x54, 0x79, 0x70, 0x65, 0x73, 0x3A, 0x00

DS003D:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x4E, 0x20, 0x61, 0x20, 0x6D, 0x20, 0x65, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x53, 0x69, 0x7A, 0x65, 0x20, 0x20, 0x20, 0x20
	.byte  0x41, 0x74, 0x74, 0x72, 0x00

DS003E:
	.byte  0x53, 0x65, 0x67, 0x6D, 0x65, 0x6E, 0x74, 0x73
	.byte  0x20, 0x61, 0x6E, 0x64, 0x20, 0x47, 0x72, 0x6F
	.byte  0x75, 0x70, 0x73, 0x3A, 0x00

DS003F:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x4E, 0x20, 0x61, 0x20, 0x6D, 0x20, 0x65, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x53, 0x69, 0x7A, 0x65, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x4C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x20
	.byte  0x20, 0x20, 0x41, 0x6C, 0x69, 0x67, 0x6E, 0x20
	.byte  0x20, 0x20, 0x43, 0x6F, 0x6D, 0x62, 0x69, 0x6E
	.byte  0x65, 0x20, 0x43, 0x6C, 0x61, 0x73, 0x73, 0x00

DS0040:
	.byte  0x50, 0x72, 0x6F, 0x63, 0x65, 0x64, 0x75, 0x72
	.byte  0x65, 0x73, 0x2C, 0x20, 0x70, 0x61, 0x72, 0x61
	.byte  0x6D, 0x65, 0x74, 0x65, 0x72, 0x73, 0x20, 0x61
	.byte  0x6E, 0x64, 0x20, 0x6C, 0x6F, 0x63, 0x61, 0x6C
	.byte  0x73, 0x3A, 0x00

DS0041:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x4E, 0x20, 0x61, 0x20, 0x6D, 0x20, 0x65, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x54, 0x79, 0x70, 0x65, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x20, 0x20
	.byte  0x20, 0x20, 0x53, 0x65, 0x67, 0x6D, 0x65, 0x6E
	.byte  0x74, 0x20, 0x20, 0x4C, 0x65, 0x6E, 0x67, 0x74
	.byte  0x68, 0x00

DS0042:
	.byte  0x53, 0x79, 0x6D, 0x62, 0x6F, 0x6C, 0x73, 0x3A
	.byte  0x00

DS0043:
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x4E, 0x20, 0x61, 0x20, 0x6D, 0x20, 0x65, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	.byte  0x54, 0x79, 0x70, 0x65, 0x20, 0x20, 0x20, 0x20
	.byte  0x20, 0x20, 0x20, 0x56, 0x61, 0x6C, 0x75, 0x65
	.byte  0x20, 0x20, 0x20, 0x20, 0x20, 0x41, 0x74, 0x74
	.byte  0x72, 0x00



.att_syntax prefix
