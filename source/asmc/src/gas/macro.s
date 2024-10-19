
.intel_syntax noprefix

.global fill_placeholders
.global StoreMacro
.global CreateMacro
.global ReleaseMacroData
.global MacroDir
.global MacroLineQueue
.global PurgeDirective
.global MacroInit

.extern PreprocessLine
.extern MacroLocals
.extern LstWrite
.extern LstWriteSrcLine
.extern StringInit
.extern GetToken
.extern get_curr_srcfile
.extern PopInputStatus
.extern PushInputStatus
.extern GetTextLine
.extern sym_remove_table
.extern SymTables
.extern LclDup
.extern LclAlloc
.extern MemFree
.extern MemAlloc
.extern tstrstart
.extern tgetenv
.extern tstricmp
.extern tstrcpy
.extern tstrchr
.extern tstrlen
.extern tmemmove
.extern tmemcpy
.extern tsprintf
.extern asmerr
.extern MacroLevel
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern StringBuffer
.extern SymCmpFunc
.extern SymFind
.extern SymCreate
.extern SymAlloc


.SECTION .text
	.ALIGN	16

fill_placeholders:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	mov	rsi, qword ptr [rbp+0x30]
$_001:	cmp	byte ptr [rsi], 0
	jz	$_006
	cmp	byte ptr [rsi], 10
	jnz	$_004
	add	rsi, 2
	movzx	ebx, byte ptr [rsi-0x1]
	dec	ebx
	cmp	ebx, dword ptr [rbp+0x38]
	jc	$_002
	add	ebx, dword ptr [rbp+0x40]
	sub	ebx, dword ptr [rbp+0x38]
	mov	r8d, ebx
	lea	rdx, [DS0000+rip]
	mov	rcx, rdi
	call	tsprintf@PLT
	add	rdi, rax
	jmp	$_003

$_002:	mov	rdx, qword ptr [rbp+0x48]
	mov	rbx, qword ptr [rdx+rbx*8]
	test	rbx, rbx
	jz	$_003
	mov	rcx, rbx
	call	tstrlen@PLT
	mov	ecx, eax
	xchg	rsi, rbx
	rep movsb
	mov	rsi, rbx
$_003:	jmp	$_005

$_004:	movsb
$_005:	jmp	$_001

$_006:
	mov	byte ptr [rdi], 0
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_007:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 1
	mov	rbx, qword ptr [rbp+0x40]
$_008:	cmp	qword ptr [rbx], 0
	je	$_018
	mov	eax, dword ptr [rbp+0x38]
	cmp	word ptr [rbx+0x8], ax
	jz	$_009
	jmp	$_017

$_009:	movsxd	r8, dword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbx]
	mov	rcx, qword ptr [rbp+0x30]
	call	qword ptr [SymCmpFunc+rip]
	test	rax, rax
	jne	$_017
	cmp	dword ptr [rbp-0x4], 256
	jl	$_010
	mov	ecx, 1005
	call	asmerr@PLT
	jmp	$_018

$_010:	mov	rdi, qword ptr [rbp+0x30]
	mov	esi, dword ptr [rbp+0x38]
	add	rsi, rdi
	cmp	rdi, qword ptr [rbp+0x28]
	jz	$_011
	cmp	byte ptr [rdi-0x1], 38
	jnz	$_011
	dec	rdi
$_011:	cmp	byte ptr [rsi], 38
	jnz	$_012
	inc	rsi
$_012:	mov	eax, 10
	stosb
	cmp	rdi, rsi
	jc	$_015
	mov	rcx, rsi
	call	tstrlen@PLT
	lea	rcx, [rsi+rax]
	lea	rdx, [rcx+0x1]
	jmp	$_014

$_013:	mov	al, byte ptr [rcx]
	mov	byte ptr [rdx], al
	dec	rcx
	dec	rdx
$_014:	cmp	rcx, rsi
	jnc	$_013
	mov	eax, dword ptr [rbp-0x4]
	mov	byte ptr [rdi], al
	jmp	$_016

$_015:	mov	eax, dword ptr [rbp-0x4]
	stosb
	mov	rcx, rsi
	call	tstrlen@PLT
	lea	r8d, [eax+0x1]
	mov	rdx, rsi
	mov	rcx, rdi
	call	tmemmove@PLT
