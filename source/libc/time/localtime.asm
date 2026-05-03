; LOCALTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; struct tm * localtime(const time_t *ptime);
; struct tm * _localtime32(const __time32_t *ptime);
; struct tm * _localtime64(const __time64_t *ptime);
;
include time.inc
include errno.inc
ifndef __UNIX__
ifdef _WIN64
undef _localtime64
ALIAS <_localtime64>=<localtime>
else
undef _localtime32
ALIAS <_localtime32>=<localtime>
endif
endif

.data
 tb tm <>
.code

localtime proc ptime:ptr time_t
    .ifd _localtime_s( &tb, ldr(ptime) )
        _set_errno( eax )
        .return( 0 )
    .endif
    lea rax,tb
    ret
    endp

    end
