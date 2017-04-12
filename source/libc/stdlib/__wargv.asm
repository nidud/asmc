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
	__wargv	 dd 0
	_wpgmptr dd 0

	.code

Install PROC PRIVATE USES esi edi

local	pgname[260]:word

	mov __wargv,malloc( _ARGV_MAX * 4 )
	;
	; Get the program name pointer from Win32 Base
	;
	GetModuleFileNameW( 0, addr pgname, 260 )
	lea edi,[eax*2+2]
	mov _wpgmptr,malloc(edi)
	memcpy(_wpgmptr, addr pgname, edi)
	mov word ptr [eax+edi-2],0

	mov ecx,__wargv
	mov [ecx],eax

	mov edx,GetCommandLineW()
	xor ecx,ecx
	movzx eax,word ptr [edx]	; skip space

	.while	byte ptr _ctype[eax*2+2] & _SPACE

		add edx,2
		mov ax,[edx]
	.endw

	.if eax == '"'		; if _argv[0] is "quoted"

		mov ecx,eax
		add edx,2
	.endif

	.while	1

		mov ax,[edx]
		add edx,2
		.break .if !eax

		.if eax == ecx

			xor ecx,ecx

		.elseif (eax == ' ' || (eax >= 9 && eax <= 13))

			mov eax,__wargv
			add eax,4

			__setwargv( addr __argc, eax, edx )

			.break
		.endif
	.endw

	inc __argc
	ret
Install ENDP

pragma_init Install, 4

	END
