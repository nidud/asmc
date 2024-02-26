; _TSTRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

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
    jz          .64
    bsf         ecx,r9d
    inc         ecx
    test        cl,0xF0
    jnz         .16
    test        cl,0x08
    jnz         .08
    test        cl,0x04
    jnz         .04
    test        cl,0x02
    jnz         .02
    mov         cl,[rdx]
    mov         [rax],cl
    jmp         .3
.0:
    bsf         ecx,ecx
    sub         r10,rdx
    lea         ecx,[r10+rcx+1]
    cmp         ecx,32
    ja          .32
    test        cl,0x30
    jnz         .16
    test        cl,0x08
    jnz         .08
    test        cl,0x04
    jnz         .04
.02:
    mov         r8w,[rdx]
    mov         dx,[rdx+rcx-2]
    mov         [rax+rcx-2],dx
    mov         [rax],r8w
    jmp         .3
.04:
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [rax+rcx-4],edx
    mov         [rax],r8d
    jmp         .3
.08:
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [rax],r8
    mov         [rax+rcx-8],rdx
    jmp         .3
.16:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [rax],xmm0
    movups      [rax+rcx-16],xmm1
    jmp         .3
.32:
    vmovups     ymm0,[rdx]
    vmovups     ymm1,[rdx+rcx-32]
    vmovups     [rax],ymm0
    vmovups     [rax+rcx-32],ymm1
    jmp         .3
.64:
    vmovaps     ymm1,[r10]
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jnz         .0
    vmovups     ymm2,[rdx]
    vmovups     [rax],ymm2
    add         r10,32
    mov         rcx,r10
    sub         rcx,rdx
    lea         rdx,[rax+rcx]
    vmovups     [rdx-32],ymm1
    jmp         .2
.1:
    vmovups     [rdx],ymm1
    add         rdx,32
    add         r10,32
.2:
    vmovaps     ymm1,[r10]
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jz          .1
    bsf         ecx,ecx
    vmovups     ymm1,[r10+rcx-31]
    vmovups     [rdx+rcx-31],ymm1
.3:
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
    jz          .4
    bsf         ecx,r9d
    inc         ecx
    test        cl,00001000B
    jnz         .2
    test        cl,00000100B
    jnz         .1
    test        cl,00000010B
    jnz         .0
    mov         cl,[rdx]
    mov         [rax],cl
    jmp         .8
.0:
    mov         r8w,[rdx]
    mov         dx,[rdx+rcx-2]
    mov         [rax+rcx-2],dx
    mov         [rax],r8w
    jmp         .8
.1:
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [rax+rcx-4],edx
    mov         [rax],r8d
    jmp         .8
.2:
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [rax],r8
    mov         [rax+rcx-8],rdx
    jmp         .8
.3:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [rax],xmm0
    movups      [rax+rcx-16],xmm1
    jmp         .8
.4:
    movaps      xmm1,[r10]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jz          .5
    bsf         ecx,ecx
    sub         r10,rdx
    lea         ecx,[r10+rcx+1]
    test        cl,11110000B
    jnz         .3
    test        cl,00001000B
    jnz         .2
    test        cl,00000100B
    jnz         .1
    jmp         .0
.5:
    movups      xmm2,[rdx]
    movups      [rax],xmm2
    add         r10,16
    mov         rcx,r10
    sub         rcx,rdx
    lea         rdx,[rax+rcx]
    movups      [rdx-16],xmm1
.6:
    movaps      xmm1,[r10]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jnz         .7
    movups      [rdx],xmm1
    add         rdx,16
    add         r10,16
    jmp         .6
.7:
    bsf         ecx,ecx
    movups      xmm0,[r10+rcx-15]
    movups      [rdx+rcx-15],xmm0
.8:

else

ifdef _WIN64
    mov     r8,rcx
else
    push    ecx
endif

.0:
    mov     __a,[rdx]
    mov     [rcx],__a
    add     rdx,TCHAR
    add     rcx,TCHAR
    test    __a,__a
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
