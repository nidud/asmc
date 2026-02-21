; IMPORT64.ASM--
;
; v2.37.77: added IMPORT for EXTERNDEF and PROTO
;
   .x64
   .model flat, fastcall
    option dllimport:<msvcrt>
    externdef import _dstbias:qword
    externdef import printf:qword
    externdef import exit:qword
   .data
    format sbyte "_dstbias: %d",10,0
   .code
main:
    sub     rsp,40
    mov     rax,_dstbias
    mov     edx,[rax]
    lea     rcx,format
    call    printf
    xor     ecx,ecx
    call    exit
    end     main
