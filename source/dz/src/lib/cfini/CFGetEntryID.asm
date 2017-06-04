include cfini.inc

	.code

CFGetEntryID PROC __ini:PCFINI, __entry:UINT

	mov	eax,__entry	; 0..99

	.while	al > 9

		add	ah,1
		sub	al,10
	.endw
	.if	ah

		xchg	al,ah
		or	ah,'0'
	.endif
	or	al,'0'
	mov	__entry,eax

	CFGetEntry( __ini, addr __entry )
	ret

CFGetEntryID ENDP

	END
