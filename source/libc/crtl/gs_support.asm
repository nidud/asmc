; GS_SUPPORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include awint.inc

ifdef _WIN64
define DEFAULT_SECURITY_COOKIE 0x00002B992DDFA232
else
define DEFAULT_SECURITY_COOKIE 0xBB40E64E
endif

externdef __security_cookie:UINT_PTR
externdef __security_cookie_complement:UINT_PTR

    .code

__security_init_cookie proc uses rbx

   .new cookie:UINT_PTR
   .new systime:FILETIME = {0}
   .new perfctr:LARGE_INTEGER

    mov rax,__security_cookie
    mov rdx,DEFAULT_SECURITY_COOKIE
    ;
    ; Do nothing if the global cookie has already been initialized.  On x86,
    ; reinitialize the cookie if it has been previously initialized to a
    ; value with the high word 0x0000.  Some versions of Windows will init
    ; the cookie in the loader, but using an older mechanism which forced the
    ; high word to zero.
    ;
ifdef _M_IX86
    .if ( eax != edx && eax & 0xFFFF0000 )
else
    .if ( rax != rdx )
endif
        not rax
        mov __security_cookie_complement,rax
       .return
    .endif

    ;
    ; Initialize the global cookie with an unpredictable value which is
    ; different for each module in a process.  Combine a number of sources
    ; of randomness.
    ;
    GetSystemTimeAsFileTime( &systime )

ifdef _WIN64
    mov rbx,systime
else
    mov ebx,systime.dwLowDateTime
    xor ebx,systime.dwHighDateTime
endif
    xor rbx,GetCurrentThreadId()
    xor rbx,GetCurrentProcessId()

if _CRT_NTDDI_MIN GE NTDDI_VISTA
    GetTickCount64()
ifdef _WIN64
    mov rcx,rax
    shl rcx,56
    xor rbx,rax
endif
    xor rbx,rax
endif

    QueryPerformanceCounter(&perfctr)

ifdef _WIN64
    mov eax,perfctr.LowPart
    shl rax,32
    xor rax,perfctr.QuadPart
    xor rbx,rax
else
    xor ebx,perfctr.LowPart
    xor ebx,perfctr.HighPart
endif

    ;
    ; Increase entropy using ASLR relocation
    ;
    lea rax,cookie
    xor rbx,rax

ifdef _WIN64
    ;
    ; On Win64, generate a cookie with the most significant word set to zero,
    ; as a defense against buffer overruns involving null-terminated strings.
    ; Don't do so on Win32, as it's more important to keep 32 bits of cookie.
    ;
    mov rax,0x0000FFFFFFFFFFFF
    and rbx,rax
endif

    ;
    ; Make sure the cookie is initialized to a value that will prevent us from
    ; reinitializing it if this routine is ever called twice.
    ;
    mov rdx,DEFAULT_SECURITY_COOKIE
    .if rbx == rdx
        inc rbx
ifdef _M_IX86
    .elseif ( !( ecx & 0xFFFF0000 ) )
        mov eax,ebx
        or  eax,0x4711
        shl eax,16
        or  ebx,eax
endif
    .endif

    mov __security_cookie,rbx
    not rbx
    mov __security_cookie_complement,rbx
    ret

__security_init_cookie endp

    end
