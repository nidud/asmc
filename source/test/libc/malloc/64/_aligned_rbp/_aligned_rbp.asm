;
; In case RBP/leave is used add RSP is not needed:
;
; *	 add rsp, 48 + @ReservedStack
; *	 leave
;
include stdio.inc
include malloc.inc

	.code

	option cstack:on

main	proc

local	a16:oword ; RSP is aligned 16
local	a8: qword
local	a4: dword
local	a1: byte

	lea rdi,a16
	.if !( rdi & 16-1 )

		printf( "Address a16: %p\n", rdi )
		printf( "Address a8:  %p\n", addr a8 )
		printf( "Address a4:  %p\n", addr a4 )
		printf( "Address a1:  %p\n", addr a1 )
		xor	eax,eax
	.else
		printf( "Error in aligned memory." )
		mov	eax,1
	.endif
	ret

main	endp

	END
