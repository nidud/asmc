; VIRTUALFREE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/mman.inc
include memoryapi.inc

define PAGE_SIZE 4096

.code

 VirtualFree proc WINAPI uses rsi rdi rbx lpAddress:ptr, dwSize:size_t, dwFreeType:DWORD
    ldr rbx,lpAddress
    ldr rsi,dwSize
    .if ( !rbx )
        .return( FALSE )
    .endif
    .if ( ldr(dwFreeType) & MEM_RELEASE )
        sub rbx,PAGE_SIZE
        .ifsd ( munmap(rbx, [rbx]) < 0 )
            .return( FALSE )
        .endif
        .return( TRUE )
    .endif
    .if ( rsi )
        add rsi,PAGE_SIZE-1
        and rsi,-PAGE_SIZE
        mprotect(rbx, rsi, PROT_NONE)
    .endif
    .return( TRUE )
    endp

    end
