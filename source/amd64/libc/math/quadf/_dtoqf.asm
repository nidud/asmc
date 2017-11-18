; _dtoqf() - double to Quadruple float
;
include intn.inc

.code
option win64:rsp nosave noauto

_dtoqf proc p:ptr, d:qword

    mov r8,rcx
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

    xchg rax,r8
    shl r8d,1
    rcl edx,1
    mov [rax+6],r8d
    mov [rax+10],edx
    add ecx,ecx
    rcr cx,1
    mov [rax+14],cx
    xor r8,r8
    mov [rax],r8
    ret

_dtoqf endp

    end
