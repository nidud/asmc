; _WMKDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include direct.inc
ifdef __UNIX__
include sys/stat.inc
include sys/syscall.inc
else
include winbase.inc
include tchar.inc
undef mkdir
ALIAS <mkdir>=<_mkdir>
endif

.code

ifdef __UNIX__
mkdir proc directory:string_t, mode:int_t
    .ifsd ( sys_mkdir( ldr(directory), ldr(mode) ) < 0 )
        neg eax
        _set_errno(eax)
    .endif
else
_tmkdir proc directory:tstring_t
    .ifd CreateDirectory( ldr(directory), 0 )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret
    endp

    end
