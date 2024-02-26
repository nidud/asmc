ifndef _STRSAFE_H_INCLUDED_
define _STRSAFE_H_INCLUDED_

include stdio.inc
include string.inc
include stdarg.inc
include specstrings.inc
include winapifamily.inc

if not defined(STRSAFE_LIB) and not defined(__PE__)
define STRSAFE_LIB
endif

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

ifdef STRSAFE_LIB

StringLengthWorkerA proto __cdecl \
                   psz: LPSTR,
                cchMax: size_t,
            pcchLength: ptr size_t

StringLengthWorkerW proto __cdecl \
                   psz: LPWSTR,
                cchMax: size_t,
            pcchLength: ptr size_t

ifdef ALIGNMENT_MACHINE
UnalignedStringLengthWorkerW proto __cdecl \
                   psz: LPWSTR,
                cchMax: size_t,
            pcchLength: ptr size_t
endif

StringExValidateSrcA proto __cdecl \
               ppszSrc: ptr LPSTR,
            pcchToRead: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateSrcW proto __cdecl \
               ppszSrc: ptr LPWSTR,
            pcchToRead: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringValidateDestA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
                cchMax: size_t

StringValidateDestAndLengthA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t

StringValidateDestW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
                cchMax: size_t

StringValidateDestAndLengthW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t

StringExValidateDestA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateDestAndLengthA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateDestW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringExValidateDestAndLengthW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
        pcchDestLength: ptr size_t,
                cchMax: size_t,
               dwFlags: DWORD

StringCopyWorkerA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
                pszSrc: LPSTR,
             cchToCopy: size_t

StringCopyWorkerW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
                pszSrc: LPWSTR,
             cchToCopy: size_t

StringVPrintfWorkerA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
             pszFormat: LPSTR,
               argList: va_list

ifdef STRSAFE_LOCALE_FUNCTIONS
StringVPrintf_lWorkerA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
     pcchNewDestLength: size_t,
             pszFormat: LPSTR,
                locale: _locale_t,
               argList: va_list
endif

StringVPrintfWorkerW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
             pszFormat: LPWSTR,
               argList: va_list

ifdef STRSAFE_LOCALE_FUNCTIONS
StringVPrintf_lWorkerW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t,
             pszFormat: LPWSTR,
                locale: _locale_t,
               argList: va_list
endif

ifndef STRSAFE_LIB_IMPL
StringGetsWorkerA proto __cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t

StringGetsWorkerW proto __cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
     pcchNewDestLength: ptr size_t
endif

StringExHandleFillBehindNullA proto __cdecl \
            pszDestEnd: LPSTR,
           cbRemaining: size_t,
               dwFlags: DWORD

StringExHandleFillBehindNullW proto __cdecl \
            pszDestEnd: LPWSTR,
           cbRemaining: size_t,
               dwFlags: DWORD

StringExHandleOtherFlagsA proto __cdecl \
               pszDest: LPSTR,
                cbDest: size_t,
 cchOriginalDestLength: size_t,
           ppszDestEnd: ptr LPSTR,
         pcchRemaining: ptr size_t,
               dwFlags: DWORD

StringExHandleOtherFlagsW proto __cdecl \
               pszDest: LPWSTR,
                cbDest: size_t,
 cchOriginalDestLength: size_t,
           ppszDestEnd: ptr LPWSTR,
         pcchRemaining: ptr size_t,
               dwFlags: DWORD

StringCchPrintfA proto __Cdecl \
               pszDest: LPSTR,
               cchDest: size_t,
             pszFormat: LPSTR,
                argptr: vararg

StringCchPrintfW proto __Cdecl \
               pszDest: LPWSTR,
               cchDest: size_t,
             pszFormat: LPWSTR,
                argptr: vararg

ifndef _M_CEE_PURE
StringCchPrintfExA proto __Cdecl :LPSTR, :size_t, :ptr LPSTR, :ptr size_t, :DWORD, :LPSTR, :vararg
StringCchPrintfExW proto __Cdecl :LPWSTR, :size_t, :ptr LPWSTR, :ptr size_t, :DWORD, :LPWSTR, :vararg
endif
StringCchVPrintfA proto __cdecl :LPSTR, :size_t, :LPSTR, :ptr
StringCchVPrintfW proto __cdecl :LPWSTR, :size_t, :LPWSTR, :ptr
StringCchLengthA proto __cdecl :LPSTR, :size_t, :ptr size_t
StringCchLengthW proto __cdecl :LPWSTR, :size_t, :ptr size_t
StringCchGetsA proto __cdecl :LPSTR, :size_t
StringCchGetsW proto __cdecl :LPWSTR, :size_t

