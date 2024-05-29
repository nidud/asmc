ifndef _INC_TIMEB
define _INC_TIMEB

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
ifdef _WIN64
time_t typedef int64_t
else
time_t typedef long_t
endif
endif
ifdef __UNIX__
define _timeb <timeb>
define _ftime <ftime>
endif
ifndef _TIMEB_DEFINED
define _TIMEB_DEFINED
_timeb		STRUC
time		time_t ?
millitm		word ?
timezone	sword ?
dstflag		sword ?
_timeb		ENDS
endif

_ftime proto __cdecl :ptr _timeb

endif
