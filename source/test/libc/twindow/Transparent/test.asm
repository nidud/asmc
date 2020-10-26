
include twindow.inc

    .code

    assume rcx:window_t

cmain proc hwnd:window_t, argc:int_t, argv:array_t, environ:array_t

    [rcx].Clear(' ')
    [rcx].PutFrame(MTRECT(9, 9, 13, 3), 0, 0x1F)
    [rcx].PutString(10, 10, 0x1E1F, 0, " &Some &Text ")
    [rcx].Show()
    [rcx].MessageBox(MB_YESNOCANCEL or MB_USERICON, "TWindow::MessageBox",
            " MB_YESNOCANCEL or MB_USERICON \n"
            " USERICON == TRANSPARENT " )
    ret

cmain endp

    end
