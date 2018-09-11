;
; dtoquad() - double to Quadruple float
;
include quadmath.inc

    .code

    option win64:rsp nosave noauto

dtoquad proc p:ptr, d:ptr
    mov r8,rcx
    mov rdx,[rdx]
    mov eax,edx
    shr rdx,32
    mov ecx,edx
    shld edx,eax,11
    shl eax,11
    sar ecx,32-12
    and cx,0x7FF
    .ifnz
        .if cx != 0x7FF
            add cx,0x3FFF-0x03FF
        .else
            or ch,0x7F
            .if edx & 0x7FFFFFFF || eax
                ;
                ; Invalid exception
                ;
                or edx,0x40000000
            .endif
        .endif
        or  edx,0x80000000
    .elseif edx || eax
        or ecx,0x3FFF-0x03FF+1
        .if !edx
            xchg edx,eax
            sub cx,32
        .endif
        .repeat
            test edx,edx
            .break .ifs
            shl eax,1
            rcl edx,1
        .untilcxz
    .endif
    shl eax,1
    rcl edx,1
    mov [r8+6],eax
    mov [r8+10],edx
    mov rax,r8
    add ecx,ecx
    rcr cx,1
    mov [rax+14],cx
    xor ecx,ecx
    mov [rax],ecx
    mov [rax+4],cx
    ret

dtoquad endp

    end
