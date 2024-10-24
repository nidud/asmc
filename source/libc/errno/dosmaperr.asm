; DOSMAPERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

_get_errno_from_oserr proto oserrno:uint_t

    .code

_dosmaperr proc oserrno:uint_t

    _set_doserrno( ldr(oserrno) )
    _set_errno( _get_errno_from_oserr( oserrno ) )
    ret

_dosmaperr endp

    end
