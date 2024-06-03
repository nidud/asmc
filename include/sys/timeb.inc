ifndef _INC_TIMEB
define _INC_TIMEB
ifndef _INC_LIBC
include libc.inc
endif

ifndef _TIME32_T_DEFINED
define _TIME32_T_DEFINED
__time32_t typedef sdword
endif
ifndef _TIME64_T_DEFINED
define _TIME64_T_DEFINED
__time64_t typedef sqword
endif
ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
ifdef _WIN64
time_t typedef __time64_t
else
time_t typedef __time32_t
endif
endif

ifdef __UNIX__
define _timeb <timeb>
define _ftime <ftime>
endif

ifndef _TIMEB_DEFINED
define _TIMEB_DEFINED
.template _timeb
    time	time_t ?
    millitm	ushort_t ?
    timezone	short_t ?
    dstflag	short_t ?
   .ends
endif

_ftime proto __cdecl :ptr _timeb

endif
