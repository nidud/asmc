ifndef __TCONSOLE_INC
__TCONSOLE_INC equ <>

include twindow.inc

.pragma list(push, 0)

F_Title     equ 0   ; at_foreground
F_Frame     equ 1
F_Files     equ 2
F_System    equ 3
F_Hidden    equ 4
F_PBShade   equ 5
F_KeyBar    equ 6
F_Desktop   equ 7
F_Inactive  equ 8
F_Dialog    equ 9
F_Panel     equ 10
F_Subdir    equ 11
F_Menus     equ 12
F_TitleKey  equ 13
F_DialogKey equ 14
F_MenusKey  equ 15

F_TextView  equ 16+14
F_TextEdit  equ 16+15

B_Desktop   equ 0   ; at_background
B_Panel     equ 1
B_Dialog    equ 2
B_Menus     equ 3
B_Error     equ 4
B_Title     equ 5
B_Inverse   equ 6
B_Gray      equ 7
B_PushButt  equ 8
B_InvPanel  equ 9
B_InvMenus  equ 10
B_TextView  equ 12
B_TextEdit  equ 13

MKAT macro b, f
    exitm<f or (b shl 4)>
    endm

AT_DESKTOP      equ MKAT(B_Desktop, F_Desktop)
AT_PANEL        equ MKAT(B_Panel,   F_Panel)
AT_DIALOG       equ MKAT(B_Dialog,  F_Dialog)
AT_MENUS        equ MKAT(B_Menus,   F_Menus)
AT_ERROR        equ MKAT(B_Error,   F_Error)
AT_TITLE        equ MKAT(B_Title,   F_Title)

KEY_ALT         equ 0x08
KEY_CTRL        equ 0x04
KEY_SHIFT       equ 0x03

KEY_ESC         equ 0x011B
KEY_BKSP        equ 0x0E08
KEY_TAB         equ 0x0F09
KEY_ENTER       equ 0x1C0D
KEY_SPACE       equ 0x3920
KEY_HOME        equ 0x4700
KEY_UP          equ 0x4800
KEY_PGUP        equ 0x4900
KEY_LEFT        equ 0x4B00
KEY_RIGHT       equ 0x4D00
KEY_END         equ 0x4F00
KEY_DOWN        equ 0x5000
KEY_PGDN        equ 0x5100
KEY_INS         equ 0x5200
KEY_DEL         equ 0x5300

KEY_F1          equ 0x3B00
KEY_F2          equ 0x3C00
KEY_F3          equ 0x3D00
KEY_F4          equ 0x3E00
KEY_F5          equ 0x3F00
KEY_F6          equ 0x4000
KEY_F7          equ 0x4100
KEY_F8          equ 0x4200
KEY_F9          equ 0x4300
KEY_F10         equ 0x4400
KEY_F11         equ 0x8500
KEY_F12         equ 0x8600

KEY_KPSTAR      equ 0x372A
KEY_KPPLUS      equ 0x4E2B
KEY_KPMIN       equ 0x4A2D
KEY_KPENTER     equ 0xE00D

KEY_CTRLF1      equ 0x5E00
KEY_CTRLF2      equ 0x5F00
KEY_CTRLF3      equ 0x6000
KEY_CTRLF4      equ 0x6100
KEY_CTRLF5      equ 0x6200
KEY_CTRLF6      equ 0x6300
KEY_CTRLF7      equ 0x6400
KEY_CTRLF8      equ 0x6500
KEY_CTRLF9      equ 0x6600
KEY_CTRLF10     equ 0x6700
KEY_CTRLF11     equ 0xA800
KEY_CTRLF12     equ 0xA900

KEY_CTRL1       equ 0x0200
KEY_CTRL2       equ 0x0300
KEY_CTRL3       equ 0x0400
KEY_CTRL4       equ 0x0500
KEY_CTRL5       equ 0x0600
KEY_CTRL6       equ 0x0700
KEY_CTRL7       equ 0x0800
KEY_CTRL8       equ 0x0900
KEY_CTRL9       equ 0x0A00
KEY_CTRL0       equ 0x0B00

