;
; v2.22 .BREAK/.CONTINUE level in nested loops
;

	.model	small
	.code

	.while 1
	    .break		; break .while 1
	    .while 2
		.break1		; break .while 1
		.while 3
		    .break2	; break .while 1
		    .while 4
			.break3 ; break .while 1
			.break2 ; break .while 2
			.break1 ; break .while 3
		    .endw
		.endw
	    .endw
	.endw

	.while 1
	    .continue		; continue .while 1
	    .while 2
		.contl1		; continue .while 1
		.while 3
		    .contl2	; continue .while 1
		    .while 4
			.contl3 ; continue .while 1
			.contl2 ; continue .while 2
			.contl1 ; continue .while 3
		    .endw
		.endw
	    .endw
	.endw
	;
	; Skip TEST: .CONT0[1|2|3] [.IF <condition>]
	;
	.while al
	    .contl0			; Jump to START .while al
	    .while bl
		.contl01		; Jump to START .while al
		.while cl
		    .contl02		; Jump to START .while al
		    .while dl
			.contl03	; Jump to START .while al
			.contl02	; Jump to START .while bl
			.contl01	; Jump to START .while cl
			.continue	; Jump to TEST .while dl
		    .endw
		.endw
	    .endw
	.endw
	END