$_016:	mov	rax, rdi
	jmp	$_019

$_017:	inc	dword ptr [rbp-0x4]
	add	rbx, 16
	jmp	$_008

$_018:	xor	eax, eax
$_019:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_020:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	byte ptr [rbp-0x1], 0
	xor	edi, edi
	xor	ebx, ebx
	mov	rsi, qword ptr [rbp+0x28]
$_021:	cmp	byte ptr [rsi], 0
	je	$_046
	movzx	eax, byte ptr [rsi-0x1]
	test	byte ptr [r15+rax], 0x44
	jz	$_022
	inc	ah
$_022:	mov	ecx, eax
	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x04
	jz	$_024
$_023:	inc	rsi
	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x44
	jnz	$_023
	jmp	$_045

$_024:	test	byte ptr [r15+rax], 0x44
	jnz	$_025
	cmp	al, 46
	jnz	$_032
	cmp	byte ptr [ModuleInfo+0x1D4+rip], 0
	jz	$_032
	cmp	rsi, qword ptr [rbp+0x28]
	jz	$_025
	cmp	cl, 93
	jz	$_032
	test	ch, ch
	jnz	$_032
$_025:	mov	rdx, rsi
$_026:	inc	rsi
	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x44
	jnz	$_026
	xor	eax, eax
	cmp	rdx, qword ptr [rbp+0x28]
	jbe	$_027
	cmp	byte ptr [rdx-0x1], 38
	jz	$_028
$_027:	cmp	byte ptr [rsi], 38
	jnz	$_029
$_028:	inc	eax
$_029:	test	bl, bl
	jz	$_030
	test	eax, eax
	jz	$_031
$_030:	mov	rax, rsi
	sub	rax, rdx
	mov	r9, qword ptr [rbp+0x30]
	mov	r8d, eax
	mov	rcx, qword ptr [rbp+0x28]
	call	$_007
	test	rax, rax
	jz	$_031
	inc	rdi
	mov	rsi, rax
$_031:	jmp	$_045

$_032:	jmp	$_043

$_033:	test	bl, bl
	jnz	$_034
	movzx	eax, byte ptr [rsi+0x1]
	mov	edx, eax
	lea	rcx, [DS0001+rip]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_034
	inc	rsi
$_034:	jmp	$_044

$_035:	inc	bh
	jmp	$_044

$_036:	test	bh, bh
	jz	$_038
	cmp	byte ptr [rbp-0x1], bh
	jnz	$_037
	mov	bl, 0
$_037:	dec	bh
$_038:	jmp	$_044

$_039:	test	bl, bl
	jz	$_041
	cmp	bl, al
	jnz	$_040
	mov	bl, 0
$_040:	jmp	$_042

$_041:	mov	bl, al
	mov	byte ptr [rbp-0x1], bh
$_042:	jmp	$_044

$_043:	cmp	eax, 33
	jz	$_033
	cmp	eax, 60
	jz	$_035
	cmp	eax, 62
	jz	$_036
	cmp	eax, 34
	jz	$_039
	cmp	eax, 39
	jz	$_039
$_044:	inc	rsi
$_045:	jmp	$_021

$_046:
	mov	rax, rdi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

StoreMacro:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 4312
	mov	dword ptr [rbp-0x34], 0
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x50], rax
	mov	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x48], rax
	mov	byte ptr [rbp-0x10A9], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_047
	mov	byte ptr [rbp-0x10A9], 1
	call	MemAlloc@PLT
	jmp	$_048

$_047:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
$_048:	mov	qword ptr [rbp-0x60], rax
	mov	rsi, qword ptr [rbp+0x28]
	mov	rdi, qword ptr [rsi+0x68]
	mov	qword ptr [rbp-0x8], rdi
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	imul	eax, dword ptr [ModuleInfo+0x220+rip], 24
	add	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x10A8], rax
	cmp	dword ptr [rbp+0x40], 0
	je	$_072
	cmp	rbx, qword ptr [rbp-0x10A8]
	jnc	$_052
	mov	rax, rbx
	mov	word ptr [rdi], 1
