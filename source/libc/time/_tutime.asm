; _TUTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int _utime(char *fname, struct utimbuf *times);
; int _utime32(char *fname, struct __utimbuf32 *times);
; int _utime64(char *fname, struct __utimbuf64 *times);
; int _wutime(wchar_t *fname, struct utimbuf *times);
; int _wutime32(wchar_t *fname, struct __utimbuf32 *times);
; int _wutime64(wchar_t *fname, struct __utimbuf64 *times);
;
include io.inc
include fcntl.inc
include errno.inc
include sys/utime.inc
ifdef __UNIX__
include sys/syscall.inc
endif
include tchar.inc
ifndef __UNIX__
ifdef _UNICODE
ifdef _WIN64
undef _wutime64
ALIAS <_wutime64>=<_wutime>
else
undef _wutime32
ALIAS <_wutime32>=<_wutime>
endif
else
ifdef _WIN64
undef _utime64
ALIAS <_utime64>=<_utime>
else
undef _utime32
ALIAS <_utime32>=<_utime>
endif
endif
endif

.code

_tutime proc fname:tstring_t, utp:ptr utimbuf
    .if ( ldr(fname) == NULL )
        .return( _set_errno(EINVAL) )
    .endif
ifdef __UNIX__
    .ifsd ( sys_utime( ldr(fname), ldr(utp) ) < 0 )
        neg eax
        _set_errno( eax )
    .endif
else
    .new fh:int_t, rc
    .ifsd ( _topen(ldr(fname), _O_RDWR or _O_BINARY) >= 0 )
        mov fh,eax
        mov rc,_futime(eax, utp)
        _close(fh)
        mov eax,rc
    .endif
endif
    ret
    endp

    end
