;
; v2.21 concatenation of line follow '(' for HLL procedure call
;
	.486
	.model	flat, stdcall
	.code

foo	proc a1, a2, a3
	ret
foo	endp

	foo	(
		1,
		2,
		3 )

	end
