
;--- a missing left square bracket in indirect addressing wasn't noticed in invoke
;--- before v2.15, resulting in wrong code.

	.386
	.MODEL FLAT

	.CODE

xxx PROC c args:dword
	ret
xxx endp

start32 proc c public
	invoke xxx, ebx]
	mov ax,4c00h
	int 21h
start32 endp

	END

