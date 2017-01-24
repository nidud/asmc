include conio.inc

	.code

rcaddrc PROC USES ebx result:PVOID, r1, r2
	mov	eax,r2
	add	ax,WORD PTR r1
	mov	ebx,result
	mov	[ebx],eax
	ret
rcaddrc ENDP

	END