include direct.inc
include winbase.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

validdrive PROC drive:SINT
	call	GetLogicalDrives
	mov	ecx,[esp+4]
	dec	ecx
	shr	eax,cl
	sbb	eax,eax
	and	eax,1
	ret	4
validdrive ENDP

	END
