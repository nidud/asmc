    .code

    mov rax,rcx

    .if r8 <= 32

        .switch notest r8

          .case 0
            ret

          .case 1
            mov cl,[rdx]
            mov [rax],cl
            ret

          .case 2,3,4
            mov cx,[rdx]
            mov dx,[rdx+r8-2]
            mov [rax+r8-2],dx
            mov [rax],cx
            ret

          .case 5,6,7,8
            mov ecx,[rdx]
            mov edx,[rdx+r8-4]
            mov [rax+r8-4],edx
            mov [rax],ecx
            ret

          .case 9,10,11,12,13,14,15,16
            mov rcx,[rdx]
            mov rdx,[rdx+r8-8]
            mov [rax],rcx
            mov [rax+r8-8],rdx
            ret

          .case 17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
            movdqu xmm0,[rdx]
            movdqu xmm1,[rdx+r8-16]
            movups [rax],xmm0
            movups [rax+r8-16],xmm1
            ret
        .endsw
    .endif

    movups xmm2,[rdx]
    movdqu xmm3,[rdx+16]
    movdqu xmm4,[rdx+r8-16]
    movdqu xmm5,[rdx+r8-32]
    .if r8 > 64

        mov ecx,eax
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
            movups [rax],xmm2
            movups [rax+16],xmm3
            movups [rax+r8-16],xmm4
            movups [rax+r8-32],xmm5
            ret
            db 5 dup(0x90)
        .endif

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
    movups [rax],xmm2
    movups [rax+16],xmm3
    movups [rax+r8-16],xmm4
    movups [rax+r8-32],xmm5
    ret

    end
