; CMMINI.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmamini proc
    panel_xormini(panela)
    ret
cmamini endp

cmbmini proc
    panel_xormini(panelb)
    ret
cmbmini endp

cmcmini proc
    panel_xormini(cpanel)
    ret
cmcmini endp

cmvolinfo proc
    panel_xorinfo(cpanel)
    ret
cmvolinfo endp

cmavolinfo proc
    panel_xorinfo(panela)
    ret
cmavolinfo endp

cmbvolinfo proc
    panel_xorinfo(panelb)
    ret
cmbvolinfo endp

    END
