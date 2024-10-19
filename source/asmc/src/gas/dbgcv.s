
.intel_syntax noprefix

.global cv_write_debug_tables

.extern CV8Label
.extern GetSymOfssize
.extern SizeFromMemtype
.extern SpecialTable
.extern SymTables
.extern store_fixup
.extern CreateFixup
.extern LclAlloc
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tmemicmp
.extern tsprintf
.extern Options
.extern ModuleInfo
.extern SymEnum
.extern _pgmptr
.extern getcwd


.SECTION .text
	.ALIGN	16

$_001:	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	movzx	edi, dl
	mov	cl, byte ptr [rsi+0x19]
	test	cl, 0xFFFFFF80
	jne	$_029
	mov	r8, qword ptr [rsi+0x20]
	mov	edx, edi
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	mov	cl, byte ptr [rsi+0x19]
	test	cl, 0x20
	jz	$_009
	jmp	$_007

$_002:	mov	eax, 70
	jmp	$_063

$_003:	mov	eax, 64
	jmp	$_063

$_004:	mov	eax, 65
	jmp	$_063

$_005:	mov	eax, 66
	jmp	$_063

$_006:	mov	eax, 119
	jmp	$_063

	jmp	$_008

$_007:	cmp	eax, 2
	jz	$_002
	cmp	eax, 4
	jz	$_003
	cmp	eax, 8
	jz	$_004
	cmp	eax, 10
	jz	$_005
	cmp	eax, 16
	jz	$_006
$_008:	jmp	$_028

$_009:	test	cl, 0x40
	jz	$_017
	jmp	$_015

$_010:	mov	eax, 16
	jmp	$_063

$_011:	mov	eax, 114
	jmp	$_063

$_012:	mov	eax, 116
	jmp	$_063

$_013:	mov	eax, 118
	jmp	$_063

$_014:	mov	eax, 119
	jmp	$_063

	jmp	$_016

$_015:	cmp	eax, 1
	jz	$_010
	cmp	eax, 2
	jz	$_011
	cmp	eax, 4
	jz	$_012
	cmp	eax, 8
	jz	$_013
	cmp	eax, 16
	jz	$_014
$_016:	jmp	$_026

$_017:	jmp	$_025

$_018:	mov	eax, 32
	jmp	$_063

$_019:	mov	eax, 117
	jmp	$_063

$_020:	mov	eax, 68
	jmp	$_063

$_021:	mov	eax, 119
	jmp	$_063

$_022:	mov	eax, 119
	jmp	$_063

$_023:	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_024
	mov	eax, 122
	jmp	$_063

$_024:	mov	eax, 33
	jmp	$_063

	jmp	$_026

$_025:	cmp	eax, 1
	jz	$_018
	cmp	eax, 4
	jz	$_019
	cmp	eax, 6
	jz	$_020
	cmp	eax, 8
	jz	$_021
	cmp	eax, 16
	jz	$_022
	cmp	eax, 2
	jz	$_023
$_026:	cmp	byte ptr [rsi+0x38], 1
	jnz	$_027
	mov	eax, 117
	jmp	$_063

$_027:	mov	eax, 119
	jmp	$_063

$_028:	jmp	$_062

$_029:	jmp	$_061

$_030:	mov	al, byte ptr [rsi+0x38]
	jmp	$_051

$_031:	cmp	byte ptr [rsi+0x1C], 0
	jz	$_032
	mov	eax, 515
	jmp	$_063

$_032:	mov	eax, 259
	jmp	$_063

$_033:	cmp	byte ptr [rsi+0x1C], 0
	jz	$_034
	mov	eax, 1283
	jmp	$_063

$_034:	mov	eax, 1027
	jmp	$_063

$_035:	mov	al, byte ptr [rsi+0x3A]
	jmp	$_049

$_036:	mov	eax, 1568
	jmp	$_063

$_037:	mov	eax, 1552
	jmp	$_063

$_038:	mov	eax, 1658
	jmp	$_063

$_039:	mov	eax, 1553
	jmp	$_063

$_040:	mov	eax, 1651
	jmp	$_063

$_041:	mov	eax, 1653
	jmp	$_063

$_042:	mov	eax, 1652
	jmp	$_063

$_043:	mov	eax, 1600
	jmp	$_063

$_044:	mov	eax, 1655
	jmp	$_063

$_045:	mov	eax, 1654
	jmp	$_063

$_046:	mov	eax, 1601
	jmp	$_063

$_047:	mov	eax, 1655
	jmp	$_063

$_048:	mov	eax, 1655
	jmp	$_063

	jmp	$_050

$_049:	cmp	al, 0
	je	$_036
	cmp	al, 64
	je	$_037
	cmp	al, 1
	je	$_038
	cmp	al, 65
	je	$_039
	cmp	al, 33
	jz	$_040
	cmp	al, 3
	jz	$_041
	cmp	al, 67
	jz	$_042
	cmp	al, 35
	jz	$_043
	cmp	al, 7
	jz	$_044
	cmp	al, 71
	jz	$_045
	cmp	al, 39
	jz	$_046
	cmp	al, 15
	jz	$_047
	cmp	al, 47
	jz	$_048
$_050:	mov	eax, 259
	jmp	$_063

	jmp	$_052

$_051:	cmp	al, 0
	je	$_031
	cmp	al, 1
	je	$_033
	cmp	al, 2
	je	$_035
$_052:	jmp	$_062

$_053:	cmp	word ptr [rsi+0x58], 0
	jz	$_054
	movzx	eax, word ptr [rsi+0x58]
	jmp	$_063

$_054:	jmp	$_062

$_055:	mov	eax, 259
	jmp	$_063

$_056:	mov	eax, 515
	jmp	$_063

$_057:	mov	rsi, qword ptr [rsi+0x20]
$_058:	cmp	qword ptr [rsi+0x20], 0
	jz	$_059
	mov	rsi, qword ptr [rsi+0x20]
	jmp	$_058

$_059:	cmp	word ptr [rsi+0x58], 0
	jz	$_060
	movzx	eax, word ptr [rsi+0x58]
	jmp	$_063

$_060:	mov	edx, edi
	movzx	edx, dl
	mov	rcx, rsi
	call	$_001
	jmp	$_063

	jmp	$_062

$_061:	cmp	cl, -61
	je	$_030
	cmp	cl, -63
	jz	$_053
	cmp	cl, -127
	jz	$_055
	cmp	cl, -126
	jz	$_056
	cmp	cl, -60
	jz	$_057
$_062:	xor	eax, eax
$_063:	leave
	pop	rdi
	pop	rsi
	ret

$_064:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	xchg	rsi, rdx
	mov	rax, rdi
	mov	rdi, rcx
	mov	ecx, dword ptr [rbp+0x20]
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_065
	mov	byte ptr [rdi], cl
	inc	rdi
	rep movsb
	jmp	$_066

$_065:	rep movsb
	mov	byte ptr [rdi], 0
	inc	rdi
$_066:	xchg	rax, rdi
	mov	rsi, rdx
	leave
	ret

$_067:
	cmp	byte ptr [Options+0x2+rip], 1
	jne	$_077
	cmp	byte ptr [rcx+0x18], 7
	jnz	$_068
	mov	eax, 6
	jmp	$_085

$_068:	test	byte ptr [rcx+0x15], 0x08
	jz	$_070
	cmp	byte ptr [Options+0x3+rip], 1
	jc	$_070
	test	dl, dl
	jnz	$_069
	mov	eax, 29
	jmp	$_085

$_069:	mov	eax, 37
	jmp	$_085

$_070:	cmp	byte ptr [rcx+0x19], -127
	jz	$_071
	cmp	byte ptr [rcx+0x19], -126
	jnz	$_073
$_071:	test	dl, dl
	jnz	$_072
	mov	eax, 9
	jmp	$_085

$_072:	mov	eax, 11
	jmp	$_085

$_073:	test	byte ptr [rcx+0x14], 0x10
	jz	$_076
	mov	eax, 8
	cmp	dword ptr [rcx+0x50], 0
	jnz	$_074
	cmp	dword ptr [rcx+0x28], 32768
	jc	$_075
$_074:	add	eax, 2
$_075:	jmp	$_085

$_076:	mov	eax, 12
	jmp	$_085

$_077:	cmp	byte ptr [rcx+0x18], 7
	jnz	$_078
	mov	eax, 8
	jmp	$_085

$_078:	test	byte ptr [rcx+0x15], 0x08
	jz	$_079
	cmp	byte ptr [Options+0x3+rip], 1
	jc	$_079
	mov	eax, 39
	jmp	$_085

$_079:	cmp	byte ptr [rcx+0x19], -127
	jz	$_080
	cmp	byte ptr [rcx+0x19], -126
	jnz	$_081
$_080:	mov	eax, 11
	jmp	$_085

$_081:	test	byte ptr [rcx+0x14], 0x10
	jz	$_084
	mov	eax, 10
	cmp	dword ptr [rcx+0x50], 0
	jnz	$_082
	cmp	dword ptr [rcx+0x28], 32768
	jc	$_083
$_082:	add	eax, 2
$_083:	jmp	$_085

$_084:	mov	eax, 14
$_085:	ret

dbgcv_flushpt:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rcx, qword ptr [rbx+0x28]
	mov	rax, qword ptr [rcx+0x68]
	mov	r9, qword ptr [rbx+0x30]
	mov	r8d, edx
	mov	rdx, qword ptr [rbx+0x10]
	call	qword ptr [rax+0x20]
	mov	qword ptr [rbx+0x10], rax
	leave
	pop	rbx
	ret

dbgcv_flushps:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rcx, qword ptr [rbx+0x20]
	mov	rax, qword ptr [rcx+0x68]
	mov	r9, qword ptr [rbx+0x30]
	mov	r8d, edx
	mov	rdx, qword ptr [rbx+0x8]
	call	qword ptr [rax+0x20]
	mov	qword ptr [rbx+0x8], rax
	leave
	pop	rbx
	ret

dbgcv_padbytes:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rcx, qword ptr [rcx+0x28]
	mov	rcx, qword ptr [rcx+0x68]
	mov	rcx, qword ptr [rcx+0x10]
