include stdio.inc
include signal.inc

    .code

    assume r11: ptr EXCEPTION_CONTEXT

PrintContext proc ExcContext:ptr EXCEPTION_CONTEXT, ExcRecord:ptr EXCEPTION_RECORD

  local flags[17]:sbyte

    mov r10,rdx ; ExcRecord
    mov r11,rcx ; ExcContext

    mov rax,0x3030303030303030
    lea rdx,flags
    mov [rdx],rax
    mov [rdx+8],rax
    mov byte ptr [rdx+16],0
    mov eax,[r11].EFlags
    mov rcx,16
    .repeat
	shr eax,1
	adc byte ptr [rdx+rcx-1],0
    .untilcxz

    printf(
	"This message is created due to unrecoverable error\n"
	"and may contain data necessary to locate it.\n"
	"\n"
	"\tException Code: %08X\n"
	"\tException Flags %08X\n"
	"\n"
	"\t  regs: RAX: %016X R8:  %016X\n"
	"\t\tRBX: %016X R9:  %016X\n"
	"\t\tRCX: %016X R10: %016X\n"
	"\t\tRDX: %016X R11: %016X\n"
	"\t\tRSI: %016X R12: %016X\n"
	"\t\tRDI: %016X R13: %016X\n"
	"\t\tRBP: %016X R14: %016X\n"
	"\t\tRSP: %016X R15: %016X\n"
	"\t\tRIP: %016X\n"
	"\n"
	"\t flags: %s\n"
	"\t        r n oditsz a p c\n\n",
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
	[r11]._Rip, &flags)
    ret

PrintContext endp

    END
