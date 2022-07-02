; __CVTLD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

    .code

__cvtld_q proc __ccall x:ptr qfloat_t, ld:ptr ldouble_t

ifdef _WIN64

    mov     rax,[rdx]
    movzx   edx,word ptr [rdx+8]
    add     dx,dx
    rcr     dx,1
    shl     rax,1
    shld    rdx,rax,64-16
    shl     rax,64-16
    mov     [rcx],rax
    mov     [rcx+8],rdx
    mov     rax,rcx

else

    mov     eax,x
    mov     ecx,ld
    mov     dx,[ecx+8]
    mov     [eax+14],dx
    mov     edx,[ecx+4]
    mov     ecx,[ecx]
    shl     ecx,1
    rcl     edx,1
    mov     [eax+6],ecx
    mov     [eax+10],edx
    xor     ecx,ecx
    mov     [eax],ecx
    mov     [eax+4],cx

endif
    ret

__cvtld_q endp

    end
