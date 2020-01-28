; TWINSHOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t

TWindow::SetShade proc uses rdi

  local rc[2]:TRect

    .return .if !( [rcx].Flags & W_SHADE )

    mov     rc,[rcx].rc
    mov     rc[4],eax
    shr     eax,16
    mov     rc[4].col,2
    dec     rc[4].row
    inc     rc[4].y
    add     rc[4].x,al
    add     rc.y,ah
    mov     rc.row,1
    add     rc.x,2
    movzx   eax,[rcx].rc.col
    mul     [rcx].rc.row
    lea     rdi,[rax*4]
    add     rdi,[rcx].Window
    [rcx].Read(&rc, rdi)
    movzx   eax,rc.col
    [rcx].Read(&rc[4], &[rdi+rax*4])
    movzx   edx,rc.col
    add     dl,rc[4].row
    add     dl,rc[4].row
    .for rax = rdi : edx : edx--, rax += 4
        mov byte ptr [rax+2],0x08
    .endf
    [rcx].Exchange(&rc, rdi)
    movzx   eax,rc.col
    [rcx].Exchange(&rc[4], &[rdi+rax*4])
    ret

TWindow::SetShade endp


TWindow::ClrShade proc uses rsi

  local rc[2]:TRect

    .return .if !( [rcx].Flags & W_SHADE )

    mov     rc,[rcx].rc
    mov     rc[4],eax
    shr     eax,16
    mov     rc[4].col,2
    dec     rc[4].row
    inc     rc[4].y
    add     rc[4].x,al
    add     rc.y,ah
    mov     rc.row,1
    add     rc.x,2
    movzx   eax,[rcx].rc.col
    mul     [rcx].rc.row
    lea     rsi,[rax*4]
    add     rsi,[rcx].Window
    [rcx].Exchange(&rc[0], rsi)
    movzx   eax,rc.col
    [rcx].Exchange(&rc[4], &[rsi+rax*4])
    ret

TWindow::ClrShade endp

TWindow::Show proc

    mov eax,[rcx].Flags
    and eax,W_ISOPEN or W_VISIBLE
    .return .ifz

    .if !( eax & W_VISIBLE )

        [rcx].Exchange(&[rcx].rc, [rcx].Window)

        .if [rcx].Flags & W_SHADE

            [rcx].SetShade()
        .endif
        or [rcx].Flags,W_VISIBLE
    .endif
    mov eax,1
    ret

TWindow::Show endp

TWindow::Hide proc

    xor eax,eax
    mov edx,[rcx].Flags
    .return .if !( edx & W_ISOPEN )

    .if edx & W_VISIBLE

        [rcx].Exchange(&[rcx].rc, [rcx].Window)

        .if [rcx].Flags & W_SHADE

            [rcx].ClrShade()
        .endif
        and [rcx].Flags,not W_VISIBLE
    .endif
    mov eax,1
    ret

TWindow::Hide endp

    end
