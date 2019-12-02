.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
.pragma comment(lib, libc, msvcrt)

_MAX_PATH	equ 260
_MAX_DRIVE	equ 3
_MAX_DIR	equ 256
_MAX_FNAME	equ 256
_MAX_EXT	equ 256

_getdrive	proto __cdecl
_chdrive	proto __cdecl :SINT
_chdir		proto __cdecl :LPSTR
_mkdir		proto __cdecl :LPSTR
_rmdir		proto __cdecl :LPSTR
_getcwd		proto __cdecl :LPSTR, :SINT
_getdcwd	proto __cdecl :SINT, :LPSTR, :SINT
_wchdir		proto __cdecl :LPWSTR
_wmkdir		proto __cdecl :LPWSTR
_wrmdir		proto __cdecl :LPWSTR
_wgetcwd	proto __cdecl :LPWSTR, :SINT
_wgetdcwd	proto __cdecl :SINT, :LPWSTR, :SINT

ifndef _MSVCRT
__allocwpath	proto __cdecl :LPSTR
endif
.pragma list(pop)
