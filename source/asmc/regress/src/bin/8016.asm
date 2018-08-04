	;
	; JWasm: Warning A4236: Text macro used prior to definition: reg
	; v2.20: warning A8016: text macro used prior to definition: reg
	; v2.21: warning A6005: expression condition may be pass-dependent: reg
	;
	.486
	.model	flat
	.code

	mov	al,reg
	mov	al,enum

	.if	reg == enum
	.elseif reg > enum
	.endif

	.while	reg > enum
		nop
	.endw

ifdef __ASMC__

	.switch al
	  .case reg
	  .case enum
	.endsw

endif
	reg equ <cl>
	enum = 1

	END
