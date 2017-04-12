; CRT.ASM--
;
; Startup module for Win64
;
_WIN64	equ 1

include asmcver.inc
include stdlib.inc
include crtl.inc
include tchar.inc

_INIT	segment para flat public 'INIT'
IStart	label byte
_INIT	ENDS
_IEND	segment para flat public 'INIT'
IEnd	label byte
_IEND	ends
_EXIT	segment para flat public 'EXIT'
EStart	label byte
_EXIT	ends
_EEND	segment para flat public 'EXIT'
EEnd	label byte
_EEND	ends

ifdef	_DLL
PROCESS_DETACH equ 0
PROCESS_ATTACH equ 1
C0END	equ <LibMain>
else
_tmain	proto
C0END	equ <mainCRTStartup>
endif
	.code

	dd 495A440Ah
	dd 564A4A50h
	db VERSSTR

ifdef	_DLL

LibMain proc hModule:qword, dwReason, dwReserved

	.if edx == PROCESS_DETACH
		lea rcx,EStart
		lea rdx,EEnd
		__initialize(rcx, rdx)
	.elseif edx == PROCESS_ATTACH
		lea rcx,IStart
		lea rdx,IEnd
		__initialize(rcx, rdx)
	.endif
	mov eax,1
	ret

LibMain endp

else

mainCRTStartup proc

	lea rcx,IStart
	lea rdx,IEnd
	__initialize(rcx, rdx)
ifndef	_NOARGV
	mov ecx,__argc
	mov rdx,__targv
	mov r8,_tenviron
	sub rsp,0x28
endif
	_tmain()
	exit( eax )

mainCRTStartup endp
endif
	END	C0END
