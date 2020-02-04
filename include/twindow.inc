ifndef __TWINDOW_INC
__TWINDOW_INC equ <>
include wincon.inc
include winuser.inc

.enum ColorAttrib : byte {

    FG_TITLE,
    FG_FRAME,
    FG_FILES,
    FG_SYSTEM,
    FG_HIDDEN,
    FG_PBSHADE,
    FG_KEYBAR,
    FG_DESKTOP,
    FG_INACTIVE,
    FG_DIALOG,
    FG_PANEL,
    FG_SUBDIR,
    FG_MENUS,
    FG_TITLEKEY,
    FG_DIALOGKEY,
    FG_MENUSKEY,

    BG_DESKTOP,
    BG_PANEL,
    BG_DIALOG,
    BG_MENUS,
    BG_ERROR,
    BG_TITLE,
    BG_INVERSE,
    BG_GRAY,
    BG_PUSHBUTTON,
    BG_INVPANEL,
    BG_INVMENUS,
    BG_UNUSED1,
    BG_TEXTVIEW,
    BG_TEXTEDIT,
    FG_TEXTVIEW,
    FG_TEXTEDIT,
    COLOR_COUNT

}

.enum WindowType {

    T_NORMAL,
    T_PUSHBUTTON,
    T_RADIOBUTTON,
    T_CHECKBOX,
    T_XCELL,
    T_EDIT,
    T_MENU,
    T_XHTML,
    T_MOUSE,
    T_SCROLLUP,
    T_SCROLLDOWN,
    T_TEXTBUTTON
}

.enum WindowFlags {

    W_ISOPEN        = 0x01,
    W_VISIBLE       = 0x02,
    W_MOVEABLE      = 0x04,
    W_SHADE         = 0x08,
    W_WNDPROC       = 0x10,
    W_CHILD         = 0x20,
    W_COLOR         = 0x40,
    W_TRANSPARENT   = 0x80,

    O_RADIO         = 0x00100, ; Active (*)
    O_CHECK         = 0x00200, ; Active [x]
    O_LIST          = 0x00400, ; Linked list item
    O_SELECT        = 0x00800, ; Select text on activation
    O_CONTROL       = 0x01000, ; Allow _CONTROL chars
    O_DEXIT         = 0x02000, ; Close dialog and return 0: Cancel
    O_PBKEY         = 0x04000, ; Return result if short key used
    O_DLGED         = 0x08000, ; dialog text -- return Left/Right
    O_GLOBAL        = 0x10000, ; Item contain global short-key table
    O_EVENT         = 0x20000, ; Item have local event handler
    O_CHILD         = 0x40000, ; Item have a child
    O_STATE         = 0x80000  ; State
}

CURSOR_NORMAL   equ 16

WM_RETURNCMD    equ WM_USER+1
WM_CHILDMSG     equ WM_USER+2
MAXSCRLINE      equ 256 ; max screen size

.pragma pack(push, 1)

.template TColor
    at          db COLOR_COUNT dup(?)
.ends
color_t         typedef ptr TColor

.template TRect
    x           db ?
    y           db ?
    col         db ?
    row         db ?

    Size        proc
    Coord       proc
    SmallRect   proc
.ends
trect_t         typedef ptr TRect

TRect_Size macro this
    movzx       eax,[this].TRect.row
    mul         [this].TRect.col
    imul        eax,eax,CHAR_INFO
    retm        <eax>
    endm

TRect_Coord macro this
    movzx       eax,[this].TRect.row
    shl         eax,16
    mov         al,[this].TRect.col
    retm        <eax>
    endm

TRect_SmallRect macro this
    movzx       eax,[this].TRect.row
    movzx       edx,[this].TRect.y
    lea         rax,[rax+rdx-1]
    shl         edx,16
    shl         eax,16
    mov         dl,[this].TRect.x
    mov         al,[this].TRect.col
    add         al,dl
    dec         al
    shl         rax,32
    or          rax,rdx
    retm        <rax>
    endm

MTRECT macro x, y, col, row
    exitm<(x or (y shl 8) or (col shl 16) or (row shl 24 ))>
    endm


TRect::Read     proto :HANDLE, :PCHAR_INFO
TRect::Write    proto :HANDLE, :PCHAR_INFO
TRect::Exchange proto :HANDLE, :PCHAR_INFO


.template TRObject
    flags       dw ?
    count       db ?
    index       db ?
    rc          TRect <>
.ends
robject_t       typedef ptr TRObject

.template TResource
    MemSize     dw ?
    dialog      TRObject <>
.ends
resource_t      typedef ptr TResource

.template TMessage
    Next        ptr_t ?
    Message     uint_t ?
    wParam      size_t ?
    lParam      ptr_t ?
.ends
message_t       typedef ptr TMessage

.class TCursor

    CursorInfo  CONSOLE_CURSOR_INFO <>
    Position    COORD <>
    Handle      HANDLE ?

    Hide        proc
    Show        proc
    Move        proc :int_t, :int_t
    Release     proc
.ends
cursor_t        typedef ptr TCursor


.class TEdit

    base            string_t ?      ; base pointer
    flags           uint_t ?        ; config
    xpos            uint_t ?        ; text window x,y
    ypos            uint_t ?
    scols           uint_t ?        ; size of screen-line
    bcols           uint_t ?        ; size of buffer-line
    xoffs           uint_t ?        ; x offset on screen
    boffs           uint_t ?        ; base offset - start of screen-line
    bcount          uint_t ?        ; byte count in line (expanded)
    clrattrib       uint_t ?        ; clear attrib/char
    clip_so         uint_t ?        ; Clipboard start offset
    clip_eo         uint_t ?        ; Clipboard end offset

    Release         proc
    IsSelected      proc
    ClipSet         proc
    ClipDel         proc
    ClipCut         proc :uint_t
    ClipPaste       proc
    GetLine         proc
    SetWinPos       proc :trect_t, :trect_t
    SetCursor       proc

    .ends
    tedit_t     typedef ptr TEdit


