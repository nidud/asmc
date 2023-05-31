; _WTOUTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert Wide char to UTF-8
;
; Return EAX 1..4 bytes, ECX byte count
;
include stdlib.inc

    .code

    option dotname

_wtoutf proc uses rdi rbx wc:wchar_t

    ldr ax,wc

    movzx eax,ax
    .if ( eax < 0x80 )

        mov ecx,1
       .return
    .endif

    mov     ebx,eax
    xor     edi,edi
    xor     eax,eax
    mov     edx,63
    mov     ecx,128
.0:
    cmp     ebx,0x80
    jbe     .1
    mov     al,bl
    and     al,0x3F
    or      al,0x80
    shl     eax,8
    shr     ebx,6
    inc     edi
    lea     ecx,[rcx+rdx+1]
    shr     edx,1
    jmp     .0
.1:
    mov     al,cl
    or      al,bl
    lea     ecx,[rdi+1]
    ret

_wtoutf endp

    end
