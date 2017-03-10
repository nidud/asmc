; v2.22 - .FOR[S] [<initialization>] : [<condition>] : [<increment/decrement>]

	.386
	.model	flat, c
	.code

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
	.for	edx = bar(1),
		ecx = bar(2),
		ebx = bar(3):,
		;
		; <condition>
		;
		edx > bar(1),
		ecx > bar(2),
		ebx > bar(3):,
		;
		; <increment/decrement>
		;
		edx = bar(1),
		ecx = bar(2),
		ebx = bar(3)
	.endf

		;
		; Return size
		;
	.for	edx = foo(bar(al),0,0,0),	; al
		ecx = foo(0,bar(al),0,0),	; ax
		ebx = foo(0,0,bar(al),0),	; eax
		eax = foo(0,0,0,bar(al)):,	; edx::eax
		edx > foo(bar(al),0,0,0),
		ecx > foo(0,bar(al),0,0),
		ebx > foo(0,0,bar(al),0),
		eax > foo(0,0,0,bar(al)):,
		edx = foo(bar(al),0,0,0),
		ecx = foo(0,bar(al),0,0),
		ebx = foo(0,0,bar(al),0),
		eax = foo(0,0,0,bar(al))
	.endf

	.for	eax = &foo,	; lea eax,foo
		eax =& foo,	; ...
		ecx =~ eax,	; mov ecx,not eax
		ebx = ~bar(0),
		ecx = ~eax ::	; ...
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
		esp = 0

	.endf

	END
