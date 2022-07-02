; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strcpy proc uses rsi rdi dst:string_t, src:string_t

ifdef _WIN64
    mov     rdi,rcx
    mov     rsi,rdx
else
    mov     edi,dst
    mov     esi,src
    mov     ecx,edi
endif
    jmp     .1
.0:
    mov     [rdi],eax
    add     rdi,4
.1:
    mov     eax,[rsi]
    add     rsi,4
    lea     edx,[rax-0x01010101]
    not     eax
    and     edx,eax
    not     eax
    and     edx,0x80808080
    jz      .0
    bt      edx,7
    mov     [rdi],al
    jc      .2
    bt      edx,15
    mov     [rdi+1],ah
    jc      .2
    shr     eax,16
    bt      edx,23
    mov     [rdi+2],al
    jc      .2
    mov     [rdi+3],ah
.2:
    mov     rax,rcx
    ret

strcpy endp

    end
