; VIRTUALPROTECT.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/mman.inc
include memoryapi.inc
include processthreadsapi.inc

define PAGE_SIZE 4096

__WinProtToLinux proto fastcall :DWORD

.code

 VirtualProtect proc WINAPI uses rsi rdi rbx lpAddress:LPVOID, dwSize:SIZE_T,
        flNewProtect:DWORD, lpflOldProtect:PDWORD
    ldr rbx,lpAddress
    ldr rsi,dwSize
    ldr rdi,lpflOldProtect
    .if ( !rbx || !rsi )
        .return( FALSE )
    .endif
    mov rax,rbx
    and rax,PAGE_SIZE-1
    and rbx,-PAGE_SIZE
    add rsi,rax
    add rsi,PAGE_SIZE-1
    and rsi,-PAGE_SIZE
    mov edx,__WinProtToLinux(ldr(flNewProtect))
    .if ( rdi )
        mov dword ptr [rdi],PAGE_READWRITE
    .endif
    .ifsd ( mprotect(rbx, rsi, edx) < 0 )
        .return( FALSE )
    .endif
    .return( TRUE )
    endp

    end
