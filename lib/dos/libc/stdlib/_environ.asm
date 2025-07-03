; _ENVIRON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc
include malloc.inc
include stdlib.inc

.data
 _environ array_t 0

.code

__initenviron proc uses si di

    pushl   ds
    invoke  malloc,_envsize
    mov     word ptr _environ,ax
    movl    word ptr _environ+2,dx
    test    ax,ax
    jz      .1
    mov     cx,_envseg
    movl    ds,dx
    mov     si,ax
    dec     cx
    mov     di,0x10
    mov     es,cx
    mov     dx,cx
    xor     ax,ax
    mov     cx,0x7FFF
    cld
.0:
    mov     [si],di
    mov     [si+2],dx
    add     si,4
    repnz   scasb
    test    cx,cx
    jz      .1
    cmp     al,es:[di]
    jnz     .0
    mov     [si],ax
    mov     [si+2],ax
if (@DataSize eq 0)
    mov     ax,ds
    mov     es,ax
endif
.1:
    popl    ds
    ret

__initenviron endp

.pragma init(__initenviron, 5)

    end
