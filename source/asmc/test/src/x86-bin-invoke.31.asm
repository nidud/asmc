
;--- up to v2.12, the qword param
;--- wasn't pushed correctly because
;--- the assembler assumed current mode
;--- was 64-bit. 

	.model small
	.x64p
	.stack 1024
	.code

tproc proto stdcall :dword, :qword, :dword

tproc proc stdcall a1:dword, a2:qword, a3:dword
	ret
tproc endp

start16:
	mov ax,4c00h
	int 21h
	invoke tproc, 0, 1, 2

	end start16
