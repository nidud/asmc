include stdio.inc
include io.inc

	.code

	ASSUME	ebx: LPFILE

fflush	PROC USES ebx edi esi fp:LPFILE
	mov	ebx,fp
	xor	esi,esi
	mov	eax,[ebx].iob_flag
	mov	edi,eax
	and	eax,_IOREAD or _IOWRT
	cmp	eax,_IOWRT
	jne	toend
	test	edi,_IOMYBUF or _IOYOURBUF
	jz	toend
	mov	eax,[ebx].iob_ptr
	sub	eax,[ebx].iob_base
	jle	toend
	push	eax
	_write( [ebx].iob_file, [ebx].iob_base, eax )
	pop	edx
	cmp	eax,edx
	jne	error
	mov	eax,[ebx].iob_flag
	test	eax,_IORW
	jz	toend
	and	eax,not _IOWRT
	mov	[ebx].iob_flag,eax
toend:
	mov	eax,[ebx].iob_base
	mov	[ebx].iob_ptr,eax
	mov	[ebx].iob_cnt,0
	mov	eax,esi
	ret
error:
	or	edi,_IOERR
	mov	[ebx].iob_flag,edi
	mov	esi,-1
	jmp	toend
fflush	ENDP

	END
