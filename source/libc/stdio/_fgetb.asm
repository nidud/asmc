; _FGETB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:LPFILE

_fgetb proc uses rbx fp:LPFILE, count:int_t

    ldr rbx,fp

    .while 1

        mov ecx,count
        .if ( [rbx]._bitcnt >= ecx )

            mov eax,1           ; create mask
            shl eax,cl
            dec eax
            and eax,[rbx]._charbuf  ; bits to EAX
            sub [rbx]._bitcnt,ecx   ; dec bit count
            shr [rbx]._charbuf,cl   ; dump used bits
           .break
        .endif

        ; add a byte to bb

        .ifd ( fgetc(rbx) == -1 )

            .if ( [rbx]._bitcnt )
                mov count,[rbx]._bitcnt
            .else
                .break
            .endif
        .else
            mov ecx,[rbx]._bitcnt
            shl eax,cl
            or  [rbx]._charbuf,eax
            add [rbx]._bitcnt,8
        .endif
    .endw
    ret

_fgetb endp

    end
