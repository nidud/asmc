	.x64
	.model	flat, stdcall
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

proto_t typedef proto :ptr, :ptr
proto_p typedef ptr proto_t
proc_p	proto_p 0

FOR	J,<B,W,D,S,SB,SW,SD>
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
