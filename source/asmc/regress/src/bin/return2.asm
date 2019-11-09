;
; v2.30 .return directive
;
    .x64
    .model flat, fastcall
    .code

main proc

  local b:byte
  local w:word
  local s:sword
  local o:oword
  local h:real2
  local f:real4
  local d:real8
  local q:real16

    .return b ; eax - movzx
    .return w ; eax - movzx
    .return s ; eax - movsx
    .return o ; rdx:rax
    .return h ; ax
    .return f ; xmm0 - movss
    .return d ; xmm0 - movsd
    .return q ; xmm0 - movaps

    ; v2.30.24 - return address

    .return(&b) ; rax - lea
    .return &b
    nop
    ret

main endp

    end
