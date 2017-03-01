;
; v2.22 .BREAK/.CONTINUE level in nested loops
;

	.model	small
	.code

	.while 1
	    .break		; break .while 1
	    .while 2
		.break(1)	; break .while 1
		.while 3
		    .break(2)	; break .while 1
		    .while 4
			.break(3) ; break .while 1
			.break(2) ; break .while 2
			.break(1) ; break .while 3
		    .endw
		.endw
	    .endw
	.endw

	.while 1
	    .continue			; continue .while 1
	    .while 2
		.continue(1)		; continue .while 1
		.while 3
		    .continue(2)	; continue .while 1
		    .while 4
			.continue(3)	; continue .while 1
			.continue(2)	; continue .while 2
			.continue(1)	; continue .while 3
		    .endw
		.endw
	    .endw
	.endw
	;
	; Skip TEST: .continue(0[1|2|3]) [.IF <condition>]
	;
	.while al
	    .continue(0)		; Jump to START .while al
	    .while bl
		.continue(01)		; Jump to START .while al
		.while cl
		    .continue(02)	; Jump to START .while al
		    .while dl
			.continue(03)	; Jump to START .while al
			.continue(02)	; Jump to START .while bl
			.continue(01)	; Jump to START .while cl
			.continue	; Jump to TEST .while dl
		    .endw
		.endw
	    .endw
	.endw
	END

