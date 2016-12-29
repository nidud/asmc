	.186
	.model	small
	.code

	.switch ax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	OPTION SWITCH:PASCAL, SWITCH:TABLE

	.switch ax
	  .case 'A','C','D','E','F','G','H','I'
	  .default
	.endsw

	OPTION SWITCH:REGAX
	OPTION SWITCH:NOTEST

	.switch ax
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
