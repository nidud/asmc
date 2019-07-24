include twindow.inc

    .code

    assume rcx:window_t

cmain proc hwnd:window_t

 local x, y

    movzx eax,[rcx].rc.col
    mov x,eax
    movzx eax,[rcx].rc.row
    mov y,eax

    [rcx].CursorGet()
    [rcx].SetMaxConsole()
    [rcx].MessageBox(MB_OK, "1", "SetMaxConsole()" )

    [rcx].MoveConsole(100, 100)

    mov edx,x
    mov r8d,y
    sub edx,20
    sub r8d,10
    [rcx].SetConsole(edx, r8d)

    [rcx].Hide()
    [rcx].Clear(0x00F00020)
    [rcx].PutString(10, 2, 0, 0, "tconsole::putxyf()\ntconsole::putxya()")
    [rcx].PutChar(10, 2, 18, 0xF000)
    [rcx].Show()
    [rcx].CursorOff()
    [rcx].MessageBox(MB_OK, "2", "MoveConsole(100, 100)" )

    [rcx].Hide()
    [rcx].Clear(0x00070020)
    [rcx].Show()
    [rcx].CursorSet()
    [rcx].SetConsole(x, y)
    [rcx].Release()
    ret

cmain endp

    end
