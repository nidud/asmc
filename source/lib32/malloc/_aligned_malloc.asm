; _ALIGNED_MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

_aligned_malloc proc dwSize:size_t, Alignment:UINT

    mov edx,Alignment
    mov eax,dwSize
    lea eax,[eax+edx+sizeof(S_HEAP)]

    .if malloc(eax)

        mov ecx,Alignment
        dec ecx
        .if eax & ecx

            lea edx,[eax-sizeof(S_HEAP)]
            lea eax,[eax+ecx+sizeof(S_HEAP)]
            not ecx
            and eax,ecx
            lea ecx,[eax-sizeof(S_HEAP)]
            mov [ecx].S_HEAP.h_prev,edx
            mov [ecx].S_HEAP.h_type,3

        .endif
    .endif
    ret

_aligned_malloc endp

    end
