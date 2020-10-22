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
HRESULT typedef int32_t
endif

SUCCEEDED macro hr
    exitm<(sdword ptr hr !>= 0)>
    endm
FAILED macro hr
    exitm<(sdword ptr hr !< 0)>
    endm

S_OK equ 0

ifndef STRSAFE_USE_SECURE_CRT
if defined(__GOT_SECURE_LIB__) AND (__GOT_SECURE_LIB__ GE 200402)
STRSAFE_USE_SECURE_CRT  equ 0
else
STRSAFE_USE_SECURE_CRT  equ 0
endif
endif

if defined(STRSAFE_LIB) or not defined(__PE__)
includelib strsafe.lib
endif

if defined(STRSAFE_NO_CB_FUNCTIONS) AND defined(STRSAFE_NO_CCH_FUNCTIONS)
.err<cannot specify both STRSAFE_NO_CB_FUNCTIONS and STRSAFE_NO_CCH_FUNCTIONS>
endif

ifndef STRSAFE_MAX_CCH
STRSAFE_MAX_CCH         equ 2147483647
endif

C_ASSERT macro exp:vararg
    if not (exp)
        .err<exp>
    endif
    exitm<>
    endm

C_ASSERT(STRSAFE_MAX_CCH LE 2147483647)
C_ASSERT(STRSAFE_MAX_CCH GT 1)

STRSAFE_MAX_LENGTH      equ (STRSAFE_MAX_CCH - 1)


STRSAFE_IGNORE_NULLS    equ 0x00000100
STRSAFE_FILL_BEHIND_NULL equ 0x00000200
STRSAFE_FILL_ON_FAILURE equ 0x00000400
STRSAFE_NULL_ON_FAILURE equ 0x00000800
STRSAFE_NO_TRUNCATION   equ 0x00001000

STRSAFE_VALID_FLAGS equ (0x000000FF OR STRSAFE_IGNORE_NULLS OR \
     STRSAFE_FILL_BEHIND_NULL OR STRSAFE_FILL_ON_FAILURE OR \
     STRSAFE_NULL_ON_FAILURE OR STRSAFE_NO_TRUNCATION)

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
STRSAFE_E_END_OF_FILE   equ 0x80070026

STRSAFE_LPSTR           typedef ptr sbyte
STRSAFE_LPCSTR          typedef ptr sbyte
STRSAFE_LPWSTR          typedef ptr wchar_t
STRSAFE_LPCWSTR         typedef ptr wchar_t
STRSAFE_LPCUWSTR        typedef ptr wchar_t

STRSAFE_PCNZCH          typedef ptr sbyte
STRSAFE_PCNZWCH         typedef ptr wchar_t
STRSAFE_PCUNZWCH        typedef ptr wchar_t


StringLengthWorkerA proto \
                   psz: STRSAFE_PCNZCH,
                cchMax: size_t,
            pcchLength: ptr size_t

StringLengthWorkerW proto \
                   psz: STRSAFE_PCNZWCH,
                cchMax: size_t,
            pcchLength: ptr size_t

ifdef ALIGNMENT_MACHINE
UnalignedStringLengthWorkerW proto \
                   psz: STRSAFE_PCUNZWCH,
                cchMax: size_t,
            pcchLength: ptr size_t
endif

StringExValidateSrcA proto \
               ppszSrc: ptr STRSAFE_PCNZCH,
            pcchToRead: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateSrcW proto \
               ppszSrc: ptr STRSAFE_PCNZWCH,
            pcchToRead: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringValidateDestA proto \
               pszDest: STRSAFE_PCNZCH,
               cchDest: size_t,
                cchMax: size_t

StringValidateDestAndLengthA proto \
               pszDest: STRSAFE_LPCSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t

StringValidateDestW proto \
               pszDest: STRSAFE_PCNZWCH,
               cchDest: size_t,
                cchMax: size_t

StringValidateDestAndLengthW proto \
               pszDest: STRSAFE_LPCWSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t

StringExValidateDestA proto \
               pszDest: STRSAFE_PCNZCH,
               cchDest: size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateDestAndLengthA proto \
               pszDest: STRSAFE_LPCSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateDestW proto \
               pszDest: STRSAFE_PCNZWCH,
               cchDest: size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateDestAndLengthW proto \
               pszDest: STRSAFE_LPCWSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringCopyWorkerA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
                pszSrc: STRSAFE_PCNZCH,
             cchToCopy: size_t

StringCopyWorkerW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
                pszSrc: STRSAFE_PCNZWCH,
             cchToCopy: size_t

StringVPrintfWorkerA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
             pszFormat: STRSAFE_LPCSTR,
               argList: va_list

ifdef STRSAFE_LOCALE_FUNCTIONS
StringVPrintf_lWorkerA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
     pcchNewDestLength: size_t,
             pszFormat: STRSAFE_LPCSTR,
                locale: _locale_t,
               argList: va_list
endif

StringVPrintfWorkerW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
             pszFormat: STRSAFE_LPCWSTR,
               argList: va_list

