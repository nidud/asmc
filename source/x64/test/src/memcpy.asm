include string.inc
include stdio.inc
include alloc.inc

TEST_OVERLAP	equ 1
size_s		equ 4096*128	; copy size

.data?
null	db 1024 dup(?)
ALIGN	16
src_1	db size_s dup(?)
ALIGN	16
dst_1	db size_s dup(?)
	db 1024 dup(?)

.data
ALIGN	4
arg_1	dq dst_1
arg_2	dq src_1
arg_3	dq size_s

nerror	dq 0

	.code

validate PROC USES rsi rdi rbx d:qword, s:qword, z:qword

	mov	rdi,d
	mov	rcx,z
	mov	rax,'x'
	inc	rcx
	mov	rsi,rdi
	rep	stosb
	.if	memcpy( rsi, s, z ) != rsi
		printf( "error return value: eax = %06X (%06X) memcpy\n", rax, d )
		inc	nerror
	.endif
	mov	rcx,z
	xor	rdx,rdx
	xor	rax,rax
	.repeat
		lodsb
		or	rdx,rax
	.untilcxz
	.if	rdx
		printf( "error data not zero: (%d) memcpy\n", z )
		inc	nerror
	.endif
	.if	BYTE PTR [rsi] != 'x'
		printf( "error data zero: memcpy\n" )
		inc	nerror
	.endif
	ret
validate ENDP

validate_copy_M_M3:	; copy(m, m+3, A..Z)
	lea	rdi,dst_1
	xor	rax,rax
	mov	rcx,16
	rep	stosd
	lea	rdi,dst_1
	lea	rcx,[rdi+3]
	mov	rbx,rdi
	mov	rax,'A'
	.repeat
		stosb
		inc	rax
	.until	rax > 'z'
	mov	rdx,rcx
	memcpy( rbx, rdx, 'z' - 'A' - 2 )
	xor	rdx,rdx
	mov	rcx,'z' - 'A' - 2
	mov	rax,'z'
	.repeat
		mov	dl,[rbx+rcx-1]
		sub	dl,al
		dec	rax
		.break .if rdx
	.untilcxz
	mov	rax,[rbx + 'z' - 'A' - 2 - 1]
	.if	rax != 'zyxz'
		inc	rdx
	.endif
	mov	rax,rcx
	ret

validate_copy_M3_M:	; copy(m+3, m, A..Z)
	lea	rdi,dst_1
	xor	rax,rax
	mov	rcx,16
	rep	stosd
	lea	rdi,dst_1
	lea	rbx,[rdi+3]
	mov	rcx,rdi
	mov	rax,'A'
	.repeat
		stosb
		inc	rax
	.until	rax > 'z'
	mov	rdx,rcx
	memmove( rbx, rdx, 'z' - 'A' - 2 )
	xor	rdx,rdx
	mov	rcx,'z' - 'A' - 2
	mov	rax,'w'
	.repeat
		mov	dl,[rbx+rcx-1]
		sub	dl,al
		dec	rax
		.break .if rdx
	.untilcxz
	mov	rax,[rbx-3]
	.if	rax != 'ACBA'
		inc	rdx
	.endif
	mov	rax,rcx
	ret

main	PROC

	mov	rdi,1
	lea	rbx,dst_1
	.while	rdi < 128
		validate( rbx, addr null, rdi )
		inc	rdi
		inc	rbx
	.endw

	lea	rdi,src_1
	mov	rcx,size_s
	mov	rax,'x'
	rep	stosb

	mov	rbx,1
	.repeat
		lea	rdi,dst_1
		mov	al,'?'
		lea	rcx,[rbx+16]
		rep	stosb
		memcpy( arg_1, arg_2, rbx )
		xor	rdx,rdx
		.if rax != arg_1
			inc	rdx
		.else
			mov	rcx,rbx
			.repeat
				.if BYTE PTR [rax+rcx-1] != 'x'
					inc	rdx
				.endif
			.untilcxz
			lea	rdi,[rax+rbx]
			mov	rcx,16
			.repeat
				.if BYTE PTR [rdi+rcx-1] != '?'
					inc	rdx
				.endif
			.untilcxz
		.endif
		.if rdx
			printf( "error: eax %06X [%06X] (%d) memcpy\n", rax, addr dst_1, rbx )
			inc	nerror
		.endif
		.break .if nerror > 10
		inc	rbx
	.until	rbx == 66
if 1
	.if !nerror
		call	validate_copy_M3_M
		.if rax
			printf( "error(m+3,m,%d): memcpy: %s\n", 'z' - 'A' - 2, addr dst_1 )
			inc	nerror
		.endif
		call	validate_copy_M_M3
		.if rax
			printf( "error(m,m+3,%d): memcpy: %s\n", 'z' - 'A' - 2, addr dst_1 )
			inc	nerror
		.endif
	.endif
endif
toend:
	mov	rax,nerror
	ret
main	ENDP

	END
