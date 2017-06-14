;
; REM
; REM MALLOC start end step [loop_count]
; REM
;
; SET CC=%AsmcDir%\bin\asmc.exe
; if not exist %CC% (
;	@echo ASMC not found: %CC%
;	exit /b 1
; )
;
; %CC% -q -pe %0
; %~n0.exe %1 %2 %3 %4
; del %~n0.exe
; exit /b %errorlevel%
;

	.x64
	.model	flat, fastcall

	.data

procs	equ <for x,<0,1,2,3,4>> ; to test

info_0	db "alloca() - macro",0
info_1	db "alloca() - proc",0
info_2	db "malloc()",0
info_3	db "HeapAlloc()",0
info_4	db "GlobalAlloc()",0
info_5	db "VirtualAlloc()",0
info_6	db "x",0
info_7	db "x",0
info_8	db "x",0
info_9	db "x",0

	ALIGN	8
p_size	dq 10 dup(0)	; proc size
result	dq 10 dup(0)	; time
total	dq 10 dup(0)	; time total
proc_p	dq 10 dup(0)	; test proc's
free_p	dq 10 dup(0)	; test proc's

info_p	dq info_0,info_1,info_2,info_3,info_4
	dq info_5,info_6,info_7,info_8,info_9
nerror	dq 0		; error count
arg_1	dq 1024		; arg 1

	.code

	option	win64:3
	option	dllimport:<msvcrt>

printf			proto :ptr byte, :vararg
exit			proto :qword
strlen			proto :ptr
atoi			proto :ptr
_getch			proto
__getmainargs		proto :ptr, :ptr, :ptr, :ptr, :ptr

	option	dllimport:<kernel32>

GetCurrentProcess	proto
SetPriorityClass	proto :ptr, :dword
Sleep			proto :ptr
HeapAlloc		proto :ptr, :dword, :ptr
HeapFree		proto :ptr, :dword, :ptr
GetProcessHeap		proto
GlobalAlloc		proto :ptr, :ptr
GlobalFree		proto :ptr
VirtualAlloc		proto :ptr, :ptr, :ptr, :ptr
VirtualFree		proto :ptr, :ptr, :ptr


	option	dllimport:NONE

PAGE_READWRITE		equ 4
MEM_COMMIT		equ 1000h
MEM_RELEASE		equ 8000h

OPEN_EXISTING		equ 3
M_RDONLY		equ 80000000h
HIGH_PRIORITY_CLASS	equ 80h
NORMAL_PRIORITY_CLASS	equ 20h
PAGE_EXECUTE_READ	equ 20h
PAGE_EXECUTE_READWRITE	equ 40h

MAXMEMORY	equ 100000h	; 1M fixed fast heap

M_BLOCK		STRUC		; Memory Block Header: 16 byte
m_size		dq ?
m_used		dq ?
m_prev		dq ?		; extended block's linked from memseg[0]
m_next		dq ?
M_BLOCK		ENDS

	.data

	memseg	dq 0		; address of main memory block
	mavail	dq 0		; address of free memory block

	.code

	OPTION PROCALIGN:16
	OPTION PROLOGUE:NONE, EPILOGUE:NONE

MEMPAGE		equ 1000h

_alloca MACRO byte_count
	mov	rax,rsp
	mov	rcx,byte_count
	.while	rcx > MEMPAGE	; probe pages
		sub	rax,MEMPAGE
		test	[rax],rax
		sub	rcx,MEMPAGE
	.endw
	sub	rax,rcx
	and	rax,-16		; align 16
	test	[rax],rax	; probe page
	mov	rsp,rax
	ENDM

alloca	PROC byte_count:qword

	lea	rax,[rsp+8]
	.while	rcx > MEMPAGE	; probe pages
		sub	rax,MEMPAGE
		test	[rax],rax
		sub	rcx,MEMPAGE
	.endw
	sub	rax,rcx
	and	rax,-16		; align 16
	test	[rax],rax	; probe page
	mov	rcx,[rsp]
	mov	rsp,rax
	jmp	rcx

