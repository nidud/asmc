include string.inc

	.code

setfext PROC path:LPSTR, ext:LPSTR
	strext( path )
	test	eax,eax
	jz	@F
	mov	byte ptr [eax],0
@@:
	strcat( path, ext )
	ret
setfext ENDP

	END
