ifndef _RICHEDIT_
_RICHEDIT_ equ <>
.xlist

ifndef _RICHEDIT_VER
_RICHEDIT_VER       equ 0x0800
endif
cchTextLimitDefault equ 32767
ifdef _UNICODE
MSFTEDIT_CLASS      equ <L"RICHEDIT50W">
else
MSFTEDIT_CLASS      equ <"RICHEDIT50W">
endif

;; NOTE:  MSFTEDIT.DLL only registers MSFTEDIT_CLASS.  If an application wants
;; to use the following Richedit classes, it needs to load the riched20.dll.
;; Otherwise, CreateWindow with RICHEDIT_CLASS would fail.
;; This also applies to any dialog that uses RICHEDIT_CLASS,

;; RichEdit 2.0 Window Class
;; On Windows CE, avoid possible conflicts on Win95
CERICHEDIT_CLASSA   equ <"RichEditCEA">
CERICHEDIT_CLASSW   equ <L"RichEditCEW">

RICHEDIT_CLASSA     equ <"RichEdit20A">
RICHEDIT_CLASS10A   equ <"RICHEDIT">    ; Richedit 1.0

ifndef MACPORT
RICHEDIT_CLASSW     equ <L"RichEdit20W">
else  ;----------------------MACPORT
RICHEDIT_CLASSW     equ <"RichEdit20W"> ; MACPORT change
endif ; MACPORT

if (_RICHEDIT_VER ge 0x0200 )
ifdef _UNICODE
RICHEDIT_CLASS      equ <RICHEDIT_CLASSW>
else
RICHEDIT_CLASS      equ <RICHEDIT_CLASSA>
endif ; UNICODE
else
RICHEDIT_CLASS      equ <RICHEDIT_CLASS10A>
endif ; _RICHEDIT_VER >= 0x0200

;; RichEdit messages

ifndef WM_CONTEXTMENU
WM_CONTEXTMENU      equ 0x007B
endif

ifndef WM_UNICHAR
WM_UNICHAR          equ 0x0109
endif

ifndef WM_PRINTCLIENT
WM_PRINTCLIENT      equ 0x0318
endif

ifndef EM_GETLIMITTEXT
EM_GETLIMITTEXT     equ (WM_USER + 37)
endif

ifndef EM_POSFROMCHAR
EM_POSFROMCHAR      equ (WM_USER + 38)
EM_CHARFROMPOS      equ (WM_USER + 39)
endif

ifndef EM_SCROLLCARET
EM_SCROLLCARET      equ (WM_USER + 49)
endif
EM_CANPASTE         equ (WM_USER + 50)
EM_DISPLAYBAND      equ (WM_USER + 51)
EM_EXGETSEL         equ (WM_USER + 52)
EM_EXLIMITTEXT      equ (WM_USER + 53)
EM_EXLINEFROMCHAR   equ (WM_USER + 54)
EM_EXSETSEL         equ (WM_USER + 55)
EM_FINDTEXT         equ (WM_USER + 56)
EM_FORMATRANGE      equ (WM_USER + 57)
EM_GETCHARFORMAT    equ (WM_USER + 58)
EM_GETEVENTMASK     equ (WM_USER + 59)
EM_GETOLEINTERFACE  equ (WM_USER + 60)
EM_GETPARAFORMAT    equ (WM_USER + 61)
EM_GETSELTEXT       equ (WM_USER + 62)
EM_HIDESELECTION    equ (WM_USER + 63)
EM_PASTESPECIAL     equ (WM_USER + 64)
EM_REQUESTRESIZE    equ (WM_USER + 65)
EM_SELECTIONTYPE    equ (WM_USER + 66)
EM_SETBKGNDCOLOR    equ (WM_USER + 67)
EM_SETCHARFORMAT    equ (WM_USER + 68)
EM_SETEVENTMASK     equ (WM_USER + 69)
EM_SETOLECALLBACK   equ (WM_USER + 70)
EM_SETPARAFORMAT    equ (WM_USER + 71)
EM_SETTARGETDEVICE  equ (WM_USER + 72)
EM_STREAMIN         equ (WM_USER + 73)
EM_STREAMOUT        equ (WM_USER + 74)
EM_GETTEXTRANGE     equ (WM_USER + 75)
EM_FINDWORDBREAK    equ (WM_USER + 76)
EM_SETOPTIONS       equ (WM_USER + 77)
EM_GETOPTIONS       equ (WM_USER + 78)
EM_FINDTEXTEX       equ (WM_USER + 79)
ifdef _WIN32
EM_GETWORDBREAKPROCEX equ (WM_USER + 80)
EM_SETWORDBREAKPROCEX equ (WM_USER + 81)
endif

;; RichEdit 2.0 messages
EM_SETUNDOLIMIT     equ (WM_USER + 82)
EM_REDO             equ (WM_USER + 84)
EM_CANREDO          equ (WM_USER + 85)
EM_GETUNDONAME      equ (WM_USER + 86)
EM_GETREDONAME      equ (WM_USER + 87)
EM_STOPGROUPTYPING  equ (WM_USER + 88)

EM_SETTEXTMODE      equ (WM_USER + 89)
EM_GETTEXTMODE      equ (WM_USER + 90)

;; enum for use with EM_GET/SETTEXTMODE
;; typedef enum tagTextMode
TM_PLAINTEXT        equ 1
TM_RICHTEXT         equ 2   ; Default behavior
TM_SINGLELEVELUNDO  equ 4
TM_MULTILEVELUNDO   equ 8   ; Default behavior
TM_SINGLECODEPAGE   equ 16
TM_MULTICODEPAGE    equ 32  ; Default behavior
;;} TEXTMODE;

EM_AUTOURLDETECT    equ (WM_USER + 91)
EM_GETAUTOURLDETECT equ (WM_USER + 92)
EM_SETPALETTE       equ (WM_USER + 93)
EM_GETTEXTEX        equ (WM_USER + 94)
EM_GETTEXTLENGTHEX  equ (WM_USER + 95)
EM_SHOWSCROLLBAR    equ (WM_USER + 96)
EM_SETTEXTEX        equ (WM_USER + 97)

;; East Asia specific messages
EM_SETPUNCTUATION   equ (WM_USER + 100)
EM_GETPUNCTUATION   equ (WM_USER + 101)
EM_SETWORDWRAPMODE  equ (WM_USER + 102)
EM_GETWORDWRAPMODE  equ (WM_USER + 103)
EM_SETIMECOLOR      equ (WM_USER + 104)
EM_GETIMECOLOR      equ (WM_USER + 105)
EM_SETIMEOPTIONS    equ (WM_USER + 106)
EM_GETIMEOPTIONS    equ (WM_USER + 107)
EM_CONVPOSITION     equ (WM_USER + 108)

EM_SETLANGOPTIONS   equ (WM_USER + 120)
EM_GETLANGOPTIONS   equ (WM_USER + 121)
EM_GETIMECOMPMODE   equ (WM_USER + 122)

