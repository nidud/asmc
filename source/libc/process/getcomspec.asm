include stdlib.inc
include alloc.inc
include io.inc
include ini.inc
include string.inc
include process.inc
include crtl.inc

externdef	__comspec:byte

	.code

getcomspec PROC USES esi com:ULONG

	mov esi,com
	mov comspec_type,esi

	__initcomspec()
	strcpy( __pCommandArg, "/C" )

	.if esi && inientryid( addr __comspec, 0 )

		mov esi,eax
		.if !_access( expenviron( eax ), 0 )

			free  ( __pCommandCom )
			mov	__pCommandCom,salloc( esi )

			mov	eax,__pCommandArg
			mov	byte ptr [eax],0
			.if	inientryid( addr __comspec, 1 )

				expenviron( eax )
				strncpy( __pCommandArg, eax, 64-1 )
			.endif
		.endif
	.endif
	mov	eax,__pCommandCom
	ret
getcomspec ENDP

Install:
	.if !_stricmp( strfn( __pCommandCom ), "cmd.exe" )

		mov comspec_type,1
	.endif
	ret

pragma_init Install, 102

	END
