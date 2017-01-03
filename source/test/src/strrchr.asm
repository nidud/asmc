include string.inc
include stdio.inc
include alloc.inc
;include math.inc

;	__MSVC__ equ 1

ifdef	__MSVC__

include \masm32\include\msvcrt.inc
includelib \masm32\lib\msvcrt.lib

endif

	.data

s0	db 0
s1	db "0123456789ABCDEFabcxxxx",0
s2	db "xxxxxxxxxxxxxxaabcdxxx",0
s3	db "xxxxxxxxxxxxx  abc",0
s4	db "xxxxxxxxxxx..a.abc",0

az	db "0123456789"
	db "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	db "abcdefghijklmnopqrstuvwxyz"
	db 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1
	db 0

table	label dword
	dd 'x',s0,0
	dd  0 ,s0,s0
	dd  0 ,s1,s1+23
	dd 'x',s1,s1+22
	dd 'a',s1,s1+16
	dd 'b',s1,s1+17
	dd 'c',s1,s1+18
	dd 'd',s2,s2+18
	dd ' ',s3,s3+14
	dd '.',s4,s4+14
	dd 0
nerror	dd 0

	.code

overlapped proc uses esi edi ebx
	invoke	VirtualAlloc,0,4096,MEM_COMMIT,PAGE_READWRITE
	test	eax,eax
	jz	toend
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
ifdef __MSVC__
	invoke	crt_strrchr,ebx,'y'
	invoke	crt_strrchr,ebx,'x'
	invoke	crt_strrchr,ebx,0
else
	invoke	strrchr,ebx,'y'
	invoke	strrchr,ebx,'x'
	invoke	strrchr,ebx,0
endif
@@:
	dec	edi
	inc	ebx
ifdef __MSVC__
	invoke	crt_strrchr,ebx,0
else
	invoke	strrchr,ebx,0
endif
	cmp	edi,4096 - 33
	jne	@B
	call	VirtualFree
toend:
	ret
overlapped endp

regress proc USES esi edi ebx
	lea	esi,az
	mov	edi,esi
loop_az:
	lodsb
	test	al,al
	jz	do_table
	push	eax
	push	edi
ifdef __MSVC__
	call	crt_strrchr
	add	esp,8
else
	call	strrchr
endif
	lea	edx,[esi-1]
	movzx	ecx,byte ptr [edx]
	cmp	eax,edx
	jne	error1
	jmp	loop_az

do_table:
	xor	edi,edi
	lea	esi,table
lupe:
	lodsd
	push	eax
	lodsd
	push	eax
ifdef __MSVC__
	call	crt_strrchr
	add	esp,8
else
	call	strrchr
endif
	mov	edx,eax
	mov	ebx,[esi-4]
	lodsd
	cmp	eax,edx
	jne	error
	inc	edi
	mov	eax,[esi]
	test	eax,eax
	jnz	lupe
	inc	eax
toend:
	ret
error1:
	printf("\n\nerror: eax = %X (%X) strrchr2(%s, %c, %c) : %s\n",
		eax,edx,edi,ecx, eax)
	inc	nerror
	xor	eax,eax
	jmp	toend
error:
	mov	esi,[esi-12]
	printf("\n\ntable[%d]: eax = %X (%X) strrchr2(%s, %c, %c)\n",
		edi, edx, eax, ebx, esi)
	inc	nerror
	xor	eax,eax
	jmp	toend
regress endp

main	PROC c
	call	regress
	jz	toend
	call	overlapped
toend:
	mov	eax,nerror
	ret
main	ENDP

	END