EM_FINDTEXTW        equ (WM_USER + 123)
EM_FINDTEXTEXW      equ (WM_USER + 124)

;; RE3.0 FE messages
EM_RECONVERSION     equ (WM_USER + 125)
EM_SETIMEMODEBIAS   equ (WM_USER + 126)
EM_GETIMEMODEBIAS   equ (WM_USER + 127)

;; BiDi specific messages
EM_SETBIDIOPTIONS   equ (WM_USER + 200)
EM_GETBIDIOPTIONS   equ (WM_USER + 201)

EM_SETTYPOGRAPHYOPTIONS equ (WM_USER + 202)
EM_GETTYPOGRAPHYOPTIONS equ (WM_USER + 203)

;; Extended edit style specific messages
EM_SETEDITSTYLE     equ (WM_USER + 204)
EM_GETEDITSTYLE     equ (WM_USER + 205)

;; Extended edit style masks
SES_EMULATESYSEDIT  equ 1
SES_BEEPONMAXTEXT   equ 2
SES_EXTENDBACKCOLOR equ 4
SES_MAPCPS          equ 8   ;; (obsolete)
SES_EMULATE10       equ 16  ;; (obsolete)
SES_USECRLF         equ 32  ;; (obsolete)
SES_NOXLTSYMBOLRANGE equ 32
SES_USEAIMM         equ 64
SES_NOIME           equ 128

SES_ALLOWBEEPS      equ 256
SES_UPPERCASE       equ 512
SES_LOWERCASE       equ 1024
SES_NOINPUTSEQUENCECHK equ 2048
SES_BIDI            equ 4096
SES_SCROLLONKILLFOCUS equ 8192
SES_XLTCRCRLFTOCR   equ 16384
SES_DRAFTMODE       equ 32768

SES_USECTF          equ 0x0010000
SES_HIDEGRIDLINES   equ 0x0020000
SES_USEATFONT       equ 0x0040000
SES_CUSTOMLOOK      equ 0x0080000
SES_LBSCROLLNOTIFY  equ 0x0100000
SES_CTFALLOWEMBED   equ 0x0200000
SES_CTFALLOWSMARTTAG equ 0x0400000
SES_CTFALLOWPROOFING equ 0x0800000

;; Options for EM_SETLANGOPTIONS and EM_GETLANGOPTIONS
IMF_AUTOKEYBOARD        equ 0x0001
IMF_AUTOFONT            equ 0x0002
IMF_IMECANCELCOMPLETE   equ 0x0004 ;; High completes comp string when aborting, low cancels
IMF_IMEALWAYSSENDNOTIFY equ 0x0008
IMF_AUTOFONTSIZEADJUST  equ 0x0010
IMF_UIFONTS             equ 0x0020
IMF_DUALFONT            equ 0x0080
IMF_NORTFFONTSUBSTITUTE equ 0x0400


;; Values for EM_GETIMECOMPMODE
ICM_NOTOPEN             equ 0x0000
ICM_LEVEL3              equ 0x0001
ICM_LEVEL2              equ 0x0002
ICM_LEVEL2_5            equ 0x0003
ICM_LEVEL2_SUI          equ 0x0004
ICM_CTF                 equ 0x0005

;; Options for EM_SETTYPOGRAPHYOPTIONS
TO_ADVANCEDTYPOGRAPHY   equ 1
TO_SIMPLELINEBREAK      equ 2
TO_DISABLECUSTOMTEXTOUT equ 4
TO_ADVANCEDLAYOUT       equ 8

;; Pegasus outline mode messages (RE 3.0)

;; Outline mode message
EM_OUTLINE              equ (WM_USER + 220)
;; Message for getting and restoring scroll pos
EM_GETSCROLLPOS         equ (WM_USER + 221)
EM_SETSCROLLPOS         equ (WM_USER + 222)
;; Change fontsize in current selection by wParam
EM_SETFONTSIZE          equ (WM_USER + 223)
EM_GETZOOM              equ (WM_USER + 224)
EM_SETZOOM              equ (WM_USER + 225)
EM_GETVIEWKIND          equ (WM_USER + 226)
EM_SETVIEWKIND          equ (WM_USER + 227)

;; RichEdit 4.0 messages
EM_GETPAGE              equ (WM_USER + 228)
EM_SETPAGE              equ (WM_USER + 229)
EM_GETHYPHENATEINFO     equ (WM_USER + 230)
EM_SETHYPHENATEINFO     equ (WM_USER + 231)
EM_GETPAGEROTATE        equ (WM_USER + 235)
EM_SETPAGEROTATE        equ (WM_USER + 236)
EM_GETCTFMODEBIAS       equ (WM_USER + 237)
EM_SETCTFMODEBIAS       equ (WM_USER + 238)
EM_GETCTFOPENSTATUS     equ (WM_USER + 240)
EM_SETCTFOPENSTATUS     equ (WM_USER + 241)
EM_GETIMECOMPTEXT       equ (WM_USER + 242)
EM_ISIME                equ (WM_USER + 243)
EM_GETIMEPROPERTY       equ (WM_USER + 244)

;; These messages control what rich edit does when it comes accross
;; OLE objects during RTF stream in.  Normally rich edit queries the client
;; application only after OleLoad has been called.  With these messages it is possible to
;; set the rich edit control to a mode where it will query the client application before
;; OleLoad is called
EM_GETQUERYRTFOBJ       equ (WM_USER + 269)
EM_SETQUERYRTFOBJ       equ (WM_USER + 270)

;; EM_SETPAGEROTATE wparam values
EPR_0                   equ 0       ;; Text flows left to right and top to bottom
EPR_270                 equ 1       ;; Text flows top to bottom and right to left
EPR_180                 equ 2       ;; Text flows right to left and bottom to top
EPR_90                  equ 3       ;; Text flows bottom to top and left to right

;; EM_SETCTFMODEBIAS wparam values
CTFMODEBIAS_DEFAULT                 equ 0x0000
CTFMODEBIAS_FILENAME                equ 0x0001
CTFMODEBIAS_NAME                    equ 0x0002
CTFMODEBIAS_READING                 equ 0x0003
CTFMODEBIAS_DATETIME                equ 0x0004
CTFMODEBIAS_CONVERSATION            equ 0x0005
CTFMODEBIAS_NUMERIC                 equ 0x0006
CTFMODEBIAS_HIRAGANA                equ 0x0007
CTFMODEBIAS_KATAKANA                equ 0x0008
CTFMODEBIAS_HANGUL                  equ 0x0009
CTFMODEBIAS_HALFWIDTHKATAKANA       equ 0x000A
CTFMODEBIAS_FULLWIDTHALPHANUMERIC   equ 0x000B
CTFMODEBIAS_HALFWIDTHALPHANUMERIC   equ 0x000C

;; EM_SETIMEMODEBIAS lparam values
IMF_SMODE_PLAURALCLAUSE equ 0x0001
IMF_SMODE_NONE          equ 0x0002

