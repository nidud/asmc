
    ; 2.33.13 - mov p, &..

ifndef __ASMC64__
    .x64
    .model flat
endif

    .data

    p ptr ?
    b db ?
    d dd ?
    q dq ?

    .code

main proc

  local w:word

    mov p,&b
    mov p,&w
    mov p,&d
    mov p,&q
    mov p,&p
    mov d,&p
    ret

main endp

    end
