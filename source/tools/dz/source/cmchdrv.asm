; CMCHDRV.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include errno.inc

    .data

cp_selectdrv    db 'Select disk Panel '
cp_selectdrv_X  db 'A',0

    .code

cmachdrv proc
    mov eax,panela
    mov cp_selectdrv_X,'A'
    jmp cmchdrv
cmachdrv endp

cmbchdrv proc
    mov eax,panelb
    mov cp_selectdrv_X,'B'
cmbchdrv endp

cmchdrv proc private uses esi

    mov esi,eax
    .if panel_state(eax)

        mov errno,0
        .if _disk_select(addr cp_selectdrv)

            push eax
            panel_sethdd(esi, eax)
            msloop()
            pop eax
        .endif
    .endif
    ret
cmchdrv endp

    END