;; EM_GETIMECOMPTEXT wparam structure
IMECOMPTEXT STRUC
cb          LONG ?      ;; count of bytes in the output buffer.
flags       DWORD ?     ;; value specifying the composition string type.
IMECOMPTEXT ENDS        ;;  Currently only support ICT_RESULTREADSTR
ICT_RESULTREADSTR       equ 1

;; Outline mode wparam values
EMO_EXIT                equ 0       ;; Enter normal mode,  lparam ignored
EMO_ENTER               equ 1       ;; Enter outline mode, lparam ignored
EMO_PROMOTE             equ 2       ;; LOWORD(lparam) == 0 ==>
                                        ;;  promote  to body-text
                                        ;; LOWORD(lparam) != 0 ==>
                                        ;;  promote/demote current selection
                                        ;;  by indicated number of levels
EMO_EXPAND              equ 3       ;; HIWORD(lparam) = EMO_EXPANDSELECTION
                                        ;;  -> expands selection to level
                                        ;;  indicated in LOWORD(lparam)
                                        ;;  LOWORD(lparam) = -1/+1 corresponds
                                        ;;  to collapse/expand button presses
                                        ;;  in winword (other values are
                                        ;;  equivalent to having pressed these
                                        ;;  buttons more than once)
                                        ;;  HIWORD(lparam) = EMO_EXPANDDOCUMENT
                                        ;;  -> expands whole document to
                                        ;;  indicated level
EMO_MOVESELECTION       equ 4       ;; LOWORD(lparam) != 0 -> move current
                                        ;;  selection up/down by indicated amount
EMO_GETVIEWMODE         equ 5       ;; Returns VM_NORMAL or VM_OUTLINE

;; EMO_EXPAND options
EMO_EXPANDSELECTION     equ 0
EMO_EXPANDDOCUMENT      equ 1

VM_NORMAL               equ 4       ;; Agrees with RTF \viewkindN
VM_OUTLINE              equ 2
VM_PAGE                 equ 9       ;; Screen page view (not print layout)

;; New notifications
EN_MSGFILTER            equ 0x0700
EN_REQUESTRESIZE        equ 0x0701
EN_SELCHANGE            equ 0x0702
EN_DROPFILES            equ 0x0703
EN_PROTECTED            equ 0x0704
EN_CORRECTTEXT          equ 0x0705          ;; PenWin specific
EN_STOPNOUNDO           equ 0x0706
EN_IMECHANGE            equ 0x0707          ;; East Asia specific
EN_SAVECLIPBOARD        equ 0x0708
EN_OLEOPFAILED          equ 0x0709
EN_OBJECTPOSITIONS      equ 0x070a
EN_LINK                 equ 0x070b
EN_DRAGDROPDONE         equ 0x070c
EN_PARAGRAPHEXPANDED    equ 0x070d
EN_PAGECHANGE           equ 0x070e
EN_LOWFIRTF             equ 0x070f
EN_ALIGNLTR             equ 0x0710          ;; BiDi specific notification
EN_ALIGNRTL             equ 0x0711          ;; BiDi specific notification

;; Event notification masks
ENM_NONE                equ 0x00000000
ENM_CHANGE              equ 0x00000001
ENM_UPDATE              equ 0x00000002
ENM_SCROLL              equ 0x00000004
ENM_SCROLLEVENTS        equ 0x00000008
ENM_DRAGDROPDONE        equ 0x00000010
ENM_PARAGRAPHEXPANDED   equ 0x00000020
ENM_PAGECHANGE          equ 0x00000040
ENM_KEYEVENTS           equ 0x00010000
ENM_MOUSEEVENTS         equ 0x00020000
ENM_REQUESTRESIZE       equ 0x00040000
ENM_SELCHANGE           equ 0x00080000
ENM_DROPFILES           equ 0x00100000
ENM_PROTECTED           equ 0x00200000
ENM_CORRECTTEXT         equ 0x00400000      ;; PenWin specific
ENM_IMECHANGE           equ 0x00800000      ;; Used by RE1.0 compatibility
ENM_LANGCHANGE          equ 0x01000000
ENM_OBJECTPOSITIONS     equ 0x02000000
ENM_LINK                equ 0x04000000
ENM_LOWFIRTF            equ 0x08000000


;; New edit control styles
ES_SAVESEL              equ 0x00008000
ES_SUNKEN               equ 0x00004000
ES_DISABLENOSCROLL      equ 0x00002000
;; Same as WS_MAXIMIZE, but that doesn't make sense so we re-use the value
ES_SELECTIONBAR         equ 0x01000000
;; Same as ES_UPPERCASE, but re-used to completely disable OLE drag'n'drop
ES_NOOLEDRAGDROP        equ 0x00000008

;; New edit control extended style
if (_WIN32_WINNT gt 0x0400) or (WINVER gt 0x0400)
ES_EX_NOCALLOLEINIT     equ 0x00000000      ;; Not supported in RE 2.0/3.0
else
ifdef  _WIN32
ES_EX_NOCALLOLEINIT     equ 0x01000000
endif
endif

;; These flags are used in FE Windows
ES_VERTICAL             equ 0x00400000      ;; Not supported in RE 2.0/3.0
ES_NOIME                equ 0x00080000
ES_SELFIME              equ 0x00040000

;; Edit control options
ECO_AUTOWORDSELECTION   equ 0x00000001
ECO_AUTOVSCROLL         equ 0x00000040
ECO_AUTOHSCROLL         equ 0x00000080
ECO_NOHIDESEL           equ 0x00000100
ECO_READONLY            equ 0x00000800
ECO_WANTRETURN          equ 0x00001000
ECO_SAVESEL             equ 0x00008000
ECO_SELECTIONBAR        equ 0x01000000
ECO_VERTICAL            equ 0x00400000      ;; FE specific


;; ECO operations
ECOOP_SET               equ 0x0001
ECOOP_OR                equ 0x0002
ECOOP_AND               equ 0x0003
ECOOP_XOR               equ 0x0004

;; New word break function actions
WB_CLASSIFY         equ 3
WB_MOVEWORDLEFT     equ 4
WB_MOVEWORDRIGHT    equ 5
WB_LEFTBREAK        equ 6
WB_RIGHTBREAK       equ 7

;; East Asia specific flags
WB_MOVEWORDPREV     equ 4
WB_MOVEWORDNEXT     equ 5
WB_PREVBREAK        equ 6
WB_NEXTBREAK        equ 7

PC_FOLLOWING        equ 1
PC_LEADING          equ 2
PC_OVERFLOW         equ 3
PC_DELIMITER        equ 4
WBF_WORDWRAP        equ 0x010
WBF_WORDBREAK       equ 0x020
WBF_OVERFLOW        equ 0x040
WBF_LEVEL1          equ 0x080
WBF_LEVEL2          equ 0x100
WBF_CUSTOM          equ 0x200

