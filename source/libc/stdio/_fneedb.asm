; _FNEEDB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:LPFILE

_fneedb proc uses rbx fp:LPFILE, count:int_t

    ldr rbx,fp

    .ifd ( _fgetb(rbx, ldr(count)) != -1 )

        add [rbx]._bitcnt,ecx
        shl [rbx]._charbuf,cl
        or  [rbx]._charbuf,eax
    .endif
    ret

_fneedb endp

    end
