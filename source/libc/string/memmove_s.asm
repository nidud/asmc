; MEMMOVE_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc

    .code

memmove_s proc dst:ptr, sizeInBytes:size_t, src:ptr, count:size_t

    ldr rax,src

    .if ( ldr(count) == 0 )
        .return( 0 ) ; nothing to do
    .endif
    .if ( ldr(dst) == NULL || rax == NULL )

        _set_errno( EINVAL )
        .return( EINVAL )
    .endif
    .if ( ldr(sizeInBytes) < ldr(count) )

        _set_errno( ERANGE )
        .return( ERANGE )
    .endif
    memmove( ldr(dst), rax, ldr(count) )
    xor eax,eax
    ret

memmove_s endp

    end
