;
; https://docs.microsoft.com/en-us/windows/console/setconsolectrlhandler
;
; The first argument (PHANDLER_ROUTINE) was incorrectly declared in wincon.inc.
;
; The handler will be called on Ctrl+C, Ctrl+Break, or a Close Window ([X])
; event to enable cleanup for a console application. Note: The test should
; be run from Explorer.
;
include conio.inc

.code

CtrlHandler proc EventCode:UINT

    .switch EventCode
      .case CTRL_C_EVENT ; 0
        _cprintf( "CTRL+C exit.\r\n" )
        .endc
      .case CTRL_BREAK_EVENT ; 1
        _cprintf( "CTRL+BRAK exit.\r\n" )
        .endc
      .case CTRL_CLOSE_EVENT ; 2
        _cprintf( "Close Window ([X]) exit.\r\n" )
        .endc
      .case CTRL_LOGOFF_EVENT ; 5
      .case CTRL_SHUTDOWN_EVENT ; 6
      .default
        _cprintf( "Unused exit.\r\n" )
        .endc
    .endsw
    _cprintf( "Hit any key to continue...\r" )
    _getch()

    SetConsoleCtrlHandler( &CtrlHandler, 0 )
    xor eax,eax
    ret

CtrlHandler endp

main proc

    ; Install handler

    SetConsoleCtrlHandler( &CtrlHandler, 1 )

    _cprintf( "CTRL+C, CTRL+BRAK, or [X] (Close Window) invokes the handler.\r\n"
              "Use any other key to exit.\r\n")
    _getch()

    ; Remove handler

    SetConsoleCtrlHandler( &CtrlHandler, 0 )
    ret

main endp

    end main
