; ASCII.ASM--
;
include consx.inc

extrn IDD_Ascii:dword

.data
    x dd 0
    y dd 0
    d dd 0
.code

event_handler proc
    .while 1
        .while !getkey()
            mov eax,edx
            shr eax,16
            and eax,3
            .ifnz
                mov eax,d
                movzx eax,[eax].S_DOBJ.dl_rect.rc_y
                .continue .if eax != keybmouse_y
                mov eax,MOUSECMD
                .break
            .endif
            mov eax,y
            .if eax == keybmouse_y
                mov eax,x
                .continue .if eax == keybmouse_x
            .endif
            mov eax,keybmouse_x
            mov x,eax
            mov eax,keybmouse_y
            mov y,eax
            mov eax,d
            mov eax,[eax].S_DOBJ.dl_rect
            add eax,0x00000307
            and eax,0x0000FFFF
            or  eax,0x10100000
            rcxyrow(eax, keybmouse_x, keybmouse_y)
            mov edx,d
            mov edx,[edx].S_DOBJ.dl_rect
            movzx ecx,dh
            movzx edx,dl
            add dl,15
            add cl,2
            .if !eax
                scputc( edx, ecx, 8, 196 )
            .else
                dec eax
                shl eax,4
                add eax,keybmouse_x
                sub eax,edx
                add eax,8
                scputf(edx, ecx, 0, 8, "[%02X %03d]", eax, eax)
            .endif
        .endw
        .break .if eax != KEY_SPACE
    .endw
    ret
event_handler endp

main proc
    SetConsoleMode(hStdInput, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
    .if rsopen(IDD_Ascii)
        mov d,eax
        mov [eax+16].S_TOBJ.to_proc,event_handler
        dlmodal(eax)
    .endif
    sub eax,eax
    ret
main endp

    end
