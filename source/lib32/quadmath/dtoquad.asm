;
; dtoquad() - double to Quadruple float
;
include quadmath.inc

    .code

dtoquad proc uses ebx p:ptr, d:ptr

    mov ecx,d
    mov eax,[ecx]
    mov edx,[ecx+4]
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
    mov ebx,p
    xchg eax,ebx
    shl ebx,1
    rcl edx,1
    mov [eax+6],ebx
    mov [eax+10],edx
    add ecx,ecx
    rcr cx,1
    mov [eax+14],cx
    xor ebx,ebx
    mov [eax],ebx
    mov [eax+4],bx
    ret

dtoquad endp

    end
