; v2.22 - Flag conditions
;
;A	NBE	Above | Not Below or Equal
;B	C/NAE	Below | Carry | Not Above or Equal
;G	NLE	Greater | Not Less or Equal (signed)
;L	NGE	Less | Not Greater or Equal (signed)
;O		Overflow (signed)
;P	PE	Parity | Parity Even
;S		Signed (signed)
;Z	E	Zero | Equal
;NA	BE	Not Above | Not Below or Equal
;NB	NC/AE	Not Below | Not Carry | Above or Equal
;NG	LE	Not Greater | Less or Equal (signed)
;NL	GE	Not Less | Greater or Equal (signed)
;NO		Not Overflow (signed)
;NP	PO	No Parity | Parity Odd
;NS		Not Signed (signed)
;NZ	NE	Not Zero | Not Equal
;
	.386
	.model	flat, c
	.code

FOR	J,<A,B,G,L,O,P,S,Z,NA,NB,NG,NL,NO,NP,NS,NZ>
	.IF&J&
		nop
	.ENDIF
	.WHILE&J&
		nop
	.ENDW
	.REPEAT
		nop
	.UNTIL&J&
	ENDM

	.WHILE	1
	FOR	J,<A,B,G,L,O,P,S,Z,NA,NB,NG,NL,NO,NP,NS,NZ>
		.BREAK&J&
		.CONTINUE&J&
		.BREAK .IF&J&
		.CONTINUE .IF&J&
		ENDM
	.ENDW
;
; Return value
;
; .if	foo(1,2) --> .if [r|e]ax
; .ifb	foo(1,2) --> .if al
; .ifw	foo(1,2) --> .if ax
; .ifd	foo(1,2) --> .if eax
; .ifs	foo(1,2) --> .if [r|e]ax (signed)
; .ifsb foo(1,2) --> .if al (signed)
; .ifsw foo(1,2) --> .if ax (signed)
; .ifsd foo(1,2) --> .if eax (signed)
;
proto_t typedef proto :ptr, :ptr
proto_p typedef ptr proto_t
proc_p	proto_p 0

FOR	J,<B,W,S,SB,SW>
	.IF&J& proc_p(1,2) > 0
		nop
	.ENDIF
	.WHILE&J& proc_p(1,2) > 0
		nop
	.ENDW
	.REPEAT
		nop
	.UNTIL&J& proc_p(1,2) > 0
	ENDM

FOR	J,<B,W,D>
	.IF&J& proc_p(1,2) == 0
		nop
	.ENDIF
	.WHILE&J& proc_p(1,2) == 0
		nop
	.ENDW
	.REPEAT
		nop
	.UNTIL&J& proc_p(1,2) == 0
	ENDM

	.WHILE	1
		.BREAK .IFS proc_p(1,2) > 0
		.BREAK .IFB proc_p(1,2)
		.BREAK .IFW proc_p(1,2)
		.BREAK .IFD proc_p(1,2)
		.CONTINUE .IFS proc_p(1,2) > 0
		.CONTINUE .IFB proc_p(1,2)
		.CONTINUE .IFW proc_p(1,2)
		.CONTINUE .IFD proc_p(1,2)
	.ENDW
	.REPEAT
		.BREAK .IFS proc_p(1,2) > 0
		.BREAK .IFB proc_p(1,2)
		.BREAK .IFW proc_p(1,2)
		.BREAK .IFD proc_p(1,2)
		.CONTINUE .IFS proc_p(1,2) > 0
		.CONTINUE .IFB proc_p(1,2)
		.CONTINUE .IFW proc_p(1,2)
		.CONTINUE .IFD proc_p(1,2)
	.UNTIL	1

	END
