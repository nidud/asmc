; STRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option dotname

strchr::

    mov     eax,[esp+4]
    movzx   ecx,byte ptr [esp+8]
.3: cmp     cl,[eax]
    je      .0
    cmp     ch,[eax]
    je      .4
    cmp     cl,[eax+1]
    je      .1
    cmp     ch,[eax+1]
    je      .4
    cmp     cl,[eax+2]
    je      .2
    cmp     ch,[eax+2]
    je      .4
    add     eax,3
    jmp     .3
.4: xor     eax,eax
    ret
.2: inc     eax
.1: inc     eax
.0: ret

    end
