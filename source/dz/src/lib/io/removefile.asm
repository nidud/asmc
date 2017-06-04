include io.inc
include dzlib.inc

	.code

removefile PROC file:LPSTR
	setfattr( file, 0 )
	remove( file )
	ret
removefile ENDP

	END
