; DLCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

    assume rbx:PDOBJ

dlclose proc uses rbx dobj:PDOBJ

   .new prevret:int_t = eax
   .new retval:int_t = 0

    ldr rbx,dobj

    .if ( [rbx].flag & W_ISOPEN )

        inc retval

        .if ( [rbx].flag & W_VISIBLE )

            inc retval
            _rcwrite([rbx].rc, [rbx].wp)
            .if ( [rbx].flag & W_SHADE )

                _rcshade([rbx].rc, [rbx].wp, 0)
            .endif
        .endif

        and [rbx].flag,not (W_ISOPEN or W_VISIBLE)
        .if !( [rbx].flag & W_MYBUF )

            free([rbx].wp)
            mov [rbx].wp,0
        .endif

        .if ( [rbx].flag & W_RCNEW )

            free(rbx)
        .endif
    .endif
    mov edx,prevret
    mov eax,retval
    ret

dlclose endp

    end
