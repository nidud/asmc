; _FLTPACKFP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltpackfp proc uses esi edi ebx q:ptr, p:ptr STRFLT

    mov esi,p
    mov edi,q

    _fltround(esi)

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
    ret

_fltpackfp endp

    end
