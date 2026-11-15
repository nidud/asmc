; VIRTUALALLOC.S--
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

 VirtualAlloc proc WINAPI uses rsi rdi rbx lpAddress:LPVOID, dwSize:SIZE_T,
        flAllocationType:DWORD, flProtect:DWORD
   .new prot:int_t
   .new total_size:SIZE_T
    ldr rbx,lpAddress
    ldr rsi,dwSize
    .if ( !rsi )
        .return( NULL )
    .endif
    mov prot,__WinProtToLinux(ldr(flProtect))
    add rsi,PAGE_SIZE - 1
    and rsi,-PAGE_SIZE
    .if ( rbx )
        and rbx,-PAGE_SIZE
        .ifsd ( mprotect(rbx, rsi, prot) < 0 )
            .return( NULL )
        .endif
        .return( rbx )
    .endif
    add rsi,PAGE_SIZE
    mov total_size,rsi
    .if ( mmap(NULL, rsi, PROT_READ or PROT_WRITE, MAP_PRIVATE or MAP_ANONYMOUS, -1, 0) == MAP_FAILED )
        .return( NULL )
    .endif
    mov rbx,rax
    mov [rbx],total_size ; Store total mapped size in metadata page
    add rbx,PAGE_SIZE    ; User pointer starts on next 4096-byte page boundary
    .if ( prot != (PROT_READ or PROT_WRITE) )
        mov rsi,total_size
        sub rsi,PAGE_SIZE
        .ifsd ( mprotect(rbx, rsi, prot) < 0 )
            sub rbx,PAGE_SIZE
            munmap(rbx, total_size)
           .return( NULL )
        .endif
    .endif
    .return( rbx )
    endp

    end
