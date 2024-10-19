
.intel_syntax noprefix

.global EvalOperand
.global EmitConstError
.global ExprEvalInit

.extern FindDotSymbol
.extern StackAdj
.extern EvalOperator
.extern atofloat
.extern _atoow
.extern quad_resize
.extern __rem64_
.extern __div64_
.extern __sqrtq
.extern __cmpq
.extern __subq
.extern __addq
.extern __divq
.extern __mulq
.extern __saro
.extern __shro
.extern __shlo
.extern __divo
.extern __mulo
.extern GetAnonymousLabel
.extern SearchNameInStruct
.extern CreateTypeSymbol
.extern CurrStruct
.extern GetStdAssumeEx_
.extern CurrProc
.extern DefineFlatGroup
.extern GetSymOfssize
.extern SetSymSegOfs
.extern GetResWName
.extern sym_add_table
.extern SizeFromRegister
.extern MemtypeFromSize
.extern SizeFromMemtype
.extern SpecialTable
.extern SymTables
.extern tstrlen
.extern tmemset
.extern tstrupr
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind
.extern SymLookup
.extern SymAlloc


.SECTION .text
	.ALIGN	16

noasmerr:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	mov	rax, -1
	leave
	ret

$_001:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	test	byte ptr [rcx+0x43], 0x10
	jz	$_002
	xor	eax, eax
	jmp	$_005

$_002:	cmp	dword ptr [rcx+0x3C], 3
	jz	$_003
	cmp	dword ptr [rdx+0x3C], 3
	jnz	$_004
$_003:	mov	ecx, 2050
	call	qword ptr [fnasmerr+rip]
	jmp	$_005

$_004:	mov	ecx, 2026
	call	qword ptr [fnasmerr+rip]
$_005:	leave
	ret

$_006:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rsi, rdx
	mov	rdi, rcx
	mov	rax, rcx
	mov	ecx, 24
	rep movsd
	mov	rcx, rax
	leave
	pop	rdi
	pop	rsi
	ret

$_007:
	mov	qword ptr [rsp+0x18], r8
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, qword ptr [rbp+0x28]
	test	byte ptr [rcx+0x43], 0x10
	jnz	$_008
	mov	rcx, rdx
	call	tstrupr@PLT
	mov	r8, rbx
	mov	rdx, rax
	mov	ecx, 3018
	call	qword ptr [fnasmerr+rip]
$_008:	mov	rax, -1
	leave
	pop	rbx
	ret

$_009:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	movzx	eax, byte ptr [rcx+0x19]
	cmp	eax, 195
	jnz	$_010
	mov	eax, 129
	cmp	byte ptr [rcx+0x1C], 0
	jz	$_010
	mov	eax, 130
$_010:	movzx	edx, byte ptr [rcx+0x38]
	mov	r8, qword ptr [rcx+0x20]
	movzx	ecx, al
	call	SizeFromMemtype@PLT
	leave
	ret

$_011:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	xor	eax, eax
	xor	edx, edx
	mov	rbx, qword ptr [rcx+0x68]
	mov	rbx, qword ptr [rbx]
$_012:	test	rbx, rbx
	jz	$_017
	mov	ecx, dword ptr [rbx+0x28]
	mov	edi, dword ptr [rbx+0x50]
	add	edi, ecx
$_013:	cmp	ecx, edi
	jnc	$_016
	mov	esi, 1
	cmp	ecx, 32
	jnc	$_014
	shl	esi, cl
	or	eax, esi
	jmp	$_015

$_014:	sub	ecx, 32
	shl	esi, cl
	or	edx, esi
	add	ecx, 32
$_015:	inc	ecx
	jmp	$_013

$_016:	mov	rbx, qword ptr [rbx+0x68]
	jmp	$_012

$_017:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_018:
	cmp	byte ptr [rcx+0x40], -64
	jnz	$_020
	mov	eax, dword ptr [rcx+0x38]
	cmp	eax, 249
	jz	$_019
	cmp	eax, 239
	jz	$_019
	cmp	eax, 251
	jz	$_019
	cmp	eax, 246
	jnz	$_020
$_019:	mov	eax, 1
	jmp	$_021

$_020:	xor	eax, eax
$_021:	ret

$_022:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [Options+0xC6+rip], 0
	jz	$_023
	call	$_001
	mov	ecx, eax
	mov	eax, 1
	jmp	$_025

$_023:	mov	dword ptr [rdx+0x3C], 0
	mov	qword ptr [rdx+0x10], 0
	cmp	dword ptr [rbp+0x20], 16
	jz	$_024
	mov	rcx, rdx
	mov	edx, dword ptr [rbp+0x20]
	call	quad_resize@PLT
$_024:	xor	eax, eax
$_025:	leave
	ret

$_026:
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rdx
	mov	rdi, r8
	mov	eax, ecx
	jmp	$_179
$C001F:
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_027
	cmp	dword ptr [rdi+0x38], 252
	jz	$_027
	mov	dword ptr [rsi+0x38], 242
	mov	byte ptr [rsi+0x40], -64
$_027:	mov	eax, dword ptr [rsi]
	and	eax, 0xFF
	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], 0
	xor	eax, eax
	jmp	$_180
$C0022:
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_028
	cmp	dword ptr [rdi+0x38], 252
	jz	$_028
	mov	dword ptr [rsi+0x38], 235
	mov	byte ptr [rsi+0x40], -64
$_028:	mov	eax, dword ptr [rsi]
	shr	eax, 8
	and	eax, 0xFF
	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], 0
	xor	eax, eax
	jmp	$_180
$C0024:
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_029
	cmp	dword ptr [rdi+0x38], 252
	jz	$_029
	mov	dword ptr [rsi+0x38], 245
	mov	byte ptr [rsi+0x40], -64
$_029:	mov	eax, dword ptr [rsi]
	and	eax, 0xFFFF
	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], 0
	xor	eax, eax
	jmp	$_180
$C0026:
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_030
	cmp	dword ptr [rdi+0x38], 252
	jz	$_030
	mov	dword ptr [rsi+0x38], 238
	mov	byte ptr [rsi+0x40], -64
$_030:	mov	eax, dword ptr [rsi]
	shr	eax, 16
	and	eax, 0xFFFF
	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], 0
	xor	eax, eax
	jmp	$_180
$C0028:
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_031
	mov	r8d, 8
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_022
	test	rax, rax
	jz	$_031
	mov	eax, ecx
	jmp	$_180

$_031:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	byte ptr [rsi+0x40], 3
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_032
	cmp	dword ptr [rdi+0x38], 252
	jz	$_032
	mov	dword ptr [rsi+0x38], 244
	mov	byte ptr [rsi+0x40], -64
$_032:	mov	dword ptr [rsi+0x4], 0
	xor	eax, eax
	jmp	$_180
$C002C:
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_033
	mov	r8d, 8
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_022
	test	rax, rax
	jz	$_033
	mov	eax, ecx
	jmp	$_180
$_033:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	byte ptr [rsi+0x40], 3
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_034
	cmp	dword ptr [rdi+0x38], 252
	jz	$_034
	mov	dword ptr [rsi+0x38], 237
	mov	byte ptr [rsi+0x40], -64
$_034:	mov	eax, dword ptr [rsi+0x4]
	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], 0
	xor	eax, eax
	jmp	$_180
$C0030:
$C0031:
$C0032:
$C0033:
	cmp	dword ptr [rbp+0x48], 249
	jnz	$_035
	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_035
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	xor	eax, eax
	jmp	$_180
$_035:	mov	rbx, qword ptr [rbp+0x40]
	test	rbx, rbx
	jz	$_036
	cmp	byte ptr [rbx+0x18], 4
	jz	$_037
$_036:	cmp	dword ptr [rdi+0x38], 252
	jnz	$_038
$_037:	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x48]
	call	GetResWName@PLT
	mov	r8, qword ptr [rbp+0x50]
	mov	rdx, rax
	mov	rcx, rdi
	call	$_007
	jmp	$_180
$_038:	test	byte ptr [rdi+0x43], 0x08
	jz	$_039
	mov	dword ptr [rdi], 0
$_039:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsi+0x38], eax
	test	byte ptr [rdi+0x43], 0x01
	jz	$_040
	xor	edx, edx
	mov	ecx, dword ptr [rbp+0x48]
	call	GetResWName@PLT
	mov	r8, qword ptr [rbp+0x50]
	mov	rdx, rax
	mov	rcx, rdi
	call	$_007
	jmp	$_180
$_040:	mov	byte ptr [rsi+0x40], -64
	xor	eax, eax
	jmp	$_180
$C003B:
	mov	rbx, qword ptr [rdi+0x50]
	test	rbx, rbx
	jz	$_041
	cmp	byte ptr [rbx+0x18], 5
	jz	$_041
	test	byte ptr [rdi+0x43], 0x04
	jz	$_042
$_041:	mov	ecx, 2094
	call	qword ptr [fnasmerr+rip]
	jmp	$_180
$_042:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsi+0x38], eax
	cmp	qword ptr [rsi+0x58], 0
	jz	$_043
	mov	dword ptr [rsi], 0
$_043:	mov	byte ptr [rsi+0x40], -64
	xor	eax, eax
	jmp	$_180
$C0041:
$C0042:
	xor	eax, eax
	mov	dword ptr [rsi+0x3C], 0
	mov	qword ptr [rsi+0x50], rax
	mov	dword ptr [rsi], eax
	mov	byte ptr [rsi+0x40], -64
	and	byte ptr [rsi+0x43], 0xFFFFFFEF
	cmp	dword ptr [rdi+0x3C], -2
	jnz	$_044
	jmp	$_180
$_044:	cmp	dword ptr [rdi+0x3C], 0
	jz	$_045
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_046
$_045:	cmp	dword ptr [rbp+0x48], 250
	jnz	$_046
	test	byte ptr [rdi+0x43], 0x20
	jz	$_046
	or	byte ptr [rsi+0x1], 0xFFFFFF80
$_046:	mov	rbx, qword ptr [rdi+0x50]
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_051
	mov	al, byte ptr [rdi+0x40]
	test	al, 0x40
	jz	$_047
	cmp	dword ptr [rbp+0x48], 250
	jnz	$_047
	or	byte ptr [rsi+0x1], 0xFFFFFF80
$_047:	and	al, 0xFFFFFFC0
	test	rbx, rbx
	jz	$_048
	cmp	byte ptr [rbx+0x18], 5
	jz	$_048
	cmp	eax, 128
	jnz	$_048
	or	byte ptr [rsi], 0x01
$_048:	mov	rcx, rdi
	call	$_018
	test	eax, eax
	jz	$_049
	test	rbx, rbx
	jz	$_049
	mov	al, byte ptr [rbx+0x19]
	and	eax, 0xC0
	cmp	eax, 128
	jnz	$_049
	or	byte ptr [rsi], 0x01
$_049:	test	rbx, rbx
	jz	$_051
	cmp	byte ptr [rbx+0x19], -60
	jz	$_050
	test	byte ptr [rdi+0x40], 0xFFFFFF80
	jz	$_050
	cmp	byte ptr [rdi+0x40], -64
	jnz	$_051
	test	byte ptr [rbx+0x19], 0xFFFFFF80
	jnz	$_051
$_050:	or	byte ptr [rsi], 0x02
$_051:	cmp	dword ptr [rdi+0x3C], -1
	jz	$_052
	test	byte ptr [rdi+0x43], 0x01
	jz	$_052
	or	byte ptr [rsi], 0x02
$_052:	mov	rcx, rdi
	call	$_018
	mov	cl, byte ptr [rdi+0x40]
	and	ecx, 0xC0
	cmp	dword ptr [rdi+0x3C], 0
	jz	$_055
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_056
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_056
	cmp	byte ptr [rdi+0x40], -64
	jnz	$_053
	test	eax, eax
	jnz	$_054
$_053:	cmp	byte ptr [rdi+0x40], -64
	jz	$_054
	cmp	ecx, 128
	jnz	$_056
$_054:	cmp	byte ptr [rbx+0x18], 1
	jz	$_055
	cmp	byte ptr [rbx+0x18], 2
	jnz	$_056
$_055:	or	byte ptr [rsi], 0x04
$_056:	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_060
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_060
	cmp	byte ptr [rdi+0x40], -64
	jnz	$_057
	cmp	dword ptr [rdi+0x38], -2
	jz	$_058
$_057:	cmp	byte ptr [rdi+0x40], -60
	jz	$_058
	test	byte ptr [rdi+0x40], 0xFFFFFF80
	jz	$_058
	cmp	byte ptr [rdi+0x40], -61
	jnz	$_060
$_058:	test	rbx, rbx
	jz	$_059
	cmp	byte ptr [rbx+0x18], 1
	jz	$_059
	cmp	byte ptr [rbx+0x18], 2
	jnz	$_060
$_059:	or	byte ptr [rsi], 0x08
$_060:	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_061
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_061
	or	byte ptr [rsi], 0x10
	test	byte ptr [rdi+0x40], 0x40
	jz	$_061
	cmp	dword ptr [rbp+0x48], 250
	jnz	$_061
	or	byte ptr [rsi+0x1], 0xFFFFFF80
$_061:	cmp	dword ptr [rdi+0x3C], -1
	jz	$_063
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_063
	test	ebx, ebx
	jz	$_062
	test	byte ptr [rbx+0x14], 0x02
	jz	$_063
$_062:	or	byte ptr [rsi], 0x20
$_063:	mov	rax, qword ptr [rdi+0x20]
	test	rax, rax
	jnz	$_064
	mov	rax, qword ptr [rdi+0x18]
$_064:	test	rax, rax
	jz	$_065
	imul	eax, dword ptr [rax+0x4], 12
$_065:	lea	rcx, [SpecialTable+rip]
	test	rbx, rbx
	jz	$_066
	cmp	byte ptr [rbx+0x18], 5
	jz	$_067
$_066:	test	byte ptr [rdi+0x43], 0x01
	jz	$_068
	test	eax, eax
	jz	$_068
	test	byte ptr [rcx+rax+0x5], 0x01
	jz	$_068
$_067:	or	byte ptr [rsi], 0x40
$_068:	test	rbx, rbx
	jz	$_069
	cmp	byte ptr [rbx+0x18], 2
	jnz	$_069
	or	dword ptr [rsi], 0x80
$_069:	cmp	dword ptr [rbp+0x48], 250
	jnz	$_070
	test	rbx, rbx
	jz	$_070
	cmp	dword ptr [rdi+0x3C], -1
	jz	$_070
	movzx	eax, byte ptr [rbx+0x1A]
	shl	eax, 8
	or	dword ptr [rsi], eax
$_070:	xor	eax, eax
	jmp	$_180
$C006F:
$C0070:
$C0071:
	mov	eax, dword ptr [rbp+0x48]
	mov	rbx, qword ptr [rbp+0x40]
	mov	dword ptr [rsi+0x3C], 0
	test	rbx, rbx
	je	$_080
	jmp	$_077
$_071:	jmp	$_080
$_072:	mov	dword ptr [rsi+0x3C], 1
	mov	qword ptr [rsi+0x50], rbx
$_073:	jmp	$_080
$_074:	mov	ecx, 2143
	call	qword ptr [fnasmerr+rip]
	jmp	$_180
$_075:	jmp	$_080
$_076:	mov	ecx, 2143
	call	qword ptr [fnasmerr+rip]
	jmp	$_180
$_077:	cmp	byte ptr [rbx+0x18], 6
	jz	$_071
	cmp	byte ptr [rbx+0x18], 5
	jz	$_071
	cmp	byte ptr [rbx+0x18], 0
	jz	$_072
	cmp	byte ptr [rbx+0x18], 2
	jz	$_078
	cmp	byte ptr [rbx+0x18], 1
	jnz	$_079
$_078:	cmp	byte ptr [rbx+0x19], -64
	jz	$_079
	cmp	byte ptr [rbx+0x19], -126
	jz	$_079
	cmp	byte ptr [rbx+0x19], -127
	jnz	$_073
$_079:	cmp	byte ptr [rbx+0x18], 4
	jz	$_074
	cmp	byte ptr [rbx+0x18], 3
	jz	$_074
	cmp	eax, 254
	jz	$_075
	cmp	eax, 240
	jz	$_075
	jmp	$_076
$_080:	jmp	$_107

$_081:	test	byte ptr [rbx+0x15], 0x04
	jz	$_082
	mov	eax, dword ptr [rbx+0x40]
	mov	dword ptr [rsi], eax
	jmp	$_083

$_082:	mov	dword ptr [rsi], 1
$_083:	jmp	$_108

$_084:	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_085
	mov	rbx, qword ptr [rdi+0x58]
	mov	eax, dword ptr [rbx+0x58]
	mov	dword ptr [rsi], eax
	jmp	$_087

$_085:	cmp	byte ptr [rbx+0x18], 2
	jnz	$_086
	test	byte ptr [rbx+0x3B], 0x01
	jnz	$_086
	mov	dword ptr [rsi], 1
	jmp	$_087

$_086:	mov	eax, dword ptr [rbx+0x58]
	mov	dword ptr [rsi], eax
$_087:	jmp	$_108

$_088:	jmp	$_099

$_089:	mov	al, byte ptr [rdi+0x40]
	and	eax, 0xC0
	cmp	eax, 128
	jnz	$_090
	mov	eax, dword ptr [rdi]
	or	eax, 0xFF00
	mov	dword ptr [rsi], eax
	jmp	$_091

