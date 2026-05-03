
option win64:auto

printf proto :ptr sbyte, :vararg

    .data
     d real4 33.0

    .code

main proc

    ; sub     rsp, 8
    ; movsd   xmm2, qword ptr [F0000]
    ; movaps  xmm1, xmm0
    ; cvtss2sd xmm0, dword ptr [d]
    ; xor     edi, edi
    ; mov     eax, 3
    ; call    printf
    ; add     rsp, 8

    invoke printf, 0, d, xmm0, 2.0
    ret

main endp

    end

