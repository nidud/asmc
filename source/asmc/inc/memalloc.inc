; MEMALLOC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MEMALLOC_INC
define __MEMALLOC_INC

LclAlloc proto fastcall :uint_t
MemAlloc proto fastcall :uint_t
LclDup   proto fastcall :string_t
MemDup   proto fastcall :string_t

if defined(__UNIX__) and defined(_WIN64)
MemFree  proto fastcall :ptr
else
MemFree macro m
    free(m)
    exitm<>
    endm
LclFree macro p
    exitm<>
    endm
endif
MemInit proto __ccall
MemFini proto __ccall

endif
