; MEMXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code

    option dotname

memxchg proc dst:string_t, src:string_t, count:size_t

ifdef _WIN64

.0:
    cmp     r8,8
    jb      .1
    sub     r8,8
    mov     rax,[rcx+r8]
    mov     r10,[rdx+r8]
    mov     [rcx+r8],r10
    mov     [rdx+r8],rax
    jmp     .0
.1:
    test    r8,r8
    jz      .3
.2:
    dec     r8
    mov     al,[rcx+r8]
    mov     r10b,[rdx+r8]
    mov     [rcx+r8],r10b
    mov     [rdx+r8],al
    jnz     .2
.3:
    mov     rax,rcx

else
    push    esi
    push    edi

    mov     edi,dst
    mov     esi,src
    mov     ecx,count
    test    ecx,ecx

.0:
    jz      .2
    test    ecx,3
    jz      .1

    sub     ecx,1
    mov     al,[esi+ecx]
    mov     dl,[edi+ecx]
    mov     [esi+ecx],dl
    mov     [edi+ecx],al
    jmp     .0

.1:
    sub     ecx,4
    mov     eax,[esi+ecx]
    mov     edx,[edi+ecx]
    mov     [esi+ecx],edx
    mov     [edi+ecx],eax
    jnz     .1

.2:
    mov     eax,edi
    pop     edi
    pop     esi
endif
    ret

memxchg endp

    end
