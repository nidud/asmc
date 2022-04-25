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

ifndef _STAT_DEFINED
define _STAT_DEFINED

.pragma pack(push, 4)

.template _STAT
    st_dev      _dev_t ?
    st_ino      _ino_t ?
    st_mode     word ?
    st_nlink    sword ?
    st_uid      sword ?
    st_gid      sword ?
    st_rdev     _dev_t ?
    st_size     _off_t ?
    st_atime    time_t ?
    st_mtime    time_t ?
    st_ctime    time_t ?
   .ends

.template _stat32
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

.template _stati64
    st_dev      _dev_t ?
    st_ino      _ino_t ?
    st_mode     word ?
    st_nlink    sword ?
    st_uid      sword ?
    st_gid      sword ?
    st_rdev     _dev_t ?
    st_size     dq ?
    st_atime    time_t ?
    st_mtime    time_t ?
    st_ctime    time_t ?
   .ends

.pragma pack(pop)

endif
ifdef __UNIX__
stat proto __cdecl :ptr sbyte, :ptr _stat32
else
define stat <_stat32>
_stat proto __cdecl :ptr sbyte, :ptr stat
endif

.pragma list(pop)
