
.intel_syntax noprefix

.global codegen
.global szNull

.extern vex_flags
.extern ResWordTable
.extern opnd_clstab
.extern CurrProc
.extern get_curr_srcfile
.extern GetLineNumber
.extern LstWrite
.extern GetCurrOffset
.extern AddFloatingPointEmulationFixup
.extern OperandSize
.extern optable_idx
.extern InstrTable
.extern AddLinnumDataRef
.extern OutputBytes
.extern OutputByte
.extern asmerr
.extern write_to_file
.extern Options
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

$_001:	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	byte ptr [rbp-0x2], 0
	mov	byte ptr [rbp-0x3], 0
	movzx	ecx, word ptr [rsi+0xE]
	lea	rax, [ResWordTable+rip]
	imul	ecx, ecx, 16
	mov	al, byte ptr [rcx+rax+0x3]
	mov	byte ptr [rbp-0x4], al
	and	al, 0xFFFFFFE0
	mov	byte ptr [rbp-0x5], al
	test	byte ptr [rbp-0x4], 0x10
	jz	$_003
	test	byte ptr [ModuleInfo+0x356+rip], 0x0B
	jnz	$_002
	mov	byte ptr [rsi+0xB], 1
$_002:	jmp	$_004

$_003:	cmp	byte ptr [ModuleInfo+0x356+rip], 4
	jnz	$_004
	mov	byte ptr [rsi+0xB], 1
$_004:	cmp	byte ptr [Options+0x1+rip], 0
	jz	$_005
	call	GetLineNumber@PLT
	mov	ebx, eax
	call	get_curr_srcfile@PLT
	mov	edx, ebx
	mov	ecx, eax
	call	AddLinnumDataRef@PLT
$_005:	mov	rdi, qword ptr [rsi+0x58]
	movzx	ebx, word ptr [rdi+0x4]
	test	ebx, 0xFD07
	jz	$_006
	movzx	eax, word ptr [rsi+0xE]
	cmp	eax, 1266
	jz	$_006
	cmp	eax, 1272
	jz	$_006
	mov	byte ptr [rsi+0xA], 0
$_006:	mov	edx, dword ptr [ModuleInfo+0x1C0+rip]
	mov	ecx, edx
	mov	eax, ebx
	and	ecx, 0xF0
	and	eax, 0xF0
	cmp	eax, ecx
	ja	$_007
	mov	ecx, edx
	mov	eax, ebx
	and	ecx, 0x07
	and	eax, 0x07
	cmp	eax, ecx
	ja	$_007
	mov	ecx, edx
	mov	eax, ebx
	and	ecx, 0xFF00
	and	eax, 0xFF00
$_007:	cmp	eax, ecx
	jbe	$_009
	movzx	eax, word ptr [rsi+0xE]
	sub	eax, 531
	lea	rcx, [optable_idx+rip]
	movzx	eax, word ptr [rcx+rax*2]
	lea	rcx, [InstrTable+rip]
	mov	ax, word ptr [rcx+rax*8+0x4]
	and	eax, 0xF0
	mov	ecx, 2085
	cmp	ebx, 48
	jnz	$_008
	cmp	eax, 48
	ja	$_008
	mov	ecx, 2087
$_008:	call	asmerr@PLT
$_009:	mov	al, byte ptr [rdi+0x2]
	and	eax, 0x07
	cmp	byte ptr [ModuleInfo+0x1D9+rip], 1
	jnz	$_010
	cmp	byte ptr [rsi+0x63], 0
	jnz	$_010
	test	ebx, 0x7
	jz	$_010
	cmp	eax, 5
	jz	$_010
	mov	byte ptr [rbp-0x3], 1
	mov	rcx, rsi
	call	AddFloatingPointEmulationFixup@PLT
$_010:	cmp	byte ptr [rsi+0xB], 0
	jz	$_011
	mov	al, byte ptr [rdi+0x3]
	mov	byte ptr [rbp-0x2], al
	mov	ecx, 98
	call	OutputByte@PLT
$_011:	cmp	dword ptr [rsi], -2
	jz	$_014
	mov	eax, dword ptr [rsi]
	sub	eax, 531
	lea	rcx, [optable_idx+rip]
	movzx	edx, word ptr [rcx+rax*2]
	lea	rcx, [InstrTable+rip]
	mov	al, byte ptr [rcx+rdx*8+0x2]
	and	eax, 0x07
	mov	cl, byte ptr [rdi+0x2]
	and	ecx, 0x07
	cmp	byte ptr [ModuleInfo+0x1D6+rip], 1
	jnz	$_012
	cmp	eax, 2
	jnz	$_012
	cmp	ecx, 3
	jnz	$_012
	mov	eax, ecx
$_012:	mov	byte ptr [rbp-0x6], al
	cmp	ecx, eax
	jz	$_013
	mov	ecx, 2068
	call	asmerr@PLT
	jmp	$_014

$_013:	lea	rcx, [InstrTable+rip]
	movzx	ecx, byte ptr [rcx+rdx*8+0x6]
	call	OutputByte@PLT
$_014:	test	byte ptr [rdi+0x4], 0x07
	jz	$_019
	mov	cl, byte ptr [rdi+0x2]
	and	ecx, 0x07
	cmp	word ptr [rsi+0xE], 910
	jnz	$_016
	cmp	byte ptr [rbp-0x3], 0
	jz	$_015
	mov	ecx, 144
	call	OutputByte@PLT
$_015:	jmp	$_019

$_016:	cmp	byte ptr [rbp-0x3], 0
	jnz	$_017
	cmp	ecx, 4
	jnz	$_018
$_017:	mov	ecx, 155
	call	OutputByte@PLT
	jmp	$_019

$_018:	cmp	ecx, 5
	jz	$_019
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 32
	jnc	$_019
	mov	ecx, 155
	call	OutputByte@PLT
$_019:	mov	al, byte ptr [rdi+0x1]
	jmp	$_030

$_020:	cmp	byte ptr [rsi+0x63], 1
	jc	$_021
	mov	byte ptr [rsi+0xA], 1
$_021:	jmp	$_031

$_022:	cmp	byte ptr [rsi+0x63], 0
	jnz	$_023
	mov	byte ptr [rsi+0xA], 1
$_023:	jmp	$_031

$_024:	cmp	byte ptr [rsi+0x63], 1
	jnz	$_025
	mov	byte ptr [rsi+0x9], 1
$_025:	jmp	$_031

$_026:	cmp	byte ptr [rsi+0x63], 1
	jz	$_027
	mov	byte ptr [rsi+0x9], 1
$_027:	jmp	$_031

$_028:	mov	byte ptr [rsi+0xA], 0
	jmp	$_031

$_029:	or	byte ptr [rsi+0x8], 0x08
	jmp	$_031

$_030:	cmp	al, 1
	jz	$_020
	cmp	al, 2
	jz	$_022
	cmp	al, 3
	jz	$_024
	cmp	al, 4
	jz	$_026
	cmp	al, 23
	jz	$_028
	cmp	al, 6
	jz	$_029
	cmp	al, 24
	jz	$_029
$_031:	test	byte ptr [rbp-0x4], 0x08
	jnz	$_036
	jmp	$_035

$_032:	mov	byte ptr [rsi+0xA], 1
	jmp	$_036

$_033:	mov	ecx, 242
	call	OutputByte@PLT
	jmp	$_036

$_034:	mov	ecx, 243
	call	OutputByte@PLT
	jmp	$_036

$_035:	cmp	al, 19
	jz	$_032
	cmp	al, 27
	jz	$_032
	cmp	al, 28
	jz	$_032
	cmp	al, 21
	jz	$_033
	cmp	al, 29
	jz	$_033
	cmp	al, 5
	jz	$_034
	cmp	al, 22
	jz	$_034
	cmp	al, 36
	jz	$_034
$_036:	cmp	byte ptr [rsi+0x9], 0
	jz	$_037
	test	byte ptr [rsi+0x66], 0xFFFFFF80
	jnz	$_037
	test	byte ptr [rdi+0x3], 0x08
	jnz	$_037
	mov	ecx, 103
	call	OutputByte@PLT