alloca	ENDP

malloc	PROC byte_count:qword

	add	rcx,32+16-1	; add header size (32)
	and	rcx,-16		; align 16

	mov	rdx,mavail
	test	rdx,rdx
	jz	create_heap

	cmp	[rdx].M_BLOCK.m_used,0
	mov	rax,[rdx].M_BLOCK.m_size
	jne	find_block
	cmp	rax,rcx
	jb	find_block

block_found:

	mov	[rdx].M_BLOCK.m_used,1
	je	@F			; same size ?

	mov	[rdx].M_BLOCK.m_size,rcx
	sub	rax,rcx			; create new free block
	mov	[rdx+rcx].M_BLOCK.m_size,rax
	mov	[rdx+rcx].M_BLOCK.m_used,0
@@:

	lea	rax,[rdx+sizeof(M_BLOCK)]; return address of memory block
	add	rdx,[rdx].M_BLOCK.m_size
	mov	mavail,rdx
toend:
	ret

find_block:

	mov	rdx,memseg
	xor	rax,rax
lupe:
	add	rdx,rax
	mov	rax,[rdx].M_BLOCK.m_size
	test	rax,rax
	jz	last
	cmp	[rdx].M_BLOCK.m_used,0
	jne	lupe
	cmp	rax,rcx
	jae	block_found
	cmp	[rdx+rax].M_BLOCK.m_used,0
	jne	lupe
merge:
	add	rax,[rdx+rax].M_BLOCK.m_size
	mov	[rdx].M_BLOCK.m_size,rax
	cmp	[rdx+rax].M_BLOCK.m_used,0
	je	merge
	cmp	rax,rcx
	jb	lupe
	jmp	block_found
last:
	mov	rdx,[rdx].M_BLOCK.m_prev
	mov	rdx,[rdx].M_BLOCK.m_prev
	test	rdx,rdx
	jnz	lupe

create_heap:

	mov	rax,MAXMEMORY
	test	rax,rax
	jz	h_alloc
	cmp	rax,rcx
	jb	h_alloc
	add	rax,sizeof(M_BLOCK) * 2

	push	rcx
	push	rbx
	mov	rbx,rax
	sub	rsp,28h
	HeapAlloc( GetProcessHeap(), 0, rbx )
	add	rsp,28h
	mov	rdx,rbx
	pop	rbx
	pop	rcx

	test	rax,rax
	jz	nomem
	sub	rdx,sizeof(M_BLOCK)
	mov	[rax].M_BLOCK.m_size,rdx
	mov	[rax].M_BLOCK.m_used,0
	mov	[rax].M_BLOCK.m_next,0
	add	rdx,rax
	mov	[rdx].M_BLOCK.m_size,0
	mov	[rdx].M_BLOCK.m_used,1
	mov	[rdx].M_BLOCK.m_prev,rax
	mov	rdx,memseg
	mov	[rax].M_BLOCK.m_prev,rdx
	.if	rdx
		push	rcx
		mov	rcx,[rdx].M_BLOCK.m_next
		mov	[rdx].M_BLOCK.m_next,rax
		mov	[rax].M_BLOCK.m_next,rcx
		.if	rcx
			mov [rcx].M_BLOCK.m_prev,rax
		.endif
		pop	rcx
	.endif
	mov	mavail,rax
	mov	memseg,rax
	mov	rdx,rax
	mov	rax,[rdx].M_BLOCK.m_size
	cmp	rax,rcx
	jae	block_found
nomem:
;	mov	errno,ENOMEM
	xor	rax,rax
	jmp	toend
