ifndef _STRSAFE_H_INCLUDED_
_STRSAFE_H_INCLUDED_ equ <>

include stdio.inc
include string.inc
include stdarg.inc
include specstrings.inc
include winapifamily.inc

ALIGNMENT_MACHINE equ 1

ifndef _HRESULT_DEFINED
_HRESULT_DEFINED equ <>
HRESULT typedef SDWORD
endif

SUCCEEDED macro hr
    if (type(hr))
	exitm<(hr !>= 0)>
    else
	exitm<((hr) GE 0)>
    endif
	endm
FAILED macro hr
    if (type(hr))
	exitm<(hr !< 0)>
    else
	exitm<((hr) LT 0)>
    endif
	endm

S_OK	equ 0

ifndef STRSAFE_USE_SECURE_CRT
if defined(__GOT_SECURE_LIB__) AND (__GOT_SECURE_LIB__ GE 200402)
STRSAFE_USE_SECURE_CRT	equ 0
else
STRSAFE_USE_SECURE_CRT	equ 0
endif
endif

ifdef _M_CEE_PURE
STRSAFEAPI		equ <clrcall>
else
STRSAFEAPI		equ <stdcall>
endif

if defined(STRSAFE_LIB_IMPL) OR defined(STRSAFE_LIB)
STRSAFEWORKERAPI	equ <stdcall>
else
STRSAFEWORKERAPI	equ <STRSAFEAPI>
endif

ifdef STRSAFE_LOCALE_FUNCTIONS
if defined(STRSAFE_LOCALE_LIB_IMPL) OR defined(STRSAFE_LIB)
STRSAFELOCALEWORKERAPI	equ <stdcall>
else
STRSAFELOCALEWORKERAPI	equ <STRSAFEAPI>
endif
endif

if defined(STRSAFE_LIB) or not defined(__PE__)
includelib strsafe.lib
endif

if defined(STRSAFE_NO_CB_FUNCTIONS) AND defined(STRSAFE_NO_CCH_FUNCTIONS)
.err<cannot specify both STRSAFE_NO_CB_FUNCTIONS and STRSAFE_NO_CCH_FUNCTIONS>
endif

ifndef STRSAFE_MAX_CCH
STRSAFE_MAX_CCH		equ 2147483647
endif

C_ASSERT macro exp:vararg
    if not (exp)
	.err<exp>
    endif
    exitm<>
    endm

C_ASSERT(STRSAFE_MAX_CCH LE 2147483647)
C_ASSERT(STRSAFE_MAX_CCH GT 1)

STRSAFE_MAX_LENGTH	equ (STRSAFE_MAX_CCH - 1)


STRSAFE_IGNORE_NULLS	equ 0x00000100
STRSAFE_FILL_BEHIND_NULL equ 0x00000200
STRSAFE_FILL_ON_FAILURE equ 0x00000400
STRSAFE_NULL_ON_FAILURE equ 0x00000800
STRSAFE_NO_TRUNCATION	equ 0x00001000

STRSAFE_VALID_FLAGS	equ (0x000000FF OR STRSAFE_IGNORE_NULLS OR STRSAFE_FILL_BEHIND_NULL OR STRSAFE_FILL_ON_FAILURE OR STRSAFE_NULL_ON_FAILURE OR STRSAFE_NO_TRUNCATION)

STRSAFE_FILL_BYTE macro x
	exitm<(((x AND 0x000000FF) OR STRSAFE_FILL_BEHIND_NULL))>
	endm
STRSAFE_FAILURE_BYTE macro x
	exitm<(((x AND 0x000000FF) OR STRSAFE_FILL_ON_FAILURE))>
	endm

STRSAFE_GET_FILL_PATTERN macro dwFlags
	exitm<(dwFlags AND 0x000000FF)>
	endm


STRSAFE_E_INSUFFICIENT_BUFFER equ 0x8007007A
STRSAFE_E_INVALID_PARAMETER equ 0x80070057
STRSAFE_E_END_OF_FILE	equ 0x80070026

