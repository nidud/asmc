Asmc Macro Assembler Reference

## .GOTOSW

.**GOTOSW**[1|2|3] [[(<_case_val_>)] | [.**IF** _condition_]]

Generates code to jump to the top of a [.SWITCH](dot_switch.md) block if _condition_ is true.

**.GOTOSW** jump's directly to the TEST label.

	.switch al
	  .case 1
	  ...
	  .case 9
	    mov al,1
	    .gotosw		; "Jump" to case 1


**GOTOSW**[1|2|3] is optional nesting level to continue.

	.switch al
	  .case 1
	    .gotosw		; continue .switch al
	    .switch bl
	      .case 1
		.gotosw1	; continue .switch al
		.switch cl
		  .case 1
		    .gotosw2	; continue .switch al
		    .switch dl
		      .case 1
			.gotosw3 ; continue .switch al
			.gotosw2 ; continue .switch bl
			.gotosw1 ; continue .switch cl
			;
			; Direct jump to .switch cl / case 1
			;
			.gotosw1(1)
		    .endsw
		.endsw
	    .endsw
	.endsw


**GOTOSW** can be used in combination with .**IF** _condition_, or a direct jump to .**GOTOSW**(<_case_val_>).

#### See Also

[Directives Reference](readme.md) | [.ENDC](dot_endc.md) | [.SWITCH](dot_switch.md)
