; RCCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

.code

rcclose proc rc:TRECT, flag:uint_t, p:PCHAR_INFO

    ldr eax,flag
    .if eax & W_ISOPEN

        .if eax & W_VISIBLE

            rchide(rc, eax, p)
            mov eax,flag
        .endif

        .if !( eax & W_MYBUF )

            free(p)
        .endif
    .endif
    mov eax,flag
    and eax,W_ISOPEN
    ret

rcclose endp

    end
