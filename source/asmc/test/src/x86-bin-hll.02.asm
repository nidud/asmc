;
; v2.22 Nesting error in .CASE with .WHILE/.REPEAT
;

    .model  small
    .code

    .switch al
      .case 1
	    .repeat
		.endc	; fatal error A1011: directive must be in control block
			;
	    .until 1
    .endsw

    END

