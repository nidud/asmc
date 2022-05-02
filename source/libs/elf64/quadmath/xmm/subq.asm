; SUBQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

subq proc dest:real16, src:real16

    .new a:real16 = dest
    .new b:real16 = src
    .return( __subq(&a, &b) )

subq endp

    end
