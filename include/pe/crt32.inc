__PE__	equ 1
include pe/kernel32.inc
include pe/msvcrt.inc

	option	dllimport:none
	option	cstack:on

	.data
	_argc		dd 0
	_argv		dd 0
	_environ	dd 0
	.code

main	proto

CRT32	proc
local	newmode:	dword,
	startinfo:	dword

	xor	eax,eax
	mov	newmode,eax
	lea	eax,newmode
	mov	startinfo,eax

	__getmainargs( addr _argc, addr _argv, addr _environ, 0, eax )
	exit( main() )
	ret
CRT32	endp
