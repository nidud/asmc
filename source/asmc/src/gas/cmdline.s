
.intel_syntax noprefix

.global init_win64
.global CollectLinkOption
.global CollectLinkObject
.global ParseCmdline
.global CmdlineFini
.global Options
.global DefaultDir

.extern banner_printed
.extern cp_logo
.extern GetFNamePart
.extern MemDup
.extern MemFree
.extern MemAlloc
.extern tgetenv
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tprintf
.extern write_options
.extern asmerr
.extern undef_name
.extern define_name
.extern exit
.extern rewind
.extern ftell
.extern fseek
.extern fread
.extern fclose
.extern fopen


.SECTION .text
	.ALIGN	16

$_001:	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	jmp	$_002
$C0002: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0000+rip]
	call	define_name@PLT
$C0003: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0002+rip]
	call	define_name@PLT
$C0004: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0003+rip]
	call	define_name@PLT
$C0005:
$C0006: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0004+rip]
	call	define_name@PLT
$C0007: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0005+rip]
	call	define_name@PLT
$C0008: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0006+rip]
	call	define_name@PLT
$C0009: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0007+rip]
	call	define_name@PLT
$C000A: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0008+rip]
	call	define_name@PLT
$C000B: lea	rdx, [DS0001+rip]
	lea	rcx, [DS0009+rip]
	call	define_name@PLT
$C000C: lea	rdx, [DS0001+rip]
	lea	rcx, [DS000A+rip]
	call	define_name@PLT
	jmp	$C000D

$_002:	cmp	ecx, 0
	jl	$C000D
	cmp	ecx, 10
	jg	$C000D
	lea	rax, [$C000D+rip]
	movzx	ecx, byte ptr [rax+rcx+($C000E-$C000D)]
	sub	rax, rcx
	jmp	rax
$C000E:
	.byte $C000D-$C000C
	.byte $C000D-$C000B
	.byte $C000D-$C000A
	.byte $C000D-$C0009
	.byte $C000D-$C0008
	.byte $C000D-$C0007
	.byte $C000D-$C0006
	.byte $C000D-$C0005
	.byte $C000D-$C0004
	.byte $C000D-$C0003
	.byte $C000D-$C0002
$C000D: leave
	ret

$_003:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rax, [cpu_option+rip]
	mov	eax, dword ptr [rax+rcx*4]
	and	dword ptr [Options+0xB4+rip], 0xFFFF0007
	or	dword ptr [Options+0xB4+rip], eax
	test	edx, edx
	jz	$_004
	cmp	dword ptr [Options+0xB4+rip], 32
	jc	$_004
	or	byte ptr [Options+0xB4+rip], 0x08
$_004:	call	$_001
	leave
	ret

init_win64:
	sub	rsp, 40
	mov	edx, 1
	mov	ecx, 10
	call	$_003
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS000B+rip]
	call	define_name@PLT
	mov	dword ptr [Options+0xA8+rip], 3
	mov	dword ptr [Options+0xB0+rip], 7
	mov	byte ptr [Options+0xCA+rip], 32
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS000C+rip]
	call	define_name@PLT
	mov	dword ptr [Options+0xA4+rip], 3
	mov	dword ptr [Options+0xAC+rip], 2
	mov	dword ptr [Options+0xB8+rip], 3
	add	rsp, 40
	ret

$_005:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	lea	rsi, [rdi+0x8]
$_006:	cmp	qword ptr [rsi], 0
	jz	$_007
	movsq
	jmp	$_006

$_007:
	movsq
	mov	rax, qword ptr [rcx]
	leave
	pop	rdi
	pop	rsi
	ret

$_008:
	xor	eax, eax
	xor	edx, edx
	mov	al, byte ptr [rcx]
$_009:	cmp	al, 48
	jc	$_010
	cmp	al, 57
	ja	$_010
	imul	edx, edx, 10
	sub	al, 48
	add	edx, eax
	inc	rcx
	mov	al, byte ptr [rcx]
	jmp	$_009

$_010:
	mov	dword ptr [OptValue+rip], edx
	mov	rax, rcx
	ret

$_011:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rdx
	mov	rdi, rcx
	cmp	byte ptr [rsi], 0
	jnz	$_013
	mov	rcx, rdi
	call	$_005
	mov	rbx, rax
	test	rbx, rbx
	jz	$_012
	mov	rsi, rbx
$_012:	jmp	$_014

$_013:	cmp	byte ptr [rsi], 61
	jnz	$_014
	inc	rsi
$_014:	cmp	byte ptr [rsi], 0
	jnz	$_015
	mov	rdx, qword ptr [rdi]
	mov	ecx, 1006
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_016

$_015:	mov	rax, rsi
$_016:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_017:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rcx, qword ptr [rbp+0x20]
	call	tstrlen@PLT
	lea	ecx, [eax+0x10]
	call	MemAlloc@PLT
	mov	rsi, rax
	mov	qword ptr [rsi], 0
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [rsi+0x8]
	call	tstrcpy@PLT
	mov	ecx, dword ptr [rbp+0x18]
	lea	rdx, [Options+rip]
	mov	rax, qword ptr [rdx+rcx*8+0x58]
	test	rax, rax
	jz	$_020
$_018:	cmp	qword ptr [rax], 0
	jz	$_019
	mov	rax, qword ptr [rax]
	jmp	$_018

$_019:	mov	qword ptr [rax], rsi
	jmp	$_021

