
; -- new record alignment

ifndef __ASMC64__
    .x64
    .model flat
endif

.pragma pack(push, 8)

.template T
    x	    db ?
    record
     a	    dd : 16 ? ; 04 should be aligned
     b	    dd : 15 ? ; 14 no alignment
     c	    dd :  1 ? ; 23 no alignment
    ends
   .ends

.pragma pack(pop)

   .code

    mov eax,(1 shl ( T.c - T.a )) ; should be 31.. (0x80000000)
    end
