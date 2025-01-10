; _UTFTOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert UTF8 to Wide char
;
; Return EAX Wide char, ECX byte count
;
include stdlib.inc

    .code

_utftow proc utf:string_t

    ldr rdx,utf

    movzx eax,byte ptr [rdx]
    .if ( eax > 0xBF && eax < 0xF8 )

        .if ( eax < 0xE0 )

            and     eax,0x1F ; C0 and C1
            shl     eax,6
            movzx   edx,byte ptr [rdx+1]
            and     edx,0x3F
            or      eax,edx
            mov     ecx,2

        .elseif ( eax < 0xF0 )

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

        .else

            and     eax,0x07 ; F5 to F7
            shl     eax,18
            movzx   ecx,byte ptr [rdx+1]
            and     ecx,0x3F
            shl     ecx,12
            or      eax,ecx
            movzx   ecx,byte ptr [rdx+2]
            and     ecx,0x3F
            shl     ecx,6
            or      eax,ecx
            movzx   ecx,byte ptr [rdx+3]
            and     ecx,0x3F
            or      eax,ecx
            mov     ecx,4
        .endif

    .else

        and eax,0x7F ; F8 to FF
        mov ecx,1
    .endif
    ret

_utftow endp

    end
