
;--- v2.19: error emitted in pass 2 only.

	.286
	.MODEL small

_TEXT2 segment 'CODE'
p2 label near
_TEXT2 ends

	.CODE

p1 label near

	call p2		;cannot have implicit far jump or call to near label

	END