$_037:	cmp	byte ptr [rsi+0xA], 0
	jz	$_039
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 48
	jnc	$_038
	mov	ecx, 2087
	call	asmerr@PLT
$_038:	mov	ecx, 102
	call	OutputByte@PLT
$_039:	cmp	dword ptr [rsi+0x4], -2
	jz	$_040
	mov	eax, dword ptr [rsi+0x4]
	lea	rcx, [sr_prefix+rip]
	mov	ecx, dword ptr [rcx+rax]
	call	OutputByte@PLT
$_040:	test	byte ptr [rdi+0x2], 0xFFFFFF80
	jz	$_041
	mov	al, byte ptr [rsi+0x8]
	mov	ah, al
	mov	dl, al
	and	ah, 0xFFFFFFFA
	and	dl, 0x04
	shr	dl, 2
	and	al, 0x01
	shl	al, 2
	or	al, dl
	or	al, ah
	mov	byte ptr [rsi+0x8], al
	mov	al, byte ptr [rsi+0x61]
	mov	byte ptr [rbp-0x6], al
	mov	ah, al
	mov	dl, al
	and	ah, 0xFFFFFFC0
	shr	dl, 3
	and	dl, 0x07
	shl	al, 3
	and	al, 0x38
	or	al, dl
	or	al, ah
	mov	byte ptr [rsi+0x61], al
$_041:	test	byte ptr [rbp-0x4], 0x08
	je	$_199
	movzx	edx, word ptr [rsi+0xE]
	lea	rcx, [vex_flags+rip]
	mov	al, byte ptr [rcx+rdx-0x515]
	mov	byte ptr [rbp-0x1], al
	xor	ebx, ebx
	mov	cl, byte ptr [rsi+0xC]
	mov	ch, byte ptr [rsi+0xD]
	and	al, 0xFFFFFF80
	cmp	byte ptr [rbp-0x2], 0
	jnz	$_043
	cmp	edx, 1372
	jz	$_042
	cmp	edx, 1396
	jnz	$_043
$_042:	xor	eax, eax
$_043:	mov	bh, al
	mov	al, byte ptr [rdi+0x1]
	jmp	$_044
$C003E: mov	bl, -128
	jmp	$C003F
$C0040: or	bh, 0x04
	jmp	$C003F
$C0042: or	bh, 0x04
$C0044: or	bh, 0x01
	jmp	$C003F
$C0048: or	bh, 0x02
	jmp	$C003F
$C004A: or	bh, 0x03
	jmp	$C003F
$_044:	cmp	al, 17
	jl	$C003F
	cmp	al, 35
	jg	$C003F
	push	rax
	movsx	rax, al
	lea	r11, [$C003F+rip]
	movzx	eax, byte ptr [r11+rax-(17)+(IT$C004C-$C003F)]
	movzx	eax, byte ptr [r11+rax+($C004C-$C003F)]
	sub	r11, rax
	pop	rax
	jmp	r11
$C004C:
	.byte $C003F-$C003E
	.byte $C003F-$C0040
	.byte $C003F-$C0042
	.byte $C003F-$C0044
	.byte $C003F-$C0048
	.byte $C003F-$C004A
	.byte 0
IT$C004C:
	.byte 1
	.byte 6
	.byte 3
	.byte 2
	.byte 5
	.byte 4
	.byte 6
	.byte 6
	.byte 0
	.byte 6
	.byte 3
	.byte 3
	.byte 5
	.byte 4
	.byte 6
	.byte 6
	.byte 3
	.byte 1
	.byte 2
$C003F: test	ch, 0x01
	jz	$_045
	or	bh, 0x04
$_045:	test	cl, 0x10
	jnz	$_047
	test	cl, 0x04
	jz	$_046
	test	ch, 0x10
	jnz	$_046
	test	ch, 0x08
	jz	$_047
$_046:	test	cl, 0x04
	jz	$_048
	cmp	ch, 8
	jnz	$_048
$_047:	or	cl, 0x08
$_048:	test	byte ptr [rsi+0x10], 0x60
	jnz	$_049
	test	dword ptr [rsi+0x28], 0x6060
	jnz	$_049
	cmp	dword ptr [rsi+0x10], 0
	jnz	$_052
	test	byte ptr [rbp-0x1], 0x01
	jz	$_052
$_049:	or	bh, 0x04
	test	ch, 0x10
	jnz	$_050
	test	byte ptr [rsi+0x29], 0x40
	jnz	$_050
	test	cl, 0x10
	jz	$_051
$_050:	or	cl, 0x48
	mov	al, byte ptr [rbp-0x2]
	and	al, 0x10
	or	bl, al
	jmp	$_052

$_051:	or	cl, 0x20
$_052:	cmp	byte ptr [rsi+0x65], 0
	jz	$_056
	mov	dl, byte ptr [rsi+0x65]
	mov	al, 16
	and	dl, 0x3F
	sub	al, dl
	shl	al, 3
	or	bh, al
	mov	al, byte ptr [rsi+0x65]
	shr	al, 1
	and	al, 0x60
	or	cl, al
	test	cl, 0x40
	jz	$_053
	or	cl, 0x08
$_053:	test	cl, 0x10
	jz	$_055
	test	ch, 0x02
	jz	$_054
	and	cl, 0xFFFFFFF7
	jmp	$_055

$_054:	or	cl, 0x08
$_055:	jmp	$_059

$_056:	or	bh, 0x60
	test	byte ptr [rdi+0x3], 0x08
	jnz	$_057
	or	bh, 0x10
$_057:	or	cl, 0x08
	test	ch, 0x08
	jz	$_058
	test	byte ptr [rbp-0x2], 0x04
	jz	$_058
	test	byte ptr [rsi+0x29], 0x70
	jnz	$_059
$_058:	or	bh, 0x08
$_059:	cmp	byte ptr [rdi+0x1], 25
	jnc	$_060
	test	byte ptr [rsi+0x8], 0x0B
	je	$_114
$_060:	cmp	byte ptr [rbp-0x2], 0
	jnz	$_061
	mov	qword ptr [rbp-0x10], rcx
	mov	ecx, 196
	call	OutputByte@PLT
	mov	rcx, qword ptr [rbp-0x10]
$_061:	mov	al, byte ptr [rdi+0x1]
	jmp	$_068

$_062:
	cmp	word ptr [rsi+0xE], 1591
	jnz	$_063
	or	ebx, 0x303
$_063:	jmp	$_069

$_064:	or	bl, 0x02
	jmp	$_069

$_065:	or	bl, 0x03
	jmp	$_069

$_066:	cmp	byte ptr [rdi+0x1], 16
	jc	$_067
	or	bl, 0x01
$_067:	jmp	$_069

$_068:	cmp	al, 31
	jz	$_062
	cmp	al, 25
	jz	$_064
	cmp	al, 27
	jz	$_064
	cmp	al, 29
	jz	$_064
	cmp	al, 30
	jz	$_064
	cmp	al, 26
	jz	$_065
	cmp	al, 28
	jz	$_065
	jmp	$_066

$_069:	mov	al, byte ptr [rsi+0x8]
	test	al, 0x01
	jnz	$_070
	or	bl, 0x20
$_070:	test	al, 0x02
	jnz	$_071
	or	bl, 0x40
$_071:	test	al, 0x04
	jnz	$_072
	or	bl, 0xFFFFFF80
$_072:	test	al, 0x08
	jz	$_073
	or	bh, 0xFFFFFF80
$_073:	mov	ah, byte ptr [rbp-0x2]
	test	ah, ah
	je	$_113
	test	ch, 0x07
	je	$_102
	mov	al, ch
	and	al, 0x0F
	jmp	$_100

$_074:	and	cl, 0xFFFFFFF7
$_075:	mov	al, bl
	and	al, 0x6F
	cmp	ax, 2146
	jnz	$_076
	or	byte ptr [rbp-0x2], 0xFFFFFFE0
	jmp	$_101

$_076:	cmp	ah, 32
	jnz	$_077
	add	rdi, 8
$_077:	test	ah, 0x02
	jnz	$_079
	cmp	byte ptr [rbp-0x5], -128
	jz	$_078
	cmp	byte ptr [rbp-0x5], 32
	jnz	$_079
$_078:	and	bl, 0xFFFFFFEF
	jmp	$_082

