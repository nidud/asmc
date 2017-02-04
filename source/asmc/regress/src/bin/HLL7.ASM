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
			.contl3 ; continue .while 1
			.contl2 ; continue .while 2
			.contl1 ; continue .while 3
			.contl0 ; continue
		    .endw
		.endw
	    .endw
	.endw

	END

