.pragma list(push, 0)
ifndef _RICHEDIT_
define _RICHEDIT_

include winapifamily.inc
include windows.inc
include wtypes.inc
include objbase.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.pragma pack(push, 4)

ifndef _RICHEDIT_VER
define _RICHEDIT_VER	0x0810
endif

define cchTextLimitDefault 32767

define MSFTEDIT_CLASS		<L"RICHEDIT50W">

define CERICHEDIT_CLASSA	<"RichEditCEA">
define CERICHEDIT_CLASSW	<L"RichEditCEW">

define RICHEDIT_CLASSA		<"RichEdit20A">
define RICHEDIT_CLASS10A	<"RICHEDIT">

ifndef MACPORT
define RICHEDIT_CLASSW		<L"RichEdit20W">
else
define RICHEDIT_CLASSW		<"RichEdit20W">
endif

if (_RICHEDIT_VER ge 0x0200 )
ifdef _UNICODE
define RICHEDIT_CLASS		<RICHEDIT_CLASSW>
else
define RICHEDIT_CLASS		<RICHEDIT_CLASSA>
endif
else
define RICHEDIT_CLASS		RICHEDIT_CLASS10A
endif

ifndef WM_CONTEXTMENU
define WM_CONTEXTMENU		0x007B
endif

ifndef WM_UNICHAR
define WM_UNICHAR		0x0109
endif

ifndef WM_PRINTCLIENT
define WM_PRINTCLIENT		0x0318
endif

ifndef EM_GETLIMITTEXT
define EM_GETLIMITTEXT		(WM_USER + 37)
endif

ifndef EM_POSFROMCHAR
define EM_POSFROMCHAR		(WM_USER + 38)
define EM_CHARFROMPOS		(WM_USER + 39)
endif

ifndef EM_SCROLLCARET
define EM_SCROLLCARET		(WM_USER + 49)
endif
define EM_CANPASTE		(WM_USER + 50)
define EM_DISPLAYBAND		(WM_USER + 51)
define EM_EXGETSEL		(WM_USER + 52)
define EM_EXLIMITTEXT		(WM_USER + 53)
define EM_EXLINEFROMCHAR	(WM_USER + 54)
define EM_EXSETSEL		(WM_USER + 55)
define EM_FINDTEXT		(WM_USER + 56)
define EM_FORMATRANGE		(WM_USER + 57)
define EM_GETCHARFORMAT		(WM_USER + 58)
define EM_GETEVENTMASK		(WM_USER + 59)
define EM_GETOLEINTERFACE	(WM_USER + 60)
define EM_GETPARAFORMAT		(WM_USER + 61)
define EM_GETSELTEXT		(WM_USER + 62)
define EM_HIDESELECTION		(WM_USER + 63)
define EM_PASTESPECIAL		(WM_USER + 64)
define EM_REQUESTRESIZE		(WM_USER + 65)
define EM_SELECTIONTYPE		(WM_USER + 66)
define EM_SETBKGNDCOLOR		(WM_USER + 67)
define EM_SETCHARFORMAT		(WM_USER + 68)
define EM_SETEVENTMASK		(WM_USER + 69)
define EM_SETOLECALLBACK	(WM_USER + 70)
define EM_SETPARAFORMAT		(WM_USER + 71)
define EM_SETTARGETDEVICE	(WM_USER + 72)
define EM_STREAMIN		(WM_USER + 73)
define EM_STREAMOUT		(WM_USER + 74)
define EM_GETTEXTRANGE		(WM_USER + 75)
define EM_FINDWORDBREAK		(WM_USER + 76)
define EM_SETOPTIONS		(WM_USER + 77)
define EM_GETOPTIONS		(WM_USER + 78)
define EM_FINDTEXTEX		(WM_USER + 79)
ifdef _WIN32
define EM_GETWORDBREAKPROCEX	(WM_USER + 80)
define EM_SETWORDBREAKPROCEX	(WM_USER + 81)
endif

define EM_SETUNDOLIMIT		(WM_USER + 82)
define EM_REDO			(WM_USER + 84)
define EM_CANREDO		(WM_USER + 85)
define EM_GETUNDONAME		(WM_USER + 86)
define EM_GETREDONAME		(WM_USER + 87)
define EM_STOPGROUPTYPING	(WM_USER + 88)

define EM_SETTEXTMODE		(WM_USER + 89)
define EM_GETTEXTMODE		(WM_USER + 90)

.enum TEXTMODE {
    TM_PLAINTEXT		= 1,
    TM_RICHTEXT			= 2,
    TM_SINGLELEVELUNDO		= 4,
    TM_MULTILEVELUNDO		= 8,
    TM_SINGLECODEPAGE		= 16,
    TM_MULTICODEPAGE		= 32
    }

define EM_AUTOURLDETECT		(WM_USER + 91)

if (_RICHEDIT_VER ge 0x0800)
define	AURL_ENABLEURL		1
define	AURL_ENABLEEMAILADDR	2
define	AURL_ENABLETELNO	4
define	AURL_ENABLEEAURLS	8
define	AURL_ENABLEDRIVELETTERS 16
define	AURL_DISABLEMIXEDLGC	32
endif

define EM_GETAUTOURLDETECT	(WM_USER + 92)
define EM_SETPALETTE		(WM_USER + 93)
define EM_GETTEXTEX		(WM_USER + 94)
define EM_GETTEXTLENGTHEX	(WM_USER + 95)
define EM_SHOWSCROLLBAR		(WM_USER + 96)
define EM_SETTEXTEX		(WM_USER + 97)

define EM_SETPUNCTUATION	(WM_USER + 100)
define EM_GETPUNCTUATION	(WM_USER + 101)
define EM_SETWORDWRAPMODE	(WM_USER + 102)
define EM_GETWORDWRAPMODE	(WM_USER + 103)
define EM_SETIMECOLOR		(WM_USER + 104)
define EM_GETIMECOLOR		(WM_USER + 105)
define EM_SETIMEOPTIONS		(WM_USER + 106)
define EM_GETIMEOPTIONS		(WM_USER + 107)
define EM_CONVPOSITION		(WM_USER + 108)

define EM_SETLANGOPTIONS	(WM_USER + 120)
define EM_GETLANGOPTIONS	(WM_USER + 121)
define EM_GETIMECOMPMODE	(WM_USER + 122)

define EM_FINDTEXTW		(WM_USER + 123)
define EM_FINDTEXTEXW		(WM_USER + 124)

define EM_RECONVERSION		(WM_USER + 125)
define EM_SETIMEMODEBIAS	(WM_USER + 126)
define EM_GETIMEMODEBIAS	(WM_USER + 127)

