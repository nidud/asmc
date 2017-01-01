include string.inc
include stdio.inc
include alloc.inc

TEST_OVERLAP	equ 1

.data
ALIGN	16
str_1	db 4096-3 dup('x'),"xxx",0
ALIGN	16
str_2	db 4096-3 dup('x'),"xxz",0
ALIGN	16
str_3	db 64 dup('x'),"xxx",0
abcd	db "abcd",0
abc1	db "abc",0
abc2	db "abc",0,"xx"
arg_1	dq str_1
arg_2	dq str_2
arg_3	dq 4096

s1	db "xxxxxxxxxxxxxxxabcxxxx",0
s2	db "xxxxxxxxxxxxxxxabcdxxx",0
s3	db "xxxxxxxxxxxxxxxabcxxxx",0
s4	db "xxxxxxxxxxxxxxxabcdxxx",0
z1	db "xxxxxxxxxxxxxxxabc",0
z2	db "xxxxxxxxxxxxxxxabcd",0
z3	db "xxxxxxxxxxxxxxxabc",0
z4	db "xxxxxxxxxxxxxxxabcd",0
z5	db "abc",0
z6	db "abc ",0
z7	db " "
z8	db 0

table	dq s1,s1,0
	dq s2,s2,0
	dq s3,s3,0
	dq s4,s4,0
	dq s1,s3,0
	dq s3,s1,0
	dq s1,s2,-1
	dq s1,s4,-1
	dq s3,s2,-1
	dq s3,s4,-1
	dq s2,s1,1
	dq s4,s1,1
	dq s2,s3,1
	dq s4,s3,1
	dq z1,z2,1
	dq z1,z4,1
	dq z3,z2,1
	dq z3,z4,1
	dq z2,z1,-1
	dq z4,z1,-1
	dq z2,z3,-1
	dq z4,z3,-1
	dq z6,z5,-1
	dq z5,z6,1
	dq z7,z8,-1
	dq z8,z7,1
	dq 0,0,0

nerror	dq 0

	.code

regress proc uses rsi rdi rbx rbp


	.if	strcmp(arg_1, arg_1)
		printf( "error 1: rax = %I64d (0) strcmp\n", rax )
		inc	nerror
	.endif

	.if	strcmp(addr str_1, addr str_2) != -1
		printf( "error 2: rax = %I64d (-1) strcmp\n", rax )
		inc	nerror
	.endif

	.if	strcmp(addr abc2, addr abc1)
		printf( "error 3: rax = %I64d (0) strcmp\n", rax )
		inc	nerror
	.endif

	.if	strcmp(addr abcd, addr abc1) != 1
		printf( "error 4: rax = %I64d (1) strcmp\n", rax )
		inc	nerror
	.endif

	.if	strcmp(addr abcd, addr abc1) != 1
		printf( "error 5: rax = %I64d (1) strcmp\n", rax )
		inc	nerror
	.endif

	.if	strcmp(addr z5, addr z6) != -1
		printf( "error 6: eax = %I64d (-1) strcmp\n", rax )
		inc	nerror
	.endif

	.if	strcmp(addr z6, addr z5) != 1
		printf( "error 7: eax = %d (1) strcmp\n", rax )
		inc	nerror
	.endif

ifdef TEST_OVERLAP

	.if	VirtualAlloc( 0, 4096, MEM_COMMIT, PAGE_READWRITE )

		mov	rbp,rax
		mov	rbx,rax
		mov	rdi,rax
		mov	rcx,4096
		mov	al,'x'
		rep	stosb
		mov	rdi,4096
		mov	BYTE PTR [rbx+4096-1],0

		lea	rcx,[rbx+15]
		strcmp( rcx, rbx )
		.repeat
			dec	rdi
			inc	rbx
			strcmp( rbx, rbx )
		.until	rdi == 4096 - 33

		VirtualFree( rbp, 0, MEM_RELEASE )
	.endif
endif

	xor	rdi,rdi
	lea	rsi,table
	.repeat
		lodsq
		mov	rdx,rax
		lodsq
		mov	rcx,rax
		call	strcmp
		mov	rdx,rax
		mov	rcx,[rsi-16]
		mov	rbx,[rsi-8]
		lodsq
		.if	rax != rdx
			printf( "\n\ntable %d: rax = %I64d (%I64d) strcmp(%s, %s)\n", rdi, rdx, rax, rbx, rcx )
			inc	nerror
			.break
		.endif
		inc	rdi
		mov	rax,[rsi]
	.until	!rax
	mov	rax,nerror
	test	rax,rax
	ret

regress endp

main	PROC
	call	regress
	jnz	toend
toend:
	mov	rax,nerror
	ret
main	ENDP

	END
