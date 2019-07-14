
include twindow.inc

    .code

    assume rcx:window_t

cmain proc hwnd:window_t, argc:int_t, argv:array_t, environ:array_t

    mov rsi,r8
    ;[rcx].Clear(0x200000)
    [rcx].Show()
    [rcx].MessageBox(MB_OK, "TWindow::MessageBox", "MB_OK" )
    [rcx].MessageBox(MB_OK or MB_ICONWARNING, NULL, "MB_OK or MB_ICONWARNING, NULL" )
    [rcx].MessageBox(MB_OK or MB_ICONERROR, NULL, "MB_OK or MB_ICONERROR, NULL" )
    [rcx].MessageBox(MB_YESNOCANCEL or MB_USERICON, "TWindow::MessageBox",
            " MB_YESNOCANCEL or MB_USERICON \n"
            " USERICON == TRANSPARENT " )
    [rcx].MessageBox(MB_CANCELTRYCONTINUE or MB_DEFBUTTON3, "TWindow::MessageBox",
            "MB_CANCELTRYCONTINUE or MB_DEFBUTTON3" )

    xor eax,eax
    ret

cmain endp

    end
