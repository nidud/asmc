include stdlib.inc
include string.inc
include ctype.inc
include alloc.inc
include crtl.inc
include winbase.inc

;
; Size of array for command line arguments
;
_ARGV_MAX equ 64

	.data
	__argv	dd 0
	_pgmptr dd 0

	.code

Install PROC PRIVATE USES esi edi

local	pgname[260]:SBYTE

	mov __argv,malloc( _ARGV_MAX * 4 )
	;
	; Get the program name pointer from Win32 Base
	;
	GetModuleFileNameA( 0, addr pgname, 260 )
	lea	eax,[eax+1]
	mov	_pgmptr,malloc( eax )
	strcpy( _pgmptr, addr pgname )
	mov	ecx,__argv
	mov	[ecx],eax

	mov	edx,GetCommandLineA()
	xor	ecx,ecx
	movzx	eax,BYTE PTR [edx] ; skip space

	.while	byte ptr _ctype[eax*2+2] & _SPACE

		add edx,1
		mov al,[edx]
	.endw

	.if eax == '"'		; if _argv[0] is "quoted"

		mov ecx,eax
		add edx,1
	.endif

	.while	1

		mov al,[edx]
		add edx,1
		.break .if !eax

		.if eax == ecx

			xor ecx,ecx

		.elseif (eax == ' ' || (eax >= 9 && eax <= 13))

			mov eax,__argv
			add eax,4

			__setargv( addr __argc, eax, edx )

			.break
		.endif
	.endw

	inc __argc
	ret
Install ENDP

pragma_init Install, 4

	END
