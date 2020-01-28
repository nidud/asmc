; TWINPUTFRAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

frame_type  struct 1
BottomRight db ?
BottomLeft  db ?
Vertical    db ?
TopRight    db ?
Horizontal  db ?
TopLeft     db ?
Cols        db ?
Rows        db ?
frame_type  ends

    .code

    assume rcx:window_t

TWindow::PutFrame proc uses rsi rdi rcx rc:TRect, type:int_t, Attrib:uchar_t

  local ft:frame_type

    .switch pascal r8
      .case 0 : mov rax,'ÚÄ¿³ÀÙ'
      .case 1 : mov rax,'ÉÍ»ºÈ¼'
      .case 2 : mov rax,'ÂÄÂ³ÁÁ'
      .case 3 : mov rax,'ÃÄ´³Ã´'
      .default
        .return 0
    .endsw

    mov     ft,rax
    movzx   eax,[rcx].rc.col
    mul     dh
    mov     edi,eax
    movzx   eax,dl
    add     edi,eax
    shl     edi,2
    add     rdi,[rcx].Window
    shr     edx,16
    sub     edx,0x0202
    mov     ft.Cols,dl
    mov     ft.Rows,dh
    movzx   eax,r9b
    movzx   edx,[rcx].rc.col
    shl     edx,2
    lea     r8,[rdi+rdx]
    shl     eax,16
    mov     al,ft.TopLeft
    movzx   r9d,ft.Cols

    .ifnz

        stosd
        mov     al,ft.Horizontal
        movzx   ecx,ft.Cols
        rep     stosd
        mov     al,ft.TopRight
        stosd
        mov     al,ft.Vertical

        .for ( ecx = 0 : cl < ft.Rows : ecx++ )

            mov     rdi,r8
            add     r8,rdx
            stosd
            mov     [rdi+r9*4],eax
        .endf

        mov     rdi,r8
        mov     al,ft.BottomLeft
        stosd
        mov     al,ft.Horizontal
        movzx   ecx,ft.Cols
        rep     stosd
        mov     al,ft.BottomRight
        stosd

    .else

        mov [rdi],al
        mov al,ft.Horizontal
        add rdi,4
        .for ( ecx = 0 : ecx < r9d : ecx++, rdi += 4 )
            mov [rdi],al
        .endf
        mov al,ft.TopRight
        mov [rdi],al
        mov al,ft.Vertical
        .for ( ecx = 0 : cl < ft.Rows : ecx++ )
            mov rdi,r8
            add r8,rdx
            mov [rdi],al
            mov [rdi+r9*4+4],al
        .endf
        mov rdi,r8
        mov al,ft.BottomLeft
        mov [rdi],al
        add rdi,4
        mov al,ft.Horizontal
        .for ( ecx = 0 : ecx < r9d : ecx++, rdi += 4 )
            mov [rdi],al
        .endf
        mov al,ft.BottomRight
        mov [rdi],al
    .endif
    ret

TWindow::PutFrame endp

    end
