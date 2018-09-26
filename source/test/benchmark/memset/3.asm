    .code

    mov     rax,rcx
    imul    edx,edx,0x01010101
    movd    xmm0,edx
    pshufd  xmm0,xmm0,0

    .if r8 <= 64
        .switch notest r8
          .case 1
            mov [rax],dl
          .case 0
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
          .case 33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,\
                49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64
            movdqu [rax+16],xmm0
            movdqu [rax+r8-32],xmm0
          .case 17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
            movdqu [rax],xmm0
            movdqu [rax+r8-16],xmm0
            ret
        .endsw
    .endif

    vperm2f128 ymm0,ymm0,ymm0,0

    .if r8 > 128
        mov rcx,rax
        and cl,-64
        add rcx,64
        lea r9,[r8-64]
        and r9b,-64
        .repeat
            sub r9,64
            vmovdqa [rcx+r9],ymm0
            vmovdqa [rcx+r9+32],ymm0
        .untilz
    .endif
    vmovdqu [rax],ymm0
    vmovdqu [rax+32],ymm0
    vmovdqu [rax+r8-64],ymm0
    vmovdqu [rax+r8-32],ymm0
    ret

    end
