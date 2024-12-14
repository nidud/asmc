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

    .while ( [rbx]._bitcnt >= 8 )

        movzx ecx,byte ptr [rbx]._charbuf
        .ifd ( fputc(ecx, rbx) == -1 )
            .return
        .endif
        sub [rbx]._bitcnt,8
        shr [rbx]._charbuf,8
    .endw

    mov ecx,[rbx]._bitcnt
    mov edx,bits
    mov eax,count

    shl edx,cl
    or  [rbx]._charbuf,edx
    add [rbx]._bitcnt,eax
    ret

_fputb endp

    end
