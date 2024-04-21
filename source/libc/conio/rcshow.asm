; RCSHOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

rcshow proc rc:TRECT, flag:uint_t, p:PCHAR_INFO

    ldr eax,flag
    and eax,W_ISOPEN or W_VISIBLE
    .ifnz
        .if !( eax & W_VISIBLE )
            .ifd _rcxchg(rc, p)
                .if ( flag & W_SHADE )
                    _rcshade(rc, p, 1)
                .endif
                mov eax,1
            .endif
        .endif
    .endif
    ret

rcshow endp

    end
