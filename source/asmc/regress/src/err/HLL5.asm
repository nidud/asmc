	.386
	.model flat
	.code

	.switch al		; error A3022: .CASE redefinition : 2(2) : 2(2)
	  .case 1,2,3,4,2
	.endsw

	.ifsb	ax > 0
	.endif
	.ifsb	eax > 0
	.endif

	END

