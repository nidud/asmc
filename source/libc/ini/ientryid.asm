include ini.inc

	.code

inientryid PROC section:LPSTR, entry
	mov	eax,entry
@@:
	cmp	al,9		; 0..99
	jbe	@F
	inc	ah
	sub	al,10
	jmp	@B
@@:
	test	ah,ah
	jz	@F
	xchg	al,ah
	or	ah,'0'
@@:
	or	al,'0'
	mov	entry,eax
	inientry( section, addr entry )
	ret
inientryid ENDP

	END
