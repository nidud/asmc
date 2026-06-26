	.386
	.model flat
	.code

	.switch eax
	  .case			; error A2008: syntax error : .case
	  .case al		; error A2022: instruction operands must be the same size : 4 - 1
	  .case PTR : WORD	; error A2008: syntax error : WORD
	  .case eax == 1	; error A2206: missing operator in expression
	  .default : .break	; error A2008: syntax error : .default : .break
	.endsw

	END

