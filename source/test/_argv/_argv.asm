include io.inc
include string.inc
include stdlib.inc

.code

main	proc c

local	lf,
	lpNumberOfBytesWritten,
	hStdOut

	mov	esi,_argv
	mov	edi,_argc
	mov	lf,0A0Dh
	mov	hStdOut,GetStdHandle( STD_OUTPUT_HANDLE )

	.while	edi

		lodsd
		mov	ebx,eax
		strlen( ebx )
		mov	edx,eax
		WriteFile(
			hStdOut,
			ebx,
			edx,
			addr lpNumberOfBytesWritten,
			0 )
		WriteFile(
			hStdOut,
			addr lf,
			2,
			addr lpNumberOfBytesWritten,
			0 )
		dec	edi
	.endw

	xor	eax,eax
	ret

main	endp

	end
