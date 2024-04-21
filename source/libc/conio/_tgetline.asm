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
    .switch eax
    .case WM_CREATE
    .case WM_CLOSE
        xor eax,eax
       .endc
    .default
ifdef _WIN64
        _defwinproc()
else
        _defwinproc(hwnd, uiMsg, wParam, lParam)
endif
       .endc
    .endsw
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
    mov     [rcx].type,T_EDIT
    or      [rcx].flags,W_WNDPROC or O_DEXIT or O_USEBEEP or O_MYBUF
    mov     [rbx].index,1
    mov     [rcx].index,1
    movzx   eax,[rbx].rc.col
    mul     [rcx].rc.y
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].window
    mov     [rcx].window,rax
    mov     rdi,rax
    movzx   eax,word ptr [rdi+2]
    shl     eax,16
    or      eax,U_MIDDLE_DOT
    movzx   ecx,[rcx].rc.col
    rep     stosd
    _at     BG_TITLE,FG_TITLE,' '
    movzx   ecx,[rbx].rc.col
    mov     edx,ecx
    mov     rdi,[rbx].window
    rep     stosd
    invoke  wcenter([rbx].window, edx, title)
    invoke  _dlshow(rbx)
    invoke  _tcontrol([rbx].object, buffer_size, 0, buffer)
    invoke  _dlmodal(rbx, &WndProc)
    xchg    rbx,rax
    invoke  _dlclose(rax)
    mov     eax,ebx
    ret

_tgetline endp

    end
