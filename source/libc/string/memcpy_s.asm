; MEMCPY_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc

    .code

memcpy_s proc dst:ptr, sizeInBytes:size_t, src:ptr, count:size_t

    .if ( count == 0 )
        .return( 0 )
    .endif

    .if ( dst == NULL )

        _set_errno(EINVAL)
        .return( EINVAL )
    .endif

    .if ( src == NULL || sizeInBytes < count )

        memset( dst, 0, sizeInBytes )
        .if ( src != NULL )
            _set_errno(EINVAL)
            .return( EINVAL )
        .endif
        .if ( sizeInBytes >= count )
            _set_errno(ERANGE)
            .return( ERANGE )
        .endif
        _set_errno(EINVAL)
        .return( EINVAL )
    .endif
    memcpy( dst, src, count )
   .return( 0 )

memcpy_s endp

    end
