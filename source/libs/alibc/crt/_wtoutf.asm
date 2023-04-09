; _WTOUTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert Wide char to UTF-8
;
; Return EAX 1..4 bytes, ECX byte count
;
include crtl.inc

.code

_wtoutf proc watcall wc:wchar_t

    movzx eax,ax
    .if ( eax < 0x80 )

        mov ecx,1
       .return
    .endif

    option dotname

    mov     esi,eax
    xor     edi,edi
    xor     eax,eax
    mov     edx,63
    mov     ecx,128
.0:
    cmp     esi,0x80
    jbe     .1
    mov     al,sil
    and     al,0x3F
    or      al,0x80
    shl     eax,8
    shr     esi,6
    inc     edi
    lea     ecx,[rcx+rdx+1]
    shr     edx,1
    jmp     .0
.1:
    mov     al,cl
    or      al,sil
    lea     ecx,[rdi+1]
    ret

_wtoutf endp

    end
