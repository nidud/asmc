include string.inc
include io.inc
include direct.inc
include stdlib.inc
include strlib.inc
include dzlib.inc

	.data

externdef envtemp:dword
echooff	  db "@echo off"
CRLF	  db 13,10,0
dzcmd_bat db "dzcmd.bat",0
dzcmd_env db "\dzcmd.env",0

	.code

CreateBatch PROC USES ebx cmd, CallBatch, UpdateEnviron

local	batch[_MAX_PATH]:SBYTE,
	argv0[_MAX_PATH]:SBYTE

	.if osopen( strfcat( addr batch, envtemp, addr dzcmd_bat ), 0, M_WRONLY, A_CREATETRUNC ) != -1
		mov	ebx,eax

		oswrite( ebx, addr echooff, 11 )
		.if CallBatch
			oswrite( ebx, "call ", 5 )
		.endif
		oswrite( ebx, cmd, strlen( cmd ) )
		oswrite( ebx, addr CRLF, 2 )
		.if UpdateEnviron
			mov	ecx,__argv
			strcpy( addr argv0, [ecx] )
			strcat( eax, " /E:" )
			strcat( eax, envtemp )
			strcat( eax, addr dzcmd_env )
			oswrite( ebx, addr argv0, strlen( eax ) )
			oswrite( ebx, addr CRLF, 2 )
		.endif
		_close( ebx )
		strcpy( cmd, addr batch )
	.endif
	ret
CreateBatch ENDP

	END
