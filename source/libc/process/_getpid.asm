; _GETPID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include process.inc
include errno.inc
include processthreadsapi.inc

ifndef __UNIX__
undef getpid
ALIAS <getpid>=<_getpid>
endif

.code

_getpid proc
    GetCurrentProcessId()
    ret
    endp

    end
