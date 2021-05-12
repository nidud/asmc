
    ; 2.31.32
    ; typeof(addr p)

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option casemap:none
    option win64:auto

    .code

main proc

  local a:byte

    mov eax,typeof(a)       ; 1
    mov eax,typeof(addr a)  ; 8
    ret

main endp

    end
