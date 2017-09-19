; CMUPDIR.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmupdir proc
    .if panel_event(cpanel, KEY_HOME)

        panel_event(cpanel, KEY_ENTER)
    .endif
    ret
cmupdir endp

    END
