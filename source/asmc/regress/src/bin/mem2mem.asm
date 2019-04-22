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

foo proc p:ptr
  local q:ptr
  local b:byte
  local w:word
  local d:dword
  local c:s

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
    ret

foo endp

    end
