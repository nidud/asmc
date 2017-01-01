include stdio.inc

PUBLIC	_stdbuf

	.data
	_stdbuf dq 0	; buffer for stdout and stderr
		dq 0

	END
