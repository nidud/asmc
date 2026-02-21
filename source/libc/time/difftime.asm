; DIFFTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc

.code

difftime proc b:time_t, a:time_t
    ldr rax,b
    ldr rdx,a
    .ifs ( rax < 0 || rdx < 0 )
        _set_errno( EINVAL )
ifdef __SSE__
        xorps xmm0,xmm0
endif
        .return( 0 )
    .endif
    sub rax,rdx
ifdef __SSE__
    cvtsi2sd xmm0,rax
endif
    ret
    endp

    end
