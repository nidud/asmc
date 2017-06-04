include direct.inc
include dzlib.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_disk_exist PROC disk
	push	edx
	mov	eax,SIZE S_DISK
	mov	edx,[esp+8]
	dec	edx
	mul	edx
	lea	edx,drvinfo[eax]
	xor	eax,eax
	cmp	[edx].S_DISK.di_flag,eax
	je	toend
	mov	eax,edx
toend:
	pop	edx
	ret	4
_disk_exist ENDP

	END
