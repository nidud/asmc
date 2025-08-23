; HEAPADD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include errno.inc

.code

_heapadd proc block:ptr, size:size_t
    .return( _set_errno( ENOSYS ) )
_heapadd endp

    end
