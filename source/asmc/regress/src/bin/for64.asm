; v2.22 - .FOR[S] [<initialization>] : [<condition>] : [<increment/decrement>]

	.x64
	.model	flat, fastcall
	.code

	; v2.27 --
	.for al <<= cl, al >>= 2, al |= cl, al ^= cl, al ~= cl, al &= cl ::
	.endf

	.FOR::
	.ENDF
	.FOR(::)
	.ENDF
	.FOR(cl=2::)
	.ENDF
	.FOR(:cl:)
	.ENDF
	.FOR(::cl--)
	.ENDF
	.FOR(cl=2:cl:)
	.ENDF
	.FOR(cl=2::cl--)
	.ENDF
	.FOR(cl=2:cl:cl--)
	.ENDF
	.FOR(cl=2,bl=al:cl<0:--cl,bl+=4)
	.ENDF
	.FOR::
	 .FOR::
	  .FOR::
	   .FOR::
		.CONTINUE(3)
		.CONTINUE(03)
		.BREAK(3)
	   .ENDF
	  .ENDF
	 .ENDF
	.ENDF

proto_1 typedef proto :byte
proto_4 typedef proto :byte, :word, :dword, :qword
proto_a typedef ptr proto_1
proto_b typedef ptr proto_4

	foo	proto_b 0
	bar	proto_a 0

		;
		; <initialization>
		;
	.for	rdx = bar(1),
		rcx = bar(2),
		rbx = bar(3):,
		;
		; <condition>
		;
		rdx > bar(1),
		rcx > bar(2),
		rbx > bar(3):,
		;
		; <increment/decrement>
		;
		rdx = bar(1),
		rcx = bar(2),
		rbx = bar(3)
	.endf

		;
		; Return size
		;
	.for	rdx = foo(bar(al),0,0,0),	; al
		rcx = foo(0,bar(al),0,0),	; ax
		rbx = foo(0,0,bar(al),0),	; eax
		rax = foo(0,0,0,bar(al)):,	; edx::eax
		rdx > foo(bar(al),0,0,0),
		rcx > foo(0,bar(al),0,0),
		rbx > foo(0,0,bar(al),0),
		rax > foo(0,0,0,bar(al)):,
		rdx = foo(bar(al),0,0,0),
		rcx = foo(0,bar(al),0,0),
		rbx = foo(0,0,bar(al),0),
		rax = foo(0,0,0,bar(al))
	.endf

	.for	rax = &foo,	; lea eax,foo
		rax =& foo,	; ...
		rcx =~ rax,	; mov ecx,not eax
		rbx = ~bar(0),
		rcx = ~rax ::	; ...
	.endf

		;
		; reg = 0 --> xor reg,reg
		;
	.for	 al = 0,
		 bl = 0,
		 cl = 0,
		 dl = 0,
		 ah = 0,
		 bh = 0,
		 ch = 0,
		 dh = 0,
		 ax = 0,
		 bx = 0,
		 cx = 0,
		 dx = 0,
		 si = 0,
		 di = 0,
		 bp = 0,
		 sp = 0,
		eax = 0,
		ebx = 0,
		ecx = 0,
		edx = 0,
		esi = 0,
		edi = 0,
		ebp = 0,
		esp = 0 ::,
		 al = 0,
		 bl = 0,
		 cl = 0,
		 dl = 0,
		 ah = 0,
		 bh = 0,
		 ch = 0,
		 dh = 0,
		 ax = 0,
		 bx = 0,
		 cx = 0,
		 dx = 0,
		 si = 0,
		 di = 0,
		 bp = 0,
		 sp = 0,
		eax = 0,
		ebx = 0,
		ecx = 0,
		edx = 0,
		esi = 0,
		edi = 0,
		ebp = 0,
		esp = 0,
		R8B = 0,
		R9B = 0,
		R10B = 0,
		R11B = 0,
		R12B = 0,
		R13B = 0,
		R14B = 0,
		R15B = 0,
		R8W  = 0,
		R9W  = 0,
		R10W = 0,
		R11W = 0,
		R12W = 0,
		R13W = 0,
		R14W = 0,
		R15W = 0,
		R8D = 0,
		R9D = 0,
		R10D = 0,
		R11D = 0,
		R12D = 0,
		R13D = 0,
		R14D = 0,
		R15D = 0,
		RAX = 0,
		RCX = 0,
		RDX = 0,
		RBX = 0,
		RSP = 0,
		RBP = 0,
		RSI = 0,
		RDI = 0,
		R8 = 0,
		R9 = 0,
		R10 = 0,
		R11 = 0,
		R12 = 0,
		R13 = 0,
		R14 = 0,
		R15 = 0
	.endf

	END
