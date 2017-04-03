include stdlib.inc
include string.inc
include ctype.inc
include alloc.inc
include direct.inc
include wchar.inc

_ARGV_MAX equ 64

	.data
	argc_max dd _ARGV_MAX

	.code

	option	cstack:on

__setwargv PROC USES esi edi ebx argc, argv:PVOID, cmdline:LPWSTR

  local base, args, count

	mov base,alloca(0x8000) ; Max argument size: 32K
	mov edi,eax
	mov esi,cmdline		; ESI to command string
	mov eax,argc
	mov eax,[eax]
	mov count,eax

	.repeat
		xor eax,eax	; Add a new argument
		mov [edi],ax
		lodsw
		.for : eax == ' ' || (eax >= 9 && eax <= 13) :

			lodsw
		.endf
		.break .if !eax ; end of command string

		xor edx,edx ; "quote from start" in EDX - remove
		xor ecx,ecx ; -I"quoted text"	 in ECX - keep

		.if eax == '"'

			inc edx
			lodsw
		.endif

		.while eax == '"'	; ""A" B"

			inc ecx
			stosw
			lodsw
		.endw

		.while eax

			.break .if !edx && !ecx && (eax == ' ' || (eax >= 9 && eax <= 13))

			.if eax == '"'
				.if ecx
					dec ecx
				.elseif edx
					.break
				.else
					inc ecx
				.endif
			.endif
			stosw
			lodsw
		.endw

		xor	eax,eax
		mov	[edi],ax
		lea	ebx,[edi+2]
		mov	edi,base
		.break .if ax == [edi]

		sub ebx,edi
		memcpy( malloc( ebx ), edi, ebx )

		mov edx,argv
		mov ecx,[edx]
		mov [edx],eax
		add argv,4
		.for ebx=count: ebx: ebx--,
		     edx+=4, eax=[edx], [edx]=ecx, ecx=eax
		.endw
		lea ecx,__argc
		mov eax,argc
		inc DWORD PTR [eax]
		.if eax != ecx

			inc DWORD PTR [ecx]
			mov eax,ecx
		.endif
		mov eax,[eax]
		.if eax == argc_max

			shl eax,1
			mov argc_max,eax
			shl eax,2
			.break .if !malloc( eax )
			mov ebx,__wargv
			mov __wargv,eax
			mov ecx,argc_max
			shl ecx,1
			memcpy( eax, ebx, ecx )
			mov ecx,argv
			sub ecx,ebx
			add eax,ecx
			mov argv,eax
		.endif
	.until WCHAR PTR [esi-WCHAR] == 0
	ret
__setwargv ENDP

	END
