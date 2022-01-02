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
    exitm<free(m)>
    endm
LclFree macro p
    exitm<>
    endm

MemInit proto __ccall
MemFini proto __ccall

endif
