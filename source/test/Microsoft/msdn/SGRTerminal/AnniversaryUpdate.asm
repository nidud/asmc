; ANNIVERSARYUPDATE.ASM--
;
; https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
;

; System headers
include windows.inc

; Standard library C-style
include wchar.inc
include conio.inc
include stdlib.inc
include stdio.inc
include tchar.inc

define ESC <"\x1b">
define CSI <"\x1b[">

.code

EnableVTMode proc

    ; Set output mode to handle virtual terminal sequences
    .new hOut:HANDLE = GetStdHandle(STD_OUTPUT_HANDLE)
    .if (hOut == INVALID_HANDLE_VALUE)

        .return false
    .endif

    .new dwMode:DWORD = 0
    .if (!GetConsoleMode(hOut, &dwMode))

        .return false
    .endif

    or dwMode, ENABLE_VIRTUAL_TERMINAL_PROCESSING
    .if (!SetConsoleMode(hOut, dwMode))

        .return false
    .endif
    .return true

EnableVTMode endp

PrintVerticalBorder proc

    printf(ESC "(0")        ; Enter Line drawing mode
    printf(CSI "104;93m")   ; bright yellow on bright blue
    printf("x")             ; in line drawing mode, \x78 -> \u2502 "Vertical Bar"
    printf(CSI "0m")        ; restore color
    printf(ESC "(B")        ; exit line drawing mode
    ret

PrintVerticalBorder endp

PrintHorizontalBorder proc uses rsi rdi Size:COORD, fIsTop:bool

    printf(ESC "(0")        ; Enter Line drawing mode
    printf(CSI "104;93m")   ; Make the border bright yellow on bright blue
    .if (fIsTop)            ; print left corner
        printf("l")
    .else
        printf("m")
    .endif

    movzx esi,Size.X
    dec esi
    .for ( edi = 1 : edi < esi : edi++ )
        printf("q") ; in line drawing mode, \x71 -> \u2500 "HORIZONTAL SCAN LINE-5"
    .endf

    .if ( fIsTop )  ; print right corner
        printf("k")
    .else
        printf("j")
    .endif
    printf(CSI "0m")
    printf(ESC "(B") ; exit line drawing mode
    ret

PrintHorizontalBorder endp

PrintStatusLine proc pszMessage:string_t, Size:COORD

    printf(CSI "%d;1H", Size.Y)
    printf(CSI "K") ; clear the line
    printf(pszMessage)
    ret

PrintStatusLine endp

_tmain proc argc:int_t, argv:array_t

    ;; First, enable VT mode
    .new fSuccess:bool = EnableVTMode()
    .if (!fSuccess)

        printf("Unable to enter VT processing mode. Quitting.\n")
       .return -1
    .endif
    .new hOut:HANDLE = GetStdHandle(STD_OUTPUT_HANDLE)
    .if (hOut == INVALID_HANDLE_VALUE)

        printf("Couldn't get the console handle. Quitting.\n")
       .return -1
    .endif

   .new ScreenBufferInfo:CONSOLE_SCREEN_BUFFER_INFO
    GetConsoleScreenBufferInfo(hOut, &ScreenBufferInfo)
   .new Size:COORD
    movzx eax,ScreenBufferInfo.srWindow.Right
    sub ax,ScreenBufferInfo.srWindow.Left
    inc eax
    mov Size.X,ax
    movzx eax,ScreenBufferInfo.srWindow.Bottom
    sub ax,ScreenBufferInfo.srWindow.Top
    inc eax
    mov Size.Y,ax

    ;; Enter the alternate buffer
    printf(CSI "?1049h")

    ;; Clear screen, tab stops, set, stop at columns 16, 32
    printf(CSI "1;1H")
    printf(CSI "2J") ; Clear screen

   .new iNumTabStops:int_t = 4 ; (0, 20, 40, width)
    printf(CSI "3g")    ; clear all tab stops
    printf(CSI "1;20H") ; Move to column 20
    printf(ESC "H")     ; set a tab stop

    printf(CSI "1;40H") ; Move to column 40
    printf(ESC "H")     ; set a tab stop

    ;; Set scrolling margins to 3, h-2
    movzx edx,Size.Y
    sub edx,2
    printf(CSI "3;%dr", edx)
    movzx edx,Size.Y
    sub edx,4
   .new iNumLines:int_t = edx

    printf(CSI "1;1H")
    printf(CSI "102;30m")
    printf("Windows 10 Anniversary Update - VT Example")
    printf(CSI "0m")

    ;; Print a top border - Yellow
    printf(CSI "2;1H")
    PrintHorizontalBorder(Size, true)

    ;; Print a bottom border
    movzx edx,Size.Y
    sub edx,1
    printf(CSI "%d;1H", edx)
    PrintHorizontalBorder(Size, false)

   .new wch:wchar_t

    ;; draw columns
    printf(CSI "3;1H")
    mov eax,iNumLines
    mul iNumTabStops
    mov esi,eax
    .for (ebx = 0 : ebx < esi: ebx++)

        PrintVerticalBorder()
        lea eax,[rbx+1]
        .if ( ebx != esi ) ; don't advance to next line if this is the last line
            printf("\t")   ; advance to next tab stop
        .endif
    .endf

    PrintStatusLine("Press any key to see text printed between tab stops.", Size)
    mov wch,_getwch()

    ;; Fill columns with output
    printf(CSI "3;1H")
    .for ( ebx = 0 : ebx < iNumLines : ebx++ )

        mov esi,iNumTabStops
        dec esi
        .for ( edi = 0 : edi < esi : edi++ )

            PrintVerticalBorder()
            printf("line=%d", ebx)
            printf("\t") ;  advance to next tab stop
        .endf
        PrintVerticalBorder() ; print border at right side
        lea eax,[rbx+1]
        .if ( eax != iNumLines )
            printf("\t") ; advance to next tab stop, (on the next line)
        .endif
    .endf

    PrintStatusLine("Press any key to demonstrate scroll margins", Size)
    mov wch,_getwch()

    printf(CSI "3;1H")
    mov eax,iNumLines
    shl eax,1
    .new count:int_t = eax
    .for ( ebx = 0 : ebx < count: ebx++)

        printf(CSI "K") ; clear the line
        mov esi,iNumTabStops
        dec esi
        .for ( edi = 0 : edi < esi : edi++ )

            PrintVerticalBorder()
            printf("line=%d", ebx)
            printf("\t") ; advance to next tab stop
        .endf
        PrintVerticalBorder() ; print border at right side
        lea eax,[rbx+1]
        .if ( eax != count )

            printf("\n") ; Advance to next line. If we're at the bottom of the margins, the text will scroll.
            printf("\r") ; return to first col in buffer
        .endif
    .endf

    PrintStatusLine("Press any key to exit", Size)
    mov wch,_getwch()

    ; Exit the alternate buffer
    printf(CSI "?1049l")
    ret

_tmain endp

    end _tstart
