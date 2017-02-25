;
; This module defines the 32-Bit Windows types and constants that are
; defined by NT, but exposed through the Win32 API.
;
include ctype.inc
include string.inc
include basetsd.inc

.xlist

ifndef _WINNT_
_WINNT_ equ 1

ANYSIZE_ARRAY equ 1

if defined(_WIN64) or defined(_M_ALPHA)
MAX_NATURAL_ALIGNMENT equ sizeof(QWORD)
else
MAX_NATURAL_ALIGNMENT equ sizeof(DWORD)
endif

;
; TYPE_ALIGNMENT will return the alignment requirements of a given type for
; the current platform.
;

TYPE_ALIGNMENT macro t
	exitm<option fieldalign:sizeof(t)>
	endm

;
; C_ASSERT() can be used to perform many compile-time assertions:
;	     type sizes, field offsets, etc.
;
; An assertion failure results in error C2118: negative subscript.
;

C_ASSERT macro e
	; typedef char __C_ASSERT__[(e)?1:-1]
	endm

POINTER_64	equ <ptr>
POINTER_32	equ <ptr>
ifdef _WIN64
POINTER_64_INT	typedef QWORD ; unsigned __int64
else
POINTER_64_INT	typedef DWORD ; unsigned long
endif

PVOID		typedef ptr
PVOID64		typedef ptr


if defined(_WIN32) or defined(_STDCALL_SUPPORTED)
NTAPI		equ <stdcall>
else
NTAPI		equ <fastcall>
endif

;
; Define API decoration for direct importing system DLL references.
;

ifndef _NTSYSTEM_
NTSYSAPI	equ <>
else
NTSYSAPI	equ <>
endif

;
; Basics
;

ifndef VOID
VOID		equ <>
CHAR		typedef sbyte
LONG		typedef sdword
endif

;
; UNICODE (Wide Character) types
;

WCHAR		typedef wchar_t ; wc,	16-bit UNICODE character
PWCHAR		typedef ptr wchar_t
LPWCH		typedef ptr wchar_t
PWCH		typedef ptr wchar_t
LPCWCH		typedef ptr wchar_t
PCWCH		typedef ptr wchar_t
NWPSTR		typedef ptr wchar_t
LPWSTR		typedef ptr wchar_t
PWSTR		typedef ptr wchar_t
LPCWSTR		typedef ptr wchar_t
PCWSTR		typedef ptr wchar_t

;
; ANSI (Multi-byte Character) types
;
PCHAR		typedef ptr sbyte
LPCH		typedef ptr sbyte
PCH		typedef ptr sbyte
LPCCH		typedef ptr sbyte
PCCH		typedef ptr sbyte

NPSTR		typedef ptr sbyte
LPSTR		typedef ptr sbyte
PSTR		typedef ptr sbyte
LPCSTR		typedef ptr sbyte
PCSTR		typedef ptr sbyte

;
; Neutral ANSI/UNICODE types and macros
;
ifdef  _UNICODE
ifndef _TCHAR_DEFINED
TCHAR		typedef wchar_t
PTCHAR		typedef ptr wchar_t
PTBYTE		typedef ptr wchar_t
_TCHAR_DEFINED	equ 1
endif
LPTCH		typedef LPWSTR
PTCH		typedef LPWSTR
PTSTR		typedef LPWSTR
LPTSTR		typedef ptr wchar_t
LPCTSTR		typedef LPCWSTR
else
ifndef _TCHAR_DEFINED
TCHAR		typedef sbyte
PTCHAR		typedef ptr sbyte
PTBYTE		typedef ptr byte
_TCHAR_DEFINED	equ 1
endif

LPTCH		typedef LPSTR
PTCH		typedef LPSTR
PTSTR		typedef LPSTR
LPTSTR		typedef ptr sbyte
LPCTSTR		typedef LPCSTR
endif

PSHORT		typedef PTR SWORD
PLONG		typedef PTR SDWORD

HANDLE		typedef PTR
PHANDLE		typedef PTR HANDLE

;
; Flag (bit) fields
;

FCHAR		typedef BYTE
FSHORT		typedef WORD
FLONG		typedef DWORD

; Component Object Model defines, and macros

ifndef _HRESULT_DEFINED
_HRESULT_DEFINED equ 1
HRESULT		typedef SINT
endif

if defined(_WIN32) or defined(_MPPC_)

; Win32 doesn't support __export

ifdef _68K_
STDMETHODCALLTYPE	equ <c>
else
STDMETHODCALLTYPE	equ <stdcall>
endif
STDMETHODVCALLTYPE	equ <c>
STDAPICALLTYPE		equ <stdcall>
STDAPIVCALLTYPE		equ <c>
else
STDMETHODCALLTYPE	equ <fastcall>
STDMETHODVCALLTYPE	equ <c>
STDAPICALLTYPE		equ <fastcall>
STDAPIVCALLTYPE		equ <c>
endif

STDAPI	equ STDAPICALLTYPE
STDAPI_ macro x
	exitm<x STDAPICALLTYPE>
	endm

STDMETHODIMP equ STDMETHODCALLTYPE
STDMETHODIMP_ macro x
	exitm<x STDMETHODCALLTYPE>
	endm

; The 'V' versions allow Variable Argument lists.

STDAPIV equ STDAPIVCALLTYPE
STDAPIV_ macro x
	exitm<x STDAPIVCALLTYPE>
	endm

STDMETHODIMPV equ STDMETHODVCALLTYPE
STDMETHODIMPV_ macro x
	exitm<x STDMETHODVCALLTYPE>
	endm

PDWORD	typedef ptr DWORD
CCHAR	typedef CHAR
LCID	typedef DWORD
PLCID	typedef PDWORD
LANGID	typedef WORD



APPLICATION_ERROR_MASK	     equ 0x20000000
ERROR_SEVERITY_SUCCESS	     equ 0x00000000
ERROR_SEVERITY_INFORMATIONAL equ 0x40000000
ERROR_SEVERITY_WARNING	     equ 0x80000000
ERROR_SEVERITY_ERROR	     equ 0xC0000000

;
; _M_IX86 included so that EM CONTEXT structure compiles with
; x86 programs. *** TBD should this be for all architectures?
;

;
; 16 byte aligned type for 128 bit floats
;

; *** TBD **** when compiler support is available:
; typedef __float80 FLOAT128;
; For we define a 128 bit structure and use force_align pragma to
; align to 128 bits.
;

FLOAT128	STRUC
LowPart		dq ?
HighPart	dq ?
FLOAT128	ENDS

PFLOAT128	typedef PTR FLOAT128

;
; __int64 is only supported by 2.0 and later midl.
; __midl is set by the 2.0 midl and not by 1.0 midl.
;

_ULONGLONG_	equ 1

LONGLONG	typedef SQWORD
ULONGLONG	typedef QWORD
PLONGLONG	typedef PTR LONGLONG
PULONGLONG	typedef PTR ULONGLONG
ifdef _WIN64
MAXLONGLONG	equ 0x7fffffffffffffff
endif

; Update Sequence Number

USN		typedef LONGLONG

LARGE_INTEGER	UNION
STRUC
 LowPart	DWORD ?
 HighPart	SINT ?
ENDS
STRUC u
 LowPart	DWORD ?
 HighPart	SINT ?
ENDS
QuadPart	LONGLONG ?
LARGE_INTEGER	ENDS

ULARGE_INTEGER	UNION
STRUC
 LowPart	DWORD ?
 HighPart	DWORD ?
ENDS
STRUC u
 LowPart	DWORD ?
 HighPart	DWORD ?
ENDS
QuadPart	ULONGLONG ?
ULARGE_INTEGER	ENDS

PLARGE_INTEGER	typedef PTR LARGE_INTEGER
PULARGE_INTEGER typedef PTR ULARGE_INTEGER

;
; Locally Unique Identifier
;

LUID		STRUC
LowPart		DWORD ?
HighPart	LONG ?
LUID		ENDS

PLUID		typedef PTR LUID

_DWORDLONG_	equ 1

DWORDLONG	typedef ULONGLONG
PDWORDLONG	typedef PTR DWORDLONG

;
; Define operations to logically shift an int64 by 0..31 bits and to multiply
; 32-bits by 32-bits to form a 64-bit product.
;
ifdef _WIN32
Int32x32To64	proto _CType Multiplier:LONG, Multiplicand:LONG
UInt32x32To64	proto _CType Multiplier:DWORD, Multiplicand:DWORD
ifdef __PE__
Int64ShllMod32	proto _CType Value:ULONGLONG, ShiftCount:DWORD
Int64ShraMod32	proto _CType Value:ULONGLONG, ShiftCount:DWORD
Int64ShrlMod32	proto _CType Value:ULONGLONG, ShiftCount:DWORD
else
Int64ShllMod32 macro Value, ShiftCount
	mov	ecx, ShiftCount
	mov	eax, dword ptr [Value]
	mov	edx, dword ptr [Value+4]
	shld	edx, eax, cl
	shl	eax, cl
	endm
Int64ShraMod32 macro Value, ShiftCount
	mov	ecx, ShiftCount
	mov	eax, dword ptr [Value]
	mov	edx, dword ptr [Value+4]
	shrd	eax, edx, cl
	sar	edx, cl
	endm
Int64ShrlMod32 macro Value, ShiftCount
	mov	ecx, ShiftCount
	mov	eax, dword ptr [Value]
	mov	edx, dword ptr [Value+4]
	shrd	eax, edx, cl
	shr	edx, cl
	endm
endif
endif	; _WIN32

ANSI_NULL	equ 0
UNICODE_NULL	equ 0
BOOLEAN		typedef BYTE
PBOOLEAN	typedef PTR BOOLEAN

;
;  Doubly linked list structure.  Can be used as either a list head, or
;  as link words.
;

LIST_ENTRY	STRUC
Flink		PVOID ?
Blink		PVOID ?
LIST_ENTRY	ENDS

PLIST_ENTRY	TYPEDEF PTR LIST_ENTRY
PRLIST_ENTRY	TYPEDEF PTR LIST_ENTRY

;
;  Singly linked list structure. Can be used as either a list head, or
;  as link words.
;

SINGLE_LIST_ENTRY STRUC
Next		PVOID ?
SINGLE_LIST_ENTRY ENDS

PSINGLE_LIST_ENTRY TYPEDEF PTR SINGLE_LIST_ENTRY

;
; Base data structures for OLE support
;

ifndef GUID_DEFINED
GUID_DEFINED	equ 1

GUID		STRUC	; size is 16
Data1		dd ?
Data2		dw ?
Data3		dw ?
Data4		db 8 dup(?)
GUID		ENDS
endif

ifndef __OBJECTID_DEFINED
__OBJECTID_DEFINED equ 1

OBJECTID	STRUC	; size is 20
Lineage		GUID <>
Uniquifier	dd ?
OBJECTID	ENDS
endif

MINCHAR		equ 0x80
MAXCHAR		equ 0x7f
MINSHORT	equ 0x8000
MAXSHORT	equ 0x7fff
MINLONG		equ 0x80000000
MAXLONG		equ 0x7fffffff
MAXBYTE		equ 0xff
MAXWORD		equ 0xffff
MAXDWORD	equ 0xffffffff

;
; Calculate the byte offset of a field in a structure of type type.
;

FIELD_OFFSET macro x, field
	exitm<x.field>
	endm

;
; Calculate the address of the base of the structure given its type, and an
; address of a field within the structure.
;

CONTAINING_RECORD macro address, x, field
	exitm<address-x.field>
	endm

;
;  Language IDs.
;
;  The following two combinations of primary language ID and
;  sublanguage ID have special semantics:
;
;    Primary Language ID   Sublanguage ID      Result
;    -------------------   ---------------     ------------------------
;    LANG_NEUTRAL	   SUBLANG_NEUTRAL     Language neutral
;    LANG_NEUTRAL	   SUBLANG_DEFAULT     User default language
;    LANG_NEUTRAL	   SUBLANG_SYS_DEFAULT System default language
;

;
;  Primary language IDs.
;

LANG_NEUTRAL		equ 0x00

LANG_AFRIKAANS		equ 0x36
LANG_ALBANIAN		equ 0x1c
LANG_ARABIC		equ 0x01
LANG_ARMENIAN		equ 0x2b
LANG_ASSAMESE		equ 0x4d
LANG_AZERI		equ 0x2c
LANG_BASQUE		equ 0x2d
LANG_BELARUSIAN		equ 0x23
LANG_BENGALI		equ 0x45
LANG_BULGARIAN		equ 0x02
LANG_CATALAN		equ 0x03
LANG_CHINESE		equ 0x04
LANG_CROATIAN		equ 0x1a
LANG_CZECH		equ 0x05
LANG_DANISH		equ 0x06
LANG_DUTCH		equ 0x13
LANG_ENGLISH		equ 0x09
LANG_ESTONIAN		equ 0x25
LANG_FAEROESE		equ 0x38
LANG_FARSI		equ 0x29
LANG_FINNISH		equ 0x0b
LANG_FRENCH		equ 0x0c
LANG_GEORGIAN		equ 0x37
LANG_GERMAN		equ 0x07
LANG_GREEK		equ 0x08
LANG_GUJARATI		equ 0x47
LANG_HEBREW		equ 0x0d
LANG_HINDI		equ 0x39
LANG_HUNGARIAN		equ 0x0e
LANG_ICELANDIC		equ 0x0f
LANG_INDONESIAN		equ 0x21
LANG_ITALIAN		equ 0x10
LANG_JAPANESE		equ 0x11
LANG_KANNADA		equ 0x4b
LANG_KASHMIRI		equ 0x60
LANG_KAZAK		equ 0x3f
LANG_KONKANI		equ 0x57
LANG_KOREAN		equ 0x12
LANG_LATVIAN		equ 0x26
LANG_LITHUANIAN		equ 0x27
LANG_MACEDONIAN		equ 0x2f
LANG_MALAY		equ 0x3e
LANG_MALAYALAM		equ 0x4c
LANG_MANIPURI		equ 0x58
LANG_MARATHI		equ 0x4e
LANG_NEPALI		equ 0x61
LANG_NORWEGIAN		equ 0x14
LANG_ORIYA		equ 0x48
LANG_POLISH		equ 0x15
LANG_PORTUGUESE		equ 0x16
LANG_PUNJABI		equ 0x46
LANG_ROMANIAN		equ 0x18
LANG_RUSSIAN		equ 0x19
LANG_SANSKRIT		equ 0x4f
LANG_SERBIAN		equ 0x1a
LANG_SINDHI		equ 0x59
LANG_SLOVAK		equ 0x1b
LANG_SLOVENIAN		equ 0x24
LANG_SPANISH		equ 0x0a
LANG_SWAHILI		equ 0x41
LANG_SWEDISH		equ 0x1d
LANG_TAMIL		equ 0x49
LANG_TATAR		equ 0x44
LANG_TELUGU		equ 0x4a
LANG_THAI		equ 0x1e
LANG_TURKISH		equ 0x1f
LANG_UKRAINIAN		equ 0x22
LANG_URDU		equ 0x20
LANG_UZBEK		equ 0x43
LANG_VIETNAMESE		equ 0x2a

;
;  Sublanguage IDs.
;
;  The name immediately following SUBLANG_ dictates which primary
;  language ID that sublanguage ID can be combined with to form a
;  valid language ID.
;

SUBLANG_NEUTRAL			 equ 0x00	 ; language neutral
SUBLANG_DEFAULT			 equ 0x01	 ; user default
SUBLANG_SYS_DEFAULT		 equ 0x02	 ; system default

SUBLANG_ARABIC_SAUDI_ARABIA	 equ 0x01	 ; Arabic (Saudi Arabia)
SUBLANG_ARABIC_IRAQ		 equ 0x02	 ; Arabic (Iraq)
SUBLANG_ARABIC_EGYPT		 equ 0x03	 ; Arabic (Egypt)
SUBLANG_ARABIC_LIBYA		 equ 0x04	 ; Arabic (Libya)
SUBLANG_ARABIC_ALGERIA		 equ 0x05	 ; Arabic (Algeria)
SUBLANG_ARABIC_MOROCCO		 equ 0x06	 ; Arabic (Morocco)
SUBLANG_ARABIC_TUNISIA		 equ 0x07	 ; Arabic (Tunisia)
SUBLANG_ARABIC_OMAN		 equ 0x08	 ; Arabic (Oman)
SUBLANG_ARABIC_YEMEN		 equ 0x09	 ; Arabic (Yemen)
SUBLANG_ARABIC_SYRIA		 equ 0x0a	 ; Arabic (Syria)
SUBLANG_ARABIC_JORDAN		 equ 0x0b	 ; Arabic (Jordan)
SUBLANG_ARABIC_LEBANON		 equ 0x0c	 ; Arabic (Lebanon)
SUBLANG_ARABIC_KUWAIT		 equ 0x0d	 ; Arabic (Kuwait)
SUBLANG_ARABIC_UAE		 equ 0x0e	 ; Arabic (U.A.E)
SUBLANG_ARABIC_BAHRAIN		 equ 0x0f	 ; Arabic (Bahrain)
SUBLANG_ARABIC_QATAR		 equ 0x10	 ; Arabic (Qatar)
SUBLANG_AZERI_LATIN		 equ 0x01	 ; Azeri (Latin)
SUBLANG_AZERI_CYRILLIC		 equ 0x02	 ; Azeri (Cyrillic)
SUBLANG_CHINESE_TRADITIONAL	 equ 0x01	 ; Chinese (Taiwan Region)
SUBLANG_CHINESE_SIMPLIFIED	 equ 0x02	 ; Chinese (PR China)
SUBLANG_CHINESE_HONGKONG	 equ 0x03	 ; Chinese (Hong Kong)
SUBLANG_CHINESE_SINGAPORE	 equ 0x04	 ; Chinese (Singapore)
SUBLANG_CHINESE_MACAU		 equ 0x05	 ; Chinese (Macau)
SUBLANG_DUTCH			 equ 0x01	 ; Dutch
SUBLANG_DUTCH_BELGIAN		 equ 0x02	 ; Dutch (Belgian)
SUBLANG_ENGLISH_US		 equ 0x01	 ; English (USA)
SUBLANG_ENGLISH_UK		 equ 0x02	 ; English (UK)
SUBLANG_ENGLISH_AUS		 equ 0x03	 ; English (Australian)
SUBLANG_ENGLISH_CAN		 equ 0x04	 ; English (Canadian)
SUBLANG_ENGLISH_NZ		 equ 0x05	 ; English (New Zealand)
SUBLANG_ENGLISH_EIRE		 equ 0x06	 ; English (Irish)
SUBLANG_ENGLISH_SOUTH_AFRICA	 equ 0x07	 ; English (South Africa)
SUBLANG_ENGLISH_JAMAICA		 equ 0x08	 ; English (Jamaica)
SUBLANG_ENGLISH_CARIBBEAN	 equ 0x09	 ; English (Caribbean)
SUBLANG_ENGLISH_BELIZE		 equ 0x0a	 ; English (Belize)
SUBLANG_ENGLISH_TRINIDAD	 equ 0x0b	 ; English (Trinidad)
SUBLANG_ENGLISH_ZIMBABWE	 equ 0x0c	 ; English (Zimbabwe)
SUBLANG_ENGLISH_PHILIPPINES	 equ 0x0d	 ; English (Philippines)
SUBLANG_FRENCH			 equ 0x01	 ; French
SUBLANG_FRENCH_BELGIAN		 equ 0x02	 ; French (Belgian)
SUBLANG_FRENCH_CANADIAN		 equ 0x03	 ; French (Canadian)
SUBLANG_FRENCH_SWISS		 equ 0x04	 ; French (Swiss)
SUBLANG_FRENCH_LUXEMBOURG	 equ 0x05	 ; French (Luxembourg)
SUBLANG_FRENCH_MONACO		 equ 0x06	 ; French (Monaco)
SUBLANG_GERMAN			 equ 0x01	 ; German
SUBLANG_GERMAN_SWISS		 equ 0x02	 ; German (Swiss)
SUBLANG_GERMAN_AUSTRIAN		 equ 0x03	 ; German (Austrian)
SUBLANG_GERMAN_LUXEMBOURG	 equ 0x04	 ; German (Luxembourg)
SUBLANG_GERMAN_LIECHTENSTEIN	 equ 0x05	 ; German (Liechtenstein)
SUBLANG_ITALIAN			 equ 0x01	 ; Italian
SUBLANG_ITALIAN_SWISS		 equ 0x02	 ; Italian (Swiss)
SUBLANG_KASHMIRI_INDIA		 equ 0x02	 ; Kashmiri (India)
SUBLANG_KOREAN			 equ 0x01	 ; Korean (Extended Wansung)
SUBLANG_LITHUANIAN		 equ 0x01	 ; Lithuanian
SUBLANG_LITHUANIAN_CLASSIC	 equ 0x02	 ; Lithuanian (Classic)
SUBLANG_MALAY_MALAYSIA		 equ 0x01	 ; Malay (Malaysia)
SUBLANG_MALAY_BRUNEI_DARUSSALAM	 equ 0x02	 ; Malay (Brunei Darussalam)
SUBLANG_NEPALI_INDIA		 equ 0x02	 ; Nepali (India)
SUBLANG_NORWEGIAN_BOKMAL	 equ 0x01	 ; Norwegian (Bokmal)
SUBLANG_NORWEGIAN_NYNORSK	 equ 0x02	 ; Norwegian (Nynorsk)
SUBLANG_PORTUGUESE		 equ 0x02	 ; Portuguese
SUBLANG_PORTUGUESE_BRAZILIAN	 equ 0x01	 ; Portuguese (Brazilian)
SUBLANG_SERBIAN_LATIN		 equ 0x02	 ; Serbian (Latin)
SUBLANG_SERBIAN_CYRILLIC	 equ 0x03	 ; Serbian (Cyrillic)
SUBLANG_SPANISH			 equ 0x01	 ; Spanish (Castilian)
SUBLANG_SPANISH_MEXICAN		 equ 0x02	 ; Spanish (Mexican)
SUBLANG_SPANISH_MODERN		 equ 0x03	 ; Spanish (Modern)
SUBLANG_SPANISH_GUATEMALA	 equ 0x04	 ; Spanish (Guatemala)
SUBLANG_SPANISH_COSTA_RICA	 equ 0x05	 ; Spanish (Costa Rica)
SUBLANG_SPANISH_PANAMA		 equ 0x06	 ; Spanish (Panama)
SUBLANG_SPANISH_DOMINICAN_REPUBLIC equ 0x07	 ; Spanish (Dominican Republic)
SUBLANG_SPANISH_VENEZUELA	 equ 0x08	 ; Spanish (Venezuela)
SUBLANG_SPANISH_COLOMBIA	 equ 0x09	 ; Spanish (Colombia)
SUBLANG_SPANISH_PERU		 equ 0x0a	 ; Spanish (Peru)
SUBLANG_SPANISH_ARGENTINA	 equ 0x0b	 ; Spanish (Argentina)
SUBLANG_SPANISH_ECUADOR		 equ 0x0c	 ; Spanish (Ecuador)
SUBLANG_SPANISH_CHILE		 equ 0x0d	 ; Spanish (Chile)
SUBLANG_SPANISH_URUGUAY		 equ 0x0e	 ; Spanish (Uruguay)
SUBLANG_SPANISH_PARAGUAY	 equ 0x0f	 ; Spanish (Paraguay)
SUBLANG_SPANISH_BOLIVIA		 equ 0x10	 ; Spanish (Bolivia)
SUBLANG_SPANISH_EL_SALVADOR	 equ 0x11	 ; Spanish (El Salvador)
SUBLANG_SPANISH_HONDURAS	 equ 0x12	 ; Spanish (Honduras)
SUBLANG_SPANISH_NICARAGUA	 equ 0x13	 ; Spanish (Nicaragua)
SUBLANG_SPANISH_PUERTO_RICO	 equ 0x14	 ; Spanish (Puerto Rico)
SUBLANG_SWEDISH			 equ 0x01	 ; Swedish
SUBLANG_SWEDISH_FINLAND		 equ 0x02	 ; Swedish (Finland)
SUBLANG_URDU_PAKISTAN		 equ 0x01	 ; Urdu (Pakistan)
SUBLANG_URDU_INDIA		 equ 0x02	 ; Urdu (India)
SUBLANG_UZBEK_LATIN		 equ 0x01	 ; Uzbek (Latin)
SUBLANG_UZBEK_CYRILLIC		 equ 0x02	 ; Uzbek (Cyrillic)

;
;  Sorting IDs.
;

SORT_DEFAULT			 equ 0x0	 ; sorting default
SORT_JAPANESE_XJIS		 equ 0x0	 ; Japanese XJIS order
SORT_JAPANESE_UNICODE		 equ 0x1	 ; Japanese Unicode order
SORT_CHINESE_BIG5		 equ 0x0	 ; Chinese BIG5 order
SORT_CHINESE_PRCP		 equ 0x0	 ; PRC Chinese Phonetic order
SORT_CHINESE_UNICODE		 equ 0x1	 ; Chinese Unicode order
SORT_CHINESE_PRC		 equ 0x2	 ; PRC Chinese Stroke Count order
SORT_CHINESE_BOPOMOFO		 equ 0x3	 ; Traditional Chinese Bopomofo order
SORT_KOREAN_KSC			 equ 0x0	 ; Korean KSC order
SORT_KOREAN_UNICODE		 equ 0x1	 ; Korean Unicode order
SORT_GERMAN_PHONE_BOOK		 equ 0x1	 ; German Phone Book order
SORT_HUNGARIAN_DEFAULT		 equ 0x0	 ; Hungarian Default order
SORT_HUNGARIAN_TECHNICAL	 equ 0x1	 ; Hungarian Technical order
SORT_GEORGIAN_TRADITIONAL	 equ 0x0	 ; Georgian Traditional order
SORT_GEORGIAN_MODERN		 equ 0x1	 ; Georgian Modern order

;
;  A language ID is a 16 bit value which is the combination of a
;  primary language ID and a secondary language ID.  The bits are
;  allocated as follows:
;
;	+-----------------------+-------------------------+
;	|     Sublanguage ID	|   Primary Language ID	  |
;	+-----------------------+-------------------------+
;	 15		      10 9			 0   bit
;
;
;  Language ID creation/extraction macros:
;
;    MAKELANGID	   - construct language id from a primary language id and
;		     a sublanguage id.
;    PRIMARYLANGID - extract primary language id from a language id.
;    SUBLANGID	   - extract sublanguage id from a language id.
;


MAKELANGID MACRO usPrimaryLanguage, usSubLanguage
	EXITM<((usSubLanguage SHL 10) OR usPrimaryLanguage)>
	ENDM

PRIMARYLANGID MACRO lgid
	EXITM<lgid & 0x3ff>
	ENDM

SUBLANGID MACRO lgid
	EXITM<lgid shr 10>
	ENDM

;
;  A locale ID is a 32 bit value which is the combination of a
;  language ID, a sort ID, and a reserved area.	 The bits are
;  allocated as follows:
;
;	+-------------+---------+-------------------------+
;	|   Reserved  | Sort ID |      Language ID	  |
;	+-------------+---------+-------------------------+
;	 31	    20 19     16 15			 0   bit
;
;
;  Locale ID creation/extraction macros:
;
;    MAKELCID		 - construct the locale id from a language id and a sort id.
;    MAKESORTLCID	 - construct the locale id from a language id, sort id, and sort version.
;    LANGIDFROMLCID	 - extract the language id from a locale id.
;    SORTIDFROMLCID	 - extract the sort id from a locale id.
;    SORTVERSIONFROMLCID - extract the sort version from a locale id.
;

NLS_VALID_LOCALE_MASK  equ 0x000fffff

MAKELCID MACRO wLanguageID, wSortID
	EXITM<((wSortID SHL 16) OR wLanguageID)>
	ENDM

MAKESORTLCID macro lgid, srtid, ver
	exitm<(MAKELCID(lgid, srtid) or (ver shl 20))>
	endm

LANGIDFROMLCID macro lcid
	exitm<lcid and 0xffff>
	endm

SORTIDFROMLCID macro lcid
	exitm<((lcid shr 16) and 0xf)>
	endm

