; RESOURCE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef _RESOURCE_
define _RESOURCE_

define RT_CURSOR        1
define RT_BITMAP        2
define RT_ICON          3
define RT_MENU          4
define RT_DIALOG        5
define RT_STRING        6
define RT_FONTDIR       7
define RT_FONT          8
define RT_ACCELERATOR   9
define RT_RCDATA        10
define RT_MESSAGETABLE  11

define RT_GROUP_CURSOR  12
define RT_GROUP_ICON    14
define RT_VERSION       16
define RT_DLGINCLUDE    17
define RT_PLUGPLAY      19
define RT_VXD           20
define RT_ANICURSOR     21
define RT_ANIICON       22
define RT_HTML          23
define RT_MANIFEST      24
define RT_ANIMATION     25

define IDC_STATIC       (-1)
define IDC_ANIMATION    990
define IDC_COMBOBOXEX   1990
define IDC_EDIT         2990
define IDC_UPDOWN       2991
define IDC_HEADER       3990
define IDC_MONTHCAL     4990
define IDC_DATETIMEPICK 5990
define IDC_LISTVIEW     6990
define IDC_TREEVIEW     7990
define IDC_TAB          8990
define IDC_BUTTON1      9990
define IDC_IPADDRESS    10990
define IDC_STATUSBAR    11990
define IDC_PROGRESSBAR  12990
define IDC_TOOLBAR      13990
define IDC_TRACKBAR     14990
define IDC_SYSLINK      15990
define IDC_REBAR        16990

define LANGID_DE        0x0407
define LANGID_US        0x0409
define LANGID_FR        0x040C
define LANGID_ES        0x040A
define LANGID_RU        0x0423
define LANGID_SE        0x041D
define LANGID_IT        0x0410
define LANGID_UK        0x044B
define LANGID_NO        0x0414
define LANGID_NN        0x0814

define RC_BUTTON        0x0080
define RC_EDIT          0x0081
define RC_STATIC        0x0082
define RC_LISTBOX       0x0083
define RC_SCROLLB       0x0084
define RC_COMPOBOX      0x0085

define ACC_VIRTKEY      0x01
define ACC_NOINVERT     0x02
define ACC_SHIFT        0x04
define ACC_CONTROL      0x08
define ACC_ALT          0x10
define ACC_LAST         0x80

define MF_INSERT        0x00000000
define MF_CHANGE        0x00000080
define MF_APPEND        0x00000100
define MF_DELETE        0x00000200
define MF_REMOVE        0x00001000
define MF_BYCOMMAND     0x00000000
define MF_BYPOSITION    0x00000400
define MF_SEPARATOR     0x00000800
define MF_ENABLED       0x00000000
define MF_GRAYED        0x00000001
define MF_DISABLED      0x00000002
define MF_UNCHECKED     0x00000000
define MF_CHECKED       0x00000008
define MF_USECHECKBITMAPS 0x00000200
define MF_STRING        0x00000000
define MF_BITMAP        0x00000004
define MF_OWNERDRAW     0x00000100
define MF_POPUP         0x00000010
define MF_MENUBARBREAK  0x00000020
define MF_MENUBREAK     0x00000040
define MF_UNHILITE      0x00000000
define MF_HILITE        0x00000080
define MF_DEFAULT       0x00001000
define MF_SYSMENU       0x00002000
define MF_HELP          0x00004000
define MF_RIGHTJUSTIFY  0x00004000

define MF_MOUSESELECT   0x00008000
define MF_END           0x00000080

