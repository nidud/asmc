; HEAPMIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include errno.inc
ifndef __UNIX__
include winbase.inc
endif

.code

_heapmin proc
ifdef __UNIX__
    .return( _set_errno( ENOSYS ) )
else
    .ifd HeapCompact( _crtheap, 0 )
        .return( 0 )
    .endif
    .return( -1 )
endif
_heapmin endp

    end