SORTVERSIONFROMLCID macro lcid
	exitm<((lcid shr 20) and 0xf)>
	endm


;
;  Default System and User IDs for language and locale.
;

LANG_SYSTEM_DEFAULT	equ MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT)
LANG_USER_DEFAULT	equ MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)

LOCALE_SYSTEM_DEFAULT	equ MAKELCID(LANG_SYSTEM_DEFAULT, SORT_DEFAULT)
LOCALE_USER_DEFAULT	equ MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT)

LOCALE_NEUTRAL	equ MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SORT_DEFAULT)

ifndef WIN32_NO_STATUS

STATUS_WAIT_0			 equ 0x00000000
STATUS_ABANDONED_WAIT_0		 equ 0x00000080
STATUS_USER_APC			 equ 0x000000C0
STATUS_TIMEOUT			 equ 0x00000102
STATUS_PENDING			 equ 0x00000103
STATUS_SEGMENT_NOTIFICATION	 equ 0x40000005
STATUS_GUARD_PAGE_VIOLATION	 equ 0x80000001
STATUS_DATATYPE_MISALIGNMENT	 equ 0x80000002
STATUS_BREAKPOINT		 equ 0x80000003
STATUS_SINGLE_STEP		 equ 0x80000004
STATUS_ACCESS_VIOLATION		 equ 0xC0000005
STATUS_IN_PAGE_ERROR		 equ 0xC0000006
STATUS_INVALID_HANDLE		 equ 0xC0000008
STATUS_NO_MEMORY		 equ 0xC0000017
STATUS_ILLEGAL_INSTRUCTION	 equ 0xC000001D
STATUS_NONCONTINUABLE_EXCEPTION	 equ 0xC0000025
STATUS_INVALID_DISPOSITION	 equ 0xC0000026
STATUS_ARRAY_BOUNDS_EXCEEDED	 equ 0xC000008C
STATUS_FLOAT_DENORMAL_OPERAND	 equ 0xC000008D
STATUS_FLOAT_DIVIDE_BY_ZERO	 equ 0xC000008E
STATUS_FLOAT_INEXACT_RESULT	 equ 0xC000008F
STATUS_FLOAT_INVALID_OPERATION	 equ 0xC0000090
STATUS_FLOAT_OVERFLOW		 equ 0xC0000091
STATUS_FLOAT_STACK_CHECK	 equ 0xC0000092
STATUS_FLOAT_UNDERFLOW		 equ 0xC0000093
STATUS_INTEGER_DIVIDE_BY_ZERO	 equ 0xC0000094
STATUS_INTEGER_OVERFLOW		 equ 0xC0000095
STATUS_PRIVILEGED_INSTRUCTION	 equ 0xC0000096
STATUS_STACK_OVERFLOW		 equ 0xC00000FD
STATUS_CONTROL_C_EXIT		 equ 0xC000013A
STATUS_FLOAT_MULTIPLE_FAULTS	 equ 0xC00002B4
STATUS_FLOAT_MULTIPLE_TRAPS	 equ 0xC00002B5
STATUS_ILLEGAL_VLM_REFERENCE	 equ 0xC00002C0

endif

MAXIMUM_WAIT_OBJECTS	equ 64		; Maximum number of wait objects
MAXIMUM_SUSPEND_COUNT	equ MAXCHAR	; Maximum times thread can be suspended

KSPIN_LOCK	typedef UINT_PTR
PKSPIN_LOCK	typedef PTR KSPIN_LOCK

ifdef _WIN32
;
; Disable these two pramas that evaluate to "sti" "cli" on x86 so that driver
; writers to not leave them inadvertantly in their code.
;

GetFiberData macro
	assume fs:nothing
	mov eax,fs:[0x10]
	mov eax,[eax]
	exitm<eax>
	endm

GetCurrentFiber macro
	assume fs:nothing
	mov eax,fs:[0x10]
	exitm<eax>
	endm

;
;  Define the size of the 80387 save area, which is in the context frame.
;

SIZE_OF_80387_REGISTERS equ 80

;
; The following flags control the contents of the CONTEXT structure.
;

CONTEXT_i386	equ 0x00010000	; this assumes that i386 and
CONTEXT_i486	equ 0x00010000	; i486 have identical context records

; end_wx86

CONTEXT_CONTROL			equ CONTEXT_i386 or 0x00000001	; SS:SP, CS:IP, FLAGS, BP
CONTEXT_INTEGER			equ CONTEXT_i386 or 0x00000002	; AX, BX, CX, DX, SI, DI
CONTEXT_SEGMENTS		equ CONTEXT_i386 or 0x00000004	; DS, ES, FS, GS
CONTEXT_FLOATING_POINT		equ CONTEXT_i386 or 0x00000008	; 387 state
CONTEXT_DEBUG_REGISTERS		equ CONTEXT_i386 or 0x00000010	; DB 0-3,6,7
CONTEXT_EXTENDED_REGISTERS	equ CONTEXT_i386 or 0x00000020	; cpu specific extensions

CONTEXT_FULL equ CONTEXT_CONTROL or CONTEXT_INTEGER or CONTEXT_SEGMENTS

MAXIMUM_SUPPORTED_EXTENSION	equ 512

FLOATING_SAVE_AREA	STRUC SIZE_T
ControlWord		dd ?
StatusWord		dd ?
TagWord			dd ?
ErrorOffset		dd ?
ErrorSelector		dd ?
DataOffset		dd ?
DataSelector		dd ?
RegisterArea		db SIZE_OF_80387_REGISTERS dup(?)
Cr0NpxState		dd ?
FLOATING_SAVE_AREA	ENDS

PFLOATING_SAVE_AREA	typedef PTR FLOATING_SAVE_AREA

;
; Context Frame
;
;  This frame has a several purposes: 1) it is used as an argument to
;  NtContinue, 2) is is used to constuct a call frame for APC delivery,
;  and 3) it is used in the user level thread creation routines.
;
;  The layout of the record conforms to a standard call frame.
;

CONTEXT STRUC

    ;
    ; The flags values within this flag control the contents of
    ; a CONTEXT record.
    ;
    ; If the context record is used as an input parameter, then
    ; for each portion of the context record controlled by a flag
    ; whose value is set, it is assumed that that portion of the
    ; context record contains valid context. If the context record
    ; is being used to modify a threads context, then only that
    ; portion of the threads context will be modified.
    ;
    ; If the context record is used as an IN OUT parameter to capture
    ; the context of a thread, then only those portions of the thread's
    ; context corresponding to set flags will be returned.
    ;
    ; The context record is never used as an OUT only parameter.
    ;

    ContextFlags dd ?

    ;
    ; This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    ; set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    ; included in CONTEXT_FULL.
    ;

    _Dr0 dd ?
    _Dr1 dd ?
    _Dr2 dd ?
    _Dr3 dd ?
    _Dr6 dd ?
    _Dr7 dd ?

    ;
    ; This section is specified/returned if the
    ; ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
    ;

    FloatSave FLOATING_SAVE_AREA <>

    ;
    ; This section is specified/returned if the
    ; ContextFlags word contians the flag CONTEXT_SEGMENTS.
    ;

    SegGs dd ?
    SegFs dd ?
    SegEs dd ?
    SegDs dd ?

    ;
    ; This section is specified/returned if the
    ; ContextFlags word contians the flag CONTEXT_INTEGER.
    ;

    _Edi dd ?
    _Esi dd ?
    _Ebx dd ?
    _Edx dd ?
    _Ecx dd ?
    _Eax dd ?

    ;
    ; This section is specified/returned if the
    ; ContextFlags word contians the flag CONTEXT_CONTROL.
    ;

    _Ebp   dd ?
    _Eip   dd ?
    SegCs  dd ? ; MUST BE SANITIZED
    EFlags dd ? ; MUST BE SANITIZED
    _Esp   dd ?
    SegSs  dd ?

    ;
    ; This section is specified/returned if the ContextFlags word
    ; contains the flag CONTEXT_EXTENDED_REGISTERS.
    ; The format and contexts are processor specific
    ;

    ExtendedRegisters db MAXIMUM_SUPPORTED_EXTENSION dup(?)

CONTEXT ENDS

else

CONTEXT_IA64			equ 0x00080000	  ; IA64 context

CONTEXT_CONTROL			equ CONTEXT_IA64 or 0x00000001
CONTEXT_LOWER_FLOATING_POINT	equ CONTEXT_IA64 or 0x00000002
CONTEXT_HIGHER_FLOATING_POINT	equ CONTEXT_IA64 or 0x00000004
CONTEXT_INTEGER			equ CONTEXT_IA64 or 0x00000008
CONTEXT_DEBUG			equ CONTEXT_IA64 or 0x00000010

CONTEXT_FLOATING_POINT		equ CONTEXT_LOWER_FLOATING_POINT or CONTEXT_HIGHER_FLOATING_POINT
CONTEXT_FULL			equ CONTEXT_CONTROL or CONTEXT_FLOATING_POINT or CONTEXT_INTEGER

LEGACY_SAVE_AREA	STRUC
ControlWord		dw ?
Reserved0		dw ?
StatusWord		dw ?
Reserved1		dw ?
TagWord			dw ?
Reserved2		dw ?
ErrorOffset		dd ?
ErrorSelector		dw ?
ErrorOpcode		dw ?
DataOffset		dd ?
DataSelector		dw ?
Reserved3		dw ?
FloatRegisters		db 8*10 dup (?)
LEGACY_SAVE_AREA	ENDS

CONTEXT STRUC

    P1Home	dq ?
    P2Home	dq ?
    P3Home	dq ?
    P4Home	dq ?
    P5Home	dq ?
    P6Home	dq ?

    ContextFlags dd ?

    MxCsr	dd ?
    SegCs	dw ?
    SegDs	dw ?
    SegEs	dw ?
    SegFs	dw ?
    SegGs	dw ?
    SegSs	dw ?
    EFlags	dd ?

    _Dr0	dq ?
    _Dr1	dq ?
    _Dr2	dq ?
    _Dr3	dq ?
    _Dr6	dq ?
    _Dr7	dq ?

    _Rax	dq ?
    _Rcx	dq ?
    _Rdx	dq ?
    _Rbx	dq ?
    _Rsp	dq ?
    _Rbp	dq ?
    _Rsi	dq ?
    _Rdi	dq ?
    _R8		dq ?
    _R9		dq ?
    _R10	dq ?
    _R11	dq ?
    _R12	dq ?
    _R13	dq ?
    _R14	dq ?
    _R15	dq ?

    _Rip	dq ?

    _Xmm0	dq 2 dup(?)
    _Xmm1	dq 2 dup(?)
    _Xmm2	dq 2 dup(?)
    _Xmm3	dq 2 dup(?)
    _Xmm4	dq 2 dup(?)
    _Xmm5	dq 2 dup(?)
    _Xmm6	dq 2 dup(?)
    _Xmm7	dq 2 dup(?)
    _Xmm8	dq 2 dup(?)
    _Xmm9	dq 2 dup(?)
    _Xmm10	dq 2 dup(?)
    _Xmm11	dq 2 dup(?)
    _Xmm12	dq 2 dup(?)
    _Xmm13	dq 2 dup(?)
    _Xmm14	dq 2 dup(?)
    _Xmm15	dq 2 dup(?)

    FltSave	LEGACY_SAVE_AREA <>

    Fill	dd ?

    DebugControl	 dq ?
    LastBranchToRip	 dq ?
    LastBranchFromRip	 dq ?
    LastExceptionToRip	 dq ?
    LastExceptionFromRip dq ?

    HighFill	dq ?

CONTEXT ENDS

endif ; _WIN64

PCONTEXT typedef ptr CONTEXT

ifndef _LDT_ENTRY_DEFINED
_LDT_ENTRY_DEFINED equ 1

LDT_ENTRY_R0 RECORD \
	    ldt_BaseHi:		8,
	    ldt_Granularity:	1,
	    ldt_ldt_Default_Big:1,
	    ldt_Reserved_0:	1,
	    ldt_Sys:		1,
	    ldt_LimitHi:	4,
	    ldt_Pres:		1,
	    ldt_Dpl:		2,
	    ldt_Type:		5,
	    ldt_BaseMid:	8

LDT_ENTRY	STRUC
LimitLow	dw ?
BaseLow		dw ?
UNION ;HighWord
  STRUC ;Bytes
    BaseMid	db ?
    Flags1	db ?	; Declare as bytes to avoid alignment
    Flags2	db ?	; Problems.
    BaseHi	db ?
  ENDS
  STRUC ;Bits
    r0		LDT_ENTRY_R0 <>
  ENDS
ENDS
LDT_ENTRY	ENDS
PLDT_ENTRY	typedef ptr LDT_ENTRY

endif


EXCEPTION_NONCONTINUABLE	equ 0x1 ; Noncontinuable exception
EXCEPTION_MAXIMUM_PARAMETERS	equ 15	; maximum number of exception parameters

;
; Exception record definition.
;

EXCEPTION_RECORD	STRUC SIZE_T
ExceptionCode		DWORD ?
ExceptionFlags		DWORD ?
ExceptionRecord		PVOID ? ; EXCEPTION_RECORD *
ExceptionAddress	PVOID ?
NumberParameters	DWORD ?
ExceptionInformation	PVOID EXCEPTION_MAXIMUM_PARAMETERS dup(?)
EXCEPTION_RECORD	ENDS

PEXCEPTION_RECORD	TYPEDEF PTR EXCEPTION_RECORD

;
; Typedef for pointer returned by exception_info()
;

EXCEPTION_POINTERS	STRUC SIZE_T
ExceptionRecord		SIZE_T ?
ContextRecord		SIZE_T ?
EXCEPTION_POINTERS	ENDS

EXCEPTION_REGISTRATION	STRUC SIZE_T
prev			SIZE_T ?
handler			SIZE_T ?
EXCEPTION_REGISTRATION	ENDS

PEXCEPTION_POINTERS	TYPEDEF PTR EXCEPTION_POINTERS

PACCESS_TOKEN		typedef PVOID
PSECURITY_DESCRIPTOR	typedef PVOID
PSID			typedef PVOID

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								    ;;
;;			      ACCESS MASK			    ;;
;;								    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Define the access mask as a longword sized structure divided up as
;  follows:
;
;	3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;	1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;      +---------------+---------------+-------------------------------+
;      |G|G|G|G|Res'd|A| StandardRights|         SpecificRights        |
;      |R|W|E|A|     |S|	       |			       |
;      +-+-------------+---------------+-------------------------------+
;
;      typedef struct _ACCESS_MASK {
;	   WORD	  SpecificRights;
;	   BYTE	 StandardRights;
;	   BYTE	 AccessSystemAcl : 1;
;	   BYTE	 Reserved : 3;
;	   BYTE	 GenericAll : 1;
;	   BYTE	 GenericExecute : 1;
;	   BYTE	 GenericWrite : 1;
;	   BYTE	 GenericRead : 1;
;      } ACCESS_MASK;
;      typedef ACCESS_MASK *PACCESS_MASK;
;
;  but to make life simple for programmer's we'll allow them to specify
;  a desired access mask by simply OR'ing together mulitple single rights
;  and treat an access mask as a DWORD.	 For example
;
;      DesiredAccess = DELETE | READ_CONTROL
;
;  So we'll declare ACCESS_MASK as DWORD
;

ACCESS_MASK	typedef DWORD
PACCESS_MASK	typedef PTR ACCESS_MASK

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								    ;;
;;			    ACCESS TYPES			    ;;
;;								    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
; The following are masks for the predefined standard access types
;

DELETE		equ 0x00010000
READ_CONTROL	equ 0x00020000
WRITE_DAC	equ 0x00040000
WRITE_OWNER	equ 0x00080000
SYNCHRONIZE	equ 0x00100000

STANDARD_RIGHTS_REQUIRED equ 0x000F0000

STANDARD_RIGHTS_READ	equ READ_CONTROL
STANDARD_RIGHTS_WRITE	equ READ_CONTROL
STANDARD_RIGHTS_EXECUTE equ READ_CONTROL

STANDARD_RIGHTS_ALL	equ 0x001F0000
SPECIFIC_RIGHTS_ALL	equ 0x0000FFFF

;
; AccessSystemAcl access type
;

ACCESS_SYSTEM_SECURITY	equ 0x01000000

;
; MaximumAllowed access type
;

MAXIMUM_ALLOWED equ 0x02000000

;
;  These are the generic rights.
;

GENERIC_READ	equ 0x80000000
GENERIC_WRITE	equ 0x40000000
GENERIC_EXECUTE equ 0x20000000
GENERIC_ALL	equ 0x10000000

;
;  Define the generic mapping array.  This is used to denote the
;  mapping of each generic access right to a specific access mask.
;

GENERIC_MAPPING STRUC
GenericRead	ACCESS_MASK ?
GenericWrite	ACCESS_MASK ?
GenericExecute	ACCESS_MASK ?
GenericAll	ACCESS_MASK ?
GENERIC_MAPPING ENDS

PGENERIC_MAPPING typedef PTR GENERIC_MAPPING

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								      ;;
;;			  LUID_AND_ATTRIBUTES			      ;;
;;								      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;

LUID_AND_ATTRIBUTES STRUC 4
Luid		LUID <>
Attributes	DWORD ?
LUID_AND_ATTRIBUTES ENDS

PLUID_AND_ATTRIBUTES typedef ptr LUID_AND_ATTRIBUTES

LUID_AND_ATTRIBUTES_ARRAY typedef LUID_AND_ATTRIBUTES
PLUID_AND_ATTRIBUTES_ARRAY typedef ptr LUID_AND_ATTRIBUTES_ARRAY

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								      ;;
;;		Security Id	(SID)				      ;;
;;								      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;
;; Pictorially the structure of an SID is as follows:
;;
;;	   1   1   1   1   1   1
;;	   5   4   3   2   1   0   9   8   7   6   5   4   3   2   1   0
;;	+---------------------------------------------------------------+
;;	|      SubAuthorityCount	|Reserved1 (SBZ)|   Revision	|
;;	+---------------------------------------------------------------+
;;	|		    IdentifierAuthority[0]			|
;;	+---------------------------------------------------------------+
;;	|		    IdentifierAuthority[1]			|
;;	+---------------------------------------------------------------+
;;	|		    IdentifierAuthority[2]			|
;;	+---------------------------------------------------------------+
;;	|								|
;;	+- -  -	 -  -  -  -  -	SubAuthority[]	-  -  -	 -  -  -  -  - -+
;;	|								|
;;	+---------------------------------------------------------------+
;;
;;

ifndef SID_IDENTIFIER_AUTHORITY_DEFINED
SID_IDENTIFIER_AUTHORITY_DEFINED equ 1
SID_IDENTIFIER_AUTHORITY STRUC
Value		db 6 dup(?)
SID_IDENTIFIER_AUTHORITY ENDS
PSID_IDENTIFIER_AUTHORITY typedef ptr SID_IDENTIFIER_AUTHORITY
endif


ifndef SID_DEFINED
SID_DEFINED		equ 1
SID			STRUC
Revision		BYTE ?
SubAuthorityCount	BYTE ?
IdentifierAuthority	SID_IDENTIFIER_AUTHORITY <>
SubAuthority		dd ANYSIZE_ARRAY dup(?)
SID			ENDS
PISID			typedef ptr SID
endif

SID_REVISION			 equ 1	; Current revision level
SID_MAX_SUB_AUTHORITIES		 equ 15 ;
SID_RECOMMENDED_SUB_AUTHORITIES	 equ 1	; Will change to around 6

SID_NAME_USE			typedef DWORD
PSID_NAME_USE			typedef ptr SID_NAME_USE

SidTypeUser			equ 1
SidTypeGroup			equ 2
SidTypeDomain			equ 3
SidTypeAlias			equ 4
SidTypeWellKnownGroup		equ 5
SidTypeDeletedAccount		equ 6
SidTypeInvalid			equ 7
SidTypeUnknown			equ 8
SidTypeComputer			equ 9

SID_AND_ATTRIBUTES STRUC
Sid		PSID ?
Attributes	DWORD ?
SID_AND_ATTRIBUTES ENDS

PSID_AND_ATTRIBUTES		typedef ptr SID_AND_ATTRIBUTES

SID_AND_ATTRIBUTES_ARRAY	typedef SID_AND_ATTRIBUTES
PSID_AND_ATTRIBUTES_ARRAY	typedef PTR SID_AND_ATTRIBUTES_ARRAY

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;									   ;;
;; Universal well-known SIDs						   ;;
;;									   ;;
;;     Null SID			    S-1-0-0				   ;;
;;     World			    S-1-1-0				   ;;
;;     Local			    S-1-2-0				   ;;
;;     Creator Owner ID		    S-1-3-0				   ;;
;;     Creator Group ID		    S-1-3-1				   ;;
;;     Creator Owner Server ID	    S-1-3-2				   ;;
;;     Creator Group Server ID	    S-1-3-3				   ;;
;;									   ;;
;;     (Non-unique IDs)		    S-1-4				   ;;
;;									   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SECURITY_NULL_SID_AUTHORITY	  equ <{0,0,0,0,0,0}>
SECURITY_WORLD_SID_AUTHORITY	  equ <{0,0,0,0,0,1}>
SECURITY_LOCAL_SID_AUTHORITY	  equ <{0,0,0,0,0,2}>
SECURITY_CREATOR_SID_AUTHORITY	  equ <{0,0,0,0,0,3}>
SECURITY_NON_UNIQUE_AUTHORITY	  equ <{0,0,0,0,0,4}>

SECURITY_NULL_RID		  equ 0x00000000
SECURITY_WORLD_RID		  equ 0x00000000
SECURITY_LOCAL_RID		  equ 0X00000000

SECURITY_CREATOR_OWNER_RID	  equ 0x00000000
SECURITY_CREATOR_GROUP_RID	  equ 0x00000001

SECURITY_CREATOR_OWNER_SERVER_RID equ 0x00000002
SECURITY_CREATOR_GROUP_SERVER_RID equ 0x00000003

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;									   ;;
;; NT well-known SIDs							   ;;
;;									   ;;
;;     NT Authority	    S-1-5					   ;;
;;     Dialup		    S-1-5-1					   ;;
;;									   ;;
;;     Network		    S-1-5-2					   ;;
;;     Batch		    S-1-5-3					   ;;
;;     Interactive	    S-1-5-4					   ;;
;;     Service		    S-1-5-6					   ;;
;;     AnonymousLogon	    S-1-5-7	  (aka null logon session)	   ;;
;;     Proxy		    S-1-5-8					   ;;
;;     ServerLogon	    S-1-5-9	  (aka domain controller account)  ;;
;;     Self		    S-1-5-10	  (self RID)			   ;;
;;     Authenticated User    S-1-5-11	  (Authenticated user somewhere)   ;;
;;     Restricted Code	    S-1-5-12	  (Running restricted code)	   ;;
;;									   ;;
;;     (Logon IDs)	    S-1-5-5-X-Y					   ;;
;;									   ;;
;;     (NT non-unique IDs)   S-1-5-0x15-...				   ;;
;;									   ;;
;;     (Built-in domain)	    s-1-5-0x20				   ;;
;;									   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


SECURITY_NT_AUTHORITY		equ <{0,0,0,0,0,5}>	;; ntifs

SECURITY_DIALUP_RID		equ 0x00000001
SECURITY_NETWORK_RID		equ 0x00000002
SECURITY_BATCH_RID		equ 0x00000003
SECURITY_INTERACTIVE_RID	equ 0x00000004
SECURITY_SERVICE_RID		equ 0x00000006
SECURITY_ANONYMOUS_LOGON_RID	equ 0x00000007
SECURITY_PROXY_RID		equ 0x00000008
SECURITY_ENTERPRISE_CONTROLLERS_RID equ 0x00000009
SECURITY_SERVER_LOGON_RID	equ SECURITY_ENTERPRISE_CONTROLLERS_RID
SECURITY_PRINCIPAL_SELF_RID	equ 0x0000000A
SECURITY_AUTHENTICATED_USER_RID equ 0x0000000B
SECURITY_RESTRICTED_CODE_RID	equ 0x0000000C

SECURITY_LOGON_IDS_RID		equ 0x00000005
SECURITY_LOGON_IDS_RID_COUNT	equ 3

SECURITY_LOCAL_SYSTEM_RID	equ 0x00000012

SECURITY_NT_NON_UNIQUE		equ 0x00000015

SECURITY_BUILTIN_DOMAIN_RID	equ 0x00000020

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;									   ;;
;; well-known domain relative sub-authority values (RIDs)...		   ;;
;;									   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Well-known users ...

DOMAIN_USER_RID_ADMIN	       equ 0x000001F4
DOMAIN_USER_RID_GUEST	       equ 0x000001F5
DOMAIN_USER_RID_KRBTGT	       equ 0x000001F6

;; well-known groups ...

DOMAIN_GROUP_RID_ADMINS	       equ 0x00000200
DOMAIN_GROUP_RID_USERS	       equ 0x00000201
DOMAIN_GROUP_RID_GUESTS	       equ 0x00000202
DOMAIN_GROUP_RID_COMPUTERS     equ 0x00000203
DOMAIN_GROUP_RID_CONTROLLERS   equ 0x00000204
DOMAIN_GROUP_RID_CERT_ADMINS   equ 0x00000205
DOMAIN_GROUP_RID_SCHEMA_ADMINS equ 0x00000206

;; well-known aliases ...

DOMAIN_ALIAS_RID_ADMINS	       equ 0x00000220
DOMAIN_ALIAS_RID_USERS	       equ 0x00000221
DOMAIN_ALIAS_RID_GUESTS	       equ 0x00000222
DOMAIN_ALIAS_RID_POWER_USERS   equ 0x00000223

DOMAIN_ALIAS_RID_ACCOUNT_OPS   equ 0x00000224
DOMAIN_ALIAS_RID_SYSTEM_OPS    equ 0x00000225
DOMAIN_ALIAS_RID_PRINT_OPS     equ 0x00000226
DOMAIN_ALIAS_RID_BACKUP_OPS    equ 0x00000227

DOMAIN_ALIAS_RID_REPLICATOR    equ 0x00000228


;;
;; Allocate the System Luid.  The first 1000 LUIDs are reserved.
;; Use #999 here (0x3E7 = 999)
;;

SYSTEM_LUID			equ <{ 0x3E7, 0x0 }>
ANONYMOUS_LOGON_LUID		equ <{ 0x3e6, 0x0 }>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								      ;;
;;			    User and Group related SID attributes     ;;
;;								      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;
;; Group attributes
;;

SE_GROUP_MANDATORY		equ 0x00000001
SE_GROUP_ENABLED_BY_DEFAULT	equ 0x00000002
SE_GROUP_ENABLED		equ 0x00000004
SE_GROUP_OWNER			equ 0x00000008
SE_GROUP_USE_FOR_DENY_ONLY	equ 0x00000010
SE_GROUP_LOGON_ID		equ 0xC0000000

;;
;; User attributes
;;

;; (None yet defined.)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								     ;;
;;			  ACL  and  ACE				     ;;
;;								     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;
;;  Define an ACL and the ACE format.  The structure of an ACL header
;;  followed by one or more ACEs.  Pictorally the structure of an ACL header
;;  is as follows:
;;
;;	3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;	1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;	+-------------------------------+---------------+---------------+
;;	|	    AclSize	       |      Sbz1     |  AclRevision  |
;;	+-------------------------------+---------------+---------------+
;;	|	      Sbz2	       |	   AceCount	       |
;;	+-------------------------------+-------------------------------+
;;
;;  The current AclRevision is defined to be ACL_REVISION.
;;
;;  AclSize is the size, in bytes, allocated for the ACL.  This includes
;;  the ACL header, ACES, and remaining free space in the buffer.
;;
;;  AceCount is the number of ACES in the ACL.
;;

;; This is the *current* ACL revision

ACL_REVISION	 equ 2
ACL_REVISION_DS	 equ 4

;; This is the history of ACL revisions. Add a new one whenever
;; ACL_REVISION is updated

ACL_REVISION1	equ 1
MIN_ACL_REVISION equ ACL_REVISION2
ACL_REVISION2	equ 2
ACL_REVISION3	equ 3
ACL_REVISION4	equ 4
MAX_ACL_REVISION equ ACL_REVISION4