$_090:	mov	eax, dword ptr [rdi]
	mov	dword ptr [rsi], eax
$_091:	jmp	$_100

$_092:	mov	eax, dword ptr [rbx+0x38]
	mov	dword ptr [rsi], eax
	jmp	$_100

$_093:	mov	rcx, rbx
	call	$_009
	mov	dword ptr [rsi], eax
	jmp	$_100

$_094:	mov	rcx, rbx
	call	GetSymOfssize@PLT
	mov	ecx, eax
	mov	eax, 2
	shl	eax, cl
	or	eax, 0xFF00
	mov	dword ptr [rsi], eax
	jmp	$_100

$_095:	mov	rcx, rbx
	call	GetSymOfssize@PLT
	test	rax, rax
	jz	$_096
	mov	eax, 65286
	jmp	$_097

$_096:	mov	eax, 65285
$_097:	mov	dword ptr [rsi], eax
	jmp	$_100

$_098:	mov	rcx, rbx
	call	$_009
	mov	dword ptr [rsi], eax
	jmp	$_100

$_099:	test	rbx, rbx
	jz	$_089
	test	byte ptr [rbx+0x15], 0x04
	jnz	$_092
	cmp	byte ptr [rbx+0x18], 5
	jz	$_093
	cmp	byte ptr [rbx+0x19], -127
	jz	$_094
	cmp	byte ptr [rbx+0x19], -126
	jz	$_095
	jmp	$_098

$_100:	jmp	$_108

$_101:	test	rbx, rbx
	jnz	$_104
	mov	rbx, qword ptr [rdi+0x60]
	test	byte ptr [rdi+0x43], 0x08
	jz	$_102
	test	rbx, rbx
	jz	$_102
	cmp	word ptr [rbx+0x5A], 4
	jnz	$_102
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsi], eax
	jmp	$_103

$_102:	mov	eax, dword ptr [rdi]
	mov	dword ptr [rsi], eax
$_103:	jmp	$_106

$_104:	cmp	byte ptr [rbx+0x18], 2
	jnz	$_105
	test	byte ptr [rbx+0x3B], 0x01
	jnz	$_105
	mov	rcx, rbx
	call	$_009
	mov	dword ptr [rsi], eax
	jmp	$_106

$_105:	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsi], eax
$_106:	jmp	$_108

$_107:	cmp	eax, 240
	je	$_081
	cmp	eax, 241
	je	$_084
	cmp	eax, 254
	je	$_088
	cmp	eax, 255
	jz	$_101
$_108:	xor	eax, eax
	jmp	$_180
$C009B:
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_109
	cmp	byte ptr [rdi+0x40], -64
	jz	$_110
	cmp	byte ptr [rdi+0x40], -127
	jz	$_110
	cmp	byte ptr [rdi+0x40], -126
	jz	$_110
$_109:	mov	ecx, 2028
	call	qword ptr [fnasmerr+rip]
	jmp	$_180
$_110:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsi+0x38], eax
	xor	eax, eax
	jmp	$_180
$C009F:
	test	byte ptr [rdi+0x43], 0x08
	jnz	$_111
	mov	ecx, 2010
	call	qword ptr [fnasmerr+rip]
	jmp	$_180
$_111:	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_112
	mov	ecx, 2034
	call	qword ptr [fnasmerr+rip]
	jmp	$_180
$_112:	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jnz	$_113
	mov	ecx, 2034
	call	asmerr@PLT
	jmp	$_180
$_113:	mov	rbx, qword ptr [thissym+rip]
	test	rbx, rbx
	jnz	$_114
	lea	rcx, [DS0000+rip]
	call	SymAlloc@PLT
	mov	qword ptr [thissym+rip], rax
	mov	rbx, rax
	mov	byte ptr [rbx+0x18], 1
	or	byte ptr [rbx+0x14], 0x02
$_114:	mov	dword ptr [rsi+0x3C], 1
	mov	qword ptr [rsi+0x50], rbx
	mov	rcx, qword ptr [rdi+0x60]
	mov	qword ptr [rbx+0x20], rcx
	test	rcx, rcx
	jz	$_115
	mov	byte ptr [rbx+0x19], -60
	jmp	$_116
$_115:	mov	cl, byte ptr [rdi+0x40]
	mov	byte ptr [rbx+0x19], cl
$_116:	mov	rcx, rbx
	call	SetSymSegOfs@PLT
	mov	rbx, qword ptr [thissym+rip]
	mov	al, byte ptr [rbx+0x19]
	mov	byte ptr [rsi+0x40], al
	xor	eax, eax
	jmp	$_180
$C00A6:
$C00A7:
	mov	rbx, qword ptr [rbp+0x40]
	mov	dword ptr [rsi+0x3C], 0
	cmp	dword ptr [rdi+0x38], -2
	jz	$_117
	cmp	byte ptr [rdi+0x40], -64
	jz	$_117
	mov	dword ptr [rdi+0x38], -2
	xor	ebx, ebx
$_117:	jmp	$_152

$_118:	cmp	qword ptr [rdi+0x50], 0
	je	$C00B1
	jmp	$_119
$C00AD: mov	dword ptr [rsi], 1
	jmp	$C00B1
$C00B2: mov	dword ptr [rsi], 2
	jmp	$C00B1
$C00B4: mov	dword ptr [rsi], 4
	jmp	$C00B1
$C00B6: mov	dword ptr [rsi], 8
	jmp	$C00B1
$C00B8: mov	rcx, qword ptr [rdi+0x50]
	call	GetSymOfssize@PLT
	mov	ecx, eax
	mov	eax, 2
	shl	eax, cl
	mov	dword ptr [rsi], eax
	or	byte ptr [rsi+0x43], 0x08
	jmp	$C00B1
$_119:	cmp	dword ptr [rdi+0x38], 235
	jl	$C00B1
	cmp	dword ptr [rdi+0x38], 261
	jg	$C00B1
	push	rax
	movsxd	rax, dword ptr [rdi+0x38]
	lea	r11, [$C00B1+rip]
	movzx	eax, byte ptr [r11+rax-(235)+(IT$C00BC-$C00B1)]
	movzx	eax, byte ptr [r11+rax+($C00BC-$C00B1)]
	sub	r11, rax
	pop	rax
	jmp	r11
$C00BC:
	.byte $C00B1-$C00AD
	.byte $C00B1-$C00B2
	.byte $C00B1-$C00B4
	.byte $C00B1-$C00B6
	.byte $C00B1-$C00B8
	.byte 0
IT$C00BC:
	.byte 0
	.byte 0
	.byte 2
	.byte 1
	.byte 4
	.byte 5
	.byte 5
	.byte 0
	.byte 0
	.byte 2
	.byte 1
	.byte 4
	.byte 5
	.byte 5
	.byte 4
	.byte 5
	.byte 4
	.byte 5
	.byte 5
	.byte 5
	.byte 5
	.byte 5
	.byte 5
	.byte 5
	.byte 5
	.byte 3
	.byte 3
$C00B1: jmp	$_154

$_120:	mov	rbx, qword ptr [rdi+0x60]
	jmp	$_134

$_121:	test	rbx, rbx
	jz	$_122
	cmp	word ptr [rbx+0x5A], 4
	jnz	$_122
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rdi], eax
$_122:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	jmp	$_136

$_123:	mov	rax, qword ptr [rdi+0x18]
	mov	ecx, dword ptr [rax+0x4]
	call	SizeFromRegister@PLT
	mov	dword ptr [rsi], eax
	or	byte ptr [rsi+0x43], 0x08
	mov	rax, qword ptr [rdi+0x18]
	imul	eax, dword ptr [rax+0x4], 12
	lea	rcx, [SpecialTable+rip]
	test	byte ptr [rcx+rax], 0x0E
	jz	$_124
	cmp	byte ptr [rsi+0x40], -64
	jnz	$_124
	mov	al, byte ptr [ModuleInfo+0x1CE+rip]
	cmp	byte ptr [rsi], al
	jnz	$_124
	mov	rax, qword ptr [rdi+0x18]
	movzx	eax, byte ptr [rax+0x1]
	call	GetStdAssumeEx_@PLT
	mov	rbx, rax
	jmp	$_125

$_124:	xor	ebx, ebx
$_125:	test	rbx, rbx
	jz	$_126
	mov	qword ptr [rsi+0x60], rbx
	mov	al, byte ptr [rbx+0x19]
	mov	byte ptr [rsi+0x40], al
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsi], eax
	jmp	$_127

$_126:	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	cmp	byte ptr [rsi+0x40], -64
	jnz	$_127
	lea	rdx, [rsi+0x40]
	mov	ecx, dword ptr [rsi]
	call	MemtypeFromSize@PLT
$_127:	jmp	$_136

$_128:	cmp	byte ptr [rdi+0x40], -64
	jz	$_131
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_129
	cmp	byte ptr [rdi+0x40], 47
	jnz	$_129
	xor	eax, eax
	jmp	$_130

$_129:	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
	mov	r8, qword ptr [rdi+0x60]
	movzx	edx, byte ptr [rdi+0x42]
	movzx	ecx, byte ptr [rdi+0x40]
	call	SizeFromMemtype@PLT
$_130:	mov	dword ptr [rsi], eax
	jmp	$_132

$_131:	mov	rbx, qword ptr [rdi+0x60]
	test	rbx, rbx
	jz	$_132
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsi], eax
	mov	al, byte ptr [rbx+0x19]
	mov	byte ptr [rsi+0x40], al
$_132:	or	byte ptr [rsi+0x43], 0x08
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	jmp	$_136

$_133:	mov	dword ptr [rsi], 0
	jmp	$_136

$_134:	test	byte ptr [rdi+0x43], 0x08
	jne	$_121
	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_135
	test	byte ptr [rdi+0x43], 0x01
	je	$_123
$_135:	cmp	byte ptr [rdi+0x40], -64
	jnz	$_128
	test	byte ptr [rdi+0x43], 0x02
	jne	$_128
	jmp	$_133

$_136:	jmp	$_154

$_137:	mov	dword ptr [rsi+0x3C], 1
	mov	qword ptr [rsi+0x50], rbx
	or	byte ptr [rsi+0x43], 0x08
	jmp	$_154

$_138:	or	byte ptr [rsi+0x43], 0x08
	mov	rbx, qword ptr [rbx+0x20]
	mov	qword ptr [rsi+0x60], rbx
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsi], eax
	mov	al, byte ptr [rbx+0x19]
	mov	byte ptr [rsi+0x40], al
	jmp	$_154

$_139:	or	byte ptr [rsi+0x43], 0x08
	cmp	byte ptr [rsi+0x40], -64
	jnz	$_140
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
$_140:	mov	rbx, qword ptr [rbp+0x40]
	jmp	$_149

$_141:	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rsi+0x28], rax
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsi], eax
	jmp	$_151

$_142:	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rsi+0x28], rax
	mov	ecx, 129
	cmp	byte ptr [rbx+0x1C], 0
	jz	$_143
	mov	ecx, 130
$_143:	xor	r8d, r8d
	movzx	edx, byte ptr [rbx+0x38]
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	mov	dword ptr [rsi], eax
	jmp	$_151

$_144:	mov	rcx, rbx
	call	GetSymOfssize@PLT
	mov	ecx, eax
	mov	eax, 2
	shl	eax, cl
	or	eax, 0xFF00
	mov	dword ptr [rsi], eax
	jmp	$_151

$_145:	mov	rcx, rbx
	call	GetSymOfssize@PLT
	test	rax, rax
	jz	$_146
	mov	eax, 65286
	jmp	$_147

$_146:	mov	eax, 65285
$_147:	mov	dword ptr [rsi], eax
	jmp	$_151

$_148:	mov	rcx, rbx
	call	GetSymOfssize@PLT
	mov	edx, eax
	mov	r8, qword ptr [rbx+0x20]
	movzx	ecx, byte ptr [rdi+0x40]
	call	SizeFromMemtype@PLT
	mov	dword ptr [rsi], eax
	jmp	$_151

$_149:	cmp	qword ptr [rdi+0x60], 0
	jz	$_150
	cmp	qword ptr [rdi+0x58], 0
	je	$_141
$_150:	cmp	byte ptr [rbx+0x19], -61
	je	$_142
	cmp	byte ptr [rbx+0x19], -127
	jz	$_144
	cmp	byte ptr [rbx+0x19], -126
	jz	$_145
	jmp	$_148

$_151:	jmp	$_154

$_152:	cmp	dword ptr [rdi+0x38], -2
	jne	$_118
	test	rbx, rbx
	je	$_120
	cmp	byte ptr [rbx+0x18], 0
	je	$_137
	cmp	byte ptr [rbx+0x19], -60
	jnz	$_153
	test	byte ptr [rdi+0x43], 0x02
	je	$_138
$_153:	jmp	$_139

$_154:	xor	eax, eax
	jmp	$_180
$C00E4:
$C00E5:
	jmp	$_159

$_155:	mov	rbx, qword ptr [rdi+0x60]
	cmp	word ptr [rbx+0x5A], 4
	jz	$_156
	mov	ecx, 2019
	call	qword ptr [fnasmerr+rip]
	jmp	$_180

$_156:	jmp	$_160

$_157:	mov	rbx, qword ptr [rdi+0x58]
	jmp	$_160

$_158:	mov	rbx, qword ptr [rdi+0x50]
	jmp	$_160

$_159:	test	byte ptr [rdi+0x43], 0x08
	jnz	$_155
	cmp	dword ptr [rdi+0x3C], 0
	jz	$_157
	jmp	$_158

$_160:	cmp	dword ptr [rbp+0x48], 247
	jz	$_161
	cmp	dword ptr [rbp+0x48], 248
	jnz	$_167
$_161:	mov	dword ptr [rsi], 0
	test	byte ptr [rdi+0x43], 0x08
	jz	$_162
	mov	rcx, rbx
	call	$_011
	jmp	$_166

$_162:	xor	eax, eax
	xor	edx, edx
	mov	ecx, dword ptr [rbx+0x28]
	mov	edi, dword ptr [rbx+0x50]
	add	edi, ecx
$_163:	cmp	ecx, edi
	jnc	$_166
	mov	ebx, 1
	cmp	ecx, 32
	jnc	$_164
	shl	ebx, cl
	or	eax, ebx
	jmp	$_165

$_164:	sub	ecx, 32
	shl	ebx, cl
	or	edx, ebx
	add	ecx, 32
$_165:	inc	ecx
	jmp	$_163

$_166:	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], edx
	jmp	$_171

$_167:	test	byte ptr [rdi+0x43], 0x08
	jz	$_170
	mov	rax, qword ptr [rbx+0x68]
	mov	rcx, qword ptr [rax]
$_168:	test	rcx, rcx
	jz	$_169
	mov	eax, dword ptr [rcx+0x50]
	add	dword ptr [rsi], eax
	mov	rcx, qword ptr [rcx+0x68]
	jmp	$_168

$_169:	jmp	$_171

$_170:	mov	eax, dword ptr [rbx+0x50]
	mov	dword ptr [rsi], eax
$_171:	mov	dword ptr [rsi+0x3C], 0
	xor	eax, eax
	jmp	$_180
$C00FC:
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_172
	mov	r8d, 16
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_022
	test	rax, rax
	jz	$_172
	mov	eax, ecx
	jmp	$_180

$_172:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	byte ptr [rsi+0x40], 7
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_173
	cmp	dword ptr [rdi+0x38], 252
	jz	$_173
	mov	dword ptr [rsi+0x38], 261
	mov	byte ptr [rsi+0x40], -64
$_173:	mov	dword ptr [rsi+0x8], 0
	mov	dword ptr [rsi+0xC], 0
	xor	eax, eax
	jmp	$_180
$C0100:
	xor	eax, eax
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_175
	mov	r8d, 16
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_022
	test	rax, rax
	jz	$_174
	mov	eax, ecx
	jmp	$_180
$_174:	jmp	$_176
$_175:	test	byte ptr [rdi+0x43], 0x20
	jz	$_176
	cmp	dword ptr [rdi+0x8], eax
	jnz	$_176
	cmp	dword ptr [rdi+0xC], eax
	jnz	$_176
	dec	eax
	mov	dword ptr [rdi+0x8], eax
	mov	dword ptr [rdi+0xC], eax
$_176:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	byte ptr [rsi+0x40], 7
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_177
	cmp	dword ptr [rdi+0x38], 252
	jz	$_177
	mov	dword ptr [rsi+0x38], 260
	mov	byte ptr [rsi+0x40], -64
$_177:	mov	rax, qword ptr [rsi+0x8]
	mov	qword ptr [rsi], rax
	mov	dword ptr [rsi+0x8], 0
	mov	dword ptr [rsi+0xC], 0
	xor	eax, eax
	jmp	$_180
$C0106:
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_178
	mov	ecx, 2176
	call	qword ptr [fnasmerr+rip]
	jmp	$_180

$_178:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	rcx, rsi
	call	__sqrtq@PLT
	jmp	$C0108

$_179:	cmp	eax, 0
	jl	$C0108
	cmp	eax, 24
	jg	$C0108
	push	rax
	lea	r11, [$C0108+rip]
	movzx	eax, word ptr [r11+rax*2+($C0109-$C0108)]
	sub	r11, rax
	pop	rax
	jmp	r11
	.ALIGN 2
