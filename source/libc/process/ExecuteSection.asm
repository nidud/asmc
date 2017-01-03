include process.inc
include string.inc
include ini.inc

	.code

ExecuteSection PROC USES esi section:LPSTR
  local cmd[256]:byte
	xor	esi,esi
	.while	inientryid( section, esi )
		mov	edx,eax
		system( strcpy( addr cmd, edx ) )
		inc	esi
	.endw
	ret
ExecuteSection ENDP

	END