ACL		STRUC
AclRevision	BYTE ?
Sbz1		BYTE ?
AclSize		WORD ?
AceCount	WORD ?
Sbz2		WORD ?
ACL		ENDS

PACL		typedef PTR ACL

;;
;;  The structure of an ACE is a common ace header followed by ace type
;;  specific data.  Pictorally the structure of the common ace header is
;;  as follows:
;;
;;	3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;	1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;	+---------------+-------+-------+---------------+---------------+
;;	|	    AceSize	       |    AceFlags   |     AceType   |
;;	+---------------+-------+-------+---------------+---------------+
;;
;;  AceType denotes the type of the ace, there are some predefined ace
;;  types
;;
;;  AceSize is the size, in bytes, of ace.
;;
;;  AceFlags are the Ace flags for audit and inheritance, defined shortly.

ACE_HEADER	STRUC
AceType		BYTE ?
AceFlags	BYTE ?
AceSize		WORD ?
ACE_HEADER	ENDS

PACE_HEADER	typedef PTR ACE_HEADER

;;
;;  The following are the predefined ace types that go into the AceType
;;  field of an Ace header.
;;

ACCESS_MIN_MS_ACE_TYPE			equ 0x0
ACCESS_ALLOWED_ACE_TYPE			equ 0x0
ACCESS_DENIED_ACE_TYPE			equ 0x1
SYSTEM_AUDIT_ACE_TYPE			equ 0x2
SYSTEM_ALARM_ACE_TYPE			equ 0x3
ACCESS_MAX_MS_V2_ACE_TYPE		equ 0x3

ACCESS_ALLOWED_COMPOUND_ACE_TYPE	equ 0x4
ACCESS_MAX_MS_V3_ACE_TYPE		equ 0x4

ACCESS_MIN_MS_OBJECT_ACE_TYPE		equ 0x5
ACCESS_ALLOWED_OBJECT_ACE_TYPE		equ 0x5
ACCESS_DENIED_OBJECT_ACE_TYPE		equ 0x6
SYSTEM_AUDIT_OBJECT_ACE_TYPE		equ 0x7
SYSTEM_ALARM_OBJECT_ACE_TYPE		equ 0x8
ACCESS_MAX_MS_OBJECT_ACE_TYPE		equ 0x8

ACCESS_MAX_MS_V4_ACE_TYPE		equ 0x8
ACCESS_MAX_MS_ACE_TYPE			equ 0x8

;;
;;  The following are the inherit flags that go into the AceFlags field
;;  of an Ace header.
;;

OBJECT_INHERIT_ACE		  equ 0x1
CONTAINER_INHERIT_ACE		  equ 0x2
NO_PROPAGATE_INHERIT_ACE	  equ 0x4
INHERIT_ONLY_ACE		  equ 0x8
INHERITED_ACE			  equ 0x10
VALID_INHERIT_FLAGS		  equ 0x1F


;;  The following are the currently defined ACE flags that go into the
;;  AceFlags field of an ACE header.  Each ACE type has its own set of
;;  AceFlags.
;;
;;  SUCCESSFUL_ACCESS_ACE_FLAG - used only with system audit and alarm ACE
;;  types to indicate that a message is generated for successful accesses.
;;
;;  FAILED_ACCESS_ACE_FLAG - used only with system audit and alarm ACE types
;;  to indicate that a message is generated for failed accesses.
;;

;;
;;  SYSTEM_AUDIT and SYSTEM_ALARM AceFlags
;;
;;  These control the signaling of audit and alarms for success or failure.
;;

SUCCESSFUL_ACCESS_ACE_FLAG	 equ 0x40
FAILED_ACCESS_ACE_FLAG		 equ 0x80


;;
;;  We'll define the structure of the predefined ACE types.  Pictorally
;;  the structure of the predefined ACE's is as follows:
;;
;;	3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;	1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;	+---------------+-------+-------+---------------+---------------+
;;	|    AceFlags	| Resd	|Inherit|    AceSize	|     AceType	|
;;	+---------------+-------+-------+---------------+---------------+
;;	|			      Mask			       |
;;	+---------------------------------------------------------------+
;;	|							       |
;;	+							       +
;;	|							       |
;;	+			      Sid			       +
;;	|							       |
;;	+							       +
;;	|							       |
;;	+---------------------------------------------------------------+
;;
;;  Mask is the access mask associated with the ACE.  This is either the
;;  access allowed, access denied, audit, or alarm mask.
;;
;;  Sid is the Sid associated with the ACE.
;;

;;  The following are the four predefined ACE types.

;;  Examine the AceType field in the Header to determine
;;  which structure is appropriate to use for casting.


ACCESS_ALLOWED_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
SidStart	DWORD ?
ACCESS_ALLOWED_ACE ENDS
PACCESS_ALLOWED_ACE typedef PTR ACCESS_ALLOWED_ACE

ACCESS_DENIED_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
SidStart	DWORD ?
ACCESS_DENIED_ACE ENDS
PACCESS_DENIED_ACE typedef PTR ACCESS_DENIED_ACE

SYSTEM_AUDIT_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
SidStart	DWORD ?
SYSTEM_AUDIT_ACE ENDS
PSYSTEM_AUDIT_ACE typedef PTR SYSTEM_AUDIT_ACE

SYSTEM_ALARM_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
SidStart	DWORD ?
SYSTEM_ALARM_ACE ENDS
PSYSTEM_ALARM_ACE typedef PTR SYSTEM_ALARM_ACE

ACCESS_ALLOWED_OBJECT_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
Flags		DWORD ?
ObjectType	GUID <>
InheritedObjectType GUID <>
SidStart	DWORD ?
ACCESS_ALLOWED_OBJECT_ACE ENDS
PACCESS_ALLOWED_OBJECT_ACE TYPEDEF PTR ACCESS_ALLOWED_OBJECT_ACE

ACCESS_DENIED_OBJECT_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
Flags		DWORD ?
ObjectType	GUID <>
InheritedObjectType GUID <>
SidStart	DWORD ?
ACCESS_DENIED_OBJECT_ACE ENDS
PACCESS_DENIED_OBJECT_ACE TYPEDEF PTR ACCESS_DENIED_OBJECT_ACE

SYSTEM_AUDIT_OBJECT_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
Flags		DWORD ?
ObjectType	GUID <>
InheritedObjectType GUID <>
SidStart	DWORD ?
SYSTEM_AUDIT_OBJECT_ACE ENDS
PSYSTEM_AUDIT_OBJECT_ACE TYPEDEF PTR SYSTEM_AUDIT_OBJECT_ACE

SYSTEM_ALARM_OBJECT_ACE STRUC
Header		ACE_HEADER <>
_Mask		ACCESS_MASK ?
Flags		DWORD ?
ObjectType	GUID <>
InheritedObjectType GUID <>
SidStart	DWORD ?
SYSTEM_ALARM_OBJECT_ACE ENDS
PSYSTEM_ALARM_OBJECT_ACE TYPEDEF PTR SYSTEM_ALARM_OBJECT_ACE

;;
;; Currently define Flags for "OBJECT" ACE types.
;;

ACE_OBJECT_TYPE_PRESENT		  equ 0x1
ACE_INHERITED_OBJECT_TYPE_PRESENT equ 0x2

;;
;;  The following declarations are used for setting and querying information
;;  about and ACL.  First are the various information classes available to
;;  the user.
;;

ACL_INFORMATION_CLASS	typedef DWORD

AclRevisionInformation	equ 1
AclSizeInformation	equ 2

;;
;;  This record is returned/sent if the user is requesting/setting the
;;  AclRevisionInformation
;;

ACL_REVISION_INFORMATION STRUC
AclRevision		dd ?
ACL_REVISION_INFORMATION ENDS
PACL_REVISION_INFORMATION typedef ptr ACL_REVISION_INFORMATION

;;
;;  This record is returned if the user is requesting AclSizeInformation
;;

ACL_SIZE_INFORMATION	STRUC
AceCount		dd ?
AclBytesInUse		dd ?
AclBytesFree		dd ?
ACL_SIZE_INFORMATION	ENDS
PACL_SIZE_INFORMATION	typedef ptr ACL_SIZE_INFORMATION

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								     ;;
;;			      SECURITY_DESCRIPTOR		     ;;
;;								     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  Define the Security Descriptor and related data types.
;;  This is an opaque data structure.

;;
;; Current security descriptor revision value
;;

SECURITY_DESCRIPTOR_REVISION	 equ 1
SECURITY_DESCRIPTOR_REVISION1	 equ 1

SECURITY_DESCRIPTOR_MIN_LENGTH	 equ sizeof(SECURITY_DESCRIPTOR)

SECURITY_DESCRIPTOR_CONTROL	typedef WORD
PSECURITY_DESCRIPTOR_CONTROL	typedef ptr SECURITY_DESCRIPTOR_CONTROL

SE_OWNER_DEFAULTED		 equ 0x0001
SE_GROUP_DEFAULTED		 equ 0x0002
SE_DACL_PRESENT			 equ 0x0004
SE_DACL_DEFAULTED		 equ 0x0008
SE_SACL_PRESENT			 equ 0x0010
SE_SACL_DEFAULTED		 equ 0x0020
SE_DACL_AUTO_INHERIT_REQ	 equ 0x0100
SE_SACL_AUTO_INHERIT_REQ	 equ 0x0200
SE_DACL_AUTO_INHERITED		 equ 0x0400
SE_SACL_AUTO_INHERITED		 equ 0x0800
SE_DACL_PROTECTED		 equ 0x1000
SE_SACL_PROTECTED		 equ 0x2000
SE_SELF_RELATIVE		 equ 0x8000

;;
;;  Where:
;;
;;	SE_OWNER_DEFAULTED - This boolean flag, when set, indicates that the
;;	   SID pointed to by the Owner field was provided by a
;;	   defaulting mechanism rather than explicitly provided by the
;;	   original provider of the security descriptor.  This may
;;	   affect the treatment of the SID with respect to inheritence
;;	   of an owner.
;;
;;	SE_GROUP_DEFAULTED - This boolean flag, when set, indicates that the
;;	   SID in the Group field was provided by a defaulting mechanism
;;	   rather than explicitly provided by the original provider of
;;	   the security descriptor.  This may affect the treatment of
;;	   the SID with respect to inheritence of a primary group.
;;
;;	SE_DACL_PRESENT - This boolean flag, when set, indicates that the
;;	   security descriptor contains a discretionary ACL.  If this
;;	   flag is set and the Dacl field of the SECURITY_DESCRIPTOR is
;;	   null, then a null ACL is explicitly being specified.
;;
;;	SE_DACL_DEFAULTED - This boolean flag, when set, indicates that the
;;	   ACL pointed to by the Dacl field was provided by a defaulting
;;	   mechanism rather than explicitly provided by the original
;;	   provider of the security descriptor.	 This may affect the
;;	   treatment of the ACL with respect to inheritence of an ACL.
;;	   This flag is ignored if the DaclPresent flag is not set.
;;
;;	SE_SACL_PRESENT - This boolean flag, when set,	indicates that the
;;	   security descriptor contains a system ACL pointed to by the
;;	   Sacl field.	If this flag is set and the Sacl field of the
;;	   SECURITY_DESCRIPTOR is null, then an empty (but present)
;;	   ACL is being specified.
;;
;;	SE_SACL_DEFAULTED - This boolean flag, when set, indicates that the
;;	   ACL pointed to by the Sacl field was provided by a defaulting
;;	   mechanism rather than explicitly provided by the original
;;	   provider of the security descriptor.	 This may affect the
;;	   treatment of the ACL with respect to inheritence of an ACL.
;;	   This flag is ignored if the SaclPresent flag is not set.
;;
;;	SE_SELF_RELATIVE - This boolean flag, when set, indicates that the
;;	   security descriptor is in self-relative form.  In this form,
;;	   all fields of the security descriptor are contiguous in memory
;;	   and all pointer fields are expressed as offsets from the
;;	   beginning of the security descriptor.  This form is useful
;;	   for treating security descriptors as opaque data structures
;;	   for transmission in communication protocol or for storage on
;;	   secondary media.
;;
;;
;;
;; Pictorially the structure of a security descriptor is as follows:
;;
;;	3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;	1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;	+---------------------------------------------------------------+
;;	|	    Control	       |Reserved1 (SBZ)|   Revision    |
;;	+---------------------------------------------------------------+
;;	|			    Owner			       |
;;	+---------------------------------------------------------------+
;;	|			    Group			       |
;;	+---------------------------------------------------------------+
;;	|			    Sacl			       |
;;	+---------------------------------------------------------------+
;;	|			    Dacl			       |
;;	+---------------------------------------------------------------+
;;
;; In general, this data structure should be treated opaquely to ensure future
;; compatibility.
;;
;;

SECURITY_DESCRIPTOR_RELATIVE STRUC
Revision		BYTE ?
Sbz1			BYTE ?
Control			SECURITY_DESCRIPTOR_CONTROL ?
Owner			DWORD ?
_Group			DWORD ?
Sacl			DWORD ?
Dacl			DWORD ?
SECURITY_DESCRIPTOR_RELATIVE ENDS
PISECURITY_DESCRIPTOR_RELATIVE typedef ptr SECURITY_DESCRIPTOR_RELATIVE

SECURITY_DESCRIPTOR	STRUC
Revision		BYTE ?
Sbz1			BYTE ?
Control			SECURITY_DESCRIPTOR_CONTROL ?
Owner			DWORD ?
_Group			DWORD ?
Sacl			DWORD ?
Dacl			DWORD ?
SECURITY_DESCRIPTOR	ENDS
PISECURITY_DESCRIPTOR	typedef ptr SECURITY_DESCRIPTOR

;; Where:
;;
;;     Revision - Contains the revision level of the security
;;	  descriptor.  This allows this structure to be passed between
;;	  systems or stored on disk even though it is expected to
;;	  change in the future.
;;
;;     Control - A set of flags which qualify the meaning of the
;;	  security descriptor or individual fields of the security
;;	  descriptor.
;;
;;     Owner - is a pointer to an SID representing an object's owner.
;;	  If this field is null, then no owner SID is present in the
;;	  security descriptor.	If the security descriptor is in
;;	  self-relative form, then this field contains an offset to
;;	  the SID, rather than a pointer.
;;
;;     Group - is a pointer to an SID representing an object's primary
;;	  group.  If this field is null, then no primary group SID is
;;	  present in the security descriptor.  If the security descriptor
;;	  is in self-relative form, then this field contains an offset to
;;	  the SID, rather than a pointer.
;;
;;     Sacl - is a pointer to a system ACL.  This field value is only
;;	  valid if the DaclPresent control flag is set.	 If the
;;	  SaclPresent flag is set and this field is null, then a null
;;	  ACL  is specified.  If the security descriptor is in
;;	  self-relative form, then this field contains an offset to
;;	  the ACL, rather than a pointer.
;;
;;     Dacl - is a pointer to a discretionary ACL.  This field value is
;;	  only valid if the DaclPresent control flag is set.  If the
;;	  DaclPresent flag is set and this field is null, then a null
;;	  ACL (unconditionally granting access) is specified.  If the
;;	  security descriptor is in self-relative form, then this field
;;	  contains an offset to the ACL, rather than a pointer.
;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								     ;;
;;		Object Type list for AccessCheckByType		     ;;
;;								     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


LPGUID			typedef ptr GUID
OBJECT_TYPE_LIST	STRUC
Level			WORD ?
Sbz			WORD ?
ObjectType		LPGUID ?
OBJECT_TYPE_LIST	ENDS
POBJECT_TYPE_LIST	typedef ptr OBJECT_TYPE_LIST

;;
;; DS values for Level
;;

ACCESS_OBJECT_GUID	 equ 0
ACCESS_PROPERTY_SET_GUID equ 1
ACCESS_PROPERTY_GUID	 equ 2

ACCESS_MAX_LEVEL	 equ 4

;;
;; Parameters to NtAccessCheckByTypeAndAditAlarm
;;

AuditEventObjectAccess			equ 0
AuditEventDirectoryServiceAccess	equ 1

AUDIT_ALLOW_NO_PRIVILEGE		equ 0x1
AUDIT_EVENT_TYPE			typedef sdword
;;
;; DS values for Source and ObjectTypeName
;;

;ACCESS_DS_SOURCE_A		equ <"DS">
;ACCESS_DS_SOURCE_W		equ <"DS">
;ACCESS_DS_OBJECT_TYPE_NAME_A	equ <"Directory Service Object">
;ACCESS_DS_OBJECT_TYPE_NAME_W	equ <"Directory Service Object">

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								     ;;
;;		Privilege Related Data Structures		     ;;
;;								     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;
;; Privilege attributes
;;

SE_PRIVILEGE_ENABLED_BY_DEFAULT equ 0x00000001
SE_PRIVILEGE_ENABLED		equ 0x00000002
SE_PRIVILEGE_USED_FOR_ACCESS	equ 0x80000000

;;
;; Privilege Set Control flags
;;

PRIVILEGE_SET_ALL_NECESSARY    equ 1

;;
;;  Privilege Set - This is defined for a privilege set of one.
;;		   If more than one privilege is needed, then this structure
;;		   will need to be allocated with more space.
;;
;;  Note: don't change this structure without fixing the INITIAL_PRIVILEGE_SET
;;  structure (defined in se.h)
;;

PRIVILEGE_SET	STRUC
PrivilegeCount	DWORD ?
Control		DWORD ?
Privilege	LUID_AND_ATTRIBUTES ANYSIZE_ARRAY dup(<?>)
PRIVILEGE_SET	ENDS
PPRIVILEGE_SET	typedef ptr PRIVILEGE_SET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								     ;;
;;		NT Defined Privileges				     ;;
;;								     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SE_CREATE_TOKEN_NAME		equ <TEXT("SeCreateTokenPrivilege")>
SE_ASSIGNPRIMARYTOKEN_NAME	equ <TEXT("SeAssignPrimaryTokenPrivilege")>
SE_LOCK_MEMORY_NAME		equ <TEXT("SeLockMemoryPrivilege")>
SE_INCREASE_QUOTA_NAME		equ <TEXT("SeIncreaseQuotaPrivilege")>
SE_UNSOLICITED_INPUT_NAME	equ <TEXT("SeUnsolicitedInputPrivilege")>
SE_MACHINE_ACCOUNT_NAME		equ <TEXT("SeMachineAccountPrivilege")>
SE_TCB_NAME			equ <TEXT("SeTcbPrivilege")>
SE_SECURITY_NAME		equ <TEXT("SeSecurityPrivilege")>
SE_TAKE_OWNERSHIP_NAME		equ <TEXT("SeTakeOwnershipPrivilege")>
SE_LOAD_DRIVER_NAME		equ <TEXT("SeLoadDriverPrivilege")>
SE_SYSTEM_PROFILE_NAME		equ <TEXT("SeSystemProfilePrivilege")>
SE_SYSTEMTIME_NAME		equ <TEXT("SeSystemtimePrivilege")>
SE_PROF_SINGLE_PROCESS_NAME	equ <TEXT("SeProfileSingleProcessPrivilege")>
SE_INC_BASE_PRIORITY_NAME	equ <TEXT("SeIncreaseBasePriorityPrivilege")>
SE_CREATE_PAGEFILE_NAME		equ <TEXT("SeCreatePagefilePrivilege")>
SE_CREATE_PERMANENT_NAME	equ <TEXT("SeCreatePermanentPrivilege")>
SE_BACKUP_NAME			equ <TEXT("SeBackupPrivilege")>
SE_RESTORE_NAME			equ <TEXT("SeRestorePrivilege")>
SE_SHUTDOWN_NAME		equ <TEXT("SeShutdownPrivilege")>
SE_DEBUG_NAME			equ <TEXT("SeDebugPrivilege")>
SE_AUDIT_NAME			equ <TEXT("SeAuditPrivilege")>
SE_SYSTEM_ENVIRONMENT_NAME	equ <TEXT("SeSystemEnvironmentPrivilege")>
SE_CHANGE_NOTIFY_NAME		equ <TEXT("SeChangeNotifyPrivilege")>
SE_REMOTE_SHUTDOWN_NAME		equ <TEXT("SeRemoteShutdownPrivilege")>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								 ;;
;;	    Security Quality Of Service				 ;;
;;								 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;
;; Impersonation Level
;;
;; Impersonation level is represented by a pair of bits in Windows.
;; If a new impersonation level is added or lowest value is changed from
;; 0 to something else, fix the Windows CreateFile call.
;;

SecurityAnonymous	equ 0
SecurityIdentification	equ 1
SecurityImpersonation	equ 2
SecurityDelegation	equ 3

SECURITY_MAX_IMPERSONATION_LEVEL equ SecurityDelegation

DEFAULT_IMPERSONATION_LEVEL equ SecurityImpersonation

SECURITY_IMPERSONATION_LEVEL typedef dword

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								 ;;
;;	    Token Object Definitions				 ;;
;;								 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;
;; Token Specific Access Rights.
;;

TOKEN_ASSIGN_PRIMARY	equ 0x0001
TOKEN_DUPLICATE		equ 0x0002
TOKEN_IMPERSONATE	equ 0x0004
TOKEN_QUERY		equ 0x0008
TOKEN_QUERY_SOURCE	equ 0x0010
TOKEN_ADJUST_PRIVILEGES equ 0x0020
TOKEN_ADJUST_GROUPS	equ 0x0040
TOKEN_ADJUST_DEFAULT	equ 0x0080
TOKEN_ADJUST_SESSIONID	equ 0x0100

TOKEN_ALL_ACCESS equ STANDARD_RIGHTS_REQUIRED  or \
		     TOKEN_ASSIGN_PRIMARY      or \
		     TOKEN_DUPLICATE	       or \
		     TOKEN_IMPERSONATE	       or \
		     TOKEN_QUERY	       or \
		     TOKEN_QUERY_SOURCE	       or \
		     TOKEN_ADJUST_PRIVILEGES   or \
		     TOKEN_ADJUST_GROUPS       or \
		     TOKEN_ADJUST_SESSIONID    or \
		     TOKEN_ADJUST_DEFAULT

TOKEN_READ	equ STANDARD_RIGHTS_READ or TOKEN_QUERY
TOKEN_WRITE	equ STANDARD_RIGHTS_WRITE   or \
		    TOKEN_ADJUST_PRIVILEGES or \
		    TOKEN_ADJUST_GROUPS	    or \
		    TOKEN_ADJUST_DEFAULT

TOKEN_EXECUTE	equ STANDARD_RIGHTS_EXECUTE

TOKEN_TYPE	typedef DWORD

;;
;;
;; Token Types
;;

    TokenPrimary		equ 1
    TokenImpersonation		equ 2

;;
;; Token Information Classes.
;;
    TOKEN_INFORMATION_CLASS	typedef dword

    TokenUser			equ 1
    TokenGroups			equ 2
    TokenPrivileges		equ 3
    TokenOwner			equ 4
    TokenPrimaryGroup		equ 5
    TokenDefaultDacl		equ 6
    TokenSource			equ 7
    TokenType			equ 8
    TokenImpersonationLevel	equ 9
    TokenStatistics		equ 10
    TokenRestrictedSids		equ 11
    TokenSessionId		equ 12


;;
;; Token information class structures
;;


TOKEN_USER		STRUC
User			SID_AND_ATTRIBUTES <>
TOKEN_USER		ENDS
PTOKEN_USER		typedef ptr TOKEN_USER

TOKEN_GROUPS		STRUC
GroupCount		dd ?
Groups			SID_AND_ATTRIBUTES ANYSIZE_ARRAY dup(<>)
TOKEN_GROUPS		ENDS
PTOKEN_GROUPS		typedef ptr TOKEN_GROUPS


TOKEN_PRIVILEGES	STRUC
PrivilegeCount		dd ?
Privileges		LUID_AND_ATTRIBUTES ANYSIZE_ARRAY dup(<>)
TOKEN_PRIVILEGES	ENDS
PTOKEN_PRIVILEGES	typedef ptr TOKEN_PRIVILEGES


TOKEN_OWNER		STRUC
Owner			PSID ?
TOKEN_OWNER		ENDS
PTOKEN_OWNER		typedef ptr TOKEN_OWNER


TOKEN_PRIMARY_GROUP	STRUC
PrimaryGroup		PSID ?
TOKEN_PRIMARY_GROUP	ENDS

PTOKEN_PRIMARY_GROUP	typedef ptr TOKEN_PRIMARY_GROUP


TOKEN_DEFAULT_DACL	STRUC
DefaultDacl		PACL ?
TOKEN_DEFAULT_DACL	ENDS
PTOKEN_DEFAULT_DACL	typedef ptr TOKEN_DEFAULT_DACL

TOKEN_SOURCE_LENGTH	equ 8

TOKEN_SOURCE		STRUC
SourceName		db TOKEN_SOURCE_LENGTH dup(?)
SourceIdentifier	LUID <>
TOKEN_SOURCE		ENDS
PTOKEN_SOURCE		typedef ptr TOKEN_SOURCE


TOKEN_STATISTICS	STRUC
TokenId			LUID <>
AuthenticationId	LUID <>
ExpirationTime		LARGE_INTEGER <>
TokenType		TOKEN_TYPE ?
ImpersonationLevel	SECURITY_IMPERSONATION_LEVEL ?
DynamicCharged		DWORD ?
DynamicAvailable	DWORD ?
GroupCount		DWORD ?
PrivilegeCount		DWORD ?
ModifiedId		LUID <>
TOKEN_STATISTICS	ENDS
PTOKEN_STATISTICS	typedef ptr TOKEN_STATISTICS


TOKEN_CONTROL		STRUC
TokenId			LUID <>
AuthenticationId	LUID <>
ModifiedId		LUID <>
TokenSource		TOKEN_SOURCE <>
TOKEN_CONTROL		ENDS
PTOKEN_CONTROL		typedef ptr TOKEN_CONTROL

;;
;; Security Tracking Mode
;;

SECURITY_DYNAMIC_TRACKING	equ TRUE
SECURITY_STATIC_TRACKING	equ FALSE

SECURITY_CONTEXT_TRACKING_MODE	typedef BOOLEAN
PSECURITY_CONTEXT_TRACKING_MODE typedef ptr SECURITY_CONTEXT_TRACKING_MODE

;;
;; Quality Of Service
;;

SECURITY_QUALITY_OF_SERVICE	STRUC
_Length				dd ?
ImpersonationLevel		SECURITY_IMPERSONATION_LEVEL ?
ContextTrackingMode		SECURITY_CONTEXT_TRACKING_MODE ?
EffectiveOnly			BOOLEAN ?
SECURITY_QUALITY_OF_SERVICE	ENDS
PSECURITY_QUALITY_OF_SERVICE	typedef ptr SECURITY_QUALITY_OF_SERVICE

;;
;; Used to represent information related to a thread impersonation
;;

SE_IMPERSONATION_STATE		STRUC
Token				PACCESS_TOKEN ?
CopyOnOpen			BOOLEAN ?
EffectiveOnly			BOOLEAN ?
Level				SECURITY_IMPERSONATION_LEVEL ?
SE_IMPERSONATION_STATE		ENDS
PSE_IMPERSONATION_STATE		typedef ptr SE_IMPERSONATION_STATE

SECURITY_INFORMATION		typedef DWORD
PSECURITY_INFORMATION		typedef ptr DWORD

OWNER_SECURITY_INFORMATION	equ 0x00000001
GROUP_SECURITY_INFORMATION	equ 0x00000002
DACL_SECURITY_INFORMATION	equ 0x00000004
SACL_SECURITY_INFORMATION	equ 0x00000008
PROCESS_TERMINATE		equ 0x0001
PROCESS_CREATE_THREAD		equ 0x0002
PROCESS_SET_SESSIONID		equ 0x0004
PROCESS_VM_OPERATION		equ 0x0008
PROCESS_VM_READ			equ 0x0010
PROCESS_VM_WRITE		equ 0x0020
PROCESS_DUP_HANDLE		equ 0x0040
PROCESS_CREATE_PROCESS		equ 0x0080
PROCESS_SET_QUOTA		equ 0x0100
PROCESS_SET_INFORMATION		equ 0x0200
PROCESS_QUERY_INFORMATION	equ 0x0400
PROCESS_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0xFFF

