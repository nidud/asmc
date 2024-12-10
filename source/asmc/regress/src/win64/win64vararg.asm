
option win64:auto

printf proto :ptr sbyte, :vararg

    .data
     d real4 33.0

    .code

main proc

    ; sub     rsp, 40
    ; movsd   xmm3, F0000
    ; movq    r9,   xmm3
    ; movaps  xmm2, xmm0
    ; movq    r8,   xmm2
    ; cvtss2sd xmm1, d
    ; movq    rdx,  xmm1
    ; xor     ecx,  ecx
    ; call    printf
    ; add     rsp, 40

    invoke printf, 0, d, xmm0, 2.0
    ret

main endp

    end

