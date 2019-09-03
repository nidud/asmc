include malloc.inc
include string.inc
include winbase.inc

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

ALIGNMENT   equ 8
BLKSIZE     equ 0x80000

.data

pBase       dd 0        ; start list of 512 kB blocks; to be moved to ModuleInfo.g
pCurr       dd 0        ; points into current block; to be moved to ModuleInfo.g
currfree    dd 0        ; free memory left in current block; to be moved to ModuleInfo.g
heaplen     dd 0x80000  ; total memory usage
hProcessHeap dd 0

.code

MemInit proc
    mov hProcessHeap,GetProcessHeap()
    mov pBase,0
    mov currfree,0
    ret
MemInit endp

MemFini proc uses ebx
    mov ebx,pBase
    .while ebx
        mov eax,ebx
        mov ebx,[ebx]
        HeapFree(hProcessHeap, 0, eax)
    .endw
    mov pBase,ebx
    ret
MemFini endp

.pragma warning(disable: 6004)

LclAlloc proc fastcall size

    mov eax,pCurr
    add ecx,ALIGNMENT-1
    and ecx,-ALIGNMENT
    .if ecx > currfree
        push edx
        push ecx
        .if ecx <= (BLKSIZE - ALIGNMENT)
            mov ecx,(BLKSIZE - ALIGNMENT)
        .endif
        mov currfree,ecx
        add ecx,ALIGNMENT
        .if HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, ecx)
            mov ecx,pBase
            mov [eax],ecx
            mov pBase,eax
            add eax,ALIGNMENT
            mov pCurr,eax
        .endif
        pop ecx
        pop edx
    .endif
    sub currfree,ecx
    add pCurr,ecx
    ret

LclAlloc endp

MemAlloc proc fastcall len

    .if !malloc(ecx)
        mov currfree,eax
        asmerr(1901)
    .endif
    ret

MemAlloc endp

    end