$_049:	cmp	rax, qword ptr [rbp-0x10A8]
	jnc	$_051
	cmp	byte ptr [rax], 44
	jnz	$_050
	inc	word ptr [rdi]
$_050:	add	rax, 24
	jmp	$_049

$_051:	movzx	ecx, word ptr [rdi]
	imul	eax, ecx, 16
	mov	ecx, eax
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x8], rax
	jmp	$_053

$_052:
	mov	word ptr [rdi], 0
	mov	qword ptr [rdi+0x8], 0
$_053:	mov	rsi, qword ptr [rdi+0x8]
	mov	dword ptr [rbp-0x1C], 0
$_054:	cmp	rbx, qword ptr [rbp-0x10A8]
	jnc	$_072
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x18], rax
	movzx	edx, byte ptr [ModuleInfo+0x1D4+rip]
	movzx	eax, byte ptr [rax]
	cmp	al, 46
	jnz	$_055
	test	dl, dl
	jnz	$_056
$_055:	test	byte ptr [r15+rax], 0x40
	jz	$_057
$_056:	cmp	byte ptr [rbx], 9
	jnz	$_058
$_057:	mov	rdx, qword ptr [rbp-0x18]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_072

	jmp	$_059

$_058:	cmp	byte ptr [rbx], 8
	jz	$_059
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 7006
	call	asmerr@PLT
$_059:	mov	qword ptr [rsi], 0
	mov	byte ptr [rsi+0x8], 0
	mov	rcx, qword ptr [rbp-0x18]
	call	tstrlen@PLT
	imul	ecx, dword ptr [rbp-0x1C], 16
	mov	word ptr [rbp+rcx-0x1098], ax
	mov	rax, qword ptr [rbp-0x18]
	mov	qword ptr [rbp+rcx-0x10A0], rax
	inc	dword ptr [rbp-0x1C]
	mov	qword ptr [rbp+rcx-0x1090], 0
	add	rbx, 24
	cmp	byte ptr [rbx], 58
	jne	$_070
	add	rbx, 24
	cmp	byte ptr [rbx], 3
	jnz	$_062
	cmp	byte ptr [rbx+0x1], 45
	jnz	$_062
	add	rbx, 24
	cmp	byte ptr [rbx], 9
	jnz	$_060
	cmp	byte ptr [rbx+0x1], 60
	jz	$_061
$_060:	mov	ecx, 3016
	call	asmerr@PLT
	jmp	$_072

$_061:	mov	rcx, qword ptr [rbx+0x8]
	call	LclDup@PLT
	mov	qword ptr [rsi], rax
	add	rbx, 24
	jmp	$_070

