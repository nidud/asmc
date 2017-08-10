include intn.inc

.code

_dtoqf proc uses ebx p:ptr, d:qword

    mov eax,dword ptr d
    mov edx,dword ptr d[4]
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
    mov [eax+2],ebx
    mov [eax],bx
    ret

_dtoqf endp

    end