$_086:	mov	rax, rdx
	sub	rax, rcx
	test	eax, 0x3
	jz	$_087
	not	eax
	and	eax, 0x03
	lea	rbx, [padtab+rip]
	mov	al, byte ptr [rbx+rax]
	mov	byte ptr [rdx], al
	inc	rdx
	jmp	$_086

$_087:
	leave
	pop	rbx
	ret

dbgcv_alignps:
	mov	rdx, qword ptr [rcx+0x18]
	mov	eax, dword ptr [rdx+0x4]
	and	eax, 0x03
	jz	$_090
	mov	edx, 4
	sub	edx, eax
	jmp	$_089

$_088:	mov	rax, qword ptr [rcx+0x8]
	mov	byte ptr [rax], 0
	inc	qword ptr [rcx+0x8]
	dec	edx
$_089:	test	edx, edx
	jnz	$_088
$_090:	mov	rax, qword ptr [rcx+0x8]
	ret

dbgcv_write_bitfield:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	esi, 12
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_091
	mov	esi, 8
$_091:	mov	edx, esi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rdi, rax
	mov	rcx, qword ptr [rbp+0x38]
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rcx+0x58], ax
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_092
	mov	word ptr [rdi], 6
	mov	word ptr [rdi+0x2], 518
	mov	eax, dword ptr [rcx+0x50]
	mov	byte ptr [rdi+0x4], al
	mov	eax, dword ptr [rcx+0x28]
	mov	byte ptr [rdi+0x5], al
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	word ptr [rdi+0x6], ax
	jmp	$_093

$_092:
	mov	word ptr [rdi], 10
	mov	word ptr [rdi+0x2], 4613
	mov	eax, dword ptr [rcx+0x50]
	mov	byte ptr [rdi+0x8], al
	mov	eax, dword ptr [rcx+0x28]
	mov	byte ptr [rdi+0x9], al
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	dword ptr [rdi+0x4], eax
	mov	word ptr [rdi+0xA], -3598
$_093:	inc	dword ptr [rbx+0x3C]
	add	qword ptr [rbx+0x10], rsi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_write_array_type:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rdi, rdx
	cmp	dword ptr [rbp+0x38], 0
	jnz	$_094
	movzx	edx, byte ptr [rbp+0x40]
	mov	rcx, rdi
	call	$_001
	mov	dword ptr [rbp+0x38], eax
$_094:	xor	esi, esi
	cmp	dword ptr [rdi+0x50], 32768
	jc	$_095
	add	esi, 4
$_095:	mov	eax, 12
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_096
	mov	eax, 8
$_096:	lea	edi, [rsi+rax+0x6]
	and	edi, 0xFFFFFFFC
	mov	edx, edi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	ecx, edi
	mov	rdi, rax
	add	qword ptr [rbx+0x10], rcx
	sub	ecx, 2
	mov	word ptr [rdi], cx
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_097
	mov	word ptr [rdi+0x2], 3
	mov	eax, dword ptr [rbp+0x38]
	mov	word ptr [rdi+0x4], ax
	mov	word ptr [rdi+0x6], 18
	lea	rdx, [rdi+0x8]
	jmp	$_098

$_097:
	mov	word ptr [rdi+0x2], 5379
	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rdi+0x4], eax
	movzx	edx, byte ptr [rbp+0x40]
	mov	rcx, qword ptr [rbp+0x30]
	call	$_001
	mov	dword ptr [rdi+0x8], eax
	lea	rdx, [rdi+0xC]
$_098:	mov	rcx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rcx+0x50]
	test	esi, esi
	jz	$_099
	mov	word ptr [rdx], -32764
	mov	dword ptr [rdx+0x2], eax
	add	rdx, 6
	jmp	$_100

$_099:	mov	word ptr [rdx], ax
	add	rdx, 2
$_100:	mov	byte ptr [rdx], 0
	inc	rdx
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x10]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_write_ptr_type:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rsi, rdx
	cmp	byte ptr [rsi+0x3A], -64
	jnz	$_101
	cmp	qword ptr [rsi+0x40], 0
	jz	$_102
$_101:	cmp	byte ptr [rsi+0x3A], -128
	jnz	$_103
$_102:	movzx	edx, byte ptr [rsi+0x38]
	mov	rcx, rsi
	call	$_001
	jmp	$_119

$_103:	mov	edi, 20
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_104
	mov	edi, 12
$_104:	mov	edx, edi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	xchg	rax, rdi
	add	qword ptr [rbx+0x10], rax
	sub	eax, 2
	mov	word ptr [rdi], ax
	cmp	byte ptr [rsi+0x38], 0
	jnz	$_106
	mov	eax, 0
	cmp	byte ptr [rsi+0x1C], 0
	jz	$_105
	mov	eax, 1
$_105:	jmp	$_109

$_106:	cmp	byte ptr [rsi+0x38], 1
	jnz	$_108
	mov	eax, 10
	cmp	byte ptr [rsi+0x1C], 0
	jz	$_107
	mov	eax, 11
$_107:	jmp	$_109

$_108:	mov	eax, 10
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_109
	mov	eax, 12
$_109:	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_110
	mov	word ptr [rdi+0x2], 2
	mov	word ptr [rdi+0x4], ax
	mov	word ptr [rdi+0x8], 0
	mov	word ptr [rdi+0xA], 0
	jmp	$_111

$_110:
	mov	word ptr [rdi+0x2], 4098
	mov	dword ptr [rdi+0x8], eax
	mov	dword ptr [rdi+0xC], 0
	mov	dword ptr [rdi+0x10], 0
$_111:	cmp	byte ptr [rsi+0x39], 1
	jbe	$_112
	movzx	edx, byte ptr [rsi+0x38]
	mov	rcx, rsi
	call	$_001
	jmp	$_116

$_112:	cmp	qword ptr [rsi+0x40], 0
	jz	$_115
	mov	rcx, qword ptr [rsi+0x40]
	cmp	word ptr [rcx+0x58], 0
	jz	$_113
	movzx	eax, word ptr [rcx+0x58]
	jmp	$_114

$_113:	movzx	edx, byte ptr [rsi+0x38]
	mov	rcx, rsi
	call	$_001
$_114:	jmp	$_116

$_115:	mov	al, byte ptr [rsi+0x19]
	mov	byte ptr [rbp-0x1], al
	mov	al, byte ptr [rsi+0x3A]
	mov	byte ptr [rsi+0x19], al
	movzx	edx, byte ptr [rsi+0x38]
	mov	rcx, rsi
	call	$_001
	mov	cl, byte ptr [rbp-0x1]
	mov	byte ptr [rsi+0x19], cl
$_116:	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_117
	mov	word ptr [rdi+0x6], ax
	jmp	$_118

$_117:	mov	dword ptr [rdi+0x4], eax
$_118:	mov	eax, dword ptr [rbx+0x3C]
	inc	dword ptr [rbx+0x3C]
$_119:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_cntproc:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rdi, r8
	mov	rsi, r9
	inc	dword ptr [rsi]
	mov	eax, 8
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_120
	mov	eax, 6
$_120:	mov	rcx, qword ptr [rbp+0x30]
	xor	edx, edx
	cmp	word ptr [rcx+0x5A], 4
	jz	$_121
	add	edx, dword ptr [rdi+0x28]
	add	edx, dword ptr [rsi+0x8]
$_121:	cmp	edx, 32768
	jc	$_122
	add	edx, 4
$_122:	mov	ecx, dword ptr [rdi+0x10]
	lea	rax, [rcx+rax+0x6]
	and	eax, 0xFFFFFFFC
	cmp	dword ptr [rdi+0x50], 32768
	jc	$_123
	add	eax, 4
$_123:	add	dword ptr [rsi+0x4], eax
	mov	rcx, qword ptr [rdi+0x20]
	cmp	byte ptr [rdi+0x19], -60
	jnz	$_124
	cmp	word ptr [rcx+0x58], 0
	jnz	$_124
	inc	dword ptr [rbx+0x38]
	mov	rdx, qword ptr [rdi+0x20]
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x40]
	dec	dword ptr [rbx+0x38]
	jmp	$_125

$_124:	cmp	byte ptr [rdi+0x19], -63
	jnz	$_125
	cmp	word ptr [rdi+0x58], 0
	jnz	$_125
	mov	r8, rdi
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x28]
$_125:	test	byte ptr [rdi+0x15], 0x02
	jz	$_126
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rdi+0x60], ax
	inc	dword ptr [rbx+0x3C]
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x30]
$_126:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_memberproc:
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rsi, r9
	mov	rdi, r8
	mov	rcx, rdx
	xor	eax, eax
	xor	edx, edx
	cmp	word ptr [rcx+0x5A], 4
	jz	$_127
	add	edx, dword ptr [rdi+0x28]
	add	edx, dword ptr [rsi+0x8]
$_127:	mov	dword ptr [rbp-0x4], edx
	cmp	edx, 32768
	jc	$_128
	add	eax, 4
$_128:	mov	dword ptr [rbp-0x8], eax
	mov	edx, 8
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_129
	mov	edx, 6
$_129:	add	eax, edx
	mov	ecx, dword ptr [rdi+0x10]
	lea	esi, [rax+rcx+0x6]
	and	esi, 0xFFFFFFFC
	mov	edx, esi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rdi, rax
	add	qword ptr [rbx+0x10], rsi
	mov	eax, 5389
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_130
	mov	eax, 1030
$_130:	mov	word ptr [rdi], ax
	mov	rsi, qword ptr [rbp+0x38]
	test	byte ptr [rsi+0x15], 0x02
	jz	$_131
	movzx	eax, word ptr [rsi+0x60]
	mov	word ptr [rsi+0x60], 0
	jmp	$_132

$_131:	xor	edx, edx
	mov	rcx, rsi
	call	$_001
$_132:	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_133
	mov	word ptr [rdi+0x2], ax
	mov	word ptr [rdi+0x4], 3
	lea	rcx, [rdi+0x6]
	jmp	$_134

$_133:	mov	dword ptr [rdi+0x4], eax
	mov	word ptr [rdi+0x2], 3
	lea	rcx, [rdi+0x8]
$_134:	mov	eax, dword ptr [rbp-0x4]
	cmp	dword ptr [rbp-0x8], 0
	jnz	$_135
	mov	word ptr [rcx], ax
	add	rcx, 2
	jmp	$_136

