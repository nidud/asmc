
; -- additional handling for C-type 64-bit RECORD fields

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

    and r.a,0x1
    and r.b,0x2
    and r.c,0x4
    and r.d,0xC1
    and r.e,0x10C1

    and t.q.a,1
    and t.q.b,0x41
    and t.q.c,0xC1
    and t.q.d,0x100100010
    and t.q.e,1

    end
