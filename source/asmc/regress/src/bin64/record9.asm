
; -- additional handling for C-type 64-bit RECORD fields

ifndef __ASMC64__
    .x64
    .model flat
endif

option casemap:none, fieldalign:8

.template R
    record
     a  dd :  1 = 1 ?
     b  dd :  3 = 1 ?
     c  dd :  4 = 1 ?
     d  dd :  8 = 1 ?
     e  dd : 16 = 1 ?
    ends
   .ends

.template T
    x   dd ?
    record q
     a  dq :  1 = 1 ?
     b  dq :  7 = 1 ?
     c  dq :  8 = 1 ?
     d  dq : 33 = 1 ?
     e  dq : 14 = 1 ?
     f  dq :  1 = 1 ?
    ends
   .ends

   .data
    r R <>
    t T <>

   .code

    mov eax,R {}
    mov rax,T.q {}

    end
