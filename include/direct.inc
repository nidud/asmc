.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
IFDEF __PE__
option		dllimport:<msvcrt>
ENDIF

_MAX_PATH	equ 260
_MAX_DRIVE	equ 3
_MAX_DIR	equ 256
_MAX_FNAME	equ 256
_MAX_EXT	equ 256

_getdrive	PROTO __cdecl
_chdrive	PROTO __cdecl :SINT
_chdir		PROTO __cdecl :LPSTR
_mkdir		PROTO __cdecl :LPSTR
_rmdir		PROTO __cdecl :LPSTR
_getcwd		PROTO __cdecl :LPSTR, :SINT
_getdcwd	PROTO __cdecl :SINT, :LPSTR, :SINT
_wchdir		PROTO __cdecl :LPWSTR
_wmkdir		PROTO __cdecl :LPWSTR
_wrmdir		PROTO __cdecl :LPWSTR
_wgetcwd	PROTO __cdecl :LPWSTR, :SINT
_wgetdcwd	PROTO __cdecl :SINT, :LPWSTR, :SINT

IFNDEF __PE__

__allocwpath	PROTO __cdecl :LPSTR
ifdef __DZ__
externdef	_diskflag:DWORD
endif

ENDIF
.pragma list(pop)
