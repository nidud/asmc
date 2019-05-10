; STRTOFLT128.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
;
; strtoflt128() - string to Quadruple float
;
include quadmath.inc

    .code

    option win64:nosave

strtoflt128 proc string:LPSTR, endptr:ptr LPSTR

    cvta_q(rcx, rdx)
    ret

strtoflt128 endp

    end