MAXIMUM_PROCESSORS		equ 32

THREAD_TERMINATE		equ 0x0001
THREAD_SUSPEND_RESUME		equ 0x0002
THREAD_GET_CONTEXT		equ 0x0008
THREAD_SET_CONTEXT		equ 0x0010
THREAD_SET_INFORMATION		equ 0x0020
THREAD_QUERY_INFORMATION	equ 0x0040
THREAD_SET_THREAD_TOKEN		equ 0x0080
THREAD_IMPERSONATE		equ 0x0100
THREAD_DIRECT_IMPERSONATION	equ 0x0200
THREAD_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3FF

JOB_OBJECT_ASSIGN_PROCESS	equ 0x0001
JOB_OBJECT_SET_ATTRIBUTES	equ 0x0002
JOB_OBJECT_QUERY		equ 0x0004
JOB_OBJECT_TERMINATE		equ 0x0008
JOB_OBJECT_SET_SECURITY_ATTRIBUTES equ 0x0010
JOB_OBJECT_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x1F
TLS_MINIMUM_AVAILABLE		equ 64

NT_TIB				STRUC
ExceptionList			PVOID ? ; EXCEPTION_REGISTRATION_RECORD *
StackBase			PVOID ?
StackLimit			PVOID ?
SubSystemTib			PVOID ?
UNION
  FiberData			PVOID ?
  Version			DWORD ?
ENDS
ArbitraryUserPointer		PVOID ?
Self				PVOID ?
NT_TIB				ENDS
PNT_TIB				typedef ptr NT_TIB

if not defined(_X86_) and not defined(_IA64_)
WX86				equ 1
endif

THREAD_BASE_PRIORITY_LOWRT	equ 15	;; value that gets a thread to LowRealtime-1
THREAD_BASE_PRIORITY_MAX	equ 2	;; maximum thread base priority boost
THREAD_BASE_PRIORITY_MIN	equ -2	;; minimum thread base priority boost
THREAD_BASE_PRIORITY_IDLE	equ -15 ;; value that gets a thread to idle

QUOTA_LIMITS			STRUC
PagedPoolLimit			SIZE_T ?
NonPagedPoolLimit		SIZE_T ?
MinimumWorkingSetSize		DWORD  ?
MaximumWorkingSetSize		DWORD  ?
PagefileLimit			SIZE_T ?
TimeLimit			LARGE_INTEGER <>
QUOTA_LIMITS			ENDS
PQUOTA_LIMITS			typedef ptr QUOTA_LIMITS

JOBOBJECT_BASIC_ACCOUNTING_INFORMATION STRUC
TotalUserTime			LARGE_INTEGER <>
TotalKernelTime			LARGE_INTEGER <>
ThisPeriodTotalUserTime		LARGE_INTEGER <>
ThisPeriodTotalKernelTime	LARGE_INTEGER <>
TotalPageFaultCount		dd ?
TotalProcesses			dd ?
ActiveProcesses			dd ?
TotalTerminatedProcesses	dd ?
JOBOBJECT_BASIC_ACCOUNTING_INFORMATION ENDS
PJOBOBJECT_BASIC_ACCOUNTING_INFORMATION typedef ptr JOBOBJECT_BASIC_ACCOUNTING_INFORMATION

JOBOBJECT_BASIC_LIMIT_INFORMATION STRUC
PerProcessUserTimeLimit		LARGE_INTEGER <>
PerJobUserTimeLimit		LARGE_INTEGER <>
LimitFlags			dd ?
MinimumWorkingSetSize		dd ?
MaximumWorkingSetSize		dd ?
ActiveProcessLimit		dd ?
Affinity			dd ?
PriorityClass			dd ?
JOBOBJECT_BASIC_LIMIT_INFORMATION ENDS
PJOBOBJECT_BASIC_LIMIT_INFORMATION typedef ptr JOBOBJECT_BASIC_LIMIT_INFORMATION

JOBOBJECT_BASIC_PROCESS_ID_LIST STRUC
NumberOfAssignedProcesses	dd ?
NumberOfProcessIdsInList	dd ?
ProcessIdLis			UINT_PTR ?
JOBOBJECT_BASIC_PROCESS_ID_LIST ENDS
PJOBOBJECT_BASIC_PROCESS_ID_LIST typedef ptr JOBOBJECT_BASIC_PROCESS_ID_LIST

JOBOBJECT_BASIC_UI_RESTRICTIONS STRUC
UIRestrictionsClass		dd ?
JOBOBJECT_BASIC_UI_RESTRICTIONS ENDS
PJOBOBJECT_BASIC_UI_RESTRICTIONS typedef ptr JOBOBJECT_BASIC_UI_RESTRICTIONS

JOBOBJECT_SECURITY_LIMIT_INFORMATION STRUC
SecurityLimitFlags		DWORD ?
JobToken			HANDLE ?
SidsToDisable			PTOKEN_GROUPS ?
PrivilegesToDelete		PTOKEN_PRIVILEGES ?
RestrictedSids			PTOKEN_GROUPS ?
JOBOBJECT_SECURITY_LIMIT_INFORMATION ENDS
PJOBOBJECT_SECURITY_LIMIT_INFORMATION typedef ptr JOBOBJECT_SECURITY_LIMIT_INFORMATION

JOBOBJECT_END_OF_JOB_TIME_INFORMATION STRUC
EndOfJobTimeAction		DWORD ?
JOBOBJECT_END_OF_JOB_TIME_INFORMATION ENDS
PJOBOBJECT_END_OF_JOB_TIME_INFORMATION typedef ptr JOBOBJECT_END_OF_JOB_TIME_INFORMATION

JOBOBJECT_ASSOCIATE_COMPLETION_PORT STRUC
CompletionKey			PVOID ?
CompletionPort			HANDLE ?
JOBOBJECT_ASSOCIATE_COMPLETION_PORT ENDS
PJOBOBJECT_ASSOCIATE_COMPLETION_PORT typedef ptr JOBOBJECT_ASSOCIATE_COMPLETION_PORT

JOB_OBJECT_TERMINATE_AT_END_OF_JOB	equ 0
JOB_OBJECT_POST_AT_END_OF_JOB		equ 1

;;
;; Completion Port Messages for job objects
;;
;; These values are returned via the lpNumberOfBytesTransferred parameter
;;

JOB_OBJECT_MSG_END_OF_JOB_TIME		equ 1
JOB_OBJECT_MSG_END_OF_PROCESS_TIME	equ 2
JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT	equ 3
JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO	equ 4


JOB_OBJECT_LIMIT_WORKINGSET		equ 0x00000001
JOB_OBJECT_LIMIT_PROCESS_TIME		equ 0x00000002
JOB_OBJECT_LIMIT_JOB_TIME		equ 0x00000004
JOB_OBJECT_LIMIT_ACTIVE_PROCESS		equ 0x00000008
JOB_OBJECT_LIMIT_AFFINITY		equ 0x00000010
JOB_OBJECT_LIMIT_PRIORITY_CLASS		equ 0x00000020
JOB_OBJECT_LIMIT_PRESERVE_JOB_TIME	equ 0x00000040

JOB_OBJECT_LIMIT_VALID_FLAGS		equ 0x0000007f

;;
;; UI restrictions for jobs
;;

JOB_OBJECT_UILIMIT_NONE			equ 0x00000000

JOB_OBJECT_UILIMIT_HANDLES		equ 0x00000001
JOB_OBJECT_UILIMIT_READCLIPBOARD	equ 0x00000002
JOB_OBJECT_UILIMIT_WRITECLIPBOARD	equ 0x00000004
JOB_OBJECT_UILIMIT_SYSTEMPARAMETERS	equ 0x00000008
JOB_OBJECT_UILIMIT_DISPLAYSETTINGS	equ 0x00000010
JOB_OBJECT_UILIMIT_GLOBALATOMS		equ 0x00000020
JOB_OBJECT_UILIMIT_DESKTOP		equ 0x00000040
JOB_OBJECT_UILIMIT_EXITWINDOWS		equ 0x00000080

JOB_OBJECT_UILIMIT_ALL			equ 0x000000FF

JOB_OBJECT_UI_VALID_FLAGS		equ 0x000000FF

JOB_OBJECT_SECURITY_NO_ADMIN		equ 0x00000001
JOB_OBJECT_SECURITY_RESTRICTED_TOKEN	equ 0x00000002
JOB_OBJECT_SECURITY_ONLY_TOKEN		equ 0x00000004
JOB_OBJECT_SECURITY_FILTER_TOKENS	equ 0x00000008

JOB_OBJECT_SECURITY_VALID_FLAGS		equ 0x0000000f

    JobObjectBasicAccountingInformation equ 1
    JobObjectBasicLimitInformation	equ 2
    JobObjectBasicProcessIdList		equ 3
    JobObjectBasicUIRestrictions	equ 4
    JobObjectSecurityLimitInformation	equ 5
    JobObjectEndOfJobTimeInformation	equ 6
    JobObjectAssociateCompletionPortInformation equ 7
    MaxJobObjectInfoClass		equ 8

JOBOBJECTINFOCLASS	typedef SINT

EVENT_MODIFY_STATE	equ 0x0002
EVENT_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3
MUTANT_QUERY_STATE	equ 0x0001

MUTANT_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or MUTANT_QUERY_STATE
SEMAPHORE_MODIFY_STATE	equ 0x0002
SEMAPHORE_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3

;;
;; Timer Specific Access Rights.
;;

TIMER_QUERY_STATE	equ 0x0001
TIMER_MODIFY_STATE	equ 0x0002
TIMER_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or \
			    TIMER_QUERY_STATE or TIMER_MODIFY_STATE


TIME_ZONE_ID_UNKNOWN	equ 0
TIME_ZONE_ID_STANDARD	equ 1
TIME_ZONE_ID_DAYLIGHT	equ 2

PROCESSOR_INTEL_386	equ 386
PROCESSOR_INTEL_486	equ 486
PROCESSOR_INTEL_PENTIUM equ 586
PROCESSOR_MIPS_R4000	equ 4000	;; incl R4101 & R3910 for Windows CE
PROCESSOR_ALPHA_21064	equ 21064
PROCESSOR_PPC_601	equ 601
PROCESSOR_PPC_603	equ 603
PROCESSOR_PPC_604	equ 604
PROCESSOR_PPC_620	equ 620
PROCESSOR_HITACHI_SH3	equ 10003	;; Windows CE
PROCESSOR_HITACHI_SH3E	equ 10004	;; Windows CE
PROCESSOR_HITACHI_SH4	equ 10005	;; Windows CE
PROCESSOR_MOTOROLA_821	equ 821		;; Windows CE
PROCESSOR_SHx_SH3	equ 103		;; Windows CE
PROCESSOR_SHx_SH4	equ 104		;; Windows CE
PROCESSOR_STRONGARM	equ 2577	;; Windows CE - 0xA11
PROCESSOR_ARM720	equ 1824	;; Windows CE - 0x720
PROCESSOR_ARM820	equ 2080	;; Windows CE - 0x820
PROCESSOR_ARM920	equ 2336	;; Windows CE - 0x920
PROCESSOR_ARM_7TDMI	equ 70001	;; Windows CE

PROCESSOR_ARCHITECTURE_INTEL		equ 0
PROCESSOR_ARCHITECTURE_MIPS		equ 1
PROCESSOR_ARCHITECTURE_ALPHA		equ 2
PROCESSOR_ARCHITECTURE_PPC		equ 3
PROCESSOR_ARCHITECTURE_SHX		equ 4
PROCESSOR_ARCHITECTURE_ARM		equ 5
PROCESSOR_ARCHITECTURE_IA64		equ 6
PROCESSOR_ARCHITECTURE_ALPHA64		equ 7
PROCESSOR_ARCHITECTURE_UNKNOWN		equ 0xFFFF

PF_FLOATING_POINT_PRECISION_ERRATA	equ 0
PF_FLOATING_POINT_EMULATED		equ 1
PF_COMPARE_EXCHANGE_DOUBLE		equ 2
PF_MMX_INSTRUCTIONS_AVAILABLE		equ 3
PF_PPC_MOVEMEM_64BIT_OK			equ 4
PF_ALPHA_BYTE_INSTRUCTIONS		equ 5
PF_XMMI_INSTRUCTIONS_AVAILABLE		equ 6
PF_AMD3D_INSTRUCTIONS_AVAILABLE		equ 7
SYSTEM_FLAG_REMOTE_BOOT_CLIENT		equ 0x00000001
SYSTEM_FLAG_DISKLESS_CLIENT		equ 0x00000002

MEMORY_BASIC_INFORMATION	STRUC SIZE_T
BaseAddress			PVOID ?
AllocationBase			PVOID ?
AllocationProtect		DWORD ?
RegionSize			SIZE_T ?
State				DWORD ?
Protect				DWORD ?
_Type				DWORD ?
MEMORY_BASIC_INFORMATION	ENDS
PMEMORY_BASIC_INFORMATION	typedef ptr MEMORY_BASIC_INFORMATION

MEMORY_BASIC_INFORMATION_VLM	STRUC
UNION
  BaseAddress			PVOID64 ?
  BaseAddressAsUlongLong	ULONGLONG ?
ENDS
UNION
  AllocationBase		PVOID64 ?
  AllocationBaseAsUlongLong	ULONGLONG ?
ENDS
RegionSize			ULONGLONG ?
AllocationProtect		dd ?
State				dd ?
Protect				dd ?
_Type				dd ?
MEMORY_BASIC_INFORMATION_VLM	ENDS
PMEMORY_BASIC_INFORMATION_VLM	typedef ptr MEMORY_BASIC_INFORMATION_VLM

SECTION_QUERY			equ 0x0001
SECTION_MAP_WRITE		equ 0x0002
SECTION_MAP_READ		equ 0x0004
SECTION_MAP_EXECUTE		equ 0x0008
SECTION_EXTEND_SIZE		equ 0x0010

SECTION_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED or SECTION_QUERY or \
				    SECTION_MAP_WRITE	or \
				    SECTION_MAP_READ	or \
				    SECTION_MAP_EXECUTE or \
				    SECTION_EXTEND_SIZE

PAGE_NOACCESS			equ 0x01
PAGE_READONLY			equ 0x02
PAGE_READWRITE			equ 0x04
PAGE_WRITECOPY			equ 0x08
PAGE_EXECUTE			equ 0x10
PAGE_EXECUTE_READ		equ 0x20
PAGE_EXECUTE_READWRITE		equ 0x40
PAGE_EXECUTE_WRITECOPY		equ 0x80
PAGE_GUARD			equ 0x100
PAGE_NOCACHE			equ 0x200
PAGE_WRITECOMBINE		equ 0x400

MEM_COMMIT			equ 0x1000
MEM_RESERVE			equ 0x2000
MEM_DECOMMIT			equ 0x4000
MEM_RELEASE			equ 0x8000
MEM_FREE			equ 0x10000
MEM_PRIVATE			equ 0x20000
MEM_MAPPED			equ 0x40000
MEM_RESET			equ 0x80000
MEM_TOP_DOWN			equ 0x100000
MEM_4MB_PAGES			equ 0x80000000
SEC_FILE			equ 0x800000
SEC_IMAGE			equ 0x1000000
SEC_VLM				equ 0x2000000
SEC_RESERVE			equ 0x4000000
SEC_COMMIT			equ 0x8000000
SEC_NOCACHE			equ 0x10000000
MEM_IMAGE			equ SEC_IMAGE

;;
;; Define access rights to files and directories
;;

;;
;; The FILE_READ_DATA and FILE_WRITE_DATA constants are also defined in
;; devioctl.h as FILE_READ_ACCESS and FILE_WRITE_ACCESS. The values for these
;; constants *MUST* always be in sync.
;; The values are redefined in devioctl.h because they must be available to
;; both DOS and NT.
;;

FILE_READ_DATA			equ 0x0001  ;; file & pipe
FILE_LIST_DIRECTORY		equ 0x0001  ;; directory

FILE_WRITE_DATA			equ 0x0002  ;; file & pipe
FILE_ADD_FILE			equ 0x0002  ;; directory

FILE_APPEND_DATA		equ 0x0004  ;; file
FILE_ADD_SUBDIRECTORY		equ 0x0004  ;; directory
FILE_CREATE_PIPE_INSTANCE	equ 0x0004  ;; named pipe

FILE_READ_EA			equ 0x0008  ;; file & directory
FILE_WRITE_EA			equ 0x0010  ;; file & directory
FILE_EXECUTE			equ 0x0020  ;; file
FILE_TRAVERSE			equ 0x0020  ;; directory
FILE_DELETE_CHILD		equ 0x0040  ;; directory
FILE_READ_ATTRIBUTES		equ 0x0080  ;; all
FILE_WRITE_ATTRIBUTES		equ 0x0100  ;; all

FILE_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3FF
FILE_GENERIC_READ	equ STANDARD_RIGHTS_READ or \
			    FILE_READ_DATA	 or \
			    FILE_READ_ATTRIBUTES or \
			    FILE_READ_EA	 or \
			    SYNCHRONIZE
FILE_GENERIC_WRITE	equ STANDARD_RIGHTS_WRITE or \
			    FILE_WRITE_DATA	  or \
			    FILE_WRITE_ATTRIBUTES or \
			    FILE_WRITE_EA	  or \
			    FILE_APPEND_DATA	  or \
			    SYNCHRONIZE
FILE_GENERIC_EXECUTE	equ STANDARD_RIGHTS_EXECUTE or \
			    FILE_READ_ATTRIBUTES    or \
			    FILE_EXECUTE	    or \
			    SYNCHRONIZE

FILE_SHARE_READ			equ 0x00000001
FILE_SHARE_WRITE		equ 0x00000002
FILE_SHARE_DELETE		equ 0x00000004
FILE_ATTRIBUTE_READONLY		equ 0x00000001
FILE_ATTRIBUTE_HIDDEN		equ 0x00000002
FILE_ATTRIBUTE_SYSTEM		equ 0x00000004
FILE_ATTRIBUTE_DIRECTORY	equ 0x00000010
FILE_ATTRIBUTE_ARCHIVE		equ 0x00000020
FILE_ATTRIBUTE_ENCRYPTED	equ 0x00000040
FILE_ATTRIBUTE_NORMAL		equ 0x00000080
FILE_ATTRIBUTE_TEMPORARY	equ 0x00000100
FILE_ATTRIBUTE_SPARSE_FILE	equ 0x00000200
FILE_ATTRIBUTE_REPARSE_POINT	equ 0x00000400
FILE_ATTRIBUTE_COMPRESSED	equ 0x00000800
FILE_ATTRIBUTE_OFFLINE		equ 0x00001000
FILE_ATTRIBUTE_NOT_CONTENT_INDEXED equ 0x00002000
FILE_NOTIFY_CHANGE_FILE_NAME	equ 0x00000001
FILE_NOTIFY_CHANGE_DIR_NAME	equ 0x00000002
FILE_NOTIFY_CHANGE_ATTRIBUTES	equ 0x00000004
FILE_NOTIFY_CHANGE_SIZE		equ 0x00000008
FILE_NOTIFY_CHANGE_LAST_WRITE	equ 0x00000010
FILE_NOTIFY_CHANGE_LAST_ACCESS	equ 0x00000020
FILE_NOTIFY_CHANGE_CREATION	equ 0x00000040
FILE_NOTIFY_CHANGE_SECURITY	equ 0x00000100
FILE_ACTION_ADDED		equ 0x00000001
FILE_ACTION_REMOVED		equ 0x00000002
FILE_ACTION_MODIFIED		equ 0x00000003
FILE_ACTION_RENAMED_OLD_NAME	equ 0x00000004
FILE_ACTION_RENAMED_NEW_NAME	equ 0x00000005
MAILSLOT_NO_MESSAGE		equ -1
MAILSLOT_WAIT_FOREVER		equ -1
FILE_CASE_SENSITIVE_SEARCH	equ 0x00000001
FILE_CASE_PRESERVED_NAMES	equ 0x00000002
FILE_UNICODE_ON_DISK		equ 0x00000004
FILE_PERSISTENT_ACLS		equ 0x00000008
FILE_FILE_COMPRESSION		equ 0x00000010
FILE_VOLUME_QUOTAS		equ 0x00000020
FILE_SUPPORTS_SPARSE_FILES	equ 0x00000040
FILE_SUPPORTS_REPARSE_POINTS	equ 0x00000080
FILE_SUPPORTS_REMOTE_STORAGE	equ 0x00000100
FILE_VOLUME_IS_COMPRESSED	equ 0x00008000
FILE_SUPPORTS_OBJECT_IDS	equ 0x00010000
FILE_SUPPORTS_ENCRYPTION	equ 0x00020000

;;
;; Define the file notification information structure
;;

FILE_NOTIFY_INFORMATION STRUC
NextEntryOffset		dd ?
Action			dd ?
FileNameLength		dd ?
FileName		WCHAR ?
FILE_NOTIFY_INFORMATION ENDS
PFILE_NOTIFY_INFORMATION typedef ptr FILE_NOTIFY_INFORMATION

;;
;; Define segement buffer structure for scatter/gather read/write.
;;

FILE_SEGMENT_ELEMENT	UNION
Buffer			PVOID64 ?
Alignment		ULONGLONG ?
FILE_SEGMENT_ELEMENT	ENDS
PFILE_SEGMENT_ELEMENT	typedef ptr FILE_SEGMENT_ELEMENT

;;
;; Structures for FSCTL_SET_REPARSE_POINT, FSCTL_GET_REPARSE_POINT, and FSCTL_DELETE_REPARSE_POINT
;;

;;
;; The reparse structure is used by layered drivers to store data in a
;; reparse point. The constraints on reparse tags are defined below.
;; This version of the reparse data buffer is only for Microsoft tags.
;;

REPARSE_DATA_BUFFER	STRUC
ReparseTag		dd ?
ReparseDataLength	dw ?
Reserved		dw ?
UNION
  STRUC SymbolicLinkReparseBuffer
   SubstituteNameOffset dw ?
   SubstituteNameLength dw ?
   PrintNameOffset	dw ?
   PrintNameLength	dw ?
   PathBuffer		dw ?
  ENDS
  STRUC MountPointReparseBuffer
   SubstituteNameOffset dw ?
   SubstituteNameLength dw ?
   PrintNameOffset	dw ?
   PrintNameLength	dw ?
   PathBuffer		dw ?
  ENDS
  STRUC GenericReparseBuffer
   DataBuffer		db ?
  ENDS
ENDS
REPARSE_DATA_BUFFER	ENDS
PREPARSE_DATA_BUFFER	typedef ptr REPARSE_DATA_BUFFER

REPARSE_DATA_BUFFER_HEADER_SIZE equ FIELD_OFFSET(REPARSE_DATA_BUFFER, GenericReparseBuffer)

;;
;; The reparse GUID structure is used by all 3rd party layered drivers to
;; store data in a reparse point. For non-Microsoft tags, The GUID field
;; cannot be GUID_NULL.
;; The constraints on reparse tags are defined below.
;; Microsoft tags can also be uses with this format of the reparse point buffer.
;;

REPARSE_GUID_DATA_BUFFER STRUC
ReparseTag		dd ?
ReparseDataLength	dw ?
Reserved		dw ?
ReparseGuid		GUID <>
STRUC GenericReparseBuffer
 DataBuffer		db ?
ENDS
REPARSE_GUID_DATA_BUFFER ENDS
PREPARSE_GUID_DATA_BUFFER typedef ptr REPARSE_GUID_DATA_BUFFER

REPARSE_GUID_DATA_BUFFER_HEADER_SIZE   equ FIELD_OFFSET(REPARSE_GUID_DATA_BUFFER, GenericReparseBuffer)


;;
;; The reparse information structure is used to return information about
;; a reparse point to the caller.
;;

REPARSE_POINT_INFORMATION	STRUC
ReparseDataLength		dw ?
UnparsedNameLength		dw ?
REPARSE_POINT_INFORMATION	ENDS
PREPARSE_POINT_INFORMATION	typedef ptr REPARSE_POINT_INFORMATION

;;
;; Maximum allowed size of the reparse data.
;;

MAXIMUM_REPARSE_DATA_BUFFER_SIZE	equ 16 * 1024

;;
;; Predefined reparse tags.
;; These tags need to avoid conflicting with IO_REMOUNT defined in ntos\inc\io.h
;;

IO_REPARSE_TAG_RESERVED_ZERO		equ 0
IO_REPARSE_TAG_RESERVED_ONE		equ 1

;;
;; The value of the following constant needs to satisfy the following conditions:
;;  (1) Be at least as large as the largest of the reserved tags.
;;  (2) Be strictly smaller than all the tags in use.
;;

IO_REPARSE_TAG_RESERVED_RANGE		equ IO_REPARSE_TAG_RESERVED_ONE

;;
;; The reparse tags are a DWORD. The 32 bits are laid out as follows:
;;
;;   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;  +-+-+-+-------------------------+-------------------------------+
;;  |M|L|N|   Reserved bits	   |	   Reparse Tag Value	   |
;;  +-+-+-+-------------------------+-------------------------------+
;;
;; M is the Microsoft bit. When set to 1, it denotes a tag owned by Microsoft.
;;   All ISVs must use a tag with a 0 in this position.
;;   Note: If a Microsoft tag is used by non-Microsoft software, the
;;   behavior is not defined.
;;
;; L is the high-latency bit. When set to 1, a file with this tag is
;;   expected to have a long latency to retrieve the first byte of data.
;;
;; N is name surrogate. When set to 1, the file represents another named
;;   entity in the system.
;;
;; The M, L, and N bits are OR-able.
;; The following macros check for the M, L and N bit values:
;;

;;
;; Macro to determine whether a reparse point tag corresponds to a tag
;; owned by Microsoft.
;;
IsReparseTagMicrosoft macro _tag
	exitm<_tag and 0x80000000>
	endm

;;
;; Macro to determine whether a reparse point tag corresponds to a file
;; that is to be displayed with the slow icon overlay.
;;
IsReparseTagHighLatency macro _tag
	exitm<_tag and 0x40000000>
	endm
;;
;; Macro to determine whether a reparse point tag corresponds to a file
;; that is to be displayed with the slow icon overlay.
;;
IsReparseTagNameSurrogate macro _tag
	exitm<_tag and 0x20000000>
	endm
;;
;; The following constant represents the bits that are valid to use in
;; reparse tags.
;;

IO_REPARSE_TAG_VALID_VALUES	equ 0xE000FFFF

;;
;; Macro to determine whether a reparse tag is a valid tag.
;;
IsReparseTagValid macro _tag
	exitm<not (_tag and (not IO_REPARSE_TAG_VALID_VALUES)) and (_tag GT IO_REPARSE_TAG_RESERVED_RANGE)>
	endm

;;
;; Microsoft tags for reparse points.
;;

IO_REPARSE_TAG_SYMBOLIC_LINK	equ IO_REPARSE_TAG_RESERVED_ZERO
IO_REPARSE_TAG_MOUNT_POINT	equ 0xA0000003
IO_REPARSE_TAG_HSM		equ 0xC0000004
IO_REPARSE_TAG_NSS		equ 0x80000005
IO_REPARSE_TAG_NSSRECOVER	equ 0x80000006
IO_REPARSE_TAG_SIS		equ 0x80000007
IO_REPARSE_TAG_DFS		equ 0x80000008

IO_COMPLETION_MODIFY_STATE	equ 0x0002
IO_COMPLETION_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3
DUPLICATE_CLOSE_SOURCE		equ 0x00000001
DUPLICATE_SAME_ACCESS		equ 0x00000002

ES_SYSTEM_REQUIRED		equ 0x00000001
ES_DISPLAY_REQUIRED		equ 0x00000002
ES_USER_PRESENT			equ 0x00000004
ES_CONTINUOUS			equ 0x80000000

EXECUTION_STATE			typedef DWORD
LATENCY_TIME			typedef DWORD

LT_DONT_CARE			equ 0
LT_LOWEST_LATENCY		equ 1

;; wmi
POWER_DEVICE_TIMEOUTS	STRUC
ConservationIdleTime	dd ?
PerformanceIdleTime	dd ?
POWER_DEVICE_TIMEOUTS	ENDS
PPOWER_DEVICE_TIMEOUTS	typedef ptr POWER_DEVICE_TIMEOUTS

