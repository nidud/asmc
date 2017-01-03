include stdlib.inc
include string.inc
include alloc.inc

	.code

getenvp PROC USES ecx edx enval:LPSTR

  local buf[2048]:byte

	.if GetEnvironmentVariable( enval, addr buf, 2048 )

		salloc( addr buf )
	.endif
	ret

getenvp ENDP

	END
