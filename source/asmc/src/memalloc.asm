; MEMALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc
ifndef __UNIX__
include winbase.inc
elseifdef _WIN64
include linux/kernel.inc
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

.data
ifndef __UNIX__
ProcessHeap HANDLE 0
endif
pBase       string_t 0 ; start list of 512 kB blocks; to be moved to ModuleInfo.g
pCurr       string_t 0 ; points into current block; to be moved to ModuleInfo.g
currfree    uint_t 0   ; free memory left in current block; to be moved to ModuleInfo.g

    .code

MemInit proc

    mov pBase,0
    mov currfree,0
ifndef __UNIX__
    mov ProcessHeap,GetProcessHeap()
endif
    ret

MemInit endp

ifdef _LIN64

MemAlloc proc fastcall uses rsi rdi rbx len:uint_t

    add ecx,(_GRANULARITY*2)-1
    and ecx,-_GRANULARITY
    mov ebx,ecx

    sys_mmap(0, rbx, MMAP_PROT, MMAP_FLAGS, -1, 0)

    xor ecx,ecx
    cmp rax,MAP_FAILED
    cmove rax,rcx

    .if ( rax )

        mov [rax],rbx
        add rax,_GRANULARITY

    .else

elseifdef __UNIX__

MemAlloc proc fastcall uses edi len:uint_t

    mov edi,ecx

    .if malloc( ecx )

        mov ecx,edi
        mov edx,eax
        mov edi,eax
        xor eax,eax
        rep stosb
        mov eax,edx

    .else

else

MemAlloc proc fastcall len:uint_t

    .if ( HeapAlloc(ProcessHeap, HEAP_ZERO_MEMORY, rcx) == NULL )

endif

        mov currfree,eax
        asmerr( 1018 )
    .endif
    ret

MemAlloc endp


ifdef _LIN64

MemFree proc fastcall uses rsi rdi p:ptr

    .if ( rcx )

        lea rdi,[rcx-_GRANULARITY]
        mov rsi,[rdi]

        sys_munmap(rdi, rsi)

    .endif

else

MemFree proc fastcall p:ptr

ifdef __UNIX__
    free( ecx )
else
    HeapFree( ProcessHeap, 0, rcx )
endif

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

    mov rax,pCurr
    add ecx,_GRANULARITY-1
    and ecx,-_GRANULARITY

    .if ( ecx <= currfree )

        sub currfree,ecx
        add pCurr,rcx

    .else

        mov currfree,ecx
        mov eax,( _HEAP_GROWSIZE - _GRANULARITY )
        .if ( ecx > eax )
            mov eax,ecx
        .endif
        add eax,_GRANULARITY

        .if ( MemAlloc( eax ) == NULL )

            mov currfree,eax
            asmerr( 1018 )
        .endif

        mov rcx,pBase
        mov [rax],rcx
        mov pBase,rax

        add rax,_GRANULARITY
        mov ecx,currfree
        mov edx,ecx
        add rdx,rax
        mov pCurr,rdx

        mov edx,( _HEAP_GROWSIZE - _GRANULARITY )
        .if ( ecx > edx )
            mov edx,ecx
        .endif
        sub edx,ecx
        mov currfree,edx
    .endif
    ret

LclAlloc endp


LclDup proc fastcall uses rbx string:string_t

    mov rbx,rcx
    lea rcx,[tstrlen( rcx ) + 1]

   .return( tstrcpy( LclAlloc( ecx ), rbx ) )

LclDup endp


MemDup proc fastcall uses rbx string:string_t

    mov rbx,rcx
    lea rcx,[tstrlen( rcx ) + 1]

   .return( tstrcpy( MemAlloc( ecx ), rbx ) )

MemDup endp

ifndef _WIN64

    option stackbase:esp

alloca proc byte_count:UINT

    mov     ecx,[esp]   ; return address
    mov     eax,[esp+4] ; size to probe
    add     esp,8
@@:
    cmp     eax,_PAGESIZE_
    jb      @F
    sub     esp,_PAGESIZE_
    or      dword ptr [esp],0
    sub     eax,_PAGESIZE_
    jmp     @B
@@:
    sub     esp,eax
    and     esp,-16     ; align 16
    mov     eax,esp
    sub     esp,4
    or      dword ptr [esp],0
    jmp     ecx

alloca endp

endif

    end

