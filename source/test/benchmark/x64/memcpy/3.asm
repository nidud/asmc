    .code

    mov rax,rcx

    .if r8 <= 64

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

          .case 33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,\
                49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64
            vmovdqu ymm0,[rdx]
            vmovdqu ymm1,[rdx+r8-32]
            vmovups [rax],ymm0
            vmovups [rax+r8-32],ymm1
            ret
            ;db 4 dup(0x90)
        .endsw
    .endif

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
            vmovdqu [rax],ymm2
            vmovdqu [rax+32],ymm3
            vmovdqu [rax+r8-32],ymm4
            vmovdqu [rax+r8-64],ymm5
            ret
            db 13 dup(0x90)
        .endif

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
    vmovdqu [rax],ymm2
    vmovdqu [rax+32],ymm3
    vmovdqu [rax+r8-32],ymm4
    vmovdqu [rax+r8-64],ymm5
    ret

    end