;; East Asia specific flags
IMF_FORCENONE           equ 0x0001
IMF_FORCEENABLE         equ 0x0002
IMF_FORCEDISABLE        equ 0x0004
IMF_CLOSESTATUSWINDOW   equ 0x0008
IMF_VERTICAL            equ 0x0020
IMF_FORCEACTIVE         equ 0x0040
IMF_FORCEINACTIVE       equ 0x0080
IMF_FORCEREMEMBER       equ 0x0100
IMF_MULTIPLEEDIT        equ 0x0400

;; Word break flags (used with WB_CLASSIFY)
WBF_CLASS           equ 0x0F
WBF_ISWHITE         equ 0x10
WBF_BREAKLINE       equ 0x20
WBF_BREAKAFTER      equ 0x40


;; Data types

ifdef _WIN32
;; Extended edit word break proc (character set aware)
CALLBACK(EDITWORDBREAKPROCEX, :LPSTR, :LONG, :BYTE, :SINT)
endif

;; All character format measurements are in twips
CHARFORMATA     STRUC 4
cbSize          UINT ?
dwMask          DWORD ?
dwEffects       DWORD ?
yHeight         LONG ?
yOffset         LONG ?
crTextColor     COLORREF ?
bCharSet        BYTE ?
bPitchAndFamily BYTE ?
szFaceName      SBYTE LF_FACESIZE dup(?)
CHARFORMATA     ENDS

CHARFORMATW     STRUC 4
cbSize          UINT ?
dwMask          DWORD ?
dwEffects       DWORD ?
yHeight         LONG ?
yOffset         LONG ?
crTextColor     COLORREF ?
bCharSet        BYTE ?
bPitchAndFamily BYTE ?
szFaceName      WCHAR LF_FACESIZE dup(?)
CHARFORMATW     ENDS

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
CHARFORMAT equ <CHARFORMATW>
else
CHARFORMAT equ <CHARFORMATA>
endif ;; UNICODE
else
CHARFORMAT equ <CHARFORMATA>
endif ;; _RICHEDIT_VER >= 0x0200

;; CHARFORMAT2 structure

CHARFORMAT2W    STRUC 4
cbSize          UINT ?
dwMask          DWORD ?
dwEffects       DWORD ?
yHeight         LONG ?
yOffset         LONG ?              ;; > 0 for superscript, < 0 for subscript
crTextColor     COLORREF ?
bCharSet        BYTE ?
bPitchAndFamily BYTE ?
szFaceName      WCHAR LF_FACESIZE dup(?)
wWeight         WORD ?              ;; Font weight (LOGFONT value)
sSpacing        SWORD ?             ;; Amount to space between letters
crBackColor     COLORREF ?          ;; Background color
lcid            LCID ?              ;; Locale ID
dwReserved      DWORD ?             ;; Reserved. Must be 0
sStyle          SWORD ?             ;; Style handle
wKerning        WORD ?              ;; Twip size above which to kern char pair
bUnderlineType  BYTE ?              ;; Underline type
bAnimation      BYTE ?              ;; Animated text like marching ants
bRevAuthor      BYTE ?              ;; Revision author index
if (_RICHEDIT_VER ge 0x0800)
bUnderlineColor BYTE ?
endif
CHARFORMAT2W    ENDS

CHARFORMAT2A    STRUC 4
cbSize          UINT ?
dwMask          DWORD ?
dwEffects       DWORD ?
yHeight         LONG ?
yOffset         LONG ?              ;; > 0 for superscript, < 0 for subscript
crTextColor     COLORREF ?
bCharSet        BYTE ?
bPitchAndFamily BYTE ?
szFaceName      SBYTE LF_FACESIZE dup(?)
wWeight         WORD ?              ;; Font weight (LOGFONT value)
sSpacing        SWORD ?             ;; Amount to space between letters
crBackColor     COLORREF ?          ;; Background color
lcid            LCID ?              ;; Locale ID
dwReserved      DWORD ?             ;; Reserved. Must be 0
sStyle          SWORD ?             ;; Style handle
wKerning        WORD ?              ;; Twip size above which to kern char pair
bUnderlineType  BYTE ?              ;; Underline type
bAnimation      BYTE ?              ;; Animated text like marching ants
bRevAuthor      BYTE ?              ;; Revision author index
if (_RICHEDIT_VER ge 0x0800)
bUnderlineColor BYTE ?
endif
CHARFORMAT2A    ENDS

ifdef _UNICODE
CHARFORMAT2 equ <CHARFORMAT2W>
else
CHARFORMAT2 equ <CHARFORMAT2A>
endif

CHARFORMATDELTA equ (sizeof(CHARFORMAT2) - sizeof(CHARFORMAT))


;; CFM_COLOR mirrors CFE_AUTOCOLOR, a little hack to easily deal with autocolor

;; CHARFORMAT masks
CFM_BOLD        equ 0x00000001
CFM_ITALIC      equ 0x00000002
CFM_UNDERLINE   equ 0x00000004
CFM_STRIKEOUT   equ 0x00000008
CFM_PROTECTED   equ 0x00000010
CFM_LINK        equ 0x00000020          ;; Exchange hyperlink extension
CFM_SIZE        equ 0x80000000
CFM_COLOR       equ 0x40000000
CFM_FACE        equ 0x20000000
CFM_OFFSET      equ 0x10000000
CFM_CHARSET     equ 0x08000000

;; CHARFORMAT effects
CFE_BOLD        equ 0x0001
CFE_ITALIC      equ 0x0002
CFE_UNDERLINE   equ 0x0004
CFE_STRIKEOUT   equ 0x0008
CFE_PROTECTED   equ 0x0010
CFE_LINK        equ 0x0020
CFE_AUTOCOLOR   equ 0x40000000          ;; NOTE: this corresponds to
                                            ;; CFM_COLOR, which controls it
;; Masks and effects defined for CHARFORMAT2 -- an (*) indicates
;; that the data is stored by RichEdit 2.0/3.0, but not displayed
CFM_SMALLCAPS       equ 0x0040          ;; (*)
CFM_ALLCAPS         equ 0x0080          ;; Displayed by 3.0
CFM_HIDDEN          equ 0x0100          ;; Hidden by 3.0
CFM_OUTLINE         equ 0x0200          ;; (*)
CFM_SHADOW          equ 0x0400          ;; (*)
CFM_EMBOSS          equ 0x0800          ;; (*)
CFM_IMPRINT         equ 0x1000          ;; (*)
CFM_DISABLED        equ 0x2000
CFM_REVISED         equ 0x4000

CFM_BACKCOLOR       equ 0x04000000
CFM_LCID            equ 0x02000000
CFM_UNDERLINETYPE   equ 0x00800000      ;; Many displayed by 3.0
CFM_WEIGHT          equ 0x00400000
CFM_SPACING         equ 0x00200000      ;; Displayed by 3.0
CFM_KERNING         equ 0x00100000      ;; (*)
CFM_STYLE           equ 0x00080000      ;; (*)
CFM_ANIMATION       equ 0x00040000      ;; (*)
CFM_REVAUTHOR       equ 0x00008000

