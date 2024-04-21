; _RCINSIDE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_rcinside proc rc:TRECT, r2:TRECT

    ldr ecx,rc
    ldr edx,r2

    xor eax,eax

    .if ( ch > dh || cl > dl )

        mov eax,5
    .else

        mov eax,ecx
        ror ecx,16
        add cx,ax
        mov eax,edx
        ror edx,16
        add dx,ax
        xor eax,eax

        .if ( ch < dh )

            inc eax
        .elseif ( cl < dl )

            mov eax,4
        .else

            shr ecx,16
            shr edx,16

            .if ( ch > dh )

                mov eax,2
            .elseif ( cl > dl )

                mov eax,3
            .endif
        .endif
    .endif
    ret

_rcinside endp

    end
