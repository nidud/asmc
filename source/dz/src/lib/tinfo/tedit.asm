include tinfo.inc

	.code

tedit	PROC fname:LPSTR, line

	.if topen( fname, 0 )

		tialigny( tinfo, line )
		tmodal()
	.endif
	ret

tedit	ENDP

	END