$C0109:
	.word $C0108-$C001F
	.word $C0108-$C0022
	.word $C0108-$C0024
	.word $C0108-$C0026
	.word $C0108-$C0028
	.word $C0108-$C002C
	.word $C0108-$C0030
	.word $C0108-$C0031
	.word $C0108-$C0032
	.word $C0108-$C0033
	.word $C0108-$C003B
	.word $C0108-$C0041
	.word $C0108-$C0042
	.word $C0108-$C006F
	.word $C0108-$C0070
	.word $C0108-$C0071
	.word $C0108-$C009B
	.word $C0108-$C009F
	.word $C0108-$C00A6
	.word $C0108-$C00A7
	.word $C0108-$C00E4
	.word $C0108-$C00E5
	.word $C0108-$C00FC
	.word $C0108-$C0100
	.word $C0108-$C0106

$C0108: xor	eax, eax
$_180:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_181:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	r8d, 104
	xor	edx, edx
	call	tmemset@PLT
	mov	rcx, rax
	mov	dword ptr [rcx+0x38], -2
	mov	dword ptr [rcx+0x3C], -2
	mov	byte ptr [rcx+0x40], -64
	mov	byte ptr [rcx+0x42], -2
	leave
	ret

$_182:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	al, byte ptr [rcx]
	jmp	$_191

$_183:	movzx	eax, byte ptr [rcx+0x1]
	jmp	$_193

$_184:	mov	eax, 1
	cmp	byte ptr [ModuleInfo+0x1D6+rip], 0
	jz	$_185
	mov	eax, 9
$_185:	jmp	$_193

$_186:	mov	eax, 2
	jmp	$_193

$_187:	mov	eax, 3
	jmp	$_193

$_188:	mov	eax, 8
	jmp	$_193

$_189:	mov	eax, 7
	cmp	byte ptr [rcx+0x1], 0
	jz	$_190
	mov	eax, 9
$_190:	jmp	$_193

	jmp	$_192

$_191:	cmp	al, 4
	jz	$_183
	cmp	al, 5
	jz	$_183
	cmp	al, 40
	jz	$_184
	cmp	al, 91
	jz	$_184
	cmp	al, 46
	jz	$_186
	cmp	al, 58
	jz	$_187
	cmp	al, 42
	jz	$_188
	cmp	al, 47
	jz	$_188
	cmp	al, 43
	jz	$_189
	cmp	al, 45
	jz	$_189
$_192:	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2008
	call	qword ptr [fnasmerr+rip]
	mov	rax, -1
$_193:	leave
	ret

$_194:
	cmp	cl, 63
	jnz	$_195
	mov	eax, 64
	jmp	$_201

$_195:	test	cl, 0xFFFFFF80
	jnz	$_196
	and	ecx, 0x1F
	inc	ecx
	mov	eax, ecx
	jmp	$_201

$_196:	cmp	edx, 254
	jnz	$_197
	movzx	edx, byte ptr [ModuleInfo+0x1CC+rip]
$_197:	cmp	cl, -127
	jnz	$_198
	mov	eax, 2
	mov	ecx, edx
	shl	eax, cl
	or	eax, 0xFF00
	jmp	$_201

$_198:	cmp	cl, -126
	jnz	$_200
	mov	eax, 65285
	test	dl, dl
	jz	$_199
	mov	eax, 2
	mov	ecx, edx
	shl	eax, cl
	add	eax, 2
	or	eax, 0xFF00
$_199:	jmp	$_201

$_200:	xor	eax, eax
$_201:	ret

$_202:
	cmp	byte ptr [rcx-0x18], 44
	jnz	$_203
	cmp	byte ptr [rcx-0x30], 2
	jnz	$_203
	cmp	byte ptr [rcx-0x48], 1
	jnz	$_203
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rcx-0x2C], 12
	mov	eax, dword ptr [r11+rax]
	test	eax, 0x10
	jz	$_203
	cmp	dword ptr [rcx-0x44], 1301
	jnc	$_203
	cmp	dword ptr [rcx-0x44], 930
	jc	$_203
	xor	eax, eax
	jmp	$_204

$_203:	or	byte ptr [rcx+0x2], 0x10
	mov	eax, 1
$_204:	ret

$_205:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	eax, dword ptr [rdx]
	mov	dword ptr [rbp-0x18], eax
	mov	rdi, rcx
	mov	rbx, r8
	imul	eax, eax, 24
	add	rbx, rax
	mov	al, byte ptr [rbx]
	jmp	$_319

$_206:	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_208
	cmp	dword ptr [rbp-0x18], 2
	jle	$_208
	cmp	byte ptr [rbx-0x18], 44
	jnz	$_208
	cmp	byte ptr [rbx-0x30], 2
	jz	$_208
	inc	dword ptr [rbp-0x18]
	inc	dword ptr [rdx]
	add	rbx, 24
	mov	al, byte ptr [rbx]
	cmp	al, 91
	jnz	$_207
	xor	eax, eax
	jmp	$_321

$_207:	jmp	$_319

$_208:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_209:	mov	dword ptr [rdi+0x3C], 0
	mov	r9d, dword ptr [rbx+0x4]
	movsx	r8d, byte ptr [rbx+0x1]
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	_atoow@PLT
	jmp	$_320

$_210:	cmp	byte ptr [rbx+0x1], 34
	jz	$_216
	cmp	byte ptr [rbx+0x1], 39
	jz	$_216
	test	byte ptr [rdi+0x43], 0x10
	jne	$_320
	mov	rcx, qword ptr [rbx+0x8]
	mov	al, byte ptr [rcx]
	cmp	byte ptr [rbx+0x1], 0
	jnz	$_212
	cmp	al, 34
	jz	$_211
	cmp	al, 39
	jnz	$_212
$_211:	mov	ecx, 2046
	call	qword ptr [fnasmerr+rip]
	jmp	$_215

$_212:	cmp	byte ptr [rbx+0x1], 123
	jnz	$_214
	mov	dword ptr [rdi+0x3C], -2
	mov	rcx, rbx
	call	$_202
	test	rax, rax
	jnz	$_213
	mov	dword ptr [rdi+0x3C], 0
	mov	qword ptr [rdi+0x10], rbx
$_213:	jmp	$_320

	jmp	$_215

$_214:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2167
	call	qword ptr [fnasmerr+rip]
$_215:	mov	rax, -1
	jmp	$_321

$_216:	mov	dword ptr [rdi+0x3C], 0
	mov	qword ptr [rdi+0x10], rbx
	mov	rdx, qword ptr [rbx+0x8]
	inc	rdx
	mov	ecx, dword ptr [rbx+0x4]
	cmp	ecx, 16
	jbe	$_217
	mov	ecx, 16
$_217:	test	ecx, ecx
	jz	$_218
	mov	al, byte ptr [rdx]
	inc	rdx
	mov	byte ptr [rdi+rcx-0x1], al
	dec	ecx
	jmp	$_217

$_218:	jmp	$_320

$_219:	mov	dword ptr [rdi+0x3C], 2
	mov	qword ptr [rdi+0x18], rbx
	imul	eax, dword ptr [rbx+0x4], 12
	lea	rcx, [SpecialTable+rip]
	movzx	eax, word ptr [rcx+rax+0x8]
	mov	ecx, dword ptr [ModuleInfo+0x1C0+rip]
	mov	edx, ecx
	and	ecx, 0xFF00
	and	edx, 0xF0
	mov	esi, eax
	and	esi, 0xF0
	test	eax, 0xFF00
	jz	$_220
	test	ecx, eax
	jz	$_221
$_220:	cmp	edx, esi
	jnc	$_223
$_221:	test	byte ptr [rbp+0x40], 0x08
	jz	$_222
	mov	dword ptr [rdi+0x3C], -1
	mov	ecx, 2085
	call	qword ptr [fnasmerr+rip]
	jmp	$_223

$_222:	mov	ecx, 2085
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_223:	cmp	dword ptr [rbp-0x18], 0
	jle	$_224
	cmp	dword ptr [rbx-0x14], 258
	jz	$_225
$_224:	cmp	dword ptr [rbp-0x18], 1
	jle	$_226
	cmp	byte ptr [rbx-0x18], 40
	jnz	$_226
	cmp	dword ptr [rbx-0x2C], 258
	jnz	$_226
$_225:	jmp	$_232

$_226:	test	byte ptr [rbp+0x40], 0x08
	jz	$_232
	lea	rcx, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	add	rax, rcx
	test	dword ptr [rax+0x4], 0x80
	jz	$_227
	or	byte ptr [rdi+0x43], 0x41
	jmp	$_232

$_227:	test	byte ptr [rax+0x3], 0x0C
	jz	$_230
	cmp	byte ptr [rbx+0x18], 58
	jnz	$_228
	cmp	byte ptr [Options+0xC6+rip], 0
	jz	$_229
	cmp	byte ptr [rbx+0x30], 2
	jnz	$_229
$_228:	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_229:	jmp	$_232

$_230:	test	byte ptr [rdi+0x43], 0x10
	jz	$_231
	mov	dword ptr [rdi+0x3C], -1
	jmp	$_232

$_231:	mov	ecx, 2031
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_232:	jmp	$_320

$_233:	cmp	dword ptr [rbp-0x18], 0
	je	$_241
	cmp	dword ptr [rbx+0x4], 271
	jne	$_241
	cmp	byte ptr [rbx+0x18], 40
	jne	$_241
	add	dword ptr [rbp-0x18], 2
	add	rbx, 48
	mov	dword ptr [rdi+0x3C], 0
	mov	dword ptr [rdi], 0
	mov	dword ptr [rdi+0x4], 0
	mov	rcx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [rbp-0x18]
	cmp	byte ptr [rbx], 41
	jnz	$_234
	mov	dword ptr [rcx], eax
	dec	dword ptr [rdi]
	dec	dword ptr [rdi+0x4]
	jmp	$_320

$_234:	cmp	byte ptr [rbx], 10
	jnz	$_235
	cmp	byte ptr [rbx+0x18], 41
	jnz	$_235
	dec	dword ptr [rdi]
	dec	dword ptr [rdi+0x4]
	inc	eax
	mov	dword ptr [rcx], eax
	jmp	$_320

$_235:	cmp	byte ptr [rbx], 8
	jne	$_241
	cmp	byte ptr [rbx+0x18], 41
	jne	$_241
	inc	eax
	mov	dword ptr [rcx], eax
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_236
	cmp	byte ptr [rax+0x18], 0
	jz	$_236
	dec	dword ptr [rdi]
	dec	dword ptr [rdi+0x4]
	jmp	$_320

$_236:	cmp	byte ptr [rbx+0x30], 0
	je	$_320
	cmp	dword ptr [rbx+0x34], 585
	jne	$_320
	cmp	dword ptr [rbx-0x44], 657
	je	$_320
	add	rbx, 72
	mov	edx, dword ptr [rbp-0x18]
	add	edx, 3
	xor	ecx, ecx
$_237:	cmp	edx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_240
	cmp	byte ptr [rbx], 41
	jnz	$_238
	test	ecx, ecx
	jz	$_240
	dec	ecx
	jmp	$_239

$_238:	cmp	byte ptr [rbx], 40
	jnz	$_239
	inc	ecx
$_239:	inc	edx
	add	rbx, 24
	jmp	$_237

$_240:	dec	edx
	mov	rcx, qword ptr [rbp+0x30]
	mov	dword ptr [rcx], edx
	jmp	$_320

$_241:	mov	rsi, qword ptr [rbx+0x8]
	test	byte ptr [rdi+0x43], 0xFFFFFF80
	jz	$_248
	mov	rcx, qword ptr [rdi+0x60]
	xor	eax, eax
	mov	dword ptr [rdi], eax
	test	rcx, rcx
	jz	$_242
	xor	r9d, r9d
	mov	r8, rdi
	mov	rdx, rsi
	call	SearchNameInStruct@PLT
$_242:	test	rax, rax
	jnz	$_247
	mov	rcx, rsi
	call	SymFind@PLT
	test	rax, rax
	jz	$_247
	cmp	byte ptr [rax+0x18], 7
	jnz	$_245
	mov	rcx, qword ptr [rdi+0x60]
	cmp	rax, rcx
	jz	$_244
	test	rcx, rcx
	jz	$_243
	test	byte ptr [rcx+0x14], 0x02
	jz	$_244
$_243:	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jnz	$_244
	xor	eax, eax
$_244:	jmp	$_247

$_245:	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jz	$_246
	cmp	byte ptr [rax+0x18], 6
	jz	$_247
	cmp	byte ptr [rax+0x18], 2
	jz	$_247
	cmp	byte ptr [rax+0x18], 1
	jz	$_247
$_246:	xor	eax, eax
$_247:	jmp	$_251

$_248:	mov	edx, dword ptr [rsi]
	or	dh, 0x20
	cmp	dl, 64
	jnz	$_250
	test	edx, 0xFF0000
	jnz	$_250
	cmp	dh, 98
	jnz	$_249
	xor	edx, edx
	lea	rcx, [rbp-0x28]
	call	GetAnonymousLabel@PLT
	mov	rsi, rax
	jmp	$_250

$_249:	cmp	dh, 102
	jnz	$_250
	mov	edx, 1
	lea	rcx, [rbp-0x28]
	call	GetAnonymousLabel@PLT
	mov	rsi, rax
$_250:	mov	rcx, rsi
	call	SymFind@PLT
$_251:	test	rax, rax
	jz	$_253
	cmp	byte ptr [rax+0x18], 0
	jz	$_253
	cmp	byte ptr [rax+0x18], 7
	jnz	$_252
	cmp	word ptr [rax+0x5A], 0
	jz	$_253
$_252:	cmp	byte ptr [rax+0x18], 9
	jz	$_253
	cmp	byte ptr [rax+0x18], 10
	jne	$_271
$_253:	test	byte ptr [rdi+0x43], 0x10
	jz	$_254
	mov	dword ptr [rdi+0x3C], -1
	jmp	$_320

$_254:	test	rax, rax
	jz	$_256
	cmp	byte ptr [rax+0x18], 9
	jz	$_255
	cmp	byte ptr [rax+0x18], 10
	jnz	$_256
$_255:	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2148
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_256:	test	rax, rax
	jnz	$_258
	cmp	byte ptr [rbx-0x18], 46
	jnz	$_258
	cmp	byte ptr [rbx-0x30], 8
	jz	$_257
	cmp	byte ptr [rbx-0x30], 93
	jnz	$_258
$_257:	mov	rdx, qword ptr [rbp+0x38]
	cmp	dword ptr [rdx+0x4], 512
	jnz	$_258
	mov	rcx, rbx
	call	FindDotSymbol@PLT
	test	rax, rax
	jz	$_258
	jmp	$_272

$_258:	cmp	dword ptr [Parse_Pass+rip], 0
	jne	$_268
	test	byte ptr [rbp+0x40], 0x02
	jne	$_268
	test	rax, rax
	jne	$_267
	mov	rcx, qword ptr [rdi+0x60]
	test	rcx, rcx
	jnz	$_264
	mov	rcx, rsi
	call	SymLookup@PLT
	mov	qword ptr [rbp-0x10], rax
	cmp	byte ptr [rax+0x18], 0
	jnz	$_260
	test	byte ptr [rax+0x14], 0x01
	jnz	$_259
	mov	rdx, rax
	lea	rcx, [SymTables+rip]
	call	sym_add_table@PLT
	mov	rax, qword ptr [rbp-0x10]
$_259:	jmp	$_263

$_260:	test	byte ptr [rdi+0x43], 0xFFFFFF80
	jz	$_262
	mov	rax, qword ptr [nullmbr+rip]
	test	rax, rax
	jnz	$_261
	lea	rcx, [DS0000+rip]
	call	SymAlloc@PLT
	mov	qword ptr [nullmbr+rip], rax
$_261:	jmp	$_263

$_262:	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2004
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_263:	jmp	$_267

$_264:	cmp	word ptr [rcx+0x5A], 0
	jz	$_265
	mov	rdx, rsi
	mov	ecx, 2006
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

	jmp	$_267

$_265:	mov	rax, qword ptr [nullmbr+rip]
	test	rax, rax
	jnz	$_266
	lea	rcx, [DS0000+rip]
	call	SymAlloc@PLT
$_266:	mov	qword ptr [rdi+0x58], rax
	mov	dword ptr [rdi+0x3C], 0
	jmp	$_320

$_267:	jmp	$_270

$_268:	cmp	byte ptr [rsi+0x1], 38
	jnz	$_269
	lea	rsi, [DS0001+rip]
$_269:	mov	rdx, rsi
	mov	ecx, 2006
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_270:	jmp	$_272

$_271:	cmp	byte ptr [rax+0x18], 8
	jnz	$_272
	mov	rax, qword ptr [rax+0x28]
$_272:	or	byte ptr [rax+0x14], 0x01
	jmp	$_298

$_273:	mov	rcx, qword ptr [rax+0x68]
	cmp	word ptr [rax+0x5A], 3
	jz	$_274
	test	byte ptr [rcx+0x11], 0x02
	jz	$_274
	mov	dword ptr [rdi+0x3C], -1
	jmp	$_299

$_274:	cmp	qword ptr [rax+0x20], 0
	jz	$_275
	cmp	rax, qword ptr [rax+0x20]
	jz	$_275
	mov	rax, qword ptr [rax+0x20]
	jmp	$_274

$_275:	mov	cl, byte ptr [rax+0x19]
	mov	dword ptr [rdi+0x3C], 0
	mov	byte ptr [rdi+0x40], cl
	or	byte ptr [rdi+0x43], 0x08
	mov	qword ptr [rdi+0x60], rax
	and	ecx, 0xC0
	cmp	word ptr [rax+0x5A], 4
	jnz	$_276
	mov	rcx, rax
	call	$_011
	mov	dword ptr [rdi], eax
	mov	dword ptr [rdi+0x4], edx
	jmp	$_280

