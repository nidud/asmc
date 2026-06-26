; IMPORT32.ASM--
;
; v2.37.77: added IMPORT for EXTERNDEF and PROTO
;
   .486
   .model flat, c
    option dllimport:<msvcrt>
    externdef import _dstbias:dword
    externdef import printf:dword
    externdef import exit:dword
   .data
    format sbyte "_dstbias: %d",10,0
   .code
main:
    mov     eax,_dstbias
    push    [eax]
    push    offset format
    call    printf
    push    0
    call    exit
    end     main
