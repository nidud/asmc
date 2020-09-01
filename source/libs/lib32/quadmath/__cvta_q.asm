; __CVTA_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvta_q proc number:ptr, string:string_t, endptr:ptr string_t

    _strtoflt(string)

    mov ecx,endptr
    .if ecx

        mov edx,[eax].STRFLT.string
        mov [ecx],edx
    .endif

    mov edx,[eax].STRFLT.mantissa
    mov ecx,number
    mov dword ptr [ecx+0x00],[edx+0x00]
    mov dword ptr [ecx+0x04],[edx+0x04]
    mov dword ptr [ecx+0x08],[edx+0x08]
    mov dword ptr [ecx+0x0C],[edx+0x0C]
    mov eax,ecx
    ret

__cvta_q endp

    end
