; MEMALLOC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MEMALLOC_INC
define __MEMALLOC_INC

MemAlloc proto fastcall :uint_t
ifdef _WIN64
MemFree  proto fastcall :ptr
else
define MemFree <free>
endif

LclAlloc    proto fastcall :uint_t
MemInit     proto __ccall
MemFini     proto __ccall
LclDup      proto fastcall :string_t
MemDup      proto fastcall :string_t

endif
