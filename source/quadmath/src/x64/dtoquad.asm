;
; dtoquad() - double to Quadruple float
;
include quadmath.inc

    .code

    option win64:rsp nosave noauto

dtoquad proc p:ptr, d:ptr
ifdef _LINUX
    mov r8,p
    mov rdx,d
else
    mov r8,rcx
endif
    mov rdx,[rdx]
    mov eax,edx
    shr rdx,32
    mov ecx,edx
    shld edx,eax,11
    shl eax,11
    shr ecx,20
    and ecx,0x7FF
    .ifnz
        .if ecx != 0x7FF
            add ecx,0x3C00
        .else
            or ecx,0x7F00
            .if edx & 0x7FFFFFFF || eax
                ;
                ; Invalid exception
                ;
                or edx,0x40000000
            .endif
        .endif
        or  edx,0x80000000
    .elseif edx || eax
        or ecx,0x3C01
        .if !edx
            xchg edx,eax
            sub ecx,32
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
    mov [rax],rcx
    ret

dtoquad endp

    end