CFE_SUBSCRIPT       equ 0x00010000      ;; Superscript and subscript are
CFE_SUPERSCRIPT     equ 0x00020000      ;;  mutually exclusive

CFM_SUBSCRIPT       equ (CFE_SUBSCRIPT | CFE_SUPERSCRIPT)
CFM_SUPERSCRIPT     equ CFM_SUBSCRIPT

;; CHARFORMAT "ALL" masks
CFM_EFFECTS     equ (CFM_BOLD or CFM_ITALIC or CFM_UNDERLINE or CFM_COLOR or \
                     CFM_STRIKEOUT or CFE_PROTECTED or CFM_LINK)
CFM_ALL         equ (CFM_EFFECTS or CFM_SIZE or CFM_FACE or CFM_OFFSET or CFM_CHARSET)

CFM_EFFECTS2    equ (CFM_EFFECTS or CFM_DISABLED or CFM_SMALLCAPS or CFM_ALLCAPS \
                    or CFM_HIDDEN  or CFM_OUTLINE or CFM_SHADOW or CFM_EMBOSS \
                    or CFM_IMPRINT or CFM_DISABLED or CFM_REVISED \
                    or CFM_SUBSCRIPT or CFM_SUPERSCRIPT or CFM_BACKCOLOR)

CFM_ALL2        equ (CFM_ALL or CFM_EFFECTS2 or CFM_BACKCOLOR or CFM_LCID \
                    or CFM_UNDERLINETYPE or CFM_WEIGHT or CFM_REVAUTHOR \
                    or CFM_SPACING or CFM_KERNING or CFM_STYLE or CFM_ANIMATION)

CFE_SMALLCAPS       equ CFM_SMALLCAPS
CFE_ALLCAPS         equ CFM_ALLCAPS
CFE_HIDDEN          equ CFM_HIDDEN
CFE_OUTLINE         equ CFM_OUTLINE
CFE_SHADOW          equ CFM_SHADOW
CFE_EMBOSS          equ CFM_EMBOSS
CFE_IMPRINT         equ CFM_IMPRINT
CFE_DISABLED        equ CFM_DISABLED
CFE_REVISED         equ CFM_REVISED

;; CFE_AUTOCOLOR and CFE_AUTOBACKCOLOR correspond to CFM_COLOR and
;; CFM_BACKCOLOR, respectively, which control them
CFE_AUTOBACKCOLOR   equ CFM_BACKCOLOR

;; Underline types. RE 1.0 displays only CFU_UNDERLINE
CFU_CF1UNDERLINE    equ 0xFF    ;; Map charformat's bit underline to CF2
CFU_INVERT          equ 0xFE    ;; For IME composition fake a selection
CFU_UNDERLINETHICKLONGDASH      equ 18  ;; (*) display as dash
CFU_UNDERLINETHICKDOTTED        equ 17  ;; (*) display as dot
CFU_UNDERLINETHICKDASHDOTDOT    equ 16  ;; (*) display as dash dot dot
CFU_UNDERLINETHICKDASHDOT       equ 15  ;; (*) display as dash dot
CFU_UNDERLINETHICKDASH          equ 14  ;; (*) display as dash
CFU_UNDERLINELONGDASH           equ 13  ;; (*) display as dash
CFU_UNDERLINEHEAVYWAVE          equ 12  ;; (*) display as wave
CFU_UNDERLINEDOUBLEWAVE         equ 11  ;; (*) display as wave
CFU_UNDERLINEHAIRLINE           equ 10  ;; (*) display as single
CFU_UNDERLINETHICK              equ 9
CFU_UNDERLINEWAVE               equ 8
CFU_UNDERLINEDASHDOTDOT         equ 7
CFU_UNDERLINEDASHDOT            equ 6
CFU_UNDERLINEDASH               equ 5
CFU_UNDERLINEDOTTED             equ 4
CFU_UNDERLINEDOUBLE             equ 3   ;; (*) display as single
CFU_UNDERLINEWORD               equ 2   ;; (*) display as single
CFU_UNDERLINE                   equ 1
CFU_UNDERLINENONE               equ 0

yHeightCharPtsMost equ 1638

;; EM_SETCHARFORMAT wParam masks
SCF_SELECTION       equ 0x0001
SCF_WORD            equ 0x0002
SCF_DEFAULT         equ 0x0000  ;; Set default charformat or paraformat
SCF_ALL             equ 0x0004  ;; Not valid with SCF_SELECTION or SCF_WORD
SCF_USEUIRULES      equ 0x0008  ;; Modifier for SCF_SELECTION; says that
                                    ;;  format came from a toolbar, etc., and
                                    ;;  hence UI formatting rules should be
                                    ;;  used instead of literal formatting
SCF_ASSOCIATEFONT   equ 0x0010  ;; Associate fontname with bCharSet (one
                                    ;;  possible for each of Western, ME, FE,
                                    ;;  Thai)
SCF_NOKBUPDATE      equ 0x0020  ;; Do not update KB layput for this change
                                    ;;  even if autokeyboard is on
SCF_ASSOCIATEFONT2  equ 0x0040  ;; Associate plane-2 (surrogate) font

CHARRANGE   STRUC
cpMin       LONG ?
cpMax       LONG ?
CHARRANGE   ENDS

TEXTRANGEA  STRUC
chrg        CHARRANGE <>
lpstrText   LPSTR ?    ;; Allocated by caller, zero terminated by RichEdit
TEXTRANGEA  ENDS
TEXTRANGEW  STRUC
chrg        CHARRANGE <>
lpstrText   LPWSTR ?   ;; Allocated by caller, zero terminated by RichEdit
TEXTRANGEW  ENDS

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
TEXTRANGE   equ <TEXTRANGEW>
else
TEXTRANGE   equ <TEXTRANGEA>
endif ;; UNICODE
else
TEXTRANGE   TEXTRANGEA
endif ;; _RICHEDIT_VER >= 0x0200

CALLBACK(EDITSTREAMCALLBACK, :DWORD_PTR, :LPBYTE, :LONG, :ptr LONG)

EDITSTREAM      STRUC
dwCookie        DWORD_PTR ?     ;; User value passed to callback as first parameter
dwError         DWORD ?         ;; Last error
pfnCallback     PVOID ?         ;; EDITSTREAMCALLBACK
EDITSTREAM      ENDS

;; Stream formats. Flags are all in low word, since high word
;; gives possible codepage choice.
SF_TEXT         equ 0x0001
SF_RTF          equ 0x0002
SF_RTFNOOBJS    equ 0x0003      ;; Write only
SF_TEXTIZED     equ 0x0004      ;; Write only

SF_UNICODE      equ 0x0010      ;; Unicode file (UCS2 little endian)
SF_USECODEPAGE  equ 0x0020      ;; CodePage given by high word
SF_NCRFORNONASCII equ 0x40      ;; Output /uN for nonASCII
SFF_WRITEXTRAPAR  equ 0x80      ;; Output \par at end

;; Flag telling stream operations to operate on selection only
;; EM_STREAMIN  replaces current selection
;; EM_STREAMOUT streams out current selection
SFF_SELECTION   equ 0x8000

