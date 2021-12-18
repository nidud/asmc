; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option dotname

strncpy::

    push    esi
    push    edi
    mov     edi,[esp+12]
    mov     esi,[esp+16]
    mov     ecx,[esp+20]
    cmp     ecx,4
    jb      .2
    mov     eax,[esi]
    lea     edx,[eax-0x01010101]
    not     eax
    and     edx,eax
    and     edx,0x80808080
    jnz     .2
    mov     eax,edi     ; align 4
    neg     eax
    and     eax,3
    mov     edx,[esi]   ; copy the first 4 bytes
    mov     [edi],edx
    add     edi,eax     ; add leading bytes
    add     esi,eax     ;
    sub     ecx,eax
    jmp     .1
.0: sub     ecx,4
    mov     eax,[esi]   ; copy 4 bytes
    mov     [edi],eax
    add     edi,4
    add     esi,4
.1: cmp     ecx,4
    jb      .2
    mov     eax,[esi]
    lea     edx,[eax-0x01010101]
    not     eax
    and     edx,eax
    and     edx,0x80808080
    jz      .0
.2: test    ecx,ecx
    jz      .4
.3: mov     al,[esi]
    mov     [edi],al
    dec     ecx
    jz      .4
    inc     edi
    inc     esi
    test    al,al
    jnz     .3
    rep     stosb
.4: mov     eax,[esp+12]
    pop     edi
    pop     esi
    ret

    end
