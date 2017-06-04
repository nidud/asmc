include consx.inc

	.code

ticontinue PROC
	xor eax,eax ; _TI_CONTINUE - continue edit
	ret
ticontinue ENDP

	END