KEY_CTRLA       equ 0x1E01
KEY_CTRLB       equ 0x3002
KEY_CTRLC       equ 0x2E03
KEY_CTRLD       equ 0x2004
KEY_CTRLE       equ 0x1205
KEY_CTRLF       equ 0x2106
KEY_CTRLG       equ 0x2207
KEY_CTRLH       equ 0x2308
KEY_CTRLI       equ 0x1709
KEY_CTRLJ       equ 0x240A
KEY_CTRLK       equ 0x250B
KEY_CTRLL       equ 0x260C
KEY_CTRLM       equ 0x320D
KEY_CTRLN       equ 0x310E
KEY_CTRLO       equ 0x180F
KEY_CTRLP       equ 0x1910
KEY_CTRLQ       equ 0x1011
KEY_CTRLR       equ 0x1312
KEY_CTRLS       equ 0x1F13
KEY_CTRLT       equ 0x1414
KEY_CTRLU       equ 0x1615
KEY_CTRLV       equ 0x2F16
KEY_CTRLW       equ 0x1117
KEY_CTRLX       equ 0x2D18
KEY_CTRLY       equ 0x1519
KEY_CTRLZ       equ 0x2C1A

KEY_CTRLP1      equ 0x1A1B
KEY_CTRLP2      equ 0x1B1D

KEY_CTRLINS     equ 0x9200
KEY_CTRLDEL     equ 0x9300
KEY_CTRLLEFT    equ 0x7300
KEY_CTRLRIGHT   equ 0x7400
KEY_CTRLUP      equ 0x8D00
KEY_CTRLDN      equ 0x9100
KEY_CTRLEND     equ 0x7500
KEY_CTRLHOME    equ 0x7700
KEY_CTRLPGUP    equ 0x8400
KEY_CTRLPGDN    equ 0x7600
KEY_CTRLTAB     equ 0x9400
KEY_CTRLENTER   equ 0x1C0A
KEY_CTRLBKSP    equ 0x0E7F

KEY_ALTF1       equ 0x6800
KEY_ALTF2       equ 0x6900
KEY_ALTF3       equ 0x6A00
KEY_ALTF4       equ 0x6B00
KEY_ALTF5       equ 0x6C00
KEY_ALTF6       equ 0x6D00
KEY_ALTF7       equ 0x6E00
KEY_ALTF8       equ 0x6F00
KEY_ALTF9       equ 0x7000
KEY_ALTF10      equ 0x7100
KEY_ALTF11      equ 0xB200
KEY_ALTF12      equ 0xB300

KEY_ALT1        equ 0x7800
KEY_ALT2        equ 0x7900
KEY_ALT3        equ 0x7A00
KEY_ALT4        equ 0x7B00
KEY_ALT5        equ 0x7C00
KEY_ALT6        equ 0x7D00
KEY_ALT7        equ 0x7E00
KEY_ALT8        equ 0x7F00
KEY_ALT9        equ 0x8000
KEY_ALT0        equ 0x8100

KEY_ALTUP       equ 0x9800
KEY_ALTDN       equ 0xA000
KEY_ALTLEFT     equ 0x9B00
KEY_ALTRIGHT    equ 0x9D00
KEY_ALTC        equ 0x2E00
KEY_ALTL        equ 0x2600
KEY_ALTM        equ 0x3200
KEY_ALTP        equ 0x1900
KEY_ALTQ        equ 0x1000
KEY_ALTS        equ 0x1F00
KEY_ALTW        equ 0x1100
KEY_ALTX        equ 0x2D00
KEY_ALTZ        equ 0x2C00

KEY_SHIFTF1     equ 0x5400
KEY_SHIFTF2     equ 0x5500
KEY_SHIFTF3     equ 0x5600
KEY_SHIFTF4     equ 0x5700
KEY_SHIFTF5     equ 0x5800
KEY_SHIFTF6     equ 0x5900
KEY_SHIFTF7     equ 0x5A00
KEY_SHIFTF8     equ 0x5B00
KEY_SHIFTF9     equ 0x5C00
KEY_SHIFTF10    equ 0x5D00
KEY_SHIFTF11    equ 0x9E00
KEY_SHIFTF12    equ 0x9F00

MOUSECMD        equ -1
KEY_MSLEFT      equ 1
KEY_MSRIGTH     equ 2
KEY_MOUSEPRESS  equ KEY_MSLEFT or KEY_MSRIGTH
KEY_MOUSEUP     equ 0x00010000
KEY_MOUSEDN     equ 0x00020000

