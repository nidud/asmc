; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

memcmp proc <usesds> uses si di s1:ptr, s2:ptr, len:size_t

    ldr     di,s1
    ldr     si,s2
    mov     cx,len
    xor     ax,ax
    repz    cmpsb
    jz      .0
    sbb     ax,ax
    sbb     ax,-1
.0:
    ret

memcmp endp

    end