define EM_SETBIDIOPTIONS	(WM_USER + 200)
define EM_GETBIDIOPTIONS	(WM_USER + 201)

define EM_SETTYPOGRAPHYOPTIONS	(WM_USER + 202)
define EM_GETTYPOGRAPHYOPTIONS	(WM_USER + 203)

define EM_SETEDITSTYLE		(WM_USER + 204)
define EM_GETEDITSTYLE		(WM_USER + 205)

define SES_EMULATESYSEDIT	1
define SES_BEEPONMAXTEXT	2
define SES_EXTENDBACKCOLOR	4
define SES_MAPCPS		8
if (_RICHEDIT_VER ge 0x0500)
define SES_HYPERLINKTOOLTIPS	8
endif
define SES_EMULATE10		16
if (_RICHEDIT_VER ge 0x0700)
define SES_DEFAULTLATINLIGA	16
endif
define SES_USECRLF		32
if (_RICHEDIT_VER ge 0x0700)
define SES_NOFOCUSLINKNOTIFY	32
endif
define SES_USEAIMM		64
define SES_NOIME		128

define SES_ALLOWBEEPS		256
define SES_UPPERCASE		512
define SES_LOWERCASE		1024
define SES_NOINPUTSEQUENCECHK	2048
define SES_BIDI			4096
define SES_SCROLLONKILLFOCUS	8192
define SES_XLTCRCRLFTOCR	16384
define SES_DRAFTMODE		32768

define SES_USECTF		0x00010000
define SES_HIDEGRIDLINES	0x00020000
define SES_USEATFONT		0x00040000
define SES_CUSTOMLOOK		0x00080000
define SES_LBSCROLLNOTIFY	0x00100000
define SES_CTFALLOWEMBED	0x00200000
define SES_CTFALLOWSMARTTAG	0x00400000
define SES_CTFALLOWPROOFING	0x00800000
if (_RICHEDIT_VER ge 0x0500)
define SES_LOGICALCARET		0x01000000
define SES_WORDDRAGDROP		0x02000000
define SES_SMARTDRAGDROP	0x04000000
define SES_MULTISELECT		0x08000000
define SES_CTFNOLOCK		0x10000000
define SES_NOEALINEHEIGHTADJUST 0x20000000
define SES_MAX			0x20000000
endif

define IMF_AUTOKEYBOARD		0x0001
define IMF_AUTOFONT		0x0002
define IMF_IMECANCELCOMPLETE	0x0004
define IMF_IMEALWAYSSENDNOTIFY	0x0008
define IMF_AUTOFONTSIZEADJUST	0x0010
define IMF_UIFONTS		0x0020
if (_RICHEDIT_VER ge 0x0800)
define IMF_NOIMPLICITLANG	0x0040
endif
define IMF_DUALFONT		0x0080
if (_RICHEDIT_VER ge 0x0800)
define IMF_NOKBDLIDFIXUP	0x0200
endif
define IMF_NORTFFONTSUBSTITUTE	0x0400
if (_RICHEDIT_VER ge 0x0800)
define IMF_SPELLCHECKING	0x0800
define IMF_TKBPREDICTION	0x1000
endif
if (_RICHEDIT_VER ge 0x0810)
define IMF_IMEUIINTEGRATION	0x2000
endif

define ICM_NOTOPEN		0x0000
define ICM_LEVEL3		0x0001
define ICM_LEVEL2		0x0002
define ICM_LEVEL2_5		0x0003
define ICM_LEVEL2_SUI		0x0004
define ICM_CTF			0x0005

define TO_ADVANCEDTYPOGRAPHY	0x0001
define TO_SIMPLELINEBREAK	0x0002
define TO_DISABLECUSTOMTEXTOUT	0x0004
define TO_ADVANCEDLAYOUT	0x0008

define EM_OUTLINE		(WM_USER + 220)
define EM_GETSCROLLPOS		(WM_USER + 221)
define EM_SETSCROLLPOS		(WM_USER + 222)
define EM_SETFONTSIZE		(WM_USER + 223)
define EM_GETZOOM		(WM_USER + 224)
define EM_SETZOOM		(WM_USER + 225)
define EM_GETVIEWKIND		(WM_USER + 226)
define EM_SETVIEWKIND		(WM_USER + 227)

define EM_GETPAGE		(WM_USER + 228)
define EM_SETPAGE		(WM_USER + 229)
define EM_GETHYPHENATEINFO	(WM_USER + 230)
define EM_SETHYPHENATEINFO	(WM_USER + 231)

define EM_GETPAGEROTATE		(WM_USER + 235)
define EM_SETPAGEROTATE		(WM_USER + 236)
define EM_GETCTFMODEBIAS	(WM_USER + 237)
define EM_SETCTFMODEBIAS	(WM_USER + 238)
define EM_GETCTFOPENSTATUS	(WM_USER + 240)
define EM_SETCTFOPENSTATUS	(WM_USER + 241)
define EM_GETIMECOMPTEXT	(WM_USER + 242)
define EM_ISIME			(WM_USER + 243)
define EM_GETIMEPROPERTY	(WM_USER + 244)

define EM_GETQUERYRTFOBJ	(WM_USER + 269)
define EM_SETQUERYRTFOBJ	(WM_USER + 270)

define EPR_0			0
define EPR_270			1
define EPR_180			2
define EPR_90			3
if (_RICHEDIT_VER ge 0x0800)
define EPR_SE			5
endif

define CTFMODEBIAS_DEFAULT	0x0000
define CTFMODEBIAS_FILENAME	0x0001
define CTFMODEBIAS_NAME		0x0002
define CTFMODEBIAS_READING	0x0003
define CTFMODEBIAS_DATETIME	0x0004
define CTFMODEBIAS_CONVERSATION 0x0005
define CTFMODEBIAS_NUMERIC	0x0006
define CTFMODEBIAS_HIRAGANA	0x0007
define CTFMODEBIAS_KATAKANA	0x0008
define CTFMODEBIAS_HANGUL	0x0009
define CTFMODEBIAS_HALFWIDTHKATAKANA		0x000A
define CTFMODEBIAS_FULLWIDTHALPHANUMERIC	0x000B
define CTFMODEBIAS_HALFWIDTHALPHANUMERIC	0x000C

define IMF_SMODE_PLAURALCLAUSE	0x0001
define IMF_SMODE_NONE		0x0002

_imecomptext		struct
cb			LONG ?
flags			DWORD ?
_imecomptext		ends
IMECOMPTEXT		typedef _imecomptext
define ICT_RESULTREADSTR	1

