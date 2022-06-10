; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ltype.inc

    .data
     DEFINE_LTYPE _ltype

    .code

    option dotname
    ;option stackbase:esp

tstrcmp proc fastcall a:string_t, b:string_t

    mov     eax,1
.0:
    test    al,al
    jz      .1
    mov     al,[ecx]
    inc     edx
    inc     ecx
    cmp     al,[edx-1]
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.1:
    ret

tstrcmp endp

tmemcmp proc fastcall uses esi edi dst:ptr, src:ptr, size:size_t

    mov     edi,dst
    mov     esi,edx
    mov     ecx,size
    xor     eax,eax
    repe    cmpsb
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.0:
    ret

tmemcmp endp

tmemicmp proc fastcall uses esi edi dst:ptr, src:ptr, size:size_t

    mov     esi,dst
    mov     edi,edx
    mov     eax,size
.0:
    test    eax,eax
    jz      .1

    mov     cl,[esi]
    mov     dl,[edi]
    inc     esi
    inc     edi
    dec     eax
    cmp     cl,dl
    je      .0

    mov     ch,cl
    sub     cl,'a'
    cmp     cl,'Z'-'A'+1
    sbb     cl,cl
    and     cl,'a'-'A'
    xor     cl,ch

    mov     dh,dl
    sub     dl,'a'
    cmp     dl,'Z'-'A'+1
    sbb     dl,dl
    and     dl,'a'-'A'
    xor     dl,dh

    cmp     cl,dl
    je      .0

    sbb     eax,eax
    sbb     eax,-1
.1:
    ret

tmemicmp endp

tstricmp proc fastcall uses esi edi a:string_t, b:string_t

    mov     esi,a
    mov     edi,edx
    mov     eax,1
.0:
    test    al,al
    jz      .1

    mov     al,[esi]
    mov     cl,[edi]
    inc     esi
    inc     edi
    cmp     al,cl
    je      .0

    mov     dl,al
    sub     al,'a'
    cmp     al,'Z'-'A'+1
    sbb     al,al
    and     al,'a'-'A'
    xor     al,dl

    mov     dl,cl
    sub     cl,'a'
    cmp     cl,'Z'-'A'+1
    sbb     cl,cl
    and     cl,'a'-'A'
    xor     cl,dl

    cmp     al,cl
    je      .0

    sbb     eax,eax
    sbb     eax,-1
.1:
    ret

tstricmp endp


tstrupr proc fastcall string:string_t

    push     ecx
.0:
    mov     al,[ecx]
    test    al,al
    jz      .1

    sub     al,'a'
    cmp     al,'Z'-'A'+1
    sbb     al,al
    and     al,'a'-'A'
    xor     [ecx],al
    inc     ecx
    jmp     .0
.1:
    pop     eax
    ret

tstrupr endp

tstrstart proc watcall string:string_t

    movzx   ecx,byte ptr [eax]
.0:
    test    _ltype[ecx+1],_SPACE
    jz      .1
    inc     eax
    mov     cl,[eax]
    jmp     .0
.1:
    ret

tstrstart endp

    end

