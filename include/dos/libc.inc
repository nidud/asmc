ifndef __LIBC_INC
define __LIBC_INC
;
; Master include file for the Asmc DOS Run Time library.
;
define __STDC__
define __LIBC__ 233

ifdef __ASMC__
if ( __ASMC__ LT __LIBC__ )
.err <incorrect version. Use the header that matches with the Asmc Assembler.>
endif
endif

if not defined(__TINY__)    and \
   not defined(__SMALL__)   and \
   not defined(__MEDIUM__)  and \
   not defined(__COMPACT__) and \
   not defined(__LARGE__)   and \
   not defined(__HUGE__)
.err <you must supply a memory model ( -m[tsmclh] )>
endif

    option casemap:none, proc:public, dotname

define __cdecl <c>
define __ctype <pascal>

size_t          typedef word
char_t          typedef sbyte
short_t         typedef sword
int_t           typedef sword
long_t          typedef sdword
uchar_t         typedef byte
ushort_t        typedef word
uint_t          typedef word
ulong_t         typedef dword

ifndef _WCHAR_T_DEFINED
define _WCHAR_T_DEFINED
wchar_t         typedef word
endif

ifndef _WCTYPE_T_DEFINED
define _WCTYPE_T_DEFINED
wint_t          typedef wchar_t
wctype_t        typedef wchar_t
endif

ifndef _TCHAR_DEFINED
define _TCHAR_DEFINED
ifdef _UNICODE
TCHAR           typedef wchar_t
PTCHAR          typedef ptr wchar_t
PTBYTE          typedef ptr wchar_t
LPTSTR          typedef ptr wchar_t
else
TCHAR           typedef char_t
PTCHAR          typedef ptr char_t
LPTSTR          typedef ptr char_t
PTBYTE          typedef ptr uchar_t
endif
endif

string_t        typedef ptr char_t
ustring_t       typedef ptr uchar_t
wstring_t       typedef ptr wchar_t

array_t         typedef ptr string_t
warray_t        typedef ptr wstring_t

int8_t          typedef sbyte
int16_t         typedef sword
int32_t         typedef sdword
int64_t         typedef sqword
int128_t        typedef oword

uint8_t         typedef byte
uint16_t        typedef word
uint32_t        typedef dword
uint64_t        typedef qword
uint128_t       typedef oword

SINT            typedef sword
UINT            typedef word
ULONG           typedef dword
PVOID           typedef ptr
HANDLE          typedef ptr
LPSTR           typedef ptr sbyte
LPWSTR          typedef ptr word
LPBYTE          typedef ptr byte
LPWORD          typedef ptr word
LPDWORD         typedef ptr dword
LPQWORD         typedef ptr qword

bool            typedef sword

define true     1
define false    0
define null     0

ifndef _CALLBACK_DEFINED
define _CALLBACK_DEFINED
CALLBACKC macro id, arguments:VARARG
    ?&id& typedef proto __cdecl &arguments
    exitm <id typedef ptr ?&id&>
    endm
CALLBACK macro id, arguments:VARARG
    ?&id& typedef proto __ctype &arguments
    exitm <id typedef ptr ?&id&>
    endm
endif

if ( sizeof(PVOID) eq 4 )
define pushl    <push>
define popl     <pop>
define movl     <mov>
define ldsl     <lds>
define lesl     <les>
define esl      <es:>
else
pushl  macro args:vararg
endm
popl   macro args:vararg
endm
movl   macro args:vararg
endm
define ldsl     <mov>
define lesl     <mov>
define esl      <>
endif

endif
