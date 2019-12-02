; CONSUSER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

.code

consuser proc

  local cursor:S_CURSOR

    CursorGet(&cursor)
    CursorSet(&console_cu)
    dlshow(&console_dl)

    .while !getkey()
    .endw

    dlhide(&console_dl)
    CursorSet(&cursor)

    xor eax,eax
    ret

consuser endp

    END
