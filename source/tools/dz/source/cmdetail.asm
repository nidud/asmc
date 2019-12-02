; CMDETAIL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmadetail proc
    mov ecx,panela
    jmp cmdetail
cmadetail endp

cmbdetail proc
    mov ecx,panelb
    jmp cmdetail
cmbdetail endp

cmcdetail proc
    mov ecx,cpanel
cmcdetail endp

cmdetail:
    mov edx,[ecx].S_PANEL.pn_wsub
    mov eax,[edx].S_WSUB.ws_flag
    and eax,not _W_WIDEVIEW
    xor eax,_W_DETAIL
    mov [edx].S_WSUB.ws_flag,eax

    panel_redraw(ecx)
    ret

    END