$_276:	cmp	ecx, 128
	jnz	$_279
	cmp	byte ptr [rax+0x19], -128
	jnz	$_277
	mov	ecx, dword ptr [rax+0x50]
	mov	dword ptr [rdi], ecx
	mov	cl, byte ptr [rax+0x38]
	mov	byte ptr [rdi+0x42], cl
	jmp	$_278

$_277:	movzx	edx, byte ptr [rax+0x38]
	movzx	ecx, byte ptr [rax+0x19]
	call	$_194
	mov	dword ptr [rdi], eax
$_278:	jmp	$_280

$_279:	mov	eax, dword ptr [rax+0x50]
	mov	dword ptr [rdi], eax
$_280:	jmp	$_299

$_281:	mov	qword ptr [rdi+0x58], rax
	mov	dword ptr [rdi+0x3C], 0
	mov	ecx, dword ptr [rax+0x28]
	add	dword ptr [rdi], ecx
$_282:	cmp	qword ptr [rax+0x20], 0
	jz	$_283
	mov	rax, qword ptr [rax+0x20]
	jmp	$_282

$_283:	mov	cl, byte ptr [rax+0x19]
	mov	byte ptr [rdi+0x40], cl
	mov	qword ptr [rdi+0x60], 0
	cmp	byte ptr [rax+0x18], 7
	jnz	$_284
	cmp	word ptr [rax+0x5A], 3
	jz	$_284
	mov	qword ptr [rdi+0x60], rax
	jmp	$_285

$_284:	cmp	cl, -61
	jnz	$_285
	cmp	byte ptr [rax+0x39], 0
	jz	$_285
	cmp	byte ptr [rax+0x3A], -128
	jz	$_285
	mov	rax, qword ptr [rax+0x40]
	mov	qword ptr [rdi+0x60], rax
	mov	byte ptr [rdi+0x41], -128
$_285:	jmp	$_299

$_286:	mov	rsi, rax
	mov	dword ptr [rdi+0x3C], 1
	test	byte ptr [rsi+0x14], 0x20
	jz	$_287
	cmp	qword ptr [rsi+0x58], 0
	jz	$_287
	xor	edx, edx
	mov	rcx, rsi
	call	qword ptr [rsi+0x58]
$_287:	cmp	byte ptr [rsi+0x18], 1
	jnz	$_289
	cmp	qword ptr [rsi+0x30], 0
	jnz	$_289
	mov	dword ptr [rdi+0x3C], 0
	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rdi], eax
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rdi+0x4], eax
	mov	al, byte ptr [rsi+0x19]
	mov	byte ptr [rdi+0x40], al
	cmp	al, 47
	jnz	$_288
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_288
	mov	dword ptr [rdi+0x3C], 3
	mov	qword ptr [rdi+0x10], 0
	mov	eax, dword ptr [rsi+0x58]
	mov	dword ptr [rdi+0x8], eax
	mov	eax, dword ptr [rsi+0x60]
	mov	dword ptr [rdi+0xC], eax
$_288:	jmp	$_297

$_289:	cmp	byte ptr [rsi+0x18], 2
	jnz	$_290
	cmp	byte ptr [rsi+0x19], -64
	jnz	$_290
	test	byte ptr [rsi+0x3B], 0x01
	jnz	$_290
	or	byte ptr [rdi+0x43], 0x04
	mov	qword ptr [rdi+0x50], rsi
	jmp	$_297

$_290:	mov	qword ptr [rdi+0x28], rbx
	mov	rcx, qword ptr [rsi+0x20]
	test	rcx, rcx
	jz	$_291
	cmp	byte ptr [rcx+0x19], -64
	jz	$_291
	mov	al, byte ptr [rcx+0x19]
	mov	byte ptr [rdi+0x40], al
	jmp	$_292

$_291:	mov	al, byte ptr [rsi+0x19]
	mov	byte ptr [rdi+0x40], al
$_292:	cmp	byte ptr [rsi+0x18], 5
	jnz	$_293
	mov	eax, dword ptr [rsi+0x28]
	add	eax, dword ptr [StackAdj+rip]
	cdq
	mov	dword ptr [rdi], eax
	mov	dword ptr [rdi+0x4], edx
	or	byte ptr [rdi+0x43], 0x01
	mov	qword ptr [rdi+0x18], rbx
	mov	rcx, qword ptr [CurrProc+rip]
	mov	rcx, qword ptr [rcx+0x68]
	movzx	eax, word ptr [rcx+0x42]
	mov	dword ptr [rbx+0x4], eax
	imul	eax, eax, 12
	lea	rcx, [SpecialTable+rip]
	mov	al, byte ptr [rcx+rax+0xA]
	mov	byte ptr [rbx+0x1], al
$_293:	mov	qword ptr [rdi+0x50], rsi
$_294:	cmp	qword ptr [rsi+0x20], 0
	jz	$_295
	mov	rsi, qword ptr [rsi+0x20]
	jmp	$_294

$_295:	cmp	byte ptr [rsi+0x18], 7
	jnz	$_296
	cmp	word ptr [rsi+0x5A], 3
	jz	$_296
	mov	qword ptr [rdi+0x60], rsi
	jmp	$_297

$_296:	mov	qword ptr [rdi+0x60], 0
$_297:	jmp	$_299

$_298:	cmp	byte ptr [rax+0x18], 7
	je	$_273
	cmp	byte ptr [rax+0x18], 6
	je	$_281
	jmp	$_286

$_299:	jmp	$_320

$_300:	mov	dword ptr [rdi+0x3C], 0
	imul	ecx, dword ptr [rbx+0x4], 12
	lea	rax, [SpecialTable+rip]
	add	rcx, rax
	mov	al, byte ptr [rcx+0xA]
	mov	byte ptr [rdi+0x40], al
	mov	eax, dword ptr [rcx+0x4]
	mov	byte ptr [rdi+0x42], al
	mov	edx, eax
	movzx	ecx, byte ptr [rdi+0x40]
	call	$_194
	mov	dword ptr [rdi], eax
	or	byte ptr [rdi+0x43], 0x08
	mov	qword ptr [rdi+0x60], 0
	jmp	$_320

$_301:	cmp	dword ptr [rbx+0x4], 274
	jnz	$_305
	test	byte ptr [rbp+0x40], 0x02
	jnz	$_303
	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	eax, 48
	jnc	$_302
	mov	ecx, 2085
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_302:	call	DefineFlatGroup@PLT
$_303:	mov	rax, qword ptr [ModuleInfo+0x200+rip]
	mov	qword ptr [rdi+0x50], rax
	test	eax, eax
	jnz	$_304
	mov	rax, -1
	jmp	$_321

$_304:	mov	qword ptr [rdi+0x28], rbx
	mov	dword ptr [rdi+0x3C], 1
	jmp	$_309

$_305:	cmp	dword ptr [rbx+0x4], 273
	jnz	$_308
	cmp	dword ptr [rbp-0x18], 2
	jle	$_308
	cmp	dword ptr [rbx-0x14], 258
	jz	$_306
	cmp	dword ptr [rbx-0x2C], 258
	jnz	$_308
$_306:	cmp	byte ptr [rbx+0x18], 8
	jz	$_307
	cmp	byte ptr [rbx+0x18], 91
	jnz	$_308
$_307:	inc	dword ptr [rdx]
	mov	dword ptr [rdi+0x3C], 1
	mov	byte ptr [rdi+0x40], -61
	jmp	$_320

	jmp	$_309

$_308:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	qword ptr [fnasmerr+rip]
	jmp	$_321

$_309:	jmp	$_320

$_310:	mov	dword ptr [rdi+0x3C], 3
	mov	byte ptr [rdi+0x40], 47
	mov	qword ptr [rdi+0x10], rbx
	movsx	eax, byte ptr [rbx+0x1]
	mov	dword ptr [rsp+0x20], eax
	xor	r9d, r9d
	mov	r8d, 16
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	atofloat@PLT
	jmp	$_320

$_311:	test	byte ptr [rdi+0x43], 0x10
	jz	$_314
	cmp	byte ptr [rbx], 0
	jz	$_312
	cmp	byte ptr [rbx], 41
	jz	$_312
	cmp	byte ptr [rbx], 93
	jnz	$_313
$_312:	xor	eax, eax
	jmp	$_321

$_313:	jmp	$_320

$_314:	mov	rcx, qword ptr [rbx+0x8]
	cmp	byte ptr [rbx], 12
	jnz	$_315
	mov	rdx, rcx
	mov	ecx, 2048
	call	qword ptr [fnasmerr+rip]
	jmp	$_318

$_315:	cmp	byte ptr [rbx], 58
	jnz	$_316
	mov	ecx, 2009
	call	qword ptr [fnasmerr+rip]
	jmp	$_318

$_316:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x03
	jz	$_317
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2016
	call	qword ptr [fnasmerr+rip]
	jmp	$_318

$_317:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	qword ptr [fnasmerr+rip]
$_318:	jmp	$_321

	jmp	$_320

$_319:	cmp	al, 38
	je	$_206
	cmp	al, 10
	je	$_209
	cmp	al, 9
	je	$_210
	cmp	al, 2
	je	$_219
	cmp	al, 5
	je	$_233
	cmp	al, 8
	je	$_241
	cmp	al, 6
	je	$_300
	cmp	al, 7
	je	$_301
	cmp	al, 11
	je	$_310
	jmp	$_311

$_320:	mov	rcx, qword ptr [rbp+0x30]
	inc	dword ptr [rcx]
	xor	eax, eax
$_321:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_322:
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	mov	eax, dword ptr [rbp+0x20]
	cmp	dword ptr [rcx+0x3C], eax
	jnz	$_323
	mov	eax, dword ptr [rbp+0x28]
	cmp	dword ptr [rdx+0x3C], eax
	jnz	$_323
	mov	eax, 1
	jmp	$_325

$_323:	mov	eax, dword ptr [rbp+0x28]
	cmp	dword ptr [rcx+0x3C], eax
	jnz	$_324
	mov	eax, dword ptr [rbp+0x20]
	cmp	dword ptr [rdx+0x3C], eax
	jnz	$_324
	mov	eax, 1
	jmp	$_325

$_324:	xor	eax, eax
$_325:	leave
	ret

$_326:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rax, qword ptr [rdx+0x18]
	test	rax, rax
	jz	$_335
	cmp	qword ptr [rcx+0x18], 0
	jnz	$_327
	mov	qword ptr [rcx+0x18], rax
	jmp	$_334

$_327:	cmp	qword ptr [rcx+0x20], 0
	jnz	$_330
	cmp	byte ptr [rax+0x1], 4
	jnz	$_328
	mov	rax, qword ptr [rcx+0x18]
	mov	qword ptr [rcx+0x20], rax
	mov	rax, qword ptr [rdx+0x18]
	mov	qword ptr [rcx+0x18], rax
	jmp	$_329

$_328:	mov	qword ptr [rcx+0x20], rax
$_329:	jmp	$_334

$_330:	cmp	byte ptr [rax-0x18], 91
	jnz	$_333
	cmp	byte ptr [rax-0x30], 8
	jnz	$_333
	cmp	byte ptr [rax-0x48], 46
	jnz	$_333
	mov	rax, qword ptr [rcx+0x50]
	test	rax, rax
	jz	$_331
	cmp	byte ptr [rax+0x19], -61
	jnz	$_331
	cmp	byte ptr [rax+0x39], 0
	jnz	$_332
$_331:	mov	ecx, 2030
	call	qword ptr [fnasmerr+rip]
	jmp	$_342

$_332:	jmp	$_334

$_333:	mov	ecx, 2030
	call	qword ptr [fnasmerr+rip]
	jmp	$_342

$_334:	or	byte ptr [rcx+0x43], 0x01
$_335:	mov	rax, qword ptr [rdx+0x20]
	test	rax, rax
	jz	$_341
	cmp	qword ptr [rcx+0x20], 0
	jnz	$_336
	mov	qword ptr [rcx+0x20], rax
	mov	al, byte ptr [rdx+0x41]
	mov	byte ptr [rcx+0x41], al
	jmp	$_340

$_336:	cmp	byte ptr [rax-0x18], 91
	jnz	$_339
	cmp	byte ptr [rax-0x30], 8
	jnz	$_339
	cmp	byte ptr [rax-0x48], 46
	jnz	$_339
	mov	rax, qword ptr [rcx+0x50]
	test	rax, rax
	jz	$_337
	cmp	byte ptr [rax+0x19], -61
	jnz	$_337
	cmp	byte ptr [rax+0x39], 0
	jnz	$_338
$_337:	mov	ecx, 2030
	call	qword ptr [fnasmerr+rip]
	jmp	$_342

$_338:	jmp	$_340

$_339:	mov	ecx, 2030
	call	qword ptr [fnasmerr+rip]
	jmp	$_342

$_340:	or	byte ptr [rcx+0x43], 0x01
$_341:	xor	eax, eax
$_342:	leave
	ret

$_343:
	cmp	dword ptr [rcx+0x3C], 1
	jnz	$_344
	test	byte ptr [rcx+0x43], 0x01
	jz	$_345
$_344:	jmp	$_353

$_345:	cmp	qword ptr [rcx+0x50], 0
	jz	$_350
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_346
	jmp	$_353

$_346:	mov	rax, qword ptr [rcx+0x50]
	cmp	byte ptr [rax+0x18], 0
	jnz	$_347
	cmp	dword ptr [rcx+0x38], -2
	jz	$_349
$_347:	cmp	byte ptr [rax+0x18], 2
	jnz	$_348
	test	byte ptr [rax+0x3B], 0x02
	jz	$_348
	test	byte ptr [rcx+0x43], 0x04
	jnz	$_349
$_348:	jmp	$_353

$_349:	mov	dword ptr [rcx], 1
$_350:	mov	qword ptr [rcx+0x28], 0
	mov	rax, qword ptr [rcx+0x58]
	test	rax, rax
	jz	$_351
	cmp	byte ptr [rax+0x18], 6
	jz	$_351
	jmp	$_353

$_351:	cmp	qword ptr [rcx+0x30], 0
	jz	$_352
	jmp	$_353

$_352:	mov	dword ptr [rcx+0x38], -2
	mov	dword ptr [rcx+0x3C], 0
	and	byte ptr [rcx+0x43], 0xFFFFFFFD
	mov	byte ptr [rcx+0x40], -64
$_353:	ret

$_354:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rax, qword ptr [rcx+0x50]
	cmp	byte ptr [rax+0x18], 2
	jnz	$_355
	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2018
	call	qword ptr [fnasmerr+rip]
	jmp	$_359

$_355:	mov	rbx, qword ptr [rdx+0x50]
	cmp	byte ptr [rax+0x18], 0
	jz	$_356
	mov	rax, qword ptr [rax+0x30]
	cmp	qword ptr [rbx+0x30], rax
	jz	$_356
	cmp	byte ptr [rbx+0x18], 0
	jnz	$_357
$_356:	cmp	byte ptr [rbx+0x18], 2
	jnz	$_358
$_357:	mov	ecx, 2025
	call	qword ptr [fnasmerr+rip]
	jmp	$_359

$_358:	mov	rax, qword ptr [rcx+0x50]
	mov	dword ptr [rcx+0x3C], 0
	mov	dword ptr [rdx+0x3C], 0
	mov	eax, dword ptr [rax+0x28]
	add	dword ptr [rcx], eax
	mov	eax, dword ptr [rbx+0x28]
	add	dword ptr [rdx], eax
	xor	eax, eax
$_359:	leave
	pop	rbx
	ret

$_360:
	mov	rax, qword ptr [rcx+0x58]
	test	rax, rax
	jz	$_361
	cmp	byte ptr [rax+0x18], 7
	jnz	$_361
	mov	eax, dword ptr [rax+0x50]
	add	dword ptr [rcx], eax
	mov	qword ptr [rcx+0x58], 0
$_361:	ret

$_362:
	cmp	dword ptr [rcx+0x3C], 2
	jnz	$_363
	test	byte ptr [rcx+0x43], 0x01
	jz	$_364
$_363:	cmp	dword ptr [rdx+0x3C], 2
	jnz	$_365
	test	byte ptr [rdx+0x43], 0x01
	jnz	$_365
$_364:	mov	rax, -1
	jmp	$_366

$_365:	xor	eax, eax
$_366:	ret

$_367:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, rdx
	call	$_362
	cmp	eax, -1
	jnz	$_368
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_391

$_368:	cmp	dword ptr [rsi+0x3C], 2
	jnz	$_369
	mov	dword ptr [rsi+0x3C], 1
$_369:	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_370
	mov	dword ptr [rdi+0x3C], 1
$_370:	cmp	qword ptr [rdi+0x30], 0
	jz	$_372
	cmp	qword ptr [rsi+0x30], 0
	jz	$_371
	mov	rbx, qword ptr [rsi+0x30]
	mov	rax, qword ptr [rdi+0x30]
	mov	al, byte ptr [rax]
	cmp	al, byte ptr [rbx]
	jnz	$_371
	mov	ecx, 3013
	call	qword ptr [fnasmerr+rip]
	jmp	$_391

$_371:	mov	rax, qword ptr [rdi+0x30]
	mov	qword ptr [rsi+0x30], rax