$_079:	and	bl, 0xFFFFFFBF
	test	ch, 0xFFFFFF80
	jz	$_080
	cmp	dword ptr [rsi+0x10], 64
	jz	$_081
$_080:	test	ch, 0x10
	jnz	$_082
	test	byte ptr [rsi+0x62], 0xFFFFFFC0
	jnz	$_082
$_081:	or	bl, 0x10
$_082:	jmp	$_101

$_083:	test	ah, 0x40
	jnz	$_086
	test	byte ptr [rsi+0x2A], 0x07
	jnz	$_084
	test	byte ptr [rsi+0x42], 0x07
	jz	$_086
$_084:	and	bl, 0xFFFFFFBF
	test	byte ptr [rsi+0x2A], 0x07
	jz	$_085
	or	bl, 0x10
	and	cl, 0xFFFFFFF7
$_085:	jmp	$_087

$_086:	and	cl, 0xFFFFFFF7
	and	bl, 0xFFFFFFEF
$_087:	jmp	$_101

$_088:	cmp	ah, 16
	jnz	$_089
	or	bl, 0xFFFFFF80
	and	bh, 0xFFFFFF8F
	and	cl, 0xFFFFFFF7
	jmp	$_101

$_089:	cmp	ah, 32
	jnz	$_090
	and	bh, 0xFFFFFFFD
	or	bh, 0x01
	add	rdi, 8
	cmp	byte ptr [rdi+0x6], 110
	jz	$_090
	add	rdi, 8
$_090:	and	bl, 0xFFFFFFEF
	test	ch, 0x10
	jnz	$_092
	cmp	byte ptr [rbp-0x5], -128
	jnz	$_091
	test	cl, cl
	jnz	$_092
$_091:	or	cl, 0x08
$_092:	jmp	$_101

$_093:	and	cl, 0xFFFFFFF7
$_094:	and	bl, 0xFFFFFFAF
	jmp	$_101

$_095:	mov	al, ah
	and	al, 0xFFFFFFFD
	cmp	al, -128
	jz	$_098
	test	ch, 0x10
	jnz	$_096
	test	byte ptr [rsi+0x62], 0xFFFFFFC0
	jz	$_098
$_096:	test	byte ptr [rbp-0x1], 0xFFFFFF80
	jnz	$_097
	cmp	byte ptr [rbp-0x5], -128
	jz	$_098
$_097:	and	cl, 0xFFFFFFF7
	or	bl, 0x10
	jmp	$_099

$_098:	and	bl, 0xFFFFFFEF
$_099:	jmp	$_101

$_100:	cmp	al, 14
	je	$_074
	cmp	al, 2
	je	$_075
	cmp	al, 12
	je	$_077
	cmp	al, 11
	je	$_083
	cmp	al, 9
	je	$_088
	cmp	al, 1
	je	$_089
	cmp	al, 15
	jz	$_093
	cmp	al, 13
	jz	$_094
	cmp	al, 3
	jz	$_094
	cmp	al, 10
	jz	$_095
$_101:	jmp	$_113

$_102:	jmp	$_112

$_103:	mov	bl, -111
	test	ch, 0x10
	jz	$_113
	mov	bl, -79
	test	ch, 0x40
	jz	$_113
	mov	bl, -47
	jmp	$_113

$_104:	mov	bl, -79
	jmp	$_113

$_105:	test	cl, 0x10
	jz	$_106
	test	byte ptr [rbp-0x2], 0x04
	jz	$_107
$_106:	or	bl, 0x10
$_107:	or	cl, 0x08
	mov	al, bl
	and	al, 0x6F
	cmp	byte ptr [rbp-0x2], 8
	jnz	$_108
	cmp	al, 98
	jnz	$_108
	mov	al, bl
	and	al, 0xFFFFFFF0
	or	byte ptr [rbp-0x2], al
$_108:	jmp	$_113

$_109:	mov	al, bl
	and	al, 0x0F
	cmp	al, 1
	jnz	$_110
	or	bl, 0x10
	jmp	$_111

$_110:	cmp	byte ptr [rbp-0x2], 8
	jnz	$_111
	cmp	al, 2
	jnz	$_111
	mov	al, bl
	and	al, 0xFFFFFFF0
	or	al, 0xFFFFFF90
	or	byte ptr [rbp-0x2], al
$_111:	jmp	$_113

$_112:	cmp	bl, -63
	jz	$_103
	cmp	bl, -59
	jz	$_104
	cmp	bl, -30
	jz	$_105
	cmp	bl, -29
	jz	$_105
	jmp	$_109

$_113:	jmp	$_146

$_114:	test	byte ptr [rsi+0x8], 0x04
	jnz	$_115
	or	bh, 0xFFFFFF80
$_115:	cmp	byte ptr [rbp-0x2], 0
	jnz	$_116
	mov	bl, -59
	jmp	$_146

$_116:	mov	ah, byte ptr [rbp-0x2]
	mov	al, ch
	and	al, 0x0F
	jmp	$_129

$_117:	and	cl, 0xFFFFFFF7
	jmp	$_130

$_118:	test	ah, 0x40
	jnz	$_119
	cmp	dword ptr [rsi+0x40], 65536
	jnz	$_120
$_119:	and	cl, 0xFFFFFFF7
$_120:	jmp	$_130

$_121:	and	cl, 0xFFFFFFF7
	jmp	$_130

$_122:	test	ch, 0x10
	jz	$_123
	and	cl, 0xFFFFFFF7
$_123:	jmp	$_130

$_124:	cmp	ah, 32
	jnz	$_125
	and	bh, 0xFFFFFFFD
	or	bh, 0x01
	add	rdi, 8
	jmp	$_126

$_125:	cmp	ah, -32
	jnz	$_126
	test	ch, 0x10
	jz	$_126
	cmp	dword ptr [rsi+0x10], 64
	jnz	$_126
	cmp	dword ptr [rsi+0x28], 64
	jnz	$_126
	mov	ah, -80
$_126:	jmp	$_130

$_127:	cmp	ah, 16
	jnz	$_128
	and	bh, 0xFFFFFF8F
	and	cl, 0xFFFFFFF7
$_128:	jmp	$_130

$_129:	cmp	al, 14
	jz	$_117
	cmp	al, 11
	jz	$_118
	cmp	al, 15
	jz	$_121
	cmp	al, 10
	jz	$_122
	cmp	al, 2
	jz	$_124
	cmp	al, 1
	jz	$_124
	cmp	al, 9
	jz	$_127
$_130:	mov	al, ah
	and	al, 0xFFFFFFF0
	or	al, 0x01
	or	bl, al
	test	byte ptr [rsi+0x8], 0x04
	jz	$_136
	mov	bl, 97
	cmp	dword ptr [rsi+0x10], 4
	jz	$_131
	test	ch, 0x40
	jz	$_133
$_131:	or	bl, 0x10
	test	ch, 0x07
	jz	$_132
	and	bl, 0xFFFFFFBF
$_132:	jmp	$_135

$_133:	cmp	byte ptr [rbp-0x2], 16
	jnz	$_134
	or	bl, 0xFFFFFFF0
	jmp	$_135

$_134:	test	ch, 0xFFFFFF80
	jz	$_135
	mov	al, ch
	and	al, 0x07
	cmp	al, 3
	jnz	$_135
	test	ch, 0x08
	jnz	$_135
	mov	bl, 33
$_135:	jmp	$_146

$_136:	test	ch, 0x01
	jz	$_142
	mov	bl, -31
	test	ch, 0x02
	jz	$_139
	test	ch, 0x08
	jz	$_137
	test	ch, 0x08
	jz	$_138
	test	ch, 0x04
	jz	$_138
$_137:	mov	bl, -95
$_138:	jmp	$_141

$_139:	test	byte ptr [rbp-0x1], 0x20
	jz	$_140
	test	byte ptr [rsi+0x2A], 0x01
	jz	$_140
	mov	bl, -15
	jmp	$_141

$_140:	or	cl, 0x08
$_141:	jmp	$_146

$_142:	test	ch, 0x02
	jnz	$_144
	mov	bl, -15
	or	cl, 0x08
	cmp	byte ptr [rbp-0x2], 16
	jnz	$_143
	and	bh, 0xFFFFFFF7
