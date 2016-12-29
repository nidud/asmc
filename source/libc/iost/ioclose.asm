include iost.inc
include io.inc

	.code

ioclose PROC USES eax io:PTR S_IOST
	mov	eax,io
	_close( [eax].S_IOST.ios_file )
	iofree( io )
	ret
ioclose ENDP

	END
