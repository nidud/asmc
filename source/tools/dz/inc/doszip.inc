; DOSZIP.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef _DOSZIP_
define _DOSZIP_

define VERSION 400

include stdafx.inc
include resource.inc
include winproc.inc

define MAXDRIVES        26
define MAXLINE          0x8000
define MAXLBUF          (MAXLINE*2)
define WMAXPATH         0x1000
define MAXMESSAGE       32
define IDLETIME         10
define CURSOR_NORMAL    16
define STARTYEAR        0
define MAXYEAR          3000

define PREV_MENU        (VK_LEFT shl 16)
define NEXT_MENU        (VK_RIGHT shl 16)

define W_ISOPEN         0x00000001
define W_VISIBLE        0x00000002
define W_MOVEABLE       0x00000004
define W_SHADE          0x00000008
define W_MYBUF          0x00000010
define W_RESOURCE       0x00000020
define W_COLOR          0x00000040
define W_HELP           0x00000080
define W_TRANSPARENT    0x00000100
define W_CHECKED        0x00000200
define W_LIST           0x00000400
define W_CHILD          0x00000800
define W_NOFOCUS        0x00001000
define W_HASFOCUS       0x00002000
define W_PARENT         0x00004000
define W_DISABLED       0x00008000
define W_AUTOEXIT       0x00010000
define W_TABSTOP        0x00020000
define W_CAPTION        0x00040000
define W_SYSMENU        0x00080000
define W_WASVISIBLE     0x00100000


PDWND typedef ptr Doszip
PDMSG typedef ptr Message
PLINE typedef ptr LineClass

.enum CLASSTYPE {
    CT_DESKTOP,
    CT_DIALOG,
    CT_MENUDLG,
    CT_HELPDLG,
    CT_MENUBAR,
    CT_KEYBAR,
    CT_TILEBAR,
    CT_SCROLLBAR,
    CT_VIEW,
    CT_EDIT,
    CT_HEXEDIT,
    CT_COMMAND,
    CT_PANEL,
    CT_WINDOW,
    CT_SECTION,
    CT_ITEMTYPE,
    CT_PUSHBUTTON,
    CT_RADIOBUTTON,
    CT_CHECKBOX,
    CT_XCELL,
    CT_TEXTINPUT,
    CT_MENUITEM,
    CT_TEXTITEM,
    CT_USERTYPE,
    CT_ENTRY,
    CT_FILE,
    CT_LINE,
    }


.enum PanelType {
    VerticalShortList,
    VerticalShortDetail,
    HorizontalShortList,
    HorizontalShortDetail,
    VerticalLongList,
    VerticalLongDetail,
    HorizontalLongList,
    HorizontalLongDetail,
    VerticalWide,
    HorizontalWide,
    }

.enum PanelSort {
     SortName,
     SortType,
     SortDate,
     SortSize
     }

.template Message

    uMsg                dd ?
    wParam              WPARAM ?
    lParam              LPARAM ?
   .ends


.template MenuClass

    m_Dlg               PDWND ?
    m_Title             CHAR_INFO 16 dup(<>)
   .ends


.template PanelClass

    record Flags
     LongNames          dd : 1 = 1 ?
     Detail             dd : 1 = 0 ?
     WideView           dd : 1 = 0 ?
     HiddenFiles        dd : 1 = 1 ?
     MiniStatus         dd : 1 = 1 ?
     DriveInfo          dd : 1 = 0 ?
     Sorttype           dd : 2 = 0 ?
     NoSort             dd : 1 = 0 ?
     PanelID            dd : 1 = 0 ?
     Visible            dd : 1 = 1 ?
     Hidden             dd : 1 = 0 ?
     SortDIr            dd : 1 = 0 ?
     RootDir            dd : 1 = 0 ?
     DriveCDRoom        dd : 1 = 0 ?
     DriveNetwork       dd : 1 = 0 ?
     DriveRemovable     dd : 1 = 0 ?
     Archive            dd : 1 = 0 ?
    ends
    m_celFirst          TRECT <>
    m_fcbCount          dd ?
    m_fcbIndex          dd ?
    m_celCount          dd ?
    m_celIndex          dd ?
    m_srcMask           LPWSTR ?
    m_arcFile           LPWSTR ?
    m_srcPath           LPWSTR ?
    m_arcPath           LPWSTR ?
    m_Cell              PDWND ?
    m_ScrollBar         PDWND ?
    m_celType           dd ?
    m_XCells            db ?
    m_YCells            db ?
   .ends