$_020:	mov	qword ptr [rdx+rcx*8+0x58], rsi
$_021:	leave
	pop	rsi
	ret

$_022:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	mov	rsi, rdx
	mov	ebx, ecx
	cmp	byte ptr [rsi], 61
	jnz	$_023
	inc	rsi
$_023:	mov	rcx, rsi
	call	GetFNamePart@PLT
	mov	rdi, rax
	lea	rdx, [DefaultDir+rip]
	cmp	byte ptr [rdi], 0
	jnz	$_026
	cmp	rbx, 4
	jnc	$_025
	cmp	byte ptr [rsi], 0
	jz	$_025
	mov	rcx, qword ptr [rdx+rbx*8]
	mov	rdi, rdx
	test	rcx, rcx
	jz	$_024
	call	MemFree@PLT
$_024:	mov	rcx, rsi
	call	MemDup@PLT
	mov	qword ptr [rdi+rbx*8], rax
$_025:	jmp	$_028

$_026:	mov	byte ptr [rbp-0x104], 0
	mov	rdx, qword ptr [rdx+rbx*8]
	cmp	rsi, rdi
	jnz	$_027
	cmp	ebx, 4
	jnc	$_027
	test	rdx, rdx
	jz	$_027
	lea	rcx, [rbp-0x104]
	call	tstrcpy@PLT
$_027:	mov	rdx, rsi
	lea	rcx, [rbp-0x104]
	call	tstrcat@PLT
	lea	rdx, [Options+rip]
	lea	rdi, [rdx+rbx*8+0x10]
	mov	rcx, qword ptr [rdi]
	call	MemFree@PLT
	lea	rcx, [rbp-0x104]
	call	MemDup@PLT
	mov	qword ptr [rdi], rax
$_028:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_029:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rdx
	movzx	eax, byte ptr [rdi]
	cmp	al, 46
	jz	$_030
	test	byte ptr [r15+rax], 0x44
	jnz	$_030
	xor	eax, eax
$_030:	test	al, al
	jz	$_031
	lea	rax, [Options+rip]
	lea	rsi, [rax+rcx*8+0x10]
	mov	rcx, qword ptr [rsi]
	call	MemFree@PLT
	mov	rcx, rdi
	call	MemDup@PLT
	mov	qword ptr [rsi], rax
	jmp	$_032

$_031:	mov	ecx, 1006
	call	asmerr@PLT
$_032:	leave
	pop	rdi
	pop	rsi
	ret

$_033:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	lea	rsi, [DS000D+rip]
	mov	rdi, rcx
	call	fopen@PLT
	mov	qword ptr [rbp-0x8], rax
	test	rax, rax
	jnz	$_034
	mov	rdx, qword ptr [rbp+0x28]
	mov	ecx, 1000
	call	asmerr@PLT
	xor	eax, eax
	jmp	$_036

$_034:	mov	qword ptr [rbp-0x10], 0
	mov	edx, 2
	xor	esi, esi
	mov	rdi, qword ptr [rbp-0x8]
	call	fseek@PLT
	test	rax, rax
	jnz	$_035
	mov	rdi, qword ptr [rbp-0x8]
	call	ftell@PLT
	test	rax, rax
	jz	$_035
	mov	rbx, rax
	lea	ecx, [rax+0x1]
	call	MemAlloc@PLT
	mov	qword ptr [rbp-0x10], rax
	mov	byte ptr [rax+rbx], 0
	mov	rdi, qword ptr [rbp-0x8]
	call	rewind@PLT
	mov	rcx, qword ptr [rbp-0x8]
	mov	edx, ebx
	mov	esi, 1
	mov	rdi, qword ptr [rbp-0x10]
	call	fread@PLT
$_035:	mov	rdi, qword ptr [rbp-0x8]
	call	fclose@PLT
	mov	rax, qword ptr [rbp-0x10]
$_036:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_037:
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 0
	mov	rsi, rdx
	mov	rdi, rcx
$_038:	mov	al, byte ptr [rsi]
	cmp	al, 34
	jnz	$_043
	inc	rsi
$_039:	cmp	dword ptr [rbp+0x38], 0
	jz	$_042
	cmp	byte ptr [rsi], 0
	jz	$_042
	mov	eax, dword ptr [rsi]
	cmp	al, 34
	jnz	$_040
	inc	rsi
	jmp	$_042

$_040:	cmp	al, 92
	jnz	$_041
	cmp	ah, 34
	jnz	$_041
	inc	rsi
$_041:	movsb
	dec	dword ptr [rbp+0x38]
	jmp	$_039

$_042:	jmp	$_048

$_043:	cmp	dword ptr [rbp+0x38], 0
	jz	$_048
	mov	al, byte ptr [rsi]
	test	al, al
	jz	$_048
	cmp	al, 13
	jz	$_048
	cmp	al, 10
	jz	$_048
	cmp	al, 32
	jz	$_044
	cmp	al, 9
	jnz	$_045
$_044:	cmp	byte ptr [rbp+0x40], 64
	jnz	$_048
$_045:	cmp	byte ptr [rbp+0x40], 0
	jnz	$_046
	cmp	al, 45
	jnz	$_046
	cmp	eax, 1818585133
	jnz	$_048
$_046:	cmp	al, 61
	jnz	$_047
	cmp	byte ptr [rbp+0x40], 36
	jnz	$_047
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_047
	mov	dword ptr [rbp-0x4], 1
	movsb
	mov	al, byte ptr [rsi]
	cmp	al, 34
	jnz	$_047
	jmp	$_038

