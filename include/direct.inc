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

ifdef __UNIX__

.enum {
    DT_UNKNOWN	= 0,
    DT_FIFO	= 1,
    DT_CHR	= 2,
    DT_DIR	= 4,
    DT_BLK	= 6,
    DT_REG	= 8,
    DT_LNK	= 10,
    DT_SOCK	= 12,
    DT_WHT	= 14
    }

dirent		struct
d_ino		size_t ?
d_off		size_t ?
d_reclen	dw ?
d_type		db ?
d_name		sbyte 1 dup(?)
dirent		ends

DIR		typedef byte
opendir		proto __cdecl :LPSTR
readdir		proto __cdecl :ptr DIR
closedir	proto __cdecl :ptr DIR

define _getcwd <getcwd>
endif

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
if not defined(_MSVCRT) or defined(_CRTBLD)
__allocwpath	proto __cdecl :LPSTR
endif
.pragma list(pop)
