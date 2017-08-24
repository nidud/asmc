include intn.inc
include errno.inc

.code

option win64:rsp nosave noauto

_qftod proc d:ptr, q:ptr

    mov r8,rcx
    movzx ecx,word ptr [rdx+14]
    mov r9d,ecx
    and r9d,Q_EXPMASK
    neg r9d
    mov rax,[rdx+6]
    rcr rax,1
    mov r9d,eax
    shl r9d,22
    .ifc
        .ifz
            shl r9d,1
        .endif
        add rax,0x0800
        .ifc
            and rax,0xFFFFFFFF
            mov r9,0x8000000000000000
            or  rax,r9
            inc cx
        .endif
    .endif
    mov r9,0xFFFFFFFFFFFFF800
    and rax,r9
    mov ebx,ecx
    and cx,0x7FFF
    add cx,0x03FF-0x3FFF
    .if cx < 0x07FF
        .if !cx
            shr rax,12
        .else
            shr rax,11
        .endif
        shl cx,1
        rcr rax,1
    .else
        .if cx >= 0xC400
            .ifs cx >= -52
                sub cx,12
                neg cx
                .if cl >= 32
                    sub cl,32
                    mov esi,eax
                    mov eax,edx
                    xor edx,edx
                .endif
                shrd esi,eax,cl
                shrd eax,edx,cl
                shr edx,cl
                add esi,esi
                adc rax,0
            .else
                xor rax,rax
                shl ecx,17
                rcr rax,1
            .endif
        .else
            shl rax,1
            shr rax,11
            shl cx,1
            rcr rax,1
            or  rax,0x7FF00000
        .endif
    .endif
    xor r9d,r9d
    .if edi < 0x3BCC
        mov ecx,q
        .if !(!edi && edi == [ecx+6] && edi == [ecx+10])
            xor eax,eax
            xor edx,edx
            mov r9d,ERANGE
        .endif
    .elseif edi >= 0x3BCD
        mov edi,edx
        and edi,0x7FF00000
        mov r9d,ERANGE
        .ifnz
            .if edi != 0x7FF00000
                xor r9d,r9d
            .endif
        .endif
    .elseif edi >= 0x3BCC
        mov edi,edx
        or  edi,eax
        mov r9d,ERANGE
        .ifnz
            mov edi,edx
            and edi,0x7FF00000
            .ifnz
                xor r9d,r9d
            .endif
        .endif
    .endif
    .if r9d
        mov errno,r9d
    .endif
    mov [r8],rax
    ret

_qftod endp

    end
