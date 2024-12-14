; _FFLUSHB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:LPFILE

_fflushb proc uses rbx fp:LPFILE

    ldr rbx,fp

    .while ( [rbx]._bitcnt >= 8 )

        movzx ecx,byte ptr [rbx]._charbuf
        .ifd ( fputc(ecx, rbx) == -1 )
            .return
        .endif
        sub [rbx]._bitcnt,8
        shr [rbx]._charbuf,8
    .endw

    .if ( [rbx]._bitcnt )

        mov eax,1
        mov ecx,[rbx]._bitcnt
        shl eax,cl
        dec eax
        and eax,[rbx]._charbuf
        fputc(eax, rbx)
    .endif
    mov [rbx]._charbuf,0
    mov [rbx]._bitcnt,0
    ret

_fflushb endp

    end
