; __CVTQ_SD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_sd() - Quad to double
;
include fltintrn.inc
include errno.inc

    .code

__cvtq_sd proc __ccall uses rsi rdi rbx d:ptr double_t, q:ptr qfloat_t

ifdef _WIN64
    mov     rax,rdx
else
    mov     eax,q
endif

    movzx   ecx,word ptr [rax+14]
    mov     edx,[rax+10]
    mov     ebx,ecx
    and     ebx,Q_EXPMASK
    mov     edi,ebx
    neg     ebx
    mov     eax,[rax+6]
    rcr     edx,1
    rcr     eax,1
    mov     esi,0xFFFFF800
    mov     ebx,eax
    shl     ebx,22
    .ifc
        .ifz
            shl ebx,1
        .endif
        add eax,0x0800
        adc edx,0
        .ifc
            mov edx,0x80000000
            inc cx
        .endif
    .endif
    and eax,esi
    mov ebx,ecx
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
        shl bx,1
        rcr edx,1
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
                adc eax,0
                adc edx,0
            .else
                xor eax,eax
                xor edx,edx
                shl ebx,17
                rcr edx,1
            .endif
        .else
            shrd eax,edx,11
            shl edx,1
            shr edx,11
            shl bx, 1
            rcr edx,1
            or  edx,0x7FF00000
        .endif
    .endif
    xor ebx,ebx
    .if edi < 0x3BCC
        mov rcx,q
        .if !(!edi && edi == [rcx+6] && edi == [rcx+10])
            xor eax,eax
            xor edx,edx
            mov ebx,ERANGE
        .endif
    .elseif edi >= 0x3BCD
        mov edi,edx
        and edi,0x7FF00000
        mov ebx,ERANGE
        .ifnz
            .if edi != 0x7FF00000
                xor ebx,ebx
            .endif
        .endif
    .elseif edi >= 0x3BCC
        mov edi,edx
        or  edi,eax
        mov ebx,ERANGE
        .ifnz
            mov edi,edx
            and edi,0x7FF00000
            .ifnz
                xor ebx,ebx
            .endif
        .endif
    .endif

    mov rdi,d
    mov [rdi],eax
    mov [rdi+4],edx
    .if ebx
        mov qerrno,ebx
    .endif

    .if ( rdi == q )

        xor eax,eax
        mov [rdi+8],eax
        mov [rdi+12],eax
    .endif
    .return( rdi )

__cvtq_sd endp

    end
