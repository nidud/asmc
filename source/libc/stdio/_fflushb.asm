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

    .while ( [rbx]._bk >= 8 )

        movzx ecx,byte ptr [rbx]._bb
        .ifd ( fputc(ecx, rbx) == -1 )
            .return
        .endif
        sub [rbx]._bk,8
        shr [rbx]._bb,8
    .endw

    .if ( [rbx]._bk )

        mov eax,1
        mov ecx,[rbx]._bk
        shl eax,cl
        dec eax
        and eax,[rbx]._bb
        fputc(eax, rbx)
    .endif
    mov [rbx]._bb,0
    mov [rbx]._bk,0
    ret

_fflushb endp

    end