ifdef STRSAFE_LOCALE_FUNCTIONS
StringVPrintf_lWorkerW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
             pszFormat: STRSAFE_LPCWSTR,
                locale: _locale_t,
               argList: va_list
endif

ifndef STRSAFE_LIB_IMPL
StringGetsWorkerA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t

StringGetsWorkerW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t
endif

StringExHandleFillBehindNullA proto \
            pszDestEnd: STRSAFE_LPSTR,
           cbRemaining: size_t,
               dwFlags: DWORD

StringExHandleFillBehindNullW proto \
            pszDestEnd: STRSAFE_LPWSTR,
           cbRemaining: size_t,
               dwFlags: DWORD


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

StringCchCopyA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_LPCSTR

StringCchCopyW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_LPCWSTR

ifdef _UNICODE
StringCchCopy equ <StringCchCopyW>
else
StringCchCopy equ <StringCchCopyA>
endif

endif ; !STRSAFE_NO_CCH_FUNCTIONS

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCopy equ <StringCbCopyW>
else
StringCbCopy equ <StringCbCopyA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCopyEx equ <StringCchCopyExW>
else
StringCchCopyEx equ <StringCchCopyExA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCopyEx equ <StringCbCopyExW>
else
StringCbCopyEx equ <StringCbCopyExA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCopyN equ <StringCchCopyNW>
else
StringCchCopyN equ <StringCchCopyNA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCopyN equ <StringCbCopyNW>
else
StringCbCopyN equ <StringCbCopyNA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCopyNEx equ <StringCchCopyNExW>
else
StringCchCopyNEx equ <StringCchCopyNExA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCopyNEx equ <StringCbCopyNExW>
else
StringCbCopyNEx equ <StringCbCopyNExA>
endif
endif

StringCchCopyNA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_PCNZCH,
             cchToCopy: size_t

StringCchCopyNW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_PCNZWCH,
             cchToCopy: size_t

StringCchCatNA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_PCNZCH,
           cchToAppend: size_t

StringCchCatNW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_PCNZWCH,
           cchToAppend: size_t

ifndef STRSAFE_NO_CCH_FUNCTIONS
StringCchCatA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_LPCSTR

StringCchCatW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
                pszSrc: STRSAFE_LPCWSTR

ifdef _UNICODE
StringCchCat equ <StringCchCatW>
else
StringCchCat equ <StringCchCatA>
endif
endif
endif  ; !STRSAFE_NO_CCH_FUNCTIONS

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCat equ <StringCbCatW>
else
StringCbCat equ <StringCbCatA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCatEx equ <StringCchCatExW>
else
StringCchCatEx equ <StringCchCatExA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCatEx equ <StringCbCatExW>
else
StringCbCatEx equ <StringCbCatExA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCatN equ <StringCchCatNW>
else
StringCchCatN equ <StringCchCatNA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCatN equ <StringCbCatNW>
else
StringCbCatN equ <StringCbCatNA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCatNEx equ <StringCchCatNExW>
else
StringCchCatNEx equ <StringCchCatNExA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCatNEx equ <StringCbCatNExW>
else
StringCbCatNEx equ <StringCbCatNExA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchVPrintf equ <StringCchVPrintfW>
else
StringCchVPrintf equ <StringCchVPrintfA>
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
StringCchVPrintf_l equ <StringCchVPrintf_lW>
else
StringCchVPrintf_l equ <StringCchVPrintf_lA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbVPrintf equ <StringCbVPrintfW>
else
StringCbVPrintf equ <StringCbVPrintfA>
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
StringCbVPrintf_l equ <StringCbVPrintf_lW>
else
StringCbVPrintf_l equ <StringCbVPrintf_lA>
endif
endif

ifndef _M_CEE_PURE

ifndef STRSAFE_NO_CCH_FUNCTIONS

ifdef _UNICODE
StringCchPrintf equ <StringCchPrintfW>
else
StringCchPrintf equ <StringCchPrintfA>
endif

StringCchPrintfA proto \
               pszDest: STRSAFE_LPSTR,
               cchDest: size_t,
             pszFormat: STRSAFE_LPCSTR,
                      : vararg

StringCchPrintfW proto \
               pszDest: STRSAFE_LPWSTR,
               cchDest: size_t,
             pszFormat: STRSAFE_LPCWSTR,
                      : vararg

endif ; STRSAFE_NO_CCH_FUNCTIONS

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
StringCchPrintf_l equ <StringCchPrintf_lW>
else
StringCchPrintf_l equ <StringCchPrintf_lA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbPrintf equ <StringCbPrintfW>
else
StringCbPrintf equ <StringCbPrintfA>
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
StringCbPrintf_l equ <StringCbPrintf_lW>
else
StringCbPrintf_l equ <StringCbPrintf_lA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchPrintfEx equ <StringCchPrintfExW>
else
StringCchPrintfEx equ <StringCchPrintfExA>
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
StringCchPrintf_lEx equ <StringCchPrintf_lExW>
else
StringCchPrintf_lEx equ <StringCchPrintf_lExA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbPrintfEx equ <StringCbPrintfExW>
else
StringCbPrintfEx equ <StringCbPrintfExA>
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
StringCbPrintf_lEx equ <StringCbPrintf_lExW>
else
StringCbPrintf_lEx equ <StringCbPrintf_lExA>
endif
endif

