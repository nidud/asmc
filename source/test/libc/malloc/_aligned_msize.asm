;
; size_t _aligned_msize(void *memblock, size_t align, size_t offset);
;
include stdio.inc
include malloc.inc
include tchar.inc

.code

_tmain proc

   .new p:ptr = _aligned_offset_malloc(1024, 16, 4)
   .new z:size_t = _aligned_msize(p, 16, 4)

    _tprintf("address: %#p\n", p)
    _tprintf("_ALIGNED_MSIZE %d\n", z)
    _aligned_free(p)
   .return( 0 )
    endp

    end _tstart