SHIFT_RIGHT             equ 0x01
SHIFT_LEFT              equ 0x02
SHIFT_CTRL              equ 0x04
SHIFT_ALT               equ 0x08
SHIFT_SCROLL            equ 0x10
SHIFT_NUMLOCK           equ 0x20
SHIFT_CAPSLOCK          equ 0x40
SHIFT_INSERTSTATE       equ 0x80
SHIFT_CTRLLEFT          equ 0x0100
SHIFT_ALTLEFT           equ 0x0200
SHIFT_ENHANCED          equ 0x0400
SHIFT_CONTROLEKEY       equ 0x0800
SHIFT_SCROLLKEY         equ 0x1000
SHIFT_NUMLOCKKEY        equ 0x2000
SHIFT_CAPSLOCKKEY       equ 0x4000
SHIFT_INSERTKEY         equ 0x8000
SHIFT_KEYSPRESSED       equ 0x01000000
SHIFT_MOUSEKEYLEFT      equ 0x00010000
SHIFT_MOUSEKEYRIGTH     equ 0x00020000
SHIFT_MOUSEKEYLEFT2     equ 0x00040000
SHIFT_MOUSEKEYLEFT3     equ 0x00080000
SHIFT_MOUSEKEYLEFT4     equ 0x00100000
SHIFT_MOUSEWHEEL        equ 0x00200000
SHIFT_MOUSEDOUBLECLICK  equ 0x00400000
SHIFT_MOUSEMOVED        equ 0x00800000
SHIFT_MOUSEFLAGS        equ 0x00FF0000
SHIFT_RELEASEKEY        equ 0x80000000

MAXKEYSTACK     equ 32
CURSOR_NORMAL   equ 16

.pragma pack(push, 1)

CURSOR          STRUC   ; CONSOLE_CURSOR_INFO
dwSize          dd ?    ; .dwSize   1..100
bVisible        dd ?    ; .bVisible 0..1
x               dw ?    ; word x,y  COORD
y               dw ?
CURSOR          ENDS
PCURSOR         typedef ptr CURSOR

.pragma pack(pop)

CON_UBEEP   equ 0x0001  ; Use Beep
CON_MOUSE   equ 0x0002  ; Use Mouse
CON_IOSFN   equ 0x0004  ; Use Long File Names
CON_CLIPB   equ 0x0008  ; Use System Clipboard
CON_ASCII   equ 0x0010  ; Use Ascii symbol
CON_NTCMD   equ 0x0020  ; Use NT Prompt
CON_CMDENV  equ 0x0040  ; CMD Compatible Mode
CON_IMODE   equ 0x0080  ; Init screen mode on startup
CON_UTIME   equ 0x0200  ; Use Time
CON_UDATE   equ 0x0400  ; Use Date
CON_LTIME   equ 0x0800  ; Use Long Time HH:MM:SS
CON_LDATE   equ 0x1000  ; Use Long Date YYYY-MM-DD
CON_SLEEP   equ 0x2000  ; Wait if set
CON_SIMDE   equ 0x4000  ; Use SSE Functions
CON_WIN95   equ 0x8000  ; Windows 95 mode if set
CON_DEFAULT equ 0x42AA
CON_SLEEP_TIME  equ 10  ; Time to wait

.class tconsole

    flags       uint_t ?
    rc          TRECT <>
    window      PCHAR_INFO ?
    backgr      PCHAR_INFO ?

    foreground  db 16 dup(?)
    background  db 16 dup(?)

    keyshift    dd ?
    keybchar    db ?
    keybscan    db ?
    keybcode    db ?
    keybstate   db ?
    keybmouse_x dd ?
    keybmouse_y dd ?
    keybcount   dd ?
    keybstack   dd MAXKEYSTACK dup(?)

    clipboard   dq ?
    clipbsize   dd ?

    Release     proc
    show        proc
    hide        proc

    read        proc :PCHAR_INFO
    write       proc :PCHAR_INFO

    getat       proc :int_t, :int_t
    getrcp      proc :TRECT
    getxyp      proc :int_t, :int_t
    getxyw      proc :int_t, :int_t
    getxyc      proc :int_t, :int_t
    getxya      proc :int_t, :int_t

    putxyw      proc :int_t, :int_t, :int_t, :uint_t
    putxyc      proc :int_t, :int_t, :int_t, :wchar_t
    putxya      proc :int_t, :int_t, :int_t, :uchar_t
    putxyf      proc :int_t, :int_t, :string_t, :vararg

    inside_x    proc :int_t
    inside_y    proc :int_t
    insidexy    proc :int_t, :int_t

    readevent   proc
    getevent    proc
    getch       proc
    shiftstate  proc
    mousepress  proc
    getmousex   proc
    getmousey   proc
    pushevent   proc :uint_t
    popevent    proc
    setkeystate proc

    clipfree    proc
    clipcopy    proc :string_t, :uint_t
    clippaste   proc

    cursoron    proc
    cursoroff   proc
    cursorget   proc :PCURSOR
    cursorset   proc :PCURSOR

    ClearConsole proc
    SetConsoleAttrib proc :uchar_t
    SetMaxConsoleSize proc
    SetConsoleSize proc :uint_t, :uint_t
    MoveConsole proc :uint_t, :uint_t

    .ends

externdef console:LPTCONSOLE

.pragma list(pop)
endif
