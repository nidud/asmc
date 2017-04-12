include stdlib.inc
include string.inc
include ctype.inc
include alloc.inc
include crtl.inc
include winbase.inc

_ARGV_MAX equ 64

	.data
	__argc	dd 0
	__argv	dq 0
	_pgmptr dq 0

	.code

	OPTION	WIN64:3, STACKBASE:rsp

Install PROC PRIVATE USES rsi
local	pgname[512]:SBYTE
	malloc( _ARGV_MAX * 8 )
	mov	__argv,rax
	;
	; Get the program name pointer from Win32 Base
	;
	GetModuleFileNameA( 0, addr pgname, 512 )
	mov	_pgmptr,salloc( addr pgname )
	mov	rcx,__argv
	mov	[rcx],rax
	mov	rsi,GetCommandLine()

	xor	rcx,rcx
	movzx	rax,BYTE PTR [rsi]	; skip space
	lea	r9,_ctype
	.while	BYTE PTR [r9+rax*2+2] & _SPACE
		add	rsi,1
		mov	al,[rsi]
	.endw
	.if	al == '"'		; if _argv[0] is "quoted"
		mov	rcx,rax
		inc	rsi
	.endif
	.repeat
		mov	al,[rsi]
		inc	rsi
		.break .if !al
		.if	rax == rcx
			xor	rcx,rcx
		.elseif BYTE PTR [r9+rax+1] & _SPACE
			mov	rdx,__argv
			add	rdx,8
			__setargv( addr __argc, rdx, rsi )
			.break
		.endif
	.until	0
	inc	__argc
	ret
Install ENDP

pragma_init Install, 4

	END
