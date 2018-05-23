;
; strtoflt128() - string to Quadruple float
;
include quadmath.inc

    .code

    option win64:nosave

strtoflt128 proc string:LPSTR, endptr:ptr LPSTR

  local q:REAL16

ifdef _LINUX
    mov rdx,rdi
    mov r8,rsi
else
    mov r8,rdx
    mov rdx,rcx
endif

    atoquad(&q, rdx, r8)
    movaps xmm0,q
    ret

strtoflt128 endp

    end
