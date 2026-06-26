
;--- v2.17: error 'constant value too large' now generally displayed
;--- masm compatible.

	.386
	.model flat

	.code
	mov ax, ds:[123456789h]

	end