h_alloc:
	push	rcx
	push	rbx
	mov	rbx,rcx
	sub	rsp,20h
	HeapAlloc( GetProcessHeap(), 0, rbx )
	add	rsp,20h
	pop	rbx
	pop	rcx
	test	rax,rax
	jz	nomem
	mov	[rax].M_BLOCK.m_size,rcx
	mov	[rax].M_BLOCK.m_used,2
	mov	rcx,memseg
	mov	[rax].M_BLOCK.m_prev,rcx
	mov	[rax].M_BLOCK.m_next,rcx
	.if	rcx
		mov rdx,[rcx].M_BLOCK.m_next
		mov [rcx].M_BLOCK.m_next,rax
		mov [rax].M_BLOCK.m_next,rdx
		.if rdx
			mov [rdx].M_BLOCK.m_prev,rax
		.endif
	.endif
	add	rax,sizeof(M_BLOCK)
	jmp	toend
malloc	ENDP

free	PROC maddr:ptr
	push	rax
	mov	rax,rcx
	sub	rax,sizeof(M_BLOCK)
	js	toend
	cmp	[rax].M_BLOCK.m_used,1
	jne	h_free
	mov	[rax].M_BLOCK.m_used,0
	mov	mavail,rax
toend:
	pop	rax
	ret
h_free:
	cmp	[rax].M_BLOCK.m_used,2
	jne	toend
	push	rdx
	mov	rdx,[rax].M_BLOCK.m_prev
	mov	rcx,[rax].M_BLOCK.m_next
	.if	rdx
		mov [rdx].M_BLOCK.m_next,rcx
	.endif
	.if	rcx
		mov [rcx].M_BLOCK.m_prev,rdx
	.endif
	push	rbx
	mov	rbx,rax
	sub	rsp,20h
	HeapFree( GetProcessHeap(), 0, rbx )
	add	rsp,20h
	pop	rbx
	pop	rdx
	pop	rax
	ret
free	ENDP

	OPTION PROLOGUE:PROLOGUEDEF, EPILOGUE:EPILOGUEDEF

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.data
HEAPCOUNT	equ 100
heap		dq HEAPCOUNT dup(0)
.code

	option cstack:on

proc_0 proc uses rsi rdi z:qword
	mov	esi,HEAPCOUNT
	lea	rdi,heap
	.while	esi
		_alloca z
		stosq
		dec	esi
	.endw
	lea	rax,heap
	ret
proc_0 endp
free_0 proc p:qword
	ret
free_0 endp

proc_1 proc uses rsi rdi z:qword
	mov	esi,HEAPCOUNT
	lea	rdi,heap
	.while	esi
		alloca( z )
		stosq
		dec	esi
	.endw
	lea	rax,heap
	ret
proc_1 endp
free_1 proc p:qword
	ret
free_1 endp

proc_2 proc uses rsi rdi z:qword
	mov	esi,HEAPCOUNT
	lea	rdi,heap
	.while	esi
		malloc( z )
		stosq
		dec	esi
	.endw
	lea	rax,heap
	ret
proc_2 endp
free_2 proc uses rsi rdi p:qword
	mov	edi,HEAPCOUNT
	mov	rsi,p
	.while	edi
		lodsq
		free( rax )
		dec	edi
	.endw
	ret
free_2 endp

proc_3 proc uses rsi rdi z:qword
	mov	esi,HEAPCOUNT
	lea	rdi,heap
	.while	esi
		HeapAlloc( GetProcessHeap(), 0, z )
		stosq
		dec	esi
	.endw
	lea	rax,heap
	ret
proc_3 endp
free_3 proc uses rsi rdi rbx p:qword
	mov	edi,HEAPCOUNT
	mov	rsi,p
	.while	edi
		lodsq
		mov	rbx,rax
		HeapFree( GetProcessHeap(), 0, rbx )
		dec	edi
	.endw
	ret
free_3 endp

proc_4 proc uses rsi rdi z:qword
	mov	esi,HEAPCOUNT
	lea	rdi,heap
	.while	esi
		GlobalAlloc( 0, z )
		stosq
		dec	esi
	.endw
	lea	rax,heap
	ret
