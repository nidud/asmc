; MEMALLOC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MEMALLOC_INC
define __MEMALLOC_INC

include malloc.inc

MemAlloc    proto fastcall :uint_t
MemFree     proto fastcall :ptr
LclAlloc    proto fastcall :uint_t
MemInit     proto
MemFini     proto

LclDup      proto fastcall :string_t
MemDup      proto fastcall :string_t

alloc_line macro
   .new mem_alloc:uchar_t = 0
    mov ecx,MaxLineLength
    .if ( ecx > MAX_LINE_LEN )
        mov mem_alloc,1
        MemAlloc( ecx )
    .else
        alloca( ecx )
    .endif
    exitm<rax>
    endm

free_line macro p
    .if ( mem_alloc )
        MemFree( p )
    .endif
    exitm<>
    endm

endif
