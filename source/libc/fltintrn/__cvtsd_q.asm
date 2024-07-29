; __CVTSD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

    .code

__cvtsd_q proc __ccall uses rbx q:ptr qfloat_t, d:ptr double_t

    ldr     rbx,q
    ldr     rdx,d

    mov     eax,[rdx]
    mov     edx,[rdx+4]
    mov     ecx,edx
    shld    edx,eax,11
    shl     eax,11
    sar     ecx,32-12
    and     cx,0x7FF

    .ifnz
        .if ( cx != 0x7FF )
            add cx,0x3FFF-0x03FF
        .else
            or ch,0x7F
            .if ( edx & 0x7FFFFFFF || eax )
                ;
                ; Invalid exception
                ;
                or edx,0x40000000
            .endif
        .endif
        or  edx,0x80000000
    .elseif ( edx || eax )
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

    add     ecx,ecx
    rcr     cx,1
    shl     eax,1
    rcl     edx,1

    xchg    rax,rbx
    mov     [rax+6],ebx
    mov     [rax+10],edx
    mov     [rax+14],cx
    xor     ebx,ebx
    mov     [rax],ebx
    mov     [rax+4],bx
    ret

__cvtsd_q endp

    end