;;
;; Image Format
;;

IMAGE_DOS_SIGNATURE	equ 0x5A4D	;; MZ
IMAGE_OS2_SIGNATURE	equ 0x454E	;; NE
IMAGE_OS2_SIGNATURE_LE	equ 0x454C	;; LE
IMAGE_VXD_SIGNATURE	equ 0x454C	;; LE
IMAGE_NT_SIGNATURE	equ 0x00004550	;; PE00

IMAGE_DOS_HEADER	STRUC 2 ;; 16 bit headers are 2 byte packed
e_magic			dw ?		;; Magic number
e_cblp			dw ?		;; Bytes on last page of file
e_cp			dw ?		;; Pages in file
e_crlc			dw ?		;; Relocations
e_cparhdr		dw ?		;; Size of header in paragraphs
e_minalloc		dw ?		;; Minimum extra paragraphs needed
e_maxalloc		dw ?		;; Maximum extra paragraphs needed
e_ss			dw ?		;; Initial (relative) SS value
e_sp			dw ?		;; Initial SP value
e_csum			dw ?		;; Checksum
e_ip			dw ?		;; Initial IP value
e_cs			dw ?		;; Initial (relative) CS value
e_lfarlc		dw ?		;; File address of relocation table
e_ovno			dw ?		;; Overlay number
e_res			dw 4 dup(?)	;; Reserved words
e_oemid			dw ?		;; OEM identifier (for e_oeminfo)
e_oeminfo		dw ?		;; OEM information; e_oemid specific
e_res2			dw 10 dup(?)	;; Reserved words
e_lfanew		dd ?		;; File address of new exe header
IMAGE_DOS_HEADER	ENDS
PIMAGE_DOS_HEADER	typedef ptr IMAGE_DOS_HEADER

IMAGE_OS2_HEADER	STRUC	;; OS/2 .EXE header
ne_magic		WORD ?		;; Magic number
ne_ver			CHAR ?		;; Version number
ne_rev			CHAR ?		;; Revision number
ne_enttab		WORD ?		;; Offset of Entry Table
ne_cbenttab		WORD ?		;; Number of bytes in Entry Table
ne_crc			LONG ?		;; Checksum of whole file
ne_flags		WORD ?		;; Flag word
ne_autodata		WORD ?		;; Automatic data segment number
ne_heap			WORD ?		;; Initial heap allocation
ne_stack		WORD ?		;; Initial stack allocation
ne_csip			LONG ?		;; Initial CS:IP setting
ne_sssp			LONG ?		;; Initial SS:SP setting
ne_cseg			WORD ?		;; Count of file segments
ne_cmod			WORD ?		;; Entries in Module Reference Table
ne_cbnrestab		WORD ?		;; Size of non-resident name table
ne_segtab		WORD ?		;; Offset of Segment Table
ne_rsrctab		WORD ?		;; Offset of Resource Table
ne_restab		WORD ?		;; Offset of resident name table
ne_modtab		WORD ?		;; Offset of Module Reference Table
ne_imptab		WORD ?		;; Offset of Imported Names Table
ne_nrestab		LONG ?		;; Offset of Non-resident Names Table
ne_cmovent		WORD ?		;; Count of movable entries
ne_align		WORD ?		;; Segment alignment shift count
ne_cres			WORD ?		;; Count of resource segments
ne_exetyp		BYTE ?		;; Target Operating system
ne_flagsothers		BYTE ?		;; Other .EXE flags
ne_pretthunks		WORD ?		;; offset to return thunks
ne_psegrefbytes		WORD ?		;; offset to segment ref. bytes
ne_swaparea		WORD ?		;; Minimum code swap area size
ne_expver		WORD ?		;; Expected Windows version number
IMAGE_OS2_HEADER	ENDS
PIMAGE_OS2_HEADER	typedef ptr IMAGE_OS2_HEADER

IMAGE_VXD_HEADER	STRUC ;; Windows VXD header
e32_magic		dw ?		;; Magic number
e32_border		db ?		;; The byte ordering for the VXD
e32_worder		db ?		;; The word ordering for the VXD
e32_level		dd ?		;; The EXE format level for now = 0
e32_cpu			dw ?		;; The CPU type
e32_os			dw ?		;; The OS type
e32_ver			dd ?		;; Module version
e32_mflags		dd ?		;; Module flags
e32_mpages		dd ?		;; Module # pages
e32_startobj		dd ?		;; Object # for instruction pointer
e32_eip			dd ?		;; Extended instruction pointer
e32_stackobj		dd ?		;; Object # for stack pointer
e32_esp			dd ?		;; Extended stack pointer
e32_pagesize		dd ?		;; VXD page size
e32_lastpagesize	dd ?		;; Last page size in VXD
e32_fixupsize		dd ?		;; Fixup section size
e32_fixupsum		dd ?		;; Fixup section checksum
e32_ldrsize		dd ?		;; Loader section size
e32_ldrsum		dd ?		;; Loader section checksum
e32_objtab		dd ?		;; Object table offset
e32_objcnt		dd ?		;; Number of objects in module
e32_objmap		dd ?		;; Object page map offset
e32_itermap		dd ?		;; Object iterated data map offset
e32_rsrctab		dd ?		;; Offset of Resource Table
e32_rsrccnt		dd ?		;; Number of resource entries
e32_restab		dd ?		;; Offset of resident name table
e32_enttab		dd ?		;; Offset of Entry Table
e32_dirtab		dd ?		;; Offset of Module Directive Table
e32_dircnt		dd ?		;; Number of module directives
e32_fpagetab		dd ?		;; Offset of Fixup Page Table
e32_frectab		dd ?		;; Offset of Fixup Record Table
e32_impmod		dd ?		;; Offset of Import Module Name Table
e32_impmodcnt		dd ?		;; Number of entries in Import Module Name Table
e32_impproc		dd ?		;; Offset of Import Procedure Name Table
e32_pagesum		dd ?		;; Offset of Per-Page Checksum Table
e32_datapage		dd ?		;; Offset of Enumerated Data Pages
e32_preload		dd ?		;; Number of preload pages
e32_nrestab		dd ?		;; Offset of Non-resident Names Table
e32_cbnrestab		dd ?		;; Size of Non-resident Name Table
e32_nressum		dd ?		;; Non-resident Name Table Checksum
e32_autodata		dd ?		;; Object # for automatic data object
e32_debuginfo		dd ?		;; Offset of the debugging information
e32_debuglen		dd ?		;; The length of the debugging info. in bytes
e32_instpreload		dd ?		;; Number of instance pages in preload section of VXD file
e32_instdemand		dd ?		;; Number of instance pages in demand load section of VXD file
e32_heapsize		dd ?		;; Size of heap - for 16-bit apps
e32_res3		db 12 dup(?)	;; Reserved words
e32_winresoff		dd ?
e32_winreslen		dd ?
e32_devid		dw ?		;; Device ID for VxD
e32_ddkver		dw ?		;; DDK version for VxD
IMAGE_VXD_HEADER	ENDS
PIMAGE_VXD_HEADER	typedef ptr IMAGE_VXD_HEADER

;;
;; File header format.
;;

IMAGE_FILE_HEADER	STRUC
Machine			dw ?
NumberOfSections	dw ?
TimeDateStamp		dd ?
PointerToSymbolTable	dd ?
NumberOfSymbols		dd ?
SizeOfOptionalHeader	dw ?
Characteristics		dw ?
IMAGE_FILE_HEADER	ENDS
PIMAGE_FILE_HEADER	typedef ptr IMAGE_FILE_HEADER


IMAGE_SIZEOF_FILE_HEADER	equ 20

; Characteristics flags

IMAGE_FILE_RELOCS_STRIPPED	     equ 0x0001 ;; Relocation info stripped from file.
IMAGE_FILE_EXECUTABLE_IMAGE	     equ 0x0002 ;; File is executable  (i.e. no unresolved externel references).
IMAGE_FILE_LINE_NUMS_STRIPPED	     equ 0x0004 ;; Line nunbers stripped from file.
IMAGE_FILE_LOCAL_SYMS_STRIPPED	     equ 0x0008 ;; Local symbols stripped from file.
IMAGE_FILE_AGGRESIVE_WS_TRIM	     equ 0x0010 ;; Agressively trim working set
IMAGE_FILE_LARGE_ADDRESS_AWARE	     equ 0x0020 ;; App can handle >2gb addresses
IMAGE_FILE_BYTES_REVERSED_LO	     equ 0x0080 ;; Bytes of machine word are reversed.
IMAGE_FILE_32BIT_MACHINE	     equ 0x0100 ;; 32 bit word machine.
IMAGE_FILE_DEBUG_STRIPPED	     equ 0x0200 ;; Debugging info stripped from file in .DBG file
IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP   equ 0x0400 ;; If Image is on removable media, copy and run from the swap file.
IMAGE_FILE_NET_RUN_FROM_SWAP	     equ 0x0800 ;; If Image is on Net, copy and run from the swap file.
IMAGE_FILE_SYSTEM		     equ 0x1000 ;; System File.
IMAGE_FILE_DLL			     equ 0x2000 ;; File is a DLL.
IMAGE_FILE_UP_SYSTEM_ONLY	     equ 0x4000 ;; File should only be run on a UP machine
IMAGE_FILE_BYTES_REVERSED_HI	     equ 0x8000 ;; Bytes of machine word are reversed.

; Machine values

IMAGE_FILE_MACHINE_UNKNOWN	equ 0
IMAGE_FILE_MACHINE_I386		equ 0x014c ;; Intel 386.
IMAGE_FILE_MACHINE_R3000	equ 0x0162 ;; MIPS little-endian, equ 0x160 big-endian
IMAGE_FILE_MACHINE_R4000	equ 0x0166 ;; MIPS little-endian
IMAGE_FILE_MACHINE_R10000	equ 0x0168 ;; MIPS little-endian
IMAGE_FILE_MACHINE_WCEMIPSV2	equ 0x0169 ;; MIPS little-endian WCE v2
IMAGE_FILE_MACHINE_ALPHA	equ 0x0184 ;; Alpha_AXP
IMAGE_FILE_MACHINE_POWERPC	equ 0x01F0 ;; IBM PowerPC Little-Endian
IMAGE_FILE_MACHINE_SH3		equ 0x01a2 ;; SH3 little-endian
IMAGE_FILE_MACHINE_SH3E		equ 0x01a4 ;; SH3E little-endian
IMAGE_FILE_MACHINE_SH4		equ 0x01a6 ;; SH4 little-endian
IMAGE_FILE_MACHINE_ARM		equ 0x01c0 ;; ARM Little-Endian
IMAGE_FILE_MACHINE_THUMB	equ 0x01c2
IMAGE_FILE_MACHINE_IA64		equ 0x0200 ;; Intel 64
IMAGE_FILE_MACHINE_MIPS16	equ 0x0266 ;; MIPS
IMAGE_FILE_MACHINE_MIPSFPU	equ 0x0366 ;; MIPS
IMAGE_FILE_MACHINE_MIPSFPU16	equ 0x0466 ;; MIPS
IMAGE_FILE_MACHINE_ALPHA64	equ 0x0284 ;; ALPHA64
IMAGE_FILE_MACHINE_AXP64	equ IMAGE_FILE_MACHINE_ALPHA64

IMAGE_FILE_MACHINE_AMD64	equ 0x8664  ; AMD64 (K8)

;;
;; Directory format.
;;

IMAGE_DATA_DIRECTORY	STRUC
VirtualAddress		dd ?
_Size			dd ?
IMAGE_DATA_DIRECTORY	ENDS
PIMAGE_DATA_DIRECTORY	typedef ptr IMAGE_DATA_DIRECTORY

IMAGE_NUMBEROF_DIRECTORY_ENTRIES equ 16

;;
;; Optional header format.
;;

IMAGE_OPTIONAL_HEADER32		STRUC

    ;;
    ;; Standard fields.
    ;;

Magic				dw ?
MajorLinkerVersion		db ?
MinorLinkerVersion		db ?
SizeOfCode			dd ?
SizeOfInitializedData		dd ?
SizeOfUninitializedData		dd ?
AddressOfEntryPoint		dd ?
BaseOfCode			dd ?
BaseOfData			dd ?

    ;;
    ;; NT additional fields.
    ;;

ImageBase			dd ?
SectionAlignment		dd ?
FileAlignment			dd ?
MajorOperatingSystemVersion	dw ?
MinorOperatingSystemVersion	dw ?
MajorImageVersion		dw ?
MinorImageVersion		dw ?
MajorSubsystemVersion		dw ?
MinorSubsystemVersion		dw ?
Win32VersionValue		dd ?
SizeOfImage			dd ?
SizeOfHeaders			dd ?
CheckSum			dd ?
Subsystem			dw ?
DllCharacteristics		dw ?
SizeOfStackReserve		dd ?
SizeOfStackCommit		dd ?
SizeOfHeapReserve		dd ?
SizeOfHeapCommit		dd ?
LoaderFlags			dd ?
NumberOfRvaAndSizes		dd ?
DataDirectory			IMAGE_DATA_DIRECTORY IMAGE_NUMBEROF_DIRECTORY_ENTRIES dup(<>)
IMAGE_OPTIONAL_HEADER32		ENDS
PIMAGE_OPTIONAL_HEADER32	typedef ptr IMAGE_OPTIONAL_HEADER32

IMAGE_ROM_OPTIONAL_HEADER	STRUC
Magic				dw ?
MajorLinkerVersion		db ?
MinorLinkerVersion		db ?
SizeOfCode			dd ?
SizeOfInitializedData		dd ?
SizeOfUninitializedData		dd ?
AddressOfEntryPoint		dd ?
BaseOfCode			dd ?
BaseOfData			dd ?
BaseOfBss			dd ?
CprMask				dd 4 dup(?)
GpValue				dd ?
IMAGE_ROM_OPTIONAL_HEADER	ENDS
PIMAGE_ROM_OPTIONAL_HEADER	typedef ptr IMAGE_ROM_OPTIONAL_HEADER

IMAGE_OPTIONAL_HEADER64		STRUC
Magic				dw ?
MajorLinkerVersion		db ?
MinorLinkerVersion		db ?
SizeOfCode			dd ?
SizeOfInitializedData		dd ?
SizeOfUninitializedData		dd ?
AddressOfEntryPoint		dd ?
BaseOfCode			dd ?
ImageBase			dq ?
SectionAlignment		dd ?
FileAlignment			dd ?
MajorOperatingSystemVersion	dw ?
MinorOperatingSystemVersion	dw ?
MajorImageVersion		dw ?
MinorImageVersion		dw ?
MajorSubsystemVersion		dw ?
MinorSubsystemVersion		dw ?
Win32VersionValue		dd ?
SizeOfImage			dd ?
SizeOfHeaders			dd ?
CheckSum			dd ?
Subsystem			dw ?
DllCharacteristics		dw ?
SizeOfStackReserve		dq ?
SizeOfStackCommit		dq ?
SizeOfHeapReserve		dq ?
SizeOfHeapCommit		dq ?
LoaderFlags			dd ?
NumberOfRvaAndSizes		dd ?
DataDirectory			IMAGE_DATA_DIRECTORY IMAGE_NUMBEROF_DIRECTORY_ENTRIES dup(<>)
IMAGE_OPTIONAL_HEADER64		ENDS
PIMAGE_OPTIONAL_HEADER64	typedef ptr IMAGE_OPTIONAL_HEADER64

IMAGE_SIZEOF_ROM_OPTIONAL_HEADER	equ 56
IMAGE_SIZEOF_STD_OPTIONAL_HEADER	equ 28
IMAGE_SIZEOF_NT_OPTIONAL32_HEADER	equ 224
IMAGE_SIZEOF_NT_OPTIONAL64_HEADER	equ 240

IMAGE_NT_OPTIONAL_HDR32_MAGIC	equ 0x10b
IMAGE_NT_OPTIONAL_HDR64_MAGIC	equ 0x20b
IMAGE_ROM_OPTIONAL_HDR_MAGIC	equ 0x107

ifdef _WIN64
IMAGE_OPTIONAL_HEADER		typedef IMAGE_OPTIONAL_HEADER64
PIMAGE_OPTIONAL_HEADER		typedef PIMAGE_OPTIONAL_HEADER64
IMAGE_SIZEOF_NT_OPTIONAL_HEADER equ IMAGE_SIZEOF_NT_OPTIONAL64_HEADER
IMAGE_NT_OPTIONAL_HDR_MAGIC	equ IMAGE_NT_OPTIONAL_HDR64_MAGIC
else
IMAGE_OPTIONAL_HEADER		typedef IMAGE_OPTIONAL_HEADER32
PIMAGE_OPTIONAL_HEADER		typedef PIMAGE_OPTIONAL_HEADER32
IMAGE_SIZEOF_NT_OPTIONAL_HEADER equ IMAGE_SIZEOF_NT_OPTIONAL32_HEADER
IMAGE_NT_OPTIONAL_HDR_MAGIC	equ IMAGE_NT_OPTIONAL_HDR32_MAGIC
endif

IMAGE_NT_HEADERS64	STRUC
Signature		dd ?
FileHeader		IMAGE_FILE_HEADER <>
OptionalHeader		IMAGE_OPTIONAL_HEADER64 <>
IMAGE_NT_HEADERS64	ENDS
PIMAGE_NT_HEADERS64	typedef ptr IMAGE_NT_HEADERS64

IMAGE_NT_HEADERS32	STRUC
Signature		dd ?
FileHeader		IMAGE_FILE_HEADER <>
OptionalHeader		IMAGE_OPTIONAL_HEADER32 <>
IMAGE_NT_HEADERS32	ENDS
PIMAGE_NT_HEADERS32	typedef ptr IMAGE_NT_HEADERS32

IMAGE_ROM_HEADERS	STRUC
FileHeader		IMAGE_FILE_HEADER <>
OptionalHeader		IMAGE_OPTIONAL_HEADER <>
IMAGE_ROM_HEADERS	ENDS
PIMAGE_ROM_HEADERS	typedef ptr IMAGE_ROM_HEADERS

IMAGE_FIRST_SECTION64 macro ntheader
	exitm<((ntheader + FIELD_OFFSET( IMAGE_NT_HEADERS64, OptionalHeader ) + \
	((PIMAGE_NT_HEADERS64)(ntheader))->FileHeader.SizeOfOptionalHeader))>
	endm

IMAGE_FIRST_SECTION32 macro ntheader
	exitm<((PIMAGE_SECTION_HEADER) ((UINT_PTR)ntheader + \
		FIELD_OFFSET( IMAGE_NT_HEADERS32, OptionalHeader ) + \
		((PIMAGE_NT_HEADERS32)(ntheader))->FileHeader.SizeOfOptionalHeader))>
	endm

ifdef _WIN64
IMAGE_NT_HEADERS	typedef IMAGE_NT_HEADERS64
PIMAGE_NT_HEADERS	typedef PIMAGE_NT_HEADERS64
IMAGE_FIRST_SECTION macro ntheader
	exitm<IMAGE_FIRST_SECTION64(ntheader)>
	endm
else
IMAGE_NT_HEADERS	typedef IMAGE_NT_HEADERS32
PIMAGE_NT_HEADERS	typedef PIMAGE_NT_HEADERS32
IMAGE_FIRST_SECTION macro ntheader
	exitm<IMAGE_FIRST_SECTION32(ntheader)>
	endm
endif


;; Subsystem Values

IMAGE_SUBSYSTEM_UNKNOWN		equ 0	 ;; Unknown subsystem.
IMAGE_SUBSYSTEM_NATIVE		equ 1	 ;; Image doesn't require a subsystem.
IMAGE_SUBSYSTEM_WINDOWS_GUI	equ 2	 ;; Image runs in the Windows GUI subsystem.
IMAGE_SUBSYSTEM_WINDOWS_CUI	equ 3	 ;; Image runs in the Windows character subsystem.
IMAGE_SUBSYSTEM_OS2_CUI		equ 5	 ;; image runs in the OS/2 character subsystem.
IMAGE_SUBSYSTEM_POSIX_CUI	equ 7	 ;; image runs in the Posix character subsystem.
IMAGE_SUBSYSTEM_NATIVE_WINDOWS	equ 8	 ;; image is a native Win9x driver.
IMAGE_SUBSYSTEM_WINDOWS_CE_GUI	equ 9	 ;; Image runs in the Windows CE subsystem.

;; DllCharacteristics Entries

;IMAGE_LIBRARY_PROCESS_INIT		equ 0x0001	;; Reserved.
;IMAGE_LIBRARY_PROCESS_TERM		equ 0x0002	;; Reserved.
;IMAGE_LIBRARY_THREAD_INIT		equ 0x0004	;; Reserved.
;IMAGE_LIBRARY_THREAD_TERM		equ 0x0008	;; Reserved.
IMAGE_DLLCHARACTERISTICS_WDM_DRIVER	equ 0x2000 ;; Driver uses WDM model

;; Directory Entries

IMAGE_DIRECTORY_ENTRY_EXPORT		equ 0	  ;; Export Directory
IMAGE_DIRECTORY_ENTRY_IMPORT		equ 1	  ;; Import Directory
IMAGE_DIRECTORY_ENTRY_RESOURCE		equ 2	  ;; Resource Directory
IMAGE_DIRECTORY_ENTRY_EXCEPTION		equ 3	  ;; Exception Directory
IMAGE_DIRECTORY_ENTRY_SECURITY		equ 4	  ;; Security Directory
IMAGE_DIRECTORY_ENTRY_BASERELOC		equ 5	  ;; Base Relocation Table
IMAGE_DIRECTORY_ENTRY_DEBUG		equ 6	  ;; Debug Directory
;IMAGE_DIRECTORY_ENTRY_COPYRIGHT	equ 7	  ;; (X86 usage)
IMAGE_DIRECTORY_ENTRY_ARCHITECTURE	equ 7	  ;; Architecture Specific Data
IMAGE_DIRECTORY_ENTRY_GLOBALPTR		equ 8	  ;; RVA of GP
IMAGE_DIRECTORY_ENTRY_TLS		equ 9	  ;; TLS Directory
IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG	equ 10	  ;; Load Configuration Directory
IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT	equ 11	  ;; Bound Import Directory in headers
IMAGE_DIRECTORY_ENTRY_IAT		equ 12	  ;; Import Address Table
IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT	equ 13	  ;; Delay Load Import Descriptors
IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR	equ 14	  ;; COM Runtime descriptor

;;
;; Section header format.
;;

IMAGE_SIZEOF_SHORT_NAME equ 8

IMAGE_SECTION_HEADER	STRUC
_Name			db IMAGE_SIZEOF_SHORT_NAME dup(?)
UNION
    PhysicalAddress	dd ?
    VirtualSize		dd ?
ENDS
VirtualAddress		dd ?
SizeOfRawData		dd ?
PointerToRawData	dd ?
PointerToRelocations	dd ?
PointerToLinenumbers	dd ?
NumberOfRelocations	dw ?
NumberOfLinenumbers	dw ?
Characteristics		dd ?
IMAGE_SECTION_HEADER	ENDS

IMAGE_SIZEOF_SECTION_HEADER	equ 40

;;
;; Section characteristics.
;;
;;	IMAGE_SCN_TYPE_REG	equ 0x00000000 ;; Reserved.
;;	IMAGE_SCN_TYPE_DSECT	equ 0x00000001 ;; Reserved.
;;	IMAGE_SCN_TYPE_NOLOAD	equ 0x00000002 ;; Reserved.
;;	IMAGE_SCN_TYPE_GROUP	equ 0x00000004 ;; Reserved.
IMAGE_SCN_TYPE_NO_PAD		equ 0x00000008 ;; Reserved.
;;	IMAGE_SCN_TYPE_COPY	equ 0x00000010 ;; Reserved.

IMAGE_SCN_CNT_CODE		equ 0x00000020	 ;; Section contains code.
IMAGE_SCN_CNT_INITIALIZED_DATA	equ 0x00000040	 ;; Section contains initialized data.
IMAGE_SCN_CNT_UNINITIALIZED_DATA equ 0x00000080	 ;; Section contains uninitialized data.

IMAGE_SCN_LNK_OTHER		equ 0x00000100	 ;; Reserved.
IMAGE_SCN_LNK_INFO		equ 0x00000200	 ;; Section contains comments or some other type of information.
;IMAGE_SCN_TYPE_OVER		equ 0x00000400 ;; Reserved.
IMAGE_SCN_LNK_REMOVE		equ 0x00000800	 ;; Section contents will not become part of image.
IMAGE_SCN_LNK_COMDAT		equ 0x00001000	 ;; Section contents comdat.
;				equ 0x00002000 ;; Reserved.
;IMAGE_SCN_MEM_PROTECTED - Obsolete equ 0x00004000
IMAGE_SCN_NO_DEFER_SPEC_EXC	equ 0x00004000	 ;; Reset speculative exceptions handling bits in the TLB entries for this section.
IMAGE_SCN_GPREL			equ 0x00008000	 ;; Section content can be accessed relative to GP
IMAGE_SCN_MEM_FARDATA		equ 0x00008000
;;IMAGE_SCN_MEM_SYSHEAP - Obsolete equ 0x00010000
IMAGE_SCN_MEM_PURGEABLE		equ 0x00020000
IMAGE_SCN_MEM_16BIT		equ 0x00020000
IMAGE_SCN_MEM_LOCKED		equ 0x00040000
IMAGE_SCN_MEM_PRELOAD		equ 0x00080000

IMAGE_SCN_ALIGN_1BYTES		equ 0x00100000	 ;;
IMAGE_SCN_ALIGN_2BYTES		equ 0x00200000	 ;;
IMAGE_SCN_ALIGN_4BYTES		equ 0x00300000	 ;;
IMAGE_SCN_ALIGN_8BYTES		equ 0x00400000	 ;;
IMAGE_SCN_ALIGN_16BYTES		equ 0x00500000	 ;; Default alignment if no others are specified.
IMAGE_SCN_ALIGN_32BYTES		equ 0x00600000	 ;;
IMAGE_SCN_ALIGN_64BYTES		equ 0x00700000	 ;;
IMAGE_SCN_ALIGN_128BYTES	equ 0x00800000	 ;;
IMAGE_SCN_ALIGN_256BYTES	equ 0x00900000	 ;;
IMAGE_SCN_ALIGN_512BYTES	equ 0x00A00000	 ;;
IMAGE_SCN_ALIGN_1024BYTES	equ 0x00B00000	 ;;
IMAGE_SCN_ALIGN_2048BYTES	equ 0x00C00000	 ;;
IMAGE_SCN_ALIGN_4096BYTES	equ 0x00D00000	 ;;
IMAGE_SCN_ALIGN_8192BYTES	equ 0x00E00000	 ;;
;; Unused			equ 0x00F00000

IMAGE_SCN_LNK_NRELOC_OVFL	equ 0x01000000	 ;; Section contains extended relocations.
IMAGE_SCN_MEM_DISCARDABLE	equ 0x02000000	 ;; Section can be discarded.
IMAGE_SCN_MEM_NOT_CACHED	equ 0x04000000	 ;; Section is not cachable.
IMAGE_SCN_MEM_NOT_PAGED		equ 0x08000000	 ;; Section is not pageable.
IMAGE_SCN_MEM_SHARED		equ 0x10000000	 ;; Section is shareable.
IMAGE_SCN_MEM_EXECUTE		equ 0x20000000	 ;; Section is executable.
IMAGE_SCN_MEM_READ		equ 0x40000000	 ;; Section is readable.
IMAGE_SCN_MEM_WRITE		equ 0x80000000	 ;; Section is writeable.

;;
;; TLS Chaacteristic Flags
;;
IMAGE_SCN_SCALE_INDEX	equ 0x00000001	 ;; Tls index is scaled

;;
;; Symbol format.
;;

IMAGE_SYMBOL		STRUC 2 ;; Symbols, relocs, and linenumbers are 2 byte packed
UNION
    ShortName		db 8 dup(?)
    STRUC
	_Short		dd ?	;; if 0, use LongName
	_Long		dd ?	;; offset into string table
    ENDS
    LongName		dd 2 dup(?)