$_135:
	mov	word ptr [rcx], -32764
	mov	dword ptr [rcx+0x2], eax
	add	rcx, 6
$_136:	mov	r8d, dword ptr [rsi+0x10]
	mov	rdx, qword ptr [rsi+0x8]
	call	$_064
	mov	rdx, rax
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x10]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_enum_fields:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	rsi, rdx
	mov	rcx, qword ptr [rsi+0x68]
	mov	rdi, qword ptr [rcx]
	xor	ebx, ebx
$_137:	test	rdi, rdi
	je	$_141
	cmp	dword ptr [rdi+0x10], 0
	jz	$_138
	mov	r9, qword ptr [rbp+0x40]
	mov	r8, rdi
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	qword ptr [rbp+0x38]
	jmp	$_140

$_138:	cmp	qword ptr [rdi+0x20], 0
	jz	$_139
	mov	rcx, qword ptr [rbp+0x40]
	mov	eax, dword ptr [rdi+0x28]
	add	dword ptr [rcx+0x8], eax
	mov	r9, rcx
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rdi+0x20]
	mov	rcx, qword ptr [rbp+0x28]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x68]
	mov	rcx, qword ptr [rbp+0x40]
	mov	eax, dword ptr [rdi+0x28]
	sub	dword ptr [rcx+0x8], eax
	jmp	$_140

$_139:	cmp	word ptr [rsi+0x5A], 2
	jnz	$_140
	mov	rax, qword ptr [rdi+0x8]
	mov	qword ptr [rbp-0x8], rax
	mov	r8d, ebx
	lea	rdx, [DS0000+rip]
	lea	rcx, [rbp-0x10]
	call	tsprintf@PLT
	mov	dword ptr [rdi+0x10], eax
	inc	ebx
	lea	rax, [rbp-0x10]
	mov	qword ptr [rdi+0x8], rax
	mov	r9, qword ptr [rbp+0x40]
	mov	r8, rdi
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	qword ptr [rbp+0x38]
	mov	rax, qword ptr [rbp-0x8]
	mov	qword ptr [rdi+0x8], rax
	mov	dword ptr [rdi+0x10], 0
$_140:	mov	rdi, qword ptr [rdi+0x68]
	jmp	$_137

$_141:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_write_type_procedure:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	esi, 16
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_142
	mov	esi, 12
$_142:	mov	edx, esi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rdi, rax
	add	qword ptr [rbx+0x10], rsi
	sub	esi, 2
	mov	word ptr [rdi], si
	inc	dword ptr [rbx+0x3C]
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_143
	mov	word ptr [rdi+0x2], 8
	mov	word ptr [rdi+0x4], 3
	mov	byte ptr [rdi+0x6], 0
	mov	byte ptr [rdi+0x7], 0
	mov	eax, dword ptr [rbp+0x38]
	mov	word ptr [rdi+0x8], ax
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rdi+0xA], ax
	mov	esi, 6
	mov	eax, 2
	jmp	$_144

$_143:
	mov	word ptr [rdi+0x2], 4104
	mov	dword ptr [rdi+0x4], 3
	mov	byte ptr [rdi+0x8], 0
	mov	byte ptr [rdi+0x9], 0
	mov	eax, dword ptr [rbp+0x38]
	mov	word ptr [rdi+0xA], ax
	mov	eax, dword ptr [rbx+0x3C]
	mov	dword ptr [rdi+0xC], eax
	mov	esi, 8
	mov	eax, 4
$_144:	mul	dword ptr [rbp+0x38]
	add	esi, eax
	mov	edx, esi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rdi, rax
	add	qword ptr [rbx+0x10], rsi
	sub	esi, 2
	mov	word ptr [rdi], si
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_145
	mov	word ptr [rdi+0x2], 513
	mov	eax, dword ptr [rbp+0x38]
	mov	word ptr [rdi+0x4], ax
	add	rdi, 6
	jmp	$_146

$_145:
	mov	word ptr [rdi+0x2], 4609
	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rdi+0x4], eax
	add	rdi, 8
$_146:	mov	rsi, qword ptr [rbp+0x30]
	mov	rsi, qword ptr [rsi+0x68]
	mov	rsi, qword ptr [rsi+0x8]
$_147:	test	rsi, rsi
	jz	$_151
	movzx	eax, word ptr [rsi+0x60]
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_148
	stosw
	jmp	$_150

$_148:	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_149
	dec	dword ptr [rbp+0x38]
	mov	ecx, dword ptr [rbp+0x38]
	mov	dword ptr [rdi+rcx*4], eax
	jmp	$_150

$_149:	stosd
$_150:	mov	rsi, qword ptr [rsi+0x78]
	jmp	$_147

$_151:
	inc	dword ptr [rbx+0x3C]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_write_type:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	rbx, rcx
	mov	rsi, rdx
	cmp	word ptr [rsi+0x5A], 3
	jne	$_158
	cmp	byte ptr [rsi+0x19], -61
	jnz	$_153
	mov	rcx, qword ptr [rsi+0x40]
	cmp	byte ptr [rsi+0x3A], -128
	jz	$_152
	test	rcx, rcx
	jz	$_152
	cmp	word ptr [rcx+0x58], 0
	jnz	$_152
	cmp	dword ptr [rbx+0x38], 0
	jnz	$_152
	mov	rdx, qword ptr [rsi+0x40]
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x40]
$_152:	mov	rdx, rsi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x38]
	mov	word ptr [rsi+0x58], ax
	jmp	$_184

$_153:	cmp	byte ptr [rsi+0x19], -60
	jnz	$_157
	cmp	qword ptr [rsi+0x20], 0
	jz	$_157
	mov	rdi, rsi
	jmp	$_155

$_154:	mov	rdi, qword ptr [rdi+0x20]
$_155:	cmp	qword ptr [rdi+0x20], 0
	jnz	$_154
	cmp	word ptr [rdi+0x58], 0
	jnz	$_156
	mov	rdx, rdi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x40]
$_156:	mov	ax, word ptr [rdi+0x58]
	mov	word ptr [rsi+0x58], ax
$_157:	jmp	$_184

	jmp	$_159

$_158:	cmp	word ptr [rsi+0x5A], 0
	jnz	$_159
	jmp	$_184

$_159:	xor	eax, eax
	mov	word ptr [rbp-0x18], ax
	cmp	dword ptr [rsi+0x50], 32768
	jc	$_160
	mov	eax, 4
$_160:	mov	dword ptr [rbp-0x10], eax
	cmp	dword ptr [rbx+0x38], 0
	jz	$_161
	mov	word ptr [rbp-0x18], 8
$_161:	lea	rax, [DS0001+rip]
	cmp	dword ptr [rsi+0x10], 0
	jz	$_162
	mov	rax, qword ptr [rsi+0x8]
$_162:	mov	qword ptr [rbp-0x8], rax
	mov	eax, 9
	cmp	dword ptr [rsi+0x10], 0
	jz	$_163
	mov	eax, dword ptr [rsi+0x10]
$_163:	mov	dword ptr [rbp-0xC], eax
	movzx	eax, word ptr [rsi+0x5A]
	jmp	$_171

$_164:	mov	eax, 12
	mov	word ptr [rbp-0x16], 5382
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_165
	mov	eax, 10
	mov	word ptr [rbp-0x16], 6
	jmp	$_166

$_165:	cmp	byte ptr [Options+0x2+rip], 2
	jnz	$_166
	mov	eax, 10
	mov	word ptr [rbp-0x16], 4102
$_166:	add	eax, dword ptr [rbp-0x10]
	add	eax, dword ptr [rbp-0xC]
	add	eax, 6
	and	eax, 0xFFFFFFFC
	mov	dword ptr [rbp-0x14], eax
	jmp	$_172

$_167:	or	byte ptr [rbp-0x18], 0x01
$_168:	mov	eax, 20
	mov	word ptr [rbp-0x16], 5381
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_169
	mov	eax, 14
	mov	word ptr [rbp-0x16], 5
	jmp	$_170

$_169:	cmp	byte ptr [Options+0x2+rip], 2
	jnz	$_170
	mov	eax, 14
	mov	word ptr [rbp-0x16], 4101
$_170:	add	eax, dword ptr [rbp-0x10]
	add	eax, dword ptr [rbp-0xC]
	add	eax, 6
	and	eax, 0xFFFFFFFC
	mov	dword ptr [rbp-0x14], eax
	jmp	$_172

$_171:	cmp	eax, 2
	je	$_164
	cmp	eax, 4
	jz	$_167
	cmp	eax, 1
	jz	$_168
$_172:	mov	dword ptr [rbp-0x28], 0
	mov	dword ptr [rbp-0x24], 0
	mov	dword ptr [rbp-0x20], 0
	mov	rcx, qword ptr [rbx]
	lea	r9, [rbp-0x28]
	mov	r8, qword ptr [rcx+0x58]
	mov	rdx, rsi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x68]
	mov	edx, 4
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rdi, rax
	add	qword ptr [rbx+0x10], 4
	mov	eax, 2
	add	eax, dword ptr [rbp-0x24]
	mov	word ptr [rdi], ax
	mov	eax, 4611
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_173
	mov	eax, 516
$_173:	mov	word ptr [rdi+0x2], ax
	mov	dword ptr [rbp-0x20], 0
	mov	rcx, qword ptr [rbx]
	lea	r9, [rbp-0x28]
	mov	r8, qword ptr [rcx+0x60]
	mov	rdx, rsi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x68]
	mov	edx, dword ptr [rbp-0x14]
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rdi, rax
	mov	eax, dword ptr [rbp-0x14]
	sub	eax, 2
	mov	word ptr [rdi], ax
	mov	ax, word ptr [rbp-0x16]
	mov	word ptr [rdi+0x2], ax
	mov	eax, dword ptr [rbp-0x28]
	mov	word ptr [rdi+0x4], ax
	movzx	eax, word ptr [rsi+0x5A]
	jmp	$_180

$_174:	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_175
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rdi+0x6], ax
	mov	ax, word ptr [rbp-0x18]
	mov	word ptr [rdi+0x8], ax
	lea	rcx, [rdi+0xA]
	jmp	$_176

