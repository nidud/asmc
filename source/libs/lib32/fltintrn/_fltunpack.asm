; _FLTUNPACK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltunpack proc uses esi edi ebx p:ptr STRFLT, q:ptr

    mov edi,p
    mov esi,q
    mov ax,[esi]
    shl eax,16
    mov dx,[esi+14]
    mov [edi+16],dx
    and dx,Q_EXPMASK
    neg dx
    mov edx,[esi+2]
    mov ebx,[esi+6]
    mov ecx,[esi+10]
    rcr ecx,1
    rcr ebx,1
    rcr edx,1
    rcr eax,1
    mov [edi],eax
    mov [edi+4],edx
    mov [edi+8],ebx
    mov [edi+12],ecx
    mov eax,edi
    ret

_fltunpack endp

    end