endif ; _M_CEE_PURE

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchVPrintfEx equ <StringCchVPrintfExW>
else
StringCchVPrintfEx equ <StringCchVPrintfExA>
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CCH_FUNCTIONS)
ifdef _UNICODE
StringCchVPrintf_lEx equ <StringCchVPrintf_lExW>
else
StringCchVPrintf_lEx equ <StringCchVPrintf_lExA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbVPrintfEx equ <StringCbVPrintfExW>
else
StringCbVPrintfEx equ <StringCbVPrintfExA>
endif
endif

if defined(STRSAFE_LOCALE_FUNCTIONS) AND NOT defined(STRSAFE_NO_CB_FUNCTIONS)
ifdef _UNICODE
StringCbVPrintf_lEx equ <StringCbVPrintf_lExW>
else
StringCbVPrintf_lEx equ <StringCbVPrintf_lExA>
endif
endif

ifndef STRSAFE_LIB_IMPL

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchGets equ <StringCchGetsW>
else
StringCchGets equ <StringCchGetsA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbGets equ <StringCbGetsW>
else
StringCbGets equ <StringCbGetsA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchGetsEx equ <StringCchGetsExW>
else
StringCchGetsEx equ <StringCchGetsExA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbGetsEx equ <StringCbGetsExW>
else
StringCbGetsEx equ <StringCbGetsExA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchLength equ <StringCchLengthW>
else
StringCchLength equ <StringCchLengthA>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbLength equ <StringCbLengthW>
else
StringCbLength equ <StringCbLengthA>
endif
endif

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
UnalignedStringCchLength equ <UnalignedStringCchLengthW>
else
UnalignedStringCchLength equ <StringCchLengthA>
endif
ifdef ALIGNMENT_MACHINE
else
UnalignedStringCchLengthW equ <StringCchLengthW>
endif
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
UnalignedStringCbLength equ <UnalignedStringCbLengthW>
else
UnalignedStringCbLength equ <StringCbLengthA>
endif
ifdef ALIGNMENT_MACHINE
else
UnalignedStringCbLengthW equ <StringCbLengthW>
endif
endif

endif ; STRSAFE_LIB_IMPL

if defined(STRSAFE_LIB_IMPL) OR NOT defined(STRSAFE_LIB)
ifndef DEPRECATE_SUPPORTED
if 0
StringLengthWorkerA     equ <StringLengthWorkerA_instead_use_StringCchLengthA_or_StringCbLengthA>
StringLengthWorkerW     equ <StringLengthWorkerW_instead_use_StringCchLengthW_or_StringCbLengthW>
UnalignedStringLengthWorkerW equ <UnalignedStringLengthWorkerW_instead_use_UnalignedStringCchLengthW>
StringExValidateSrcA    equ <StringExValidateSrcA_do_not_call_this_function>
StringExValidateSrcW    equ <StringExValidateSrcW_do_not_call_this_function>
StringValidateDestA     equ <StringValidateDestA_do_not_call_this_function>
StringValidateDestAndLengthA equ <StringValidateDestAndLengthA_do_not_call_this_function>
StringValidateDestW     equ <StringValidateDestW_do_not_call_this_function>
StringValidateDestAndLengthW equ <StringValidateDestAndLengthW_do_not_call_this_function>
StringExValidateDestA   equ <StringExValidateDestA_do_not_call_this_function>
StringExValidateDestAndLengthA equ <StringExValidateDestAndLengthA_do_not_call_this_function>
StringExValidateDestW   equ <StringExValidateDestW_do_not_call_this_function>
StringExValidateDestAndLengthW equ <StringExValidateDestAndLengthW_do_not_call_this_function>
StringCopyWorkerA       equ <StringCopyWorkerA_instead_use_StringCchCopyA_or_StringCbCopyA>
StringCopyWorkerW       equ <StringCopyWorkerW_instead_use_StringCchCopyW_or_StringCbCopyW>
StringVPrintfWorkerA    equ <StringVPrintfWorkerA_instead_use_StringCchVPrintfA_or_StringCbVPrintfA>
StringVPrintfWorkerW    equ <StringVPrintfWorkerW_instead_use_StringCchVPrintfW_or_StringCbVPrintfW>
StringGetsWorkerA       equ <StringGetsWorkerA_instead_use_StringCchGetsA_or_StringCbGetsA>
StringGetsWorkerW       equ <StringGetsWorkerW_instead_use_StringCchGetsW_or_StringCbGetsW>
StringExHandleFillBehindNullA equ <StringExHandleFillBehindNullA_do_not_call_this_function>
StringExHandleFillBehindNullW equ <StringExHandleFillBehindNullW_do_not_call_this_function>
StringExHandleOtherFlagsA equ <StringExHandleOtherFlagsA_do_not_call_this_function>
StringExHandleOtherFlagsW equ <StringExHandleOtherFlagsW_do_not_call_this_function>
endif
endif
endif

endif ; _STRSAFE_H_INCLUDED_
