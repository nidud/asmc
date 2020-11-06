;
; http://undoc.airesoft.co.uk/kernel32.dll/ConsoleMenuControl.php
;
include twindow.inc

MENU_ID = 500

; Return handle to the console's window menu

ConsoleMenuControl proto hConOut    : HANDLE, ; Handle to a console screen buffer
                         cmdIdLow   : dword,  ; The lowest menu id to report
                         cmdIdHigh  : dword   ; The highest menu id to report

    .data
    hMenu HMENU 0

    .code

    assume rcx:ptr TWindow

WndProc proc hwnd:ptr TWindow, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch edx

    .case WM_CREATE
        [rcx].Clear(0x000000B0)
        [rcx].PutString(2, 4, 0, 0,
            " A menu item is added to the Console window \n"
            " ConsoleMenuControl() \n"
            "\n"
            " Reading events... \n"
            " Select the menu item to close "
        )
        [rcx].Show()
        .return 0

    .case MENU_ID
        DeleteMenu(hMenu, MENU_ID, 0)
        hwnd.MessageBox(MB_OK, "ConsoleMenuControl", "The menu item is Removed")
        .return 0

    .endsw
    [rcx].DefWindowProc(edx, r8, r9)
    ret

WndProc endp

cmain proc hwnd:ptr TWindow, argc:int_t, argv:array_t, environ:array_t

    ; Get handle to the Console window menu

    mov rax,[rcx].Class
    mov hMenu,ConsoleMenuControl([rax].TClass.StdOut, MENU_ID, MENU_ID)

    ; Append a Menu item to it

    AppendMenu(rax, MF_STRING, MENU_ID, "ConsoleMenuControl()")

    ; Main message loop

    hwnd.Register(&WndProc)
    ret

cmain endp

    end