$_175:	mov	eax, dword ptr [rbx+0x3C]
	mov	dword ptr [rdi+0x8], eax
	mov	ax, word ptr [rbp-0x18]
	mov	word ptr [rdi+0x6], ax
	lea	rcx, [rdi+0xC]
$_176:	inc	dword ptr [rbx+0x3C]
	jmp	$_181

$_177:	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_178
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rdi+0x6], ax
	mov	ax, word ptr [rbp-0x18]
	mov	word ptr [rdi+0x8], ax
	mov	word ptr [rdi+0xA], 0
	mov	word ptr [rdi+0xC], 0
	lea	rcx, [rdi+0xE]
	jmp	$_179

$_178:	mov	eax, dword ptr [rbx+0x3C]
	mov	dword ptr [rdi+0x8], eax
	mov	ax, word ptr [rbp-0x18]
	mov	word ptr [rdi+0x6], ax
	mov	dword ptr [rdi+0xC], 0
	mov	dword ptr [rdi+0x10], 0
	lea	rcx, [rdi+0x14]
$_179:	inc	dword ptr [rbx+0x3C]
	jmp	$_181

$_180:	cmp	eax, 2
	je	$_174
	cmp	eax, 4
	jz	$_177
	cmp	eax, 1
	jz	$_177
$_181:	mov	rdx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rdx+0x50]
	cmp	dword ptr [rbp-0x10], 0
	jnz	$_182
	mov	word ptr [rcx], ax
	add	rcx, 2
	jmp	$_183

$_182:
	mov	word ptr [rcx], -32764
	mov	dword ptr [rcx+0x2], eax
	add	rcx, 6
$_183:	mov	r8d, dword ptr [rbp-0xC]
	mov	rdx, qword ptr [rbp-0x8]
	call	$_064
	mov	rdx, rax
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x10]
	mov	eax, dword ptr [rbp-0x14]
	add	qword ptr [rbx+0x10], rax
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rsi+0x58], ax
	inc	dword ptr [rbx+0x3C]
$_184:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_185:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	xor	edi, edi
	xor	ebx, ebx
$_186:	cmp	ebx, 2
	jnc	$_191
	movzx	edx, word ptr [rsi+rbx*2+0x48]
	test	edx, edx
	jz	$_190
	lea	r11, [SpecialTable+rip]
	imul	eax, edx, 12
	mov	ecx, dword ptr [r11+rax]
	lea	r11, [SpecialTable+rip]
	imul	eax, edx, 12
	movzx	eax, byte ptr [r11+rax+0xA]
	inc	eax
	test	ecx, 0x2
	jz	$_187
	add	eax, 8
	jmp	$_189

$_187:	test	ecx, 0x4
	jz	$_188
	add	eax, 16
	jmp	$_189

$_188:	test	ecx, 0xC000000
	jz	$_189
	add	eax, 24
$_189:	lea	rcx, [rbx*8]
	shl	eax, cl
	or	edi, eax
$_190:	inc	ebx
	jmp	$_186

$_191:
	mov	eax, edi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_192:
	cmp	ecx, 115
	jc	$_193
	cmp	ecx, 122
	ja	$_193
	lea	rax, [reg64+rip]
	movzx	eax, byte ptr [rax+rcx-0x73]
	add	eax, 328
	jmp	$_195

$_193:	cmp	ecx, 123
	jc	$_194
	cmp	ecx, 130
	ja	$_194
	lea	eax, [rcx+0xD5]
	jmp	$_195

$_194:	lea	eax, [rcx+0xFD]
$_195:	ret

dbgcv_write_symbol:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 136
	mov	rsi, rdx
	mov	rbx, rcx
	mov	rcx, rsi
	call	GetSymOfssize@PLT
	mov	byte ptr [rbp-0xD], al
	movzx	edx, al
	mov	rcx, rsi
	call	$_067
	mov	dword ptr [rbp-0x4], eax
	test	byte ptr [rsi+0x14], 0x10
	je	$_211
	mov	edi, 32769
	mov	eax, dword ptr [rsi+0x28]
	mov	edx, dword ptr [rsi+0x50]
	test	edx, edx
	jnz	$_196
	cmp	eax, 32768
	jc	$_201
$_196:	test	edx, edx
	jns	$_197
	neg	eax
	neg	edx
	sbb	edx, 0
$_197:	test	edx, edx
	jnz	$_200
	cmp	eax, 255
	ja	$_198
	mov	edi, 32768
	dec	dword ptr [rbp-0x4]
	jmp	$_199

$_198:	cmp	eax, 65535
	jbe	$_199
	mov	edi, 32771
	add	dword ptr [rbp-0x4], 2
$_199:	jmp	$_201

$_200:	add	dword ptr [rbp-0x4], 6
	mov	edi, 32777
$_201:	mov	eax, dword ptr [rbp-0x4]
	mov	ecx, dword ptr [rsi+0x10]
	lea	edx, [rax+rcx+0x1]
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rcx, rax
	xchg	rcx, rdi
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_202
	mov	word ptr [rdi+0x2], 3
	mov	word ptr [rdi+0x4], 17
	lea	rdx, [rdi+0x8]
	jmp	$_203

$_202:
	mov	word ptr [rdi+0x2], 4359
	mov	dword ptr [rdi+0x4], 17
	lea	rdx, [rdi+0xA]
$_203:	mov	eax, dword ptr [rsi+0x28]
	cmp	dword ptr [rsi+0x50], 0
	jnz	$_204
	cmp	eax, 32768
	jc	$_209
$_204:	cmp	ecx, 32768
	jnz	$_205
	mov	byte ptr [rdx], al
	mov	eax, ecx
	mov	ecx, 16
	jmp	$_208

$_205:	cmp	ecx, 32769
	jnz	$_206
	mov	word ptr [rdx], ax
	mov	eax, ecx
	mov	ecx, 17
	jmp	$_208

$_206:	cmp	ecx, 32771
	jnz	$_207
	mov	dword ptr [rdx], eax
	mov	eax, ecx
	mov	ecx, 18
	jmp	$_208

$_207:	cmp	ecx, 32777
	jnz	$_208
	mov	dword ptr [rdx], eax
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rdx+0x4], eax
	mov	eax, ecx
	mov	ecx, 19
$_208:	mov	word ptr [rdi+0x4], cx
$_209:	mov	word ptr [rdx-0x2], ax
	mov	eax, dword ptr [rbp-0x4]
	mov	ecx, dword ptr [rsi+0x10]
	lea	edx, [rax+rcx-0x1]
	mov	word ptr [rdi], dx
	add	qword ptr [rbx+0x8], rax
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_210
	add	edx, 2
	mov	rcx, qword ptr [rbx+0x18]
	add	dword ptr [rcx+0x4], edx
$_210:	mov	r8d, dword ptr [rsi+0x10]
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	$_064
	mov	qword ptr [rbx+0x8], rax
	jmp	$_299

$_211:	mov	ecx, dword ptr [rsi+0x10]
	lea	eax, [rcx+rax+0x1]
	mov	edx, eax
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rdi, rax
	cmp	byte ptr [rsi+0x18], 7
	jne	$_218
	mov	eax, 9
	mov	edx, 4360
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_212
	mov	eax, 7
	mov	edx, 4
$_212:	mov	word ptr [rdi+0x2], dx
	sub	eax, 2
	mov	ecx, dword ptr [rsi+0x10]
	add	eax, ecx
	mov	word ptr [rdi], ax
	cmp	word ptr [rsi+0x58], 0
	jz	$_213
	movzx	eax, word ptr [rsi+0x58]
	jmp	$_214

$_213:	movzx	edx, byte ptr [rbp-0xD]
	mov	rcx, rsi
	call	$_001
$_214:	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_215
	mov	word ptr [rdi+0x4], ax
	jmp	$_216

$_215:	mov	dword ptr [rdi+0x4], eax
$_216:	test	eax, eax
	jz	$_217
	mov	eax, dword ptr [rbp-0x4]
	add	qword ptr [rbx+0x8], rax
	mov	r8d, dword ptr [rsi+0x10]
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	$_064
	mov	qword ptr [rbx+0x8], rax
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_217
	mov	eax, dword ptr [rsi+0x10]
	add	eax, dword ptr [rbp-0x4]
	inc	eax
	mov	rcx, qword ptr [rbx+0x18]
	add	dword ptr [rcx+0x4], eax
$_217:	jmp	$_299

$_218:	test	byte ptr [rsi+0x15], 0x08
	je	$_247
	cmp	byte ptr [Options+0x3+rip], 1
	jc	$_247
	mov	rdx, qword ptr [rsi+0x68]
	mov	qword ptr [rbp-0x20], rdx
	mov	rax, qword ptr [rdx+0x8]
	mov	qword ptr [rbp-0x50], rax
	mov	rax, qword ptr [rdx+0x10]
	mov	qword ptr [rbp-0x48], rax
	mov	dword ptr [rbp-0x2C], 0
$_219:	cmp	dword ptr [rbp-0x2C], 2
	jge	$_233
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_221
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_221
	mov	dword ptr [rbp-0x30], 0
	mov	rcx, qword ptr [rbp-0x50]
$_220:	test	rcx, rcx
	jz	$_221
	mov	rsi, rcx
	mov	rcx, qword ptr [rcx+0x78]
	inc	dword ptr [rbp-0x30]
	jmp	$_220

$_221:	mov	ecx, dword ptr [rbp-0x2C]
	mov	dword ptr [rbp+rcx*4-0x3C], 0
	mov	rdi, qword ptr [rbp+rcx*8-0x50]
$_222:	test	rdi, rdi
	je	$_232
	mov	ecx, dword ptr [rbp-0x2C]
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_223
	test	ecx, ecx
	jz	$_224
$_223:	mov	rsi, rdi
$_224:	inc	dword ptr [rbp+rcx*4-0x3C]
	cmp	byte ptr [rsi+0x19], -64
	jnz	$_225
	test	byte ptr [rsi+0x3B], 0x04
	jz	$_225
	mov	word ptr [rbp-0x60], 259
	jmp	$_228

$_225:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_226
	mov	rdx, rsi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x38]
	jmp	$_227

$_226:	movzx	edx, byte ptr [rbp-0xD]
	mov	rcx, rsi
	call	$_001
