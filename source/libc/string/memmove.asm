; MEMMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memmove proc dst:ptr, src:ptr, count:size_t

ifdef _WIN64
ifdef __UNIX__
    memcpy(rdi, rsi, rdx)
else
    memcpy(rcx, rdx, r8)
endif
else
    memcpy(dst, src, count)
endif
    ret

memmove endp

    end