$_372:	cmp	dword ptr [rsi+0x3C], 0
	jnz	$_373
	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_373
	mov	rax, qword ptr [rdi]
	add	qword ptr [rsi], rax
	jmp	$_390

$_373:	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_374
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_374
	mov	rdx, rdi
	mov	rcx, rsi
	call	__addq@PLT
	jmp	$_390

$_374:	cmp	dword ptr [rsi+0x3C], 1
	jne	$_380
	cmp	dword ptr [rdi+0x3C], 1
	jne	$_380
	mov	rcx, rsi
	call	$_360
	mov	rcx, rdi
	call	$_360
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_326
	cmp	eax, -1
	jnz	$_375
	jmp	$_391

$_375:	cmp	qword ptr [rdi+0x50], 0
	jz	$_378
	mov	rax, qword ptr [rsi+0x50]
	test	rax, rax
	jz	$_376
	cmp	byte ptr [rax+0x18], 0
	jz	$_376
	mov	rax, qword ptr [rdi+0x50]
	cmp	byte ptr [rax+0x18], 0
	jz	$_376
	mov	ecx, 2101
	call	qword ptr [fnasmerr+rip]
	jmp	$_391

$_376:	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rsi+0x28], rax
	mov	rax, qword ptr [rdi+0x50]
	mov	qword ptr [rsi+0x50], rax
	cmp	byte ptr [rsi+0x40], -64
	jnz	$_377
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
$_377:	cmp	dword ptr [rdi+0x38], -2
	jz	$_378
	mov	eax, dword ptr [rdi+0x38]
	mov	dword ptr [rsi+0x38], eax
$_378:	mov	rax, qword ptr [rdi]
	add	qword ptr [rsi], rax
	cmp	qword ptr [rdi+0x60], 0
	jz	$_379
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
$_379:	jmp	$_390

$_380:	mov	r9d, 1
	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_322
	test	rax, rax
	je	$_389
	cmp	dword ptr [rsi+0x3C], 0
	jnz	$_386
	mov	rax, qword ptr [rsi]
	add	qword ptr [rdi], rax
	test	byte ptr [rsi+0x43], 0x01
	jz	$_381
	or	byte ptr [rdi+0x43], 0x01
$_381:	test	byte ptr [rsi+0x43], 0x02
	jz	$_382
	or	byte ptr [rdi+0x43], 0x02
	mov	al, byte ptr [rsi+0x40]
	mov	byte ptr [rdi+0x40], al
	jmp	$_383

$_382:	cmp	byte ptr [rdi+0x40], -64
	jnz	$_383
	mov	al, byte ptr [rsi+0x40]
	mov	byte ptr [rdi+0x40], al
$_383:	cmp	qword ptr [rdi+0x58], 0
	jnz	$_384
	mov	rax, qword ptr [rsi+0x58]
	mov	qword ptr [rdi+0x58], rax
$_384:	cmp	qword ptr [rdi+0x60], 0
	jz	$_385
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
$_385:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	jmp	$_388

$_386:	mov	rax, qword ptr [rdi]
	add	qword ptr [rsi], rax
	cmp	qword ptr [rdi+0x58], 0
	jz	$_387
	mov	rax, qword ptr [rdi+0x58]
	mov	qword ptr [rsi+0x58], rax
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
	jmp	$_388

$_387:	cmp	byte ptr [rsi+0x40], -64
	jnz	$_388
	test	byte ptr [rdi+0x43], 0x08
	jnz	$_388
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
$_388:	mov	rcx, rsi
	call	$_360
	jmp	$_390

$_389:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_001
	jmp	$_391

$_390:	xor	eax, eax
$_391:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_392:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, rdx
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_362
	cmp	eax, -1
	jnz	$_393
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_427

$_393:	mov	rax, qword ptr [rdi+0x50]
	cmp	dword ptr [rsi+0x3C], 1
	jnz	$_394
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_394
	test	rax, rax
	jz	$_394
	cmp	byte ptr [rax+0x18], 0
	jz	$_395
$_394:	mov	rcx, rdi
	call	$_343
$_395:	jmp	$_420

$_396:	mov	rax, qword ptr [rdi]
	sub	qword ptr [rsi], rax
	jmp	$_426

$_397:	mov	rdx, rdi
	mov	rcx, rsi
	call	__subq@PLT
	jmp	$_426

$_398:	mov	rax, qword ptr [rdi]
	sub	qword ptr [rsi], rax
	mov	rcx, rsi
	call	$_360
	jmp	$_426

$_399:	mov	rcx, rsi
	call	$_360
	mov	rcx, rdi
	call	$_360
	test	byte ptr [rdi+0x43], 0x01
	jz	$_400
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_427

$_400:	cmp	qword ptr [rdi+0x28], 0
	jnz	$_402
	mov	rax, qword ptr [rdi]
	sub	qword ptr [rsi], rax
	test	byte ptr [rdi+0x43], 0x01
	jz	$_401
	or	byte ptr [rsi+0x43], 0x01
$_401:	jmp	$_416

$_402:	cmp	qword ptr [rsi+0x28], 0
	jz	$_403
	cmp	qword ptr [rsi+0x50], 0
	jz	$_403
	cmp	qword ptr [rdi+0x50], 0
	jnz	$_404
$_403:	mov	ecx, 2094
	call	qword ptr [fnasmerr+rip]
	jmp	$_427

$_404:	mov	rbx, qword ptr [rsi+0x50]
	mov	eax, dword ptr [rbx+0x28]
	add	dword ptr [rsi], eax
	mov	rax, qword ptr [rdi+0x50]
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_408
	cmp	byte ptr [rax+0x18], 2
	jz	$_405
	cmp	byte ptr [rbx+0x18], 2
	jnz	$_406
$_405:	cmp	rax, qword ptr [rsi+0x50]
	jz	$_406
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2018
	call	qword ptr [fnasmerr+rip]
	jmp	$_427

$_406:	mov	rax, qword ptr [rax+0x30]
	cmp	qword ptr [rbx+0x30], rax
	jz	$_407
	mov	ecx, 2025
	call	qword ptr [fnasmerr+rip]
	jmp	$_427

$_407:	mov	rax, qword ptr [rdi+0x50]
$_408:	mov	dword ptr [rsi+0x3C], 0
	cmp	byte ptr [rbx+0x18], 0
	jz	$_409
	cmp	byte ptr [rax+0x18], 0
	jnz	$_411
$_409:	mov	dword ptr [rsi], 1
	cmp	byte ptr [rbx+0x18], 0
	jz	$_410
	mov	qword ptr [rsi+0x50], rax
	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rsi+0x28], rax
$_410:	mov	dword ptr [rsi+0x3C], 1
	jmp	$_412

$_411:	mov	eax, dword ptr [rax+0x28]
	sub	dword ptr [rsi], eax
	sbb	dword ptr [rsi+0x4], 0
	mov	rax, qword ptr [rdi]
	sub	qword ptr [rsi], rax
	mov	qword ptr [rsi+0x28], 0
	mov	qword ptr [rsi+0x50], 0
$_412:	test	byte ptr [rsi+0x43], 0x01
	jnz	$_414
	cmp	dword ptr [rsi+0x38], 249
	jnz	$_413
	cmp	dword ptr [rdi+0x38], 249
	jnz	$_413
	mov	dword ptr [rsi+0x38], -2
$_413:	jmp	$_415

$_414:	mov	dword ptr [rsi+0x3C], 1
$_415:	and	byte ptr [rsi+0x43], 0xFFFFFFFD
	mov	byte ptr [rsi+0x40], -64
$_416:	jmp	$_426

$_417:	test	byte ptr [rdi+0x43], 0x01
	jz	$_418
	or	byte ptr [rsi+0x43], 0x01
$_418:	mov	dword ptr [rsi+0x3C], 1
	mov	rdx, qword ptr [rdi]
	mov	rax, -1
	mul	rdx
	mov	qword ptr [rsi], rax
	jmp	$_426

$_419:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_001
	jmp	$_427

	jmp	$_426

$_420:	cmp	dword ptr [rsi+0x3C], 0
	jnz	$_421
	cmp	dword ptr [rdi+0x3C], 0
	je	$_396
$_421:	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_422
	cmp	dword ptr [rdi+0x3C], 3
	je	$_397
$_422:	cmp	dword ptr [rsi+0x3C], 1
	jnz	$_423
	cmp	dword ptr [rdi+0x3C], 0
	je	$_398
$_423:	cmp	dword ptr [rsi+0x3C], 1
	jnz	$_424
	cmp	dword ptr [rdi+0x3C], 1
	je	$_399
$_424:	cmp	dword ptr [rsi+0x3C], 2
	jnz	$_425
	cmp	dword ptr [rdi+0x3C], 0
	jz	$_417
$_425:	jmp	$_419

$_426:	xor	eax, eax
$_427:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_428:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	test	byte ptr [rcx+0x43], 0x10
	jz	$_429
	mov	dword ptr [rcx+0x3C], -1
	xor	eax, eax
	jmp	$_430

$_429:	mov	ecx, 2166
	call	qword ptr [fnasmerr+rip]
$_430:	leave
	ret

$_431:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, rdx
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_362
	cmp	eax, -1
	jnz	$_432
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_468

$_432:	cmp	dword ptr [rsi+0x3C], 2
	jnz	$_433
	mov	dword ptr [rsi+0x3C], 1
$_433:	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_434
	mov	dword ptr [rdi+0x3C], 1
$_434:	mov	rax, qword ptr [rdi+0x50]
	test	rax, rax
	jz	$_436
	cmp	byte ptr [rax+0x18], 0
	jnz	$_436
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_436
	mov	rax, qword ptr [nullstruct+rip]
	test	rax, rax
	jnz	$_435
	xor	r8d, r8d
	lea	rdx, [DS0001+0x2+rip]
	xor	ecx, ecx
	call	CreateTypeSymbol@PLT
	mov	qword ptr [nullstruct+rip], rax
$_435:	mov	qword ptr [rdi+0x60], rax
	or	byte ptr [rdi+0x43], 0x08
	mov	qword ptr [rdi+0x50], 0
	mov	dword ptr [rdi+0x3C], 0
$_436:	cmp	dword ptr [rsi+0x3C], 1
	jne	$_444
	cmp	dword ptr [rdi+0x3C], 1
	jne	$_444
	cmp	qword ptr [rdi+0x58], 0
	jnz	$_437
	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jnz	$_437
	mov	rcx, rsi
	call	$_428
	jmp	$_468

$_437:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_326
	cmp	eax, -1
	jnz	$_438
	jmp	$_468

$_438:	mov	rax, qword ptr [rdi+0x50]
	test	rax, rax
	jz	$_440
	mov	rbx, qword ptr [rsi+0x50]
	test	rbx, rbx
	jz	$_439
	cmp	byte ptr [rbx+0x18], 0
	jz	$_439
	cmp	byte ptr [rax+0x18], 0
	jz	$_439
	mov	ecx, 2101
	call	qword ptr [fnasmerr+rip]
	jmp	$_468

$_439:	mov	rax, qword ptr [rdi+0x28]
	mov	qword ptr [rsi+0x28], rax
	mov	rax, qword ptr [rdi+0x50]
	mov	qword ptr [rsi+0x50], rax
$_440:	mov	rax, qword ptr [rdi+0x58]
	test	rax, rax
	jz	$_441
	mov	qword ptr [rsi+0x58], rax
$_441:	mov	eax, dword ptr [rdi]
	add	dword ptr [rsi], eax
	test	byte ptr [rsi+0x43], 0x02
	jnz	$_442
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
$_442:	mov	rax, qword ptr [rdi+0x60]
	test	rax, rax
	jz	$_443
	mov	qword ptr [rsi+0x60], rax
$_443:	jmp	$_467

$_444:	cmp	dword ptr [rsi+0x3C], 0
	jne	$_450
	cmp	dword ptr [rdi+0x3C], 1
	jne	$_450
	test	byte ptr [rsi+0x43], 0x08
	jz	$_445
	cmp	qword ptr [rsi+0x60], 0
	jz	$_445
	and	byte ptr [rdi+0x43], 0xFFFFFFBF
	mov	dword ptr [rsi], 0
	mov	dword ptr [rsi+0x4], 0
$_445:	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jnz	$_446
	test	byte ptr [rsi+0x43], 0x08
	jnz	$_446
	cmp	qword ptr [rsi+0x58], 0
	jnz	$_446
	mov	rcx, rsi
	call	$_428
	jmp	$_468

$_446:	mov	rax, qword ptr [rsi+0x58]
	test	rax, rax
	jz	$_447
	cmp	byte ptr [rax+0x18], 7
	jnz	$_447
	mov	eax, dword ptr [rax+0x28]
	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], 0
$_447:	test	byte ptr [rsi+0x43], 0x01
	jz	$_448
	or	byte ptr [rdi+0x43], 0x01
$_448:	mov	rax, qword ptr [rsi]
	add	qword ptr [rdi], rax
	cmp	qword ptr [rdi+0x58], 0
	jz	$_449
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
$_449:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	jmp	$_467

$_450:	cmp	dword ptr [rsi+0x3C], 1
	jne	$_457
	cmp	dword ptr [rdi+0x3C], 0
	jne	$_457
	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jnz	$_452
	cmp	qword ptr [rdi+0x60], 0
	jz	$_451
	test	byte ptr [rdi+0x43], 0x08
	jnz	$_452
$_451:	cmp	qword ptr [rdi+0x58], 0
	jnz	$_452
	mov	rcx, rsi
	call	$_428
	jmp	$_468

$_452:	test	byte ptr [rdi+0x43], 0x08
	jz	$_453
	cmp	qword ptr [rdi+0x60], 0
	jz	$_453
	and	byte ptr [rsi+0x43], 0xFFFFFFBF
	mov	rbx, qword ptr [rdi+0x60]
	mov	eax, dword ptr [rbx+0x50]
	sub	dword ptr [rdi], eax
	sbb	dword ptr [rdi+0x4], 0
$_453:	mov	rbx, qword ptr [rdi+0x58]
	test	rbx, rbx
	jz	$_454
	cmp	byte ptr [rbx+0x18], 7
	jnz	$_454
	mov	eax, dword ptr [rbx+0x28]
	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], 0
$_454:	mov	rax, qword ptr [rdi]
	add	qword ptr [rsi], rax
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	test	rbx, rbx
	jz	$_456
	mov	qword ptr [rsi+0x58], rbx
	test	rax, rax
	jz	$_456
	test	byte ptr [rdi+0x43], 0xFFFFFF80
	jz	$_456
	test	byte ptr [rsi+0x43], 0x02
	jz	$_455
	cmp	byte ptr [rdi+0x41], -128
	jnz	$_455
	mov	qword ptr [rsi+0x60], 0
	jmp	$_456

$_455:	or	byte ptr [rsi+0x43], 0xFFFFFF80
$_456:	jmp	$_467

$_457:	cmp	dword ptr [rsi+0x3C], 0
	jne	$_466
	cmp	dword ptr [rdi+0x3C], 0
	jne	$_466
	cmp	qword ptr [rdi+0x58], 0
	jnz	$_458
	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jnz	$_458
	mov	rcx, rsi
	call	$_428
	jmp	$_468

$_458:	cmp	qword ptr [rsi+0x60], 0
	jz	$_464
	cmp	qword ptr [rsi+0x58], 0
	jz	$_459
	mov	rax, qword ptr [rdi]
	add	qword ptr [rsi], rax
	jmp	$_460

$_459:	mov	rax, qword ptr [rdi]
	mov	qword ptr [rsi], rax
$_460:	mov	rax, qword ptr [rdi+0x58]
	mov	qword ptr [rsi+0x58], rax
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
	and	byte ptr [rsi+0x43], 0xFFFFFFF7
	test	byte ptr [rdi+0x43], 0x08
	jz	$_461
	or	byte ptr [rsi+0x43], 0x08
$_461:	mov	rax, qword ptr [rdi+0x60]
	cmp	qword ptr [rsi+0x60], rax
	jz	$_462
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	jmp	$_463

$_462:	mov	qword ptr [rsi+0x60], 0
$_463:	jmp	$_465

$_464:	mov	rax, qword ptr [rdi]
	add	qword ptr [rsi], rax
	mov	rax, qword ptr [rdi+0x58]
	mov	qword ptr [rsi+0x58], rax
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
$_465:	jmp	$_467

$_466:	mov	rcx, rsi
	call	$_428
	jmp	$_468

$_467:	xor	eax, eax
$_468:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_469:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, rdx
	mov	rax, qword ptr [rdi+0x30]
	test	rax, rax
	jz	$_472
	cmp	dword ptr [rsi+0x3C], 2
	jnz	$_470
	cmp	byte ptr [rax], 2
	jz	$_471
$_470:	cmp	dword ptr [rsi+0x3C], 1
	jnz	$_472
	cmp	byte ptr [rax], 8
	jnz	$_472
$_471:	mov	ecx, 3013
	call	qword ptr [fnasmerr+rip]
	jmp	$_493

$_472:	jmp	$_476

$_473:	test	byte ptr [rdi+0x43], 0x01
	jnz	$_474
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_493

$_474:	jmp	$_477

$_475:	mov	ecx, 2050
	call	qword ptr [fnasmerr+rip]
	jmp	$_493

	jmp	$_477

$_476:	cmp	dword ptr [rdi+0x3C], 2
	jz	$_473
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_475
$_477:	cmp	dword ptr [rsi+0x3C], 2
	jne	$_484
	cmp	qword ptr [rsi+0x20], 0
	jz	$_478
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_493