proc_4 endp
free_4 proc uses rsi rdi p:qword
	mov	edi,HEAPCOUNT
	mov	rsi,p
	.while	edi
		lodsq
		GlobalFree( rax )
		dec	edi
	.endw
	ret
free_4 endp

proc_5 proc uses rsi rdi z:qword
	mov	esi,HEAPCOUNT
	lea	rdi,heap
	.while	esi
		VirtualAlloc( 0, z, MEM_COMMIT, PAGE_READWRITE )
		stosq
		dec	esi
	.endw
	lea	rax,heap
	ret
proc_5 endp
free_5 proc uses rsi rdi p:qword
	mov	edi,HEAPCOUNT
	mov	rsi,p
	.while	edi
		lodsq
		VirtualFree( rax, 0, MEM_RELEASE )
		dec	edi
	.endw
	ret
free_5 endp

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

TestProc PROC USES rsi rdi rbx r12 r13 count:QWORD, proc_id:QWORD

	mov	rsi,rdx		; proc id 0..9

	lea	rax,proc_p
	mov	r12,[rax+rdx*8] ; proc
	lea	rax,free_p
	mov	r13,[rax+rdx*8]

	Sleep ( 0 )

	;
	; x64-Version of MichaelW's macros
	;

	SetPriorityClass( GetCurrentProcess(), HIGH_PRIORITY_CLASS )

	xor	rax,rax
	cpuid
	rdtsc
	mov	edi,eax
	xor	rax,rax
	cpuid
	mov	rcx,count
	shl	ecx,10
	.while	ecx
		sub	ecx,1
	.endw
	xor	rax,rax
	cpuid
	rdtsc
	sub	eax,edi
	mov	edi,eax
	xor	rax, rax
	cpuid
	rdtsc
	mov	esi,eax
	xor	rax,rax
	cpuid
	mov	rbx,count
	shl	rbx,10
	.while	rbx
		mov	rcx,arg_1
		call	r12
		mov	rcx,rax
		call	r13
		dec	rbx
	.endw

	xor	rax,rax
	cpuid
	rdtsc
	sub	eax,edi
	sub	eax,esi
	mov	edi,eax

	SetPriorityClass( GetCurrentProcess(), NORMAL_PRIORITY_CLASS )

	shr	edi,10
	mov	rsi,proc_id
	lea	rcx,result
	add	[rcx+rsi*8],edi
	lea	rax,info_p
	mov	rax,[rax+rsi*8]

	printf( "%9i cycles, rep(%i) %i.asm: %s\n",
		edi, count, esi, rax )

	mov	eax,1
toend:
	ret
TestProc ENDP

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

ValidateProc PROC USES rsi rdi rbx ID

	lea	rax,proc_p
	mov	rsi,[rax+rcx*8]
	lea	rax,free_p
	mov	rdi,[rax+rcx*8]
	.if	rsi
		mov	rcx,1024
		call	rsi
		mov	byte ptr [rax+1024-1],9
		mov	rbx,rax
		;printf( "%08X\n", rax )
		mov	rcx,rbx
		call	rdi
	.endif
	ret

ValidateProc ENDP

GetCycleCount proc uses rsi rdi rbx l1, l2, step, count

	mov	rbx,rcx
	mov	rdi,rdx

	.while	edi >= ebx

		mov	arg_1,rbx

		printf( "-- alloc(%i)\n", ebx )
		procs
			TestProc( count, x )
		endm
		add	ebx,step
	.endw

	lea	rsi,result
	lea	rdi,total

	.while	1
		xor	rbx,rbx
		xor	rdx,rdx
		xor	rcx,rcx
		dec	rdx
		.repeat
			mov	rax,[rsi+rcx*8]
			.if	eax && eax < edx
				mov	rdx,rax
				mov	rbx,rcx
			.endif
			inc	rcx
		.until	ecx == 10
		mov	eax,[rsi+rbx*8]
		.break .if !eax
		add	[rdi+rbx*8],eax
		xor	eax,eax
		mov	[rsi+rbx*8],eax
	.endw

	printf( "\ntotal [%i .. %i], ++%i\n", l1, l2, step )

	.while	1
		xor	r8,r8
		xor	rdx,rdx
		xor	rcx,rcx
		dec	rdx
		.repeat
			mov	eax,[rdi+rcx*8]
			.if	eax && eax < edx
				mov	rdx,rax
				mov	r8,rcx
			.endif
			inc	ecx
		.until	ecx == 10

		mov	edx,[rdi+r8*8]
		.break .if !edx
		xor	eax,eax
		mov	[rdi+r8*8],eax
		lea	rcx,info_p
		mov	r9d,[rcx+r8*8]

		printf("%9i cycles proc_%i: %s\n", edx, r8d, r9d)
	.endw

	printf( "hit any key to continue...\n" )
	_getch()

	ret

