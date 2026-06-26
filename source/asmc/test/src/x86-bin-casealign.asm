
; v2.21 - align .CASE labels
;
; .SWITCH [x]
;
;	jmp start_label
;	ALIGN <casealign> ; <<-- align .CASE label if set
;	case_label:
;	ALIGN <casealign> ; <<-- align SWITCH-TEST label if set
;	start_label:
;

	.486
	.model	flat
	.code

	option	casealign:0

	.switch al
	  .case dl : nop
	  .case cl : nop
	  .case bl : nop
	  .case ah : nop
	  .case dh : nop
	  .case ch : nop
	  .case bh : nop
	.endsw

	option	casealign:16

	.switch al
	  .case dl : nop
	  .case cl : nop
	  .case bl : nop
	  .case ah : nop
	  .case dh : nop
	  .case ch : nop
	  .case bh : nop
	.endsw

	END
