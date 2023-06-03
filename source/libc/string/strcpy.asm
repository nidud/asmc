; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option dotname

if defined(__AVX__) and defined(_WIN64)

strcpy::
ifdef __UNIX__
    mov     rcx,rdi
    mov     rdx,rsi
endif
    mov     rax,rcx
    mov     r10,rdx
    and     r10,-32
    vxorps  ymm0,ymm0,ymm0
    vpcmpeqb ymm1,ymm0,[r10]
    vpmovmskb r9d,ymm1
    add     r10,32
    mov     cl,dl
    and     cl,32-1
    shr     r9d,cl
    test    r9d,r9d
    jz      .64
    bsf     ecx,r9d
    inc     ecx
    test    cl,0xF0
    jnz     .16
    test    cl,0x08
    jnz     .08
    test    cl,0x04
    jnz     .04
    test    cl,0x02
    jnz     .02
    mov     cl,[rdx]
    mov     [rax],cl
    jmp     .3
.0:
    bsf     ecx,ecx
    sub     r10,rdx
    lea     ecx,[r10+rcx+1]
    cmp     ecx,32
    ja      .32
    test    cl,0x30
    jnz     .16
    test    cl,0x08
    jnz     .08
    test    cl,0x04
    jnz     .04
.02:
    mov     r8w,[rdx]
    mov     dx,[rdx+rcx-2]
    mov     [rax+rcx-2],dx
    mov     [rax],r8w
    jmp     .3
.04:
    mov     r8d,[rdx]
    mov     edx,[rdx+rcx-4]
    mov     [rax+rcx-4],edx
    mov     [rax],r8d
    jmp     .3
.08:
    mov     r8,[rdx]
    mov     rdx,[rdx+rcx-8]
    mov     [rax],r8
    mov     [rax+rcx-8],rdx
    jmp     .3
.16:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+rcx-16]
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm1
    jmp     .3
.32:
    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+rcx-32]
    vmovups [rax],ymm0
    vmovups [rax+rcx-32],ymm1
    jmp     .3
.64:
    vmovaps ymm1,[r10]
    vpcmpeqb ymm2,ymm0,ymm1
    vpmovmskb ecx,ymm2
    test    ecx,ecx
    jnz     .0
    vmovups ymm2,[rdx]
    vmovups [rax],ymm2
    add     r10,32
    mov     rcx,r10
    sub     rcx,rdx
    lea     rdx,[rax+rcx]
    vmovups [rdx-32],ymm1
    jmp     .2
.1:
    vmovups [rdx],ymm1
    add     rdx,32
    add     r10,32
.2:
    vmovaps ymm1,[r10]
    vpcmpeqb ymm2,ymm0,ymm1
    vpmovmskb ecx,ymm2
    test    ecx,ecx
    jz      .1
    bsf     ecx,ecx
    vmovups ymm1,[r10+rcx-31]
    vmovups [rdx+rcx-31],ymm1
.3:
    vzeroupper
    ret

else
if defined(__UNIX__) and defined(_WIN64)
strcpy proc dst:string_t, src:string_t
else
strcpy proc uses rsi rdi dst:string_t, src:string_t
endif

    ldr     rcx,dst
    ldr     rsi,src
    mov     rdi,rsi
    mov     rdx,rcx
    xor     eax,eax
    mov     rcx,-1
    repne   scasb
    not     rcx
    mov     rax,rdx
    mov     rdi,rdx
    rep     movsb
    ret

strcpy endp
endif
    end
