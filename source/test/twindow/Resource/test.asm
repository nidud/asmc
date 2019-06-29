
include twindow.inc

extern IDD_EditColor:idd_t

    .code

    assume rcx:window_t

EditProc proc hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch edx
      .case WM_LBUTTONDOWN
        .return [rcx].OnLButtonDown(edx, r8, r9)
      .case WM_LBUTTONUP
        .return [rcx].OnLButtonUp(edx, r8, r9)
      .case WM_MOUSEMOVE
        .return [rcx].OnMouseMove(edx, r8, r9)
      .case WM_SYSCHAR
        .return [rcx].OnSysChar(edx, r8, r9)
      .case WM_CHAR
        .return [rcx].OnChar(edx, r8, r9)
      .case WM_CREATE
        [rcx].Show()
        [rcx].SetFocus(1)
        .return 0
      .case WM_CLOSE
        [rcx].KillFocus()
        .return [rcx].Release()
    .endsw
    mov eax,1
    ret

EditProc endp

WndProc proc hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch edx
      .case WM_CREATE
        [rcx].Clear(0x000000B0)
        [rcx].Show()
        mov rcx,[rcx].Resource(IDD_EditColor)
        [rcx].Register(&EditProc)
        .return 0
      .case WM_ENTERIDLE
        Sleep(4)
        .return 0
      .case WM_SYSCHAR
        .return [rcx].OnSysChar(edx, r8, r9)
      .case WM_CHAR
        .return [rcx].OnChar(edx, r8, r9)
    .endsw
    mov eax,1
    ret

WndProc endp

cmain proc hwnd:window_t, argc:int_t, argv:array_t, environ:array_t

    [rcx].Register(&WndProc)
    ret

cmain endp

    end
