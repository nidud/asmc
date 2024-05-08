.pragma list(push, 0)
ifndef __DIRECT_INC
define __DIRECT_INC

include io.inc
ifdef __UNIX__
include sys/stat.inc
endif

define _MAX_PATH	260
define _MAX_DRIVE	3
define _MAX_DIR		256
define _MAX_FNAME	256
define _MAX_EXT		256

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
LPDIR		typedef ptr DIR
opendir		proto __cdecl :LPSTR
readdir		proto __cdecl :LPDIR
closedir	proto __cdecl :LPDIR
fchdir		proto __cdecl :int_t

define _rmdir	<rmdir>
define _mkdir	<mkdir>
define _chdir	<chdir>
define _getcwd	<getcwd>

define _F_SUBDIR	_S_IFDIR
else
define _F_SUBDIR	_A_SUBDIR
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


define DMAXPATH		2048	; the max length is 0x8000..

define _D_MALLOC	0x0001
define _D_SORTNAME	0x0010
define _D_SORTTYPE	0x0020
define _D_SORTDATE	0x0040
define _D_SORTSIZE	0x0080
define _D_SORTSUB	0x0100
define _D_DOSORT	0x00F0

.template FILENTA
    attrib	uint_t ?
    time	uint_t ?
    size	uint64_t ?
    name	string_t ?
    nbuf	char_t 1 dup(?)
   .ends
    PFILENTA	typedef ptr FILENTA

.template FILENTW
    attrib	uint_t ?
    time	uint_t ?
    size	uint64_t ?
    name	wstring_t ?
    nbuf	wchar_t 1 dup(?)
   .ends
    PFILENTW	typedef ptr FILENTW

.template DIRENTW
    flags	uint_t ?
    count	uint_t ?
    path	wstring_t ?
    mask	wstring_t ?
    fcb		PFILENTW ?
   .ends
    PDIRENTW	typedef ptr DIRENTW

.template DIRENTA
    flags	uint_t ?
    count	uint_t ?
    path	string_t ?
    mask	string_t ?
    fcb		PFILENTA ?
   .ends
    PDIRENTA	typedef ptr DIRENTA

ifdef _UNICODE
FILENT		typedef FILENTW
DIRENT		typedef DIRENTW
else
FILENT		typedef FILENTA
DIRENT		typedef DIRENTA
endif
PFILENT		typedef ptr FILENT
PDIRENT		typedef ptr DIRENT

_dopenA		proto __cdecl :PDIRENTA, :LPSTR, :LPSTR, :UINT
_dopenW		proto __cdecl :PDIRENTW, :LPWSTR, :LPWSTR, :UINT
_dclose		proto __cdecl :PDIRENT
_dfree		proto __cdecl :PDIRENT
_dreadA		proto __cdecl :PDIRENTA
_dreadW		proto __cdecl :PDIRENTW
_dsortA		proto __cdecl :PDIRENTA
_dsortW		proto __cdecl :PDIRENTW
_dsearchA	proto __cdecl :PDIRENTA, :LPSTR
_dsearchW	proto __cdecl :PDIRENTW, :LPWSTR

ifdef _UNICODE
define _dopen	<_dopenW>
define _dread	<_dreadW>
define _dsort	<_dsortW>
define _dsearch <_dsearchW>
else
define _dopen	<_dopenA>
define _dread	<_dreadA>
define _dsort	<_dsortA>
define _dsearch <_dsearchA>
endif

endif

endif
.pragma list(pop)