$_143:	jmp	$_146

$_144:	test	ch, 0x08
	jz	$_145
	mov	bl, -15
	jmp	$_146

$_145:	test	ch, 0x02
	jz	$_146
	cmp	byte ptr [rbp-0x2], 32
	jnz	$_146
	mov	bl, -31
$_146:	shl	ecx, 16
	or	ebx, ecx
	cmp	byte ptr [rbp-0x2], 0
	je	$_188
	xor	eax, eax
	xor	edx, edx
	test	byte ptr [rbp-0x2], 0x02
	jz	$_147
	and	byte ptr [rbp-0x1], 0xFFFFFFBF
$_147:	test	dword ptr [rsi+0x28], 0x607F00
	jz	$_148
	mov	edx, 24
$_148:	test	dword ptr [rsi+rdx+0x10], 0x607F00
	je	$_184
	cmp	byte ptr [rbp-0x5], -128
	jnz	$_153
	mov	eax, 4
	cmp	byte ptr [rsi+0x60], 0
	jnz	$_149
	mov	eax, 1
	jmp	$_152

$_149:	cmp	byte ptr [rsi+0x60], 1
	jnz	$_150
	mov	eax, 2
	jmp	$_152

$_150:	test	byte ptr [rbp-0x2], 0x02
	jnz	$_151
	test	byte ptr [rbp-0x1], 0xFFFFFF80
	jz	$_152
$_151:	mov	eax, 8
$_152:	jmp	$_184

$_153:	test	byte ptr [rsi+0xC], 0x10
	jz	$_156
	mov	eax, 4
	test	byte ptr [rbp-0x2], 0x02
	jnz	$_154
	test	byte ptr [rbp-0x1], 0xFFFFFF80
	jz	$_155
	test	byte ptr [rbp-0x1], 0x40
	jnz	$_155
$_154:	mov	eax, 8
$_155:	jmp	$_184

$_156:	jmp	$_183

$_157:	mov	al, byte ptr [rsi+0x60]
	inc	al
	jmp	$_184

$_158:	test	byte ptr [rsi+rdx+0x11], 0x40
	jz	$_159
	mov	eax, 64
	jmp	$_162

$_159:	test	byte ptr [rsi+rdx+0x11], 0x20
	jz	$_160
	mov	eax, 32
	jmp	$_162

$_160:	test	byte ptr [rsi+rdx+0x11], 0x10
	jz	$_161
	mov	eax, 16
	jmp	$_162

$_161:	jmp	$_184

$_162:	mov	ecx, 24
	test	edx, edx
	jz	$_163
	xor	ecx, ecx
$_163:	cmp	dword ptr [rsi+rcx+0x10], 64
	jnz	$_164
	mov	eax, 64
	jmp	$_165

$_164:	cmp	dword ptr [rsi+rcx+0x10], 32
	jnz	$_165
	mov	eax, 32
$_165:	jmp	$_181

$_166:	cmp	eax, 64
	jnz	$_167
	mov	eax, 16
	jmp	$_169

$_167:	cmp	eax, 32
	jnz	$_168
	mov	eax, 8
	jmp	$_169

$_168:	mov	eax, 4
$_169:	jmp	$_182

$_170:	cmp	eax, 64
	jnz	$_171
	mov	eax, 8
	jmp	$_173

$_171:	cmp	eax, 32
	jnz	$_172
	mov	eax, 4
	jmp	$_173

$_172:	mov	eax, 2
$_173:	jmp	$_182

$_174:	cmp	eax, 64
	jnz	$_175
	mov	eax, 32
	jmp	$_177

$_175:	cmp	eax, 32
	jnz	$_176
	mov	eax, 16
	jmp	$_177

$_176:	mov	eax, 8
$_177:	jmp	$_182

$_178:	mov	eax, 16
	test	byte ptr [rbp-0x1], 0xFFFFFF80
	jnz	$_182
	mov	eax, 8
	jmp	$_182

$_179:	mov	eax, 32
	test	byte ptr [rbp-0x1], 0xFFFFFF80
	jnz	$_182
$_180:	mov	eax, 16
	jmp	$_182

$_181:	cmp	byte ptr [rbp-0x5], 32
	je	$_166
	cmp	byte ptr [rbp-0x5], 64
	jz	$_170
	cmp	byte ptr [rbp-0x5], 96
	jz	$_174
	cmp	byte ptr [rbp-0x5], -96
	jz	$_178
	cmp	byte ptr [rbp-0x5], -64
	jz	$_179
	cmp	byte ptr [rbp-0x5], -32
	jz	$_180
$_182:	jmp	$_184

$_183:	cmp	byte ptr [rsi+0x60], 15
	je	$_157
	cmp	byte ptr [rsi+0x60], 31
	je	$_157
	cmp	byte ptr [rsi+0x60], 63
	je	$_157
	cmp	byte ptr [rsi+0x60], 3
	je	$_157
	cmp	byte ptr [rsi+0x60], 7
	je	$_157
	jmp	$_158

$_184:	test	eax, eax
	jz	$_185
	cmp	dword ptr [rsi+rdx+0x20], 0
	jz	$_185
	or	byte ptr [rsi+0x61], 0xFFFFFF80
	and	byte ptr [rsi+0x61], 0xFFFFFFBF
	mov	ecx, dword ptr [rsi+rdx+0x20]
	dec	eax
	and	ecx, eax
	test	ecx, ecx
	jnz	$_185
	push	rdx
	lea	ecx, [rax+0x1]
	mov	eax, dword ptr [rsi+rdx+0x20]
	cdq
	idiv	ecx
	pop	rdx
	cmp	eax, -128
	jl	$_185
	cmp	eax, 127
	jg	$_185
	mov	dword ptr [rsi+rdx+0x20], eax
	and	byte ptr [rsi+0x61], 0x7F
	or	byte ptr [rsi+0x61], 0x40
$_185:	test	byte ptr [rbp-0x2], 0x08
	jz	$_188
	or	bh, 0x10
	mov	cl, byte ptr [rsi+0x64]
	mov	al, cl
	and	ecx, 0x1F
	and	eax, 0x40
	or	eax, 0x01
	mov	edx, ecx
	shr	edx, 1
	not	edx
	and	edx, 0x08
	or	eax, edx
	test	al, 0x40
	jz	$_186
	cmp	dword ptr [rsi+0x28], 32
	jnz	$_186
	and	al, 0xFFFFFFBF
	or	al, 0x20
$_186:	shl	eax, 16
	and	ebx, 0xFF00FFFF
	or	ebx, eax
	shl	ecx, 3
	not	ecx
	and	ecx, 0x40
	mov	al, byte ptr [rbp-0x2]
	and	eax, 0xF0
	or	eax, 0x02
	or	eax, ecx
	mov	cl, byte ptr [rsi+0x62]
	and	ecx, 0xC0
	cmp	cl, -128
	jnz	$_187
	or	al, 0x20
$_187:	mov	bl, al
	mov	byte ptr [rsi+0x64], 0
$_188:	movzx	ecx, bl
	call	OutputByte@PLT
	shr	ebx, 8
	cmp	byte ptr [rbp-0x2], 0
	jz	$_191
	or	bl, 0xFFFFFF84
	test	byte ptr [rbp-0x1], 0x40
	jz	$_189
	and	bl, 0x7F
$_189:	movzx	ecx, bl
	call	OutputByte@PLT
	shr	ebx, 8
	test	bh, 0x20
	jz	$_190
	test	byte ptr [rsi+0xC], 0x40
	jnz	$_190
	and	bl, 0xFFFFFFBF
$_190:	movzx	ecx, bl
	call	OutputByte@PLT
	jmp	$_198

$_191:	mov	rdx, rdi
	mov	rdi, qword ptr [rsi+0x58]
	test	byte ptr [rdi+0x3], 0x08
	jz	$_197
	cmp	byte ptr [rdi+0x3], 9
	jnz	$_196
	mov	al, byte ptr [rbp-0x6]
	not	al
	shl	al, 3
	and	al, 0x38
	and	bl, 0xFFFFFFC7
	or	bl, al
	test	byte ptr [rsi+0x8], 0x04
	jz	$_192
	and	bl, 0xFFFFFFBF
