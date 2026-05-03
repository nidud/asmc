; GMTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
ifndef __UNIX__
ifdef _WIN64
undef _gmtime64
ALIAS <_gmtime64>=<gmtime>
else
undef _gmtime32
ALIAS <_gmtime32>=<gmtime>
endif
endif

    .data
     tb tm <>

    .code

gmtime proc tp:ptr time_t
    .ifd _gmtime_s(&tb, ldr(tp))
        xor eax,eax
    .else
        lea rax,tb
    .endif
    ret
    endp

    end
