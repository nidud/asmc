include stdlib.inc
include string.inc
include ctype.inc
include alloc.inc
include crtl.inc
;
; Size of array for command line arguments
;
_ARGV_MAX equ 64

	.data
	_argc	dd 0
	_argv	dd 0
	_pgmptr dd 0

	.code

Install PROC PRIVATE

local	pgname[260]:BYTE

	mov	_argv,malloc( _ARGV_MAX * 4 )
	;
	; Get the program name pointer from Win32 Base
	;
	GetModuleFileNameA( 0, addr pgname, 260 )
	mov	_pgmptr,salloc( addr pgname )
	mov	ecx,_argv
	mov	[ecx],eax
	mov	edx,GetCommandLine()
	xor	ecx,ecx
	movzx	eax,BYTE PTR [edx]	; skip space
	.while	__ctype[eax+1] & _SPACE
		add	edx,1
		mov	al,[edx]
	.endw
	.if	eax == '"'		; if _argv[0] is "quoted"
		mov	ecx,eax
		inc	edx
	.endif

	.while	1

		mov	al,[edx]
		inc	edx
		.break .if !eax

		.if	eax == ecx

			xor	ecx,ecx
		.elseif __ctype[eax+1] & _SPACE

			mov	eax,_argv
			add	eax,4
			__setargv( addr _argc, eax, edx )

			.break
		.endif
	.endw

	inc	_argc
	ret
Install ENDP

pragma_init Install, 4

	END