$_192:
	cmp	word ptr [rsi+0xE], 1593
	jnz	$_193
	and	byte ptr [rsi+0x61], 0xFFFFFFF7
	jmp	$_195

$_193:
	cmp	word ptr [rsi+0xE], 1593
	jnz	$_194
	mov	al, byte ptr [rbp-0x6]
	and	al, 0xFFFFFFC8
	mov	byte ptr [rsi+0x61], al
	jmp	$_195

$_194:	and	byte ptr [rsi+0x61], 0xFFFFFFCF
$_195:	jmp	$_197

$_196:	mov	al, byte ptr [rsi+0x64]
	shl	al, 3
	not	al
	and	al, 0x38
	and	bl, 0xFFFFFFC7
	or	bl, al
	mov	al, byte ptr [rsi+0x64]
	shr	al, 4
	or	bl, al
	mov	byte ptr [rsi+0x64], 0
$_197:	mov	rdi, rdx
	movzx	ecx, bl
	call	OutputByte@PLT
$_198:	jmp	$_206

$_199:	cmp	byte ptr [rsi+0x8], 0
	jz	$_201
	cmp	word ptr [rsi+0xE], 1278
	jz	$_201
	cmp	word ptr [rsi+0xE], 1215
	jz	$_201
	cmp	byte ptr [rsi+0x63], 2
	jz	$_200
	mov	ecx, 2024
	call	asmerr@PLT
$_200:	movzx	eax, byte ptr [rsi+0x8]
	or	eax, 0x40
	mov	ecx, eax
	call	OutputByte@PLT
$_201:	cmp	byte ptr [rdi+0x1], 16
	jc	$_206
	mov	ecx, 15
	call	OutputByte@PLT
	mov	al, byte ptr [rdi+0x1]
	jmp	$_205

$_202:	mov	ecx, 15
	call	OutputByte@PLT
	jmp	$_206

$_203:	mov	ecx, 56
	call	OutputByte@PLT
	jmp	$_206

$_204:	mov	ecx, 58
	call	OutputByte@PLT
	jmp	$_206

$_205:	cmp	al, 18
	jz	$_202
	cmp	al, 25
	jz	$_203
	cmp	al, 29
	jz	$_203
	cmp	al, 27
	jz	$_203
	cmp	al, 26
	jz	$_204
	cmp	al, 36
	jz	$_204
	cmp	al, 28
	jz	$_204
$_206:	xor	ecx, ecx
	test	byte ptr [rsi+0x66], 0x01
	jz	$_207
	inc	ecx
$_207:	mov	al, byte ptr [rdi+0x2]
	and	eax, 0x70
	shr	eax, 4
	jmp	$_223

$_208:	mov	al, byte ptr [rsi+0x61]
	and	al, 0x3F
	or	al, byte ptr [rdi+0x6]
	mov	ecx, eax
	call	OutputByte@PLT
	jmp	$_224

$_209:	mov	al, byte ptr [rdi+0x6]
	or	al, cl
	mov	ecx, eax
	call	OutputByte@PLT
	jmp	$_224

$_210:	xor	ecx, ecx
$_211:	cmp	byte ptr [rdi+0x1], 18
	jz	$_212
	mov	al, byte ptr [rdi+0x6]
	or	al, cl
	or	al, byte ptr [rsi+0x64]
	mov	ecx, eax
	call	OutputByte@PLT
$_212:	mov	bl, byte ptr [rdi+0x7]
	or	bl, byte ptr [rsi+0x61]
	test	byte ptr [rsi+0x66], 0xFFFFFF80
	jz	$_213
	and	bl, 0x7F
$_213:	movzx	eax, word ptr [rsi+0xE]
	jmp	$_216

$_214:	mov	bl, -8
	or	bl, byte ptr [rsi+0x61]
	jmp	$_217

$_215:	mov	ecx, 246
	call	OutputByte@PLT
	jmp	$_217

$_216:	cmp	eax, 1278
	jz	$_214
	cmp	eax, 1279
	jz	$_215
$_217:	mov	ecx, ebx
	call	OutputByte@PLT
	cmp	byte ptr [rsi+0x63], 0
	jnz	$_218
	cmp	byte ptr [rsi+0x9], 0
	jz	$_224
$_218:	cmp	byte ptr [rsi+0x63], 1
	jnz	$_219
	cmp	byte ptr [rsi+0x9], 0
	jnz	$_224
$_219:	and	bl, 0xFFFFFFC7
	jmp	$_221

$_220:	movzx	ecx, byte ptr [rsi+0x62]
	call	OutputByte@PLT
	jmp	$_222

$_221:	cmp	bl, 4
	jz	$_220
	cmp	bl, 68
	jz	$_220
	cmp	bl, -124
	jz	$_220
$_222:	jmp	$_224

$_223:	cmp	eax, 3
	je	$_208
	cmp	eax, 1
	je	$_209
	cmp	eax, 2
	je	$_210
	jmp	$_211

$_224:
	leave
	pop	rbx
	pop	rdi
	ret

$_225:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	xor	ebx, ebx
	mov	rdi, qword ptr [rsi+0x58]
	movzx	eax, word ptr [rsi+0xE]
	jmp	$_229

$_226:	cmp	dword ptr [rsi+0x38], 0
	je	$_263
	cmp	dword ptr [rbp+0x28], 2
	je	$_263
	jmp	$_230

$_227:	cmp	dword ptr [rsi+0x38], 0
	je	$_263
	cmp	dword ptr [rbp+0x28], 0
	je	$_263
	cmp	dword ptr [rbp+0x28], 2
	je	$_263
	jmp	$_230

$_228:	jmp	$_263

	jmp	$_230

$_229:	cmp	eax, 1582
	jz	$_226
	cmp	eax, 1583
	jz	$_226
	cmp	eax, 1589
	jz	$_226
	cmp	eax, 1590
	jz	$_226
	cmp	eax, 1584
	jz	$_227
	cmp	eax, 1585
	jz	$_227
	cmp	eax, 1586
	jz	$_227
	cmp	eax, 1587
	jz	$_227
	cmp	eax, 1588
	jz	$_227
	cmp	eax, 744
	jz	$_228
	cmp	eax, 745
	jz	$_228
$_230:	mov	al, byte ptr [rdi+0x2]
	and	eax, 0x07
	cmp	eax, 2
	je	$_263
	cmp	eax, 3
	je	$_263
	mov	eax, dword ptr [rbp+0x20]
	jmp	$_258

$_231:	mov	ebx, 1
	jmp	$_259

$_232:	mov	ebx, 2
	jmp	$_259

$_233:	mov	ebx, 4
	jmp	$_259

$_234:	mov	ebx, 6
	jmp	$_259

$_235:	mov	ebx, 8
	jmp	$_259

$_236:	mov	al, byte ptr [rsi+0x61]
	and	eax, 0xC0
	jmp	$_256

$_237:	mov	ebx, 1
	jmp	$_257

$_238:	cmp	byte ptr [rsi+0x63], 0
	jnz	$_239
	cmp	byte ptr [rsi+0x9], 0
	jz	$_240
$_239:	cmp	byte ptr [rsi+0x63], 1
	jnz	$_242
	cmp	byte ptr [rsi+0x9], 0
	jz	$_242
$_240:	mov	al, byte ptr [rsi+0x61]
	and	al, 0x07
	cmp	al, 6
	jnz	$_241
	mov	ebx, 2
$_241:	jmp	$_251

$_242:	mov	al, byte ptr [rdi+0x6]
	and	al, 0xFFFFFFFC
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_243
	cmp	al, -96
	jnz	$_243
	cmp	byte ptr [rdi+0x1], 0
	jnz	$_243
	mov	ebx, 8
	jmp	$_251

$_243:	mov	al, byte ptr [rsi+0x61]
	and	eax, 0x07
	jmp	$_250

$_244:	mov	al, byte ptr [rsi+0x62]
	and	al, 0x07
	cmp	al, 5
	jnz	$_251
$_245:	mov	ebx, 4
	imul	ecx, dword ptr [rbp+0x28], 24
	mov	eax, dword ptr [rsi+rcx+0x20]
	mov	edx, dword ptr [rsi+rcx+0x24]
	xor	ecx, ecx
	test	edx, edx
	jnz	$_246
	cmp	eax, 2147483648
	jc	$_248
