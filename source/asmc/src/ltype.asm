; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc

ifndef _DLL
.data
  DEFINE_LTYPE _ltype
endif
.code

tstrupr proc fastcall string:string_t
    mov rdx,rcx
    .repeat
        .if ( isllower( [rcx] ) )
            and byte ptr [rcx],not 0x20
        .endif
        inc rcx
    .until !eax
    .return( rdx )
    endp

tstrstart proc fastcall string:string_t
    ltokstart( rcx )
    ret
    endp

ifdef _LIN64

tmemcpy proc fastcall dst:ptr, src:ptr, len:uint_t
    mov     r10,rdi
    mov     r11,rsi
    mov     rax,rcx
    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    rep     movsb
    mov     rsi,r11
    mov     rdi,r10
    ret
    endp


tmemset proc fastcall dst:ptr, chr:int_t, len:uint_t
    mov     r10,rdi
    mov     r9,rcx
    mov     rdi,rcx
    mov     eax,edx
    mov     ecx,r8d
    rep     stosb
    mov     rax,r9
    mov     rdi,r10
    ret
    endp


tmemcmp proc fastcall s1:ptr, s2:ptr, len:uint_t
    mov     r10,rdi
    mov     r11,rsi
    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    xor     eax,eax
    repz    cmpsb
    mov     rsi,r11
    mov     rdi,r10
    jz      .1
    sbb     eax,eax
    sbb     eax,-1
.1:
    ret
    endp


tstrlen proc fastcall s1:string_t
    mov     rdx,rdi
    mov     rdi,rcx
    mov     rcx,-1
    xor     eax,eax
    repnz   scasb
    mov     rax,rcx
    mov     rdi,rdx
    not     rax
    dec     rax
    ret
    endp


tmemicmp proc fastcall s1:ptr, s2:ptr, len:uint_t
    mov     eax,r8d
.1:
    test    eax,eax
    jz      .2
    dec     eax
    mov     r8b,[rcx+rax]
    cmp     r8b,[rdx+rax]
    je      .1
    xor     r8b,0x20
    cmp     r8b,[rdx+rax]
    je      .1
    sbb     eax,eax
    sbb     eax,-1
.2:
    ret
    endp


tstrchr proc fastcall string:string_t, char:int_t
    xor     eax,eax
.1:
    cmp     al,[rcx]
    jz      .3
    cmp     dl,[rcx]
    jz      .2
    inc     rcx
    jmp     .1
.2:
    mov     rax,rcx
.3:
    ret
    endp


tstrrchr proc fastcall string:string_t, char:int_t
    xor     eax,eax
.1:
    cmp     byte ptr [rcx],0
    jz      .2
    cmp     dl,[rcx]
    cmovz   rax,rcx
    inc     rcx
    jmp     .1
.2:
    ret
    endp


tstrcpy proc fastcall s1:string_t, s2:string_t
    mov     r8,rcx
.1:
    mov     al,[rdx]
    mov     [rcx],al
    inc     rdx
    inc     rcx
    test    al,al
    jnz     .1
    mov     rax,r8
    ret
    endp


tstrcat proc fastcall s1:string_t, s2:string_t
    mov     r10,rbx
    mov     r11,rcx
    mov     rbx,rcx
.0:
    mov     eax,[rbx]
    add     rbx,4
    lea     ecx,[rax-0x01010101]
    not     eax
    and     ecx,eax
    and     ecx,0x80808080
    jz      .0
    bsf     ecx,ecx
    shr     ecx,3
    lea     rbx,[rbx+rcx-4]
    mov     rcx,rdx
    jmp     .2
.1:
    mov     [rbx],eax
    add     rbx,4
.2:
    mov     eax,[rcx]
    add     rcx,4
    lea     edx,[rax-0x01010101]
    not     eax
    and     edx,eax
    not     eax
    and     edx,0x80808080
    jz      .1
    bt      edx,7
    mov     [rbx],al
    jc      .3
    bt      edx,15
    mov     [rbx+1],ah
    jc      .3
    shr     eax,16
    bt      edx,23
    mov     [rbx+2],al
    jc      .3
    mov     [rbx+3],ah
.3:
    mov     rax,r11
    mov     rbx,r10
    ret
    endp


tstrncpy proc fastcall s1:string_t, s2:string_t, len:int_t
    mov     r11,rdi
    mov     rdi,rcx
    mov     r10,rcx
    mov     ecx,r8d
.1:
    test    ecx,ecx
    jz      .2
    dec     ecx
    mov     al,[rdx]
    mov     [rdi],al
    add     rdx,1
    add     rdi,1
    test    al,al
    jnz     .1
    rep     stosb
.2:
    mov     rax,r10
    mov     rdi,r11
    ret
    endp


tstrcmp proc fastcall s1:string_t, s2:string_t
    dec     rcx
    dec     rdx
    mov     eax,1
.1:
    test    eax,eax
    jz      .2
    inc     rcx
    inc     rdx
    mov     al,[rcx]
    cmp     al,[rdx]
    je      .1
    sbb     eax,eax
    sbb     eax,-1
.2:
    ret
    endp


tstricmp proc fastcall s1:string_t, s2:string_t
    dec     rcx
    dec     rdx
    mov     eax,1
.1:
    test    eax,eax
    jz      .2
    inc     rcx
    inc     rdx
    mov     al,[rcx]
    cmp     al,[rdx]
    je      .1
    xor     al,0x20
    cmp     al,[rdx]
    je      .1
    xor     al,0x20
    cmp     al,[rdx]
    sbb     eax,eax
    sbb     eax,-1
.2:
    ret
    endp


tstrstr proc fastcall uses rsi rdi rbx s1:string_t, s2:string_t
    mov     rdi,rcx
    mov     rbx,rdx
    mov     esi,tstrlen(rbx)
    test    eax,eax
    jz      .3
    mov     ecx,tstrlen(rdi)
    test    eax,eax
    jz      .3
    xor     eax,eax
    dec     rsi
.0:
    mov     al,[rbx]
    repne   scasb
    mov     al,0
    jnz     .3
    test    esi,esi
    jz      .2
    cmp     ecx,esi
    jb      .3
    mov     edx,esi
.1:
    mov     al,[rbx+rdx]
    cmp     al,[rdi+rdx-1]
    jne     .0
    dec     edx
    jnz     .1
.2:
    lea     rax,[rdi-1]
.3:
    ret
    endp


tfwrite proc fastcall uses rsi rdi b:string_t, x:int_t, y:int_t, fp:LPFILE
    mov esi,edx
    mov rdi,rcx
    fwrite(rdi, esi, r8d, r9)
    ret
    endp

tfseek proc fastcall uses rsi rdi fp:LPFILE, offs:size_t, where:int_t
    mov rsi,rdx
    fseek(rcx, rsi, r8d)
    ret
    endp

endif

    end
