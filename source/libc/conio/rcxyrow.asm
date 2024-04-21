; RCXYROW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

rcxyrow proc rc:TRECT, x:int_t, y:int_t

    ldr ecx,rc
    ldr eax,y
    ldr edx,x

    .if ( dl >= cl && al >= ch )

        mov ah,dl
        mov edx,ecx
        shr edx,16

        add cl,dl
        .if ( ah < cl )

            mov ah,ch
            add ch,dh

            .if ( al < ch )

                sub al,ah
                inc al
                movzx eax,al
               .return
            .endif
        .endif
    .endif
    xor eax,eax
    ret

rcxyrow endp

    end