$_246:	inc	ecx
	cmp	edx, -1
	jc	$_248
	cmp	edx, -1
	jnz	$_247
	cmp	eax, 2147483648
	jc	$_248
$_247:	xor	ecx, ecx
$_248:	cmp	byte ptr [rsi+0x63], 2
	jnz	$_249
	test	ecx, ecx
	jz	$_249
	mov	ecx, 2070
	call	asmerr@PLT
$_249:	jmp	$_251

$_250:	cmp	eax, 4
	jz	$_244
	cmp	eax, 5
	jz	$_245
$_251:	jmp	$_257

$_252:	mov	ebx, 4
	cmp	byte ptr [rsi+0x63], 0
	jnz	$_253
	cmp	byte ptr [rsi+0x9], 0
	jz	$_254
$_253:	cmp	byte ptr [rsi+0x63], 1
	jnz	$_255
	cmp	byte ptr [rsi+0x9], 0
	jz	$_255
$_254:	mov	ebx, 2
$_255:	jmp	$_257

$_256:	cmp	eax, 64
	je	$_237
	cmp	eax, 0
	je	$_238
	cmp	eax, 128
	jz	$_252
$_257:	jmp	$_259

$_258:	test	eax, 0x10000
	jne	$_231
	test	eax, 0x20000
	jne	$_232
	test	eax, 0x40000
	jne	$_233
	test	eax, 0x40000000
	jne	$_234
	test	eax, 0x80000
	jne	$_235
	test	eax, 0x607F00
	jne	$_236
$_259:	mov	edi, ebx
	imul	ebx, dword ptr [rbp+0x28], 24
	test	edi, edi
	je	$_263
	cmp	qword ptr [rsi+rbx+0x18], 0
	je	$_262
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_261
	mov	eax, 1
	mov	rdx, qword ptr [rsi+rbx+0x18]
	mov	cl, byte ptr [rdx+0x18]
	shl	eax, cl
	mov	rcx, qword ptr [ModuleInfo+0x1A8+rip]
	movzx	ecx, word ptr [rcx+0x8]
	test	ecx, eax
	jz	$_261
	mov	rcx, qword ptr [ModuleInfo+0x1A8+rip]
	lea	rax, [rcx+0xA]
	lea	rcx, [szNull+rip]
	cmp	qword ptr [rdx+0x30], 0
	jz	$_260
	mov	rcx, qword ptr [rdx+0x30]
	mov	rcx, qword ptr [rcx+0x8]
$_260:	mov	r8, rcx
	mov	rdx, rax
	mov	ecx, 3001
	call	asmerr@PLT
$_261:	cmp	dword ptr [write_to_file+rip], 0
	jz	$_262
	call	GetCurrOffset@PLT
	mov	rdx, qword ptr [rsi+rbx+0x18]
	mov	dword ptr [rdx+0x14], eax
	mov	r8, rdx
	mov	edx, edi
	lea	rcx, [rsi+rbx+0x20]
	call	OutputBytes@PLT
	jmp	$_263

$_262:	xor	r8d, r8d
	mov	edx, edi
	lea	rcx, [rsi+rbx+0x20]
	call	OutputBytes@PLT
$_263:	leave
	pop	rbx
	pop	rdi
	ret

$_264:
	push	rdi
	push	rbx
	mov	rdi, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rdi]
	imul	ebx, eax, 12
	lea	rcx, [opnd_clstab+rip]
	cmp	byte ptr [rcx+rbx+0x8], 0
	jz	$_265
	cmp	byte ptr [rcx+rbx+0x8], 5
	jnz	$_267
$_265:	cmp	dword ptr [rsi+0x40], 0
	jz	$_266
	mov	rax, -1
	jmp	$_282

$_266:	xor	eax, eax
	jmp	$_282

$_267:	movzx	eax, byte ptr [rcx+rbx+0x8]
	jmp	$_280

$_268:	cmp	dword ptr [rsi+0x40], 8388609
	jnz	$_269
	xor	eax, eax
	jmp	$_282

$_269:	jmp	$_281

$_270:	test	byte ptr [rsi+0x42], 0x07
	jz	$_273
	cmp	dword ptr [rsi+0x50], -128
	jl	$_273
	cmp	word ptr [rsi+0xE], 698
	jnz	$_271
	cmp	dword ptr [rsi+0x50], 128
	jl	$_272
$_271:
	cmp	word ptr [rsi+0xE], 698
	jz	$_273
	cmp	dword ptr [rsi+0x50], 256
	jge	$_273
$_272:	mov	dword ptr [rsi+0x40], 65536
	xor	eax, eax
	jmp	$_282

$_273:	jmp	$_281

$_274:	test	byte ptr [rsi+0x42], 0x07
	je	$_281
	xor	eax, eax
	jmp	$_282

$_275:
	cmp	word ptr [rsi+0xE], 1301
	jc	$_278
	test	dword ptr [rsi+0x40], 0x100070
	jz	$_276
	xor	eax, eax
	jmp	$_282

$_276:	movzx	eax, word ptr [rsi+0xE]
	jmp	$_277
$C018A:
$C018B:
$C018C:
$C018D:
$C018E:
$C018F:
$C0190:
$C0191:
$C0192:
$C0193: xor	eax, eax
	jmp	$_282
$_277:	cmp	eax, 1582
	jl	$C0194
	cmp	eax, 1591
	jg	$C0194
	push	rax
	lea	r11, [$C0194+rip]
	movzx	eax, byte ptr [r11+rax-1582+($C0195-$C0194)]
	sub	r11, rax
	pop	rax
	jmp	r11
$C0195:
	.byte $C0194-$C018A
	.byte $C0194-$C018B
	.byte $C0194-$C018E
	.byte $C0194-$C018F
	.byte $C0194-$C0190
	.byte $C0194-$C0191
	.byte $C0194-$C0192
	.byte $C0194-$C018C
	.byte $C0194-$C018D
	.byte $C0194-$C0193
$C0194:
	jmp	$_279

$_278:	cmp	dword ptr [rsi+0x40], 16
	jnz	$_279
	cmp	dword ptr [rsi+0x50], 0
	jnz	$_279
	xor	eax, eax
	jmp	$_282

$_279:	jmp	$_281

$_280:	cmp	eax, 1
	je	$_268
	cmp	eax, 2
	je	$_270
	cmp	eax, 4
	je	$_274
	cmp	eax, 3
	je	$_275
$_281:	mov	rax, -1
$_282:	pop	rbx
	pop	rdi
	ret

$_283:
	push	rdi
	push	rbx
	sub	rsp, 40
	mov	rdi, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rdi]
	imul	ebx, eax, 12
	lea	rcx, [opnd_clstab+rip]
	add	rbx, rcx
	cmp	byte ptr [rbx+0x8], 2
	jnz	$_284
	mov	edx, 2
	mov	ecx, 65536
	call	$_225
	jmp	$_287

$_284:	cmp	byte ptr [rbx+0x8], 4
	jnz	$_285
	mov	edx, 2
	mov	ecx, dword ptr [rsi+0x40]
	call	$_225
	jmp	$_287

$_285:	cmp	byte ptr [rbx+0x8], 5
	jnz	$_286
	movzx	eax, word ptr [rsi+0xE]
	sub	eax, 961
	mov	ecx, 8
	xor	edx, edx
	div	ecx
	mov	dword ptr [rsi+0x50], edx
	mov	qword ptr [rsi+0x48], 0
	mov	edx, 2
	mov	ecx, 65536
	call	$_225
	jmp	$_287

$_286:
	cmp	word ptr [rsi+0xE], 1301
	jc	$_287
	cmp	byte ptr [rbx+0x8], 3
	jnz	$_287
	mov	eax, dword ptr [rsi+0x50]
	shl	eax, 4
	mov	dword ptr [rsi+0x50], eax
	mov	edx, 2
	mov	ecx, 65536
	call	$_225
$_287:	add	rsp, 40
	pop	rbx
	pop	rdi
	ret