.template EditClass

    record Flags
     MenuBar            dd : 1 ?
     ScrollBar          dd : 1 ?
     LineNumbers        dd : 1 ?
     Syntax             dd : 1 ?
     Folding            dd : 1 ?
     CreateBackup       dd : 1 ?
     AutoIndent         dd : 1 ?
     KeepTabs           dd : 1 ?
     OverwriteBlocks    dd : 1 ?
     UnixMode           dd : 1 ?
     TabSize            dd : 2 ?
     MultiLine          dd : 1 ?
     AutoSelect         dd : 1 ?
     Modified           dd : 1 ?
     FileUTF8           dd : 1 ?
     FileUTF16          dd : 1 ?
     FileBOM            dd : 1 ?
     FileBinary         dd : 1 ?
     FileCR             dd : 1 ?
     FileTab            dd : 1 ?
    ends
    m_FTime             dd ?
    m_XPos              db ?
    m_YPos              db ?
    m_Cols              db ?
    m_Rows              db ?
    m_XOffs             db ?
    m_YOffs             db ?
    m_LOffs             dd ?
    m_BOffs             dd ?
    m_ClipSL            dd ?
    m_ClipSO            dd ?
    m_ClipEL            dd ?
    m_ClipEO            dd ?
    m_Attribute         dd ?
    m_ScrollBar         PDWND ?
   .ends


.template CommandClass

    m_Path              PDWND ?
   .ends


.template ProgressClass

    m_XPos              dd ?
    m_Loop              dd ?
    m_Size              dq ?
    m_Name              LPWSTR ?
   .ends


.template CalendarClass

    m_Day               dd ?
    m_Month             dd ?
    m_Year              dd ?
    m_CurDay            dd ?
    m_CurMonth          dd ?
    m_CurYear           dd ?
    m_WeekDay           dd ?
    m_DaysInMonth       dd ?
   .ends


.template LineClass

    record Flags
     IsFile             dd : 1 ?
     IsBlank            dd : 1 ?
     IsFolded           dd : 1 ?
    ends
    m_Size              dd ?
    m_Count             dd ?
    union
     m_Indent           dd ?
     m_Offset           dd ?
    ends
    m_LBuf              LPSTR ?
    m_TBuf              LPSTR ?
   .ends


.template FileClass

    record Flags
     Selected           dd : 1 ?
     RootDir            dd : 1 ?
     UpDir              dd : 1 ?
     CDRoom             dd : 1 ?
     Archive            dd : 1 ?
     FullPath           dd : 1 ?
    ends
    m_Attributes        dd ?
    m_Time              FILETIME <>
    union
     struct
      m_LSize           dd ?
      m_HSize           dd ?
     ends
     m_Size             dq ?
    ends
   .ends


.enum ScrollAction {
    ScrollNoAction,
    ScrollMove,
    ScrollMoveUp,
    ScrollMoveDown,
    ScrollPageUp,
    ScrollPageDown
    }


.template ScrollClass

    m_Count             dd ? ; items per line
    m_Lines             dd ?
    m_Thumb             dd ?
    m_Offset            dd ?
    m_Attribute         dd ?
   .ends


