; MEMALLOC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MEMALLOC_INC
define __MEMALLOC_INC

MemAlloc    proto fastcall :uint_t
MemFree     proto fastcall :ptr
LclAlloc    proto fastcall :uint_t
MemInit     proto
MemFini     proto

LclDup      proto fastcall :string_t
MemDup      proto fastcall :string_t

endif
