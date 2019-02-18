; v2.21 pass depended expansion of text
; if text is expanded in second pass:
;
;    error A2004: symbol type conflict : "assert failed: "
;
	.486
	.model	flat, stdcall

printf	proto c :ptr sbyte, :vararg

	.code

	.assert:on

assert	macro
	;
	; late-expanded text <= 8 used as CONST value..
	; if > 8: error A2084: constant value too large
	;
	printf( "assert failed: " )
	exitm<>
	endm

	.assert:assert

main	PROC

	.assert eax == 0

main	ENDP

	END	main
