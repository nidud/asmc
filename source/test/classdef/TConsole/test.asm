include tdialog.inc

    .code

main proc

    _getch()
    Console.SetMaxConsole()
    _getch()
    Console.SetConsoleSize(50, 20)
    _getch()
    Console.SetConsoleSize(80, 25)
    ret

main endp

    end
