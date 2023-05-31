; _TCONTROL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; A text control is added externally (Unicode/ASCII) and buffering
; added to the main window (128*TCHAR+TEDIT)
;
; Flags:
;
; O_DEXIT   - dialog exits on Enter
; O_USEBEEP - if no-can-do: try to delete a char at the end
; O_SELECT  - text is auto selected on entry
;
include conio.inc
include tchar.inc

    .code

    assume rbx:THWND

WndProc proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov rbx,hwnd
    .switch uiMsg
    .case WM_CREATE
        _dlshow(rbx)
        _tcontrol([rbx].object, 128, ' ', "string to edit......")
        .return( 0 )
    .case WM_CLOSE
        _dlclose(rbx)
        .return( 0 )
    .default
        mov rbx,[rbx].object
        .if ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
            .return
        .endif
    .endsw
    .return(_defwinproc(hwnd, uiMsg, wParam, lParam))

WndProc endp

    assume rcx:THWND

_tmain proc argc:int_t, argv:array_t

   .new rc:TRECT = { 10, 8, 50, 8 }
   .new f1:TRECT = { 16, 0, 18, 3 }
   .new f2:TRECT = { 14, 4, 22, 3 }
   .new ec:TRECT = { 15, 5, 20, 1 }

    mov rbx,_dlopen(rc, 1, W_MOVEABLE or W_TRANSPARENT or W_SHADE, 128*TCHAR+TEDIT)
    _rcframe(rc, f1, [rbx].window, BOX_SINGLE_ARC, 0x0F)
    _rcframe(rc, f2, [rbx].window, BOX_SINGLE_ARC, 0x06)
    _rcputs(rc, [rbx].window, 17, 1, 0x0F, "  Text Control  ")

    mov     rcx,[rbx].object
    mov     [rcx].rc,ec
    mov     [rcx].type,T_EDIT
    or      [rcx].flags,W_WNDPROC or O_DEXIT or O_USEBEEP or O_SELECT
    movzx   eax,[rbx].rc.col
    mul     [rcx].rc.y
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].window
    mov     [rcx].window,rax

    _dlinit(rcx, 0)
    _dlmodal(rbx, &WndProc)
    ret

_tmain endp

    end
