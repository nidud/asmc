include io.inc
include direct.inc
include string.inc

externdef	envtemp:DWORD
removefile	proto :LPSTR

	.code

removetemp PROC path:LPSTR

  local nbuf[_MAX_PATH]:BYTE

	removefile( strfcat( addr nbuf, envtemp, path ) )
	ret

removetemp ENDP

	END
