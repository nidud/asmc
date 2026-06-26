
;--- v2.17: check size operand of DUP operator for overflow
;--- was accepted as long as low32 of value was "positive".

	.386
	.MODEL FLAT, stdcall

	.CODE

start:
	db 5000000000 dup (?)


	END start
