include cruntime.inc
include malloc.inc
include winheap.inc
include windows.inc
include mtdll.inc
include dbgint.inc
include rtcsup.inc
include internal.inc

.code

;; Check if the low fragmentation heap is enabled

_is_LFH_enabled proc private
ifdef _CRT_APP
    ;; CRT App uses the default process heap
    .return TRUE
else
    .new heaptype:LONG
    mov heaptype,-1
    .if HeapQueryInformation(_crtheap, HeapCompatibilityInformation, &heaptype, sizeof(heaptype), NULL)
        mov eax,FALSE
        .if heaptype == 2
            mov eax,TRUE
        .endif
    .endif
endif
    ret
_is_LFH_enabled endp

_expand_base proc pBlock:ptr, newsize:size_t

  local pvReturn:ptr
  local oldsize:size_t

    ; validation section

    .if ( rcx != NULL )

        _set_errno(EINVAL)
        .return NULL
    .endif

    .if rdx > _HEAP_MAXREQ

        _set_errno(ENOMEM)
        .return NULL
    .endif

    .if rdx == 0

        mov newsize,1
    .endif

    mov oldsize,HeapSize(_crtheap, 0, pBlock)
    mov pvReturn,HeapReAlloc(_crtheap, HEAP_REALLOC_IN_PLACE_ONLY, pBlock, newsize)

    .if (pvReturn == NULL)

        ; If the failure is caused by the use of the LFH, just return the original block.
        ; LFH can only allocate blocks up to 16 KB.
        .if (oldsize <= 0x4000 && newsize <= oldsize && _is_LFH_enabled())
            mov pvReturn,pBlock
        .else
            _set_errno(_get_errno_from_oserr(GetLastError()))
        .endif

        .if (pvReturn)

            RTCCALLBACK(_RTC_Free_hook, (pBlock, 0))
            RTCCALLBACK(_RTC_Allocate_hook, (pvReturn, newsize, 0))
        .endif
    .endif

    .return pvReturn

_expand_base endp

    end
