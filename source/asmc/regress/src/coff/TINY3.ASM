
;--- 32-bit tiny model, format coff/djgpp;
;--- no "assume cs:dgroup" is to be generated.

	.386
	.MODEL tiny

	.data

	assume ds:_data

XXX fword 0

	.code

test1 proc
	call XXX
	ret
test1 endp


	END
