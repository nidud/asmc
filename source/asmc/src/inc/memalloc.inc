.pragma list(push, 0)
ifndef _MEMALLOC_H_
_MEMALLOC_H_ equ <>

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
.pragma list(pop)