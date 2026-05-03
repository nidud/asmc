;
; v2.30.28 -- sizeof(zword)
;
ifndef __ASMC64__
    .x64
    .model flat
endif
    .code

foo proc

  local z1:zword
  local z2:zword

    lea rax,z1
    lea rcx,z2
    ret

foo endp

    end
