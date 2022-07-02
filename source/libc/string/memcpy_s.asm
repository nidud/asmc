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

        ; nothing to do
        .return( 0 )
    .endif

    ; validation section
    .if ( dst == NULL )

        .return( EINVAL )
    .endif

    .if ( src == NULL || sizeInBytes < count )

        ; zeroes the destination buffer

        memset( dst, 0, sizeInBytes )

        .if ( src != NULL )
            .return( EINVAL )
        .endif
        .if ( sizeInBytes >= count )
            .return( ERANGE )
        .endif
        ; useless, but prefast is confused
        .return( EINVAL )
    .endif
    memcpy( dst, src, count )
   .return( 0 )

memcpy_s endp

    end
