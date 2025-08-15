; MEMCCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

.code

_memccpy proc uses rsi dest:ptr, src:ptr, c:int_t, count:size_t

    ldr rcx,dest
    ldr rdx,src
    ldr eax,c
    ldr rsi,count

    .for ( ah = al : rsi : rsi--, rcx++, rdx++ )

        mov al,[rdx]
        mov [rcx],al
        .if ( al == ah )
            .break
        .endif
    .endf
    xor eax,eax
    .if ( rsi )
        lea rax,[rcx+1]
    .endif
    ret

_memccpy endp

    end
