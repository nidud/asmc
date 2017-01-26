; v2.22 - Test for pre-existing flag conditions (same as Jxx)
;
;	.IFA	- if Above
;	.IFAE	- if Above or Equal
;	.IFB	- if Below
;	.IFBE	- if Not Below or Equal
;	.IFC	- if Carry
;	.IFE	- if Equal
;	.IFG	- if Greater (signed)
;	.IFGE	- if Greater or Equal (signed)
;	.IFL	- if Less (signed)
;	.IFLE	- if Less or Equal (signed)
;	.IFNA	- if Not Above
;	.IFNAE	- if Not Above or Equal
;	.IFNB	- if Not Below
;	.IFNBE	- if Not Below or Equal
;	.IFNC	- if Not Carry
;	.IFNE	- if Not Equal
;	.IFNG	- if Not Greater (signed)
;	.IFNGE	- if Not Greater or Equal (signed)
;	.IFNL	- if Not Less (signed)
;	.IFNLE	- if Not Less or Equal (signed)
;	.IFNO	- if Not Overflow (signed)
;	.IFNP	- if No Parity
;	.IFNS	- if Not Signed (signed)
;	.IFNZ	- if Not Zero
;	.IFO	- if Overflow (signed)
;	.IFP	- if Parity
;	.IFPE	- if Parity Even
;	.IFPO	- if Parity Odd
;	.IFS	- if Signed (signed)
;	.IFZ	- if Zero
;
	.386
	.model	flat
	.code

	.IFA
	.ENDIF
	.IFAE
	.ENDIF
	.IFB
	.ENDIF
	.IFBE
	.ENDIF
	.IFC
	.ENDIF
	.IFE
	.ENDIF
	.IFG
	.ENDIF
	.IFGE
	.ENDIF
	.IFL
	.ENDIF
	.IFLE
	.ENDIF
	.IFNA
	.ENDIF
	.IFNAE
	.ENDIF
	.IFNB
	.ENDIF
	.IFNBE
	.ENDIF
	.IFNC
	.ENDIF
	.IFNE
	.ENDIF
	.IFNG
	.ENDIF
	.IFNGE
	.ENDIF
	.IFNL
	.ENDIF
	.IFNLE
	.ENDIF
	.IFNO
	.ENDIF
	.IFNP
	.ENDIF
	.IFNS
	.ENDIF
	.IFNZ
	.ENDIF
	.IFO
	.ENDIF
	.IFP
	.ENDIF
	.IFPE
	.ENDIF
	.IFPO
	.ENDIF
	.IFS
	.ENDIF
	.IFZ
	.ENDIF

	.WHILE	1
		.BREAK .IFA
		.BREAK .IFAE
		.BREAK .IFB
		.BREAK .IFBE
		.BREAK .IFC
		.BREAK .IFE
		.BREAK .IFG
		.BREAK .IFGE
		.BREAK .IFL
		.BREAK .IFLE
		.BREAK .IFNA
		.BREAK .IFNAE
		.BREAK .IFNB
		.BREAK .IFNBE
		.BREAK .IFNC
		.BREAK .IFNE
		.BREAK .IFNG
		.BREAK .IFNGE
		.BREAK .IFNL
		.BREAK .IFNLE
		.BREAK .IFNO
		.BREAK .IFNP
		.BREAK .IFNS
		.BREAK .IFNZ
		.BREAK .IFO
		.BREAK .IFP
		.BREAK .IFPE
		.BREAK .IFPO
		.BREAK .IFS
		.BREAK .IFZ

		.CONTINUE .IFA
		.CONTINUE .IFAE
		.CONTINUE .IFB
		.CONTINUE .IFBE
		.CONTINUE .IFC
		.CONTINUE .IFE
		.CONTINUE .IFG
		.CONTINUE .IFGE
		.CONTINUE .IFL
		.CONTINUE .IFLE
		.CONTINUE .IFNA
		.CONTINUE .IFNAE
		.CONTINUE .IFNB
		.CONTINUE .IFNBE
		.CONTINUE .IFNC
		.CONTINUE .IFNE
		.CONTINUE .IFNG
		.CONTINUE .IFNGE
		.CONTINUE .IFNL
		.CONTINUE .IFNLE
		.CONTINUE .IFNO
		.CONTINUE .IFNP
		.CONTINUE .IFNS
		.CONTINUE .IFNZ
		.CONTINUE .IFO
		.CONTINUE .IFP
		.CONTINUE .IFPE
		.CONTINUE .IFPO
		.CONTINUE .IFS
		.CONTINUE .IFZ
	.ENDW

	END
