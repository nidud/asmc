; _DOSMAPERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

_get_errno_from_oserr proto oserrno:ulong_t

    .code

_dosmaperr proc oserrno:ulong_t
ifndef _WIN64
    mov ecx,oserrno
endif
    _set_doserrno( ecx )
    _set_errno( _get_errno_from_oserr( oserrno ) )
    .return( -1 )

_dosmaperr endp

    end
