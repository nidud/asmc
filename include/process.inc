.pragma list(push, 0)

ifndef __LIBC_INC
 include libc.inc
endif

.pragma comment(lib, libc, msvcrt)

_P_WAIT		equ 0
_P_NOWAIT	equ 1
_OLD_P_OVERLAY	equ 2
_P_NOWAITO	equ 3
_P_DETACH	equ 4

; CreationFlags: CREATE_NEW_CONSOLE, DETACHED_PROCESS

system		PROTO lpCommand:LPSTR
process		PROTO lpProgram:LPSTR, lpCommand:LPSTR, CreationFlags:DWORD

externdef	errorlevel:DWORD	; Exit Code from GetExitCodeProcess
externdef	comspec_type:DWORD	; 1 if CMD.EXE, 0 if %comspec%

externdef	__pCommandCom:LPSTR	; "C:\Windows\system32\cmd.exe"
externdef	__pCommandArg:LPSTR	; "/C "

__initcomspec	proto	; Auto install..

CreateConsole	PROTO :LPSTR, :DWORD
CreateBatch	PROTO :LPSTR, :DWORD, :DWORD
CmdIsExe	PROTO :LPSTR

.pragma list(pop)