$_047:	movsb
	dec	dword ptr [rbp+0x38]
	jmp	$_043

$_048:
	mov	byte ptr [rdi], 0
	mov	rax, rsi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_049:
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rcx, rbx
	call	tstrlen@PLT
	lea	ecx, [eax+0x10]
	call	MemAlloc@PLT
	mov	rdx, qword ptr [rbp+0x20]
	mov	rcx, qword ptr [rdx]
	test	rcx, rcx
	jz	$_052
$_050:	cmp	qword ptr [rcx], 0
	jz	$_051
	mov	rcx, qword ptr [rcx]
	jmp	$_050

$_051:	mov	qword ptr [rcx], rax
	jmp	$_053

$_052:	mov	qword ptr [rdx], rax
$_053:	mov	qword ptr [rax], 0
	mov	rdx, rbx
	lea	rcx, [rax+0x8]
	call	tstrcpy@PLT
	leave
	pop	rbx
	ret

CollectLinkOption:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rdx, [Options+0x78+rip]
	call	$_049
	leave
	ret

CollectLinkObject:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rdx, [Options+0x80+rip]
	call	$_049
	leave
	ret

$_054:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, rcx
	mov	rdi, rdx
	mov	rbx, qword ptr [rsi]
	mov	eax, dword ptr [rbx]
	cmp	al, 68
	jnz	$_055
	mov	r9d, 36
	mov	r8d, 256
	lea	rdx, [rbx+0x1]
	mov	rcx, rdi
	call	$_037
	mov	qword ptr [rsi], rax
	mov	rdx, rdi
	mov	ecx, 1
	call	$_017
	jmp	$_184

$_055:	cmp	al, 73
	jnz	$_056
	mov	r9d, 64
	mov	r8d, 256
	lea	rdx, [rbx+0x1]
	mov	rcx, rdi
	call	$_037
	mov	qword ptr [rsi], rax
	mov	rdx, rdi
	mov	ecx, 2
	call	$_017
	jmp	$_184

$_056:	xor	r9d, r9d
	mov	r8d, 16
	mov	rdx, rbx
	mov	rcx, rdi
	call	$_037
	mov	qword ptr [rsi], rax
	mov	eax, dword ptr [rdi]
	test	ah, ah
	jnz	$_057
	and	eax, 0xFF
	jmp	$_058

$_057:	test	eax, 0xFF0000
	jnz	$_058
	and	eax, 0xFFFF
$_058:	jmp	$_146

$_059:	mov	eax, dword ptr [rdi+0x4]
	cmp	al, 58
	jnz	$_060
	test	ah, ah
	jnz	$_061
$_060:	mov	rdx, rdi
	mov	ecx, 1006
	call	asmerr@PLT
$_061:	mov	eax, dword ptr [rdi+0x5]
	xor	ebx, ebx
	jmp	$_069

$_062:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS000E+rip]
	call	define_name@PLT
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS000F+rip]
	call	define_name@PLT
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0010+rip]
	call	define_name@PLT
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0011+rip]
	call	define_name@PLT
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0012+rip]
	call	define_name@PLT
	inc	ebx
$_063:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0013+rip]
	call	define_name@PLT
	inc	ebx
$_064:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0014+rip]
	call	define_name@PLT
	inc	ebx
$_065:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0002+rip]
	call	define_name@PLT
	inc	ebx
$_066:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0003+rip]
	call	define_name@PLT
	inc	ebx
	jmp	$_070

$_067:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0015+rip]
	call	define_name@PLT
	jmp	$_070

$_068:	mov	rdx, rdi
	mov	ecx, 1006
	call	asmerr@PLT
	jmp	$_070

$_069:	cmp	eax, 894981697
	je	$_062
	cmp	eax, 844650049
	je	$_063
	cmp	eax, 5789249
	je	$_064
	cmp	eax, 843404115
	jz	$_065
	cmp	eax, 4543315
	jz	$_066
	cmp	eax, 842219849
	jz	$_067
	jmp	$_068

$_070:	mov	byte ptr [Options+0xD3+rip], bl
	jmp	$_184

$_071:	or	byte ptr [Options+0xCA+rip], 0x40
	jmp	$_184

$_072:	cmp	dword ptr [Options+0xA8+rip], 3
	jnz	$_073
	or	byte ptr [Options+0xD0+rip], 0x02
$_073:	jmp	$_184

$_074:	mov	byte ptr [Options+0xDB+rip], 1
	jmp	$_184

$_075:	mov	dword ptr [Options+0xA4+rip], 2
	mov	dword ptr [Options+0xA8+rip], 0
	jmp	$_184

$_076:	mov	byte ptr [Options+0xDB+rip], 1
	mov	byte ptr [Options+0x96+rip], 1
$_077:	mov	byte ptr [Options+rip], 1
$_078:	mov	byte ptr [banner_printed+rip], 1
	jmp	$_184

$_079:	mov	byte ptr [Options+0xDB+rip], 1
	mov	dword ptr [Options+0xA4+rip], 0
	mov	dword ptr [Options+0xA8+rip], 0
	jmp	$_184

$_080:	mov	byte ptr [Options+0x94+rip], 1
	mov	byte ptr [Options+0x95+rip], 0
	jmp	$_184

$_081:	or	byte ptr [Options+0xCA+rip], 0x01
	jmp	$_184

