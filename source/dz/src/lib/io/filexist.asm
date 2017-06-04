include io.inc

	.code

filexist PROC file:LPSTR
	getfattr( file )
	inc	eax
	jz	@F
	dec	eax		; 1 = file
	and	eax,_A_SUBDIR	; 2 = subdir
	shr	eax,4
	inc	eax
@@:
	ret
filexist ENDP

	END

