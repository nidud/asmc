; CMWIDEVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmawideview proc
    mov ecx,panela
    jmp cmwideview
cmawideview endp

cmbwideview proc
    mov ecx,panelb
    jmp cmwideview
cmbwideview endp

cmcwideview proc
    mov ecx,cpanel
cmcwideview endp

cmwideview:
    mov edx,[ecx].S_PANEL.pn_wsub
    mov eax,[edx].S_WSUB.ws_flag
    and eax,not _W_DETAIL
    xor eax,_W_WIDEVIEW
    mov [edx].S_WSUB.ws_flag,eax

    panel_redraw(ecx)
    ret

    END
