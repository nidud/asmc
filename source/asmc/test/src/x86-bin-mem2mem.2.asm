
    ; 2.33.67 - mem2mem / type ptr

    .486
    .model flat, c

    s1 struct
    q  dq ?
    s1 ends

    .code

main proc

  local t:s1

    add t.q,t.q
    ret

main endp

    end
