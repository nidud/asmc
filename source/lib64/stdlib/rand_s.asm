; RAND_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include cruntime.inc
include mtdll.inc
include stddef.inc
include stdlib.inc
include internal.inc
include ntsecapi.inc
include libloaderapi.inc
include intrin.inc

__TO_STR macro x
    exitm<"&x&">
    endm
_TO_STR macro x
    exitm<__TO_STR(x)>
    endm

CALLBACK(PGENRANDOM, :PVOID, :ULONG)

    .data
    g_pfnRtlGenRandom PGENRANDOM 0

    .code

_initp_misc_rand_s proc enull:ptr

    mov g_pfnRtlGenRandom,rcx
    ret

_initp_misc_rand_s endp

rand_s proc _RandomValue:ptr UINT

  local pfnRtlGenRandom:PGENRANDOM
  local encoded:PGENRANDOM
  local enull:ptr_t
  local hRandDll:HMODULE

    ;_VALIDATE_RETURN_ERRCODE( _RandomValue != NULL, EINVAL );

    mov pfnRtlGenRandom,DecodePointer(g_pfnRtlGenRandom)
    xor edx,edx
    mov rcx,_RandomValue ; // Review : better value to initialize it to?
    mov [rcx],edx

    .if ( rax == NULL ) ; pfnRtlGenRandom

ifdef _CORESYS
RAND_DLL equ <L"cryptbase.dll">
else
RAND_DLL equ <L"ADVAPI32.DLL">
endif
        ;; advapi32.dll/cryptbase.dll is unloaded when the App exits.
        mov hRandDll,LoadLibraryExW(RAND_DLL, NULL, LOAD_LIBRARY_SEARCH_SYSTEM32)
ifndef _CORESYS
        .if (!hRandDll && GetLastError() == ERROR_INVALID_PARAMETER)

            ;; LOAD_LIBRARY_SEARCH_SYSTEM32 is not supported on this platfrom,
            ;; try one more time using default options
            mov hRandDll,LoadLibraryExW(RAND_DLL, NULL, 0)
        .endif
endif
        .if (!hRandDll)

            _VALIDATE_RETURN_ERRCODE(<"rand_s is not available on this platform", 0>, EINVAL)
        .endif

        mov pfnRtlGenRandom,GetProcAddress( hRandDll, _TO_STR( RtlGenRandom ) )
        .if ( pfnRtlGenRandom == NULL )

            _VALIDATE_RETURN_ERRCODE(<"rand_s is not available on this platform", 0>, _get_errno_from_oserr(GetLastError()))
        .endif
        mov encoded,EncodePointer(pfnRtlGenRandom)
        mov enull,EncodePointer(NULL)
ifdef _M_IX86
        .if ( InterlockedExchange(&g_pfnRtlGenRandom, encoded) != enull )
else
        .if ( _InterlockedExchangePointer(&g_pfnRtlGenRandom, encoded) != enull )
endif

            ;; A different thread has already loaded advapi32.dll/cryptbase.dll.
            FreeLibrary( hRandDll )
        .endif
    .endif

    .if ( !pfnRtlGenRandom( _RandomValue, sizeof( uint_t ) ) )

        mov errno,ENOMEM
        mov eax,errno
    .endif
    xor eax,eax
    ret
rand_s endp
if 0
rand_s proc _RandomValue:ptr UINT

    rand()
    mov rcx,_RandomValue
    mov [rcx],eax
    mov eax,1
    ret

rand_s endp
endif
    end
