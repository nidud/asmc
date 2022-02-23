ifndef _INC_TIMEB
define _INC_TIMEB
ifdef _CRTBLD
ifndef _INTERNAL_IFSTRIP_
include cruntime.inc
endif
endif

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
time_t typedef sdword
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
