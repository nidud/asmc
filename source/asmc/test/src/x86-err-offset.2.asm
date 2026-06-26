
;--- v2.17: now always error "constant value too large" if offset exceeds 32-bit
;---        previously was a warning, level 3: ( displacement out of range )

	.386
	.model flat

	.code
	mov ax, [ebx+123456789h]

	end
