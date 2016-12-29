include stdio.inc

PUBLIC	_stdbuf

	.data
	_stdbuf dd 0	; buffer for stdout and stderr
		dd 0

	END
