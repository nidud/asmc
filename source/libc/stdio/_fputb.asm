; _FPUTB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:LPFILE

_fputb proc uses rbx fp:LPFILE, bits:uint_t, count:int_t

    ldr rbx,fp

    .while ( [rbx]._bk >= 8 )

        movzx ecx,byte ptr [rbx]._bb
        .ifd ( fputc(ecx, rbx) == -1 )
            .return
        .endif
        sub [rbx]._bk,8
        shr [rbx]._bb,8
    .endw

    mov ecx,[rbx]._bk
    mov edx,bits
    mov eax,count

    shl edx,cl
    or  [rbx]._bb,edx
    add [rbx]._bk,eax
    ret

_fputb endp

    end
