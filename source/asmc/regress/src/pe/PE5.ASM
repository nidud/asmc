
;--- testcase and fix provided by nidud

    .x64
    .model flat

    .data
    d_08 label byte
    d_16 label word
    d_32 label dword
    d_64 label qword
    qword -1,-1

    .code
start:
    mov d_08[0],0
    mov d_08[1],0
    mov d_08[2],0
    mov d_08[3],0
    mov d_16[0],0
    mov d_16[2],0
    mov d_16[4],0
    mov d_16[6],0
    mov d_32[0],0
    mov d_32[4],0
    ret

    end start

