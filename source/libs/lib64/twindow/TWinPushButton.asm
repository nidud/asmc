; TWINPUSHBUTTON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t
    assume rbx:window_t

TWindow::PushButton proc uses rsi rdi rbx rcx rc:TRect, id:uint_t, title:string_t

    mov     rsi,r9
    mov     rbx,[rcx].Child(edx, r8d, T_PUSHBUTTON)
    .return .if !rax

    mov     rdi,[rbx].Window()
    movzx   ecx,[rbx].rc.col
    mov     rdx,[rbx].Color
    movzx   eax,byte ptr [rdx+BG_PUSHBUTTON]
    or      al,[rdx+FG_TITLE]
    shl     eax,16
    mov     al,' '
    mov     r11,rdi
    rep     stosd
    mov     al,[rdi+2]
    and     eax,0xF0
    or      al,[rdx+FG_PBSHADE]
    shl     eax,16
    mov     al,'Ü'
    mov     [rdi],eax
    lea     rdi,[r11+r8*4+4]
    movzx   ecx,[rbx].rc.col
    mov     al,'ß'
    rep     stosd
    lea     rdi,[r11+8]
    mov     al,byte ptr [rdx+BG_PUSHBUTTON]
    mov     cl,al
    or      al,[rdx+FG_TITLE]
    or      cl,[rdx+FG_TITLEKEY]
    shl     eax,16

    .while 1

        lodsb
        .break .if !al

        .if al != '&'

            stosd
            .continue(0)

        .else

            lodsb
            .break .if !al

            mov [rdi],ax
            mov [rdi+2],cl
            add rdi,4
            and al,not 0x20
            mov byte ptr [rbx].SysKey,al
        .endif
    .endw

    mov eax,1
    ret

TWindow::PushButton endp

    end
