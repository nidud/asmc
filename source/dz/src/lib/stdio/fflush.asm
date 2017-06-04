include stdio.inc
include io.inc

	.code

	ASSUME	ebx: LPFILE

fflush	PROC USES ebx edi esi fp:LPFILE
	mov	ebx,fp
	xor	esi,esi
	mov	eax,[ebx]._flag
	mov	edi,eax
	and	eax,_IOREAD or _IOWRT
	cmp	eax,_IOWRT
	jne	toend
	test	edi,_IOMYBUF or _IOYOURBUF
	jz	toend
	mov	eax,[ebx]._ptr
	sub	eax,[ebx]._base
	jle	toend
	push	eax
	_write( [ebx]._file, [ebx]._base, eax )
	pop	edx
	cmp	eax,edx
	jne	error
	mov	eax,[ebx]._flag
	test	eax,_IORW
	jz	toend
	and	eax,not _IOWRT
	mov	[ebx]._flag,eax
toend:
	mov	eax,[ebx]._base
	mov	[ebx]._ptr,eax
	mov	[ebx]._cnt,0
	mov	eax,esi
	ret
error:
	or	edi,_IOERR
	mov	[ebx]._flag,edi
	mov	esi,-1
	jmp	toend
fflush	ENDP

	END
