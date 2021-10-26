ifndef _STRSAFE_H_INCLUDED_
define _STRSAFE_H_INCLUDED_

include stdio.inc
include string.inc
include stdarg.inc
include specstrings.inc
include winapifamily.inc

define ALIGNMENT_MACHINE 1

ifndef _HRESULT_DEFINED
define _HRESULT_DEFINED
HRESULT typedef int32_t
endif

SUCCEEDED proto watcall hr:HRESULT {
    retm<(sdword ptr eax !>= 0)>
    }
FAILED proto watcall hr:HRESULT {
    retm<(sdword ptr eax !< 0)>
    }

define S_OK 0

ifndef STRSAFE_USE_SECURE_CRT
if defined(__GOT_SECURE_LIB__) AND (__GOT_SECURE_LIB__ GE 200402)
define STRSAFE_USE_SECURE_CRT 0
else
define STRSAFE_USE_SECURE_CRT 0
endif
endif

ifdef STRSAFE_LIB
includelib strsafe.lib
endif

if defined(STRSAFE_NO_CB_FUNCTIONS) AND defined(STRSAFE_NO_CCH_FUNCTIONS)
.err<cannot specify both STRSAFE_NO_CB_FUNCTIONS and STRSAFE_NO_CCH_FUNCTIONS>
endif

ifndef STRSAFE_MAX_CCH
define STRSAFE_MAX_CCH 2147483647
endif

C_ASSERT macro exp
    if (exp)
        exitm<>
    else
        .err<exp>
    endif
    endm

C_ASSERT(STRSAFE_MAX_CCH LE 2147483647)
C_ASSERT(STRSAFE_MAX_CCH GT 1)

define STRSAFE_MAX_LENGTH       (STRSAFE_MAX_CCH - 1)

define STRSAFE_IGNORE_NULLS     0x00000100
define STRSAFE_FILL_BEHIND_NULL 0x00000200
define STRSAFE_FILL_ON_FAILURE  0x00000400
define STRSAFE_NULL_ON_FAILURE  0x00000800
define STRSAFE_NO_TRUNCATION    0x00001000

define STRSAFE_VALID_FLAGS (0x000000FF OR STRSAFE_IGNORE_NULLS OR STRSAFE_FILL_BEHIND_NULL OR STRSAFE_FILL_ON_FAILURE OR STRSAFE_NULL_ON_FAILURE OR STRSAFE_NO_TRUNCATION)

STRSAFE_FILL_BYTE macro x
        exitm<(((x AND 0x000000FF) OR STRSAFE_FILL_BEHIND_NULL))>
        endm
STRSAFE_FAILURE_BYTE macro x
        exitm<(((x AND 0x000000FF) OR STRSAFE_FILL_ON_FAILURE))>
        endm

STRSAFE_GET_FILL_PATTERN macro dwFlags
        exitm<(dwFlags AND 0x000000FF)>
        endm


define STRSAFE_E_INSUFFICIENT_BUFFER    0x8007007A
define STRSAFE_E_INVALID_PARAMETER      0x80070057
define STRSAFE_E_END_OF_FILE            0x80070026

STRSAFE_LPSTR           typedef ptr sbyte
STRSAFE_LPCSTR          typedef ptr sbyte
STRSAFE_LPWSTR          typedef ptr wchar_t
STRSAFE_LPCWSTR         typedef ptr wchar_t
STRSAFE_LPCUWSTR        typedef ptr wchar_t

STRSAFE_PCNZCH          typedef ptr sbyte
STRSAFE_PCNZWCH         typedef ptr wchar_t
STRSAFE_PCUNZWCH        typedef ptr wchar_t

ifdef STRSAFE_LIB

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

StringExHandleOtherFlagsA proto \
               pszDest: STRSAFE_LPSTR,
                cbDest: size_t,
 cchOriginalDestLength: size_t,
           ppszDestEnd: ptr STRSAFE_LPSTR,
         pcchRemaining: ptr size_t,
               dwFlags: DWORD

StringExHandleOtherFlagsW proto \
               pszDest: STRSAFE_LPWSTR,
                cbDest: size_t,
 cchOriginalDestLength: size_t,
           ppszDestEnd: ptr STRSAFE_LPWSTR,
         pcchRemaining: ptr size_t,
               dwFlags: DWORD

endif ; !STRSAFE_LIB

