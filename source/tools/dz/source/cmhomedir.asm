; CMHOMEDIR.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmhomedir proc  ; Ctrl-Home

    .if panel_state(cpanel)

        mov edx,[eax].S_PANEL.pn_wsub
        mov eax,[edx].S_WSUB.ws_flag
        or  eax,_W_ROOTDIR
        and eax,not _W_ARCHIVE
        mov [edx].S_WSUB.ws_flag,eax
        mov eax,[edx].S_WSUB.ws_arch
        mov byte ptr [eax],0

        panel_read(cpanel)
        panel_putitem(cpanel, 0)
    .endif
    ret

cmhomedir endp

    END
