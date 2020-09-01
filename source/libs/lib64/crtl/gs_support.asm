; GS_SUPPORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include awint.inc

DEFAULT_SECURITY_COOKIE equ 0x00002B992DDFA232

externdef __security_cookie:UINT_PTR
externdef __security_cookie_complement:UINT_PTR

    .code

__security_init_cookie proc uses rbx

    local cookie:UINT_PTR
    local systime:qword
    local perfctr:LARGE_INTEGER

    mov systime,0

    mov rax,__security_cookie
    mov rdx,DEFAULT_SECURITY_COOKIE
    .if rax != rdx
        not rax
        mov __security_cookie_complement,rax
        .return
    .endif

    GetSystemTimeAsFileTime(&systime)

    mov rbx,systime

    xor rbx,GetCurrentThreadId()
    xor rbx,GetCurrentProcessId()

if _CRT_NTDDI_MIN GE NTDDI_VISTA
    shl GetTickCount64(),56
    xor rbx,rax
    xor rbx,GetTickCount64()
endif

    QueryPerformanceCounter(&perfctr)

    mov eax,perfctr.LowPart
    shl rax,32
    xor rax,perfctr.QuadPart
    xor rbx,rax
    lea rax,cookie
    xor rbx,rax
    mov rax,0x0000FFFFffffFFFF
    and rbx,rax
    mov rdx,DEFAULT_SECURITY_COOKIE
    .if rbx == rdx

        lea rbx,[rdx+1]
    .endif
    mov __security_cookie,rbx
    not rbx
    mov __security_cookie_complement,rbx
    ret

__security_init_cookie endp

    end
