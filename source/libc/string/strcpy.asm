; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

if defined(__AVX__) and defined(_WIN64)

strcpy proc dst:ptr sbyte, src:ptr sbyte

    mov         rax,rcx
    mov         r8,rdx

    and         r8,-32              ; align to boundary
    vxorps      ymm0,ymm0,ymm0
    vpcmpeqb    ymm1,ymm0,[r8]      ; compare 32 byte
    vpmovmskb   r9d,ymm1            ; get result
    add         r8,32               ; next block

    mov         cl,dl               ; skip (rdx-r8) from result
    and         cl,32-1
    shr         r9d,cl

    test        r9d,r9d             ; case CL zero..
    jz          first_block         ; favor short lengths

    bsf         ecx,r9d             ; zero found in first block
    inc         ecx                 ; include '\0'

    test        cl,11110000B        ; 16..32
    jnz         copy_16_32
    test        cl,00001000B        ; 8..15
    jnz         copy_8_16
    test        cl,00000100B        ; 4..7
    jnz         copy_4_8
    test        cl,00000010B        ; 2..3
    jnz         copy_2_4
    mov         cl,[rdx]            ; 1
    mov         [rax],cl
    ret

copy_2_4:
    mov         r8w,[rdx]
    mov         dx,[rdx+rcx-2]
    mov         [rax+rcx-2],dx
    mov         [rax],r8w
    ret
copy_4_8:
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [rax+rcx-4],edx
    mov         [rax],r8d
    ret
copy_8_16:
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [rax],r8
    mov         [rax+rcx-8],rdx
    ret
copy_16_32:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [rax],xmm0
    movups      [rax+rcx-16],xmm1
    ret
copy_32_64:
    vmovups     ymm0,[rdx]
    vmovups     ymm1,[rdx+rcx-32]
    vmovups     [rax],ymm0
    vmovups     [rax+rcx-32],ymm1
    ret

first_block:

    vmovaps     ymm1,[r8]           ; size >= 2
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jz          size_32

    bsf         ecx,ecx
    sub         r8,rdx
    lea         ecx,[r8+rcx+1]
    cmp         ecx,32
    ja          copy_32_64
    test        cl,00110000B
    jnz         copy_16_32
    test        cl,00001000B
    jnz         copy_8_16
    test        cl,00000100B
    jnz         copy_4_8
    jmp         copy_2_4

size_32:

    vmovups     ymm2,[rdx]          ; size > 32
    vmovups     [rax],ymm2          ; overlap: 0..31 byte

    add         r8,32
    mov         rcx,r8
    sub         rcx,rdx
    lea         rdx,[rax+rcx]
    vmovups     [rdx-32],ymm1

loop_32:

    vmovaps     ymm1,[r8]
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jnz         tail

    vmovups     [rdx],ymm1
    add         rdx,32
    add         r8,32
    jmp         loop_32

tail:

    bsf         ecx,ecx
    vmovups     ymm1,[r8+rcx-31]
    vmovups     [rdx+rcx-31],ymm1
    ret

else

strcpy proc uses rsi rdi dst:string_t, src:string_t

    ldr     rdi,src
    ldr     rdx,dst
    mov     rsi,rdi
    xor     eax,eax
    mov     rcx,-1
    repne   scasb
    not     rcx
    mov     rax,rdx
    mov     rdi,rdx
    rep     movsb
    ret

endif

strcpy endp

    end
