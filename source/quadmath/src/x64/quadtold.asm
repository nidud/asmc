include quadmath.inc

    .code

    option win64:rsp nosave noauto

quadtold proc ld:ptr, q:ptr

    mov r8w,[rdx+14]
    mov eax,r8d
    and eax,LD_EXPMASK
    neg eax
    mov rax,[rdx+6]
    rcr rax,1

    ;; round result

    .ifc
        .if rax == -1
            mov rax,0x8000000000000000
            inc r8w
        .else
            add rax,1
        .endif
    .endif
    mov [rcx],rax
    mov [rcx+8],r8w
    mov rax,rcx
    ret

quadtold endp

    end
