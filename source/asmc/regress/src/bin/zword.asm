;
; v2.30.28 -- sizeof(zword)
;
    .x64
    .model flat
    .code

foo proc

  local z1:zword
  local z2:zword

    lea rax,z1
    lea rcx,z2
    ret

foo endp

    end
