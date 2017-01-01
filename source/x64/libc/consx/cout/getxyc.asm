include consx.inc
include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

getxyc	proc uses rcx rdx x, y

local	NumberOfCharsRead:QWORD,
	Character:QWORD

	xor	rax,rax
	mov	Character,rax
	mov	NumberOfCharsRead,rax
	mov	al,dl
	shl	eax,16
	mov	al,cl

	ReadConsoleOutputCharacter(
		hStdOutput,
		addr Character,
		1,
		eax,
		addr NumberOfCharsRead )

	mov	rax,Character
	and	rax,0FFh
	ret

getxyc	endp

	END