STRSAFE_LPSTR		typedef ptr sbyte
STRSAFE_LPCSTR		typedef ptr sbyte
STRSAFE_LPWSTR		typedef ptr wchar_t
STRSAFE_LPCWSTR		typedef ptr wchar_t
STRSAFE_LPCUWSTR	typedef ptr wchar_t

STRSAFE_PCNZCH		typedef ptr sbyte
STRSAFE_PCNZWCH		typedef ptr wchar_t
STRSAFE_PCUNZWCH	typedef ptr wchar_t

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEWORKERAPI
StringLengthWorkerA proto WINAPI \
		   psz: STRSAFE_PCNZCH,
		cchMax: size_t,
	    pcchLength: ptr size_t

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEWORKERAPI
StringLengthWorkerW proto WINAPI \
		   psz: STRSAFE_PCNZWCH,
		cchMax: size_t,
	    pcchLength: ptr size_t

ifdef ALIGNMENT_MACHINE
;STRSAFEWORKERAPI
UnalignedStringLengthWorkerW proto WINAPI \
		   psz: STRSAFE_PCUNZWCH,
		cchMax: size_t,
	    pcchLength: ptr size_t

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEWORKERAPI
StringExValidateSrcA proto WINAPI \
	       ppszSrc: ptr STRSAFE_PCNZCH,
	    pcchToRead: ptr size_t,
		cchMax: size_t,
	       dwFlags: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEWORKERAPI
StringExValidateSrcW proto WINAPI \
	       ppszSrc: ptr STRSAFE_PCNZWCH,
	    pcchToRead: ptr size_t,
		cchMax: size_t,
	       dwFlags: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEWORKERAPI
StringValidateDestA proto WINAPI \
	       pszDest: STRSAFE_PCNZCH,
	       cchDest: size_t,
		cchMax: size_t

;STRSAFEWORKERAPI
StringValidateDestAndLengthA proto WINAPI \
	       pszDest: STRSAFE_LPCSTR,
	       cchDest: size_t,
	pcchDestLength: ptr size_t,
		cchMax: size_t


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEWORKERAPI
StringValidateDestW proto WINAPI \
	       pszDest: STRSAFE_PCNZWCH,
	       cchDest: size_t,
		cchMax: size_t

;STRSAFEWORKERAPI
StringValidateDestAndLengthW proto WINAPI \
	       pszDest: STRSAFE_LPCWSTR,
	       cchDest: size_t,
	pcchDestLength: ptr size_t,
		cchMax: size_t


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEWORKERAPI
StringExValidateDestA proto WINAPI \
	       pszDest: STRSAFE_PCNZCH,
	       cchDest: size_t,
		cchMax: size_t,
	       dwFlags: DWORD


;STRSAFEWORKERAPI
StringExValidateDestAndLengthA proto WINAPI \
	       pszDest: STRSAFE_LPCSTR,
	       cchDest: size_t,
	pcchDestLength: ptr size_t,
		cchMax: size_t,
	       dwFlags: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEWORKERAPI
StringExValidateDestW proto WINAPI \
	       pszDest: STRSAFE_PCNZWCH,
	       cchDest: size_t,
		cchMax: size_t,
	       dwFlags: DWORD


;STRSAFEWORKERAPI
StringExValidateDestAndLengthW proto WINAPI \
	       pszDest: STRSAFE_LPCWSTR,
	       cchDest: size_t,
	pcchDestLength: ptr size_t,
		cchMax: size_t,
	       dwFlags: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEWORKERAPI
