include crtl.inc
include stdlib.inc
include process.inc
include malloc.inc
include winbase.inc

PUBLIC	__pCommandCom
PUBLIC	__pCommandArg
PUBLIC	__comspec

	.data

default		db "COMMAND",0
__comspec	db "Comspec",0
command_arg	db "/C",0
		db 61 dup(0)

__pCommandCom	LPSTR default
__pCommandArg	LPSTR command_arg

	.code

__initcomspec PROC

	local buffer[1024]:BYTE

	.if	comspec_type

		SearchPath(NULL, "cmd.exe", NULL, 1024, addr buffer, NULL)
	.else

		GetEnvironmentVariable(addr __comspec, addr buffer, 1024)
	.endif

	.if	eax

		free(__pCommandCom)
		mov  __pCommandCom,_strdup(addr buffer)
	.endif
	ret

__initcomspec ENDP

pragma_init __initcomspec, 60

	END