ENDS
Value			dd ?
SectionNumber		dw ?
_Type			dw ?
StorageClass		db ?
NumberOfAuxSymbols	db ?
IMAGE_SYMBOL		ENDS
PIMAGE_SYMBOL		typedef ptr IMAGE_SYMBOL

IMAGE_SIZEOF_SYMBOL	equ 18

;;
;; Section values.
;;
;; Symbols have a section number of the section in which they are
;; defined. Otherwise, section numbers have the following meanings:
;;

IMAGE_SYM_UNDEFINED		equ 0		;; Symbol is undefined or is common.
IMAGE_SYM_ABSOLUTE		equ -1		;; Symbol is an absolute value.
IMAGE_SYM_DEBUG			equ -2		;; Symbol is a special debug item.

;;
;; Type (fundamental) values.
;;

IMAGE_SYM_TYPE_NULL		equ 0x0000	;; no type.
IMAGE_SYM_TYPE_VOID		equ 0x0001	;;
IMAGE_SYM_TYPE_CHAR		equ 0x0002	;; type character.
IMAGE_SYM_TYPE_SHORT		equ 0x0003	;; type short integer.
IMAGE_SYM_TYPE_INT		equ 0x0004	;;
IMAGE_SYM_TYPE_LONG		equ 0x0005	;;
IMAGE_SYM_TYPE_FLOAT		equ 0x0006	;;
IMAGE_SYM_TYPE_DOUBLE		equ 0x0007	;;
IMAGE_SYM_TYPE_STRUCT		equ 0x0008	;;
IMAGE_SYM_TYPE_UNION		equ 0x0009	;;
IMAGE_SYM_TYPE_ENUM		equ 0x000A	;; enumeration.
IMAGE_SYM_TYPE_MOE		equ 0x000B	;; member of enumeration.
IMAGE_SYM_TYPE_BYTE		equ 0x000C	;;
IMAGE_SYM_TYPE_WORD		equ 0x000D	;;
IMAGE_SYM_TYPE_UINT		equ 0x000E	;;
IMAGE_SYM_TYPE_DWORD		equ 0x000F	;;
IMAGE_SYM_TYPE_PCODE		equ 0x8000	;;

;;
;; Type (derived) values.
;;

IMAGE_SYM_DTYPE_NULL		equ 0	 ;; no derived type.
IMAGE_SYM_DTYPE_POINTER		equ 1	 ;; pointer.
IMAGE_SYM_DTYPE_FUNCTION	equ 2	 ;; function.
IMAGE_SYM_DTYPE_ARRAY		equ 3	 ;; array.

;;
;; Storage classes.
;;

; StorageClass values

IMAGE_SYM_CLASS_END_OF_FUNCTION	    equ -1
IMAGE_SYM_CLASS_NULL		    equ 0x0000
IMAGE_SYM_CLASS_AUTOMATIC	    equ 0x0001
IMAGE_SYM_CLASS_EXTERNAL	    equ 0x0002
IMAGE_SYM_CLASS_STATIC		    equ 0x0003
IMAGE_SYM_CLASS_REGISTER	    equ 0x0004
IMAGE_SYM_CLASS_EXTERNAL_DEF	    equ 0x0005
IMAGE_SYM_CLASS_LABEL		    equ 0x0006
IMAGE_SYM_CLASS_UNDEFINED_LABEL	    equ 0x0007
IMAGE_SYM_CLASS_MEMBER_OF_STRUCT    equ 0x0008
IMAGE_SYM_CLASS_ARGUMENT	    equ 0x0009
IMAGE_SYM_CLASS_STRUCT_TAG	    equ 0x000A
IMAGE_SYM_CLASS_MEMBER_OF_UNION	    equ 0x000B
IMAGE_SYM_CLASS_UNION_TAG	    equ 0x000C
IMAGE_SYM_CLASS_TYPE_DEFINITION	    equ 0x000D
IMAGE_SYM_CLASS_UNDEFINED_STATIC    equ 0x000E
IMAGE_SYM_CLASS_ENUM_TAG	    equ 0x000F
IMAGE_SYM_CLASS_MEMBER_OF_ENUM	    equ 0x0010
IMAGE_SYM_CLASS_REGISTER_PARAM	    equ 0x0011
IMAGE_SYM_CLASS_BIT_FIELD	    equ 0x0012

IMAGE_SYM_CLASS_FAR_EXTERNAL	    equ 0x0044	;; Not in PECOFF v8 spec

IMAGE_SYM_CLASS_BLOCK		    equ 0x0064
IMAGE_SYM_CLASS_FUNCTION	    equ 0x0065
IMAGE_SYM_CLASS_END_OF_STRUCT	    equ 0x0066
IMAGE_SYM_CLASS_FILE		    equ 0x0067
;; new
IMAGE_SYM_CLASS_SECTION		    equ 0x0068
IMAGE_SYM_CLASS_WEAK_EXTERNAL	    equ 0x0069
IMAGE_SYM_CLASS_CLR_TOKEN	    equ 0x006B

;; type packing constants

N_BTMASK    equ 0x000F
N_TMASK	    equ 0x0030
N_TMASK1    equ 0x00C0
N_TMASK2    equ 0x00F0
N_BTSHFT    equ 4
N_TSHIFT    equ 2

;; MACROS

;; Basic Type of x
BTYPE	macro x
	exitm<((x) and N_BTMASK)>
	endm
;; Is x a pointer?
ifndef ISPTR
ISPTR	macro x
	exitm<(((x) and N_TMASK) == (IMAGE_SYM_DTYPE_POINTER shl N_BTSHFT))>
	endm
endif
;; Is x a function?
ifndef ISFCN
ISFCN	macro x
	exitm<(((x) and N_TMASK) == (IMAGE_SYM_DTYPE_FUNCTION shl N_BTSHFT))>
	endm
endif
;; Is x an array?
ifndef ISARY
ISARY	macro x
	exitm<(((x) and N_TMASK) == (IMAGE_SYM_DTYPE_ARRAY shl N_BTSHFT))>
	endm
endif
;; Is x a structure, union, or enumeration TAG?
ifndef ISTAG
ISTAG	macro x
	exitm<((x)==IMAGE_SYM_CLASS_STRUCT_TAG or (x)==IMAGE_SYM_CLASS_UNION_TAG or (x)==IMAGE_SYM_CLASS_ENUM_TAG)>
	endm
endif
ifndef INCREF
INCREF	macro x
	exitm<((((x) and  not N_BTMASK) shl N_TSHIFT) or (IMAGE_SYM_DTYPE_POINTER shl N_BTSHFT) or ((x) and N_BTMASK))>
	endm
endif
ifndef DECREF
DECREF	macro x
	exitm<((((x) shr N_TSHIFT) and not N_BTMASK) or ((x) and N_BTMASK))>
	endm
endif

;;
;; Auxiliary entry format.
;;

IMAGE_AUX_SYMBOL	UNION
;
; AUX format 2: .bf and .ef entries
;
STRUC
 TagIndex		dd ?	;; struct, union, or enum tag index
 UNION
  STRUC
    Linenumber		dw ?	;; declaration line number
    _Size		dw ?	;; size of struct, union, or enum
  ENDS
  TotalSize		dd ?
 ENDS
 UNION
  STRUC
   PointerToLinenumber	dd ?
   PointerToNextFunction dd ?
  ENDS				;; if ISARY, up to 4 dimen.
; STRUC
   Dimension		dw 4 dup(?)
; ENDS
 ENDS
 TvIndex		dw ?
ENDS
;
; AUX format 4: file entries
;
STRUC
 _Name			db IMAGE_SIZEOF_SYMBOL dup(?)
ENDS
;
; AUX format 5: section entries
;
STRUC
 _Length		dd ?	;; section length
 NumberOfRelocations	dw ?	;; number of relocation entries
 NumberOfLinenumbers	dw ?	;; number of line numbers
 CheckSum		dd ?	;; checksum for communal
 Number			dw ?	;; section number to associate with
 Selection		db ?	;; communal selection type
ENDS
IMAGE_AUX_SYMBOL	ENDS
PIMAGE_AUX_SYMBOL	typedef ptr IMAGE_AUX_SYMBOL

IMAGE_SIZEOF_AUX_SYMBOL equ 18

;;
;; Communal selection types.
;;

; values for IMAGE_AUX_SYMBOL.Section.Selection

IMAGE_COMDAT_SELECT_NODUPLICATES    equ 1
IMAGE_COMDAT_SELECT_ANY		    equ 2
IMAGE_COMDAT_SELECT_SAME_SIZE	    equ 3
IMAGE_COMDAT_SELECT_EXACT_MATCH	    equ 4
IMAGE_COMDAT_SELECT_ASSOCIATIVE	    equ 5
IMAGE_COMDAT_SELECT_LARGEST	    equ 6
IMAGE_COMDAT_SELECT_NEWEST	    equ 7

; values for IMAGE_AUX_SYMBOL.Sym.Characteristics(=TotalSize)

IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY  equ 1
IMAGE_WEAK_EXTERN_SEARCH_LIBRARY    equ 2
IMAGE_WEAK_EXTERN_SEARCH_ALIAS	    equ 3

;;
;; Relocation format.
;;

IMAGE_RELOCATION	STRUC
UNION
    VirtualAddress	dd ?
    RelocCount		dd ?	;; Set to the real count when IMAGE_SCN_LNK_NRELOC_OVFL is set
ENDS
SymbolTableIndex	dd ?
_Type			dw ?
IMAGE_RELOCATION	ENDS
PIMAGE_RELOCATION	typedef ptr IMAGE_RELOCATION

IMAGE_SIZEOF_RELOCATION equ 10

;;
;; I386 relocation types.
;;

IMAGE_REL_I386_ABSOLUTE		equ 0x0000 ;; Reference is absolute, no relocation is necessary
IMAGE_REL_I386_DIR16		equ 0x0001 ;; Direct 16-bit reference to the symbols virtual address
IMAGE_REL_I386_REL16		equ 0x0002 ;; PC-relative 16-bit reference to the symbols virtual address
IMAGE_REL_I386_DIR32		equ 0x0006 ;; Direct 32-bit reference to the symbols virtual address
IMAGE_REL_I386_DIR32NB		equ 0x0007 ;; Direct 32-bit reference to the symbols virtual address, base not included
IMAGE_REL_I386_SEG12		equ 0x0009 ;; Direct 16-bit reference to the segment-selector bits of a 32-bit virtual address
IMAGE_REL_I386_SECTION		equ 000Ah ; 16bit section index
IMAGE_REL_I386_SECREL		equ 000Bh ; 32bit offset (SECTIONREL)
IMAGE_REL_I386_TOKEN		equ 000Ch ; CLR token
IMAGE_REL_I386_SECREL7		equ 000Dh ; 7bit offset
IMAGE_REL_I386_REL32		equ 0x0014 ;; PC-relative 32-bit reference to the symbols virtual address

; X86-64 relocations

IMAGE_REL_AMD64_ABSOLUTE	equ 0000h ; Reference is absolute, no relocation is necessary
IMAGE_REL_AMD64_ADDR64		equ 0001h ; 64-bit address (VA)
IMAGE_REL_AMD64_ADDR32		equ 0002h ; 32-bit address (VA)
IMAGE_REL_AMD64_ADDR32NB	equ 0003h ; 32-bit address w/o image base (RVA)
IMAGE_REL_AMD64_REL32		equ 0004h ; 32-bit relative address from byte following reloc
IMAGE_REL_AMD64_REL32_1		equ 0005h ; 32-bit relative address from byte distance 1 from reloc
IMAGE_REL_AMD64_REL32_2		equ 0006h ; 32-bit relative address from byte distance 2 from reloc
IMAGE_REL_AMD64_REL32_3		equ 0007h ; 32-bit relative address from byte distance 3 from reloc
IMAGE_REL_AMD64_REL32_4		equ 0008h ; 32-bit relative address from byte distance 4 from reloc
IMAGE_REL_AMD64_REL32_5		equ 0009h ; 32-bit relative address from byte distance 5 from reloc
IMAGE_REL_AMD64_SECTION		equ 000Ah ; Section index
IMAGE_REL_AMD64_SECREL		equ 000Bh ; 32 bit offset from base of section containing target
IMAGE_REL_AMD64_SECREL7		equ 000Ch ; 7 bit unsigned offset from base of section containing target
IMAGE_REL_AMD64_TOKEN		equ 000Dh ; 32 bit metadata token

;;
;; MIPS relocation types.
;;

IMAGE_REL_MIPS_ABSOLUTE		equ 0x0000 ;; Reference is absolute, no relocation is necessary
IMAGE_REL_MIPS_REFHALF		equ 0x0001
IMAGE_REL_MIPS_REFWORD		equ 0x0002
IMAGE_REL_MIPS_JMPADDR		equ 0x0003
IMAGE_REL_MIPS_REFHI		equ 0x0004
IMAGE_REL_MIPS_REFLO		equ 0x0005
IMAGE_REL_MIPS_GPREL		equ 0x0006
IMAGE_REL_MIPS_LITERAL		equ 0x0007
IMAGE_REL_MIPS_SECTION		equ 0x000A
IMAGE_REL_MIPS_SECREL		equ 0x000B
IMAGE_REL_MIPS_SECRELLO		equ 0x000C ;; Low 16-bit section relative referemce (used for >32k TLS)
IMAGE_REL_MIPS_SECRELHI		equ 0x000D ;; High 16-bit section relative reference (used for >32k TLS)
IMAGE_REL_MIPS_JMPADDR16	equ 0x0010
IMAGE_REL_MIPS_REFWORDNB	equ 0x0022
IMAGE_REL_MIPS_PAIR		equ 0x0025

;;
;; Alpha Relocation types.
;;

IMAGE_REL_ALPHA_ABSOLUTE	equ 0x0000
IMAGE_REL_ALPHA_REFLONG		equ 0x0001
IMAGE_REL_ALPHA_REFQUAD		equ 0x0002
IMAGE_REL_ALPHA_GPREL32		equ 0x0003
IMAGE_REL_ALPHA_LITERAL		equ 0x0004
IMAGE_REL_ALPHA_LITUSE		equ 0x0005
IMAGE_REL_ALPHA_GPDISP		equ 0x0006
IMAGE_REL_ALPHA_BRADDR		equ 0x0007
IMAGE_REL_ALPHA_HINT		equ 0x0008
IMAGE_REL_ALPHA_INLINE_REFLONG	equ 0x0009
IMAGE_REL_ALPHA_REFHI		equ 0x000A
IMAGE_REL_ALPHA_REFLO		equ 0x000B
IMAGE_REL_ALPHA_PAIR		equ 0x000C
IMAGE_REL_ALPHA_MATCH		equ 0x000D
IMAGE_REL_ALPHA_SECTION		equ 0x000E
IMAGE_REL_ALPHA_SECREL		equ 0x000F
IMAGE_REL_ALPHA_REFLONGNB	equ 0x0010
IMAGE_REL_ALPHA_SECRELLO	equ 0x0011 ;; Low 16-bit section relative reference
IMAGE_REL_ALPHA_SECRELHI	equ 0x0012 ;; High 16-bit section relative reference
IMAGE_REL_ALPHA_REFQ3		equ 0x0013 ;; High 16 bits of 48 bit reference
IMAGE_REL_ALPHA_REFQ2		equ 0x0014 ;; Middle 16 bits of 48 bit reference
IMAGE_REL_ALPHA_REFQ1		equ 0x0015 ;; Low 16 bits of 48 bit reference
IMAGE_REL_ALPHA_GPRELLO		equ 0x0016 ;; Low 16-bit GP relative reference
IMAGE_REL_ALPHA_GPRELHI		equ 0x0017 ;; High 16-bit GP relative reference


;;
;; IBM PowerPC relocation types.
;;

IMAGE_REL_PPC_ABSOLUTE		equ 0x0000 ;; NOP
IMAGE_REL_PPC_ADDR64		equ 0x0001 ;; 64-bit address
IMAGE_REL_PPC_ADDR32		equ 0x0002 ;; 32-bit address
IMAGE_REL_PPC_ADDR24		equ 0x0003 ;; 26-bit address, shifted left 2 (branch absolute)
IMAGE_REL_PPC_ADDR16		equ 0x0004 ;; 16-bit address
IMAGE_REL_PPC_ADDR14		equ 0x0005 ;; 16-bit address, shifted left 2 (load doubleword)
IMAGE_REL_PPC_REL24		equ 0x0006 ;; 26-bit PC-relative offset, shifted left 2 (branch relative)
IMAGE_REL_PPC_REL14		equ 0x0007 ;; 16-bit PC-relative offset, shifted left 2 (br cond relative)
IMAGE_REL_PPC_TOCREL16		equ 0x0008 ;; 16-bit offset from TOC base
IMAGE_REL_PPC_TOCREL14		equ 0x0009 ;; 16-bit offset from TOC base, shifted left 2 (load doubleword)

IMAGE_REL_PPC_ADDR32NB		equ 0x000A ;; 32-bit addr w/o image base
IMAGE_REL_PPC_SECREL		equ 0x000B ;; va of containing section (as in an image sectionhdr)
IMAGE_REL_PPC_SECTION		equ 0x000C ;; sectionheader number
IMAGE_REL_PPC_IFGLUE		equ 0x000D ;; substitute TOC restore instruction iff symbol is glue code
IMAGE_REL_PPC_IMGLUE		equ 0x000E ;; symbol is glue code; virtual address is TOC restore instruction
IMAGE_REL_PPC_SECREL16		equ 0x000F ;; va of containing section (limited to 16 bits)
IMAGE_REL_PPC_REFHI		equ 0x0010
IMAGE_REL_PPC_REFLO		equ 0x0011
IMAGE_REL_PPC_PAIR		equ 0x0012
IMAGE_REL_PPC_SECRELLO		equ 0x0013 ;; Low 16-bit section relative reference (used for >32k TLS)
IMAGE_REL_PPC_SECRELHI		equ 0x0014 ;; High 16-bit section relative reference (used for >32k TLS)
IMAGE_REL_PPC_GPREL		equ 0x0015

IMAGE_REL_PPC_TYPEMASK		equ 0x00FF ;; mask to isolate above values in IMAGE_RELOCATION.Type

;; Flag bits in IMAGE_RELOCATION.TYPE

IMAGE_REL_PPC_NEG		equ 0x0100 ;; subtract reloc value rather than adding it
IMAGE_REL_PPC_BRTAKEN		equ 0x0200 ;; fix branch prediction bit to predict branch taken
IMAGE_REL_PPC_BRNTAKEN		equ 0x0400 ;; fix branch prediction bit to predict branch not taken
IMAGE_REL_PPC_TOCDEFN		equ 0x0800 ;; toc slot defined in file (or, data in toc)

;;
;; Hitachi SH3 relocation types.
;;
IMAGE_REL_SH3_ABSOLUTE		equ 0x0000 ;; No relocation
IMAGE_REL_SH3_DIRECT16		equ 0x0001 ;; 16 bit direct
IMAGE_REL_SH3_DIRECT32		equ 0x0002 ;; 32 bit direct
IMAGE_REL_SH3_DIRECT8		equ 0x0003 ;; 8 bit direct, -128..255
IMAGE_REL_SH3_DIRECT8_WORD	equ 0x0004 ;; 8 bit direct .W (0 ext.)
IMAGE_REL_SH3_DIRECT8_LONG	equ 0x0005 ;; 8 bit direct .L (0 ext.)
IMAGE_REL_SH3_DIRECT4		equ 0x0006 ;; 4 bit direct (0 ext.)
IMAGE_REL_SH3_DIRECT4_WORD	equ 0x0007 ;; 4 bit direct .W (0 ext.)
IMAGE_REL_SH3_DIRECT4_LONG	equ 0x0008 ;; 4 bit direct .L (0 ext.)
IMAGE_REL_SH3_PCREL8_WORD	equ 0x0009 ;; 8 bit PC relative .W
IMAGE_REL_SH3_PCREL8_LONG	equ 0x000A ;; 8 bit PC relative .L
IMAGE_REL_SH3_PCREL12_WORD	equ 0x000B ;; 12 LSB PC relative .W
IMAGE_REL_SH3_STARTOF_SECTION	equ 0x000C ;; Start of EXE section
IMAGE_REL_SH3_SIZEOF_SECTION	equ 0x000D ;; Size of EXE section
IMAGE_REL_SH3_SECTION		equ 0x000E ;; Section table index
IMAGE_REL_SH3_SECREL		equ 0x000F ;; Offset within section
IMAGE_REL_SH3_DIRECT32_NB	equ 0x0010 ;; 32 bit direct not based

IMAGE_REL_ARM_ABSOLUTE		equ 0x0000 ;; No relocation required
IMAGE_REL_ARM_ADDR32		equ 0x0001 ;; 32 bit address
IMAGE_REL_ARM_ADDR32NB		equ 0x0002 ;; 32 bit address w/o image base
IMAGE_REL_ARM_BRANCH24		equ 0x0003 ;; 24 bit offset << 2 & sign ext.
IMAGE_REL_ARM_BRANCH11		equ 0x0004 ;; Thumb: 2 11 bit offsets
IMAGE_REL_ARM_SECTION		equ 0x000E ;; Section table index
IMAGE_REL_ARM_SECREL		equ 0x000F ;; Offset within section

;;
;; IA64 relocation types.
;;

IMAGE_REL_IA64_ABSOLUTE		equ 0x0000
IMAGE_REL_IA64_IMM14		equ 0x0001
IMAGE_REL_IA64_IMM22		equ 0x0002
IMAGE_REL_IA64_IMM64		equ 0x0003
IMAGE_REL_IA64_DIR32		equ 0x0004
IMAGE_REL_IA64_DIR64		equ 0x0005
IMAGE_REL_IA64_PCREL21B		equ 0x0006
IMAGE_REL_IA64_PCREL21M		equ 0x0007
IMAGE_REL_IA64_PCREL21F		equ 0x0008
IMAGE_REL_IA64_GPREL22		equ 0x0009
IMAGE_REL_IA64_LTOFF22		equ 0x000A
IMAGE_REL_IA64_SECTION		equ 0x000B
IMAGE_REL_IA64_SECREL22		equ 0x000C
IMAGE_REL_IA64_SECREL64I	equ 0x000D
IMAGE_REL_IA64_SECREL32		equ 0x000E
IMAGE_REL_IA64_LTOFF64		equ 0x000F
IMAGE_REL_IA64_DIR32NB		equ 0x0010
IMAGE_REL_IA64_RESERVED_11	equ 0x0011
IMAGE_REL_IA64_RESERVED_12	equ 0x0012
IMAGE_REL_IA64_RESERVED_13	equ 0x0013
IMAGE_REL_IA64_RESERVED_14	equ 0x0014
IMAGE_REL_IA64_RESERVED_15	equ 0x0015
IMAGE_REL_IA64_RESERVED_16	equ 0x0016
IMAGE_REL_IA64_ADDEND		equ 0x001F

EXT_IMM64 macro Value,Address,Size,InstPos,ValPos
	exitm <Value  or  = ( ( ( ( * ( Address )  shr	InstPos )  and	( ( 1  shl  Size ) - 1 ) ) )  shl  ValPos ) >
	endm
INS_IMM64 macro Value,Address,Size,InstPos,ValPos
	exitm <* Address = ( * Address	and   not  ( ( ( 1  shl	 Size ) - 1 )  shl  InstPos ) )	 or  ( ( ( ( Value  shr	 ValPos )  and	( ( 1  shl  Size ) - 1 ) ) )  shl  InstPos ) >
	endm

EMARCH_ENC_I17_IMM7B_INST_WORD_X	equ 3
EMARCH_ENC_I17_IMM7B_SIZE_X		equ 7
EMARCH_ENC_I17_IMM7B_INST_WORD_POS_X	equ 4
EMARCH_ENC_I17_IMM7B_VAL_POS_X		equ 0

EMARCH_ENC_I17_IMM9D_INST_WORD_X	equ 3
EMARCH_ENC_I17_IMM9D_SIZE_X		equ 9
EMARCH_ENC_I17_IMM9D_INST_WORD_POS_X	equ 18
EMARCH_ENC_I17_IMM9D_VAL_POS_X		equ 7

EMARCH_ENC_I17_IMM5C_INST_WORD_X	equ 3
EMARCH_ENC_I17_IMM5C_SIZE_X		equ 5
EMARCH_ENC_I17_IMM5C_INST_WORD_POS_X	equ 13
EMARCH_ENC_I17_IMM5C_VAL_POS_X		equ 16

EMARCH_ENC_I17_IC_INST_WORD_X		equ 3
EMARCH_ENC_I17_IC_SIZE_X		equ 1
EMARCH_ENC_I17_IC_INST_WORD_POS_X	equ 12
EMARCH_ENC_I17_IC_VAL_POS_X		equ 21

EMARCH_ENC_I17_IMM41a_INST_WORD_X	equ 1
EMARCH_ENC_I17_IMM41a_SIZE_X		equ 10
EMARCH_ENC_I17_IMM41a_INST_WORD_POS_X	equ 14
EMARCH_ENC_I17_IMM41a_VAL_POS_X		equ 22

EMARCH_ENC_I17_IMM41b_INST_WORD_X	equ 1
EMARCH_ENC_I17_IMM41b_SIZE_X		equ 8
EMARCH_ENC_I17_IMM41b_INST_WORD_POS_X	equ 24
EMARCH_ENC_I17_IMM41b_VAL_POS_X		equ 32

EMARCH_ENC_I17_IMM41c_INST_WORD_X	equ 2
EMARCH_ENC_I17_IMM41c_SIZE_X		equ 23
EMARCH_ENC_I17_IMM41c_INST_WORD_POS_X	equ 0
EMARCH_ENC_I17_IMM41c_VAL_POS_X		equ 40

EMARCH_ENC_I17_SIGN_INST_WORD_X		equ 3
EMARCH_ENC_I17_SIGN_SIZE_X		equ 1
EMARCH_ENC_I17_SIGN_INST_WORD_POS_X	equ 27
EMARCH_ENC_I17_SIGN_VAL_POS_X		equ 63

;;
;; Line number format.
;;

IMAGE_LINENUMBER	STRUC
UNION
    SymbolTableIndex	dd ?	;; Symbol table index of function name if Linenumber is 0.
    VirtualAddress	dd ?	;; Virtual address of line number.
ENDS
Linenumber		dw ?	;; Line number.
IMAGE_LINENUMBER	ENDS
PIMAGE_LINENUMBER	typedef ptr IMAGE_LINENUMBER

IMAGE_SIZEOF_LINENUMBER equ 6

;;
;; Based relocation format.
;;

IMAGE_BASE_RELOCATION	STRUC
VirtualAddress		dd ?
SizeOfBlock		dd ?
;;  WORD	   TypeOffset[1];
IMAGE_BASE_RELOCATION	ENDS
PIMAGE_BASE_RELOCATION	typedef ptr IMAGE_BASE_RELOCATION

IMAGE_SIZEOF_BASE_RELOCATION	equ 8

;;
;; Based relocation types.
;;

IMAGE_REL_BASED_ABSOLUTE	equ 0
IMAGE_REL_BASED_HIGH		equ 1
IMAGE_REL_BASED_LOW		equ 2
IMAGE_REL_BASED_HIGHLOW		equ 3
IMAGE_REL_BASED_HIGHADJ		equ 4
IMAGE_REL_BASED_MIPS_JMPADDR	equ 5
IMAGE_REL_BASED_SECTION		equ 6
IMAGE_REL_BASED_REL32		equ 7

IMAGE_REL_BASED_MIPS_JMPADDR16	equ 9
IMAGE_REL_BASED_IA64_IMM64	equ 9
IMAGE_REL_BASED_DIR64		equ 10
IMAGE_REL_BASED_HIGH3ADJ	equ 11


;;
;; Archive format.
;;

IMAGE_ARCHIVE_START_SIZE	equ 8
IMAGE_ARCHIVE_START		equ <"!",3Ch,"arch",3Eh,0Ah>
IMAGE_ARCHIVE_END		equ <"`",0Ah>
IMAGE_ARCHIVE_PAD		equ 10
IMAGE_ARCHIVE_LINKER_MEMBER	equ <"/               ">
IMAGE_ARCHIVE_LONGNAMES_MEMBER	equ <"//              ">

