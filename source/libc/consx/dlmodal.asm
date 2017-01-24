include consx.inc

	.code

dlmodal PROC dobj:PTR S_DOBJ
	dlevent( dobj )
	dlclose( dobj )
	mov	eax,edx
	test	eax,eax
	ret
dlmodal ENDP

	END
