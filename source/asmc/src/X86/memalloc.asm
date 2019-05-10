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

BLKSIZE		equ 80000h
ALIGNMENT	equ 8

MMALLOC MACRO z
ifdef _LINUX
	malloc(z)
else
	HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, z)
endif
	ENDM

MFREE	MACRO p
ifdef _LINUX
	free(p)
else
	HeapFree(hProcessHeap, 0, p)
endif
	ENDM

	.data

pBase		dd 0		; start list of 512 kB blocks; to be moved to ModuleInfo.g
pCurr		dd 0		; points into current block; to be moved to ModuleInfo.g
currfree	dd 0		; free memory left in current block; to be moved to ModuleInfo.g
heaplen		dd 80000h	; total memory usage
ifndef _LINUX
hProcessHeap	dd 0
endif
	.code

MemInit proc
ifndef _LINUX
	GetProcessHeap()
	mov hProcessHeap,eax
endif
	xor eax,eax
	mov pBase,eax
	mov currfree,eax
	ret
MemInit endp

MemFini proc
	push ebx
	mov ebx,pBase
	.while ebx
		mov eax,ebx
		mov ebx,[ebx]
		MFREE( eax )
	.endw
	mov pBase,ebx
	pop ebx
	ret
MemFini endp

.pragma warning(disable: 6004)

LclAlloc proc fastcall len
	mov eax,pCurr
	add ecx,ALIGNMENT-1
	and ecx,-ALIGNMENT
	cmp ecx,currfree
	ja  alloc
done:
	sub currfree,ecx
	add pCurr,ecx
	ret
alloc:
	push edx
	push ecx
	cmp ecx,BLKSIZE-ALIGNMENT
	ja  @F
	mov ecx,BLKSIZE-ALIGNMENT
@@:
	mov currfree,ecx
	add ecx,ALIGNMENT
	MMALLOC(ecx)
	test eax,eax
	jz  mem_error
ifdef _LINUX
	mov ecx,currfree
	add ecx,ALIGNMENT
	memset(eax, 0, ecx)
endif
	mov ecx,pBase
	mov [eax],ecx
	mov pBase,eax
	add eax,ALIGNMENT
	mov pCurr,eax
	pop ecx
	pop edx
	jmp done
LclAlloc endp

MemAlloc proc fastcall len
	malloc( len )
	test eax,eax
	jz mem_error
	ret
MemAlloc endp

mem_error:
	mov currfree,eax
	asmerr( 1901 )
	ret

	END

