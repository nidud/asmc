include consx.inc
include string.inc

	.code

__wcpath PROC USES ebx b:PVOID, l:DWORD, p:LPSTR
	mov	ecx,strlen( p )
	mov	edx,p
	mov	eax,b
	cmp	ecx,l
	jbe	toend
	mov	ebx,[edx]
	add	edx,ecx
	mov	ecx,l
	sub	edx,ecx
	add	edx,4
	cmp	bh,':'
	jne	@F
	mov	[eax],bl
	mov	[eax+2],bh
	shr	ebx,8
	mov	bl,'.'
	add	eax,4
	add	edx,2
	sub	ecx,2
	jmp	@set
@@:
	mov	bx,'/.'
@set:
	mov	[eax],bh
	mov	[eax+2],bl
	mov	[eax+4],bl
	mov	[eax+6],bh
	add	eax,8
	sub	ecx,4
toend:
	ret
__wcpath ENDP

	END
