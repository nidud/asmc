; MEMALLOC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MEMALLOC_INC
define __MEMALLOC_INC

LclAlloc proto fastcall :size_t
MemAlloc proto fastcall :size_t
MemFree macro m
    exitm<free(m)>
    endm
LclFree macro p
    exitm<>
    endm

MemInit proto
MemFini proto

endif
