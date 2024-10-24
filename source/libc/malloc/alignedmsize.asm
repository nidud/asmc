; ALIGNEDMSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; size_t _aligned_msize(void *memblock, size_t align, size_t offset);
;
include malloc.inc

.code

_aligned_msize proc memblock:ptr, alignment:size_t, offs:size_t

    _msize( ldr(memblock) )
    ret

_aligned_msize endp

    end