endif ; !STRSAFE_LIB

ifndef ALIGNMENT_MACHINE
define UnalignedStringCchLengthW    <StringCchLengthW>
endif

ifdef _UNICODE
define StringValidateDest           <StringValidateDestW>
define StringValidateDestAndLength  <StringValidateDestAndLengthW>
define StringExValidateSrc          <StringExValidateSrcW>
define StringExValidateDest         <StringExValidateDestW>
define StringCopyWorker             <StringCopyWorkerW>
define StringLengthWorker           <StringLengthWorkerW>
define StringGetsWorker             <StringGetsWorkerW>
define StringVPrintfWorker          <StringVPrintfWorkerW>
define StringExHandleFillBehindNull <StringExHandleFillBehindNullW>
define StringExHandleOtherFlags     <StringExHandleOtherFlagsW>
define StringCchPrintf              <StringCchPrintfW>
define StringCchCopy                <StringCchCopyW>
define StringCchCopyEx              <StringCchCopyExW>
define StringCchCopyN               <StringCchCopyNW>
define StringCchCopyNEx             <StringCchCopyNExW>
define StringCchCat                 <StringCchCatW>
define StringCchCatEx               <StringCchCatExW>
define StringCchCatN                <StringCchCatNW>
define StringCchCatNEx              <StringCchCatNExW>
define StringCchVPrintf             <StringCchVPrintfW>
define StringCchVPrintf_l           <StringCchVPrintf_lW>
define StringCchPrintf_l            <StringCchPrintf_lW>
define StringCchPrintfEx            <StringCchPrintfExW>
define StringCchPrintf_lEx          <StringCchPrintf_lExW>
define StringCchVPrintfEx           <StringCchVPrintfExW>
define StringCchVPrintf_lEx         <StringCchVPrintf_lExW>
define StringCchGets                <StringCchGetsW>
define StringCchGetsEx              <StringCchGetsExW>
define StringCchLength              <StringCchLengthW>
define UnalignedStringCchLength     <UnalignedStringCchLengthW>
else
define StringValidateDest           <StringValidateDestA>
define StringValidateDestAndLength  <StringValidateDestAndLengthA>
define StringExValidateSrc          <StringExValidateSrcA>
define StringExValidateDest         <StringExValidateDestA>
define StringCopyWorker             <StringCopyWorkerA>
define StringLengthWorker           <StringLengthWorkerA>
define StringGetsWorker             <StringGetsWorkerA>
define StringVPrintfWorker          <StringVPrintfWorkerA>
define StringExHandleFillBehindNull <StringExHandleFillBehindNullA>
define StringExHandleOtherFlags     <StringExHandleOtherFlagsA>
define StringCchPrintf              <StringCchPrintfA>
define StringCchCopy                <StringCchCopyA>
define StringCchCopyEx              <StringCchCopyExA>
define StringCchCopyN               <StringCchCopyNA>
define StringCchCopyNEx             <StringCchCopyNExA>
define StringCchCat                 <StringCchCatA>
define StringCchCatEx               <StringCchCatExA>
define StringCchCatN                <StringCchCatNA>
define StringCchCatNEx              <StringCchCatNExA>
define StringCchVPrintf             <StringCchVPrintfA>
define StringCchVPrintf_l           <StringCchVPrintf_lA>
define StringCchPrintf_l            <StringCchPrintf_lA>
define StringCchPrintfEx            <StringCchPrintfExA>
define StringCchPrintf_lEx          <StringCchPrintf_lExA>
define StringCchVPrintfEx           <StringCchVPrintfExA>
define StringCchVPrintf_lEx         <StringCchVPrintf_lExA>
define StringCchGets                <StringCchGetsA>
define StringCchGetsEx              <StringCchGetsExA>
define StringCchLength              <StringCchLengthA>
define UnalignedStringCchLength     <StringCchLengthA>
endif

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

endif ; _STRSAFE_H_INCLUDED_
