include consx.inc
include winuser.inc

    .code

ConsoleIdle proc

    .if console & CON_SLEEP

        Sleep(CON_SLEEP_TIME)

ifdef DEBUG
        mov eax,hCurrentWindow
else
        .if GetForegroundWindow() != hCurrentWindow

            mov eax,keyshift
            and dword ptr [eax],not 0x00FF030F

            .while  GetForegroundWindow() != hCurrentWindow

                Sleep(CON_SLEEP_TIME * 10)
                .break .if tupdate()
            .endw
        .endif
endif
    .endif

    tupdate()
    ret

ConsoleIdle endp

    END
