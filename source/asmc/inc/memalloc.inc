; MEMALLOC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MEMALLOC_INC
define __MEMALLOC_INC

LclAlloc proto fastcall :uint_t
MemAlloc proto fastcall :uint_t

MemFree macro m
if defined(__UNIX__) and defined(_WIN64)
    push    rsi
    push    rdi
    free(m)
    pop     rdi
    pop     rsi
else
    free(m)
endif
    exitm<>
    endm
LclFree macro p
    exitm<>
    endm

MemInit proto __ccall
MemFini proto __ccall

endif
