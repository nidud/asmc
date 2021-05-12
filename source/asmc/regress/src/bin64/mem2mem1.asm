
    ; 2.31.50 - mem2mem / quadmath

ifndef __ASMC64__
    .x64
    .model flat
endif

    s1 struct
    o oword ?
    s1 ends

    .data

    r1 = 1.4142135623730951454746218587388
    r2 = 0.0000000000000000966729331345291
    r real16 r1 - r2
    ;  = 1.4142131471660089242773689984252 - old
    ;  = 1.4142135623730950488016887242097 - new

    .code

main proc

  local t:s1

    mov t,[rcx] ; ok
    mov [rcx],t ; failed -- moved one byte
    ret

main endp

    end
