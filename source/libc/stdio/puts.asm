include stdio.inc
include io.inc
include string.inc

	.code

puts	PROC string:LPSTR
	_write( stdout.iob_file, string, strlen( string ) )
	ret
puts	ENDP

	END
