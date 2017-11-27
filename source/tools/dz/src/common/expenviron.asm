include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

	.code ; expand '%TEMP%' to 'C:\TEMP'


expenviron PROC USES ecx string:LPSTR
  local buffer
	alloca( 8000h )
	mov	buffer,eax
	ExpandEnvironmentStrings( string, buffer, 8000h-1 )
	strcpy( string, buffer )
	ret
expenviron ENDP

	END
