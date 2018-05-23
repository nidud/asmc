;
; quadtoi64() - Quadruple float to long long
;
include quadmath.inc
include limits.inc

.code

option win64:rsp nosave noauto

quadtoi64 proc q:ptr
ifdef _LINUX
    mov rcx,rdi
endif
    mov dx,[rcx+14]
    mov eax,edx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor rax,rax
        .if edx & 0x8000
            dec rax
        .endif
    .elseif eax > 62 + Q_EXPBIAS
        mov qerrno,ERANGE
        mov rax,_I64_MAX
        .if edx & 0x8000
            mov rax,_I64_MIN
        .endif
    .else
        mov edx,eax
        sub edx,Q_EXPBIAS
        mov r8,[rcx+6]
        mov rax,1
        .while edx
            shl r8,1
            rcl rax,1
            dec edx
        .endw
        .if byte ptr [rcx+15] & 0x80
            neg rax
        .endif
    .endif
    ret

quadtoi64 endp

    END
