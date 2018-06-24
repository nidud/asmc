    .code

memcpy::
memmove::

    mov rax,rcx

    .if r8 <= 16

        option switch:table, switch:notest, switch:regax

        .switch r8

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
        .endsw
    .endif

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
    ret

    end
