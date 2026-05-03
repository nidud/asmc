;
; v2.28: relative fixup error
;
    .x64
    .model flat
    .data
    d_08 label byte
    d_16 label word
    d_32 label dword
    d_64 label qword
    oword -1,-1
    .code
start:
    mov d_08[1],al      ; 2 --> 1
    mov d_16[2],ax      ; 4 --> 2
    mov d_32[4],eax     ; 8 --> 4
    mov d_64[8],rax     ;16 --> 8
    ret
    end start

