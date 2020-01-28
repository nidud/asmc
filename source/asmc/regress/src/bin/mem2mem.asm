; MEM2MEM.ASM--
;
; v2.30.01 memory,memory operands
;

.x64
.model flat, fastcall
.code

s struct
b db ?
w dw ?
d dd ?
q dq ?
s ends

s3 struct
b db 3 dup(?)
s3 ends

s16 struct
b db 16 dup(?)
s16 ends

s32 struct
b db 32 dup(?)
s32 ends

s64 struct
b db 64 dup(?)
s64 ends

foo proc p:ptr
  local q:ptr
  local b:byte
  local w:word
  local d:dword
  local c:s
  local z3:s3
  local z16:s16
  local z32:s32
  local z64:s64

    cmp b,c.b
    test [rdi+rdx],[rsi+rax*2]

    add word ptr [rdx],[rax]
    add [rdx],[rax]

    add b,c.b
    sub b,c.b
    and b,c.b
    or  b,c.b
    xor b,c.b
    mov b,c.b

    add w,c.w
    sub w,c.w
    and w,c.w
    or  w,c.w
    xor w,c.w
    mov w,c.w

    add d,c.d
    sub d,c.d
    and d,c.d
    or  d,c.d
    xor d,c.d
    mov d,c.d

    add q,p
    sub q,p
    and q,p
    or  q,p
    xor q,p
    mov q,p

    add [rdx].s.b,c.b
    sub [rdx].s.b,c.b
    and [rdx].s.b,c.b
    or  [rdx].s.b,c.b
    xor [rdx].s.b,c.b
    mov [rdx].s.b,c.b

    ; v2.31.12 -- added extension

    mov c,c
    mov z3,z3
    mov z16,z16
    mov z32,z32 ; max
    mov z64,z64 ; movsb
    mov z64,z32 ; mov 32
    mov z64,z16 ; mov 16
    mov z64,z3  ; mov 3

    ret

foo endp

    end