define EMO_EXIT			0
define EMO_ENTER		1
define EMO_PROMOTE		2
define EMO_EXPAND		3
define EMO_MOVESELECTION	4
define EMO_GETVIEWMODE		5

define EMO_EXPANDSELECTION	0
define EMO_EXPANDDOCUMENT	1

define VM_NORMAL		4
define VM_OUTLINE		2
define VM_PAGE			9

if (_RICHEDIT_VER ge 0x0800)

define EM_INSERTTABLE		(WM_USER + 232)

_tableRowParms		struct
cbRow			BYTE ?
cbCell			BYTE ?
cCell			BYTE ?
cRow			BYTE ?
dxCellMargin		LONG ?
dxIndent		LONG ?
dyHeight		LONG ?
record flags
 nAlignment		DWORD : 3 ?
 fRTL			DWORD : 1 ?
 fKeep			DWORD : 1 ?
 fKeepFollow		DWORD : 1 ?
 fWrap			DWORD : 1 ?
 fIdentCells		DWORD : 1 ?
ends
cpStartRow		LONG ?
bTableLevel		BYTE ?
iCell			BYTE ?
_tableRowParms		ends
TABLEROWPARMS		typedef _tableRowParms

_tableCellParms		struct
dxWidth			LONG ?
record flags
 nVertAlign		WORD : 2 ?
 fMergeTop		WORD : 1 ?
 fMergePrev		WORD : 1 ?
 fVertical		WORD : 1 ?
 fMergeStart		WORD : 1 ?
 fMergeCont		WORD : 1 ?
ends
wShading		WORD ?
dxBrdrLeft		sword ?
dyBrdrTop		sword ?
dxBrdrRight		sword ?
dyBrdrBottom		sword ?
crBrdrLeft		COLORREF ?
crBrdrTop		COLORREF ?
crBrdrRight		COLORREF ?
crBrdrBottom		COLORREF ?
crBackPat		COLORREF ?
crForePat		COLORREF ?
_tableCellParms		ends
TABLECELLPARMS		typedef _tableCellParms


define EM_GETAUTOCORRECTPROC	(WM_USER + 233)
define EM_SETAUTOCORRECTPROC	(WM_USER + 234)
define EM_CALLAUTOCORRECTPROC	(WM_USER + 255)

CALLBACK(AutoCorrectProc, :LANGID, :ptr, :ptr, :LONG, :ptr)

define ATP_NOCHANGE		0
define ATP_CHANGE		1
define ATP_NODELIMITER		2
define ATP_REPLACEALLTEXT	4

define EM_GETTABLEPARMS		(WM_USER + 265)

define EM_SETEDITSTYLEEX	(WM_USER + 275)
define EM_GETEDITSTYLEEX	(WM_USER + 276)
define SES_EX_NOTABLE		0x00000004
define SES_EX_NOMATH		0x00000040
define SES_EX_HANDLEFRIENDLYURL 0x00000100
define SES_EX_NOTHEMING		0x00080000
define SES_EX_NOACETATESELECTION 0x00100000
define SES_EX_USESINGLELINE	0x00200000
define SES_EX_MULTITOUCH	0x08000000
define SES_EX_HIDETEMPFORMAT	0x10000000
define SES_EX_USEMOUSEWPARAM	0x20000000

define EM_GETSTORYTYPE		(WM_USER + 290)
define EM_SETSTORYTYPE		(WM_USER + 291)

define EM_GETELLIPSISMODE	(WM_USER + 305)
define EM_SETELLIPSISMODE	(WM_USER + 306)

define ELLIPSIS_MASK		0x00000003
define ELLIPSIS_NONE		0x00000000
define ELLIPSIS_END		0x00000001
define ELLIPSIS_WORD		0x00000003

define EM_SETTABLEPARMS		(WM_USER + 307)

define EM_GETTOUCHOPTIONS	(WM_USER + 310)
define EM_SETTOUCHOPTIONS	(WM_USER + 311)
define EM_INSERTIMAGE		(WM_USER + 314)
define EM_SETUIANAME		(WM_USER + 320)
define EM_GETELLIPSISSTATE	(WM_USER + 322)

define RTO_SHOWHANDLES		1
define RTO_DISABLEHANDLES	2
define RTO_READINGMODE		3

tagRICHEDIT_IMAGE_PARAMETERS struct
xWidth			LONG ?
yHeight			LONG ?
Ascent			LONG ?
Type			LONG ?
pwszAlternateText	LPCWSTR ?
pIStream		ptr IStream ?
tagRICHEDIT_IMAGE_PARAMETERS ends
RICHEDIT_IMAGE_PARAMETERS typedef tagRICHEDIT_IMAGE_PARAMETERS

endif

define EN_MSGFILTER		0x0700
define EN_REQUESTRESIZE		0x0701
define EN_SELCHANGE		0x0702
define EN_DROPFILES		0x0703
define EN_PROTECTED		0x0704
define EN_CORRECTTEXT		0x0705
define EN_STOPNOUNDO		0x0706
define EN_IMECHANGE		0x0707
define EN_SAVECLIPBOARD		0x0708
define EN_OLEOPFAILED		0x0709
define EN_OBJECTPOSITIONS	0x070a
define EN_LINK			0x070b
define EN_DRAGDROPDONE		0x070c
define EN_PARAGRAPHEXPANDED	0x070d
define EN_PAGECHANGE		0x070e
define EN_LOWFIRTF		0x070f
define EN_ALIGNLTR		0x0710
define EN_ALIGNRTL		0x0711
if (_RICHEDIT_VER ge 0x0800)
define EN_CLIPFORMAT		0x0712
define EN_STARTCOMPOSITION	0x0713
define EN_ENDCOMPOSITION	0x0714

_endcomposition		struct
nmhdr			NMHDR <>
dwCode			DWORD ?
_endcomposition		ends
ENDCOMPOSITIONNOTIFY	typedef _endcomposition

define ECN_ENDCOMPOSITION	0x0001
define ECN_NEWTEXT		0x0002
endif