.class Doszip

    record Flags
     Open               dd : 1 ?
     Visible            dd : 1 ?
     Moveable           dd : 1 ?
     Shade              dd : 1 ?
     Mybuf              dd : 1 ?
     Resource           dd : 1 ?
     Color              dd : 1 ?
     Help               dd : 1 ?
     Transparent        dd : 1 ?
     Checked            dd : 1 ?
     List               dd : 1 ?
     Child              dd : 1 ?
     NoFocus            dd : 1 ?
     HasFocus           dd : 1 ?
     Parent             dd : 1 ?
     Disabled           dd : 1 ?
     AutoExit           dd : 1 ?
     TabStop            dd : 1 ?
     Caption            dd : 1 ?
     SysMenu            dd : 1 ?
     WasVisible         dd : 1 ?
    ends
    m_Type              dd ?
    m_Home              PDWND ?
    m_Base              PDWND ?
    m_This              PDWND ?
    m_Prev              PDWND ?
    m_Next              PDWND ?
    union
     m_Text             LPSTR ?
     m_UText            LPWSTR ?
    ends
    m_Id                dd ?

    union
     struct
      m_rc              TRECT <>
      m_Window          PCHAR_INFO ?
      m_Resource        PIDD ?
      m_Cursor          CURSOR <>
      m_State           dd ?
      m_SysKey          dd ?
     ends
     File               FileClass <>
     Line               LineClass <>
     Entry              LineClass <>
     Section            LineClass <>
    ends

    union
     struct
      record Setup
       AutoSaveSetup    dd : 1 = 1 ?
       UseBeep          dd : 1 = 0 ?
       UseMouse         dd : 1 = 1 ?
       UseShortNames    dd : 1 = 0 ?
       UseClipboard     dd : 1 = 1 ?
       UseNetwork       dd : 1 = 0 ?
       UseNTPrompt      dd : 1 = 1 ?
       CMDCompatible    dd : 1 = 0 ?
       RestoreScreen    dd : 1 = 1 ?
       DeleteHistory    dd : 1 = 0 ?
       EscForUserScreen dd : 1 = 1 ?
       MenuBar          dd : 1 = 1 ?
       UseTime          dd : 1 = 1 ?
       UseDate          dd : 1 = 1 ?
       UseLongDate      dd : 1 = 0 ?
       UseLongTime      dd : 1 = 0 ?
       CommandLine      dd : 1 = 1 ?
       KeyBar           dd : 1 = 1 ?
      ends
      record Panels
       PanelSize        dd : 8 = 6 ?
       PanelID          dd : 1 = 0 ?
       Horizontal       dd : 1 = 0 ?
       WideView         dd : 1 = 0 ?
       InsertMoves      dd : 1 = 1 ?
       SelectSubDir     dd : 1 = 0 ?
       SortDirectories  dd : 1 = 0 ?
       ClearCDRDOnly    dd : 1 = 1 ?
      ends
      record Editor
       MenuBar          dd : 1 = 1 ?
       ScrollBar        dd : 1 = 1 ?
       LineNumbers      dd : 1 = 1 ?
       Syntax           dd : 1 = 1 ?
       Folding          dd : 1 = 1 ?
       CreateBackup     dd : 1 = 1 ?
       AutoIndent       dd : 1 = 1 ?
       KeepTabs         dd : 1 = 0 ?
       OverwriteBlocks  dd : 1 = 1 ?
       UnixMode         dd : 1 = 0 ?
       TabSize          dd : 2 = 2 ?
      ends
      record Confirm
       Copy             db : 1 = 1 ?
       Move             db : 1 = 1 ?
       Delete           db : 1 = 1 ?
       Directory        db : 1 = 1 ?
       System           db : 1 = 1 ?
       Hidden           db : 1 = 1 ?
       Exit             db : 1 = 1 ?
      ends
      record Search
       SearchSubdir     db : 1 = 0 ?
       SearchCase       db : 1 = 1 ?
       PromtReplace     db : 1 = 1 ?
      ends
      record Viewer
       MenuBar          db : 1 = 1 ?
       HexOffset        db : 1 = 1 ?
      ends
      m_LBuf            LPSTR ?
      m_TBuf            LPSTR ?
      m_MenuBar         PDWND ?
      m_KeyBar          PDWND ?
      m_PanelA          PDWND ?
      m_PanelB          PDWND ?
      m_CPanel          PDWND ?
      m_Command         PDWND ?
     ends
     Menu               MenuClass <>
     Panel              PanelClass <>
     Command            CommandClass <>
     Edit               EditClass <>
     Scroll             ScrollClass <>
     Calendar           CalendarClass <>
     Progress           ProgressClass <>
    ends

    Doszip              proc :SDWORD, :warray_t
    Release             proc
    WinProc             proc :DWORD, :WPARAM, :LPARAM, :VARARG
    PostMessage         proc :DWORD, :WPARAM, :LPARAM
    MessageBox          proc :LPWSTR, :LPWSTR, :DWORD, :VARARG
    Run                 proc
   .ends


MKID macro T, I
    exitm<(I shl 16 or T)>
    endm

MKAT macro B, F, wC
ifnb <wC>
    exitm<(((B shl 4 or F) shl 16) or wC)>
else
    exitm<(B shl 4 or F)>
endif
    endm

SetClass proto watcall :PDWND {
    mov     rbx,rax
ifdef __DEBUG__
    mov     this,rax
endif
    }

GetWindowSize proto watcall :TRECT {
    mov     edx,eax
    shr     edx,24
    shr     eax,16
    movzx   eax,al
    mov     ecx,eax
    imul    eax,edx
    shl     eax,2
    }

KeyCtrl macro reg
    exitm<(reg & (RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED))>
    endm

KeyAlt macro reg
    exitm<(reg & (RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED))>
    endm

KeyShift macro reg
    exitm<reg & SHIFT_PRESSED>
    endm

endif
