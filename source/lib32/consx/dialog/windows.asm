; WINDOWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

MAXWINDOWS  equ 20

    .data
    windows  dd MAXWINDOWS dup(0)
    winflag  dw MAXWINDOWS dup(0)
    winlevel dd 0

    .code

__dlpush proc uses eax
    mov eax,winlevel
    .if eax < MAXWINDOWS
        inc winlevel
        mov windows[eax*4],edi
    .endif
    ret
__dlpush endp

__dlpop proc uses eax
    sub eax,eax
    .repeat
        .break .if eax == winlevel
        .if windows[eax*4] != edi
            inc eax
            .continue(0)
        .endif
        .repeat
            mov ecx,windows[eax*4+4]
            mov windows[eax*4],ecx
            inc eax
        .until eax == winlevel
        dec winlevel
    .until 1
    ret
__dlpop endp

dlhideall proc uses esi
    mov esi,winlevel
    .while  esi
        dec esi
        mov edx,windows[esi*4]
        mov ax,[edx].S_DOBJ.dl_flag
        mov winflag[esi*2],ax
        and [edx].S_DOBJ.dl_flag,not _D_ONSCR
        rchide([edx].S_DOBJ.dl_rect, eax, [edx].S_DOBJ.dl_wp)
    .endw
    ret
dlhideall endp

dlshowall proc uses esi ecx edx eax
    xor esi,esi
    .while  esi != winlevel
        mov dx,winflag[esi*2]
        .if dx & _D_ONSCR
            mov eax,windows[esi*4]
            mov [eax].S_DOBJ.dl_flag,dx
            xor dx,_D_ONSCR
            rcshow([eax].S_DOBJ.dl_rect, edx, [eax].S_DOBJ.dl_wp)
        .endif
        inc esi
    .endw
    ret
dlshowall endp

    END
