
;--- forward reference in a type expression, used as left operand for PTR

ifdef __ASMC__
option masm:on
endif
	.386
	.model flat

	.code

	mov eax, (TYPE var) ptr [ebx]

var dd 0

end