IMAGE_ARCHIVE_MEMBER_HEADER	STRUC
_Name				db 16 dup(?)	;; File member name - `/' terminated.
Date				db 12 dup(?)	;; File member date - decimal.
UserID				db  6 dup(?)	;; File member user id - decimal.
GroupID				db  6 dup(?)	;; File member group id - decimal.
Mode				db  8 dup(?)	;; File member mode - octal.
_Size				db 10 dup(?)	;; File member size - decimal.
EndHeader			db  2 dup(?)	;; String to end header.
IMAGE_ARCHIVE_MEMBER_HEADER	ENDS
PIMAGE_ARCHIVE_MEMBER_HEADER	typedef ptr IMAGE_ARCHIVE_MEMBER_HEADER

IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR equ 60

;;
;; DLL support.
;;

;;
;; Export Format
;;

IMAGE_EXPORT_DIRECTORY		STRUC
Characteristics			dd ?
TimeDateStamp			dd ?
MajorVersion			dw ?
MinorVersion			dw ?
_Name				dd ?
Base				dd ?
NumberOfFunctions		dd ?
NumberOfNames			dd ?
AddressOfFunctions		dd ?	;; RVA from base of image
AddressOfNames			dd ?	;; RVA from base of image
AddressOfNameOrdinals		dd ?	;; RVA from base of image
IMAGE_EXPORT_DIRECTORY		ENDS
PIMAGE_EXPORT_DIRECTORY		typedef ptr IMAGE_EXPORT_DIRECTORY

;;
;; Import Format
;;

IMAGE_IMPORT_BY_NAME	STRUC
Hint			dw ?
_Name			db ?
IMAGE_IMPORT_BY_NAME	ENDS
PIMAGE_IMPORT_BY_NAME	typedef ptr IMAGE_IMPORT_BY_NAME

IMAGE_THUNK_DATA64	STRUC 8 ; Use align 8 for the 64-bit IAT.
UNION ; u1
  ForwarderString	LPBYTE ?
  Function		PDWORD ?
  Ordinal			ULONGLONG ?
  AddressOfData		PIMAGE_IMPORT_BY_NAME ?
ENDS
IMAGE_THUNK_DATA64	ENDS
PIMAGE_THUNK_DATA64	typedef ptr IMAGE_THUNK_DATA64

IMAGE_THUNK_DATA32	STRUC
UNION
  ForwarderString	LPBYTE ?
  Function		PDWORD ?
  Ordinal		dd ?
  AddressOfData		PIMAGE_IMPORT_BY_NAME ?
ENDS
IMAGE_THUNK_DATA32	ENDS
PIMAGE_THUNK_DATA32	typedef ptr IMAGE_THUNK_DATA32

IMAGE_ORDINAL_FLAG32	equ 0x80000000
IMAGE_ORDINAL_FLAG64	equ 0x8000000000000000

IMAGE_ORDINAL64 macro Ordinal
	exitm<Ordinal and 0xffff>
	endm

IMAGE_ORDINAL32 macro Ordinal
	exitm<Ordinal and 0xffff>
	endm

IMAGE_SNAP_BY_ORDINAL64 macro Ordinal
	exitm<Ordinal and IMAGE_ORDINAL_FLAG64>
	endm

IMAGE_SNAP_BY_ORDINAL32 macro Ordinal
	exitm<Ordinal and IMAGE_ORDINAL_FLAG32>
	endm

;;
;; Thread Local Storage
;;

IMAGE_TLS_CALLBACK_T typedef proto :PVOID, :DWORD, :PVOID
PIMAGE_TLS_CALLBACK  typedef ptr IMAGE_TLS_CALLBACK_T

IMAGE_TLS_DIRECTORY64	STRUC
StartAddressOfRawData	dq ?
EndAddressOfRawData	dq ?
AddressOfIndex		PDWORD ?
AddressOfCallBacks	PIMAGE_TLS_CALLBACK ?
SizeOfZeroFill		dd ?
Characteristics		dd ?
IMAGE_TLS_DIRECTORY64	ENDS
PIMAGE_TLS_DIRECTORY64	typedef ptr IMAGE_TLS_DIRECTORY64

IMAGE_TLS_DIRECTORY32	STRUC
StartAddressOfRawData	dd ?
EndAddressOfRawData	dd ?
AddressOfIndex		PDWORD ?
AddressOfCallBacks	PIMAGE_TLS_CALLBACK ?
SizeOfZeroFill		dd ?
Characteristics		dd ?
IMAGE_TLS_DIRECTORY32	ENDS
PIMAGE_TLS_DIRECTORY32	typedef ptr IMAGE_TLS_DIRECTORY32

ifdef _WIN64
IMAGE_ORDINAL_FLAG	equ IMAGE_ORDINAL_FLAG64
IMAGE_THUNK_DATA	typedef IMAGE_THUNK_DATA64
PIMAGE_THUNK_DATA	typedef PIMAGE_THUNK_DATA64
IMAGE_TLS_DIRECTORY	typedef IMAGE_TLS_DIRECTORY64
PIMAGE_TLS_DIRECTORY	typedef PIMAGE_TLS_DIRECTORY64
IMAGE_ORDINAL macro Ordinal
	 exitm<IMAGE_ORDINAL64(Ordinal)>
	 endm
IMAGE_SNAP_BY_ORDINAL macro Ordinal
	 exitm<IMAGE_SNAP_BY_ORDINAL64(Ordinal)>
	 endm
else
IMAGE_ORDINAL_FLAG	equ IMAGE_ORDINAL_FLAG32
IMAGE_THUNK_DATA	typedef IMAGE_THUNK_DATA32
PIMAGE_THUNK_DATA	typedef PIMAGE_THUNK_DATA32
IMAGE_TLS_DIRECTORY	typedef IMAGE_TLS_DIRECTORY32
PIMAGE_TLS_DIRECTORY	typedef PIMAGE_TLS_DIRECTORY32
IMAGE_ORDINAL macro Ordinal
	 exitm<IMAGE_ORDINAL32(Ordinal)>
	 endm
IMAGE_SNAP_BY_ORDINAL macro Ordinal
	 exitm<IMAGE_SNAP_BY_ORDINAL32(Ordinal)>
	 endm
endif

IMAGE_IMPORT_DESCRIPTOR STRUC
UNION
  Characteristics	dd ?	;; 0 for terminating null import descriptor
  OriginalFirstThunk	dd ?	;; RVA to original unbound IAT (PIMAGE_THUNK_DATA)
ENDS
TimeDateStamp		dd ?	;; 0 if not bound,
				;; -1 if bound, and real date\time stamp
				;;	  in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
				;; O.W. date/time stamp of DLL bound to (Old BIND)
ForwarderChain		dd ?	;; -1 if no forwarders
_Name			dd ?
FirstThunk		dd ?	;; RVA to IAT (if bound this IAT has actual addresses)
IMAGE_IMPORT_DESCRIPTOR ENDS

PIMAGE_IMPORT_DESCRIPTOR typedef ptr IMAGE_IMPORT_DESCRIPTOR

;;
;; New format import descriptors pointed to by DataDirectory[ IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT ]
;;

IMAGE_BOUND_IMPORT_DESCRIPTOR	STRUC
TimeDateStamp			dd ?
OffsetModuleName		dw ?
NumberOfModuleForwarderRefs	dw ?
;; Array of zero or more IMAGE_BOUND_FORWARDER_REF follows
IMAGE_BOUND_IMPORT_DESCRIPTOR	ENDS
PIMAGE_BOUND_IMPORT_DESCRIPTOR	typedef ptr IMAGE_BOUND_IMPORT_DESCRIPTOR

IMAGE_BOUND_FORWARDER_REF	STRUC
TimeDateStamp			dd ?
OffsetModuleName		dw ?
Reserved			dw ?
IMAGE_BOUND_FORWARDER_REF	ENDS
PIMAGE_BOUND_FORWARDER_REF	typedef ptr IMAGE_BOUND_FORWARDER_REF

;;
;; Stub structure for IA64 transition stubs
;;
IMAGE_MIX_ISA_LIMIT		equ 2

IMAGE_STUB_DIRECTORY		STRUC
SecondaryImportAddressTable	dd ?	;; RVA of Secondary IAT
ExpectedISA			dw IMAGE_MIX_ISA_LIMIT dup(?) ;; Indicator of available ISA stubs
StubAddressTable		dd IMAGE_MIX_ISA_LIMIT dup(?) ;; RVA of Stub Address Tables
IMAGE_STUB_DIRECTORY		ENDS
PIMAGE_STUB_DIRECTORY		typedef ptr IMAGE_STUB_DIRECTORY

IA64_STUB_NOT_AVAILABLE		equ -1
IA64_JMPE_MASK			equ 0x00ffffff
IA64_JMPE_MARKER		equ 0x0035000f

;;
;; Resource Format.
;;

;;
;; Resource directory consists of two counts, following by a variable length
;; array of directory entries.	The first count is the number of entries at
;; beginning of the array that have actual names associated with each entry.
;; The entries are in ascending order, case insensitive strings.	 The second
;; count is the number of entries that immediately follow the named entries.
;; This second count identifies the number of entries that have 16-bit integer
;; Ids as their name.  These entries are also sorted in ascending order.
;;
;; This structure allows fast lookup by either name or number, but for any
;; given resource entry only one form of lookup is supported, not both.
;; This is consistant with the syntax of the .RC file and the .RES file.
;;

IMAGE_RESOURCE_DIRECTORY	STRUC
Characteristics			dd ?
TimeDateStamp			dd ?
MajorVersion			dw ?
MinorVersion			dw ?
NumberOfNamedEntries		dw ?
NumberOfIdEntries		dw ?
;;  IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[];
IMAGE_RESOURCE_DIRECTORY	ENDS
PIMAGE_RESOURCE_DIRECTORY	typedef ptr IMAGE_RESOURCE_DIRECTORY

IMAGE_RESOURCE_NAME_IS_STRING	     equ 0x80000000
IMAGE_RESOURCE_DATA_IS_DIRECTORY     equ 0x80000000
;;
;; Each directory contains the 32-bit Name of the entry and an offset,
;; relative to the beginning of the resource directory of the data associated
;; with this directory entry.  If the name of the entry is an actual text
;; string instead of an integer Id, then the high order bit of the name field
;; is set to one and the low order 31-bits are an offset, relative to the
;; beginning of the resource directory of the string, which is of type
;; IMAGE_RESOURCE_DIRECTORY_STRING.  Otherwise the high bit is clear and the
;; low-order 16-bits are the integer Id that identify this resource directory
;; entry. If the directory entry is yet another resource directory (i.e. a
;; subdirectory), then the high order bit of the offset field will be
;; set to indicate this.	 Otherwise the high bit is clear and the offset
;; field points to a resource data entry.
;;

IMAGE_RESOURCE_DIRECTORY_ENTRY_R0 RECORD \
	irde_NameIsString:	1,
	irde_NameOffset:	31
IMAGE_RESOURCE_DIRECTORY_ENTRY_R1 RECORD \
	irde_DataIsDirectory:	1,
	irde_OffsetToDirectory: 31

IMAGE_RESOURCE_DIRECTORY_ENTRY STRUC
UNION
  STRUC
    r0		IMAGE_RESOURCE_DIRECTORY_ENTRY_R0 <>
  ENDS
  _Name		dd ?
  Id		dw ?
ENDS
UNION
  OffsetToData	dd ?
  STRUC
    r1		IMAGE_RESOURCE_DIRECTORY_ENTRY_R1 <>
  ENDS
ENDS
IMAGE_RESOURCE_DIRECTORY_ENTRY	ENDS
PIMAGE_RESOURCE_DIRECTORY_ENTRY typedef ptr IMAGE_RESOURCE_DIRECTORY_ENTRY

;;
;; For resource directory entries that have actual string names, the Name
;; field of the directory entry points to an object of the following type.
;; All of these string objects are stored together after the last resource
;; directory entry and before the first resource data object.  This minimizes
;; the impact of these variable length objects on the alignment of the fixed
;; size directory entry objects.
;;

IMAGE_RESOURCE_DIRECTORY_STRING STRUC
_Length				dw ?
NameString			db ?
IMAGE_RESOURCE_DIRECTORY_STRING ENDS
PIMAGE_RESOURCE_DIRECTORY_STRING typedef ptr IMAGE_RESOURCE_DIRECTORY_STRING


IMAGE_RESOURCE_DIR_STRING_U	STRUC
_Length				dw ?
NameString			dw ?
IMAGE_RESOURCE_DIR_STRING_U	ENDS
PIMAGE_RESOURCE_DIR_STRING_U	typedef ptr IMAGE_RESOURCE_DIR_STRING_U


;;
;; Each resource data entry describes a leaf node in the resource directory
;; tree.	 It contains an offset, relative to the beginning of the resource
;; directory of the data for the resource, a size field that gives the number
;; of bytes of data at that offset, a CodePage that should be used when
;; decoding code point values within the resource data. Typically for new
;; applications the code page would be the unicode code page.
;;

IMAGE_RESOURCE_DATA_ENTRY	STRUC
OffsetToData			dd ?
_Size				dd ?
CodePage			dd ?
Reserved			dd ?
IMAGE_RESOURCE_DATA_ENTRY	ENDS
PIMAGE_RESOURCE_DATA_ENTRY	typedef ptr IMAGE_RESOURCE_DATA_ENTRY

;;
;; Load Configuration Directory Entry
;;

IMAGE_LOAD_CONFIG_DIRECTORY	STRUC
Characteristics			dd ?
TimeDateStamp			dd ?
MajorVersion			dw ?
MinorVersion			dw ?
GlobalFlagsClear		dd ?
GlobalFlagsSet			dd ?
CriticalSectionDefaultTimeout	dd ?
DeCommitFreeBlockThreshold	dd ?
DeCommitTotalFreeThreshold	dd ?
LockPrefixTable			PVOID ?
MaximumAllocationSize		dd ?
VirtualMemoryThreshold		dd ?
ProcessHeapFlags		dd ?
ProcessAffinityMask		dd ?
CSDVersion			dw ?
Reserved1			dw ?
EditList			PVOID ?
Reserved			dd ?
IMAGE_LOAD_CONFIG_DIRECTORY	ENDS
PIMAGE_LOAD_CONFIG_DIRECTORY	typedef ptr IMAGE_LOAD_CONFIG_DIRECTORY


;;
;; Function table entry format for IA64 images. Function table is
;; pointed to by the IMAGE_DIRECTORY_ENTRY_EXCEPTION directory entry.
;; This definition duplicates the one in ntia64.h for use by portable
;; image file mungers.
;;

IMAGE_IA64_RUNTIME_FUNCTION_ENTRY	STRUC
BeginAddress				dd ?
EndAddress				dd ?
UnwindInfoAddress			dd ?
IMAGE_IA64_RUNTIME_FUNCTION_ENTRY	ENDS
PIMAGE_IA64_RUNTIME_FUNCTION_ENTRY	typedef ptr IMAGE_IA64_RUNTIME_FUNCTION_ENTRY

;;
;; Function table entry format for ALPHA images.	 Function table is
;; pointed to by the IMAGE_DIRECTORY_ENTRY_EXCEPTION directory entry.
;; This definition duplicates ones in ntmips.h and ntalpha.h for use
;; by portable image file mungers.
;;

IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY	STRUC
BeginAddress				dd ?
EndAddress				dd ?
ExceptionHandler			dd ?
HandlerData				dd ?
PrologEndAddress			dd ?
IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY	ENDS
PIMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY	typedef ptr IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY

IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY	STRUC
BeginAddress				dq ?
EndAddress				dq ?
ExceptionHandler			dq ?
HandlerData				dq ?
PrologEndAddress			dq ?
IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY	ENDS

PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY	typedef ptr IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY
IMAGE_AXP64_RUNTIME_FUNCTION_ENTRY	typedef IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY
PIMAGE_AXP64_RUNTIME_FUNCTION_ENTRY	typedef PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY

;;
;; WIN CE Exception table format
;;

IMAGE_CE_RUNTIME_FUNCTION_ENTRY_R0 RECORD \
	icrfe_ExceptionFlag:	1,
	icrfe_ThirtyTwoBit:	1,
	icrfe_FuncLen:		22,
	icrfe_PrologLen:	8

IMAGE_CE_RUNTIME_FUNCTION_ENTRY		STRUC
FuncStart				dd ?
r0					IMAGE_CE_RUNTIME_FUNCTION_ENTRY_R0 <>
IMAGE_CE_RUNTIME_FUNCTION_ENTRY		ENDS
PIMAGE_CE_RUNTIME_FUNCTION_ENTRY	typedef ptr IMAGE_CE_RUNTIME_FUNCTION_ENTRY

if defined(_IA64_)
IMAGE_RUNTIME_FUNCTION_ENTRY	typedef IMAGE_IA64_RUNTIME_FUNCTION_ENTRY
PIMAGE_RUNTIME_FUNCTION_ENTRY	typedef PIMAGE_IA64_RUNTIME_FUNCTION_ENTRY
else
IMAGE_RUNTIME_FUNCTION_ENTRY	typedef IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY
PIMAGE_RUNTIME_FUNCTION_ENTRY	typedef PIMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY
endif

;;
;; Debug Format
;;

IMAGE_DEBUG_DIRECTORY		STRUC
Characteristics			dd ?
TimeDateStamp			dd ?
MajorVersion			dw ?
MinorVersion			dw ?
_Type				dd ?
SizeOfData			dd ?
AddressOfRawData		dd ?
PointerToRawData		dd ?
IMAGE_DEBUG_DIRECTORY		ENDS
PIMAGE_DEBUG_DIRECTORY		typedef ptr IMAGE_DEBUG_DIRECTORY

IMAGE_DEBUG_TYPE_UNKNOWN	equ 0
IMAGE_DEBUG_TYPE_COFF		equ 1
IMAGE_DEBUG_TYPE_CODEVIEW	equ 2
IMAGE_DEBUG_TYPE_FPO		equ 3
IMAGE_DEBUG_TYPE_MISC		equ 4
IMAGE_DEBUG_TYPE_EXCEPTION	equ 5
IMAGE_DEBUG_TYPE_FIXUP		equ 6
IMAGE_DEBUG_TYPE_OMAP_TO_SRC	equ 7
IMAGE_DEBUG_TYPE_OMAP_FROM_SRC	equ 8
IMAGE_DEBUG_TYPE_BORLAND	equ 9
IMAGE_DEBUG_TYPE_RESERVED10	equ 10


IMAGE_COFF_SYMBOLS_HEADER	STRUC
NumberOfSymbols			dd ?
LvaToFirstSymbol		dd ?
NumberOfLinenumbers		dd ?
LvaToFirstLinenumber		dd ?
RvaToFirstByteOfCode		dd ?
RvaToLastByteOfCode		dd ?
RvaToFirstByteOfData		dd ?
RvaToLastByteOfData		dd ?
IMAGE_COFF_SYMBOLS_HEADER	ENDS
PIMAGE_COFF_SYMBOLS_HEADER	typedef ptr IMAGE_COFF_SYMBOLS_HEADER

FRAME_FPO	equ 0
FRAME_TRAP	equ 1
FRAME_TSS	equ 2
FRAME_NONFPO	equ 3

FPO_DATA_R0	RECORD \
	fpo_cbFrame:	2,	;; frame type
	fpo_reserved:	1,	;; reserved for future use
	fpo_fUseBP:	1,	;; TRUE if EBP has been allocated
	fpo_fHasSEH:	1,	;; TRUE if SEH in func
	fpo_cbRegs:	3,	;; # regs saved
	fpo_cbProlog:	8	;; # bytes in prolog

FPO_DATA	STRUC
ulOffStart	dd ?		;; offset 1st byte of function code
cbProcSize	dd ?		;; # bytes in function
cdwLocals	dd ?		;; # bytes in locals/4
cdwParams	dw ?		;; # bytes in params/4
r0		FPO_DATA_R0 <>
FPO_DATA	ENDS
PFPO_DATA	typedef ptr FPO_DATA
SIZEOF_RFPO_DATA	equ 16


IMAGE_DEBUG_MISC_EXENAME	equ 1

IMAGE_DEBUG_MISC	STRUC
DataType		dd ?	;; type of misc data, see defines
_Length			dd ?	;; total length of record, rounded to four
				;; byte multiple.
Unicode			BOOLEAN ? ;; TRUE if data is unicode string
Reserved		db 3 dup(?)
Data			db ?	;; Actual data
IMAGE_DEBUG_MISC	ENDS
PIMAGE_DEBUG_MISC	typedef ptr IMAGE_DEBUG_MISC


;;
;; Function table extracted from MIPS/ALPHA/IA64 images.	 Does not contain
;; information needed only for runtime support. Just those fields for
;; each entry needed by a debugger.
;;

if defined(_IA64_)

IMAGE_FUNCTION_ENTRY	STRUC
StartingAddress		dd ?
EndingAddress		dd ?
UnwindInfoAddress	dd ?
IMAGE_FUNCTION_ENTRY	ENDS
PIMAGE_FUNCTION_ENTRY	typedef ptr IMAGE_FUNCTION_ENTRY

else

IMAGE_FUNCTION_ENTRY	STRUC
StartingAddress		dd ?
EndingAddress		dd ?
EndOfPrologue		dd ?
IMAGE_FUNCTION_ENTRY	ENDS
PIMAGE_FUNCTION_ENTRY	typedef ptr IMAGE_FUNCTION_ENTRY

endif

IMAGE_FUNCTION_ENTRY64	STRUC
StartingAddress		dq ?
EndingAddress		dq ?
EndOfPrologue		dq ?
IMAGE_FUNCTION_ENTRY64	ENDS
PIMAGE_FUNCTION_ENTRY64 typedef ptr IMAGE_FUNCTION_ENTRY64

;;
;; Debugging information can be stripped from an image file and placed
;; in a separate .DBG file, whose file name part is the same as the
;; image file name part (e.g. symbols for CMD.EXE could be stripped
;; and placed in CMD.DBG).  This is indicated by the IMAGE_FILE_DEBUG_STRIPPED
;; flag in the Characteristics field of the file header.	 The beginning of
;; the .DBG file contains the following structure which captures certain
;; information from the image file.  This allows a debug to proceed even if
;; the original image file is not accessable.  This header is followed by
;; zero of more IMAGE_SECTION_HEADER structures, followed by zero or more
;; IMAGE_DEBUG_DIRECTORY structures.  The latter structures and those in
;; the image file contain file offsets relative to the beginning of the
;; .DBG file.
;;
;; If symbols have been stripped from an image, the IMAGE_DEBUG_MISC structure
;; is left in the image file, but not mapped.  This allows a debugger to
;; compute the name of the .DBG file, from the name of the image in the
;; IMAGE_DEBUG_MISC structure.
;;

IMAGE_SEPARATE_DEBUG_HEADER	STRUC
Signature			dw ?
Flags				dw ?
Machine				dw ?
Characteristics			dw ?
TimeDateStamp			dd ?
CheckSum			dd ?
ImageBase			dd ?
SizeOfImage			dd ?
NumberOfSections		dd ?
ExportedNamesSize		dd ?
DebugDirectorySize		dd ?
SectionAlignment		dd ?
Reserved			dd 2 dup(?)
IMAGE_SEPARATE_DEBUG_HEADER	ENDS
PIMAGE_SEPARATE_DEBUG_HEADER	typedef ptr IMAGE_SEPARATE_DEBUG_HEADER

ifndef _MAC
IMAGE_SEPARATE_DEBUG_SIGNATURE equ 0x4944
else
IMAGE_SEPARATE_DEBUG_SIGNATURE equ 0x4449
endif

IMAGE_SEPARATE_DEBUG_FLAGS_MASK equ 0x8000
IMAGE_SEPARATE_DEBUG_MISMATCH	equ 0x8000 ;; when DBG was updated, the
					   ;; old checksum didn't match.

;;
;;  The .arch section is made up of headers, each describing an amask position/value
;;  pointing to an array of IMAGE_ARCHITECTURE_ENTRY's.  Each "array" (both the header
;;  and entry arrays) are terminiated by a quadword of 0xffffffffL.
;;
;;  NOTE: There may be quadwords of 0 sprinkled around and must be skipped.
;;

IMAGE_ARCHITECTURE_HEADER_R0 RECORD \
	iah_int2:	16,	;; MBZ
	iah_AmaskShift: 8,	;; Amask bit in question for this fixup
	iah_int1:	7,	;; MBZ
	iah_AmaskValue: 1	;; 1 -> code section depends on mask bit
				;; 0 -> new instruction depends on mask bit
IMAGE_ARCHITECTURE_HEADER	STRUC
r0				IMAGE_ARCHITECTURE_HEADER_R0 <>
FirstEntryRVA			dd ?	;; RVA into .arch section to array of ARCHITECTURE_ENTRY's
IMAGE_ARCHITECTURE_HEADER	ENDS
PIMAGE_ARCHITECTURE_HEADER	typedef ptr IMAGE_ARCHITECTURE_HEADER

IMAGE_ARCHITECTURE_ENTRY	STRUC
FixupInstRVA			dd ?	;; RVA of instruction to fixup
NewInst				dd ?	;; fixup instruction (see alphaops.h)
IMAGE_ARCHITECTURE_ENTRY	ENDS
PIMAGE_ARCHITECTURE_ENTRY	typedef ptr IMAGE_ARCHITECTURE_ENTRY


;; The following structure defines the new import object.  Note the values of the first two fields,
;; which must be set as stated in order to differentiate old and new import members.
;; Following this structure, the linker emits two null-terminated strings used to recreate the
;; import at the time of use.  The first string is the import's name, the second is the dll's name.

IMPORT_OBJECT_HDR_SIG2	equ 0xffff
IMPORT_OBJECT_HEADER_R0 RECORD \
	ioh_Reserved:	11,	;; Reserved. Must be zero.
	ioh_NameType:	3,	;; IMPORT_NAME_TYPE
	ioh_Type:	2	;; IMPORT_TYPE

IMPORT_OBJECT_HEADER	STRUC
Sig1			dw ?	;; Must be IMAGE_FILE_MACHINE_UNKNOWN
Sig2			dw ?	;; Must be IMPORT_OBJECT_HDR_SIG2.
Version			dw ?
Machine			dw ?
TimeDateStamp		dd ?	;; Time/date stamp
SizeOfData		dd ?	;; particularly useful for incremental links
UNION
  Ordinal		dw ?	;; if grf & IMPORT_OBJECT_ORDINAL
  Hint			dw ?
ENDS
r0			IMPORT_OBJECT_HEADER_R0 <>
IMPORT_OBJECT_HEADER	ENDS

IMPORT_OBJECT_CODE		equ 0
IMPORT_OBJECT_DATA		equ 1
IMPORT_OBJECT_CONST		equ 2

IMPORT_OBJECT_ORDINAL		equ 0	;; Import by ordinal
IMPORT_OBJECT_NAME		equ 1	;; Import name == public symbol name.
IMPORT_OBJECT_NAME_NO_PREFIX	equ 2	;; Import name == public symbol name skipping leading ?, @, or optionally _.
IMPORT_OBJECT_NAME_UNDECORATE	equ 3	;; Import name == public symbol name skipping leading ?, @, or optionally _
					;; and truncating at first @
;;
;; End Image Format
;;

;;
;; for move macros
;;

HEAP_NO_SERIALIZE		equ 0x00000001
HEAP_GROWABLE			equ 0x00000002
HEAP_GENERATE_EXCEPTIONS	equ 0x00000004
HEAP_ZERO_MEMORY		equ 0x00000008
HEAP_REALLOC_IN_PLACE_ONLY	equ 0x00000010
HEAP_TAIL_CHECKING_ENABLED	equ 0x00000020
HEAP_FREE_CHECKING_ENABLED	equ 0x00000040
HEAP_DISABLE_COALESCE_ON_FREE	equ 0x00000080
HEAP_CREATE_ALIGN_16		equ 0x00010000
HEAP_CREATE_ENABLE_TRACING	equ 0x00020000
HEAP_MAXIMUM_TAG		equ 0x0FFF
HEAP_PSEUDO_TAG_FLAG		equ 0x8000
HEAP_TAG_SHIFT			equ 18

HEAP_MAKE_TAG_FLAGS macro b, o
	exitm<b + (o shl 18)>
	endm

IS_TEXT_UNICODE_ASCII16			equ 0x0001
IS_TEXT_UNICODE_REVERSE_ASCII16		equ 0x0010

IS_TEXT_UNICODE_STATISTICS		equ 0x0002
IS_TEXT_UNICODE_REVERSE_STATISTICS	equ 0x0020

IS_TEXT_UNICODE_CONTROLS		equ 0x0004
IS_TEXT_UNICODE_REVERSE_CONTROLS	equ 0x0040

IS_TEXT_UNICODE_SIGNATURE		equ 0x0008
IS_TEXT_UNICODE_REVERSE_SIGNATURE	equ 0x0080

IS_TEXT_UNICODE_ILLEGAL_CHARS		equ 0x0100
IS_TEXT_UNICODE_ODD_LENGTH		equ 0x0200
IS_TEXT_UNICODE_DBCS_LEADBYTE		equ 0x0400
IS_TEXT_UNICODE_NULL_BYTES		equ 0x1000

IS_TEXT_UNICODE_UNICODE_MASK		equ 0x000F
IS_TEXT_UNICODE_REVERSE_MASK		equ 0x00F0
IS_TEXT_UNICODE_NOT_UNICODE_MASK	equ 0x0F00
IS_TEXT_UNICODE_NOT_ASCII_MASK		equ 0xF000

COMPRESSION_FORMAT_NONE		equ 0x0000
COMPRESSION_FORMAT_DEFAULT	equ 0x0001
COMPRESSION_FORMAT_LZNT1	equ 0x0002
COMPRESSION_ENGINE_STANDARD	equ 0x0000
COMPRESSION_ENGINE_MAXIMUM	equ 0x0100

RtlCompareMemory proto _CType :ptr, :ptr, :size_t

if defined(_M_AXP64) or defined(_M_IA64)

RtlEqualMemory macro S1, S2, L
	exitm<RtlCompareMemory(S1,S2,L) == L>
	endm
RtlCopyMemory proto _CType :ptr, :ptr, :size_t
RtlCopyMemory32 proto _CType :ptr, :ptr, :dword
RtlMoveMemory proto _CType :ptr, :ptr, :size_t
RtlFillMemory proto _CType :ptr, :size_t, :byte
RtlZeroMemory proto _CType :ptr, :size_t

else
RtlEqualMemory macro D, S, L
	exitm<!memcmp(D,S,L)>
	endm
RtlMoveMemory macro D, S, L
	exitm<memmove(D,S,L)>
	endm
RtlCopyMemory macro D, S, L
	exitm<memcpy(D,S,L)>
	endm
RtlFillMemory macro D, L, F
	exitm<memset(D,F,L)>
	endm
RtlZeroMemory macro D, L
	exitm<memset(D,0,L)>
	endm
endif


if defined(_ALPHA_) or defined(_M_IA64)

RtlMoveMemory64 proto _CType :ptr, :ptr, :qword
RtlFillMemory64 proto _CType :ptr, :qword, :byte
RtlZeroMemory64 proto _CType :ptr, :qword

endif

MESSAGE_RESOURCE_ENTRY		STRUC
_Length				dw ?
Flags				dw ?
Text				db ?
MESSAGE_RESOURCE_ENTRY		ENDS
PMESSAGE_RESOURCE_ENTRY		typedef ptr MESSAGE_RESOURCE_ENTRY

MESSAGE_RESOURCE_UNICODE	equ 0x0001

MESSAGE_RESOURCE_BLOCK		STRUC
LowId				dd ?
HighId				dd ?
OffsetToEntries			dd ?
MESSAGE_RESOURCE_BLOCK		ENDS
PMESSAGE_RESOURCE_BLOCK		typedef ptr MESSAGE_RESOURCE_BLOCK

MESSAGE_RESOURCE_DATA		STRUC
NumberOfBlocks			dd ?
Blocks				MESSAGE_RESOURCE_BLOCK <>
MESSAGE_RESOURCE_DATA		ENDS
PMESSAGE_RESOURCE_DATA		typedef ptr MESSAGE_RESOURCE_DATA


RTL_CRITICAL_SECTION_DEBUG	STRUC
_Type				dw ?
CreatorBackTraceIndex		dw ?
CriticalSection			PVOID ?;PRTL_CRITICAL_SECTION ?
ProcessLocksList		LIST_ENTRY <>
EntryCount			dd ?
ContentionCount			dd ?
Spare				dd 2 dup(?)
RTL_CRITICAL_SECTION_DEBUG	ENDS
PRTL_CRITICAL_SECTION_DEBUG	typedef ptr RTL_CRITICAL_SECTION_DEBUG
RTL_RESOURCE_DEBUG		typedef RTL_CRITICAL_SECTION_DEBUG
PRTL_RESOURCE_DEBUG		typedef ptr RTL_CRITICAL_SECTION_DEBUG

RTL_CRITSECT_TYPE		equ 0
RTL_RESOURCE_TYPE		equ 1

RTL_CRITICAL_SECTION		STRUC
DebugInfo			PRTL_CRITICAL_SECTION_DEBUG ?

    ;;
    ;;	The following three fields control entering and exiting the critical
    ;;	section for the resource
    ;;

LockCount			LONG ?
RecursionCount			LONG ?
OwningThread			HANDLE ? ;; from the thread's ClientId->UniqueThread

LockSemaphore			HANDLE ?
SpinCount			dd ?
RTL_CRITICAL_SECTION		ENDS
PRTL_CRITICAL_SECTION		typedef ptr RTL_CRITICAL_SECTION

SEF_DACL_AUTO_INHERIT		equ 0x1
SEF_SACL_AUTO_INHERIT		equ 0x2
SEF_DEFAULT_DESCRIPTOR_FOR_OBJECT equ 0x4
SEF_AVOID_PRIVILEGE_CHECK	equ 0x8

WT_EXECUTEDEFAULT		equ 0x00000000
WT_EXECUTEINIOTHREAD		equ 0x00000001
WT_EXECUTEINUITHREAD		equ 0x00000002
WT_EXECUTEINWAITTHREAD		equ 0x00000004
WT_EXECUTEDELETEWAIT		equ 0x00000008
WT_EXECUTEINLONGTHREAD		equ 0x00000010

WAITORTIMERCALLBACK_T		typedef proto :PVOID, :BOOLEAN
WAITORTIMERCALLBACKFUNC		typedef ptr WAITORTIMERCALLBACK_T
WORKERCALLBACK_T		typedef proto :PVOID
WORKERCALLBACKFUNC		typedef ptr WORKERCALLBACK_T

DLL_PROCESS_ATTACH		equ 1
DLL_THREAD_ATTACH		equ 2
DLL_THREAD_DETACH		equ 3
DLL_PROCESS_DETACH		equ 0

;;
;; Defines for the READ flags for Eventlogging
;;
EVENTLOG_SEQUENTIAL_READ	equ 0X0001
EVENTLOG_SEEK_READ		equ 0X0002
EVENTLOG_FORWARDS_READ		equ 0X0004
EVENTLOG_BACKWARDS_READ		equ 0X0008

;;
;; The types of events that can be logged.
;;
EVENTLOG_SUCCESS		equ 0X0000
EVENTLOG_ERROR_TYPE		equ 0x0001
EVENTLOG_WARNING_TYPE		equ 0x0002
EVENTLOG_INFORMATION_TYPE	equ 0x0004
EVENTLOG_AUDIT_SUCCESS		equ 0x0008
EVENTLOG_AUDIT_FAILURE		equ 0x0010

;;
;; Defines for the WRITE flags used by Auditing for paired events
;; These are not implemented in Product 1
;;

EVENTLOG_START_PAIRED_EVENT    equ 0x0001
EVENTLOG_END_PAIRED_EVENT      equ 0x0002
EVENTLOG_END_ALL_PAIRED_EVENTS equ 0x0004
EVENTLOG_PAIRED_EVENT_ACTIVE   equ 0x0008
EVENTLOG_PAIRED_EVENT_INACTIVE equ 0x0010

;;
;; Structure that defines the header of the Eventlog record. This is the
;; fixed-sized portion before all the variable-length strings, binary
;; data and pad bytes.
;;
;; TimeGenerated is the time it was generated at the client.
;; TimeWritten is the time it was put into the log at the server end.
;;

EVENTLOGRECORD			STRUC
_Length				dd ?	;; Length of full record
Reserved			dd ?	;; Used by the service
RecordNumber			dd ?	;; Absolute record number
TimeGenerated			dd ?	;; Seconds since 1-1-1970
TimeWritten			dd ?	;; Seconds since 1-1-1970
EventID				dd ?
EventType			dw ?
NumStrings			dw ?
EventCategory			dw ?
ReservedFlags			dw ?	;; For use with paired events (auditing)
ClosingRecordNumber		dd ?	;; For use with paired events (auditing)
StringOffset			dd ?	;; Offset from beginning of record
UserSidLength			dd ?
UserSidOffset			dd ?
DataLength			dd ?
DataOffset			dd ?	;; Offset from beginning of record
    ;;
    ;; Then follow:
    ;;
    ;; WCHAR SourceName[]
    ;; WCHAR Computername[]
    ;; SID   UserSid
    ;; WCHAR Strings[]
    ;; BYTE  Data[]
    ;; CHAR  Pad[]
    ;; DWORD Length;
    ;;
EVENTLOGRECORD			ENDS
PEVENTLOGRECORD			typedef ptr EVENTLOGRECORD

MAXLOGICALLOGNAMESIZE		equ 256

EVENTSFORLOGFILE		STRUC
ulSize				dd ?
szLogicalLogFile		WCHAR MAXLOGICALLOGNAMESIZE dup(?) ;; name of the logical file-security/application/system
ulNumRecords			dd ?
pEventLogRecords		EVENTLOGRECORD <>
EVENTSFORLOGFILE		ENDS
PEVENTSFORLOGFILE		typedef ptr EVENTSFORLOGFILE

PACKEDEVENTINFO			STRUC
ulSize				dd ?	;;total size of the structure
ulNumEventsForLogFile		dd ?	;;number of EventsForLogFile structure that follow
ulOffsets			dd ?	;;the offsets from the start of this structure to the EVENTSFORLOGFILE structure
PACKEDEVENTINFO			ENDS
PPACKEDEVENTINFO		typedef ptr PACKEDEVENTINFO

DBG_CONTINUE			equ 0x00010002
DBG_TERMINATE_THREAD		equ 0x40010003
DBG_TERMINATE_PROCESS		equ 0x40010004
DBG_CONTROL_C			equ 0x40010005
DBG_CONTROL_BREAK		equ 0x40010008
DBG_EXCEPTION_NOT_HANDLED	equ 0x80010001

;;
;; Registry Specific Access Rights.
;;

KEY_QUERY_VALUE			equ 0x0001
KEY_SET_VALUE			equ 0x0002
KEY_CREATE_SUB_KEY		equ 0x0004
KEY_ENUMERATE_SUB_KEYS		equ 0x0008
KEY_NOTIFY			equ 0x0010
KEY_CREATE_LINK			equ 0x0020

KEY_READ	equ ((STANDARD_RIGHTS_READ or KEY_QUERY_VALUEor or KEY_ENUMERATE_SUB_KEYS or KEY_NOTIFY) \
		 and (not SYNCHRONIZE))
KEY_WRITE	equ ((STANDARD_RIGHTS_WRITE or KEY_SET_VALUE or KEY_CREATE_SUB_KEY) \
		 and (not SYNCHRONIZE))
KEY_EXECUTE	equ (KEY_READ and (not SYNCHRONIZE))
KEY_ALL_ACCESS	equ ((STANDARD_RIGHTS_ALL or KEY_QUERY_VALUE or KEY_SET_VALUE or KEY_CREATE_SUB_KEY \
		 or KEY_ENUMERATE_SUB_KEYS or KEY_NOTIFY or KEY_CREATE_LINK) and (not SYNCHRONIZE))

;;
;; Open/Create Options
;;

REG_OPTION_RESERVED		equ 0x00000000	;; Parameter is reserved
REG_OPTION_NON_VOLATILE		equ 0x00000000	;; Key is preserved
						;; when system is rebooted
REG_OPTION_VOLATILE		equ 0x00000001	;; Key is not preserved
						;; when system is rebooted
REG_OPTION_CREATE_LINK		equ 0x00000002	;; Created key is a
						;; symbolic link
REG_OPTION_BACKUP_RESTORE	equ 0x00000004	;; open for backup or restore
						;; special access rules
						;; privilege required
REG_OPTION_OPEN_LINK		equ 0x00000008	;; Open symbolic link

REG_LEGAL_OPTION		equ REG_OPTION_RESERVED or \
				    REG_OPTION_NON_VOLATILE or \
				    REG_OPTION_VOLATILE or \
				    REG_OPTION_CREATE_LINK or \
				    REG_OPTION_BACKUP_RESTORE or \
				    REG_OPTION_OPEN_LINK

;;
;; Key creation/open disposition
;;

REG_CREATED_NEW_KEY		equ 0x00000001	;; New Registry Key created
REG_OPENED_EXISTING_KEY		equ 0x00000002	;; Existing Key opened

;;
;; Key restore flags
;;

REG_WHOLE_HIVE_VOLATILE		equ 0x00000001	;; Restore whole hive volatile
REG_REFRESH_HIVE		equ 0x00000002	;; Unwind changes to last flush
REG_NO_LAZY_FLUSH		equ 0x00000004	;; Never lazy flush this hive

;; end_ntddk end_wdm end_nthal

;;
;; Notify filter values
;;
REG_NOTIFY_CHANGE_NAME		equ 0x00000001	;; Create or delete (child)
REG_NOTIFY_CHANGE_ATTRIBUTES	equ 0x00000002
REG_NOTIFY_CHANGE_LAST_SET	equ 0x00000004	;; time stamp
REG_NOTIFY_CHANGE_SECURITY	equ 0x00000008

REG_LEGAL_CHANGE_FILTER equ REG_NOTIFY_CHANGE_NAME   or \
			REG_NOTIFY_CHANGE_ATTRIBUTES or \
			REG_NOTIFY_CHANGE_LAST_SET   or \
			REG_NOTIFY_CHANGE_SECURITY

;;
;;
;; Predefined Value Types.
;;

REG_NONE			equ 0	;; No value type
REG_SZ				equ 1	;; Unicode nul terminated string
REG_EXPAND_SZ			equ 2	;; Unicode nul terminated string
					;; (with environment variable references)
REG_BINARY			equ 3	;; Free form binary
REG_DWORD			equ 4	;; 32-bit number
REG_DWORD_LITTLE_ENDIAN		equ 4	;; 32-bit number (same as REG_DWORD)
REG_DWORD_BIG_ENDIAN		equ 5	;; 32-bit number
REG_LINK			equ 6	;; Symbolic Link (unicode)
REG_MULTI_SZ			equ 7	;; Multiple Unicode strings
REG_RESOURCE_LIST		equ 8	;; Resource list in the resource map
REG_FULL_RESOURCE_DESCRIPTOR	equ 9	;; Resource list in the hardware description
REG_RESOURCE_REQUIREMENTS_LIST	equ 10

;;
;; Service Types (Bit Mask)
;;
SERVICE_KERNEL_DRIVER	       equ 0x00000001
SERVICE_FILE_SYSTEM_DRIVER     equ 0x00000002
SERVICE_ADAPTER		       equ 0x00000004
SERVICE_RECOGNIZER_DRIVER      equ 0x00000008

SERVICE_DRIVER		       equ SERVICE_KERNEL_DRIVER or \
				   SERVICE_FILE_SYSTEM_DRIVER or \
				   SERVICE_RECOGNIZER_DRIVER

SERVICE_WIN32_OWN_PROCESS      equ 0x00000010
SERVICE_WIN32_SHARE_PROCESS    equ 0x00000020
SERVICE_WIN32		       equ SERVICE_WIN32_OWN_PROCESS or \
				   SERVICE_WIN32_SHARE_PROCESS

SERVICE_INTERACTIVE_PROCESS    equ 0x00000100

SERVICE_TYPE_ALL	       equ SERVICE_WIN32 or \
				   SERVICE_ADAPTER or \
				   SERVICE_DRIVER  or \
				   SERVICE_INTERACTIVE_PROCESS

;;
;; Start Type
;;

SERVICE_BOOT_START	       equ 0x00000000
SERVICE_SYSTEM_START	       equ 0x00000001
SERVICE_AUTO_START	       equ 0x00000002
SERVICE_DEMAND_START	       equ 0x00000003
SERVICE_DISABLED	       equ 0x00000004

;;
;; Error control type
;;
SERVICE_ERROR_IGNORE	       equ 0x00000000
SERVICE_ERROR_NORMAL	       equ 0x00000001
SERVICE_ERROR_SEVERE	       equ 0x00000002
SERVICE_ERROR_CRITICAL	       equ 0x00000003

;;
;;
;; Define the registry driver node enumerations
;;

    DriverType		     equ SERVICE_KERNEL_DRIVER
    FileSystemType	     equ SERVICE_FILE_SYSTEM_DRIVER
    Win32ServiceOwnProcess   equ SERVICE_WIN32_OWN_PROCESS
    Win32ServiceShareProcess equ SERVICE_WIN32_SHARE_PROCESS
    AdapterType		     equ SERVICE_ADAPTER
    RecognizerType	     equ SERVICE_RECOGNIZER_DRIVER

    BootLoad	equ SERVICE_BOOT_START
    SystemLoad	equ SERVICE_SYSTEM_START
    AutoLoad	equ SERVICE_AUTO_START
    DemandLoad	equ SERVICE_DEMAND_START
    DisableLoad equ SERVICE_DISABLED

    IgnoreError	  equ SERVICE_ERROR_IGNORE
    NormalError	  equ SERVICE_ERROR_NORMAL
    SevereError	  equ SERVICE_ERROR_SEVERE
    CriticalError equ SERVICE_ERROR_CRITICAL

;;
;; IOCTL_TAPE_ERASE definitions
;;

TAPE_ERASE_SHORT		equ 0
TAPE_ERASE_LONG			equ 1

TAPE_ERASE			STRUC
_Type				DWORD ?
Immediate			BOOLEAN ?
TAPE_ERASE			ENDS
PTAPE_ERASE			typedef ptr TAPE_ERASE

;;
;; IOCTL_TAPE_PREPARE definitions
;;

TAPE_LOAD			equ 0
TAPE_UNLOAD			equ 1
TAPE_TENSION			equ 2
TAPE_LOCK			equ 3
TAPE_UNLOCK			equ 4
TAPE_FORMAT			equ 5

TAPE_PREPARE			STRUC
Operation			DWORD ?
Immediate			BOOLEAN ?
TAPE_PREPARE			ENDS
PTAPE_PREPARE			typedef ptr TAPE_PREPARE

;;
;; IOCTL_TAPE_WRITE_MARKS definitions
;;

TAPE_SETMARKS			equ 0
TAPE_FILEMARKS			equ 1
TAPE_SHORT_FILEMARKS		equ 2
TAPE_LONG_FILEMARKS		equ 3

TAPE_WRITE_MARKS		STRUC
_Type				DWORD ?
Count				DWORD ?
Immediate			BOOLEAN ?
TAPE_WRITE_MARKS		ENDS
PTAPE_WRITE_MARKS		typedef ptr TAPE_WRITE_MARKS

;;
;; IOCTL_TAPE_GET_POSITION definitions
;;

TAPE_ABSOLUTE_POSITION		equ 0
TAPE_LOGICAL_POSITION		equ 1
TAPE_PSEUDO_LOGICAL_POSITION	equ 2

TAPE_GET_POSITION		STRUC
_Type				DWORD ?
Partition			DWORD ?
_Offset				LARGE_INTEGER <>
TAPE_GET_POSITION		ENDS
PTAPE_GET_POSITION		typedef ptr TAPE_GET_POSITION

;;
;; IOCTL_TAPE_SET_POSITION definitions
;;

TAPE_REWIND			equ 0
TAPE_ABSOLUTE_BLOCK		equ 1
TAPE_LOGICAL_BLOCK		equ 2
TAPE_PSEUDO_LOGICAL_BLOCK	equ 3
TAPE_SPACE_END_OF_DATA		equ 4
TAPE_SPACE_RELATIVE_BLOCKS	equ 5
TAPE_SPACE_FILEMARKS		equ 6
TAPE_SPACE_SEQUENTIAL_FMKS	equ 7
TAPE_SPACE_SETMARKS		equ 8
TAPE_SPACE_SEQUENTIAL_SMKS	equ 9

TAPE_SET_POSITION		STRUC
Method				DWORD ?
Partition			DWORD ?
_Offset				LARGE_INTEGER <>
Immediate			BOOLEAN ?
TAPE_SET_POSITION		ENDS
PTAPE_SET_POSITION		typedef ptr TAPE_SET_POSITION

;;
;; IOCTL_TAPE_GET_DRIVE_PARAMS definitions
;;

;;
;; Definitions for FeaturesLow parameter
;;

TAPE_DRIVE_FIXED		equ 0x00000001
TAPE_DRIVE_SELECT		equ 0x00000002
TAPE_DRIVE_INITIATOR		equ 0x00000004

TAPE_DRIVE_ERASE_SHORT		equ 0x00000010
TAPE_DRIVE_ERASE_LONG		equ 0x00000020
TAPE_DRIVE_ERASE_BOP_ONLY	equ 0x00000040
TAPE_DRIVE_ERASE_IMMEDIATE	equ 0x00000080

TAPE_DRIVE_TAPE_CAPACITY	equ 0x00000100
TAPE_DRIVE_TAPE_REMAINING	equ 0x00000200
TAPE_DRIVE_FIXED_BLOCK		equ 0x00000400
TAPE_DRIVE_VARIABLE_BLOCK	equ 0x00000800

TAPE_DRIVE_WRITE_PROTECT	equ 0x00001000
TAPE_DRIVE_EOT_WZ_SIZE		equ 0x00002000

TAPE_DRIVE_ECC			equ 0x00010000
TAPE_DRIVE_COMPRESSION		equ 0x00020000
TAPE_DRIVE_PADDING		equ 0x00040000
TAPE_DRIVE_REPORT_SMKS		equ 0x00080000

TAPE_DRIVE_GET_ABSOLUTE_BLK	equ 0x00100000
TAPE_DRIVE_GET_LOGICAL_BLK	equ 0x00200000
TAPE_DRIVE_SET_EOT_WZ_SIZE	equ 0x00400000

TAPE_DRIVE_EJECT_MEDIA		equ 0x01000000
TAPE_DRIVE_CLEAN_REQUESTS	equ 0x02000000
TAPE_DRIVE_SET_CMP_BOP_ONLY	equ 0x04000000

TAPE_DRIVE_RESERVED_BIT		equ 0x80000000 ;;don't use this bit!
;;					       ;;can't be a low features bit!
;;					       ;;reserved; high features only

;;
;; Definitions for FeaturesHigh parameter
;;

TAPE_DRIVE_LOAD_UNLOAD		equ 0x80000001
TAPE_DRIVE_TENSION		equ 0x80000002
TAPE_DRIVE_LOCK_UNLOCK		equ 0x80000004
TAPE_DRIVE_REWIND_IMMEDIATE	equ 0x80000008

TAPE_DRIVE_SET_BLOCK_SIZE	equ 0x80000010
TAPE_DRIVE_LOAD_UNLD_IMMED	equ 0x80000020
TAPE_DRIVE_TENSION_IMMED	equ 0x80000040
TAPE_DRIVE_LOCK_UNLK_IMMED	equ 0x80000080

TAPE_DRIVE_SET_ECC		equ 0x80000100
TAPE_DRIVE_SET_COMPRESSION	equ 0x80000200
TAPE_DRIVE_SET_PADDING		equ 0x80000400
TAPE_DRIVE_SET_REPORT_SMKS	equ 0x80000800

TAPE_DRIVE_ABSOLUTE_BLK		equ 0x80001000
TAPE_DRIVE_ABS_BLK_IMMED	equ 0x80002000
TAPE_DRIVE_LOGICAL_BLK		equ 0x80004000
TAPE_DRIVE_LOG_BLK_IMMED	equ 0x80008000

TAPE_DRIVE_END_OF_DATA		equ 0x80010000
TAPE_DRIVE_RELATIVE_BLKS	equ 0x80020000
TAPE_DRIVE_FILEMARKS		equ 0x80040000
TAPE_DRIVE_SEQUENTIAL_FMKS	equ 0x80080000

TAPE_DRIVE_SETMARKS		equ 0x80100000
TAPE_DRIVE_SEQUENTIAL_SMKS	equ 0x80200000
TAPE_DRIVE_REVERSE_POSITION	equ 0x80400000
TAPE_DRIVE_SPACE_IMMEDIATE	equ 0x80800000

TAPE_DRIVE_WRITE_SETMARKS	equ 0x81000000
TAPE_DRIVE_WRITE_FILEMARKS	equ 0x82000000
TAPE_DRIVE_WRITE_SHORT_FMKS	equ 0x84000000
TAPE_DRIVE_WRITE_LONG_FMKS	equ 0x88000000

TAPE_DRIVE_WRITE_MARK_IMMED	equ 0x90000000
TAPE_DRIVE_FORMAT		equ 0xA0000000
TAPE_DRIVE_FORMAT_IMMEDIATE	equ 0xC0000000
TAPE_DRIVE_HIGH_FEATURES	equ 0x80000000 ;;mask for high features flag

TAPE_GET_DRIVE_PARAMETERS	STRUC
ECC				BOOLEAN ?
Compression			BOOLEAN ?
DataPadding			BOOLEAN ?
ReportSetmarks			BOOLEAN ?
DefaultBlockSize		DWORD ?
MaximumBlockSize		DWORD ?
MinimumBlockSize		DWORD ?
MaximumPartitionCount		DWORD ?
FeaturesLow			DWORD ?
FeaturesHigh			DWORD ?
EOTWarningZoneSize		DWORD ?
TAPE_GET_DRIVE_PARAMETERS	ENDS
PTAPE_GET_DRIVE_PARAMETERS	typedef ptr TAPE_GET_DRIVE_PARAMETERS

;;
;; IOCTL_TAPE_SET_DRIVE_PARAMETERS definitions
;;

TAPE_SET_DRIVE_PARAMETERS	STRUC
ECC				BOOLEAN ?
Compression			BOOLEAN ?
DataPadding			BOOLEAN ?
ReportSetmarks			BOOLEAN ?
EOTWarningZoneSize		DWORD ?
TAPE_SET_DRIVE_PARAMETERS	ENDS
PTAPE_SET_DRIVE_PARAMETERS	typedef ptr TAPE_SET_DRIVE_PARAMETERS

;;
;; IOCTL_TAPE_GET_MEDIA_PARAMETERS definitions
;;

TAPE_GET_MEDIA_PARAMETERS	STRUC
Capacity			LARGE_INTEGER <>
Remaining			LARGE_INTEGER <>
BlockSize			DWORD ?
PartitionCount			DWORD ?
WriteProtected			BOOLEAN ?
TAPE_GET_MEDIA_PARAMETERS	ENDS
PTAPE_GET_MEDIA_PARAMETERS	typedef ptr TAPE_GET_MEDIA_PARAMETERS

;;
;; IOCTL_TAPE_SET_MEDIA_PARAMETERS definitions
;;

TAPE_SET_MEDIA_PARAMETERS	STRUC
BlockSize			dd ?
TAPE_SET_MEDIA_PARAMETERS	ENDS
PTAPE_SET_MEDIA_PARAMETERS	typedef ptr TAPE_SET_MEDIA_PARAMETERS

;;
;; IOCTL_TAPE_CREATE_PARTITION definitions
;;

TAPE_FIXED_PARTITIONS		equ 0
TAPE_SELECT_PARTITIONS		equ 1
TAPE_INITIATOR_PARTITIONS	equ 2

TAPE_CREATE_PARTITION		STRUC
Method				dd ?
Count				dd ?
_Size				dd ?
TAPE_CREATE_PARTITION		ENDS
PTAPE_CREATE_PARTITION		typedef ptr TAPE_CREATE_PARTITION

endif	; _WINNT_

.list