StringCopyWorkerA proto WINAPI \
	       pszDest: STRSAFE_LPSTR,
	       cchDest: size_t,
     pcchNewDestLength: ptr size_t,
		pszSrc: STRSAFE_PCNZCH,
	     cchToCopy: size_t


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEWORKERAPI
StringCopyWorkerW proto WINAPI \
	       pszDest: STRSAFE_LPWSTR,
	       cchDest: size_t,
     pcchNewDestLength: ptr size_t,
		pszSrc: STRSAFE_PCNZWCH,
	     cchToCopy: size_t


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEWORKERAPI
StringVPrintfWorkerA proto WINAPI \
	       pszDest: STRSAFE_LPSTR,
	       cchDest: size_t,
     pcchNewDestLength: ptr size_t,
	     pszFormat: STRSAFE_LPCSTR,
	       argList: va_list


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifdef STRSAFE_LOCALE_FUNCTIONS
;STRSAFELOCALEWORKERAPI
StringVPrintf_lWorkerA proto WINAPI \
	       pszDest: STRSAFE_LPSTR,
	       cchDest: size_t,
     pcchNewDestLength: size_t,
	     pszFormat: STRSAFE_LPCSTR,
		locale: _locale_t,
	       argList: va_list
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEWORKERAPI
StringVPrintfWorkerW proto WINAPI \
	       pszDest: STRSAFE_LPWSTR,
	       cchDest: size_t,
     pcchNewDestLength: ptr size_t,
	     pszFormat: STRSAFE_LPCWSTR,
	       argList: va_list


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifdef STRSAFE_LOCALE_FUNCTIONS
;STRSAFELOCALEWORKERAPI
StringVPrintf_lWorkerW proto WINAPI \
	       pszDest: STRSAFE_LPWSTR,
	       cchDest: size_t,
     pcchNewDestLength: ptr size_t,
	     pszFormat: STRSAFE_LPCWSTR,
		locale: _locale_t,
	       argList: va_list
endif

endif

ifndef STRSAFE_LIB_IMPL

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEAPI
StringGetsWorkerA proto WINAPI \
	       pszDest: STRSAFE_LPSTR,
	       cchDest: size_t,
     pcchNewDestLength: ptr size_t

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEAPI
StringGetsWorkerW proto WINAPI \
	       pszDest: STRSAFE_LPWSTR,
	       cchDest: size_t,
     pcchNewDestLength: ptr size_t

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;STRSAFEWORKERAPI
StringExHandleFillBehindNullA proto WINAPI \
	    pszDestEnd: STRSAFE_LPSTR,
	   cbRemaining: size_t,
	       dwFlags: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;STRSAFEWORKERAPI
StringExHandleFillBehindNullW proto WINAPI \
	    pszDestEnd: STRSAFE_LPWSTR,
	   cbRemaining: size_t,
	       dwFlags: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

endif

__WARNING_CYCLOMATIC_COMPLEXITY equ 28734
__WARNING_USING_UNINIT_VAR equ 6001
__WARNING_RETURN_UNINIT_VAR equ 6101
__WARNING_DEREF_NULL_PTR equ 6011
__WARNING_MISSING_ZERO_TERMINATION2 equ 6054
__WARNING_INVALID_PARAM_VALUE_1 equ 6387
__WARNING_INCORRECT_ANNOTATION equ 26007
__WARNING_POTENTIAL_BUFFER_OVERFLOW_HIGH_PRIORITY equ 26015
__WARNING_PRECONDITION_NULLTERMINATION_VIOLATION equ 26035
__WARNING_POSTCONDITION_NULLTERMINATION_VIOLATION equ 26036
__WARNING_HIGH_PRIORITY_OVERFLOW_POSTCONDITION equ 26045
__WARNING_RANGE_POSTCONDITION_VIOLATION equ 26061
__WARNING_POTENTIAL_RANGE_POSTCONDITION_VIOLATION equ 26071
__WARNING_INVALID_PARAM_VALUE_3 equ 28183
__WARNING_RETURNING_BAD_RESULT equ 28196
__WARNING_BANNED_API_USAGE equ 28719
__WARNING_POST_EXPECTED equ 28210

ifndef STRSAFE_LIB_IMPL

ifndef STRSAFE_NO_CCH_FUNCTIONS

StringCchCopyA proto pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR
StringCchCopyW proto pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR

ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCopy		equ <StringCchCopyW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCopy		equ <StringCchCopyA>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