define ENM_NONE			0x00000000
define ENM_CHANGE		0x00000001
define ENM_UPDATE		0x00000002
define ENM_SCROLL		0x00000004
define ENM_SCROLLEVENTS		0x00000008
define ENM_DRAGDROPDONE		0x00000010
define ENM_PARAGRAPHEXPANDED	0x00000020
define ENM_PAGECHANGE		0x00000040
if (_RICHEDIT_VER ge 0x0800)
define ENM_CLIPFORMAT		0x00000080
endif
define ENM_KEYEVENTS		0x00010000
define ENM_MOUSEEVENTS		0x00020000
define ENM_REQUESTRESIZE	0x00040000
define ENM_SELCHANGE		0x00080000
define ENM_DROPFILES		0x00100000
define ENM_PROTECTED		0x00200000
define ENM_CORRECTTEXT		0x00400000
define ENM_IMECHANGE		0x00800000
define ENM_LANGCHANGE		0x01000000
define ENM_OBJECTPOSITIONS	0x02000000
define ENM_LINK			0x04000000
define ENM_LOWFIRTF		0x08000000
if (_RICHEDIT_VER ge 0x0800)
define ENM_STARTCOMPOSITION	0x10000000
define ENM_ENDCOMPOSITION	0x20000000
define ENM_GROUPTYPINGCHANGE	0x40000000
define ENM_HIDELINKTOOLTIP	0x80000000
endif

define ES_SAVESEL		0x00008000
define ES_SUNKEN		0x00004000
define ES_DISABLENOSCROLL	0x00002000
define ES_SELECTIONBAR		0x01000000
define ES_NOOLEDRAGDROP		0x00000008

define ES_EX_NOCALLOLEINIT	0x00000000

define ES_VERTICAL		0x00400000
define ES_NOIME			0x00080000
define ES_SELFIME		0x00040000

define ECO_AUTOWORDSELECTION	0x00000001
define ECO_AUTOVSCROLL		0x00000040
define ECO_AUTOHSCROLL		0x00000080
define ECO_NOHIDESEL		0x00000100
define ECO_READONLY		0x00000800
define ECO_WANTRETURN		0x00001000
define ECO_SAVESEL		0x00008000
define ECO_SELECTIONBAR		0x01000000
define ECO_VERTICAL		0x00400000

define ECOOP_SET		0x0001
define ECOOP_OR			0x0002
define ECOOP_AND		0x0003
define ECOOP_XOR		0x0004

define WB_CLASSIFY		3
define WB_MOVEWORDLEFT		4
define WB_MOVEWORDRIGHT		5
define WB_LEFTBREAK		6
define WB_RIGHTBREAK		7

define WB_MOVEWORDPREV		4
define WB_MOVEWORDNEXT		5
define WB_PREVBREAK		6
define WB_NEXTBREAK		7

define PC_FOLLOWING		1
define PC_LEADING		2
define PC_OVERFLOW		3
define PC_DELIMITER		4
define WBF_WORDWRAP		0x010
define WBF_WORDBREAK		0x020
define WBF_OVERFLOW		0x040
define WBF_LEVEL1		0x080
define WBF_LEVEL2		0x100
define WBF_CUSTOM		0x200

define IMF_FORCENONE		0x0001
define IMF_FORCEENABLE		0x0002
define IMF_FORCEDISABLE		0x0004
define IMF_CLOSESTATUSWINDOW	0x0008
define IMF_VERTICAL		0x0020
define IMF_FORCEACTIVE		0x0040
define IMF_FORCEINACTIVE	0x0080
define IMF_FORCEREMEMBER	0x0100
define IMF_MULTIPLEEDIT		0x0400

define WBF_CLASS		0x0F
define WBF_ISWHITE		0x10
define WBF_BREAKLINE		0x20
define WBF_BREAKAFTER		0x40

ifdef _WIN32
CALLBACK(EDITWORDBREAKPROCEX, :ptr, :LONG, :BYTE, :sdword)
endif

_charformat		struct
cbSize			UINT ?
dwMask			DWORD ?
dwEffects		DWORD ?
yHeight			LONG ?
yOffset			LONG ?
crTextColor		COLORREF ?
bCharSet		BYTE ?
bPitchAndFamily		BYTE ?
szFaceName		sbyte LF_FACESIZE dup(?)
_charformat		ends
CHARFORMATA		typedef _charformat

_charformatw		struct
cbSize			UINT ?
dwMask			DWORD ?
dwEffects		DWORD ?
yHeight			LONG ?
yOffset			LONG ?
crTextColor		COLORREF ?
bCharSet		BYTE ?
bPitchAndFamily		BYTE ?
szFaceName		WCHAR LF_FACESIZE dup(?)
_charformatw		ends
CHARFORMATW		typedef _charformatw

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
define CHARFORMAT <CHARFORMATW>
else
define CHARFORMAT <CHARFORMATA>
endif
else
define CHARFORMAT CHARFORMATA
endif

if defined(__cplusplus)

_charformatw		struct
wWeight			WORD ?
sSpacing		sword ?
crBackColor		COLORREF ?
lcid			LCID ?
if (_RICHEDIT_VER ge 0x0500)
union
 dwReserved		DWORD ?
 dwCookie		DWORD ?
ends
else
dwReserved		DWORD ?
endif
sStyle			sword ?
wKerning		WORD ?
bUnderlineType		BYTE ?
bAnimation		BYTE ?
bRevAuthor		BYTE ?
if (_RICHEDIT_VER ge 0x0800)
bUnderlineColor		BYTE ?
endif
_charformatw		ends

_charformat		struct
wWeight			WORD ?
sSpacing		sword ?
crBackColor		COLORREF ?
lcid			LCID ?
if (_RICHEDIT_VER ge 0x0500)
union
 dwReserved		DWORD ?
 dwCookie		DWORD ?
ends
else
dwReserved		DWORD ?
endif
sStyle			sword ?
wKerning		WORD ?
bUnderlineType		BYTE ?
bAnimation		BYTE ?
bRevAuthor		BYTE ?
if (_RICHEDIT_VER ge 0x0800)
bUnderlineColor		BYTE ?
endif
_charformat		ends

else

_charformat2w		struct
cbSize			UINT ?
dwMask			DWORD ?
dwEffects		DWORD ?
yHeight			LONG ?
yOffset			LONG ?
crTextColor		COLORREF ?
bCharSet		BYTE ?
bPitchAndFamily		BYTE ?
szFaceName		WCHAR LF_FACESIZE dup(?)
wWeight			WORD ?
sSpacing		sword ?
crBackColor		COLORREF ?
lcid			LCID ?
if (_RICHEDIT_VER ge 0x0500)
union
 dwReserved		DWORD ?
 dwCookie		DWORD ?
ends
else
dwReserved		DWORD ?
endif
sStyle			sword ?
wKerning		WORD ?
bUnderlineType		BYTE ?
bAnimation		BYTE ?
bRevAuthor		BYTE ?
if (_RICHEDIT_VER ge 0x0800)
bUnderlineColor		BYTE ?
endif
_charformat2w		ends
CHARFORMAT2W		typedef _charformat2w