$_478:	mov	rax, qword ptr [rsi+0x18]
	imul	eax, dword ptr [rax+0x4], 12
	lea	rbx, [SpecialTable+rip]
	test	byte ptr [rbx+rax+0x3], 0x0C
	jnz	$_479
	mov	ecx, 2096
	call	qword ptr [fnasmerr+rip]
	jmp	$_493

$_479:	mov	rax, qword ptr [rsi+0x18]
	mov	qword ptr [rdi+0x30], rax
	test	byte ptr [rsi+0x43], 0x01
	jz	$_480
	or	byte ptr [rdi+0x43], 0x01
$_480:	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_481
	mov	dword ptr [rdi+0x3C], 1
$_481:	test	byte ptr [rsi+0x43], 0x02
	jz	$_482
	or	byte ptr [rdi+0x43], 0x02
	mov	al, byte ptr [rsi+0x40]
	mov	byte ptr [rdi+0x40], al
	mov	al, byte ptr [rsi+0x42]
	mov	byte ptr [rdi+0x42], al
$_482:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	cmp	qword ptr [rdi+0x60], 0
	jz	$_483
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
$_483:	jmp	$_492

$_484:	cmp	dword ptr [rsi+0x3C], 1
	jne	$_491
	cmp	qword ptr [rsi+0x30], 0
	jne	$_491
	cmp	dword ptr [rsi+0x38], -2
	jne	$_491
	cmp	dword ptr [rsi], 0
	jne	$_491
	cmp	qword ptr [rsi+0x50], 0
	je	$_491
	cmp	qword ptr [rsi+0x18], 0
	jnz	$_491
	cmp	qword ptr [rsi+0x20], 0
	jnz	$_491
	mov	rax, qword ptr [rsi+0x50]
	cmp	byte ptr [rax+0x18], 4
	jz	$_485
	cmp	byte ptr [rax+0x18], 3
	jnz	$_488
$_485:	mov	dword ptr [rdi+0x3C], 1
	mov	rax, qword ptr [rsi+0x28]
	mov	qword ptr [rdi+0x30], rax
	test	byte ptr [rsi+0x43], 0x01
	jz	$_486
	or	byte ptr [rdi+0x43], 0x01
$_486:	test	byte ptr [rsi+0x43], 0x02
	jz	$_487
	or	byte ptr [rdi+0x43], 0x02
	mov	al, byte ptr [rsi+0x40]
	mov	byte ptr [rdi+0x40], al
	mov	al, byte ptr [rsi+0x42]
	mov	byte ptr [rdi+0x42], al
$_487:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	jmp	$_490

$_488:	cmp	dword ptr [Parse_Pass+rip], 0
	ja	$_489
	cmp	byte ptr [rax+0x18], 0
	jz	$_490
$_489:	mov	ecx, 2096
	call	qword ptr [fnasmerr+rip]
	jmp	$_493

$_490:	jmp	$_492

$_491:	mov	ecx, 2096
	call	qword ptr [fnasmerr+rip]
	jmp	$_493

$_492:	xor	eax, eax
$_493:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_494:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	mov	rdi, rdx
	mov	rcx, rdi
	call	$_343
	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_495
	mov	dword ptr [rsi+0x3C], 0
	mov	rax, qword ptr [rdi]
	mov	qword ptr [rsi], rax
	mov	rax, qword ptr [rdi+0x8]
	mov	qword ptr [rsi+0x8], rax
	jmp	$_497

$_495:	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_496
	mov	dword ptr [rsi+0x3C], 3
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
	mov	rax, qword ptr [rdi]
	mov	qword ptr [rsi], rax
	mov	rax, qword ptr [rdi+0x8]
	mov	qword ptr [rsi+0x8], rax
	and	byte ptr [rsi+0xF], 0x7F
	mov	al, byte ptr [rdi+0x43]
	mov	byte ptr [rsi+0x43], al
	jmp	$_497

$_496:	mov	ecx, 2026
	call	qword ptr [fnasmerr+rip]
	jmp	$_498

$_497:	xor	eax, eax
$_498:	leave
	pop	rdi
	pop	rsi
	ret

$_499:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rdi, rdx
	mov	rcx, rdi
	call	$_343
	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_501
	mov	al, byte ptr [rdi+0x43]
	mov	byte ptr [rsi+0x43], al
	xor	byte ptr [rsi+0x43], 0x20
	mov	dword ptr [rsi+0x3C], 0
	mov	rax, qword ptr [rdi]
	mov	rdx, qword ptr [rdi+0x8]
	neg	rax
	mov	qword ptr [rsi], rax
	sbb	eax, eax
	test	rdx, rdx
	jz	$_500
	bt	eax, 0
	adc	rdx, 0
	neg	rdx
	mov	qword ptr [rsi+0x8], rdx
$_500:	jmp	$_503

$_501:	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_502
	mov	dword ptr [rsi+0x3C], 3
	mov	al, byte ptr [rdi+0x40]
	mov	byte ptr [rsi+0x40], al
	mov	rax, qword ptr [rdi]
	mov	qword ptr [rsi], rax
	mov	rax, qword ptr [rdi+0x8]
	mov	qword ptr [rsi+0x8], rax
	xor	byte ptr [rsi+0xF], 0xFFFFFF80
	mov	al, byte ptr [rdi+0x43]
	mov	byte ptr [rsi+0x43], al
	xor	byte ptr [rsi+0x43], 0x20
	jmp	$_503

$_502:	mov	ecx, 2026
	call	qword ptr [fnasmerr+rip]
	jmp	$_504

$_503:	xor	eax, eax
$_504:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_505:
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	test	byte ptr [rsi+0x43], 0x02
	jz	$_506
	mov	rbx, qword ptr [rsi+0x60]
	test	rbx, rbx
	jz	$_506
	cmp	byte ptr [rbx+0x19], -61
	jnz	$_506
	cmp	byte ptr [rbx+0x39], 1
	jnz	$_506
	mov	al, byte ptr [rbx+0x3A]
	mov	byte ptr [rsi+0x40], al
	mov	rax, qword ptr [rbx+0x40]
	mov	qword ptr [rsi+0x60], rax
	jmp	$_511

$_506:	xor	ebx, ebx
	cmp	qword ptr [rsi+0x20], 0
	jz	$_507
	mov	rax, qword ptr [rsi+0x20]
	movzx	eax, byte ptr [rax+0x1]
	call	GetStdAssumeEx_@PLT
	mov	rbx, rax
$_507:	test	rbx, rbx
	jnz	$_508
	cmp	qword ptr [rsi+0x18], 0
	jz	$_508
	mov	rax, qword ptr [rsi+0x18]
	movzx	eax, byte ptr [rax+0x1]
	call	GetStdAssumeEx_@PLT
	mov	rbx, rax
$_508:	test	rbx, rbx
	jz	$_511
	cmp	byte ptr [rbx+0x19], -60
	jnz	$_509
	mov	rax, qword ptr [rbx+0x20]
	mov	qword ptr [rsi+0x60], rax
	jmp	$_511

$_509:	cmp	byte ptr [rbx+0x39], 1
	jnz	$_511
	mov	rax, qword ptr [rbx+0x40]
	mov	qword ptr [rsi+0x60], rax
	cmp	qword ptr [rbx+0x40], 0
	jz	$_510
	mov	rbx, qword ptr [rbx+0x40]
	mov	al, byte ptr [rbx+0x19]
	mov	byte ptr [rsi+0x40], al
	jmp	$_511

$_510:	mov	al, byte ptr [rbx+0x3A]
	mov	byte ptr [rsi+0x40], al
$_511:	leave
	pop	rbx
	pop	rsi
	ret

$_512:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [rcx+0x41], 0
	jbe	$_513
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_515

$_513:	inc	byte ptr [rcx+0x41]
	cmp	dword ptr [rdx+0x3C], 0
	jz	$_514
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_515

$_514:	mov	eax, dword ptr [rdx]
	mov	dword ptr [rcx], eax
	xor	eax, eax
$_515:	leave
	ret

$_516:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, qword ptr [rcx+0x60]
	mov	rdi, qword ptr [rdx+0x60]
	cmp	byte ptr [rcx+0x40], -61
	jnz	$_521
	cmp	byte ptr [rdx+0x40], -61
	jnz	$_521
	mov	rbx, rcx
	test	rsi, rsi
	jnz	$_517
	mov	rax, qword ptr [rcx+0x28]
	mov	rcx, qword ptr [rax+0x8]
	call	SymFind@PLT
	mov	rsi, rax
	mov	rdx, qword ptr [rbp+0x30]
$_517:	test	rdi, rdi
	jnz	$_518
	mov	rax, qword ptr [rdx+0x28]
	mov	rcx, qword ptr [rax+0x8]
	call	SymFind@PLT
	mov	rdi, rax
$_518:	mov	al, byte ptr [rdi+0x39]
	cmp	byte ptr [rsi+0x39], al
	jnz	$_519
	mov	al, byte ptr [rdi+0x3A]
	cmp	byte ptr [rsi+0x3A], al
	jnz	$_519
	mov	rax, qword ptr [rdi+0x40]
	cmp	qword ptr [rsi+0x40], rax
	jnz	$_519
	mov	eax, dword ptr [rbp+0x38]
	jmp	$_520

$_519:	mov	eax, dword ptr [rbp+0x38]
	not	eax
$_520:	cdq
	mov	rcx, rbx
	mov	dword ptr [rcx], eax
	mov	dword ptr [rcx+0x4], edx
	jmp	$_526

$_521:	test	rsi, rsi
	jz	$_522
	cmp	word ptr [rsi+0x5A], 3
	jnz	$_522
	cmp	byte ptr [rsi+0x39], 0
	jnz	$_522
	mov	qword ptr [rcx+0x60], 0
$_522:	test	rdi, rdi
	jz	$_523
	cmp	word ptr [rdi+0x5A], 3
	jnz	$_523
	cmp	byte ptr [rdi+0x39], 0
	jnz	$_523
	mov	qword ptr [rdx+0x60], 0
$_523:	mov	al, byte ptr [rdx+0x40]
	cmp	byte ptr [rcx+0x40], al
	jnz	$_524
	mov	rax, qword ptr [rdx+0x60]
	cmp	qword ptr [rcx+0x60], rax
	jnz	$_524
	mov	eax, dword ptr [rbp+0x38]
	jmp	$_525

$_524:	mov	eax, dword ptr [rbp+0x38]
	not	eax
$_525:	cdq
	mov	dword ptr [rcx], eax
	mov	dword ptr [rcx+0x4], edx
$_526:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_527:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	mov	rsi, rcx
	mov	rdi, rdx
	mov	rbx, r8
	mov	qword ptr [rsi+0x10], 0
	cmp	dword ptr [rdi+0x8], 0
	jnz	$_528
	cmp	dword ptr [rdi+0xC], 0
	jz	$_532
$_528:	cmp	byte ptr [rdi+0x40], 47
	jz	$_532
	cmp	byte ptr [rbx], 4
	jnz	$_529
	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_529
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jz	$_532
$_529:	test	byte ptr [rdi+0x43], 0x10
	jnz	$_532
	cmp	byte ptr [rbx], 43
	jz	$_530
	cmp	byte ptr [rbx], 45
	jnz	$_531
$_530:	cmp	byte ptr [rbx+0x1], 0
	jz	$_532
$_531:	mov	ecx, 2084
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_532:	movzx	eax, byte ptr [rbx]
	jmp	$_673

$_533:	test	byte ptr [rdi+0x43], 0x40
	jz	$_534
	and	byte ptr [rdi+0x43], 0xFFFFFFBF
	cmp	qword ptr [rsi+0x50], 0
	jnz	$_534
	mov	rcx, rdi
	call	$_505
$_534:	cmp	dword ptr [rsi+0x3C], -2
	jnz	$_536
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	test	byte ptr [rsi+0x43], 0x08
	jz	$_535
	cmp	dword ptr [rsi+0x3C], 0
	jnz	$_535
	and	byte ptr [rsi+0x43], 0xFFFFFFF7
$_535:	jmp	$_674

$_536:	test	byte ptr [rsi+0x43], 0x08
	jz	$_538
	cmp	qword ptr [rsi+0x60], 0
	jnz	$_538
	cmp	dword ptr [rdi+0x3C], 1
	jz	$_537
	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_538
$_537:	mov	ecx, 2009
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_538:	mov	rax, qword ptr [rsi+0x18]
	test	rax, rax
	jz	$_539
	cmp	dword ptr [rax+0x4], 31
	jnz	$_539
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_512
	jmp	$_675

$_539:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_367
	jmp	$_675

$_540:	cmp	dword ptr [rsi+0x3C], -2
	jnz	$_541
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rsi+0x60], rax
	jmp	$_674

$_541:	test	byte ptr [rsi+0x43], 0x08
	jz	$_542
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_542
	mov	ecx, 2009
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_542:	mov	rax, qword ptr [rsi+0x18]
	cmp	qword ptr [rsi+0x18], 0
	jz	$_543
	cmp	dword ptr [rax+0x4], 31
	jnz	$_543
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_512
	jmp	$_675

$_543:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_367
	jmp	$_675

$_544:	cmp	byte ptr [rbx+0x1], 0
	jnz	$_545
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_494
	jmp	$_675

$_545:	mov	r8, rbx
	mov	rdx, rdi
	mov	rcx, rsi
	call	EvalOperator@PLT
	cmp	eax, -1
	jnz	$_546
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_367
	jmp	$_675

$_546:	jmp	$_674

$_547:	cmp	byte ptr [rbx+0x1], 0
	jnz	$_548
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_499
	jmp	$_675

$_548:	mov	r8, rbx
	mov	rdx, rdi
	mov	rcx, rsi
	call	EvalOperator@PLT
	cmp	eax, -1
	jnz	$_549
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_392
	jmp	$_675

$_549:	jmp	$_674

$_550:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_431
	jmp	$_675

$_551:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_469
	jmp	$_675

$_552:	mov	rcx, rsi
	call	$_343
	mov	rcx, rdi
	call	$_343
	cmp	dword ptr [rsi+0x3C], 0
	jnz	$_553
	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_553
	mov	rdx, qword ptr [rsi]
	mov	rax, qword ptr [rdi]
	mul	rdx
	mov	qword ptr [rsi], rax
	jmp	$_561

$_553:	xor	r9d, r9d
	mov	r8d, 2
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_322
	test	rax, rax
	jz	$_559
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_362
	cmp	eax, -1
	jnz	$_554
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_554:	cmp	dword ptr [rdi+0x3C], 2
	jnz	$_555
	mov	rax, qword ptr [rdi+0x18]
	mov	qword ptr [rsi+0x20], rax
	jmp	$_556

$_555:	mov	rax, qword ptr [rsi+0x18]
	mov	qword ptr [rsi+0x20], rax
	mov	eax, dword ptr [rdi]
	mov	dword ptr [rsi], eax
$_556:	cmp	dword ptr [rsi], 0
	jle	$_557
	cmp	dword ptr [rsi], 127
	jle	$_558
$_557:	mov	ecx, 2083
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_558:	mov	eax, dword ptr [rsi]
	mov	byte ptr [rsi+0x41], al
	mov	dword ptr [rsi], 0
	mov	qword ptr [rsi+0x18], 0
	or	byte ptr [rsi+0x43], 0x01
	mov	dword ptr [rsi+0x3C], 1
	jmp	$_561

$_559:	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_560
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_560
	mov	rdx, rdi
	mov	rcx, rsi
	call	__mulq@PLT
	jmp	$_561

$_560:	mov	r8, rbx
	mov	rdx, rdi
	mov	rcx, rsi
	call	EvalOperator@PLT
	cmp	eax, -1
	jnz	$_561
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_001
	jmp	$_675

$_561:	jmp	$_674

$_562:	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_563
	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_563
	mov	rdx, rdi
	mov	rcx, rsi
	call	__divq@PLT
	jmp	$_674

$_563:	mov	r8, rbx
	mov	rdx, rdi
	mov	rcx, rsi
	call	EvalOperator@PLT
	cmp	eax, -1
	jne	$_674
	mov	rcx, rsi
	call	$_343
	mov	rcx, rdi
	call	$_343
	cmp	dword ptr [rsi+0x3C], 0
	jnz	$_564
	cmp	dword ptr [rdi+0x3C], 0
	jz	$_565
$_564:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_001
	jmp	$_675

$_565:	cmp	dword ptr [rdi], 0
	jnz	$_566
	cmp	dword ptr [rdi+0x4], 0
	jnz	$_566
	mov	ecx, 2169
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_566:	mov	rdx, qword ptr [rdi]
	mov	rax, qword ptr [rsi]
	call	__div64_@PLT
	mov	qword ptr [rsi], rax
	jmp	$_674

$_567:	cmp	dword ptr [rbx+0x4], 270
	jne	$_581
	test	byte ptr [rsi+0x43], 0x08
	jnz	$_569
	mov	rax, qword ptr [rsi+0x50]
	test	rax, rax
	jz	$_568
	cmp	byte ptr [rax+0x18], 0
	jnz	$_568
	mov	r8d, 1
	xor	edx, edx
	mov	rcx, rax
	call	CreateTypeSymbol@PLT
	mov	rax, qword ptr [rsi+0x50]
	mov	qword ptr [rsi+0x60], rax
	mov	qword ptr [rsi+0x50], 0
	or	byte ptr [rsi+0x43], 0x08
	jmp	$_569

