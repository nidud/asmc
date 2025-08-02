; MEMCPY_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc

    .code

memcpy_s proc dst:ptr, sizeInBytes:size_t, src:ptr, count:size_t

    .if ( ldr(count) == 0 )
        .return( 0 )
    .endif

    .if ( ldr(dst) == NULL )

        _set_errno(EINVAL)
        .return( EINVAL )
    .endif

    .if ( ldr(src) == NULL || ldr(sizeInBytes) < ldr(count) )

        memset( ldr(dst), 0, ldr(sizeInBytes) )
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
    memcpy( ldr(dst), src, ldr(count) )
   .return( 0 )

memcpy_s endp

    end