endif

endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCopy		equ <StringCbCopyW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCopy		equ <StringCbCopyA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCopyEx		equ <StringCchCopyExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCopyEx		equ <StringCchCopyExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCopyEx		equ <StringCbCopyExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCopyEx		equ <StringCbCopyExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCopyN		equ <StringCchCopyNW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCopyN		equ <StringCchCopyNA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCopyN		equ <StringCbCopyNW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCopyN		equ <StringCbCopyNA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCopyNEx	equ <StringCchCopyNExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCopyNEx	equ <StringCchCopyNExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCopyNEx		equ <StringCbCopyNExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCopyNEx		equ <StringCbCopyNExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS

StringCchCatA proto  pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR
StringCchCatW proto  pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR

ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCat		equ <StringCchCatW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCat		equ <StringCchCatA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCat		equ <StringCbCatW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCat		equ <StringCbCatA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCatEx		equ <StringCchCatExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCatEx		equ <StringCchCatExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCatEx		equ <StringCbCatExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCatEx		equ <StringCbCatExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCatN		equ <StringCchCatNW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCatN		equ <StringCchCatNA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCatN		equ <StringCbCatNW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCatN		equ <StringCbCatNA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchCatNEx		equ <StringCchCatNExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchCatNEx		equ <StringCchCatNExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbCatNEx		equ <StringCbCatNExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbCatNEx		equ <StringCbCatNExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchVPrintf	equ <StringCchVPrintfW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchVPrintf	equ <StringCchVPrintfA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchVPrintf_l	equ <StringCchVPrintf_lW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchVPrintf_l	equ <StringCchVPrintf_lA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbVPrintf		equ <StringCbVPrintfW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbVPrintf		equ <StringCbVPrintfA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbVPrintf_l	equ <StringCbVPrintf_lW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbVPrintf_l	equ <StringCbVPrintf_lA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef _M_CEE_PURE

ifndef STRSAFE_NO_CCH_FUNCTIONS

ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchPrintf		equ <StringCchPrintfW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchPrintf		equ <StringCchPrintfA>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchPrintfA proto pszDest:STRSAFE_LPSTR, cchDest:size_t, pszFormat:STRSAFE_LPCSTR, :vararg
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchPrintfW proto pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszFormat:STRSAFE_LPCWSTR, :vararg
endif

endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchPrintf_l	equ <StringCchPrintf_lW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchPrintf_l	equ <StringCchPrintf_lA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbPrintf		equ <StringCbPrintfW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbPrintf		equ <StringCbPrintfA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbPrintf_l	equ <StringCbPrintf_lW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbPrintf_l	equ <StringCbPrintf_lA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchPrintfEx	equ <StringCchPrintfExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchPrintfEx	equ <StringCchPrintfExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchPrintf_lEx	equ <StringCchPrintf_lExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchPrintf_lEx	equ <StringCchPrintf_lExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbPrintfEx	equ <StringCbPrintfExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbPrintfEx	equ <StringCbPrintfExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbPrintf_lEx	equ <StringCbPrintf_lExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbPrintf_lEx	equ <StringCbPrintf_lExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchVPrintfEx	equ <StringCchVPrintfExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchVPrintfEx	equ <StringCchVPrintfExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchVPrintf_lEx	equ <StringCchVPrintf_lExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchVPrintf_lEx	equ <StringCchVPrintf_lExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbVPrintfEx	equ <StringCbVPrintfExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbVPrintfEx	equ <StringCbVPrintfExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbVPrintf_lEx	equ <StringCbVPrintf_lExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbVPrintf_lEx	equ <StringCbVPrintf_lExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_LIB_IMPL

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchGets		equ <StringCchGetsW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchGets		equ <StringCchGetsA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbGets		equ <StringCbGetsW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbGets		equ <StringCbGetsA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchGetsEx		equ <StringCchGetsExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchGetsEx		equ <StringCchGetsExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbGetsEx		equ <StringCbGetsExW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbGetsEx		equ <StringCbGetsExA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCchLength		equ <StringCchLengthW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCchLength		equ <StringCchLengthA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StringCbLength		equ <StringCbLengthW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
StringCbLength		equ <StringCbLengthA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
UnalignedStringCchLength equ <UnalignedStringCchLengthW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
UnalignedStringCchLength equ <StringCchLengthA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifdef ALIGNMENT_MACHINE
else
UnalignedStringCchLengthW equ <StringCchLengthW>
endif
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
UnalignedStringCbLength equ <UnalignedStringCbLengthW>
endif
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
UnalignedStringCbLength equ <StringCbLengthA>
endif
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifdef ALIGNMENT_MACHINE
else
UnalignedStringCbLengthW equ <StringCbLengthW>
endif
endif
endif

