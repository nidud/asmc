    .code

    mov rax,rcx
    imul edx,edx,0x01010101
    movd xmm0,edx
    vpermilps xmm0,xmm0,0

    .if r8 <= 32
        .switch jmp r8
          .case 0
            ret
          .case 1
            mov [rax],dl
            ret
          .case 2,3,4
            mov [rax+r8-2],dx
            mov [rax],dx
            ret
          .case 9,10,11,12,13,14,15,16
            mov [rax+4],edx
            mov [rax+r8-8],edx
          .case 5,6,7,8
            mov [rax+r8-4],edx
            mov [rax],edx
            ret
          .case 17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
            movdqu [rax],xmm0
            movdqu [rax+r8-16],xmm0
            ret
        .endsw
    .endif

    vperm2f128 ymm0,ymm0,ymm0,0
    .if r8 > 64
        mov ecx,eax
        neg ecx
        and ecx,32-1
        mov r9,r8
        sub r9,rcx
        and r9b,-32
        add rcx,rax
        add rcx,r9
        neg r9
        .repeat
            vmovdqa [rcx+r9],ymm0
            add r9,32
        .untilz
    .endif
    vmovdqu [rax],ymm0
    vmovdqu [rax+r8-32],ymm0
    ret

    end
