; Arguments are expanded from start of array, existing pushed back. This to
; enable insertion of additional arguments from the environment or from a @file
;
; If a @file have these arguments:
;	-a
;	-b -c
; in command:
;	PROG @file -x -y *.txt
; this expands to (second call):
;	PROG @<file> -a -b -c -x -y *.txt
;
; On the second call the local argc is 3 and argv points to [-x] (&_argv[2])
; On return the local argc is 6 and argv points to [-a] (&_argv[2])
;
; Note: The main array (_argv) is allocated in _argv.asm
;
include stdlib.inc
include string.inc
include ctype.inc
include alloc.inc
include direct.inc

_ARGV_MAX equ 64

	.data
	argc_max dd _ARGV_MAX

	.code

	option	cstack:on

__setargv PROC USES esi edi ebx argc, argv:PVOID, cmdline:LPSTR

  local base, args, count

	alloca( 8000h )		; Max argument size: 32K
	mov	base,eax
	mov	edi,eax
	mov	esi,cmdline	; ESI to command string
	mov	eax,argc
	mov	eax,[eax]
	mov	count,eax

	.repeat
		xor	eax,eax ; Add a new argument
		mov	[edi],al
		.repeat
			lodsb	; skip space
		.until !( __ctype[eax+1] & _SPACE )
		.break .if !eax ; end of command string

		xor	edx,edx ; "quote from start" in EDX - remove
		xor	ecx,ecx ; -I"quoted text"    in ECX - keep

		.if	eax == '"'
			add	edx,1
			lodsb
		.endif
		.while	eax == '"'	; ""A" B"
			add	ecx,1
			stosb
			lodsb
		.endw
		.while	eax
			.break .if !edx && !ecx && __ctype[eax+1] & _SPACE
			.if	eax == '"'
				.if	ecx
					dec	ecx
				.elseif edx
					.break
				.else
					inc	ecx
				.endif
			.endif
			stosb
			lodsb
		.endw
		xor	eax,eax
		mov	[edi],al
		mov	edi,base
		.break .if al == [edi]
		salloc( edi )
		mov	edx,argv
		mov	ecx,[edx]
		mov	[edx],eax
		add	argv,4
		mov	ebx,count
		.while	ebx
			add	edx,4
			mov	eax,[edx]
			mov	[edx],ecx
			mov	ecx,eax
			dec	ebx
		.endw
		lea	ecx,_argc
		mov	eax,argc
		inc	DWORD PTR [eax]
		.if	eax != ecx
			inc	DWORD PTR [ecx]
			mov	eax,ecx
		.endif
		mov	eax,[eax]
		.if	eax == argc_max
			shl	eax,1
			mov	argc_max,eax
			shl	eax,2
			.break .if !malloc( eax )
			mov	ebx,_argv
			mov	_argv,eax
			mov	ecx,argc_max
			shl	ecx,1
			memcpy( eax, ebx, ecx )
			mov	ecx,argv
			sub	ecx,ebx
			add	eax,ecx
			mov	argv,eax
		.endif
	.until	BYTE PTR [esi-1] == 0
	ret
__setargv ENDP

	END
