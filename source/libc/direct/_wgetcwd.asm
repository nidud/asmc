; _WGETCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
ifdef __UNIX__
include errno.inc
endif
    .code

_wgetcwd proc buffer:LPWSTR, maxlen:SINT
ifdef __UNIX__
    _set_errno( ENOSYS )
    xor eax,eax
else

    ldr rcx,buffer
    ldr edx,maxlen

    _wgetdcwd( 0, rcx, edx )
endif
    ret

_wgetcwd endp

    end
