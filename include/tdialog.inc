ifndef __TDIALOG_INC
__TDIALOG_INC equ <>

include tconsole.inc

.pragma list(push, 0)
.pragma pack(push, 1)

ROBJECT     STRUC
flags       dw ?
count       db ?
index       db ?
rc          TRECT <>
ROBJECT     ENDS

IDDOBJ      STRUC
memsize     dw ?
dialog      ROBJECT <>
IDDOBJ      ENDS

.pragma pack(pop)

LPROBJECT   typedef ptr ROBJECT
LPIDDOBJ    typedef ptr IDDOBJ

_O_PBUTT    equ 0
_O_RBUTT    equ 1
_O_CHBOX    equ 2
_O_XCELL    equ 3
_O_TEDIT    equ 4
_O_MENUS    equ 5
_O_XHTML    equ 6
_O_MOUSE    equ 7
_O_LLMSU    equ 8
_O_LLMSD    equ 9
_O_TBUTT    equ 10

_O_RADIO    equ 0x0010
_O_FLAGB    equ 0x0020
_O_LLIST    equ 0x0040
_O_DTEXT    equ 0x0080
_O_CONTR    equ 0x0100
_O_DEXIT    equ 0x0200
_O_PBKEY    equ 0x0400
_O_DLGED    equ 0x0800
_O_GLCMD    equ 0x1000
_O_EVENT    equ 0x2000
_O_CHILD    equ 0x4000
_O_STATE    equ 0x8000
_O_DEACT    equ _O_STATE


.classdef TObject :LPROBJECT

    flags   dw ?
    count   db ?
    index   db ?
    rc      TRECT <>
    pData   PVOID ?

    Modal   proc

    .ends


_D_DOPEN    equ 0x01
_D_ONSCR    equ 0x02
_D_DMOVE    equ 0x04
_D_SHADE    equ 0x08
_D_MYBUF    equ 0x10    ; do not delete on exit (static)
_D_RCNEW    equ 0x20    ; dlclose -- delete dialog if set
_D_RESAT    equ 0x40    ; attrib is index in color table (rcedit)
_D_DHELP    equ 0x80    ; execute thelp() if set

_D_CLEAR    equ 0x0100  ; args on open/create
_D_BACKG    equ 0x0200
_D_FOREG    equ 0x0400
_D_STERR    equ 0x1000  ; error color (red)
_D_MENUS    equ 0x2000  ; menus color (gray), no title
_D_MUSER    equ 0x4000

_D_COLOR    equ _D_BACKG or _D_FOREG
_D_RESRC    equ _D_RCNEW or _D_MYBUF
_D_SETRC    equ _D_RCNEW or _D_MYBUF or _D_DOPEN
_D_STDDLG   equ _D_DMOVE or _D_SHADE or _D_CLEAR or _D_COLOR
_D_STDERR   equ _D_STDDLG or _D_STERR


.classdef TDialog

    flags   UINT ?
    count   UINT ?
    index   UINT ?
    window  LPTWINDOW ?
    object  LPTOBJECT ?

    Open    proc :TRECT, :UINT
    OpenIDD proc :LPIDDOBJ

    GetBitFlag proc :UINT, :UINT, :UINT
    SetBitFlag proc :UINT, :UINT, :UINT, :UINT

    .ends

.pragma list(pop)
endif
