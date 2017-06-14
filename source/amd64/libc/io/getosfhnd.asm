include io.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

getosfhnd PROC handle:SINT
	or	rax,-1
	.if	ecx < _nfile
		lea	r8,_osfile
		.if	BYTE PTR [r8+rcx] & FH_OPEN
			lea r8,_osfhnd
			mov rax,[r8+rcx*8]
		.endif
	.endif
	ret
getosfhnd ENDP

	END