$_082:	mov	byte ptr [Options+0x94+rip], 0
	mov	byte ptr [Options+0x95+rip], 1
	jmp	$_184

$_083:	mov	byte ptr [Options+0x94+rip], 0
	mov	byte ptr [Options+0x95+rip], 0
	jmp	$_184

$_084:	mov	byte ptr [Options+0xD8+rip], 1
	jmp	$_184

$_085:	mov	byte ptr [Options+0xD6+rip], 1
	jmp	$_184

$_086:	mov	byte ptr [Options+0xC+rip], 1
	jmp	$_184

$_087:	mov	edx, 1
	mov	ecx, 10
	call	$_003
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS000C+rip]
	call	define_name@PLT
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS000B+rip]
	call	define_name@PLT
	or	byte ptr [Options+0xCA+rip], 0x20
	mov	dword ptr [Options+0xB0+rip], 7
	mov	dword ptr [Options+0xA4+rip], 3
	mov	dword ptr [Options+0xA8+rip], 3
	mov	dword ptr [Options+0xAC+rip], 2
	mov	dword ptr [Options+0xB8+rip], 3
	jmp	$_184

$_088:	mov	rbx, qword ptr [rsi]
	jmp	$_090

$_089:	inc	rbx
$_090:	cmp	byte ptr [rbx], 0
	jnz	$_089
	mov	qword ptr [rsi], rbx
	jmp	$_184

$_091:	mov	byte ptr [Options+0xD5+rip], 1
	jmp	$_184

$_092:	mov	byte ptr [Options+0xD5+rip], 0
	jmp	$_184

$_093:	mov	byte ptr [Options+0xD4+rip], 3
	jmp	$_184

$_094:	mov	byte ptr [Options+0xD1+rip], 1
	jmp	$_184

$_095:	mov	dword ptr [Options+0xAC+rip], 7
	jmp	$_184

$_096:	mov	dword ptr [Options+0xAC+rip], 2
	jmp	$_184

$_097:	mov	dword ptr [Options+0xAC+rip], 8
	jmp	$_184

$_098:	call	write_options@PLT
	xor	edi, edi
	call	exit@PLT
$_099:	or	byte ptr [Options+0xD0+rip], 0x01
	jmp	$_184

$_100:	mov	byte ptr [Options+0xD7+rip], 2
	jmp	$_184

$_101:	mov	byte ptr [Options+0xD7+rip], 1
	jmp	$_184

$_102:	mov	byte ptr [Options+0x88+rip], 1
	jmp	$_184

$_103:	xor	r9d, r9d
	mov	r8d, 36
	mov	edx, 2
	lea	rcx, [cp_logo+rip]
	call	tprintf@PLT
	lea	rcx, [DS0016+rip]
	call	tprintf@PLT
	xor	edi, edi
	call	exit@PLT
$_104:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0017+rip]
	call	define_name@PLT
$_105:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0018+rip]
	call	define_name@PLT
	jmp	$_184

$_106:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0017+rip]
	call	define_name@PLT
$_107:	mov	byte ptr [Options+0xD2+rip], 1
$_108:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS0019+rip]
	call	define_name@PLT
	jmp	$_184

$_109:	mov	byte ptr [Options+0xCE+rip], 3
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001A+rip]
	call	define_name@PLT
$_110:	lea	rcx, [DS000C+rip]
	call	undef_name@PLT
	mov	dword ptr [Options+0xAC+rip], 7
	mov	dword ptr [Options+0xB8+rip], 2
	cmp	dword ptr [Options+0xA8+rip], 3
	jz	$_111
	mov	dword ptr [Options+0xA8+rip], 2
$_111:	mov	dword ptr [Options+0xA4+rip], 0
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001B+rip]
	call	define_name@PLT
	mov	byte ptr [Options+0xDB+rip], 1
	jmp	$_184

$_112:	mov	byte ptr [Options+0xCE+rip], 2
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001C+rip]
	call	define_name@PLT
	jmp	$_110

$_113:	mov	byte ptr [Options+0xCF+rip], 1
	mov	byte ptr [Options+0x90+rip], 1
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001D+rip]
	call	define_name@PLT
	jmp	$_110

$_114:	mov	byte ptr [Options+0xF+rip], 1
	jmp	$_184

$_115:	jmp	$_184

$_116:	mov	byte ptr [Options+0xA1+rip], 1
	jmp	$_184

$_117:	mov	byte ptr [Options+0x9B+rip], 1
	jmp	$_184

$_118:	mov	byte ptr [Options+0xA0+rip], 1
	jmp	$_184

$_119:	or	byte ptr [Options+0xD0+rip], 0x04
	jmp	$_184

$_120:	mov	byte ptr [Options+0xDA+rip], 1
	jmp	$_184

$_121:	mov	byte ptr [Options+0x9A+rip], 1
	jmp	$_184

$_122:	mov	byte ptr [Options+0xA3+rip], 1
	jmp	$_184

$_123:	mov	byte ptr [Options+0xD+rip], 0
	jmp	$_184

$_124:	or	byte ptr [Options+0xCA+rip], 0x02
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001E+rip]
	call	define_name@PLT
	jmp	$_184

$_125:	mov	byte ptr [Options+0xE+rip], 1
	jmp	$_184

$_126:	jmp	$_184

$_127:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001F+rip]
	call	define_name@PLT
	mov	byte ptr [Options+0x1+rip], 1
	mov	byte ptr [Options+0x2+rip], 4
	mov	byte ptr [Options+0x8B+rip], 1
	mov	byte ptr [Options+0x3+rip], 2
	jmp	$_184

