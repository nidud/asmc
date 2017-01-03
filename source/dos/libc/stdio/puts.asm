; PUTS.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include string.inc

	.code

puts	PROC _CType PUBLIC string:DWORD
	invoke strlen,string
	invoke write,stdout.iob_file,string,ax
	ret
puts	ENDP

	END
