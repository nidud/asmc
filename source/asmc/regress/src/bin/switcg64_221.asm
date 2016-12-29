	.x64
	.model	flat, fastcall
	.code

	.switch rax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	OPTION SWITCH:PASCAL, SWITCH:TABLE

	.switch rax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	OPTION SWITCH:REGAX
	OPTION SWITCH:NOTEST

	.switch rax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	.switch al
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	OPTION SWITCH:NOTEST

	.switch al
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	END

