; _DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
define _CONIO_RETRO_COLORS
include conio.inc
include malloc.inc

.data
 _console   THWND 0
 _consize   COORD <>
 _conmax    COORD <>
 _conmode   uint_t ?
 _errmode   uint_t ?
 _conattrib uint_t ?

 _conscolor COLOR {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },{
     LIGHTGRAY,      ; FG_TITLE      7
     LIGHTGRAY,      ; FG_FRAME      7
     WHITE,          ; FG_FILES      F
     LIGHTGRAY,      ; FG_SYSTEM     7
     DARKGRAY,       ; FG_HIDDEN     8
     DARKGRAY,       ; FG_PBSHADE    8
     LIGHTGRAY,      ; FG_KEYBAR     7
     BROWN,          ; FG_DESKTOP    6
     DARKGRAY,       ; FG_INACTIVE   8
     LIGHTGRAY,      ; FG_DIALOG     7
     LIGHTGREEN,     ; FG_PANEL      A
     LIGHTCYAN,      ; FG_SUBDIR     B
     WHITE,          ; FG_MENUS      F
     LIGHTCYAN,      ; FG_TITLEKEY   B
     LIGHTCYAN,      ; FG_DIALOGKEY  B
     LIGHTCYAN,      ; FG_MENUSKEY   B
     LIGHTGRAY,      ; FG_TEXTVIEW   7
     LIGHTGRAY       ; FG_TEXTEDIT   7
    },{
     BLACK shl 4,    ; BG_DESKTOP    0
     BLACK shl 4,    ; BG_PANEL      0
     BLACK shl 4,    ; BG_DIALOG     0
     BLUE  shl 4,    ; BG_MENUS      1
     RED   shl 4,    ; BG_ERROR      4
     BLUE  shl 4,    ; BG_TITLE      1
     CYAN  shl 4,    ; BG_INVERSE    3
     BLACK shl 4,    ; BG_GRAY       0
     BLUE  shl 4,    ; BG_PUSHBUTTON 1
     CYAN  shl 4,    ; BG_INVPANEL   3
     BLACK shl 4,    ; BG_INVMENUS   0
     BLACK shl 4,    ; BG_TEXTVIEW   0
     BLACK shl 4     ; BG_TEXTEDIT   0
    } }

    .code

    assume rcx:THWND

_conslink proc hwnd:THWND

    mov rax,hwnd
    mov rcx,_console
    .if ( rcx )
        .while ( [rcx].next )
            mov rcx,[rcx].next
        .endw
        mov [rax].TCLASS.prev,rcx
        mov [rcx].TCLASS.next,rax
    .endif
    ret

_conslink endp


_consunlink proc hwnd:THWND

    mov rax,hwnd
    mov rcx,[rax].TCLASS.prev
    mov rdx,[rax].TCLASS.next
    .if ( rcx )
        mov [rcx].TCLASS.next,rdx
    .endif
    .if ( rdx )
        mov [rdx].TCLASS.prev,rcx
    .endif
    ret

_consunlink endp


__inticonsole proc uses rsi rdi rbx

   .new ci:CONSOLE_SCREEN_BUFFER_INFOEX = {CONSOLE_SCREEN_BUFFER_INFOEX}
   .new rc:TRECT = { 0, 0, 80, 25 }

    .if GetConsoleScreenBufferInfoEx(_confh, &ci)

        mov rc.row,ci.srWindow.Bottom
        mov _consize.Y,ax
        mov rc.col,ci.srWindow.Right
        mov _consize.X,ax
        mov _conattrib,ci.wAttributes
        mov _conmax,ci.dwMaximumWindowSize
        lea rsi,ci.ColorTable
        lea rdi,_conscolor
        mov ecx,16
        rep movsd

        .if _dlopen(rc, 0, 0, 0)

            mov _console,rax
            _rcread(rc, [rax].TCLASS.window)
            mov _errmode,SetErrorMode(SEM_FAILCRITICALERRORS)
            GetConsoleMode(_coninpfh, &_conmode)
            SetConsoleMode(_coninpfh, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
            FlushConsoleInputBuffer(_coninpfh)
        .endif
    .endif
    ret

__inticonsole endp


__termconsole proc

    mov rax,_console
    .if ( rax )
        _dlclose(rax)
    .endif
    SetConsoleMode(_coninpfh, _conmode)
    SetErrorMode(_errmode)
    ret

__termconsole endp

.pragma(init(__inticonsole, 100))
.pragma(exit(__termconsole, 2))

    end