$_128:	mov	byte ptr [Options+0xC7+rip], 1
	jmp	$_184

$_129:	mov	byte ptr [Options+0xA2+rip], 1
	jmp	$_184

$_130:	mov	dword ptr [Options+0xB8+rip], 0
	jmp	$_184

$_131:	mov	dword ptr [Options+0xB8+rip], 1
	jmp	$_184

$_132:	mov	byte ptr [Options+0x98+rip], 1
	jmp	$_184

$_133:	mov	byte ptr [Options+0x1+rip], 1
	jmp	$_184

$_134:	mov	byte ptr [Options+0x89+rip], 1
	jmp	$_184

$_135:	mov	byte ptr [Options+0x8A+rip], 1
	jmp	$_184

$_136:	mov	byte ptr [Options+0x8B+rip], 1
	jmp	$_184

$_137:	mov	byte ptr [Options+0x8C+rip], 1
	jmp	$_184

$_138:	mov	byte ptr [Options+0x8D+rip], 1
	jmp	$_184

$_139:	mov	byte ptr [Options+0xC6+rip], 1
	jmp	$_184

$_140:	mov	byte ptr [Options+0xC9+rip], 1
	jmp	$_184

$_141:	mov	byte ptr [Options+0x8F+rip], 0
	jmp	$_184

$_142:	mov	byte ptr [Options+0x8F+rip], 1
	jmp	$_184

$_143:	mov	byte ptr [Options+0x8F+rip], 2
	jmp	$_184

$_144:	mov	byte ptr [Options+0x90+rip], 1
	jmp	$_184

$_145:	mov	byte ptr [Options+0x91+rip], 1
	jmp	$_184

	jmp	$_147

$_146:	cmp	eax, 1751347809
	je	$_059
	cmp	eax, 1702064993
	je	$_071
	cmp	eax, 1869903201
	je	$_072
	cmp	eax, 99
	je	$_074
	cmp	eax, 1717989219
	je	$_075
	cmp	eax, 20549
	je	$_076
	cmp	eax, 113
	je	$_077
	cmp	eax, 1869377390
	je	$_078
	cmp	eax, 7235938
	je	$_079
	cmp	eax, 28739
	je	$_080
	cmp	eax, 29507
	je	$_081
	cmp	eax, 30019
	je	$_082
	cmp	eax, 30787
	je	$_083
	cmp	eax, 1853124452
	je	$_084
	cmp	eax, 1650749029
	je	$_085
	cmp	eax, 29029
	je	$_086
	cmp	eax, 912682085
	je	$_087
	cmp	eax, 1869771365
	je	$_088
	cmp	eax, 1667854438
	je	$_091
	cmp	eax, 762277478
	je	$_092
	cmp	eax, 1835102822
	je	$_093
	cmp	eax, 25927
	je	$_094
	cmp	eax, 29255
	je	$_095
	cmp	eax, 29511
	je	$_096
	cmp	eax, 30279
	je	$_097
	cmp	eax, 1818585133
	je	$_098
	cmp	eax, 104
	je	$_098
	cmp	eax, 1701670760
	je	$_099
	cmp	eax, 1952736361
	je	$_100
	cmp	eax, 6579305
	je	$_101
	cmp	eax, 1802398060
	je	$_102
	cmp	eax, 1869049708
	je	$_103
	cmp	eax, 6575181
	je	$_104
	cmp	eax, 21581
	je	$_105
	cmp	eax, 6571085
	je	$_106
	cmp	eax, 1768714094
	je	$_107
	cmp	eax, 17485
	je	$_108
	cmp	eax, 6514032
	je	$_109
	cmp	eax, 25968
	je	$_110
	cmp	eax, 6776176
	je	$_112
	cmp	eax, 6579568
	je	$_113
	cmp	eax, 114
	je	$_114
	cmp	eax, 24915
	je	$_115
	cmp	eax, 26195
	je	$_116
	cmp	eax, 26451
	je	$_117
	cmp	eax, 28243
	je	$_118
	cmp	eax, 1667331187
	je	$_119
	cmp	eax, 1987279219
	je	$_120
	cmp	eax, 30803
	je	$_121
	cmp	eax, 1701208435
	je	$_122
	cmp	eax, 119
	je	$_123
	cmp	eax, 29559
	je	$_124
	cmp	eax, 22615
	je	$_125
	cmp	eax, 913205623
	je	$_126
	cmp	eax, 14170
	je	$_127
	cmp	eax, 88
	je	$_128
	cmp	eax, 26202
	je	$_129
	cmp	eax, 3171962
	je	$_130
	cmp	eax, 3237498
	je	$_131
	cmp	eax, 26458
	je	$_132
	cmp	eax, 25690
	je	$_133
	cmp	eax, 6515834
	je	$_134
	cmp	eax, 6581370
	je	$_135
	cmp	eax, 6712442
	je	$_136
	cmp	eax, 7367802
	je	$_137
	cmp	eax, 7564410
	je	$_138
	cmp	eax, 6647386
	je	$_139
	cmp	eax, 29530
	je	$_140
	cmp	eax, 3175546
	je	$_141
	cmp	eax, 3241082
	je	$_142
	cmp	eax, 3306618
	je	$_143
	cmp	eax, 6650490
	je	$_144
	cmp	eax, 7567994
	je	$_145
