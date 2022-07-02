; _FLTUNPACK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltunpack proc __ccall p:ptr STRFLT, q:ptr
ifdef _WIN64
    mov     rax,[rdx]
    mov     r8,[rdx+8]
    shld    r9,r8,16
    shld    r8,rax,16
    shl     rax,16
    mov     [rcx].STRFLT.mantissa.e,r9w
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     r8,1
    rcr     rax,1
    mov     [rcx].STRFLT.mantissa.l,rax
    mov     [rcx].STRFLT.mantissa.h,r8
    mov     rax,rcx
else
    push    esi
    push    edi
    mov     edi,p
    mov     esi,q
    mov     ax,[esi]
    shl     eax,16
    mov     dx,[esi+14]
    mov     [edi].STRFLT.mantissa.e,dx
    and     dx,Q_EXPMASK
    neg     dx
    mov     edx,[esi+2]
    mov     ecx,[esi+6]
    mov     esi,[esi+10]
    rcr     esi,1
    rcr     ecx,1
    rcr     edx,1
    rcr     eax,1
    mov     dword ptr [edi].STRFLT.mantissa.l[0],eax
    mov     dword ptr [edi].STRFLT.mantissa.l[4],edx
    mov     dword ptr [edi].STRFLT.mantissa.h[0],ecx
    mov     dword ptr [edi].STRFLT.mantissa.h[4],esi
    mov     eax,edi
    pop     edi
    pop     esi
endif
    ret

_fltunpack endp

    end