.template TContext
union
  struct
    State       db ?
    Flags       db ?
    x           db ?
    y           db ?
    rc          TRect <>
  ends
    object      ptr_t ?
ends
.ends
context_t       typedef ptr TContext

.pragma pack(pop)

window_t        typedef ptr TWindow

.template TClass
    Instance    window_t ?
    StdIn       HANDLE ?
    StdOut      HANDLE ?
    Message     message_t ?
    Buttons     uint_t ?
    Focus       uint_t ?
    Console     window_t ?
    ConMode     uint_t ?
    ErrMode     uint_t ?
    Clipbord    string_t ?
    ClipSize    uint_t ?
    State       uint_t ?
.ends
class_t         typedef ptr TClass

CALLBACK(tproc_t, :window_t, :uint_t, :size_t, :ptr_t)

.class TWindow

    rc              TRect <>
    Flags           uint_t ?
    Window          PCHAR_INFO ?
    Color           color_t ?
    Class           class_t ?
    Type            uint_t ?
    Index           uint_t ?
    WndProc         tproc_t ?
    Child           window_t ?
    Prev            window_t ?
    Cursor          cursor_t ?
    SysKey          uint_t ?
    Context         TContext <>

    Open            proc :TRect, :uint_t
    Load            proc :resource_t
    Resource        proc :resource_t
    Release         proc

    Show            proc
    Hide            proc
    Move            proc :int_t, :int_t

    Read            proc :trect_t, :PCHAR_INFO
    Write           proc :trect_t, :PCHAR_INFO
    Exchange        proc :trect_t, :PCHAR_INFO

    SetShade        proc
    ClrShade        proc

    Clear           proc :CHAR_INFO
    PutFrame        proc :TRect, :int_t, :uchar_t
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
    DefWindowProc   proc :uint_t, :size_t, :ptr

    Child           proc :TRect, :uint_t, :uint_t
    Window          proc
    PushButton      proc :TRect, :uint_t, :string_t
    GetFocus        proc
    SetFocus        proc :uint_t
    GetItem         proc :uint_t

    MoveConsole     proc :int_t, :int_t
    SetConsole      proc :int_t, :int_t
    SetMaxConsole   proc
    ConsoleSize     proc

    CGetChar        proc :int_t, :int_t
    CPutChar        proc :int_t, :int_t, :int_t, :CHAR_INFO
    CPutString      proc :int_t, :int_t, :ushort_t, :int_t, :string_t, :vararg
    CPutPath        proc :int_t, :int_t, :int_t, :string_t
    CPutCenter      proc :int_t, :int_t, :int_t, :string_t
    CPutBackground  proc :int_t, :int_t, :int_t, :uchar_t

    .ends

TWindow::Open           proto :TRect, :uint_t
TWindow::Load           proto :resource_t
TWindow::Resource       proto :resource_t
TWindow::Release        proto
TWindow::Show           proto
TWindow::Hide           proto
TWindow::Move           proto :int_t, :int_t
TWindow::Read           proto :trect_t, :PCHAR_INFO
TWindow::Write          proto :trect_t, :PCHAR_INFO
TWindow::Exchange       proto :trect_t, :PCHAR_INFO
TWindow::SetShade       proto
TWindow::ClrShade       proto
TWindow::Clear          proto :CHAR_INFO
TWindow::PutFrame       proto :TRect, :int_t, :uchar_t
TWindow::PutChar        proto :int_t, :int_t, :int_t, :CHAR_INFO
TWindow::PutString      proto :int_t, :int_t, :ushort_t, :int_t, :string_t, :vararg
TWindow::PutPath        proto :int_t, :int_t, :int_t, :string_t
TWindow::PutCenter      proto :int_t, :int_t, :int_t, :string_t
TWindow::PutTitle       proto :string_t
TWindow::MessageBox     proto :int_t, :string_t, :string_t, :vararg
TWindow::CursorGet      proto
TWindow::CursorSet      proto
TWindow::CursorOn       proto
TWindow::CursorOff      proto
TWindow::CursorMove     proto :int_t, :int_t
TWindow::Register       proto :tproc_t
TWindow::Send           proto :uint_t, :size_t, :ptr
TWindow::Post           proto :uint_t, :size_t, :ptr
TWindow::PostQuit       proto :int_t
TWindow::DefWindowProc  proto :uint_t, :size_t, :ptr
TWindow::Child          proto :TRect, :uint_t, :uint_t
TWindow::Window         proto
TWindow::PushButton     proto :TRect, :uint_t, :string_t
TWindow::GetFocus       proto
TWindow::SetFocus       proto :uint_t
TWindow::GetItem        proto :uint_t
TWindow::MoveConsole    proto :int_t, :int_t
TWindow::SetConsole     proto :int_t, :int_t
TWindow::SetMaxConsole  proto
TWindow::ConsoleSize    proto
TWindow::CGetChar       proto :int_t, :int_t
TWindow::CPutChar       proto :int_t, :int_t, :int_t, :CHAR_INFO
TWindow::CPutString     proto :int_t, :int_t, :ushort_t, :int_t, :string_t, :vararg
TWindow::CPutPath       proto :int_t, :int_t, :int_t, :string_t
TWindow::CPutCenter     proto :int_t, :int_t, :int_t, :string_t
TWindow::CPutBackground proto :int_t, :int_t, :int_t, :uchar_t

endif
