include stdio.inc
include io.inc
include string.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

puts	PROC string:LPSTR
	_write( stdout._file, string, strlen( string ) )
	ret
puts	ENDP

	END
