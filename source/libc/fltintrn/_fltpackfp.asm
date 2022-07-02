; _FLTPACKFP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

ifdef _WIN64

_fltpackfp proc __ccall dst:ptr, src:ptr STRFLT

    _fltround( rdx )

    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
    mov     cx, [rcx].STRFLT.mantissa.e
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    mov     rcx,dst
    mov     [rcx],rax
    mov     [rcx+8],rdx
    mov     rax,rcx

else

_fltpackfp proc __ccall uses esi edi ebx q:ptr, p:ptr STRFLT

    mov esi,p
    mov edi,q

    _fltround( esi )

    mov eax,[esi]
    mov edx,[esi+4]
    mov ebx,[esi+8]
    mov ecx,[esi+12]
    shl eax,1
    rcl edx,1
    rcl ebx,1
    rcl ecx,1
    shr eax,16
    mov [edi],ax
    mov [edi+2],edx
    mov [edi+6],ebx
    mov [edi+10],ecx
    mov ax,[esi+16]
    mov [edi+14],ax
    mov eax,edi
endif
    ret

_fltpackfp endp

    end
