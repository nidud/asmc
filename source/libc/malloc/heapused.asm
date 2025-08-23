; HEAPUSED.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include errno.inc

.code

_heapused proc pUsed:ptr size_t, pCommit:ptr size_t

    _set_errno( ENOSYS )
    .return( 0 )

_heapused endp

    end
