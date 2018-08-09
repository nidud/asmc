include tdialog.inc

    .code

main proc

  local cursor:CURSOR

    Console.CursorGet(&cursor)
    Console.Maxconsole()
    Console.Getch()
    Console.Moveconsole(100, 100)
    Console.Setconsole(50, 8)
    Console.Setattrib(0x1B)
    Console.Clrconsole()
    Console.CPrintf(10, 2, "TConsole::CPrintf()\n TConsole::CPuta()")
    Console.CPuta(10, 3, 19, 0x70)
    Console.Update()
    Console.CursorOff()
    Console.Getch()
    Console.Setattrib(0x07)
    Console.Clrconsole()
    Console.Update()
    Console.CursorSet(&cursor)
    Console.Setconsole(80, 25)
    ret

main endp

    end
