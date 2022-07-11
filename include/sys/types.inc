ifndef _INC_TYPES
define _INC_TYPES

ifndef _TIME_T_DEFINED
time_t typedef sdword
define _TIME_T_DEFINED
endif

ifndef _INO_T_DEFINED
_ino_t typedef word
if not __STDC__
ino_t  typedef word
endif
define _INO_T_DEFINED
endif

ifndef _DEV_T_DEFINED
_dev_t typedef dword
if not __STDC__
dev_t  typedef dword
endif
define _DEV_T_DEFINED
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

ifndef __uid_t_defined
__uid_t typedef dword
uid_t   typedef __uid_t
define __uid_t_defined
endif

__pid_t typedef sdword
pid_t   typedef sdword

__useconds_t typedef sdword
useconds_t   typedef __useconds_t

endif