GetCycleCount endp

main	proc argc:dword, argv:qword, environ:qword

	lea	rdi,proc_p
	lea	rax,proc_0
	stosq
	lea	rax,proc_1
	stosq
	lea	rax,proc_2
	stosq
	lea	rax,proc_3
	stosq
	lea	rax,proc_4
	stosq
	lea	rax,proc_5
	stosq
	lea	rdi,free_p
	lea	rax,free_0
	stosq
	lea	rax,free_1
	stosq
	lea	rax,free_2
	stosq
	lea	rax,free_3
	stosq
	lea	rax,free_4
	stosq
	lea	rax,free_5
	stosq

	procs
		ValidateProc(x)
		cmp	nerror,0
		jne	error
	endm

	.if	argc < 4
		GetCycleCount( 1000, 3000, 1000, 100 )
	.else
		mov	rsi,argv
		mov	rcx,[rsi+8]
		atoi  ( rcx )
		mov	rbx,rax
		mov	rcx,[rsi+16]
		atoi  ( rcx )
		mov	rdi,rax
		mov	rcx,[rsi+24]
		atoi  ( rcx )
		mov	r8,rax
		mov	r9,3000

		xor	rax,rax
		.switch
		  .case ebx > edi
			printf( "error %%%i: value to large (%i)\n", ebx )
			jmp	error
		.endsw

		.if	argc > 4

			xchg	r8d,esi
			mov	rcx,[r8+32]
			atoi  ( rcx )
			mov	r9d,eax
			mov	r8d,esi
		.endif

		GetCycleCount( ebx, edi, r8d, r9d )
	.endif
	xor	eax,eax
toend:
	ret
error:
	printf( "hit any key to continue...\n" )
	_getch()
	jmp	toend
main	endp

;-------------------------------------------------------------------------------
; Startup and CPU detection
;-------------------------------------------------------------------------------

SSE_MMX		equ 0001h
SSE_SSE		equ 0002h
SSE_SSE2	equ 0004h
SSE_SSE3	equ 0008h
SSE_SSSE3	equ 0010h
SSE_SSE41	equ 0020h
SSE_SSE42	equ 0040h
SSE_XGETBV	equ 0080h
SSE_AVX		equ 0100h
SSE_AVX2	equ 0200h
SSE_AVXOS	equ 0400h

