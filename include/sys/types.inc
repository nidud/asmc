ifndef _INC_TYPES
define _INC_TYPES

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
ifdef _WIN64
time_t typedef int64_t
else
time_t typedef long_t
endif
endif
ifndef _INO_T_DEFINED
define _INO_T_DEFINED
ino_t typedef word
endif
ifndef _DEV_T_DEFINED
define _DEV_T_DEFINED
dev_t typedef dword
endif
ifndef _OFF_T_DEFINED
define _OFF_T_DEFINED
off32_t typedef sdword
off64_t typedef qword
ifdef _WIN64
off_t typedef qword
else
off_t typedef sdword
endif
endif
ifndef _UID_T_DEFINED
define _UID_T_DEFINED
uid_t typedef dword
endif
ifndef _GID_T_DEFINED
define _GID_T_DEFINED
gid_t typedef dword
endif
ifndef _PID_T_DEFINED
define _PID_T_DEFINED
pid_t typedef sdword
endif
ifndef _ID_T_DEFINED
define _ID_T_DEFINED
id_t typedef dword
endif
useconds_t typedef sdword

if __STDC__
_ino_t          typedef ino_t
_dev_t          typedef dev_t
_off32_t        typedef off32_t
_off64_t        typedef off64_t
_off_t          typedef off_t
__uid_t         typedef uid_t
__pid_t         typedef pid_t
__id_t          typedef id_t
__useconds_t    typedef useconds_t
endif

endif
