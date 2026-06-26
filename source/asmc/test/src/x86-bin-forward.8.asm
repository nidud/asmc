
;--- difference of 2 labels, at least one is a forward ref
;--- the difference is used as operand for another op ( SHL here ).
;--- didn't work in v2.09 - v2.15 ( error 'constant expected' )

_TEXT segment word public 'CODE'

var1 dw 0

	mov [var1], ( offset lbl1 - $ ) shl 8
lbl1:
	ret

_TEXT ends

	end