;; Flag telling stream operations to ignore some FE control words
;; having to do with FE word breaking and horiz vs vertical text.
;; Not used in RichEdit 2.0 and later
SFF_PLAINRTF    equ 0x4000

;; Flag telling file stream output (SFF_SELECTION flag not set) to persist
;; \viewscaleN control word.
SFF_PERSISTVIEWSCALE equ 0x2000

;; Flag telling file stream input with SFF_SELECTION flag not set not to
;; close the document
SFF_KEEPDOCINFO equ 0x1000

;; Flag telling stream operations to output in Pocket Word format
SFF_PWD         equ 0x0800

;; 3-bit field specifying the value of N - 1 to use for \rtfN or \pwdN
SF_RTFVAL       equ 0x0700

FINDTEXTA       STRUC
chrg            CHARRANGE <>
lpstrText       LPCSTR ?
FINDTEXTA       ENDS

FINDTEXTW       STRUC
chrg            CHARRANGE <>
lpstrText       LPCWSTR ?
FINDTEXTW       ENDS

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
FINDTEXT    equ <FINDTEXTW>
else
FINDTEXT    equ <FINDTEXTA>
endif  ;; UNICODE
else
FINDTEXT    equ <FINDTEXTA>
endif ;; _RICHEDIT_VER >= 0x0200

FINDTEXTEXA     STRUC
chrg            CHARRANGE <>
lpstrText       LPCSTR ?
chrgText        CHARRANGE <>
FINDTEXTEXA     ENDS

FINDTEXTEXW     STRUC
chrg            CHARRANGE <>
lpstrText       LPCWSTR ?
chrgText        CHARRANGE <>
FINDTEXTEXW     ENDS

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
FINDTEXTEX  equ <FINDTEXTEXW>
else
FINDTEXTEX  equ <FINDTEXTEXA>
endif ;; UNICODE
else
FINDTEXTEX  equ <FINDTEXTEXA>
endif ;; _RICHEDIT_VER >= 0x0200


FORMATRANGE     STRUC
hdc             HDC ?
hdcTarget       HDC ?
rc              RECT <>
rcPage          RECT <>
chrg            CHARRANGE <>
FORMATRANGE     ENDS

;; All paragraph measurements are in twips

MAX_TAB_STOPS   equ 32
lDefaultTab     equ 720
MAX_TABLE_CELLS equ 63

PARAFORMAT      STRUC
cbSize          UINT ?
dwMask          DWORD ?
wNumbering      WORD ?
wEffects        WORD ?
dxStartIndent   LONG ?
dxRightIndent   LONG ?
dxOffset        LONG ?
wAlignment      WORD ?
cTabCount       SWORD ?
rgxTabs         LONG MAX_TAB_STOPS dup(?)
PARAFORMAT      ENDS

PARAFORMAT2     STRUC
cbSize          UINT ?
dwMask          DWORD ?
wNumbering      WORD ?
wReserved       WORD ?
dxStartIndent   LONG ?
dxRightIndent   LONG ?
dxOffset        LONG ?
wAlignment      WORD ?
cTabCount       SWORD ?
rgxTabs         LONG MAX_TAB_STOPS dup(?)
dySpaceBefore   LONG ?        ;; Vertical spacing before para
dySpaceAfter    LONG ?        ;; Vertical spacing after para
dyLineSpacing   LONG ?        ;; Line spacing depending on Rule
sStyle          SWORD ?       ;; Style handle
bLineSpacingRule BYTE ?       ;; Rule for line spacing (see tom.doc)
bOutlineLevel   BYTE ?        ;; Outline Level
wShadingWeight  WORD ?        ;; Shading in hundredths of a per cent
wShadingStyle   WORD ?        ;; Byte 0: style, nib 2: cfpat, 3: cbpat
wNumberingStart WORD ?        ;; Starting value for numbering
wNumberingStyle WORD ?        ;; Alignment, Roman/Arabic, (), ), ., etc.
wNumberingTab   WORD ?        ;; Space bet 1st indent and 1st-line text
wBorderSpace    WORD ?        ;; Border-text spaces (nbl/bdr in pts)
wBorderWidth    WORD ?        ;; Pen widths (nbl/bdr in half twips)
wBorders        WORD ?        ;; Border styles (nibble/border)
PARAFORMAT2     ENDS


;; PARAFORMAT mask values
PFM_STARTINDENT         equ 0x00000001
PFM_RIGHTINDENT         equ 0x00000002
PFM_OFFSET              equ 0x00000004
PFM_ALIGNMENT           equ 0x00000008
PFM_TABSTOPS            equ 0x00000010
PFM_NUMBERING           equ 0x00000020
PFM_OFFSETINDENT        equ 0x80000000

;; PARAFORMAT 2.0 masks and effects
PFM_SPACEBEFORE         equ 0x00000040
PFM_SPACEAFTER          equ 0x00000080
PFM_LINESPACING         equ 0x00000100
PFM_STYLE               equ 0x00000400
PFM_BORDER              equ 0x00000800  ;; (*)
PFM_SHADING             equ 0x00001000  ;; (*)
PFM_NUMBERINGSTYLE      equ 0x00002000  ;; RE 3.0
PFM_NUMBERINGTAB        equ 0x00004000  ;; RE 3.0
PFM_NUMBERINGSTART      equ 0x00008000  ;; RE 3.0

PFM_RTLPARA             equ 0x00010000
PFM_KEEP                equ 0x00020000  ;; (*)
PFM_KEEPNEXT            equ 0x00040000  ;; (*)
PFM_PAGEBREAKBEFORE     equ 0x00080000  ;; (*)
PFM_NOLINENUMBER        equ 0x00100000  ;; (*)
PFM_NOWIDOWCONTROL      equ 0x00200000  ;; (*)
PFM_DONOTHYPHEN         equ 0x00400000  ;; (*)
PFM_SIDEBYSIDE          equ 0x00800000  ;; (*)
PFM_TABLE               equ 0x40000000  ;; RE 3.0
PFM_TEXTWRAPPINGBREAK   equ 0x20000000  ;; RE 3.0
PFM_TABLEROWDELIMITER   equ 0x10000000  ;; RE 4.0

;; The following three properties are read only
PFM_COLLAPSED           equ 0x01000000  ;; RE 3.0
PFM_OUTLINELEVEL        equ 0x02000000  ;; RE 3.0
PFM_BOX                 equ 0x04000000  ;; RE 3.0
PFM_RESERVED2           equ 0x08000000  ;; RE 4.0


;; PARAFORMAT "ALL" masks
PFM_ALL     equ (PFM_STARTINDENT or PFM_RIGHTINDENT or PFM_OFFSET or \
                 PFM_ALIGNMENT   or PFM_TABSTOPS    or PFM_NUMBERING or \
                 PFM_OFFSETINDENT or PFM_RTLPARA)

