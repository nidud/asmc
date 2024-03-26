ifndef __STAT_INC
define __STAT_INC
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
define _S_IFLNK  0xA000
define _S_IFSOCK 0xC000
define _S_IFNAM  0x5000

define S_IFMT   _S_IFMT
define S_IFDIR  _S_IFDIR
define S_IFIFO  _S_IFIFO
define S_IFCHR  _S_IFCHR
define S_IFBLK  _S_IFBLK
define S_IFREG  _S_IFREG
define S_IREAD  _S_IREAD
define S_IWRITE _S_IWRITE
define S_IEXEC  _S_IEXEC

define S_IFNAM  _S_IFNAM
define S_IFLNK  _S_IFLNK
define S_IFSOCK _S_IFSOCK

define S_ISUID  0x0800
define S_ISGID  0x0400
define S_ISVTX  0x0200
define S_ENFMT  0x0400

define S_IRWXU  0x01C0
define S_IRUSR  0x0100          ; Read by owner
define S_IWUSR  0x0080          ; Write by owner
define S_IXUSR  0x0040          ; Execute by owner
define S_IREAD  S_IRUSR
define S_IWRITE S_IWUSR
define S_IEXEC  S_IXUSR

define S_IRGRP (S_IRUSR shr 3)  ; Read by group
define S_IWGRP (S_IWUSR shr 3)  ; Write by group
define S_IXGRP (S_IXUSR shr 3)  ; Execute by group
define S_IRWXG (S_IRWXU shr 3)  ; Read, write, and execute by group

define S_IROTH (S_IRGRP shr 3)  ; Read by others
define S_IWOTH (S_IWGRP shr 3)  ; Write by others
define S_IXOTH (S_IXGRP shr 3)  ; Execute by others
define S_IRWXO (S_IRWXG shr 3)  ; Read, write, and execute by others

define ACCESSPERMS  (S_IRWXU or S_IRWXG or S_IRWXO) ; 0777
define ALLPERMS     (S_ISUID or S_ISGID or S_ISVTX or S_IRWXU or S_IRWXG or S_IRWXO) ; 07777
define DEFFILEMODE  (S_IRUSR or S_IWUSR or S_IRGRP or S_IWGRP or S_IROTH or S_IWOTH) ; 0666

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
_off32_t typedef sdword
_off64_t typedef qword
ifdef _WIN64
_off_t typedef qword
else
_off_t typedef sdword
endif
if not __STDC__
off_t   typedef _off_t
off32_t typedef sdword
off64_t typedef qword
endif
endif

ifndef _TIME32_T_DEFINED
define _TIME32_T_DEFINED
__time32_t typedef sdword
endif

ifndef _STAT_DEFINED
define _STAT_DEFINED

.pragma pack(push, size_t)

.template _stat32
ifdef __UNIX__
    st_dev      dq ?        ; 0
    st_ino      size_t ?    ; 8
 ifdef _WIN64
    st_nlink    dq ?        ; 16
    st_mode     dd ?        ; 24
 else
    st_mode     dd ?        ; 16
    st_nlink    dd ?        ; 20
 endif
    st_uid      dd ?        ; 24/28
    st_gid      dd ?        ; 28/32
    st_rdev     dq ?        ; 32/40
    st_size     size_t ?    ; 44/48
    st_blksize  size_t ?    ; 48/56
    st_blocks   size_t ?    ; 52/64
    st_atime    size_t ?    ; 56/72
    st_atimesec size_t ?    ; 60/80
    st_mtime    size_t ?    ; 64/88
    st_mtimesec size_t ?    ; 68/96
    st_ctime    size_t ?    ; 72/104
    st_ctimesec size_t ?    ; 76/112
 ifndef _WIN64
    st_reserved db 8 dup(?) ; 88
 else
    st_reserved db 24 dup(?); 144
 endif
else
    st_dev      dd ?        ; 0
    st_ino      dw ?        ; 4
    st_mode     dw ?        ; 6
    st_nlink    sword ?     ; 8
    st_uid      sword ?     ; 10
    st_gid      sword ?     ; 12
    st_rdev     dd ?        ; 16
    st_size     dd ?        ; 20
    st_atime    size_t ?    ; 24
    st_mtime    size_t ?    ; 28/32
    st_ctime    size_t ?    ; 32/40
endif
   .ends

.template _stati64
ifdef __UNIX__
    st_dev      dq ?        ; 0
    st_ino      dq ?        ; 8
    st_nlink    dq ?        ; 16
    st_mode     dd ?        ; 24
    st_uid      dd ?        ; 28
    st_gid      dd ?        ; 32
    st_pad      dd ?        ; 36
    st_rdev     dq ?        ; 40
    st_size     dq ?        ; 48
    st_blksize  dq ?        ; 56
    st_blocks   dq ?        ; 64
    st_atime    dq ?        ; 72
    st_atimesec dq ?        ; 80
    st_mtime    dq ?        ; 88
    st_mtimesec dq ?        ; 96
    st_ctime    dq ?        ; 104
    st_ctimesec dq ?        ; 112
    st_reserved db 24 dup(?)
else
    st_dev      dd ?        ; 0
    st_ino      dw ?        ; 4
    st_mode     dw ?        ; 6
    st_nlink    sword ?     ; 8
    st_uid      sword ?     ; 10
    st_gid      sword ?     ; 12
    st_rdev     dd ?        ; 16
    st_size     dq ?        ; 24
    st_atime    dq ?        ; 32
    st_mtime    dq ?        ; 40
    st_ctime    dq ?        ; 48
endif
   .ends

.pragma pack(pop)

endif

PSTAT   typedef ptr _stat32
PSTAT64 typedef ptr _stati64

ifdef __UNIX__
define _stat    <stat>
define _fstat   <fstat>
define _stat64  <stat64>
define _fstat64 <fstat64>
chmod       proto __cdecl :string_t, :int_t
endif

_stat       proto __cdecl :string_t, :PSTAT
_fstat      proto __cdecl :int_t, :PSTAT
_stat64     proto __cdecl :string_t, :PSTAT64
_fstat64    proto __cdecl :int_t, :PSTAT64

ifndef _WSTAT_DEFINED
define _WSTAT_DEFINED
_wstat32    typedef _stat32
_wstati64   typedef _stati64
_wstat      proto __cdecl :wstring_t, :PSTAT
_wstat64    proto __cdecl :wstring_t, :PSTAT64
endif

.pragma list(pop)
endif
