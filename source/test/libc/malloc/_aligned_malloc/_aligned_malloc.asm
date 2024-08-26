;
; https://msdn.microsoft.com/en-us/library/8z34s9c6.aspx
;
include stdio.inc
include malloc.inc

    .code

_tmain proc

    ; Note alignment should be 2^N where N is any positive int.

    .if _aligned_malloc(100, 512)

        mov rbx,rax
        _aligned_free(rax)
        .if !( ebx & 512-1 )
            _tprintf("This pointer, %#p, is aligned on %u\n", rbx, 512)
        .else
            _tprintf("This pointer, %#p, is not aligned on %u\n", rbx, 512)
        .endif
        xor eax,eax
    .else
        _tprintf("Error allocation aligned memory.")
        mov eax,1
    .endif
    ret

_tmain endp

    end _tstart
