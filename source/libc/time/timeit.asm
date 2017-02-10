include stdio.inc
include time.inc
include timeit.inc
include process.inc

S_TIMEIT	STRUC
begin		dq ?
overhead	dq ?
result		dd ?
infotext	dd ?
S_TIMEIT	ENDS

.data
ALIGN 8	      ;; Optimal alignment for QWORD
__counter__qword__count__	dq 0
__counter__loop__count__	dd 100
__counter__loop__counter__	dd 0

tmtable S_TIMEIT 32 dup(<>)

	.code
	.686
	.xmm

counter_init PROC
	push	eax
	push	ecx
	push	edi
	lea	edi,tmtable
	xor	eax,eax
	mov	ecx,sizeof(tmtable) / 4
	rep	stosd
	pop	edi
	pop	ecx
	pop	eax
	ret
counter_init ENDP

	ASSUME	edi:PTR S_TIMEIT

counter_begin PROC index, info

	push	eax
	push	ecx
	push	edx
	push	ebx
	push	edi

	mov	eax,index
	mov	ecx,sizeof(S_TIMEIT)
	mul	ecx
	lea	edi,tmtable
	add	edi,eax
	mov	eax,info
	mov	[edi].infotext,eax

	call	GetCurrentProcess
	SetPriorityClass( eax, HIGH_PRIORITY_CLASS )

	xor	eax, eax	;; Use same CPUID input value for each call
	cpuid			;; Flush pipe & wait for pending ops to finish
	rdtsc			;; Read Time Stamp Counter
	push	edx		;; Preserve high-order 32 bits of start count
	push	eax		;; Preserve low-order 32 bits of start count
	mov	__counter__loop__counter__, 100
	xor	eax, eax
	cpuid			;; Make sure loop setup instructions finish
      ALIGN 16			;; Optimal loop alignment for P6
      @@:			;; Start an empty reference loop
	sub	__counter__loop__counter__, 1
	jnz	@B

	xor	eax, eax
	cpuid			;; Make sure loop instructions finish
	rdtsc			;; Read end count
	pop	ecx		;; Recover low-order 32 bits of start count
	sub	eax, ecx	;; Low-order 32 bits of overhead count in EAX
	pop	ecx		;; Recover high-order 32 bits of start count
	sbb	edx, ecx	;; High-order 32 bits of overhead count in EDX
	;
	; Preserve overhead count
	;
	mov	DWORD PTR [edi].overhead[4],edx
	mov	DWORD PTR [edi].overhead,eax

	xor	eax, eax
	cpuid
	rdtsc
	;
	; Preserve start count
	;
	mov	DWORD PTR [edi].begin[4],edx
	mov	DWORD PTR [edi].begin,eax
	xor	eax, eax
	cpuid			;; Make sure loop setup instructions finish

	pop	edi
	pop	ebx
	pop	edx
	pop	ecx
	pop	eax
	ret
counter_begin ENDP

counter_end PROC index
	pushfd
	push	ecx
	push	edx
	push	ebx
	push	edi
	mov	eax,index
	mov	ecx,sizeof(S_TIMEIT)
	mul	ecx
	lea	edi,tmtable
	add	edi,eax

	xor	eax, eax
	cpuid			;; Make sure loop instructions finish
	rdtsc			;; Read end count
	mov	ecx,DWORD PTR [edi].begin	;; Recover low-order 32 bits of start count
	sub	eax, ecx			;; Low-order 32 bits of test count in EAX
	mov	ecx,DWORD PTR [edi].begin[4]	;; Recover high-order 32 bits of start count
	sbb	edx, ecx			;; High-order 32 bits of test count in EDX
	mov	ecx,DWORD PTR [edi].overhead	;; Recover low-order 32 bits of overhead count
	sub	eax, ecx			;; Low-order 32 bits of adjusted count in EAX
	mov	ecx,DWORD PTR [edi].overhead[4] ;; Recover high-order 32 bits of overhead count
	sbb	edx, ecx			;; High-order 32 bits of adjusted count in EDX

	mov	DWORD PTR __counter__qword__count__, eax
	mov	DWORD PTR __counter__qword__count__ + 4, edx

	call	GetCurrentProcess
	SetPriorityClass( eax, NORMAL_PRIORITY_CLASS )

	ifdef _EMMS
	  EMMS
	endif

	finit
	fild	__counter__qword__count__
	fild	__counter__loop__count__
	fdiv
	fistp	__counter__qword__count__

	mov	eax, DWORD PTR __counter__qword__count__
	cmp	eax,0
	jl	@F
	add	[edi].result,eax
@@:
	pop	edi
	pop	ebx
	pop	edx
	pop	ecx
	popfd
	ret
counter_end ENDP

counter_exit PROC USES esi edi ebx edx ecx eax count, text

local	t:SYSTEMTIME, time[16]:SBYTE, date[16]:SBYTE

	GetLocalTime( addr t )
	strsdate( addr date, addr t )
	strstime( addr time, addr t )

	.if	fopen( "timeit.txt", "at+" )

		mov esi,eax
		fprintf( esi, "%s - %s %s:\n", text, addr date, addr time )

		lea	edi,tmtable
		xor	ebx,ebx
		.while	count

			fprintf( esi, "%2d:%12d %s\n", ebx, [edi].result, [edi].infotext )

			add edi,sizeof(S_TIMEIT)
			inc ebx
			dec count
		.endw
		fclose( esi )
	.endif
	ret

counter_exit ENDP

	END
