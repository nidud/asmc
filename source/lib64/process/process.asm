; PROCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include process.inc
include string.inc
include conio.inc
include crtl.inc

PUBLIC	errorlevel	; Exit Code from GetExitCodeProcess

	.data
	errorlevel dd 0

	.code

	OPTION	WIN64:3, STACKBASE:rsp

process PROC USES rsi rdi program:LPSTR, command:LPSTR, CreationFlags:DWORD

local	PI:PROCESS_INFORMATION,
	SINFO:STARTUPINFO,
	ConsoleMode:dword

	xor	eax,eax
	mov	errno,eax
	mov	errorlevel,eax

	lea	rdi,PI
	mov	rsi,rdi
	mov	ecx,sizeof( PROCESS_INFORMATION )
	rep	stosb
	lea	rdi,SINFO
	mov	ecx,sizeof( STARTUPINFO )
	rep	stosb
	lea	rdi,SINFO
	mov	SINFO.cb,sizeof( STARTUPINFO )

	SetErrorMode( OldErrorMode )
	GetConsoleMode( hStdInput, addr ConsoleMode )
	mov	r10d,CreationFlags
	and	r10d,CREATE_NEW_CONSOLE or DETACHED_PROCESS
	xor	eax,eax
	CreateProcess( program, command, rax, rax, eax, r10d, rax, rax, rdi, rsi )
	mov	rdi,rax
	mov	rsi,PI.hProcess
	_dosmaperr(GetLastError())
	test	rdi,rdi
	jz	error
	test	CreationFlags,_P_NOWAIT
	jnz	@F
	WaitForSingleObject( rsi, INFINITE )
	GetExitCodeProcess( rsi, addr errorlevel )
@@:
	CloseHandle( rsi )
	CloseHandle( PI.hThread )
error:
	GetStdHandle( STD_OUTPUT_HANDLE )
	mov	hStdOutput,rax
	GetStdHandle( STD_INPUT_HANDLE )
	mov	hStdInput,rax
	SetConsoleMode( rax, ConsoleMode )
	SetErrorMode( SEM_FAILCRITICALERRORS )
	mov	eax,edi
	ret
process ENDP

	END
