; _UTFTOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert UTF8 to Wide char
;
; Return EAX UTF16, ECX byte count
;
include stdlib.inc

    .code

_utftow proc utf:string_t

    ldr     rdx,utf

    lea     rcx,_lookuptrailbytes
    movzx   eax,byte ptr [rdx]
    movzx   ecx,byte ptr [rcx+rax]
    inc     ecx

    .if ( ecx == 1 )

        and     eax,0x7F

    .elseif ( ecx == 2 )

        and     eax,0x1F
        shl     eax,6
        movzx   edx,byte ptr [rdx+1]
        and     edx,0x3F
        or      eax,edx

    .elseif ( ecx == 3 )

        and     eax,0x0F
        shl     eax,12
        movzx   ecx,byte ptr [rdx+1]
        and     ecx,0x3F
        shl     ecx,6
        or      eax,ecx
        movzx   edx,byte ptr [rdx+2]
        and     edx,0x3F
        or      eax,edx
        mov     ecx,3
    .endif
    ret

_utftow endp

    end
