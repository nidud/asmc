include string.inc
include fltintrn.inc

	.code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

_cropzeros proc buffer:LPSTR

	mov r10,rcx
	add r10,strlen(r10)
	mov eax,'0'
	.while	[r10-1] == al
	    mov byte ptr [r10-1],0
	    dec r10
	.endw
	.if byte ptr [r10-1] == '.'
	    mov byte ptr [r10-1],0
	.endif
	ret

_cropzeros endp

	END