endif

if defined(STRSAFE_LIB_IMPL) OR NOT defined(STRSAFE_LIB)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifdef ALIGNMENT_MACHINE
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
ifdef STRSAFE_LOCALE_FUNCTIONS
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifdef STRSAFE_LOCALE_FUNCTIONS
endif
endif
endif

ifndef STRSAFE_LIB_IMPL
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
endif

if defined(STRSAFE_LIB_IMPL) OR NOT defined(STRSAFE_LIB)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifdef DEPRECATE_SUPPORTED
else
StringLengthWorkerA	equ <StringLengthWorkerA_instead_use_StringCchLengthA_or_StringCbLengthA>
StringLengthWorkerW	equ <StringLengthWorkerW_instead_use_StringCchLengthW_or_StringCbLengthW>
UnalignedStringLengthWorkerW equ <UnalignedStringLengthWorkerW_instead_use_UnalignedStringCchLengthW>
StringExValidateSrcA	equ <StringExValidateSrcA_do_not_call_this_function>
StringExValidateSrcW	equ <StringExValidateSrcW_do_not_call_this_function>
StringValidateDestA	equ <StringValidateDestA_do_not_call_this_function>
StringValidateDestAndLengthA equ <StringValidateDestAndLengthA_do_not_call_this_function>
StringValidateDestW	equ <StringValidateDestW_do_not_call_this_function>
StringValidateDestAndLengthW equ <StringValidateDestAndLengthW_do_not_call_this_function>
StringExValidateDestA	equ <StringExValidateDestA_do_not_call_this_function>
StringExValidateDestAndLengthA equ <StringExValidateDestAndLengthA_do_not_call_this_function>
StringExValidateDestW	equ <StringExValidateDestW_do_not_call_this_function>
StringExValidateDestAndLengthW equ <StringExValidateDestAndLengthW_do_not_call_this_function>
StringCopyWorkerA	equ <StringCopyWorkerA_instead_use_StringCchCopyA_or_StringCbCopyA>
StringCopyWorkerW	equ <StringCopyWorkerW_instead_use_StringCchCopyW_or_StringCbCopyW>
StringVPrintfWorkerA	equ <StringVPrintfWorkerA_instead_use_StringCchVPrintfA_or_StringCbVPrintfA>
StringVPrintfWorkerW	equ <StringVPrintfWorkerW_instead_use_StringCchVPrintfW_or_StringCbVPrintfW>
StringGetsWorkerA	equ <StringGetsWorkerA_instead_use_StringCchGetsA_or_StringCbGetsA>
StringGetsWorkerW	equ <StringGetsWorkerW_instead_use_StringCchGetsW_or_StringCbGetsW>
StringExHandleFillBehindNullA equ <StringExHandleFillBehindNullA_do_not_call_this_function>
StringExHandleFillBehindNullW equ <StringExHandleFillBehindNullW_do_not_call_this_function>
StringExHandleOtherFlagsA equ <StringExHandleOtherFlagsA_do_not_call_this_function>
StringExHandleOtherFlagsW equ <StringExHandleOtherFlagsW_do_not_call_this_function>
endif

endif
endif