$_227:	mov	word ptr [rbp-0x60], ax
$_228:	test	byte ptr [rsi+0x15], 0x02
	jz	$_229
	movzx	r9d, byte ptr [rbp-0xD]
	movzx	r8d, word ptr [rbp-0x60]
	mov	rdx, rsi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x30]
	mov	eax, dword ptr [rbx+0x3C]
	inc	dword ptr [rbx+0x3C]
	mov	word ptr [rbp-0x60], ax
$_229:	mov	ax, word ptr [rbp-0x60]
	mov	word ptr [rsi+0x60], ax
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_231
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_231
	mov	ecx, 1
	dec	dword ptr [rbp-0x30]
	mov	rsi, qword ptr [rbp-0x50]
$_230:	cmp	dword ptr [rbp-0x30], ecx
	jle	$_231
	inc	ecx
	mov	rsi, qword ptr [rsi+0x78]
	jmp	$_230

$_231:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_222

$_232:	inc	dword ptr [rbp-0x2C]
	jmp	$_219

$_233:	mov	rdi, qword ptr [rbx+0x8]
	mov	rsi, qword ptr [rbp+0x30]
	cmp	byte ptr [rbp-0xD], 0
	jne	$_236
	mov	eax, dword ptr [rsi+0x10]
	add	eax, 28
	mov	word ptr [rdi], ax
	mov	eax, 260
	test	dword ptr [rsi+0x14], 0x80
	jz	$_234
	mov	eax, 261
$_234:	mov	word ptr [rdi+0x2], ax
	mov	dword ptr [rdi+0x4], 0
	mov	dword ptr [rdi+0x8], 0
	mov	dword ptr [rdi+0xC], 0
	mov	eax, dword ptr [rsi+0x50]
	mov	word ptr [rdi+0x10], ax
	mov	rcx, qword ptr [rsi+0x68]
	movzx	eax, byte ptr [rcx+0x41]
	mov	word ptr [rdi+0x12], ax
	mov	eax, dword ptr [rsi+0x50]
	mov	word ptr [rdi+0x14], ax
	mov	word ptr [rdi+0x16], 0
	mov	word ptr [rdi+0x18], 0
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rdi+0x1A], ax
	xor	eax, eax
	cmp	byte ptr [rsi+0x19], -126
	jnz	$_235
	mov	eax, 4
$_235:	mov	byte ptr [rdi+0x1C], al
	mov	dword ptr [rbp-0xC], 9
	mov	dword ptr [rbp-0x8], 22
	jmp	$_246

$_236:	mov	dword ptr [rbp-0x5C], 40
	mov	eax, 4367
	test	dword ptr [rsi+0x14], 0x80
	jz	$_237
	mov	eax, 4368
$_237:	mov	word ptr [rbp-0x5E], ax
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_239
	mov	dword ptr [rbp-0x5C], 38
	mov	eax, 516
	test	dword ptr [rsi+0x14], 0x80
	jz	$_238
	mov	eax, 517
$_238:	mov	word ptr [rbp-0x5E], ax
$_239:	mov	eax, dword ptr [rbp-0x5C]
	sub	eax, 2
	mov	ecx, dword ptr [rsi+0x10]
	add	eax, ecx
	mov	word ptr [rdi], ax
	mov	ax, word ptr [rbp-0x5E]
	mov	word ptr [rdi+0x2], ax
	mov	dword ptr [rdi+0x4], 0
	mov	dword ptr [rdi+0x8], 0
	mov	dword ptr [rdi+0xC], 0
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rdi+0x10], eax
	mov	rcx, qword ptr [rsi+0x68]
	movzx	eax, byte ptr [rcx+0x41]
	mov	dword ptr [rdi+0x14], eax
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rdi+0x18], eax
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_242
	mov	dword ptr [rdi+0x1C], 0
	mov	word ptr [rdi+0x20], 0
	mov	eax, dword ptr [rbx+0x3C]
	mov	word ptr [rdi+0x22], ax
	mov	byte ptr [rdi+0x24], 0
	cmp	byte ptr [rsi+0x19], -126
	jnz	$_240
	mov	byte ptr [rdi+0x24], 4
$_240:	mov	rcx, qword ptr [rbp-0x20]
	test	byte ptr [rcx+0x40], 0xFFFFFF80
	jz	$_241
	mov	byte ptr [rdi+0x24], 1
$_241:	mov	dword ptr [rbp-0x8], 28
	jmp	$_245

$_242:	mov	dword ptr [rdi+0x20], 0
	mov	word ptr [rdi+0x24], 0
	mov	eax, dword ptr [rbx+0x3C]
	mov	dword ptr [rdi+0x1C], eax
	mov	byte ptr [rdi+0x26], 0
	cmp	byte ptr [rsi+0x19], -126
	jnz	$_243
	mov	byte ptr [rdi+0x26], 4
$_243:	mov	rcx, qword ptr [rbp-0x20]
	test	byte ptr [rcx+0x40], 0xFFFFFF80
	jz	$_244
	mov	byte ptr [rdi+0x26], 1
$_244:	mov	dword ptr [rbp-0x8], 32
$_245:	mov	dword ptr [rbp-0xC], 10
$_246:	mov	r8d, dword ptr [rbp-0x3C]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x48]
	jmp	$_267

$_247:	cmp	byte ptr [rsi+0x19], -127
	jz	$_248
	cmp	byte ptr [rsi+0x19], -126
	jne	$_255
$_248:	mov	eax, dword ptr [rsi+0x10]
	cmp	byte ptr [rbp-0xD], 0
	jnz	$_250
	add	eax, 8
	mov	word ptr [rdi], ax
	mov	word ptr [rdi+0x2], 265
	xor	eax, eax
	mov	word ptr [rdi+0x4], ax
	mov	word ptr [rdi+0x6], ax
	cmp	byte ptr [rsi+0x19], -126
	jnz	$_249
	mov	eax, 4
$_249:	mov	byte ptr [rdi+0x8], al
	mov	dword ptr [rbp-0xC], 9
	mov	dword ptr [rbp-0x8], 4
	jmp	$_254

$_250:	add	eax, 10
	mov	word ptr [rdi], ax
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_251
	mov	word ptr [rdi+0x2], 521
	jmp	$_252

$_251:
	mov	word ptr [rdi+0x2], 4357
$_252:	xor	eax, eax
	mov	dword ptr [rdi+0x4], eax
	mov	word ptr [rdi+0x8], ax
	cmp	byte ptr [rsi+0x19], -126
	jnz	$_253
	mov	eax, 4
$_253:	mov	byte ptr [rdi+0xA], al
	mov	dword ptr [rbp-0xC], 10
	mov	dword ptr [rbp-0x8], 4
$_254:	jmp	$_267

$_255:	test	byte ptr [rsi+0x15], 0x02
	jz	$_256
	movzx	r9d, byte ptr [rbp-0xD]
	xor	r8d, r8d
	mov	rdx, rsi
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x30]
	mov	eax, dword ptr [rbx+0x3C]
	inc	dword ptr [rbx+0x3C]
	jmp	$_257

$_256:	movzx	edx, byte ptr [rbp-0xD]
	mov	rcx, rsi
	call	$_001
$_257:	mov	word ptr [rbp-0x60], ax
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_258
	mov	dword ptr [rbp-0x5C], 13
	mov	dword ptr [rdi+0x4], 0
	mov	word ptr [rdi+0x8], 0
	mov	word ptr [rdi+0xA], ax
	mov	dword ptr [rbp-0x8], 4
	jmp	$_259

$_258:	mov	dword ptr [rbp-0x5C], 15
	mov	dword ptr [rdi+0x8], 0
	mov	word ptr [rdi+0xC], 0
	mov	dword ptr [rdi+0x4], eax
	mov	dword ptr [rbp-0x8], 8
$_259:	mov	eax, dword ptr [rsi+0x10]
	add	eax, dword ptr [rbp-0x5C]
	sub	eax, 2
	mov	word ptr [rdi], ax
	cmp	byte ptr [rbp-0xD], 0
	jnz	$_261
	mov	eax, 257
	test	dword ptr [rsi+0x14], 0x80
	jz	$_260
	mov	eax, 258
$_260:	mov	word ptr [rbp-0x5E], ax
	mov	dword ptr [rbp-0xC], 9
	jmp	$_266

