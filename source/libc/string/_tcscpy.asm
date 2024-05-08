; _TCSCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcscpy proc dst:LPTSTR, src:LPTSTR

    ldr         rcx,dst
    ldr         rdx,src

if defined(__AVX__) and defined(_WIN64) and not defined(_UNICODE)

    mov         rax,rcx
    mov         r10,rdx
    and         r10,-32
    vxorps      ymm0,ymm0,ymm0
    vpcmpeqb    ymm1,ymm0,[r10]
    vpmovmskb   r9d,ymm1
    add         r10,32
    mov         cl,dl
    and         cl,32-1
    shr         r9d,cl
    test        r9d,r9d
    jz          .0
    bsf         ecx,r9d
    mov         r9,rax
    jmp         .4
.0:
    vmovaps     ymm1,[r10]
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jz          .1
    bsf         ecx,ecx
    sub         r10,rdx
    add         ecx,r10d
    mov         r9,rax
    jmp         .4
.1:
    vmovups     ymm3,[rdx]
    lea         rcx,[r10+32]
    sub         rcx,rdx
    lea         rdx,[r10+32]
    lea         r9,[rax+rcx]
    vmovups     [r9-32],ymm1
.2:
    vmovaps     ymm1,[rdx]
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jnz         .3
    vmovups     [r9],ymm1
    add         rdx,32
    add         r9,32
    jmp         .2
.3:
    vmovups     [rax],ymm3
    bsf         ecx,ecx
.4:
    inc         ecx
    test        cl,11100000B
    jnz         .32_64
    test        cl,00010000B
    jnz         .16_32
    test        cl,00001000B
    jnz         .08_16
    test        cl,00000100B
    jnz         .04_08
    test        cl,00000010B
    jnz         .02_04
    mov         cl,[rdx]
    mov         [r9],cl
    jmp         .5
.02_04:
    mov         r8w,[rdx]
    mov         dx,[rdx+rcx-2]
    mov         [r9+rcx-2],dx
    mov         [r9],r8w
    jmp         .5
.04_08:
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [r9+rcx-4],edx
    mov         [r9],r8d
    jmp         .5
.08_16:
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [r9],r8
    mov         [r9+rcx-8],rdx
    jmp         .5
.16_32:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [r9],xmm0
    movups      [r9+rcx-16],xmm1
    jmp         .5
.32_64:
    vmovups     ymm0,[rdx]
    vmovups     ymm1,[rdx+rcx-32]
    vmovups     [r9],ymm0
    vmovups     [r9+rcx-32],ymm1
.5:
    vzeroupper

elseif defined(_WIN64) and not defined(_UNICODE)

    mov         rax,rcx
    mov         r10,rdx
    and         r10,-16
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,[r10]
    pmovmskb    r9d,xmm0
    add         r10,16
    mov         cl,dl
    and         cl,16-1
    shr         r9d,cl
    test        r9d,r9d
    jz          .0
    bsf         ecx,r9d
    mov         r9,rax
    jmp         .4
.0:
    movaps      xmm1,[r10]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jz          .1
    bsf         ecx,ecx
    sub         r10,rdx
    add         ecx,r10d
    mov         r9,rax
    jmp         .4
.1:
    movups      xmm2,[rdx]
    lea         rcx,[r10+16]
    sub         rcx,rdx
    lea         rdx,[r10+16]
    lea         r9,[rax+rcx]
    movups      [r9-16],xmm1
.2:
    movaps      xmm1,[rdx]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jnz         .3
    movups      [r9],xmm1
    add         rdx,16
    add         r9,16
    jmp         .2
.3:
    movups      [rax],xmm2
    bsf         ecx,ecx
.4:
    inc         ecx
    test        cl,11110000B
    jnz         .16_32
    test        cl,00001000B
    jnz         .08_16
    test        cl,00000100B
    jnz         .04_08
    test        cl,00000010B
    jnz         .02_04
    mov         cl,[rdx]
    mov         [r9],cl
    jmp         .5
.02_04:
    mov         r8w,[rdx]
    mov         dx,[rdx+rcx-2]
    mov         [r9+rcx-2],dx
    mov         [r9],r8w
    jmp         .5
.04_08:
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [r9+rcx-4],edx
    mov         [r9],r8d
    jmp         .5
.08_16:
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [r9],r8
    mov         [r9+rcx-8],rdx
    jmp         .5
.16_32:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [r9],xmm0
    movups      [r9+rcx-16],xmm1
.5:

else

ifdef _WIN64
    mov     r8,rcx
else
    push    ecx
endif

.0:
    mov     _tal,[rdx]
    mov     [rcx],_tal
    add     rdx,TCHAR
    add     rcx,TCHAR
    test    _tal,_tal
    jnz     .0

ifdef _WIN64
    mov     rax,r8
else
    pop     eax
endif

endif
    ret

_tcscpy endp

    end