define __WARNING_CYCLOMATIC_COMPLEXITY 28734
define __WARNING_USING_UNINIT_VAR 6001
define __WARNING_RETURN_UNINIT_VAR 6101
define __WARNING_DEREF_NULL_PTR 6011
define __WARNING_MISSING_ZERO_TERMINATION2 6054
define __WARNING_INVALID_PARAM_VALUE_1 6387
define __WARNING_INCORRECT_ANNOTATION 26007
define __WARNING_POTENTIAL_BUFFER_OVERFLOW_HIGH_PRIORITY 26015
define __WARNING_PRECONDITION_NULLTERMINATION_VIOLATION 26035
define __WARNING_POSTCONDITION_NULLTERMINATION_VIOLATION 26036
define __WARNING_HIGH_PRIORITY_OVERFLOW_POSTCONDITION 26045
define __WARNING_RANGE_POSTCONDITION_VIOLATION 26061
define __WARNING_POTENTIAL_RANGE_POSTCONDITION_VIOLATION 26071
define __WARNING_INVALID_PARAM_VALUE_3 28183
define __WARNING_RETURNING_BAD_RESULT 28196
define __WARNING_BANNED_API_USAGE 28719
define __WARNING_POST_EXPECTED 28210

ifndef STRSAFE_LIB

