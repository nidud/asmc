
include twindow.inc

    .code

    assume rcx:window_t

cmain proc hwnd:window_t, argc:int_t, argv:array_t, environ:array_t

    [rcx].Clear(0x0200B0)
    [rcx].Show()
if 0
    .while 1

        [rcx].MessageBox(
            MB_OK,
            "TWindow::MessageBox",
            "MB_OK" )

        [rcx].MessageBox(
            MB_OK or MB_ICONWARNING,  NULL,
            "MB_OK or MB_ICONWARNING, NULL" )

        [rcx].MessageBox(
            MB_OK or MB_ICONERROR,  NULL,
            "MB_OK or MB_ICONERROR, NULL" )

        [rcx].MessageBox(
            MB_YESNOCANCEL or MB_USERICON,
            "TWindow::MessageBox",
            " MB_YESNOCANCEL or MB_USERICON \n"
            " USERICON == TRANSPARENT " )

        .break .ifd [rcx].MessageBox(
            MB_CANCELTRYCONTINUE or MB_DEFBUTTON3,
            "TWindow::MessageBox",
            "MB_CANCELTRYCONTINUE or MB_DEFBUTTON3" ) != IDTRYAGAIN
    .endw
endif
    [rcx].MessageBox(
            MB_CANCELTRYCONTINUE or MB_DEFBUTTON3,
            "TWindow::MessageBox", "MB_CANCELTRYCONTINUE or MB_DEFBUTTON3" )

    xor eax,eax
    ret

cmain endp

    end
