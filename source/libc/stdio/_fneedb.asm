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
    ldr ecx,count

    .while 1

        .if ( ecx <= [rbx]._bitcnt )

            mov eax,1           ; create mask
            shl eax,cl
            dec eax
            and eax,[rbx]._charbuf  ; bits to EAX
           .break
        .endif

        ; add a byte to bb

        .ifd ( fgetc(rbx) == -1 )

            .break
        .endif
        mov ecx,[rbx]._bitcnt
        shl eax,cl
        or  [rbx]._charbuf,eax
        add [rbx]._bitcnt,8
        mov ecx,count
    .endw
    ret

_fneedb endp

    end
