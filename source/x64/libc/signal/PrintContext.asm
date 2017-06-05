include stdio.inc
include signal.inc

	.data

format	label byte
	db "This message is created due to unrecoverable error",10
	db "and may contain data necessary to locate it.",10
	db 10
	db 9, "Exception Code: %08X", 10
	db 9, "Exception Flags %08X", 10
	db 10
	db 9,'  regs: RAX: %016X R8:  %016X',10
	db 9,9, 'RBX: %016X R9:  %016X',10
	db 9,9, 'RCX: %016X R10: %016X',10
	db 9,9, 'RDX: %016X R11: %016X',10
	db 9,9, 'RSI: %016X R12: %016X',10
	db 9,9, 'RDI: %016X R13: %016X',10
	db 9,9, 'RBP: %016X R14: %016X',10
	db 9,9, 'RSP: %016X R15: %016X',10
	db 9,9, 'RIP: %016X',10
	db 10
	db 9,' flags: '
bits	db '0000000000000000',10
	db 9,'        r n oditsz a p c',10
	db 10,0

	.code

	OPTION	WIN64:2, STACKBASE:rsp

PrintContext PROC ExcContext:PTR EXCEPTION_CONTEXT, ExcRecord:PTR EXCEPTION_RECORD

	mov	r10,rdx ; ExcRecord
	mov	r11,rcx ; ExcContext

	mov	rax,3030303030303030h
	lea	rdx,bits
	mov	[rdx],rax
	mov	[rdx+8],rax

	ASSUME	r11:PTR EXCEPTION_CONTEXT

	mov	eax,[r11].EFlags
	mov	rcx,16
	.repeat
		shr	eax,1
		adc	byte ptr [rdx+rcx-1],0
	.untilcxz

	printf( addr format,
		[r10].EXCEPTION_RECORD.ExceptionCode,
		[r10].EXCEPTION_RECORD.ExceptionFlags,
		[r11]._Rax, [r11]._R8,
		[r11]._Rbx, [r11]._R9,
		[r11]._Rcx, [r11]._R10,
		[r11]._Rdx, [r11]._R11,
		[r11]._Rsi, [r11]._R12,
		[r11]._Rdi, [r11]._R13,
		[r11]._Rbp, [r11]._R14,
		[r11]._Rsp, [r11]._R15,
		[r11]._Rip )

	ret
PrintContext ENDP

	END