;; Note: PARAFORMAT has no effects (BiDi RichEdit 1.0 does have PFE_RTLPARA)
PFM_EFFECTS equ (PFM_RTLPARA or PFM_KEEP or PFM_KEEPNEXT or PFM_TABLE \
                    or PFM_PAGEBREAKBEFORE or PFM_NOLINENUMBER  \
                    or PFM_NOWIDOWCONTROL or PFM_DONOTHYPHEN or PFM_SIDEBYSIDE \
                    or PFM_TABLE or PFM_TABLEROWDELIMITER)

PFM_ALL2    equ (PFM_ALL or PFM_EFFECTS or PFM_SPACEBEFORE or PFM_SPACEAFTER \
                    or PFM_LINESPACING or PFM_STYLE or PFM_SHADING or PFM_BORDER \
                    or PFM_NUMBERINGTAB or PFM_NUMBERINGSTART or PFM_NUMBERINGSTYLE)

PFE_RTLPARA             equ (PFM_RTLPARA         shr 16)
PFE_KEEP                equ (PFM_KEEP            shr 16) ;; (*)
PFE_KEEPNEXT            equ (PFM_KEEPNEXT        shr 16) ;; (*)
PFE_PAGEBREAKBEFORE     equ (PFM_PAGEBREAKBEFORE shr 16) ;; (*)
PFE_NOLINENUMBER        equ (PFM_NOLINENUMBER    shr 16) ;; (*)
PFE_NOWIDOWCONTROL      equ (PFM_NOWIDOWCONTROL  shr 16) ;; (*)
PFE_DONOTHYPHEN         equ (PFM_DONOTHYPHEN     shr 16) ;; (*)
PFE_SIDEBYSIDE          equ (PFM_SIDEBYSIDE      shr 16) ;; (*)
PFE_TEXTWRAPPINGBREAK   equ (PFM_TEXTWRAPPINGBREAK shr 16) ;; (*)

;; The following four effects are read only
PFE_COLLAPSED           equ (PFM_COLLAPSED       shr 16) ;; (+)
PFE_BOX                 equ (PFM_BOX             shr 16) ;; (+)
PFE_TABLE               equ (PFM_TABLE           shr 16) ;; Inside table row. RE 3.0
PFE_TABLEROWDELIMITER   equ (PFM_TABLEROWDELIMITER shr 16) ;; Table row start. RE 4.0

;; PARAFORMAT numbering options
PFN_BULLET      equ 1       ;; tomListBullet

;; PARAFORMAT2 wNumbering options
PFN_ARABIC      equ 2       ;; tomListNumberAsArabic:   0, 1, 2,    ...
PFN_LCLETTER    equ 3       ;; tomListNumberAsLCLetter: a, b, c,    ...
PFN_UCLETTER    equ 4       ;; tomListNumberAsUCLetter: A, B, C,    ...
PFN_LCROMAN     equ 5       ;; tomListNumberAsLCRoman:  i, ii, iii, ...
PFN_UCROMAN     equ 6       ;; tomListNumberAsUCRoman:  I, II, III, ...

;; PARAFORMAT2 wNumberingStyle options
PFNS_PAREN      equ 0x000   ;; default, e.g.,                 1)
PFNS_PARENS     equ 0x100   ;; tomListParentheses/256, e.g., (1)
PFNS_PERIOD     equ 0x200   ;; tomListPeriod/256, e.g.,       1.
PFNS_PLAIN      equ 0x300   ;; tomListPlain/256, e.g.,        1
PFNS_NONUMBER   equ 0x400   ;; Used for continuation w/o number

PFNS_NEWNUMBER  equ 0x8000  ;; Start new number with wNumberingStart
                                ;; (can be combined with other PFNS_xxx)
;; PARAFORMAT alignment options
PFA_LEFT             equ 1
PFA_RIGHT            equ 2
PFA_CENTER           equ 3

;; PARAFORMAT2 alignment options
PFA_JUSTIFY          equ 4  ;; New paragraph-alignment option 2.0 (*)
PFA_FULL_INTERWORD   equ 4  ;; These are supported in 3.0 with advanced
PFA_FULL_INTERLETTER equ 5  ;;  typography enabled
PFA_FULL_SCALED      equ 6
PFA_FULL_GLYPHS      equ 7
PFA_SNAP_GRID        equ 8


;; Notification structures
ifndef WM_NOTIFY
WM_NOTIFY   equ 0x004E
NMHDR       STRUC
hwndFrom    HWND ?
idFrom      UINT ?
_code       UINT ?
NMHDR       ENDS
endif  ;; !WM_NOTIFY

MSGFILTER   STRUC
nmhdr       NMHDR <>
msg         UINT ?
wParam      WPARAM ?
lParam      LPARAM ?
MSGFILTER   ENDS

REQRESIZE   STRUC
nmhdr       NMHDR <>
rc          RECT <>
REQRESIZE   ENDS

SELCHANGE   STRUC
nmhdr       NMHDR <>
chrg        CHARRANGE <>
seltyp      WORD ?
SELCHANGE   ENDS


SEL_EMPTY       equ 0x0000
SEL_TEXT        equ 0x0001
SEL_OBJECT      equ 0x0002
SEL_MULTICHAR   equ 0x0004
SEL_MULTIOBJECT equ 0x0008

;; Used with IRichEditOleCallback::GetContextMenu, this flag will be
;; passed as a "selection type".  It indicates that a context menu for
;; a right-mouse drag drop should be generated.  The IOleObject parameter
;; will really be the IDataObject for the drop
GCM_RIGHTMOUSEDROP  equ 0x8000

ENDROPFILES STRUC
nmhdr       NMHDR <>
hDrop       HANDLE ?
cp          LONG ?
fProtected  BOOL ?
ENDROPFILES ENDS

ENPROTECTED STRUC
nmhdr       NMHDR <>
msg         UINT ?
wParam      WPARAM ?
lParam      LPARAM ?
chrg        CHARRANGE <>
ENPROTECTED ENDS

ENSAVECLIPBOARD STRUC
nmhdr           NMHDR <>
cObjectCount    LONG ?
cch             LONG ?
ENSAVECLIPBOARD ENDS

ifndef MACPORT
ENOLEOPFAILED   STRUC
nmhdr           NMHDR <>
iob             LONG ?
lOper           LONG ?
hr              HRESULT ?
ENOLEOPFAILED   ENDS
endif

OLEOP_DOVERB    equ 1

OBJECTPOSITIONS STRUC
nmhdr           NMHDR <>
cObjectCount    LONG ?
pcpPositions    LPDWORD ?
OBJECTPOSITIONS ENDS

ENLINK          STRUC
nmhdr           NMHDR <>
msg             UINT ?
wParam          WPARAM ?
lParam          LPARAM ?
chrg            CHARRANGE <>
ENLINK          ENDS

ENLOWFIRTF      STRUC
nmhdr           NMHDR <>
szControl       LPSTR ?
ENLOWFIRTF      ENDS

;; PenWin specific
ENCORRECTTEXT   STRUC
nmhdr           NMHDR <>
chrg            CHARRANGE <>
seltyp          WORD ?
ENCORRECTTEXT   ENDS

