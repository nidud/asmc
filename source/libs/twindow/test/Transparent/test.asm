
include twindow.inc

    .code

cmain proc this:ptr TWindow, argc:int_t, argv:array_t, environ:array_t

;    this.Clear(' ')
    this.PutFrame(MTRECT(9, 9, 13, 3), 0, 0x1F)
    this.PutString(10, 10, 0x1E1F, 0, " &Some &Text ")
    this.Show()

    this.MessageBox(
        MB_YESNOCANCEL or MB_USERICON,
        "TWindow::MessageBox",
        " MB_YESNOCANCEL or MB_USERICON \n"
        " USERICON == TRANSPARENT " )
    ret

cmain endp

    end
