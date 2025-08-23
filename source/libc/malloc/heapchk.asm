; HEAPCHK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
ifdef __UNIX__
include errno.inc
else
include winbase.inc
endif

.code

_heapchk proc
ifdef __UNIX__
    .return( _set_errno( ENOSYS ) )
else
    .ifd ( !HeapValidate(_crtheap, 0, NULL) )

        .return( _HEAPBADNODE )
    .endif
    .return( _HEAPOK )
endif
_heapchk endp


_heapset proc _fill:uint_t

    .return( _heapchk() )

_heapset endp

    end
