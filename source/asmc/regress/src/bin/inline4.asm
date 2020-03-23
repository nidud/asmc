
; v2.31.24 :vararg {

    .x64
    .model flat, fastcall

    option casemap:none, win64:auto

w64 proto fastcall :vararg { exitm<> }
sys proto syscall  :vararg { exitm<> }

    .code

main proc

    w64 ( rcx, rdx, r8, r9)
    sys ( rdi, rsi, rdx, rcx, r8, r9 )
    sys ( xmm0, xmm1, xmm2, xmm3, xmm4, xmm5 )
    w64 ( xmm0, xmm1, xmm2, xmm3 )
    w64 ( 1.0, 2.0, 3.0, 4.0, 5.0 )
    sys ( 1.0, 2.0, 3.0, 4.0, 5.0 )
    ret

main endp

    end

