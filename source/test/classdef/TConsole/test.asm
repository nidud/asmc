include tconsole.inc

    .code

    assume rcx: ptr tconsole

main proc

  local cursor:CURSOR

    mov rcx,console
    [rcx].cursorget(&cursor)
    [rcx].SetMaxConsoleSize()
    [rcx].getch()
    [rcx].MoveConsole(100, 100)
    [rcx].SetConsoleSize(50, 8)
    [rcx].SetConsoleAttrib(0x1B)
    [rcx].ClearConsole()
    [rcx].putxyf(10, 2, "tconsole::putxyf()\ntconsole::putxya()")
    [rcx].putxya(10, 3, 18, 0x70)
    [rcx].show()
    [rcx].cursoroff()
    [rcx].getch()
    [rcx].SetConsoleAttrib(0x07)
    [rcx].ClearConsole()
    [rcx].show()
    [rcx].cursorset(&cursor)
    [rcx].SetConsoleSize(80, 25)
    [rcx].Release()
    ret

main endp

    end