;; East Asia specific
PUNCTUATION     STRUC
iSize           UINT ?
szPunctuation   LPSTR ?
PUNCTUATION     ENDS

;; East Asia specific
COMPCOLOR       STRUC
crText          COLORREF ?
crBackground    COLORREF ?
dwEffects       DWORD ?
COMPCOLOR       ENDS


;; Clipboard formats - use as parameter to RegisterClipboardFormat()
CF_RTF          equ <"Rich Text Format">
CF_RTFNOOBJS    equ <"Rich Text Format Without Objects">
CF_RETEXTOBJ    equ <"RichEdit Text and Objects">

;; Paste Special
REPASTESPECIAL  STRUC
dwAspect        DWORD ?
dwParam         LPDWORD ?
REPASTESPECIAL  ENDS

;;  UndoName info
;;typedef enum _undonameid
UID_UNKNOWN     equ 0
UID_TYPING      equ 1
UID_DELETE      equ 2
UID_DRAGDROP    equ 3
UID_CUT         equ 4
UID_PASTE       equ 5
UID_AUTOCORRECT equ 6
;;} UNDONAMEID;

;; Flags for the SETEXTEX data structure
ST_DEFAULT      equ 0
ST_KEEPUNDO     equ 1
ST_SELECTION    equ 2
ST_NEWCHARS     equ 4

;; EM_SETTEXTEX info; this struct is passed in the wparam of the message
SETTEXTEX       STRUC
flags           DWORD ?     ;; Flags (see the ST_XXX defines)
codepage        UINT ?      ;; Code page for translation (CP_ACP for sys default,
SETTEXTEX       ENDS        ;;  1200 for Unicode, -1 for control default)

;; Flags for the GETEXTEX data structure
GT_DEFAULT      equ 0
GT_USECRLF      equ 1
GT_SELECTION    equ 2
GT_RAWTEXT      equ 4
GT_NOHIDDENTEXT equ 8

;; EM_GETTEXTEX info; this struct is passed in the wparam of the message
GETTEXTEX       STRUC
cb              DWORD ?     ;; Count of bytes in the string
flags           DWORD ?     ;; Flags (see the GT_XXX defines
codepage        UINT ?      ;; Code page for translation (CP_ACP for sys default,
                            ;;  1200 for Unicode, -1 for control default)
lpDefaultChar   LPCSTR ?    ;; Replacement for unmappable chars
lpUsedDefChar   LPBOOL ?    ;; Pointer to flag set when def char used
GETTEXTEX       ENDS

;; Flags for the GETTEXTLENGTHEX data structure
GTL_DEFAULT     equ 0   ;; Do default (return # of chars)
GTL_USECRLF     equ 1   ;; Compute answer using CRLFs for paragraphs
GTL_PRECISE     equ 2   ;; Compute a precise answer
GTL_CLOSE       equ 4   ;; Fast computation of a "close" answer
GTL_NUMCHARS    equ 8   ;; Return number of characters
GTL_NUMBYTES    equ 16  ;; Return number of _bytes_

;; EM_GETTEXTLENGTHEX info; this struct is passed in the wparam of the msg
GETTEXTLENGTHEX STRUC
flags           DWORD ?     ;; Flags (see GTL_XXX defines)
codepage        UINT ?      ;; Code page for translation (CP_ACP for default,
GETTEXTLENGTHEX ENDS        ;;  1200 for Unicode)

;; BiDi specific features
BIDIOPTIONS     STRUC
cbSize          UINT ?
wMask           WORD ?
wEffects        WORD ?
BIDIOPTIONS     ENDS

;; BIDIOPTIONS masks
if (_RICHEDIT_VER eq 0x0100)
BOM_DEFPARADIR          equ 0x0001  ;; Default paragraph direction (implies alignment) (obsolete)
BOM_PLAINTEXT           equ 0x0002  ;; Use plain text layout (obsolete)
endif ;; _RICHEDIT_VER == 0x0100
BOM_NEUTRALOVERRIDE     equ 0x0004  ;; Override neutral layout (obsolete)
BOM_CONTEXTREADING      equ 0x0008  ;; Context reading order
BOM_CONTEXTALIGNMENT    equ 0x0010  ;; Context alignment
BOM_LEGACYBIDICLASS     equ 0x0040  ;; Legacy Bidi classification

;; BIDIOPTIONS effects
if (_RICHEDIT_VER eq 0x0100)
BOE_RTLDIR              equ 0x0001  ;; Default paragraph direction (implies alignment) (obsolete)
BOE_PLAINTEXT           equ 0x0002  ;; Use plain text layout (obsolete)
endif ;; _RICHEDIT_VER == 0x0100
BOE_NEUTRALOVERRIDE     equ 0x0004  ;; Override neutral layout (obsolete)
BOE_CONTEXTREADING      equ 0x0008  ;; Context reading order
BOE_CONTEXTALIGNMENT    equ 0x0010  ;; Context alignment
BOE_LEGACYBIDICLASS     equ 0x0040  ;; Legacy Bidi classification

;; Additional EM_FINDTEXT[EX] flags
FR_MATCHDIAC            equ 0x20000000
FR_MATCHKASHIDA         equ 0x40000000
FR_MATCHALEFHAMZA       equ 0x80000000

;; UNICODE embedding character
ifndef WCH_EMBEDDING
WCH_EMBEDDING           equ 0xFFFC
endif ;; WCH_EMBEDDING

;; khyph - Kind of hyphenation
;; typedef enum tagKHYPH
khyphNil                equ 0   ;; No Hyphenation
khyphNormal             equ 1   ;; Normal Hyphenation
khyphAddBefore          equ 2   ;; Add letter before hyphen
khyphChangeBefore       equ 3   ;; Change letter before hyphen
khyphDeleteBefore       equ 4   ;; Delete letter before hyphen
khyphChangeAfter        equ 5   ;; Change letter after hyphen
khyphDelAndChange       equ 6   ;; Delete letter before hyphen and change
                                ;;  letter preceding hyphen
; KHYPH

HYPHRESULT      STRUC
khyph           DWORD ?     ;; Kind of hyphenation
ichHyph         LONG ?      ;; Character which was hyphenated
chHyph          WCHAR ?     ;; Depending on hyphenation type, character added, changed, etc.
HYPHRESULT      ENDS

HyphenateProc proto WINAPI \
           pszWord: ptr WCHAR,
            langid: LANGID,
         ichExceed: LONG,
       phyphresult: ptr HYPHRESULT

HYPHENATEINFO   STRUC
cbSize          SWORD ?     ;; Size of HYPHENATEINFO structure
dxHyphenateZone SWORD ?     ;; If a space character is closer to the margin
                            ;;  than this value, don't hyphenate (in TWIPs)
pfnHyphenate    PVOID ?     ;; (WCHAR*, LANGID, long, HYPHRESULT*);
HYPHENATEINFO   ENDS

.list
endif ; !_RICHEDIT_