$_147:	mov	qword ptr [rsi], rbx
	mov	eax, dword ptr [rbx]
	cmp	al, 101
	jnz	$_148
	lea	rcx, [rbx+0x1]
	call	$_008
	mov	qword ptr [rsi], rax
	mov	eax, dword ptr [OptValue+rip]
	mov	dword ptr [Options+0x8+rip], eax
	jmp	$_184

$_148:	cmp	al, 87
	jnz	$_152
	lea	rcx, [rbx+0x1]
	call	$_008
	mov	qword ptr [rsi], rax
	cmp	dword ptr [OptValue+rip], 0
	jge	$_149
	mov	rdx, rbx
	mov	ecx, 8000
	call	asmerr@PLT
	jmp	$_151

$_149:	cmp	dword ptr [OptValue+rip], 3
	jle	$_150
	mov	rdx, rbx
	mov	ecx, 4008
	call	asmerr@PLT
	jmp	$_151

$_150:	mov	eax, dword ptr [OptValue+rip]
	mov	byte ptr [Options+0xD+rip], al
$_151:	jmp	$_184

$_152:	and	eax, 0xFFFF
	mov	dword ptr [rbp-0x8], eax
	lea	rcx, [rbx+0x2]
	call	$_008
	mov	qword ptr [rsi], rax
	jmp	$_168

$_153:	mov	eax, dword ptr [OptValue+rip]
	mov	dword ptr [Options+0xBC+rip], eax
	or	byte ptr [Options+0xCA+rip], 0x02
	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001E+rip]
	call	define_name@PLT
	jmp	$_184

$_154:	xor	ecx, ecx
$_155:	mov	eax, 1
	shl	eax, cl
	inc	ecx
	cmp	eax, 4096
	jbe	$_156
	mov	rdx, rbx
	mov	ecx, 1006
	call	asmerr@PLT
$_156:	cmp	eax, dword ptr [OptValue+rip]
	jnz	$_155
	dec	ecx
	mov	byte ptr [Options+0xCD+rip], cl
	jmp	$_184

$_157:	xor	ecx, ecx
$_158:	mov	eax, 1
	shl	eax, cl
	inc	ecx
	cmp	eax, 32
	jbe	$_159
	mov	rdx, rbx
	mov	ecx, 1006
	call	asmerr@PLT
$_159:	cmp	eax, dword ptr [OptValue+rip]
	jnz	$_158
	dec	ecx
	mov	byte ptr [Options+0xC8+rip], cl
	jmp	$_184

$_160:	lea	rdx, [DS0001+rip]
	lea	rcx, [DS001F+rip]
	call	define_name@PLT
	mov	byte ptr [Options+0x1+rip], 1
	mov	byte ptr [Options+0x2+rip], 1
	mov	byte ptr [Options+0x3+rip], 2
	mov	eax, dword ptr [OptValue+rip]
	test	eax, eax
	jz	$_167
	cmp	eax, 3
	jbe	$_166
	cmp	byte ptr [rbx+0x3], 0
	jz	$_162
	cmp	byte ptr [rbx+0x4], 0
	jz	$_161
	mov	rdx, rbx
	mov	ecx, 1006
	call	asmerr@PLT
$_161:	movzx	eax, word ptr [rbx+0x2]
	sub	eax, 12336
	mov	byte ptr [Options+0x3+rip], al
	shr	eax, 8
$_162:	cmp	eax, 5
	jnz	$_163
	mov	byte ptr [Options+0x2+rip], 2
	jmp	$_165

$_163:	cmp	eax, 8
	jnz	$_164
	mov	byte ptr [Options+0x2+rip], 4
	mov	byte ptr [Options+0x8B+rip], 1
	jmp	$_165

$_164:	mov	rdx, rbx
	mov	ecx, 1006
	call	asmerr@PLT
$_165:	jmp	$_167

$_166:	mov	byte ptr [Options+0x3+rip], al
$_167:	jmp	$_184

	jmp	$_169

$_168:	cmp	dword ptr [rbp-0x8], 29559
	je	$_153
	cmp	dword ptr [rbp-0x8], 28755
	je	$_154
	cmp	dword ptr [rbp-0x8], 28762
	je	$_157
	cmp	dword ptr [rbp-0x8], 26970
	je	$_160
$_169:	mov	r9d, 36
	mov	r8d, 256
	lea	rdx, [rbx+0x2]
	mov	rcx, rdi
	call	$_037
	mov	qword ptr [rsi], rax
	mov	eax, dword ptr [rbp-0x8]
	jmp	$_174

$_170:	mov	rdx, rdi
	mov	ecx, 8
	call	$_029
	jmp	$_184

$_171:	mov	rdx, rdi
	mov	ecx, 7
	call	$_029
	jmp	$_184

$_172:	mov	rdx, rdi
	mov	ecx, 5
	call	$_029
	jmp	$_184

$_173:	mov	rdx, rdi
	mov	ecx, 6
	call	$_029
	jmp	$_184

	jmp	$_175

$_174:	cmp	eax, 25454
	jz	$_170
	cmp	eax, 25710
	jz	$_171
	cmp	eax, 28014
	jz	$_172
	cmp	eax, 29806
	jz	$_173
$_175:	mov	r9d, 64
	mov	r8d, 256
	lea	rdx, [rbx+0x2]
	mov	rcx, rdi
	call	$_037
	mov	qword ptr [rsi], rax
	mov	eax, dword ptr [rbp-0x8]
	jmp	$_178

