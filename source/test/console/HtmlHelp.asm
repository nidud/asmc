include htmlhelp.inc
include conio.inc
include stdio.inc
include string.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:tstring_t
    .new buffer[512]:tchar_t
    .if ( ldr(argc) == 2 )
        ldr rdx,argv
        _tcscpy(&buffer, [rdx+size_t])
        _tcscat(&buffer, "::/index.htm>Mainwin")
        mov rcx,GetDesktopWindow()
        .if HtmlHelp(rcx, &buffer, HH_DISPLAY_TOPIC, NULL)
            _tprintf(
                "The help window is active as long as the App is running\n"
                "Hit any key to exit..\n"
                )
            _getch()
        .endif
    .endif
    .return(0)
    endp

    end _tstart