$_261:	mov	rcx, qword ptr [rsi+0x30]
	mov	eax, 1
	test	byte ptr [ModuleInfo+0x1F2+rip], 0x01
	jz	$_262
	cmp	qword ptr [rcx+0x50], 0
	jz	$_262
	mov	rcx, qword ptr [rcx+0x50]
	lea	rdx, [DS0002+rip]
	mov	rcx, qword ptr [rcx+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_262
	mov	ecx, 525
	test	dword ptr [rsi+0x14], 0x80
	jz	$_262
	mov	ecx, 526
$_262:	test	eax, eax
	jz	$_265
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_264
	mov	ecx, 513
	test	dword ptr [rsi+0x14], 0x80
	jz	$_263
	mov	ecx, 514
$_263:	jmp	$_265

$_264:	mov	ecx, 4364
	test	dword ptr [rsi+0x14], 0x80
	jz	$_265
	mov	ecx, 4365
$_265:	mov	word ptr [rbp-0x5E], cx
	mov	dword ptr [rbp-0xC], 10
$_266:	mov	ax, word ptr [rbp-0x5E]
	mov	word ptr [rdi+0x2], ax
$_267:	mov	eax, dword ptr [rbp-0x8]
	add	qword ptr [rbx+0x8], rax
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_268
	mov	rcx, qword ptr [rbx+0x18]
	add	dword ptr [rcx+0x4], eax
$_268:	mov	rax, qword ptr [rbx+0x20]
	mov	rdi, qword ptr [rax+0x68]
	mov	rax, qword ptr [rbx+0x8]
	sub	rax, qword ptr [rdi+0x10]
	add	eax, dword ptr [rdi+0x8]
	mov	dword ptr [rdi+0xC], eax
	cmp	dword ptr [Options+0xA4+rip], 2
	jnz	$_270
	xor	r8d, r8d
	mov	edx, 13
	mov	rcx, rsi
	call	CreateFixup@PLT
	mov	rcx, rax
	mov	eax, dword ptr [rdi+0xC]
	mov	dword ptr [rcx+0x14], eax
	mov	r8, qword ptr [rbx+0x8]
	mov	rdx, qword ptr [rbx+0x20]
	call	store_fixup@PLT
	xor	r8d, r8d
	mov	edx, 8
	mov	rcx, rsi
	call	CreateFixup@PLT
	mov	rcx, rax
	mov	eax, 2
	cmp	dword ptr [rbp-0xC], 10
	jnz	$_269
	mov	eax, 4
$_269:	add	eax, dword ptr [rdi+0xC]
	mov	dword ptr [rcx+0x14], eax
	mov	r8, qword ptr [rbx+0x8]
	mov	rdx, qword ptr [rbx+0x20]
	call	store_fixup@PLT
	jmp	$_271

$_270:	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, rsi
	call	CreateFixup@PLT
	mov	rcx, rax
	mov	eax, dword ptr [rdi+0xC]
	mov	dword ptr [rcx+0x14], eax
	mov	r8, qword ptr [rbx+0x8]
	mov	rdx, qword ptr [rbx+0x20]
	call	store_fixup@PLT
$_271:	mov	eax, dword ptr [rbp-0x4]
	sub	eax, dword ptr [rbp-0x8]
	add	qword ptr [rbx+0x8], rax
	mov	r8d, dword ptr [rsi+0x10]
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	$_064
	mov	qword ptr [rbx+0x8], rax
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_272
	mov	eax, dword ptr [rsi+0x10]
	add	eax, dword ptr [rbp-0x4]
	sub	eax, dword ptr [rbp-0x8]
	inc	eax
	mov	rcx, qword ptr [rbx+0x18]
	add	dword ptr [rcx+0x4], eax
$_272:	test	byte ptr [rsi+0x15], 0x08
	je	$_299
	cmp	byte ptr [Options+0x3+rip], 1
	jc	$_299
	mov	dword ptr [rbp-0x2C], 0
$_273:	cmp	dword ptr [rbp-0x2C], 2
	jge	$_298
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_275
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_275
	mov	dword ptr [rbp-0x30], 0
	mov	rcx, qword ptr [rbp-0x50]
$_274:	test	rcx, rcx
	jz	$_275
	inc	dword ptr [rbp-0x30]
	mov	rsi, rcx
	mov	rcx, qword ptr [rcx+0x78]
	jmp	$_274

$_275:	mov	ecx, dword ptr [rbp-0x2C]
	mov	rdi, qword ptr [rbp+rcx*8-0x50]
$_276:	test	rdi, rdi
	je	$_297
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_277
	cmp	dword ptr [rbp-0x2C], 0
	jz	$_278
$_277:	mov	rsi, rdi
$_278:	cmp	byte ptr [rsi+0x18], 10
	jne	$_282
	mov	dword ptr [rbp-0x4], 10
	mov	word ptr [rbp-0x5E], 4358
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_279
	mov	dword ptr [rbp-0x4], 8
	mov	word ptr [rbp-0x5E], 2
$_279:	mov	edx, dword ptr [rsi+0x10]
	add	edx, dword ptr [rbp-0x4]
	inc	edx
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rdx, rax
	mov	eax, dword ptr [rsi+0x10]
	add	eax, dword ptr [rbp-0x4]
	lea	eax, [rax-0x1]
	mov	word ptr [rdx], ax
	mov	ax, word ptr [rbp-0x5E]
	mov	word ptr [rdx+0x2], ax
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_280
	mov	ax, word ptr [rsi+0x60]
	mov	word ptr [rdx+0x4], ax
	mov	rcx, rsi
	call	$_185
	mov	rdx, qword ptr [rbx+0x8]
	mov	word ptr [rdx+0x6], ax
	jmp	$_281

$_280:	movzx	eax, word ptr [rsi+0x60]
	mov	dword ptr [rdx+0x4], eax
	mov	rcx, rsi
	call	$_185
	mov	rdx, qword ptr [rbx+0x8]
	mov	word ptr [rdx+0x8], ax
$_281:	jmp	$_293

$_282:	cmp	byte ptr [rbp-0xD], 0
	jnz	$_283
	mov	dword ptr [rbp-0x4], 8
	mov	edx, dword ptr [rsi+0x10]
	add	edx, dword ptr [rbp-0x4]
	inc	edx
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rdx, rax
	mov	eax, 7
	add	eax, dword ptr [rsi+0x10]
	mov	word ptr [rdx], ax
	mov	word ptr [rdx+0x2], 256
	mov	eax, dword ptr [rsi+0x28]
	mov	word ptr [rdx+0x4], ax
	mov	ax, word ptr [rsi+0x60]
	mov	word ptr [rdx+0x6], ax
	jmp	$_293

$_283:	mov	rcx, qword ptr [rbp-0x20]
	movzx	ecx, word ptr [rcx+0x42]
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	cmp	byte ptr [rbp-0xD], 2
	jz	$_284
	cmp	byte ptr [r11+rax+0xA], 5
	je	$_290
$_284:	mov	dword ptr [rbp-0x4], 14
	mov	word ptr [rbp-0x5E], 4369
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_285
	mov	dword ptr [rbp-0x4], 12
	mov	word ptr [rbp-0x5E], 524
$_285:	mov	edx, dword ptr [rsi+0x10]
	add	edx, dword ptr [rbp-0x4]
	inc	edx
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rdx, rax
	mov	eax, dword ptr [rsi+0x10]
	add	eax, dword ptr [rbp-0x4]
	lea	eax, [rax-0x1]
	mov	word ptr [rdx], ax
	mov	ax, word ptr [rbp-0x5E]
	mov	word ptr [rdx+0x2], ax
	mov	rcx, qword ptr [rbp-0x20]
	movzx	ecx, word ptr [rcx+0x42]
	imul	eax, ecx, 12
	lea	rdx, [SpecialTable+rip]
	cmp	word ptr [rdx+rax+0x8], 112
	jnz	$_286
	call	$_192
	mov	dword ptr [rbp-0x5C], eax
	jmp	$_287

$_286:	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	movzx	eax, byte ptr [r11+rax+0xA]
	mov	dword ptr [rbp-0x5C], eax
	add	dword ptr [rbp-0x5C], 17
$_287:	mov	rdx, qword ptr [rbx+0x8]
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_288
	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rdx+0x4], eax
	mov	ax, word ptr [rsi+0x60]
	mov	word ptr [rdx+0xA], ax
	mov	eax, dword ptr [rbp-0x5C]
	mov	word ptr [rdx+0x8], ax
	jmp	$_289

$_288:	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rdx+0x4], eax
	movzx	eax, word ptr [rsi+0x60]
	mov	dword ptr [rdx+0x8], eax
	mov	eax, dword ptr [rbp-0x5C]
	mov	word ptr [rdx+0xC], ax
$_289:	jmp	$_293

$_290:	mov	dword ptr [rbp-0x4], 12
	mov	word ptr [rbp-0x5E], 4363
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_291
	mov	dword ptr [rbp-0x4], 10
	mov	word ptr [rbp-0x5E], 512
$_291:	mov	edx, dword ptr [rsi+0x10]
	add	edx, dword ptr [rbp-0x4]
	inc	edx
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rdx, rax
	mov	eax, dword ptr [rsi+0x10]
	add	eax, dword ptr [rbp-0x4]
	lea	eax, [rax-0x1]
	mov	word ptr [rdx], ax
	mov	ax, word ptr [rbp-0x5E]
	mov	word ptr [rdx+0x2], ax
	cmp	byte ptr [Options+0x2+rip], 1
	jnz	$_292
	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rdx+0x4], eax
	mov	ax, word ptr [rsi+0x60]
	mov	word ptr [rdx+0x8], ax
	jmp	$_293

$_292:	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rdx+0x4], eax
	movzx	eax, word ptr [rsi+0x60]
	mov	dword ptr [rdx+0x8], eax
$_293:
	mov	word ptr [rsi+0x60], 0
	mov	eax, dword ptr [rbp-0x4]
	add	qword ptr [rbx+0x8], rax
	mov	r8d, dword ptr [rsi+0x10]
	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, qword ptr [rbx+0x8]
	call	$_064
	mov	qword ptr [rbx+0x8], rax
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_294
	mov	eax, dword ptr [rsi+0x10]
	add	eax, dword ptr [rbp-0x4]
	inc	eax
	mov	rcx, qword ptr [rbx+0x18]
	add	dword ptr [rcx+0x4], eax
$_294:	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jnz	$_296
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_296
	mov	ecx, 1
	dec	dword ptr [rbp-0x30]
	mov	rsi, qword ptr [rbp-0x50]
$_295:	cmp	dword ptr [rbp-0x30], ecx
	jle	$_296
	inc	ecx
	mov	rsi, qword ptr [rsi+0x78]
	jmp	$_295

$_296:	mov	rdi, qword ptr [rdi+0x78]
	jmp	$_276

$_297:	inc	dword ptr [rbp-0x2C]
	jmp	$_273

$_298:	mov	edx, 4
	mov	rcx, rbx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	word ptr [rax], 2
	mov	word ptr [rax+0x2], 6
	add	qword ptr [rbx+0x8], 4
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_299
	mov	rcx, qword ptr [rbx+0x18]
	add	dword ptr [rcx+0x4], 4
$_299:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

dbgcv_flush_section:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	rdi, qword ptr [rbx+0x20]
	mov	rsi, qword ptr [rbx+0x8]
	mov	rcx, qword ptr [rdi+0x68]
	mov	rax, qword ptr [rcx+0x10]
	mov	qword ptr [rbx+0x8], rax
	sub	rsi, rax
	mov	eax, dword ptr [rbp+0x38]
	lea	rcx, [rsi+rax+0x18]
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	qword ptr [rdi], 0
	lea	rax, [rsi+0x8]
	add	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rdi+0x8], eax
	lea	rcx, [rdi+rsi+0x10]
	mov	qword ptr [rbx+0x18], rcx
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rcx], eax
	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rcx+0x4], eax
	test	esi, esi
	jz	$_300
	mov	ecx, esi
	lea	rdx, [rdi+0x10]
	mov	rax, qword ptr [rbx+0x8]
	xchg	rax, rsi
	xchg	rdx, rdi
	rep movsb
	mov	rdi, rdx
	mov	rsi, rax
