; STRRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

   .code

    option dotname

strrchr::

    mov     edx,[esp+4]
    movzx   ecx,byte ptr [esp+8]
    xor     eax,eax
.0: cmp     cl,[edx]
    je      .5
.1: cmp     ch,[edx]
    je      .4
    cmp     cl,[edx+1]
    je      .6
.2: cmp     ch,[edx+1]
    je      .4
    cmp     cl,[edx+2]
    je      .7
.3: cmp     ch,[edx+2]
    je      .4
    add     edx,3
    jmp     .0
.4: ret
.5: mov     eax,edx
    jmp     .1
.6: lea     eax,[edx+1]
    jmp     .2
.7: lea     eax,[edx+2]
    jmp     .3

    end