$_568:	mov	ecx, 2010
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_569:	or	byte ptr [rdi+0x43], 0x02
	cmp	dword ptr [rdi+0x3C], 2
	jne	$_576
	test	byte ptr [rdi+0x43], 0x01
	jz	$_570
	test	byte ptr [rdi+0x43], 0x40
	jz	$_576
$_570:	mov	rax, qword ptr [rdi+0x18]
	mov	ecx, dword ptr [rax+0x4]
	imul	eax, ecx, 12
	lea	rdx, [SpecialTable+rip]
	add	rdx, rax
	test	byte ptr [rdx+0x3], 0x0C
	jz	$_572
	cmp	dword ptr [rsi], 2
	jz	$_571
	cmp	dword ptr [rsi], 4
	jz	$_571
	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_571:	jmp	$_575

$_572:	mov	eax, dword ptr [rdx+0x4]
	and	eax, 0x7F
	jnz	$_573
	mov	eax, 4
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_573
	mov	eax, 8
$_573:	cmp	eax, dword ptr [rsi]
	jz	$_575
	cmp	eax, 16
	jnz	$_574
	cmp	byte ptr [rsi+0x40], 35
	jz	$_575
	cmp	byte ptr [rsi+0x40], 39
	jz	$_575
$_574:	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_575:	jmp	$_577

$_576:	cmp	dword ptr [rdi+0x3C], 3
	jnz	$_577
	test	byte ptr [rsi+0x40], 0x20
	jnz	$_577
	mov	ecx, 2050
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_577:	mov	al, byte ptr [rsi+0x40]
	mov	byte ptr [rdi+0x40], al
	mov	al, byte ptr [rsi+0x42]
	mov	byte ptr [rdi+0x42], al
	test	byte ptr [rdi+0x43], 0x08
	jz	$_578
	mov	eax, dword ptr [rsi]
	mov	dword ptr [rdi], eax
$_578:	cmp	qword ptr [rsi+0x30], 0
	jz	$_580
	cmp	qword ptr [rdi+0x30], 0
	jnz	$_579
	mov	rax, qword ptr [rsi+0x30]
	mov	qword ptr [rdi+0x30], rax
$_579:	mov	dword ptr [rdi+0x3C], 1
$_580:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	jmp	$_674

$_581:	mov	rcx, rsi
	call	$_343
	mov	rcx, rdi
	call	$_343
	cmp	dword ptr [rsi+0x3C], 0
	jnz	$_582
	cmp	dword ptr [rdi+0x3C], 0
	jz	$_584
$_582:	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_583
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_584
$_583:	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_585
	cmp	dword ptr [rdi+0x3C], 0
	jnz	$_585
$_584:	jmp	$_591

$_585:	cmp	byte ptr [rbx+0x1], 10
	jnz	$_590
	cmp	dword ptr [rsi+0x3C], 0
	jz	$_590
	cmp	dword ptr [rsi+0x3C], 1
	jnz	$_588
	test	byte ptr [rsi+0x43], 0x01
	jnz	$_588
	cmp	qword ptr [rsi+0x50], 0
	jz	$_588
	cmp	dword ptr [rdi+0x3C], 1
	jnz	$_586
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_586
	cmp	qword ptr [rdi+0x50], 0
	jz	$_586
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_354
	cmp	eax, -1
	je	$_675
	jmp	$_587

$_586:	mov	ecx, 2094
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_587:	jmp	$_589

$_588:	mov	ecx, 2095
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_589:	jmp	$_591

$_590:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_001
	jmp	$_675

$_591:	mov	eax, dword ptr [rbx+0x4]
	jmp	$_631
$C02FA:
	test	byte ptr [rsi+0x43], 0x08
	jz	$_592
	test	byte ptr [rdi+0x43], 0x08
	jz	$_592
	mov	r8d, 4294967295
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_516
	jmp	$_595

$_592:	xor	eax, eax
	xor	edx, edx
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_593
	mov	dword ptr [rsi+0x3C], 0
	mov	byte ptr [rsi+0x40], -64
	add	rdx, qword ptr [rsi+0x8]
	sub	rdx, qword ptr [rdi+0x8]
	mov	qword ptr [rsi+0x8], rax
$_593:	add	rdx, qword ptr [rsi]
	sub	rdx, qword ptr [rdi]
	jnz	$_594
	dec	rax
$_594:	mov	qword ptr [rsi], rax
$_595:	jmp	$C02FF
$C0300:
	test	byte ptr [rsi+0x43], 0x08
	jz	$_596
	test	byte ptr [rdi+0x43], 0x08
	jz	$_596
	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, rsi
	call	$_516
	jmp	$_599

$_596:	xor	eax, eax
	xor	edx, edx
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_597
	add	rdx, qword ptr [rsi+0x8]
	sub	rdx, qword ptr [rdi+0x8]
	mov	qword ptr [rsi+0x8], rax
	mov	dword ptr [rsi+0x3C], 0
	mov	byte ptr [rsi+0x40], -64
$_597:	add	rdx, qword ptr [rsi]
	sub	rdx, qword ptr [rdi]
	jz	$_598
	dec	rax
$_598:	mov	qword ptr [rsi], rax
$_599:	jmp	$C02FF
$C0305:
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_601
	mov	rdx, rdi
	mov	rcx, rsi
	call	__cmpq@PLT
	xor	ecx, ecx
	mov	dword ptr [rsi+0x3C], 0
	mov	byte ptr [rsi+0x40], -64
	mov	qword ptr [rsi+0x8], rcx
	cmp	eax, -1
	jnz	$_600
	dec	rcx
$_600:	jmp	$_602

$_601:	xor	ecx, ecx
	mov	rax, qword ptr [rdi]
	cmp	qword ptr [rsi], rax
	jge	$_602
	dec	rcx
$_602:	mov	qword ptr [rsi], rcx
	jmp	$C02FF
$C030A:
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_604
	mov	rdx, rdi
	mov	rcx, rsi
	call	__cmpq@PLT
	xor	ecx, ecx
	mov	qword ptr [rsi+0x8], rcx
	mov	dword ptr [rsi+0x3C], 0
	mov	byte ptr [rsi+0x40], -64
	cmp	eax, 1
	jz	$_603
	dec	rcx
$_603:	jmp	$_605

$_604:	xor	ecx, ecx
	mov	rax, qword ptr [rdi]
	cmp	qword ptr [rsi], rax
	jg	$_605
	dec	rcx
$_605:	mov	qword ptr [rsi], rcx
	jmp	$C02FF
$C030F:
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_607
	mov	rdx, rdi
	mov	rcx, rsi
	call	__cmpq@PLT
	xor	ecx, ecx
	mov	qword ptr [rsi+0x8], rcx
	mov	dword ptr [rsi+0x3C], 0
	mov	byte ptr [rsi+0x40], -64
	cmp	eax, 1
	jnz	$_606
	dec	rcx
$_606:	jmp	$_608

$_607:	xor	ecx, ecx
	mov	rax, qword ptr [rdi]
	cmp	qword ptr [rsi], rax
	jle	$_608
	dec	rcx
$_608:	mov	qword ptr [rsi], rcx
	jmp	$C02FF
$C0314:
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_610
	mov	rdx, rdi
	mov	rcx, rsi
	call	__cmpq@PLT
	xor	ecx, ecx
	mov	qword ptr [rsi+0x8], rcx
	mov	dword ptr [rsi+0x3C], 0
	mov	byte ptr [rsi+0x40], -64
	cmp	eax, -1
	jz	$_609
	dec	rcx
$_609:	jmp	$_611

$_610:	xor	ecx, ecx
	mov	rax, qword ptr [rdi]
	cmp	qword ptr [rsi], rax
	jl	$_611
	dec	rcx
$_611:	mov	qword ptr [rsi], rcx
	jmp	$C02FF
$C0319:
	cmp	dword ptr [rdi], 0
	jnz	$_612
	cmp	dword ptr [rdi+0x4], 0
	jnz	$_612
	mov	ecx, 2169
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_612:	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_613
	lea	r8, [rbp-0x70]
	mov	rdx, rdi
	mov	rcx, rsi
	call	__divo@PLT
	mov	rax, qword ptr [rbp-0x70]
	mov	qword ptr [rsi], rax
	mov	rax, qword ptr [rbp-0x68]
	mov	qword ptr [rsi+0x8], rax
	jmp	$C02FF

$_613:	mov	rdx, qword ptr [rdi]
	mov	rax, qword ptr [rsi]
	call	__rem64_@PLT
	mov	qword ptr [rsi], rax
	jmp	$C02FF
$C031C:
	cmp	dword ptr [rdi], 0
	jge	$_614
	mov	ecx, 2092
	call	qword ptr [fnasmerr+rip]
	jmp	$C02FF
$_614:	mov	eax, 64
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_615
	mov	eax, 128
	jmp	$_616
$_615:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 1
	jnz	$_616
	mov	eax, 32
$_616:	mov	r8d, eax
	mov	edx, dword ptr [rdi]
	mov	rcx, rsi
	call	__shlo@PLT
	cmp	byte ptr [ModuleInfo+0x1D6+rip], 0
	jz	$_617
	xor	eax, eax
	mov	dword ptr [rsi+0x4], eax
	mov	qword ptr [rsi+0x8], rax
$_617:	jmp	$C02FF
$C0323:
	cmp	dword ptr [rdi], 0
	jge	$_618
	mov	ecx, 2092
	call	qword ptr [fnasmerr+rip]
	jmp	$C02FF
$_618:	mov	eax, 64
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_619
	mov	eax, 128
	jmp	$_620
$_619:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 1
	jnz	$_620
	mov	eax, 32
$_620:	mov	r8d, eax
	mov	edx, dword ptr [rdi]
	mov	rcx, rsi
	call	__shro@PLT
	jmp	$C02FF
$C0328:
	cmp	dword ptr [rdi], 0
	jge	$_621
	mov	ecx, 2092
	call	qword ptr [fnasmerr+rip]
	jmp	$C02FF
$_621:	mov	eax, 64
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_622
	mov	eax, 128
	jmp	$_623
$_622:	cmp	byte ptr [ModuleInfo+0x1CC+rip], 1
	jnz	$_623
	mov	eax, 32
$_623:	mov	r8d, eax
	mov	edx, dword ptr [rdi]
	mov	rcx, rsi
	call	__saro@PLT
	jmp	$C02FF
$C032D:
	cmp	dword ptr [rsi+0x3C], 3
	jz	$_624
	mov	ecx, 2187
	call	qword ptr [fnasmerr+rip]
$_624:	mov	rax, qword ptr [rdi]
	add	qword ptr [rsi], rax
	mov	rax, qword ptr [rdi+0x8]
	adc	qword ptr [rsi+0x8], rax
	jmp	$C02FF
$C032F:
	cmp	dword ptr [rsi+0x3C], 3
	jz	$_625
	mov	ecx, 2187
	call	qword ptr [fnasmerr+rip]
$_625:	mov	rax, qword ptr [rdi+0x8]
	sub	qword ptr [rsi+0x8], rax
	mov	rax, qword ptr [rdi]
	sbb	qword ptr [rsi], rax
	jmp	$C02FF
$C0331:
	cmp	dword ptr [rsi+0x3C], 3
	jz	$_626
	mov	ecx, 2187
	call	qword ptr [fnasmerr+rip]
$_626:	xor	r8d, r8d
	mov	rdx, rdi
	mov	rcx, rsi
	call	__mulo@PLT
	jmp	$C02FF
$C0333:
	cmp	dword ptr [rsi+0x3C], 3
	jz	$_627
	mov	ecx, 2187
	call	qword ptr [fnasmerr+rip]
$_627:	lea	r8, [rbp-0x70]
	mov	rdx, rdi
	mov	rcx, rsi
	call	__divo@PLT
	jmp	$C02FF
$C0335:
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_628
	mov	rax, qword ptr [rdi+0x8]
	and	qword ptr [rsi+0x8], rax
$_628:	mov	rax, qword ptr [rdi]
	and	qword ptr [rsi], rax
	jmp	$C02FF
$C0337:
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_629
	mov	rax, qword ptr [rdi+0x8]
	or	qword ptr [rsi+0x8], rax
$_629:	mov	rax, qword ptr [rdi]
	or	qword ptr [rsi], rax
	jmp	$C02FF
$C0339:
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_630
	mov	rax, qword ptr [rdi+0x8]
	xor	qword ptr [rsi+0x8], rax
$_630:	mov	rax, qword ptr [rdi]
	xor	qword ptr [rsi], rax
	jmp	$C02FF

$_631:	cmp	rax, 581
	jl	$_632
	cmp	rax, 596
	jg	$_632
	push	rax
	lea	r11, [$C02FF+rip]
	movzx	eax, byte ptr [r11+rax-(581)+(IT$C033B-$C02FF)]
	movzx	eax, word ptr [r11+rax*2+($C033B-$C02FF)]
	sub	r11, rax
	pop	rax
	jmp	r11

	.ALIGN 2
$C033B:
	.word $C02FF-$C031C
	.word $C02FF-$C0323
	.word $C02FF-$C0328
	.word $C02FF-$C032D
	.word $C02FF-$C032F
	.word $C02FF-$C0335
	.word $C02FF-$C0337
	.word $C02FF-$C0339
	.word 0
IT$C033B:
	.byte 3
	.byte 6
	.byte 8
	.byte 8
	.byte 5
	.byte 4
	.byte 7
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 8
	.byte 0
	.byte 2
	.byte 0
	.byte 1
	.ALIGN 2
$C033C:

$_632:	cmp	rax, 263
	je	$C02FA
	cmp	rax, 264
	je	$C0300
	cmp	rax, 268
	je	$C0305
	cmp	rax, 267
	je	$C030A
	cmp	rax, 266
	je	$C030F
	cmp	rax, 265
	je	$C0314
	cmp	rax, 269
	je	$C0319
	cmp	rax, 655
	je	$C0331
	cmp	rax, 653
	je	$C0333
$C02FF: jmp	$_674

$_633:	cmp	dword ptr [rbx+0x4], 657
	jnz	$_636
	mov	rcx, rdi
	call	$_343
	cmp	dword ptr [rdi+0x3C], 0
	jz	$_634
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_634
	mov	ecx, 2026
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_634:	mov	rdx, rdi
	mov	rcx, rsi
	call	$_006
	not	qword ptr [rsi]
	cmp	dword ptr [rsi+0x3C], 3
	jnz	$_635
	not	qword ptr [rsi+0x8]
$_635:	jmp	$_674

$_636:	imul	eax, dword ptr [rbx+0x4], 12
	lea	rcx, [SpecialTable+rip]
	mov	ecx, dword ptr [rcx+rax]
	mov	rax, qword ptr [rdi+0x50]
	cmp	qword ptr [rdi+0x58], 0
	jz	$_637
	mov	rax, qword ptr [rdi+0x58]
$_637:	mov	qword ptr [rbp-0x8], rax
	mov	esi, ecx
	cmp	dword ptr [rdi+0x38], -2
	jz	$_638
	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	inc	eax
	add	rax, qword ptr [rbx+0x10]
	jmp	$_641

$_638:	test	rax, rax
	jz	$_639
	mov	rax, qword ptr [rax+0x8]
	jmp	$_641

$_639:	cmp	qword ptr [rdi+0x18], 0
	jz	$_640
	test	byte ptr [rdi+0x43], 0x01
	jnz	$_640
	mov	rax, qword ptr [rdi+0x18]
	mov	rax, qword ptr [rax+0x8]
	jmp	$_641

$_640:	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	inc	eax
	add	rax, qword ptr [rbx+0x10]
$_641:	mov	rdx, rax
	mov	ecx, esi
	mov	rsi, qword ptr [rbp+0x28]
	jmp	$_670

$_642:	mov	rax, qword ptr [rdi+0x58]
	test	rax, rax
	jz	$_646
	cmp	byte ptr [rax+0x18], 7
	jz	$_646
	cmp	byte ptr [rax+0x19], -63
	jnz	$_644
	test	ecx, 0x40
	jnz	$_643
	mov	r8, rdx
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	$_007
	jmp	$_675

$_643:	jmp	$_645

$_644:	test	ecx, 0x10
	jnz	$_645
	mov	r8, rdx
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	$_007
	jmp	$_675

$_645:	jmp	$_651

$_646:	test	byte ptr [rdi+0x43], 0x08
	jz	$_648
	test	ecx, 0x1
	jnz	$_647
	mov	r8, rdx
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	$_007
	jmp	$_675

$_647:	jmp	$_651

$_648:	test	ecx, 0x20
	jnz	$_651
	test	byte ptr [rdi+0x43], 0x10
	jz	$_649
	mov	rax, -1
	jmp	$_675

$_649:	cmp	ecx, 2
	jnz	$_650
	mov	ecx, 2094
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_650:	mov	ecx, 2009
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_651:	jmp	$_671

$_652:	test	byte ptr [rdi+0x43], 0x01
	jz	$_654
	cmp	qword ptr [rdi+0x50], 0
	jnz	$_654
	test	ecx, 0x4
	jnz	$_653
	mov	r8, rdx
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	$_007
	jmp	$_675

$_653:	jmp	$_658

$_654:	test	ecx, 0x2
	jnz	$_658
	test	byte ptr [rdi+0x43], 0x10
	jz	$_655
	mov	rax, -1
	jmp	$_675