$_288:
	mov	qword ptr [rsp+0x8], rcx
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	rdi, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rdi]
	imul	ebx, eax, 12
	lea	rcx, [opnd_clstab+rip]
	mov	eax, dword ptr [rbx+rcx]
	mov	dword ptr [rbp-0x4], eax
	mov	ebx, dword ptr [rsi+0x28]
	movzx	eax, word ptr [rsi+0xE]
	sub	eax, 1301
	lea	rcx, [vex_flags+rip]
	cmp	word ptr [rsi+0xE], 1301
	jc	$_297
	test	byte ptr [rcx+rax], 0x01
	je	$_297
	test	dword ptr [rsi+0x10], 0x106060
	jz	$_295
	test	ebx, 0x40
	jz	$_289
	or	ebx, 0x20
	jmp	$_290

$_289:	test	ebx, 0x4000
	jz	$_290
	or	ebx, 0x2000
$_290:	test	ebx, 0x20
	jz	$_291
	or	ebx, 0x10
	jmp	$_294

$_291:	test	ebx, 0x2000
	jz	$_292
	or	ebx, 0x1000
	jmp	$_294

$_292:	test	ebx, 0x1000
	jz	$_293
	or	ebx, 0x800
	jmp	$_294

$_293:	test	ebx, 0x10
	jz	$_294
	test	byte ptr [rcx+rax], 0x20
	jnz	$_294
	mov	ecx, 2085
	call	asmerr@PLT
	jmp	$_344

$_294:	jmp	$_296

$_295:	cmp	dword ptr [rsi+0x10], 4202240
	jnz	$_296
	test	ebx, 0x60
	jz	$_296
	or	ebx, 0x10
$_296:	jmp	$_300

$_297:	cmp	dword ptr [rbp+0x20], 16
	jnz	$_300
	cmp	ebx, 2048
	jnz	$_300
	mov	rax, qword ptr [CurrProc+rip]
	test	rax, rax
	jz	$_299
	cmp	byte ptr [rax+0x1A], 8
	jnz	$_298
	or	ebx, 0x1000
$_298:	jmp	$_300

$_299:	cmp	byte ptr [ModuleInfo+0x1B6+rip], 8
	jnz	$_300
	or	ebx, 0x1000
$_300:	mov	rdi, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rdi]
	imul	eax, eax, 12
	lea	rcx, [opnd_clstab+rip]
	mov	eax, dword ptr [rcx+rax+0x4]
	jmp	$_341

$_301:	test	eax, ebx
	je	$_315
	test	byte ptr [rbp+0x20], 0x01
	jz	$_303
	mov	byte ptr [rsi+0xA], 0
	mov	ebx, 65536
	mov	rax, qword ptr [rsi+0x30]
	test	rax, rax
	jz	$_302
	cmp	byte ptr [rax+0x18], 11
	jz	$_302
	mov	byte ptr [rax+0x18], 4
$_302:	jmp	$_314

$_303:	test	byte ptr [rbp+0x20], 0x02
	jz	$_304
	mov	ebx, 131072
	jmp	$_314

$_304:	test	byte ptr [rbp+0x20], 0x0C
	jz	$_306
	mov	byte ptr [rsi+0xA], 1
	cmp	byte ptr [rsi+0x63], 0
	jz	$_305
	mov	byte ptr [rsi+0xA], 0
$_305:	mov	ebx, 262144
	jmp	$_314

$_306:	test	dword ptr [rbp+0x20], 0x401F00
	jz	$_314
	mov	rdx, rsi
	mov	ecx, dword ptr [rbp+0x20]
	call	OperandSize@PLT
	jmp	$_313

$_307:	mov	ebx, 65536
	mov	byte ptr [rsi+0xA], 0
	jmp	$_314

$_308:	mov	ebx, 131072
	mov	byte ptr [rsi+0xA], 0
	cmp	byte ptr [rsi+0x63], 0
	jz	$_309
	mov	byte ptr [rsi+0xA], 1
$_309:	jmp	$_314

$_310:	mov	ebx, 262144
	mov	byte ptr [rsi+0xA], 1
	cmp	byte ptr [rsi+0x63], 0
	jz	$_311
	mov	byte ptr [rsi+0xA], 0
$_311:	jmp	$_314

$_312:	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_314

$_313:	cmp	rax, 1
	jz	$_307
	cmp	rax, 2
	jz	$_308
	cmp	rax, 8
	jz	$_310
	cmp	rax, 4
	jz	$_310
	jmp	$_312

$_314:	call	$_001
	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x20]
	call	$_225
	mov	edx, 1
	mov	ecx, ebx
	call	$_225
	xor	eax, eax
	jmp	$_344

$_315:	jmp	$_342

$_316:	test	eax, ebx
	jz	$_320
	test	byte ptr [rsi+0x66], 0x08
	jz	$_317
	cmp	ebx, 65536
	jne	$_342
$_317:	cmp	dword ptr [rsi+0x38], 255
	jg	$_320
	cmp	dword ptr [rsi+0x38], -128
	jl	$_320
	mov	rax, qword ptr [rsi+0x30]
	test	rax, rax
	jz	$_319
	cmp	byte ptr [rax+0x18], 5
	jz	$_318
	cmp	byte ptr [rax+0x18], 6
	jnz	$_319
$_318:	mov	byte ptr [rax+0x18], 4
$_319:	call	$_001
	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x20]
	call	$_225
	mov	edx, 1
	mov	ecx, 65536
	call	$_225
	xor	eax, eax
	jmp	$_344

$_320:	jmp	$_342

$_321:	mov	edx, eax
	movzx	eax, word ptr [rsi+0xE]
	cmp	byte ptr [ModuleInfo+0x1E2+rip], 0
	jz	$_322
	cmp	eax, 585
	je	$_342
	cmp	eax, 582
	je	$_342
	cmp	eax, 587
	je	$_342
$_322:	mov	rax, qword ptr [rsi+0x30]
	test	rax, rax
	jz	$_323
	mov	rcx, qword ptr [rax+0x30]
	cmp	byte ptr [rcx+0x18], 0
	jne	$_342
$_323:	test	byte ptr [rsi+0x66], 0x08
	jnz	$_325
	movsx	eax, byte ptr [rsi+0x38]
	movsx	ecx, word ptr [rsi+0x38]
	test	dword ptr [rbp+0x20], 0x202
	jz	$_324
	cmp	eax, ecx
	jnz	$_324
	or	edx, 0x20000
	jmp	$_325

$_324:	test	dword ptr [rbp+0x20], 0xC0C
	jz	$_325
	cmp	eax, dword ptr [rsi+0x38]
	jnz	$_325
	or	edx, 0x40000
$_325:	test	edx, ebx
	jz	$_326
	call	$_001
	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x20]
	call	$_225
	mov	edx, 1
	mov	ecx, 65536
	call	$_225
	xor	eax, eax
	jmp	$_344

$_326:	jmp	$_342

$_327:	test	eax, ebx
	jz	$_328
	cmp	dword ptr [rsi+0x38], 1
	jnz	$_328
	call	$_001
	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x20]
	call	$_225
	xor	eax, eax
	jmp	$_344

$_328:	jmp	$_342

$_329:	jmp	$_333

$_330:	test	ebx, 0xC
	jnz	$_331
	or	ebx, 0x0C
$_331:	jmp	$_334

$_332:	call	$_001
	mov	edx, 2
	mov	ecx, 8847360
	call	$_225
	xor	eax, eax
	jmp	$_344

	jmp	$_334

$_333:
	cmp	word ptr [rsi+0xE], 1582
	jz	$_330
	cmp	word ptr [rsi+0xE], 1583
	jz	$_330
	cmp	word ptr [rsi+0xE], 1589
	jz	$_330
	cmp	word ptr [rsi+0xE], 1590
	jz	$_330
	cmp	word ptr [rsi+0xE], 1591
	jz	$_332
$_334:	test	eax, ebx
	jz	$_340
	call	$_264
	cmp	eax, -1
	je	$_342
	call	$_001
	test	dword ptr [rbp+0x20], 0x406F7F00
	jz	$_335
	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x20]
	call	$_225
$_335:	test	ebx, 0x406F7F00
	jz	$_336
	mov	edx, 1
	mov	ecx, ebx
	call	$_225
