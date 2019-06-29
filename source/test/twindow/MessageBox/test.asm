
include twindow.inc

    .code

    assume rcx:window_t

cmain proc hwnd:window_t, argc:int_t, argv:array_t, environ:array_t

    mov rsi,r8
    [rcx].Clear(0xB0)
    [rcx].PutTitle("MessageBox")
    [rcx].PutString(2, 2, 0, 0, " Module: %s ", [rsi])
    [rcx].Show()
    .repeat
        [rcx].MessageBox(MB_YESNOCANCEL, "Caption",
            "int TWindow::MessageBox(\n"
            "    UINT    uType,      \n"
            "    LPCTSTR lpCaption,  \n"
            "    LPCTSTR lpFormat,   \n"
            "    ...                 \n"
            ");                      \n"
            )
    .until [rcx].MessageBox(MB_ICONWARNING or MB_CANCELTRYCONTINUE or MB_DEFBUTTON2,
        "Account Details", "Resource not available\nDo you want to try again?" ) != IDTRYAGAIN
    ret

cmain endp

    end
