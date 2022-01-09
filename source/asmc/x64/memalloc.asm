; MEMALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc
ifndef __UNIX__
include winbase.inc
endif
include asmc.inc
;
; what items are stored in the heap?
; - symbols + symbol names ( asym, dsym; symbol.c )
; - macro lines ( StoreMacro(); macro.c )
; - file names ( CurrFName[]; assemble.c )
; - temp items + buffers ( omf.c, bin.c, coff.c, elf.c )
; - contexts ( reused; context.c )
; - codeview debug info ( dbgcv.c )
; - library names ( includelib; directiv.c )
; - src lines for FASTPASS ( fastpass.c )
; - fixups ( fixup.c )
; - hll items (reused; .IF, .WHILE, .REPEAT; hll.c )
; - one big input buffer ( src line buffer, tokenarray, string buffer; input.c )
; - src filenames array ( AddFile(); input.c )
; - line number info ( -Zd, -Zi; linnum.c )
; - macro parameter array + default values ( macro.c )
; - prologue, epilogue macro names ??? ( option.c )
; - dll names ( OPTION DLLIMPORT; option.c )
; - std queue items ( see queues in struct module_vars; globals.h, queue.c )
; - renamed keyword queue ( reswords.c )
; - safeseh queue ( safeseh.c )
; - segment alias names ( segment.c )
; - segment stack ( segment.c )
; - segment buffers ( 1024 for omf, else may be HUGE ) ( segment.c )
; - segment names for simplified segment directives (simsegm.c )
; - strings of text macros ( string.c )
; - struct/union/record member items + default values ( types.c )
; - procedure prologue argument, debug info ( proc.c )
;
;
; FASTMEM is a simple memory alloc approach which allocates chunks of 512 kB
; and will release it only at MemFini().
;
; May be considered to create an additional "line heap" to store lines of
; loop macros and generated code - since this is hierarchical, a simple
; Mark/Release mechanism will do the memory management.
; currently generated code lines are stored in the C heap, while
; loop macro lines go to the "fastmem" heap.
;

ALIGNMENT   equ 16
BLKSIZE     equ 0x80000

.data
ifndef __UNIX__
hProcessHeap    HANDLE 0
endif
pBase           dq 0 ; start list of 512 kB blocks; to be moved to ModuleInfo.g
pCurr           dq 0 ; points into current block; to be moved to ModuleInfo.g
currfree        dd 0 ; free memory left in current block; to be moved to ModuleInfo.g

    .code

    option dotname

MemInit proc

    mov pBase,0
    mov currfree,0
ifndef __UNIX__
    mov hProcessHeap,GetProcessHeap()
endif
    ret

MemInit endp

ifdef __UNIX__

define PROT_READ    1
define PROT_WRITE   2
define MAP_PRIVATE  2
define MAP_ANON     0x20
define MAP_FAILED   (-1)
define SYS_MMAP     9
define SYS_MUNMAP   11

MemAlloc proc fastcall uses rsi rdi rbx len:uint_t

    add     ecx,32-1
    and     ecx,-16
    mov     ebx,ecx
    xor     edi,edi
    mov     rsi,rbx
    mov     edx,PROT_READ or PROT_WRITE
    mov     r10d,MAP_PRIVATE or MAP_ANON
    mov     r8,-1
    xor     r9d,r9d
    mov     eax,SYS_MMAP
    syscall
    xor     ecx,ecx
    cmp     rax,MAP_FAILED
    cmove   rax,rcx

    .if ( rax )

        mov [rax],rbx
        add rax,16

    .else
else
MemAlloc proc fastcall len:uint_t

    .if ( HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, rcx) == NULL )
endif
        mov currfree,eax
        asmerr( 1018 )
    .endif
    ret

MemAlloc endp

ifdef __UNIX__

MemFree proc fastcall uses rsi rdi p:ptr

    .if ( rcx )

        lea rdi,[rcx-16]
        mov rsi,[rdi]
        mov eax,SYS_MUNMAP
        syscall
    .endif

else

MemFree proc fastcall p:ptr

    HeapFree(hProcessHeap, 0, rcx)
endif
    ret

MemFree endp

MemFini proc uses rbx

    mov rbx,pBase
    .while rbx
        mov rcx,rbx
        mov rbx,[rbx]
        MemFree(rcx)
    .endw
    mov pBase,rbx
    ret

MemFini endp

LclAlloc proc fastcall size:uint_t

    mov     rax,pCurr
    add     ecx,ALIGNMENT-1
    and     ecx,-ALIGNMENT
    cmp     ecx,currfree
    ja      .1
.0:
    sub     currfree,ecx
    add     pCurr,rcx
    ret
.1:
    mov     size,ecx
    mov     eax,(BLKSIZE - ALIGNMENT)
    cmp     ecx,eax
    cmovb   ecx,eax
    mov     currfree,ecx
    add     ecx,ALIGNMENT

    MemAlloc(ecx)

    test    rax,rax
    jz      .2
    mov     rcx,pBase
    mov     [rax],rcx
    mov     pBase,rax
    add     rax,ALIGNMENT
    mov     pCurr,rax
    mov     ecx,size
    jmp     .0
.2:
    mov     currfree,eax
    asmerr( 1018 )

LclAlloc endp

LclDup proc fastcall string:string_t

    lea rcx,[tstrlen( rcx ) + 1]

   .return( tstrcpy( LclAlloc( ecx ), string ) )

LclDup endp

MemDup proc fastcall string:string_t

    lea rcx,[tstrlen( rcx ) + 1]

   .return( tstrcpy( MemAlloc( ecx ), string ) )

MemDup endp

    end