$_336:	movzx	eax, byte ptr [rdi]
	imul	eax, eax, 12
	lea	rcx, [opnd_clstab+rip]
	cmp	byte ptr [rcx+rax+0x8], 0
	jz	$_337
	test	byte ptr [rdi+0x3], 0x08
	jnz	$_337
	call	$_283
$_337:	cmp	byte ptr [rdi+0x1], 18
	jnz	$_339
	movzx	eax, byte ptr [rdi+0x6]
	test	byte ptr [rsi+0x66], 0x01
	jz	$_338
	or	eax, 0x01
$_338:	mov	ecx, eax
	call	OutputByte@PLT
$_339:	xor	eax, eax
	jmp	$_344

$_340:	jmp	$_342

$_341:	cmp	eax, 458752
	je	$_301
	cmp	eax, 8847360
	je	$_316
	cmp	eax, 65536
	je	$_321
	cmp	eax, 2162688
	je	$_327
	cmp	eax, 12
	je	$_329
	jmp	$_334

$_342:	add	qword ptr [rsi+0x58], 8
	mov	rdi, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rdi]
	imul	eax, eax, 12
	lea	rcx, [opnd_clstab+rip]
	mov	eax, dword ptr [rcx+rax]
	cmp	eax, dword ptr [rbp-0x4]
	jnz	$_343
	test	byte ptr [rdi+0x2], 0x08
	je	$_300
$_343:	sub	qword ptr [rsi+0x58], 8
	mov	rax, -1
$_344:	leave
	pop	rbx
	pop	rdi
	ret

$_345:
	mov	qword ptr [rsp+0x8], rcx
	push	rdi
	push	rbp
	mov	rbp, rsp
	imul	eax, dword ptr [rbp+0x18], 24
	mov	rdi, qword ptr [rsi+rax+0x18]
	test	rdi, rdi
	jz	$_346
	cmp	byte ptr [rdi+0x18], 3
	jnz	$_346
	call	GetCurrOffset@PLT
	sub	eax, dword ptr [rdi+0x14]
	mov	byte ptr [rdi+0x1A], al
$_346:	leave
	pop	rdi
	ret

$_347:
	mov	qword ptr [rsp+0x8], rcx
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	dword ptr [rsi+0x28], 0
	jne	$_353
	mov	rdi, qword ptr [rsi+0x58]
	movzx	eax, byte ptr [rdi]
	imul	ecx, eax, 12
	lea	rdx, [opnd_clstab+rip]
	cmp	dword ptr [rdx+rcx+0x4], 0
	jz	$_348
	mov	rax, -1
	jmp	$_356

$_348:	cmp	dword ptr [rbp+0x20], 4202240
	jnz	$_351
	add	rdi, 8
	movzx	eax, byte ptr [rdi]
	imul	eax, eax, 12
	test	dword ptr [rdx+rax], 0x401F00
	jz	$_351
	test	byte ptr [rdi+0x2], 0x08
	jnz	$_351
	xor	ecx, ecx
	xor	edx, edx
	mov	rax, qword ptr [rsi+0x18]
	test	rax, rax
	jz	$_349
	mov	rdx, qword ptr [rax+0x30]
	test	rdx, rdx
	jz	$_349
	mov	cl, byte ptr [rdx+0x18]
$_349:	test	byte ptr [rsi+0x66], 0x40
	jnz	$_351
	test	eax, eax
	jz	$_350
	test	rdx, rdx
	jz	$_350
	test	ecx, ecx
	jz	$_351
$_350:	mov	ecx, 2023
	call	asmerr@PLT
$_351:	call	$_001
	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x20]
	call	$_225
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_352
	xor	ecx, ecx
	call	$_345
$_352:	xor	eax, eax
	jmp	$_356

$_353:	mov	ecx, dword ptr [rbp+0x20]
	call	$_288
	test	eax, eax
	jnz	$_355
	cmp	byte ptr [rsi+0x63], 2
	jnz	$_354
	xor	ecx, ecx
	call	$_345
	mov	ecx, 1
	call	$_345
$_354:	xor	eax, eax
	jmp	$_356

$_355:	mov	rax, -1
$_356:	leave
	pop	rbx
	pop	rdi
	ret

codegen:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	al, byte ptr [rsi+0xB]
	mov	byte ptr [rbp-0x1], al
	mov	rdi, qword ptr [rsi+0x58]
	mov	ax, word ptr [rdi+0x4]
	and	eax, 0x08
	mov	ecx, dword ptr [ModuleInfo+0x1C0+rip]
	and	ecx, 0x08
	cmp	eax, ecx
	jbe	$_357
	mov	ecx, 2085
	call	asmerr@PLT
	jmp	$_378

$_357:	mov	ebx, dword ptr [rsi+0x10]
	test	ebx, 0x70000
	jz	$_359
	cmp	ebx, 65536
	jnz	$_358
	mov	ebx, 458752
	jmp	$_359

$_358:	cmp	ebx, 131072
	jnz	$_359
	mov	ebx, 393216
$_359:	movzx	eax, word ptr [rsi+0xE]
	sub	eax, 1301
	lea	rcx, [vex_flags+rip]
	cmp	word ptr [rsi+0xE], 1301
	jc	$_364
	test	byte ptr [rcx+rax], 0x01
	jz	$_364
	test	ebx, 0x6060
	jz	$_364
	test	byte ptr [rsi+0x28], 0x10
	jz	$_360
	test	byte ptr [rcx+rax], 0x20
	jnz	$_360
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_378

$_360:	test	ebx, 0x40
	jz	$_361
	or	ebx, 0x20
	jmp	$_362

$_361:	test	ebx, 0x4000
	jz	$_362
	or	ebx, 0x2000
$_362:	test	ebx, 0x20
	jz	$_363
	or	ebx, 0x10
	jmp	$_364

$_363:	or	ebx, 0x1000
$_364:	movzx	eax, byte ptr [rdi]
	imul	eax, eax, 12
	lea	rcx, [opnd_clstab+rip]
	mov	ecx, dword ptr [rcx+rax]
	test	ecx, ecx
	jnz	$_366
	test	ebx, ebx
	jnz	$_366
	call	$_001
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_365
	xor	r8d, r8d
	mov	edx, dword ptr [rbp+0x30]
	mov	ecx, 1
	call	LstWrite@PLT
$_365:	xor	eax, eax
	jmp	$_378

$_366:	test	ecx, ebx
	je	$_377
	mov	eax, 4294967295
	jmp	$_374

$_367:	call	$_347
	jmp	$_375

$_368:	cmp	dword ptr [rsi+0x20], 255
	jg	$_369
	cmp	dword ptr [rsi+0x20], -128
	jl	$_369
	mov	ecx, 65536
	call	$_347
$_369:	jmp	$_375

$_370:	cmp	dword ptr [rsi+0x20], 3
	jnz	$_371
	xor	ecx, ecx
	call	$_347
$_371:	jmp	$_375

$_372:	cmp	byte ptr [rbp-0x1], 0
	jz	$_373
	cmp	byte ptr [rdi+0x3], 0
	jz	$_375
$_373:	mov	ecx, dword ptr [rsi+0x10]
	call	$_347
	jmp	$_375

$_374:	cmp	ecx, 262144
	jz	$_367
	cmp	ecx, 131072
	jz	$_367
	cmp	ecx, 8847360
	jz	$_368
	cmp	ecx, 4259840
	jz	$_370
	jmp	$_372

$_375:	test	eax, eax
	jnz	$_377
	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_376
	xor	r8d, r8d
	mov	edx, dword ptr [rbp+0x30]
	mov	ecx, 1
	call	LstWrite@PLT
$_376:	xor	eax, eax
	jmp	$_378

$_377:	add	qword ptr [rsi+0x58], 8
	mov	rdi, qword ptr [rsi+0x58]
	test	byte ptr [rdi+0x2], 0x08
	je	$_364
	mov	ecx, 2070
	call	asmerr@PLT
$_378:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

szNull:
	.byte  0x3C, 0x4E, 0x55, 0x4C, 0x4C, 0x3E, 0x00

sr_prefix:
	.byte  0x26, 0x2E, 0x36, 0x3E, 0x64, 0x65


.att_syntax prefix
