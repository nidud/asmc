
    ; v2.34.01 name conflict with register param and stuct members

    .486
    .model flat, c

     s1 struc
     a  dd ?
     b  dd ?
     s1 ends

    .code

foo proc watcall a:dword, b:dword

  local s:s1

    mov s.a,a
    mov s.b,b
    ret

foo endp

bar proc fastcall a:dword, b:dword

  local s:s1

    mov s.a,a
    mov s.b,b
    ret

bar endp

end
