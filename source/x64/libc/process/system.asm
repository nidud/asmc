include stdlib.inc
include process.inc
include string.inc
include alloc.inc
include direct.inc

MAXCMDL equ 8000h

EXTRN	comspec:QWORD
EXTRN	comspex:QWORD
PUBLIC	cp_quote

	.data
	cp_quote db '"',0

	.code

	OPTION	WIN64:3, STACKBASE:rsp

system	PROC USES rdi rsi rbx r12 string:LPSTR

	local	arg0[_MAX_PATH]:BYTE

	.if	malloc( MAXCMDL )
		mov	rbx,rax
		mov	BYTE PTR [rax],0
		mov	rdi,string
		mov	r12d,' '
		.if	BYTE PTR [rdi] == '"'
			inc	rdi
			mov	r12b,'"'
		.endif
		xor	rsi,rsi
		.if	strchr( rdi, r12d )
			mov	BYTE PTR [rax],0
			mov	rsi,rax
		.endif
		strncpy( addr arg0, rdi, _MAX_PATH-1 )
		.if	rsi
			mov	[rsi],r12b
			.if	dl == '"'
				inc rsi
			.endif
		.else
			strlen( string )
			add	rax,string
			mov	rsi,rax
		.endif
		mov	rdi,rsi
		strcat( strcpy( rbx, comspec ), " " )
		mov	rdx,comspex
		.if	BYTE PTR [rdx]
			strcat( strcat( rbx, rdx ), " " )
		.endif
		lea	rsi,arg0
		lea	r12,cp_quote
		.if	strchr( rsi, ' ' )
			strcat( strcat( strcat( rbx, r12 ), rsi ), r12 )
		.else
			strcat( rbx, rsi )
		.endif
		process( 0, strcat( rbx, rdi ), 0 )
		free( rbx )
	.endif
	ret
system	ENDP

	END
