; CONSOLEEVENT.ASM--
;
; https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events
;

include windows.inc
include stdio.inc
include tchar.inc

option dllimport:none

.data
 hStdin HANDLE 0
 fdwSaveOldMode DWORD 0

.code

ErrorExit       proto :LPCSTR
KeyEventProc    proto :ptr KEY_EVENT_RECORD
MouseEventProc  proto :ptr MOUSE_EVENT_RECORD
ResizeEventProc proto :ptr WINDOW_BUFFER_SIZE_RECORD

_tmain proc argc:int_t, argv:array_t

    .new cNumRead:DWORD
    .new fdwMode:DWORD
    .new i:DWORD
    .new irInBuf[128]:INPUT_RECORD
    .new counter:int_t = 0

    ;; Get the standard input handle.

    mov hStdin,GetStdHandle(STD_INPUT_HANDLE)
    .if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle")
    .endif

    ;; Save the current input mode, to be restored on exit.

    .if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
        ErrorExit("GetConsoleMode")
    .endif

    ;; Enable the window and mouse input events.

    mov fdwMode,ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT
    .if (! SetConsoleMode(hStdin, fdwMode) )
        ErrorExit("SetConsoleMode")
    .endif

    ;; Loop to read and handle the next 100 input events.

    .while (counter <= 100)

        inc counter

        ;; Wait for the events.

        .if (! ReadConsoleInput(
                hStdin,      ;; input buffer handle
                &irInBuf,    ;; buffer to read into
                128,         ;; size of read buffer
                &cNumRead) ) ;; number of records read
            ErrorExit("ReadConsoleInput")
        .endif

        ;; Dispatch the events to the appropriate handler.

        assume rbx:ptr INPUT_RECORD
        .for ( rbx = &irInBuf, i = 0: i < cNumRead: i++, rbx += INPUT_RECORD )
            .switch ([rbx].EventType)
            .case KEY_EVENT ;; keyboard input
                KeyEventProc( &[rbx].Event.KeyEvent )
               .endc
            .case MOUSE_EVENT ; mouse input
                MouseEventProc( &[rbx].Event.MouseEvent )
               .endc
            .case WINDOW_BUFFER_SIZE_EVENT ; scrn buf. resizing
                ResizeEventProc( &[rbx].Event.WindowBufferSizeEvent )
               .endc
            .case FOCUS_EVENT    ; disregard focus events
            .case MENU_EVENT     ; disregard menu events
                .endc
            .default
                ErrorExit("Unknown event type")
               .endc
            .endsw
        .endf
    .endw

    ;; Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode)
    .return 0
    endp


ErrorExit proc lpszMessage:LPSTR

    fprintf(stderr, "%s\n", lpszMessage)

    ;; Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode)
    ExitProcess(0)
    ret
    endp

KeyEventProc proc ker:ptr KEY_EVENT_RECORD
    printf("Key event: ")
    mov rcx,ker
    .if ( [rcx].KEY_EVENT_RECORD.bKeyDown )
        printf("key pressed\n")
    .else
        printf("key released\n")
    .endif
    ret
    endp

ifndef MOUSE_HWHEELED
define MOUSE_HWHEELED 0x0008
endif

    assume rbx:ptr MOUSE_EVENT_RECORD

MouseEventProc proc uses rbx mer:ptr MOUSE_EVENT_RECORD

    printf("Mouse event: ")
    mov rbx,mer
    .switch([rbx].dwEventFlags)
    .case 0
        .if ( [rbx].dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
            printf("left button press \n")
        .elseif ( [rbx].dwButtonState == RIGHTMOST_BUTTON_PRESSED )
            printf("right button press \n")
        .elseif ( [rbx].dwButtonState == FROM_LEFT_3RD_BUTTON_PRESSED )
            printf("middle button press \n")
        .else
            printf("button press\n")
        .endif
        .endc
    .case DOUBLE_CLICK
        printf("double click\n")
       .endc
    .case MOUSE_HWHEELED
        printf("horizontal mouse wheel\n")
       .endc
    .case MOUSE_MOVED
        printf("mouse moved\n")
       .endc
    .case MOUSE_WHEELED
        printf("vertical mouse wheel\n")
       .endc
    .default
        printf("unknown\n")
       .endc
    .endsw
    ret
    endp

ResizeEventProc proc wbsr:ptr WINDOW_BUFFER_SIZE_RECORD
    printf("Resize event\n")
    mov rcx,wbsr
    printf("Console screen buffer is %d columns by %d rows.\n",
            [rcx].WINDOW_BUFFER_SIZE_RECORD.dwSize.X, [rcx].WINDOW_BUFFER_SIZE_RECORD.dwSize.Y)
    ret
    endp

    end _tstart