$_655:	cmp	dword ptr [rbx+0x4], 238
	jnz	$_656
	cmp	byte ptr [rdi+0x43], 4
	jz	$_656
	mov	ecx, 2105
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_656:	cmp	byte ptr [rdi+0x43], 4
	jnz	$_657
	mov	ecx, 2026
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

	jmp	$_658

$_657:	mov	ecx, 2009
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_658:	jmp	$_671

$_659:	test	ecx, 0x8
	jne	$_667
	test	byte ptr [rdi+0x43], 0x10
	jne	$_666
	cmp	ecx, 2
	jnz	$_660
	mov	ecx, 2094
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_660:	cmp	ecx, 51
	jnz	$_662
	test	byte ptr [rdi+0x43], 0x01
	jz	$_661
	mov	ecx, 2098
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

	jmp	$_662

$_661:	mov	ecx, 2032
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_662:	test	ecx, 0x20
	jz	$_663
	mov	ecx, 2105
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_663:	test	byte ptr [rdi+0x43], 0x01
	jz	$_664
	mov	ecx, 2081
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

	jmp	$_665

$_664:	mov	ecx, 2009
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_665:	jmp	$_667

$_666:	mov	rax, -1
	jmp	$_675

$_667:	jmp	$_671

$_668:	test	ecx, 0x100
	jnz	$_669
	mov	ecx, 2050
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

$_669:	jmp	$_671

$_670:	cmp	dword ptr [rdi+0x3C], 0
	je	$_642
	cmp	dword ptr [rdi+0x3C], 1
	je	$_652
	cmp	dword ptr [rdi+0x3C], 2
	je	$_659
	cmp	dword ptr [rdi+0x3C], 3
	jz	$_668
$_671:	imul	eax, dword ptr [rbx+0x4], 12
	lea	rcx, [SpecialTable+rip]
	mov	ecx, dword ptr [rcx+rax+0x4]
	mov	qword ptr [rsp+0x28], rdx
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, qword ptr [rbp-0x8]
	mov	r8, rdi
	mov	rdx, rsi
	call	$_026
	jmp	$_675

$_672:	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	qword ptr [fnasmerr+rip]
	jmp	$_675

	jmp	$_674

$_673:	cmp	eax, 91
	je	$_533
	cmp	eax, 40
	je	$_540
	cmp	eax, 43
	je	$_544
	cmp	eax, 45
	je	$_547
	cmp	eax, 46
	je	$_550
	cmp	eax, 58
	je	$_551
	cmp	eax, 42
	je	$_552
	cmp	eax, 47
	je	$_562
	cmp	eax, 5
	je	$_567
	cmp	eax, 4
	je	$_633
	jmp	$_672

$_674:	xor	eax, eax
$_675:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_676:
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	and	byte ptr [rcx+0x43], 0xFFFFFFEF
	test	byte ptr [rdx+0x43], 0x10
	jz	$_677
	or	byte ptr [rcx+0x43], 0x10
$_677:	mov	rax, qword ptr [rbp+0x20]
	jmp	$_685

$_678:	mov	rax, qword ptr [rdx+0x50]
	cmp	qword ptr [rdx+0x60], 0
	jz	$_679
	mov	rax, qword ptr [rdx+0x60]
	mov	qword ptr [rcx+0x60], rax
	or	byte ptr [rcx+0x43], 0xFFFFFF80
	jmp	$_681

$_679:	cmp	byte ptr [ModuleInfo+0x1D8+rip], 0
	jnz	$_680
	test	rax, rax
	jz	$_680
	cmp	byte ptr [rax+0x18], 0
	jnz	$_680
	mov	qword ptr [rcx+0x60], 0
	or	byte ptr [rcx+0x43], 0xFFFFFF80
	jmp	$_681

$_680:	test	rax, rax
	jz	$_681
	cmp	byte ptr [rax+0x19], -61
	jnz	$_681
	cmp	byte ptr [rax+0x39], 0
	jz	$_681
	mov	rax, qword ptr [rax+0x40]
	mov	qword ptr [rcx+0x60], rax
	or	byte ptr [rcx+0x43], 0xFFFFFF80
$_681:	jmp	$_686

$_682:	cmp	dword ptr [rax+0x4], 250
	jz	$_683
	cmp	dword ptr [rax+0x4], 234
	jnz	$_684
$_683:	or	byte ptr [rcx+0x43], 0x10
$_684:	jmp	$_686

$_685:	cmp	byte ptr [rax], 46
	jz	$_678
	cmp	byte ptr [rax], 4
	jz	$_682
$_686:	leave
	ret

$_687:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	imul	eax, ecx, 24
	cmp	byte ptr [rdx+rax], 12
	ja	$_688
	mov	ecx, 2206
	call	qword ptr [fnasmerr+rip]
	jmp	$_689

$_688:	mov	rdx, qword ptr [rdx+rax+0x8]
	mov	ecx, 2008
	call	qword ptr [fnasmerr+rip]
$_689:	leave
	ret

$_690:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	dword ptr [rbp-0x4], 0
	mov	rdi, rcx
	imul	ebx, dword ptr [rdx], 24
	add	rbx, qword ptr [rbp+0x38]
	imul	eax, dword ptr [rbp+0x40], 24
	add	rax, qword ptr [rbp+0x38]
	mov	qword ptr [rbp-0x80], rax
	mov	al, byte ptr [rbx]
	cmp	dword ptr [rdi+0x3C], -2
	jnz	$_691
	cmp	al, 40
	jz	$_691
	cmp	al, 91
	jz	$_691
	cmp	al, 43
	jz	$_691
	cmp	al, 45
	jz	$_691
	cmp	al, 4
	jz	$_691
	movzx	r9d, byte ptr [rbp+0x48]
	mov	r8, qword ptr [rbp+0x38]
	mov	rcx, rdi
	call	$_205
	mov	dword ptr [rbp-0x4], eax
	mov	rax, qword ptr [rbp+0x30]
	imul	ebx, dword ptr [rax], 24
	add	rbx, qword ptr [rbp+0x38]
$_691:	jmp	$_725

$_692:	mov	rsi, rbx
	cmp	dword ptr [rdi+0x3C], -2
	jz	$_699
	mov	dl, byte ptr [rsi]
	cmp	dl, 43
	jz	$_693
	cmp	dl, 45
	jnz	$_694
$_693:	mov	byte ptr [rsi+0x1], 1
	jmp	$_699

$_694:	cmp	dl, 40
	jnc	$_695
	cmp	dl, 4
	jz	$_695
	cmp	dl, 5
	jnz	$_696
$_695:	cmp	dl, 4
	jnz	$_699
$_696:	cmp	dl, 9
	jnz	$_697
	cmp	byte ptr [rsi+0x1], 123
	jnz	$_697
	mov	rcx, rsi
	call	$_202
	mov	rdx, qword ptr [rbp+0x30]
	inc	dword ptr [rdx]
	add	rbx, 24
	jmp	$_725

	jmp	$_699

$_697:	mov	dword ptr [rbp-0x4], -1
	test	byte ptr [rdi+0x43], 0x10
	jnz	$_698
	sub	rsi, qword ptr [rbp+0x38]
	mov	ecx, 24
	xor	edx, edx
	mov	eax, esi
	div	ecx
	mov	rdx, qword ptr [rbp+0x38]
	mov	ecx, eax
	call	$_687
$_698:	jmp	$_726

$_699:	mov	rdx, qword ptr [rbp+0x30]
	inc	dword ptr [rdx]
	add	rbx, 24
	lea	rcx, [rbp-0x70]
	call	$_181
	mov	r8, rsi
	mov	rdx, rdi
	lea	rcx, [rbp-0x70]
	call	$_676
	cmp	byte ptr [rsi], 40
	jz	$_700
	cmp	byte ptr [rsi], 91
	jne	$_706
$_700:	xor	ecx, ecx
	mov	dword ptr [rbp-0x74], 41
	cmp	byte ptr [rsi], 91
	jnz	$_701
	mov	dword ptr [rbp-0x74], 93
	mov	ecx, 8
	jmp	$_702

$_701:	test	byte ptr [rdi+0x43], 0xFFFFFF80
	jz	$_702
	mov	rax, qword ptr [rdi+0x60]
	mov	qword ptr [rbp-0x10], rax
	or	byte ptr [rbp-0x2D], 0xFFFFFF80
$_702:	or	cl, byte ptr [rbp+0x48]
	and	ecx, 0xFFFFFFFB
	mov	byte ptr [rsp+0x20], cl
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x70]
	call	$_690
	mov	dword ptr [rbp-0x4], eax
	mov	rax, qword ptr [rbp+0x30]
	imul	ebx, dword ptr [rax], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	eax, dword ptr [rbp-0x74]
	cmp	al, byte ptr [rbx]
	jz	$_704
	cmp	dword ptr [rbp-0x4], -1
	jz	$_703
	mov	ecx, 2157
	call	qword ptr [fnasmerr+rip]
	mov	rax, qword ptr [rdi+0x50]
	cmp	byte ptr [rbx], 44
	jnz	$_703
	test	rax, rax
	jz	$_703
	cmp	byte ptr [rax+0x18], 0
	jnz	$_703
	mov	rdx, qword ptr [rax+0x8]
	mov	ecx, 2006
	call	qword ptr [fnasmerr+rip]
$_703:	mov	dword ptr [rbp-0x4], -1
	jmp	$_705

$_704:	mov	rdx, qword ptr [rbp+0x30]
	inc	dword ptr [rdx]
	add	rbx, 24
$_705:	jmp	$_709

$_706:	cmp	byte ptr [rbx], 40
	jz	$_707
	cmp	byte ptr [rbx], 91
	jz	$_707
	cmp	byte ptr [rbx], 43
	jz	$_707
	cmp	byte ptr [rbx], 45
	jz	$_707
	cmp	byte ptr [rbx], 4
	jnz	$_708
$_707:	movzx	ecx, byte ptr [rbp+0x48]
	or	ecx, 0x04
	mov	byte ptr [rsp+0x20], cl
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x70]
	call	$_690
	mov	dword ptr [rbp-0x4], eax
	jmp	$_709

$_708:	movzx	r9d, byte ptr [rbp+0x48]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x70]
	call	$_205
	mov	dword ptr [rbp-0x4], eax
$_709:	mov	rcx, qword ptr [rbp+0x30]
	imul	ebx, dword ptr [rcx], 24
	add	rbx, qword ptr [rbp+0x38]
	movzx	eax, byte ptr [rbx]
	jmp	$_718

$_710:	cmp	eax, 43
	jz	$_711
	cmp	eax, 45
	jnz	$_712
$_711:	mov	byte ptr [rbx+0x1], 1
	jmp	$_717

$_712:	cmp	eax, 40
	jnc	$_713
	cmp	eax, 4
	jz	$_713
	cmp	eax, 5
	jnz	$_714
$_713:	cmp	eax, 4
	jnz	$_717
$_714:	cmp	eax, 9
	jnz	$_715
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_715
	mov	rcx, rbx
	call	$_202
	mov	rdx, qword ptr [rbp+0x30]
	inc	dword ptr [rdx]
	add	rbx, 24
	jmp	$_716

$_715:	mov	dword ptr [rbp-0x4], -1
	test	byte ptr [rdi+0x43], 0x10
	jnz	$_716
	mov	rcx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbp+0x38]
	mov	ecx, dword ptr [rcx]
	call	$_687
$_716:	jmp	$_719

$_717:	mov	rcx, rbx
	call	$_182
	mov	dword ptr [rbp-0x84], eax
	mov	rcx, rsi
	call	$_182
	cmp	dword ptr [rbp-0x84], eax
	jge	$_719
	mov	cl, byte ptr [rbp+0x48]
	or	cl, 0x04
	mov	byte ptr [rsp+0x20], cl
	mov	r9d, dword ptr [rbp+0x40]
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp-0x70]
	call	$_690
	mov	dword ptr [rbp-0x4], eax
	mov	rax, qword ptr [rbp+0x30]
	imul	ebx, dword ptr [rax], 24
	add	rbx, qword ptr [rbp+0x38]
	movzx	eax, byte ptr [rbx]
$_718:	cmp	dword ptr [rbp-0x4], -1
	jz	$_719
	cmp	rbx, qword ptr [rbp-0x80]
	jnc	$_719
	cmp	eax, 41
	jz	$_719
	cmp	eax, 93
	jne	$_710
$_719:	cmp	dword ptr [rbp-0x4], -1
	jnz	$_723
	test	byte ptr [rbp-0x2D], 0x10
	jz	$_723
	jmp	$_721

$_720:	mov	rcx, qword ptr [rbp+0x30]
	inc	dword ptr [rcx]
	add	rbx, 24
$_721:	cmp	rbx, qword ptr [rbp-0x80]
	jnc	$_722
	cmp	byte ptr [rbx], 41
	jz	$_722
	cmp	byte ptr [rbx], 93
	jnz	$_720
$_722:	mov	dword ptr [rbp-0x34], -2
	mov	dword ptr [rbp-0x4], 0
$_723:	cmp	dword ptr [rbp-0x4], -1
	jz	$_724
	mov	r8, rsi
	lea	rdx, [rbp-0x70]
	mov	rcx, rdi
	call	$_527
	mov	dword ptr [rbp-0x4], eax
$_724:	test	byte ptr [rbp+0x48], 0x04
	jnz	$_726
$_725:	cmp	dword ptr [rbp-0x4], 0
	jnz	$_726
	cmp	rbx, qword ptr [rbp-0x80]
	jnc	$_726
	cmp	byte ptr [rbx], 41
	jz	$_726
	cmp	byte ptr [rbx], 93
	jne	$_692
$_726:	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

EvalOperand:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	ebx, dword ptr [rcx]
	mov	esi, ebx
	imul	ebx, ebx, 24
	add	rbx, qword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp+0x38]
	call	$_181
$_727:	cmp	esi, dword ptr [rbp+0x30]
	jge	$_742
	movzx	eax, byte ptr [rbx]
	jmp	$_740

$_728:	mov	eax, dword ptr [rbx+0x4]
	jmp	$_735

$_729:	mov	byte ptr [rbx], 5
	mov	byte ptr [rbx+0x1], 8
	jmp	$_741

$_730:	mov	byte ptr [rbx], 5
	mov	byte ptr [rbx+0x1], 7
	jmp	$_741

$_731:	mov	byte ptr [rbx], 5
	mov	byte ptr [rbx+0x1], 8
	jmp	$_741

$_732:	mov	byte ptr [rbx], 4
	mov	byte ptr [rbx+0x1], 11
	jmp	$_741

$_733:	mov	byte ptr [rbx], 5
	mov	byte ptr [rbx+0x1], 12
	jmp	$_741

$_734:	mov	byte ptr [rbx], 5
	mov	byte ptr [rbx+0x1], 13
	jmp	$_741

$_735:	cmp	eax, 655
	jz	$_729
	cmp	eax, 653
	jz	$_729
	cmp	eax, 586
	jz	$_730
	cmp	eax, 581
	jz	$_730
	cmp	eax, 593
	jz	$_731
	cmp	eax, 594
	jz	$_731
	cmp	eax, 595
	jz	$_731
	cmp	eax, 596
	jz	$_731
	cmp	eax, 657
	jz	$_732
	cmp	eax, 585
	jz	$_733
	cmp	eax, 582
	jz	$_734
	cmp	eax, 587
	jz	$_734
	jmp	$_742

$_736:	cmp	dword ptr [rbx+0x4], 272
	jz	$_742
	jmp	$_741

$_737:	cmp	dword ptr [rbx+0x4], 508
	jnz	$_739
	mov	byte ptr [rbx], 6
	mov	dl, byte ptr [ModuleInfo+0x1B5+rip]
	mov	eax, 1
	xchg	edx, ecx
	shl	eax, cl
	mov	ecx, edx
	and	eax, 0x70
	mov	eax, 226
	jz	$_738
	mov	eax, 227
$_738:	mov	dword ptr [rbx+0x4], eax
	jmp	$_741

$_739:	jmp	$_742

$_740:	cmp	eax, 1
	je	$_728
	cmp	eax, 7
	jz	$_736
	cmp	eax, 3
	jz	$_737
	cmp	eax, 44
	jz	$_739
$_741:	inc	esi
	add	rbx, 24
	jmp	$_727

$_742:
	mov	rdx, qword ptr [rbp+0x20]
	cmp	esi, dword ptr [rdx]
	jnz	$_743
	xor	eax, eax
	jmp	$_745

$_743:	lea	rax, [asmerr@PLT+rip]
	test	byte ptr [rbp+0x40], 0x01
	jz	$_744
	lea	rax, [noasmerr+rip]
$_744:	mov	qword ptr [fnasmerr+rip], rax
	movzx	eax, byte ptr [rbp+0x40]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, esi
	mov	r8, qword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp+0x38]
	call	$_690
$_745:	leave
	pop	rbx
	pop	rsi
	ret

EmitConstError:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	ecx, 2084
	call	asmerr@PLT
	leave
	ret

ExprEvalInit:
	xor	eax, eax
	mov	qword ptr [thissym+rip], rax
	mov	qword ptr [nullstruct+rip], rax
	mov	qword ptr [nullmbr+rip], rax
	ret


.SECTION .data
	.ALIGN	16

thissym:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

nullstruct:
	.quad  0x0000000000000000

nullmbr: .quad	0x0000000000000000

fnasmerr:
	.quad  thissym

	.quad  thissym+0x40400000000000

DS0000:
	.byte  0x00

DS0001:
	.byte  0x40, 0x40, 0x00



.att_syntax prefix
