include stdlib.inc
include string.inc
include ctype.inc
include alloc.inc
include crtl.inc
include winbase.inc

IFDEF	_UNICODE
XC	equ <ax>
ARGV	equ <__wargv>
PGMPTR	equ <_wpgmptr>
ELSE
XC	equ <al>
ARGV	equ <__argv>
PGMPTR	equ <_pgmptr>
ENDIF
;
; Size of array for command line arguments
;
_ARGV_MAX equ 64

	.data
	__argc dd 0
	ARGV   dd 0
	PGMPTR dd 0

	.code

Install PROC PRIVATE USES esi edi

local	pgname[260]:TCHAR

	mov ARGV,malloc( _ARGV_MAX * 4 )
	;
	; Get the program name pointer from Win32 Base
	;
	GetModuleFileName( 0, addr pgname, 260 )
IFDEF	_UNICODE
	lea	eax,[eax*2+2]
ELSE
	lea	eax,[eax+1]
ENDIF
	mov	PGMPTR,malloc( eax )
	lstrcpy( PGMPTR, addr pgname )
	mov	ecx,ARGV
	mov	[ecx],eax

	mov	edx,GetCommandLine()
	xor	ecx,ecx
	movzx	eax,TCHAR PTR [edx]	; skip space

	.while	byte ptr _ctype[eax*2+2] & _SPACE

		add edx,TCHAR
		mov XC,[edx]
	.endw

	.if	eax == '"'		; if _argv[0] is "quoted"

		mov ecx,eax
		add edx,TCHAR
	.endif

	.while	1

		mov XC,[edx]
		add edx,TCHAR
		.break .if !eax

		.if eax == ecx

			xor ecx,ecx

		.elseif (eax == ' ' || (eax >= 9 && eax <= 13))

			mov eax,ARGV
			add eax,4

			__setargv( addr __argc, eax, edx )

			.break
		.endif
	.endw

	inc	__argc
	ret
Install ENDP

pragma_init Install, 4

	END