_charformat2a		struct
cbSize			UINT ?
dwMask			DWORD ?
dwEffects		DWORD ?
yHeight			LONG ?
yOffset			LONG ?
crTextColor		COLORREF ?
bCharSet		BYTE ?
bPitchAndFamily		BYTE ?
szFaceName		sbyte LF_FACESIZE dup(?)
wWeight			WORD ?
sSpacing		sword ?
crBackColor		COLORREF ?
lcid			LCID ?
if (_RICHEDIT_VER ge 0x0500)
union
 dwReserved		DWORD ?
 dwCookie		DWORD ?
ends
else
dwReserved		DWORD ?
endif
sStyle			sword ?
wKerning		WORD ?
bUnderlineType		BYTE ?
bAnimation		BYTE ?
bRevAuthor		BYTE ?
if (_RICHEDIT_VER ge 0x0800)
bUnderlineColor		BYTE ?
endif
_charformat2a		ends
CHARFORMAT2A		typedef _charformat2a

endif

ifdef _UNICODE
define CHARFORMAT2 <CHARFORMAT2W>
else
define CHARFORMAT2 <CHARFORMAT2A>
endif

define CHARFORMATDELTA	(sizeof(CHARFORMAT2) - sizeof(CHARFORMAT))

define CFM_BOLD		0x00000001
define CFM_ITALIC	0x00000002
define CFM_UNDERLINE	0x00000004
define CFM_STRIKEOUT	0x00000008
define CFM_PROTECTED	0x00000010
define CFM_LINK		0x00000020
define CFM_SIZE		0x80000000
define CFM_COLOR	0x40000000
define CFM_FACE		0x20000000
define CFM_OFFSET	0x10000000
define CFM_CHARSET	0x08000000

define CFE_BOLD		0x00000001
define CFE_ITALIC	0x00000002
define CFE_UNDERLINE	0x00000004
define CFE_STRIKEOUT	0x00000008
define CFE_PROTECTED	0x00000010
define CFE_LINK		0x00000020
define CFE_AUTOCOLOR	0x40000000
define CFM_SMALLCAPS	0x00000040
define CFM_ALLCAPS	0x00000080
define CFM_HIDDEN	0x00000100
define CFM_OUTLINE	0x00000200
define CFM_SHADOW	0x00000400
define CFM_EMBOSS	0x00000800
define CFM_IMPRINT	0x00001000
define CFM_DISABLED	0x00002000
define CFM_REVISED	0x00004000

define CFM_REVAUTHOR	0x00008000
define CFE_SUBSCRIPT	0x00010000
define CFE_SUPERSCRIPT	0x00020000
define CFM_ANIMATION	0x00040000
define CFM_STYLE	0x00080000
define CFM_KERNING	0x00100000
define CFM_SPACING	0x00200000
define CFM_WEIGHT	0x00400000
define CFM_UNDERLINETYPE	0x00800000
if (_RICHEDIT_VER ge 0x0600)
define CFM_COOKIE		0x01000000
endif
define CFM_LCID			0x02000000
define CFM_BACKCOLOR		0x04000000

define CFM_SUBSCRIPT		(CFE_SUBSCRIPT or CFE_SUPERSCRIPT)
define CFM_SUPERSCRIPT	CFM_SUBSCRIPT

define CFM_EFFECTS (CFM_BOLD or CFM_ITALIC or CFM_UNDERLINE or CFM_COLOR or CFM_STRIKEOUT or CFE_PROTECTED or CFM_LINK)
define CFM_ALL (CFM_EFFECTS or CFM_SIZE or CFM_FACE or CFM_OFFSET or CFM_CHARSET)

define CFM_EFFECTS2 (CFM_EFFECTS or CFM_DISABLED or CFM_SMALLCAPS or CFM_ALLCAPS or CFM_HIDDEN or CFM_OUTLINE or CFM_SHADOW or CFM_EMBOSS or CFM_IMPRINT or CFM_REVISED or CFM_SUBSCRIPT or CFM_SUPERSCRIPT or CFM_BACKCOLOR)

if (_RICHEDIT_VER ge 0x0600)
define CFM_ALL2	 (CFM_ALL or CFM_EFFECTS2 or CFM_BACKCOLOR or CFM_LCID or CFM_UNDERLINETYPE or CFM_WEIGHT or CFM_REVAUTHOR or CFM_SPACING or CFM_KERNING or CFM_STYLE or CFM_ANIMATION or CFM_COOKIE)
else
define CFM_ALL2	 (CFM_ALL or CFM_EFFECTS2 or CFM_BACKCOLOR or CFM_LCID or CFM_UNDERLINETYPE or CFM_WEIGHT or CFM_REVAUTHOR or CFM_SPACING or CFM_KERNING or CFM_STYLE or CFM_ANIMATION)
endif

define CFE_SMALLCAPS		CFM_SMALLCAPS
define CFE_ALLCAPS		CFM_ALLCAPS
define CFE_HIDDEN		CFM_HIDDEN
define CFE_OUTLINE		CFM_OUTLINE
define CFE_SHADOW		CFM_SHADOW
define CFE_EMBOSS		CFM_EMBOSS
define CFE_IMPRINT		CFM_IMPRINT
define CFE_DISABLED		CFM_DISABLED
define CFE_REVISED		CFM_REVISED

define CFE_AUTOBACKCOLOR	CFM_BACKCOLOR

define CFM_FONTBOUND		0x00100000
define	CFM_LINKPROTECTED	0x00800000
define CFM_EXTENDED		0x02000000
define CFM_MATHNOBUILDUP	0x08000000
define CFM_MATH			0x10000000
define CFM_MATHORDINARY		0x20000000

define	CFM_ALLEFFECTS		(CFM_EFFECTS2 or CFM_FONTBOUND or CFM_EXTENDED or CFM_MATHNOBUILDUP or CFM_MATH or CFM_MATHORDINARY)

define CFE_FONTBOUND		0x00100000
define	CFE_LINKPROTECTED	0x00800000
define CFE_EXTENDED		0x02000000
define CFE_MATHNOBUILDUP	0x08000000
define CFE_MATH			0x10000000
define CFE_MATHORDINARY		0x20000000

