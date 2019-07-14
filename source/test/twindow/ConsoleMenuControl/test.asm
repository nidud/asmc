;
; http://undoc.airesoft.co.uk/kernel32.dll/ConsoleMenuControl.php
;
include twindow.inc

MENU_ID = 500

ConsoleMenuControl proto :HANDLE, :int_t, :int_t

    .data
    hMenu HMENU 0

    .code

    assume rcx:window_t

WndProc proc hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch edx
      .case WM_CREATE
        [rcx].Clear(0x000000B0)
        [rcx].PutString(2, 4, 0, 0, " A menu item is added to the Console window ")
        [rcx].Show()
        .return 0
      .case MENU_ID
        DeleteMenu(hMenu, MENU_ID, 0)
        hwnd.MessageBox(MB_OK, "ConsoleMenuControl", "The menu item is Removed")
        .return 0
    .endsw
    DefTWindowProc(rcx, edx, r8, r9)
    ret

WndProc endp

cmain proc hwnd:window_t, argc:int_t, argv:array_t, environ:array_t

    mov rax,[rcx].Class
    mov hMenu,ConsoleMenuControl([rax].APPINFO.StdOut, MENU_ID, MENU_ID)
    AppendMenu(rax, MF_STRING, MENU_ID, "ConsoleMenuControl()")
    hwnd.Register(&WndProc)
    ret

cmain endp

    end
