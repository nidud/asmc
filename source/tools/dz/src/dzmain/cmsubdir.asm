; CMSUBDIR.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc

    .code

cmsubdir proc

    .if panel_curobj(cpanel)

        .if ecx & _A_SUBDIR

            panel_event(cpanel, KEY_ENTER)
        .endif
    .endif
    ret

cmsubdir endp

    END
