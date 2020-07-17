; _RESETSTK.ASM - Recover from Stack overflow.
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include malloc.inc
include windows.inc
include internal.inc
include awint.inc

MIN_STACK_REQ_WINNT equ 2

    .code

_resetstkoflw proc uses rsi rdi rbx

  local MemoryInfo       : MEMORY_BASIC_INFORMATION,
        SystemInfo       : SYSTEM_INFO,
        flOldProtect     : DWORD,
        StackSizeInBytes : ULONG

    mov rsi,rsp

    .return .if !VirtualQuery( rsi, &MemoryInfo, sizeof( MemoryInfo ) )

    GetSystemInfo( &SystemInfo )

    mov ebx,SystemInfo.dwPageSize
    xor edi,edi
    mov StackSizeInBytes,edi

    .if __crtSetThreadStackGuarantee( &StackSizeInBytes )

        .if StackSizeInBytes > 0

            mov edi,StackSizeInBytes
        .endif
    .endif

    lea     rcx,[rbx-1]
    add     rdi,rcx
    not     rcx
    and     rdi,rcx

    mov     eax,0
    cmovnz  rax,rbx
    add     rdi,rax

    imul    rax,rbx,MIN_STACK_REQ_WINNT
    cmp     rdi,rax
    cmovb   rdi,rax

    and rsi,rcx
    sub rsi,rdi

    xor eax,eax
    mov rcx,MemoryInfo.AllocationBase
    add rbx,rcx
    .return .if rsi < rbx ; (pMaxGuard < pMinGuard)
    .return .ifd !VirtualAlloc  ( rsi, edi, MEM_COMMIT, PAGE_READWRITE )
    .return .ifd !VirtualProtect( rsi, edi, PAGE_READWRITE or PAGE_GUARD, &flOldProtect )
    .return 1

_resetstkoflw endp

    end
