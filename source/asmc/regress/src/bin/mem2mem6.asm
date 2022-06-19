
    ; 2.34

    .686
    .xmm
    .model flat, c
    .code


foo proc

  local a:qword, b:qword

    and a,b
    or  a,b
    xor a,b
    ret

foo endp

    end
