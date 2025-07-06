; MEMCMP.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

memcmp proc uses si di s1:ptr, s2:ptr, len:size_t

    pushl   ds
    ldr     di,s1
    ldr     si,s2
    mov     cx,len
    xor     ax,ax
    repz    cmpsb
    jz      .0
    sbb     ax,ax
    sbb     ax,-1
.0:
    popl    ds
    ret

memcmp endp

    end
