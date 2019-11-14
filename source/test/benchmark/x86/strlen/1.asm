    .686
    .xmm
    .model flat
    .code

    mov     eax,[esp+4]
    mov     ecx,[esp+4]
    and     eax,-16
    and     ecx,16-1
    or      edx,-1
    shl     edx,cl
    xorps   xmm0,xmm0
    pcmpeqb xmm0,[eax]
    add     eax,16
    pmovmskb ecx,xmm0
    xorps   xmm0,xmm0
    and     ecx,edx
    jnz     L2
L1:
    movaps  xmm1,[eax]
    pcmpeqb xmm1,xmm0
    pmovmskb ecx,xmm1
    add     eax,16
    test    ecx,ecx
    jz      L1
L2:
    bsf     ecx,ecx
    lea     eax,[eax+ecx-16]
    sub     eax,[esp+4]
    ret

    end
