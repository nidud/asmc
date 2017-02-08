;
; From MichaelW's timer macros - /masm32/macros/timers.asm
;
.xlist

counter_init	PROTO
counter_begin	PROTO :DWORD, :DWORD
counter_end	PROTO :DWORD
counter_exit	PROTO :DWORD, :DWORD


timeit_init macro
ifdef __TIMEIT__
	counter_init()
endif
	endm

timeit_start macro id, text
ifdef __TIMEIT__
	counter_begin(id, text)
endif
	endm

timeit_end macro id
ifdef __TIMEIT__
	push	eax
	counter_end(id)
	pop	eax
endif
	endm

timeit_exit macro count, text
ifdef __TIMEIT__
	counter_exit(count,text)
endif
	endm

.list
