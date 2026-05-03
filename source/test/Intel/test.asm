;
; http://www.intel.com/software/sde
;
; Intel Software Development Emulator
;

include stdio.inc
include intrin.inc

    .code

strlen proc string:string_t

    mov     rdx,rcx
    mov     rax,-1
    and     ecx,64-1
    shl     rax,cl
    kmovq   k2,rax
    mov     rax,rdx
    and     rax,-64
    vxorps  zmm0,zmm0,zmm0
    vpcmpeqb k1{k2},zmm0,[rax]

    .while 1

        add   rax,64
        kmovq rcx,k1
        .break .if rcx

        vpcmpeqb k1,zmm0,[rax]
    .endw
    bsf rcx,rcx
    lea rax,[rax+rcx-64]
    sub rax,rdx
    ret

strlen endp

PrintK proc string:string_t

  local kx[2]:qword

    kmovq r8,k2
    kmovq r9,k1

    printf( " input:\t%016llX - alignment\n"
            " K2:\t%016llX - align mask\n"
            " K1:\t%016llX - end mask\n", rcx, r8, r9 )
    ret

PrintK endp

if 0

PrintZMM0 proc string:string_t

  local zm:__m512i

    vmovups zm,zmm0

    printf(" zmm0:\t%016llX%016llX%016llX%016llX\n"
           "\t%016llX%016llX%016llX%016llX\n",
           zm.m512i_u64[0x38], zm.m512i_u64[0x30],
           zm.m512i_u64[0x28], zm.m512i_u64[0x20],
           zm.m512i_u64[0x18], zm.m512i_u64[0x10],
           zm.m512i_u64[0x08], zm.m512i_u64[0x00])
    ret

PrintZMM0 endp

endif

main proc

 local buffer[128]:char_t

    mov eax,'x'
    lea rdi,buffer
    mov ecx,127
    rep stosb
    xor eax,eax
    stosb

    printf("strlen(\"a\"): %d\n", strlen("a"))
    PrintK("a")
    printf("strlen(\"abc\"): %d\n", strlen("abc"))
    PrintK("abc")
    printf("strlen(buffer): %d\n", strlen(&buffer))
    PrintK(&buffer)
    xor eax,eax
    ret

main endp

    end
