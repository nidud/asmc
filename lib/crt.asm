; CRT.ASM--
;
; Startup module for Win32
;
_WIN32	equ 1

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
C0END		equ <LibMain>
PROCESS_DETACH	equ 0
PROCESS_ATTACH	equ 1
else
ifdef	_WATCOM
extern	main_:ABS
_lkmain equ <main_>
else
_tmain	proto c
_lkmain equ <_tmain>
endif
ifndef	_NOARGV
extern	__targv:dword
extern	_tenviron:dword
endif
C0END	equ <mainCRTStartup>
endif
	.code

	dd 495A440Ah
	dd 564A4A50h
	db VERSSTR

ifdef	_DLL

LibMain proc hModule:qword, dwReason, dwReserved

	.if dwReason == PROCESS_DETACH
		lea ecx,EStart
		lea edx,EEnd
		__initialize(ecx, edx)
	.elseif dwReason == PROCESS_ATTACH
		lea ecx,IStart
		lea edx,IEnd
		__initialize(ecx, edx)
	.endif
	mov eax,1
	ret

LibMain endp

else

mainCRTStartup PROC

	lea ecx,IStart
	lea edx,IEnd
	__initialize(ecx, edx)

ifndef	_NOARGV
	mov ecx,__argc
	mov edx,__targv
	mov ebx,_tenviron
 ifdef	_WATCOM
	mov	eax,ecx
 else
	push	ebx
	push	edx
	push	ecx
 endif
endif
	exit( _lkmain() )

mainCRTStartup endp
endif
	END	C0END
