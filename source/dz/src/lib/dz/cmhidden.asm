; CMHIDDEN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmahidden proc
    xor config.c_apath.ws_flag,_W_HIDDEN
    panel_update(panela)
    ret
cmahidden endp

cmchidden proc
    mov eax,panela
    cmp eax,cpanel
    je  cmahidden
cmchidden endp

cmbhidden proc
    xor config.c_bpath.ws_flag,_W_HIDDEN
    panel_update(panelb)
    ret
cmbhidden endp

    END
