
; v2.21 - align .WHILE loops
;
; .WHILE x
;
;	jmp start
;	ALIGN <loopalign> ; <<-- align .WHILE and .REPEAT label if set
;	loop_label:
;
	.486
	.model	flat
	.code

	option	loopalign:0

	.while	al
		nop
	.endw
	.repeat
		nop
	.until	!al
	.repeat
		nop
	.untilcxz

	option	loopalign:4

	.while	al
		nop
	.endw
	.repeat
		nop
	.until	!al
	.repeat
		nop
	.untilcxz

	option	loopalign:8

	.while	al
		nop
	.endw
	.repeat
		nop
	.until	!al
	.repeat
		nop
	.untilcxz

	option	loopalign:16

	.while	al
		nop
	.endw
	.repeat
		nop
	.until	!al
	.repeat
		nop
	.untilcxz

	END