define CFU_CF1UNDERLINE 0xFF
define CFU_INVERT			0xFE
define CFU_UNDERLINETHICKLONGDASH	18
define CFU_UNDERLINETHICKDOTTED		17
define CFU_UNDERLINETHICKDASHDOTDOT	16
define CFU_UNDERLINETHICKDASHDOT	15
define CFU_UNDERLINETHICKDASH		14
define CFU_UNDERLINELONGDASH		13
define CFU_UNDERLINEHEAVYWAVE		12
define CFU_UNDERLINEDOUBLEWAVE		11
define CFU_UNDERLINEHAIRLINE		10
define CFU_UNDERLINETHICK		9
define CFU_UNDERLINEWAVE		8
define CFU_UNDERLINEDASHDOTDOT		7
define CFU_UNDERLINEDASHDOT		6
define CFU_UNDERLINEDASH		5
define CFU_UNDERLINEDOTTED		4
define CFU_UNDERLINEDOUBLE		3
define CFU_UNDERLINEWORD		2
define CFU_UNDERLINE			1
define CFU_UNDERLINENONE		0

define yHeightCharPtsMost 1638

define SCF_SELECTION		0x0001
define SCF_WORD			0x0002
define SCF_DEFAULT		0x0000
define SCF_ALL			0x0004
define SCF_USEUIRULES		0x0008
define SCF_ASSOCIATEFONT	0x0010
define SCF_NOKBUPDATE		0x0020
define SCF_ASSOCIATEFONT2	0x0040
if (_RICHEDIT_VER ge 0x0500)
define SCF_SMARTFONT		0x0080
define SCF_CHARREPFROMLCID	0x0100

define SPF_DONTSETDEFAULT	0x0002
define SPF_SETDEFAULT		0x0004
endif

_charrange		struct
cpMin			LONG ?
cpMax			LONG ?
_charrange		ends
CHARRANGE		typedef _charrange

_textrange		struct
chrg			CHARRANGE <>
lpstrText		LPSTR ?
_textrange		ends
TEXTRANGEA		typedef _textrange

_textrangew		struct
chrg			CHARRANGE <>
lpstrText		LPWSTR ?
_textrangew		ends
TEXTRANGEW		typedef _textrangew

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
define TEXTRANGE	<TEXTRANGEW>
else
define TEXTRANGE	<TEXTRANGEA>
endif
else
define TEXTRANGE	TEXTRANGEA
endif

CALLBACK(EDITSTREAMCALLBACK, :DWORD_PTR, :LPBYTE, :LONG, :ptr)

_editstream		struct
dwCookie		DWORD_PTR ?
dwError			DWORD ?
pfnCallback		EDITSTREAMCALLBACK ?
_editstream		ends
EDITSTREAM		typedef _editstream

define SF_TEXT		0x0001
define SF_RTF		0x0002
define SF_RTFNOOBJS	0x0003
define SF_TEXTIZED	0x0004

define SF_UNICODE	0x0010
define SF_USECODEPAGE	0x0020
define SF_NCRFORNONASCII 0x40
define SFF_WRITEXTRAPAR	 0x80

define SFF_SELECTION	0x8000

define SFF_PLAINRTF	0x4000

define SFF_PERSISTVIEWSCALE 0x2000

define SFF_KEEPDOCINFO 0x1000

define SFF_PWD		0x0800

define SF_RTFVAL	0x0700

_findtext		struct
chrg			CHARRANGE <>
lpstrText		LPCSTR ?
_findtext		ends
FINDTEXTA		typedef _findtext

_findtextw		struct
chrg			CHARRANGE <>
lpstrText		LPCWSTR ?
_findtextw		ends
FINDTEXTW		typedef _findtextw

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
define FINDTEXT <FINDTEXTW>
else
define FINDTEXT <FINDTEXTA>
endif
else
define FINDTEXT FINDTEXTA
endif

_findtextexa		struct
chrg			CHARRANGE <>
lpstrText		LPCSTR ?
chrgText		CHARRANGE <>
_findtextexa		ends
FINDTEXTEXA		typedef _findtextexa

_findtextexw		struct
chrg			CHARRANGE <>
lpstrText		LPCWSTR ?
chrgText		CHARRANGE <>
_findtextexw		ends
FINDTEXTEXW		typedef _findtextexw

if (_RICHEDIT_VER ge 0x0200)
ifdef _UNICODE
define FINDTEXTEX	<FINDTEXTEXW>
else
define FINDTEXTEX	<FINDTEXTEXA>
endif
else
define FINDTEXTEX	FINDTEXTEXA
endif

_formatrange		struct
hdc			HDC ?
hdcTarget		HDC ?
_rc			RECT <>
rcPage			RECT <>
chrg			CHARRANGE <>
_formatrange		ends
FORMATRANGE		typedef _formatrange

define MAX_TAB_STOPS 32
define lDefaultTab 720
define MAX_TABLE_CELLS 63

_paraformat		struct
cbSize			UINT ?
dwMask			DWORD ?
wNumbering		WORD ?
union
 wReserved		WORD ?
 wEffects		WORD ?
ends
dxStartIndent		LONG ?
dxRightIndent		LONG ?
dxOffset		LONG ?
wAlignment		WORD ?
cTabCount		sword ?
rgxTabs			LONG MAX_TAB_STOPS dup(?)
_paraformat		ends
PARAFORMAT		typedef _paraformat

ifdef __cplusplus
_paraformat		struct
dySpaceBefore		LONG ?
dySpaceAfter		LONG ?
dyLineSpacing		LONG ?
sStyle			sword ?
bLineSpacingRule	BYTE ?
bOutlineLevel		BYTE ?
wShadingWeight		WORD ?
wShadingStyle		WORD ?
wNumberingStart		WORD ?
wNumberingStyle		WORD ?
wNumberingTab		WORD ?
wBorderSpace		WORD ?
wBorderWidth		WORD ?
wBorders		WORD ?
_paraformat		ends

else

_paraformat2		struct
cbSize			UINT ?
dwMask			DWORD ?
wNumbering		WORD ?
union
 wReserved		WORD ?
 wEffects		WORD ?
ends
dxStartIndent		LONG ?
dxRightIndent		LONG ?
dxOffset		LONG ?
wAlignment		WORD ?
cTabCount		sword ?
rgxTabs			LONG MAX_TAB_STOPS dup(?)
dySpaceBefore		LONG ?
dySpaceAfter		LONG ?
dyLineSpacing		LONG ?
sStyle			sword ?
bLineSpacingRule	BYTE ?
bOutlineLevel		BYTE ?
wShadingWeight		WORD ?
wShadingStyle		WORD ?
wNumberingStart		WORD ?
wNumberingStyle		WORD ?
wNumberingTab		WORD ?
wBorderSpace		WORD ?
wBorderWidth		WORD ?
wBorders		WORD ?
_paraformat2		ends
PARAFORMAT2		typedef _paraformat2

