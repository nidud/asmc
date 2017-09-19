; CMLONG.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmalong proc
    mov ecx,panela
    jmp cmlong
cmalong endp

cmblong proc
    mov ecx,panelb
    jmp cmlong
cmblong endp

cmclong proc
    mov ecx,cpanel
cmclong endp

cmlong:
    mov edx,[ecx].S_PANEL.pn_wsub
    xor [edx].S_WSUB.ws_flag,_W_LONGNAME
    panel_update(ecx)
    ret

    END