$_300:	mov	rdx, qword ptr [rbx+0x30]
	lea	rcx, [rdx+0x48]
	mov	rdx, qword ptr [rcx]
	cmp	rdx, qword ptr [rbx+0x20]
	jz	$_301
	sub	rcx, 24
$_301:	cmp	qword ptr [rcx+0x8], 0
	jnz	$_302
	mov	qword ptr [rcx+0x8], rdi
	mov	qword ptr [rcx+0x10], rdi
	jmp	$_303

$_302:	mov	rdx, qword ptr [rcx+0x10]
	mov	qword ptr [rdx], rdi
	mov	qword ptr [rcx+0x10], rdi
$_303:	mov	rdx, qword ptr [rbx+0x20]
	mov	rcx, qword ptr [rdx+0x68]
	mov	eax, dword ptr [rcx+0x8]
	lea	rax, [rsi+rax+0x8]
	add	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rcx+0xC], eax
	mov	dword ptr [rcx+0x8], eax
	mov	rax, qword ptr [rbx+0x18]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

cv_write_debug_tables:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 216
	lea	rax, [vtable+rip]
	mov	qword ptr [rbp-0x60], rax
	mov	rsi, rcx
	mov	qword ptr [rbp-0x40], rsi
	mov	rcx, qword ptr [rsi+0x68]
	mov	rsi, qword ptr [rcx+0x10]
	mov	rdi, qword ptr [rbp+0x30]
	mov	qword ptr [rbp-0x38], rdi
	mov	rcx, qword ptr [rdi+0x68]
	mov	rdi, qword ptr [rcx+0x10]
	mov	dword ptr [rbp-0x24], 4096
	mov	dword ptr [rbp-0x28], 0
	mov	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x30], rax
	movzx	eax, byte ptr [Options+0x2+rip]
	stosd
	mov	qword ptr [rbp-0x50], rdi
	mov	dword ptr [rsi], eax
	add	rsi, 4
	mov	qword ptr [rbp-0x58], rsi
	cmp	byte ptr [Options+0x2+rip], 4
	jne	$_330
	imul	ecx, dword ptr [ModuleInfo+0xB8+rip], 12
	call	LclAlloc@PLT
	mov	qword ptr [rbp-0x20], rax
	mov	rdi, rax
	xor	eax, eax
	mov	rsi, qword ptr [ModuleInfo+0xB0+rip]
	mov	ebx, dword ptr [ModuleInfo+0xB8+rip]
$_304:	test	ebx, ebx
	jz	$_305
	movsq
	stosd
	dec	ebx
	jmp	$_304

$_305:	mov	ecx, 1040
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	esi, 1040
	call	getcwd@PLT
	mov	rcx, rdi
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x68], eax
	add	rax, rdi
	mov	qword ptr [rbp-0x10], rax
	mov	qword ptr [rbp-0x18], rdi
	xor	r8d, r8d
	mov	edx, 243
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x20]
	mov	rbx, rax
	inc	dword ptr [rbx+0x4]
	mov	rdi, qword ptr [rbp-0x58]
	mov	byte ptr [rdi], 0
	inc	qword ptr [rbp-0x58]
	mov	rdi, qword ptr [rbp-0x20]
	mov	dword ptr [rbp-0x4], 0
$_306:	mov	eax, dword ptr [ModuleInfo+0xB8+rip]
	cmp	dword ptr [rbp-0x4], eax
	jge	$_308
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rdi+0x8], eax
	mov	rsi, qword ptr [rdi]
	mov	eax, dword ptr [rsi]
	cmp	al, 92
	jz	$_307
	cmp	al, 46
	jz	$_307
	cmp	ah, 58
	jz	$_307
	lea	rdx, [DS0003+rip]
	mov	rcx, qword ptr [rbp-0x10]
	call	tstrcpy@PLT
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp-0x10]
	call	tstrcat@PLT
	mov	rsi, qword ptr [rbp-0x18]
$_307:	mov	rcx, rsi
	call	tstrlen@PLT
	inc	rax
	mov	dword ptr [rbp-0x8], eax
	mov	edx, eax
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	xchg	rax, rdi
	mov	ecx, dword ptr [rbp-0x8]
	add	qword ptr [rbp-0x58], rcx
	add	dword ptr [rbx+0x4], ecx
	rep movsb
	mov	rdi, rax
	inc	dword ptr [rbp-0x4]
	add	rdi, 12
	jmp	$_306

$_308:	mov	rcx, qword ptr [rbp-0x10]
	mov	byte ptr [rcx], 0
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x18]
	mov	eax, dword ptr [rbx+0x4]
	add	eax, 3
	and	eax, 0xFFFFFFFC
	add	eax, 8
	mov	dword ptr [rbp-0x64], eax
	xor	r8d, r8d
	mov	edx, 244
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x20]
	mov	rbx, rax
	mov	rsi, qword ptr [rbp-0x20]
	mov	dword ptr [rbp-0x4], 0
$_309:	mov	eax, dword ptr [ModuleInfo+0xB8+rip]
	cmp	dword ptr [rbp-0x4], eax
	jge	$_310
	mov	edx, 8
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rdi, rax
	mov	eax, dword ptr [rsi+0x8]
	stosd
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rsi+0x8], eax
	xor	eax, eax
	stosd
	add	dword ptr [rbx+0x4], 8
	mov	qword ptr [rbp-0x58], rdi
	inc	dword ptr [rbp-0x4]
	add	rsi, 12
	jmp	$_309

$_310:	mov	eax, dword ptr [rbx+0x4]
	add	eax, 3
	and	eax, 0xFFFFFFFC
	add	eax, 20
	add	dword ptr [rbp-0x64], eax
	mov	rcx, qword ptr [CV8Label+rip]
	xor	eax, eax
	test	rcx, rcx
	jz	$_311
	mov	rcx, qword ptr [rcx+0x30]
	mov	rcx, qword ptr [rcx+0x68]
	mov	eax, dword ptr [rcx+0x18]
$_311:	test	eax, eax
	jz	$_312
	mov	dword ptr [rbp-0x6C], 0
	xor	r8d, r8d
	mov	edx, 13
	mov	rcx, qword ptr [CV8Label+rip]
	call	CreateFixup@PLT
	mov	rcx, rax
	mov	eax, dword ptr [rbp-0x64]
	mov	dword ptr [rcx+0x14], eax
	lea	r8, [rbp-0x6C]
	mov	rdx, qword ptr [rbp-0x40]
	call	store_fixup@PLT
	xor	r8d, r8d
	mov	edx, 8
	mov	rcx, qword ptr [CV8Label+rip]
	call	CreateFixup@PLT
	mov	rcx, rax
	mov	eax, dword ptr [rbp-0x64]
	add	eax, 4
	mov	dword ptr [rcx+0x14], eax
	lea	r8, [rbp-0x6C]
	mov	rdx, qword ptr [rbp-0x40]
	call	store_fixup@PLT
$_312:	mov	qword ptr [rbp-0x48], 0
	mov	rsi, qword ptr [SymTables+0x20+rip]
$_313:	test	rsi, rsi
	je	$_325
	mov	rbx, qword ptr [rsi+0x68]
	cmp	qword ptr [rbx+0x38], 0
	je	$_324
	cmp	qword ptr [rbp-0x48], 0
	jz	$_314
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x18]
$_314:	mov	r8d, 24
	mov	edx, 242
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x20]
	mov	rdi, rax
	add	rdi, 8
	mov	qword ptr [rbp-0x78], rdi
	mov	dword ptr [rdi], 0
	mov	word ptr [rdi+0x4], 0
	mov	word ptr [rdi+0x6], 0
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rdi+0x8], eax
	add	rdi, 12
	mov	qword ptr [rbp-0x80], rdi
	mov	dword ptr [rdi], 0
	mov	dword ptr [rdi+0x4], 0
	mov	dword ptr [rdi+0x8], 0
	mov	rbx, qword ptr [rbx+0x38]
	mov	rbx, qword ptr [rbx]
	jmp	$_323

$_315:	mov	eax, dword ptr [rbx+0x10]
	cmp	dword ptr [rbx+0x8], 0
	jnz	$_316
	mov	eax, dword ptr [rbx+0xC]
	shr	eax, 20
$_316:	mov	dword ptr [rbp-0x9C], eax
	mov	rcx, qword ptr [rbp-0x80]
	mov	dword ptr [rcx+0x8], 12
	mov	rdx, qword ptr [rbp-0x20]
	imul	eax, eax, 12
	mov	eax, dword ptr [rdx+rax+0x8]
	mov	dword ptr [rcx], eax
	mov	qword ptr [rbp-0x98], 0
$_317:	test	rbx, rbx
	je	$_323
	cmp	dword ptr [rbx+0x8], 0
	jnz	$_318
	mov	eax, dword ptr [rbx+0xC]
	shr	eax, 20
	mov	ecx, dword ptr [rbx+0xC]
	mov	rdx, qword ptr [rbx+0x10]
	mov	edx, dword ptr [rdx+0x28]
	jmp	$_319

$_318:	mov	eax, dword ptr [rbx+0x10]
	mov	ecx, dword ptr [rbx+0x8]
	mov	edx, dword ptr [rbx+0xC]
$_319:	cmp	dword ptr [rbp-0x9C], eax
	jne	$_323
	mov	dword ptr [rbp-0xA0], eax
	mov	dword ptr [rbp-0xA4], ecx
	mov	dword ptr [rbp-0xA8], edx
	mov	rcx, qword ptr [rbp-0x98]
	test	rcx, rcx
	jz	$_321
	mov	eax, dword ptr [rcx+0x4]
	and	eax, 0xFFFFFF
	cmp	edx, dword ptr [rcx]
	jc	$_320
	cmp	edx, dword ptr [rcx]
	jnz	$_321
	cmp	dword ptr [rbp-0xA4], eax
	jnz	$_321
$_320:	jmp	$_322

$_321:	mov	edx, 8
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	qword ptr [rbp-0x90], rax
	add	qword ptr [rbp-0x58], 8
	mov	rcx, qword ptr [rbp-0x48]
	add	dword ptr [rcx+0x4], 8
	mov	rcx, qword ptr [rbp-0x80]
	inc	dword ptr [rcx+0x4]
	add	dword ptr [rcx+0x8], 8
	mov	rcx, qword ptr [rbp-0x90]
	mov	eax, dword ptr [rbp-0xA8]
	mov	dword ptr [rcx], eax
	mov	eax, dword ptr [rbp-0xA4]
	or	eax, 0x80000000
	mov	dword ptr [rcx+0x4], eax
	mov	qword ptr [rbp-0x98], rcx