endif

define PFM_STARTINDENT		0x00000001
define PFM_RIGHTINDENT		0x00000002
define PFM_OFFSET		0x00000004
define PFM_ALIGNMENT		0x00000008
define PFM_TABSTOPS		0x00000010
define PFM_NUMBERING		0x00000020
define PFM_OFFSETINDENT		0x80000000

define PFM_SPACEBEFORE		0x00000040
define PFM_SPACEAFTER		0x00000080
define PFM_LINESPACING		0x00000100
define PFM_STYLE		0x00000400
define PFM_BORDER		0x00000800
define PFM_SHADING		0x00001000
define PFM_NUMBERINGSTYLE	0x00002000
define PFM_NUMBERINGTAB		0x00004000
define PFM_NUMBERINGSTART	0x00008000

define PFM_RTLPARA		0x00010000
define PFM_KEEP			0x00020000
define PFM_KEEPNEXT		0x00040000
define PFM_PAGEBREAKBEFORE	0x00080000
define PFM_NOLINENUMBER		0x00100000
define PFM_NOWIDOWCONTROL	0x00200000
define PFM_DONOTHYPHEN		0x00400000
define PFM_SIDEBYSIDE		0x00800000

define PFM_COLLAPSED		0x01000000
define PFM_OUTLINELEVEL		0x02000000
define PFM_BOX			0x04000000
define PFM_RESERVED2		0x08000000
define PFM_TABLEROWDELIMITER	0x10000000
define PFM_TEXTWRAPPINGBREAK	0x20000000
define PFM_TABLE		0x40000000

define PFM_ALL (PFM_STARTINDENT or PFM_RIGHTINDENT or PFM_OFFSET or PFM_ALIGNMENT or PFM_TABSTOPS or PFM_NUMBERING or PFM_OFFSETINDENT or PFM_RTLPARA)

define PFM_EFFECTS (PFM_RTLPARA or PFM_KEEP or PFM_KEEPNEXT or PFM_TABLE or PFM_PAGEBREAKBEFORE or PFM_NOLINENUMBER or PFM_NOWIDOWCONTROL or PFM_DONOTHYPHEN or PFM_SIDEBYSIDE or PFM_TABLE or PFM_TABLEROWDELIMITER)

define PFM_ALL2 (PFM_ALL or PFM_EFFECTS or PFM_SPACEBEFORE or PFM_SPACEAFTER or PFM_LINESPACING or PFM_STYLE or PFM_SHADING or PFM_BORDER or PFM_NUMBERINGTAB or PFM_NUMBERINGSTART or PFM_NUMBERINGSTYLE)

define PFE_RTLPARA		(PFM_RTLPARA shr 16)
define PFE_KEEP			(PFM_KEEP shr 16)
define PFE_KEEPNEXT		(PFM_KEEPNEXT shr 16)
define PFE_PAGEBREAKBEFORE	(PFM_PAGEBREAKBEFORE shr 16)
define PFE_NOLINENUMBER		(PFM_NOLINENUMBER shr 16)
define PFE_NOWIDOWCONTROL	(PFM_NOWIDOWCONTROL shr 16)
define PFE_DONOTHYPHEN		(PFM_DONOTHYPHEN shr 16)
define PFE_SIDEBYSIDE		(PFM_SIDEBYSIDE shr 16)
define PFE_TEXTWRAPPINGBREAK	(PFM_TEXTWRAPPINGBREAK shr 16)

define PFE_COLLAPSED		(PFM_COLLAPSED shr 16)
define PFE_BOX			(PFM_BOX shr 16)
define PFE_TABLE		(PFM_TABLE shr 16)
define PFE_TABLEROWDELIMITER	(PFM_TABLEROWDELIMITER shr 16)

define PFN_BULLET		1

define PFN_ARABIC		2
define PFN_LCLETTER		3
define PFN_UCLETTER		4
define PFN_LCROMAN		5
define PFN_UCROMAN		6

define PFNS_PAREN		0x000
define PFNS_PARENS		0x100
define PFNS_PERIOD		0x200
define PFNS_PLAIN		0x300
define PFNS_NONUMBER		0x400

define PFNS_NEWNUMBER		0x8000
define PFA_LEFT			1
define PFA_RIGHT		2
define PFA_CENTER		3

define PFA_JUSTIFY		4
define PFA_FULL_INTERWORD	4

ifndef WM_NOTIFY
define WM_NOTIFY		0x004E

_nmhdr			struct
hwndFrom		HWND ?
idFrom			UINT ?
code			UINT ?
_nmhdr			ends
NMHDR			typedef _nmhdr
endif

_msgfilter		struct
nmhdr			NMHDR <>
msg			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
_msgfilter		ends
MSGFILTER		typedef _msgfilter

_reqresize		struct
nmhdr			NMHDR <>
_rc			RECT <>
_reqresize		ends
REQRESIZE		typedef _reqresize

_selchange		struct
nmhdr			NMHDR <>
chrg			CHARRANGE <>
seltyp			WORD ?
_selchange		ends
SELCHANGE		typedef _selchange

if (_RICHEDIT_VER ge 0x0800)
_grouptypingchange	struct
nmhdr			NMHDR <>
fGroupTyping		BOOL ?
_grouptypingchange	ends
GROUPTYPINGCHANGE	typedef _grouptypingchange
endif

_clipboardformat	struct
nmhdr			NMHDR <>
cf			CLIPFORMAT ?
_clipboardformat	ends
CLIPBOARDFORMAT		typedef _clipboardformat

define SEL_EMPTY	0x0000
define SEL_TEXT		0x0001
define SEL_OBJECT	0x0002
define SEL_MULTICHAR	0x0004
define SEL_MULTIOBJECT	0x0008

define GCM_RIGHTMOUSEDROP	0x8000

if (_RICHEDIT_VER ge 0x0800)
_getcontextmenuex	struct
chrg			CHARRANGE <>
dwFlags			DWORD ?
pt			POINT <>
pvReserved		ptr ?
_getcontextmenuex	ends
GETCONTEXTMENUEX	typedef _getcontextmenuex

define GCMF_GRIPPER	0x00000001
define GCMF_SPELLING	0x00000002
define GCMF_TOUCHMENU	0x00004000
define GCMF_MOUSEMENU	0x00002000
endif

_endropfiles		struct
nmhdr			NMHDR <>
hDrop			HANDLE ?
cp			LONG ?
fProtected		BOOL ?
_endropfiles		ends
ENDROPFILES		typedef _endropfiles

