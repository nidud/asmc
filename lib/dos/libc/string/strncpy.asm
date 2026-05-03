; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strncpy proc <usesds> uses si di s1:string_t, s2:string_t, count:size_t

    ldr     si,s2
    ldr     di,s1
    mov     dx,di
    xor     ax,ax
    mov     cx,count
.0:
    movsb
    dec     cx
    jz      .1
    cmp     [si-1],al
    jne     .0
.1:
    mov     ax,dx
    movl    dx,es
    ret

strncpy endp

    end
