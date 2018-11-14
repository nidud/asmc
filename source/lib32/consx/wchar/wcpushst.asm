; WCPUSHST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .data
    wcvisible db 0

    .code

wcstline proc private

    mov ecx,_scrcol
    mov ch,1
    shl ecx,16
    mov ch,byte ptr _scrrow
    rcxchg(ecx, eax)
    ret

wcstline endp

wcpushst proc uses ebx wc:PVOID, cp:LPSTR

    .if wcvisible == 1
        mov eax,wc
        wcstline()
    .endif

    mov al,' '
    mov ah,at_background[B_Menus]
    or  ah,at_foreground[F_KeyBar]
    wcputw(wc, _scrcol, eax)
    mov ebx,wc
    mov byte ptr [ebx+36],179
    add ebx,2
    wcputs(ebx, _scrcol, _scrcol, cp)
    mov eax,wc
    wcstline()
    mov wcvisible,1
    ret

wcpushst endp

wcpopst proc wp:PVOID

    mov eax,wp
    wcstline()
    xor wcvisible,1
    ret

wcpopst endp

    END