define BS_PUSHBUTTON    0x00000000
define BS_DEFPUSHBUTTON 0x00000001
define BS_CHECKBOX      0x00000002
define BS_AUTOCHECKBOX  0x00000003
define BS_RADIOBUTTON   0x00000004
define BS_3STATE        0x00000005
define BS_AUTO3STATE    0x00000006
define BS_GROUPBOX      0x00000007
define BS_USERBUTTON    0x00000008
define BS_AUTORADIOBUTTON 0x00000009
define BS_PUSHBOX       0x0000000A
define BS_OWNERDRAW     0x0000000B
define BS_TYPEMASK      0x0000000F
define BS_LEFTTEXT      0x00000020
define BS_TEXT          0x00000000
define BS_ICON          0x00000040
define BS_BITMAP        0x00000080
define BS_LEFT          0x00000100
define BS_RIGHT         0x00000200
define BS_CENTER        0x00000300
define BS_TOP           0x00000400
define BS_BOTTOM        0x00000800
define BS_VCENTER       0x00000C00
define BS_PUSHLIKE      0x00001000
define BS_MULTILINE     0x00002000
define BS_NOTIFY        0x00004000
define BS_FLAT          0x00008000
define BS_RIGHTBUTTON   BS_LEFTTEXT

define WS_OVERLAPPED    0x00000000
define WS_POPUP         0x80000000
define WS_CHILD         0x40000000
define WS_MINIMIZE      0x20000000
define WS_VISIBLE       0x10000000
define WS_DISABLED      0x08000000
define WS_CLIPSIBLINGS  0x04000000
define WS_CLIPCHILDREN  0x02000000
define WS_MAXIMIZE      0x01000000
define WS_CAPTION       0x00C00000
define WS_BORDER        0x00800000
define WS_DLGFRAME      0x00400000
define WS_VSCROLL       0x00200000
define WS_HSCROLL       0x00100000
define WS_SYSMENU       0x00080000
define WS_THICKFRAME    0x00040000
define WS_GROUP         0x00020000
define WS_TABSTOP       0x00010000

define ES_LEFT          0x0000
define ES_CENTER        0x0001

define DS_ABSALIGN      0x01
define DS_SYSMODAL      0x02
define DS_LOCALEDIT     0x20
define DS_SETFONT       0x40
define DS_MODALFRAME    0x80
define DS_NOIDLEMSG     0x100
define DS_SETFOREGROUND 0x200

define SS_LEFT          0x00000000
define SS_CENTER        0x00000001
define SS_RIGHT         0x00000002

define CBS_SIMPLE       0x0001
define LBS_NOTIFY       0x0001
define SBS_HORZ         0x0000

.pragma pack(push, 1)

; File data

ICONDIRENTRY    struct
bWidth          db ?    ; Image width in pixels
bHeight         db ?    ; Image height in pixels
bColorCount     db ?    ; Number of colors in the color table
bReserved       db ?    ; Reserved: Must be 0
wPlanes         dw ?    ; icon: color planes (0 or 1), cursor: horizontal coord: pixels from the left
wBitCount       dw ?    ; icon: bits per pixel, cursor: vertical coord: pixels from the top
dwBytesInRes    dd ?    ; Image data size in byte
dwImageOffset   dd ?    ; offset of the DIB or PNG data from the beginning of the ICO/CUR file
ICONDIRENTRY    ends

ICONDIR         struct
idReserved      dw ?    ; Must be 0
idType          dw ?    ; mage type: 1 for ICO, 2 for CUR
idCount         dw ?    ; Number of images in the file
idEntries       ICONDIRENTRY 0 dup(<?>)
ICONDIR         ends

; Resource data: https://devblogs.microsoft.com/oldnewthing/20120720-00/?p=7083/

GRPICONDIRENTRY struct
bWidth          db ?
bHeight         db ?
bColorCount     db ?
bReserved       db ?
wPlanes         dw ?
wBitCount       dw ?
dwBytesInRes    dd ?
nId             dw ?
GRPICONDIRENTRY ends

GRPICONDIR      struct
idReserved      dw ?
idType          dw ?
idCount         dw ?
idEntries       GRPICONDIRENTRY 0 dup(<?>)
GRPICONDIR      ends

.pragma pack(pop)

; string.asm

ExpandCString proto __ccall :string_t, :string_t, :string_t, :int_t

endif
