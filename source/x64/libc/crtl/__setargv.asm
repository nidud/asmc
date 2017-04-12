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
; On the second call the local argc is 3 and argv points to [-x] (&__argv[2])
; On return the local argc is 6 and argv points to [-a] (&__argv[2])
;
; Note: The main array (__argv) is allocated in __argv.asm
;
include stdlib.inc
include string.inc
include ctype.inc
include alloc.inc
include direct.inc

_ARGV_MAX equ 64

	.data
	argc_max dq _ARGV_MAX

	.code

	OPTION	WIN64:3, STACKBASE:rsp

__setargv PROC USES rsi rdi rbx rbp r12 r13 r14 r15 argc:SIZE_T, argv:PVOID, cmdline:LPSTR


	malloc( 8000h )		; Max argument size: 32K
	mov	r12,rax
	jz	toend

	mov	rdi,rax
	mov	rsi,cmdline	; ESI to command string
	mov	rax,argc
	mov	rax,[rax]
	mov	r13,rax

	.repeat
		lea	r9,_ctype
		xor	rax,rax ; Add a new argument
		mov	[rdi],al
		.repeat
			lodsb	; skip space
		.until !( BYTE PTR [r9+rax*2+2] & _SPACE )
		.break .if !rax ; end of command string

		xor	rdx,rdx ; "quote from start" in EDX - remove
		xor	rcx,rcx ; -I"quoted text"    in ECX - keep

		.if	rax == '"'
			add	rdx,1
			lodsb
		.endif
		.while	rax == '"'	; ""A" B"
			add	rcx,1
			stosb
			lodsb
		.endw
		.while	rax
			.break .if !rdx && !rcx && BYTE PTR [r9+rax+1] & _SPACE
			.if	rax == '"'
				.if	rcx
					dec	rcx
				.elseif rdx
					.break
				.else
					inc	rcx
				.endif
			.endif
			stosb
			lodsb
		.endw
		xor	rax,rax
		mov	[rdi],al
		mov	rdi,r12
		.break .if al == [rdi]
		salloc( rdi )
		mov	rdx,argv
		mov	rcx,[rdx]
		mov	[rdx],rax
		add	argv,8
		mov	rbx,r13
		.while	rbx
			add	rdx,8
			mov	rax,[rdx]
			mov	[rdx],rcx
			mov	rcx,rax
			dec	rbx
		.endw
		lea	rcx,__argc
		mov	rax,argc
		inc	QWORD PTR [rax]
		.if	rax != rcx
			inc	QWORD PTR [rcx]
			mov	rax,rcx
		.endif
		mov	rax,[rax]
		.if	rax == argc_max
			shl	rax,1
			mov	argc_max,rax
			shl	rax,3
			.break .if !malloc( rax )
			mov	rbx,__argv
			mov	__argv,rax
			mov	r8,argc_max
			shl	r8,1
			memcpy( rax, rbx, r8 )
			mov	rcx,argv
			sub	rcx,rbx
			add	rax,rcx
			mov	argv,rax
		.endif
	.until	BYTE PTR [rsi-1] == 0

	free( r12 )

toend:
	ret
__setargv ENDP

	END
