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

    .if ( [rbx].flags & W_ISOPEN )

        inc retval

        .if ( [rbx].flags & W_VISIBLE )

            inc retval
            _rcwrite([rbx].rc, [rbx].window)
            .if ( [rbx].flags & W_SHADE )

                _rcshade([rbx].rc, [rbx].window, 0)
            .endif
        .endif

        and [rbx].flags,not (W_ISOPEN or W_VISIBLE)
        .if !( [rbx].flags & W_MYBUF )

            free([rbx].window)
            mov [rbx].window,NULL
        .endif

        .if ( [rbx].flags & W_RCNEW )

            free(rbx)
        .endif
    .endif
    mov edx,prevret
    mov eax,retval
    ret

dlclose endp

    end
