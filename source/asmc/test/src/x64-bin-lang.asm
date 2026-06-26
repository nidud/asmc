;
; v2.30: languages x64 - c pascal stdcall fastcall vectorcall syscall
;
.code

p1 proc c a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    add l1,a1
    add l2,a2
    add l3,a3
    add l4,a4
    ret
    endp

p2 proc pascal a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    mov l1,a1
    mov l2,a2
    mov l3,a3
    mov l4,a4
    p1( l1, l2, l3, l4 )
    ret
    endp

p3 proc stdcall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    mov l1,a1
    mov l2,a2
    mov l3,a3
    mov l4,a4
    p2( l1, l2, l3, l4 )
    ret
    endp

p4 proc fastcall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    mov l1,a1
    mov l2,a2
    mov l3,a3
    mov l4,a4
    p3( l1, l2, l3, l4 )
    ret
    endp

p5 proc vectorcall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    mov l1,a1
    mov l2,a2
    mov l3,a3
    mov l4,a4
    p4( l1, l2, l3, l4 )
    ret
    endp

p6 proc syscall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    mov l1,a1
    mov l2,a2
    mov l3,a3
    mov l4,a4
    p5( l1, l2, l3, l4 )
    ret
    endp

    end
