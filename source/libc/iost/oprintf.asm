include io.inc
include stdio.inc
include iost.inc

	.code

oprintf PROC c format:LPSTR, argptr:VARARG
	ftobufin( format, addr argptr )
	mov	ecx,eax
while_1:
	mov	al,[edx]
	inc	edx
	test	al,al
	jz	break
	cmp	al,0Ah
	je	lf
continue:
	call	oputc
	jnz	while_1
break:
	mov	eax,ecx
	ret
lf:
	mov	eax,STDO.ios_file
	test	_osfile[eax],FH_TEXT
	jz	@F
	mov	eax,0Dh
	call	oputc
	jz	break
	inc	ecx
@@:
	mov	eax,0Ah
	jmp	continue
oprintf ENDP

	END