define StringValidateDestA <StringValidateDest>
define StringValidateDestW <StringValidateDest>

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCopy equ <StringCchCopyW>
else
StringCchCopy equ <StringCchCopyA>
endif
StringCchCopyA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR {
    .if (SUCCEEDED(StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringCopyWorkerA(pszDest, cchDest, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .elseif ( cchDest )
        mov byte ptr [pszDest],0
    .endif
    }
StringCchCopyW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR {
    .if (SUCCEEDED(StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringCopyWorkerW(pszDest, cchDest, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .elseif ( cchDest )
        mov word ptr [pszDest],0
    .endif
    }
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCopy equ <StringCbCopyW>
else
StringCbCopy equ <StringCbCopyA>
endif
StringCbCopyA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR {
    .if (SUCCEEDED(StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringCopyWorkerA(pszDest, cchDest, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .elseif ( cchDest )
        mov byte ptr [pszDest],0
    .endif
    }
StringCbCopyW proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR {
    shr cchDest,1
    .if (SUCCEEDED(StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringCopyWorkerW(pszDest, cchDest, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .elseif ( cchDest )
        mov byte ptr [pszDest],0
    .endif
    }
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
StringCchCopyNA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZCH, cchToCopy:size_t {
    .if (SUCCEEDED(StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)))
        .if (cchToCopy > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
            mov byte ptr [pszDest],0
        .else
            StringCopyWorkerA(pszDest, cchDest, NULL, pszSrc, cchToCopy)
        .endif
    .elseif cchDest
        mov byte ptr [pszDest],0
    .endif
    }
StringCchCopyNW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZWCH, cchToCopy:size_t {
    .if (SUCCEEDED(StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)))
        .if (cchToCopy > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
            mov word ptr [pszDest],0
        .else
            StringCopyWorkerW(pszDest, cchDest, NULL, pszSrc, cchToCopy)
        .endif
    .elseif cchDest
        mov word ptr [pszDest],0
    .endif
    }
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCopyN equ <StringCbCopyNW>
else
StringCbCopyN equ <StringCbCopyNA>
endif
StringCbCopyNA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZCH, cchToCopy:size_t {
    .if (SUCCEEDED(StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)))
        .if (cchToCopy > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
            mov byte ptr [pszDest],0
        .else
            StringCopyWorkerA(pszDest, cchDest, NULL, pszSrc, cchToCopy)
        .endif
    .endif
    }
StringCbCopyNW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZWCH, cchToCopy:size_t {
    shr cchDest,1
    .if (SUCCEEDED(StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)))
        shr cchToCopy,1
        .if (cchToCopy > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
            mov word ptr [pszDest],0
        .else
            StringCopyWorkerW(pszDest, cchDest, NULL, pszSrc, cchToCopy)
        .endif
    .endif
    }
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

ifndef STRSAFE_NO_CCH_FUNCTIONS
ifdef _UNICODE
StringCchCat equ <StringCchCatW>
else
StringCchCat equ <StringCchCatA>
endif
StringCchCatA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR {
    mov r9,pszSrc
    .if (SUCCEEDED(StringValidateDestAndLengthA(pszDest, cchDest, 0, STRSAFE_MAX_CCH)))
        StringCopyWorkerA(pszDest, cchDest, NULL, r9, STRSAFE_MAX_LENGTH)
    .endif
    }
StringCchCatW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR {
    mov r9,pszSrc
    .if (SUCCEEDED(StringValidateDestAndLengthW(pszDest, cchDest, 0, STRSAFE_MAX_CCH)))
        StringCopyWorkerW(pszDest, cchDest, NULL, r9, STRSAFE_MAX_LENGTH)
    .endif
    }
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCat equ <StringCbCatW>
else
StringCbCat equ <StringCchCatA>
endif
StringCbCatW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR {
    shr cchDest,1
    StringCchCatW(pszDest, cchDest, pszSrc)
    }
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
StringCchCatNA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZCH, cchToAppend:size_t {
    .new cchDestLength:size_t
    .if (SUCCEEDED(StringValidateDestAndLengthA(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH)))
        .if (cchToAppend > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
        .else
            add pszDest,cchDestLength
            sub cchDest,cchDestLength
            StringCopyWorkerA(pszDest, cchDest, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    }
StringCchCatNW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZWCH, cchToAppend:size_t {
    .new cchDestLength:size_t
    .if (SUCCEEDED(StringValidateDestAndLengthW(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH)))
        .if (cchToAppend > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
        .else
            add pszDest,cchDestLength
            sub cchDest,cchDestLength
            StringCopyWorkerW(pszDest, cchDest, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    }
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbCatN equ <StringCbCatNW>
else
StringCbCatN equ <StringCbCatNA>
endif
StringCbCatNA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZCH, cchToAppend:size_t {
    .new cchDestLength:size_t
    .if (SUCCEEDED(StringValidateDestAndLengthA(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH)))
        .if (cchToAppend > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
        .else
            add pszDest,cchDestLength
            sub cchDest,cchDestLength
            StringCopyWorkerA(pszDest, cchDest, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    }
StringCbCatNW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_PCNZWCH, cchToAppend:size_t {
    .new cchDestLength:size_t
    shr cchDest,1
    .if (SUCCEEDED(StringValidateDestAndLengthW(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH)))
        shr cchToAppend,1
        .if (cchToAppend > STRSAFE_MAX_LENGTH)
            mov eax,STRSAFE_E_INVALID_PARAMETER
        .else
            add pszDest,cchDestLength
            sub cchDest,cchDestLength
            StringCopyWorkerW(pszDest, cchDest, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    }
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
StringCchVPrintfA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszFormat:STRSAFE_LPCSTR, argList:ptr {
    .if (SUCCEEDED(StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringVPrintfWorkerA(pszDest, cchDest, NULL, pszFormat, argList)
    .elseif ( cchDest )
        mov byte ptr [pszDest],0
    .endif
    }
StringCchVPrintfW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszFormat:STRSAFE_LPWSTR, argList:ptr {
    .if (SUCCEEDED(StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringVPrintfWorkerW(pszDest, cchDest, NULL, pszFormat, argList)
    .elseif ( cchDest )
        mov word ptr [pszDest],0
    .endif
    }
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
StringCchPrintfA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pszFormat:STRSAFE_LPCSTR, argList:vararg {
    .if (SUCCEEDED(StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringVPrintfWorkerA(pszDest, cchDest, NULL, pszFormat, &argList)
    .elseif ( cchDest )
        mov byte ptr [pszDest],0
    .endif
    }
StringCchPrintfW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszFormat:STRSAFE_LPCWSTR, argList:vararg {
    .if (SUCCEEDED(StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringVPrintfWorkerW(pszDest, cchDest, NULL, pszFormat, &argList)
    .elseif ( cchDest )
        mov byte ptr [pszDest],0
    .endif
    }
endif

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

StringCchPrintfExA proto _Cdecl :STRSAFE_LPSTR, :size_t, :ptr STRSAFE_LPSTR,
    :ptr size_t, :DWORD, :STRSAFE_LPCSTR, :vararg

StringCchPrintfExW proto _Cdecl :STRSAFE_LPWSTR, :size_t, :ptr STRSAFE_LPWSTR,
    :ptr size_t, :DWORD, :STRSAFE_LPCWSTR, :vararg

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
StringCchGetsA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t {
    .if (SUCCEEDED(StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringGetsWorkerA(pszDest, cchDest, NULL)
    .elseif ( cchDest )
        mov byte ptr [pszDest],0
    .endif
    }
StringCchGetsW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t {
    .if (SUCCEEDED(StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)))
        StringGetsWorkerW(pszDest, cchDest, NULL)
    .elseif ( cchDest )
        mov word ptr [pszDest],0
    .endif
    }
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbGets equ <StringCbGetsW>
else
StringCbGets equ <StringCchGetsA>
endif
StringCbGetsW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t {
    shr cchDest,1
    StringCchGetsW(pszDest, cchDest)
    }
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
StringCchLengthA proto fastcall psz:STRSAFE_PCNZCH, cchMax:size_t, pcchLength:ptr size_t {
    .if ((psz == NULL) || (cchMax > STRSAFE_MAX_CCH))
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorkerA(psz, cchMax, pcchLength)
    .endif
    .if (FAILED(eax) && pcchLength)
        mov size_t ptr [pcchLength],0
    .endif
    }
StringCchLengthW proto fastcall psz:STRSAFE_PCNZWCH, cchMax:size_t, pcchLength:ptr size_t {
    .if ((psz == NULL) || (cchMax > STRSAFE_MAX_CCH))
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorkerW(psz, cchMax, pcchLength)
    .endif
    .if (FAILED(eax) && pcchLength)
        mov size_t ptr [pcchLength],0
    .endif
    }
endif

ifndef STRSAFE_NO_CB_FUNCTIONS
ifdef _UNICODE
StringCbLength equ <StringCbLengthW>
else
StringCbLength equ <StringCbLengthA>
endif
StringCbLengthA proto fastcall psz:STRSAFE_PCNZCH, cchMax:size_t, pcbLength:ptr size_t {
    .new cchLength:size_t = 0
    .if ((psz == NULL) || (cchMax > STRSAFE_MAX_CCH))
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorkerA(psz, cchMax, &cchLength)
    .endif
    .if ( pcbLength )
        .if (SUCCEEDED(eax))
            mov [pcbLength],cchLength
        .else
            mov size_t ptr [pcbLength],0
        .endif
    .endif
    }
StringCbLengthW proto fastcall psz:STRSAFE_PCNZWCH, cchMax:size_t, pcbLength:ptr size_t {
    .new cchLength:size_t = 0
    shr cchMax,1
    .if ((psz == NULL) || (cchMax > STRSAFE_MAX_CCH))
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorkerW(psz, cchMax, &cchLength)
    .endif
    .if ( pcbLength )
        .if (SUCCEEDED(eax))
            mov rax,cchLength
            shl rax,1
            mov [pcbLength],rax
            mov eax,S_OK
        .else
            mov size_t ptr [pcbLength],0
        .endif
    .endif
    }
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
endif ; STRSAFE_LIB

if defined(STRSAFE_LIB_IMPL) OR NOT defined(STRSAFE_LIB)

StringLengthWorkerA proto fastcall psz:STRSAFE_PCNZCH, cchMax:size_t, pcchLength:ptr size_t {
    xor eax,eax
    mov r10,cchMax
    .while ( cchMax && ( al != [psz] ) )
        inc psz
        dec cchMax
    .endw
    .if !cchMax
        mov r10,cchMax
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    sub r10,cchMax
    .if pcchLength
        mov [pcchLength],r10
    .endif
    }

StringLengthWorkerW proto fastcall psz:STRSAFE_PCNZWCH, cchMax:size_t, pcchLength:ptr size_t {
    xor eax,eax
    mov r10,cchMax
    .while ( cchMax && ( ax != [psz] ) )
        add psz,2
        dec cchMax
    .endw
    .if !cchMax
        mov r10,cchMax
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    sub r10,cchMax
    .if pcchLength
        mov [pcchLength],r10
    .endif
    }

ifdef ALIGNMENT_MACHINE
UnalignedStringLengthWorkerW proto fastcall psz:STRSAFE_PCUNZWCH, cchMax:size_t, pcchLength:ptr size_t {
    mov eax,S_OK
    .new cchOriginalMax:size_t = cchMax
    .while (cchMax && (word ptr [psz] != 0))
        add psz,2
        dec cchMax
    .endw
    .if (cchMax == 0)
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    .if (pcchLength)
        .if (SUCCEEDED(eax))
            mov rax,cchOriginalMax
            sub rax,cchMax
            mov [pcchLength],rax
            mov eax,S_OK
        .else
            mov size_t ptr [pcchLength],0
        .endif
    .endif
    }
endif

StringExValidateSrcA proto fastcall ppszSrc:ptr STRSAFE_PCNZCH, pcchToRead:ptr size_t, cchMax:size_t, dwFlags:DWORD {
    mov eax,S_OK
    .if (pcchToRead && ([pcchToRead] >= cchMax))
        mov hr,STRSAFE_E_INVALID_PARAMETER
    .elseif ((dwFlags & STRSAFE_IGNORE_NULLS) && (STRSAFE_PCNZCH ptr [ppszSrc] == NULL))
        lea rax,@CStr("")
        mov [ppszSrc],rax
        .if (pcchToRead)
            size_t ptr [pcchToRead],0
        .endif
        mov eax,S_OK
    .endif
    }
StringExValidateSrcW proto fastcall ppszSrc:ptr STRSAFE_PCNZWCH, pcchToRead:ptr size_t, cchMax:size_t, dwFlags:DWORD {
    mov eax,S_OK
    .if (pcchToRead && ([pcchToRead] >= cchMax))
        mov hr,STRSAFE_E_INVALID_PARAMETER
    .elseif ((dwFlags & STRSAFE_IGNORE_NULLS) && (STRSAFE_PCNZWCH ptr [ppszSrc] == NULL))
        lea rax,@CStr(L"")
        mov [ppszSrc],rax
        .if (pcchToRead)
            size_t ptr [pcchToRead],0
        .endif
        mov eax,S_OK
    .endif
    }

StringValidateDest proto fastcall pszDest:STRSAFE_PCNZCH, cchDest:size_t, cchMax:abs {
    xor eax,eax
    .if rax == pszDest || cchDest > cchMax
        or eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    }

StringValidateDestAndLengthA proto fastcall pszDest:STRSAFE_LPCSTR, cchDest:size_t, pcchDestLength:ptr size_t, cchMax:abs {
    xor eax,eax
    .if rax == pszDest || cchDest > cchMax
        mov [pcchDestLength],rax
        or eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorkerA(pszDest, cchDest, pcchDestLength)
    .endif
    }
StringValidateDestAndLengthW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t, pcchDestLength:ptr size_t, cchMax:abs {
    xor eax,eax
    .if rax == pszDest || cchDest > cchMax
        mov [pcchDestLength],rax
        or eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorkerW(pszDest, cchDest, pcchDestLength)
    .endif
    }

StringCopyWorkerA proto fastcall pszDest:STRSAFE_LPSTR, cchDest:size_t, pcchNewDestLength:ptr size_t, pszSrc:STRSAFE_PCNZCH, cchToCopy:size_t {
    xor r10d,r10d
    mov r11,cchToCopy
    .while (cchDest && r11 && (byte ptr [pszSrc] != 0))
        mov al,[pszSrc]
        mov [pszDest],al
        inc pszSrc
        inc pszDest
        dec cchDest
        dec r11
        inc r10
    .endw
    mov eax,S_OK
    .if (cchDest == 0)
        dec pszDest
        dec r10
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .endif
    mov byte ptr [pszDest],0
    .if ( pcchNewDestLength )
        mov [pcchNewDestLength],r10
    .endif
    }

StringCopyWorkerW proto fastcall pszDest:STRSAFE_LPWSTR, cchDest:size_t,
        pcchNewDestLength:ptr size_t, pszSrc:STRSAFE_PCNZWCH, cchToCopy:size_t {
    xor eax,eax
    xchg rdi,pszDest
    xchg rsi,pszSrc
    xor r10d,r10d
    mov r11,cchToCopy
    .while (cchDest && r11 && ([rsi] != ax))
        movsw
        dec cchDest
        dec r11
        inc r10
    .endw
    xchg rdi,pszDest
    xchg rsi,pszSrc
    .if rax == cchDest
        sub pszDest,2
        dec r10
        or eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .endif
    mov word ptr [pszDest],0
    .if ( pcchNewDestLength )
        mov [pcchNewDestLength],r10
    .endif
    }

StringVPrintfWorkerA proto fastcall :STRSAFE_LPSTR, cchDest:size_t, :ptr size_t, pszFormat:STRSAFE_LPCSTR, argList:ptr {

   .new pszDest:STRSAFE_LPSTR = _1
   .new pcchNewDestLength:ptr size_t = _3
   .new hr:HRESULT = S_OK
   .new retval:int_t
   .new cchMax:size_t

    mov rax,cchDest
    dec rax
    mov cchMax,rax

if (STRSAFE_USE_SECURE_CRT eq 1) and not defined(STRSAFE_LIB_IMPL)
    mov retval,_vsnprintf_s(pszDest, cchDest, cchMax, pszFormat, argList)
else
    mov retval,_vsnprintf(pszDest, cchMax, pszFormat, argList)
endif
    mov rdx,pszDest
    .if ((retval < 0) || (rax > cchMax))
        mov rcx,cchMax
        mov byte ptr [rdx+rcx],0
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .elseif (rax == cchMax)
        mov rcx,cchMax
        mov byte ptr [rdx+rcx],0
        mov eax,S_OK
    .else
        mov rcx,rax
        mov eax,S_OK
    .endif
    mov rdx,pcchNewDestLength
    .if ( rdx )
        mov [rdx],rcx
    .endif
    }

StringVPrintfWorkerW proto fastcall :STRSAFE_LPWSTR, cchDest:size_t, :ptr size_t, pszFormat:STRSAFE_LPWSTR, argList:ptr {

   .new pszDest:STRSAFE_LPSTR = _1
   .new pcchNewDestLength:ptr size_t = _3
   .new hr:HRESULT = S_OK
   .new retval:int_t
   .new cchMax:size_t

    mov rax,cchDest
    dec rax
    mov cchMax,rax

if (STRSAFE_USE_SECURE_CRT eq 1) and not defined(STRSAFE_LIB_IMPL)
    mov retval,_vsnwprintf_s(pszDest, cchDest, cchMax, pszFormat, argList)
else
    mov retval,_vsnwprintf(pszDest, cchMax, pszFormat, argList)
endif
    mov rdx,pszDest
    .if ((retval < 0) || (rax > cchMax))
        mov rcx,cchMax
        mov word ptr [rdx+rcx*2],0
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .elseif (rax == cchMax)
        mov rcx,cchMax
        mov word ptr [rdx+rcx*2],0
        mov eax,S_OK
    .else
        mov rcx,rax
        mov eax,S_OK
    .endif
    mov rdx,pcchNewDestLength
    .if ( rdx )
        mov [rdx],rcx
    .endif
    }

StringGetsWorkerA proto fastcall :STRSAFE_LPSTR, :size_t, :ptr size_t {
    .new pszDest:STRSAFE_LPSTR = _1
    .new cchDest:size_t = _2
    .new pcchNewDestLength:ptr size_t = _3
    .new hr:HRESULT = S_OK
    .new cchNewDestLength:size_t = 0
    .if (_2 == 1)
        mov byte ptr [pszDest],0
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .else
        .while (cchDest > 1)
            getc(&stdin)
            .if (eax == EOF)
                .if (cchNewDestLength == 0)
                    mov hr,STRSAFE_E_END_OF_FILE
                .endif
                .break
            .endif
            .if (al == 10)
                .break
            .endif
            mov rcx,pszDest
            mov [rcx],al
            dec cchDest
            inc pszDest
            inc cchNewDestLength
        .endw
        mov rcx,pszDest
        mov byte ptr [rcx],0
    .endif
    mov rdx,pcchNewDestLength
    .if ( rdx )
        mov rax,cchNewDestLength
        mov [rdx],rax
    .endif
    mov eax,hr
    }
StringGetsWorkerW proto fastcall :STRSAFE_LPWSTR, :size_t, :ptr size_t {
    .new pszDest:STRSAFE_LPWSTR = _1
    .new cchDest:size_t = _2
    .new pcchNewDestLength:ptr size_t = _3
    .new hr:HRESULT = S_OK
    .new cchNewDestLength:size_t = 0
    .if (_2 == 1)
        mov word ptr [pszDest],0
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .else
        .while (cchDest > 1)
            getwc(&stdin)
            .if (eax == EOF)
                .if (cchNewDestLength == 0)
                    mov hr,STRSAFE_E_END_OF_FILE
                .endif
                .break
            .endif
            .if (ax == 10)
                .break
            .endif
            mov rcx,pszDest
            mov [rcx],ax
            dec cchDest
            add pszDest,2
            inc cchNewDestLength
        .endw
        mov rcx,pszDest
        mov word ptr [rcx],0
    .endif
    mov rdx,pcchNewDestLength
    .if ( rdx )
        mov rax,cchNewDestLength
        mov [rdx],rax
    .endif
    mov eax,hr
    }

endif ; defined(STRSAFE_LIB_IMPL) OR NOT defined(STRSAFE_LIB)
endif ; _STRSAFE_H_INCLUDED_
