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
arg_1	dd dst_1
arg_2	dd src_1
arg_3	dd size_s

nerror	dd 0

	.code

validate PROC USES esi edi ebx d, s, z

	mov	edi,d
	mov	ecx,z
	mov	eax,'x'
	inc	ecx
	mov	esi,edi
	rep	stosb
	.if	memcpy( esi, s, z ) != esi
		printf( "error return value: eax = %06X (%06X) memcpy\n", eax, d )
		inc	nerror
	.endif
	mov	ecx,z
	xor	edx,edx
	xor	eax,eax
	.repeat
		lodsb
		or	edx,eax
	.untilcxz
	.if	edx
		printf( "error data not zero: (%d) memcpy\n", z )
		inc	nerror
	.endif
	.if	BYTE PTR [esi] != 'x'
		printf( "error data zero: memcpy\n" )
		inc	nerror
	.endif
	ret
validate ENDP

validate_copy_M_M3:	; copy(m, m+3, A..Z)
	lea	edi,dst_1
	xor	eax,eax
	mov	ecx,16
	rep	stosd
	lea	edi,dst_1
	lea	ecx,[edi+3]
	mov	ebx,edi
	mov	eax,'A'
	.repeat
		stosb
		inc	eax
	.until	eax > 'z'
	memcpy( ebx, ecx, 'z' - 'A' - 2 )
	xor	edx,edx
	mov	ecx,'z' - 'A' - 2
	mov	eax,'z'
	.repeat
		mov	dl,[ebx+ecx-1]
		sub	dl,al
		dec	eax
		.break .if edx
	.untilcxz
	mov	eax,[ebx + 'z' - 'A' - 2 - 1]
	.if	eax != 'zyxz'
		inc	edx
	.endif
	mov	eax,ecx
	ret

validate_copy_M3_M:	; copy(m+3, m, A..Z)
	lea	edi,dst_1
	xor	eax,eax
	mov	ecx,16
	rep	stosd
	lea	edi,dst_1
	lea	ebx,[edi+3]
	mov	ecx,edi
	mov	eax,'A'
	.repeat
		stosb
		inc	eax
	.until	eax > 'z'
	memmove( ebx, ecx, 'z' - 'A' - 2 )
	xor	edx,edx
	mov	ecx,'z' - 'A' - 2
	mov	eax,'w'
	.repeat
		mov	dl,[ebx+ecx-1]
		sub	dl,al
		dec	eax
		.break .if edx
	.untilcxz
	mov	eax,[ebx-3]
	.if	eax != 'ACBA'
		inc	edx
	.endif
	mov	eax,ecx
	ret

main	PROC c

	mov	edi,1
	lea	ebx,dst_1
	.while	edi < 128
		validate( ebx, addr null, edi )
		inc	edi
		inc	ebx
	.endw

	lea	edi,src_1
	mov	ecx,size_s
	mov	eax,'x'
	rep	stosb

	mov	ebx,1
	.repeat
		lea	edi,dst_1
		mov	al,'?'
		lea	ecx,[ebx+16]
		rep	stosb
		memcpy( arg_1, arg_2, ebx )
		xor	edx,edx
		.if eax != arg_1
			inc	edx
		.else
			mov	ecx,ebx
			.repeat
				.if BYTE PTR [eax+ecx-1] != 'x'
					inc	edx
				.endif
			.untilcxz
			lea	edi,[eax+ebx]
			mov	ecx,16
			.repeat
				.if BYTE PTR [edi+ecx-1] != '?'
					inc	edx
				.endif
			.untilcxz
		.endif
		.if edx
			printf( "error: eax %06X [%06X] (%d) memcpy\n", eax, addr dst_1, ebx )
			inc	nerror
		.endif
		.break .if nerror > 10
		inc	ebx
	.until	ebx == 66
if 1
	.if !nerror
		call	validate_copy_M3_M
		.if eax
			printf( "error(m+3,m,%d): memcpy: %s\n", 'z' - 'A' - 2, addr dst_1 )
			inc	nerror
		.endif
		call	validate_copy_M_M3
		.if eax
			printf( "error(m,m+3,%d): memcpy: %s\n", 'z' - 'A' - 2, addr dst_1 )
			inc	nerror
		.endif
	.endif
endif
toend:
	mov	eax,nerror
	ret
main	ENDP

	END
