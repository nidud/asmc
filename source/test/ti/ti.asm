include io.inc
include direct.inc
include time.inc
include errno.inc
include stdio.inc
include stdlib.inc
include string.inc
include process.inc

.data

tiinfo		db "TimeIt Version 1.0. Public Domain",10
		db 10
		db "USAGE: TI <command> <args>",10,0
comspec_type	dd 1

.code

main	proc c uses ebx edi esi

local	cmd[_MAX_PATH]:byte
local	com[_MAX_PATH]:byte

	mov	edi,_argc
	mov	esi,_argv
	.if	edi > 1

		lea	ebx,cmd
		lodsd
		lodsd
		strcpy( ebx, eax )
		sub	edi,2

		.while	edi
			strcat( ebx, " " )
			lodsd
			strcat( ebx, eax )
			dec	edi
		.endw

		mov	edi,GetTickCount()
		system( ebx )
		sub	GetTickCount(),edi
		printf( "%5d ClockTicks: %s\n", eax, ebx )
		xor	eax,eax
	.else
		printf( addr tiinfo )
	.endif
	ret

main	endp

	end
