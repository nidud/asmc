
    ; 2.31.32
    ; TYPEOF(addr p)

    option casemap:none
    option win64:auto

    .code

main proc

  local a:byte

    mov eax,TYPEOF(a)       ; 1
    mov eax,TYPEOF(addr a)  ; 8
    ret
    endp

    end
