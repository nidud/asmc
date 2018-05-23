;
; quadtod() - Quad to double
;
include quadmath.inc

.code

option win64:rsp nosave noauto

quadtod proc d:ptr, q:ptr
ifdef _LINUX
    push rdi
    mov r10,rsi
else
    push rcx
    mov r10,rdx
endif
    movzx ecx,word ptr [r10+14]
    mov r8d,ecx
    and r8d,Q_EXPMASK
    mov r9d,r8d
    neg r8d
    mov eax,[r10+6]
    mov edx,[r10+10]
    rcr edx,1
    rcr eax,1
    mov r8d,eax
    shl r8d,22
    .ifc
        .ifz
            shl r8d,1
        .endif
        add eax,0x0800
        adc edx,0
        .ifc
            mov edx,0x80000000
            inc cx
        .endif
    .endif
    and eax,0xFFFFF800
    mov r8d,ecx
    and cx,0x7FFF
    add cx,0x03FF-0x3FFF
    .if cx < 0x07FF
        .if !cx
            shrd eax,edx,12
            shl  edx,1
            shr  edx,12
        .else
            shrd eax,edx,11
            shl  edx,1
            shrd edx,ecx,11
        .endif
        shl r8w,1
        rcr edx,1
    .else
        .if cx >= 0xC400
            .ifs cx >= -52
                mov r8d,0xFFFFF800
                sub cx,12
                neg cx
                .if cl >= 32
                    sub cl,32
                    mov r8d,eax
                    mov eax,edx
                    xor edx,edx
                .endif
                shrd r8d,eax,cl
                shrd eax,edx,cl
                shr edx,cl
                add r8d,r8d
                adc eax,0
                adc edx,0
            .else
                xor eax,eax
                xor edx,edx
                shl r8d,17
                rcr edx,1
            .endif
        .else
            shrd eax,edx,11
            shl edx,1
            shr edx,11
            shl r8w, 1
            rcr edx,1
            or  edx,0x7FF00000
        .endif
    .endif
    xor r8d,r8d
    .switch
    .case r9d < 0x3BCC
        .endc .if ( !r9d && r9d == [r10+6] && r9d == [r10+10] )
        xor eax,eax
        xor edx,edx
        mov r8d,ERANGE
        .endc
    .case r9d >= 0x3BCD
        mov r9d,edx
        and r9d,0x7FF00000
        mov r8d,ERANGE
        .endc .ifz
        .endc .if r9d == 0x7FF00000
        xor r8d,r8d
        .endc
    .case r9d >= 0x3BCC
        mov r9d,edx
        or  r9d,eax
        mov r8d,ERANGE
        .endc .ifz
        mov r9d,edx
        and r9d,0x7FF00000
        .endc .ifz
        xor r8d,r8d
    .endsw
    .if r8d
        mov qerrno,r8d
    .endif
    mov ecx,eax
    pop rax
    mov [rax],ecx
    mov [rax+4],edx
    ret

quadtod endp

    end
