ifndef __UTIME_INC
define __UTIME_INC
include libc.inc
ifndef _TIME32_T_DEFINED
define _TIME32_T_DEFINED
__time32_t typedef int_t
endif
ifndef _TIME64_T_DEFINED
define _TIME64_T_DEFINED
__time64_t typedef int64_t
endif
ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
ifdef _WIN64
time_t typedef int64_t
else
time_t typedef int_t
endif
endif

utimbuf         struct
actime          time_t ?
modtime         time_t ?
utimbuf         ends
_utimbuf        typedef utimbuf

utimbuf32       struct
actime          __time32_t ?
modtime         __time32_t ?
utimbuf32       ends
__utimbuf32     typedef utimbuf32

utimbuf64       struct
actime          __time64_t ?
modtime         __time64_t ?
utimbuf64       ends
__utimbuf64     typedef utimbuf64

_futime         proto __cdecl :int_t, :ptr utimbuf
_utime          proto __cdecl :string_t, :ptr utimbuf
_wutime         proto __cdecl :wstring_t, :ptr utimbuf

_futime32       proto __cdecl :int_t, :ptr __utimbuf32
_futime64       proto __cdecl :int_t, :ptr __utimbuf64
_utime32        proto __cdecl :string_t, :ptr __utimbuf32
_utime64        proto __cdecl :string_t, :ptr __utimbuf64
_wutime32       proto __cdecl :wstring_t, :ptr __utimbuf32
_wutime64       proto __cdecl :wstring_t, :ptr __utimbuf64

endif
