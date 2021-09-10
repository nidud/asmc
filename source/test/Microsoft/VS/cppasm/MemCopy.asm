; MEMCOPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

if defined(__AVX__) or defined(__AVX2__)
CHUNK equ 64
else
CHUNK equ 16
endif

    .code

    option win64:rsp noauto

MemCopy proc target:ptr sbyte, source:ptr sbyte, count:sdword

    mov rax,rcx

    .if r8 <= CHUNK

        .switch jmp r8

          .case 0
            ret

          .case 1
            mov cl,[rdx]
            mov [rax],cl
            ret

          .case 2,3,4
            mov cx,[rdx]
            mov dx,[rdx+r8-2]
            mov [rax],cx
            mov [rax+r8-2],dx
            ret

          .case 5,6,7,8
            mov ecx,[rdx]
            mov edx,[rdx+r8-4]
            mov [rax],ecx
            mov [rax+r8-4],edx
            ret

          .case 9,10,11,12,13,14,15,16
            mov rcx,[rdx]
            mov rdx,[rdx+r8-8]
            mov [rax],rcx
            mov [rax+r8-8],rdx
            ret

if (CHUNK EQ 64)

          .case 17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
            movdqu xmm0,[rdx]
            movdqu xmm1,[rdx+r8-16]
            movups [rax],xmm0
            movups [rax+r8-16],xmm1
            ret

          .case 33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,\
                49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64
            vmovdqu ymm0,[rdx]
            vmovdqu ymm1,[rdx+r8-32]
            vmovups [rax],ymm0
            vmovups [rax+r8-32],ymm1
            ret
endif

        .endsw
    .endif

if (CHUNK EQ 16)

    movups xmm2,[rdx]
    movups xmm3,[rdx+r8-16]

    .if r8 > 32

        movups xmm4,[rdx+16]
        movups xmm5,[rdx+r8-32]

        .if r8 >= 64

            neg ecx
            and ecx,32-1
            add rdx,rcx
            mov r9,r8
            sub r9,rcx
            add rcx,rax
            and r9b,-32

            .if rcx > rdx

                .repeat

                    sub r9,32
                    movups xmm0,[rdx+r9]
                    movups xmm1,[rdx+r9+16]
                    movaps [rcx+r9],xmm0
                    movaps [rcx+r9+16],xmm1

                .untilz

            .else

                lea rcx,[rcx+r9]
                lea rdx,[rdx+r9]
                neg r9

                .repeat

                    movups xmm0,[rdx+r9]
                    movups xmm1,[rdx+r9+16]
                    movaps [rcx+r9],xmm0
                    movaps [rcx+r9+16],xmm1
                    add r9,32

                .untilz

            .endif

        .endif

        movups [rax+16],xmm4
        movups [rax+r8-32],xmm5
    .endif

    movups [rax],xmm2
    movups [rax+r8-16],xmm3

else

    vmovdqu ymm2,[rdx]
    vmovdqu ymm3,[rdx+32]
    vmovdqu ymm4,[rdx+r8-32]
    vmovdqu ymm5,[rdx+r8-64]

    .if r8 > 128

        mov ecx,eax
        neg ecx
        and ecx,64-1
        add rdx,rcx
        mov r9,r8
        sub r9,rcx
        add rcx,rax
        and r9b,-64

        .if rcx > rdx

            .repeat

                sub r9,64
                vmovdqu ymm0,[rdx+r9]
                vmovdqu ymm1,[rdx+r9+32]
                vmovdqa [rcx+r9],ymm0
                vmovdqa [rcx+r9+32],ymm1

            .untilz

        .else

            lea rcx,[rcx+r9]
            lea rdx,[rdx+r9]
            neg r9

            .repeat

                vmovdqu ymm0,[rdx+r9]
                vmovdqu ymm1,[rdx+r9+32]
                vmovdqa [rcx+r9],ymm0
                vmovdqa [rcx+r9+32],ymm1
                add r9,64

            .untilz
        .endif
    .endif

    vmovdqu [rax],ymm2
    vmovdqu [rax+32],ymm3
    vmovdqu [rax+r8-32],ymm4
    vmovdqu [rax+r8-64],ymm5

endif

    ret

MemCopy endp

    end
