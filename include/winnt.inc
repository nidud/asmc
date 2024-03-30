.pragma list(push, 0)

ifndef _WINNT_
define _WINNT_

include ctype.inc
include string.inc
include basetsd.inc
ifndef _WIN32_FUSION
define _WIN32_FUSION
endif

define ANYSIZE_ARRAY 1

.pragma comment(lib, ntdll)

if defined(_WIN64) or defined(_M_ALPHA)
define MAX_NATURAL_ALIGNMENT		8
define MEMORY_ALLOCATION_ALIGNMENT	16
else
define MAX_NATURAL_ALIGNMENT		4
define MEMORY_ALLOCATION_ALIGNMENT	8
endif
.pragma pack(push, MAX_NATURAL_ALIGNMENT)

TYPE_ALIGNMENT macro t
	local S1
	S1 STRUC
	l1 db ?
	l2 t ?
	S1 ENDS
	exitm<S1.l2>
	endm

TYPE_ALIGNMENTS macro s
	local S1
	S1 STRUC
	l1 db ?
	l2 s <>
	S1 ENDS
	exitm<S1.l2>
	endm

ifdef _WIN64
ifdef _AMD64_
PROBE_ALIGNMENT macro _s
	exitm<TYPE_ALIGNMENT(DWORD)>
	endm
elseifdef _IA64_
PROBE_ALIGNMENT macro _s
if TYPE_ALIGNMENT(_s) GT TYPE_ALIGNMENT(DWORD)
	exitm<TYPE_ALIGNMENT(_s)>
else
	exitm<TYPE_ALIGNMENT(DWORD)>
endif
	endm
else
	.err <No Target Architecture>
endif
PROBE_ALIGNMENT32 macro _s
	exitm<TYPE_ALIGNMENT(DWORD)>
	endm
else
PROBE_ALIGNMENT macro _s
	exitm<TYPE_ALIGNMENT(DWORD)>
	endm
endif

ifndef SYSTEM_CACHE_ALIGNMENT_SIZE
if defined(_AMD64_) or defined(_X86_)
define SYSTEM_CACHE_ALIGNMENT_SIZE 64
else
define SYSTEM_CACHE_ALIGNMENT_SIZE 128
endif
endif

ifndef DECLSPEC_ALIGN
DECLSPEC_ALIGN macro x
if (_MSC_VER GE 1300)
	exitm<x>
else
	exitm<>
endif
	endm
endif

ifdef DEPRECATE_DDK_FUNCTIONS
ifdef _NTDDK_
DECLSPEC_DEPRECATED_DDK equ DECSPEC_DEPRECATED
ifdef DEPRECATE_SUPPORTED
PRAGMA_DEPRECATED_DDK	equ 1
endif
else
DECLSPEC_DEPRECATED_DDK equ 1
PRAGMA_DEPRECATED_DDK	equ 1
endif
else
DECLSPEC_DEPRECATED_DDK equ 1
PRAGMA_DEPRECATED_DDK	equ 0
endif


PVOID		typedef ptr
PVOID64		typedef ptr
ifndef VOID
VOID		equ <>
CHAR		typedef sbyte
LONG		typedef sdword
endif

WCHAR		typedef word ; 16-bit UNICODE character
PWCH		typedef ptr WCHAR
LPWCH		typedef ptr WCHAR
PWCHAR		typedef ptr WCHAR
PCWCH		typedef ptr WCHAR
LPCWCH		typedef ptr WCHAR
NWPSTR		typedef ptr WCHAR
LPWSTR		typedef ptr WCHAR
PWSTR		typedef ptr WCHAR
PZPWSTR		typedef ptr PWSTR
PCZPWSTR	typedef ptr PWSTR
LPUWSTR		typedef ptr WCHAR
PUWSTR		typedef ptr WCHAR
LPCWSTR		typedef ptr WCHAR
PCWSTR		typedef ptr WCHAR
PZPCWSTR	typedef ptr PCWSTR
LPCUWSTR	typedef ptr WCHAR
PCUWSTR		typedef ptr WCHAR

PZZWSTR		typedef ptr WCHAR
PCZZWSTR	typedef ptr WCHAR
PUZZWSTR	typedef ptr WCHAR ;UNALIGNED
PCUZZWSTR	typedef ptr WCHAR ;UNALIGNED

PNZWCH		typedef ptr WCHAR
PCNZWCH		typedef ptr WCHAR
PUNZWCH		typedef ptr WCHAR ;UNALIGNED
PCUNZWCH	typedef ptr WCHAR ;UNALIGNED

if _WIN32_WINNT GE 0x0600

PCWCHAR		typedef ptr WCHAR
PCUWCHAR	typedef ptr WCHAR ;UNALIGNED
UCSCHAR		typedef dword

UCSCHAR_INVALID_CHARACTER equ 0xffffffff

MIN_UCSCHAR	equ 0
MAX_UCSCHAR	equ 0x0010FFFF

PUCSCHAR	typedef ptr UCSCHAR
PCUCSCHAR	typedef ptr UCSCHAR
PUCSSTR		typedef ptr UCSCHAR
PUUCSSTR	typedef ptr UCSCHAR ;UNALIGNED
PCUCSSTR	typedef ptr UCSCHAR
PCUUCSSTR	typedef ptr UCSCHAR ;UNALIGNED
PUUCSCHAR	typedef ptr UCSCHAR ;UNALIGNED
PCUUCSCHAR	typedef ptr UCSCHAR ;UNALIGNED

endif

PCH		typedef ptr CHAR
LPCH		typedef ptr CHAR
PCCH		typedef ptr CHAR
PCHAR		typedef ptr CHAR
LPCCH		typedef ptr CHAR
NPSTR		typedef ptr CHAR
LPSTR		typedef ptr CHAR
PSTR		typedef ptr CHAR
PZPSTR		typedef ptr PSTR
PCZPSTR		typedef ptr PSTR
LPCSTR		typedef ptr CHAR
PCSTR		typedef ptr CHAR
PZPCSTR		typedef ptr PCSTR
PZZSTR		typedef ptr CHAR
PCZZSTR		typedef ptr CHAR
PNZCH		typedef ptr CHAR
PCNZCH		typedef ptr CHAR

ifdef _UNICODE

ifndef _TCHAR_DEFINED
define _TCHAR_DEFINED
TBYTE		typedef WCHAR
TCHAR		typedef WCHAR
PTCHAR		typedef ptr WCHAR
PTBYTE		typedef ptr WCHAR
endif

PTCH		typedef LPWCH
LPTCH		typedef LPWCH
PCTCH		typedef LPCWCH
LPCTCH		typedef LPCWCH
PTSTR		typedef LPWSTR
LPTSTR		typedef LPWSTR
PCTSTR		typedef LPCWSTR
LPCTSTR		typedef LPCWSTR
LPUTSTR		typedef LPUWSTR
PUTSTR		typedef LPUWSTR
PCUTSTR		typedef LPCUWSTR
LPCUTSTR	typedef LPCUWSTR

PZZTSTR		typedef PZZWSTR
PCZZTSTR	typedef PCZZWSTR
PUZZTSTR	typedef PUZZWSTR
PCUZZTSTR	typedef PCUZZWSTR
PNZTCH		typedef PNZWCH
PCNZTCH		typedef PCNZWCH
PUNZTCH		typedef PUNZWCH
PCUNZTCH	typedef PCUNZWCH

__TEXT macro quote
	exitm<quote>
	endm

else ; _UNICODE

ifndef _TCHAR_DEFINED
define _TCHAR_DEFINED
TBYTE		typedef CHAR
TCHAR		typedef CHAR
PTCHAR		typedef ptr CHAR
PTBYTE		typedef ptr CHAR
endif

PTCH		typedef LPCH
LPTCH		typedef LPCH
PCTCH		typedef LPCCH
LPCTCH		typedef LPCCH
PTSTR		typedef LPSTR
LPTSTR		typedef LPSTR
PUTSTR		typedef LPSTR
LPUTSTR		typedef LPSTR
PCTSTR		typedef LPCSTR
LPCTSTR		typedef LPCSTR
PCUTSTR		typedef LPCSTR
LPCUTSTR	typedef LPCSTR
PZZTSTR		typedef PZZSTR
PUZZTSTR	typedef PZZSTR
PCZZTSTR	typedef PCZZSTR
PCUZZTSTR	typedef PCZZSTR
PNZTCH		typedef PNZCH
PUNZTCH		typedef PNZCH
PCNZTCH		typedef PCNZCH
PCUNZTCH	typedef PCNZCH

__TEXT	macro quote
	exitm<quote>
	endm

endif ; _UNICODE

TEXT	macro quote
	exitm<__TEXT(quote)>
	endm

PSHORT	typedef ptr sword
PLONG	typedef ptr LONG

ALL_PROCESSOR_GROUPS	equ 0xffff


PROCESSOR_NUMBER	STRUC
_Group			dw ?
Number			db ?
Reserved		db ?
PROCESSOR_NUMBER	ENDS
PPROCESSOR_NUMBER	typedef ptr PROCESSOR_NUMBER


GROUP_AFFINITY		STRUC
Mask			KAFFINITY ?
_Group			dw ?
Reserved		dw 3 dup(?)
GROUP_AFFINITY		ENDS
PGROUP_AFFINITY		typedef ptr GROUP_AFFINITY


HANDLE	typedef ptr
PHANDLE typedef ptr HANDLE
FCHAR	typedef BYTE
FSHORT	typedef WORD
FLONG	typedef DWORD

ifdef STRICT
DECLARE_HANDLE macro h_name
	&h_name&__ struc
	unused	   SINT ?
	&h_name&__ ends
	exitm<h_name typedef ptr &h_name&__>
	endm
else
DECLARE_HANDLE macro name
	exitm<name typedef HANDLE>
	endm
endif

ifndef _HRESULT_DEFINED
define _HRESULT_DEFINED
HRESULT typedef LONG
endif

PDWORD		typedef ptr DWORD
CCHAR		typedef CHAR
LCID		typedef DWORD
PLCID		typedef PDWORD
LANGID		typedef WORD

APPLICATION_ERROR_MASK	     equ 0x20000000
ERROR_SEVERITY_SUCCESS	     equ 0x00000000
ERROR_SEVERITY_INFORMATIONAL equ 0x40000000
ERROR_SEVERITY_WARNING	     equ 0x80000000
ERROR_SEVERITY_ERROR	     equ 0xC0000000

FLOAT128	STRUC
LowPart		dq ?
HighPart	dq ?
FLOAT128	ENDS
PFLOAT128	typedef PTR FLOAT128


define _ULONGLONG_

if not defined(_M_IX86) or (defined(_INTEGRAL_MAX_BITS) and _INTEGRAL_MAX_BITS GE 64)
LONGLONG	typedef sqword
ULONGLONG	typedef qword
MAXLONGLONG	equ 0x7fffffffffffffff
else
LONGLONG	typedef sqword ; double - REAL8
ULONGLONG	typedef qword  ; double - REAL8
endif
PLONGLONG	typedef PTR LONGLONG
PULONGLONG	typedef PTR ULONGLONG

USN		typedef LONGLONG

ifdef MIDL_PASS
LARGE_INTEGER	STRUC
else
LARGE_INTEGER	UNION
    STRUC
      LowPart	dd ?
      HighPart	LONG ?
    ENDS
    STRUC u
      LowPart	dd ?
      HighPart	LONG ?
    ENDS
endif
    QuadPart	LONGLONG ?
LARGE_INTEGER	ENDS
PLARGE_INTEGER	typedef PTR LARGE_INTEGER

ifdef MIDL_PASS
ULARGE_INTEGER	STRUC
else
ULARGE_INTEGER	UNION
    STRUC
      LowPart	dd ?
      HighPart	dd ?
    ENDS
    STRUC u
      LowPart	dd ?
      HighPart	dd ?
    ENDS
endif
    QuadPart	ULONGLONG ?
ULARGE_INTEGER	ENDS
PULARGE_INTEGER typedef PTR ULARGE_INTEGER


LUID		STRUC
LowPart		dd ?
HighPart	LONG ?
LUID		ENDS

PLUID		typedef PTR LUID

_DWORDLONG_	equ 1

DWORDLONG	typedef ULONGLONG
PDWORDLONG	typedef PTR DWORDLONG


if defined(MIDL_PASS) OR defined(_M_CEE_PURE) OR defined(_68K_) OR defined(_MPPC_) OR defined(_M_IA64) OR defined(_M_AMD64)
Int32x32To64 proto fastcall :int_t, :int_t {
	movsxd	rax, ecx
	movsxd	rdx, edx
	imul	rax, rdx
	}
UInt32x32To64 proto fastcall :ULONG, :ULONG {
	mov	eax, ecx
	imul	rax, rdx
	}
Int64ShllMod32 proto fastcall :ULONGLONG, :ULONG {
	mov	rax, rcx
	mov	ecx, edx
	shl	rax, cl
	}
Int64ShraMod32 proto fastcall :LONGLONG, :ULONG {
	mov	rax, rcx
	mov	ecx, edx
	sar	rax, cl
	}
Int64ShrlMod32 proto fastcall :ULONGLONG, :ULONG {
	mov	rax, rcx
	mov	ecx, edx
	shr	rax, cl
	}
elseifdef _M_IX86
Int32x32To64 proto watcall :LONG, :LONG {
	imul	edx
	}
UInt32x32To64 proto watcall :ULONG, :ULONG {
	mul	edx
	}
Int64ShllMod32 proto watcall :ULONGLONG, :ULONG {
	shld	edx, eax, cl
	shl	eax, cl
	}
Int64ShraMod32 proto watcall :LONGLONG, :ULONG {
	shrd	eax, edx, cl
	sar	edx, cl
	}
Int64ShrlMod32 proto watcall :ULONGLONG, :ULONG {
	shrd	eax, edx, cl
	shr	edx, cl
	}
else
.err <Must define a target architecture.>
endif

ifdef _M_AMD64
RotateLeft8		equ <_rotl8>
RotateLeft16		equ <_rotl16>
RotateRight8		equ <_rotr8>
RotateRight16		equ <_rotr16>
endif

if _MSC_VER GE 1300
RotateLeft32		equ <_rotl>
RotateLeft64		equ <_rotl64>
RotateRight32		equ <_rotr>
RotateRight64		equ <_rotr64>
endif

ANSI_NULL	equ 0
UNICODE_NULL	equ 0
BOOLEAN		typedef BYTE
PBOOLEAN	typedef PTR BOOLEAN

UNICODE_STRING_MAX_BYTES equ 65534
UNICODE_STRING_MAX_CHARS equ 32767


LIST_ENTRY	STRUC
Flink		PVOID ?
Blink		PVOID ?
LIST_ENTRY	ENDS
PLIST_ENTRY	TYPEDEF PTR LIST_ENTRY
PRLIST_ENTRY	TYPEDEF PTR LIST_ENTRY


SINGLE_LIST_ENTRY STRUC
Next		PVOID ?
SINGLE_LIST_ENTRY ENDS
PSINGLE_LIST_ENTRY TYPEDEF PTR SINGLE_LIST_ENTRY


LIST_ENTRY32		STRUC
Flink			dd ?
Blink			dd ?
LIST_ENTRY32		ENDS
PLIST_ENTRY32		typedef ptr LIST_ENTRY32

LIST_ENTRY64		STRUC
Flink			ULONGLONG ?
Blink			ULONGLONG ?
LIST_ENTRY64		ENDS
PLIST_ENTRY64		typedef ptr LIST_ENTRY64


include guiddef.inc

ifndef __OBJECTID_DEFINED
define __OBJECTID_DEFINED
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


FIELD_OFFSET macro x, field
	exitm<x.field>
	endm

RTL_FIELD_SIZE macro x, field
	exitm<sizeof(x.field)>
	endm

RTL_SIZEOF_THROUGH_FIELD macro x, field
	exitm<FIELD_OFFSET(x, field) + RTL_FIELD_SIZE(x, field)>
	endm

RTL_CONTAINS_FIELD macro x, z, Field
	exitm<x.Field + sizeof(x.Field) LE x+z>
	endm

RTL_NUMBER_OF_V1 macro A
	exitm<lengthof(A)>
	endm

RTL_NUMBER_OF_V2 macro A
	exitm<RTL_NUMBER_OF_V1(A)>
	endm

ifdef ENABLE_RTL_NUMBER_OF_V2
RTL_NUMBER_OF macro A
	exitm<RTL_NUMBER_OF_V2(A)>
	endm
else
RTL_NUMBER_OF macro A
	exitm<RTL_NUMBER_OF_V1(A)>
	endm
endif

ARRAYSIZE macro A
	exitm<RTL_NUMBER_OF_V2(A)>
	endm
_ARRAYSIZE macro A
	exitm<RTL_NUMBER_OF_V1(A)>
	endm

RTL_FIELD_TYPE macro x, field
	exitm<x.field>
	endm

RTL_NUMBER_OF_FIELD macro x, field
	exitm<RTL_NUMBER_OF(RTL_FIED_TYPE(x, field))>
	endm

RTL_PADDING_BETWEEN_FIELDS macro T, F1, F2
	if FIELD_OFFSET(T, F2) GT FIELD_OFFSET(T, F1)
	    exitm<(FIELD_OFFSET(T, F2) - FIELD_OFFSET(T, F1) - RTL_FIELD_SIZE(T, F1))>
	else
	    exitm<(FIELD_OFFSET(T, F1) - FIELD_OFFSET(T, F2) - RTL_FIELD_SIZE(T, F2))>
	endif
	endm

RTL_BITS_OF macro sizeOfArg
	exitm<(sizeof(sizeOfArg) * 8)>
	endm

RTL_BITS_OF_FIELD macro x, field
	exitm<(RTL_BITS_OF(RTL_FIED_TYPE(x, field)))>
	endm


CONTAINING_RECORD proto fastcall :ptr, type:abs, field:abs {
	lea rax,[rcx-type.field]
	}

ifndef __EXCPT_INC
 include excpt.inc
endif

define EXCEPTION_MAXIMUM_PARAMETERS 15 ; maximum number of exception parameters


EXCEPTION_RECORD	STRUC SIZE_T
ExceptionCode		dd ?
ExceptionFlags		dd ?
ExceptionRecord		PVOID ? ; EXCEPTION_RECORD *
ExceptionAddress	PVOID ?
NumberParameters	dd ?
ExceptionInformation	PVOID EXCEPTION_MAXIMUM_PARAMETERS dup(?)
EXCEPTION_RECORD	ENDS
PEXCEPTION_RECORD	TYPEDEF PTR EXCEPTION_RECORD

CALLBACK(PEXCEPTION_ROUTINE, :PEXCEPTION_RECORD, :PVOID, :ptr CONTEXT, :PVOID)

VER_SERVER_NT		equ 0x80000000
VER_WORKSTATION_NT	equ 0x40000000
VER_SUITE_SMALLBUSINESS equ 0x00000001
VER_SUITE_ENTERPRISE	equ 0x00000002
VER_SUITE_BACKOFFICE	equ 0x00000004
VER_SUITE_COMMUNICATIONS equ 0x00000008
VER_SUITE_TERMINAL	equ 0x00000010
VER_SUITE_SMALLBUSINESS_RESTRICTED equ 0x00000020
VER_SUITE_EMBEDDEDNT	equ 0x00000040
VER_SUITE_DATACENTER	equ 0x00000080
VER_SUITE_SINGLEUSERTS	equ 0x00000100
VER_SUITE_PERSONAL	equ 0x00000200
VER_SUITE_BLADE		equ 0x00000400
VER_SUITE_EMBEDDED_RESTRICTED equ 0x00000800
VER_SUITE_SECURITY_APPLIANCE equ 0x00001000
VER_SUITE_STORAGE_SERVER equ 0x00002000
VER_SUITE_COMPUTE_SERVER equ 0x00004000
VER_SUITE_WH_SERVER	equ 0x00008000


PRODUCT_UNDEFINED	equ 0x00000000

PRODUCT_ULTIMATE	equ 0x00000001
PRODUCT_HOME_BASIC	equ 0x00000002
PRODUCT_HOME_PREMIUM	equ 0x00000003
PRODUCT_ENTERPRISE	equ 0x00000004
PRODUCT_HOME_BASIC_N	equ 0x00000005
PRODUCT_BUSINESS	equ 0x00000006
PRODUCT_STANDARD_SERVER equ 0x00000007
PRODUCT_DATACENTER_SERVER equ 0x00000008
PRODUCT_SMALLBUSINESS_SERVER equ 0x00000009
PRODUCT_ENTERPRISE_SERVER equ 0x0000000A
PRODUCT_STARTER		equ 0x0000000B
PRODUCT_DATACENTER_SERVER_CORE equ 0x0000000C
PRODUCT_STANDARD_SERVER_CORE equ 0x0000000D
PRODUCT_ENTERPRISE_SERVER_CORE equ 0x0000000E
PRODUCT_ENTERPRISE_SERVER_IA64 equ 0x0000000F
PRODUCT_BUSINESS_N	equ 0x00000010
PRODUCT_WEB_SERVER	equ 0x00000011
PRODUCT_CLUSTER_SERVER	equ 0x00000012
PRODUCT_HOME_SERVER	equ 0x00000013
PRODUCT_STORAGE_EXPRESS_SERVER equ 0x00000014
PRODUCT_STORAGE_STANDARD_SERVER equ 0x00000015
PRODUCT_STORAGE_WORKGROUP_SERVER equ 0x00000016
PRODUCT_STORAGE_ENTERPRISE_SERVER equ 0x00000017
PRODUCT_SERVER_FOR_SMALLBUSINESS equ 0x00000018
PRODUCT_SMALLBUSINESS_SERVER_PREMIUM equ 0x00000019
PRODUCT_HOME_PREMIUM_N	equ 0x0000001A
PRODUCT_ENTERPRISE_N	equ 0x0000001B
PRODUCT_ULTIMATE_N	equ 0x0000001C
PRODUCT_WEB_SERVER_CORE equ 0x0000001D
PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT equ 0x0000001E
PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY equ 0x0000001F
PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING equ 0x00000020
PRODUCT_SERVER_FOUNDATION equ 0x00000021
PRODUCT_HOME_PREMIUM_SERVER equ 0x00000022
PRODUCT_SERVER_FOR_SMALLBUSINESS_V equ 0x00000023
PRODUCT_STANDARD_SERVER_V equ 0x00000024
PRODUCT_DATACENTER_SERVER_V equ 0x00000025
PRODUCT_ENTERPRISE_SERVER_V equ 0x00000026
PRODUCT_DATACENTER_SERVER_CORE_V equ 0x00000027
PRODUCT_STANDARD_SERVER_CORE_V equ 0x00000028
PRODUCT_ENTERPRISE_SERVER_CORE_V equ 0x00000029
PRODUCT_HYPERV		equ 0x0000002A
PRODUCT_STORAGE_EXPRESS_SERVER_CORE equ 0x0000002B
PRODUCT_STORAGE_STANDARD_SERVER_CORE equ 0x0000002C
PRODUCT_STORAGE_WORKGROUP_SERVER_CORE equ 0x0000002D
PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE equ 0x0000002E
PRODUCT_STARTER_N	equ 0x0000002F
PRODUCT_PROFESSIONAL	equ 0x00000030
PRODUCT_PROFESSIONAL_N	equ 0x00000031
PRODUCT_SB_SOLUTION_SERVER equ 0x00000032
PRODUCT_SERVER_FOR_SB_SOLUTIONS equ 0x00000033
PRODUCT_STANDARD_SERVER_SOLUTIONS equ 0x00000034
PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE equ 0x00000035
PRODUCT_SB_SOLUTION_SERVER_EM equ 0x00000036
PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM equ 0x00000037
PRODUCT_SOLUTION_EMBEDDEDSERVER equ 0x00000038
PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE equ 0x00000039
PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE equ 0x0000003F
PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT equ 0x0000003B
PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL equ 0x0000003C
PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC equ 0x0000003D
PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC equ 0x0000003E
PRODUCT_CLUSTER_SERVER_V equ 0x00000040
PRODUCT_EMBEDDED	equ 0x00000041
PRODUCT_STARTER_E	equ 0x00000042
PRODUCT_HOME_BASIC_E	equ 0x00000043
PRODUCT_HOME_PREMIUM_E	equ 0x00000044
PRODUCT_PROFESSIONAL_E	equ 0x00000045
PRODUCT_ENTERPRISE_E	equ 0x00000046
PRODUCT_ULTIMATE_E	equ 0x00000047

PRODUCT_UNLICENSED	equ 0xABCDABCD

LANG_NEUTRAL		equ 0x00
LANG_INVARIANT		equ 0x7f

LANG_AFRIKAANS		equ 0x36
LANG_ALBANIAN		equ 0x1c
LANG_ALSATIAN		equ 0x84
LANG_AMHARIC		equ 0x5e
LANG_ARABIC		equ 0x01
LANG_ARMENIAN		equ 0x2b
LANG_ASSAMESE		equ 0x4d
LANG_AZERI		equ 0x2c
LANG_BASHKIR		equ 0x6d
LANG_BASQUE		equ 0x2d
LANG_BELARUSIAN		equ 0x23
LANG_BENGALI		equ 0x45
LANG_BRETON		equ 0x7e
LANG_BOSNIAN		equ 0x1a
LANG_BOSNIAN_NEUTRAL	equ 0x781a
LANG_BULGARIAN		equ 0x02
LANG_CATALAN		equ 0x03
LANG_CHINESE		equ 0x04
LANG_CHINESE_SIMPLIFIED equ 0x04
LANG_CHINESE_TRADITIONAL equ 0x7c04
LANG_CORSICAN		equ 0x83
LANG_CROATIAN		equ 0x1a
LANG_CZECH		equ 0x05
LANG_DANISH		equ 0x06
LANG_DARI		equ 0x8c
LANG_DIVEHI		equ 0x65
LANG_DUTCH		equ 0x13
LANG_ENGLISH		equ 0x09
LANG_ESTONIAN		equ 0x25
LANG_FAEROESE		equ 0x38
LANG_FARSI		equ 0x29
LANG_FILIPINO		equ 0x64
LANG_FINNISH		equ 0x0b
LANG_FRENCH		equ 0x0c
LANG_FRISIAN		equ 0x62
LANG_GALICIAN		equ 0x56
LANG_GEORGIAN		equ 0x37
LANG_GERMAN		equ 0x07
LANG_GREEK		equ 0x08
LANG_GREENLANDIC	equ 0x6f
LANG_GUJARATI		equ 0x47
LANG_HAUSA		equ 0x68
LANG_HEBREW		equ 0x0d
LANG_HINDI		equ 0x39
LANG_HUNGARIAN		equ 0x0e
LANG_ICELANDIC		equ 0x0f
LANG_IGBO		equ 0x70
LANG_INDONESIAN		equ 0x21
LANG_INUKTITUT		equ 0x5d
LANG_IRISH		equ 0x3c
LANG_ITALIAN		equ 0x10
LANG_JAPANESE		equ 0x11
LANG_KANNADA		equ 0x4b
LANG_KASHMIRI		equ 0x60
LANG_KAZAK		equ 0x3f
LANG_KHMER		equ 0x53
LANG_KICHE		equ 0x86
LANG_KINYARWANDA	equ 0x87
LANG_KONKANI		equ 0x57
LANG_KOREAN		equ 0x12
LANG_KYRGYZ		equ 0x40
LANG_LAO		equ 0x54
LANG_LATVIAN		equ 0x26
LANG_LITHUANIAN		equ 0x27
LANG_LOWER_SORBIAN	equ 0x2e
LANG_LUXEMBOURGISH	equ 0x6e
LANG_MACEDONIAN		equ 0x2f
LANG_MALAY		equ 0x3e
LANG_MALAYALAM		equ 0x4c
LANG_MALTESE		equ 0x3a
LANG_MANIPURI		equ 0x58
LANG_MAORI		equ 0x81
LANG_MAPUDUNGUN		equ 0x7a
LANG_MARATHI		equ 0x4e
LANG_MOHAWK		equ 0x7c
LANG_MONGOLIAN		equ 0x50
LANG_NEPALI		equ 0x61
LANG_NORWEGIAN		equ 0x14
LANG_OCCITAN		equ 0x82
LANG_ORIYA		equ 0x48
LANG_PASHTO		equ 0x63
LANG_PERSIAN		equ 0x29
LANG_POLISH		equ 0x15
LANG_PORTUGUESE		equ 0x16
LANG_PUNJABI		equ 0x46
LANG_QUECHUA		equ 0x6b
LANG_ROMANIAN		equ 0x18
LANG_ROMANSH		equ 0x17
LANG_RUSSIAN		equ 0x19
LANG_SAMI		equ 0x3b
LANG_SANSKRIT		equ 0x4f
LANG_SCOTTISH_GAELIC	equ 0x91
LANG_SERBIAN		equ 0x1a
LANG_SERBIAN_NEUTRAL	equ 0x7c1a
LANG_SINDHI		equ 0x59
LANG_SINHALESE		equ 0x5b
LANG_SLOVAK		equ 0x1b
LANG_SLOVENIAN		equ 0x24
LANG_SOTHO		equ 0x6c
LANG_SPANISH		equ 0x0a
LANG_SWAHILI		equ 0x41
LANG_SWEDISH		equ 0x1d
LANG_SYRIAC		equ 0x5a
LANG_TAJIK		equ 0x28
LANG_TAMAZIGHT		equ 0x5f
LANG_TAMIL		equ 0x49
LANG_TATAR		equ 0x44
LANG_TELUGU		equ 0x4a
LANG_THAI		equ 0x1e
LANG_TIBETAN		equ 0x51
LANG_TIGRIGNA		equ 0x73
LANG_TSWANA		equ 0x32
LANG_TURKISH		equ 0x1f
LANG_TURKMEN		equ 0x42
LANG_UIGHUR		equ 0x80
LANG_UKRAINIAN		equ 0x22
LANG_UPPER_SORBIAN	equ 0x2e
LANG_URDU		equ 0x20
LANG_UZBEK		equ 0x43
LANG_VIETNAMESE		equ 0x2a
LANG_WELSH		equ 0x52
LANG_WOLOF		equ 0x88
LANG_XHOSA		equ 0x34
LANG_YAKUT		equ 0x85
LANG_YI			equ 0x78
LANG_YORUBA		equ 0x6a
LANG_ZULU		equ 0x35


SUBLANG_NEUTRAL		equ 0x00
SUBLANG_DEFAULT		equ 0x01
SUBLANG_SYS_DEFAULT	equ 0x02
SUBLANG_CUSTOM_DEFAULT	equ 0x03
SUBLANG_CUSTOM_UNSPECIFIED equ 0x04
SUBLANG_UI_CUSTOM_DEFAULT equ 0x05


SUBLANG_AFRIKAANS_SOUTH_AFRICA equ 0x01
SUBLANG_ALBANIAN_ALBANIA equ 0x01
SUBLANG_ALSATIAN_FRANCE equ 0x01
SUBLANG_AMHARIC_ETHIOPIA equ 0x01
SUBLANG_ARABIC_SAUDI_ARABIA equ 0x01
SUBLANG_ARABIC_IRAQ	equ 0x02
SUBLANG_ARABIC_EGYPT	equ 0x03
SUBLANG_ARABIC_LIBYA	equ 0x04
SUBLANG_ARABIC_ALGERIA	equ 0x05
SUBLANG_ARABIC_MOROCCO	equ 0x06
SUBLANG_ARABIC_TUNISIA	equ 0x07
SUBLANG_ARABIC_OMAN	equ 0x08
SUBLANG_ARABIC_YEMEN	equ 0x09
SUBLANG_ARABIC_SYRIA	equ 0x0a
SUBLANG_ARABIC_JORDAN	equ 0x0b
SUBLANG_ARABIC_LEBANON	equ 0x0c
SUBLANG_ARABIC_KUWAIT	equ 0x0d
SUBLANG_ARABIC_UAE	equ 0x0e
SUBLANG_ARABIC_BAHRAIN	equ 0x0f
SUBLANG_ARABIC_QATAR	equ 0x10
SUBLANG_ARMENIAN_ARMENIA equ 0x01
SUBLANG_ASSAMESE_INDIA	equ 0x01
SUBLANG_AZERI_LATIN	equ 0x01
SUBLANG_AZERI_CYRILLIC	equ 0x02
SUBLANG_BASHKIR_RUSSIA	equ 0x01
SUBLANG_BASQUE_BASQUE	equ 0x01
SUBLANG_BELARUSIAN_BELARUS equ 0x01
SUBLANG_BENGALI_INDIA	equ 0x01
SUBLANG_BENGALI_BANGLADESH equ 0x02
SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN equ 0x05
SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_CYRILLIC equ 0x08
SUBLANG_BRETON_FRANCE	equ 0x01
SUBLANG_BULGARIAN_BULGARIA equ 0x01
SUBLANG_CATALAN_CATALAN equ 0x01
SUBLANG_CHINESE_TRADITIONAL equ 0x01
SUBLANG_CHINESE_SIMPLIFIED equ 0x02
SUBLANG_CHINESE_HONGKONG equ 0x03
SUBLANG_CHINESE_SINGAPORE equ 0x04
SUBLANG_CHINESE_MACAU	equ 0x05
SUBLANG_CORSICAN_FRANCE equ 0x01
SUBLANG_CZECH_CZECH_REPUBLIC equ 0x01
SUBLANG_CROATIAN_CROATIA equ 0x01
SUBLANG_CROATIAN_BOSNIA_HERZEGOVINA_LATIN equ 0x04
SUBLANG_DANISH_DENMARK	equ 0x01
SUBLANG_DARI_AFGHANISTAN equ 0x01
SUBLANG_DIVEHI_MALDIVES equ 0x01
SUBLANG_DUTCH		equ 0x01
SUBLANG_DUTCH_BELGIAN	equ 0x02
SUBLANG_ENGLISH_US	equ 0x01
SUBLANG_ENGLISH_UK	equ 0x02
SUBLANG_ENGLISH_AUS	equ 0x03
SUBLANG_ENGLISH_CAN	equ 0x04
SUBLANG_ENGLISH_NZ	equ 0x05
SUBLANG_ENGLISH_EIRE	equ 0x06
SUBLANG_ENGLISH_SOUTH_AFRICA equ 0x07
SUBLANG_ENGLISH_JAMAICA equ 0x08
SUBLANG_ENGLISH_CARIBBEAN equ 0x09
SUBLANG_ENGLISH_BELIZE	equ 0x0a
SUBLANG_ENGLISH_TRINIDAD equ 0x0b
SUBLANG_ENGLISH_ZIMBABWE equ 0x0c
SUBLANG_ENGLISH_PHILIPPINES equ 0x0d
SUBLANG_ENGLISH_INDIA	equ 0x10
SUBLANG_ENGLISH_MALAYSIA equ 0x11
SUBLANG_ENGLISH_SINGAPORE equ 0x12
SUBLANG_ESTONIAN_ESTONIA equ 0x01
SUBLANG_FAEROESE_FAROE_ISLANDS equ 0x01
SUBLANG_FILIPINO_PHILIPPINES equ 0x01
SUBLANG_FINNISH_FINLAND equ 0x01
SUBLANG_FRENCH		equ 0x01
SUBLANG_FRENCH_BELGIAN	equ 0x02
SUBLANG_FRENCH_CANADIAN equ 0x03
SUBLANG_FRENCH_SWISS	equ 0x04
SUBLANG_FRENCH_LUXEMBOURG equ 0x05
SUBLANG_FRENCH_MONACO	equ 0x06
SUBLANG_FRISIAN_NETHERLANDS equ 0x01
SUBLANG_GALICIAN_GALICIAN equ 0x01
SUBLANG_GEORGIAN_GEORGIA equ 0x01
SUBLANG_GERMAN		equ 0x01
SUBLANG_GERMAN_SWISS	equ 0x02
SUBLANG_GERMAN_AUSTRIAN equ 0x03
SUBLANG_GERMAN_LUXEMBOURG equ 0x04
SUBLANG_GERMAN_LIECHTENSTEIN equ 0x05
SUBLANG_GREEK_GREECE	equ 0x01
SUBLANG_GREENLANDIC_GREENLAND equ 0x01
SUBLANG_GUJARATI_INDIA	equ 0x01
SUBLANG_HAUSA_NIGERIA_LATIN equ 0x01
SUBLANG_HEBREW_ISRAEL	equ 0x01
SUBLANG_HINDI_INDIA	equ 0x01
SUBLANG_HUNGARIAN_HUNGARY equ 0x01
SUBLANG_ICELANDIC_ICELAND equ 0x01
SUBLANG_IGBO_NIGERIA	equ 0x01
SUBLANG_INDONESIAN_INDONESIA equ 0x01
SUBLANG_INUKTITUT_CANADA equ 0x01
SUBLANG_INUKTITUT_CANADA_LATIN equ 0x02
SUBLANG_IRISH_IRELAND	equ 0x02
SUBLANG_ITALIAN		equ 0x01
SUBLANG_ITALIAN_SWISS	equ 0x02
SUBLANG_JAPANESE_JAPAN	equ 0x01
SUBLANG_KANNADA_INDIA	equ 0x01
SUBLANG_KASHMIRI_SASIA	equ 0x02
SUBLANG_KASHMIRI_INDIA	equ 0x02
SUBLANG_KAZAK_KAZAKHSTAN equ 0x01
SUBLANG_KHMER_CAMBODIA	equ 0x01
SUBLANG_KICHE_GUATEMALA equ 0x01
SUBLANG_KINYARWANDA_RWANDA equ 0x01
SUBLANG_KONKANI_INDIA	equ 0x01
SUBLANG_KOREAN		equ 0x01
SUBLANG_KYRGYZ_KYRGYZSTAN equ 0x01
SUBLANG_LAO_LAO		equ 0x01
SUBLANG_LATVIAN_LATVIA	equ 0x01
SUBLANG_LITHUANIAN	equ 0x01
SUBLANG_LOWER_SORBIAN_GERMANY equ 0x02
SUBLANG_LUXEMBOURGISH_LUXEMBOURG equ 0x01
SUBLANG_MACEDONIAN_MACEDONIA equ 0x01
SUBLANG_MALAY_MALAYSIA	equ 0x01
SUBLANG_MALAY_BRUNEI_DARUSSALAM equ 0x02
SUBLANG_MALAYALAM_INDIA equ 0x01
SUBLANG_MALTESE_MALTA	equ 0x01
SUBLANG_MAORI_NEW_ZEALAND equ 0x01
SUBLANG_MAPUDUNGUN_CHILE equ 0x01
SUBLANG_MARATHI_INDIA	equ 0x01
SUBLANG_MOHAWK_MOHAWK	equ 0x01
SUBLANG_MONGOLIAN_CYRILLIC_MONGOLIA equ 0x01
SUBLANG_MONGOLIAN_PRC	equ 0x02
SUBLANG_NEPALI_INDIA	equ 0x02
SUBLANG_NEPALI_NEPAL	equ 0x01
SUBLANG_NORWEGIAN_BOKMAL equ 0x01
SUBLANG_NORWEGIAN_NYNORSK equ 0x02
SUBLANG_OCCITAN_FRANCE	equ 0x01
SUBLANG_ORIYA_INDIA	equ 0x01
SUBLANG_PASHTO_AFGHANISTAN equ 0x01
SUBLANG_PERSIAN_IRAN	equ 0x01
SUBLANG_POLISH_POLAND	equ 0x01
SUBLANG_PORTUGUESE	equ 0x02
SUBLANG_PORTUGUESE_BRAZILIAN equ 0x01
SUBLANG_PUNJABI_INDIA	equ 0x01
SUBLANG_QUECHUA_BOLIVIA equ 0x01
SUBLANG_QUECHUA_ECUADOR equ 0x02
SUBLANG_QUECHUA_PERU	equ 0x03
SUBLANG_ROMANIAN_ROMANIA equ 0x01
SUBLANG_ROMANSH_SWITZERLAND equ 0x01
SUBLANG_RUSSIAN_RUSSIA	equ 0x01
SUBLANG_SAMI_NORTHERN_NORWAY equ 0x01
SUBLANG_SAMI_NORTHERN_SWEDEN equ 0x02
SUBLANG_SAMI_NORTHERN_FINLAND equ 0x03
SUBLANG_SAMI_LULE_NORWAY equ 0x04
SUBLANG_SAMI_LULE_SWEDEN equ 0x05
SUBLANG_SAMI_SOUTHERN_NORWAY equ 0x06
SUBLANG_SAMI_SOUTHERN_SWEDEN equ 0x07
SUBLANG_SAMI_SKOLT_FINLAND equ 0x08
SUBLANG_SAMI_INARI_FINLAND equ 0x09
SUBLANG_SANSKRIT_INDIA	equ 0x01
SUBLANG_SCOTTISH_GAELIC equ 0x01
SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_LATIN equ 0x06
SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_CYRILLIC equ 0x07
SUBLANG_SERBIAN_MONTENEGRO_LATIN equ 0x0b
SUBLANG_SERBIAN_MONTENEGRO_CYRILLIC equ 0x0c
SUBLANG_SERBIAN_SERBIA_LATIN equ 0x09
SUBLANG_SERBIAN_SERBIA_CYRILLIC equ 0x0a
SUBLANG_SERBIAN_CROATIA equ 0x01
SUBLANG_SERBIAN_LATIN	equ 0x02
SUBLANG_SERBIAN_CYRILLIC equ 0x03
SUBLANG_SINDHI_INDIA	equ 0x01
SUBLANG_SINDHI_PAKISTAN equ 0x02
SUBLANG_SINDHI_AFGHANISTAN equ 0x02
SUBLANG_SINHALESE_SRI_LANKA equ 0x01
SUBLANG_SOTHO_NORTHERN_SOUTH_AFRICA equ 0x01
SUBLANG_SLOVAK_SLOVAKIA equ 0x01
SUBLANG_SLOVENIAN_SLOVENIA equ 0x01
SUBLANG_SPANISH		equ 0x01
SUBLANG_SPANISH_MEXICAN equ 0x02
SUBLANG_SPANISH_MODERN	equ 0x03
SUBLANG_SPANISH_GUATEMALA equ 0x04
SUBLANG_SPANISH_COSTA_RICA equ 0x05
SUBLANG_SPANISH_PANAMA	equ 0x06
SUBLANG_SPANISH_DOMINICAN_REPUBLIC equ 0x07
SUBLANG_SPANISH_VENEZUELA equ 0x08
SUBLANG_SPANISH_COLOMBIA equ 0x09
SUBLANG_SPANISH_PERU	equ 0x0a
SUBLANG_SPANISH_ARGENTINA equ 0x0b
SUBLANG_SPANISH_ECUADOR equ 0x0c
SUBLANG_SPANISH_CHILE	equ 0x0d
SUBLANG_SPANISH_URUGUAY equ 0x0e
SUBLANG_SPANISH_PARAGUAY equ 0x0f
SUBLANG_SPANISH_BOLIVIA equ 0x10
SUBLANG_SPANISH_EL_SALVADOR equ 0x11
SUBLANG_SPANISH_HONDURAS equ 0x12
SUBLANG_SPANISH_NICARAGUA equ 0x13
SUBLANG_SPANISH_PUERTO_RICO equ 0x14
SUBLANG_SPANISH_US	equ 0x15
SUBLANG_SWAHILI_KENYA	equ 0x01
SUBLANG_SWEDISH		equ 0x01
SUBLANG_SWEDISH_FINLAND equ 0x02
SUBLANG_SYRIAC_SYRIA	equ 0x01
SUBLANG_TAJIK_TAJIKISTAN equ 0x01
SUBLANG_TAMAZIGHT_ALGERIA_LATIN equ 0x02
SUBLANG_TAMIL_INDIA	equ 0x01
SUBLANG_TATAR_RUSSIA	equ 0x01
SUBLANG_TELUGU_INDIA	equ 0x01
SUBLANG_THAI_THAILAND	equ 0x01
SUBLANG_TIBETAN_PRC	equ 0x01
SUBLANG_TIGRIGNA_ERITREA equ 0x02
SUBLANG_TSWANA_SOUTH_AFRICA equ 0x01
SUBLANG_TURKISH_TURKEY	equ 0x01
SUBLANG_TURKMEN_TURKMENISTAN equ 0x01
SUBLANG_UIGHUR_PRC	equ 0x01
SUBLANG_UKRAINIAN_UKRAINE equ 0x01
SUBLANG_UPPER_SORBIAN_GERMANY equ 0x01
SUBLANG_URDU_PAKISTAN	equ 0x01
SUBLANG_URDU_INDIA	equ 0x02
SUBLANG_UZBEK_LATIN	equ 0x01
SUBLANG_UZBEK_CYRILLIC	equ 0x02
SUBLANG_VIETNAMESE_VIETNAM equ 0x01
SUBLANG_WELSH_UNITED_KINGDOM equ 0x01
SUBLANG_WOLOF_SENEGAL	equ 0x01
SUBLANG_XHOSA_SOUTH_AFRICA equ 0x01
SUBLANG_YAKUT_RUSSIA	equ 0x01
SUBLANG_YI_PRC		equ 0x01
SUBLANG_YORUBA_NIGERIA	equ 0x01
SUBLANG_ZULU_SOUTH_AFRICA equ 0x01


SORT_DEFAULT		equ 0x0

SORT_INVARIANT_MATH	equ 0x1

SORT_JAPANESE_XJIS	equ 0x0
SORT_JAPANESE_UNICODE	equ 0x1
SORT_JAPANESE_RADICALSTROKE equ 0x4

SORT_CHINESE_BIG5	equ 0x0
SORT_CHINESE_PRCP	equ 0x0
SORT_CHINESE_UNICODE	equ 0x1
SORT_CHINESE_PRC	equ 0x2
SORT_CHINESE_BOPOMOFO	equ 0x3
SORT_CHINESE_RADICALSTROKE equ 0x4

SORT_KOREAN_KSC		equ 0x0
SORT_KOREAN_UNICODE	equ 0x1

SORT_GERMAN_PHONE_BOOK	equ 0x1

SORT_HUNGARIAN_DEFAULT	equ 0x0
SORT_HUNGARIAN_TECHNICAL equ 0x1

SORT_GEORGIAN_TRADITIONAL equ 0x0
SORT_GEORGIAN_MODERN	equ 0x1


MAKELANGID MACRO usPrimaryLanguage, usSubLanguage
	EXITM<((usSubLanguage SHL 10) OR usPrimaryLanguage)>
	ENDM

PRIMARYLANGID MACRO lgid
	EXITM<lgid & 0x3ff>
	ENDM

SUBLANGID MACRO lgid
	EXITM<lgid shr 10>
	ENDM


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


LOCALE_NAME_MAX_LENGTH	equ 85


LANG_SYSTEM_DEFAULT	equ MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT)
LANG_USER_DEFAULT	equ MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)

LOCALE_SYSTEM_DEFAULT	equ MAKELCID(LANG_SYSTEM_DEFAULT, SORT_DEFAULT)
LOCALE_USER_DEFAULT	equ MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT)
LOCALE_CUSTOM_DEFAULT	equ MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_CUSTOM_DEFAULT), SORT_DEFAULT)
LOCALE_CUSTOM_UNSPECIFIED equ MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_CUSTOM_UNSPECIFIED), SORT_DEFAULT)
LOCALE_CUSTOM_UI_DEFAULT equ MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_UI_CUSTOM_DEFAULT), SORT_DEFAULT)
LOCALE_NEUTRAL		equ MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SORT_DEFAULT)
LOCALE_INVARIANT	equ MAKELCID(MAKELANGID(LANG_INVARIANT, SUBLANG_NEUTRAL), SORT_DEFAULT)



ifndef UNREFERENCED_PARAMETER
ifdef __DEBUG__
UNREFERENCED_PARAMETER macro P
	exitm<lea rax,P>
	endm
DBG_UNREFERENCED_PARAMETER macro P
	exitm<lea rax,P>
	endm
DBG_UNREFERENCED_LOCAL_VARIABLE macro V
	exitm<lea rax,P>
	endm
else
UNREFERENCED_PARAMETER macro P
	exitm<>
	endm
DBG_UNREFERENCED_PARAMETER macro P
	exitm<>
	endm
DBG_UNREFERENCED_LOCAL_VARIABLE macro V
	exitm<>
	endm
endif
endif

COMPILETIME_OR_2FLAGS macro a,b
	exitm<((a) OR (b))>
	endm
COMPILETIME_OR_3FLAGS macro a,b,q
	exitm<((a) OR (b) OR (q))>
	endm
COMPILETIME_OR_4FLAGS macro a,b,q,d
	exitm<((a) OR (b) OR (q) OR (d))>
	endm
COMPILETIME_OR_5FLAGS macro a,b,q,d,e
	exitm<((a) OR (b) OR (q) OR (d) OR (e))>
	endm

ifndef WIN32_NO_STATUS

STATUS_WAIT_0			equ 0x00000000
STATUS_ABANDONED_WAIT_0		equ 0x00000080
STATUS_USER_APC			equ 0x000000C0
STATUS_TIMEOUT			equ 0x00000102
STATUS_PENDING			equ 0x00000103
STATUS_SEGMENT_NOTIFICATION	equ 0x40000005
STATUS_GUARD_PAGE_VIOLATION	equ 0x80000001
STATUS_DATATYPE_MISALIGNMENT	equ 0x80000002
STATUS_BREAKPOINT		equ 0x80000003
STATUS_SINGLE_STEP		equ 0x80000004
STATUS_LONGJUMP			equ 0x80000026
STATUS_UNWIND_CONSOLIDATE	equ 0x80000029
STATUS_ACCESS_VIOLATION		equ 0xC0000005
STATUS_IN_PAGE_ERROR		equ 0xC0000006
STATUS_INVALID_HANDLE		equ 0xC0000008
STATUS_INVALID_PARAMETER	equ 0xC000000D
STATUS_NO_MEMORY		equ 0xC0000017
STATUS_ILLEGAL_INSTRUCTION	equ 0xC000001D
STATUS_NONCONTINUABLE_EXCEPTION equ 0xC0000025
STATUS_INVALID_DISPOSITION	equ 0xC0000026
STATUS_ARRAY_BOUNDS_EXCEEDED	equ 0xC000008C
STATUS_FLOAT_DENORMAL_OPERAND	equ 0xC000008D
STATUS_FLOAT_DIVIDE_BY_ZERO	equ 0xC000008E
STATUS_FLOAT_INEXACT_RESULT	equ 0xC000008F
STATUS_FLOAT_INVALID_OPERATION	equ 0xC0000090
STATUS_FLOAT_OVERFLOW		equ 0xC0000091
STATUS_FLOAT_STACK_CHECK	equ 0xC0000092
STATUS_FLOAT_UNDERFLOW		equ 0xC0000093
STATUS_INTEGER_DIVIDE_BY_ZERO	equ 0xC0000094
STATUS_INTEGER_OVERFLOW		equ 0xC0000095
STATUS_PRIVILEGED_INSTRUCTION	equ 0xC0000096
STATUS_STACK_OVERFLOW		equ 0xC00000FD
STATUS_DLL_NOT_FOUND		equ 0xC0000135
STATUS_ORDINAL_NOT_FOUND	equ 0xC0000138
STATUS_ENTRYPOINT_NOT_FOUND	equ 0xC0000139
STATUS_CONTROL_C_EXIT		equ 0xC000013A
STATUS_DLL_INIT_FAILED		equ 0xC0000142
STATUS_FLOAT_MULTIPLE_FAULTS	equ 0xC00002B4
STATUS_FLOAT_MULTIPLE_TRAPS	equ 0xC00002B5
STATUS_ILLEGAL_VLM_REFERENCE	equ 0xC00002C0
STATUS_REG_NAT_CONSUMPTION	equ 0xC00002C9
STATUS_STACK_BUFFER_OVERRUN	equ 0xC0000409
STATUS_INVALID_CRUNTIME_PARAMETER equ 0xC0000417
STATUS_ASSERTION_FAILURE	equ 0xC0000420

if defined(STATUS_SUCCESS) OR (_WIN32_WINNT GT 0x0500) OR (_WIN32_FUSION GE 0x0100)
STATUS_SXS_EARLY_DEACTIVATION	equ 0xC015000F
STATUS_SXS_INVALID_DEACTIVATION equ 0xC0150010
endif
endif

MAXIMUM_WAIT_OBJECTS	equ 64		; Maximum number of wait objects
MAXIMUM_SUSPEND_COUNT	equ MAXCHAR	; Maximum times thread can be suspended

KSPIN_LOCK	typedef UINT_PTR
PKSPIN_LOCK	typedef PTR KSPIN_LOCK

M128A		STRUC DECLSPEC_ALIGN(16)
_Low		ULONGLONG ?
_High		LONGLONG ?
M128A		ENDS
PM128A		typedef ptr M128A

XSAVE_FORMAT		STRUC DECLSPEC_ALIGN(16)
ControlWord		dw ?
StatusWord		dw ?
TagWord			db ?
Reserved1		db ?
ErrorOpcode		dw ?
ErrorOffset		dd ?
ErrorSelector		dw ?
Reserved2		dw ?
DataOffset		dd ?
DataSelector		dw ?
Reserved3		dw ?
MxCsr			dd ?
MxCsr_Mask		dd ?
FloatRegisters		M128A 8 dup(<>)
ifdef _WIN64
XmmRegisters		M128A 16 dup(<>)
Reserved4		db 96 dup(?)
else
XmmRegisters		M128A 8 dup(<>)
Reserved4		db 192 dup(?)
StackControl		dd 7 dup(?)
Cr0NpxState		dd ?
endif
XSAVE_FORMAT		ENDS
PXSAVE_FORMAT		typedef ptr XSAVE_FORMAT

XSAVE_AREA_HEADER	STRUC DECLSPEC_ALIGN(8)
Mask			dq ?
Reserved		dq 7 dup(?)
XSAVE_AREA_HEADER	ENDS
PXSAVE_AREA_HEADER	typedef ptr XSAVE_AREA_HEADER

XSAVE_AREA		STRUC DECLSPEC_ALIGN(16)
LegacyState		XSAVE_FORMAT <>
Header			XSAVE_AREA_HEADER <>
XSAVE_AREA		ENDS
PXSAVE_AREA		typedef ptr XSAVE_AREA

XSTATE_CONTEXT		STRUC
Mask			dd ?
Length			dd ?
Reserved1		dd ?
Area			PXSAVE_AREA ? ; __field_bcount_opt(Length) ?
ifdef _X86_
Reserved2		dd ?
endif
Buffer			PVOID ?
ifdef _X86_
Reserved3		dd ?
endif
XSTATE_CONTEXT		ENDS
PXSTATE_CONTEXT		typedef ptr XSTATE_CONTEXT

SCOPE_TABLE_AMD64	STRUC
Count			dd ?
STRUC ScopeRecord
 BeginAddress		dd ?
 EndAddress		dd ?
 HandlerAddress		dd ?
 JumpTarget		dd ?
ENDS
SCOPE_TABLE_AMD64	ENDS
PSCOPE_TABLE_AMD64	typedef ptr SCOPE_TABLE_AMD64


XSAVE_ALIGN		equ 64
MINIMAL_XSTATE_AREA_LENGTH equ XSAVE_AREA


CONTEXT_CHUNK		STRUC
_Offset			LONG ?
Length			dd ?
CONTEXT_CHUNK		ENDS
PCONTEXT_CHUNK		typedef ptr CONTEXT_CHUNK


CONTEXT_EX		STRUC
All			CONTEXT_CHUNK <>
Legacy			CONTEXT_CHUNK <>
XState			CONTEXT_CHUNK <>
CONTEXT_EX		ENDS
PCONTEXT_EX		typedef ptr CONTEXT_EX

CONTEXT_EX_LENGTH	equ ALIGN_UP_BY(CONTEXT_EX, STACK_AIGN)


RTL_CONTEXT_EX_OFFSET macro ContextEx, Chunk
	endm

RTL_CONTEXT_EX_LENGTH macro ContextEx, Chunk
	endm

RTL_CONTEXT_EX_CHUNK macro Base, Layout, Chunk
	endm

RTL_CONTEXT_OFFSET macro Context, Chunk
	endm

RTL_CONTEXT_LENGTH macro Context, Chunk
	endm

RTL_CONTEXT_CHUNK macro Context, Chunk
	endm

if NOT defined(__midl) AND NOT defined(MIDL_PASS)

C_ASSERT macro exp
    if (exp)
	exitm<>
    else
	.err<exp>
    endif
    endm


C_ASSERT((XSAVE_FORMAT and (XSAVE_ALIGN - 1)) eq 0)
C_ASSERT((FIELD_OFFSET(XSAVE_AREA, Header) and (XSAVE_ALIGN - 1)) eq 0)

C_ASSERT(MINIMAL_XSTATE_AREA_LENGTH eq 512 + 64)

endif

ifdef _AMD64_

if defined(_M_AMD64) AND NOT defined(RC_INVOKED) AND NOT defined(MIDL_PASS)

if 0
BitTest			equ <_bittest>
BitTestAndComplement	equ <_bittestandcomplement>
BitTestAndSet		equ <_bittestandset>
BitTestAndReset		equ <_bittestandreset>
InterlockedBitTestAndSet equ <_interlockedbittestandset>
InterlockedBitTestAndReset equ <_interlockedbittestandreset>

BitTest64		equ <_bittest64>
BitTestAndComplement64	equ <_bittestandcomplement64>
BitTestAndSet64		equ <_bittestandset64>
BitTestAndReset64	equ <_bittestandreset64>
InterlockedBitTestAndSet64 equ <_interlockedbittestandset64>
InterlockedBitTestAndReset64 equ <_interlockedbittestandreset64>

BitScanForward		equ <_BitScanForward>
BitScanReverse		equ <_BitScanReverse>
BitScanForward64	equ <_BitScanForward64>
BitScanReverse64	equ <_BitScanReverse64>

InterlockedIncrement16	equ <_InterlockedIncrement16>
InterlockedDecrement16	equ <_InterlockedDecrement16>
InterlockedCompareExchange16 equ <_InterlockedCompareExchange16>

InterlockedAnd		equ <_InterlockedAnd>
InterlockedAndAcquire	equ <_InterlockedAnd>
InterlockedAndRelease	equ <_InterlockedAnd>
InterlockedOr		equ <_InterlockedOr>
InterlockedOrAcquire	equ <_InterlockedOr>
InterlockedOrRelease	equ <_InterlockedOr>
InterlockedXor		equ <_InterlockedXor>
InterlockedIncrement	equ <_InterlockedIncrement>
InterlockedDecrement	equ <_InterlockedDecrement>
InterlockedAdd		equ <_InterlockedAdd>
InterlockedExchange	equ <_InterlockedExchange>
InterlockedExchangeAdd	equ <_InterlockedExchangeAdd>
InterlockedCompareExchange equ <_InterlockedCompareExchange>

InterlockedAnd64	equ <_InterlockedAnd64>
InterlockedAndAffinity	equ <InterlockedAnd64>
InterlockedOr64		equ <_InterlockedOr64>
InterlockedOrAffinity	equ <InterlockedOr64>
InterlockedXor64	equ <_InterlockedXor64>
InterlockedIncrement64	equ <_InterlockedIncrement64>
InterlockedDecrement64	equ <_InterlockedDecrement64>
InterlockedAdd64	equ <_InterlockedAdd64>
InterlockedExchange64	equ <_InterlockedExchange64>
InterlockedExchangeAcquire64 equ <InterlockedExchange64>
InterlockedExchangeAdd64 equ <_InterlockedExchangeAdd64>
InterlockedCompareExchange64 equ <_InterlockedCompareExchange64>

InterlockedExchangePointer equ <_InterlockedExchangePointer>
InterlockedCompareExchangePointer equ <_InterlockedCompareExchangePointer>
endif

InterlockedExchangeAddSizeT macro a, b
	exitm<InterlockedExchangeAdd64(a, b)>
	endm
InterlockedIncrementSizeT macro a
	exitm<InterlockedIncrement64(a)>
	endm
InterlockedDecrementSizeT macro a
	exitm<InterlockedDecrement64(a)>
	endm

ifndef _X86AMD64_
InterlockedAdd macro Addend, Value
	endm
endif

ifndef _X86AMD64_
InterlockedAdd64 macro Addend, Value
	add InterlockedExchangeAdd64(Addend, Value),Value
	exitm<rax>
	endm
endif

if _MSC_FULL_VER GE 140041204

InterlockedAnd8		equ <_InterlockedAnd8>
InterlockedOr8		equ <_InterlockedOr8>
InterlockedXor8		equ <_InterlockedXor8>
InterlockedAnd16	equ <_InterlockedAnd16>
InterlockedOr16		equ <_InterlockedOr16>
InterlockedXor16	equ <_InterlockedXor16>

endif


CacheLineFlush macro Address
	exitm<_mm_clflush(Address)>
	endm

FastFence		equ <__faststorefence>
LoadFence		equ <_mm_lfence>
MemoryFence		equ <_mm_mfence>
StoreFence		equ <_mm_sfence>

_MM_HINT_T0		equ 1
_MM_HINT_T1		equ 2
_MM_HINT_T2		equ 3
_MM_HINT_NTA		equ 0

YieldProcessor		equ <_mm_pause>
MemoryBarrier		equ <__faststorefence>
PreFetchCacheLine macro l, a
	exitm<_mm_prefetch(a, l)>
	endm
PrefetchForWrite macro p
	exitm<_m_prefetchw(p)>
	endm
ReadForWriteAccess macro p
	exitm<(_m_prefetchw(p), *(p))>
	endm


PF_TEMPORAL_LEVEL_1	equ _MM_HINT_T0
PF_TEMPORAL_LEVEL_2	equ _MM_HINT_T1
PF_TEMPORAL_LEVEL_3	equ _MM_HINT_T2
PF_NON_TEMPORAL_LEVEL_ALL equ _MM_HINT_NTA


_mm_getcsr proto fastcall {
    stmxcsr [rsp]
    mov	    eax,[rsp]
    }

_mm_setcsr proto fastcall :dword {
    mov	    [rsp],ecx
    ldmxcsr [rsp]
    }

__int2c proto fastcall {
    int	    0x2c
    }

__getcallerseflags proto fastcall {
    pushfq
    pop	    rax
    }

__segmentlimit proto fastcall :dword {
    mov	    eax,ecx
    lsl	    eax,eax
    }

__readpmc proto fastcall :dword {
    rdpmc
    shl	    rdx,32
    or	    rax,rdx
    }

__rdtsc proto fastcall {
    rdtsc
    shl	    rdx,32
    or	    rax,rdx
    }


ReadMxCsr		 equ <_mm_getcsr>
WriteMxCsr		 equ <_mm_setcsr>
DbgRaiseAssertionFailure equ <__int2c>
GetCallersEflags	 equ <__getcallerseflags>
GetSegmentLimit		 equ <__segmentlimit>
ReadPMC			 equ <__readpmc>
ReadTimeStampCounter	 equ <__rdtsc>


__movsb proto fastcall :ptr, :ptr, :sdword {
    push    rsi
    push    rdi
    mov	    rdi,rcx
    mov	    rsi,rdx
    mov	    ecx,r8d
    rep	    movsb
    pop	    rdi
    pop	    rsi
    }

__movsw proto fastcall :ptr, :ptr, :sdword {
    push    rsi
    push    rdi
    mov	    rdi,rcx
    mov	    rsi,rdx
    mov	    ecx,r8d
    rep	    movsw
    pop	    rdi
    pop	    rsi
    }

__movsd proto fastcall :ptr, :ptr, :sdword {
    push    rsi
    push    rdi
    mov	    rdi,rcx
    mov	    rsi,rdx
    mov	    ecx,r8d
    rep	    movsd
    pop	    rdi
    pop	    rsi
    }

__movsq proto fastcall :ptr, :qword, :sdword {
    push    rsi
    push    rdi
    mov	    rdi,rcx
    mov	    rsi,rdx
    mov	    ecx,r8d
    rep	    movsq
    pop	    rdi
    pop	    rsi
    }

__stosb proto fastcall :ptr, :byte, :sdword {
    push    rdi
    mov	    rdi,rcx
    mov	    al,dl
    mov	    ecx,r8d
    rep	    stosb
    pop	    rdi
    }

__stosw proto fastcall :ptr, :word, :sdword {
    push    rdi
    mov	    rdi,rcx
    mov	    ax,dx
    mov	    ecx,r8d
    rep	    stosw
    pop	    rdi
    }

__stosd proto fastcall :ptr, :dword, :sdword {
    push    rdi
    mov	    rdi,rcx
    mov	    eax,edx
    mov	    ecx,r8d
    rep	    stosd
    pop	    rdi
    }

__stosq proto fastcall :ptr, :ptr, :sdword {
    push    rdi
    mov	    rdi,rcx
    mov	    rax,rdx
    mov	    ecx,r8d
    rep	    stosd
    pop	    rdi
    }


MultiplyHigh		equ <__mulh>
UnsignedMultiplyHigh	equ <__umulh>

;LONGLONG
__mulh proto WINAPI \
	    Multiplier: LONG64,
	  Multiplicand: LONG64
;ULONGLONG
__umulh proto WINAPI \
	    Multiplier: DWORD64,
	  Multiplicand: DWORD64


ShiftLeft128	equ <__shiftleft128>
ShiftRight128	equ <__shiftright128>

__shiftleft128 proto :qword, :qword, :dword {
    mov	    rax,rcx
    mov	    ecx,r8d
    shld    rdx,rax,cl
    sal	    rax,cl
    .if cl & 0xC0
	.if cl & 0x80
	    xor eax,eax
	    xor edx,edx
	.else
	    mov rdx,rax
	    xor eax,eax
	.endif
    .endif
    }

__shiftright128 proto :qword, :qword, :dword {
    mov	    rax,rcx
    mov	    ecx,r8d
    shrd    rdx,rax,cl
    sar	    rax,cl
    .if cl & 0xC0
	.if cl & 0x80
	    xor eax,eax
	    xor edx,edx
	.else
	    mov rax,rdx
	    xor rdx,rdx
	.endif
    .endif
    }

ifdef _WIN64
_mul128 proto fastcall :qword, :qword, :ptr qword {
    mov rax,rdx
    mul rcx
    .if r8
	mov [r8],rdx
    .endif
    }
else
_mul128 proto :qword, :qword, :ptr qword
endif

define Multiply128 <_mul128>
ifndef UnsignedMultiply128
define UnsignedMultiply128 <_mul128>
define _umul128 <_mul128>
endif

__readgsbyte proto fastcall :ptr {
    movzx   eax,byte ptr gs:[rcx]
    }
__readgsword proto fastcall :ptr {
    movzx   eax,word ptr gs:[rcx]
    }
__readgsdword proto fastcall :ptr {
    mov	    eax,gs:[rcx]
    }
__readgsqword proto fastcall :ptr {
    mov	    rax,gs:[rcx]
    }

__writegsbyte proto fastcall :ptr, :byte {
    mov	    gs:[rcx],dl
    }
__writegsword proto fastcall :ptr, :word {
    mov	    gs:[rcx],dx
    }
__writegsdword proto fastcall :ptr, :dword {
    mov	    gs:[rcx],edx
    }
__writegsqword proto fastcall :ptr, :qword {
    mov	    gs:[rcx],rdx
    }


ifndef _MANAGED

__addgsbyte proto fastcall :ptr, :byte {
    add	    gs:[rcx],dl
    }
__addgsword proto fastcall :ptr, :word {
    add	    gs:[rcx],dx
    }
__addgsdword proto fastcall :ptr, :dword {
    add	    gs:[rcx],edx
    }
__addgsqword proto fastcall :ptr, :qword {
    add	    gs:[rcx],rdx
    }

__incgsbyte proto fastcall :ptr {
    inc	    byte ptr gs:[rcx]
    }
__incgsword proto fastcall :ptr {
    inc	    word ptr gs:[rcx]
    }
__incgsdword proto fastcall :ptr {
    inc	    dword ptr gs:[rcx]
    }
__incgsqword proto fastcall :ptr {
    inc	    qword ptr gs:[rcx]
    }

endif
endif

EXCEPTION_READ_FAULT	equ 0
EXCEPTION_WRITE_FAULT	equ 1
EXCEPTION_EXECUTE_FAULT equ 8

CONTEXT_AMD64		equ 0x100000

CONTEXT_CONTROL		equ (CONTEXT_AMD64 OR 0x1)
CONTEXT_INTEGER		equ (CONTEXT_AMD64 OR 0x2)
CONTEXT_SEGMENTS	equ (CONTEXT_AMD64 OR 0x4)
CONTEXT_FLOATING_POINT	equ (CONTEXT_AMD64 OR 0x8)
CONTEXT_DEBUG_REGISTERS equ (CONTEXT_AMD64 OR 0x10)

CONTEXT_FULL		equ (CONTEXT_CONTROL OR CONTEXT_INTEGER OR CONTEXT_FOATING_POINT)
CONTEXT_ALL		equ (CONTEXT_CONTROL OR CONTEXT_INTEGER OR CONTEXT_SEGMENTS OR CONTEXT_FOATING_POINT OR CONTEXT_DEBUG_REGISTERS)
CONTEXT_XSTATE		equ (CONTEXT_AMD64 OR 0x20)

CONTEXT_EXCEPTION_ACTIVE equ 0x8000000
CONTEXT_SERVICE_ACTIVE	equ 0x10000000
CONTEXT_EXCEPTION_REQUEST equ 0x40000000
CONTEXT_EXCEPTION_REPORTING equ 0x80000000

INITIAL_MXCSR		equ 0x1f80
INITIAL_FPCSR		equ 0x027f

XMM_SAVE_AREA32		typedef XSAVE_FORMAT
PXMM_SAVE_AREA32	typedef ptr XSAVE_FORMAT

CONTEXT			STRUC 16
 P1Home			dq ?
 P2Home			dq ?
 P3Home			dq ?
 P4Home			dq ?
 P5Home			dq ?
 P6Home			dq ?
 ContextFlags		dd ?
 MxCsr			dd ?
 SegCs			dw ?
 SegDs			dw ?
 SegEs			dw ?
 SegFs			dw ?
 SegGs			dw ?
 SegSs			dw ?
 EFlags			dd ?
 _Dr0			dq ?
 _Dr1			dq ?
 _Dr2			dq ?
 _Dr3			dq ?
 _Dr6			dq ?
 _Dr7			dq ?
 _Rax			dq ?
 _Rcx			dq ?
 _Rdx			dq ?
 _Rbx			dq ?
 _Rsp			dq ?
 _Rbp			dq ?
 _Rsi			dq ?
 _Rdi			dq ?
 _R8			dq ?
 _R9			dq ?
 _R10			dq ?
 _R11			dq ?
 _R12			dq ?
 _R13			dq ?
 _R14			dq ?
 _R15			dq ?
 _Rip			dq ?
 union
  FltSave		XMM_SAVE_AREA32 <>
  struct
   Header		M128A 2 dup(<>)
   Legacy		M128A 8 dup(<>)
   _Xmm0		M128A <>
   _Xmm1		M128A <>
   _Xmm2		M128A <>
   _Xmm3		M128A <>
   _Xmm4		M128A <>
   _Xmm5		M128A <>
   _Xmm6		M128A <>
   _Xmm7		M128A <>
   _Xmm8		M128A <>
   _Xmm9		M128A <>
   _Xmm10		M128A <>
   _Xmm11		M128A <>
   _Xmm12		M128A <>
   _Xmm13		M128A <>
   _Xmm14		M128A <>
   _Xmm15		M128A <>
  ends
 ends
 VectorRegister		M128A 26 dup(<>)
 VectorControl		dq ?
 DebugControl		dq ?
 LastBranchToRip	dq ?
 LastBranchFromRip	dq ?
 LastExceptionToRip	dq ?
 LastExceptionFromRip	dq ?
CONTEXT			ENDS
PCONTEXT		typedef ptr CONTEXT

SCOPE_TABLE		typedef SCOPE_TABLE_AMD64
PSCOPE_TABLE		typedef ptr SCOPE_TABLE_AMD64

_IMAGE_RUNTIME_FUNCTION_ENTRY STRUC
BeginAddress		dd ?
EndAddress		dd ?
UNION
 UnwindInfoAddress	dd ?
 UnwindData		dd ?
ENDS
_IMAGE_RUNTIME_FUNCTION_ENTRY ENDS

RUNTIME_FUNCTION	typedef _IMAGE_RUNTIME_FUNCTION_ENTRY
PRUNTIME_FUNCTION	typedef ptr _IMAGE_RUNTIME_FUNCTION_ENTRY

define RUNTIME_FUNCTION_INDIRECT 0x1

define UNW_FLAG_NHANDLER       0x0
define UNW_FLAG_EHANDLER       0x1
define UNW_FLAG_UHANDLER       0x2
define UNW_FLAG_CHAININFO      0x4

define UNW_FLAG_NO_EPILOGUE    0x80000000

define UNWIND_HISTORY_TABLE_SIZE 12

UNWIND_HISTORY_TABLE_ENTRY STRUC
ImageBase		dq ?
FunctionEntry		PRUNTIME_FUNCTION ?
UNWIND_HISTORY_TABLE_ENTRY ENDS
PUNWIND_HISTORY_TABLE_ENTRY typedef ptr UNWIND_HISTORY_TABLE_ENTRY

UNWIND_HISTORY_TABLE	STRUC
Count			dd ?
LocalHint		db ?
GlobalHint		db ?
Search			db ?
Once			db ?
LowAddress		dq ?
HighAddress		dq ?
Entry			UNWIND_HISTORY_TABLE_ENTRY UNWIND_HISTORY_TABLE_SIZE dup(<>)
UNWIND_HISTORY_TABLE	ENDS
PUNWIND_HISTORY_TABLE	typedef ptr UNWIND_HISTORY_TABLE


CALLBACK(PGET_RUNTIME_FUNCTION_CALLBACK, :qword, :ptr)
CALLBACK(POUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK, :HANDLE, :ptr, :PDWORD, :PRUNTIME_FUNCTION)

OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK_EXPORT_NAME equ <"OutOfProcessFunctionTableCallback">

DISPATCHER_CONTEXT	STRUC
ControlPc		dq ?
ImageBase		dq ?
FunctionEntry		PRUNTIME_FUNCTION ?
EstablisherFrame	dq ?
TargetIp		dq ?
ContextRecord		PCONTEXT ?
LanguageHandler		PEXCEPTION_ROUTINE ?
HandlerData		PVOID ?
HistoryTable		PUNWIND_HISTORY_TABLE ?
ScopeIndex		dd ?
Fill0			dd ?
DISPATCHER_CONTEXT	ENDS
PDISPATCHER_CONTEXT	typedef ptr DISPATCHER_CONTEXT

CALLBACK(PEXCEPTION_FILTER, :ptr EXCEPTION_POINTERS, :ptr)
CALLBACK(PTERMINATION_HANDLER, :BOOLEAN, :ptr)

;NTSYSAPI
;VOID
RtlRestoreContext proto WINAPI \
	 ContextRecord: PCONTEXT,
       ExceptionRecord: ptr EXCEPTION_RECORD

;BOOLEAN
RtlAddFunctionTable proto WINAPI \
	 FunctionTable: PRUNTIME_FUNCTION,
	    EntryCount: DWORD,
	   BaseAddress: DWORD64

;PRUNTIME_FUNCTION
RtlLookupFunctionEntry proto WINAPI \
	     ControlPc: DWORD64,
	     ImageBase: PDWORD64,
	  HistoryTable: PUNWIND_HISTORY_TABLE


KNONVOLATILE_CONTEXT_POINTERS  STRUC
UNION
 FloatingContext	PM128A 16 dup(?)
 STRUC
  _Xmm0			PM128A ?
  _Xmm1			PM128A ?
  _Xmm2			PM128A ?
  _Xmm3			PM128A ?
  _Xmm4			PM128A ?
  _Xmm5			PM128A ?
  _Xmm6			PM128A ?
  _Xmm7			PM128A ?
  _Xmm8			PM128A ?
  _Xmm9			PM128A ?
  _Xmm10		PM128A ?
  _Xmm11		PM128A ?
  _Xmm12		PM128A ?
  _Xmm13		PM128A ?
  _Xmm14		PM128A ?
  _Xmm15		PM128A ?
 ENDS
ENDS
UNION
 IntegerContext		PDWORD64 16 dup(?)
 STRUC
  _Rax			PDWORD64 ?
  _Rcx			PDWORD64 ?
  _Rdx			PDWORD64 ?
  _Rbx			PDWORD64 ?
  _Rsp			PDWORD64 ?
  _Rbp			PDWORD64 ?
  _Rsi			PDWORD64 ?
  _Rdi			PDWORD64 ?
  _R8			PDWORD64 ?
  _R9			PDWORD64 ?
  _R10			PDWORD64 ?
  _R11			PDWORD64 ?
  _R12			PDWORD64 ?
  _R13			PDWORD64 ?
  _R14			PDWORD64 ?
  _R15			PDWORD64 ?
 ENDS
ENDS
KNONVOLATILE_CONTEXT_POINTERS ENDS
PKNONVOLATILE_CONTEXT_POINTERS typedef ptr KNONVOLATILE_CONTEXT_POINTERS

;NTSYSAPI
;PEXCEPTION_ROUTINE
RtlVirtualUnwind proto WINAPI \
	   HandlerType: DWORD,
	     ImageBase: DWORD64,
	     ControlPc: DWORD64,
	 FunctionEntry: PRUNTIME_FUNCTION,
	 ContextRecord: PCONTEXT,
	   HandlerData: PVOID,
      EstablisherFrame: PDWORD64,
       ContextPointers: PKNONVOLATILE_CONTEXT_POINTERS

;BOOLEAN
RtlInstallFunctionTableCallback proto WINAPI \
       TableIdentifier: DWORD64,
	   BaseAddress: DWORD64,
		Length: DWORD,
	      Callback: PGET_RUNTIME_FUNCTION_CALLBACK,
	       Context: PVOID,
OutOfProcessCallbackDll: PCWSTR

;BOOLEAN
RtlDeleteFunctionTable proto WINAPI \
	 FunctionTable: PRUNTIME_FUNCTION

endif

ifdef _X86_

;if defined(_M_IX86) AND NOT defined(RC_INVOKED) AND NOT defined(MIDL_PASS)
if defined(_M_IX86) AND NOT defined(MIDL_PASS)

if (_MSC_FULL_VER GE 14000101)

BitTest			equ <_bittest>
BitTestAndComplement	equ <_bittestandcomplement>
BitTestAndSet		equ <_bittestandset>
BitTestAndReset		equ <_bittestandreset>
InterlockedBitTestAndSet equ <_interlockedbittestandset>
InterlockedBitTestAndReset equ <_interlockedbittestandreset>

BitScanForward		equ <_BitScanForward>
BitScanReverse		equ <_BitScanReverse>

else

InterlockedBitTestAndSet proto fastcall :ptr, :dword {
	mov	eax,edx
	lock	bts [rcx],eax
	setc	al
	}

InterlockedBitTestAndReset proto fastcall :ptr, :dword {
	mov	eax,edx
	lock	btr [rcx],eax
	setc	al
	}

endif

if (_MSC_FULL_VER GE 140040816) OR (defined(_PREFAST_) AND (_MSC_VER GE 1400))

InterlockedAnd16	equ <_InterlockedAnd16>
InterlockedCompareExchange16 equ <_InterlockedCompareExchange16>
InterlockedOr16		equ <_InterlockedOr16>

endif

ifndef _M_CEE_PURE

InterlockedBitTestAndComplement proto fastcall :ptr, :dword {
	mov	eax,edx
	lock	btc [rcx],eax
	setc	al
	}
endif

if (_MSC_FULL_VER GE 13012035) OR defined(_PREFIX_) OR defined(_PREFAST_)


__writefsbyte proto fastcall :ptr, :byte {
    assume  fs:nothing
    mov	    fs:[rcx],dl
    assume  fs:error
    }

__writefsword proto fastcall :ptr, :word {
    assume  fs:nothing
    mov	    fs:[rcx],dx
    assume  fs:error
    }

__writefsdword proto fastcall :ptr, :dword {
    assume  fs:nothing
    mov	    fs:[rcx],edx
    assume  fs:error
    }

endif

if (_MSC_FULL_VER GE 140050727) OR defined(_PREFIX_) OR defined(_PREFAST_)

ifndef _MANAGED

__addfsbyte proto fastcall :ptr, :byte {
    assume  fs:nothing
    add	    fs:[rcx],dl
    assume  fs:error
    }
__addfsword proto fastcall :ptr, :word {
    assume  fs:nothing
    add	    fs:[rcx],dx
    assume  fs:error
    }
__addfsdword proto fastcall :ptr, :dword {
    assume  fs:nothing
    add	    fs:[rcx],edx
    assume  fs:error
    }

__incfsbyte proto fastcall :ptr {
    assume  fs:nothing
    inc	    byte ptr fs:[rcx]
    assume  fs:error
    }
__incfsword proto fastcall :ptr {
    assume  fs:nothing
    inc	    word ptr fs:[rcx]
    assume  fs:error
    }
__incfsdword proto fastcall :ptr {
    assume  fs:nothing
    inc	    dword ptr fs:[rcx]
    assume  fs:error
    }

endif
endif

if (_MSC_FULL_VER GE 140041204) OR defined(_PREFIX_) OR defined(_PREFAST_)

;VOID
_mm_pause proto WINAPI

YieldProcessor	equ <_mm_pause>

else

ifndef _M_CEE_PURE
YieldProcessor macro
	exitm<rep nop>
	endm
endif
endif

endif

if NOT defined(MIDL_PASS) AND defined(_M_IX86)

ifndef _M_CEE_PURE

;FORCEINLINE
;VOID
MemoryBarrier macro
    endm

endif


PreFetchCacheLine macro l, a
	endm
PrefetchForWrite macro p
	endm
ReadForWriteAccess macro p
	endm


PF_TEMPORAL_LEVEL_1 equ 1
PF_NON_TEMPORAL_LEVEL_ALL equ 1

if _MSC_FULL_VER GE 140050727
ReadPMC equ <__readpmc>
endif

if _MSC_FULL_VER GE 140040310
ReadTimeStampCounter equ <__rdtsc>
else
endif


;if defined(_X86_) AND defined(_M_IX86) AND NOT defined(RC_INVOKED) AND NOT defined(MIDL_PASS)
if defined(_X86_) AND defined(_M_IX86) AND NOT defined(MIDL_PASS)

if _MSC_FULL_VER GE 140030222
DbgRaiseAssertionFailure equ <__int2c>
endif

endif

if (_MSC_FULL_VER GE 13012035)

GetFiberData macro
	exitm<__readfsdword(0x10)>
	endm
GetCurrentFiber macro
	exitm<__readfsdword(0x10)>
	endm
else

if _MSC_VER GE 1200
endif

;__inline PVOID
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
if _MSC_VER GE 1200
else
endif
endif

endif


EXCEPTION_READ_FAULT	equ 0
EXCEPTION_WRITE_FAULT	equ 1
EXCEPTION_EXECUTE_FAULT equ 8

SIZE_OF_80387_REGISTERS equ 80


;ifndef RC_INVOKED

CONTEXT_i386		equ 0x00010000
CONTEXT_i486		equ 0x00010000

CONTEXT_CONTROL		equ CONTEXT_i386 OR 0x00000001
CONTEXT_INTEGER		equ CONTEXT_i386 OR 0x00000002
CONTEXT_SEGMENTS	equ CONTEXT_i386 OR 0x00000004
CONTEXT_FLOATING_POINT	equ CONTEXT_i386 OR 0x00000008
CONTEXT_DEBUG_REGISTERS equ CONTEXT_i386 OR 0x00000010
CONTEXT_EXTENDED_REGISTERS equ CONTEXT_i386 OR 0x00000020
CONTEXT_FULL		equ CONTEXT_CONTROL OR CONTEXT_INTEGER OR CONTEXT_SEGMENTS
CONTEXT_ALL		equ CONTEXT_CONTROL OR CONTEXT_INTEGER OR CONTEXT_SEGMENTS OR \
			    CONTEXT_DEBUG_REGISTERS OR CONTEXT_FLOATING_POINT OR \
			    CONTEXT_EXTENDED_REGISTERS
CONTEXT_XSTATE		equ CONTEXT_i386 OR 0x00000040


MAXIMUM_SUPPORTED_EXTENSION equ 512

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

if NOT defined(__midl) AND NOT defined(MIDL_PASS)
if (XSAVE_FORMAT NE MAXIMUM_SUPPORTED_EXTENSION)
	.err <XSAVE_FORMAT != MAXIMUM_SUPPORTED_EXTENSION>
endif
endif

.pragma pack(push, 4)

CONTEXT		STRUC
ContextFlags	dd ?
_Dr0		dd ?
_Dr1		dd ?
_Dr2		dd ?
_Dr3		dd ?
_Dr6		dd ?
_Dr7		dd ?
FloatSave	FLOATING_SAVE_AREA <>
SegGs		dd ?
SegFs		dd ?
SegEs		dd ?
SegDs		dd ?
_Edi		dd ?
_Esi		dd ?
_Ebx		dd ?
_Edx		dd ?
_Ecx		dd ?
_Eax		dd ?
_Ebp		dd ?
_Eip		dd ?
SegCs		dd ? ; MUST BE SANITIZED
EFlags		dd ? ; MUST BE SANITIZED
_Esp		dd ?
SegSs		dd ?
ExtendedRegisters db MAXIMUM_SUPPORTED_EXTENSION dup(?)
CONTEXT		ENDS

PCONTEXT typedef ptr CONTEXT

.pragma pack(pop)

endif


ifndef _LDT_ENTRY_DEFINED
define _LDT_ENTRY_DEFINED

LDT_ENTRY	STRUC
LimitLow	dw ?
BaseLow		dw ?
UNION ;HighWord
 STRUC Bytes
  BaseMid	db ?
  Flags1	db ?	; Declare as bytes to avoid alignment
  Flags2	db ?	; Problems.
  BaseHi	db ?
 ENDS
 RECORD Bits
  BaseMid	dd : 8 ?
  Type		dd : 5 ?
  Dpl		dd : 2 ?
  Pres		dd : 1 ?
  LimitHi	dd : 4 ?
  Sys		dd : 1 ?
  Reserved_0	dd : 1 ?
  Default_Big	dd : 1 ?
  Granularity	dd : 1 ?
  BaseHi	dd : 8 ?
 ENDS
ENDS
LDT_ENTRY	ENDS
PLDT_ENTRY	typedef ptr LDT_ENTRY

endif

;if defined(_M_IA64) AND NOT defined(RC_INVOKED) AND NOT defined(MIDL_PASS)
if defined(_M_IA64) AND NOT defined(MIDL_PASS)

if 0
BitTest			equ <_bittest>
BitTestAndComplement	equ <_bittestandcomplement>
BitTestAndSet		equ <_bittestandset>
BitTestAndReset		equ <_bittestandreset>

BitTest64		equ <_bittest64>
BitTestAndComplement64	equ <_bittestandcomplement64>
BitTestAndSet64		equ <_bittestandset64>
BitTestAndReset64	equ <_bittestandreset64>

BitScanForward		equ <_BitScanForward>
BitScanReverse		equ <_BitScanReverse>
BitScanForward64	equ <_BitScanForward64>
BitScanReverse64	equ <_BitScanReverse64>

InterlockedCompareExchange16 equ <_InterlockedCompareExchange16>

InterlockedAdd		equ <_InterlockedAdd>
InterlockedIncrement	equ <_InterlockedIncrement>
InterlockedDecrement	equ <_InterlockedDecrement>
InterlockedExchange	equ <_InterlockedExchange>
InterlockedExchangeAdd	equ <_InterlockedExchangeAdd>
InterlockedAdd64	equ <_InterlockedAdd64>
InterlockedIncrement64	equ <_InterlockedIncrement64>
InterlockedDecrement64	equ <_InterlockedDecrement64>
InterlockedExchange64	equ <_InterlockedExchange64>
InterlockedExchangeAdd64 equ <_InterlockedExchangeAdd64>
InterlockedCompareExchange64 equ <_InterlockedCompareExchange64>
InterlockedCompare64Exchange128 equ <_InterlockedCompare64Exchange128>
InterlockedCompareExchange equ <_InterlockedCompareExchange>
InterlockedExchangePointer equ <_InterlockedExchangePointer>
InterlockedCompareExchangePointer equ <_InterlockedCompareExchangePointer>

InterlockedExchangeAddSizeT macro a, b
	exitm<InterlockedExchangeAdd64(a, b)>
	endm
InterlockedIncrementSizeT macro a
	exitm<InterlockedIncrement64(a)>
	endm
InterlockedDecrementSizeT macro a
	exitm<InterlockedDecrement64(a)>
	endm

InterlockedOr		equ <_InterlockedOr>
InterlockedOr8		equ <_InterlockedOr8>
InterlockedOr16		equ <_InterlockedOr16>
InterlockedOr64		equ <_InterlockedOr64>
InterlockedXor		equ <_InterlockedXor>
InterlockedXor8		equ <_InterlockedXor8>
InterlockedXor16	equ <_InterlockedXor16>
InterlockedXor64	equ <_InterlockedXor64>
InterlockedAnd		equ <_InterlockedAnd>
InterlockedAnd8		equ <_InterlockedAnd8>
InterlockedAnd16	equ <_InterlockedAnd16>
InterlockedAnd64	equ <_InterlockedAnd64>

ifndef InterlockedAnd64
InterlockedAnd64	equ <_InterlockedAnd64>
endif
InterlockedAndAffinity	equ <InterlockedAnd64>
ifndef InterlockedOr64
InterlockedOr64		equ <_InterlockedOr64>
endif
InterlockedOrAffinity	equ <_InterlockedOr64>
ifndef InterlockedXor64
InterlockedXor64	equ <_InterlockedXor64>
endif
ifndef InterlockedBitTestAndSet
InterlockedBitTestAndSet equ <_InterlockedBitTestAndSet>
endif
ifndef InterlockedBitTestAndReset
InterlockedBitTestAndReset equ <_InterlockedBitTestAndReset>
endif
ifndef InterlockedBitTestAndSet64
InterlockedBitTestAndSet64 equ <_InterlockedBitTestAndSet64>
endif
ifndef InterlockedBitTestAndReset64
InterlockedBitTestAndReset64 equ <_InterlockedBitTestAndReset64>
endif
ifndef InterlockedBitTestAndComplement
InterlockedBitTestAndComplement equ <_InterlockedBitTestAndComplement>
endif
ifndef InterlockedBitTestAndComplement64
InterlockedBitTestAndComplement64 equ <_InterlockedBitTestAndComplement64>
endif

endif
endif

if NOT defined(__midl) AND NOT defined(GENUTIL) AND NOT defined(_GENIA64_) AND defined(_IA64_)

ifdef _M_IA64

_rdtebex macro
	exitm<NtCurrentTeb()>
	endm

GetCurrentFiber macro
	exitm<[NtCurrentTeb()].FiberData>
	endm
GetFiberData macro
	mov rax,GetCurrentFiber()
	mov rax,[rax]
	exitm<rax>
	endm

if defined(_IA64_) AND defined(_M_IA64) AND NOT defined(MIDL_PASS)

;void
__break proto WINAPI \
		 StIIM: SINT

BREAK_DEBUG_BASE	equ 0x080000
ASSERT_BREAKPOINT	equ (BREAK_DEBUG_BASE+3)

;FORCEINLINE
;VOID
DbgRaiseAssertionFailure macro
    __break(ASSERT_BREAKPOINT)
    endm

endif

;void
__yield proto WINAPI
;void
__mf proto WINAPI
;void
__lfetch proto WINAPI \
		 Level: SINT,
	       Address: PVOID
;void
__lfetchfault proto WINAPI \
		 Level: SINT,
	       Address: PVOID
;void
__lfetch_excl proto WINAPI \
		 Level: SINT,
	       Address: PVOID
;void
__lfetchfault_excl proto WINAPI \
		 Level: SINT,
	       Address: PVOID


MD_LFHINT_NONE		equ 0x00
MD_LFHINT_NT1		equ 0x01
MD_LFHINT_NT2		equ 0x02
MD_LFHINT_NTA		equ 0x03


ReadTimeStampCounter macro
	exitm<__getReg(3116)>
	endm

;unsigned __int64
__getReg proto WINAPI \
		Number: SINT

YieldProcessor		equ <__yield>
MemoryBarrier		equ <__mf>
PreFetchCacheLine	equ <__lfetch>
PrefetchForWrite macro p
	endm

ReadForWriteAccess macro p
	exitm<(__lfetch_excl(MD_LFHINT_NONE, p), *p)>
	endm


PF_TEMPORAL_LEVEL_1	equ MD_LFHINT_NONE
PF_TEMPORAL_LEVEL_2	equ MD_LFHINT_NT1
PF_TEMPORAL_LEVEL_3	equ MD_LFHINT_NT2
PF_NON_TEMPORAL_LEVEL_ALL equ MD_LFHINT_NTA


UnsignedMultiplyHigh	equ <__UMULH>

;ULONGLONG
__UMULH proto WINAPI \
	    Multiplier: ULONGLONG,
	  Multiplicand: ULONGLONG


if (_MSC_VER GE 1400)

UnsignedMultiply128	equ <_umul128>

;DWORD64
ifndef _M_X64
_umul128 proto Multiplier: DWORD64, Multiplicand: DWORD64, HighProduct: ptr DWORD64
endif
endif

else

;STRUC TEB *
NtCurrentTeb proto WINAPI

endif

endif

ifdef _IA64_

EXCEPTION_READ_FAULT	equ 0
EXCEPTION_WRITE_FAULT	equ 1
EXCEPTION_EXECUTE_FAULT equ 2

;ifndef RC_INVOKED

CONTEXT_IA64		equ 0x00080000

CONTEXT_CONTROL		equ CONTEXT_IA64 OR 0x00000001
CONTEXT_LOWER_FLOATING_POINT equ CONTEXT_IA64 OR 0x00000002
CONTEXT_HIGHER_FLOATING_POINT equ CONTEXT_IA64 OR 0x00000004
CONTEXT_INTEGER		equ CONTEXT_IA64 OR 0x00000008
CONTEXT_DEBUG		equ CONTEXT_IA64 OR 0x00000010
CONTEXT_IA32_CONTROL	equ CONTEXT_IA64 OR 0x00000020


CONTEXT_FLOATING_POINT	equ CONTEXT_LOWER_FLOATING_POINT OR CONTEXT_HIGHER_FOATING_POINT
CONTEXT_FULL		equ CONTEXT_CONTROL OR CONTEXT_FLOATING_POINT OR \
			    CONTEXT_INTEGER OR CONTEXT_IA32_CONTROL
CONTEXT_ALL		equ CONTEXT_CONTROL OR CONTEXT_FLOATING_POINT OR \
			    CONTEXT_INTEGER OR CONTEXT_DEBUG OR CONTEXT_IA32_CONTROL

CONTEXT_EXCEPTION_ACTIVE    equ 0x8000000
CONTEXT_SERVICE_ACTIVE	    equ 0x10000000
CONTEXT_EXCEPTION_REQUEST   equ 0x40000000
CONTEXT_EXCEPTION_REPORTING equ 0x80000000

;endif

XMM_SAVE_AREA32		typedef XSAVE_FORMAT
PXMM_SAVE_AREA32	typedef ptr XSAVE_FORMAT

CONTEXT			STRUC
 P1Home			dq ?
 P2Home			dq ?
 P3Home			dq ?
 P4Home			dq ?
 P5Home			dq ?
 P6Home			dq ?
 ContextFlags		dd ?
 MxCsr			dd ?
 SegCs			dw ?
 SegDs			dw ?
 SegEs			dw ?
 SegFs			dw ?
 SegGs			dw ?
 SegSs			dw ?
 EFlags			dd ?
 _Dr0			dq ?
 _Dr1			dq ?
 _Dr2			dq ?
 _Dr3			dq ?
 _Dr6			dq ?
 _Dr7			dq ?
 _Rax			dq ?
 _Rcx			dq ?
 _Rdx			dq ?
 _Rbx			dq ?
 _Rsp			dq ?
 _Rbp			dq ?
 _Rsi			dq ?
 _Rdi			dq ?
 _R8			dq ?
 _R9			dq ?
 _R10			dq ?
 _R11			dq ?
 _R12			dq ?
 _R13			dq ?
 _R14			dq ?
 _R15			dq ?
 _Rip			dq ?
 union
  FltSave		XMM_SAVE_AREA32 <>
  Q			oword 16 dup(?)
  D			dq 32 dup(?)
  struct
   Header		M128A 2 dup(<>)
   Legacy		M128A 8 dup(<>)
   _Xmm0		M128A <>
   _Xmm1		M128A <>
   _Xmm2		M128A <>
   _Xmm3		M128A <>
   _Xmm4		M128A <>
   _Xmm5		M128A <>
   _Xmm6		M128A <>
   _Xmm7		M128A <>
   _Xmm8		M128A <>
   _Xmm9		M128A <>
   _Xmm10		M128A <>
   _Xmm11		M128A <>
   _Xmm12		M128A <>
   _Xmm13		M128A <>
   _Xmm14		M128A <>
   _Xmm15		M128A <>
  ends
  S			dd 32 dup(?)
 ends
 VectorRegister		oword 26 dup(?) ; M128A
 VectorControl		dq ?
 DebugControl		dq ?
 LastBranchToRip	dq ?
 LastBranchFromRip	dq ?
 LastExceptionToRip	dq ?
 LastExceptionFromRip	dq ?
CONTEXT			ENDS
PCONTEXT		typedef ptr CONTEXT

SCOPE_TABLE		typedef SCOPE_TABLE_AMD64
PSCOPE_TABLE		typedef ptr SCOPE_TABLE_AMD64

PLABEL_DESCRIPTOR	STRUC
EntryPoint		ULONGLONG ?
GlobalPointer		ULONGLONG ?
PLABEL_DESCRIPTOR	ENDS
PPLABEL_DESCRIPTOR	typedef ptr PLABEL_DESCRIPTOR

RUNTIME_FUNCTION_INDIRECT equ 0x1

RUNTIME_FUNCTION	STRUC
BeginAddress		dd ?
EndAddress		dd ?
UnwindInfoAddress	dd ?
RUNTIME_FUNCTION	ENDS
PRUNTIME_FUNCTION	typedef ptr RUNTIME_FUNCTION

UNW_FLAG_NHANDLER	equ 0x0
UNW_FLAG_EHANDLER	equ 0x1
UNW_FLAG_UHANDLER	equ 0x2

UNWIND_HISTORY_TABLE_SIZE equ 12

UNWIND_HISTORY_TABLE_ENTRY STRUC
ImageBase		dd ?
Gp			dd ?
FunctionEntry		PRUNTIME_FUNCTION ?
UNWIND_HISTORY_TABLE_ENTRY ENDS
PUNWIND_HISTORY_TABLE_ENTRY typedef ptr UNWIND_HISTORY_TABLE_ENTRY

UNWIND_HISTORY_TABLE	STRUC
Count			dd ?
LocalHint		db ?
GlobalHint		db ?
Search			db ?
Once			db ?
LowAddress		dd ?
HighAddress		dd ?
Entry			UNWIND_HISTORY_TABLE_ENTRY UNWIND_HISTORY_TABLE_SIZE dup(<>)
UNWIND_HISTORY_TABLE	ENDS
PUNWIND_HISTORY_TABLE	typedef ptr UNWIND_HISTORY_TABLE

DISPATCHER_CONTEXT	STRUC
ControlPc		DWORD ?
ImageBase		DWORD ?
FunctionEntry		PRUNTIME_FUNCTION ?
EstablisherFrame	DWORD ?
TargetPc		DWORD ?
ContextRecord		PCONTEXT ?
LanguageHandler		PEXCEPTION_ROUTINE ?
HandlerData		PVOID ?
HistoryTable		PUNWIND_HISTORY_TABLE ?
ScopeIndex		DWORD ?
ControlPcIsUnwound	BOOLEAN ?
NonVolatileRegisters	PBYTE ?
Reserved		DWORD ?
DISPATCHER_CONTEXT	ENDS
PDISPATCHER_CONTEXT	typedef ptr DISPATCHER_CONTEXT

CALLBACK(PEXCEPTION_FILTER, :ptr EXCEPTION_POINTERS, :PVOID)
CALLBACK(PTERMINATION_HANDLER, :BOOLEAN, :PVOID)

;PRUNTIME_FUNCTION
CALLBACK(PGET_RUNTIME_FUNCTION_CALLBACK, ControlPc:DWORD64, Context:PVOID)

;DWORD
CALLBACK(POUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK, \
	       Process: HANDLE,			  \
	  TableAddress: PVOID,			  \
	       Entries: PDWORD,			  \
	     Functions: PRUNTIME_FUNCTION)

OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK_EXPORT_NAME equ <"OutOfProcessFunctionTableCallback">

;NTSYSAPI
;BOOLEAN
RtlAddFunctionTable proto WINAPI \
	 FunctionTable: PRUNTIME_FUNCTION,
	    EntryCount: DWORD,
	   BaseAddress: ULONGLONG,
	      TargetGp: ULONGLONG

;BOOLEAN
RtlInstallFunctionTableCallback proto WINAPI \
       TableIdentifier: DWORD64,
	   BaseAddress: DWORD64,
		Length: DWORD,
	      TargetGp: DWORD64,
	      Callback: PGET_RUNTIME_FUNCTION_CALLBACK,
	       Context: PVOID,
OutOfProcessCallbackDll: PCWSTR

;BOOLEAN
RtlDeleteFunctionTable proto WINAPI \
	 FunctionTable: PRUNTIME_FUNCTION

;PRUNTIME_FUNCTION
RtlLookupFunctionEntry proto WINAPI \
	     ControlPc: ULONGLONG,
	     ImageBase: PULONGLONG,
	      TargetGp: PULONGLONG


KNONVOLATILE_CONTEXT_POINTERS  STRUC
FltS0			PFLOAT128 ?
FltS1			PFLOAT128 ?
FltS2			PFLOAT128 ?
FltS3			PFLOAT128 ?
HighFloatingContext	PFLOAT128 10 dup(?)
FltS4			PFLOAT128 ?
FltS5			PFLOAT128 ?
FltS6			PFLOAT128 ?
FltS7			PFLOAT128 ?
FltS8			PFLOAT128 ?
FltS9			PFLOAT128 ?
FltS10			PFLOAT128 ?
FltS11			PFLOAT128 ?
FltS12			PFLOAT128 ?
FltS13			PFLOAT128 ?
FltS14			PFLOAT128 ?
FltS15			PFLOAT128 ?
FltS16			PFLOAT128 ?
FltS17			PFLOAT128 ?
FltS18			PFLOAT128 ?
FltS19			PFLOAT128 ?
IntS0			PULONGLONG ?
IntS1			PULONGLONG ?
IntS2			PULONGLONG ?
IntS3			PULONGLONG ?
IntSp			PULONGLONG ?
IntS0Nat		PULONGLONG ?
IntS1Nat		PULONGLONG ?
IntS2Nat		PULONGLONG ?
IntS3Nat		PULONGLONG ?
IntSpNat		PULONGLONG ?
Preds			PULONGLONG ?
BrRp			PULONGLONG ?
BrS0			PULONGLONG ?
BrS1			PULONGLONG ?
BrS2			PULONGLONG ?
BrS3			PULONGLONG ?
BrS4			PULONGLONG ?
ApUNAT			PULONGLONG ?
ApLC			PULONGLONG ?
ApEC			PULONGLONG ?
RsPFS			PULONGLONG ?
StFSR			PULONGLONG ?
StFIR			PULONGLONG ?
StFDR			PULONGLONG ?
Cflag			PULONGLONG ?
StFPSR			PULONGLONG ?
KNONVOLATILE_CONTEXT_POINTERS ENDS
PKNONVOLATILE_CONTEXT_POINTERS typedef ptr KNONVOLATILE_CONTEXT_POINTERS

FRAME_POINTERS		STRUC
MemoryStackFp		ULONGLONG ?
BackingStoreFp		ULONGLONG ?
FRAME_POINTERS		ENDS
PFRAME_POINTERS		typedef ptr FRAME_POINTERS

;NTSYSAPI
;ULONGLONG
RtlVirtualUnwind proto WINAPI \
	   HandlerType: DWORD,	 ;; <-- ifdef _WIN64
	     ImageBase: ULONGLONG,
	     ControlPc: ULONGLONG,
	 FunctionEntry: PRUNTIME_FUNCTION,
	 ContextRecord: PCONTEXT,
	    InFunction: PBOOLEAN,
      EstablisherFrame: PFRAME_POINTERS,
       ContextPointers: PKNONVOLATILE_CONTEXT_POINTERS

;VOID
RtlRestoreContext proto WINAPI \
	 ContextRecord: PCONTEXT,
       ExceptionRecord: ptr EXCEPTION_RECORD

;VOID
__jump_unwind proto WINAPI \
	 TargetMsFrame: ULONGLONG,
	 TargetBsFrame: ULONGLONG,
	      TargetPc: ULONGLONG

endif ; _IA64_

ifdef _WIN64

ReadAcquire8 proto :ptr char_t {
    movsx eax,char_t ptr [_1]
}

ReadNoFence8 proto :ptr char_t {
    movsx eax,char_t ptr [_1]
}

WriteRelease8 proto :ptr char_t, :char_t {
    mov [_1],_2
}

WriteNoFence8 proto :ptr char_t, :char_t {
    mov [_1],_2
}

ReadAcquire16 proto :ptr short_t {
    movsx eax,short_t ptr [_1]
}

ReadNoFence16 proto :ptr short_t {
    movsx eax,short_t ptr [_1]
}

WriteRelease16 proto :ptr short_t, :short_t {
    mov [_1],_2
}

WriteNoFence16 proto :ptr short_t, :short_t {
    mov [_1],_2
}

ReadAcquire proto :ptr short_t {
    movsx eax,short_t ptr [_1]
}

ReadNoFence proto :ptr LONG {
    mov eax,[_1]
}

WriteRelease proto :ptr LONG, :LONG {
    mov [_1],_2
}

WriteNoFence proto :ptr LONG, :LONG {
    mov [_1],_2
}

ReadAcquire64 proto :ptr LONG64 {
    mov rax,[_1]
}

ReadNoFence64 proto :ptr LONG64 {
    mov rax,[_1]
}

WriteRelease64 proto :ptr LONG64, :LONG64 {
    mov [_1],_2
}

WriteNoFence64 proto :ptr LONG64, :LONG64 {
    mov [_1],_2
}

ReadRaw8 proto :ptr SBYTE {
    movsx eax,sbyte ptr [_1]
}

WriteRaw8 proto :ptr SBYTE, :SBYTE {
    mov [_1],_2
}

ReadRaw16 proto :ptr SWORD {
    movsx eax,sword ptr [_1]
}

WriteRaw16 proto :ptr SWORD, :SWORD {
    mov [_1],_2
}

;ReadRaw proto :ptr LONG { mov eax,[rcx] }
;WriteRaw proto :ptr LONG, :LONG { mov [rcx],edx }

ReadRaw64 proto :ptr LONG64 {
    mov rax,[_1]
}

WriteRaw64 proto :ptr LONG64, :LONG64 {
    mov [_1],_2
}

ReadUCharAcquire	proto :ptr BYTE { ReadAcquire8(rcx) }
ReadUCharNoFence	proto :ptr BYTE { ReadNoFence8(rcx) }
ReadUCharRaw		proto :ptr BYTE { ReadRaw8(rcx) }
WriteUCharRelease	proto :ptr BYTE, :BYTE { WriteRelease8(rcx, dl) }
WriteUCharNoFence	proto :ptr BYTE, :BYTE { WriteNoFence8(rcx, dl) }
WriteUCharRaw		proto :ptr BYTE, :BYTE { WriteRaw8(rcx, dl) }
ReadUShortAcquire	proto :ptr WORD { ReadAcquire16(rcx) }
ReadUShortNoFence	proto :ptr WORD { ReadNoFence16(rcx) }
ReadUShortRaw		proto :ptr WORD { ReadRaw16(rcx) }
WriteUShortRelease	proto :ptr WORD, :WORD { WriteRelease16(rcx, dx) }
WriteUShortNoFence	proto :ptr WORD, :WORD { WriteNoFence16(rcx, dx) }
WriteUShortRaw		proto :ptr WORD, :WORD { WriteRaw16(rcx, dx) }
ReadULongAcquire	proto :ptr DWORD { ReadAcquire(rcx) }
ReadULongNoFence	proto :ptr DWORD { ReadNoFence(rcx) }
ReadULongRaw		proto :ptr DWORD { mov eax,[rcx] }
WriteULongRelease	proto :ptr DWORD, :DWORD { WriteRelease(rcx, edx) }
WriteULongNoFence	proto :ptr DWORD, :DWORD { WriteNoFence(rcx, edx) }
WriteULongRaw		proto :ptr DWORD, :DWORD { mov [rcx],edx }
ReadULong64Acquire	proto :ptr DWORD64 { ReadAcquire64(rcx) }
ReadULong64NoFence	proto :ptr DWORD64 { ReadNoFence64(rcx) }
ReadULong64Raw		proto :ptr DWORD64 { ReadRaw64(rcx) }
WriteULong64Release	proto :ptr DWORD64, :DWORD64 { WriteRelease64(rcx, rdx) }
WriteULong64NoFence	proto :ptr DWORD64, :DWORD64 { WriteNoFence64(rcx, rdx) }
WriteULong64Raw		proto :ptr DWORD64, :DWORD64 { WriteRaw64(rcx, rdx) }

ReadSizeTAcquire	equ <ReadULongPtrAcquire>
ReadSizeTNoFence	equ <ReadULongPtrNoFence>
ReadSizeTRaw		equ <ReadULongPtrRaw>
WriteSizeTRelease	equ <WriteULongPtrRelease>
WriteSizeTNoFence	equ <WriteULongPtrNoFence>
WriteSizeTRaw		equ <WriteULongPtrRaw>

endif

ifdef _WIN64

ReadPointerAcquire	proto :ptr { ReadAcquire64(rcx) }
ReadPointerNoFence	proto :ptr { ReadNoFence64(rcx) }
ReadPointerRaw		proto :ptr { ReadRaw64(rcx) }
WritePointerRelease	proto :ptr, :ptr { WriteRelease64(rcx, rdx) }
WritePointerNoFence	proto :ptr, :ptr { WriteNoFence64(rcx, rdx) }
WritePointerRaw		proto :ptr, :ptr { WriteRaw64(rcx, rdx) }

ReadLongPtrAcquire	equ <ReadAcquire64>
ReadLongPtrNoFence	equ <ReadNoFence64>
ReadLongPtrRaw		equ <ReadRaw64>
WriteLongPtrRelease	equ <WriteRelease64>
WriteLongPtrNoFence	equ <WriteNoFence64>
WriteLongPtrRaw		equ <WriteRaw64>
ReadULongPtrAcquire	equ <ReadULong64Acquire>
ReadULongPtrNoFence	equ <ReadULong64NoFence>
ReadULongPtrRaw		equ <ReadULong64Raw>
WriteULongPtrRelease	equ <WriteULong64Release>
WriteULongPtrNoFence	equ <WriteULong64NoFence>
WriteULongPtrRaw	equ <WriteULong64Raw>

endif ; _WIN64

WOW64_CONTEXT_i386	equ 0x00010000
WOW64_CONTEXT_i486	equ 0x00010000

WOW64_CONTEXT_CONTROL	equ WOW64_CONTEXT_i386 OR 0x00000001
WOW64_CONTEXT_INTEGER	equ WOW64_CONTEXT_i386 OR 0x00000002
WOW64_CONTEXT_SEGMENTS	equ WOW64_CONTEXT_i386 OR 0x00000004
WOW64_CONTEXT_FLOATING_POINT equ WOW64_CONTEXT_i386 OR 0x00000008
WOW64_CONTEXT_DEBUG_REGISTERS equ WOW64_CONTEXT_i386 OR 0x00000010
WOW64_CONTEXT_EXTENDED_REGISTERS equ WOW64_CONTEXT_i386 OR 0x00000020

WOW64_CONTEXT_FULL	equ WOW64_CONTEXT_CONTROL OR WOW64_CONTEXT_INTEGER OR \
			    WOW64_CONTEXT_SEGMENTS
WOW64_CONTEXT_ALL	equ WOW64_CONTEXT_CONTROL OR WOW64_CONTEXT_INTEGER OR \
			    WOW64_CONTEXT_SEGMENTS OR WOW64_CONTEXT_DEBUG_REGISTERS OR \
			    WOW64_CONTEXT_FLOATING_POINT
WOW64_CONTEXT_XSTATE	equ WOW64_CONTEXT_i386 OR 0x00000040

;endif


WOW64_SIZE_OF_80387_REGISTERS equ 80

WOW64_MAXIMUM_SUPPORTED_EXTENSION equ 512

WOW64_FLOATING_SAVE_AREA  STRUC
ControlWord		dd ?
StatusWord		dd ?
TagWord			dd ?
ErrorOffset		dd ?
ErrorSelector		dd ?
DataOffset		dd ?
DataSelector		dd ?
RegisterArea		db WOW64_SIZE_OF_80387_REGISTERS dup(?)
Cr0NpxState		dd ?
WOW64_FLOATING_SAVE_AREA ENDS
PWOW64_FLOATING_SAVE_AREA typedef ptr WOW64_FLOATING_SAVE_AREA

.pragma pack(push, 4)

WOW64_CONTEXT		STRUC
ContextFlags		dd ?
_Dr0			dd ?
_Dr1			dd ?
_Dr2			dd ?
_Dr3			dd ?
_Dr6			dd ?
_Dr7			dd ?
FloatSave		WOW64_FLOATING_SAVE_AREA <>
SegGs			dd ?
SegFs			dd ?
SegEs			dd ?
SegDs			dd ?
_Edi			dd ?
_Esi			dd ?
_Ebx			dd ?
_Edx			dd ?
_Ecx			dd ?
_Eax			dd ?
_Ebp			dd ?
_Eip			dd ?
SegCs			dd ?
EFlags			dd ?
_Esp			dd ?
SegSs			dd ?
ExtendedRegisters	db WOW64_MAXIMUM_SUPPORTED_EXTENSION dup(?)
WOW64_CONTEXT		ENDS
PWOW64_CONTEXT		typedef ptr WOW64_CONTEXT

.pragma pack(pop)

WOW64_LDT_ENTRY		STRUC
LimitLow		dw ?
BaseLow			dw ?
UNION ;HighWord
 STRUC Bytes
  BaseMid		db ?
  Flags1		db ?	; Declare as bytes to avoid alignment
  Flags2		db ?	; Problems.
  BaseHi		db ?
 ENDS
 RECORD Bits
  BaseMid		dd : 8 ?
  Type			dd : 5 ?
  Dpl			dd : 2 ?
  Pres			dd : 1 ?
  LimitHi		dd : 4 ?
  Sys			dd : 1 ?
  Reserved_0		dd : 1 ?
  Default_Big		dd : 1 ?
  Granularity		dd : 1 ?
  BaseHi		dd : 8 ?
 ENDS
ENDS
WOW64_LDT_ENTRY		ENDS
PWOW64_LDT_ENTRY	typedef ptr WOW64_LDT_ENTRY

WOW64_DESCRIPTOR_TABLE_ENTRY  STRUC
Selector		dd ?
Descriptor		WOW64_LDT_ENTRY <>
WOW64_DESCRIPTOR_TABLE_ENTRY ENDS
PWOW64_DESCRIPTOR_TABLE_ENTRY typedef ptr WOW64_DESCRIPTOR_TABLE_ENTRY


EXCEPTION_MAXIMUM_PARAMETERS	equ 15	; maximum number of exception parameters

EXCEPTION_NONCONTINUABLE	equ 0x1 ; Noncontinuable exception
EXCEPTION_UNWINDING		equ 0x2 ; Unwind is in progress
EXCEPTION_EXIT_UNWIND		equ 0x4 ; Exit unwind is in progress
EXCEPTION_STACK_INVALID		equ 0x8 ; Stack out of limits or unaligned
EXCEPTION_NESTED_CALL		equ 0x10 ; Nested exception handler call
EXCEPTION_TARGET_UNWIND		equ 0x20 ; Target unwind in progress
EXCEPTION_COLLIDED_UNWIND	equ 0x40 ; Collided exception handler call

EXCEPTION_UNWIND		equ EXCEPTION_UNWINDING or \
				    EXCEPTION_EXIT_UNWIND or \
				    EXCEPTION_TARGET_UNWIND or \
				    EXCEPTION_COLLIDED_UNWIND

IS_UNWINDING macro Flag
	exitm<(Flag & EXCEPTION_UNWIND)>
	endm
IS_DISPATCHING macro Flag
	exitm<!!(Flag & EXCEPTION_UNWIND)>
	endm
IS_TARGET_UNWIND macro Flag
	exitm<(Flag & EXCEPTION_TARGET_UNWIND)>
	endm

EXCEPTION_RECORD32	STRUC
ExceptionCode		dd ?
ExceptionFlags		dd ?
ExceptionRecord		dd ?
ExceptionAddress	dd ?
NumberParameters	dd ?
ExceptionInformation	dd EXCEPTION_MAXIMUM_PARAMETERS dup(?)
EXCEPTION_RECORD32	ENDS
PEXCEPTION_RECORD32	typedef ptr EXCEPTION_RECORD32

EXCEPTION_RECORD64	STRUC
ExceptionCode		dd ?
ExceptionFlags		dd ?
ExceptionRecord		DWORD64 ?
ExceptionAddress	DWORD64 ?
NumberParameters	dd ?
__unusedAlignment	dd ?
ExceptionInformation	DWORD64 EXCEPTION_MAXIMUM_PARAMETERS dup(?)
EXCEPTION_RECORD64	ENDS
PEXCEPTION_RECORD64	typedef ptr EXCEPTION_RECORD64


EXCEPTION_POINTERS	STRUC
ExceptionRecord		PEXCEPTION_RECORD ?
ContextRecord		PCONTEXT ?
EXCEPTION_POINTERS	ENDS
PEXCEPTION_POINTERS	typedef ptr EXCEPTION_POINTERS

EXCEPTION_REGISTRATION	STRUC SIZE_T
prev			SIZE_T ?
handler			SIZE_T ?
EXCEPTION_REGISTRATION	ENDS
PEXCEPTION_REGISTRATION typedef ptr EXCEPTION_REGISTRATION

;VOID
RtlUnwind proto WINAPI \
	   TargetFrame: PVOID,
	      TargetIp: PVOID,
       ExceptionRecord: PEXCEPTION_RECORD,
	   ReturnValue: PVOID

ifdef _IA64_
;VOID
RtlUnwind2 proto WINAPI \
	   TargetFrame: FRAME_POINTERS,
	      TargetIp: PVOID,
       ExceptionRecord: PEXCEPTION_RECORD,
	   ReturnValue: PVOID,
	 ContextRecord: PCONTEXT
endif

ifdef _AMD64_
;VOID
RtlUnwindEx proto WINAPI \
	   TargetFrame: PVOID,
	      TargetIp: PVOID,
       ExceptionRecord: PEXCEPTION_RECORD,
	   ReturnValue: PVOID,
	 ContextRecord: PCONTEXT,
	  HistoryTable: PUNWIND_HISTORY_TABLE
elseifdef _IA64_
;VOID
RtlUnwindEx proto WINAPI \
	   TargetFrame: FRAME_POINTERS,
	      TargetIp: PVOID,
       ExceptionRecord: PEXCEPTION_RECORD,
	   ReturnValue: PVOID,
	 ContextRecord: PCONTEXT,
	  HistoryTable: PUNWIND_HISTORY_TABLE
endif

PACCESS_TOKEN		typedef ptr
PSECURITY_DESCRIPTOR	typedef ptr
PSID			typedef ptr
PCLAIMS_BLOB		typedef ptr

ACCESS_MASK		typedef DWORD
PACCESS_MASK		typedef PTR ACCESS_MASK

DELETE			equ 0x00010000
READ_CONTROL		equ 0x00020000
WRITE_DAC		equ 0x00040000
WRITE_OWNER		equ 0x00080000
SYNCHRONIZE		equ 0x00100000

STANDARD_RIGHTS_REQUIRED equ 0x000F0000

STANDARD_RIGHTS_READ	equ READ_CONTROL
STANDARD_RIGHTS_WRITE	equ READ_CONTROL
STANDARD_RIGHTS_EXECUTE equ READ_CONTROL

STANDARD_RIGHTS_ALL	equ 0x001F0000
SPECIFIC_RIGHTS_ALL	equ 0x0000FFFF

ACCESS_SYSTEM_SECURITY	equ 0x01000000

MAXIMUM_ALLOWED equ 0x02000000

GENERIC_READ	equ 0x80000000
GENERIC_WRITE	equ 0x40000000
GENERIC_EXECUTE equ 0x20000000
GENERIC_ALL	equ 0x10000000

GENERIC_MAPPING STRUC
GenericRead	ACCESS_MASK ?
GenericWrite	ACCESS_MASK ?
GenericExecute	ACCESS_MASK ?
GenericAll	ACCESS_MASK ?
GENERIC_MAPPING ENDS

PGENERIC_MAPPING typedef PTR GENERIC_MAPPING

.pragma pack(push, 4)

LUID_AND_ATTRIBUTES STRUC
Luid		LUID <>
Attributes	dd ?
LUID_AND_ATTRIBUTES ENDS
PLUID_AND_ATTRIBUTES typedef ptr LUID_AND_ATTRIBUTES
LUID_AND_ATTRIBUTES_ARRAY typedef LUID_AND_ATTRIBUTES
PLUID_AND_ATTRIBUTES_ARRAY typedef ptr LUID_AND_ATTRIBUTES_ARRAY

.pragma pack(pop)

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
ifdef MIDL_PASS
;SubAuthority		dd [SubAuthorityCount] dup(?)
SubAuthority		dd ANYSIZE_ARRAY dup(?)
else
SubAuthority		dd ANYSIZE_ARRAY dup(?)
endif
SID			ENDS
PISID			typedef ptr SID
endif

ifndef MIDL_PASS
SECURITY_MAX_SID_SIZE	equ (SID - DWORD + (SID_MAX_SUB_AUTHORITIES * DWORD))
endif

SID_REVISION		equ 1	; Current revision level
SID_MAX_SUB_AUTHORITIES equ 15
SID_RECOMMENDED_SUB_AUTHORITIES equ 1	; Will change to around 6

.enum SID_NAME_USE {
    SidTypeUser = 1,
    SidTypeGroup,
    SidTypeDomain,
    SidTypeAlias,
    SidTypeWellKnownGroup,
    SidTypeDeletedAccount,
    SidTypeInvalid,
    SidTypeUnknown,
    SidTypeComputer }
    PSID_NAME_USE	typedef ptr SID_NAME_USE

SID_AND_ATTRIBUTES	STRUC
ifdef MIDL_PASS
Sid			PISID ?
else
Sid			PSID ?
endif
Attributes		dd ?
SID_AND_ATTRIBUTES	ENDS
PSID_AND_ATTRIBUTES	typedef ptr SID_AND_ATTRIBUTES

SID_AND_ATTRIBUTES_ARRAY STRUC
SID_AND_ATTRIBUTES ANYSIZE_ARRAY dup(<>)
SID_AND_ATTRIBUTES_ARRAY ENDS
;SID_AND_ATTRIBUTES_ARRAY  typedef SID_AND_ATTRIBUTES;[ANYSIZE_ARRAY]
PSID_AND_ATTRIBUTES_ARRAY typedef PTR SID_AND_ATTRIBUTES_ARRAY

SID_HASH_SIZE		equ 32
SID_HASH_ENTRY		typedef ULONG_PTR
PSID_HASH_ENTRY		typedef ptr ULONG_PTR

SID_AND_ATTRIBUTES_HASH STRUC
SidCount		dd ?
SidAttr			PSID_AND_ATTRIBUTES ?
_Hash			SID_HASH_ENTRY SID_HASH_SIZE dup(?)
SID_AND_ATTRIBUTES_HASH ENDS
PSID_AND_ATTRIBUTES_HASH typedef ptr SID_AND_ATTRIBUTES_HASH


SECURITY_NULL_SID_AUTHORITY	  equ <{0,0,0,0,0,0}>
SECURITY_WORLD_SID_AUTHORITY	  equ <{0,0,0,0,0,1}>
SECURITY_LOCAL_SID_AUTHORITY	  equ <{0,0,0,0,0,2}>
SECURITY_CREATOR_SID_AUTHORITY	  equ <{0,0,0,0,0,3}>
SECURITY_NON_UNIQUE_AUTHORITY	  equ <{0,0,0,0,0,4}>
SECURITY_RESOURCE_MANAGER_AUTHORITY equ <{0,0,0,0,0,9}>

SECURITY_NULL_RID		  equ 0x00000000
SECURITY_WORLD_RID		  equ 0x00000000
SECURITY_LOCAL_RID		  equ 0X00000000

SECURITY_CREATOR_OWNER_RID	  equ 0x00000000
SECURITY_CREATOR_GROUP_RID	  equ 0x00000001
SECURITY_LOCAL_LOGON_RID	  equ 0x00000001

SECURITY_CREATOR_OWNER_SERVER_RID equ 0x00000002
SECURITY_CREATOR_GROUP_SERVER_RID equ 0x00000003
SECURITY_CREATOR_OWNER_RIGHTS_RID equ 0x00000004

SECURITY_NT_AUTHORITY		equ <{0,0,0,0,0,5}>

SECURITY_DIALUP_RID		equ 0x00000001
SECURITY_NETWORK_RID		equ 0x00000002
SECURITY_BATCH_RID		equ 0x00000003
SECURITY_INTERACTIVE_RID	equ 0x00000004
SECURITY_LOGON_IDS_RID		equ 0x00000005
SECURITY_LOGON_IDS_RID_COUNT	equ 3
SECURITY_SERVICE_RID		equ 0x00000006
SECURITY_ANONYMOUS_LOGON_RID	equ 0x00000007
SECURITY_PROXY_RID		equ 0x00000008
SECURITY_ENTERPRISE_CONTROLLERS_RID equ 0x00000009
SECURITY_SERVER_LOGON_RID	equ SECURITY_ENTERPRISE_CONTROLLERS_RID
SECURITY_PRINCIPAL_SELF_RID	equ 0x0000000A
SECURITY_AUTHENTICATED_USER_RID equ 0x0000000B
SECURITY_RESTRICTED_CODE_RID	equ 0x0000000C
SECURITY_TERMINAL_SERVER_RID	equ 0x0000000D
SECURITY_REMOTE_LOGON_RID	equ 0x0000000E
SECURITY_THIS_ORGANIZATION_RID	equ 0x0000000F
SECURITY_IUSER_RID		equ 0x00000011
SECURITY_LOCAL_SYSTEM_RID	equ 0x00000012
SECURITY_NT_NON_UNIQUE		equ 0x00000015
SECURITY_LOCAL_SERVICE_RID	equ 0x00000013
SECURITY_NETWORK_SERVICE_RID	equ 0x00000014
SECURITY_NT_NON_UNIQUE		equ 0x00000015
SECURITY_NT_NON_UNIQUE_SUB_AUTH_COUNT equ 3
SECURITY_ENTERPRISE_READONLY_CONTROLLERS_RID equ 0x00000016
SECURITY_BUILTIN_DOMAIN_RID	equ 0x00000020
SECURITY_WRITE_RESTRICTED_CODE_RID equ 0x00000021


SECURITY_PACKAGE_BASE_RID	equ 0x00000040
SECURITY_PACKAGE_RID_COUNT	equ 2
SECURITY_PACKAGE_NTLM_RID	equ 0x0000000A
SECURITY_PACKAGE_SCHANNEL_RID	equ 0x0000000E
SECURITY_PACKAGE_DIGEST_RID	equ 0x00000015

SECURITY_CRED_TYPE_BASE_RID	equ 0x00000041
SECURITY_CRED_TYPE_RID_COUNT	equ 2
SECURITY_CRED_TYPE_THIS_ORG_CERT_RID equ 0x00000001

SECURITY_MIN_BASE_RID		equ 0x00000050
SECURITY_SERVICE_ID_BASE_RID	equ 0x00000050
SECURITY_SERVICE_ID_RID_COUNT	equ 6

SECURITY_RESERVED_ID_BASE_RID	equ 0x00000051
SECURITY_APPPOOL_ID_BASE_RID	equ 0x00000052
SECURITY_APPPOOL_ID_RID_COUNT	equ 6

SECURITY_VIRTUALSERVER_ID_BASE_RID equ 0x00000053
SECURITY_VIRTUALSERVER_ID_RID_COUNT equ 6

SECURITY_USERMODEDRIVERHOST_ID_BASE_RID equ 0x00000054
SECURITY_USERMODEDRIVERHOST_ID_RID_COUNT equ 6

SECURITY_CLOUD_INFRASTRUCTURE_SERVICES_ID_BASE_RID equ 0x00000055
SECURITY_CLOUD_INFRASTRUCTURE_SERVICES_ID_RID_COUNT equ 6

SECURITY_WMIHOST_ID_BASE_RID	equ 0x00000056
SECURITY_WMIHOST_ID_RID_COUNT	equ 6

SECURITY_TASK_ID_BASE_RID	equ 0x00000057
SECURITY_NFS_ID_BASE_RID	equ 0x00000058
SECURITY_COM_ID_BASE_RID	equ 0x00000059

DOMAIN_USER_RID_ADMIN	       equ 0x000001F4
DOMAIN_USER_RID_GUEST	       equ 0x000001F5
DOMAIN_USER_RID_KRBTGT	       equ 0x000001F6
DOMAIN_USER_RID_MAX	       equ 0x000003E7

DOMAIN_GROUP_RID_ADMINS	       equ 0x00000200
DOMAIN_GROUP_RID_USERS	       equ 0x00000201
DOMAIN_GROUP_RID_GUESTS	       equ 0x00000202
DOMAIN_GROUP_RID_COMPUTERS     equ 0x00000203
DOMAIN_GROUP_RID_CONTROLLERS   equ 0x00000204
DOMAIN_GROUP_RID_CERT_ADMINS   equ 0x00000205
DOMAIN_GROUP_RID_SCHEMA_ADMINS equ 0x00000206
DOMAIN_GROUP_RID_ENTERPRISE_ADMINS equ 0x00000207
DOMAIN_GROUP_RID_POLICY_ADMINS equ 0x00000208
DOMAIN_GROUP_RID_READONLY_CONTROLLERS equ 0x00000209

DOMAIN_ALIAS_RID_ADMINS	       equ 0x00000220
DOMAIN_ALIAS_RID_USERS	       equ 0x00000221
DOMAIN_ALIAS_RID_GUESTS	       equ 0x00000222
DOMAIN_ALIAS_RID_POWER_USERS   equ 0x00000223
DOMAIN_ALIAS_RID_ACCOUNT_OPS   equ 0x00000224
DOMAIN_ALIAS_RID_SYSTEM_OPS    equ 0x00000225
DOMAIN_ALIAS_RID_PRINT_OPS     equ 0x00000226
DOMAIN_ALIAS_RID_BACKUP_OPS    equ 0x00000227
DOMAIN_ALIAS_RID_REPLICATOR    equ 0x00000228

DOMAIN_ALIAS_RID_RAS_SERVERS			equ 0x00000229
DOMAIN_ALIAS_RID_PREW2KCOMPACCESS		equ 0x0000022A
DOMAIN_ALIAS_RID_REMOTE_DESKTOP_USERS		equ 0x0000022B
DOMAIN_ALIAS_RID_NETWORK_CONFIGURATION_OPS	equ 0x0000022C
DOMAIN_ALIAS_RID_INCOMING_FOREST_TRUST_BUILDERS equ 0x0000022D

DOMAIN_ALIAS_RID_MONITORING_USERS		equ 0x0000022E
DOMAIN_ALIAS_RID_LOGGING_USERS			equ 0x0000022F
DOMAIN_ALIAS_RID_AUTHORIZATIONACCESS		equ 0x00000230
DOMAIN_ALIAS_RID_TS_LICENSE_SERVERS		equ 0x00000231
DOMAIN_ALIAS_RID_DCOM_USERS			equ 0x00000232
DOMAIN_ALIAS_RID_IUSERS				equ 0x00000238
DOMAIN_ALIAS_RID_CRYPTO_OPERATORS		equ 0x00000239
DOMAIN_ALIAS_RID_CACHEABLE_PRINCIPALS_GROUP	equ 0x0000023B
DOMAIN_ALIAS_RID_NON_CACHEABLE_PRINCIPALS_GROUP equ 0x0000023C
DOMAIN_ALIAS_RID_EVENT_LOG_READERS_GROUP	equ 0x0000023D
DOMAIN_ALIAS_RID_CERTSVC_DCOM_ACCESS_GROUP	equ 0x0000023E

SECURITY_MANDATORY_LABEL_AUTHORITY	    equ <{0,0,0,0,0,16}>
SECURITY_MANDATORY_UNTRUSTED_RID	    equ 0x00000000
SECURITY_MANDATORY_LOW_RID		    equ 0x00001000
SECURITY_MANDATORY_MEDIUM_RID		    equ 0x00002000
SECURITY_MANDATORY_MEDIUM_PLUS_RID	    equ (SECURITY_MANDATORY_MEDIUM_RID + 0x100)
SECURITY_MANDATORY_HIGH_RID		    equ 0x00003000
SECURITY_MANDATORY_SYSTEM_RID		    equ 0x00004000
SECURITY_MANDATORY_PROTECTED_PROCESS_RID    equ 0x00005000

SECURITY_MANDATORY_MAXIMUM_USER_RID equ SECURITY_MANDATORY_SYSTEM_RID

MANDATORY_LEVEL_TO_MANDATORY_RID macro IL
	exitm<(IL * 0x1000)>
	endm

.enum WELL_KNOWN_SID_TYPE {
    WinNullSid					= 0,
    WinWorldSid					= 1,
    WinLocalSid					= 2,
    WinCreatorOwnerSid				= 3,
    WinCreatorGroupSid				= 4,
    WinCreatorOwnerServerSid			= 5,
    WinCreatorGroupServerSid			= 6,
    WinNtAuthoritySid				= 7,
    WinDialupSid				= 8,
    WinNetworkSid				= 9,
    WinBatchSid					= 10,
    WinInteractiveSid				= 11,
    WinServiceSid				= 12,
    WinAnonymousSid				= 13,
    WinProxySid					= 14,
    WinEnterpriseControllersSid			= 15,
    WinSelfSid					= 16,
    WinAuthenticatedUserSid			= 17,
    WinRestrictedCodeSid			= 18,
    WinTerminalServerSid			= 19,
    WinRemoteLogonIdSid				= 20,
    WinLogonIdsSid				= 21,
    WinLocalSystemSid				= 22,
    WinLocalServiceSid				= 23,
    WinNetworkServiceSid			= 24,
    WinBuiltinDomainSid				= 25,
    WinBuiltinAdministratorsSid			= 26,
    WinBuiltinUsersSid				= 27,
    WinBuiltinGuestsSid				= 28,
    WinBuiltinPowerUsersSid			= 29,
    WinBuiltinAccountOperatorsSid		= 30,
    WinBuiltinSystemOperatorsSid		= 31,
    WinBuiltinPrintOperatorsSid			= 32,
    WinBuiltinBackupOperatorsSid		= 33,
    WinBuiltinReplicatorSid			= 34,
    WinBuiltinPreWindows2000CompatibleAccessSid = 35,
    WinBuiltinRemoteDesktopUsersSid		= 36,
    WinBuiltinNetworkConfigurationOperatorsSid	= 37,
    WinAccountAdministratorSid			= 38,
    WinAccountGuestSid				= 39,
    WinAccountKrbtgtSid				= 40,
    WinAccountDomainAdminsSid			= 41,
    WinAccountDomainUsersSid			= 42,
    WinAccountDomainGuestsSid			= 43,
    WinAccountComputersSid			= 44,
    WinAccountControllersSid			= 45,
    WinAccountCertAdminsSid			= 46,
    WinAccountSchemaAdminsSid			= 47,
    WinAccountEnterpriseAdminsSid		= 48,
    WinAccountPolicyAdminsSid			= 49,
    WinAccountRasAndIasServersSid		= 50,
    WinNTLMAuthenticationSid			= 51,
    WinDigestAuthenticationSid			= 52,
    WinSChannelAuthenticationSid		= 53,
    WinThisOrganizationSid			= 54,
    WinOtherOrganizationSid			= 55,
    WinBuiltinIncomingForestTrustBuildersSid	= 56,
    WinBuiltinPerfMonitoringUsersSid		= 57,
    WinBuiltinPerfLoggingUsersSid		= 58,
    WinBuiltinAuthorizationAccessSid		= 59,
    WinBuiltinTerminalServerLicenseServersSid	= 60,
    WinBuiltinDCOMUsersSid			= 61,
    WinBuiltinIUsersSid				= 62,
    WinIUserSid					= 63,
    WinBuiltinCryptoOperatorsSid		= 64,
    WinUntrustedLabelSid			= 65,
    WinLowLabelSid				= 66,
    WinMediumLabelSid				= 67,
    WinHighLabelSid				= 68,
    WinSystemLabelSid				= 69,
    WinWriteRestrictedCodeSid			= 70,
    WinCreatorOwnerRightsSid			= 71,
    WinCacheablePrincipalsGroupSid		= 72,
    WinNonCacheablePrincipalsGroupSid		= 73,
    WinEnterpriseReadonlyControllersSid		= 74,
    WinAccountReadonlyControllersSid		= 75,
    WinBuiltinEventLogReadersGroup		= 76,
    WinNewEnterpriseReadonlyControllersSid	= 77,
    WinBuiltinCertSvcDComAccessGroup		= 78,
    WinMediumPlusLabelSid			= 79,
    WinLocalLogonSid				= 80,
    WinConsoleLogonSid				= 81,
    WinThisOrganizationCertificateSid		= 82,
    }


SYSTEM_LUID			equ <{ 0x3E7, 0x0 }>
ANONYMOUS_LOGON_LUID		equ <{ 0x3e6, 0x0 }>
LOCALSERVICE_LUID		equ <{ 0x3e5, 0x0 }>
NETWORKSERVICE_LUID		equ <{ 0x3e4, 0x0 }>
IUSER_LUID			equ <{ 0x3e3, 0x0 }>

SE_GROUP_MANDATORY		equ 0x00000001
SE_GROUP_ENABLED_BY_DEFAULT	equ 0x00000002
SE_GROUP_ENABLED		equ 0x00000004
SE_GROUP_OWNER			equ 0x00000008
SE_GROUP_USE_FOR_DENY_ONLY	equ 0x00000010

SE_GROUP_INTEGRITY		equ 0x00000020
SE_GROUP_INTEGRITY_ENABLED	equ 0x00000040
SE_GROUP_LOGON_ID		equ 0xC0000000
SE_GROUP_RESOURCE		equ 0x20000000

SE_GROUP_VALID_ATTRIBUTES	equ SE_GROUP_MANDATORY		OR \
				    SE_GROUP_ENABLED_BY_DEFAULT OR \
				    SE_GROUP_ENABLED		OR \
				    SE_GROUP_OWNER		OR \
				    SE_GROUP_USE_FOR_DENY_ONLY	OR \
				    SE_GROUP_LOGON_ID		OR \
				    SE_GROUP_RESOURCE		OR \
				    SE_GROUP_INTEGRITY		OR \
				    SE_GROUP_INTEGRITY_ENABLED


ACL_REVISION	 equ 2
ACL_REVISION_DS	 equ 4

ACL_REVISION1		equ 1
MIN_ACL_REVISION	equ ACL_REVISION2
ACL_REVISION2		equ 2
ACL_REVISION3		equ 3
ACL_REVISION4		equ 4
MAX_ACL_REVISION	equ ACL_REVISION4

ACL		STRUC
AclRevision	db ?
Sbz1		db ?
AclSize		dw ?
AceCount	dw ?
Sbz2		dw ?
ACL		ENDS
PACL		typedef PTR ACL

ACE_HEADER	STRUC
AceType		db ?
AceFlags	db ?
AceSize		dw ?
ACE_HEADER	ENDS
PACE_HEADER	typedef PTR ACE_HEADER

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

ACCESS_ALLOWED_CALLBACK_ACE_TYPE	equ 0x9
ACCESS_DENIED_CALLBACK_ACE_TYPE		equ 0xA
ACCESS_ALLOWED_CALLBACK_OBJECT_ACE_TYPE equ 0xB
ACCESS_DENIED_CALLBACK_OBJECT_ACE_TYPE	equ 0xC
SYSTEM_AUDIT_CALLBACK_ACE_TYPE		equ 0xD
SYSTEM_ALARM_CALLBACK_ACE_TYPE		equ 0xE
SYSTEM_AUDIT_CALLBACK_OBJECT_ACE_TYPE	equ 0xF
SYSTEM_ALARM_CALLBACK_OBJECT_ACE_TYPE	equ 0x10

SYSTEM_MANDATORY_LABEL_ACE_TYPE		equ 0x11
ACCESS_MAX_MS_V5_ACE_TYPE		equ 0x11

OBJECT_INHERIT_ACE		  equ 0x1
CONTAINER_INHERIT_ACE		  equ 0x2
NO_PROPAGATE_INHERIT_ACE	  equ 0x4
INHERIT_ONLY_ACE		  equ 0x8
INHERITED_ACE			  equ 0x10
VALID_INHERIT_FLAGS		  equ 0x1F

SUCCESSFUL_ACCESS_ACE_FLAG	 equ 0x40
FAILED_ACCESS_ACE_FLAG		 equ 0x80

ACCESS_ALLOWED_ACE	STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
ACCESS_ALLOWED_ACE	ENDS
PACCESS_ALLOWED_ACE	typedef PTR ACCESS_ALLOWED_ACE

ACCESS_DENIED_ACE	STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
ACCESS_DENIED_ACE	ENDS
PACCESS_DENIED_ACE	typedef PTR ACCESS_DENIED_ACE

SYSTEM_AUDIT_ACE	STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
SYSTEM_AUDIT_ACE	ENDS
PSYSTEM_AUDIT_ACE	typedef PTR SYSTEM_AUDIT_ACE

SYSTEM_ALARM_ACE	STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
SYSTEM_ALARM_ACE	ENDS
PSYSTEM_ALARM_ACE	typedef PTR SYSTEM_ALARM_ACE

SYSTEM_MANDATORY_LABEL_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
SYSTEM_MANDATORY_LABEL_ACE ENDS
PSYSTEM_MANDATORY_LABEL_ACE typedef ptr SYSTEM_MANDATORY_LABEL_ACE

SYSTEM_MANDATORY_LABEL_NO_WRITE_UP   equ 0x1
SYSTEM_MANDATORY_LABEL_NO_READ_UP    equ 0x2
SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP equ 0x4

SYSTEM_MANDATORY_LABEL_VALID_MASK equ SYSTEM_MANDATORY_LABEL_NO_WRITE_UP OR \
				      SYSTEM_MANDATORY_LABEL_NO_READ_UP	 OR \
				      SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP

ACCESS_ALLOWED_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
ACCESS_ALLOWED_OBJECT_ACE ENDS
PACCESS_ALLOWED_OBJECT_ACE TYPEDEF PTR ACCESS_ALLOWED_OBJECT_ACE

ACCESS_DENIED_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
ACCESS_DENIED_OBJECT_ACE ENDS
PACCESS_DENIED_OBJECT_ACE TYPEDEF PTR ACCESS_DENIED_OBJECT_ACE

SYSTEM_AUDIT_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
SYSTEM_AUDIT_OBJECT_ACE ENDS
PSYSTEM_AUDIT_OBJECT_ACE TYPEDEF PTR SYSTEM_AUDIT_OBJECT_ACE

SYSTEM_ALARM_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
SYSTEM_ALARM_OBJECT_ACE ENDS
PSYSTEM_ALARM_OBJECT_ACE TYPEDEF PTR SYSTEM_ALARM_OBJECT_ACE


ACCESS_ALLOWED_CALLBACK_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
ACCESS_ALLOWED_CALLBACK_ACE ENDS
PACCESS_ALLOWED_CALLBACK_ACE typedef ptr ACCESS_ALLOWED_CALLBACK_ACE

ACCESS_DENIED_CALLBACK_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
ACCESS_DENIED_CALLBACK_ACE ENDS
PACCESS_DENIED_CALLBACK_ACE typedef ptr ACCESS_DENIED_CALLBACK_ACE

SYSTEM_AUDIT_CALLBACK_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
SYSTEM_AUDIT_CALLBACK_ACE ENDS
PSYSTEM_AUDIT_CALLBACK_ACE typedef ptr SYSTEM_AUDIT_CALLBACK_ACE

SYSTEM_ALARM_CALLBACK_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
SidStart		dd ?
SYSTEM_ALARM_CALLBACK_ACE ENDS
PSYSTEM_ALARM_CALLBACK_ACE typedef ptr SYSTEM_ALARM_CALLBACK_ACE

ACCESS_ALLOWED_CALLBACK_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
ACCESS_ALLOWED_CALLBACK_OBJECT_ACE ENDS
PACCESS_ALLOWED_CALLBACK_OBJECT_ACE typedef ptr ACCESS_ALLOWED_CALLBACK_OBJECT_ACE

ACCESS_DENIED_CALLBACK_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
ACCESS_DENIED_CALLBACK_OBJECT_ACE ENDS
PACCESS_DENIED_CALLBACK_OBJECT_ACE typedef ptr ACCESS_DENIED_CALLBACK_OBJECT_ACE

SYSTEM_AUDIT_CALLBACK_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
SYSTEM_AUDIT_CALLBACK_OBJECT_ACE ENDS
PSYSTEM_AUDIT_CALLBACK_OBJECT_ACE typedef ptr SYSTEM_AUDIT_CALLBACK_OBJECT_ACE

SYSTEM_ALARM_CALLBACK_OBJECT_ACE STRUC
Header			ACE_HEADER <>
Mask			ACCESS_MASK ?
Flags			dd ?
ObjectType		GUID <>
InheritedObjectType	GUID <>
SidStart		dd ?
SYSTEM_ALARM_CALLBACK_OBJECT_ACE ENDS
PSYSTEM_ALARM_CALLBACK_OBJECT_ACE typedef ptr SYSTEM_ALARM_CALLBACK_OBJECT_ACE

ACE_OBJECT_TYPE_PRESENT		  equ 0x1
ACE_INHERITED_OBJECT_TYPE_PRESENT equ 0x2

ACL_INFORMATION_CLASS	typedef SDWORD

AclRevisionInformation	equ 1
AclSizeInformation	equ 2

ACL_REVISION_INFORMATION STRUC
AclRevision		dd ?
ACL_REVISION_INFORMATION ENDS
PACL_REVISION_INFORMATION typedef ptr ACL_REVISION_INFORMATION

ACL_SIZE_INFORMATION	STRUC
AceCount		dd ?
AclBytesInUse		dd ?
AclBytesFree		dd ?
ACL_SIZE_INFORMATION	ENDS
PACL_SIZE_INFORMATION	typedef ptr ACL_SIZE_INFORMATION

SECURITY_DESCRIPTOR_REVISION	 equ 1
SECURITY_DESCRIPTOR_REVISION1	 equ 1

SECURITY_DESCRIPTOR_MIN_LENGTH	 equ SECURITY_DESCRIPTOR

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
SE_RM_CONTROL_VALID		 equ 0x4000
SE_SELF_RELATIVE		 equ 0x8000

SECURITY_DESCRIPTOR_RELATIVE STRUC
Revision		db ?
Sbz1			db ?
Control			SECURITY_DESCRIPTOR_CONTROL ?
Owner			dd ?
_Group			dd ?
Sacl			dd ?
Dacl			dd ?
SECURITY_DESCRIPTOR_RELATIVE ENDS
PISECURITY_DESCRIPTOR_RELATIVE typedef ptr SECURITY_DESCRIPTOR_RELATIVE

SECURITY_DESCRIPTOR	STRUC
Revision		db ?
Sbz1			db ?
Control			SECURITY_DESCRIPTOR_CONTROL ?
Owner			dd ?
_Group			dd ?
Sacl			dd ?
Dacl			dd ?
SECURITY_DESCRIPTOR	ENDS
PISECURITY_DESCRIPTOR	typedef ptr SECURITY_DESCRIPTOR

OBJECT_TYPE_LIST	STRUC
Level			dw ?
Sbz			dw ?
ObjectType		LPGUID ?
OBJECT_TYPE_LIST	ENDS
POBJECT_TYPE_LIST	typedef ptr OBJECT_TYPE_LIST

ACCESS_OBJECT_GUID	 equ 0
ACCESS_PROPERTY_SET_GUID equ 1
ACCESS_PROPERTY_GUID	 equ 2

ACCESS_MAX_LEVEL	 equ 4

AuditEventObjectAccess			equ 0
AuditEventDirectoryServiceAccess	equ 1

AUDIT_ALLOW_NO_PRIVILEGE		equ 0x1
AUDIT_EVENT_TYPE			typedef sdword

;ACCESS_DS_SOURCE_A		equ <"DS">
;ACCESS_DS_SOURCE_W		equ <"DS">
;ACCESS_DS_OBJECT_TYPE_NAME_A	equ <"Directory Service Object">
;ACCESS_DS_OBJECT_TYPE_NAME_W	equ <"Directory Service Object">

SE_PRIVILEGE_ENABLED_BY_DEFAULT equ 0x00000001
SE_PRIVILEGE_ENABLED		equ 0x00000002
SE_PRIVILEGE_REMOVED		equ 0X00000004
SE_PRIVILEGE_USED_FOR_ACCESS	equ 0x80000000
SE_PRIVILEGE_VALID_ATTRIBUTES	equ SE_PRIVILEGE_ENABLED_BY_DEFAULT OR \
				    SE_PRIVILEGE_ENABLED	    OR \
				    SE_PRIVILEGE_REMOVED	    OR \
				    SE_PRIVILEGE_USED_FOR_ACCESS

PRIVILEGE_SET_ALL_NECESSARY    equ 1

PRIVILEGE_SET	STRUC
PrivilegeCount	dd ?
Control		dd ?
Privilege	LUID_AND_ATTRIBUTES ANYSIZE_ARRAY dup(<?>)
PRIVILEGE_SET	ENDS
PPRIVILEGE_SET	typedef ptr PRIVILEGE_SET

ACCESS_REASON_TYPE_MASK		equ 0xffff0000
ACCESS_REASON_DATA_MASK		equ 0x0000ffff

.enum ACCESS_REASON_TYPE {
    AccessReasonNone		 = 0x00000000,
    AccessReasonAllowedAce	 = 0x00010000,
    AccessReasonDeniedAce	 = 0x00020000,
    AccessReasonAllowedParentAce = 0x00030000,
    AccessReasonDeniedParentAce	 = 0x00040000,
    AccessReasonMissingPrivilege = 0x00100000,
    AccessReasonFromPrivilege	 = 0x00200000,
    AccessReasonIntegrityLevel	 = 0x00300000,
    AccessReasonOwnership	 = 0x00400000,
    AccessReasonNullDacl	 = 0x00500000,
    AccessReasonEmptyDacl	 = 0x00600000,
    AccessReasonNoSD		 = 0x00700000,
    AccessReasonNoGrant		 = 0x00800000
    }

ACCESS_REASON		typedef DWORD
ACCESS_REASONS		STRUC
Data			ACCESS_REASON 32 dup(?)
ACCESS_REASONS		ENDS
PACCESS_REASONS		typedef ptr ACCESS_REASONS


SE_SECURITY_DESCRIPTOR_FLAG_NO_OWNER_ACE    equ 0x00000001
SE_SECURITY_DESCRIPTOR_FLAG_NO_LABEL_ACE    equ 0x00000002
SE_SECURITY_DESCRIPTOR_VALID_FLAGS	    equ 0x00000003

SE_SECURITY_DESCRIPTOR	STRUC
Size			dd ?
Flags			dd ?
SecurityDescriptor	PSECURITY_DESCRIPTOR ?
SE_SECURITY_DESCRIPTOR	ENDS
PSE_SECURITY_DESCRIPTOR typedef ptr SE_SECURITY_DESCRIPTOR

SE_ACCESS_REQUEST	STRUC
Size			dd ?
SecurityDescriptor	PSECURITY_DESCRIPTOR ?
DesiredAccess		ACCESS_MASK ?
PreviouslyGrantedAccess ACCESS_MASK ?
PrincipalSelfSid	PSID ?	; Need to watch how this field affects the cache.
GenericMapping		PGENERIC_MAPPING ?
ObjectTypeListCount	dd ?
ObjectTypeList		POBJECT_TYPE_LIST ?
SE_ACCESS_REQUEST	ENDS
PSE_ACCESS_REQUEST	typedef ptr SE_ACCESS_REQUEST

SE_ACCESS_REPLY		STRUC
Size			dd ?
ResultListCount		dd ?	; Indicate the array size of GrantedAccess and
GrantedAccess		PACCESS_MASK ?
AccessStatus		PDWORD ?
AccessReason		PACCESS_REASONS ?
Privileges		PPRIVILEGE_SET ?
SE_ACCESS_REPLY		ENDS
PSE_ACCESS_REPLY	typedef ptr SE_ACCESS_REPLY

SE_CREATE_TOKEN_NAME		equ <"SeCreateTokenPrivilege">
SE_ASSIGNPRIMARYTOKEN_NAME	equ <"SeAssignPrimaryTokenPrivilege">
SE_LOCK_MEMORY_NAME		equ <"SeLockMemoryPrivilege">
SE_INCREASE_QUOTA_NAME		equ <"SeIncreaseQuotaPrivilege">
SE_UNSOLICITED_INPUT_NAME	equ <"SeUnsolicitedInputPrivilege">
SE_MACHINE_ACCOUNT_NAME		equ <"SeMachineAccountPrivilege">
SE_TCB_NAME			equ <"SeTcbPrivilege">
SE_SECURITY_NAME		equ <"SeSecurityPrivilege">
SE_TAKE_OWNERSHIP_NAME		equ <"SeTakeOwnershipPrivilege">
SE_LOAD_DRIVER_NAME		equ <"SeLoadDriverPrivilege">
SE_SYSTEM_PROFILE_NAME		equ <"SeSystemProfilePrivilege">
SE_SYSTEMTIME_NAME		equ <"SeSystemtimePrivilege">
SE_PROF_SINGLE_PROCESS_NAME	equ <"SeProfileSingleProcessPrivilege">
SE_INC_BASE_PRIORITY_NAME	equ <"SeIncreaseBasePriorityPrivilege">
SE_CREATE_PAGEFILE_NAME		equ <"SeCreatePagefilePrivilege">
SE_CREATE_PERMANENT_NAME	equ <"SeCreatePermanentPrivilege">
SE_BACKUP_NAME			equ <"SeBackupPrivilege">
SE_RESTORE_NAME			equ <"SeRestorePrivilege">
SE_SHUTDOWN_NAME		equ <"SeShutdownPrivilege">
SE_DEBUG_NAME			equ <"SeDebugPrivilege">
SE_AUDIT_NAME			equ <"SeAuditPrivilege">
SE_SYSTEM_ENVIRONMENT_NAME	equ <"SeSystemEnvironmentPrivilege">
SE_CHANGE_NOTIFY_NAME		equ <"SeChangeNotifyPrivilege">
SE_REMOTE_SHUTDOWN_NAME		equ <"SeRemoteShutdownPrivilege">
SE_UNDOCK_NAME			equ <"SeUndockPrivilege">
SE_SYNC_AGENT_NAME		equ <"SeSyncAgentPrivilege">
SE_ENABLE_DELEGATION_NAME	equ <"SeEnableDelegationPrivilege">
SE_MANAGE_VOLUME_NAME		equ <"SeManageVolumePrivilege">
SE_IMPERSONATE_NAME		equ <"SeImpersonatePrivilege">
SE_CREATE_GLOBAL_NAME		equ <"SeCreateGlobalPrivilege">
SE_TRUSTED_CREDMAN_ACCESS_NAME	equ <"SeTrustedCredManAccessPrivilege">
SE_RELABEL_NAME			equ <"SeRelabelPrivilege">
SE_INC_WORKING_SET_NAME		equ <"SeIncreaseWorkingSetPrivilege">
SE_TIME_ZONE_NAME		equ <"SeTimeZonePrivilege">
SE_CREATE_SYMBOLIC_LINK_NAME	equ <"SeCreateSymbolicLinkPrivilege">

SecurityAnonymous	equ 0
SecurityIdentification	equ 1
SecurityImpersonation	equ 2
SecurityDelegation	equ 3

SECURITY_IMPERSONATION_LEVEL	typedef sdword ; enum
PSECURITY_IMPERSONATION_LEVEL	typedef ptr SECURITY_IMPERSONATION_LEVEL

SECURITY_MAX_IMPERSONATION_LEVEL equ SecurityDelegation
SECURITY_MIN_IMPERSONATION_LEVEL equ SecurityAnonymous
DEFAULT_IMPERSONATION_LEVEL	 equ SecurityImpersonation
VALID_IMPERSONATION_LEVEL macro L
	exitm<((L GE SECURITY_MIN_IMPERSONATION_LEVEL) AND (L LE SECURITY_MAX_IMPERSONATION_LEVEL))>
	endm

TOKEN_ASSIGN_PRIMARY	equ 0x0001
TOKEN_DUPLICATE		equ 0x0002
TOKEN_IMPERSONATE	equ 0x0004
TOKEN_QUERY		equ 0x0008
TOKEN_QUERY_SOURCE	equ 0x0010
TOKEN_ADJUST_PRIVILEGES equ 0x0020
TOKEN_ADJUST_GROUPS	equ 0x0040
TOKEN_ADJUST_DEFAULT	equ 0x0080
TOKEN_ADJUST_SESSIONID	equ 0x0100

TOKEN_ALL_ACCESS_P equ STANDARD_RIGHTS_REQUIRED	 or \
		     TOKEN_ASSIGN_PRIMARY      or \
		     TOKEN_DUPLICATE	       or \
		     TOKEN_IMPERSONATE	       or \
		     TOKEN_QUERY	       or \
		     TOKEN_QUERY_SOURCE	       or \
		     TOKEN_ADJUST_PRIVILEGES   or \
		     TOKEN_ADJUST_GROUPS       or \
		     TOKEN_ADJUST_DEFAULT
if(_WIN32_WINNT GT 0x0400)
TOKEN_ALL_ACCESS equ TOKEN_ALL_ACCESS_P OR TOKEN_ADJUST_SESSIONID
else
TOKEN_ALL_ACCESS equ TOKEN_ALL_ACCESS_P
endif

TOKEN_READ	equ STANDARD_RIGHTS_READ or TOKEN_QUERY
TOKEN_WRITE	equ STANDARD_RIGHTS_WRITE   or \
		    TOKEN_ADJUST_PRIVILEGES or \
		    TOKEN_ADJUST_GROUPS	    or \
		    TOKEN_ADJUST_DEFAULT

TOKEN_EXECUTE	equ STANDARD_RIGHTS_EXECUTE

.enum TOKEN_TYPE {
    TokenPrimary		= 1,
    TokenImpersonation		= 2
    }

.enum TOKEN_ELEVATION_TYPE {
    TokenElevationTypeDefault	= 1,
    TokenElevationTypeFull	= 2,
    TokenElevationTypeLimited	= 3 }
    PTOKEN_ELEVATION_TYPE	typedef ptr TOKEN_ELEVATION_TYPE

.enum TOKEN_INFORMATION_CLASS {
    TokenUser			= 1,
    TokenGroups			= 2,
    TokenPrivileges		= 3,
    TokenOwner			= 4,
    TokenPrimaryGroup		= 5,
    TokenDefaultDacl		= 6,
    TokenSource			= 7,
    TokenType			= 8,
    TokenImpersonationLevel	= 9,
    TokenStatistics		= 10,
    TokenRestrictedSids		= 11,
    TokenSessionId		= 12,
    TokenGroupsAndPrivileges	= 13,
    TokenSessionReference	= 14,
    TokenSandBoxInert		= 15,
    TokenAuditPolicy		= 16,
    TokenOrigin			= 17,
    TokenElevationType		= 18,
    TokenLinkedToken		= 19,
    TokenElevation		= 20,
    TokenHasRestrictions	= 21,
    TokenAccessInformation	= 22,
    TokenVirtualizationAllowed	= 23,
    TokenVirtualizationEnabled	= 24,
    TokenIntegrityLevel		= 25,
    TokenUIAccess		= 26,
    TokenMandatoryPolicy	= 27,
    TokenLogonSid		= 28,
    MaxTokenInfoClass		= 29 }
    PTOKEN_INFORMATION_CLASS	typedef ptr TOKEN_INFORMATION_CLASS

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

TOKEN_GROUPS_AND_PRIVILEGES STRUC
SidCount		dd ?
SidLength		dd ?
Sids			PSID_AND_ATTRIBUTES ?
RestrictedSidCount	dd ?
RestrictedSidLength	dd ?
RestrictedSids		PSID_AND_ATTRIBUTES ?
PrivilegeCount		dd ?
PrivilegeLength		dd ?
Privileges		PLUID_AND_ATTRIBUTES ?
AuthenticationId	LUID <>
TOKEN_GROUPS_AND_PRIVILEGES ENDS
PTOKEN_GROUPS_AND_PRIVILEGES typedef ptr TOKEN_GROUPS_AND_PRIVILEGES

TOKEN_LINKED_TOKEN	STRUC
LinkedToken		HANDLE ?
TOKEN_LINKED_TOKEN	ENDS
PTOKEN_LINKED_TOKEN	typedef ptr TOKEN_LINKED_TOKEN

TOKEN_ELEVATION		STRUC
TokenIsElevated		dd ?
TOKEN_ELEVATION		ENDS
PTOKEN_ELEVATION	typedef ptr TOKEN_ELEVATION

TOKEN_MANDATORY_LABEL	STRUC
_Label			SID_AND_ATTRIBUTES <>
TOKEN_MANDATORY_LABEL	ENDS
PTOKEN_MANDATORY_LABEL	typedef ptr TOKEN_MANDATORY_LABEL

TOKEN_MANDATORY_POLICY_OFF	       equ 0x0
TOKEN_MANDATORY_POLICY_NO_WRITE_UP     equ 0x1
TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN equ 0x2
TOKEN_MANDATORY_POLICY_VALID_MASK      equ TOKEN_MANDATORY_POLICY_NO_WRITE_UP OR \
					   TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN
TOKEN_MANDATORY_POLICY	STRUC
Policy			dd ?
TOKEN_MANDATORY_POLICY	ENDS
PTOKEN_MANDATORY_POLICY typedef ptr TOKEN_MANDATORY_POLICY

TOKEN_ACCESS_INFORMATION STRUC
SidHash			PSID_AND_ATTRIBUTES_HASH ?
RestrictedSidHash	PSID_AND_ATTRIBUTES_HASH ?
Privileges		PTOKEN_PRIVILEGES ?
AuthenticationId	LUID <>
TokenType		TOKEN_TYPE ?
ImpersonationLevel	SECURITY_IMPERSONATION_LEVEL ?
MandatoryPolicy		TOKEN_MANDATORY_POLICY <>
Flags			dd ?
TOKEN_ACCESS_INFORMATION ENDS
PTOKEN_ACCESS_INFORMATION typedef ptr TOKEN_ACCESS_INFORMATION

POLICY_AUDIT_SUBCATEGORY_COUNT equ 53

TOKEN_AUDIT_POLICY	STRUC
PerUserPolicy		db ((POLICY_AUDIT_SUBCATEGORY_COUNT) SHR 1) + 1 dup(?)
TOKEN_AUDIT_POLICY	ENDS
PTOKEN_AUDIT_POLICY	typedef ptr TOKEN_AUDIT_POLICY

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
DynamicCharged		dd ?
DynamicAvailable	dd ?
GroupCount		dd ?
PrivilegeCount		dd ?
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

_TOKEN_ORIGIN		struct
OriginatingLogonSession LUID <>
_TOKEN_ORIGIN		ends
TOKEN_ORIGIN		typedef _TOKEN_ORIGIN
PTOKEN_ORIGIN		typedef ptr _TOKEN_ORIGIN

.enum MANDATORY_LEVEL {
    MandatoryLevelUntrusted = 0,
    MandatoryLevelLow,
    MandatoryLevelMedium,
    MandatoryLevelHigh,
    MandatoryLevelSystem,
    MandatoryLevelSecureProcess,
    MandatoryLevelCount
    }
PMANDATORY_LEVEL	typedef ptr MANDATORY_LEVEL


_TOKEN_APPCONTAINER_INFORMATION struct
TokenAppContainer	PSID ?
_TOKEN_APPCONTAINER_INFORMATION ends
TOKEN_APPCONTAINER_INFORMATION typedef _TOKEN_APPCONTAINER_INFORMATION
PTOKEN_APPCONTAINER_INFORMATION typedef ptr _TOKEN_APPCONTAINER_INFORMATION

ifndef MIDL_PASS
define TOKEN_APPCONTAINER_SID_MAX_SIZE (sizeof(TOKEN_APPCONTAINER_INFORMATION) + SECURITY_MAX_SID_SIZE)
endif

_TOKEN_SID_INFORMATION	struct
Sid			PSID ?
_TOKEN_SID_INFORMATION	ends
TOKEN_SID_INFORMATION	typedef _TOKEN_SID_INFORMATION
PTOKEN_SID_INFORMATION	typedef ptr _TOKEN_SID_INFORMATION

_TOKEN_BNO_ISOLATION_INFORMATION struct
IsolationPrefix		PWSTR ?
IsolationEnabled	BOOLEAN ?
_TOKEN_BNO_ISOLATION_INFORMATION ends
TOKEN_BNO_ISOLATION_INFORMATION typedef _TOKEN_BNO_ISOLATION_INFORMATION
PTOKEN_BNO_ISOLATION_INFORMATION typedef ptr _TOKEN_BNO_ISOLATION_INFORMATION

define CLAIM_SECURITY_ATTRIBUTE_TYPE_INVALID   0x00
define CLAIM_SECURITY_ATTRIBUTE_TYPE_INT64     0x01
define CLAIM_SECURITY_ATTRIBUTE_TYPE_UINT64    0x02
define CLAIM_SECURITY_ATTRIBUTE_TYPE_STRING    0x03

_CLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE struct
Version			DWORD64 ?
Name			PWSTR ?
_CLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE ends
CLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE typedef _CLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE
PCLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE typedef ptr _CLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE

define CLAIM_SECURITY_ATTRIBUTE_TYPE_FQBN      0x04
define CLAIM_SECURITY_ATTRIBUTE_TYPE_SID       0x05
define CLAIM_SECURITY_ATTRIBUTE_TYPE_BOOLEAN   0x06

_CLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE struct
pValue			PVOID ?
ValueLength		DWORD ?
_CLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE ends
CLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE typedef _CLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE
PCLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE typedef ptr _CLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE

define CLAIM_SECURITY_ATTRIBUTE_TYPE_OCTET_STRING  0x10
define CLAIM_SECURITY_ATTRIBUTE_NON_INHERITABLE	     0x0001
define CLAIM_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE	     0x0002
define CLAIM_SECURITY_ATTRIBUTE_USE_FOR_DENY_ONLY 0x0004
define CLAIM_SECURITY_ATTRIBUTE_DISABLED_BY_DEFAULT 0x0008
define CLAIM_SECURITY_ATTRIBUTE_DISABLED 0x0010
define CLAIM_SECURITY_ATTRIBUTE_MANDATORY 0x0020
define CLAIM_SECURITY_ATTRIBUTE_VALID_FLAGS   ( CLAIM_SECURITY_ATTRIBUTE_NON_INHERITABLE or CLAIM_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE or CLAIM_SECURITY_ATTRIBUTE_USE_FOR_DENY_ONLY or CLAIM_SECURITY_ATTRIBUTE_DISABLED_BY_DEFAULT or CLAIM_SECURITY_ATTRIBUTE_DISABLED or CLAIM_SECURITY_ATTRIBUTE_MANDATORY )
define CLAIM_SECURITY_ATTRIBUTE_CUSTOM_FLAGS   0xFFFF0000

_CLAIM_SECURITY_ATTRIBUTE_V1 struct
Name			PWSTR ?
ValueType		WORD ?
Reserved		WORD ?
Flags			DWORD ?
ValueCount		DWORD ?
union Values
 pInt64			PLONG64 ?
 pUint64		PDWORD64 ?
 ppString		ptr PWSTR ?
 pFqbn			PCLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE ?
 pOctetString		PCLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE ?
ends
_CLAIM_SECURITY_ATTRIBUTE_V1 ends
CLAIM_SECURITY_ATTRIBUTE_V1 typedef _CLAIM_SECURITY_ATTRIBUTE_V1
PCLAIM_SECURITY_ATTRIBUTE_V1 typedef ptr _CLAIM_SECURITY_ATTRIBUTE_V1

_CLAIM_SECURITY_ATTRIBUTE_RELATIVE_V1 struct
Name			DWORD ?
ValueType		WORD ?
Reserved		WORD ?
Flags			DWORD ?
ValueCount		DWORD ?
union Values
 pInt64			DWORD ANYSIZE_ARRAY dup(?)
 pUint64		DWORD ANYSIZE_ARRAY dup(?)
 ppString		DWORD ANYSIZE_ARRAY dup(?)
 pFqbn			DWORD ANYSIZE_ARRAY dup(?)
 pOctetString		DWORD ANYSIZE_ARRAY dup(?)
ends
_CLAIM_SECURITY_ATTRIBUTE_RELATIVE_V1 ends
CLAIM_SECURITY_ATTRIBUTE_RELATIVE_V1 typedef _CLAIM_SECURITY_ATTRIBUTE_RELATIVE_V1
PCLAIM_SECURITY_ATTRIBUTE_RELATIVE_V1 typedef ptr _CLAIM_SECURITY_ATTRIBUTE_RELATIVE_V1

define CLAIM_SECURITY_ATTRIBUTES_INFORMATION_VERSION_V1	   1
define CLAIM_SECURITY_ATTRIBUTES_INFORMATION_VERSION CLAIM_SECURITY_ATTRIBUTES_INFORMATION_VERSION_V1

_CLAIM_SECURITY_ATTRIBUTES_INFORMATION struct
Version			WORD ?
Reserved		WORD ?
AttributeCount		DWORD ?
union Attribute
 pAttributeV1		PCLAIM_SECURITY_ATTRIBUTE_V1 ?
ends
_CLAIM_SECURITY_ATTRIBUTES_INFORMATION ends
CLAIM_SECURITY_ATTRIBUTES_INFORMATION typedef _CLAIM_SECURITY_ATTRIBUTES_INFORMATION
PCLAIM_SECURITY_ATTRIBUTES_INFORMATION typedef ptr _CLAIM_SECURITY_ATTRIBUTES_INFORMATION

define SECURITY_DYNAMIC_TRACKING      (TRUE)
define SECURITY_STATIC_TRACKING	      (FALSE)

SECURITY_CONTEXT_TRACKING_MODE	typedef BOOLEAN
PSECURITY_CONTEXT_TRACKING_MODE typedef ptr SECURITY_CONTEXT_TRACKING_MODE


SECURITY_QUALITY_OF_SERVICE	STRUC
Length				dd ?
ImpersonationLevel		SECURITY_IMPERSONATION_LEVEL ?
ContextTrackingMode		SECURITY_CONTEXT_TRACKING_MODE ?
EffectiveOnly			BOOLEAN ?
SECURITY_QUALITY_OF_SERVICE	ENDS
PSECURITY_QUALITY_OF_SERVICE	typedef ptr SECURITY_QUALITY_OF_SERVICE


SE_IMPERSONATION_STATE		STRUC
Token				PACCESS_TOKEN ?
CopyOnOpen			BOOLEAN ?
EffectiveOnly			BOOLEAN ?
Level				SECURITY_IMPERSONATION_LEVEL ?
SE_IMPERSONATION_STATE		ENDS
PSE_IMPERSONATION_STATE		typedef ptr SE_IMPERSONATION_STATE

DISABLE_MAX_PRIVILEGE		equ 0x1
SANDBOX_INERT			equ 0x2
LUA_TOKEN			equ 0x4
WRITE_RESTRICTED		equ 0x8

SECURITY_INFORMATION		typedef DWORD
PSECURITY_INFORMATION		typedef ptr DWORD

PROTECTED_DACL_SECURITY_INFORMATION   equ 0x80000000
PROTECTED_SACL_SECURITY_INFORMATION   equ 0x40000000
UNPROTECTED_DACL_SECURITY_INFORMATION equ 0x20000000
UNPROTECTED_SACL_SECURITY_INFORMATION equ 0x10000000

OWNER_SECURITY_INFORMATION	equ 0x00000001
GROUP_SECURITY_INFORMATION	equ 0x00000002
DACL_SECURITY_INFORMATION	equ 0x00000004
SACL_SECURITY_INFORMATION	equ 0x00000008
LABEL_SECURITY_INFORMATION	equ 0x00000010

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

PROCESS_SUSPEND_RESUME		  equ 0x0800
PROCESS_QUERY_LIMITED_INFORMATION equ 0x1000
if (NTDDI_VERSION GE NTDDI_VISTA)
PROCESS_ALL_ACCESS equ STANDARD_RIGHTS_REQUIRED OR SYNCHRONIZE OR 0xFFFF
else
PROCESS_ALL_ACCESS equ STANDARD_RIGHTS_REQUIRED OR SYNCHRONIZE OR 0xFFF
endif

ifdef _WIN64
MAXIMUM_PROC_PER_GROUP		equ 64
else
MAXIMUM_PROC_PER_GROUP		equ 32
endif
MAXIMUM_PROCESSORS		equ MAXIMUM_PROC_PER_GROUP

THREAD_TERMINATE		equ 0x0001
THREAD_SUSPEND_RESUME		equ 0x0002
THREAD_GET_CONTEXT		equ 0x0008
THREAD_SET_CONTEXT		equ 0x0010
THREAD_SET_INFORMATION		equ 0x0020
THREAD_QUERY_INFORMATION	equ 0x0040
THREAD_SET_THREAD_TOKEN		equ 0x0080
THREAD_IMPERSONATE		equ 0x0100
THREAD_DIRECT_IMPERSONATION	equ 0x0200

THREAD_SET_LIMITED_INFORMATION	 equ 0x0400
THREAD_QUERY_LIMITED_INFORMATION equ 0x0800
if (NTDDI_VERSION GE NTDDI_VISTA)
THREAD_ALL_ACCESS equ STANDARD_RIGHTS_REQUIRED OR SYNCHRONIZE OR 0xFFFF
else
THREAD_ALL_ACCESS equ STANDARD_RIGHTS_REQUIRED OR SYNCHRONIZE OR 0x3FF
endif

JOB_OBJECT_ASSIGN_PROCESS	equ 0x0001
JOB_OBJECT_SET_ATTRIBUTES	equ 0x0002
JOB_OBJECT_QUERY		equ 0x0004
JOB_OBJECT_TERMINATE		equ 0x0008
JOB_OBJECT_SET_SECURITY_ATTRIBUTES equ 0x0010
JOB_OBJECT_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x1F

JOB_SET_ARRAY			STRUC
JobHandle			HANDLE ?; Handle to job object to insert
MemberLevel			dd ?	; Level of this job in the set. Must be > 0. Can be sparse.
Flags				dd ?	; Unused. Must be zero
JOB_SET_ARRAY			ENDS
PJOB_SET_ARRAY			typedef ptr JOB_SET_ARRAY

FLS_MAXIMUM_AVAILABLE		equ 4080
TLS_MINIMUM_AVAILABLE		equ 64

EXCEPTION_REGISTRATION_RECORD	STRUC
Next				ptr EXCEPTION_REGISTRATION_RECORD ?
Handler				PEXCEPTION_ROUTINE ?
EXCEPTION_REGISTRATION_RECORD	ENDS
PEXCEPTION_REGISTRATION_RECORD	typedef ptr EXCEPTION_REGISTRATION_RECORD

NT_TIB				STRUC
ExceptionList			PEXCEPTION_REGISTRATION_RECORD ?
StackBase			PVOID ?
StackLimit			PVOID ?
SubSystemTib			PVOID ?
ifdef _MSC_EXTENSIONS
UNION
  FiberData			PVOID ?
  Version			dd ?
ENDS
else
FiberData			PVOID ?
endif
ArbitraryUserPointer		PVOID ?
Self				PVOID ?
NT_TIB				ENDS
PNT_TIB				typedef ptr NT_TIB

NT_TIB32			STRUC
ExceptionList			dd ?
StackBase			dd ?
StackLimit			dd ?
SubSystemTib			dd ?
ifdef _MSC_EXTENSIONS
UNION
  FiberData			dd ?
  Version			dd ?
ENDS
else
FiberData			dd ?
endif
ArbitraryUserPointer		dd ?
Self				dd ?
NT_TIB32			ENDS
PNT_TIB32			typedef ptr NT_TIB32

NT_TIB64			STRUC
ExceptionList			dq ?
StackBase			dq ?
StackLimit			dq ?
SubSystemTib			dq ?
ifdef _MSC_EXTENSIONS
UNION
  FiberData			dq ?
  Version			dq ?
ENDS
else
FiberData			dq ?
endif
ArbitraryUserPointer		dq ?
Self				dq ?
NT_TIB64			ENDS
PNT_TIB64			typedef ptr NT_TIB64

THREAD_BASE_PRIORITY_LOWRT	equ 15
THREAD_BASE_PRIORITY_MAX	equ 2
THREAD_BASE_PRIORITY_MIN	equ -2
THREAD_BASE_PRIORITY_IDLE	equ -15

UMS_CREATE_THREAD_ATTRIBUTES	STRUC
UmsVersion			dd ?
UmsContext			PVOID ?
UmsCompletionList		PVOID ?
UMS_CREATE_THREAD_ATTRIBUTES	ENDS
PUMS_CREATE_THREAD_ATTRIBUTES	typedef ptr UMS_CREATE_THREAD_ATTRIBUTES

QUOTA_LIMITS			STRUC
PagedPoolLimit			SIZE_T ?
NonPagedPoolLimit		SIZE_T ?
MinimumWorkingSetSize		SIZE_T ?
MaximumWorkingSetSize		SIZE_T ?
PagefileLimit			SIZE_T ?
TimeLimit			LARGE_INTEGER <>
QUOTA_LIMITS			ENDS
PQUOTA_LIMITS			typedef ptr QUOTA_LIMITS

QUOTA_LIMITS_HARDWS_MIN_ENABLE	equ 0x00000001
QUOTA_LIMITS_HARDWS_MIN_DISABLE equ 0x00000002
QUOTA_LIMITS_HARDWS_MAX_ENABLE	equ 0x00000004
QUOTA_LIMITS_HARDWS_MAX_DISABLE equ 0x00000008
QUOTA_LIMITS_USE_DEFAULT_LIMITS equ 0x00000010

RATE_QUOTA_LIMIT		STRUC
RateData			dd ?
RECORD
 RatePercent			dd : 7 ?
 Reserved0			dd : 25 ?
ENDS
RATE_QUOTA_LIMIT		ENDS
PRATE_QUOTA_LIMIT		typedef ptr RATE_QUOTA_LIMIT

QUOTA_LIMITS_EX			STRUC
PagedPoolLimit			SIZE_T ?
NonPagedPoolLimit		SIZE_T ?
MinimumWorkingSetSize		SIZE_T ?
MaximumWorkingSetSize		SIZE_T ?
PagefileLimit			SIZE_T ?
TimeLimit			LARGE_INTEGER <>
WorkingSetLimit			SIZE_T ?
Reserved2			SIZE_T ?
Reserved3			SIZE_T ?
Reserved4			SIZE_T ?
Flags				dd ?
CpuRateLimit			RATE_QUOTA_LIMIT <>
QUOTA_LIMITS_EX			ENDS
PQUOTA_LIMITS_EX		typedef ptr QUOTA_LIMITS_EX

IO_COUNTERS			STRUC
ReadOperationCount		ULONGLONG ?
WriteOperationCount		ULONGLONG ?
OtherOperationCount		ULONGLONG ?
ReadTransferCount		ULONGLONG ?
WriteTransferCount		ULONGLONG ?
OtherTransferCount		ULONGLONG ?
IO_COUNTERS			ENDS
PIO_COUNTERS			typedef ptr IO_COUNTERS

MAX_HW_COUNTERS			equ 16
THREAD_PROFILING_FLAG_DISPATCH	equ 0x00000001

.enum HARDWARE_COUNTER_TYPE {
    PMCCounter,
    MaxHardwareCounterType
    }
PHARDWARE_COUNTER_TYPE typedef ptr HARDWARE_COUNTER_TYPE

.enum PROCESS_MITIGATION_POLICY {
    ProcessDEPPolicy,
    ProcessASLRPolicy,
    ProcessDynamicCodePolicy,
    ProcessStrictHandleCheckPolicy,
    ProcessSystemCallDisablePolicy,
    ProcessMitigationOptionsMask,
    ProcessExtensionPointDisablePolicy,
    ProcessReserved1Policy,
    ProcessSignaturePolicy,
    MaxProcessMitigationPolicy
   }
PPROCESS_MITIGATION_POLICY typedef ptr PROCESS_MITIGATION_POLICY


PROCESS_MITIGATION_ASLR_POLICY	STRUC
RECORD Flags
 EnableBottomUpRandomization	dd :  1 ?
 EnableForceRelocateImages	dd :  1 ?
 EnableHighEntropy		dd :  1 ?
 DisallowStrippedImages		dd :  1 ?
 ReservedFlags			dd : 28 ?
ENDS
PROCESS_MITIGATION_ASLR_POLICY	ENDS
PPROCESS_MITIGATION_ASLR_POLICY typedef ptr PROCESS_MITIGATION_ASLR_POLICY

PROCESS_MITIGATION_DEP_POLICY	STRUC
RECORD Flags
 Enable				dd :  1 ?
 DisableAtlThunkEmulation	dd :  1 ?
 ReservedFlags			dd : 30 ?
ENDS
Permanent			BOOLEAN ?
PROCESS_MITIGATION_DEP_POLICY	ENDS
PPROCESS_MITIGATION_DEP_POLICY	typedef ptr PROCESS_MITIGATION_DEP_POLICY

PROCESS_MITIGATION_STRICT_HANDLE_CHECK_POLICY STRUC
RECORD Flags
 RaiseExceptionOnInvalidHandleReference dd :  1 ?
 HandleExceptionsPermanentlyEnabled	dd :  1 ?
 ReservedFlags				dd : 30 ?
ENDS
PROCESS_MITIGATION_STRICT_HANDLE_CHECK_POLICY ENDS
PPROCESS_MITIGATION_STRICT_HANDLE_CHECK_POLICY typedef ptr PROCESS_MITIGATION_STRICT_HANDLE_CHECK_POLICY

PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY STRUC
RECORD Flags
 DisallowWin32kSystemCalls	dd :  1 ?
 ReservedFlags			dd : 31 ?
ENDS
PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY ENDS
PPROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY typedef ptr PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY

PROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY STRUC
RECORD Flags
 DisableExtensionPoints		dd :  1 ?
 ReservedFlags			dd : 31 ?
ENDS
PROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY ENDS
PPROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY typedef ptr PROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY

PROCESS_MITIGATION_DYNAMIC_CODE_POLICY STRUC
RECORD Flags
 ProhibitDynamicCode		dd :  1 ?
 ReservedFlags			dd : 31 ?
ENDS
PROCESS_MITIGATION_DYNAMIC_CODE_POLICY ENDS
PPROCESS_MITIGATION_DYNAMIC_CODE_POLICY typedef ptr PROCESS_MITIGATION_DYNAMIC_CODE_POLICY

PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY STRUC
RECORD Flags
 MicrosoftSignedOnly		dd :  1 ?
 ReservedFlags			dd : 31 ?
ENDS
PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY ENDS
PPROCESS_MITIGATION_BINARY_SIGNATURE_POLICY typedef ptr PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY

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
MinimumWorkingSetSize		SIZE_T ?
MaximumWorkingSetSize		SIZE_T ?
ActiveProcessLimit		dd ?
Affinity			ULONG_PTR ?
PriorityClass			dd ?
JOBOBJECT_BASIC_LIMIT_INFORMATION ENDS
PJOBOBJECT_BASIC_LIMIT_INFORMATION typedef ptr JOBOBJECT_BASIC_LIMIT_INFORMATION

JOBOBJECT_EXTENDED_LIMIT_INFORMATION STRUC
BasicLimitInformation		JOBOBJECT_BASIC_LIMIT_INFORMATION <>
IoInfo				IO_COUNTERS <>
ProcessMemoryLimit		SIZE_T ?
JobMemoryLimit			SIZE_T ?
PeakProcessMemoryUsed		SIZE_T ?
PeakJobMemoryUsed		SIZE_T ?
JOBOBJECT_EXTENDED_LIMIT_INFORMATION ENDS
PJOBOBJECT_EXTENDED_LIMIT_INFORMATION typedef ptr JOBOBJECT_EXTENDED_LIMIT_INFORMATION

JOBOBJECT_BASIC_PROCESS_ID_LIST STRUC
NumberOfAssignedProcesses	dd ?
NumberOfProcessIdsInList	dd ?
ProcessIdLis			ULONG_PTR ?
JOBOBJECT_BASIC_PROCESS_ID_LIST ENDS
PJOBOBJECT_BASIC_PROCESS_ID_LIST typedef ptr JOBOBJECT_BASIC_PROCESS_ID_LIST

JOBOBJECT_BASIC_UI_RESTRICTIONS STRUC
UIRestrictionsClass		dd ?
JOBOBJECT_BASIC_UI_RESTRICTIONS ENDS
PJOBOBJECT_BASIC_UI_RESTRICTIONS typedef ptr JOBOBJECT_BASIC_UI_RESTRICTIONS

JOBOBJECT_SECURITY_LIMIT_INFORMATION STRUC
SecurityLimitFlags		dd ?
JobToken			HANDLE ?
SidsToDisable			PTOKEN_GROUPS ?
PrivilegesToDelete		PTOKEN_PRIVILEGES ?
RestrictedSids			PTOKEN_GROUPS ?
JOBOBJECT_SECURITY_LIMIT_INFORMATION ENDS
PJOBOBJECT_SECURITY_LIMIT_INFORMATION typedef ptr JOBOBJECT_SECURITY_LIMIT_INFORMATION

JOBOBJECT_END_OF_JOB_TIME_INFORMATION STRUC
EndOfJobTimeAction		dd ?
JOBOBJECT_END_OF_JOB_TIME_INFORMATION ENDS
PJOBOBJECT_END_OF_JOB_TIME_INFORMATION typedef ptr JOBOBJECT_END_OF_JOB_TIME_INFORMATION

JOBOBJECT_ASSOCIATE_COMPLETION_PORT STRUC
CompletionKey			PVOID ?
CompletionPort			HANDLE ?
JOBOBJECT_ASSOCIATE_COMPLETION_PORT ENDS
PJOBOBJECT_ASSOCIATE_COMPLETION_PORT typedef ptr JOBOBJECT_ASSOCIATE_COMPLETION_PORT

JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION STRUC
BasicInfo			JOBOBJECT_BASIC_ACCOUNTING_INFORMATION <>
IoInfo				IO_COUNTERS <>
JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION ENDS
PJOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION typedef ptr JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION

JOBOBJECT_JOBSET_INFORMATION	STRUC
MemberLevel			dd ?
JOBOBJECT_JOBSET_INFORMATION	ENDS
PJOBOBJECT_JOBSET_INFORMATION	typedef ptr JOBOBJECT_JOBSET_INFORMATION

JOB_OBJECT_TERMINATE_AT_END_OF_JOB	equ 0
JOB_OBJECT_POST_AT_END_OF_JOB		equ 1


JOB_OBJECT_MSG_END_OF_JOB_TIME		equ 1
JOB_OBJECT_MSG_END_OF_PROCESS_TIME	equ 2
JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT	equ 3
JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO	equ 4
JOB_OBJECT_MSG_NEW_PROCESS		equ 6
JOB_OBJECT_MSG_EXIT_PROCESS		equ 7
JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS	equ 8
JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT	equ 9
JOB_OBJECT_MSG_JOB_MEMORY_LIMIT		equ 10

JOB_OBJECT_LIMIT_WORKINGSET		equ 0x00000001
JOB_OBJECT_LIMIT_PROCESS_TIME		equ 0x00000002
JOB_OBJECT_LIMIT_JOB_TIME		equ 0x00000004
JOB_OBJECT_LIMIT_ACTIVE_PROCESS		equ 0x00000008
JOB_OBJECT_LIMIT_AFFINITY		equ 0x00000010
JOB_OBJECT_LIMIT_PRIORITY_CLASS		equ 0x00000020
JOB_OBJECT_LIMIT_PRESERVE_JOB_TIME	equ 0x00000040
JOB_OBJECT_LIMIT_SCHEDULING_CLASS	equ 0x00000080
JOB_OBJECT_LIMIT_PROCESS_MEMORY		equ 0x00000100
JOB_OBJECT_LIMIT_JOB_MEMORY		equ 0x00000200
JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION equ 0x00000400
JOB_OBJECT_LIMIT_BREAKAWAY_OK		equ 0x00000800
JOB_OBJECT_LIMIT_SILENT_BREAKAWAY_OK	equ 0x00001000
JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE	equ 0x00002000

JOB_OBJECT_LIMIT_SUBSET_AFFINITY	equ 0x00004000
JOB_OBJECT_LIMIT_RESERVED3		equ 0x00008000
JOB_OBJECT_LIMIT_RESERVED4		equ 0x00010000
JOB_OBJECT_LIMIT_RESERVED5		equ 0x00020000
JOB_OBJECT_LIMIT_RESERVED6		equ 0x00040000

JOB_OBJECT_LIMIT_VALID_FLAGS		equ 0x0007ffff
JOB_OBJECT_BASIC_LIMIT_VALID_FLAGS	equ 0x000000ff
JOB_OBJECT_EXTENDED_LIMIT_VALID_FLAGS	equ 0x00007fff
JOB_OBJECT_RESERVED_LIMIT_VALID_FLAGS	equ 0x0007ffff

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

.enum JOBOBJECTINFOCLASS {
    JobObjectBasicAccountingInformation = 1,
    JobObjectBasicLimitInformation,
    JobObjectBasicProcessIdList,
    JobObjectBasicUIRestrictions,
    JobObjectSecurityLimitInformation,
    JobObjectEndOfJobTimeInformation,
    JobObjectAssociateCompletionPortInformation,
    JobObjectBasicAndIoAccountingInformation,
    JobObjectExtendedLimitInformation,
    JobObjectJobSetInformation,
    JobObjectGroupInformation,
    JobObjectNotificationLimitInformation,
    JobObjectLimitViolationInformation,
    JobObjectGroupInformationEx,
    JobObjectCpuRateControlInformation,
    JobObjectCompletionFilter,
    JobObjectCompletionCounter,
    JobObjectReserved1Information = 18,
    JobObjectReserved2Information,
    JobObjectReserved3Information,
    JobObjectReserved4Information,
    JobObjectReserved5Information,
    JobObjectReserved6Information,
    JobObjectReserved7Information,
    JobObjectReserved8Information,
    JobObjectReserved9Information,
    JobObjectReserved10Information,
    JobObjectReserved11Information,
    JobObjectReserved12Information,
    JobObjectReserved13Information,
    JobObjectReserved14Information = 31,
    JobObjectNetRateControlInformation,
    JobObjectNotificationLimitInformation2,
    JobObjectLimitViolationInformation2,
    JobObjectCreateSilo,
    JobObjectSiloBasicInformation,
    JobObjectReserved15Information = 37,
    JobObjectReserved16Information = 38,
    JobObjectReserved17Information = 39,
    JobObjectReserved18Information = 40,
    JobObjectReserved19Information = 41,
    JobObjectReserved20Information = 42,
    JobObjectReserved21Information = 43,
    JobObjectReserved22Information = 44,
    JobObjectReserved23Information = 45,
    JobObjectReserved24Information = 46,
    JobObjectReserved25Information = 47,
    MaxJobObjectInfoClass
    }

_SILOOBJECT_BASIC_INFORMATION struct
SiloId			DWORD ?
SiloParentId		DWORD ?
NumberOfProcesses	DWORD ?
IsInServerSilo		BOOLEAN ?
Reserved		BYTE 3 dup(?)
_SILOOBJECT_BASIC_INFORMATION ends
SILOOBJECT_BASIC_INFORMATION typedef _SILOOBJECT_BASIC_INFORMATION
PSILOOBJECT_BASIC_INFORMATION typedef ptr _SILOOBJECT_BASIC_INFORMATION

.enum SERVERSILO_STATE {
    SERVERSILO_INITING = 0,
    SERVERSILO_STARTED,
    SERVERSILO_SHUTTING_DOWN,
    SERVERSILO_TERMINATING,
    SERVERSILO_TERMINATED,
    }

_SERVERSILO_BASIC_INFORMATION struct
ServiceSessionId	DWORD ?
State			SERVERSILO_STATE ?
ExitStatus		DWORD ?
IsDownlevelContainer	BOOLEAN ?
ApiSetSchema		PVOID ?
HostApiSetSchema	PVOID ?
_SERVERSILO_BASIC_INFORMATION ends
SERVERSILO_BASIC_INFORMATION typedef _SERVERSILO_BASIC_INFORMATION
PSERVERSILO_BASIC_INFORMATION typedef ptr _SERVERSILO_BASIC_INFORMATION

.enum FIRMWARE_TYPE {
    FirmwareTypeUnknown,
    FirmwareTypeBios,
    FirmwareTypeUefi,
    FirmwareTypeMax
    }
PFIRMWARE_TYPE		typedef ptr PFIRMWARE_TYPE

EVENT_MODIFY_STATE	equ 0x0002
EVENT_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3
MUTANT_QUERY_STATE	equ 0x0001

MUTANT_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or MUTANT_QUERY_STATE
SEMAPHORE_MODIFY_STATE	equ 0x0002
SEMAPHORE_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3


TIMER_QUERY_STATE	equ 0x0001
TIMER_MODIFY_STATE	equ 0x0002
TIMER_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or \
			    TIMER_QUERY_STATE or TIMER_MODIFY_STATE

TIME_ZONE_ID_UNKNOWN	equ 0
TIME_ZONE_ID_STANDARD	equ 1
TIME_ZONE_ID_DAYLIGHT	equ 2

.enum LOGICAL_PROCESSOR_RELATIONSHIP {
    RelationProcessorCore,
    RelationNumaNode,
    RelationCache,
    RelationProcessorPackage,
    RelationGroup,
    RelationAll = 0xffff
    }

LTP_PC_SMT		equ 0x1

.enum PROCESSOR_CACHE_TYPE {
    CacheUnified,
    CacheInstruction,
    CacheData,
    CacheTrace
    }

CACHE_FULLY_ASSOCIATIVE equ 0xFF

CACHE_DESCRIPTOR	STRUC
Level			db ?
Associativity		db ?
LineSize		dw ?
Size			dd ?
Type			PROCESSOR_CACHE_TYPE ?
CACHE_DESCRIPTOR	ENDS
PCACHE_DESCRIPTOR	typedef ptr CACHE_DESCRIPTOR

SYSTEM_LOGICAL_PROCESSOR_INFORMATION STRUC
ProcessorMask		ULONG_PTR ?
Relationship		LOGICAL_PROCESSOR_RELATIONSHIP ?
UNION
 STRUC ProcessorCore
  Flags			db ?
 ENDS
 STRUC NumaNode
  NodeNumber		dd ?
 ENDS
 Cache			CACHE_DESCRIPTOR <>
 Reserved		ULONGLONG 2 dup(?)
ENDS
SYSTEM_LOGICAL_PROCESSOR_INFORMATION ENDS
PSYSTEM_LOGICAL_PROCESSOR_INFORMATION typedef ptr SYSTEM_LOGICAL_PROCESSOR_INFORMATION

PROCESSOR_RELATIONSHIP	STRUC
Flags			db ?
Reserved		db 21 dup(?)
GroupCount		dw ?
GroupMask		GROUP_AFFINITY ANYSIZE_ARRAY dup(<>)
PROCESSOR_RELATIONSHIP	ENDS
PPROCESSOR_RELATIONSHIP typedef ptr PROCESSOR_RELATIONSHIP

NUMA_NODE_RELATIONSHIP	STRUC
NodeNumber		dd ?
Reserved		db 20 dup(?)
GroupMask		GROUP_AFFINITY <>
NUMA_NODE_RELATIONSHIP	ENDS
PNUMA_NODE_RELATIONSHIP typedef ptr NUMA_NODE_RELATIONSHIP

CACHE_RELATIONSHIP	STRUC
Level			db ?
Associativity		db ?
LineSize		dw ?
CacheSize		dd ?
Type			PROCESSOR_CACHE_TYPE ?
Reserved		db 20 dup(?)
GroupMask		GROUP_AFFINITY <>
CACHE_RELATIONSHIP	ENDS
PCACHE_RELATIONSHIP	typedef ptr CACHE_RELATIONSHIP

PROCESSOR_GROUP_INFO	STRUC
MaximumProcessorCount	db ?
ActiveProcessorCount	db ?
Reserved		db 38 dup(?)
ActiveProcessorMask	KAFFINITY ?
PROCESSOR_GROUP_INFO	ENDS
PPROCESSOR_GROUP_INFO	typedef ptr PROCESSOR_GROUP_INFO

GROUP_RELATIONSHIP	STRUC
MaximumGroupCount	dw ?
ActiveGroupCount	dw ?
Reserved		db 20 dup(?)
GroupInfo		PROCESSOR_GROUP_INFO ANYSIZE_ARRAY dup(<>)
GROUP_RELATIONSHIP	ENDS
PGROUP_RELATIONSHIP	typedef ptr GROUP_RELATIONSHIP

SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX STRUC
Relationship		LOGICAL_PROCESSOR_RELATIONSHIP ?
Size			dd ?
UNION
Processor		PROCESSOR_RELATIONSHIP <>
NumaNode		NUMA_NODE_RELATIONSHIP <>
Cache			CACHE_RELATIONSHIP <>
_Group			GROUP_RELATIONSHIP <>
ENDS
SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX ENDS
PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX typedef ptr SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX

.enum _CPU_SET_INFORMATION_TYPE {
    CpuSetInformation
    }
CPU_SET_INFORMATION_TYPE typedef _CPU_SET_INFORMATION_TYPE
PCPU_SET_INFORMATION_TYPE typedef ptr _CPU_SET_INFORMATION_TYPE

define SYSTEM_CPU_SET_INFORMATION_PARKED 0x1
define SYSTEM_CPU_SET_INFORMATION_ALLOCATED 0x2
define SYSTEM_CPU_SET_INFORMATION_ALLOCATED_TO_TARGET_PROCESS 0x4
define SYSTEM_CPU_SET_INFORMATION_REALTIME 0x8

_SYSTEM_CPU_SET_INFORMATION struct
Size			DWORD ?
Type			CPU_SET_INFORMATION_TYPE ?
union
 struct CpuSet
  Id			DWORD ?
  _Group		WORD ?
  LogicalProcessorIndex BYTE ?
  CoreIndex		BYTE ?
  LastLevelCacheIndex	BYTE ?
  NumaNodeIndex		BYTE ?
  EfficiencyClass	BYTE ?
  union
   AllFlags		BYTE ?
   struct
    record
     Parked		BYTE : 1 ?
     Allocated		BYTE : 1 ?
     AllocatedToTargetProcess BYTE : 1 ?
     RealTime		BYTE : 1 ?
     ReservedFlags	BYTE : 4 ?
    ends
   ends
  ends
  union
   Reserved		DWORD ?
   SchedulingClass	BYTE ?
  ends
  AllocationTag		DWORD64 ?
 ends
ends
_SYSTEM_CPU_SET_INFORMATION ends
SYSTEM_CPU_SET_INFORMATION  typedef _SYSTEM_CPU_SET_INFORMATION
PSYSTEM_CPU_SET_INFORMATION typedef ptr _SYSTEM_CPU_SET_INFORMATION


SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION STRUC
CycleTime		DWORD64 ?
SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION ENDS
PSYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION typedef ptr SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION


PROCESSOR_INTEL_386	equ 386
PROCESSOR_INTEL_486	equ 486
PROCESSOR_INTEL_PENTIUM equ 586
PROCESSOR_INTEL_IA64	equ 2200
PROCESSOR_AMD_X8664	equ 8664
PROCESSOR_MIPS_R4000	equ 4000
PROCESSOR_ALPHA_21064	equ 21064
PROCESSOR_PPC_601	equ 601
PROCESSOR_PPC_603	equ 603
PROCESSOR_PPC_604	equ 604
PROCESSOR_PPC_620	equ 620
PROCESSOR_HITACHI_SH3	equ 10003
PROCESSOR_HITACHI_SH3E	equ 10004
PROCESSOR_HITACHI_SH4	equ 10005
PROCESSOR_MOTOROLA_821	equ 821
PROCESSOR_SHx_SH3	equ 103
PROCESSOR_SHx_SH4	equ 104
PROCESSOR_STRONGARM	equ 2577
PROCESSOR_ARM720	equ 1824
PROCESSOR_ARM820	equ 2080
PROCESSOR_ARM920	equ 2336
PROCESSOR_ARM_7TDMI	equ 70001
PROCESSOR_OPTIL		equ 0x494f

PROCESSOR_ARCHITECTURE_INTEL		equ 0
PROCESSOR_ARCHITECTURE_MIPS		equ 1
PROCESSOR_ARCHITECTURE_ALPHA		equ 2
PROCESSOR_ARCHITECTURE_PPC		equ 3
PROCESSOR_ARCHITECTURE_SHX		equ 4
PROCESSOR_ARCHITECTURE_ARM		equ 5
PROCESSOR_ARCHITECTURE_IA64		equ 6
PROCESSOR_ARCHITECTURE_ALPHA64		equ 7
PROCESSOR_ARCHITECTURE_MSIL		equ 8
PROCESSOR_ARCHITECTURE_AMD64		equ 9
PROCESSOR_ARCHITECTURE_IA32_ON_WIN64	equ 10
PROCESSOR_ARCHITECTURE_NEUTRAL		equ 11
PROCESSOR_ARCHITECTURE_UNKNOWN		equ 0xFFFF

PF_FLOATING_POINT_PRECISION_ERRATA	equ 0
PF_FLOATING_POINT_EMULATED		equ 1
PF_COMPARE_EXCHANGE_DOUBLE		equ 2
PF_MMX_INSTRUCTIONS_AVAILABLE		equ 3
PF_PPC_MOVEMEM_64BIT_OK			equ 4
PF_ALPHA_BYTE_INSTRUCTIONS		equ 5
PF_XMMI_INSTRUCTIONS_AVAILABLE		equ 6
PF_AMD3D_INSTRUCTIONS_AVAILABLE		equ 7
PF_RDTSC_INSTRUCTION_AVAILABLE		equ 8
PF_PAE_ENABLED				equ 9
PF_XMMI64_INSTRUCTIONS_AVAILABLE	equ 10
PF_SSE_DAZ_MODE_AVAILABLE		equ 11
PF_NX_ENABLED				equ 12
PF_SSE3_INSTRUCTIONS_AVAILABLE		equ 13
PF_COMPARE_EXCHANGE128			equ 14
PF_COMPARE64_EXCHANGE128		equ 15
PF_CHANNELS_ENABLED			equ 16
PF_XSAVE_ENABLED			equ 17
PF_ARM_VFP_32_REGISTERS_AVAILABLE	equ 18
PF_ARM_NEON_INSTRUCTIONS_AVAILABLE	equ 19
PF_SECOND_LEVEL_ADDRESS_TRANSLATION	equ 20
PF_VIRT_FIRMWARE_ENABLED		equ 21
PF_RDWRFSGSBASE_AVAILABLE		equ 22
PF_FASTFAIL_AVAILABLE			equ 23
PF_ARM_DIVIDE_INSTRUCTION_AVAILABLE	equ 24
PF_ARM_64BIT_LOADSTORE_ATOMIC		equ 25
PF_ARM_EXTERNAL_CACHE_AVAILABLE		equ 26
PF_ARM_FMAC_INSTRUCTIONS_AVAILABLE	equ 27
PF_RDRAND_INSTRUCTION_AVAILABLE		equ 28

XSTATE_LEGACY_FLOATING_POINT		equ 0
XSTATE_LEGACY_SSE			equ 1
XSTATE_GSSE				equ 2

XSTATE_MASK_LEGACY_FLOATING_POINT	equ (1 shl (XSTATE_LEGACY_FLOATING_POINT))
XSTATE_MASK_LEGACY_SSE			equ (1 shl (XSTATE_LEGACY_SSE))
XSTATE_MASK_LEGACY			equ XSTATE_MASK_LEGACY_FLOATING_POINT or XSTATE_MASK_LEGACY_SSE
XSTATE_MASK_GSSE			equ (1 shl (XSTATE_GSSE))

MAXIMUM_XSTATE_FEATURES			equ 64

XSTATE_FEATURE		STRUC
_Offset			dd ?
Size			dd ?
XSTATE_FEATURE		ENDS
PXSTATE_FEATURE		typedef ptr XSTATE_FEATURE

XSTATE_CONFIGURATION	STRUC
EnabledFeatures		DWORD64 ?
Size			dd ?
OptimizedSave		dd ?	;: 1;
Features		XSTATE_FEATURE MAXIMUM_XSTATE_FEATURES dup(<>)
XSTATE_CONFIGURATION	ENDS
PXSTATE_CONFIGURATION	typedef ptr XSTATE_CONFIGURATION

SYSTEM_FLAG_REMOTE_BOOT_CLIENT	equ 0x00000001
SYSTEM_FLAG_DISKLESS_CLIENT	equ 0x00000002

MEMORY_BASIC_INFORMATION	STRUC SIZE_T
BaseAddress			PVOID ?
AllocationBase			PVOID ?
AllocationProtect		dd ?
RegionSize			SIZE_T ?
State				dd ?
Protect				dd ?
Type				dd ?
MEMORY_BASIC_INFORMATION	ENDS
PMEMORY_BASIC_INFORMATION	typedef ptr MEMORY_BASIC_INFORMATION

MEMORY_BASIC_INFORMATION32	STRUC 4
BaseAddress			dd ?
AllocationBase			dd ?
AllocationProtect		dd ?
RegionSize			dd ?
State				dd ?
Protect				dd ?
Type				dd ?
MEMORY_BASIC_INFORMATION32	ENDS
PMEMORY_BASIC_INFORMATION32	typedef ptr MEMORY_BASIC_INFORMATION32

MEMORY_BASIC_INFORMATION64	STRUC 8
BaseAddress			ULONGLONG ?
AllocationBase			ULONGLONG ?
AllocationProtect		dd ?
RegionSize			ULONGLONG ?
State				dd ?
Protect				dd ?
Type				dd ?
MEMORY_BASIC_INFORMATION64	ENDS
PMEMORY_BASIC_INFORMATION64	typedef ptr MEMORY_BASIC_INFORMATION64

define CFG_CALL_TARGET_VALID	0x00000001
define CFG_CALL_TARGET_PROCESSED 0x00000002
define CFG_CALL_TARGET_CONVERT_EXPORT_SUPPRESSED_TO_VALID 0x00000004

_CFG_CALL_TARGET_INFO		struct
Offs				ULONG_PTR ?
Flags				ULONG_PTR ?
_CFG_CALL_TARGET_INFO		ends
CFG_CALL_TARGET_INFO		typedef _CFG_CALL_TARGET_INFO
PCFG_CALL_TARGET_INFO		typedef ptr _CFG_CALL_TARGET_INFO


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
Type				dd ?
MEMORY_BASIC_INFORMATION_VLM	ENDS
PMEMORY_BASIC_INFORMATION_VLM	typedef ptr MEMORY_BASIC_INFORMATION_VLM

SECTION_QUERY		equ 0x0001
SECTION_MAP_WRITE	equ 0x0002
SECTION_MAP_READ	equ 0x0004
SECTION_MAP_EXECUTE	equ 0x0008
SECTION_EXTEND_SIZE	equ 0x0010

SECTION_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED or SECTION_QUERY or \
			    SECTION_MAP_WRITE	or \
			    SECTION_MAP_READ	or \
			    SECTION_MAP_EXECUTE or \
			    SECTION_EXTEND_SIZE

SESSION_QUERY_ACCESS	equ 0x0001
SESSION_MODIFY_ACCESS	equ 0x0002

SESSION_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED OR \
			    SESSION_QUERY_ACCESS OR \
			    SESSION_MODIFY_ACCESS

PAGE_NOACCESS		equ 0x01
PAGE_READONLY		equ 0x02
PAGE_READWRITE		equ 0x04
PAGE_WRITECOPY		equ 0x08
PAGE_EXECUTE		equ 0x10
PAGE_EXECUTE_READ	equ 0x20
PAGE_EXECUTE_READWRITE	equ 0x40
PAGE_EXECUTE_WRITECOPY	equ 0x80
PAGE_GUARD		equ 0x100
PAGE_NOCACHE		equ 0x200
PAGE_WRITECOMBINE	equ 0x400

MEM_COMMIT		equ 0x1000
MEM_RESERVE		equ 0x2000
MEM_DECOMMIT		equ 0x4000
MEM_RELEASE		equ 0x8000
MEM_FREE		equ 0x10000
MEM_PRIVATE		equ 0x20000
MEM_MAPPED		equ 0x40000
MEM_RESET		equ 0x80000
MEM_TOP_DOWN		equ 0x100000
MEM_WRITE_WATCH		equ 0x200000
MEM_PHYSICAL		equ 0x400000
MEM_ROTATE		equ 0x800000
MEM_LARGE_PAGES		equ 0x20000000
MEM_4MB_PAGES		equ 0x80000000

SEC_FILE		equ 0x800000
SEC_IMAGE		equ 0x1000000
SEC_PROTECTED_IMAGE	equ 0x2000000
SEC_VLM			equ 0x2000000
SEC_RESERVE		equ 0x4000000
SEC_COMMIT		equ 0x8000000
SEC_NOCACHE		equ 0x10000000
SEC_WRITECOMBINE	equ 0x40000000
SEC_LARGE_PAGES		equ 0x80000000
MEM_IMAGE		equ SEC_IMAGE
WRITE_WATCH_FLAG_RESET	equ 0x01

FILE_READ_DATA		equ 0x0001
FILE_LIST_DIRECTORY	equ 0x0001

FILE_WRITE_DATA		equ 0x0002
FILE_ADD_FILE		equ 0x0002

FILE_APPEND_DATA	equ 0x0004
FILE_ADD_SUBDIRECTORY	equ 0x0004
FILE_CREATE_PIPE_INSTANCE equ 0x0004

FILE_READ_EA		equ 0x0008
FILE_WRITE_EA		equ 0x0010
FILE_EXECUTE		equ 0x0020
FILE_TRAVERSE		equ 0x0020
FILE_DELETE_CHILD	equ 0x0040
FILE_READ_ATTRIBUTES	equ 0x0080
FILE_WRITE_ATTRIBUTES	equ 0x0100

FILE_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0x3FF
FILE_GENERIC_READ	equ STANDARD_RIGHTS_READ or FILE_READ_DATA or FILE_READ_ATTRIBUTES or FILE_READ_EA or SYNCHRONIZE
FILE_GENERIC_WRITE	equ STANDARD_RIGHTS_WRITE or FILE_WRITE_DATA or FILE_WRITE_ATTRIBUTES or FILE_WRITE_EA or FILE_APPEND_DATA or SYNCHRONIZE
FILE_GENERIC_EXECUTE	equ STANDARD_RIGHTS_EXECUTE or FILE_READ_ATTRIBUTES or FILE_EXECUTE or SYNCHRONIZE

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
FILE_NAMED_STREAMS		equ 0x00040000
FILE_READ_ONLY_VOLUME		equ 0x00080000
FILE_SEQUENTIAL_WRITE_ONCE	equ 0x00100000
FILE_SUPPORTS_TRANSACTIONS	equ 0x00200000
FILE_SUPPORTS_HARD_LINKS	equ 0x00400000
FILE_SUPPORTS_EXTENDED_ATTRIBUTES equ 0x00800000
FILE_SUPPORTS_OPEN_BY_FILE_ID	equ 0x01000000
FILE_SUPPORTS_USN_JOURNAL	equ 0x02000000
FILE_SUPPORTS_INTEGRITY_STREAMS equ 0x04000000
FILE_INVALID_FILE_ID		equ -1

FILE_ID_128		STRUC
Identifier		db 16 dup(?)
FILE_ID_128		ENDS
PFILE_ID_128		typedef ptr FILE_ID_128

FILE_NOTIFY_INFORMATION STRUC
NextEntryOffset		dd ?
Action			dd ?
FileNameLength		dd ?
FileName		WCHAR ?
FILE_NOTIFY_INFORMATION ENDS
PFILE_NOTIFY_INFORMATION typedef ptr FILE_NOTIFY_INFORMATION

FILE_SEGMENT_ELEMENT	UNION
Buffer			PVOID64 ?
Alignment		ULONGLONG ?
FILE_SEGMENT_ELEMENT	ENDS
PFILE_SEGMENT_ELEMENT	typedef ptr FILE_SEGMENT_ELEMENT

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

REPARSE_POINT_INFORMATION	STRUC
ReparseDataLength		dw ?
UnparsedNameLength		dw ?
REPARSE_POINT_INFORMATION	ENDS
PREPARSE_POINT_INFORMATION	typedef ptr REPARSE_POINT_INFORMATION

MAXIMUM_REPARSE_DATA_BUFFER_SIZE equ 16 * 1024

IO_REPARSE_TAG_RESERVED_ZERO	equ 0
IO_REPARSE_TAG_RESERVED_ONE	equ 1
IO_REPARSE_TAG_RESERVED_RANGE	equ IO_REPARSE_TAG_RESERVED_ONE

IsReparseTagMicrosoft macro _tag
	exitm<_tag and 0x80000000>
	endm

IsReparseTagHighLatency macro _tag
	exitm<_tag and 0x40000000>
	endm
IsReparseTagNameSurrogate macro _tag
	exitm<_tag and 0x20000000>
	endm

IO_REPARSE_TAG_MOUNT_POINT	equ 0xA0000003
IO_REPARSE_TAG_HSM		equ 0xC0000004
IO_REPARSE_TAG_HSM2		equ 0x80000006
IO_REPARSE_TAG_SIS		equ 0x80000007
IO_REPARSE_TAG_WIM		equ 0x80000008
IO_REPARSE_TAG_CSV		equ 0x80000009
IO_REPARSE_TAG_DFS		equ 0x8000000A
IO_REPARSE_TAG_SYMLINK		equ 0xA000000C
IO_REPARSE_TAG_DFSR		equ 0x80000012

IO_COMPLETION_MODIFY_STATE	equ 0x0002
IO_COMPLETION_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED OR SYNCHRONIZE OR 0x3

DUPLICATE_CLOSE_SOURCE		equ 0x00000001
DUPLICATE_SAME_ACCESS		equ 0x00000002

PROCESSOR_PERF_BOOST_POLICY_DISABLED	equ 0
PROCESSOR_PERF_BOOST_POLICY_MAX		equ 100
CORE_PARKING_POLICY_CHANGE_IDEAL	equ 0
CORE_PARKING_POLICY_CHANGE_SINGLE	equ 1
CORE_PARKING_POLICY_CHANGE_ROCKET	equ 2
;CORE_PARKING_POLICY_CHANGE_MAX CORE_PARKING_POLICY_CHANGE_ROCKET
POWER_DEVICE_IDLE_POLICY_PERFORMANCE	equ 0
POWER_DEVICE_IDLE_POLICY_CONSERVATIVE	equ 1

.enum SYSTEM_POWER_STATE {
    PowerSystemUnspecified = 0,
    PowerSystemWorking	   = 1,
    PowerSystemSleeping1   = 2,
    PowerSystemSleeping2   = 3,
    PowerSystemSleeping3   = 4,
    PowerSystemHibernate   = 5,
    PowerSystemShutdown	   = 6,
    PowerSystemMaximum	   = 7
    }

PSYSTEM_POWER_STATE typedef ptr SYSTEM_POWER_STATE

define POWER_SYSTEM_MAXIMUM 7

.enum POWER_ACTION {
    PowerActionNone = 0,
    PowerActionReserved,
    PowerActionSleep,
    PowerActionHibernate,
    PowerActionShutdown,
    PowerActionShutdownReset,
    PowerActionShutdownOff,
    PowerActionWarmEject
    }

PPOWER_ACTION typedef ptr POWER_ACTION

.enum DEVICE_POWER_STATE {
    PowerDeviceUnspecified,
    PowerDeviceD0,
    PowerDeviceD1,
    PowerDeviceD2,
    PowerDeviceD3,
    PowerDeviceMaximum
    }

PDEVICE_POWER_STATE typedef ptr DEVICE_POWER_STATE

.enum MONITOR_DISPLAY_STATE {
    PowerMonitorOff,
    PowerMonitorOn,
    PowerMonitorDim
    }

PMONITOR_DISPLAY_STATE typedef ptr MONITOR_DISPLAY_STATE

.enum USER_ACTIVITY_PRESENCE {
    PowerUserPresent = 0,
    PowerUserNotPresent,
    PowerUserInactive,
    PowerUserMaximum,
    PowerUserInvalid = PowerUserMaximum
    }

PUSER_ACTIVITY_PRESENCE typedef ptr USER_ACTIVITY_PRESENCE


ES_SYSTEM_REQUIRED		equ 0x00000001
ES_DISPLAY_REQUIRED		equ 0x00000002
ES_USER_PRESENT			equ 0x00000004
ES_AWAYMODE_REQUIRED		equ 0x00000040
ES_CONTINUOUS			equ 0x80000000

EXECUTION_STATE			typedef DWORD
PEXECUTION_STATE		typedef ptr DWORD

.enum LATENCY_TIME {
    LT_DONT_CARE,
    LT_LOWEST_LATENCY
    }

if (_WIN32_WINNT GE _WIN32_WINNT_WIN7)
DIAGNOSTIC_REASON_VERSION		equ 0
DIAGNOSTIC_REASON_SIMPLE_STRING		equ 0x00000001
DIAGNOSTIC_REASON_DETAILED_STRING	equ 0x00000002
DIAGNOSTIC_REASON_NOT_SPECIFIED		equ 0x80000000
DIAGNOSTIC_REASON_INVALID_FLAGS		equ (not 0x80000003)
endif

POWER_REQUEST_CONTEXT_VERSION		equ 0
POWER_REQUEST_CONTEXT_SIMPLE_STRING	equ 0x00000001
POWER_REQUEST_CONTEXT_DETAILED_STRING	equ 0x00000002

.enum POWER_REQUEST_TYPE {
    PowerRequestDisplayRequired,
    PowerRequestSystemRequired,
    PowerRequestAwayModeRequired,
    PowerRequestExecutionRequired
    }

PPOWER_REQUEST_TYPE typedef ptr POWER_REQUEST_TYPE

if (NTDDI_VERSION GE NTDDI_WINXP)

PDCAP_D0_SUPPORTED		equ 0x00000001
PDCAP_D1_SUPPORTED		equ 0x00000002
PDCAP_D2_SUPPORTED		equ 0x00000004
PDCAP_D3_SUPPORTED		equ 0x00000008
PDCAP_WAKE_FROM_D0_SUPPORTED	equ 0x00000010
PDCAP_WAKE_FROM_D1_SUPPORTED	equ 0x00000020
PDCAP_WAKE_FROM_D2_SUPPORTED	equ 0x00000040
PDCAP_WAKE_FROM_D3_SUPPORTED	equ 0x00000080
PDCAP_WARM_EJECT_SUPPORTED	equ 0x00000100

CM_POWER_DATA		STRUC
PD_Size			dd ?
PD_MostRecentPowerState DEVICE_POWER_STATE ?
PD_Capabilities		dd ?
PD_D1Latency		dd ?
PD_D2Latency		dd ?
PD_D3Latency		dd ?
PD_PowerStateMapping	DEVICE_POWER_STATE POWER_SYSTEM_MAXIMUM dup(?)
PD_DeepestSystemWake	SYSTEM_POWER_STATE ?
CM_POWER_DATA		ENDS
PCM_POWER_DATA		typedef ptr CM_POWER_DATA

endif

.enum SYSTEM_POWER_CONDITION {
    PoAc,
    PoDc,
    PoHot,
    PoConditionMaximum
    }

SYSTEM_POWER_CONDITION	typedef sdword ; enum {
PoAc			equ 0
PoDc			equ 1
PoHot			equ 2
PoConditionMaximum	equ 3

SET_POWER_SETTING_VALUE STRUC
Version			dd ?
Guid			GUID <>
PowerCondition		SYSTEM_POWER_CONDITION ?
DataLength		dd ?
Data			db ANYSIZE_ARRAY dup(?)
SET_POWER_SETTING_VALUE ENDS
PSET_POWER_SETTING_VALUE typedef ptr SET_POWER_SETTING_VALUE

POWER_SETTING_VALUE_VERSION equ 1

NOTIFY_USER_POWER_SETTING STRUC
Guid			GUID <>
NOTIFY_USER_POWER_SETTING ENDS
PNOTIFY_USER_POWER_SETTING typedef ptr NOTIFY_USER_POWER_SETTING

APPLICATIONLAUNCH_SETTING_VALUE	 STRUC
ActivationTime		LARGE_INTEGER <>
Flags			dd ?
ButtonInstanceID	dd ?
APPLICATIONLAUNCH_SETTING_VALUE ENDS
PAPPLICATIONLAUNCH_SETTING_VALUE typedef ptr APPLICATIONLAUNCH_SETTING_VALUE

.enum POWER_PLATFORM_ROLE {
    PlatformRoleUnspecified = 0,
    PlatformRoleDesktop,
    PlatformRoleMobile,
    PlatformRoleWorkstation,
    PlatformRoleEnterpriseServer,
    PlatformRoleSOHOServer,
    PlatformRoleAppliancePC,
    PlatformRolePerformanceServer, ;; v1 last supported
    PlatformRoleSlate,		   ;; v2 last supported
    PlatformRoleMaximum
    }

PPOWER_PLATFORM_ROLE typedef ptr POWER_PLATFORM_ROLE

if (NTDDI_VERSION GE NTDDI_WINXP) OR NOT defined(_BATCLASS_)
BATTERY_REPORTING_SCALE STRUC
Granularity		dd ?
Capacity		dd ?
BATTERY_REPORTING_SCALE ENDS
PBATTERY_REPORTING_SCALE typedef ptr BATTERY_REPORTING_SCALE
endif

PPM_WMI_LEGACY_PERFSTATE STRUC
Frequency		dd ?
Flags			dd ?
PercentFrequency	dd ?
PPM_WMI_LEGACY_PERFSTATE ENDS
PPPM_WMI_LEGACY_PERFSTATE typedef ptr PPM_WMI_LEGACY_PERFSTATE

PPM_WMI_IDLE_STATE	STRUC
Latency			dd ?
Power			dd ?
TimeCheck		dd ?
PromotePercent		db ?
DemotePercent		db ?
StateType		db ?
Reserved		db ?
StateFlags		dd ?
Context			dd ?
IdleHandler		dd ?
Reserved1		dd ?
PPM_WMI_IDLE_STATE	ENDS
PPPM_WMI_IDLE_STATE	typedef ptr PPM_WMI_IDLE_STATE

PPM_WMI_IDLE_STATES	STRUC
Type			dd ?
Count			dd ?
TargetState		dd ?
OldState		dd ?
TargetProcessors	dd ?
State			PPM_WMI_IDLE_STATE ANYSIZE_ARRAY dup(<>)
PPM_WMI_IDLE_STATES	ENDS
PPPM_WMI_IDLE_STATES	typedef ptr PPM_WMI_IDLE_STATES

PPM_WMI_IDLE_STATES_EX	STRUC
Type			dd ?
Count			dd ?
TargetState		dd ?
OldState		dd ?
TargetProcessors	PVOID ?
State			PPM_WMI_IDLE_STATE ANYSIZE_ARRAY dup(<>)
PPM_WMI_IDLE_STATES_EX	ENDS
PPPM_WMI_IDLE_STATES_EX typedef ptr PPM_WMI_IDLE_STATES_EX

PPM_WMI_PERF_STATE	STRUC
Frequency		dd ?
Power			dd ?
PercentFrequency	db ?
IncreaseLevel		db ?
DecreaseLevel		db ?
Type			db ?
IncreaseTime		dd ?
DecreaseTime		dd ?
Control			dd ?
Status			dd ?
HitCount		dd ?
Reserved1		dd ?
Reserved2		dd ?
Reserved3		dd ?
PPM_WMI_PERF_STATE	ENDS
PPPM_WMI_PERF_STATE	typedef ptr PPM_WMI_PERF_STATE

PPM_WMI_PERF_STATES	STRUC
Count			dd ?
MaxFrequency		dd ?
CurrentState		dd ?
MaxPerfState		dd ?
MinPerfState		dd ?
LowestPerfState		dd ?
ThermalConstraint	dd ?
BusyAdjThreshold	db ?
PolicyType		db ?
Type			db ?
Reserved		db ?
TimerInterval		dd ?
TargetProcessors	dd ?
PStateHandler		dd ?
PStateContext		dd ?
TStateHandler		dd ?
TStateContext		dd ?
FeedbackHandler		dd ?
Reserved1		dd ?
Reserved2		dd ?
State			PPM_WMI_IDLE_STATE ANYSIZE_ARRAY dup(<>)
PPM_WMI_PERF_STATES	ENDS
PPPM_WMI_PERF_STATES	typedef ptr PPM_WMI_PERF_STATES

PPM_WMI_PERF_STATES_EX	STRUC
Count			dd ?
MaxFrequency		dd ?
CurrentState		dd ?
MaxPerfState		dd ?
MinPerfState		dd ?
LowestPerfState		dd ?
ThermalConstraint	dd ?
BusyAdjThreshold	db ?
PolicyType		db ?
Type			db ?
Reserved		db ?
TimerInterval		dd ?
TargetProcessors	PVOID ?
PStateHandler		dd ?
PStateContext		dd ?
TStateHandler		dd ?
TStateContext		dd ?
FeedbackHandler		dd ?
Reserved1		dd ?
Reserved2		dd ?
State			PPM_WMI_PERF_STATE ANYSIZE_ARRAY dup(<>)
PPM_WMI_PERF_STATES_EX	ENDS
PPPM_WMI_PERF_STATES_EX typedef ptr PPM_WMI_PERF_STATES_EX

PROC_IDLE_BUCKET_COUNT	equ 6

PPM_IDLE_STATE_ACCOUNTING STRUC
IdleTransitions		dd ?
FailedTransitions	dd ?
InvalidBucketIndex	dd ?
TotalTime		dd ?
IdleTimeBuckets		dd PROC_IDLE_BUCKET_COUNT dup(?)
PPM_IDLE_STATE_ACCOUNTING ENDS
PPPM_IDLE_STATE_ACCOUNTING typedef ptr PPM_IDLE_STATE_ACCOUNTING

PPM_IDLE_ACCOUNTING	STRUC
StateCount		dd ?
TotalTransitions	dd ?
ResetCount		dd ?
StartTime		dd ?
State			PPM_IDLE_STATE_ACCOUNTING ANYSIZE_ARRAY dup(<>)
PPM_IDLE_ACCOUNTING	ENDS
PPPM_IDLE_ACCOUNTING	typedef ptr PPM_IDLE_ACCOUNTING

PROC_IDLE_BUCKET_COUNT_EX equ 16

PPM_IDLE_STATE_BUCKET_EX STRUC
TotalTimeUs		dd ?
MinTimeUs		dd ?
MaxTimeUs		dd ?
Count			dd ?
PPM_IDLE_STATE_BUCKET_EX ENDS
PPPM_IDLE_STATE_BUCKET_EX typedef ptr PPM_IDLE_STATE_BUCKET_EX

PPM_IDLE_STATE_ACCOUNTING_EX STRUC
TotalTime		dd ?
IdleTransitions		dd ?
FailedTransitions	dd ?
InvalidBucketIndex	dd ?
MinTimeUs		dd ?
MaxTimeUs		dd ?
IdleTimeBuckets		PPM_IDLE_STATE_BUCKET_EX PROC_IDLE_BUCKET_COUNT_EX dup(<>)
PPM_IDLE_STATE_ACCOUNTING_EX ENDS
PPPM_IDLE_STATE_ACCOUNTING_EX typedef ptr PPM_IDLE_STATE_ACCOUNTING_EX

PPM_IDLE_ACCOUNTING_EX	STRUC
StateCount		dd ?
TotalTransitions	dd ?
ResetCount		dd ?
StartTime		dd ?
State			PPM_IDLE_STATE_ACCOUNTING_EX ANYSIZE_ARRAY dup(<>)
PPM_IDLE_ACCOUNTING_EX	ENDS
PPPM_IDLE_ACCOUNTING_EX typedef ptr PPM_IDLE_ACCOUNTING_EX


ACPI_PPM_SOFTWARE_ALL	equ 0xFC
ACPI_PPM_SOFTWARE_ANY	equ 0xFD
ACPI_PPM_HARDWARE_ALL	equ 0xFE


MS_PPM_SOFTWARE_ALL	equ 0x1


PPM_FIRMWARE_ACPI1C2	equ 0x00000001
PPM_FIRMWARE_ACPI1C3	equ 0x00000002
PPM_FIRMWARE_ACPI1TSTATES equ 0x00000004
PPM_FIRMWARE_CST	equ 0x00000008
PPM_FIRMWARE_CSD	equ 0x00000010
PPM_FIRMWARE_PCT	equ 0x00000020
PPM_FIRMWARE_PSS	equ 0x00000040
PPM_FIRMWARE_XPSS	equ 0x00000080
PPM_FIRMWARE_PPC	equ 0x00000100
PPM_FIRMWARE_PSD	equ 0x00000200
PPM_FIRMWARE_PTC	equ 0x00000400
PPM_FIRMWARE_TSS	equ 0x00000800
PPM_FIRMWARE_TPC	equ 0x00001000
PPM_FIRMWARE_TSD	equ 0x00002000
PPM_FIRMWARE_PCCH	equ 0x00004000
PPM_FIRMWARE_PCCP	equ 0x00008000

PPM_PERFSTATE_EVENT	STRUC
State			dd ?
Status			dd ?
Latency			dd ?
Speed			dd ?
Processor		dd ?
PPM_PERFSTATE_EVENT	ENDS
PPPM_PERFSTATE_EVENT	typedef ptr PPM_PERFSTATE_EVENT

PPM_PERFSTATE_DOMAIN_EVENT STRUC
State			dd ?
Latency			dd ?
Speed			dd ?
Processors		dd ?
PPM_PERFSTATE_DOMAIN_EVENT ENDS
PPPM_PERFSTATE_DOMAIN_EVENT typedef ptr PPM_PERFSTATE_DOMAIN_EVENT

PPM_IDLESTATE_EVENT	STRUC
NewState		dd ?
OldState		dd ?
Processors		dd ?
PPM_IDLESTATE_EVENT	ENDS
PPPM_IDLESTATE_EVENT	typedef ptr PPM_IDLESTATE_EVENT

PPM_THERMALCHANGE_EVENT STRUC
ThermalConstraint	dd ?
Processors		dd ?
PPM_THERMALCHANGE_EVENT ENDS
PPPM_THERMALCHANGE_EVENT typedef ptr PPM_THERMALCHANGE_EVENT

PPM_THERMAL_POLICY_EVENT STRUC
Mode			db ?
Processors		dd ?
PPM_THERMAL_POLICY_EVENT ENDS
PPPM_THERMAL_POLICY_EVENT typedef ptr PPM_THERMAL_POLICY_EVENT

POWER_ACTION_POLICY	STRUC
Action			POWER_ACTION ?
Flags			dd ?
EventCode		dd ?
POWER_ACTION_POLICY	ENDS
PPOWER_ACTION_POLICY	typedef ptr POWER_ACTION_POLICY

POWER_ACTION_QUERY_ALLOWED	equ 0x00000001
POWER_ACTION_UI_ALLOWED		equ 0x00000002
POWER_ACTION_OVERRIDE_APPS	equ 0x00000004
POWER_ACTION_PSEUDO_TRANSITION	equ 0x08000000
POWER_ACTION_LIGHTEST_FIRST	equ 0x10000000
POWER_ACTION_LOCK_CONSOLE	equ 0x20000000
POWER_ACTION_DISABLE_WAKES	equ 0x40000000
POWER_ACTION_CRITICAL		equ 0x80000000

POWER_LEVEL_USER_NOTIFY_TEXT	equ 0x00000001
POWER_LEVEL_USER_NOTIFY_SOUND	equ 0x00000002
POWER_LEVEL_USER_NOTIFY_EXEC	equ 0x00000004
POWER_USER_NOTIFY_BUTTON	equ 0x00000008
POWER_USER_NOTIFY_SHUTDOWN	equ 0x00000010
POWER_USER_NOTIFY_FORCED_SHUTDOWN equ 0x00000020
POWER_FORCE_TRIGGER_RESET	equ 0x80000000


BATTERY_DISCHARGE_FLAGS_EVENTCODE_MASK equ 0x00000007
BATTERY_DISCHARGE_FLAGS_ENABLE equ 0x80000000

SYSTEM_POWER_LEVEL	STRUC
Enable			BOOLEAN ?
Spare			db 3 dup(?)
BatteryLevel		dd ?
PowerPolicy		POWER_ACTION_POLICY <>
MinSystemState		SYSTEM_POWER_STATE ?
SYSTEM_POWER_LEVEL	ENDS
PSYSTEM_POWER_LEVEL	typedef ptr SYSTEM_POWER_LEVEL

NUM_DISCHARGE_POLICIES	equ 4
DISCHARGE_POLICY_CRITICAL equ 0
DISCHARGE_POLICY_LOW	equ 1

SYSTEM_POWER_POLICY	STRUC
Revision		dd ?
PowerButton		POWER_ACTION_POLICY <>
SleepButton		POWER_ACTION_POLICY <>
LidClose		POWER_ACTION_POLICY <>
LidOpenWake		SYSTEM_POWER_STATE ?
Reserved		dd ?
Idle			POWER_ACTION_POLICY <>
IdleTimeout		dd ?
IdleSensitivity		db ?
DynamicThrottle		db ?
Spare2			db 2 dup(?)
MinSleep		SYSTEM_POWER_STATE ?
MaxSleep		SYSTEM_POWER_STATE ?
ReducedLatencySleep	SYSTEM_POWER_STATE ?
WinLogonFlags		dd ?
Spare3			dd ?
DozeS4Timeout		dd ?
BroadcastCapacityResolution dd ?
DischargePolicy		SYSTEM_POWER_LEVEL NUM_DISCHARGE_POLICIES dup(<>)
VideoTimeout		dd ?
VideoDimDisplay		BOOLEAN ?
VideoReserved		dd 3 dup(?)
SpindownTimeout		dd ?
OptimizeForPower	BOOLEAN ?
FanThrottleTolerance	db ?
ForcedThrottle		db ?
MinThrottle		db ?
OverThrottled		POWER_ACTION_POLICY <>
SYSTEM_POWER_POLICY	ENDS
PSYSTEM_POWER_POLICY	typedef ptr SYSTEM_POWER_POLICY

PROCESSOR_IDLESTATE_POLICY_COUNT equ 0x3

PROCESSOR_IDLESTATE_INFO STRUC
TimeCheck		dd ?
DemotePercent		db ?
PromotePercent		db ?
Spare			db 2 dup(?)
PROCESSOR_IDLESTATE_INFO ENDS
PPROCESSOR_IDLESTATE_INFO typedef ptr PROCESSOR_IDLESTATE_INFO

PROCESSOR_IDLESTATE_POLICY STRUC
Revision		dw ?
UNION Flags
 AsWORD			dw ?
 RECORD
  AllowScaling		dw :  1 ?
  Disabled		dw :  1 ?
  Reserved		dw : 14 ?
 ENDS
ENDS
PolicyCount		dd ?
Policy			PROCESSOR_IDLESTATE_INFO PROCESSOR_IDLESTATE_POLICY_COUNT dup(<>)
PROCESSOR_IDLESTATE_POLICY ENDS
PPROCESSOR_IDLESTATE_POLICY typedef ptr PROCESSOR_IDLESTATE_POLICY

PO_THROTTLE_NONE	equ 0
PO_THROTTLE_CONSTANT	equ 1
PO_THROTTLE_DEGRADE	equ 2
PO_THROTTLE_ADAPTIVE	equ 3
PO_THROTTLE_MAXIMUM	equ 4

PROCESSOR_POWER_POLICY_INFO STRUC
TimeCheck		dd ?
DemoteLimit		dd ?
PromoteLimit		dd ?
DemotePercent		db ?
PromotePercent		db ?
Spare			db 2 dup(?)
RECORD
 AllowDemotion		dd :  1 ?
 AllowPromotion		dd :  1 ?
 Reserved		dd : 30 ?
ENDS
PROCESSOR_POWER_POLICY_INFO ENDS
PPROCESSOR_POWER_POLICY_INFO typedef ptr PROCESSOR_POWER_POLICY_INFO

PROCESSOR_POWER_POLICY	STRUC
Revision		dd ?
DynamicThrottle		db ?
Spare			db 3 dup(?)
RECORD
 DisableCStates		dd :  1 ?
 Reserved		dd : 31 ?
ENDS
PolicyCount		dd ?
Policy			PROCESSOR_POWER_POLICY_INFO 3 dup(<>)
PROCESSOR_POWER_POLICY	ENDS
PPROCESSOR_POWER_POLICY typedef ptr PROCESSOR_POWER_POLICY

PROCESSOR_PERFSTATE_POLICY STRUC
Revision		dd ?
MaxThrottle		db ?
MinThrottle		db ?
BusyAdjThreshold	db ?
UNION Flags
 Spare			db ?
 UNION
  AsBYTE		db ?
  RECORD
   NoDomainAccounting	db : 1 ?
   IncreasePolicy	db : 2 ?
   DecreasePolicy	db : 2 ?
   Reserved		db : 3 ?
  ENDS
 ENDS
ENDS
TimeCheck		dd ?
IncreaseTime		dd ?
DecreaseTime		dd ?
IncreasePercent		dd ?
DecreasePercent		dd ?
PROCESSOR_PERFSTATE_POLICY ENDS
PPROCESSOR_PERFSTATE_POLICY typedef ptr PROCESSOR_PERFSTATE_POLICY

ADMINISTRATOR_POWER_POLICY STRUC
MinSleep		SYSTEM_POWER_STATE ?
MaxSleep		SYSTEM_POWER_STATE ?
MinVideoTimeout		dd ?
MaxVideoTimeout		dd ?
MinSpindownTimeout	dd ?
MaxSpindownTimeout	dd ?
ADMINISTRATOR_POWER_POLICY ENDS
PADMINISTRATOR_POWER_POLICY typedef ptr ADMINISTRATOR_POWER_POLICY

SYSTEM_BATTERY_STATE	STRUC
AcOnLine		BOOLEAN ?
BatteryPresent		BOOLEAN ?
Charging		BOOLEAN ?
Discharging		BOOLEAN ?
Spare1			BOOLEAN 4 dup(?)
MaxCapacity		dd ?
RemainingCapacity	dd ?
Rate			dd ?
EstimatedTime		dd ?
DefaultAlert1		dd ?
DefaultAlert2		dd ?
SYSTEM_BATTERY_STATE	ENDS
PSYSTEM_BATTERY_STATE	typedef ptr SYSTEM_BATTERY_STATE

.pragma pack(push, 2)

IMAGE_DOS_SIGNATURE	equ 0x5A4D
IMAGE_OS2_SIGNATURE	equ 0x454E
IMAGE_OS2_SIGNATURE_LE	equ 0x454C
IMAGE_VXD_SIGNATURE	equ 0x454C
IMAGE_NT_SIGNATURE	equ 0x00004550

IMAGE_DOS_HEADER	STRUC
e_magic			dw ?
e_cblp			dw ?
e_cp			dw ?
e_crlc			dw ?
e_cparhdr		dw ?
e_minalloc		dw ?
e_maxalloc		dw ?
e_ss			dw ?
e_sp			dw ?
e_csum			dw ?
e_ip			dw ?
e_cs			dw ?
e_lfarlc		dw ?
e_ovno			dw ?
e_res			dw 4 dup(?)
e_oemid			dw ?
e_oeminfo		dw ?
e_res2			dw 10 dup(?)
e_lfanew		dd ?
IMAGE_DOS_HEADER	ENDS
PIMAGE_DOS_HEADER	typedef ptr IMAGE_DOS_HEADER

ifndef __UNIX__
externdef __ImageBase:IMAGE_DOS_HEADER
endif

IMAGE_OS2_HEADER	STRUC
ne_magic		dw ?
ne_ver			CHAR ?
ne_rev			CHAR ?
ne_enttab		dw ?
ne_cbenttab		dw ?
ne_crc			LONG ?
ne_flags		dw ?
ne_autodata		dw ?
ne_heap			dw ?
ne_stack		dw ?
ne_csip			LONG ?
ne_sssp			LONG ?
ne_cseg			dw ?
ne_cmod			dw ?
ne_cbnrestab		dw ?
ne_segtab		dw ?
ne_rsrctab		dw ?
ne_restab		dw ?
ne_modtab		dw ?
ne_imptab		dw ?
ne_nrestab		LONG ?
ne_cmovent		dw ?
ne_align		dw ?
ne_cres			dw ?
ne_exetyp		db ?
ne_flagsothers		db ?
ne_pretthunks		dw ?
ne_psegrefbytes		dw ?
ne_swaparea		dw ?
ne_expver		dw ?
IMAGE_OS2_HEADER	ENDS
PIMAGE_OS2_HEADER	typedef ptr IMAGE_OS2_HEADER

IMAGE_VXD_HEADER	STRUC
e32_magic		dw ?
e32_border		db ?
e32_worder		db ?
e32_level		dd ?
e32_cpu			dw ?
e32_os			dw ?
e32_ver			dd ?
e32_mflags		dd ?
e32_mpages		dd ?
e32_startobj		dd ?
e32_eip			dd ?
e32_stackobj		dd ?
e32_esp			dd ?
e32_pagesize		dd ?
e32_lastpagesize	dd ?
e32_fixupsize		dd ?
e32_fixupsum		dd ?
e32_ldrsize		dd ?
e32_ldrsum		dd ?
e32_objtab		dd ?
e32_objcnt		dd ?
e32_objmap		dd ?
e32_itermap		dd ?
e32_rsrctab		dd ?
e32_rsrccnt		dd ?
e32_restab		dd ?
e32_enttab		dd ?
e32_dirtab		dd ?
e32_dircnt		dd ?
e32_fpagetab		dd ?
e32_frectab		dd ?
e32_impmod		dd ?
e32_impmodcnt		dd ?
e32_impproc		dd ?
e32_pagesum		dd ?
e32_datapage		dd ?
e32_preload		dd ?
e32_nrestab		dd ?
e32_cbnrestab		dd ?
e32_nressum		dd ?
e32_autodata		dd ?
e32_debuginfo		dd ?
e32_debuglen		dd ?
e32_instpreload		dd ?
e32_instdemand		dd ?
e32_heapsize		dd ?
e32_res3		db 12 dup(?)
e32_winresoff		dd ?
e32_winreslen		dd ?
e32_devid		dw ?
e32_ddkver		dw ?
IMAGE_VXD_HEADER	ENDS
PIMAGE_VXD_HEADER	typedef ptr IMAGE_VXD_HEADER

.pragma pack(pop)

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


IMAGE_SIZEOF_FILE_HEADER equ 20

IMAGE_FILE_RELOCS_STRIPPED	equ 0x0001
IMAGE_FILE_EXECUTABLE_IMAGE	equ 0x0002
IMAGE_FILE_LINE_NUMS_STRIPPED	equ 0x0004
IMAGE_FILE_LOCAL_SYMS_STRIPPED	equ 0x0008
IMAGE_FILE_AGGRESIVE_WS_TRIM	equ 0x0010
IMAGE_FILE_LARGE_ADDRESS_AWARE	equ 0x0020
IMAGE_FILE_BYTES_REVERSED_LO	equ 0x0080
IMAGE_FILE_32BIT_MACHINE	equ 0x0100
IMAGE_FILE_DEBUG_STRIPPED	equ 0x0200
IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP equ 0x0400
IMAGE_FILE_NET_RUN_FROM_SWAP	equ 0x0800
IMAGE_FILE_SYSTEM		equ 0x1000
IMAGE_FILE_DLL			equ 0x2000
IMAGE_FILE_UP_SYSTEM_ONLY	equ 0x4000
IMAGE_FILE_BYTES_REVERSED_HI	equ 0x8000

IMAGE_FILE_MACHINE_UNKNOWN	equ 0
IMAGE_FILE_MACHINE_I386		equ 0x014c
IMAGE_FILE_MACHINE_R3000	equ 0x0162
IMAGE_FILE_MACHINE_R4000	equ 0x0166
IMAGE_FILE_MACHINE_R10000	equ 0x0168
IMAGE_FILE_MACHINE_WCEMIPSV2	equ 0x0169
IMAGE_FILE_MACHINE_ALPHA	equ 0x0184
IMAGE_FILE_MACHINE_SH3		equ 0x01a2
IMAGE_FILE_MACHINE_SH3DSP	equ 0x01a3
IMAGE_FILE_MACHINE_SH3E		equ 0x01a4
IMAGE_FILE_MACHINE_SH4		equ 0x01a6
IMAGE_FILE_MACHINE_SH5		equ 0x01a8
IMAGE_FILE_MACHINE_ARM		equ 0x01c0
IMAGE_FILE_MACHINE_THUMB	equ 0x01c2
IMAGE_FILE_MACHINE_AM33		equ 0x01d3
IMAGE_FILE_MACHINE_POWERPC	equ 0x01F0
IMAGE_FILE_MACHINE_POWERPCFP	equ 0x01f1
IMAGE_FILE_MACHINE_IA64		equ 0x0200
IMAGE_FILE_MACHINE_MIPS16	equ 0x0266
IMAGE_FILE_MACHINE_ALPHA64	equ 0x0284
IMAGE_FILE_MACHINE_MIPSFPU	equ 0x0366
IMAGE_FILE_MACHINE_MIPSFPU16	equ 0x0466
IMAGE_FILE_MACHINE_AXP64	equ IMAGE_FILE_MACHINE_ALPHA64
IMAGE_FILE_MACHINE_TRICORE	equ 0x0520
IMAGE_FILE_MACHINE_CEF		equ 0x0CEF
IMAGE_FILE_MACHINE_EBC		equ 0x0EBC
IMAGE_FILE_MACHINE_AMD64	equ 0x8664
IMAGE_FILE_MACHINE_M32R		equ 0x9041
IMAGE_FILE_MACHINE_CEE		equ 0xC0EE


IMAGE_DATA_DIRECTORY	STRUC
VirtualAddress		dd ?
Size			dd ?
IMAGE_DATA_DIRECTORY	ENDS
PIMAGE_DATA_DIRECTORY	typedef ptr IMAGE_DATA_DIRECTORY

IMAGE_NUMBEROF_DIRECTORY_ENTRIES equ 16

IMAGE_OPTIONAL_HEADER32		STRUC
Magic				dw ?
MajorLinkerVersion		db ?
MinorLinkerVersion		db ?
SizeOfCode			dd ?
SizeOfInitializedData		dd ?
SizeOfUninitializedData		dd ?
AddressOfEntryPoint		dd ?
BaseOfCode			dd ?
BaseOfData			dd ?
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
ImageBase			ULONGLONG ?
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
SizeOfStackReserve		ULONGLONG ?
SizeOfStackCommit		ULONGLONG ?
SizeOfHeapReserve		ULONGLONG ?
SizeOfHeapCommit		ULONGLONG ?
LoaderFlags			dd ?
NumberOfRvaAndSizes		dd ?
DataDirectory			IMAGE_DATA_DIRECTORY IMAGE_NUMBEROF_DIRECTORY_ENTRIES dup(<>)
IMAGE_OPTIONAL_HEADER64		ENDS
PIMAGE_OPTIONAL_HEADER64	typedef ptr IMAGE_OPTIONAL_HEADER64

IMAGE_SIZEOF_ROM_OPTIONAL_HEADER  equ 56
IMAGE_SIZEOF_STD_OPTIONAL_HEADER  equ 28
IMAGE_SIZEOF_NT_OPTIONAL32_HEADER equ 224
IMAGE_SIZEOF_NT_OPTIONAL64_HEADER equ 240

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
OptionalHeader		IMAGE_ROM_OPTIONAL_HEADER <>
IMAGE_ROM_HEADERS	ENDS
PIMAGE_ROM_HEADERS	typedef ptr IMAGE_ROM_HEADERS

ifdef _WIN64
IMAGE_NT_HEADERS	typedef IMAGE_NT_HEADERS64
PIMAGE_NT_HEADERS	typedef PIMAGE_NT_HEADERS64
else
IMAGE_NT_HEADERS	typedef IMAGE_NT_HEADERS32
PIMAGE_NT_HEADERS	typedef PIMAGE_NT_HEADERS32
endif

;; IMAGE_FIRST_SECTION doesn't need 32/64 versions since the file header is the same either way.

IMAGE_FIRST_SECTION macro ntheader
	movzx	eax,[ntheader].FileHeader.SizeOfOptionalHeader
	add	eax,FIELD_OFFSET( IMAGE_NT_HEADERS, OptionalHeader )
	add	rax,ntheader
	retm	<rax>
	endm

IMAGE_SUBSYSTEM_UNKNOWN		equ 0
IMAGE_SUBSYSTEM_NATIVE		equ 1
IMAGE_SUBSYSTEM_WINDOWS_GUI	equ 2
IMAGE_SUBSYSTEM_WINDOWS_CUI	equ 3
IMAGE_SUBSYSTEM_OS2_CUI		equ 5
IMAGE_SUBSYSTEM_POSIX_CUI	equ 7
IMAGE_SUBSYSTEM_NATIVE_WINDOWS	equ 8
IMAGE_SUBSYSTEM_WINDOWS_CE_GUI	equ 9
IMAGE_SUBSYSTEM_EFI_APPLICATION equ 10
IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER equ 11
IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER equ 12
IMAGE_SUBSYSTEM_EFI_ROM		equ 13
IMAGE_SUBSYSTEM_XBOX		equ 14
IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION equ 16


;IMAGE_LIBRARY_PROCESS_INIT		equ 0x0001
;IMAGE_LIBRARY_PROCESS_TERM		equ 0x0002
;IMAGE_LIBRARY_THREAD_INIT		equ 0x0004
;IMAGE_LIBRARY_THREAD_TERM		equ 0x0008
IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA equ 0x0020
IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE	equ 0x0040
IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY equ 0x0080
IMAGE_DLLCHARACTERISTICS_NX_COMPAT	equ 0x0100
IMAGE_DLLCHARACTERISTICS_NO_ISOLATION	equ 0x0200
IMAGE_DLLCHARACTERISTICS_NO_SEH		equ 0x0400
IMAGE_DLLCHARACTERISTICS_NO_BIND	equ 0x0800
IMAGE_DLLCHARACTERISTICS_WDM_DRIVER	equ 0x2000
IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE equ 0x8000

IMAGE_DIRECTORY_ENTRY_EXPORT		equ 0
IMAGE_DIRECTORY_ENTRY_IMPORT		equ 1
IMAGE_DIRECTORY_ENTRY_RESOURCE		equ 2
IMAGE_DIRECTORY_ENTRY_EXCEPTION		equ 3
IMAGE_DIRECTORY_ENTRY_SECURITY		equ 4
IMAGE_DIRECTORY_ENTRY_BASERELOC		equ 5
IMAGE_DIRECTORY_ENTRY_DEBUG		equ 6
;IMAGE_DIRECTORY_ENTRY_COPYRIGHT	equ 7
IMAGE_DIRECTORY_ENTRY_ARCHITECTURE	equ 7
IMAGE_DIRECTORY_ENTRY_GLOBALPTR		equ 8
IMAGE_DIRECTORY_ENTRY_TLS		equ 9
IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG	equ 10
IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT	equ 11
IMAGE_DIRECTORY_ENTRY_IAT		equ 12
IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT	equ 13
IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR	equ 14


ANON_OBJECT_HEADER	STRUC
Sig1			dw ?
Sig2			dw ?
Version			dw ?
Machine			dw ?
TimeDateStamp		dd ?
ClassID			CLSID <>
SizeOfData		dd ?
ANON_OBJECT_HEADER	ENDS

ANON_OBJECT_HEADER_V2	STRUC
Sig1			dw ?
Sig2			dw ?
Version			dw ?
Machine			dw ?
TimeDateStamp		dd ?
ClassID			CLSID <>
SizeOfData		dd ?
Flags			dd ?
MetaDataSize		dd ?
MetaDataOffset		dd ?
ANON_OBJECT_HEADER_V2	ENDS

ANON_OBJECT_HEADER_BIGOBJ  STRUC
Sig1			dw ?
Sig2			dw ?
Version			dw ?
Machine			dw ?
TimeDateStamp		dd ?
ClassID			CLSID <>
SizeOfData		dd ?
Flags			dd ?
MetaDataSize		dd ?
MetaDataOffset		dd ?
NumberOfSections	dd ?
PointerToSymbolTable	dd ?
NumberOfSymbols		dd ?
ANON_OBJECT_HEADER_BIGOBJ ENDS


IMAGE_SIZEOF_SHORT_NAME equ 8

IMAGE_SECTION_HEADER	STRUC
Name			sbyte IMAGE_SIZEOF_SHORT_NAME dup(?)
UNION Misc
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
PIMAGE_SECTION_HEADER	typedef ptr IMAGE_SECTION_HEADER

IMAGE_SIZEOF_SECTION_HEADER	equ 40

IMAGE_SCN_TYPE_NO_PAD		equ 0x00000008

IMAGE_SCN_CNT_CODE		equ 0x00000020
IMAGE_SCN_CNT_INITIALIZED_DATA	equ 0x00000040
IMAGE_SCN_CNT_UNINITIALIZED_DATA equ 0x00000080

IMAGE_SCN_LNK_OTHER		equ 0x00000100
IMAGE_SCN_LNK_INFO		equ 0x00000200
;IMAGE_SCN_TYPE_OVER		equ 0x00000400
IMAGE_SCN_LNK_REMOVE		equ 0x00000800
IMAGE_SCN_LNK_COMDAT		equ 0x00001000
;IMAGE_SCN_MEM_PROTECTED - Obsolete equ 0x00004000
IMAGE_SCN_NO_DEFER_SPEC_EXC	equ 0x00004000
IMAGE_SCN_GPREL			equ 0x00008000
IMAGE_SCN_MEM_FARDATA		equ 0x00008000
IMAGE_SCN_MEM_PURGEABLE		equ 0x00020000
IMAGE_SCN_MEM_16BIT		equ 0x00020000
IMAGE_SCN_MEM_LOCKED		equ 0x00040000
IMAGE_SCN_MEM_PRELOAD		equ 0x00080000

IMAGE_SCN_ALIGN_1BYTES		equ 0x00100000
IMAGE_SCN_ALIGN_2BYTES		equ 0x00200000
IMAGE_SCN_ALIGN_4BYTES		equ 0x00300000
IMAGE_SCN_ALIGN_8BYTES		equ 0x00400000
IMAGE_SCN_ALIGN_16BYTES		equ 0x00500000
IMAGE_SCN_ALIGN_32BYTES		equ 0x00600000
IMAGE_SCN_ALIGN_64BYTES		equ 0x00700000
IMAGE_SCN_ALIGN_128BYTES	equ 0x00800000
IMAGE_SCN_ALIGN_256BYTES	equ 0x00900000
IMAGE_SCN_ALIGN_512BYTES	equ 0x00A00000
IMAGE_SCN_ALIGN_1024BYTES	equ 0x00B00000
IMAGE_SCN_ALIGN_2048BYTES	equ 0x00C00000
IMAGE_SCN_ALIGN_4096BYTES	equ 0x00D00000
IMAGE_SCN_ALIGN_8192BYTES	equ 0x00E00000
IMAGE_SCN_ALIGN_MASK		equ 0x00F00000

IMAGE_SCN_LNK_NRELOC_OVFL	equ 0x01000000
IMAGE_SCN_MEM_DISCARDABLE	equ 0x02000000
IMAGE_SCN_MEM_NOT_CACHED	equ 0x04000000
IMAGE_SCN_MEM_NOT_PAGED		equ 0x08000000
IMAGE_SCN_MEM_SHARED		equ 0x10000000
IMAGE_SCN_MEM_EXECUTE		equ 0x20000000
IMAGE_SCN_MEM_READ		equ 0x40000000
IMAGE_SCN_MEM_WRITE		equ 0x80000000

IMAGE_SCN_SCALE_INDEX	equ 0x00000001

IMAGE_SYMBOL		STRUC WORD
UNION
    ShortName		sbyte 8 dup(?)
    STRUC
	_Short		dd ?
	_Long		dd ?
    ENDS
    LongName		dd 2 dup(?)
ENDS
Value			dd ?
SectionNumber		dw ?
Type			dw ?
StorageClass		db ?
NumberOfAuxSymbols	db ?
IMAGE_SYMBOL		ENDS
PIMAGE_SYMBOL		typedef ptr IMAGE_SYMBOL

IMAGE_SIZEOF_SYMBOL	equ 18

IMAGE_SYMBOL_EX		STRUC
UNION
    ShortName		sbyte 8 dup(?)
    STRUC
	_Short		dd ?
	_Long		dd ?
    ENDS
    LongName		dd 2 dup(?)
ENDS
Value			dd ?
SectionNumber		LONG ?
Type			dw ?
StorageClass		db ?
NumberOfAuxSymbols	db ?
IMAGE_SYMBOL_EX		ENDS
PIMAGE_SYMBOL_EX	typedef ptr IMAGE_SYMBOL_EX

IMAGE_SYM_UNDEFINED		equ 0
IMAGE_SYM_ABSOLUTE		equ -1
IMAGE_SYM_DEBUG			equ -2
IMAGE_SYM_SECTION_MAX		equ 0xFEFF
IMAGE_SYM_SECTION_MAX_EX	equ MAXLONG

IMAGE_SYM_TYPE_NULL		equ 0x0000
IMAGE_SYM_TYPE_VOID		equ 0x0001
IMAGE_SYM_TYPE_CHAR		equ 0x0002
IMAGE_SYM_TYPE_SHORT		equ 0x0003
IMAGE_SYM_TYPE_INT		equ 0x0004
IMAGE_SYM_TYPE_LONG		equ 0x0005
IMAGE_SYM_TYPE_FLOAT		equ 0x0006
IMAGE_SYM_TYPE_DOUBLE		equ 0x0007
IMAGE_SYM_TYPE_STRUCT		equ 0x0008
IMAGE_SYM_TYPE_UNION		equ 0x0009
IMAGE_SYM_TYPE_ENUM		equ 0x000A
IMAGE_SYM_TYPE_MOE		equ 0x000B
IMAGE_SYM_TYPE_BYTE		equ 0x000C
IMAGE_SYM_TYPE_WORD		equ 0x000D
IMAGE_SYM_TYPE_UINT		equ 0x000E
IMAGE_SYM_TYPE_DWORD		equ 0x000F
IMAGE_SYM_TYPE_PCODE		equ 0x8000

IMAGE_SYM_DTYPE_NULL		equ 0
IMAGE_SYM_DTYPE_POINTER		equ 1
IMAGE_SYM_DTYPE_FUNCTION	equ 2
IMAGE_SYM_DTYPE_ARRAY		equ 3

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

IMAGE_SYM_CLASS_FAR_EXTERNAL	    equ 0x0044

IMAGE_SYM_CLASS_BLOCK		    equ 0x0064
IMAGE_SYM_CLASS_FUNCTION	    equ 0x0065
IMAGE_SYM_CLASS_END_OF_STRUCT	    equ 0x0066
IMAGE_SYM_CLASS_FILE		    equ 0x0067
IMAGE_SYM_CLASS_SECTION		    equ 0x0068
IMAGE_SYM_CLASS_WEAK_EXTERNAL	    equ 0x0069
IMAGE_SYM_CLASS_CLR_TOKEN	    equ 0x006B

N_BTMASK    equ 0x000F
N_TMASK	    equ 0x0030
N_TMASK1    equ 0x00C0
N_TMASK2    equ 0x00F0
N_BTSHFT    equ 4
N_TSHIFT    equ 2

BTYPE	macro x
	exitm<((x) and N_BTMASK)>
	endm
ifndef ISPTR
ISPTR	macro x
	exitm<(((x) and N_TMASK) == (IMAGE_SYM_DTYPE_POINTER shl N_BTSHFT))>
	endm
endif
ifndef ISFCN
ISFCN	macro x
	exitm<(((x) and N_TMASK) == (IMAGE_SYM_DTYPE_FUNCTION shl N_BTSHFT))>
	endm
endif
ifndef ISARY
ISARY	macro x
	exitm<(((x) and N_TMASK) == (IMAGE_SYM_DTYPE_ARRAY shl N_BTSHFT))>
	endm
endif
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

.pragma pack(push, 2)

IMAGE_AUX_SYMBOL_TOKEN_DEF STRUC WORD
bAuxType		db ?
bReserved		db ?
SymbolTableIndex	dd ?
rgbReserved		db 12 dup(?)
IMAGE_AUX_SYMBOL_TOKEN_DEF ENDS
PIMAGE_AUX_SYMBOL_TOKEN_DEF typedef ptr IMAGE_AUX_SYMBOL_TOKEN_DEF

.pragma pack(pop)

IMAGE_AUX_SYMBOL	UNION
STRUC
 TagIndex		dd ?
 UNION
  STRUC
    Linenumber		dw ?
    Size		dw ?
  ENDS
  TotalSize		dd ?
 ENDS
 UNION
  STRUC
   PointerToLinenumber	dd ?
   PointerToNextFunction dd ?
  ENDS
   Dimension		dw 4 dup(?)
 ENDS
 TvIndex		dw ?
ENDS
STRUC
  Name			db IMAGE_SIZEOF_SYMBOL dup(?)
ENDS
STRUC
 Length			dd ?
 NumberOfRelocations	dw ?
 NumberOfLinenumbers	dw ?
 CheckSum		dd ?
 Number			dw ?
 Selection		db ?
ENDS
IMAGE_AUX_SYMBOL	ENDS
PIMAGE_AUX_SYMBOL	typedef ptr IMAGE_AUX_SYMBOL

IMAGE_AUX_SYMBOL_EX	UNION
STRUC Sym
 WeakDefaultSymIndex	dd ?
 WeakSearchType		dd ?
 rgbReserved		db 12 dup(?)
ENDS
STRUC File
 Name			db IMAGE_SYMBOL_EX dup(?)
ENDS
STRUC Section
 Length			dd ?
 NumberOfRelocations	dw ?
 NumberOfLinenumbers	dw ?
 CheckSum		dd ?
 Number			dw ?
 Selection		db ?
 bReserved		db ?
 HighNumber		dw ?
 rgbReserved		db 2 dup(?)
ENDS
STRUC
 TokenDef		IMAGE_AUX_SYMBOL_TOKEN_DEF <>
 rgbReserved		db 2 dup(?)
ENDS
STRUC CRC
 crc			dd ?
 rgbReserved		db 16 dup(?)
ENDS
IMAGE_AUX_SYMBOL_EX	ENDS
PIMAGE_AUX_SYMBOL_EX	typedef ptr IMAGE_AUX_SYMBOL_EX

IMAGE_AUX_SYMBOL_TYPE	typedef sdword ; enum
IMAGE_AUX_SYMBOL_TYPE_TOKEN_DEF equ 1

IMAGE_SIZEOF_AUX_SYMBOL equ 18

IMAGE_COMDAT_SELECT_NODUPLICATES    equ 1
IMAGE_COMDAT_SELECT_ANY		    equ 2
IMAGE_COMDAT_SELECT_SAME_SIZE	    equ 3
IMAGE_COMDAT_SELECT_EXACT_MATCH	    equ 4
IMAGE_COMDAT_SELECT_ASSOCIATIVE	    equ 5
IMAGE_COMDAT_SELECT_LARGEST	    equ 6
IMAGE_COMDAT_SELECT_NEWEST	    equ 7

IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY  equ 1
IMAGE_WEAK_EXTERN_SEARCH_LIBRARY    equ 2
IMAGE_WEAK_EXTERN_SEARCH_ALIAS	    equ 3

IMAGE_RELOCATION	STRUC 2
UNION
    VirtualAddress	dd ?
    RelocCount		dd ?
ENDS
SymbolTableIndex	dd ?
Type			dw ?
IMAGE_RELOCATION	ENDS
PIMAGE_RELOCATION	typedef ptr IMAGE_RELOCATION

IMAGE_SIZEOF_RELOCATION equ 10

IMAGE_REL_I386_ABSOLUTE		equ 0x0000
IMAGE_REL_I386_DIR16		equ 0x0001
IMAGE_REL_I386_REL16		equ 0x0002
IMAGE_REL_I386_DIR32		equ 0x0006
IMAGE_REL_I386_DIR32NB		equ 0x0007
IMAGE_REL_I386_SEG12		equ 0x0009
IMAGE_REL_I386_SECTION		equ 0x000A
IMAGE_REL_I386_SECREL		equ 0x000B
IMAGE_REL_I386_TOKEN		equ 0x000C
IMAGE_REL_I386_SECREL7		equ 0x000D
IMAGE_REL_I386_REL32		equ 0x0014

IMAGE_REL_MIPS_ABSOLUTE		equ 0x0000
IMAGE_REL_MIPS_REFHALF		equ 0x0001
IMAGE_REL_MIPS_REFWORD		equ 0x0002
IMAGE_REL_MIPS_JMPADDR		equ 0x0003
IMAGE_REL_MIPS_REFHI		equ 0x0004
IMAGE_REL_MIPS_REFLO		equ 0x0005
IMAGE_REL_MIPS_GPREL		equ 0x0006
IMAGE_REL_MIPS_LITERAL		equ 0x0007
IMAGE_REL_MIPS_SECTION		equ 0x000A
IMAGE_REL_MIPS_SECREL		equ 0x000B
IMAGE_REL_MIPS_SECRELLO		equ 0x000C
IMAGE_REL_MIPS_SECRELHI		equ 0x000D
IMAGE_REL_MIPS_TOKEN		equ 0x000E
IMAGE_REL_MIPS_JMPADDR16	equ 0x0010
IMAGE_REL_MIPS_REFWORDNB	equ 0x0022
IMAGE_REL_MIPS_PAIR		equ 0x0025

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
IMAGE_REL_ALPHA_SECRELLO	equ 0x0011
IMAGE_REL_ALPHA_SECRELHI	equ 0x0012
IMAGE_REL_ALPHA_REFQ3		equ 0x0013
IMAGE_REL_ALPHA_REFQ2		equ 0x0014
IMAGE_REL_ALPHA_REFQ1		equ 0x0015
IMAGE_REL_ALPHA_GPRELLO		equ 0x0016
IMAGE_REL_ALPHA_GPRELHI		equ 0x0017

IMAGE_REL_PPC_ABSOLUTE		equ 0x0000
IMAGE_REL_PPC_ADDR64		equ 0x0001
IMAGE_REL_PPC_ADDR32		equ 0x0002
IMAGE_REL_PPC_ADDR24		equ 0x0003
IMAGE_REL_PPC_ADDR16		equ 0x0004
IMAGE_REL_PPC_ADDR14		equ 0x0005
IMAGE_REL_PPC_REL24		equ 0x0006
IMAGE_REL_PPC_REL14		equ 0x0007
IMAGE_REL_PPC_TOCREL16		equ 0x0008
IMAGE_REL_PPC_TOCREL14		equ 0x0009

IMAGE_REL_PPC_ADDR32NB		equ 0x000A
IMAGE_REL_PPC_SECREL		equ 0x000B
IMAGE_REL_PPC_SECTION		equ 0x000C
IMAGE_REL_PPC_IFGLUE		equ 0x000D
IMAGE_REL_PPC_IMGLUE		equ 0x000E
IMAGE_REL_PPC_SECREL16		equ 0x000F
IMAGE_REL_PPC_REFHI		equ 0x0010
IMAGE_REL_PPC_REFLO		equ 0x0011
IMAGE_REL_PPC_PAIR		equ 0x0012
IMAGE_REL_PPC_SECRELLO		equ 0x0013
IMAGE_REL_PPC_SECRELHI		equ 0x0014
IMAGE_REL_PPC_GPREL		equ 0x0015
IMAGE_REL_PPC_TOKEN		equ 0x0016

IMAGE_REL_PPC_TYPEMASK		equ 0x00FF

IMAGE_REL_PPC_NEG		equ 0x0100
IMAGE_REL_PPC_BRTAKEN		equ 0x0200
IMAGE_REL_PPC_BRNTAKEN		equ 0x0400
IMAGE_REL_PPC_TOCDEFN		equ 0x0800

IMAGE_REL_SH3_ABSOLUTE		equ 0x0000
IMAGE_REL_SH3_DIRECT16		equ 0x0001
IMAGE_REL_SH3_DIRECT32		equ 0x0002
IMAGE_REL_SH3_DIRECT8		equ 0x0003
IMAGE_REL_SH3_DIRECT8_WORD	equ 0x0004
IMAGE_REL_SH3_DIRECT8_LONG	equ 0x0005
IMAGE_REL_SH3_DIRECT4		equ 0x0006
IMAGE_REL_SH3_DIRECT4_WORD	equ 0x0007
IMAGE_REL_SH3_DIRECT4_LONG	equ 0x0008
IMAGE_REL_SH3_PCREL8_WORD	equ 0x0009
IMAGE_REL_SH3_PCREL8_LONG	equ 0x000A
IMAGE_REL_SH3_PCREL12_WORD	equ 0x000B
IMAGE_REL_SH3_STARTOF_SECTION	equ 0x000C
IMAGE_REL_SH3_SIZEOF_SECTION	equ 0x000D
IMAGE_REL_SH3_SECTION		equ 0x000E
IMAGE_REL_SH3_SECREL		equ 0x000F
IMAGE_REL_SH3_DIRECT32_NB	equ 0x0010
IMAGE_REL_SH3_GPREL4_LONG	equ 0x0011
IMAGE_REL_SH3_TOKEN		equ 0x0012
IMAGE_REL_SHM_PCRELPT		equ 0x0013
IMAGE_REL_SHM_REFLO		equ 0x0014
IMAGE_REL_SHM_REFHALF		equ 0x0015
IMAGE_REL_SHM_RELLO		equ 0x0016
IMAGE_REL_SHM_RELHALF		equ 0x0017
IMAGE_REL_SHM_PAIR		equ 0x0018

IMAGE_REL_SH_NOMODE		equ 0x8000

IMAGE_REL_ARM_ABSOLUTE		equ 0x0000
IMAGE_REL_ARM_ADDR32		equ 0x0001
IMAGE_REL_ARM_ADDR32NB		equ 0x0002
IMAGE_REL_ARM_BRANCH24		equ 0x0003
IMAGE_REL_ARM_BRANCH11		equ 0x0004
IMAGE_REL_ARM_TOKEN		equ 0x0005
IMAGE_REL_ARM_GPREL12		equ 0x0006
IMAGE_REL_ARM_GPREL7		equ 0x0007
IMAGE_REL_ARM_BLX24		equ 0x0008
IMAGE_REL_ARM_BLX11		equ 0x0009
IMAGE_REL_ARM_SECTION		equ 0x000E
IMAGE_REL_ARM_SECREL		equ 0x000F

IMAGE_REL_AM_ABSOLUTE		equ 0x0000
IMAGE_REL_AM_ADDR32		equ 0x0001
IMAGE_REL_AM_ADDR32NB		equ 0x0002
IMAGE_REL_AM_CALL32		equ 0x0003
IMAGE_REL_AM_FUNCINFO		equ 0x0004
IMAGE_REL_AM_REL32_1		equ 0x0005
IMAGE_REL_AM_REL32_2		equ 0x0006
IMAGE_REL_AM_SECREL		equ 0x0007
IMAGE_REL_AM_SECTION		equ 0x0008
IMAGE_REL_AM_TOKEN		equ 0x0009

IMAGE_REL_AMD64_ABSOLUTE	equ 0x0000
IMAGE_REL_AMD64_ADDR64		equ 0x0001
IMAGE_REL_AMD64_ADDR32		equ 0x0002
IMAGE_REL_AMD64_ADDR32NB	equ 0x0003
IMAGE_REL_AMD64_REL32		equ 0x0004
IMAGE_REL_AMD64_REL32_1		equ 0x0005
IMAGE_REL_AMD64_REL32_2		equ 0x0006
IMAGE_REL_AMD64_REL32_3		equ 0x0007
IMAGE_REL_AMD64_REL32_4		equ 0x0008
IMAGE_REL_AMD64_REL32_5		equ 0x0009
IMAGE_REL_AMD64_SECTION		equ 0x000A
IMAGE_REL_AMD64_SECREL		equ 0x000B
IMAGE_REL_AMD64_SECREL7		equ 0x000C
IMAGE_REL_AMD64_TOKEN		equ 0x000D
IMAGE_REL_AMD64_SREL32		equ 0x000E
IMAGE_REL_AMD64_PAIR		equ 0x000F
IMAGE_REL_AMD64_SSPAN32		equ 0x0010

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
IMAGE_REL_IA64_DIR32NB		equ 0x0010
IMAGE_REL_IA64_SREL14		equ 0x0011
IMAGE_REL_IA64_SREL22		equ 0x0012
IMAGE_REL_IA64_SREL32		equ 0x0013
IMAGE_REL_IA64_UREL32		equ 0x0014
IMAGE_REL_IA64_PCREL60X		equ 0x0015
IMAGE_REL_IA64_PCREL60B		equ 0x0016
IMAGE_REL_IA64_PCREL60F		equ 0x0017
IMAGE_REL_IA64_PCREL60I		equ 0x0018
IMAGE_REL_IA64_PCREL60M		equ 0x0019
IMAGE_REL_IA64_IMMGPREL64	equ 0x001A
IMAGE_REL_IA64_TOKEN		equ 0x001B
IMAGE_REL_IA64_GPREL32		equ 0x001C
IMAGE_REL_IA64_ADDEND		equ 0x001F

IMAGE_REL_CEF_ABSOLUTE	equ 0x0000
IMAGE_REL_CEF_ADDR32	equ 0x0001
IMAGE_REL_CEF_ADDR64	equ 0x0002
IMAGE_REL_CEF_ADDR32NB	equ 0x0003
IMAGE_REL_CEF_SECTION	equ 0x0004
IMAGE_REL_CEF_SECREL	equ 0x0005
IMAGE_REL_CEF_TOKEN	equ 0x0006

IMAGE_REL_CEE_ABSOLUTE	equ 0x0000
IMAGE_REL_CEE_ADDR32	equ 0x0001
IMAGE_REL_CEE_ADDR64	equ 0x0002
IMAGE_REL_CEE_ADDR32NB	equ 0x0003
IMAGE_REL_CEE_SECTION	equ 0x0004
IMAGE_REL_CEE_SECREL	equ 0x0005
IMAGE_REL_CEE_TOKEN	equ 0x0006

IMAGE_REL_M32R_ABSOLUTE equ 0x0000
IMAGE_REL_M32R_ADDR32	equ 0x0001
IMAGE_REL_M32R_ADDR32NB equ 0x0002
IMAGE_REL_M32R_ADDR24	equ 0x0003
IMAGE_REL_M32R_GPREL16	equ 0x0004
IMAGE_REL_M32R_PCREL24	equ 0x0005
IMAGE_REL_M32R_PCREL16	equ 0x0006
IMAGE_REL_M32R_PCREL8	equ 0x0007
IMAGE_REL_M32R_REFHALF	equ 0x0008
IMAGE_REL_M32R_REFHI	equ 0x0009
IMAGE_REL_M32R_REFLO	equ 0x000A
IMAGE_REL_M32R_PAIR	equ 0x000B
IMAGE_REL_M32R_SECTION	equ 0x000C
IMAGE_REL_M32R_SECREL32 equ 0x000D
IMAGE_REL_M32R_TOKEN	equ 0x000E

IMAGE_REL_EBC_ABSOLUTE	equ 0x0000
IMAGE_REL_EBC_ADDR32NB	equ 0x0001
IMAGE_REL_EBC_REL32	equ 0x0002
IMAGE_REL_EBC_SECTION	equ 0x0003
IMAGE_REL_EBC_SECREL	equ 0x0004

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

X3_OPCODE_INST_WORD_X	equ 3
X3_OPCODE_SIZE_X	equ 4
X3_OPCODE_INST_WORD_POS_X equ 28
X3_OPCODE_SIGN_VAL_POS_X equ 0

X3_I_INST_WORD_X	equ 3
X3_I_SIZE_X		equ 1
X3_I_INST_WORD_POS_X	equ 27
X3_I_SIGN_VAL_POS_X	equ 59

X3_D_WH_INST_WORD_X	equ 3
X3_D_WH_SIZE_X		equ 3
X3_D_WH_INST_WORD_POS_X equ 24
X3_D_WH_SIGN_VAL_POS_X	equ 0

X3_IMM20_INST_WORD_X	equ 3
X3_IMM20_SIZE_X		equ 20
X3_IMM20_INST_WORD_POS_X equ 4
X3_IMM20_SIGN_VAL_POS_X equ 0

X3_IMM39_1_INST_WORD_X	equ 2
X3_IMM39_1_SIZE_X	equ 23
X3_IMM39_1_INST_WORD_POS_X equ 0
X3_IMM39_1_SIGN_VAL_POS_X equ 36

X3_IMM39_2_INST_WORD_X	equ 1
X3_IMM39_2_SIZE_X	equ 16
X3_IMM39_2_INST_WORD_POS_X equ 16
X3_IMM39_2_SIGN_VAL_POS_X equ 20

X3_P_INST_WORD_X	equ 3
X3_P_SIZE_X		equ 4
X3_P_INST_WORD_POS_X	equ 0
X3_P_SIGN_VAL_POS_X	equ 0

X3_TMPLT_INST_WORD_X	equ 0
X3_TMPLT_SIZE_X		equ 4
X3_TMPLT_INST_WORD_POS_X equ 0
X3_TMPLT_SIGN_VAL_POS_X equ 0

X3_BTYPE_QP_INST_WORD_X equ 2
X3_BTYPE_QP_SIZE_X	equ 9
X3_BTYPE_QP_INST_WORD_POS_X equ 23
X3_BTYPE_QP_INST_VAL_POS_X equ 0

X3_EMPTY_INST_WORD_X	equ 1
X3_EMPTY_SIZE_X		equ 2
X3_EMPTY_INST_WORD_POS_X equ 14
X3_EMPTY_INST_VAL_POS_X equ 0

IMAGE_LINENUMBER	STRUC
UNION
    SymbolTableIndex	dd ?
    VirtualAddress	dd ?
ENDS
Linenumber		dw ?
IMAGE_LINENUMBER	ENDS
PIMAGE_LINENUMBER	typedef ptr IMAGE_LINENUMBER

IMAGE_SIZEOF_LINENUMBER equ 6

IMAGE_BASE_RELOCATION	STRUC
VirtualAddress		dd ?
SizeOfBlock		dd ?
IMAGE_BASE_RELOCATION	ENDS
PIMAGE_BASE_RELOCATION	typedef ptr IMAGE_BASE_RELOCATION

IMAGE_SIZEOF_BASE_RELOCATION	equ 8

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

IMAGE_ARCHIVE_START_SIZE	equ 8
IMAGE_ARCHIVE_START		equ <"!",3Ch,"arch",3Eh,0Ah>
IMAGE_ARCHIVE_END		equ <"`",0Ah>
IMAGE_ARCHIVE_PAD		equ 10
IMAGE_ARCHIVE_LINKER_MEMBER	equ <"/               ">
IMAGE_ARCHIVE_LONGNAMES_MEMBER	equ <"//              ">

IMAGE_ARCHIVE_MEMBER_HEADER	STRUC
Name				db 16 dup(?)
Date				db 12 dup(?)
UserID				db  6 dup(?)
GroupID				db  6 dup(?)
Mode				db  8 dup(?)
Size				db 10 dup(?)
EndHeader			db  2 dup(?)
IMAGE_ARCHIVE_MEMBER_HEADER	ENDS
PIMAGE_ARCHIVE_MEMBER_HEADER	typedef ptr IMAGE_ARCHIVE_MEMBER_HEADER

IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR equ 60

IMAGE_EXPORT_DIRECTORY		STRUC
Characteristics			dd ?
TimeDateStamp			dd ?
MajorVersion			dw ?
MinorVersion			dw ?
Name				dd ?
Base				dd ?
NumberOfFunctions		dd ?
NumberOfNames			dd ?
AddressOfFunctions		dd ?
AddressOfNames			dd ?
AddressOfNameOrdinals		dd ?
IMAGE_EXPORT_DIRECTORY		ENDS
PIMAGE_EXPORT_DIRECTORY		typedef ptr IMAGE_EXPORT_DIRECTORY

IMAGE_IMPORT_BY_NAME	STRUC
Hint			dw ?
Name			db ?
IMAGE_IMPORT_BY_NAME	ENDS
PIMAGE_IMPORT_BY_NAME	typedef ptr IMAGE_IMPORT_BY_NAME

.pragma pack(push, 8)

IMAGE_THUNK_DATA64	STRUC
UNION
  ForwarderString	LPBYTE ?
  Function		PDWORD ?
  Ordinal		ULONGLONG ?
  AddressOfData		PIMAGE_IMPORT_BY_NAME ?
ENDS
IMAGE_THUNK_DATA64	ENDS

.pragma pack(pop)

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


CALLBACK(PIMAGE_TLS_CALLBACK, :PVOID, :DWORD, :PVOID)

IMAGE_TLS_DIRECTORY64	STRUC
StartAddressOfRawData	dq ?
EndAddressOfRawData	dq ?
AddressOfIndex		PDWORD ?
AddressOfCallBacks	PIMAGE_TLS_CALLBACK ?
SizeOfZeroFill		dd ?
RECORD Characteristics
 Reserved0		dd : 20 ?
 Alignment		dd :  4 ?
 Reserved1		dd :  8 ?
ENDS
IMAGE_TLS_DIRECTORY64	ENDS
PIMAGE_TLS_DIRECTORY64	typedef ptr IMAGE_TLS_DIRECTORY64

IMAGE_TLS_DIRECTORY32	STRUC
StartAddressOfRawData	dd ?
EndAddressOfRawData	dd ?
AddressOfIndex		PDWORD ?
AddressOfCallBacks	PIMAGE_TLS_CALLBACK ?
SizeOfZeroFill		dd ?
RECORD Characteristics
 Reserved0		dd : 20 ?
 Alignment		dd :  4 ?
 Reserved1		dd :  8 ?
ENDS
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
  Characteristics	dd ?
  OriginalFirstThunk	dd ?
ENDS
TimeDateStamp		dd ?
ForwarderChain		dd ?
Name			dd ?
FirstThunk		dd ?
IMAGE_IMPORT_DESCRIPTOR ENDS

PIMAGE_IMPORT_DESCRIPTOR typedef ptr IMAGE_IMPORT_DESCRIPTOR


IMAGE_BOUND_IMPORT_DESCRIPTOR STRUC
TimeDateStamp		dd ?
OffsetModuleName	dw ?
NumberOfModuleForwarderRefs dw ?
IMAGE_BOUND_IMPORT_DESCRIPTOR ENDS
PIMAGE_BOUND_IMPORT_DESCRIPTOR typedef ptr IMAGE_BOUND_IMPORT_DESCRIPTOR

IMAGE_BOUND_FORWARDER_REF STRUC
TimeDateStamp		dd ?
OffsetModuleName	dw ?
Reserved		dw ?
IMAGE_BOUND_FORWARDER_REF ENDS
PIMAGE_BOUND_FORWARDER_REF typedef ptr IMAGE_BOUND_FORWARDER_REF

IMAGE_DELAYLOAD_DESCRIPTOR STRUC
UNION Attributes
 AllAttributes		dd ?
 RECORD
  RvaBased		dd :  1 ?
  ReservedAttributes	dd : 31 ?
 ENDS
ENDS
DllNameRVA		dd ?
ModuleHandleRVA		dd ?
ImportAddressTableRVA	dd ?
ImportNameTableRVA	dd ?
BoundImportAddressTableRVA dd ?
UnloadInformationTableRVA dd ?
TimeDateStamp		dd ?
IMAGE_DELAYLOAD_DESCRIPTOR ENDS
PIMAGE_DELAYLOAD_DESCRIPTOR typedef ptr IMAGE_DELAYLOAD_DESCRIPTOR

IMAGE_MIX_ISA_LIMIT	equ 2

IMAGE_STUB_DIRECTORY	STRUC
SecondaryImportAddressTable dd ?
ExpectedISA		dw IMAGE_MIX_ISA_LIMIT dup(?)
StubAddressTable	dd IMAGE_MIX_ISA_LIMIT dup(?)
IMAGE_STUB_DIRECTORY	ENDS
PIMAGE_STUB_DIRECTORY	typedef ptr IMAGE_STUB_DIRECTORY

IA64_STUB_NOT_AVAILABLE equ -1
IA64_JMPE_MASK		equ 0x00ffffff
IA64_JMPE_MARKER	equ 0x0035000f

IMAGE_RESOURCE_DIRECTORY STRUC
Characteristics		dd ?
TimeDateStamp		dd ?
MajorVersion		dw ?
MinorVersion		dw ?
NumberOfNamedEntries	dw ?
NumberOfIdEntries	dw ?
IMAGE_RESOURCE_DIRECTORY ENDS
PIMAGE_RESOURCE_DIRECTORY typedef ptr IMAGE_RESOURCE_DIRECTORY

IMAGE_RESOURCE_NAME_IS_STRING	     equ 0x80000000
IMAGE_RESOURCE_DATA_IS_DIRECTORY     equ 0x80000000

IMAGE_RESOURCE_DIRECTORY_ENTRY STRUC
UNION
 Name			dd ?
 Id			dw ?
 RECORD
  NameOffset		dd : 31 ?
  NameIsString		dd :  1 ?
 ENDS
ENDS
UNION
  OffsetToData		dd ?
  RECORD
   OffsetToDirectory	dd : 31 ?
   DataIsDirectory	dd :  1 ?
  ENDS
ENDS
IMAGE_RESOURCE_DIRECTORY_ENTRY	ENDS
PIMAGE_RESOURCE_DIRECTORY_ENTRY typedef ptr IMAGE_RESOURCE_DIRECTORY_ENTRY

IMAGE_RESOURCE_DIRECTORY_STRING STRUC
Length			dw ?
NameString		db ?
IMAGE_RESOURCE_DIRECTORY_STRING ENDS
PIMAGE_RESOURCE_DIRECTORY_STRING typedef ptr IMAGE_RESOURCE_DIRECTORY_STRING

IMAGE_RESOURCE_DIR_STRING_U STRUC
Length			dw ?
NameString		dw ?
IMAGE_RESOURCE_DIR_STRING_U ENDS
PIMAGE_RESOURCE_DIR_STRING_U typedef ptr IMAGE_RESOURCE_DIR_STRING_U

IMAGE_RESOURCE_DATA_ENTRY STRUC
OffsetToData		dd ?
Size			dd ?
CodePage		dd ?
Reserved		dd ?
IMAGE_RESOURCE_DATA_ENTRY ENDS
PIMAGE_RESOURCE_DATA_ENTRY typedef ptr IMAGE_RESOURCE_DATA_ENTRY

IMAGE_LOAD_CONFIG_DIRECTORY STRUC
Characteristics		dd ?
TimeDateStamp		dd ?
MajorVersion		dw ?
MinorVersion		dw ?
GlobalFlagsClear	dd ?
GlobalFlagsSet		dd ?
CriticalSectionDefaultTimeout dd ?
DeCommitFreeBlockThreshold dd ?
DeCommitTotalFreeThreshold dd ?
LockPrefixTable		PVOID ?
MaximumAllocationSize	dd ?
VirtualMemoryThreshold	dd ?
ProcessHeapFlags	dd ?
ProcessAffinityMask	dd ?
CSDVersion		dw ?
Reserved1		dw ?
EditList		PVOID ?
Reserved		dd ?
IMAGE_LOAD_CONFIG_DIRECTORY ENDS
PIMAGE_LOAD_CONFIG_DIRECTORY typedef ptr IMAGE_LOAD_CONFIG_DIRECTORY

IMAGE_IA64_RUNTIME_FUNCTION_ENTRY STRUC
BeginAddress		dd ?
EndAddress		dd ?
UnwindInfoAddress	dd ?
IMAGE_IA64_RUNTIME_FUNCTION_ENTRY ENDS
PIMAGE_IA64_RUNTIME_FUNCTION_ENTRY typedef ptr IMAGE_IA64_RUNTIME_FUNCTION_ENTRY


IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY STRUC
BeginAddress		dd ?
EndAddress		dd ?
ExceptionHandler	dd ?
HandlerData		dd ?
PrologEndAddress	dd ?
IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY ENDS
PIMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY typedef ptr IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY

IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY STRUC
BeginAddress		dq ?
EndAddress		dq ?
ExceptionHandler	dq ?
HandlerData		dq ?
PrologEndAddress	dq ?
IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY ENDS

PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY typedef ptr IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY
IMAGE_AXP64_RUNTIME_FUNCTION_ENTRY typedef IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY
PIMAGE_AXP64_RUNTIME_FUNCTION_ENTRY typedef PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY

IMAGE_CE_RUNTIME_FUNCTION_ENTRY STRUC
FuncStart		dd ?
RECORD
 PrologLen		dd :  8 ?
 FuncLen		dd : 22 ?
 ThirtyTwoBit		dd :  1 ?
 ExceptionFlag		dd :  1 ?
ENDS
IMAGE_CE_RUNTIME_FUNCTION_ENTRY ENDS
PIMAGE_CE_RUNTIME_FUNCTION_ENTRY typedef ptr IMAGE_CE_RUNTIME_FUNCTION_ENTRY

ifdef _IA64_
IMAGE_RUNTIME_FUNCTION_ENTRY	typedef IMAGE_IA64_RUNTIME_FUNCTION_ENTRY
PIMAGE_RUNTIME_FUNCTION_ENTRY	typedef PIMAGE_IA64_RUNTIME_FUNCTION_ENTRY
else
IMAGE_RUNTIME_FUNCTION_ENTRY	typedef IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY
PIMAGE_RUNTIME_FUNCTION_ENTRY	typedef PIMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY
endif

IMAGE_DEBUG_DIRECTORY	STRUC
Characteristics		dd ?
TimeDateStamp		dd ?
MajorVersion		dw ?
MinorVersion		dw ?
Type			dd ?
SizeOfData		dd ?
AddressOfRawData	dd ?
PointerToRawData	dd ?
IMAGE_DEBUG_DIRECTORY	ENDS
PIMAGE_DEBUG_DIRECTORY	typedef ptr IMAGE_DEBUG_DIRECTORY

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
IMAGE_DEBUG_TYPE_CLSID		equ 11

IMAGE_COFF_SYMBOLS_HEADER STRUC
NumberOfSymbols		dd ?
LvaToFirstSymbol	dd ?
NumberOfLinenumbers	dd ?
LvaToFirstLinenumber	dd ?
RvaToFirstByteOfCode	dd ?
RvaToLastByteOfCode	dd ?
RvaToFirstByteOfData	dd ?
RvaToLastByteOfData	dd ?
IMAGE_COFF_SYMBOLS_HEADER ENDS
PIMAGE_COFF_SYMBOLS_HEADER typedef ptr IMAGE_COFF_SYMBOLS_HEADER

FRAME_FPO		equ 0
FRAME_TRAP		equ 1
FRAME_TSS		equ 2
FRAME_NONFPO		equ 3

FPO_DATA		STRUC
ulOffStart		dd ?
cbProcSize		dd ?
cdwLocals		dd ?
cdwParams		dw ?
RECORD
 cbProlog		dw : 8 ?
 cbRegs			dw : 3 ?
 fHasSEH		dw : 1 ?
 fUseBP			dw : 1 ?
 reserved		dw : 1 ?
 cbFrame		dw : 2 ?
ENDS
FPO_DATA		ENDS
PFPO_DATA		typedef ptr FPO_DATA
SIZEOF_RFPO_DATA	equ 16

IMAGE_DEBUG_MISC_EXENAME equ 1

IMAGE_DEBUG_MISC	STRUC
DataType		dd ?
Length			dd ?
Unicode			BOOLEAN ?
Reserved		db 3 dup(?)
Data			db ?
IMAGE_DEBUG_MISC	ENDS
PIMAGE_DEBUG_MISC	typedef ptr IMAGE_DEBUG_MISC

IMAGE_FUNCTION_ENTRY	STRUC
StartingAddress		dd ?
EndingAddress		dd ?
EndOfPrologue		dd ?
IMAGE_FUNCTION_ENTRY	ENDS
PIMAGE_FUNCTION_ENTRY	typedef ptr IMAGE_FUNCTION_ENTRY

IMAGE_FUNCTION_ENTRY64	STRUC
StartingAddress		dq ?
EndingAddress		dq ?
UNION
   EndOfPrologue	dq ?
   UnwindInfoAddress	dq ?
ENDS
IMAGE_FUNCTION_ENTRY64	ENDS
PIMAGE_FUNCTION_ENTRY64 typedef ptr IMAGE_FUNCTION_ENTRY64


IMAGE_SEPARATE_DEBUG_HEADER STRUC
Signature		dw ?
Flags			dw ?
Machine			dw ?
Characteristics		dw ?
TimeDateStamp		dd ?
CheckSum		dd ?
ImageBase		dd ?
SizeOfImage		dd ?
NumberOfSections	dd ?
ExportedNamesSize	dd ?
DebugDirectorySize	dd ?
SectionAlignment	dd ?
Reserved		dd 2 dup(?)
IMAGE_SEPARATE_DEBUG_HEADER ENDS
PIMAGE_SEPARATE_DEBUG_HEADER typedef ptr IMAGE_SEPARATE_DEBUG_HEADER

NON_PAGED_DEBUG_INFO	STRUC
Signature		dw ?
Flags			dw ?
Size			dd ?
Machine			dw ?
Characteristics		dw ?
TimeDateStamp		dd ?
CheckSum		dd ?
SizeOfImage		dd ?
ImageBase		dq ?
NON_PAGED_DEBUG_INFO	ENDS
PNON_PAGED_DEBUG_INFO	typedef ptr NON_PAGED_DEBUG_INFO

ifndef _MAC
IMAGE_SEPARATE_DEBUG_SIGNATURE equ 0x4944
NON_PAGED_DEBUG_SIGNATURE      equ 0x494E
else
IMAGE_SEPARATE_DEBUG_SIGNATURE equ 0x4449
NON_PAGED_DEBUG_SIGNATURE      equ 0x4E49
endif

IMAGE_SEPARATE_DEBUG_FLAGS_MASK equ 0x8000
IMAGE_SEPARATE_DEBUG_MISMATCH	equ 0x8000


IMAGE_ARCHITECTURE_HEADER STRUC
RECORD
 AmaskValue		dd : 1 ?
 int1			dd : 7 ?
 AmaskShift		dd : 8 ?
 int2			dd :16 ?
ENDS
FirstEntryRVA		dd ?
IMAGE_ARCHITECTURE_HEADER ENDS
PIMAGE_ARCHITECTURE_HEADER typedef ptr IMAGE_ARCHITECTURE_HEADER

IMAGE_ARCHITECTURE_ENTRY STRUC
FixupInstRVA		dd ?
NewInst			dd ?
IMAGE_ARCHITECTURE_ENTRY ENDS
PIMAGE_ARCHITECTURE_ENTRY typedef ptr IMAGE_ARCHITECTURE_ENTRY

IMPORT_OBJECT_HDR_SIG2	equ 0xffff

IMPORT_OBJECT_HEADER	STRUC
Sig1			dw ?
Sig2			dw ?
Version			dw ?
Machine			dw ?
TimeDateStamp		dd ?
SizeOfData		dd ?
UNION
  Ordinal		dw ?
  Hint			dw ?
ENDS
RECORD
 Type			dw:2 ?
 NameType		dw:3 ?
 Reserved		dw:11 ?
ENDS
IMPORT_OBJECT_HEADER	ENDS

.enum IMPORT_OBJECT_TYPE {
    IMPORT_OBJECT_CODE = 0,
    IMPORT_OBJECT_DATA = 1,
    IMPORT_OBJECT_CONST = 2
    }

.enum IMPORT_OBJECT_NAME_TYPE {
    IMPORT_OBJECT_ORDINAL = 0,
    IMPORT_OBJECT_NAME = 1,
    IMPORT_OBJECT_NAME_NO_PREFIX = 2,
    IMPORT_OBJECT_NAME_UNDECORATE = 3
    }

ifndef __IMAGE_COR20_HEADER_DEFINED__
define __IMAGE_COR20_HEADER_DEFINED__

.enum ReplacesCorHdrNumericDefines {

    COMIMAGE_FLAGS_ILONLY		= 0x00000001,
    COMIMAGE_FLAGS_32BITREQUIRED	= 0x00000002,
    COMIMAGE_FLAGS_IL_LIBRARY		= 0x00000004,
    COMIMAGE_FLAGS_STRONGNAMESIGNED	= 0x00000008,
    COMIMAGE_FLAGS_NATIVE_ENTRYPOINT	= 0x00000010,
    COMIMAGE_FLAGS_TRACKDEBUGDATA	= 0x00010000,

    COR_VERSION_MAJOR_V2		= 2,
    COR_VERSION_MAJOR			= COR_VERSION_MAJOR_V2,
    COR_VERSION_MINOR			= 0,
    COR_DELETED_NAME_LENGTH		= 8,
    COR_VTABLEGAP_NAME_LENGTH		= 8,

    NATIVE_TYPE_MAX_CB			= 1,
    COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE = 0xFF,

    IMAGE_COR_MIH_METHODRVA		= 0x01,
    IMAGE_COR_MIH_EHRVA			= 0x02,
    IMAGE_COR_MIH_BASICBLOCK		= 0x08,

    COR_VTABLE_32BIT			= 0x01,
    COR_VTABLE_64BIT			= 0x02,
    COR_VTABLE_FROM_UNMANAGED		= 0x04,
    COR_VTABLE_FROM_UNMANAGED_RETAIN_APPDOMAIN = 0x08,
    COR_VTABLE_CALL_MOST_DERIVED	= 0x10,

    IMAGE_COR_EATJ_THUNK_SIZE		= 32,

    MAX_CLASS_NAME			= 1024,
    MAX_PACKAGE_NAME			= 1024
    }

IMAGE_COR20_HEADER	STRUC
cb			dd ?
MajorRuntimeVersion	dw ?
MinorRuntimeVersion	dw ?
MetaData		IMAGE_DATA_DIRECTORY <>
Flags			dd ?
UNION
 EntryPointToken	dd ?
 EntryPointRVA		dd ?
ENDS
Resources		IMAGE_DATA_DIRECTORY <>
StrongNameSignature	IMAGE_DATA_DIRECTORY <>
CodeManagerTable	IMAGE_DATA_DIRECTORY <>
VTableFixups		IMAGE_DATA_DIRECTORY <>
ExportAddressTableJumps IMAGE_DATA_DIRECTORY <>
ManagedNativeHeader	IMAGE_DATA_DIRECTORY <>
IMAGE_COR20_HEADER	ENDS
PIMAGE_COR20_HEADER	typedef ptr IMAGE_COR20_HEADER

endif

ifdef _MAC
ifndef __STRING_INC
include string.inc
endif
else
ifndef __STRING_INC
include string.inc
endif
endif

ifndef _SLIST_HEADER_
define _SLIST_HEADER_

ifdef _WIN64
SLIST_ENTRY		STRUC DECLSPEC_ALIGN(16)
Next			PVOID ?;PSLIST_ENTRY ?
SLIST_ENTRY		ENDS
PSLIST_ENTRY		typedef ptr SLIST_ENTRY
SLIST_ENTRY32		STRUC
Next			dd ?
SLIST_ENTRY32		ENDS
PSLIST_ENTRY32		typedef ptr SLIST_ENTRY32
else
SLIST_ENTRY		equ <SINGLE_LIST_ENTRY>
PSLIST_ENTRY		equ <PSINGLE_LIST_ENTRY>
SLIST_ENTRY32		typedef SLIST_ENTRY
PSLIST_ENTRY32		typedef ptr SLIST_ENTRY
endif

ifdef _WIN64

SLIST_HEADER		UNION DECLSPEC_ALIGN(16)
STRUC
 Alignment		ULONGLONG ?
 Region			ULONGLONG ?
ENDS
STRUC
 RECORD
  Depth			dq : 16 ?
  Sequence		dq : 48 ?
 ENDS
 RECORD
  Reserved		dq :  4 ?
  NextEntry		dq : 60 ?
 ENDS
ENDS
SLIST_HEADER		ENDS
PSLIST_HEADER		typedef ptr SLIST_HEADER

SLIST_HEADER32		STRUC
Alignment		ULONGLONG ?
STRUC
 Next			SLIST_ENTRY32 <>
 Depth			dw ?
 Sequence		dw ?
ENDS
SLIST_HEADER32		ENDS
PSLIST_HEADER32		typedef ptr SLIST_HEADER32

else

SLIST_HEADER		UNION
Alignment		ULONGLONG ?
STRUC
 Next			SLIST_ENTRY <>
 Depth			dw ?
 Sequence		dw ?
ENDS
SLIST_HEADER		ENDS
PSLIST_HEADER		typedef ptr SLIST_HEADER
SLIST_HEADER32		typedef SLIST_HEADER
PSLIST_HEADER32		typedef ptr SLIST_HEADER

endif
endif ;; _SLIST_HEADER_

;NTSYSAPI
;VOID
RtlInitializeSListHead proto WINAPI \
	      ListHead: PSLIST_HEADER
;PSLIST_ENTRY
RtlFirstEntrySList proto WINAPI \
	      ListHead: PSLIST_HEADER
;PSLIST_ENTRY
RtlInterlockedPopEntrySList proto WINAPI \
	      ListHead: PSLIST_HEADER
;PSLIST_ENTRY
RtlInterlockedPushEntrySList proto WINAPI \
	      ListHead: PSLIST_HEADER,
	     ListEntry: PSLIST_ENTRY
;PSLIST_ENTRY
RtlInterlockedFlushSList proto WINAPI \
	      ListHead: PSLIST_HEADER
;WORD
RtlQueryDepthSList proto WINAPI \
	      ListHead: PSLIST_HEADER
ifdef _IA64_
;PSLIST_ENTRY32
RtlInterlockedPopEntrySList32 proto WINAPI \
	      ListHead: PSLIST_HEADER32
endif

ifndef _RTL_RUN_ONCE_DEF
define _RTL_RUN_ONCE_DEF

RTL_RUN_ONCE_INIT	    equ <{0}>
RTL_RUN_ONCE_CHECK_ONLY	    equ 0x00000001
RTL_RUN_ONCE_ASYNC	    equ 0x00000002
RTL_RUN_ONCE_INIT_FAILED    equ 0x00000004


RTL_RUN_ONCE_CTX_RESERVED_BITS equ 2

RTL_RUN_ONCE		UNION
_Ptr			PVOID ?
RTL_RUN_ONCE		ENDS
PRTL_RUN_ONCE		typedef ptr RTL_RUN_ONCE

;DWORD
CALLBACK(PRTL_RUN_ONCE_INIT_FN, RunOnce:PRTL_RUN_ONCE, Parameter:PVOID, Context:PVOID)

endif

RTL_BARRIER		STRUC
Reserved1		DWORD ?
Reserved2		DWORD ?
Reserved3		ULONG_PTR 2 dup(?)
Reserved4		DWORD ?
Reserved5		DWORD ?
RTL_BARRIER		ENDS
PRTL_BARRIER		typedef ptr RTL_BARRIER

FAST_FAIL_LEGACY_GS_VIOLATION equ 0
FAST_FAIL_VTGUARD_CHECK_FAILURE equ 1
FAST_FAIL_STACK_COOKIE_CHECK_FAILURE equ 2
FAST_FAIL_CORRUPT_LIST_ENTRY equ 3
FAST_FAIL_INCORRECT_STACK equ 4
FAST_FAIL_INVALID_ARG	equ 5
FAST_FAIL_GS_COOKIE_INIT equ 6
FAST_FAIL_FATAL_APP_EXIT equ 7
FAST_FAIL_RANGE_CHECK_FAILURE equ 8
FAST_FAIL_UNSAFE_REGISTRY_ACCESS equ 9
FAST_FAIL_GUARD_ICALL_CHECK_FAILURE equ 10
FAST_FAIL_GUARD_WRITE_CHECK_FAILURE equ 11
FAST_FAIL_INVALID_FIBER_SWITCH equ 12
FAST_FAIL_INVALID_SET_OF_CONTEXT equ 13
FAST_FAIL_INVALID_REFERENCE_COUNT equ 14
FAST_FAIL_INVALID_JUMP_BUFFER equ 18
FAST_FAIL_MRDATA_MODIFIED equ 19
FAST_FAIL_CERTIFICATION_FAILURE equ 20
FAST_FAIL_INVALID_EXCEPTION_CHAIN equ 21
FAST_FAIL_CRYPTO_LIBRARY equ 22
FAST_FAIL_INVALID_CALL_IN_DLL_CALLOUT equ 23
FAST_FAIL_INVALID_IMAGE_BASE equ 24
FAST_FAIL_DLOAD_PROTECTION_FAILURE equ 25
FAST_FAIL_UNSAFE_EXTENSION_CALL equ 26
FAST_FAIL_INVALID_FAST_FAIL_CODE equ 0xFFFFFFFF

if (NTDDI_VERSION GE NTDDI_LONGHORN)

;VOID
RtlRunOnceInitialize proto WINAPI \
	       RunOnce: PRTL_RUN_ONCE
;DWORD
RtlRunOnceExecuteOnce proto WINAPI \
	       RunOnce: PRTL_RUN_ONCE,
		InitFn: PRTL_RUN_ONCE_INIT_FN,
	     Parameter: PVOID,
	       Context: PVOID
;DWORD
RtlRunOnceBeginInitialize proto WINAPI \
	       RunOnce: PRTL_RUN_ONCE,
		 Flags: DWORD,
	       Context: PVOID
;DWORD
RtlRunOnceComplete proto WINAPI \
	       RunOnce: PRTL_RUN_ONCE,
		 Flags: DWORD,
	       Context: PVOID

endif

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

ifndef MIDL_PASS
;FORCEINLINE
;DWORD
HEAP_MAKE_TAG_FLAGS macro TagBase, Tag
    endm
endif

if (NTDDI_VERSION GT NTDDI_WINXP)
;WORD
RtlCaptureStackBackTrace proto WINAPI \
	  FramesToSkip: DWORD,
       FramesToCapture: DWORD,
	     BackTrace: PVOID,
	 BackTraceHash: PDWORD
endif

if (NTDDI_VERSION GT NTDDI_WIN2K)
;VOID
RtlCaptureContext proto WINAPI \
	 ContextRecord: PCONTEXT
endif

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
COMPRESSION_ENGINE_HIBER	equ 0x0200

ifdef _DBG_MEMCPY_INLINE_
if _DBG_MEMCPY_INLINE_ and not defined(MIDL_PASS) and not defined(_MEMCPY_INLINE_) and not defined(_CRTBLD)
define _MEMCPY_INLINE_
;FORCEINLINE
;PVOID
memcpy_inline macro dst, src, _size
	endm
;memcpy equ <memcpy_inline>
endif
endif

if (NTDDI_VERSION GE NTDDI_WIN2K)
;SIZE_T
RtlCompareMemory proto WINAPI \
	      Source1: PVOID,
	      Source2: PVOID,
	       Length: SIZE_T
endif

RtlEqualMemory macro Destination, Source, L
	.if !memcmp(Destination,Source,L)
	    inc eax
	.else
	    mov eax,0
	.endif
	exitm<eax>
	endm
RtlMoveMemory equ <memmove>
RtlCopyMemory equ <memcpy>
RtlFillMemory macro Destination, L, Fill
	exitm<memset(Destination,Fill,L)>
	endm
RtlZeroMemory macro Destination, L
	exitm<memset(Destination,0,L)>
	endm

RtlSecureZeroMemory macro vptr, cnt
ifdef _M_AMD64
    __stosb(vptr, 0, cnt)
else
    .for : cnt : vptr++, cnt--
	mov byte ptr [vptr],0
    .endf
endif
    exitm<vptr>
    endm

SEF_DACL_AUTO_INHERIT		  equ 0x01
SEF_SACL_AUTO_INHERIT		  equ 0x02
SEF_DEFAULT_DESCRIPTOR_FOR_OBJECT equ 0x04
SEF_AVOID_PRIVILEGE_CHECK	  equ 0x08
SEF_AVOID_OWNER_CHECK		  equ 0x10
SEF_DEFAULT_OWNER_FROM_PARENT	  equ 0x20
SEF_DEFAULT_GROUP_FROM_PARENT	  equ 0x40
SEF_MACL_NO_WRITE_UP		  equ 0x100
SEF_MACL_NO_READ_UP		  equ 0x200
SEF_MACL_NO_EXECUTE_UP		  equ 0x400
SEF_AVOID_OWNER_RESTRICTION	  equ 0x1000

SEF_MACL_VALID_FLAGS	equ SEF_MACL_NO_WRITE_UP OR \
			    SEF_MACL_NO_READ_UP	 OR \
			    SEF_MACL_NO_EXECUTE_UP

MESSAGE_RESOURCE_ENTRY	STRUC
Length			dw ?
Flags			dw ?
Text			db ?
MESSAGE_RESOURCE_ENTRY	ENDS
PMESSAGE_RESOURCE_ENTRY typedef ptr MESSAGE_RESOURCE_ENTRY

MESSAGE_RESOURCE_UNICODE equ 0x0001

MESSAGE_RESOURCE_BLOCK	STRUC
LowId			dd ?
HighId			dd ?
OffsetToEntries		dd ?
MESSAGE_RESOURCE_BLOCK	ENDS
PMESSAGE_RESOURCE_BLOCK typedef ptr MESSAGE_RESOURCE_BLOCK

MESSAGE_RESOURCE_DATA	STRUC
NumberOfBlocks		dd ?
Blocks			MESSAGE_RESOURCE_BLOCK <>
MESSAGE_RESOURCE_DATA	ENDS
PMESSAGE_RESOURCE_DATA	typedef ptr MESSAGE_RESOURCE_DATA

;PVOID
RtlPcToFileHeader proto WINAPI \
	       PcValue: PVOID,
	   BaseOfImage: PVOID

OSVERSIONINFOA		STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		db 128 dup(?) ; Maintenance string for PSS usage
OSVERSIONINFOA		ENDS
POSVERSIONINFOA		TYPEDEF PTR OSVERSIONINFOA
LPOSVERSIONINFOA	TYPEDEF PTR OSVERSIONINFOA
OSVERSIONINFOW		STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		dw 128 dup(?) ; Maintenance string for PSS usage
OSVERSIONINFOW		ENDS
POSVERSIONINFOW		TYPEDEF PTR OSVERSIONINFOW
LPOSVERSIONINFOW	TYPEDEF PTR OSVERSIONINFOW
ifdef _UNICODE
OSVERSIONINFO	typedef OSVERSIONINFOW
POSVERSIONINFO	typedef POSVERSIONINFOW
LPOSVERSIONINFO typedef LPOSVERSIONINFOW
else
OSVERSIONINFO	typedef OSVERSIONINFOA
POSVERSIONINFO	typedef POSVERSIONINFOA
LPOSVERSIONINFO typedef LPOSVERSIONINFOA
endif

OSVERSIONINFOEXA	STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		db 128 dup(?)	; Maintenance string for PSS usage
wServicePackMajor	dw ?
wServicePackMinor	dw ?
wReserved		dw 2 dup(?)
OSVERSIONINFOEXA	ENDS
POSVERSIONINFOEXA	typedef PTR OSVERSIONINFOEXA
LPOSVERSIONINFOEXA	typedef PTR OSVERSIONINFOEXA
OSVERSIONINFOEXW	STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		dw 128 dup(?)	; Maintenance string for PSS usage
wServicePackMajor	dw ?
wServicePackMinor	dw ?
wReserved		dw 2 dup(?)
OSVERSIONINFOEXW	ENDS
POSVERSIONINFOEXW	typedef PTR OSVERSIONINFOEXW
LPOSVERSIONINFOEXW	typedef PTR OSVERSIONINFOEXW
ifdef _UNICODE
OSVERSIONINFOEX		typedef OSVERSIONINFOEXW
POSVERSIONINFOEX	typedef POSVERSIONINFOEXW
LPOSVERSIONINFOEX	typedef LPOSVERSIONINFOEXW
else
OSVERSIONINFOEX		typedef OSVERSIONINFOEXA
POSVERSIONINFOEX	typedef POSVERSIONINFOEXA
LPOSVERSIONINFOEX	typedef LPOSVERSIONINFOEXA
endif

STATUS_SUCCESS		equ 0

VER_EQUAL		equ 1
VER_GREATER		equ 2
VER_GREATER_EQUAL	equ 3
VER_LESS		equ 4
VER_LESS_EQUAL		equ 5
VER_AND			equ 6
VER_OR			equ 7

VER_CONDITION_MASK	equ 7
VER_NUM_BITS_PER_CONDITION_MASK equ 3


VER_MINORVERSION	equ 0x0000001
VER_MAJORVERSION	equ 0x0000002
VER_BUILDNUMBER		equ 0x0000004
VER_PLATFORMID		equ 0x0000008
VER_SERVICEPACKMINOR	equ 0x0000010
VER_SERVICEPACKMAJOR	equ 0x0000020
VER_SUITENAME		equ 0x0000040
VER_PRODUCT_TYPE	equ 0x0000080


VER_NT_WORKSTATION	equ 0x0000001
VER_NT_DOMAIN_CONTROLLER equ 0x0000002
VER_NT_SERVER		equ 0x0000003


VER_PLATFORM_WIN32s	equ 0
VER_PLATFORM_WIN32_WINDOWS equ 1
VER_PLATFORM_WIN32_NT	equ 2



VER_SET_CONDITION macro _m_,_t_,_c_
	exitm<mov _m_,VerSetConditionMask(_m_,_t_,_c_)>
	endm

if (NTDDI_VERSION GE NTDDI_WIN2K)
;NTSYSAPI
;ULONGLONG
VerSetConditionMask proto WINAPI \
	 ConditionMask: ULONGLONG,
	      TypeMask: DWORD,
	     Condition: BYTE

RtlGetVersion	    proto WINAPI \
  lpVersionInformation: ptr

endif

if (NTDDI_VERSION GE NTDDI_VISTA)
;BOOLEAN
RtlGetProductInfo proto WINAPI \
	OSMajorVersion: DWORD,
	OSMinorVersion: DWORD,
	SpMajorVersion: DWORD,
	SpMinorVersion: DWORD,
   ReturnedProductType: PDWORD
endif

RTL_UMS_VERSION		equ 0x0100

.enum RTL_UMS_THREAD_INFO_CLASS {
    UmsThreadInvalidInfoClass = 0,
    UmsThreadUserContext,
    UmsThreadPriority,
    UmsThreadAffinity,
    UmsThreadTeb,
    UmsThreadIsSuspended,
    UmsThreadIsTerminated,
    UmsThreadMaxInfoClass
    }
PRTL_UMS_THREAD_INFO_CLASS typedef ptr RTL_UMS_THREAD_INFO_CLASS

.enum RTL_UMS_SCHEDULER_REASON {
    UmsSchedulerStartup = 0,
    UmsSchedulerThreadBlocked,
    UmsSchedulerThreadYield,
    }
PRTL_UMS_SCHEDULER_REASON typedef ptr RTL_UMS_SCHEDULER_REASON

;VOID
CALLBACK(PRTL_UMS_SCHEDULER_ENTRY_POINT, :RTL_UMS_SCHEDULER_REASON, :ULONG_PTR, :PVOID)

if (NTDDI_VERSION GE NTDDI_WIN7)
;DWORD
RtlCopyExtendedContext proto WINAPI \
	   Destination: PCONTEXT_EX,
	  ContextFlags: DWORD,
		Source: PCONTEXT_EX
;DWORD
RtlInitializeExtendedContext proto WINAPI \
	       Context: PVOID,
	  ContextFlags: DWORD,
	     ContextEx: PCONTEXT_EX
;DWORD64
RtlGetEnabledExtendedFeatures proto WINAPI \
	   FeatureMask: DWORD64
;DWORD
RtlGetExtendedContextLength proto WINAPI \
	  ContextFlags: DWORD,
	 ContextLength: PDWORD
;DWORD64
RtlGetExtendedFeaturesMask proto WINAPI \
	     ContextEx: PCONTEXT_EX
;PVOID
RtlLocateExtendedFeature proto WINAPI \
	     ContextEx: PCONTEXT_EX,
	     FeatureId: DWORD,
		Length: PDWORD
;PCONTEXT
RtlLocateLegacyContext proto WINAPI \
	     ContextEx: PCONTEXT_EX,
		Length: PDWORD
;VOID
RtlSetExtendedFeaturesMask proto WINAPI \
	     ContextEx: PCONTEXT_EX,
	   FeatureMask: DWORD64
endif

RTL_CRITICAL_SECTION_DEBUG	STRUC
Type				dw ?
CreatorBackTraceIndex		dw ?
CriticalSection			PVOID ?;PRTL_CRITICAL_SECTION ?
ProcessLocksList		LIST_ENTRY <>
EntryCount			dd ?
ContentionCount			dd ?
Flags				dd ?
CreatorBackTraceIndexHigh	dw ?
SpareWORD			dw ?
RTL_CRITICAL_SECTION_DEBUG	ENDS
PRTL_CRITICAL_SECTION_DEBUG	typedef ptr RTL_CRITICAL_SECTION_DEBUG
RTL_RESOURCE_DEBUG		typedef RTL_CRITICAL_SECTION_DEBUG
PRTL_RESOURCE_DEBUG		typedef ptr RTL_CRITICAL_SECTION_DEBUG

RTL_CRITSECT_TYPE	equ 0
RTL_RESOURCE_TYPE	equ 1

RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO equ 0x01000000
RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN	equ 0x02000000
RTL_CRITICAL_SECTION_FLAG_STATIC_INIT	equ 0x04000000
RTL_CRITICAL_SECTION_ALL_FLAG_BITS	equ 0xFF000000
RTL_CRITICAL_SECTION_FLAG_RESERVED	equ (RTL_CRITICAL_SECTION_ALL_FLAG_BITS AND \
	( NOT (RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO OR \
	RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN OR RTL_CRITICAL_SECTION_FAG_STATIC_INIT)))

RTL_CRITICAL_SECTION_DEBUG_FLAG_STATIC_INIT equ 0x00000001

.pragma pack(push, 8)

RTL_CRITICAL_SECTION	STRUC
DebugInfo		PRTL_CRITICAL_SECTION_DEBUG ?
LockCount		LONG ?
RecursionCount		LONG ?
OwningThread		HANDLE ?
LockSemaphore		HANDLE ?
SpinCount		ULONG_PTR ?
RTL_CRITICAL_SECTION	ENDS
PRTL_CRITICAL_SECTION	typedef ptr RTL_CRITICAL_SECTION

.pragma pack(pop)

RTL_SRWLOCK		STRUC
_Ptr			PVOID ?
RTL_SRWLOCK		ENDS
PRTL_SRWLOCK		typedef ptr RTL_SRWLOCK

RTL_SRWLOCK_INIT	equ <{0}>

RTL_CONDITION_VARIABLE	STRUC
_Ptr			PVOID ?
RTL_CONDITION_VARIABLE	ENDS
PRTL_CONDITION_VARIABLE typedef ptr RTL_CONDITION_VARIABLE

RTL_CONDITION_VARIABLE_INIT equ <{0}>
RTL_CONDITION_VARIABLE_LOCKMODE_SHARED equ 0x1

;VOID
CALLBACK(PAPCFUNC, :ULONG_PTR)
;LONG
CALLBACK(PVECTORED_EXCEPTION_HANDLER, ExceptionInfo:ptr EXCEPTION_POINTERS)

.enum HEAP_INFORMATION_CLASS {
    HeapCompatibilityInformation,
    HeapEnableTerminationOnCorruption
    }

CALLBACK(WAITORTIMERCALLBACKFUNC, :PVOID, :BOOLEAN)
CALLBACK(WORKERCALLBACKFUNC, :PVOID)
define WAITORTIMERCALLBACK <WAITORTIMERCALLBACKFUNC>

CALLBACK(APC_CALLBACK_FUNCTION, :DWORD, :PVOID, :PVOID)
CALLBACK(PFLS_CALLBACK_FUNCTION, :PVOID)
CALLBACK(PSECURE_MEMORY_CACHE_CALLBACK, :PVOID, :SIZE_T)

WT_SET_MAX_THREADPOOL_THREADS macro Flags, Limit
	exitm<(((Flags) OR ((Limit) SHL 16)))>
	endm


WT_EXECUTEDEFAULT		equ 0x00000000
WT_EXECUTEINIOTHREAD		equ 0x00000001
WT_EXECUTEINUITHREAD		equ 0x00000002
WT_EXECUTEINWAITTHREAD		equ 0x00000004
WT_EXECUTEDELETEWAIT		equ 0x00000008
WT_EXECUTEINLONGTHREAD		equ 0x00000010
WT_EXECUTEINTIMERTHREAD		equ 0x00000020
WT_EXECUTEINPERSISTENTIOTHREAD	equ 0x00000040
WT_EXECUTEINPERSISTENTTHREAD	equ 0x00000080
WT_TRANSFER_IMPERSONATION	equ 0x00000100

ACTIVATION_CONTEXT	typedef ptr

.enum ACTIVATION_CONTEXT_INFO_CLASS {
    ActivationContextBasicInformation			    = 1,
    ActivationContextDetailedInformation		    = 2,
    AssemblyDetailedInformationInActivationContext	    = 3,
    FileInformationInAssemblyOfAssemblyInActivationContext  = 4,
    RunlevelInformationInActivationContext		    = 5,
    CompatibilityInformationInActivationContext		    = 6,
    ActivationContextManifestResourceName		    = 7,
    MaxActivationContextInfoClass,
    AssemblyDetailedInformationInActivationContxt	    = 3,
    FileInformationInAssemblyOfAssemblyInActivationContxt   = 4
    }

ACTIVATIONCONTEXTINFOCLASS equ ACTIVATION_CONTEXT_INFO_CASS

ACTIVATION_CONTEXT_QUERY_INDEX STRUC
ulAssemblyIndex		dd ?
ulFileIndexInAssembly	dd ?
ACTIVATION_CONTEXT_QUERY_INDEX ENDS
PACTIVATION_CONTEXT_QUERY_INDEX typedef ptr ACTIVATION_CONTEXT_QUERY_INDEX
PCACTIVATION_CONTEXT_QUERY_INDEX typedef ptr ACTIVATION_CONTEXT_QUERY_INDEX


ACTIVATION_CONTEXT_PATH_TYPE_NONE	 equ 1
ACTIVATION_CONTEXT_PATH_TYPE_WIN32_FILE	 equ 2
ACTIVATION_CONTEXT_PATH_TYPE_URL	 equ 3
ACTIVATION_CONTEXT_PATH_TYPE_ASSEMBLYREF equ 4

ASSEMBLY_FILE_DETAILED_INFORMATION  STRUC
ulFlags			dd ?
ulFilenameLength	dd ?
ulPathLength		dd ?
lpFileName		PCWSTR ?
lpFilePath		PCWSTR ?
ASSEMBLY_FILE_DETAILED_INFORMATION ENDS
PASSEMBLY_FILE_DETAILED_INFORMATION typedef ptr ASSEMBLY_FILE_DETAILED_INFORMATION
PCASSEMBLY_FILE_DETAILED_INFORMATION typedef ptr ASSEMBLY_FILE_DETAILED_INFORMATION

_ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION	equ _ASSEMBLY_FILE_DETAILED_INFORMATION
ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION	equ ASSEMBLY_FILE_DETAILED_INFORMATION
PASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION	equ PASSEMBLY_FILE_DETAILED_INFORMATION
PCASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION equ PCASSEMBLY_FILE_DETAILED_INFORMATION

ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION STRUC
ulFlags				dd ?
ulEncodedAssemblyIdentityLength dd ?
ulManifestPathType		dd ?
ulManifestPathLength		dd ?
liManifestLastWriteTime		LARGE_INTEGER <>
ulPolicyPathType		dd ?
ulPolicyPathLength		dd ?
liPolicyLastWriteTime		LARGE_INTEGER <>
ulMetadataSatelliteRosterIndex	dd ?
ulManifestVersionMajor		dd ?
ulManifestVersionMinor		dd ?
ulPolicyVersionMajor		dd ?
ulPolicyVersionMinor		dd ?
ulAssemblyDirectoryNameLength	dd ?
lpAssemblyEncodedAssemblyIdentity PCWSTR ?
lpAssemblyManifestPath		PCWSTR ?
lpAssemblyPolicyPath		PCWSTR ?
lpAssemblyDirectoryName		PCWSTR ?
ulFileCount			dd ?
ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION ENDS
PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION typedef ptr ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION
PCACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION typedef ptr ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION

.enum ACTCTX_REQUESTED_RUN_LEVEL {
    ACTCTX_RUN_LEVEL_UNSPECIFIED,
    ACTCTX_RUN_LEVEL_AS_INVOKER,
    ACTCTX_RUN_LEVEL_HIGHEST_AVAILABLE,
    ACTCTX_RUN_LEVEL_REQUIRE_ADMIN,
    ACTCTX_RUN_LEVEL_NUMBERS
    }

ACTIVATION_CONTEXT_RUN_LEVEL_INFORMATION STRUC
ulFlags			dd ?
RunLevel		ACTCTX_REQUESTED_RUN_LEVEL ?
UiAccess		dd ?
ACTIVATION_CONTEXT_RUN_LEVEL_INFORMATION ENDS
PACTIVATION_CONTEXT_RUN_LEVEL_INFORMATION typedef ptr ACTIVATION_CONTEXT_RUN_LEVEL_INFORMATION

.enum ACTCTX_COMPATIBILITY_ELEMENT_TYPE {
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE_UNKNOWN,
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE_OS,
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE_MITIGATION
    }

COMPATIBILITY_CONTEXT_ELEMENT STRUC
Id			GUID <>
Type			ACTCTX_COMPATIBILITY_ELEMENT_TYPE ?
COMPATIBILITY_CONTEXT_ELEMENT ENDS
PCOMPATIBILITY_CONTEXT_ELEMENT typedef ptr COMPATIBILITY_CONTEXT_ELEMENT
PCCOMPATIBILITY_CONTEXT_ELEMENT typedef ptr COMPATIBILITY_CONTEXT_ELEMENT

ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION STRUC
ElementCount		dd ?
Elements		COMPATIBILITY_CONTEXT_ELEMENT <>
ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION ENDS
PACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION typedef ptr ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION

PCACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION typedef ptr ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION

MAX_SUPPORTED_OS_NUM	equ 4
INVALID_OS_COUNT	equ 0xffff

SUPPORTED_OS_INFO	STRUC
OsCount			dw ?
MitigationExist		dw ?
OsList			dw MAX_SUPPORTED_OS_NUM dup(?)
SUPPORTED_OS_INFO	ENDS
PSUPPORTED_OS_INFO	typedef ptr SUPPORTED_OS_INFO

ACTIVATION_CONTEXT_DETAILED_INFORMATION	 STRUC
dwFlags			dd ?
ulFormatVersion		dd ?
ulAssemblyCount		dd ?
ulRootManifestPathType	dd ?
ulRootManifestPathChars dd ?
ulRootConfigurationPathType dd ?
ulRootConfigurationPathChars dd ?
ulAppDirPathType	dd ?
ulAppDirPathChars	dd ?
lpRootManifestPath	PCWSTR ?
lpRootConfigurationPath PCWSTR ?
lpAppDirPath		PCWSTR ?
ACTIVATION_CONTEXT_DETAILED_INFORMATION ENDS
PACTIVATION_CONTEXT_DETAILED_INFORMATION typedef ptr ACTIVATION_CONTEXT_DETAILED_INFORMATION
PCACTIVATION_CONTEXT_DETAILED_INFORMATION typedef ptr ACTIVATION_CONTEXT_DETAILED_INFORMATION

HARDWARE_COUNTER_DATA	STRUC
Type			HARDWARE_COUNTER_TYPE ?
Reserved		dd ?
Value			dd ?
HARDWARE_COUNTER_DATA	ENDS
PHARDWARE_COUNTER_DATA	typedef ptr HARDWARE_COUNTER_DATA

PERFORMANCE_DATA_VERSION equ 1

PERFORMANCE_DATA	STRUC
Size			dw ?
Version			db ?
HwCountersCount		db ?
ContextSwitchCount	dd ?
WaitReasonBitMap	dd ?
CycleTime		dd ?
RetryCount		dd ?
Reserved		dd ?
HwCounters		HARDWARE_COUNTER_DATA MAX_HW_COUNTERS dup(<>)
PERFORMANCE_DATA	ENDS
PPERFORMANCE_DATA	typedef ptr PERFORMANCE_DATA

READ_THREAD_PROFILING_FLAG_DISPATCHING equ 0x00000001
READ_THREAD_PROFILING_FLAG_HARDWARE_COUNTERS equ 0x00000002

DLL_PROCESS_ATTACH	equ 1
DLL_THREAD_ATTACH	equ 2
DLL_THREAD_DETACH	equ 3
DLL_PROCESS_DETACH	equ 0

EVENTLOG_SEQUENTIAL_READ	equ 0X0001
EVENTLOG_SEEK_READ		equ 0X0002
EVENTLOG_FORWARDS_READ		equ 0X0004
EVENTLOG_BACKWARDS_READ		equ 0X0008

EVENTLOG_SUCCESS		equ 0X0000
EVENTLOG_ERROR_TYPE		equ 0x0001
EVENTLOG_WARNING_TYPE		equ 0x0002
EVENTLOG_INFORMATION_TYPE	equ 0x0004
EVENTLOG_AUDIT_SUCCESS		equ 0x0008
EVENTLOG_AUDIT_FAILURE		equ 0x0010


EVENTLOG_START_PAIRED_EVENT    equ 0x0001
EVENTLOG_END_PAIRED_EVENT      equ 0x0002
EVENTLOG_END_ALL_PAIRED_EVENTS equ 0x0004
EVENTLOG_PAIRED_EVENT_ACTIVE   equ 0x0008
EVENTLOG_PAIRED_EVENT_INACTIVE equ 0x0010


EVENTLOGRECORD			STRUC
Length				dd ?
Reserved			dd ?
RecordNumber			dd ?
TimeGenerated			dd ?
TimeWritten			dd ?
EventID				dd ?
EventType			dw ?
NumStrings			dw ?
EventCategory			dw ?
ReservedFlags			dw ?
ClosingRecordNumber		dd ?
StringOffset			dd ?
UserSidLength			dd ?
UserSidOffset			dd ?
DataLength			dd ?
DataOffset			dd ?
EVENTLOGRECORD			ENDS
PEVENTLOGRECORD			typedef ptr EVENTLOGRECORD

define MAXLOGICALLOGNAMESIZE   256

ifdef _MSC_EXTENSIONS
EVENTSFORLOGFILE		STRUC
ulSize				dd ?
szLogicalLogFile		WCHAR MAXLOGICALLOGNAMESIZE dup(?)
ulNumRecords			dd ?
pEventLogRecords		EVENTLOGRECORD <>
EVENTSFORLOGFILE		ENDS
PEVENTSFORLOGFILE		typedef ptr EVENTSFORLOGFILE


PACKEDEVENTINFO			STRUC
ulSize				dd ?
ulNumEventsForLogFile		dd ?
ulOffsets			dd ?
PACKEDEVENTINFO			ENDS
PPACKEDEVENTINFO		typedef ptr PACKEDEVENTINFO
endif

DBG_CONTINUE			equ 0x00010002
DBG_TERMINATE_THREAD		equ 0x40010003
DBG_TERMINATE_PROCESS		equ 0x40010004
DBG_CONTROL_C			equ 0x40010005
DBG_CONTROL_BREAK		equ 0x40010008
DBG_EXCEPTION_NOT_HANDLED	equ 0x80010001

KEY_QUERY_VALUE		equ 0x0001
KEY_SET_VALUE		equ 0x0002
KEY_CREATE_SUB_KEY	equ 0x0004
KEY_ENUMERATE_SUB_KEYS	equ 0x0008
KEY_NOTIFY		equ 0x0010
KEY_CREATE_LINK		equ 0x0020
KEY_WOW64_32KEY		equ 0x0200
KEY_WOW64_64KEY		equ 0x0100
KEY_WOW64_RES		equ 0x0300

KEY_READ	equ (STANDARD_RIGHTS_READ or KEY_QUERY_VALUE or \
		    KEY_ENUMERATE_SUB_KEYS or KEY_NOTIFY) and not SYNCHRONIZE
KEY_WRITE	equ (STANDARD_RIGHTS_WRITE or KEY_SET_VALUE or KEY_CREATE_SUB_KEY) \
		    and (not SYNCHRONIZE)
KEY_EXECUTE	equ KEY_READ and (not SYNCHRONIZE)
KEY_ALL_ACCESS	equ (STANDARD_RIGHTS_ALL or KEY_QUERY_VALUE or KEY_SET_VALUE or \
		    KEY_CREATE_SUB_KEY or KEY_ENUMERATE_SUB_KEYS or KEY_NOTIFY or \
		    KEY_CREATE_LINK) and (not SYNCHRONIZE)



REG_OPTION_RESERVED		equ 0x00000000
REG_OPTION_NON_VOLATILE		equ 0x00000000
REG_OPTION_VOLATILE		equ 0x00000001
REG_OPTION_CREATE_LINK		equ 0x00000002
REG_OPTION_BACKUP_RESTORE	equ 0x00000004
REG_OPTION_OPEN_LINK		equ 0x00000008

REG_LEGAL_OPTION equ REG_OPTION_RESERVED or \
		     REG_OPTION_NON_VOLATILE or \
		     REG_OPTION_VOLATILE or \
		     REG_OPTION_CREATE_LINK or \
		     REG_OPTION_BACKUP_RESTORE or \
		     REG_OPTION_OPEN_LINK

REG_OPEN_LEGAL_OPTION equ REG_OPTION_RESERVED OR REG_OPTION_BACKUP_RESTORE


REG_CREATED_NEW_KEY		equ 0x00000001
REG_OPENED_EXISTING_KEY		equ 0x00000002

define REG_STANDARD_FORMAT     1
define REG_LATEST_FORMAT       2
define REG_NO_COMPRESSION      4

REG_WHOLE_HIVE_VOLATILE		equ 0x00000001
REG_REFRESH_HIVE		equ 0x00000002
REG_NO_LAZY_FLUSH		equ 0x00000004
REG_FORCE_RESTORE		equ 0x00000008
REG_APP_HIVE			equ 0x00000010
REG_PROCESS_PRIVATE		equ 0x00000020
REG_START_JOURNAL		equ 0x00000040
REG_HIVE_EXACT_FILE_GROWTH	equ 0x00000080
REG_HIVE_NO_RM			equ 0x00000100
REG_HIVE_SINGLE_LOG		equ 0x00000200
REG_BOOT_HIVE			equ 0x00000400
REG_LOAD_HIVE_OPEN_HANDLE	equ 0x00000800
REG_FLUSH_HIVE_FILE_GROWTH	equ 0x00001000

REG_FORCE_UNLOAD		equ 1

REG_NOTIFY_CHANGE_NAME		equ 0x00000001
REG_NOTIFY_CHANGE_ATTRIBUTES	equ 0x00000002
REG_NOTIFY_CHANGE_LAST_SET	equ 0x00000004
REG_NOTIFY_CHANGE_SECURITY	equ 0x00000008
REG_NOTIFY_THREAD_AGNOSTIC	equ 0x10000000

REG_LEGAL_CHANGE_FILTER		equ 0x1000000F

REG_NONE			equ 0
REG_SZ				equ 1
REG_EXPAND_SZ			equ 2
REG_BINARY			equ 3
REG_DWORD			equ 4
REG_DWORD_LITTLE_ENDIAN		equ 4
REG_DWORD_BIG_ENDIAN		equ 5
REG_LINK			equ 6
REG_MULTI_SZ			equ 7
REG_RESOURCE_LIST		equ 8
REG_FULL_RESOURCE_DESCRIPTOR	equ 9
REG_RESOURCE_REQUIREMENTS_LIST	equ 10
REG_QWORD			equ 11
REG_QWORD_LITTLE_ENDIAN		equ 11

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

SERVICE_BOOT_START	       equ 0x00000000
SERVICE_SYSTEM_START	       equ 0x00000001
SERVICE_AUTO_START	       equ 0x00000002
SERVICE_DEMAND_START	       equ 0x00000003
SERVICE_DISABLED	       equ 0x00000004

SERVICE_ERROR_IGNORE	       equ 0x00000000
SERVICE_ERROR_NORMAL	       equ 0x00000001
SERVICE_ERROR_SEVERE	       equ 0x00000002
SERVICE_ERROR_CRITICAL	       equ 0x00000003

.enum CM_SERVICE_NODE_TYPE {
    DriverType		     = SERVICE_KERNEL_DRIVER,
    FileSystemType	     = SERVICE_FILE_SYSTEM_DRIVER,
    Win32ServiceOwnProcess   = SERVICE_WIN32_OWN_PROCESS,
    Win32ServiceShareProcess = SERVICE_WIN32_SHARE_PROCESS,
    AdapterType		     = SERVICE_ADAPTER,
    RecognizerType	     = SERVICE_RECOGNIZER_DRIVER
    }

.enum CM_SERVICE_LOAD_TYPE {
    BootLoad	= SERVICE_BOOT_START,
    SystemLoad	= SERVICE_SYSTEM_START,
    AutoLoad	= SERVICE_AUTO_START,
    DemandLoad	= SERVICE_DEMAND_START,
    DisableLoad = SERVICE_DISABLED
    }

.enum CM_ERROR_CONTROL_TYPE {
    IgnoreError	  = SERVICE_ERROR_IGNORE,
    NormalError	  = SERVICE_ERROR_NORMAL,
    SevereError	  = SERVICE_ERROR_SEVERE,
    CriticalError = SERVICE_ERROR_CRITICAL
    }

define CM_SERVICE_NETWORK_BOOT_LOAD	 0x00000001
define CM_SERVICE_VIRTUAL_DISK_BOOT_LOAD 0x00000002
define CM_SERVICE_USB_DISK_BOOT_LOAD	 0x00000004
define CM_SERVICE_SD_DISK_BOOT_LOAD	 0x00000008
define CM_SERVICE_USB3_DISK_BOOT_LOAD	 0x00000010
define CM_SERVICE_MEASURED_BOOT_LOAD	 0x00000020
define CM_SERVICE_VERIFIER_BOOT_LOAD	 0x00000040
define CM_SERVICE_WINPE_BOOT_LOAD	 0x00000080

define CM_SERVICE_VALID_PROMOTION_MASK	 0x000000FF

TAPE_ERASE_SHORT		equ 0
TAPE_ERASE_LONG			equ 1

TAPE_ERASE			STRUC
Type				dd ?
Immediate			BOOLEAN ?
TAPE_ERASE			ENDS
PTAPE_ERASE			typedef ptr TAPE_ERASE


TAPE_LOAD			equ 0
TAPE_UNLOAD			equ 1
TAPE_TENSION			equ 2
TAPE_LOCK			equ 3
TAPE_UNLOCK			equ 4
TAPE_FORMAT			equ 5

TAPE_PREPARE			STRUC
Operation			dd ?
Immediate			BOOLEAN ?
TAPE_PREPARE			ENDS
PTAPE_PREPARE			typedef ptr TAPE_PREPARE


TAPE_SETMARKS			equ 0
TAPE_FILEMARKS			equ 1
TAPE_SHORT_FILEMARKS		equ 2
TAPE_LONG_FILEMARKS		equ 3

TAPE_WRITE_MARKS		STRUC
Type				dd ?
Count				dd ?
Immediate			BOOLEAN ?
TAPE_WRITE_MARKS		ENDS
PTAPE_WRITE_MARKS		typedef ptr TAPE_WRITE_MARKS


TAPE_ABSOLUTE_POSITION		equ 0
TAPE_LOGICAL_POSITION		equ 1
TAPE_PSEUDO_LOGICAL_POSITION	equ 2

TAPE_GET_POSITION		STRUC
Type				dd ?
Partition			dd ?
_Offset				LARGE_INTEGER <>
TAPE_GET_POSITION		ENDS
PTAPE_GET_POSITION		typedef ptr TAPE_GET_POSITION


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
Method				dd ?
Partition			dd ?
_Offset				LARGE_INTEGER <>
Immediate			BOOLEAN ?
TAPE_SET_POSITION		ENDS
PTAPE_SET_POSITION		typedef ptr TAPE_SET_POSITION



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

TAPE_DRIVE_RESERVED_BIT		equ 0x80000000


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
TAPE_DRIVE_HIGH_FEATURES	equ 0x80000000

TAPE_GET_DRIVE_PARAMETERS	STRUC
ECC				BOOLEAN ?
Compression			BOOLEAN ?
DataPadding			BOOLEAN ?
ReportSetmarks			BOOLEAN ?
DefaultBlockSize		dd ?
MaximumBlockSize		dd ?
MinimumBlockSize		dd ?
MaximumPartitionCount		dd ?
FeaturesLow			dd ?
FeaturesHigh			dd ?
EOTWarningZoneSize		dd ?
TAPE_GET_DRIVE_PARAMETERS	ENDS
PTAPE_GET_DRIVE_PARAMETERS	typedef ptr TAPE_GET_DRIVE_PARAMETERS


TAPE_SET_DRIVE_PARAMETERS	STRUC
ECC				BOOLEAN ?
Compression			BOOLEAN ?
DataPadding			BOOLEAN ?
ReportSetmarks			BOOLEAN ?
EOTWarningZoneSize		dd ?
TAPE_SET_DRIVE_PARAMETERS	ENDS
PTAPE_SET_DRIVE_PARAMETERS	typedef ptr TAPE_SET_DRIVE_PARAMETERS


TAPE_GET_MEDIA_PARAMETERS	STRUC
Capacity			LARGE_INTEGER <>
Remaining			LARGE_INTEGER <>
BlockSize			dd ?
PartitionCount			dd ?
WriteProtected			BOOLEAN ?
TAPE_GET_MEDIA_PARAMETERS	ENDS
PTAPE_GET_MEDIA_PARAMETERS	typedef ptr TAPE_GET_MEDIA_PARAMETERS


TAPE_SET_MEDIA_PARAMETERS	STRUC
BlockSize			dd ?
TAPE_SET_MEDIA_PARAMETERS	ENDS
PTAPE_SET_MEDIA_PARAMETERS	typedef ptr TAPE_SET_MEDIA_PARAMETERS


TAPE_FIXED_PARTITIONS		equ 0
TAPE_SELECT_PARTITIONS		equ 1
TAPE_INITIATOR_PARTITIONS	equ 2

TAPE_CREATE_PARTITION		STRUC
Method				dd ?
Count				dd ?
Size				dd ?
TAPE_CREATE_PARTITION		ENDS
PTAPE_CREATE_PARTITION		typedef ptr TAPE_CREATE_PARTITION

TAPE_QUERY_DRIVE_PARAMETERS	equ 0
TAPE_QUERY_MEDIA_CAPACITY	equ 1
TAPE_CHECK_FOR_DRIVE_PROBLEM	equ 2
TAPE_QUERY_IO_ERROR_DATA	equ 3
TAPE_QUERY_DEVICE_ERROR_DATA	equ 4

TAPE_WMI_OPERATIONS	STRUC
Method			dd ?
DataBufferSize		dd ?
DataBuffer		PVOID ?
TAPE_WMI_OPERATIONS	ENDS
PTAPE_WMI_OPERATIONS	typedef ptr TAPE_WMI_OPERATIONS

.enum TAPE_DRIVE_PROBLEM_TYPE {
   TapeDriveProblemNone,
   TapeDriveReadWriteWarning,
   TapeDriveReadWriteError,
   TapeDriveReadWarning,
   TapeDriveWriteWarning,
   TapeDriveReadError,
   TapeDriveWriteError,
   TapeDriveHardwareError,
   TapeDriveUnsupportedMedia,
   TapeDriveScsiConnectionError,
   TapeDriveTimetoClean,
   TapeDriveCleanDriveNow,
   TapeDriveMediaLifeExpired,
   TapeDriveSnappedTape
   }

ifndef _NTTMAPI_
define _NTTMAPI_

include ktmtypes.inc


TRANSACTIONMANAGER_QUERY_INFORMATION	equ 0x0001
TRANSACTIONMANAGER_SET_INFORMATION	equ 0x0002
TRANSACTIONMANAGER_RECOVER		equ 0x0004
TRANSACTIONMANAGER_RENAME		equ 0x0008
TRANSACTIONMANAGER_CREATE_RM		equ 0x0010

TRANSACTIONMANAGER_BIND_TRANSACTION	equ 0x0020


TRANSACTIONMANAGER_GENERIC_READ equ STANDARD_RIGHTS_READ OR \
				    TRANSACTIONMANAGER_QUERY_INFORMATION

TRANSACTIONMANAGER_GENERIC_WRITE equ STANDARD_RIGHTS_WRITE OR \
				     TRANSACTIONMANAGER_SET_INFORMATION OR \
				     TRANSACTIONMANAGER_RECOVER OR \
				     TRANSACTIONMANAGER_RENAME OR \
				     TRANSACTIONMANAGER_CREATE_RM

TRANSACTIONMANAGER_GENERIC_EXECUTE equ STANDARD_RIGHTS_EXECUTE

TRANSACTIONMANAGER_ALL_ACCESS equ STANDARD_RIGHTS_REQUIRED OR \
				  TRANSACTIONMANAGER_GENERIC_READ OR \
				  TRANSACTIONMANAGER_GENERIC_WRITE OR \
				  TRANSACTIONMANAGER_GENERIC_EXECUTE OR \
				  TRANSACTIONMANAGER_BIND_TRANSACTION
TRANSACTION_QUERY_INFORMATION	equ 0x0001
TRANSACTION_SET_INFORMATION	equ 0x0002
TRANSACTION_ENLIST		equ 0x0004
TRANSACTION_COMMIT		equ 0x0008
TRANSACTION_ROLLBACK		equ 0x0010
TRANSACTION_PROPAGATE		equ 0x0020
TRANSACTION_RIGHT_RESERVED1	equ 0x0040


TRANSACTION_GENERIC_READ	equ STANDARD_RIGHTS_READ OR \
				    TRANSACTION_QUERY_INFORMATION OR \
				    SYNCHRONIZE

TRANSACTION_GENERIC_WRITE	equ STANDARD_RIGHTS_WRITE OR \
				    TRANSACTION_SET_INFORMATION OR \
				    TRANSACTION_COMMIT OR \
				    TRANSACTION_ENLIST OR \
				    TRANSACTION_ROLLBACK OR \
				    TRANSACTION_PROPAGATE OR \
				    SYNCHRONIZE

TRANSACTION_GENERIC_EXECUTE	equ STANDARD_RIGHTS_EXECUTE OR \
				    TRANSACTION_COMMIT	OR \
				    TRANSACTION_ROLLBACK  OR \
				    SYNCHRONIZE

TRANSACTION_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED OR \
				    TRANSACTION_GENERIC_READ OR \
				    TRANSACTION_GENERIC_WRITE OR \
				    TRANSACTION_GENERIC_EXECUTE

TRANSACTION_RESOURCE_MANAGER_RIGHTS equ TRANSACTION_GENERIC_READ OR \
				    STANDARD_RIGHTS_WRITE OR \
				    TRANSACTION_SET_INFORMATION OR \
				    TRANSACTION_ENLIST OR \
				    TRANSACTION_ROLLBACK OR \
				    TRANSACTION_PROPAGATE OR \
				    SYNCHRONIZE

RESOURCEMANAGER_QUERY_INFORMATION	equ 0x0001
RESOURCEMANAGER_SET_INFORMATION		equ 0x0002
RESOURCEMANAGER_RECOVER			equ 0x0004
RESOURCEMANAGER_ENLIST			equ 0x0008
RESOURCEMANAGER_GET_NOTIFICATION	equ 0x0010
RESOURCEMANAGER_REGISTER_PROTOCOL	equ 0x0020
RESOURCEMANAGER_COMPLETE_PROPAGATION	equ 0x0040

RESOURCEMANAGER_GENERIC_READ equ STANDARD_RIGHTS_READ OR \
			RESOURCEMANAGER_QUERY_INFORMATION OR \
			SYNCHRONIZE

RESOURCEMANAGER_GENERIC_WRITE equ STANDARD_RIGHTS_WRITE OR \
			RESOURCEMANAGER_SET_INFORMATION OR \
			RESOURCEMANAGER_RECOVER OR \
			RESOURCEMANAGER_ENLIST OR \
			RESOURCEMANAGER_GET_NOTIFICATION OR \
			RESOURCEMANAGER_REGISTER_PROTOCOL OR \
			RESOURCEMANAGER_COMPLETE_PROPAGATION OR \
			SYNCHRONIZE

RESOURCEMANAGER_GENERIC_EXECUTE equ STANDARD_RIGHTS_EXECUTE OR \
			RESOURCEMANAGER_RECOVER OR \
			RESOURCEMANAGER_ENLIST OR \
			RESOURCEMANAGER_GET_NOTIFICATION OR \
			RESOURCEMANAGER_COMPLETE_PROPAGATION OR \
			SYNCHRONIZE

RESOURCEMANAGER_ALL_ACCESS equ STANDARD_RIGHTS_REQUIRED OR \
			RESOURCEMANAGER_GENERIC_READ OR \
			RESOURCEMANAGER_GENERIC_WRITE OR \
			RESOURCEMANAGER_GENERIC_EXECUTE

ENLISTMENT_QUERY_INFORMATION	equ 0x0001
ENLISTMENT_SET_INFORMATION	equ 0x0002
ENLISTMENT_RECOVER		equ 0x0004
ENLISTMENT_SUBORDINATE_RIGHTS	equ 0x0008
ENLISTMENT_SUPERIOR_RIGHTS	equ 0x0010

ENLISTMENT_GENERIC_READ equ STANDARD_RIGHTS_READ OR \
			ENLISTMENT_QUERY_INFORMATION

ENLISTMENT_GENERIC_WRITE equ (STANDARD_RIGHTS_WRITE OR \
			ENLISTMENT_SET_INFORMATION OR \
			ENLISTMENT_RECOVER OR \
			ENLISTMENT_SUBORDINATE_RIGHTS OR \
			ENLISTMENT_SUPERIOR_RIGHTS)

ENLISTMENT_GENERIC_EXECUTE equ (STANDARD_RIGHTS_EXECUTE OR \
			ENLISTMENT_RECOVER OR \
			ENLISTMENT_SUBORDINATE_RIGHTS OR \
			ENLISTMENT_SUPERIOR_RIGHTS)

ENLISTMENT_ALL_ACCESS	equ (STANDARD_RIGHTS_REQUIRED OR \
			ENLISTMENT_GENERIC_READ OR \
			ENLISTMENT_GENERIC_WRITE OR \
			ENLISTMENT_GENERIC_EXECUTE)

.enum TRANSACTION_OUTCOME {
    TransactionOutcomeUndetermined = 1,
    TransactionOutcomeCommitted,
    TransactionOutcomeAborted,
    }

.enum TRANSACTION_STATE {
    TransactionStateNormal = 1,
    TransactionStateIndoubt,
    TransactionStateCommittedNotify,
    }

TRANSACTION_BASIC_INFORMATION STRUC
TransactionId		GUID <>
State			dd ?
Outcome			dd ?
TRANSACTION_BASIC_INFORMATION ENDS
PTRANSACTION_BASIC_INFORMATION typedef ptr TRANSACTION_BASIC_INFORMATION

TRANSACTIONMANAGER_BASIC_INFORMATION STRUC
TmIdentity		GUID <>
VirtualClock		LARGE_INTEGER <>
TRANSACTIONMANAGER_BASIC_INFORMATION ENDS
PTRANSACTIONMANAGER_BASIC_INFORMATION typedef ptr TRANSACTIONMANAGER_BASIC_INFORMATION

TRANSACTIONMANAGER_LOG_INFORMATION STRUC
LogIdentity		GUID <>
TRANSACTIONMANAGER_LOG_INFORMATION ENDS
PTRANSACTIONMANAGER_LOG_INFORMATION typedef ptr TRANSACTIONMANAGER_LOG_INFORMATION

TRANSACTIONMANAGER_LOGPATH_INFORMATION STRUC
LogPathLength		dd ?
LogPath			dw ?
TRANSACTIONMANAGER_LOGPATH_INFORMATION ENDS
PTRANSACTIONMANAGER_LOGPATH_INFORMATION typedef ptr TRANSACTIONMANAGER_LOGPATH_INFORMATION

TRANSACTIONMANAGER_RECOVERY_INFORMATION STRUC
LastRecoveredLsn	ULONGLONG ?
TRANSACTIONMANAGER_RECOVERY_INFORMATION ENDS
PTRANSACTIONMANAGER_RECOVERY_INFORMATION typedef ptr TRANSACTIONMANAGER_RECOVERY_INFORMATION


TRANSACTIONMANAGER_OLDEST_INFORMATION STRUC
OldestTransactionGuid	GUID <>
TRANSACTIONMANAGER_OLDEST_INFORMATION ENDS
PTRANSACTIONMANAGER_OLDEST_INFORMATION typedef ptr TRANSACTIONMANAGER_OLDEST_INFORMATION


TRANSACTION_PROPERTIES_INFORMATION STRUC
IsolationLevel		dd ?
IsolationFlags		dd ?
Timeout			LARGE_INTEGER <>
Outcome			dd ?
DescriptionLength	dd ?
Description		dw ?
TRANSACTION_PROPERTIES_INFORMATION ENDS
PTRANSACTION_PROPERTIES_INFORMATION typedef ptr TRANSACTION_PROPERTIES_INFORMATION

TRANSACTION_BIND_INFORMATION STRUC
TmHandle		HANDLE ?
TRANSACTION_BIND_INFORMATION ENDS
PTRANSACTION_BIND_INFORMATION typedef ptr TRANSACTION_BIND_INFORMATION

TRANSACTION_ENLISTMENT_PAIR  STRUC
EnlistmentId		GUID <>
ResourceManagerId	GUID <>
TRANSACTION_ENLISTMENT_PAIR ENDS
PTRANSACTION_ENLISTMENT_PAIR typedef ptr TRANSACTION_ENLISTMENT_PAIR

TRANSACTION_ENLISTMENTS_INFORMATION STRUC
NumberOfEnlistments	dd ?
EnlistmentPair		TRANSACTION_ENLISTMENT_PAIR <>
TRANSACTION_ENLISTMENTS_INFORMATION ENDS
PTRANSACTION_ENLISTMENTS_INFORMATION typedef ptr TRANSACTION_ENLISTMENTS_INFORMATION

TRANSACTION_SUPERIOR_ENLISTMENT_INFORMATION STRUC
SuperiorEnlistmentPair	TRANSACTION_ENLISTMENT_PAIR <>
TRANSACTION_SUPERIOR_ENLISTMENT_INFORMATION ENDS
PTRANSACTION_SUPERIOR_ENLISTMENT_INFORMATION typedef ptr TRANSACTION_SUPERIOR_ENLISTMENT_INFORMATION


RESOURCEMANAGER_BASIC_INFORMATION STRUC
ResourceManagerId	GUID <>
DescriptionLength	dd ?
Description		dw ?
RESOURCEMANAGER_BASIC_INFORMATION ENDS
PRESOURCEMANAGER_BASIC_INFORMATION typedef ptr RESOURCEMANAGER_BASIC_INFORMATION

RESOURCEMANAGER_COMPLETION_INFORMATION STRUC
IoCompletionPortHandle	HANDLE ?
CompletionKey		ULONG_PTR ?
RESOURCEMANAGER_COMPLETION_INFORMATION ENDS
PRESOURCEMANAGER_COMPLETION_INFORMATION typedef ptr RESOURCEMANAGER_COMPLETION_INFORMATION

.enum TRANSACTION_INFORMATION_CLASS {
    TransactionBasicInformation,
    TransactionPropertiesInformation,
    TransactionEnlistmentInformation,
    TransactionSuperiorEnlistmentInformation,
    TransactionBindInformation, ; private and deprecated
    TransactionDTCPrivateInformation ; private and deprecated
    }

.enum TRANSACTIONMANAGER_INFORMATION_CLASS {
    TransactionManagerBasicInformation,
    TransactionManagerLogInformation,
    TransactionManagerLogPathInformation,
    TransactionManagerRecoveryInformation = 4,
    TransactionManagerOnlineProbeInformation = 3,
    TransactionManagerOldestTransactionInformation = 5
    }

.enum RESOURCEMANAGER_INFORMATION_CLASS {
    ResourceManagerBasicInformation,
    ResourceManagerCompletionInformation
    }

ENLISTMENT_BASIC_INFORMATION STRUC
EnlistmentId		GUID <>
TransactionId		GUID <>
ResourceManagerId	GUID <>
ENLISTMENT_BASIC_INFORMATION ENDS
PENLISTMENT_BASIC_INFORMATION typedef ptr ENLISTMENT_BASIC_INFORMATION

ENLISTMENT_CRM_INFORMATION STRUC
CrmTransactionManagerId GUID <>
CrmResourceManagerId	GUID <>
CrmEnlistmentId		GUID <>
ENLISTMENT_CRM_INFORMATION ENDS
PENLISTMENT_CRM_INFORMATION typedef ptr ENLISTMENT_CRM_INFORMATION

.enum ENLISTMENT_INFORMATION_CLASS {
    EnlistmentBasicInformation,
    EnlistmentRecoveryInformation,
    EnlistmentCrmInformation
    }

TRANSACTION_LIST_ENTRY	STRUC
UOW			UOW <>
TRANSACTION_LIST_ENTRY	ENDS
PTRANSACTION_LIST_ENTRY typedef ptr TRANSACTION_LIST_ENTRY

TRANSACTION_LIST_INFORMATION  STRUC
NumberOfTransactions	dd ?
TransactionInformation	TRANSACTION_LIST_ENTRY <>
TRANSACTION_LIST_INFORMATION ENDS
PTRANSACTION_LIST_INFORMATION typedef ptr TRANSACTION_LIST_INFORMATION

.enum KTMOBJECT_TYPE {
    KTMOBJECT_TRANSACTION,
    KTMOBJECT_TRANSACTION_MANAGER,
    KTMOBJECT_RESOURCE_MANAGER,
    KTMOBJECT_ENLISTMENT,
    KTMOBJECT_INVALID
    }
PKTMOBJECT_TYPE		typedef ptr KTMOBJECT_TYPE

KTMOBJECT_CURSOR	STRUC
LastQuery		GUID <>
ObjectIdCount		dd ?
ObjectIds		GUID <>
KTMOBJECT_CURSOR	ENDS
PKTMOBJECT_CURSOR	typedef ptr KTMOBJECT_CURSOR

endif ;; _NTTMAPI_

TP_VERSION		typedef DWORD
PTP_VERSION		typedef ptr TP_VERSION
CALLBACK(PTP_CALLBACK_INSTANCE)
CALLBACK(PTP_SIMPLE_CALLBACK, Instance:PTP_CALLBACK_INSTANCE, Context:PVOID)
PTP_POOL		typedef ptr TP_POOL

.enum TP_CALLBACK_PRIORITY {
    TP_CALLBACK_PRIORITY_HIGH,
    TP_CALLBACK_PRIORITY_NORMAL,
    TP_CALLBACK_PRIORITY_LOW,
    TP_CALLBACK_PRIORITY_INVALID,
    TP_CALLBACK_PRIORITY_COUNT = TP_CALLBACK_PRIORITY_INVALID
    }

TP_POOL_STACK_INFORMATION STRUC
StackReserve		SIZE_T ?
StackCommit		SIZE_T ?
TP_POOL_STACK_INFORMATION ENDS
PTP_POOL_STACK_INFORMATION typedef ptr TP_POOL_STACK_INFORMATION

PTP_CLEANUP_GROUP	typedef ptr TP_CLEANUP_GROUP
CALLBACK(PTP_CLEANUP_GROUP_CANCEL_CALLBACK, ObjectContext:PVOID, CleanupContext:PVOID)

if (_WIN32_WINNT GE _WIN32_WINNT_WIN7)

TP_CALLBACK_ENVIRON_V3	STRUC
Version			TP_VERSION ?
Pool			PTP_POOL ?
CleanupGroup		PTP_CLEANUP_GROUP ?
CleanupGroupCancelCallback PTP_CLEANUP_GROUP_CANCEL_CALLBACK ?
RaceDll			PVOID ?
ActivationContext	ACTIVATION_CONTEXT ?
FinalizationCallback	PTP_SIMPLE_CALLBACK ?
UNION u
 Flags			dd ?
 RECORD s
  LongFunction		dd :  1 ?
  Persistent		dd :  1 ?
  Private		dd : 30 ?
 ENDS
ENDS
CallbackPriority	TP_CALLBACK_PRIORITY ?
Size			dd ?
TP_CALLBACK_ENVIRON_V3	ENDS
PTP_CALLBACK_ENVIRON	typedef ptr TP_CALLBACK_ENVIRON_V3

TP_CALLBACK_ENVIRON	typedef TP_CALLBACK_ENVIRON_V3

else

TP_CALLBACK_ENVIRON_V1	STRUC
Version			TP_VERSION ?
Pool			PTP_POOL ?
CleanupGroup		PTP_CLEANUP_GROUP ?
CleanupGroupCancelCallback PTP_CLEANUP_GROUP_CANCEL_CALLBACK ?
RaceDll			PVOID ?
ActivationContext	ACTIVATION_CONTEXT ?
FinalizationCallback	PTP_SIMPLE_CALLBACK ?
UNION u
 Flags			dd ?
 RECORD s
  LongFunction		dd :  1 ?
  Persistent		dd :  1 ?
  Private		dd : 30 ?
 ENDS
ENDS
TP_CALLBACK_ENVIRON_V1	ENDS
PTP_CALLBACK_ENVIRON	typedef ptr TP_CALLBACK_ENVIRON_V1
TP_CALLBACK_ENVIRON	typedef TP_CALLBACK_ENVIRON_V1

endif

ifndef MIDL_PASS

;VOID
ifdef _WIN64
TpInitializeCallbackEnviron proto :PTP_CALLBACK_ENVIRON
TpSetCallbackThreadpool proto :PTP_CALLBACK_ENVIRON, :PTP_POOL
TpSetCallbackCleanupGroup proto :PTP_CALLBACK_ENVIRON, :PTP_CLEANUP_GROUP,
	:PTP_CLEANUP_GROUP_CANCEL_CALLBACK
TpSetCallbackActivationContext proto :PTP_CALLBACK_ENVIRON, :ptr ACTIVATION_CONTEXT
TpSetCallbackNoActivationContext proto :PTP_CALLBACK_ENVIRON
TpSetCallbackLongFunction proto :PTP_CALLBACK_ENVIRON
TpSetCallbackRaceWithDll proto :PTP_CALLBACK_ENVIRON, :ptr
endif

TpInitializeCallbackEnviron macro this
	assume this:PTP_CALLBACK_ENVIRON
if (_WIN32_WINNT GE _WIN32_WINNT_WIN7)
	mov [this].Version,3
else
	mov [this].Version,1
endif
	mov [this].Pool,NULL
	mov [this].CleanupGroup,NULL
	mov [this].CleanupGroupCancelCallback,NULL
	mov [this].RaceDll,NULL
	mov [this].ActivationContext,NULL
	mov [this].FinalizationCallback,NULL
	mov [this].u.Flags,0
if (_WIN32_WINNT GE _WIN32_WINNT_WIN7)
	mov [this].CallbackPriority,TP_CALLBACK_PRIORITY_NORMAL
	mov [this].Size,TP_CALLBACK_ENVIRON
endif
	assume this:nothing
	exitm<>
	endm

TpSetCallbackThreadpool macro CallbackEnviron, Pool
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.Pool,Pool
	exitm<>
	endm

TpSetCallbackCleanupGroup macro CallbackEnviron, CleanupGroup, CleanupGroupCancelCallback
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.CleanupGroup,CleanupGroup
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.CleanupGroupCancelCallback,CleanupGroupCancelCallback
	exitm<>
	endm

TpSetCallbackActivationContext macro CallbackEnviron, ActivationContext
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.ActivationContext,ActivationContext
	exitm<>
	endm

TpSetCallbackNoActivationContext macro CallbackEnviron
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.ActivationContext,-1
	exitm<>
	endm

TpSetCallbackLongFunction macro CallbackEnviron
	or [CallbackEnviron].TP_CALLBACK_ENVIRON.u.Flags,1 ; .LongFunction
	exitm<>
	endm

TpSetCallbackRaceWithDll macro CallbackEnviron, DllHandle
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.RaceDll,DllHandle
	exitm<>
	endm

TpSetCallbackFinalizationCallback macro CallbackEnviron, FinalizationCallback
	mov CallbackEnviron.FinalizationCallback,FinalizationCallback
	exitm<>
	endm
if (_WIN32_WINNT GE _WIN32_WINNT_WIN7)

TpSetCallbackPriority macro CallbackEnviron, Priority
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.CallbackPriority,Priority
	exitm<>
	endm
endif

TpSetCallbackPersistent macro CallbackEnviron
	mov [CallbackEnviron].TP_CALLBACK_ENVIRON.u.s.Persistent,1
	exitm<>
	endm

TpDestroyCallbackEnviron macro CallbackEnviron
	endm

endif ;; !MIDL_PASS

PTP_WORK		typedef ptr TP_WORK

CALLBACK(PTP_WORK_CALLBACK, Instance:PTP_CALLBACK_INSTANCE, Context:PVOID, Work:PTP_WORK)

PTP_TIMER		typedef ptr TP_TIMER

CALLBACK(PTP_TIMER_CALLBACK, Instance:PTP_CALLBACK_INSTANCE, Context:PVOID, Timer:PTP_TIMER)

TP_WAIT_RESULT		typedef DWORD
PTP_WAIT		typedef ptr TP_WAIT

CALLBACK(PTP_WAIT_CALLBACK, Instance:PTP_CALLBACK_INSTANCE, Context:PVOID, _Wait:PTP_WAIT, WaitResult:TP_WAIT_RESULT)

PTP_IO			typedef ptr TP_IO

if defined(_M_AMD64) or defined(_WIN64)
;TEB *
NtCurrentTeb macro
	exitm<__readgsqword(FIELD_OFFSET(NT_TIB, Self))>
	endm
;PVOID
GetCurrentFiber macro
	exitm<__readgsqword(FIELD_OFFSET(NT_TIB, FiberData))>
	endm
;PVOID
GetFiberData macro
	exitm<GetCurrentFiber()>
	endm
endif


if defined(_M_IX86) AND NOT defined(MIDL_PASS)

PcTeb			equ 0x18

if (_MSC_FULL_VER GE 13012035)
NtCurrentTeb macro
	exitm<__readfsdword(PcTeb)>
	endm

else
NtCurrentTeb macro
	mov eax,fs:[PcTeb]
	exitm<eax>
	endm

endif
endif

if (_WIN32_WINNT GT 0x0500) OR (_WIN32_FUSION GE 0x0100) ;OR ISOLATION_AWARE_ENABLED
ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION		equ 1
ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION		equ 2
ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION	equ 3
ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION	equ 4
ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION	equ 5
ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION equ 6
ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION	equ 7
ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE	equ 8
ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES		equ 9
ACTIVATION_CONTEXT_SECTION_APPLICATION_SETTINGS		equ 10
ACTIVATION_CONTEXT_SECTION_COMPATIBILITY_INFO		equ 11
endif

.pragma pack(pop)
endif
.pragma list(pop)