mainCRTStartup proc

	local	argc:dword,
		argv:qword,
		environ:qword,
		lpflOldProtect:qword,
		sselevel:dword,
		cpustring[80]:byte

	lea	rax,cpustring
	__getmainargs( addr argc, addr argv, addr environ, rax, rax )

	pushfq
	pop	rax
	mov	rcx,200000h
	mov	rdx,rax
	xor	rax,rcx
	push	rax
	popfq
	pushfq
	pop	rax
	xor	rax,rdx
	and	rax,rcx

	.if	!ZERO?

		xor	rax,rax
		cpuid
		.if	rax
			.if	ah == 5
				xor	rax,rax
			.else
				mov	rax,7
				xor	rcx,rcx
				cpuid			; check AVX2 support
				xor	rax,rax
				bt	ebx,5		; AVX2
				rcl	eax,1		; into bit 9
				push	rax
				mov	eax,1
				cpuid
				pop	rax
				bt	ecx,28		; AVX support by CPU
				rcl	eax,1		; into bit 8
				bt	ecx,27		; XGETBV supported
				rcl	eax,1		; into bit 7
				bt	ecx,20		; SSE4.2
				rcl	eax,1		; into bit 6
				bt	ecx,19		; SSE4.1
				rcl	eax,1		; into bit 5
				bt	ecx,9		; SSSE3
				rcl	eax,1		; into bit 4
				bt	ecx,0		; SSE3
				rcl	eax,1		; into bit 3
				bt	edx,26		; SSE2
				rcl	eax,1		; into bit 2
				bt	edx,25		; SSE
				rcl	eax,1		; into bit 1
				bt	ecx,0		; MMX
				rcl	eax,1		; into bit 0
				mov	sselevel,eax
			.endif
		.endif
	.endif

	.if	eax & SSE_XGETBV
		push	rax
		xor	rcx,rcx
		xgetbv
		and	rax,6		; AVX support by OS?
		pop	rax
		.if	!ZERO?
			or sselevel,SSE_AVXOS
		.endif
	.endif

	.if	!( eax & SSE_SSE2 )
		printf( "CPU error: Need SSE2 level\n" )
		exit( 0 )
	.endif

	lea	r8,cpustring
	xor	r9,r9
	.repeat
		lea	rax,[r9+80000002h]
		cpuid
		mov	[r8],eax
		mov	[r8+4],ebx
		mov	[r8+8],ecx
		mov	[r8+12],edx
		add	r8,16
		inc	r9
	.until	r9 == 3

	lea	rax,cpustring
	.while BYTE PTR [rax] == ' '
		inc	rax
	.endw
	printf( rax )

	printf( " (" )
	mov	eax,sselevel

	option	switch:pascal

	.switch
	  .case eax & SSE_AVX2:	 printf( "AVX2" )
	  .case eax & SSE_AVX:	 printf( "AVX" )
	  .case eax & SSE_SSE42: printf( "SSE4.2" )
	  .case eax & SSE_SSE41: printf( "SSE4.1" )
	  .case eax & SSE_SSSE3: printf( "SSSE3" )
	  .case eax & SSE_SSE3:	 printf( "SSE3" )
	  .default
		printf( "SSE2" )
	.endsw

	printf( ")\n----------------------------------------------\n" )

	exit( main( argc, argv, environ ) )

mainCRTStartup endp

	END	mainCRTStartup

-- alloc(1000)
    73653 cycles, rep(100) 0.asm: alloca() - macro
    96685 cycles, rep(100) 1.asm: alloca() - proc
   217940 cycles, rep(100) 2.asm: malloc()
  1615011 cycles, rep(100) 3.asm: HeapAlloc()
  1750094 cycles, rep(100) 4.asm: GlobalAlloc()
-- alloc(2000)
    73306 cycles, rep(100) 0.asm: alloca() - macro
    95155 cycles, rep(100) 1.asm: alloca() - proc
   367394 cycles, rep(100) 2.asm: malloc()
  1686304 cycles, rep(100) 3.asm: HeapAlloc()
  1849929 cycles, rep(100) 4.asm: GlobalAlloc()
-- alloc(3000)
    73146 cycles, rep(100) 0.asm: alloca() - macro
    95161 cycles, rep(100) 1.asm: alloca() - proc
   265251 cycles, rep(100) 2.asm: malloc()
  2446648 cycles, rep(100) 3.asm: HeapAlloc()
  2464322 cycles, rep(100) 4.asm: GlobalAlloc()

total [1000 .. 3000], ++1000
   220105 cycles proc_0: alloca() - macro
   287001 cycles proc_1: alloca() - proc
   850585 cycles proc_2: malloc()
  5747963 cycles proc_3: HeapAlloc()
  6064345 cycles proc_4: GlobalAlloc()
hit any key to continue...
