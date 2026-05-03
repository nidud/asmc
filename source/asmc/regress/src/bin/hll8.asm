;
; v2.24 - missing ".while eax" if preceded by a label
;
	.386
	.model	flat
	.code

L2:	.while	eax

		nop
	.endw

	end

