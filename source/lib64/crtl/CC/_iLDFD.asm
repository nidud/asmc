include crtl.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

_iLDFD proc
    ;
    ; long double[rax] to double[rdx]
    ;
    push    rdx
    movzx   ecx,word ptr [eax+8]
    mov     edx,[eax+4]
    mov     eax,[eax]
    mov     r8d,0FFFFF800h
    mov     r10d,eax
    shl     r10d,22
    jnc     L002
    jnz     @F
    add     r8d,r8d
@@:
    add     eax,00000800h
    adc     edx,0
    jnc     L002
    mov     edx,80000000h
    inc     ecx
L002:
    and     eax,r8d
    mov     r10d,ecx
    and     ecx,00007FFFh
    add     ecx,0FFFFC400h
    and     ecx,0000FFFFh
    cmp     ecx,000007FFh
    jnc     L005
    test    ecx,ecx
    jnz     @F
    shrd    eax,edx,12
    add     edx,edx
    shr     edx,12
    jmp     L004
@@:
    shrd    eax,edx,11
    add     edx,edx
    shrd    edx,ecx,11
L004:
    shl     r10d,1
    rcr     edx,1
    jmp     toend
L005:
    cmp     ecx,0000C400h
    jb      L009
    cmp     ecx,0000FFCCh
    jl      L007
    sub     ecx,0000000Ch
    neg     ecx
    and     ecx,0FFFF0000h
    cmp     ecx,00000020h
    jb      L006
    sub     ecx,00000020h
    mov     r8d,eax
    mov     eax,edx
    xor     edx,edx
L006:
    shrd    r8d,eax,cl
    shrd    eax,edx,cl
    shr     edx,cl
    add     r8d,r8d
    adc     eax,0
    adc     edx,0
    jmp     toend
L007:
    xor     eax,eax
    xor     edx,edx
    shl     r10d,17
    rcr     edx,1
    jmp     toend
L009:
    shrd    eax,edx,11
    add     edx,edx
    shr     edx,11
    shl     r10d,1
    rcr     edx,1
    or      edx,7FF00000h
    cmp     ecx,000043FFh
    je      toend
    ;int     3   ; OVERFLOW exception
toend:
    pop     r8
    mov     [r8],eax
    mov     [r8+4],edx
    ret
_iLDFD endp

    END
