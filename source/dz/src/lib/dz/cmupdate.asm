; CMUPDATE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmaupdate proc
    panel_reread(panela)
    ret
cmaupdate endp

cmbupdate proc
    panel_reread(panelb)
    ret
cmbupdate endp

cmcupdate proc
    panel_reread(cpanel)
    ret
cmcupdate endp

    END
