include string.inc
include stdio.inc
include alloc.inc
include winbase.inc

	.data

s0	db 0
s1	db "xxxxxxxxxxxxxxxxabcxxxx",0
s2	db "xxxxxxxxxxxxxxaabcdxxx",0
s3	db "xxxxxxxxxxxxx  abc",0
s4	db "xxxxxxxxxxx..a.abc",0

table	label dword
	dd  1,'x',s0,0
	dd  1, 0 ,s0,s0
	dd 24, 0 ,s1,s1+23
	dd 24,'x',s1,s1
	dd 24,'a',s1,s1+16
	dd 24,'b',s1,s1+17
	dd 24,'c',s1,s1+18
	dd 23,'d',s2,s2+18
	dd 19,' ',s3,s3+13
	dd 19,'.',s4,s4+11
	dd 0
nerror	dd 0

	.code

overlapped proc uses esi edi ebx
	.if VirtualAlloc( 0, 4096, MEM_COMMIT, PAGE_READWRITE )
		push	MEM_RELEASE
		push	0
		push	eax
		mov	ebx,eax
		mov	edi,eax
		mov	ecx,4096
		mov	eax,'x'
		rep	stosb
		mov	edi,4096
		mov	BYTE PTR [ebx+4096-1],0
		lea	eax,[ebx+15]
		memchr( ebx, 'y', 4096 )
		memchr( ebx, 'x', 4096 )
		memchr( ebx,   0, 4096 )
		.repeat
			dec	edi
			inc	ebx
			memchr( ebx, 0, edi )
		.until	edi == 4096 - 33
		call	VirtualFree
	.endif
	ret
overlapped endp

regress proc USES esi edi ebx
	xor	edi,edi
	lea	esi,table
	.repeat
		memchr( [esi+8], [esi+4], [esi] )
		mov	edx,eax
		mov	ecx,[esi]
		mov	ebx,[esi+8]
		mov	eax,[esi+12]
		add	esi,16
		.if	eax != edx
			mov	esi,[esi-12]
			printf( "\n\ntable %d: eax = %X (%X) memchr(%s, %c, %d)\n",
				edi, edx, eax, ebx, esi, ecx )
			inc	nerror
			mov	eax,-1
			.break
		.endif
		inc	edi
		mov	eax,[esi]
	.until	!eax
	mov	eax,nerror
	test	eax,eax
	ret
regress endp

main	PROC c
	call	regress
	jnz	toend
	call	overlapped
toend:
	mov	eax,nerror
	ret
main	ENDP

	END
