.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

define _S_IFMT   0xF000
define _S_IFDIR  0x4000
define _S_IFIFO  0x1000
define _S_IFCHR  0x2000
define _S_IFBLK  0x3000
define _S_IFREG  0x8000
define _S_IREAD  0x0100
define _S_IWRITE 0x0080
define _S_IEXEC  0x0040

define S_IFMT   _S_IFMT
define S_IFDIR  _S_IFDIR
define S_IFIFO  _S_IFIFO
define S_IFCHR  _S_IFCHR
define S_IFBLK  _S_IFBLK
define S_IFREG  _S_IFREG
define S_IREAD  _S_IREAD
define S_IWRITE _S_IWRITE
define S_IEXEC  _S_IEXEC

ifndef _INO_T_DEFINED
define _INO_T_DEFINED
_ino_t typedef word
endif
ifndef _DEV_T_DEFINED
define _DEV_T_DEFINED
_dev_t typedef dword
endif
ifndef _OFF_T_DEFINED
define _OFF_T_DEFINED
ifdef _WIN64
_off_t typedef qword
else
_off_t typedef sdword
endif
endif
ifndef _TIME32_T_DEFINED
define _TIME32_T_DEFINED
__time32_t typedef sdword
endif

.template stat
    st_dev      _dev_t ?
    st_ino      _ino_t ?
    st_mode     word ?
    st_nlink    sword ?
    st_uid      sword ?
    st_gid      sword ?
    st_rdev     _dev_t ?
    st_size     _off_t ?
    st_atime    __time32_t ?
    st_mtime    __time32_t ?
    st_ctime    __time32_t ?
   .ends

_stat proto __cdecl :ptr sbyte, :ptr stat

.pragma list(pop)
