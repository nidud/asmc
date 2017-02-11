include tinfo.inc

IFDEF DEBUG
;__TIMEIT__ equ 1
ENDIF
include timeit.inc

	.code

tedit	PROC fname:LPSTR, line

	timeit_init
	timeit_start 0, "tedit"

	.if	topen( fname, 0 )

		tialigny( tinfo, line )
		tmodal()
	.endif

	timeit_end 0
	timeit_exit 10, "tedit"
	ret

tedit	ENDP

	END
