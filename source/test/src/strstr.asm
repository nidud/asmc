include string.inc
include stdio.inc
include alloc.inc
include winbase.inc

TEST_OVERLAP	equ 1

	.data

s1	db "xxxxxxxxxxxxxxxxabcxxxx",0
s2	db "xxxxxxxxxxxxxxaabcdxxx",0
s3	db "xxxxxxxxxxxxxababcxxxx",0
s4	db "xxxxxxxxxxxxabcabcdxxx",0
s5	db "xxxxxxxxxxxxx  abc",0
s6	db "xxxxxxxxxxxxxx abcd",0
s7	db "xxxxxxxxxxx..a.abc",0
s8	db "xxxxxxxxxxxxx  abc ",0
z1	db "abc",0
z2	db "xxx",0

s9	db "x eax ax ah al",0
z3	db "ah",0

table	label dword
	dd z3,s9,s9+9
	dd z1,s1,s1+16
	dd z1,s2,s2+15
	dd z1,s3,s3+15
	dd z1,s4,s4+12
	dd z1,s5,s5+15
	dd z1,s6,s6+15
	dd z1,s7,s7+15
	dd z1,s8,s8+15
	dd z2,s1,s1
	dd s5,s8,s8
	dd s8,s5,0

	dd 0,0,0,0,0

nerror	dd 0

	.code

main	PROC c

ifdef TEST_OVERLAP

	.if VirtualAlloc(0,4096,MEM_COMMIT,PAGE_READWRITE)
		push	MEM_RELEASE
		push	0
		push	eax
		mov	ebx,eax
		mov	edi,eax
		mov	ecx,4096
		mov	eax,'x'
		rep	stosb
		mov	edi,4096
		mov	BYTE PTR [ebx+edi-1],0
		lea	eax,[ebx+15]
		invoke	strstr,eax,ebx
		.repeat
			dec	edi
			inc	ebx
			mov	BYTE PTR [ebx+edi-1],0
			invoke	strstr,ebx,ebx
		.until	edi == 4096 - 33
		call	VirtualFree
	.endif
endif

	xor	edi,edi
	lea	esi,table
	.repeat
		lodsd
		mov	ecx,eax
		lodsd
		strstr( eax, ecx )
		mov	edx,eax
		mov	ecx,[esi-8]
		mov	ebx,[esi-4]
		lodsd
		.if	eax != edx
			printf( "\n\ntable %d: eax = %d (%d) strstr(%s, %s)\n", edi, edx, eax, ebx, ecx )
			inc	nerror
			.break
		.endif
		inc	edi
		mov	eax,[esi]
	.until !eax

toend:
	mov	eax,nerror
	ret
main	ENDP

	END
