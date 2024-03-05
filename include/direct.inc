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

.pragma pack(push, size_t)

dirent		struct
d_ino		size_t ?
d_off		size_t ?
d_reclen	ushort_t ?
d_type		char_t ?
d_name		char_t 1 dup(?)
dirent		ends

.pragma pack(pop)

DIR		typedef byte
opendir		proto __cdecl :LPSTR
readdir		proto __cdecl :ptr DIR
closedir	proto __cdecl :ptr DIR
fchdir		proto __cdecl :int_t

define _rmdir	<rmdir>
define _mkdir	<mkdir>
define _chdir	<chdir>
define _getcwd	<getcwd>
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
__copy_path_to_wide_string proto __cdecl :ptr char_t, :ptr ptr wchar_t
endif
.pragma list(pop)
