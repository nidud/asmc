; ENABLINGVTERMINAL.ASM--
;
; https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
;

include stdio.inc
include windows.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

    ;; Set output mode to handle virtual terminal sequences
    .new hOut:HANDLE = GetStdHandle(STD_OUTPUT_HANDLE)
    .if (hOut == INVALID_HANDLE_VALUE)

        .return false
    .endif
    .new hIn:HANDLE = GetStdHandle(STD_INPUT_HANDLE)
    .if (hIn == INVALID_HANDLE_VALUE)

        .return false
    .endif

    .new dwOriginalOutMode:DWORD = 0
    .new dwOriginalInMode:DWORD = 0
    .if (!GetConsoleMode(hOut, &dwOriginalOutMode))

        .return false
    .endif
    .if (!GetConsoleMode(hIn, &dwOriginalInMode))

        .return false
    .endif

    .new dwRequestedOutModes:DWORD = ENABLE_VIRTUAL_TERMINAL_PROCESSING or DISABLE_NEWLINE_AUTO_RETURN
    .new dwRequestedInModes:DWORD = ENABLE_VIRTUAL_TERMINAL_INPUT

    .new dwOutMode:DWORD = dwOriginalOutMode
     or dwOutMode,dwRequestedOutModes
    .if (!SetConsoleMode(hOut, dwOutMode))

        ;; we failed to set both modes, try to step down mode gracefully.
        mov dwRequestedOutModes,ENABLE_VIRTUAL_TERMINAL_PROCESSING
        mov dwOutMode,dwOriginalOutMode
        or  dwOutMode,dwRequestedOutModes
        .if (!SetConsoleMode(hOut, dwOutMode))

            ;; Failed to set any VT mode, can't do anything here.
            .return -1
        .endif
    .endif

   .new dwInMode:DWORD = dwOriginalInMode
    or  dwInMode,dwRequestedInModes
    .if (!SetConsoleMode(hIn, dwInMode))

        ;; Failed to set VT input mode, can't do anything here.
        .return -1
    .endif
    .return 0

_tmain endp

    end _tstart
