; IMPORT64_2.ASM--
;
; v2.37.80: relocation fixup
;
    option dllimport:<msvcrt>
    externdef import _dstbias:qword
    externdef import printf:qword
    externdef import exit:qword
   .data
    format sbyte "_dstbias: %d",10,0
    p dq format
   .code
main:
    sub     rsp,40
    mov     rax,_dstbias
    mov     edx,[rax]
    mov     rcx,p
    call    printf
    xor     ecx,ecx
    call    exit
    end     main
