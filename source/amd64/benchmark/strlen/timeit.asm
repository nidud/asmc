; asmc -q -bin ?.asm
; asmc -q -pe %0
; %~n0.exe
; del ?.bin
; del %~n0.exe
; exit

ifndef __64__
	.x64
	.model	flat, fastcall
endif
	option	win64:2, switch:pascal

	.data

procs	equ <for x,<0,1,2,3,4>> ; to test

info_0	db "strlen(msvcrt.dll)",0
info_1	db "SSE Intel Silvermont",0
info_2	db "SSE Intel Atom",0
info_3	db "x86",0
info_4	db "x86 bsf",0
info_5	db "SSE",0
info_6	db "x",0
info_7	db "x",0
info_8	db "x",0
info_9	db "x",0

	ALIGN	8
p_size	dq 10 dup(0)	; proc size
result	dq 10 dup(0)	; time
total	dq 10 dup(0)	; time total
proc_p	dq 10 dup(0)	; test proc's
info_p	dq info_0,info_1,info_2,info_3,info_4
	dq info_5,info_6,info_7,info_8,info_9
nerror	dq 0		; error count

size_s	equ 1024	; maximum string size to test

	ALIGN	16
	db 16 dup(0)
strings db size_s dup('x')
	db 16 dup(0)
arg_1	dq 0


	.code

	option	dllimport:<msvcrt>

printf			proto :ptr byte, :vararg
exit			proto :qword
strlen			proto :ptr
_getch			proto
__getmainargs		proto :ptr, :ptr, :ptr, :ptr, :ptr

	option	dllimport:<kernel32>

GetCurrentProcess	proto
CreateFileA		proto :ptr, :dword, :dword, :ptr, :dword, :dword, :ptr
ReadFile		proto :ptr, :ptr, :ptr, :ptr, :ptr
CloseHandle		proto :ptr
FlushInstructionCache	proto :ptr, :ptr, :ptr
VirtualProtect		proto :ptr, :ptr, :ptr, :ptr
SetPriorityClass	proto :ptr, :dword
Sleep			proto :ptr

	option	dllimport:NONE

size_p	equ 1024	; Max proc size
align	16
proc_x	db size_p dup(0)

;-------------------------------------------------------------------------------
; Read binary file
;-------------------------------------------------------------------------------

ReadProc PROC USES rbx rsi rdi ID	; 0..9

	local	file_name:qword,
		read_size:qword

	mov	rax,6E69622E30h		; 0.bin
	or	al,cl
	mov	file_name,rax
	lea	rdi,proc_x

	FlushInstructionCache(GetCurrentProcess(), rdi, size_p)

	xor	rax,rax
	mov	rcx,size_p/8
	rep	stosq

	xor	rdi,rdi
	.if	CreateFileA(addr file_name, 80000000h, edi, rdi, 3, edi, rdi) != -1

		mov	rbx,rax
		.if	ReadFile(rbx, addr proc_x, size_p, addr read_size, 0)
			mov	rdi,read_size
		.endif
		CloseHandle(rbx)
	.endif

	.if	!rdi
		printf("error reading: %s\n", addr file_name)
	.endif

	mov	rax,rdi
	ret
ReadProc ENDP

TestProc PROC USES rsi rdi rbx r12 count:QWORD, proc_id:QWORD

	mov	count,rcx
	mov	proc_id,rdx

	mov	rsi,rdx		; proc id 0..9

	xor	rax,rax
	lea	rbx,p_size
	lea	rbx,[rbx+rdx*8]
	mov	[rbx],eax	; proc size

	lea	rax,proc_p
	mov	rax,[rax+rdx*8] ; proc
	.if	!rax

		ReadProc( edx )
		mov	[rbx],eax
		test	eax,eax
		lea	rax,proc_x
		jz	toend
	.endif
	mov	r12,rax

	Sleep ( 0 )

	;
	; x64-Version of MichaelW's macros
	;

	HIGH_PRIORITY_CLASS	equ 80h
	NORMAL_PRIORITY_CLASS	equ 20h
	PAGE_EXECUTE_READ	equ 20h
	PAGE_EXECUTE_READWRITE	equ 40h

	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)

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
		dec	rbx
	.endw

	xor	rax,rax
	cpuid
	rdtsc
	sub	eax,edi
	sub	eax,esi
	mov	edi,eax

	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)

	shr	edi,10
	mov	rsi,proc_id
	lea	rcx,result
	add	[rcx+rsi*8],edi
	lea	r9,p_size
	mov	r9,[r9+rsi*8]
	lea	rax,info_p
	mov	rax,[rax+rsi*8]

	printf( "%9i cycles, rep(%i), code(%3i) %i.asm: %s\n",
		edi, count, r9, esi, rax )

	mov	eax,1
toend:
	ret
TestProc ENDP

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

validate_x PROC USES rsi rdi rbx x:QWORD

	mov	x,rcx

	lea	rax,proc_p
	mov	rsi,[rax+rcx*8]
	.if	!rsi
		.if	ReadProc( ecx )
			lea rsi,proc_x
		.endif
	.endif

	.if	rsi

		mov	rdi,rsi
		lea	rsi,strings
		add	rsi,size_s
		xor	rbx,rbx

		.while	rbx < 200 && nerror < 10

			mov	rcx,rsi
			call	rdi

			.if	rax != rbx
				printf( "error: rax = %i (%i) %u.asm\n", eax, ebx, x )
				inc	nerror
			.endif
			add	rbx,1
			sub	rsi,1
		.endw
	.else
		printf( "error load: %d.asm\n", x )
		inc	nerror
	.endif
	ret

validate_x ENDP

GetCycleCount proc uses rsi rdi rbx l1, l2, step, count

	mov	l1,	ecx
	mov	l2,	edx
	mov	step,	r8d
	mov	count,	r9d

	mov	rbx,rcx
	mov	rdi,rdx

	.while	edi >= ebx

		lea	rax,strings
		add	rax,size_s
		sub	rax,rbx
		mov	arg_1,rax

		printf( "-- strlen(%i)\n", ebx )
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

	printf( "\ntotal [%i .. %i], %i++\n", l1, l2, step )

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

		printf("%9i cycles %i.asm: %s\n", edx, r8d, r9d)
	.endw

	printf( "hit any key to continue...\n" )
	_getch()

	ret

GetCycleCount endp

main	proc argc:dword, argv:qword, environ:qword

	lea	rax,strings
	mov	arg_1,rax

	strlen(rax)
	mov	rax,__imp_strlen
	mov	proc_p,rax

	procs
		validate_x(x)
		cmp	nerror,0
		jne	error
	endm

	GetCycleCount( 1, 20, 1, 3000 )
;	GetCycleCount( 10, 70, 15, 2000 )
;	GetCycleCount( 70, 120, 4, 1000 )
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

	.if	!VirtualProtect( addr proc_x,
				size_p,
				PAGE_EXECUTE_READWRITE,
				addr lpflOldProtect )

		printf( "VirtualProtect error..\n" )
		exit  ( 1 )
	.endif

	exit( main( argc, argv, environ ) )

mainCRTStartup endp

	END	mainCRTStartup

