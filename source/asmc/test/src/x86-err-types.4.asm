
;--- forward reference in a type expression, used as left operand for PTR

	.386
	.model flat

	.code

	mov eax, (TYPEOF var) ptr [ebx]

var dw 0

end

