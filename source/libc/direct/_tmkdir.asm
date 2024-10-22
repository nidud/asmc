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
endif
include tchar.inc

    .code

if defined(__UNIX__) and not defined(_UNICODE)
mkdir proc directory:LPSTR, mode:int_t
ifdef _WIN64
    .ifsd ( sys_mkdir(rdi, esi) < 0 )
else
    .ifs ( sys_mkdir(directory, mode) < 0 )
endif
        neg eax
        _set_errno(eax)
    .endif
    ret

mkdir endp
endif

_tmkdir proc directory:LPTSTR

    ldr rcx,directory
ifdef __UNIX__
ifdef _UNICODE
    _set_errno( ENOSYS )
else
    mkdir(rcx, S_IRWXU or S_IRWXG or S_IROTH or S_IXOTH)
endif
else
    .if CreateDirectory( rcx, 0 )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_tmkdir endp

    end
