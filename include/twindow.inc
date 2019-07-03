ifndef __TWINDOW_INC
__TWINDOW_INC equ <>
include conio.inc

FG_TITLE        equ 0       ; Foreground
FG_FRAME        equ 1
FG_FILES        equ 2
FG_SYSTEM       equ 3
FG_HIDDEN       equ 4
FG_PBSHADE      equ 5
FG_KEYBAR       equ 6
FG_DESKTOP      equ 7
FG_INACTIVE     equ 8
FG_DIALOG       equ 9
FG_PANEL        equ 10
FG_SUBDIR       equ 11
FG_MENUS        equ 12
FG_TITLEKEY     equ 13
FG_DIALOGKEY    equ 14
FG_MENUSKEY     equ 15

BG_DESKTOP      equ  0+16   ; Background
BG_PANEL        equ  1+16
BG_DIALOG       equ  2+16
BG_MENUS        equ  3+16
BG_ERROR        equ  4+16
BG_TITLE        equ  5+16
BG_INVERSE      equ  6+16
BG_GRAY         equ  7+16
BG_PUSHBUTTON   equ  8+16
BG_INVPANEL     equ  9+16
BG_INVMENUS     equ 10+16

BG_TEXTVIEW     equ 12+16
BG_TEXTEDIT     equ 13+16
FG_TEXTVIEW     equ 14+16
FG_TEXTEDIT     equ 15+16

; Window Type

T_NORMAL        equ 0
T_PUSHBUTTON    equ 1
T_RADIOBUTTON   equ 2
T_CHECKBOX      equ 3
T_XCELL         equ 4
T_EDIT          equ 5
T_MENUS         equ 6
T_XHTML         equ 7
T_MOUSE         equ 8
T_SCROLLUP      equ 9
T_SCROLLDOWN    equ 10
T_TEXTBUTTON    equ 11

; Window Flags

W_ISOPEN        equ 0x01
W_VISIBLE       equ 0x02
W_MOVEABLE      equ 0x04
W_SHADE         equ 0x08
W_WNDPROC       equ 0x10
W_CHILD         equ 0x20
W_COLOR         equ 0x40
W_TRANSPARENT   equ 0x80

O_RADIO         equ 0x00100 ; Active (*)
O_CHECK         equ 0x00200 ; Active [x]
O_LIST          equ 0x00400 ; Linked list item
O_SELECT        equ 0x00800 ; Select text on activation
O_CONTROL       equ 0x01000 ; Allow _CONTROL chars
O_DEXIT         equ 0x02000 ; Close dialog and return 0: Cancel
O_PBKEY         equ 0x04000 ; Return result if short key used
O_DLGED         equ 0x08000 ; dialog text -- return Left/Right
O_GLOBAL        equ 0x10000 ; Item contain global short-key table
O_EVENT         equ 0x20000 ; Item have local event handler
O_CHILD         equ 0x40000 ; Item have a child
O_STATE         equ 0x80000 ; State

CURSOR_NORMAL   equ 16

WM_RETURNCMD    equ WM_USER+1
WM_CHILDMSG     equ WM_USER+2

ROBJECT         STRUC BYTE
flags           dw ?
count           db ?
index           db ?
rc              TRECT <>
ROBJECT         ENDS
robj_t          typedef ptr ROBJECT

IDDOBJ          STRUC BYTE
MemSize         dw ?
dialog          ROBJECT <>
IDDOBJ          ENDS
idd_t           typedef ptr IDDOBJ

TMESSAGE        STRUC
Next            ptr_t ?
Message         uint_t ?
wParam          size_t ?
lParam          ptr_t ?
TMESSAGE        ENDS
msg_t           typedef ptr TMESSAGE

TCURSOR         STRUC
CursorInfo      CONSOLE_CURSOR_INFO <>
Position        COORD <>
TCURSOR         ENDS
cursor_t        typedef ptr TCURSOR

TCONTEXT        STRUC BYTE
State           db ?
Flags           db ?
x               db ?
y               db ?
rc              TRECT <>
TCONTEXT        ENDS
context_t       typedef ptr TCONTEXT
window_t        typedef ptr TWindow

CALLBACK(tproc_t, :window_t, :uint_t, :size_t, :ptr_t)

APPINFO         STRUC
Instance        window_t ?
StdIn           HANDLE ?
StdOut          HANDLE ?
Message         msg_t ?
Buttons         dd ?
Focus           dd ?
Console         window_t ?
ConMode         dd ?
ErrMode         dd ?
Clipbord        string_t ?
ClipSize        dd ?
State           dd ?
APPINFO         ENDS
class_t         typedef ptr APPINFO

.class TWindow

    rc              TRECT <>
    Flags           uint_t ?
    Window          PCHAR_INFO ?
    Color           string_t ?
    Class           class_t ?
    Type            uint_t ?
    Index           uint_t ?
    WndProc         tproc_t ?
    Child           window_t ?
    PrevInst        window_t ?
    Cursor          cursor_t ?
    SysKey          uint_t ?
    Context         intptr_t ?

    Open            proc :TRECT, :uint_t
    Load            proc :idd_t
    Resource        proc :idd_t
    Release         proc

    Show            proc
    Hide            proc
    Move            proc :int_t, :int_t

    Read            proc
    Write           proc
    SetShade        proc
    ClrShade        proc

    Clear           proc :CHAR_INFO
    PutFrame        proc :TRECT, :int_t, :uchar_t
    PutChar         proc :int_t, :int_t, :int_t, :CHAR_INFO
    PutString       proc :int_t, :int_t, :ushort_t, :int_t, :string_t, :vararg
    PutPath         proc :int_t, :int_t, :int_t, :string_t
    PutCenter       proc :int_t, :int_t, :int_t, :string_t
    PutTitle        proc :string_t
    MessageBox      proc :int_t, :string_t, :string_t, :vararg

    CursorGet       proc
    CursorSet       proc
    CursorOn        proc
    CursorOff       proc
    CursorMove      proc :int_t, :int_t

    Register        proc :tproc_t
    Send            proc :uint_t, :size_t, :ptr
    Post            proc :uint_t, :size_t, :ptr
    PostQuit        proc :int_t
    Dispatch        proc :msg_t
    Translate       proc :msg_t

    Child           proc :TRECT, :uint_t, :uint_t
    Window          proc
    Focus           proc
    SetFocus        proc :uint_t
    KillFocus       proc
    NextItem        proc
    PrevItem        proc
    GetItem         proc :uint_t

    PushBCreate     proc :TRECT, :uint_t, :string_t
    PushBSet        proc
    PushBClear      proc
    PushBSetShade   proc
    PushBClrShade   proc

    Inside          proc :COORD

    OnLButtonDown   proc :uint_t, :size_t, :ptr
    OnMouseMove     proc :uint_t, :size_t, :ptr
    OnLButtonUp     proc :uint_t, :size_t, :ptr
    OnSetFocus      proc
    OnKillFocus     proc
    OnChar          proc :uint_t, :size_t, :ptr
    OnSysChar       proc :uint_t, :size_t, :ptr

    MoveConsole     proc x:int_t, y:int_t
    SetConsole      proc x:int_t, y:int_t
    SetMaxConsole   proc
    ConsoleSize     proc

    .ends

TEditColor          proto :window_t

endif
