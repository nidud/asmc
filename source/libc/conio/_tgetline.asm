; _TGETLINE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

    .code

WndProc proc private hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr eax,uiMsg
    .if ( eax == WM_CREATE || eax == WM_CLOSE )

        .return( 0 )
    .endif
ifdef _WIN64
    _defwinproc()
else
    _defwinproc(hwnd, uiMsg, wParam, lParam)
endif
    ret

WndProc endp

    assume rbx:THWND
    assume rcx:THWND

_tgetline proc uses rdi rbx title:tstring_t, buffer:tstring_t, line_size:int_t, buffer_size:int_t

   .new     rc:TRECT
   .new     tc:TRECT

    mov     rc.y,5
    mov     rc.row,5
    mov     tc.x,4
    mov     tc.y,2
    mov     tc.row,1
    ldr     eax,line_size
    mov     tc.col,al
    add     al,8
    mov     rc.col,al
    shr     al,1
    mov     ah,40
    sub     ah,al
    mov     rc.x,ah

    mov     rbx,_dlopen(rc, 1, W_MOVEABLE or W_TRANSPARENT, TEDIT)
    mov     rcx,[rbx].object
    mov     [rcx].rc,tc
    or      [rcx].flags,O_WNDPROC or O_DEXIT or O_TEDIT or O_MYBUF or O_USEBEEP
    mov     [rbx].index,1
    mov     [rcx].oindex,1
    mov     [rcx].retval,1
    movzx   eax,[rbx].rc.col
    mul     [rcx].rc.y
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].window
    mov     [rcx].window,rax
    mov     rdi,rax
    mov     eax,0x000B0000 or U_MIDDLE_DOT
    movzx   ecx,[rcx].rc.col
    rep     stosd
    _at     BG_TITLE,FG_TITLE,' '
    movzx   ecx,[rbx].rc.col
    mov     edx,ecx
    mov     rdi,[rbx].window
    rep     stosd
    mov     ecx,edx
    invoke  wcenter([rbx].window, ecx, title)
    invoke  _tcontrol([rbx].object, buffer_size, buffer)
    invoke  _dlshow(rbx)
    invoke  _dlmodal(rbx, &WndProc)
    xchg    rbx,rax
    invoke  _dlclose(rax)
    mov     eax,ebx
    ret

_tgetline endp

    end
