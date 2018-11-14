; RCXYROW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcxyrow proc uses edx rc, x, y

    mov al,byte ptr y
    mov ah,byte ptr x
    mov dl,rc.S_RECT.rc_x
    mov dh,rc.S_RECT.rc_y

    .repeat
        .if ah >= dl && al >= dh
            add dl,rc.S_RECT.rc_col
            .if ah < dl
                mov ah,dh
                add dh,rc.S_RECT.rc_row
                .if al < dh
                    sub al,ah
                    inc al
                    movzx eax,al
                    .break
                .endif
            .endif
        .endif
        xor eax,eax
    .until 1
    ret

rcxyrow endp

    END
