include stdio.inc

	.code
ifdef DEBUG
db_break PROC
	int 3
	ret
db_break ENDP
endif
	END
