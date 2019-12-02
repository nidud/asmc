; UPDATEMOUSEEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

DOUBLE_CLICK    equ 2
MOUSE_WHEELED   equ 4
MOUSE_HWHEELED  equ 8

    .code

    assume ebx:ptr INPUT_RECORD

UpdateMouseEvent proc uses ebx pInput:ptr INPUT_RECORD

    mov ebx,pInput
    movzx eax,[ebx].MouseEvent.dwMousePosition.x
    mov keybmouse_x,eax
    mov ax,[ebx].MouseEvent.dwMousePosition.y
    mov keybmouse_y,eax
    mov eax,keyshift
    mov edx,[eax]
    and edx,not SHIFT_MOUSEFLAGS
    mov eax,[ebx].MouseEvent.dwButtonState
    mov ecx,eax
    and eax,3h
    shl eax,16
    or  eax,edx
    mov edx,[ebx].MouseEvent.dwEventFlags
    mov ebx,eax
    .if edx == MOUSE_WHEELED
        mov eax,KEY_MOUSEUP
        .ifs ecx <= 0
            mov eax,KEY_MOUSEDN
        .endif
        PushEvent(eax)
    .endif
    mov edx,keyshift
    mov [edx],ebx
    ret

UpdateMouseEvent endp

    END