$_176:	mov	byte ptr [Options+0x93+rip], 1
	mov	rdx, rdi
	mov	ecx, 4
	call	$_022
	jmp	$_184

$_177:	mov	byte ptr [Options+0x92+rip], 1
	mov	rdx, rdi
	mov	ecx, 2
	call	$_022
	jmp	$_184

	jmp	$_179

$_178:	cmp	eax, 25670
	jz	$_176
	cmp	eax, 27718
	jz	$_177
$_179:	lea	rdx, [rbx+0x2]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_011
	test	rax, rax
	jz	$_183
	mov	rbx, rax
	mov	r9d, 64
	mov	r8d, 256
	mov	rdx, rbx
	mov	rcx, rdi
	call	$_037
	mov	qword ptr [rsi], rax
	mov	eax, dword ptr [rbp-0x8]
	cmp	eax, 27714
	jnz	$_180
	mov	rcx, rdi
	call	MemDup@PLT
	mov	qword ptr [Options+0x70+rip], rax
	jmp	$_184

$_180:	cmp	eax, 26950
	jnz	$_181
	mov	rdx, rdi
	xor	ecx, ecx
	call	$_017
	jmp	$_184

$_181:	cmp	eax, 28486
	jnz	$_182
	mov	rdx, rdi
	mov	ecx, 1
	call	$_022
	jmp	$_184

$_182:	cmp	eax, 30534
	jnz	$_183
	mov	rdx, rdi
	mov	ecx, 3
	call	$_022
	jmp	$_184

$_183:	lea	rdx, [rbx-0x3]
	mov	ecx, 1006
	call	asmerr@PLT
$_184:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ParseCmdline:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	mov	rsi, rcx
	mov	rdi, rdx
	xor	ebx, ebx
$_185:	cmp	ebx, 4
	jnc	$_187
	lea	rdx, [Options+rip]
	mov	rcx, qword ptr [rdx+rbx*8+0x10]
	test	rcx, rcx
	jz	$_186
	mov	qword ptr [rdx+rbx*8+0x10], 0
	call	MemFree@PLT
$_186:	inc	ebx
	jmp	$_185

$_187:
	mov	rbx, qword ptr [rsi]
$_188:	test	rbx, rbx
	je	$_200
	mov	eax, dword ptr [rbx]
	jmp	$_198

$_189:	inc	rbx
	jmp	$_199

$_190:	mov	rcx, rsi
	call	$_005
	mov	rbx, rax
	jmp	$_199

$_191:	inc	rbx
	mov	r9d, 64
	mov	r8d, 259
	mov	rdx, rbx
	lea	rcx, [rbp-0x104]
	call	$_037
	mov	qword ptr [rsi], rax
	xor	ebx, ebx
	cmp	byte ptr [rbp-0x104], 0
	jz	$_192
	lea	rcx, [rbp-0x104]
	call	tgetenv@PLT
	mov	rbx, rax
$_192:	test	rbx, rbx
	jnz	$_193
	lea	rcx, [rbp-0x104]
	call	$_033
	mov	rbx, rax
$_193:	jmp	$_199

$_194:	cmp	byte ptr [Options+0x88+rip], 0
	jnz	$_195
	inc	rbx
	mov	qword ptr [rsi], rbx
	lea	rdx, [rbp-0x104]
	mov	rcx, rsi
	call	$_054
	inc	dword ptr [rdi]
	mov	rbx, qword ptr [rsi]
	jmp	$_199

$_195:	mov	r9d, 64
	mov	r8d, 259
	mov	rdx, rbx
	lea	rcx, [rbp-0x104]
	call	$_037
	mov	rbx, rax
	mov	qword ptr [rsi], rbx
	cmp	byte ptr [Options+0x88+rip], 0
	jz	$_196
	lea	rcx, [rbp-0x104]
	call	CollectLinkOption
	jmp	$_197

$_196:	lea	rcx, [rbp-0x104]
	call	MemDup@PLT
	mov	qword ptr [Options+0x10+rip], rax
	inc	dword ptr [rdi]
	jmp	$_201

$_197:	jmp	$_199

$_198:	cmp	al, 13
	je	$_189
	cmp	al, 10
	je	$_189
	cmp	al, 9
	je	$_189
	cmp	al, 32
	je	$_189
	cmp	al, 0
	je	$_190
	cmp	al, 64
	je	$_191
	cmp	al, 45
	je	$_194
	jmp	$_195

$_199:	jmp	$_188

$_200:	mov	qword ptr [rsi], rbx
	xor	eax, eax
$_201:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

CmdlineFini:
	push	rsi
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	xor	ebx, ebx
	lea	rsi, [DefaultDir+rip]
	lea	rdi, [Options+rip]
	jmp	$_203

$_202:	xor	eax, eax
	mov	rcx, qword ptr [rsi+rbx*8]
	mov	qword ptr [rsi+rbx*8], rax
	mov	qword ptr [rdi+rbx*8+0x10], rax
	call	MemFree@PLT
	inc	ebx
$_203:	cmp	ebx, 4
	jc	$_202
	xor	ebx, ebx
	jmp	$_207

$_204:	lea	rdx, [Options+rip]
	mov	rdi, qword ptr [rdx+rbx*8+0x58]
	jmp	$_206

$_205:	mov	rsi, qword ptr [rdi]
	mov	rcx, rdi
	call	MemFree@PLT
	mov	rdi, rsi
