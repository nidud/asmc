include consx.inc

	.code

tiretevent PROC
	mov	eax,_TE_RETEVENT ; return current event (keystroke)
	ret
tiretevent ENDP

	END
