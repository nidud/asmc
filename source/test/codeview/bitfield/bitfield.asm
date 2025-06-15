
; -- handle C-type RECORD fields

includelib libc.lib

option casemap:none, win64:3

.pragma pack(push, 8)

.template T
    x       db ?
    record
     a      dd : 16 ?   ; 04 should be aligned
     b      dd : 15 ?   ; 14 no alignment
     c      dd :  1 ?   ; 23 no alignment
    ends
    y       db ?
    record q
     d      db : 1 ?
     e      db : 1 ?
     f      db : 6 ?
    ends
    record
     g      dw : 8 ?
     h      dw : 8 ?
    ends
   .ends

.pragma pack(pop)

   .code

main proc

   local r:T

    mov eax,typeof T        ; 12
    mov eax,typeof r        ; 12
    mov eax,sizeof T        ; 12
    mov eax,sizeof T.q      ; 1

    mov eax,maskof T.a      ; 0000FFFF
    mov eax,maskof T.b      ; 7FFF0000
    mov eax,maskof T.c      ; 80000000

    mov eax,maskof r.a      ; ---
    mov eax,maskof r.b
    mov eax,maskof r.c

    mov eax,widthof r.a     ; 16
    mov eax,widthof r.b     ; 15
    mov eax,widthof r.c     ; 1

    mov eax,T.a             ; 0
    mov eax,T.b             ; 16
    mov eax,T.c             ; 31

    ; bit-field to register

    mov ax,r.a              ; MOV
    mov eax,r.a             ; MOVZX
    mov eax,r.b             ; MOV/AND
    mov al,r.c              ; MOVZX/SHR
    mov eax,r.c             ; MOVZX/AND/SHR ?

    mov eax,r.q.d           ; MOVZX/AND
    mov eax,r.q.e           ; MOVZX/AND/SHR 1
    mov eax,r.q.f           ; MOVZX/AND/SHR 2

    mov eax,r.g             ; MOVZX
    mov eax,r.h             ; MOVZX

    ; imm to bit-field

    mov r.a,16              ; MOV
    mov r.b,15              ; AND/OR
    mov r.c,1               ; OR

    mov r.q.d,1             ; OR
    mov r.q.e,0             ; AND
    mov r.q.f,0x3F          ; AND/OR

    mov r.g,8               ; MOV
    mov r.h,8               ; MOV

    ; compare bit-field,imm

    cmp r.a,16              ; CMP
    cmp r.b,15              ; MOV/AND/CMP

    cmp r.c,1               ; MOV/AND/CMP
    je @F
    nop
@@:
    cmp r.c,0               ; TEST
    je @F
    nop
@@:
    mov r.c,0               ; OR

    cmp r.c,1               ; MOV/AND/CMP
    je @F
    nop
@@:
    cmp r.c,0               ; TEST
    je @F
    nop
@@:

    cmp r.q.d,1             ; MOV/AND/CMP
    cmp r.q.e,0             ; TEST
    cmp r.q.f,0x3F          ; MOVZX/AND/CMP

    cmp r.g,8               ; CMP
    cmp r.h,8               ; CMP

    .if r.a                 ; TEST/JZ
    .endif
    .if r.a < 16            ; CMP/JNC
    .endif
    .if r.b < 16            ; MOV/AND/CMP/JNC
    .endif
    .if !r.q.d              ; TEST/JNZ
    .endif

    ret

main endp

    end
