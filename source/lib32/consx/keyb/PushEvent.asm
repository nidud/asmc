; PUSHEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

PushEvent proc Event:dword

    mov eax,Event
    mov ecx,keybcount
    .if ecx < MAXKEYSTACK-1

        inc keybcount
        mov keybstack[ecx*4],eax
    .endif
    ret

PushEvent endp

PopEvent proc

    mov eax,keyshift
    mov edx,[eax]

    xor eax,eax
    .if eax != keybcount

        dec keybcount
        mov eax,keybcount
        mov eax,keybstack[eax*4]
        test eax,eax
    .endif
    ret

PopEvent endp

    END
