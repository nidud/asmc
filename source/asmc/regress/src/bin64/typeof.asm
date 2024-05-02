
    ; 2.31.32
    ; TYPEOF(addr p)

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option casemap:none
    option win64:auto

    .code

main proc

  local a:byte

    mov eax,TYPEOF(a)       ; 1
    mov eax,TYPEOF(addr a)  ; 8
    ret

main endp

    end
