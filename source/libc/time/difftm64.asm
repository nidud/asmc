; DIFFTM64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc

.code

difftm64 proc b:__time64_t, a:__time64_t
ifdef _WIN64
    ldr rax,b
    ldr rdx,a
    .ifs ( rax < 0 || rdx < 0 )
        _set_errno( EINVAL )
        xorps xmm0,xmm0
       .return( 0 )
    .endif
    sub rax,rdx
    cvtsi2sd xmm0,rax
else
    _set_errno( EINVAL )
ifdef __SSE__
    xorps xmm0,xmm0
endif
    xor eax,eax
endif
    ret
    endp

    end