$_062:	lea	rdx, [DS0002+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_063
	mov	byte ptr [rsi+0x8], 1
	add	rbx, 24
	jmp	$_070

$_063:	cmp	byte ptr [rbx], 7
	jnz	$_065
	cmp	dword ptr [rbx+0x4], 275
	jnz	$_065
	mov	rdx, qword ptr [rbp+0x28]
	or	byte ptr [rdx+0x38], 0x01
	cmp	byte ptr [rbx+0x18], 0
	jz	$_064
	mov	ecx, 2129
	call	asmerr@PLT
	jmp	$_072

$_064:	add	rbx, 24
	jmp	$_070

$_065:	cmp	byte ptr [rbx], 3
	jnz	$_067
	cmp	dword ptr [rbx+0x4], 511
	jnz	$_067
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_067
	cmp	rsi, qword ptr [rdi+0x8]
	jz	$_066
	mov	ecx, 2143
	call	asmerr@PLT
	jmp	$_072

$_066:	mov	rdx, qword ptr [rbp+0x28]
	or	byte ptr [rdx+0x38], 0x04
	add	rbx, 24
	jmp	$_070

$_067:	lea	rdx, [DS0003+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_069
	mov	rdx, qword ptr [rbp+0x28]
	or	byte ptr [rdx+0x38], 0x09
	cmp	byte ptr [rbx+0x18], 0
	jz	$_068
	mov	ecx, 2129
	call	asmerr@PLT
	jmp	$_072

$_068:	add	rbx, 24
	jmp	$_070

$_069:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_072

$_070:	cmp	rbx, qword ptr [rbp-0x10A8]
	jnc	$_071
	cmp	byte ptr [rbx], 44
	jz	$_071
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_072

$_071:	add	rbx, 24
	add	rsi, 16
	jmp	$_054

$_072:
	mov	dword ptr [rbp-0x38], 0
	lea	rax, [rdi+0x10]
	mov	qword ptr [rbp-0x30], rax
$_073:	mov	rcx, qword ptr [rbp-0x60]
	call	qword ptr [GetLine+rip]
	mov	qword ptr [rbp-0x10], rax
	test	rax, rax
	jnz	$_074
	mov	ecx, 1008
	call	asmerr@PLT
$_074:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_075
	and	byte ptr [ModuleInfo+0x1C6+rip], 0xFFFFFFFE
	mov	r8, qword ptr [rbp-0x60]
	xor	edx, edx
	mov	ecx, 8
	call	LstWrite@PLT
$_075:	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rbp-0x70], rax
	mov	dword ptr [rbp-0x58], 0
$_076:	mov	rcx, qword ptr [rbp-0x70]
	call	tstrstart@PLT
	mov	qword ptr [rbp-0x70], rax
	test	cl, cl
	jz	$_077
	cmp	cl, 59
	jnz	$_079
$_077:	cmp	dword ptr [rbp+0x40], 0
	jz	$_078
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 0
	mov	byte ptr [rax+0x9], 0
	mov	rdx, qword ptr [rbp-0x30]
	mov	qword ptr [rdx], rax
	mov	qword ptr [rbp-0x30], rax
$_078:	jmp	$_121

$_079:	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	mov	qword ptr [rbp-0x68], rax
	mov	byte ptr [rbp-0x54], 0
	mov	byte ptr [rbp-0x53], 0
	mov	byte ptr [rbp-0xA0], 0
	lea	rdx, [rbp-0x70]
	lea	rcx, [rbp-0xA0]
	call	GetToken@PLT
	cmp	eax, -1
	jnz	$_081
	cmp	byte ptr [rbp-0x10A9], 0
	jz	$_080
	mov	rcx, qword ptr [rbp-0x60]
	call	MemFree@PLT
$_080:	mov	rax, -1
	jmp	$_124

$_081:	mov	edx, 92
	mov	rcx, qword ptr [rbp-0x70]
	call	tstrchr@PLT
	test	rax, rax
	jz	$_086
	mov	rdi, qword ptr [rbp-0x70]
	mov	rax, rdi
	jmp	$_084

$_082:	mov	byte ptr [rbp-0x52], 0
	lea	rdx, [rbp-0x70]
	lea	rcx, [rbp-0x88]
	call	GetToken@PLT
	test	byte ptr [rbp-0x52], 0x01
	jz	$_083
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_083
	and	byte ptr [ModuleInfo+0x1C6+rip], 0xFFFFFFFE
	mov	r8, qword ptr [rbp-0x70]
	xor	edx, edx
	mov	ecx, 8
	call	LstWrite@PLT
$_083:	mov	rcx, qword ptr [rbp-0x70]
	call	tstrstart@PLT
	mov	qword ptr [rbp-0x70], rax
$_084:	cmp	byte ptr [rax], 0
	jz	$_085
	cmp	byte ptr [rax], 59
	jnz	$_082
$_085:	mov	qword ptr [rbp-0x70], rdi
$_086:	cmp	byte ptr [rbp-0xA0], 0
	je	$_076
	cmp	dword ptr [rbp-0x38], 0
	jne	$_097
	cmp	byte ptr [rbp-0xA0], 3
	jne	$_097
	cmp	dword ptr [rbp-0x9C], 510
	jne	$_097
	cmp	dword ptr [rbp+0x40], 0
	jnz	$_087
	jmp	$_121

$_087:	mov	rcx, qword ptr [rbp-0x70]
	call	tstrstart@PLT
	mov	qword ptr [rbp-0x70], rax
	test	cl, cl
	je	$_096
	cmp	cl, 59
	je	$_096
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	mov	qword ptr [rbp-0x68], rax
	lea	rdx, [rbp-0x70]
	lea	rcx, [rbp-0xA0]
	call	GetToken@PLT
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	movzx	edx, byte ptr [ModuleInfo+0x1D4+rip]
	movzx	eax, byte ptr [rcx]
	cmp	al, 46
	jnz	$_088
	test	dl, dl
	jnz	$_089
$_088:	test	byte ptr [r15+rax], 0x40
	jnz	$_089
	mov	rdx, rcx
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_096

	jmp	$_090

$_089:	cmp	byte ptr [rbp-0xA0], 8
	jz	$_090
	mov	rdx, rcx
	mov	ecx, 7006
	call	asmerr@PLT
$_090:	cmp	dword ptr [rbp-0x1C], 255
	jnz	$_091
	mov	ecx, 1005
	call	asmerr@PLT
	jmp	$_096

$_091:	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	tstrlen@PLT
	mov	edi, eax
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
	imul	ecx, dword ptr [rbp-0x1C], 16
	mov	word ptr [rbp+rcx-0x1098], di
	mov	qword ptr [rbp+rcx-0x10A0], rax
	mov	qword ptr [rbp+rcx-0x1090], 0
	inc	dword ptr [rbp-0x1C]
	mov	rcx, rdi
	mov	rdi, rax
	mov	rdx, rsi
	mov	rsi, qword ptr [ModuleInfo+0x188+rip]
	rep movsb
	mov	rsi, rdx
	mov	rdi, qword ptr [rbp-0x8]
	inc	word ptr [rdi+0x2]
	mov	rcx, qword ptr [rbp-0x70]
	call	tstrstart@PLT
	mov	qword ptr [rbp-0x70], rax
	cmp	cl, 44
	jnz	$_092
	inc	qword ptr [rbp-0x70]
	jmp	$_095

$_092:	movzx	edx, byte ptr [ModuleInfo+0x1D4+rip]
	movzx	eax, cl
	cmp	al, 46
	jnz	$_093
	test	dl, dl
	jnz	$_094
$_093:	test	byte ptr [r15+rax], 0x40
	jz	$_095
$_094:	mov	rdx, qword ptr [rbp-0x70]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_096

$_095:	jmp	$_087

$_096:	jmp	$_121

$_097:	mov	dword ptr [rbp-0x38], 1
	mov	rdx, qword ptr [rbp-0x70]
	cmp	byte ptr [rbp-0xA0], 58
	jnz	$_098
	dec	rdx
	mov	qword ptr [rbp-0x10], rdx
	jmp	$_119

$_098:	cmp	byte ptr [rbp-0xA0], 3
	jnz	$_108
	cmp	dword ptr [rbp-0x9C], 474
	jz	$_099
	cmp	dword ptr [rbp-0x9C], 409
	jnz	$_103
$_099:	cmp	dword ptr [rbp-0x34], 0
	jnz	$_102
	jmp	$_101

$_100:	inc	rdx
$_101:	movzx	eax, byte ptr [rdx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_100
	test	al, al
	jz	$_102
	cmp	al, 59
	jz	$_102
	mov	rdx, qword ptr [rbp+0x28]
	or	byte ptr [rdx+0x38], 0x02
$_102:	jmp	$_107

$_103:	cmp	dword ptr [rbp-0x9C], 475
	jnz	$_106
	cmp	dword ptr [rbp-0x34], 0
	jz	$_104
	dec	dword ptr [rbp-0x34]
	jmp	$_105

$_104:	jmp	$_122

$_105:	jmp	$_107

$_106:	cmp	byte ptr [rbp-0x9F], 1
	jnz	$_107
	inc	dword ptr [rbp-0x34]
$_107:	jmp	$_119

$_108:	cmp	byte ptr [rbp-0xA0], 1
	jnz	$_109
	cmp	byte ptr [rdx], 38
	jne	$_119
$_109:	mov	byte ptr [rbp-0xA0], 0
	mov	rcx, qword ptr [rbp-0x70]
	jmp	$_111

$_110:	add	rcx, 1
$_111:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_110
	xchg	rax, rcx
	mov	qword ptr [rbp-0x70], rax
	test	cl, cl
	jz	$_112
	cmp	cl, 59
	jnz	$_113
$_112:	jmp	$_117

$_113:	movzx	edi, byte ptr [rax-0x1]
	lea	rdx, [rbp-0x70]
	lea	rcx, [rbp-0xA0]
	call	GetToken@PLT
	cmp	eax, -1
	jnz	$_114
	jmp	$_117

$_114:	mov	rdx, qword ptr [rbp-0x70]
	cmp	byte ptr [rbp-0xA0], 1
	jz	$_115
	cmp	byte ptr [rbp-0xA0], 3
	jnz	$_116
$_115:	cmp	edi, 38
	jz	$_116
	cmp	byte ptr [rdx], 38
	jz	$_116
	jmp	$_117

$_116:	jmp	$_109

$_117:	cmp	byte ptr [rbp-0xA0], 3
	jnz	$_119
	cmp	dword ptr [rbp-0x9C], 473
	jz	$_118
	cmp	byte ptr [rbp-0x9F], 1
	jnz	$_119
$_118:	inc	dword ptr [rbp-0x34]
$_119:	cmp	dword ptr [rbp+0x40], 0
	jz	$_121
	xor	eax, eax
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_120
	lea	rdx, [rbp-0x10A0]
	mov	rcx, qword ptr [rbp-0x10]
	call	$_020
$_120:	mov	byte ptr [rbp-0x10AA], al
	mov	rcx, qword ptr [rbp-0x10]
	call	tstrlen@PLT
	mov	edi, eax
	add	eax, 16
	mov	ecx, eax
	call	LclAlloc@PLT
	mov	rdx, qword ptr [rbp-0x30]
	mov	qword ptr [rdx], rax
	mov	qword ptr [rax], 0
	mov	cl, byte ptr [rbp-0x10AA]
	mov	byte ptr [rax+0x8], cl
	inc	edi
	mov	qword ptr [rbp-0x30], rax
	mov	r8d, edi
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [rax+0x9]
	call	tmemcpy@PLT
$_121:	jmp	$_073

$_122:	mov	rdx, qword ptr [rbp+0x28]
	or	byte ptr [rdx+0x14], 0x02
	and	byte ptr [rdx+0x38], 0xFFFFFFEF
	cmp	byte ptr [rbp-0x10A9], 0
	jz	$_123
	mov	rcx, qword ptr [rbp-0x60]
	call	MemFree@PLT
$_123:	xor	eax, eax
$_124:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CreateMacro:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	call	SymCreate@PLT
	test	rax, rax
	jz	$_125
	mov	byte ptr [rax+0x18], 9
	and	byte ptr [rax+0x38], 0xFFFFFFFC
	mov	rbx, rax
	mov	ecx, 32
	call	LclAlloc@PLT
	mov	rcx, rax
	mov	rax, rbx
	mov	qword ptr [rax+0x68], rcx
	xor	edx, edx
	mov	word ptr [rcx], dx
	mov	word ptr [rcx+0x2], dx
	mov	qword ptr [rcx+0x8], rdx
	mov	qword ptr [rcx+0x10], rdx
	mov	dword ptr [rcx+0x18], edx
$_125:	leave
	pop	rbx
	ret

ReleaseMacroData:
	mov	rax, rcx
	and	byte ptr [rax+0x38], 0xFFFFFFFE
	mov	rcx, qword ptr [rax+0x68]
	xor	eax, eax
	mov	word ptr [rcx], ax
	mov	word ptr [rcx+0x2], ax
	mov	qword ptr [rcx+0x8], rax
	mov	qword ptr [rcx+0x10], rax
	mov	dword ptr [rcx+0x18], eax
	ret

MacroDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rdx
	mov	rdi, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	SymFind@PLT
	mov	rsi, rax
	test	rax, rax
	jnz	$_126
	mov	rcx, rdi
	call	CreateMacro
	mov	rsi, rax
	jmp	$_131

$_126:	cmp	byte ptr [rsi+0x18], 9
	jz	$_131
	cmp	byte ptr [rsi+0x18], 0
	jz	$_129
	cmp	byte ptr [rsi+0x18], 2
	jnz	$_127
	cmp	byte ptr [ModuleInfo+0x337+rip], 0
	jnz	$_127
	mov	rbx, rdx
	mov	rcx, rdi
	call	SymAlloc@PLT
	mov	qword ptr [rsi+0x40], rax
	or	byte ptr [rsi+0x16], 0x10
	mov	rsi, rax
	mov	qword ptr [rsi+0x58], rbx
	and	byte ptr [rsi+0x38], 0xFFFFFFFC
	jmp	$_130

	jmp	$_128

$_127:	mov	rdx, rdi
	mov	ecx, 2005
	call	asmerr@PLT
	jmp	$_137

$_128:	jmp	$_131

$_129:	mov	rdx, rsi
	lea	rcx, [SymTables+rip]
	call	sym_remove_table@PLT
$_130:	mov	byte ptr [rsi+0x18], 9
	mov	ecx, 32
	call	LclAlloc@PLT
	mov	qword ptr [rsi+0x68], rax
	mov	rdi, rax
	mov	ecx, 32
	xor	eax, eax
	rep stosb
$_131:	mov	rdi, qword ptr [rsi+0x68]
	call	get_curr_srcfile@PLT
	mov	dword ptr [rdi+0x18], eax
	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_132
	test	byte ptr [rsi+0x14], 0x40
	jz	$_134
$_132:	cmp	qword ptr [rdi+0x10], 0
	jz	$_133
	mov	rcx, rsi
	call	ReleaseMacroData
	and	byte ptr [rsi+0x38], 0xFFFFFFFD
	or	byte ptr [rsi+0x14], 0x40
$_133:	mov	dword ptr [rbp-0x4], 1
	jmp	$_135

$_134:	mov	dword ptr [rbp-0x4], 0
$_135:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_136
	call	LstWriteSrcLine@PLT
$_136:	inc	dword ptr [rbp+0x28]
	mov	r9d, dword ptr [rbp-0x4]
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, rsi
	call	StoreMacro
$_137:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

GeLineQueue:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rax, qword ptr [ModuleInfo+0xC8+rip]
	test	rax, rax
	je	$_150
	mov	rsi, rax
	mov	rax, qword ptr [rsi]
	mov	qword ptr [ModuleInfo+0xC8+rip], rax
	lea	rdx, [rsi+0x8]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcpy@PLT
	mov	rdi, rax
	mov	rcx, rsi
	call	MemFree@PLT
	xor	ebx, ebx
$_138:	mov	ecx, 4294967295
	xor	eax, eax
	repne scasb
	neg	ecx
	dec	rdi
	dec	ecx
	je	$_149
$_139:	dec	rdi
	cmp	byte ptr [rdi], 32
	ja	$_140
	dec	rcx
	jnz	$_139
$_140:	mov	byte ptr [rdi+0x1], al
	mov	al, byte ptr [rdi]
	jmp	$_147

$_141:	inc	bl
$_142:	mov	al, 32
	mov	word ptr [rdi+0x1], ax
	add	rdi, 2
	mov	rsi, qword ptr [ModuleInfo+0xC8+rip]
	test	rsi, rsi
	jz	$_149
	mov	rax, qword ptr [rsi]
	mov	qword ptr [ModuleInfo+0xC8+rip], rax
	lea	rdx, [rsi+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	rcx, rsi
	call	MemFree@PLT
	jmp	$_138

$_143:	inc	bh
	jmp	$_142

$_144:	cmp	bl, 1
	jbe	$_149
	dec	bl
	jmp	$_148

$_145:	cmp	bh, 1
	jbe	$_149
	dec	bh
$_146:	test	ebx, ebx
	jnz	$_142
	jmp	$_149

$_147:	cmp	al, 40
	jz	$_141
	cmp	al, 44
	jz	$_142
	cmp	al, 58
	jz	$_142
	cmp	al, 38
	jz	$_142
	cmp	al, 124
	jz	$_142
	cmp	al, 123
	jz	$_143
	cmp	al, 41
	jz	$_144
	cmp	al, 125
	jz	$_145
	jmp	$_146

$_148:	jmp	$_138

$_149:	mov	rax, qword ptr [rbp+0x28]
$_150:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

MacroLineQueue:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	lea	rcx, [rbp-0x20]
	call	PushInputStatus@PLT
	mov	qword ptr [rbp-0x30], rax
	inc	dword ptr [ModuleInfo+0x210+rip]
	mov	rax, qword ptr [GetLine+rip]
	mov	qword ptr [rbp-0x28], rax
	lea	rax, [GeLineQueue+rip]
	mov	qword ptr [GetLine+rip], rax
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	qword ptr [GetLine+rip]
	test	rax, rax
	jz	$_151
	mov	rcx, qword ptr [rbp-0x30]
	call	PreprocessLine@PLT
$_151:	mov	rax, qword ptr [rbp-0x28]
	mov	qword ptr [GetLine+rip], rax
	dec	dword ptr [ModuleInfo+0x210+rip]
	lea	rcx, [rbp-0x20]
	call	PopInputStatus@PLT
	leave
	ret

PurgeDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	inc	dword ptr [rbp+0x28]
$_152:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 8
	jz	$_153
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_159

$_153:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rsi, rax
	test	rax, rax
	jnz	$_154
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_159

$_154:	cmp	byte ptr [rsi+0x18], 9
	jz	$_155
	lea	rdx, [DS0004+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_159

$_155:	mov	rcx, rsi
	call	ReleaseMacroData
	or	byte ptr [rsi+0x14], 0x40
	or	byte ptr [rsi+0x38], 0x10
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jge	$_158
	cmp	byte ptr [rbx], 44
	jnz	$_156
	cmp	byte ptr [rbx+0x18], 0
	jnz	$_157
$_156:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_159

$_157:	inc	dword ptr [rbp+0x28]
$_158:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jl	$_152
	xor	eax, eax
$_159:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

EnvironFunc:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rdx
	mov	rax, qword ptr [rcx+0x18]
	mov	rcx, qword ptr [rax]
	call	tgetenv@PLT
	mov	rsi, rax
	mov	rdi, rbx
	mov	byte ptr [rdi], 0
	test	rsi, rsi
	jz	$_161
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	ecx, eax
	cmp	eax, 2048
	jc	$_160
	mov	ecx, 2047
$_160:	rep movsb
	mov	byte ptr [rdi], 0
$_161:	xor	eax, eax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

MacroInit:
	mov	qword ptr [rsp+0x8], rcx
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [MacroLevel+rip], 0
	mov	dword ptr [MacroLocals+rip], 0
	cmp	dword ptr [rbp+0x18], 0
	jnz	$_162
	call	StringInit@PLT
	lea	rcx, [DS0005+rip]
	call	CreateMacro
	or	byte ptr [rax+0x14], 0x22
	or	byte ptr [rax+0x38], 0x02
	lea	rcx, [EnvironFunc+rip]
	mov	qword ptr [rax+0x28], rcx
	mov	rax, qword ptr [rax+0x68]
	mov	word ptr [rax], 1
	mov	rdi, rax
	mov	ecx, 16
	call	LclAlloc@PLT
	mov	qword ptr [rdi+0x8], rax
	mov	qword ptr [rax], 0
	mov	byte ptr [rax+0x8], 1
$_162:	xor	eax, eax
	leave
	pop	rdi
	ret


.SECTION .data
	.ALIGN	16

GetLine:
	.quad  GetTextLine

DS0000:
	.byte  0x3F, 0x3F, 0x25, 0x30, 0x34, 0x58, 0x00

DS0001:
	.byte  0x3C, 0x3E, 0x22, 0x27, 0x00

DS0002:
	.byte  0x52, 0x45, 0x51, 0x00

DS0003:
	.byte  0x56, 0x41, 0x52, 0x41, 0x52, 0x47, 0x4D, 0x4C
	.byte  0x00

DS0004:
	.byte  0x6D, 0x61, 0x63, 0x72, 0x6F, 0x20, 0x6E, 0x61
	.byte  0x6D, 0x65, 0x00

DS0005:
	.byte  0x40, 0x45, 0x6E, 0x76, 0x69, 0x72, 0x6F, 0x6E
	.byte  0x00


.att_syntax prefix