$_206:	test	rdi, rdi
	jnz	$_205
	lea	rdx, [Options+rip]
	mov	qword ptr [rdx+rbx*8+0x58], 0
	inc	ebx
$_207:	cmp	ebx, 3
	jc	$_204
	leave
	pop	rbx
	pop	rsi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

Options:
	.quad  0x0000000000000000
	.quad  0x0000020000000032
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000100000000
	.quad  0x0000000100000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000040000000001
	.quad  0x0003040000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000

DefaultDir:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

OptValue: .int	 0x00000000

cpu_option:
	.byte  0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte  0x20, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte  0x40, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte  0x60, 0x00, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00
	.byte  0x60, 0x05, 0x00, 0x00, 0x60, 0x0D, 0x00, 0x00
	.byte  0x70, 0x00, 0x00, 0x00

DS0000:
	.byte  0x5F, 0x5F, 0x50, 0x36, 0x34, 0x5F, 0x5F, 0x00

DS0001:
	.byte  0x31, 0x00

DS0002:
	.byte  0x5F, 0x5F, 0x53, 0x53, 0x45, 0x32, 0x5F, 0x5F
	.byte  0x00

DS0003:
	.byte  0x5F, 0x5F, 0x53, 0x53, 0x45, 0x5F, 0x5F, 0x00

DS0004:
	.byte  0x5F, 0x5F, 0x50, 0x36, 0x38, 0x36, 0x5F, 0x5F
	.byte  0x00

DS0005:
	.byte  0x5F, 0x5F, 0x50, 0x35, 0x38, 0x36, 0x5F, 0x5F
	.byte  0x00

DS0006:
	.byte  0x5F, 0x5F, 0x50, 0x34, 0x38, 0x36, 0x5F, 0x5F
	.byte  0x00

DS0007:
	.byte  0x5F, 0x5F, 0x50, 0x33, 0x38, 0x36, 0x5F, 0x5F
	.byte  0x00

DS0008:
	.byte  0x5F, 0x5F, 0x50, 0x32, 0x38, 0x36, 0x5F, 0x5F
	.byte  0x00

DS0009:
	.byte  0x5F, 0x5F, 0x50, 0x31, 0x38, 0x36, 0x5F, 0x5F
	.byte  0x00

DS000A:
	.byte  0x5F, 0x5F, 0x50, 0x38, 0x36, 0x5F, 0x5F, 0x00

DS000B:
	.byte  0x5F, 0x57, 0x49, 0x4E, 0x36, 0x34, 0x00

DS000C:
	.byte  0x5F, 0x5F, 0x55, 0x4E, 0x49, 0x58, 0x5F, 0x5F
	.byte  0x00

DS000D:
	.byte  0x72, 0x62, 0x00

DS000E:
	.byte  0x5F, 0x5F, 0x41, 0x56, 0x58, 0x35, 0x31, 0x32
	.byte  0x42, 0x57, 0x5F, 0x5F, 0x00

DS000F:
	.byte  0x5F, 0x5F, 0x41, 0x56, 0x58, 0x35, 0x31, 0x32
	.byte  0x43, 0x44, 0x5F, 0x5F, 0x00

DS0010:
	.byte  0x5F, 0x5F, 0x41, 0x56, 0x58, 0x35, 0x31, 0x32
	.byte  0x44, 0x51, 0x5F, 0x5F, 0x00

DS0011:
	.byte  0x5F, 0x5F, 0x41, 0x56, 0x58, 0x35, 0x31, 0x32
	.byte  0x46, 0x5F, 0x5F, 0x00

DS0012:
	.byte  0x5F, 0x5F, 0x41, 0x56, 0x58, 0x35, 0x31, 0x32
	.byte  0x56, 0x4C, 0x5F, 0x5F, 0x00

DS0013:
	.byte  0x5F, 0x5F, 0x41, 0x56, 0x58, 0x32, 0x5F, 0x5F
	.byte  0x00

DS0014:
	.byte  0x5F, 0x5F, 0x41, 0x56, 0x58, 0x5F, 0x5F, 0x00

DS0015:
	.byte  0x5F, 0x4D, 0x5F, 0x49, 0x58, 0x38, 0x36, 0x5F
	.byte  0x46, 0x50, 0x00

DS0016:
	.byte  0x0A, 0x00

DS0017:
	.byte  0x5F, 0x44, 0x45, 0x42, 0x55, 0x47, 0x00

DS0018:
	.byte  0x5F, 0x4D, 0x54, 0x00

DS0019:
	.byte  0x5F, 0x4D, 0x53, 0x56, 0x43, 0x52, 0x54, 0x00

DS001A:
	.byte  0x5F, 0x5F, 0x43, 0x55, 0x49, 0x5F, 0x5F, 0x00

DS001B:
	.byte  0x5F, 0x5F, 0x50, 0x45, 0x5F, 0x5F, 0x00

DS001C:
	.byte  0x5F, 0x5F, 0x47, 0x55, 0x49, 0x5F, 0x5F, 0x00

DS001D:
	.byte  0x5F, 0x5F, 0x44, 0x4C, 0x4C, 0x5F, 0x5F, 0x00

DS001E:
	.byte  0x5F, 0x55, 0x4E, 0x49, 0x43, 0x4F, 0x44, 0x45
	.byte  0x00

DS001F:
	.byte  0x5F, 0x5F, 0x44, 0x45, 0x42, 0x55, 0x47, 0x5F
	.byte  0x5F, 0x00


.att_syntax prefix