_enprotected		struct
nmhdr			NMHDR <>
msg			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
chrg			CHARRANGE <>
_enprotected		ends
ENPROTECTED		typedef _enprotected

_ensaveclipboard	struct
nmhdr			NMHDR <>
cObjectCount		LONG ?
cch			LONG ?
_ensaveclipboard	ends
ENSAVECLIPBOARD		typedef _ensaveclipboard

ifndef MACPORT
_enoleopfailed		struct
nmhdr			NMHDR <>
iob			LONG ?
lOper			LONG ?
hr			HRESULT ?
_enoleopfailed		ends
ENOLEOPFAILED		typedef _enoleopfailed
endif

define OLEOP_DOVERB	1

_objectpositions	struct
nmhdr			NMHDR <>
cObjectCount		LONG ?
pcpPositions		ptr LONG ?
_objectpositions	ends
OBJECTPOSITIONS		typedef _objectpositions

_enlink			struct
nmhdr			NMHDR <>
msg			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
chrg			CHARRANGE <>
_enlink			ends
ENLINK			typedef _enlink

_enlowfirtf		struct
nmhdr			NMHDR <>
szControl		ptr sbyte ?
_enlowfirtf		ends
ENLOWFIRTF		typedef _enlowfirtf

_encorrecttext		struct
nmhdr			NMHDR <>
chrg			CHARRANGE <>
seltyp			WORD ?
_encorrecttext		ends
ENCORRECTTEXT		typedef _encorrecttext

_punctuation		struct
iSize			UINT ?
szPunctuation		LPSTR ?
_punctuation		ends
PUNCTUATION		typedef _punctuation

_compcolor		struct
crText			COLORREF ?
crBackground		COLORREF ?
dwEffects		DWORD ?
_compcolor		ends
COMPCOLOR		typedef _compcolor

define CF_RTF		<"Rich Text Format">
define CF_RTFNOOBJS	<"Rich Text Format Without Objects">
define CF_RETEXTOBJ	<"RichEdit Text and Objects">

_repastespecial		struct
dwAspect		DWORD ?
dwParam			DWORD_PTR ?
_repastespecial		ends
REPASTESPECIAL		typedef _repastespecial

.enum UNDONAMEID {
    UID_UNKNOWN		= 0,
    UID_TYPING		= 1,
    UID_DELETE		= 2,
    UID_DRAGDROP	= 3,
    UID_CUT		= 4,
    UID_PASTE		= 5,
    UID_AUTOTABLE	= 6
    }

define ST_DEFAULT	0
define ST_KEEPUNDO	1
define ST_SELECTION	2
define ST_NEWCHARS	4
if (_RICHEDIT_VER ge 0x0500)
define ST_UNICODE	8
endif

_settextex		struct
flags			DWORD ?
codepage		UINT ?
_settextex		ends
SETTEXTEX		typedef _settextex

define GT_DEFAULT	0
define GT_USECRLF	1
define GT_SELECTION	2
define GT_RAWTEXT	4
define GT_NOHIDDENTEXT	8

_gettextex		struct
cb			DWORD ?
flags			DWORD ?
codepage		UINT ?
lpDefaultChar		LPCSTR ?
lpUsedDefChar		LPBOOL ?
_gettextex		ends
GETTEXTEX		typedef _gettextex

define GTL_DEFAULT	0
define GTL_USECRLF	1
define GTL_PRECISE	2
define GTL_CLOSE	4
define GTL_NUMCHARS	8
define GTL_NUMBYTES	16

_gettextlengthex	struct
flags			DWORD ?
codepage		UINT ?
_gettextlengthex	ends
GETTEXTLENGTHEX		typedef _gettextlengthex

_bidioptions		struct
cbSize			UINT ?
wMask			WORD ?
wEffects		WORD ?
_bidioptions		ends
BIDIOPTIONS		typedef _bidioptions

if (_RICHEDIT_VER eq 0x0100)
define BOM_DEFPARADIR		0x0001
define BOM_PLAINTEXT		0x0002
endif
define BOM_NEUTRALOVERRIDE	0x0004
define BOM_CONTEXTREADING	0x0008
define BOM_CONTEXTALIGNMENT	0x0010
define BOM_LEGACYBIDICLASS	0x0040
if (_RICHEDIT_VER ge 0x0600)
define BOM_UNICODEBIDI		0x0080
endif

if (_RICHEDIT_VER eq 0x0100)
define BOE_RTLDIR		0x0001
define BOE_PLAINTEXT		0x0002
endif
define BOE_NEUTRALOVERRIDE	0x0004
define BOE_CONTEXTREADING	0x0008
define BOE_CONTEXTALIGNMENT	0x0010
if (_RICHEDIT_VER ge 0x0800)
define BOE_FORCERECALC		0x0020
endif
define BOE_LEGACYBIDICLASS	0x0040
if (_RICHEDIT_VER ge 0x0600)
define BOE_UNICODEBIDI		0x0080
endif

define FR_MATCHDIAC		0x20000000
define FR_MATCHKASHIDA		0x40000000
define FR_MATCHALEFHAMZA	0x80000000

ifndef WCH_EMBEDDING
define WCH_EMBEDDING		0xFFFC
endif

.enum KHYPH {
    khyphNil,
    khyphNormal,
    khyphAddBefore,
    khyphChangeBefore,
    khyphDeleteBefore,
    khyphChangeAfter,
    khyphDelAndChange
    }

hyphresult		struct
khyph			KHYPH ?
ichHyph			sdword ?
chHyph			WCHAR ?
hyphresult		ends
HYPHRESULT		typedef hyphresult

CALLBACK(HyphenateProc, :ptr, :LANGID, :sdword, :ptr)

tagHyphenateInfo	struct
cbSize			sword ?
dxHyphenateZone		sword ?
pfnHyphenate		HyphenateProc ?
tagHyphenateInfo	ends
HYPHENATEINFO		typedef tagHyphenateInfo

.pragma pack(pop)

if (_RICHEDIT_VER ge 0x0600 )
ifndef RICHEDIT60_CLASS
define RICHEDIT60_CLASS		<L"RICHEDIT60W">
endif
endif

define PFA_FULL_NEWSPAPER	5
define PFA_FULL_INTERLETTER	6
define PFA_FULL_SCALED		7
define PFA_FULL_GLYPHS		8

define	AURL_ENABLEEA		1

define GCM_TOUCHMENU		0x4000
define GCM_MOUSEMENU		0x2000

endif

endif
.pragma list(pop)
