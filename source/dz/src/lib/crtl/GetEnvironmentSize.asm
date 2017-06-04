include stdlib.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

GetEnvironmentSize PROC EnvironmentStrings:LPSTR
	mov	edx,edi
	mov	edi,[esp+4]
	xor	eax,eax
	mov	ecx,-1
	.while	al != [edi]
		repnz	scasb
	.endw
	mov	edi,edx
	sub	eax,ecx
	ret	4
GetEnvironmentSize ENDP

	END
