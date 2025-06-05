
; -- handle C-type RECORD fields

ifndef __ASMC64__
    .x64
    .model flat
endif

option casemap:none, win64:3

.pragma pack(push, 8)

.template T
    x	    db ?
    record
     a	    dd : 16 ?	; 04 should be aligned
     b	    dd : 15 ?	; 14 no alignment
     c	    dd :  1 ?	; 23 no alignment
    ends
    y	    db ?	; 08
    record q		; 09
     d	    db : 1 ?
     e	    db : 1 ?
     f	    db : 6 ?
    ends
    record
     g	    dw : 8 ?
     h	    dw : 8 ?
    ends
   .ends

.pragma pack(pop)

   .code

main proc

   local r:T

    mov eax,typeof T
    mov eax,typeof r
    mov eax,sizeof T
    mov eax,sizeof T.q

    mov eax,maskof T.a
    mov eax,maskof T.b
    mov eax,maskof T.c

    mov eax,T.a	    ; 4 - same offset
    mov eax,T.b	    ; 4
    mov eax,T.c	    ; 4


    ; bit-field to register

    mov eax,r.a	    ; MOVZX
    mov eax,r.b	    ; MOV/AND/SHR 16
    mov eax,r.c	    ; MOV/AND/SHR 31

    mov eax,r.q.d   ; MOVZX/AND
    mov eax,r.q.e   ; MOVZX/AND/SHR 1
    mov eax,r.q.f   ; MOVZX/AND/SHR 2

    mov eax,r.g	    ; MOVZX
    mov eax,r.h	    ; MOVZX

    ; imm to bit-field

    mov r.a,16	    ; MOV
    mov r.b,15	    ; AND/OR
    mov r.c,1	    ; OR

    mov r.q.d,1	    ; OR
    mov r.q.e,0	    ; AND
    mov r.q.f,0x3F  ; AND/OR

    mov r.g,8	    ; MOV
    mov r.h,8	    ; MOV

    ; compare bit-field,imm

    cmp r.a,16	    ; CMP
    cmp r.b,15	    ; MOV/AND/CMP
    cmp r.c,1	    ; TEST

    cmp r.q.d,1	    ; TEST
    cmp r.q.e,0	    ; TEST
    cmp r.q.f,0x3F  ; MOVZX/AND/CMP

    cmp r.g,8	    ; CMP
    cmp r.h,8	    ; CMP

    .if r.a	    ; TEST/JZ
    .endif
    .if r.a < 16    ; CMP/JNC
    .endif
    .if r.b < 16    ; MOV/AND/CMP/JNC
    .endif
    .if !r.q.d	    ; TEST/JNZ
    .endif

    ret

main endp

    end
