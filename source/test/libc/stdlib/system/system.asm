include process.inc
include tchar.inc

ifdef _WIN64
ifdef _UNICODE
define cmd <"echo 64-bit Unicode">
else
define cmd <"echo 64-bit ASCII">
endif
else
ifdef _UNICODE
define cmd <"echo 32-bit Unicode">
else
define cmd <"echo 32-bit ASCII">
endif
endif

    .code

_tmain proc

    _tsystem( cmd )
    ret

_tmain endp

    end _tstart