$_322:	mov	rbx, qword ptr [rbx]
	jmp	$_317

$_323:	test	rbx, rbx
	jne	$_315
$_324:	mov	rsi, qword ptr [rsi+0x70]
	jmp	$_313

$_325:	cmp	qword ptr [rbp-0x48], 0
	jz	$_326
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x18]
$_326:	xor	r8d, r8d
	mov	edx, 241
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x20]
	mov	rsi, qword ptr [rbp-0x58]
	mov	qword ptr [rbp-0xB0], rsi
	mov	rdi, qword ptr [ModuleInfo+0x98+rip]
	mov	eax, dword ptr [rdi]
	cmp	al, 92
	jz	$_327
	cmp	al, 46
	jz	$_327
	cmp	ah, 58
	jz	$_327
	lea	rdx, [DS0003+rip]
	mov	rcx, qword ptr [rbp-0x10]
	call	tstrcpy@PLT
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x10]
	call	tstrcat@PLT
	mov	rdi, qword ptr [rbp-0x18]
$_327:	mov	rcx, rdi
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x8], eax
	add	eax, 7
	mov	word ptr [rsi], ax
	mov	word ptr [rsi+0x2], 4353
	mov	dword ptr [rsi+0x4], 0
	add	qword ptr [rbp-0x58], 8
	mov	r8d, dword ptr [rbp-0x8]
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x58]
	call	$_064
	mov	qword ptr [rbp-0x58], rax
	mov	rcx, qword ptr [rbp-0x10]
	mov	byte ptr [rcx], 0
	mov	rdi, qword ptr [rbp-0x58]
	mov	word ptr [rdi+0x2], 4412
	lea	rdx, [DS0004+rip]
	lea	rcx, [rdi+0x1A]
	call	tstrcpy@PLT
	mov	word ptr [rdi], 46
	add	qword ptr [rbp-0x58], 48
	mov	rdx, qword ptr [rbp-0x58]
	mov	byte ptr [rdx-0x1], 0
	mov	dword ptr [rdi+0x4], 3
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	shr	eax, 4
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_328
	mov	eax, 208
$_328:	mov	word ptr [rdi+0x8], ax
	mov	word ptr [rdi+0xA], 0
	mov	word ptr [rdi+0xC], 0
	mov	word ptr [rdi+0xE], 0
	mov	word ptr [rdi+0x10], 0
	mov	word ptr [rdi+0x12], 2
	mov	word ptr [rdi+0x14], 36
	mov	word ptr [rdi+0x16], 0
	mov	word ptr [rdi+0x18], 0
	mov	rdi, qword ptr [rbp-0x58]
	mov	byte ptr [rdi+0x4], 0
	mov	word ptr [rdi+0x2], 4413
	lea	rdi, [rdi+0x5]
	mov	rsi, qword ptr [rbp-0x18]
	mov	ebx, dword ptr [rbp-0x68]
	mov	eax, 6584163
	stosd
	lea	ecx, [rbx+0x1]
	rep movsb
	mov	eax, 6649957
	stosd
	mov	rsi, qword ptr [_pgmptr+rip]
	mov	rcx, rsi
	call	tstrlen@PLT
	inc	rax
	mov	ecx, eax
	rep movsb
	mov	eax, 6517363
	stosd
	mov	rdx, qword ptr [rbp-0x20]
	mov	rsi, qword ptr [rdx]
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp-0x18]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_329
	lea	rsi, [rsi+rbx+0x1]
$_329:	mov	rcx, rsi
	call	tstrlen@PLT
	inc	rax
	mov	ecx, eax
	rep movsb
	xor	eax, eax
	stosb
	mov	rax, rdi
	mov	rdx, qword ptr [rbp-0x58]
	sub	rax, rdx
	sub	rax, 2
	mov	word ptr [rdx], ax
	mov	qword ptr [rbp-0x58], rdi
	mov	rbx, qword ptr [rbp-0x48]
	sub	rdi, qword ptr [rbp-0xB0]
	add	dword ptr [rbx+0x4], edi
	jmp	$_342

$_330:	mov	rsi, qword ptr [ModuleInfo+0x98+rip]
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	rbx, rax
$_331:	test	ebx, ebx
	jz	$_334
	mov	al, byte ptr [rsi+rbx-0x1]
	cmp	al, 47
	jz	$_332
	cmp	al, 92
	jnz	$_333
$_332:	jmp	$_334

$_333:	dec	ebx
	jmp	$_331

$_334:	add	rsi, rbx
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	ecx, eax
	mov	rdi, qword ptr [rbp-0x58]
	add	eax, 7
	mov	word ptr [rdi], ax
	mov	word ptr [rdi+0x2], 9
	mov	dword ptr [rdi+0x4], 1
	add	rdi, 8
	mov	r8d, ecx
	mov	rdx, rsi
	mov	rcx, rdi
	call	$_064
	mov	rdi, rax
	lea	rcx, [DS0004+rip]
	call	tstrlen@PLT
	mov	ebx, eax
	add	eax, 7
	mov	word ptr [rdi], ax
	mov	word ptr [rdi+0x2], 1
	mov	eax, 208
	cmp	byte ptr [ModuleInfo+0x1CD+rip], 2
	jz	$_335
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	shr	eax, 4
$_335:	test	al, al
	jnz	$_336
	mov	al, 1
$_336:	mov	byte ptr [rdi+0x4], al
	mov	byte ptr [rdi+0x5], 3
	mov	word ptr [rdi+0x6], 0
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	test	cl, cl
	jz	$_341
	mov	edx, 1
	shl	edx, cl
	cmp	cl, 6
	jnz	$_337
	or	byte ptr [rdi+0x6], 0x00
	jmp	$_339

$_337:	mov	eax, 0
	test	edx, 0x68
	jz	$_338
	mov	eax, 1
$_338:	shl	eax, 5
	or	word ptr [rdi+0x6], ax
$_339:	mov	eax, 0
	test	edx, 0x70
	jz	$_340
	mov	eax, 1
$_340:	shl	eax, 8
	or	word ptr [rdi+0x6], ax
$_341:	add	rdi, 8
	mov	r8d, ebx
	lea	rdx, [DS0004+rip]
	mov	rcx, rdi
	call	$_064
	mov	qword ptr [rbp-0x58], rax
$_342:	xor	esi, esi
	jmp	$_344

$_343:	mov	rsi, rax
	cmp	byte ptr [rsi+0x18], 7
	jnz	$_344
	cmp	word ptr [rsi+0x5A], 3
	jz	$_344
	cmp	word ptr [rsi+0x58], 0
	jnz	$_344
	mov	rdx, rsi
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x40]
$_344:	lea	rdx, [rbp-0x4]
	mov	rcx, rsi
	call	SymEnum@PLT
	test	rax, rax
	jnz	$_343
	xor	esi, esi
	jmp	$_353

$_345:	mov	rsi, rax
	jmp	$_352

$_346:	cmp	byte ptr [Options+0x3+rip], 2
	jc	$_354
$_347:	mov	eax, dword ptr [rsi+0x14]
	mov	edx, eax
	and	edx, 0x20
	mov	ecx, eax
	and	ecx, 0x10
	and	eax, 0x40
	cmp	byte ptr [Options+0x3+rip], 3
	jnc	$_348
	mov	eax, ecx
$_348:	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_349
	cmp	rsi, qword ptr [CV8Label+rip]
	jz	$_350
$_349:	test	eax, eax
	jnz	$_350
	test	edx, edx
	jz	$_351
$_350:	jmp	$_353

$_351:	mov	rdx, rsi
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x50]
	jmp	$_353

$_352:	cmp	byte ptr [rsi+0x18], 7
	jz	$_346
	cmp	byte ptr [rsi+0x18], 1
	jz	$_347
$_353:	lea	rdx, [rbp-0x4]
	mov	rcx, rsi
	call	SymEnum@PLT
	test	rax, rax
	jnz	$_345
$_354:	mov	edx, 4096
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	cmp	byte ptr [Options+0x2+rip], 4
	jnz	$_355
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x18]
$_355:	mov	edx, 4096
	lea	rcx, [rbp-0x60]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax+0x8]
	mov	rdi, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rdx+0xC]
	mov	dword ptr [rdi+0x50], eax
	mov	dword ptr [rdx+0x8], 0
	mov	rdi, qword ptr [rbp+0x28]
	mov	rdx, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rdx+0xC]
	mov	dword ptr [rdi+0x50], eax
	mov	dword ptr [rdx+0x8], 0
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

padtab:
	.byte  0xF1, 0xF2, 0xF3

reg64:
	.byte  0x00, 0x02, 0x03, 0x01, 0x07, 0x06, 0x04, 0x05

DS0000:
	.byte  0x40, 0x40, 0x25, 0x75, 0x00

DS0001:
	.byte  0x5F, 0x5F, 0x75, 0x6E, 0x6E, 0x61, 0x6D, 0x65
	.byte  0x64, 0x00

DS0002:
	.byte  0x54, 0x4C, 0x53, 0x00

vtable:
	.quad  dbgcv_flushpt
	.quad  dbgcv_flushps
	.quad  dbgcv_padbytes
	.quad  dbgcv_alignps
	.quad  dbgcv_flush_section
	.quad  dbgcv_write_bitfield
	.quad  dbgcv_write_array_type
	.quad  dbgcv_write_ptr_type
	.quad  dbgcv_write_type
	.quad  dbgcv_write_type_procedure
	.quad  dbgcv_write_symbol
	.quad  dbgcv_cntproc
	.quad  dbgcv_memberproc
	.quad  dbgcv_enum_fields

DS0003:
	.byte  0x5C, 0x00

DS0004:
	.byte  0x41, 0x73, 0x6D, 0x63, 0x20, 0x4D, 0x61, 0x63
	.byte  0x72, 0x6F, 0x20, 0x41, 0x73, 0x73, 0x65, 0x6D
	.byte  0x62, 0x6C, 0x65, 0x72, 0x00


.att_syntax prefix
